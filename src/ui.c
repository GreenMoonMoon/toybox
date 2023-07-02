//
// Created by josue on 2023-06-20.
//
#include "ui.h"
#include <stddef.h>
#include <string.h>
//#include "example/calculator.h"
#include "example/node_editor.h"
//#include "example/overview.h"
#include "example/style.c"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#include "nuklear.h"
#include "glad/gl.h"
#include "viewport.h"


#define MAX_VERTEX_MEMORY (512 * 1024)
#define MAX_ELEMENT_MEMORY (128 * 1024)

struct nk_sdl_device {
  struct nk_buffer cmds;
  struct nk_draw_null_texture null;
  GLuint vbo, vao, ebo;
  GLuint prog;
  GLuint vert_shdr;
  GLuint frag_shdr;
  GLint attrib_pos;
  GLint attrib_uv;
  GLint attrib_col;
  GLint uniform_tex;
  GLint uniform_proj;
  GLuint font_tex;
};

struct nk_sdl_vertex {
  float position[2];
  float uv[2];
  nk_byte col[4];
};

static struct nk_sdl {
  SDL_Window *win;
  struct nk_sdl_device ogl;
  struct nk_context ctx;
  struct nk_font_atlas atlas;
} sdl;

static struct nk_colorf bg;

static void ui_device_create(void) {
    GLint status;

    // language=GLSL
    static const GLchar *vertex_shader =
        "#version 460 core\n\nuniform mat4 ProjMtx;\nin vec2 Position;\nin vec2 TexCoord;\nin vec4 Color;\nout vec2 Frag_UV;\nout vec4 Frag_Color;\n\nvoid main() {\n    Frag_UV = TexCoord;\n    Frag_Color = Color;\n    gl_Position = ProjMtx * vec4(Position.xy, 0, 1);\n}";

    // language=GLSL
    static const GLchar *fragment_shader =
        "#version 460 core\nprecision mediump float;\nuniform sampler2D Texture;\nin vec2 Frag_UV;\nin vec4 Frag_Color;\nout vec4 Out_Color;\n\nvoid main(){\n    Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n}\n";

    struct nk_sdl_device *dev = &sdl.ogl;
    nk_buffer_init_default(&dev->cmds);
    dev->prog = glCreateProgram();
    dev->vert_shdr = glCreateShader(GL_VERTEX_SHADER);
    dev->frag_shdr = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(dev->vert_shdr, 1, &vertex_shader, 0);
    glShaderSource(dev->frag_shdr, 1, &fragment_shader, 0);
    glCompileShader(dev->vert_shdr);
    glCompileShader(dev->frag_shdr);
    glGetShaderiv(dev->vert_shdr, GL_COMPILE_STATUS, &status);
    // assert(status == GL_TRUE);
    glGetShaderiv(dev->frag_shdr, GL_COMPILE_STATUS, &status);
    // assert(status == GL_TRUE);
    glAttachShader(dev->prog, dev->vert_shdr);
    glAttachShader(dev->prog, dev->frag_shdr);
    glLinkProgram(dev->prog);
    glGetProgramiv(dev->prog, GL_LINK_STATUS, &status);
    // assert(status == GL_TRUE);

    dev->uniform_tex = glGetUniformLocation(dev->prog, "Texture");
    dev->uniform_proj = glGetUniformLocation(dev->prog, "ProjMtx");
    dev->attrib_pos = glGetAttribLocation(dev->prog, "Position");
    dev->attrib_uv = glGetAttribLocation(dev->prog, "TexCoord");
    dev->attrib_col = glGetAttribLocation(dev->prog, "Color");

    {
        /* buffer setup */
        GLsizei vs = sizeof(struct nk_sdl_vertex);
        size_t vp = offsetof(struct nk_sdl_vertex, position);
        size_t vt = offsetof(struct nk_sdl_vertex, uv);
        size_t vc = offsetof(struct nk_sdl_vertex, col);

        glGenBuffers(1, &dev->vbo);
        glGenBuffers(1, &dev->ebo);
        glGenVertexArrays(1, &dev->vao);

        glBindVertexArray(dev->vao);
        glBindBuffer(GL_ARRAY_BUFFER, dev->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dev->ebo);

        glEnableVertexAttribArray((GLuint) dev->attrib_pos);
        glEnableVertexAttribArray((GLuint) dev->attrib_uv);
        glEnableVertexAttribArray((GLuint) dev->attrib_col);

        glVertexAttribPointer((GLuint) dev->attrib_pos, 2, GL_FLOAT, GL_FALSE, vs, (void *) vp);
        glVertexAttribPointer((GLuint) dev->attrib_uv, 2, GL_FLOAT, GL_FALSE, vs, (void *) vt);
        glVertexAttribPointer((GLuint) dev->attrib_col, 4, GL_UNSIGNED_BYTE, GL_TRUE, vs, (void *) vc);
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void nk_sdl_device_upload_atlas(const void *image, int width, int height) {
    struct nk_sdl_device *dev = &sdl.ogl;
    glGenTextures(1, &dev->font_tex);
    glBindTexture(GL_TEXTURE_2D, dev->font_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei) width, (GLsizei) height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, image);
}

static void ui_device_delete(void) {
    struct nk_sdl_device *dev = &sdl.ogl;
    glDetachShader(dev->prog, dev->vert_shdr);
    glDetachShader(dev->prog, dev->frag_shdr);
    glDeleteShader(dev->vert_shdr);
    glDeleteShader(dev->frag_shdr);
    glDeleteProgram(dev->prog);
    glDeleteTextures(1, &dev->font_tex);
    glDeleteBuffers(1, &dev->vbo);
    glDeleteBuffers(1, &dev->ebo);
    nk_buffer_free(&dev->cmds);
}

static void clipboard_paste(nk_handle usr, struct nk_text_edit *edit) {
    const char *text = SDL_GetClipboardText();
    if (text) nk_textedit_paste(edit, text, nk_strlen(text));
    (void) usr;
}

static void clipboard_copy(nk_handle usr, const char *text, int len) {
    char *str = 0;
    (void) usr;
    if (!len) return;
    str = (char *) malloc((size_t) len + 1);
    if (!str) return;
    memcpy(str, text, (size_t) len);
    str[len] = '\0';
    SDL_SetClipboardText(str);
    free(str);
}

struct nk_context *ui_init(struct Viewport *viewport) {
    sdl.win = (SDL_Window *) viewport_get_window(viewport);
    nk_init_default(&sdl.ctx, 0);
    sdl.ctx.clip.copy = clipboard_copy;
    sdl.ctx.clip.paste = clipboard_paste;
    sdl.ctx.clip.userdata = nk_handle_ptr(0);
    ui_device_create();
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    return &sdl.ctx;
}

void ui_draw(enum nk_anti_aliasing AA, int max_vertex_buffer, int max_element_buffer) {
    struct nk_sdl_device *dev = &sdl.ogl;
    int width, height;
    int display_width, display_height;
    struct nk_vec2 scale;
    GLfloat ortho[4][4] = {
        {2.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, -2.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, -1.0f, 0.0f},
        {-1.0f, 1.0f, 0.0f, 1.0f},
    };
    SDL_GetWindowSize(sdl.win, &width, &height);
    SDL_GL_GetDrawableSize(sdl.win, &display_width, &display_height);
    ortho[0][0] /= (GLfloat) width;
    ortho[1][1] /= (GLfloat) height;

    scale.x = (float) display_width / (float) width;
    scale.y = (float) display_height / (float) height;

    /* setup global state */
    glViewport(0, 0, display_width, display_height);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);
    glActiveTexture(GL_TEXTURE0);

    /* setup program */
    glUseProgram(dev->prog);
    glUniform1i(dev->uniform_tex, 0);
    glUniformMatrix4fv(dev->uniform_proj, 1, GL_FALSE, &ortho[0][0]);
    {
        /* convert from command queue into draw list and draw to screen */
        const struct nk_draw_command *cmd;
        void *vertices, *elements;
        const nk_draw_index *offset = NULL;
        struct nk_buffer vbuf, ebuf;

        /* allocate vertex and element buffer */
        glBindVertexArray(dev->vao);
        glBindBuffer(GL_ARRAY_BUFFER, dev->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dev->ebo);

        glBufferData(GL_ARRAY_BUFFER, max_vertex_buffer, NULL, GL_STREAM_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_element_buffer, NULL, GL_STREAM_DRAW);

        /* load vertices/elements directly into vertex/element buffer */
        vertices = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        elements = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
        {
            /* fill convert configuration */
            struct nk_convert_config config;
            static const struct nk_draw_vertex_layout_element vertex_layout[] = {
                {NK_VERTEX_POSITION, NK_FORMAT_FLOAT, NK_OFFSETOF(struct nk_sdl_vertex, position)},
                {NK_VERTEX_TEXCOORD, NK_FORMAT_FLOAT, NK_OFFSETOF(struct nk_sdl_vertex, uv)},
                {NK_VERTEX_COLOR, NK_FORMAT_R8G8B8A8, NK_OFFSETOF(struct nk_sdl_vertex, col)},
                {NK_VERTEX_LAYOUT_END}
            };
            NK_MEMSET(&config, 0, sizeof(config));
            config.vertex_layout = vertex_layout;
            config.vertex_size = sizeof(struct nk_sdl_vertex);
            config.vertex_alignment = NK_ALIGNOF(struct nk_sdl_vertex);
//            config.null = dev->null;
            config.circle_segment_count = 22;
            config.curve_segment_count = 22;
            config.arc_segment_count = 22;
            config.global_alpha = 1.0f;
            config.shape_AA = AA;
            config.line_AA = AA;

            /* setup buffers to load vertices and elements */
            nk_buffer_init_fixed(&vbuf, vertices, (nk_size) max_vertex_buffer);
            nk_buffer_init_fixed(&ebuf, elements, (nk_size) max_element_buffer);
            nk_convert(&sdl.ctx, &dev->cmds, &vbuf, &ebuf, &config);
        }
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

        /* iterate over and execute each draw command */
        nk_draw_foreach(cmd, &sdl.ctx, &dev->cmds) {
            if (!cmd->elem_count) continue;
            glBindTexture(GL_TEXTURE_2D, (GLuint) cmd->texture.id);
            glScissor((GLint) (cmd->clip_rect.x * scale.x),
                      (GLint) ((height - (GLint) (cmd->clip_rect.y + cmd->clip_rect.h)) * scale.y),
                      (GLint) (cmd->clip_rect.w * scale.x),
                      (GLint) (cmd->clip_rect.h * scale.y));
            glDrawElements(GL_TRIANGLES, (GLsizei) cmd->elem_count, GL_UNSIGNED_SHORT, offset);
            offset += cmd->elem_count;
        }
        nk_clear(&sdl.ctx);
    }

    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glDisable(GL_BLEND);
    glDisable(GL_SCISSOR_TEST);
}

static void ui_font_stash_begin(struct nk_font_atlas **atlas) {
    nk_font_atlas_init_default(&sdl.atlas);
    nk_font_atlas_begin(&sdl.atlas);
    *atlas = &sdl.atlas;
}

static void ui_font_stash_end(void) {
    const void *image;
    int w, h;
    image = nk_font_atlas_bake(&sdl.atlas, &w, &h, NK_FONT_ATLAS_RGBA32);
    nk_sdl_device_upload_atlas(image, w, h);
    nk_font_atlas_end(&sdl.atlas, nk_handle_id((int) sdl.ogl.font_tex), &sdl.ogl.null);
    if (sdl.atlas.default_font)
        nk_style_set_font(&sdl.ctx, &sdl.atlas.default_font->handle);

}

int ui_handle_event(SDL_Event *event) {
    struct nk_context *ctx = &sdl.ctx;
    if (event->type == SDL_KEYUP || event->type == SDL_KEYDOWN) {
        /* key events */
        int down = event->type == SDL_KEYDOWN;
        const Uint8 *state = SDL_GetKeyboardState(0);
        SDL_Keycode sym = event->key.keysym.sym;
        if (sym == SDLK_RSHIFT || sym == SDLK_LSHIFT)
            nk_input_key(ctx, NK_KEY_SHIFT, down);
        else if (sym == SDLK_DELETE)
            nk_input_key(ctx, NK_KEY_DEL, down);
        else if (sym == SDLK_RETURN)
            nk_input_key(ctx, NK_KEY_ENTER, down);
        else if (sym == SDLK_TAB)
            nk_input_key(ctx, NK_KEY_TAB, down);
        else if (sym == SDLK_BACKSPACE)
            nk_input_key(ctx, NK_KEY_BACKSPACE, down);
        else if (sym == SDLK_HOME) {
            nk_input_key(ctx, NK_KEY_TEXT_START, down);
            nk_input_key(ctx, NK_KEY_SCROLL_START, down);
        } else if (sym == SDLK_END) {
            nk_input_key(ctx, NK_KEY_TEXT_END, down);
            nk_input_key(ctx, NK_KEY_SCROLL_END, down);
        } else if (sym == SDLK_PAGEDOWN) {
            nk_input_key(ctx, NK_KEY_SCROLL_DOWN, down);
        } else if (sym == SDLK_PAGEUP) {
            nk_input_key(ctx, NK_KEY_SCROLL_UP, down);
        } else if (sym == SDLK_z)
            nk_input_key(ctx, NK_KEY_TEXT_UNDO, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_r)
            nk_input_key(ctx, NK_KEY_TEXT_REDO, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_c)
            nk_input_key(ctx, NK_KEY_COPY, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_v)
            nk_input_key(ctx, NK_KEY_PASTE, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_x)
            nk_input_key(ctx, NK_KEY_CUT, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_b)
            nk_input_key(ctx, NK_KEY_TEXT_LINE_START, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_e)
            nk_input_key(ctx, NK_KEY_TEXT_LINE_END, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_UP)
            nk_input_key(ctx, NK_KEY_UP, down);
        else if (sym == SDLK_DOWN)
            nk_input_key(ctx, NK_KEY_DOWN, down);
        else if (sym == SDLK_LEFT) {
            if (state[SDL_SCANCODE_LCTRL])
                nk_input_key(ctx, NK_KEY_TEXT_WORD_LEFT, down);
            else nk_input_key(ctx, NK_KEY_LEFT, down);
        } else if (sym == SDLK_RIGHT) {
            if (state[SDL_SCANCODE_LCTRL])
                nk_input_key(ctx, NK_KEY_TEXT_WORD_RIGHT, down);
            else nk_input_key(ctx, NK_KEY_RIGHT, down);
        } else return 0;
        return 1;
    } else if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
        /* mouse button */
        int down = event->type == SDL_MOUSEBUTTONDOWN;
        const int x = event->button.x, y = event->button.y;
        if (event->button.button == SDL_BUTTON_LEFT) {
            if (event->button.clicks > 1)
                nk_input_button(ctx, NK_BUTTON_DOUBLE, x, y, down);
            nk_input_button(ctx, NK_BUTTON_LEFT, x, y, down);
        } else if (event->button.button == SDL_BUTTON_MIDDLE)
            nk_input_button(ctx, NK_BUTTON_MIDDLE, x, y, down);
        else if (event->button.button == SDL_BUTTON_RIGHT)
            nk_input_button(ctx, NK_BUTTON_RIGHT, x, y, down);
        return 1;
    } else if (event->type == SDL_MOUSEMOTION) {
        /* mouse motion */
        if (ctx->input.mouse.grabbed) {
            int x = (int) ctx->input.mouse.prev.x, y = (int) ctx->input.mouse.prev.y;
            nk_input_motion(ctx, x + event->motion.xrel, y + event->motion.yrel);
        } else nk_input_motion(ctx, event->motion.x, event->motion.y);
        return 1;
    } else if (event->type == SDL_TEXTINPUT) {
        /* text input */
        nk_glyph glyph;
        memcpy(glyph, event->text.text, NK_UTF_SIZE);
        nk_input_glyph(ctx, glyph);
        return 1;
    } else if (event->type == SDL_MOUSEWHEEL) {
        /* mouse wheel */
        nk_input_scroll(ctx, nk_vec2((float) event->wheel.x, (float) event->wheel.y));
        return 1;
    }
    return 0;
}

void ui_load_fonts(struct nk_context *ctx, struct nk_font_atlas *atlas) {
    ui_font_stash_begin(&atlas);
    struct nk_font
        *jetbrains = nk_font_atlas_add_from_file(atlas, "assets/font/jetbrains/JetBrainsMono-Regular.ttf", 14, 0);
    ui_font_stash_end();

    nk_style_load_all_cursors(ctx, atlas->cursors);
    nk_style_set_font(ctx, &jetbrains->handle);
}

void ui_draw_demo(struct nk_context *ctx) {
    nk_clear(ctx);
    if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
                 NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
                     NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
        nk_layout_row_static(ctx, 30, 80, 1);

        static int property = 1;

        if (nk_button_label(ctx, "button"))
            printf("button pressed!\n");
        nk_layout_row_dynamic(ctx, 30, 2);
        nk_option_label(ctx, "easy", 0);
        nk_option_label(ctx, "hard", 1);
        nk_layout_row_dynamic(ctx, 22, 1);
        nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "background:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 25, 1);
        if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx), 400))) {
            nk_layout_row_dynamic(ctx, 120, 1);
            bg = nk_color_picker(ctx, bg, NK_RGBA);
            nk_layout_row_dynamic(ctx, 25, 1);
            bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f, 0.005f);
            bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f, 0.005f);
            bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f, 0.005f);
            bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f, 0.005f);
            nk_combo_end(ctx);
        }
    }
    nk_end(ctx);

//    overview(ctx);
//    calculator(ctx);
    node_editor(ctx);

    /* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
    ui_draw(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
}

void ui_delete(void) {
    nk_font_atlas_clear(&sdl.atlas);
    nk_free(&sdl.ctx);
    ui_device_delete();
    memset(&sdl, 0, sizeof(sdl));
}
void ui_event_start(struct nk_context *context) {
    nk_input_begin(context);
}

void ui_event_end(struct nk_context *context) {
    nk_input_end(context);
}

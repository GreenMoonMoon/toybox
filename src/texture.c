//
// Created by josue on 2023-06-15.
//

#include "texture.h"
#include "io/file.h"
#include "glad/gl.h"

static Texture load_texture(uint8_t *image_data, int32_t width, int32_t height){
    GLuint handle;
    glCreateTextures(GL_TEXTURE_2D, 1, &handle); //the "texture" keyword without any qualifiers default to a 2D texture
    glTextureStorage2D(handle, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(handle, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    Texture result = {
        .texture_handle = handle,
        .sampler_handle = 0,
    };
    return result;
}

Texture load_texture_from_png(const char *filename) {
    uint8_t *image_data;
    int32_t width;
    int32_t height;
    size_t image_buffer_size = read_png_file(filename, &image_data, &width, &height);

    Texture result = load_texture(image_data, width, height);
    return result;
}

void texture_unload(Texture texture) {
    glDeleteTextures(1, &texture.texture_handle);
}

void texture_enable(Texture texture, int32_t unit) {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture.texture_handle);
}

//
// Created by josue on 2023-02-16.
//

#include "mesh.h"
#include <string.h>
#include "camera.h"
#include "shader.h"
#include "types.h"
#include "glad/gl.h"

struct GenericVertex {
  vec3 position;
  vec3 normal;
  vec2 uv;
};

uint32_t mesh_load_vertex_buffer(Mesh *mesh, const u8 *vertices, i32 vertex_size, isize vertex_count) {
    GLuint buffer;
    glCreateBuffers(1, &buffer);

    glNamedBufferData(buffer, (i64) (vertex_size * vertex_count), vertices, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &mesh->vao);
    glVertexArrayVertexBuffer(mesh->vao, 0, buffer, 0, vertex_size);

}

void mesh_load(Mesh mesh) {
    GLuint buffers[2];
    glCreateBuffers(2, buffers);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, (int64_t) mesh.data.vertices_data, mesh.data.vertices_data, GL_STATIC_DRAW);
    GLintptr base_offset = 0;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (int64_t) mesh.data.indices_data_size, mesh.data.indices_data, GL_STATIC_DRAW);

    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, buffers[0], base_offset, mesh.data.vertex_size); // Bind a buffer to binding point 0
    glVertexArrayElementBuffer(vao, buffers[1]);

    // FIXME: use an attribute object to manage non-conform vertex struct
    mesh_set_vertex_attribute(mesh, 0, 3, 0);
    mesh_set_vertex_attribute(mesh, 1, 3, sizeof(vec3));
    mesh_set_vertex_attribute(mesh, 2, 2, sizeof(vec3) + sizeof(vec3));

    mesh.vao = vao;
    mesh.buffers[0] = buffers[0];
    mesh.buffers[1] = buffers[1];
    mesh.index_count = mesh.data.indices_data_size / sizeof(i32);
}

void mesh_set_vertex_attribute(Mesh mesh, u32 attribute_index, i32 attribute_dimension, i32 offset) {
    glEnableVertexArrayAttrib(mesh.vao, attribute_index);
    glVertexArrayAttribFormat(mesh.vao, attribute_index, attribute_dimension, GL_FLOAT, GL_FALSE, offset);
    glVertexArrayAttribBinding(mesh.vao, attribute_index, 0); // Bind attribute location to binding point
}

void mesh_unload(Mesh mesh) {
    // Check and unbind vertex array before deleting it
    i32 bound_vao;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &bound_vao);
    if (bound_vao == mesh.vao) glBindVertexArray(0);

    glDeleteBuffers(2, mesh.buffers);
    glDeleteVertexArrays(1, &mesh.vao);
}

void mesh_delete(Mesh mesh) {
    mesh_unload(mesh);
    if (mesh.data.vertices_data) free(mesh.data.vertices_data);
    if (mesh.data.indices_data) free(mesh.data.indices_data);
}

//Mesh create_primitive(const Vertex *vertices, size_t vertices_size, const uint32_t *indices, size_t indices_size) {
//    uint32_t vertex_count = vertices_size / sizeof(Vertex);
//    uint32_t index_count = indices_size / sizeof(uint32_t);
//
//    Mesh mesh = load_mesh(vertices, vertex_count, indices, index_count);
//    mesh_set_vertex_attribute(mesh, 0, 3, offsetof(Vertex, position));
//    mesh_set_vertex_attribute(mesh, 2, 2, offsetof(Vertex, uv));
//
//    mesh.vertices = malloc(vertices_size);
//    memcpy(mesh.vertices, vertices_size, vertices, vertices_size);
//    mesh.vertex_count = vertex_count;
//
//    mesh.indices = malloc(indices_size);
//    memcpy(mesh.indices, indices_size, indices, indices_size);
//
//    return mesh;
//}
#define CREATE_PRIMITIVE(V, I) create_primitive(V, sizeof(V), I, sizeof(I))

Mesh new_quad_mesh(f32 width, f32 height) {
    const struct GenericVertex vertices[] = {
        {{0.0f, height, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
        {{width, 0.0f, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
        {{width, height, 0.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},
    };

    const u32 indices[] = {
        0, 1, 2, 2, 3, 0,
    };

    Mesh mesh = {0};
    mesh.data.vertices_data = malloc(sizeof(vertices));
    if (mesh.data.vertices_data) {
        memcpy(mesh.data.vertices_data, vertices, sizeof(vertices));
        mesh.data.vertices_data_size = sizeof(vertices);
        mesh.data.vertex_size = sizeof(struct GenericVertex);
    }
    mesh.data.indices_data = malloc(sizeof(indices));
    if (mesh.data.indices_data) {
        memcpy(mesh.data.indices_data, indices, sizeof(indices));
        mesh.data.indices_data_size = sizeof(indices);
    }

    return mesh;
}

Mesh new_cube_mesh(f32 width, f32 height, f32 depth) {
    const struct GenericVertex vertices[] = {
        {{0.0f, height, 0.0f}, {0.57535f, -0.57535f, 0.57535f}, {0.0f, 1.0f}},
        {{0.0f, 0.0f, 0.0f}, {0.57535f, 0.57535f, 0.57535f}, {0.0f, 0.0f}},
        {{width, 0.0f, 0.0f}, {-0.57535f, 0.57535f, 0.57535f}, {1.0f, 0.0f}},
        {{width, height, 0.0f}, {-0.57535f, -0.57535f, 0.57535f}, {1.0f, 1.0f}},
        {{0.0f, height, depth}, {0.57535f, -0.57535f, -0.57535f}, {0.0f, 1.0f}},
        {{0.0f, 0.0f, depth}, {0.57535f, 0.57535f, -0.57535f}, {0.0f, 0.0f}},
        {{width, 0.0f, depth}, {-0.57535f, 0.57535f, -0.57535f}, {1.0f, 0.0f}},
        {{width, height, depth}, {-0.57535f, -0.57535f, -0.57535f}, {1.0f, 1.0f}},
    };

    const u32 indices[] = {
        1, 0, 2, 3, 2, 0,
        2, 3, 6, 7, 6, 3,
        6, 7, 5, 4, 5, 7,
        5, 4, 1, 0, 1, 4,
        0, 4, 3, 7, 3, 4,
        5, 1, 6, 2, 6, 1,
    };

    Mesh mesh = {0};
    mesh.data.vertices_data = malloc(sizeof(vertices));
    if (mesh.data.vertices_data) {
        memcpy(mesh.data.vertices_data, vertices, sizeof(vertices));
        mesh.data.vertices_data_size = sizeof(vertices);
        mesh.data.vertex_size = sizeof(struct GenericVertex);
    }
    mesh.data.indices_data = malloc(sizeof(indices));
    if (mesh.data.indices_data) {
        memcpy(mesh.data.indices_data, indices, sizeof(indices));
        mesh.data.indices_data_size = sizeof(indices);
    }

    return mesh;
}

Mesh new_grid_mesh(f32 width, f32 depth, i32 subdivision_x, i32 subdivision_y) {
    Mesh mesh = {0};

    // Generate vertices
    f32 quad_width = width / (f32) (subdivision_x + 1);
    f32 quad_height = depth / (f32) (subdivision_y + 1);
    f32 uv_factor_x = 1.0f / (f32) (subdivision_x + 2);
    f32 uv_factor_y = 1.0f / (f32) (subdivision_y + 2);

    i32 vertex_count = (subdivision_x + 2) * (subdivision_y + 2);
    isize vertices_size = vertex_count * sizeof(struct GenericVertex);
    struct GenericVertex *vertices_data = malloc(vertices_size);
    if (mesh.data.vertices_data) {
        for (i32 y = 0; y < subdivision_y + 2; ++y) {
            for (i32 x = 0; x < subdivision_x + 2; ++x) {
                i32 vi = y * (subdivision_x + 2) + x;
                vertices_data[vi] = (struct GenericVertex) {
                    .position = {(f32) x * quad_width, 0.0f, (f32) y * quad_height},
                    .normal = {0.0f, 1.0f, 0.0f},
                    .uv = {(f32) x * uv_factor_x, (f32) y * uv_factor_y},
                };
            }
        }
        mesh.data.vertices_data = (u8*)vertices_data;
        mesh.data.vertices_data_size = vertices_size;
        mesh.data.vertex_size = sizeof(struct GenericVertex);
    }

    // Generate indices
    i32 index_count = ((subdivision_x + 1) * (subdivision_y + 1)) * 6;
    isize indices_size = index_count * sizeof(u32);
    mesh.data.indices_data = malloc(indices_size);
    if (mesh.data.indices_data) {
        u32 index = 0;
        for (i32 y = 0; y < subdivision_y + 1; ++y) {
            for (i32 x = 0; x < subdivision_x + 1; ++x) {
                u32 bl = y * (subdivision_x + 2) + x;          // bottom left
                u32 tl = (y + 1) * (subdivision_x + 2) + x;     // top left
                u32 br = y * (subdivision_x + 2) + x + 1;      // bottom right
                u32 tr = (y + 1) * (subdivision_x + 2) + x + 1; // top right

                // first quad triangle
                mesh.data.indices_data[index++] = br;
                mesh.data.indices_data[index++] = bl;
                mesh.data.indices_data[index++] = tl;

                // second quad triangle
                mesh.data.indices_data[index++] = tl;
                mesh.data.indices_data[index++] = tr;
                mesh.data.indices_data[index++] = br;
            }
        }
        mesh.data.indices_data_size = sizeof(indices_size);
    }

    return mesh;
}

void mesh_draw_generic(Mesh mesh, mat4 transform, struct Camera *camera) {
    glBindVertexArray(mesh.vao);
    shader_enable(default_generic_shader);
    shader_set_mvp(default_generic_shader, transform, camera->transform, camera->projection);
    glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
}

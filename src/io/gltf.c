#include "gltf.h"
#include <stdlib.h>
#include <stdio.h>
#include "model.h"
#define CGLTF_IMPLEMENTATION
#include "cgltf.h"

typedef struct GpuBufferList {
    uint32_t *handles;
    cgltf_buffer_view *buffer_views;
    uint32_t buffer_view_count;
} GpuBufferList;

void print_result(cgltf_result result){
    char *message;
    switch (result) {
        case cgltf_result_data_too_short:
            message = "Data is too short";
            break;
        case cgltf_result_unknown_format:
            message = "Unknown format";
            break;
        case cgltf_result_invalid_json:
            message = "Invalid JSON";
            break;
        case cgltf_result_invalid_gltf:
            message = "Invalid GLTF";
            break;
        case cgltf_result_file_not_found:
            message = "File not found";
            break;
        case cgltf_result_io_error:
            // todo: print the io error
            message = "IO error";
            break;
        case cgltf_result_out_of_memory:
            message = "Out of memory";
            break;
        case cgltf_result_legacy_gltf:
            message = "Legacy GLTF not supported";
            break;
        default:
            message = "";
            break;
    }
    fprintf(stderr, "ERROR GLTF: %s", message);
}

uint32_t load_buffer(cgltf_buffer_view *buffer_view){
    uint32_t handle = 0;
    void *data = (void *)((uintptr_t)buffer_view->buffer->data + buffer_view->offset);
    switch (buffer_view->type) {
        case cgltf_buffer_view_type_indices:
            handle = load_static_element_array_buffer(buffer_view->size, data);
            break;
        case cgltf_buffer_view_type_vertices:
            handle = load_static_array_buffer(buffer_view->size, data);
            break;
        default:
            break;
    }
    return handle;
}

uint32_t get_buffer_handle(cgltf_buffer_view *buffer_view, GpuBufferList *gpu_buffer_list) {
    for (int i = 0; i < gpu_buffer_list->buffer_view_count; ++i) {
        if(buffer_view == &gpu_buffer_list->buffer_views[i]) {
            uint32_t handle = gpu_buffer_list->handles[i];
            if (handle == 0){
                handle = load_buffer(buffer_view);
                gpu_buffer_list->handles[i] = handle;
            }
            return handle;
        }
    }
    return 0;
}

size_t gltf_load_meshes_from_file(const char *filename, struct Mesh **meshes) {
    cgltf_options options = {0};
    cgltf_data *data;

    size_t mesh_count = 0;

    cgltf_result result = cgltf_parse_file(&options, filename, &data);
    if (result == cgltf_result_success) {
        cgltf_load_buffers(&options, data, filename);
        GpuBufferList gpu_buffer_list = {
                .buffer_views = data->buffer_views,
                .buffer_view_count = data->buffer_views_count,
                .handles = calloc(data->buffer_views_count, sizeof(uint32_t)),
        };

        // Load Meshes

        //    Mesh mesh = {
        //        .primitive_count = 1,
        //        .primitives = malloc(sizeof(Primitive)),
        //    };
        //    init_primitive(TRIANGLES_DRAW_MODE, mesh.primitives);
        //    uint32_t vertex_position_handle = load_static_array_buffer(sizeof(cube_vertices), &cube_vertices);
        //    GpuBufferView vertex_position_buffer = {
        //            .handle = vertex_position_handle,
        //            .offset = 0,
        //            .stride = 3 * sizeof(float),
        //    };
        //    uint32_t indices_handle = load_static_element_array_buffer(sizeof(cube_indices), &cube_indices);
        //
        //    set_primitive_attribute_3f(POSITION_INDEX, 0, 0, vertex_position_buffer, mesh.primitives);
        //    set_primitive_indices(8, indices_handle, mesh.primitives);

        mesh_count = data->meshes_count;
        *meshes = malloc(mesh_count * sizeof(Mesh));
        for (int i = 0; i < mesh_count; ++i) {
            cgltf_mesh *mesh_data = &data->meshes[i];
            Mesh *mesh = &(*meshes)[i];

            mesh->primitive_count = mesh_data->primitives_count;
            mesh->primitives = malloc(mesh_data->primitives_count * sizeof(Primitive));

            for (int j = 0; j < mesh_data->primitives_count; ++j) {
                cgltf_primitive *primitive_data = &mesh_data->primitives[j];

                DrawMode mode;
                switch(primitive_data->type){
                    case cgltf_primitive_type_points:
                        mode = POINTS_DRAW_MODE;
                        break;
                    case cgltf_primitive_type_lines:
                        mode = LINES_DRAW_MODE;
                        break;
                    case cgltf_primitive_type_line_loop:
                        mode = LINE_LOOPS_DRAW_MODE;
                        break;
                    case cgltf_primitive_type_line_strip:
                        mode = LINE_STRIPS_DRAW_MODE;
                        break;
                    case cgltf_primitive_type_triangle_strip:
                        mode = TRIANGLE_STRIPS_DRAW_MODE;
                        break;
                    case cgltf_primitive_type_triangle_fan:
                        mode = TRIANGLE_FANS_DRAW_MODE;
                        break;
                    default:
                        mode = TRIANGLES_DRAW_MODE;
                        break;
                }
                init_primitive(mode, &mesh->primitives[j]);

                for (int k = 0; k < primitive_data->attributes_count; ++k) {
                    uint32_t binding_index = k;
                    cgltf_attribute *attribute = &primitive_data->attributes[k];
                    cgltf_accessor *accessor = attribute->data;

                    GpuBufferView buffer = {
                            .handle = get_buffer_handle(accessor->buffer_view, &gpu_buffer_list),
                            .stride = accessor->stride,
                            .offset = accessor->offset,
                    };

                    switch(attribute->type){
                        case cgltf_attribute_type_position:
                            set_primitive_attribute_3f(accessor->normalized, POSITION_INDEX, binding_index, buffer, &mesh->primitives[j]);
                            break;
                        case cgltf_attribute_type_normal:
                            set_primitive_attribute_3f(accessor->normalized, NORMAL_INDEX, binding_index, buffer, &mesh->primitives[j]);
                            break;
                        case cgltf_attribute_type_tangent:
                            set_primitive_attribute_3f(accessor->normalized, TANGENT_INDEX, binding_index, buffer, &mesh->primitives[j]);
                            break;
                        case cgltf_attribute_type_texcoord:
                            set_primitive_attribute_2f(accessor->normalized, TEXCOORD_INDEX, binding_index, buffer, &mesh->primitives[j]);
                            break;
                        case cgltf_attribute_type_color:
                            set_primitive_attribute_3f(accessor->normalized, COLOR_INDEX, binding_index, buffer, &mesh->primitives[j]);
                            break;
                        case cgltf_attribute_type_joints:
                        case cgltf_attribute_type_weights:
                        case cgltf_attribute_type_custom:
                        default:
                            break;
                    }
                }

                cgltf_accessor *accessor_data = primitive_data->indices;
                set_primitive_indices((int32_t)accessor_data->count, get_buffer_handle(accessor_data->buffer_view, &gpu_buffer_list), &mesh->primitives[j]);
            }
        }

        free(gpu_buffer_list.handles);
        cgltf_free(data);
    }

    return mesh_count;
}

bool load_gltf_file(const char *filename, gltfResource *gltf_resource) {


    return true;
}

void free_gltf(gltfResource gltf_resource){

}

size_t gltf_load_models(const char *filename, struct Model **models) {
    cgltf_options options = {0};
    cgltf_data *data;

    size_t model_count = 0;

    cgltf_result result = cgltf_parse_file(&options, filename, &data);
    if (result == cgltf_result_success) {
        result = cgltf_load_buffers(&options, data, filename);
        if (result != cgltf_result_success) {
            print_result(result);
            cgltf_free(data);
            return 0;
        }


    }

    return model_count;
}

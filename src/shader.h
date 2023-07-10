//
// Created by josue on 2023-07-03.
//

#ifndef TOYBOX_SRC_SHADER_H_
#define TOYBOX_SRC_SHADER_H_

#include "types.h"

typedef struct Shader {
  u32 handle;
  // Uniform locations
  i32 view_loc;
  i32 model_view_loc;
  i32 normal_loc;
  i32 projection_loc;
  i32 mvp_loc;
  i32 light_source_loc;
  i32 light_intensity_loc;
  i32 diffuse_reflectivity_loc;
  i32 albedo_loc;
  i32 heightmap_loc;
  i32 scale_loc;
  i32 offset_loc;
  i32 eye_position_loc;
} Shader;

Shader default_generic_shader;

Shader setup_shader(u32 program_handle);

Shader load_shader_from_file(const char* vertex_source_file, const char* fragment_source_file);
Shader load_tesselation_material_from_files(const char *vertex_source_file,
                                            const char *tess_control_source_file,
                                            const char *tess_evaluation_source_file,
                                            const char *fragment_source_file);
void shader_delete(Shader shader);

void init_default_shaders(void);
void clean_default_shaders(void);

void shader_enable(Shader shader);
void shader_set_mvp(Shader shader, mat4 model, mat4 view, mat4 projection);

#endif //TOYBOX_SRC_SHADER_H_

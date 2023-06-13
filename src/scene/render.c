//
// Created by josue on 2023-01-30.
//
#include "render.h"
#include "inputs.h"

#include "types/mesh.h"
#include "graphic/material.h"

void draw_mesh(Mesh mesh) {

}

void draw_node(Node node, Camera camera, Mesh *meshes, Shader *shaders){
    shader_use(shaders[node.shader_index]);



    draw_mesh(meshes[node.mesh_index]);
}

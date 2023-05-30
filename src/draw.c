//
// Created by josue on 2023-05-29.
//

#include "draw.h"
#include "glad/gl.h"
#include "viewport.h"
//#include "material.h"
//#include "scene.h"
//#include "model.h"

void draw_frame_start() {
    glClearColor(0.7f, 0.9f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void draw_frame_end(Viewport *viewport) {
    viewport_swap_window(viewport);
}

void draw_mesh(Mesh mesh, Material material) {
    material_set_in_use(material);

    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.index_count, );
}

//void draw_node(struct Node *node, struct Camera *camera) {
//    draw_model(node->model);
//}
//
//void draw_model(struct Model *model) {
//    material_set_in_use(model->material);
////    material_set_mvp(model->material, node.transform, camera.transform, camera.projection);
////    material_set_light(model->material, (vec3) {0.0f, 0.0f, -5.0f}, (vec3) {2.0f}, (vec3) {0.8f});
////    material_set_normal_matrix(model->material, node.normal_matrix);
//
//    for (int i = 0; i < model->mesh_count; ++i) {
//        glBindVertexArray(model->meshes[i].vao);
//        glDrawElements(model->meshes[i].mode, model->meshes[i].index_count, GL_UNSIGNED_INT, 0);
//    }
//}


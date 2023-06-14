//
// Created by josue on 2023-05-29.
//

#include "draw.h"
#include "glad/gl.h"

void draw_mesh(Mesh mesh, mat4 model, mat4 view, mat4 projection, Material material) {
    glBindVertexArray(mesh.vao);
    material_set_in_use(material);
    material_set_mvp(material, model, view, projection);
    glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
}

void draw_mesh_wireframe(Mesh mesh, mat4 model, mat4 view, mat4 projection, Material material) {
    glBindVertexArray(mesh.vao);
    material_set_in_use(material);
    material_set_mvp(material, model, view, projection);

    // Old version of doing wireframe rendering
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
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


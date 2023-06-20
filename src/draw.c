//
// Created by josue on 2023-05-29.
//

#include "draw.h"
#include "glad/gl.h"

#include "terrain.h"

void draw_mesh(Mesh mesh, mat4 model, mat4 view, mat4 projection, Material material) {
    glBindVertexArray(mesh.vao);
    material_enable(material);
    material_set_mvp(material, model, view, projection);
    glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
}

void draw_mesh_wireframe(Mesh mesh, mat4 model, mat4 view, mat4 projection, Material material) {
    glBindVertexArray(mesh.vao);
    material_enable(material);
    material_set_mvp(material, model, view, projection);

    // Old version of doing wireframe rendering
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_POINTS, 0, mesh.vertex_count);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void draw_terrain(TerrainMesh *mesh, vec4 *model, vec4 *view, vec4 *projection, Material material) {
    glBindVertexArray(mesh->vao);
    material_enable(material);
    material_set_mvp(material, model, view, projection);

    // Old version of doing wireframe rendering
    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawArrays(GL_PATCHES, 0, mesh->vertex_count);
}

void draw_terrain_wireframe(TerrainMesh *mesh, vec4 *model, vec4 *view, vec4 *projection, Material material) {
    glBindVertexArray(mesh->vao);
    material_enable(material);
    material_set_mvp(material, model, view, projection);

    // Old version of doing wireframe rendering
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glDrawArrays(GL_PATCHES, 0, mesh->vertex_count);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

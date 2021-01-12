#include "pipeline.h"
#include "util.h"

bool gfx3d_pipeline_create(Gfx3dPipeline *pipeline, uint32_t viewport_w, uint32_t viewport_h) {
    if (!gfx3d_rasterizer_create(&pipeline->rasterizer, viewport_w, viewport_h)) {
        return false;
    }

    pipeline->viewport_w = viewport_w;
    pipeline->viewport_h = viewport_h;

    return true;
}

void gfx3d_pipeline_destroy(Gfx3dPipeline *pipeline) {
    gfx3d_rasterizer_destroy(&pipeline->rasterizer);
}

void gfx3d_pipeline_clear(Gfx3dPipeline *pipeline, Gfx3dColor clear_color) {
    gfx3d_rasterizer_clear(&pipeline->rasterizer, clear_color);
}

static Gfx3dVec3 project_to_screen(Gfx3dVec4 clip, uint32_t viewport_w, uint32_t viewport_h) {
    uint32_t win_center_x = viewport_w / 2;
    uint32_t win_center_y = viewport_h / 2;

    return gfx3d_vec3(
        (clip.x*(float)viewport_w) / (2.0f*clip.w) + win_center_x,
        (clip.y*(float)viewport_h) / (2.0f*clip.w) + win_center_y,
        clip.z
    );
}

void gfx3d_pipeline_draw(Gfx3dPipeline *pipeline, const Gfx3dGeometry *geo, Gfx3dMat4 mvp) {
    uint32_t viewport_w = pipeline->viewport_w;
    uint32_t viewport_h = pipeline->viewport_h;

    for (int i = 0; i < geo->num_indices; i+=3) {
        Gfx3dVertex v1 = geo->vertices[geo->indices[i]];
        Gfx3dVertex v2 = geo->vertices[geo->indices[i+1]];
        Gfx3dVertex v3 = geo->vertices[geo->indices[i+2]];

        Gfx3dVec4 clipV1 = gfx3d_mat4_mul_vec4(mvp, gfx3d_vec4_from_vec3(v1.position));
        Gfx3dVec4 clipV2 = gfx3d_mat4_mul_vec4(mvp, gfx3d_vec4_from_vec3(v2.position));
        Gfx3dVec4 clipV3 = gfx3d_mat4_mul_vec4(mvp, gfx3d_vec4_from_vec3(v3.position));

        // TODO: Proper clipping of triangles.

        Gfx3dTriangle triangle;
        triangle.vertices[0] = gfx3d_vertex(project_to_screen(clipV1, viewport_w, viewport_h), v1.color, v1.normal);
        triangle.vertices[1] = gfx3d_vertex(project_to_screen(clipV2, viewport_w, viewport_h), v2.color, v2.normal);
        triangle.vertices[2] = gfx3d_vertex(project_to_screen(clipV3, viewport_w, viewport_h), v3.color, v3.normal);
        gfx3d_rasterizer_draw_triangle(&pipeline->rasterizer, triangle);
    }
}

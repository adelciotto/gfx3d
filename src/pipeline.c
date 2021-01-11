#include "pipeline.h"
#include "util.h"

bool gfx3d_pipeline_create(Gfx3dPipeline *pipeline, int viewport_w, int viewport_h) {
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

static bool vertex_out_of_bounds(Gfx3dVec4 v) {
    return v.x < -v.w || v.x > v.w || v.y < -v.w
           || v.y > v.w || v.z < -v.w || v.z > v.w;
}

static Gfx3dVec3 project_to_screen(Gfx3dVec4 clip, int viewport_w, int viewport_h) {
    int win_center_x = viewport_w / 2;
    int win_center_y = viewport_h / 2;

    return gfx3d_vec3(
        (clip.x*(float)viewport_w) / (2.0f*clip.w) + win_center_x,
        (clip.y*(float)viewport_h) / (2.0f*clip.w) + win_center_y,
        clip.z
    );
}

void gfx3d_pipeline_draw(Gfx3dPipeline *pipeline, const Gfx3dGeometry *geo, Gfx3dMat4 mvp) {
    int viewport_w = pipeline->viewport_w;
    int viewport_h = pipeline->viewport_h;

    for (int i = 0; i < geo->num_indices; i+=3) {
        Gfx3dVertex v1 = geo->vertices[geo->indices[i]];
        Gfx3dVertex v2 = geo->vertices[geo->indices[i+1]];
        Gfx3dVertex v3 = geo->vertices[geo->indices[i+2]];

        Gfx3dVec4 clipV1 = gfx3d_mat4_mul_vec4(mvp, gfx3d_vec4_from_vec3(v1.position));
        Gfx3dVec4 clipV2 = gfx3d_mat4_mul_vec4(mvp, gfx3d_vec4_from_vec3(v2.position));
        Gfx3dVec4 clipV3 = gfx3d_mat4_mul_vec4(mvp, gfx3d_vec4_from_vec3(v3.position));

        if (vertex_out_of_bounds(clipV1)
            && vertex_out_of_bounds(clipV2)
            && vertex_out_of_bounds(clipV3)) {
            continue;
        }

        Gfx3dTriangle triangle;
        triangle.vertices[0] = gfx3d_vertex(project_to_screen(clipV1, viewport_w, viewport_h), v1.color, v1.normal);
        triangle.vertices[1] = gfx3d_vertex(project_to_screen(clipV2, viewport_w, viewport_h), v2.color, v2.normal);
        triangle.vertices[2] = gfx3d_vertex(project_to_screen(clipV3, viewport_w, viewport_h), v3.color, v3.normal);
        gfx3d_rasterizer_draw_triangle(&pipeline->rasterizer, triangle);
    }
}

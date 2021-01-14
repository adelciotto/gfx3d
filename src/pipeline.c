#include "pipeline.h"
#include "util.h"

bool gfx3d_pipeline_create(gfx3d_pipeline_t *pipeline, uint32_t viewport_w, uint32_t viewport_h) {
    if (!gfx3d_rasterizer_create(&pipeline->rasterizer, viewport_w, viewport_h)) {
        return false;
    }

    pipeline->viewport_w = viewport_w;
    pipeline->viewport_h = viewport_h;

    return true;
}

void gfx3d_pipeline_destroy(gfx3d_pipeline_t *pipeline) {
    gfx3d_rasterizer_destroy(&pipeline->rasterizer);
}

void gfx3d_pipeline_clear(gfx3d_pipeline_t *pipeline, gfx3d_color_t clear_color) {
    gfx3d_rasterizer_clear(&pipeline->rasterizer, clear_color);
}

static gfx3d_vec3_t project_to_screen(gfx3d_vec4_t clip, uint32_t viewport_w, uint32_t viewport_h) {
    uint32_t win_center_x = viewport_w / 2;
    uint32_t win_center_y = viewport_h / 2;

    return gfx3d_vec3(
        (clip.x*(float)viewport_w) / (2.0f*clip.w) + win_center_x,
        (clip.y*(float)viewport_h) / (2.0f*clip.w) + win_center_y,
        clip.z
    );
}

void gfx3d_pipeline_draw(gfx3d_pipeline_t *pipeline, const gfx3d_geometry_t *geo, gfx3d_mat4_t mvp) {
    uint32_t viewport_w = pipeline->viewport_w;
    uint32_t viewport_h = pipeline->viewport_h;

    for (int i = 0; i < geo->num_indices; i+=3) {
        gfx3d_vertex_t v1 = geo->vertices[geo->indices[i]];
        gfx3d_vertex_t v2 = geo->vertices[geo->indices[i+1]];
        gfx3d_vertex_t v3 = geo->vertices[geo->indices[i+2]];

        gfx3d_vec4_t clipV1 = gfx3d_mat4_mul_vec4(mvp, gfx3d_vec4_from_vec3(v1.position));
        gfx3d_vec4_t clipV2 = gfx3d_mat4_mul_vec4(mvp, gfx3d_vec4_from_vec3(v2.position));
        gfx3d_vec4_t clipV3 = gfx3d_mat4_mul_vec4(mvp, gfx3d_vec4_from_vec3(v3.position));

        // TODO: Proper clipping of triangles.

        gfx3d_triangle_t triangle;
        triangle.vertices[0] = gfx3d_vertex(project_to_screen(clipV1, viewport_w, viewport_h), v1.color, v1.normal);
        triangle.vertices[1] = gfx3d_vertex(project_to_screen(clipV2, viewport_w, viewport_h), v2.color, v2.normal);
        triangle.vertices[2] = gfx3d_vertex(project_to_screen(clipV3, viewport_w, viewport_h), v3.color, v3.normal);
        gfx3d_rasterizer_draw_triangle(&pipeline->rasterizer, triangle);
    }
}

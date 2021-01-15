#ifndef GFX3D_PIPELINE_H
#define GFX3D_PIPELINE_H

#include "3dmath.h"
#include "color.h"
#include "framebuffer.h"
#include "geometry.h"

typedef struct gfx3d_pipeline_t {
    uint32_t viewport_w;
    uint32_t viewport_h;
    gfx3d_framebuffer_t framebuffer;
    float *zbuffer;
} gfx3d_pipeline_t;

bool gfx3d_pipeline_create(gfx3d_pipeline_t *pipeline, uint32_t viewport_w, uint32_t viewport_h);
void gfx3d_pipeline_destroy(gfx3d_pipeline_t *pipeline);
void gfx3d_pipeline_clear(gfx3d_pipeline_t *pipeline, gfx3d_color_t color);
void gfx3d_pipeline_draw(gfx3d_pipeline_t *pipeline, gfx3d_geometry_t *geometry, gfx3d_mat4_t mvp);

#endif // GFX3D_PIPELINE_H

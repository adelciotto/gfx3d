#ifndef GFX3D_RASTERIZER_H
#define GFX3D_RASTERIZER_H

#include "framebuffer.h"
#include "geometry.h"
#include "3dmath.h"
#include "color.h"

typedef struct gfx3d_rasterizer_t {
    uint32_t screen_w;
    uint32_t screen_h;
    gfx3d_framebuffer_t framebuffer;
    float *zbuffer;
} gfx3d_rasterizer_t;

bool gfx3d_rasterizer_create(gfx3d_rasterizer_t *rasterizer, uint32_t screen_w, uint32_t screen_h);
void gfx3d_rasterizer_destroy(gfx3d_rasterizer_t *rasterizer);
void gfx3d_rasterizer_clear(gfx3d_rasterizer_t *rasterizer, gfx3d_color_t clear_color);
void gfx3d_rasterizer_draw_triangle(gfx3d_rasterizer_t *rasterizer, gfx3d_triangle_t triangle);

#endif // GFX3D_RASTERIZER_H

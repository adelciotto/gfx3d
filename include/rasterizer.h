#ifndef GFX3D_RASTERIZER_H
#define GFX3D_RASTERIZER_H

#include "framebuffer.h"
#include "geometry.h"
#include "3dmath.h"
#include "color.h"

typedef struct Gfx3dRasterizer {
    int screen_w;
    int screen_h;
    Gfx3dFramebuffer framebuffer;
    float *zbuffer;
} Gfx3dRasterizer;

bool gfx3d_rasterizer_create(Gfx3dRasterizer *rasterizer, int screen_w, int screen_h);
void gfx3d_rasterizer_destroy(Gfx3dRasterizer *rasterizer);
void gfx3d_rasterizer_clear(Gfx3dRasterizer *rasterizer, Gfx3dColor clear_color);
void gfx3d_rasterizer_draw_triangle(Gfx3dRasterizer *rasterizer, Gfx3dTriangle triangle);

#endif // GFX3D_RASTERIZER_H

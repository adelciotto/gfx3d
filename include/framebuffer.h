#ifndef GFX3D_FRAMEBUFFER_H
#define GFX3D_FRAMEBUFFER_H

#include "util.h"

#define GFX3D_BITS_PER_PIXEL    32
#define GFX3D_BYTES_PER_PIXEL   4

typedef struct Gfx3dFramebuffer {
    int width;
    int height;
    int pitch;
    uint8_t *pixels;
} Gfx3dFramebuffer;

bool gfx3d_framebuffer_create(Gfx3dFramebuffer *fb, int width, int height);
void gfx3d_framebuffer_destroy(Gfx3dFramebuffer *fb);
void gfx3d_framebuffer_clear(Gfx3dFramebuffer *fb, uint8_t r, uint8_t g, uint8_t b);
void gfx3d_framebuffer_set_pixel(Gfx3dFramebuffer *fb, int sx, int sy, uint8_t r, uint8_t g, uint8_t b);

#endif // GFX3D_FRAMEBUFFER_H

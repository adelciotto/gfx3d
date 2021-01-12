#ifndef GFX3D_FRAMEBUFFER_H
#define GFX3D_FRAMEBUFFER_H

#include "util.h"

#define GFX3D_BITS_PER_PIXEL    32
#define GFX3D_BYTES_PER_PIXEL   4

typedef struct Gfx3dFramebuffer {
    uint32_t width;
    uint32_t height;
    uint32_t pitch;
    uint8_t *pixels;
} Gfx3dFramebuffer;

bool gfx3d_framebuffer_create(Gfx3dFramebuffer *fb, uint32_t width, uint32_t height);
void gfx3d_framebuffer_destroy(Gfx3dFramebuffer *fb);
void gfx3d_framebuffer_clear(Gfx3dFramebuffer *fb, uint8_t r, uint8_t g, uint8_t b);
void gfx3d_framebuffer_set_pixel(Gfx3dFramebuffer *fb, uint32_t sx, uint32_t sy, uint8_t r, uint8_t g, uint8_t b);

#endif // GFX3D_FRAMEBUFFER_H

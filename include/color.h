#ifndef GFX3D_COLOR_H
#define GFX3D_COLOR_H

#include "util.h"

typedef struct gfx3d_color_t {
    float r;
    float g;
    float b;
    float a;
} gfx3d_color_t;

#define GFX3D_COLOR_WHITE() {.r = 1.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f}
#define GFX3D_COLOR_BLACK() {.r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f}
#define GFX3D_COLOR_RED() {.r = 1.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f}
#define GFX3D_COLOR_LIME() {.r = 0.0f, .g = 1.0f, .b = 0.0f, .a = 1.0f}
#define GFX3D_COLOR_BLUE() {.r = 0.0f, .g = 0.0f, .b = 1.0f, .a = 1.0f}
#define GFX3D_COLOR_MAROON() {.r = 0.5f, .g = 0.0f, .b = 0.0f, .a = 1.0f}
#define GFX3D_COLOR_YELLOW() {.r = 1.0f, .g = 1.0f, .b = 0.0f, .a = 1.0f}
#define GFX3D_COLOR_GREEN() {.r = 0.0f, .g = 0.5f, .b = 0.0f, .a = 1.0f}
#define GFX3D_COLOR_AQUA() {.r = 0.0f, .g = 1.0f, .b = 1.0f, .a = 1.0f}
#define GFX3D_COLOR_FUCHSIA() {.r = 1.0f, .g = 0.0f, .b = 1.0f, .a = 1.0f}
#define GFX3D_COLOR_PURPLE() {.r = 0.5f, .g = 0.0f, .b = 0.5f, .a = 1.0f}


gfx3d_color_t gfx3d_color(float r, float g, float b);
void gfx3d_color_to_rgb_u8(gfx3d_color_t c, uint8_t *r, uint8_t *g, uint8_t *b);
gfx3d_color_t gfx3d_color_lerp(gfx3d_color_t a, gfx3d_color_t b, float t);

#endif // GFX3D_COLOR_H

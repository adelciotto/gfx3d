#ifndef GFX3D_COLOR_H
#define GFX3D_COLOR_H

#include "util.h"

typedef struct Gfx3dColor {
    float r;
    float g;
    float b;
    float a;
} Gfx3dColor;

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
#define GFX3D_COLOR_PURPLE() {.r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f}


Gfx3dColor gfx3d_color(float r, float g, float b);
void gfx3d_color_to_rgb_u8(Gfx3dColor c, uint8_t *r, uint8_t *g, uint8_t *b);
Gfx3dColor gfx3d_color_lerp(Gfx3dColor a, Gfx3dColor b, float t);

#endif // GFX3D_COLOR_H

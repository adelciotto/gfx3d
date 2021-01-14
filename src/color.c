#include "color.h"
#include "3dmath.h"

gfx3d_color_t gfx3d_color(float r, float g, float b) {
    return (gfx3d_color_t){ .r = r, .g = g, .b = b };
}

void gfx3d_color_to_rgb_u8(gfx3d_color_t c, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = (uint8_t)(c.r*255.0f);
    *g = (uint8_t)(c.g*255.0f);
    *b = (uint8_t)(c.b*255.0f);
}

gfx3d_color_t gfx3d_color_lerp(gfx3d_color_t a, gfx3d_color_t b, float t) {
    return (gfx3d_color_t){
        .r = gfx3d_lerp(a.r, b.r, t),
        .g = gfx3d_lerp(a.g, b.g, t),
        .b = gfx3d_lerp(a.b, b.b, t)
    };
}


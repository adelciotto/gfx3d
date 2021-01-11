#include "color.h"
#include "3dmath.h"

Gfx3dColor gfx3d_color(float r, float g, float b) {
    return (Gfx3dColor){ .r = r, .g = g, .b = b };
}

void gfx3d_color_to_rgb_u8(Gfx3dColor c, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = (uint8_t)(c.r*255.0f);
    *g = (uint8_t)(c.g*255.0f);
    *b = (uint8_t)(c.b*255.0f);
}

Gfx3dColor gfx3d_color_lerp(Gfx3dColor a, Gfx3dColor b, float t) {
    return (Gfx3dColor){
        .r = gfx3d_lerp(a.r, b.r, t),
        .g = gfx3d_lerp(a.g, b.g, t),
        .b = gfx3d_lerp(a.b, b.b, t)
    };
}


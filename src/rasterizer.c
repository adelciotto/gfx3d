#include "rasterizer.h"

bool gfx3d_rasterizer_create(Gfx3dRasterizer *rasterizer, uint32_t screen_w, uint32_t screen_h) {
    if (!gfx3d_framebuffer_create(&rasterizer->framebuffer, screen_w, screen_h)) {
        return false;
    }

    float *zbuffer = calloc(screen_w*screen_h, sizeof(float));
    if (zbuffer == NULL) {
        ERRORF("Unable to allocate memory for zbuffer");
        gfx3d_framebuffer_destroy(&rasterizer->framebuffer);
        return false;
    }

    rasterizer->screen_w = screen_w;
    rasterizer->screen_h = screen_h;
    rasterizer->zbuffer = zbuffer;

    return true;
}

void gfx3d_rasterizer_destroy(Gfx3dRasterizer *rasterizer) {
    if (rasterizer->zbuffer != NULL) {
        free(rasterizer->zbuffer);
        rasterizer->zbuffer = NULL;
    }

    gfx3d_framebuffer_destroy(&rasterizer->framebuffer);
}

void gfx3d_rasterizer_clear(Gfx3dRasterizer *rasterizer, Gfx3dColor clear_color) {
    uint8_t r, g, b;
    gfx3d_color_to_rgb_u8(clear_color, &r, &g, &b);

    gfx3d_framebuffer_clear(&rasterizer->framebuffer, r, g, b);

    uint32_t size = rasterizer->screen_w*rasterizer->screen_h;
    for (uint32_t i = 0; i < size; i++) {
        rasterizer->zbuffer[i] = INFINITY;
    }
}

static float edge_function(Gfx3dVec3 va, Gfx3dVec3 vb, Gfx3dVec3 vc) {
    return (vc.x - va.x) * (vb.y - va.y) - (vc.y - va.y) * (vb.x - va.x);
}

void gfx3d_rasterizer_draw_triangle(Gfx3dRasterizer *rasterizer, Gfx3dTriangle triangle) {
    Gfx3dVec3 v0 = triangle.vertices[0].position;
    Gfx3dVec3 v1 = triangle.vertices[1].position;
    Gfx3dVec3 v2 = triangle.vertices[2].position;
    Gfx3dColor c0 = triangle.vertices[0].color;
    Gfx3dColor c1 = triangle.vertices[1].color;
    Gfx3dColor c2 = triangle.vertices[2].color;

    c0.r /= v0.z; c0.g /= v0.z; c0.b /= v0.z;
    c1.r /= v1.z; c1.g /= v1.z; c1.b /= v1.z;
    c2.r /= v2.z; c2.g /= v2.z; c2.b /= v2.z;

    v0.z = 1.0f / v0.z;
    v1.z = 1.0f / v1.z;
    v2.z = 1.0f / v2.z;

    uint32_t screen_w = rasterizer->screen_w;
    uint32_t screen_h = rasterizer->screen_h;

    float xmin = fminf(v0.x, fminf(v1.x, v2.x));
    float xmax = fmaxf(v0.x, fmaxf(v1.x, v2.x));
    float ymin = fminf(v0.y, fminf(v1.y, v2.y));
    float ymax = fmaxf(v0.y, fmaxf(v1.y, v2.y));

    if (xmin > screen_w - 1 || xmax < 0 || ymin > screen_h - 1 || ymax < 0) {
        return;
    }

    uint32_t x0 = gfx3d_util_max(0, (int32_t)floorf(xmin));
    uint32_t x1 = gfx3d_util_min(screen_w - 1, (int32_t)floorf(xmax));
    uint32_t y0 = gfx3d_util_max(0, (int32_t)floorf(ymin));
    uint32_t y1 = gfx3d_util_min(screen_h - 1, (int32_t)floorf(ymax));

    float area = edge_function(v0, v1, v2);
    float inv_area = 1.0f / area;

    for (uint32_t y = y0; y <= y1; y++) {
        for (uint32_t x = x0; x <= x1; x++) {
            Gfx3dVec3 p = gfx3d_vec3(x, y, 0.0f);
            float w0 = edge_function(v1, v2, p);
            float w1 = edge_function(v2, v0, p);
            float w2 = edge_function(v0, v1, p);

            if (w0 <= 0.0f && w1 <= 0.0f && w2 <= 0.0f) {
                w0 *= inv_area;
                w1 *= inv_area;
                w2 *= inv_area;

                float z = 1.0f / (w0 * v0.z + w1 * v1.z + w2 * v2.z);
                Gfx3dColor col = gfx3d_color(
                    (w0 * c0.r + w1 * c1.r + w2 * c2.r) * z,
                    (w0 * c0.g + w1 * c1.g + w2 * c2.g) * z,
                    (w0 * c0.b + w1 * c1.b + w2 * c2.b) * z
                );

                int i = y * rasterizer->screen_w + x;
                if (z < rasterizer->zbuffer[i]) {
                    rasterizer->zbuffer[i] = z;

                    uint8_t r, g, b;
                    gfx3d_color_to_rgb_u8(col, &r, &g, &b);
                    gfx3d_framebuffer_set_pixel(&rasterizer->framebuffer, x, y, r, g, b);
                }
            }
        }
    }
}

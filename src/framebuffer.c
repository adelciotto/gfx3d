#include "framebuffer.h"

bool gfx3d_framebuffer_create(Gfx3dFramebuffer *fb, int width, int height) {
    uint64_t size = width*height*GFX3D_BYTES_PER_PIXEL;
    uint8_t *pixels = calloc(size, 1);
    if (pixels == NULL) {
        ERRORF("Unable to allocate memory for pixels");
        return false;
    }

    fb->width = width;
    fb->height = height;
    fb->pitch = width*GFX3D_BYTES_PER_PIXEL;
    fb->pixels = pixels;
    return true;
}

void gfx3d_framebuffer_destroy(Gfx3dFramebuffer *fb) {
    if (fb->pixels != NULL) {
        free(fb->pixels);
        fb->pixels = NULL;
    }
}

void gfx3d_framebuffer_clear(Gfx3dFramebuffer *fb, uint8_t r, uint8_t g, uint8_t b) {
    int size = fb->pitch*fb->height;
    for (int i = 0; i < size; i += GFX3D_BYTES_PER_PIXEL) {
        fb->pixels[i] = b;
        fb->pixels[i+1] = g;
        fb->pixels[i+2] = r;
        fb->pixels[i+3] = 255;
    }
}

void gfx3d_framebuffer_set_pixel(Gfx3dFramebuffer *fb, int sx, int sy, uint8_t r, uint8_t g, uint8_t b) {
    if (sx >= 0 && sx < fb->width && sy >= 0 && sy < fb->height) {
        int i = fb->pitch*sy + sx*GFX3D_BYTES_PER_PIXEL;
        fb->pixels[i] = b;
        fb->pixels[i+1] = g;
        fb->pixels[i+2] = r;
        fb->pixels[i+3] = 255;
    }
}


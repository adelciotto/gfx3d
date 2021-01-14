#include "framebuffer.h"

bool gfx3d_framebuffer_create(gfx3d_framebuffer_t *fb, uint32_t width, uint32_t height) {
    uint32_t size = width*height*GFX3D_BYTES_PER_PIXEL;
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

void gfx3d_framebuffer_destroy(gfx3d_framebuffer_t *fb) {
    if (fb->pixels != NULL) {
        free(fb->pixels);
        fb->pixels = NULL;
    }
}

void gfx3d_framebuffer_clear(gfx3d_framebuffer_t *fb, uint8_t r, uint8_t g, uint8_t b) {
    uint32_t size = fb->pitch*fb->height;
    for (uint32_t i = 0; i < size; i += GFX3D_BYTES_PER_PIXEL) {
        fb->pixels[i] = b;
        fb->pixels[i+1] = g;
        fb->pixels[i+2] = r;
        fb->pixels[i+3] = 255;
    }
}

void gfx3d_framebuffer_set_pixel(gfx3d_framebuffer_t *fb, uint32_t sx, uint32_t sy, uint8_t r, uint8_t g, uint8_t b) {
    uint32_t i = fb->pitch*sy + sx*GFX3D_BYTES_PER_PIXEL;

    fb->pixels[i] = b;
    fb->pixels[i+1] = g;
    fb->pixels[i+2] = r;
    fb->pixels[i+3] = 255;
}


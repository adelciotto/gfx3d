#ifndef GFX3D_WINDOW_H
#define GFX3D_WINDOW_H

#include <SDL2/SDL.h>
#include "util.h"

typedef struct gfx3d_window_t {
    int internal_width;
    int internal_height;
    int win_scale;
    bool fullscreen;
    bool vsync;
    bool should_close;

    SDL_Window *sdl_win;
    SDL_Renderer *sdl_rend;
    SDL_Texture *sdl_tex;
} gfx3d_window_t;

bool gfx3d_window_create(gfx3d_window_t *win, int internal_width, int internal_height, int win_scale, bool fullscreen, bool vsync);
void gfx3d_window_destroy(gfx3d_window_t *win);
void gfx3d_window_poll_events(gfx3d_window_t *win);
void gfx3d_window_upload_pixels(gfx3d_window_t *win, uint8_t *pixels, int pitch);
void gfx3d_window_swap(gfx3d_window_t *win);

float gfx3d_elapsed_time();
uint64_t gfx3d_performance_get_counter();
double gfx3d_performance_elapsed_time(uint64_t end, uint64_t start);

#endif // GFX3D_WINDOW_H

#ifndef GFX3D_WINDOW_H
#define GFX3D_WINDOW_H

#include <SDL2/SDL.h>
#include "util.h"

typedef struct Gfx3dWindow {
    int internal_width;
    int internal_height;
    int win_scale;
    bool fullscreen;
    bool vsync;
    bool should_close;

    SDL_Window *sdl_win;
    SDL_Renderer *sdl_rend;
    SDL_Texture *sdl_tex;
} Gfx3dWindow;

bool gfx3d_window_create(Gfx3dWindow *win, int internal_width, int internal_height, int win_scale, bool fullscreen, bool vsync);
void gfx3d_window_destroy(Gfx3dWindow *win);
void gfx3d_window_poll_events(Gfx3dWindow *win);
void gfx3d_window_present(Gfx3dWindow *win, uint8_t *pixels, int pitch);

float gfx3d_elapsed_time();

#endif // GFX3D_WINDOW_H

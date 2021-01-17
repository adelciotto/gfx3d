#include "window.h"

#define WINDOW_TITLE "gfx3d"

bool gfx3d_window_create(gfx3d_window_t *win, int internal_width, int internal_height, int win_scale, bool fullscreen, bool vsync) {
    SDL_Window *sdl_win = NULL;
    SDL_Renderer *sdl_rend = NULL;
    SDL_Texture *sdl_tex = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        ERRORF("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;
    if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    sdl_win = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           internal_width*win_scale, internal_height*win_scale, flags);
    if (sdl_win == NULL) {
        ERRORF("Unable to create SDL_Window: %s", SDL_GetError());
        goto error;
    }

    const char *vsync_hint_val = vsync ? "1" : "0";
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, vsync_hint_val);
    sdl_rend = SDL_CreateRenderer(sdl_win, -1, SDL_RENDERER_ACCELERATED);
    if (sdl_rend == NULL) {
        ERRORF("Unable to create SDL_Renderer: %s", SDL_GetError());
        goto error;
    }

    sdl_tex = SDL_CreateTexture(sdl_rend, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
                                internal_width, internal_height);
    if (sdl_tex == NULL) {
        ERRORF("Unable to create SDL_Texture: %s", SDL_GetError());
        goto error;
    }

    if (SDL_RenderSetLogicalSize(sdl_rend, internal_width, internal_height) != 0) {
        WARNF("Unable to set SDL_Renderer logical size: %s", SDL_GetError());
    }

    win->internal_width = internal_width;
    win->internal_height = internal_height;
    win->win_scale = win_scale;
    win->fullscreen = fullscreen;
    win->vsync = vsync;
    win->should_close = false;
    win->sdl_win = sdl_win;
    win->sdl_rend = sdl_rend;
    win->sdl_tex = sdl_tex;

    return true;

error:
    if (sdl_tex != NULL) SDL_DestroyTexture(sdl_tex);
    if (sdl_rend != NULL) SDL_DestroyRenderer(sdl_rend);
    if (sdl_win != NULL) SDL_DestroyWindow(sdl_win);
    SDL_Quit();
    return false;
}

void gfx3d_window_destroy(gfx3d_window_t *win) {
    if (win->sdl_tex != NULL) SDL_DestroyTexture(win->sdl_tex);
    if (win->sdl_rend != NULL) SDL_DestroyRenderer(win->sdl_rend);
    if (win->sdl_win != NULL) SDL_DestroyWindow(win->sdl_win);

    SDL_Quit();
}

void gfx3d_window_poll_events(gfx3d_window_t *win) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            win->should_close = true;
        }
    }
}

void gfx3d_window_upload_pixels(gfx3d_window_t *win, uint8_t *pixels, int pitch) {
    SDL_UpdateTexture(win->sdl_tex, NULL, pixels, pitch);

    SDL_RenderClear(win->sdl_rend);
    SDL_RenderCopy(win->sdl_rend, win->sdl_tex, NULL, NULL);
}

void gfx3d_window_swap(gfx3d_window_t *win) {
    SDL_RenderPresent(win->sdl_rend);
}

float gfx3d_elapsed_time() {
    return (float)SDL_GetTicks() / 1000.0f;
}

uint64_t gfx3d_performance_get_counter() {
    return SDL_GetPerformanceCounter();
}

double gfx3d_performance_elapsed_time(uint64_t end, uint64_t start) {
    return (double)((end - start)*1000) / (double)SDL_GetPerformanceFrequency();
}

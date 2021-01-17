#ifndef GFX3D_TEXT_H
#define GFX3D_TEXT_H

#include <SDL2/SDL.h>
#include "3dmath.h"
#include "util.h"

bool gfx3d_text_init(SDL_Renderer *sdl_rend);
void gfx3d_text_destroy();
void gfx3d_text_draw(const char *text, gfx3d_vec2_t position, float scale);

#endif // GFX3D_TEXT_H

#ifndef GFX3D_PIPELINE_H
#define GFX3D_PIPELINE_H

#include "3dmath.h"
#include "color.h"
#include "rasterizer.h"

typedef struct Gfx3dPipeline {
    uint32_t viewport_w;
    uint32_t viewport_h;
    Gfx3dRasterizer rasterizer;
} Gfx3dPipeline;

bool gfx3d_pipeline_create(Gfx3dPipeline *pipeline, uint32_t viewport_w, uint32_t viewport_h);
void gfx3d_pipeline_destroy(Gfx3dPipeline *pipeline);
void gfx3d_pipeline_clear(Gfx3dPipeline *pipeline, Gfx3dColor color);
void gfx3d_pipeline_draw(Gfx3dPipeline *pipeline, const Gfx3dGeometry *geo, Gfx3dMat4 mvp);

#endif // GFX3D_PIPELINE_H

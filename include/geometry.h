#ifndef GFX3D_GEOMETRY_H
#define GFX3D_GEMOETRY_H

#include "3dmath.h"
#include "color.h"

typedef struct gfx3d_vertex_t {
    gfx3d_vec3_t position;
    gfx3d_color_t color;
    gfx3d_vec3_t normal;
} gfx3d_vertex_t;

gfx3d_vertex_t gfx3d_vertex(gfx3d_vec3_t position, gfx3d_color_t color, gfx3d_vec3_t normal);

typedef struct gfx3d_triangle_t {
    gfx3d_vertex_t vertices[3];
} gfx3d_triangle_t;

typedef struct gfx3d_geometry_t {
    const gfx3d_vertex_t *vertices;
    int num_vertices;
    const unsigned int *indices;
    int num_indices;
} gfx3d_geometry_t;

void gfx3d_geometry_cube(gfx3d_geometry_t *geo);

#endif // GFX3D_GEOMETRY_H

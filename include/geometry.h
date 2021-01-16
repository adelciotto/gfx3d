#ifndef GFX3D_GEOMETRY_H
#define GFX3D_GEMOETRY_H

#include "3dmath.h"
#include "color.h"

typedef struct gfx3d_vertex_list_t {
    gfx3d_vec3_t *positions;
    gfx3d_vec3_t *normals;
    gfx3d_color_t *colors;
} gfx3d_vertex_list_t;

typedef struct gfx3d_geometry_t {
    gfx3d_vertex_list_t vertices;
    int num_vertices;
} gfx3d_geometry_t;

void gfx3d_geometry_cube(gfx3d_geometry_t *geo);

#endif // GFX3D_GEOMETRY_H

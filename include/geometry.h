#ifndef GFX3D_GEOMETRY_H
#define GFX3D_GEMOETRY_H

#include "3dmath.h"
#include "color.h"

typedef struct Gfx3dVertex {
    Gfx3dVec3 position;
    Gfx3dColor color;
    Gfx3dVec3 normal;
} Gfx3dVertex;

Gfx3dVertex gfx3d_vertex(Gfx3dVec3 position, Gfx3dColor color, Gfx3dVec3 normal);

typedef struct Gfx3dTriangle {
    Gfx3dVertex vertices[3];
} Gfx3dTriangle;

typedef struct Gfx3dGeometry {
    const Gfx3dVertex *vertices;
    int num_vertices;
    const unsigned int *indices;
    int num_indices;
} Gfx3dGeometry;

void gfx3d_geometry_cube(Gfx3dGeometry *geo);

#endif // GFX3D_GEOMETRY_H

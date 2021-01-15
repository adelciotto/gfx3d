#include "geometry.h"

static const gfx3d_vec3_t s_cube_vertex_positions[] = {
    {-1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {-1.0f, -1.0f, -1.0f},
    {1.0f, -1.0f, -1.0f},
    {-1.0f, 1.0f, -1.0f},
    {1.0f, 1.0f, -1.0f}
};
static const gfx3d_vec3_t s_cube_vertex_normals[] = {
    GFX3D_VEC3_ZERO(),
    GFX3D_VEC3_ZERO(),
    GFX3D_VEC3_ZERO(),
    GFX3D_VEC3_ZERO(),
    GFX3D_VEC3_ZERO(),
    GFX3D_VEC3_ZERO(),
    GFX3D_VEC3_ZERO(),
    GFX3D_VEC3_ZERO()
};
static const gfx3d_color_t s_cube_vertex_colors[] = {
    GFX3D_COLOR_WHITE(),
    GFX3D_COLOR_RED(),
    GFX3D_COLOR_LIME(),
    GFX3D_COLOR_BLUE(),
    GFX3D_COLOR_MAROON(),
    GFX3D_COLOR_AQUA(),
    GFX3D_COLOR_PURPLE(),
    GFX3D_COLOR_YELLOW()
};
static const unsigned int s_cube_indices[] = {
    // Front
    0, 1, 3, 0, 3, 2,
    // Right
    1, 5, 7, 1, 7, 3,
    // Back
    5, 4, 6, 5, 6, 7,
    // Left
    4, 0, 2, 4, 2, 6,
    // Bottom
    4, 5, 1, 4, 1, 0,
    // Top
    2, 3, 7, 2, 7, 6
};

void gfx3d_geometry_cube(gfx3d_geometry_t *geo) {
    geo->vertices.positions = s_cube_vertex_positions;
    geo->vertices.normals = s_cube_vertex_normals;
    geo->vertices.colors = s_cube_vertex_colors;
    geo->num_vertices = ARRAY_LEN(s_cube_vertex_positions);

    geo->num_indices = ARRAY_LEN(s_cube_indices);
    geo->indices = s_cube_indices;
}


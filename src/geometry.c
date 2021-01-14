#include "geometry.h"

static const gfx3d_vertex_t s_cube_vertices[] = {
    {.position = {-1.0f, -1.0f, 1.0f}, .color = GFX3D_COLOR_WHITE(), .normal = GFX3D_VEC3_ZERO()},
    {.position = {1.0f, -1.0f, 1.0f}, .color = GFX3D_COLOR_RED(), .normal = GFX3D_VEC3_ZERO()},
    {.position = {-1.0f, 1.0f, 1.0f}, .color = GFX3D_COLOR_LIME(), .normal = GFX3D_VEC3_ZERO()},
    {.position = {1.0f, 1.0f, 1.0f}, .color = GFX3D_COLOR_BLUE(), .normal = GFX3D_VEC3_ZERO()},
    {.position = {-1.0f, -1.0f, -1.0f}, .color = GFX3D_COLOR_MAROON(), .normal = GFX3D_VEC3_ZERO()},
    {.position = {1.0f, -1.0f, -1.0f}, .color = GFX3D_COLOR_AQUA(), .normal = GFX3D_VEC3_ZERO()},
    {.position = {-1.0f, 1.0f, -1.0f}, .color = GFX3D_COLOR_PURPLE(), .normal = GFX3D_VEC3_ZERO()},
    {.position = {1.0f, 1.0f, -1.0f}, .color = GFX3D_COLOR_YELLOW(), .normal = GFX3D_VEC3_ZERO()}
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

gfx3d_vertex_t gfx3d_vertex(gfx3d_vec3_t position, gfx3d_color_t color, gfx3d_vec3_t normal) {
    return (gfx3d_vertex_t){
        .position = position,
        .color = color,
        .normal = normal
    };
}

void gfx3d_geometry_cube(gfx3d_geometry_t *geo) {
    geo->num_vertices = ARRAY_LEN(s_cube_vertices);
    geo->vertices = s_cube_vertices;

    geo->num_indices = ARRAY_LEN(s_cube_indices);
    geo->indices = s_cube_indices;
}


#include "geometry.h"

static const gfx3d_vec3_t s_cube_vertex_positions[] = {
    // Front
    {-1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {-1.0f, -1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f},
    // Right
    {1.0f, -1.0f, 1.0f},
    {1.0f, -1.0f, -1.0f},
    {1.0f, 1.0f, -1.0f},
    {1.0f, -1.0f, 1.0f},
    {1.0f, 1.0f, -1.0f},
    {1.0f, 1.0f, 1.0f},
    // Back
    {1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, 1.0f, -1.0f},
    {1.0f, -1.0f, -1.0f},
    {-1.0f, 1.0f, -1.0f},
    {1.0f, 1.0f, -1.0f},
    // Left
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, -1.0f, 1.0f},
    {-1.0f, 1.0f, 1.0f},
    {-1.0f, -1.0f, -1.0f},
    {-1.0f, 1.0f, 1.0f},
    {-1.0f, 1.0f, -1.0f},
    // Bottom
    {-1.0f, -1.0f, -1.0f},
    {1.0f, -1.0f, -1.0f},
    {1.0f, -1.0f, 1.0f},
    {-1.0f, -1.0f, -1.0f},
    {1.0f, -1.0f, 1.0f},
    {-1.0f, -1.0f, 1.0f},
    // Top
    {-1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, -1.0f},
    {-1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, -1.0f},
    {-1.0f, 1.0f, -1.0f}
};
static const gfx3d_vec3_t s_cube_vertex_normals[] = {
    // Front
    {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f},
    // Right
    {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    // Back
    {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
    // Left
    {-1.0f, 0.0f, 0.0f},
    {-1.0f, 0.0f, 0.0f},
    {-1.0f, 0.0f, 0.0f},
    {-1.0f, 0.0f, 0.0f},
    {-1.0f, 0.0f, 0.0f},
    {-1.0f, 0.0f, 0.0f},
    // Bottom
    {0.0f, -1.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    {0.0f, -1.0f, 0.0f},
    // Top
    {0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 1.0f, 0.0f}
};
static const gfx3d_color_t s_cube_vertex_colors[] = {
    // Front
    GFX3D_COLOR_RED(),
    GFX3D_COLOR_RED(),
    GFX3D_COLOR_RED(),
    GFX3D_COLOR_RED(),
    GFX3D_COLOR_RED(),
    GFX3D_COLOR_RED(),
    // Right
    GFX3D_COLOR_GREEN(),
    GFX3D_COLOR_GREEN(),
    GFX3D_COLOR_GREEN(),
    GFX3D_COLOR_GREEN(),
    GFX3D_COLOR_GREEN(),
    GFX3D_COLOR_GREEN(),
    // Back
    GFX3D_COLOR_BLUE(),
    GFX3D_COLOR_BLUE(),
    GFX3D_COLOR_BLUE(),
    GFX3D_COLOR_BLUE(),
    GFX3D_COLOR_BLUE(),
    GFX3D_COLOR_BLUE(),
    // Left
    GFX3D_COLOR_YELLOW(),
    GFX3D_COLOR_YELLOW(),
    GFX3D_COLOR_YELLOW(),
    GFX3D_COLOR_YELLOW(),
    GFX3D_COLOR_YELLOW(),
    GFX3D_COLOR_YELLOW(),
    // Bottom
    GFX3D_COLOR_PURPLE(),
    GFX3D_COLOR_PURPLE(),
    GFX3D_COLOR_PURPLE(),
    GFX3D_COLOR_PURPLE(),
    GFX3D_COLOR_PURPLE(),
    GFX3D_COLOR_PURPLE(),
    // Top
    GFX3D_COLOR_LIME(),
    GFX3D_COLOR_LIME(),
    GFX3D_COLOR_LIME(),
    GFX3D_COLOR_LIME(),
    GFX3D_COLOR_LIME(),
    GFX3D_COLOR_LIME(),
};

void gfx3d_geometry_cube(gfx3d_geometry_t *geo) {
    geo->vertices.positions = s_cube_vertex_positions;
    geo->vertices.normals = s_cube_vertex_normals;
    geo->vertices.colors = s_cube_vertex_colors;
    geo->num_vertices = ARRAY_LEN(s_cube_vertex_positions);
}


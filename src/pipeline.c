#include "pipeline.h"
#include "util.h"

typedef struct triangle_t {
    gfx3d_vec3_t obj_space_positions[3];
    gfx3d_vec4_t clip_space_positions[3];
    gfx3d_vec3_t screen_space_positions[3];

    bool has_normals;
    gfx3d_vec3_t normals[3];

    bool has_colors;
    gfx3d_color_t colors[3];
} triangle_t;

bool gfx3d_pipeline_create(gfx3d_pipeline_t *pipeline, uint32_t viewport_w, uint32_t viewport_h) {
    if (!gfx3d_framebuffer_create(&pipeline->framebuffer, viewport_w, viewport_h)) {
        return false;
    }

    float *zbuffer = calloc(viewport_w*viewport_h, sizeof(float));
    if (zbuffer == NULL) {
        ERRORF("Unable to allocate memory for zbuffer");
        gfx3d_framebuffer_destroy(&pipeline->framebuffer);
        return false;
    }

    pipeline->viewport_w = viewport_w;
    pipeline->viewport_h = viewport_h;
    pipeline->zbuffer = zbuffer;

    return true;
}

void gfx3d_pipeline_destroy(gfx3d_pipeline_t *pipeline) {
    if (pipeline->zbuffer != NULL) {
        free(pipeline->zbuffer);
        pipeline->zbuffer = NULL;
    }

    gfx3d_framebuffer_destroy(&pipeline->framebuffer);
}

void gfx3d_pipeline_clear(gfx3d_pipeline_t *pipeline, gfx3d_color_t clear_color) {
    uint8_t r, g, b;
    gfx3d_color_to_rgb_u8(clear_color, &r, &g, &b);

    gfx3d_framebuffer_clear(&pipeline->framebuffer, r, g, b);

    uint32_t size = pipeline->viewport_w*pipeline->viewport_h;
    for (uint32_t i = 0; i < size; i++) {
        pipeline->zbuffer[i] = INFINITY;
    }
}

static triangle_t triangle_from_indices(gfx3d_geometry_t *geometry, uint32_t a, uint32_t b, uint32_t c) {
    triangle_t triangle;
    triangle.obj_space_positions[0] = geometry->vertices.positions[a];
    triangle.obj_space_positions[1] = geometry->vertices.positions[b];
    triangle.obj_space_positions[2] = geometry->vertices.positions[c];

    triangle.clip_space_positions[0] = gfx3d_vec4_zero();
    triangle.clip_space_positions[1] = gfx3d_vec4_zero();
    triangle.clip_space_positions[2] = gfx3d_vec4_zero();
    triangle.screen_space_positions[0] = gfx3d_vec3_zero();
    triangle.screen_space_positions[1] = gfx3d_vec3_zero();
    triangle.screen_space_positions[2] = gfx3d_vec3_zero();

    triangle.has_normals = geometry->vertices.normals != NULL;
    if (triangle.has_normals) {
        triangle.normals[0] = geometry->vertices.normals[a];
        triangle.normals[1] = geometry->vertices.normals[b];
        triangle.normals[2] = geometry->vertices.normals[c];
    }

    triangle.has_colors = geometry->vertices.colors != NULL;
    if (triangle.has_colors) {
        triangle.colors[0] = geometry->vertices.colors[a];
        triangle.colors[1] = geometry->vertices.colors[b];
        triangle.colors[2] = geometry->vertices.colors[c];
    }

    return triangle;
}

static void transform_triangle(triangle_t *triangle, gfx3d_mat4_t mvp) {
    gfx3d_vec4_t v0 = gfx3d_vec4_from_vec3(triangle->obj_space_positions[0]);
    gfx3d_vec4_t v1 = gfx3d_vec4_from_vec3(triangle->obj_space_positions[1]);
    gfx3d_vec4_t v2 = gfx3d_vec4_from_vec3(triangle->obj_space_positions[2]);

    triangle->clip_space_positions[0] = gfx3d_mat4_mul_vec4(mvp, v0);
    triangle->clip_space_positions[1] = gfx3d_mat4_mul_vec4(mvp, v1);
    triangle->clip_space_positions[2] = gfx3d_mat4_mul_vec4(mvp, v2);
}

static bool clip_triangle(triangle_t *triangle) {
    // TODO: Implement clipping.
    return false;
}

static gfx3d_vec3_t project_point(gfx3d_vec4_t clip, int viewport_w, int viewport_h) {
    uint32_t win_center_x = viewport_w / 2;
    uint32_t win_center_y = viewport_h / 2;

    return gfx3d_vec3(
        (clip.x*(float)viewport_w) / (2.0f*clip.w) + win_center_x,
        (clip.y*(float)viewport_h) / (2.0f*clip.w) + win_center_y,
        clip.z / clip.w
    );
}

static void project_triangle(triangle_t *triangle, uint32_t viewport_w, uint32_t viewport_h) {
    gfx3d_vec4_t v0 = triangle->clip_space_positions[0];
    gfx3d_vec4_t v1 = triangle->clip_space_positions[1];
    gfx3d_vec4_t v2 = triangle->clip_space_positions[2];

    triangle->screen_space_positions[0] = project_point(v0, viewport_w, viewport_h);
    triangle->screen_space_positions[1] = project_point(v1, viewport_w, viewport_h);
    triangle->screen_space_positions[2] = project_point(v2, viewport_w, viewport_h);
}

static bool is_triangle_backfacing(triangle_t *triangle) {
    gfx3d_vec3_t v0 = triangle->screen_space_positions[0];
    gfx3d_vec3_t v1 = triangle->screen_space_positions[1];
    gfx3d_vec3_t v2 = triangle->screen_space_positions[2];

    gfx3d_vec3_t a = gfx3d_vec3_sub(v1, v0);
    gfx3d_vec3_t b = gfx3d_vec3_sub(v2, v0);
    gfx3d_vec3_t N = gfx3d_vec3_cross(a, b);

    return N.z < 0;
}

static float edge_function(gfx3d_vec3_t va, gfx3d_vec3_t vb, gfx3d_vec3_t vc) {
    return (vc.x - va.x) * (vb.y - va.y) - (vc.y - va.y) * (vb.x - va.x);
}

static void draw_triangle(gfx3d_pipeline_t *pipeline, triangle_t *triangle) {
    gfx3d_vec3_t v0 = triangle->screen_space_positions[0];
    gfx3d_vec3_t v1 = triangle->screen_space_positions[1];
    gfx3d_vec3_t v2 = triangle->screen_space_positions[2];

    uint32_t screen_w = pipeline->viewport_w;
    uint32_t screen_h = pipeline->viewport_h;

    float xmin = fminf(v0.x, fminf(v1.x, v2.x));
    float xmax = fmaxf(v0.x, fmaxf(v1.x, v2.x));
    float ymin = fminf(v0.y, fminf(v1.y, v2.y));
    float ymax = fmaxf(v0.y, fmaxf(v1.y, v2.y));

    if (xmin > screen_w - 1 || xmax < 0 || ymin > screen_h - 1 || ymax < 0) {
        return;
    }

    gfx3d_color_t c0 = triangle->colors[0];
    gfx3d_color_t c1 = triangle->colors[1];
    gfx3d_color_t c2 = triangle->colors[2];

    c0.r /= v0.z; c0.g /= v0.z; c0.b /= v0.z;
    c1.r /= v1.z; c1.g /= v1.z; c1.b /= v1.z;
    c2.r /= v2.z; c2.g /= v2.z; c2.b /= v2.z;

    v0.z = 1.0f / v0.z;
    v1.z = 1.0f / v1.z;
    v2.z = 1.0f / v2.z;

    uint32_t x0 = gfx3d_util_max(0, (int32_t)floorf(xmin));
    uint32_t x1 = gfx3d_util_min(screen_w - 1, (int32_t)floorf(xmax));
    uint32_t y0 = gfx3d_util_max(0, (int32_t)floorf(ymin));
    uint32_t y1 = gfx3d_util_min(screen_h - 1, (int32_t)floorf(ymax));

    float area = edge_function(v0, v1, v2);
    float inv_area = 1.0f / area;

    for (uint32_t y = y0; y <= y1; y++) {
        for (uint32_t x = x0; x <= x1; x++) {
            gfx3d_vec3_t p = gfx3d_vec3(x, y, 0.0f);
            float w0 = edge_function(v1, v2, p);
            float w1 = edge_function(v2, v0, p);
            float w2 = edge_function(v0, v1, p);

            if (w0 <= 0.0f && w1 <= 0.0f && w2 <= 0.0f) {
                w0 *= inv_area;
                w1 *= inv_area;
                w2 *= inv_area;

                float z = 1.0f / (w0 * v0.z + w1 * v1.z + w2 * v2.z);
                gfx3d_color_t col = gfx3d_color(
                    (w0 * c0.r + w1 * c1.r + w2 * c2.r) * z,
                    (w0 * c0.g + w1 * c1.g + w2 * c2.g) * z,
                    (w0 * c0.b + w1 * c1.b + w2 * c2.b) * z
                );

                int i = y * screen_w + x;
                if (z < pipeline->zbuffer[i]) {
                    pipeline->zbuffer[i] = z;

                    uint8_t r, g, b;
                    gfx3d_color_to_rgb_u8(col, &r, &g, &b);
                    gfx3d_framebuffer_set_pixel(&pipeline->framebuffer, x, y, r, g, b);
                }
            }
        }
    }
}

void gfx3d_pipeline_draw(gfx3d_pipeline_t *pipeline, gfx3d_geometry_t *geometry, gfx3d_mat4_t mvp) {
    for (int i = 0; i < geometry->num_vertices; i+=3) {
        // Assemble triangle vertices from indices.
        triangle_t triangle = triangle_from_indices(geometry, i, i+1, i+2);

        // Transform the triangle to clip space.
        transform_triangle(&triangle, mvp);

        // Clip the triangle to the view volume.
        if (clip_triangle(&triangle)) {
            continue;
        }

        // Project the triangle onto screen space.
        project_triangle(&triangle, pipeline->viewport_w, pipeline->viewport_h);

        // Is the triangle backfacing?
        if (is_triangle_backfacing(&triangle)) {
            continue;
        }

        // Draw the triangle.
        draw_triangle(pipeline, &triangle);
    }
}

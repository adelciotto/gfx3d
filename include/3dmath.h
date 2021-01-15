#ifndef GFX3D_3DMATH_H
#define GFX3D_3DMATH_H

#include "util.h"
#include <math.h>

#define GFX3D_PI M_PI
#define GFX3D_TWOPI M_PI*2.0f

typedef struct gfx3d_vec3_t {
    float x;
    float y;
    float z;
} gfx3d_vec3_t;

typedef struct gfx3d_vec4_t {
    float x;
    float y;
    float z;
    float w;
} gfx3d_vec4_t;

#define GFX3D_VEC4_ZERO() {.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f}

gfx3d_vec4_t gfx3d_vec4(float x, float y, float z);
gfx3d_vec4_t gfx3d_vec4_zero();
gfx3d_vec4_t gfx3d_vec4_from_vec3(gfx3d_vec3_t v);

#define GFX3D_VEC3_ZERO() {.x = 0.0f, .y = 0.0f, .z = 0.0f}

gfx3d_vec3_t gfx3d_vec3(float x, float y, float z);
gfx3d_vec3_t gfx3d_vec3_zero();
gfx3d_vec3_t gfx3d_vec3_sub(gfx3d_vec3_t va, gfx3d_vec3_t vb);
gfx3d_vec3_t gfx3d_vec3_add(gfx3d_vec3_t va, gfx3d_vec3_t vb);
gfx3d_vec3_t gfx3d_vec3_scale(gfx3d_vec3_t v, float s);
float gfx3d_vec3_length(gfx3d_vec3_t v);
void gfx3d_vec3_normalize(gfx3d_vec3_t *v);
float gfx3d_vec3_dot(gfx3d_vec3_t va, gfx3d_vec3_t vb);
gfx3d_vec3_t gfx3d_vec3_cross(gfx3d_vec3_t va, gfx3d_vec3_t vb);

typedef float gfx3d_mat4_t[4][4];

void gfx3d_mat4_zero(gfx3d_mat4_t out);
void gfx3d_mat4_identity(gfx3d_mat4_t out);
void gfx3d_mat4_translate_make(gfx3d_mat4_t out, gfx3d_vec3_t t);
void gfx3d_mat4_scale_make(gfx3d_mat4_t out, gfx3d_vec3_t s);
void gfx3d_mat4_rotate_make(gfx3d_mat4_t out, float angle, gfx3d_vec3_t axis);
void gfx3d_mat4_perspective(gfx3d_mat4_t out, float fovy, float aspect, float near, float far);
void gfx3d_mat4_lookat(gfx3d_mat4_t out, gfx3d_vec3_t eye, gfx3d_vec3_t center, gfx3d_vec3_t up);
void gfx3d_mat4_mul(gfx3d_mat4_t out, gfx3d_mat4_t ma, gfx3d_mat4_t mb);
gfx3d_vec4_t gfx3d_mat4_mul_vec4(gfx3d_mat4_t m, gfx3d_vec4_t v);

float gfx3d_deg2rad(float deg);
float gfx3d_lerp(float a, float b, float t);

#endif // GFX3D_3DMATH_H

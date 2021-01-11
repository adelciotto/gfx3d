#ifndef GFX3D_3DMATH_H
#define GFX3D_3DMATH_H

#include "util.h"
#include <math.h>

#define GFX3D_PI M_PI
#define GFX3D_TWOPI M_PI*2.0f

typedef struct Gfx3dVec3 {
    float x;
    float y;
    float z;
} Gfx3dVec3;

typedef struct Gfx3dVec4 {
    float x;
    float y;
    float z;
    float w;
} Gfx3dVec4;

#define GFX3D_VEC4_ZERO() {.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f}

Gfx3dVec4 gfx3d_vec4(float x, float y, float z);
Gfx3dVec4 gfx3d_vec4_from_vec3(Gfx3dVec3 v);

#define GFX3D_VEC3_ZERO() {.x = 0.0f, .y = 0.0f, .z = 0.0f}

Gfx3dVec3 gfx3d_vec3(float x, float y, float z);
Gfx3dVec3 gfx3d_vec3_zero();
Gfx3dVec3 gfx3d_vec3_sub(Gfx3dVec3 va, Gfx3dVec3 vb);
Gfx3dVec3 gfx3d_vec3_add(Gfx3dVec3 va, Gfx3dVec3 vb);
Gfx3dVec3 gfx3d_vec3_scale(Gfx3dVec3 v, float s);
float gfx3d_vec3_length(Gfx3dVec3 v);
void gfx3d_vec3_normalize(Gfx3dVec3 *v);
float gfx3d_vec3_dot(Gfx3dVec3 va, Gfx3dVec3 vb);
Gfx3dVec3 gfx3d_vec3_cross(Gfx3dVec3 va, Gfx3dVec3 vb);

typedef float Gfx3dMat4[4][4];

void gfx3d_mat4_zero(Gfx3dMat4 out);
void gfx3d_mat4_identity(Gfx3dMat4 out);
void gfx3d_mat4_translate_make(Gfx3dMat4 out, Gfx3dVec3 t);
void gfx3d_mat4_scale_make(Gfx3dMat4 out, Gfx3dVec3 s);
void gfx3d_mat4_rotate_make(Gfx3dMat4 out, float angle, Gfx3dVec3 axis);
void gfx3d_mat4_perspective(Gfx3dMat4 out, float fovy, float aspect, float near, float far);
void gfx3d_mat4_lookat(Gfx3dMat4 out, Gfx3dVec3 eye, Gfx3dVec3 center, Gfx3dVec3 up);
void gfx3d_mat4_mul(Gfx3dMat4 out, Gfx3dMat4 ma, Gfx3dMat4 mb);
Gfx3dVec4 gfx3d_mat4_mul_vec4(Gfx3dMat4 m, Gfx3dVec4 v);

float gfx3d_deg2rad(float deg);
float gfx3d_lerp(float a, float b, float t);

#endif // GFX3D_3DMATH_H

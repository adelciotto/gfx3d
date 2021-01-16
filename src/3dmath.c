#include "3dmath.h"

#define TO_RADIANS M_PI / 180.0f

gfx3d_vec4_t gfx3d_vec4(float x, float y, float z) {
    return (gfx3d_vec4_t){.x = x, .y = y, .z = z, .w = 1.0f};
}

gfx3d_vec4_t gfx3d_vec4_from_vec3(gfx3d_vec3_t v) {
    return gfx3d_vec4(v.x, v.y, v.z);
}

gfx3d_vec4_t gfx3d_vec4_zero() {
    return gfx3d_vec4(0.0f, 0.0f, 0.0f);
}

gfx3d_vec3_t gfx3d_vec3(float x, float y, float z) {
    return (gfx3d_vec3_t){.x = x, .y = y, .z = z};
}

gfx3d_vec3_t gfx3d_vec3_zero() {
    return gfx3d_vec3(0.0f, 0.0f, 0.0f);
}

gfx3d_vec3_t gfx3d_vec3_add(gfx3d_vec3_t va, gfx3d_vec3_t vb) {
    return gfx3d_vec3(va.x + vb.x, va.y + vb.y, va.z + vb.z);
}

gfx3d_vec3_t gfx3d_vec3_sub(gfx3d_vec3_t va, gfx3d_vec3_t vb) {
    return gfx3d_vec3(va.x - vb.x, va.y - vb.y, va.z - vb.z);
}

gfx3d_vec3_t gfx3d_vec3_scale(gfx3d_vec3_t v, float s) {
    return gfx3d_vec3(v.x * s, v.y * s, v.z * s);
}

gfx3d_vec3_t gfx3d_vec3_negate(gfx3d_vec3_t v) {
    return gfx3d_vec3(-v.x, -v.y, -v.z);
}

float gfx3d_vec3_length(gfx3d_vec3_t v) {
    return sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
}

void gfx3d_vec3_normalize(gfx3d_vec3_t *v) {
    float inv_len = 1.0f / gfx3d_vec3_length(*v);
    v->x *= inv_len;
    v->y *= inv_len;
    v->z *= inv_len;
}

float gfx3d_vec3_dot(gfx3d_vec3_t va, gfx3d_vec3_t vb) {
    return va.x * vb.x + va.y * vb.y + va.z * vb.z;
}

gfx3d_vec3_t gfx3d_vec3_cross(gfx3d_vec3_t va, gfx3d_vec3_t vb) {
    return gfx3d_vec3(
        va.y * vb.z - va.z * vb.y,
        va.z * vb.x - va.x * vb.z,
        va.x * vb.y - va.y * vb.x
    );
}

void gfx3d_mat4_zero(gfx3d_mat4_t out) {
    out[0][0] = 0.0f; out[1][0] = 0.0f; out[2][0] = 0.0f; out[3][0] = 0.0f;
    out[0][1] = 0.0f; out[1][1] = 0.0f; out[2][1] = 0.0f; out[3][1] = 0.0f;
    out[0][2] = 0.0f; out[1][2] = 0.0f; out[2][2] = 0.0f; out[3][2] = 0.0f;
    out[0][3] = 0.0f; out[1][3] = 0.0f; out[2][3] = 0.0f; out[3][3] = 0.0f;
}

void gfx3d_mat4_identity(gfx3d_mat4_t out) {
    out[0][0] = 1.0f; out[1][0] = 0.0f; out[2][0] = 0.0f; out[3][0] = 0.0f;
    out[0][1] = 0.0f; out[1][1] = 1.0f; out[2][1] = 0.0f; out[3][1] = 0.0f;
    out[0][2] = 0.0f; out[1][2] = 0.0f; out[2][2] = 1.0f; out[3][2] = 0.0f;
    out[0][3] = 0.0f; out[1][3] = 0.0f; out[2][3] = 0.0f; out[3][3] = 1.0f;
}

void gfx3d_mat4_translate_make(gfx3d_mat4_t out, gfx3d_vec3_t t) {
    gfx3d_mat4_identity(out);

    out[3][0] = t.x;
    out[3][1] = t.y;
    out[3][2] = t.z;
}

void gfx3d_mat4_scale_make(gfx3d_mat4_t out, gfx3d_vec3_t s) {
    gfx3d_mat4_identity(out);

    out[0][0] = s.x;
    out[1][1] = s.y;
    out[2][2] = s.z;
}

void gfx3d_mat4_rotate_make(gfx3d_mat4_t out, float angle, gfx3d_vec3_t axis) {
    gfx3d_mat4_identity(out);

    float c = cosf(angle);

    gfx3d_vec3_normalize(&axis);
    gfx3d_vec3_t v = gfx3d_vec3_scale(axis, 1.0f - c);
    gfx3d_vec3_t vs = gfx3d_vec3_scale(axis, sinf(angle));

    out[0][0] = axis.x * v.x;
    out[0][1] = axis.y * v.x;
    out[0][2] = axis.z * v.x;
    out[1][0] = axis.x * v.y;
    out[1][1] = axis.y * v.y;
    out[1][2] = axis.x * v.y;
    out[2][0] = axis.x * v.z;
    out[2][1] = axis.y * v.z;
    out[2][2] = axis.z * v.z;

    out[0][0] += c;     out[1][0] -= vs.z;  out[2][0] += vs.y;
    out[0][1] += vs.z;  out[1][1] += c;     out[2][1] -= vs.x;
    out[0][2] -= vs.y;  out[1][2] += vs.x;  out[2][2] += c;
}

void gfx3d_mat4_perspective(gfx3d_mat4_t out, float fovy, float aspect, float near, float far) {
    gfx3d_mat4_zero(out);

    float f = 1.0f / tanf(fovy * 0.5f);
    float fn = 1.0f / (near - far);

    out[0][0] = f / aspect;
    out[1][1] = f;
    out[2][2] = (near + far) * fn;
    out[2][3] = -1.0f;
    out[3][2] = 2.0f * near * far * fn;
}

void gfx3d_mat4_lookat(gfx3d_mat4_t out, gfx3d_vec3_t eye, gfx3d_vec3_t center, gfx3d_vec3_t up) {
    gfx3d_mat4_identity(out);

    gfx3d_vec3_t f = gfx3d_vec3_sub(center, eye);
    gfx3d_vec3_normalize(&f);

    gfx3d_vec3_t s = gfx3d_vec3_cross(f, up);
    gfx3d_vec3_normalize(&s);
    gfx3d_vec3_t u = gfx3d_vec3_cross(s, f);

    out[0][0] = s.x;
    out[0][1] = u.x;
    out[0][2] = -f.x;
    out[1][0] = s.y;
    out[1][1] = u.y;
    out[1][2] = -f.y;
    out[2][0] = s.z;
    out[2][1] = u.z;
    out[2][2] = -f.z;
    out[3][0] = -gfx3d_vec3_dot(s, eye);
    out[3][1] = gfx3d_vec3_dot(u, eye);
    out[3][2] = gfx3d_vec3_dot(f, eye);
}

void gfx3d_mat4_mul(gfx3d_mat4_t out, gfx3d_mat4_t ma, gfx3d_mat4_t mb) {
    float a00 = ma[0][0], a01 = ma[0][1], a02 = ma[0][2], a03 = ma[0][3],
          a10 = ma[1][0], a11 = ma[1][1], a12 = ma[1][2], a13 = ma[1][3],
          a20 = ma[2][0], a21 = ma[2][1], a22 = ma[2][2], a23 = ma[2][3],
          a30 = ma[3][0], a31 = ma[3][1], a32 = ma[3][2], a33 = ma[3][3];

    float b00 = mb[0][0], b01 = mb[0][1], b02 = mb[0][2], b03 = mb[0][3],
          b10 = mb[1][0], b11 = mb[1][1], b12 = mb[1][2], b13 = mb[1][3],
          b20 = mb[2][0], b21 = mb[2][1], b22 = mb[2][2], b23 = mb[2][3],
          b30 = mb[3][0], b31 = mb[3][1], b32 = mb[3][2], b33 = mb[3][3];

    out[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
    out[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
    out[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
    out[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;
    out[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
    out[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
    out[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
    out[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;
    out[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
    out[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
    out[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
    out[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;
    out[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
    out[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
    out[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
    out[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
}

gfx3d_vec4_t gfx3d_mat4_mul_vec4(gfx3d_mat4_t m, gfx3d_vec4_t v) {
    return (gfx3d_vec4_t){
        m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w,
        m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w,
        m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w,
        m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w
    };
}

float gfx3d_deg2rad(float deg) {
    return deg*TO_RADIANS;
}

float gfx3d_lerp(float a, float b, float t) {
    return (1.0f - t) * a + t * b;
}


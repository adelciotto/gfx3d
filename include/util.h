#ifndef GFX3D_UTIL_H
#define GFX3D_UTIL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ERRORF(fmt, ...) \
    fprintf(stderr, "ERROR - %s() in %s, line %i: " fmt"\n", __func__, __FILE__, __LINE__, ## __VA_ARGS__)
#define WARNF(fmt, ...) \
    fprintf(stderr, "WARN - %s() in %s, line %i: " fmt"\n", __func__, __FILE__, __LINE__, ## __VA_ARGS__)
#define INFOF(fmt, ...) \
    printf("INFO - %s() in %s, line %i: " fmt"\n", __func__, __FILE__, __LINE__, ## __VA_ARGS__)

#define ARRAY_LEN(arr) (int)((sizeof(arr)) / (sizeof(arr[0])))

static inline int32_t gfx3d_util_max(int32_t a, int32_t b) {
    return a > b ? a : b;
}

static inline int32_t gfx3d_util_min(int32_t a, int32_t b) {
    return a < b ? a : b;
}

#endif // GFX3D_UTIL_H

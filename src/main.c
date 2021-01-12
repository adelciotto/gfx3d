#include "gfx3d.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int exit_code = EXIT_SUCCESS;

    const uint32_t width = 640;
    const uint32_t height = 480;

    Gfx3dWindow win;
    if (!gfx3d_window_create(&win, width, height, 2, false, true)) {
        exit_code = EXIT_FAILURE;
        goto exit;
    }

    Gfx3dPipeline pipeline;
    if (!gfx3d_pipeline_create(&pipeline, width, height)) {
        exit_code = EXIT_FAILURE;
        goto exit;
    }

    Gfx3dGeometry cube_geo;
    gfx3d_geometry_cube(&cube_geo);

    Gfx3dMat4 proj;
    gfx3d_mat4_perspective(proj, gfx3d_deg2rad(90.0f), (float)width / (float)height, 0.1f, 100.0f);

    Gfx3dVec3 camera_pos = gfx3d_vec3(0.0f, 0.0f, 3.0f);
    Gfx3dVec3 camera_front = gfx3d_vec3(0.0f, 0.0f, -1.0f);
    Gfx3dVec3 camera_up = gfx3d_vec3(0.0f, 1.0f, 0.0f);

    while (!win.should_close) {
        gfx3d_window_poll_events(&win);

        float t = gfx3d_elapsed_time();
        float x = 1.2f * sinf(t*GFX3D_TWOPI*0.3f + 0.1f) + 1.5f * sinf(t*GFX3D_TWOPI*0.2f + 0.3f);
        Gfx3dMat4 translate;
        gfx3d_mat4_translate_make(translate, gfx3d_vec3(x, 0.0f, -1.0f));

        float angle = sinf(t*GFX3D_TWOPI*0.05f + 0.1f) + 1.15f * sinf(t*GFX3D_TWOPI*0.1f + 0.3f);
        Gfx3dMat4 rotate;
        gfx3d_mat4_rotate_make(rotate, angle, gfx3d_vec3(1.0f, 1.0f, 1.0f));

        Gfx3dMat4 model;
        gfx3d_mat4_identity(model);
        gfx3d_mat4_mul(model, translate, rotate);

        Gfx3dMat4 view;
        gfx3d_mat4_lookat(view, camera_pos, gfx3d_vec3_add(camera_pos, camera_front), camera_up);

        Gfx3dMat4 mvp;
        gfx3d_mat4_mul(mvp, proj, view);
        gfx3d_mat4_mul(mvp, mvp, model);

        Gfx3dColor col = GFX3D_COLOR_BLACK();
        gfx3d_pipeline_clear(&pipeline, col);

        gfx3d_pipeline_draw(&pipeline, &cube_geo, mvp);

        gfx3d_window_present(&win, pipeline.rasterizer.framebuffer.pixels, pipeline.rasterizer.framebuffer.pitch);
    }

exit:
    gfx3d_pipeline_destroy(&pipeline);
    gfx3d_window_destroy(&win);
    return exit_code;
}

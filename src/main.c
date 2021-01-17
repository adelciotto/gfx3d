#include "gfx3d.h"
#include <stdlib.h>

#define MAX_FRAME_SAMPLES 100

typedef struct frame_stats_t {
    uint64_t current_counter;
    uint64_t last_counter;
    double delta_time_ms;
    double delta_time_secs;
    int sample_index;
    double samples_sum;
    double samples[MAX_FRAME_SAMPLES];
    double average_fps;
} frame_stats_t;

int main(int argc, char *argv[]) {
    int exit_code = EXIT_SUCCESS;

    const uint32_t width = 640;
    const uint32_t height = 480;

    gfx3d_window_t win;
    if (!gfx3d_window_create(&win, width, height, 2, false, true)) {
        exit_code = EXIT_FAILURE;
        goto exit;
    }

    gfx3d_text_init(win.sdl_rend);

    gfx3d_pipeline_t pipeline;
    if (!gfx3d_pipeline_create(&pipeline, width, height)) {
        exit_code = EXIT_FAILURE;
        goto exit;
    }

    gfx3d_geometry_t cube_geo;
    gfx3d_geometry_cube(&cube_geo);

    gfx3d_mat4_t proj;
    gfx3d_mat4_perspective(proj, gfx3d_deg2rad(90.0f), (float)width / (float)height, 0.1f, 100.0f);

    gfx3d_vec3_t camera_pos = gfx3d_vec3(0.0f, 0.0f, 3.0f);
    gfx3d_vec3_t camera_front = gfx3d_vec3(0.0f, 0.0f, -1.0f);
    gfx3d_vec3_t camera_up = gfx3d_vec3(0.0f, 1.0f, 0.0f);

    frame_stats_t frame_stats = (frame_stats_t){
        .current_counter = gfx3d_performance_get_counter(),
        .last_counter = 0,
        .delta_time_ms = 0.0f,
        .delta_time_secs = 0.0f,
        .sample_index = 0,
        .samples_sum = 0.0f,
        .average_fps = 0.0f
    };
    for (int i = 0; i < MAX_FRAME_SAMPLES; i++) frame_stats.samples[i] = 0.0f;

    while (!win.should_close) {
        frame_stats.last_counter = frame_stats.current_counter;
        frame_stats.current_counter = gfx3d_performance_get_counter();
        frame_stats.delta_time_ms = gfx3d_performance_elapsed_time(frame_stats.current_counter, frame_stats.last_counter);
        frame_stats.delta_time_secs = frame_stats.delta_time_ms / 1000.0;

        gfx3d_window_poll_events(&win);

        float t = gfx3d_elapsed_time();
        float x = 1.2f * sinf(t*GFX3D_TWOPI*0.3f + 0.1f) + 1.5f * sinf(t*GFX3D_TWOPI*0.2f + 0.3f);
        gfx3d_mat4_t translate;
        gfx3d_mat4_translate_make(translate, gfx3d_vec3(x, 0.0f, -1.0f));

        float angle = sinf(t*GFX3D_TWOPI*0.05f + 0.1f) + 1.15f * sinf(t*GFX3D_TWOPI*0.1f + 0.3f);
        gfx3d_mat4_t rotate;
        gfx3d_mat4_rotate_make(rotate, angle, gfx3d_vec3(1.0f, 1.0f, 1.0f));

        gfx3d_mat4_t model;
        gfx3d_mat4_identity(model);
        gfx3d_mat4_mul(model, translate, rotate);

        gfx3d_mat4_t view;
        gfx3d_mat4_lookat(view, camera_pos, gfx3d_vec3_add(camera_pos, camera_front), camera_up);

        gfx3d_mat4_t mvp;
        gfx3d_mat4_mul(mvp, proj, view);
        gfx3d_mat4_mul(mvp, mvp, model);

        gfx3d_color_t col = GFX3D_COLOR_BLACK();
        gfx3d_pipeline_clear(&pipeline, col);

        gfx3d_pipeline_draw(&pipeline, &cube_geo, mvp);

        gfx3d_window_upload_pixels(&win, pipeline.framebuffer.pixels, pipeline.framebuffer.pitch);

        double new_sample = 1.0 / frame_stats.delta_time_secs;
        frame_stats.samples_sum -= frame_stats.samples[frame_stats.sample_index];
        frame_stats.samples_sum += new_sample;
        frame_stats.samples[frame_stats.sample_index] = new_sample;
        frame_stats.sample_index = (frame_stats.sample_index + 1) % MAX_FRAME_SAMPLES;
        frame_stats.average_fps = frame_stats.samples_sum / (double)MAX_FRAME_SAMPLES;

        char buf[1024];
        sprintf(buf, "%.2f FPS, %.4f ms/f", frame_stats.average_fps, frame_stats.delta_time_ms);
        gfx3d_text_draw(buf, gfx3d_vec2(10.0f, 10.0f), 1.0f);

        gfx3d_window_swap(&win);
    }

exit:
    gfx3d_pipeline_destroy(&pipeline);
    gfx3d_window_destroy(&win);
    return exit_code;
}

/*
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <stdio.h>

#அந்தர்பாவ "libavutil/ambient_viewing_environment.h"
#அந்தர்பாவ "libavutil/frame.h"
#அந்தர்பாவ "libavutil/mem.h"

நிலையான வெறுமை print_env(மாறிலி AVAmbientViewingEnvironment *env)
{
    printf("illuminance=%d/%d, light_x=%d/%d, light_y=%d/%d\n",
           env->ambient_illuminance.இலக்கம், env->ambient_illuminance.den,
           env->ambient_light_x.இலக்கம்,     env->ambient_light_x.den,
           env->ambient_light_y.இலக்கம்,     env->ambient_light_y.den);
}

முழு முதன்மை(வெறுமை)
{
    AVAmbientViewingEnvironment *env;
    AVFrame *frame;
    size_t size = 0;

    /* av_ambient_viewing_environment_alloc with size out-param */
    printf("Testing av_ambient_viewing_environment_alloc(&size)\n");
    env = av_ambient_viewing_environment_alloc(&size);
    எனில் (env) {
        printf("alloc: OK, size_set=%s\n", size == அளவு(*env) ? "yes" : "no");
        print_env(env);
        av_free(env);
    } இல்லையெனில் {
        printf("alloc: FAIL\n");
    }

    /* av_ambient_viewing_environment_alloc with NULL size */
    printf("\nTesting av_ambient_viewing_environment_alloc(NULL)\n");
    env = av_ambient_viewing_environment_alloc(வெற்று);
    எனில் (env) {
        printf("alloc(NULL): OK\n");
        print_env(env);
        av_free(env);
    } இல்லையெனில் {
        printf("alloc(NULL): FAIL\n");
    }

    /* write and read back */
    printf("\nTesting write/read back\n");
    env = av_ambient_viewing_environment_alloc(வெற்று);
    எனில் (env) {
        env->ambient_illuminance = (AVRational){ 314, 10 };
        env->ambient_light_x     = (AVRational){ 15635, 50000 };
        env->ambient_light_y     = (AVRational){ 16450, 50000 };
        print_env(env);
        av_free(env);
    }

    /* av_ambient_viewing_environment_create_side_data */
    printf("\nTesting av_ambient_viewing_environment_create_side_data()\n");
    frame = av_frame_alloc();
    எனில் (frame) {
        env = av_ambient_viewing_environment_create_side_data(frame);
        எனில் (env) {
            printf("side_data: OK\n");
            print_env(env);
        } இல்லையெனில் {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    printf("\nTesting OOM paths\n");
    av_max_alloc(1);
    env = av_ambient_viewing_environment_alloc(&size);
    printf("alloc OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    env = av_ambient_viewing_environment_alloc(வெற்று);
    printf("alloc(NULL) OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    av_max_alloc(INT_MAX);

    frame = av_frame_alloc();
    எனில் (frame) {
        av_max_alloc(1);
        env = av_ambient_viewing_environment_create_side_data(frame);
        printf("side_data OOM: %s\n", env ? "FAIL" : "OK");
        av_max_alloc(INT_MAX);
        av_frame_free(&frame);
    }

    திரும்பு 0;
}

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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/ambient_viewing_environment.h"
#अन्तर्भाव "libavutil/frame.h"
#अन्तर्भाव "libavutil/mem.h"

स्थिर शून्य print_env(ध्रुव AVAmbientViewingEnvironment *env)
{
    printf("illuminance=%d/%d, light_x=%d/%d, light_y=%d/%d\n",
           env->ambient_illuminance.अङ्कः, env->ambient_illuminance.den,
           env->ambient_light_x.अङ्कः,     env->ambient_light_x.den,
           env->ambient_light_y.अङ्कः,     env->ambient_light_y.den);
}

पूर्णाङ्क main(शून्य)
{
    AVAmbientViewingEnvironment *env;
    AVFrame *frame;
    size_t size = 0;

    /* av_ambient_viewing_environment_alloc with size out-param */
    printf("Testing av_ambient_viewing_environment_alloc(&size)\n");
    env = av_ambient_viewing_environment_alloc(&size);
    सचे (env) {
        printf("alloc: OK, size_set=%s\n", size == परिमाण(*env) ? "yes" : "no");
        print_env(env);
        av_free(env);
    } अञ्ञथा {
        printf("alloc: FAIL\n");
    }

    /* av_ambient_viewing_environment_alloc with NULL size */
    printf("\nTesting av_ambient_viewing_environment_alloc(NULL)\n");
    env = av_ambient_viewing_environment_alloc(रिक्त);
    सचे (env) {
        printf("alloc(NULL): OK\n");
        print_env(env);
        av_free(env);
    } अञ्ञथा {
        printf("alloc(NULL): FAIL\n");
    }

    /* write and read back */
    printf("\nTesting write/read back\n");
    env = av_ambient_viewing_environment_alloc(रिक्त);
    सचे (env) {
        env->ambient_illuminance = (AVRational){ 314, 10 };
        env->ambient_light_x     = (AVRational){ 15635, 50000 };
        env->ambient_light_y     = (AVRational){ 16450, 50000 };
        print_env(env);
        av_free(env);
    }

    /* av_ambient_viewing_environment_create_side_data */
    printf("\nTesting av_ambient_viewing_environment_create_side_data()\n");
    frame = av_frame_alloc();
    सचे (frame) {
        env = av_ambient_viewing_environment_create_side_data(frame);
        सचे (env) {
            printf("side_data: OK\n");
            print_env(env);
        } अञ्ञथा {
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
    env = av_ambient_viewing_environment_alloc(रिक्त);
    printf("alloc(NULL) OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    av_max_alloc(INT_MAX);

    frame = av_frame_alloc();
    सचे (frame) {
        av_max_alloc(1);
        env = av_ambient_viewing_environment_create_side_data(frame);
        printf("side_data OOM: %s\n", env ? "FAIL" : "OK");
        av_max_alloc(INT_MAX);
        av_frame_free(&frame);
    }

    पटिनिवत्त 0;
}

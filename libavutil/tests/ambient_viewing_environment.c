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

स्थिर शून्य print_env(स्थिरांक AVAmbientViewingEnvironment *env)
{
    म_लिखो("illuminance=%d/%d, light_x=%d/%d, light_y=%d/%d\n",
           env->ambient_illuminance.अंक, env->ambient_illuminance.den,
           env->ambient_light_x.अंक,     env->ambient_light_x.den,
           env->ambient_light_y.अंक,     env->ambient_light_y.den);
}

पूर्णांक main(शून्य)
{
    AVAmbientViewingEnvironment *env;
    AVFrame *frame;
    माप_प्रकार size = 0;

    /* av_ambient_viewing_environment_alloc with size out-param */
    म_लिखो("Testing av_ambient_viewing_environment_alloc(&size)\n");
    env = av_ambient_viewing_environment_alloc(&size);
    जर (env) {
        म_लिखो("alloc: OK, size_set=%s\n", size == आकार(*env) ? "yes" : "no");
        print_env(env);
        av_free(env);
    } अन्यथा {
        म_लिखो("alloc: FAIL\n");
    }

    /* av_ambient_viewing_environment_alloc with NULL size */
    म_लिखो("\nTesting av_ambient_viewing_environment_alloc(NULL)\n");
    env = av_ambient_viewing_environment_alloc(रिक्त);
    जर (env) {
        म_लिखो("alloc(NULL): OK\n");
        print_env(env);
        av_free(env);
    } अन्यथा {
        म_लिखो("alloc(NULL): FAIL\n");
    }

    /* write and read back */
    म_लिखो("\nTesting write/read back\n");
    env = av_ambient_viewing_environment_alloc(रिक्त);
    जर (env) {
        env->ambient_illuminance = (AVRational){ 314, 10 };
        env->ambient_light_x     = (AVRational){ 15635, 50000 };
        env->ambient_light_y     = (AVRational){ 16450, 50000 };
        print_env(env);
        av_free(env);
    }

    /* av_ambient_viewing_environment_create_side_data */
    म_लिखो("\nTesting av_ambient_viewing_environment_create_side_data()\n");
    frame = av_frame_alloc();
    जर (frame) {
        env = av_ambient_viewing_environment_create_side_data(frame);
        जर (env) {
            म_लिखो("side_data: OK\n");
            print_env(env);
        } अन्यथा {
            म_लिखो("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    म_लिखो("\nTesting OOM paths\n");
    av_max_alloc(1);
    env = av_ambient_viewing_environment_alloc(&size);
    म_लिखो("alloc OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    env = av_ambient_viewing_environment_alloc(रिक्त);
    म_लिखो("alloc(NULL) OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    av_max_alloc(पूर्णांक_उच्च);

    frame = av_frame_alloc();
    जर (frame) {
        av_max_alloc(1);
        env = av_ambient_viewing_environment_create_side_data(frame);
        म_लिखो("side_data OOM: %s\n", env ? "FAIL" : "OK");
        av_max_alloc(पूर्णांक_उच्च);
        av_frame_free(&frame);
    }

    परत 0;
}

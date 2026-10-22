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

#ضمن <limits.h>
#ضمن <stdio.h>

#ضمن "libavutil/ambient_viewing_environment.h"
#ضمن "libavutil/frame.h"
#ضمن "libavutil/mem.h"

ساكن فراغ print_env(ثابت AVAmbientViewingEnvironment *env)
{
    چاپ_کن("illuminance=%d/%d, light_x=%d/%d, light_y=%d/%d\n",
           env->ambient_illuminance.رقم, env->ambient_illuminance.den,
           env->ambient_light_x.رقم,     env->ambient_light_x.den,
           env->ambient_light_y.رقم,     env->ambient_light_y.den);
}

صحيح اصلی(فراغ)
{
    AVAmbientViewingEnvironment *env;
    AVFrame *قاب;
    size_t اندازه = 0;

    /* av_ambient_viewing_environment_alloc with size out-param */
    چاپ_کن("Testing av_ambient_viewing_environment_alloc(&size)\n");
    env = av_ambient_viewing_environment_alloc(&اندازه);
    إذا (env) {
        چاپ_کن("alloc: OK, size_set=%s\n", اندازه == حجم(*env) ? "yes" : "no");
        print_env(env);
        av_free(env);
    } وإلا {
        چاپ_کن("alloc: FAIL\n");
    }

    /* av_ambient_viewing_environment_alloc with NULL size */
    چاپ_کن("\nTesting av_ambient_viewing_environment_alloc(NULL)\n");
    env = av_ambient_viewing_environment_alloc(عدم);
    إذا (env) {
        چاپ_کن("alloc(NULL): OK\n");
        print_env(env);
        av_free(env);
    } وإلا {
        چاپ_کن("alloc(NULL): FAIL\n");
    }

    /* write and read back */
    چاپ_کن("\nTesting write/read back\n");
    env = av_ambient_viewing_environment_alloc(عدم);
    إذا (env) {
        env->ambient_illuminance = (AVRational){ 314, 10 };
        env->ambient_light_x     = (AVRational){ 15635, 50000 };
        env->ambient_light_y     = (AVRational){ 16450, 50000 };
        print_env(env);
        av_free(env);
    }

    /* av_ambient_viewing_environment_create_side_data */
    چاپ_کن("\nTesting av_ambient_viewing_environment_create_side_data()\n");
    قاب = av_قاب_alloc();
    إذا (قاب) {
        env = av_ambient_viewing_environment_create_side_داده(قاب);
        إذا (env) {
            چاپ_کن("side_data: OK\n");
            print_env(env);
        } وإلا {
            چاپ_کن("side_data: FAIL\n");
        }
        av_قاب_free(&قاب);
    }

    /* OOM paths via av_max_alloc */
    چاپ_کن("\nTesting OOM paths\n");
    av_max_alloc(1);
    env = av_ambient_viewing_environment_alloc(&اندازه);
    چاپ_کن("alloc OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    env = av_ambient_viewing_environment_alloc(عدم);
    چاپ_کن("alloc(NULL) OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    av_max_alloc(بیشترین_صحیح);

    قاب = av_قاب_alloc();
    إذا (قاب) {
        av_max_alloc(1);
        env = av_ambient_viewing_environment_create_side_داده(قاب);
        چاپ_کن("side_data OOM: %s\n", env ? "FAIL" : "OK");
        av_max_alloc(بیشترین_صحیح);
        av_قاب_free(&قاب);
    }

    أرجع 0;
}

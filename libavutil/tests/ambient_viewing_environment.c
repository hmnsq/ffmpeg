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
    چاپ_کړه("illuminance=%d/%d, light_x=%d/%d, light_y=%d/%d\n",
           env->ambient_illuminance.عدد, env->ambient_illuminance.den,
           env->ambient_light_x.عدد,     env->ambient_light_x.den,
           env->ambient_light_y.عدد,     env->ambient_light_y.den);
}

صحيح اصلي(فراغ)
{
    AVAmbientViewingEnvironment *env;
    AVFrame *چوکاټ;
    size_t اندازه = 0;

    /* av_ambient_viewing_environment_alloc with size out-param */
    چاپ_کړه("Testing av_ambient_viewing_environment_alloc(&size)\n");
    env = av_ambient_viewing_environment_alloc(&اندازه);
    إذا (env) {
        چاپ_کړه("alloc: OK, size_set=%s\n", اندازه == حجم(*env) ? "yes" : "no");
        print_env(env);
        av_free(env);
    } وإلا {
        چاپ_کړه("alloc: FAIL\n");
    }

    /* av_ambient_viewing_environment_alloc with NULL size */
    چاپ_کړه("\nTesting av_ambient_viewing_environment_alloc(NULL)\n");
    env = av_ambient_viewing_environment_alloc(عدم);
    إذا (env) {
        چاپ_کړه("alloc(NULL): OK\n");
        print_env(env);
        av_free(env);
    } وإلا {
        چاپ_کړه("alloc(NULL): FAIL\n");
    }

    /* write and read back */
    چاپ_کړه("\nTesting write/read back\n");
    env = av_ambient_viewing_environment_alloc(عدم);
    إذا (env) {
        env->ambient_illuminance = (AVRational){ 314, 10 };
        env->ambient_light_x     = (AVRational){ 15635, 50000 };
        env->ambient_light_y     = (AVRational){ 16450, 50000 };
        print_env(env);
        av_free(env);
    }

    /* av_ambient_viewing_environment_create_side_data */
    چاپ_کړه("\nTesting av_ambient_viewing_environment_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        env = av_ambient_viewing_environment_create_side_معلومات(چوکاټ);
        إذا (env) {
            چاپ_کړه("side_data: OK\n");
            print_env(env);
        } وإلا {
            چاپ_کړه("side_data: FAIL\n");
        }
        av_چوکاټ_free(&چوکاټ);
    }

    /* OOM paths via av_max_alloc */
    چاپ_کړه("\nTesting OOM paths\n");
    av_max_alloc(1);
    env = av_ambient_viewing_environment_alloc(&اندازه);
    چاپ_کړه("alloc OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    env = av_ambient_viewing_environment_alloc(عدم);
    چاپ_کړه("alloc(NULL) OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    av_max_alloc(لوی_عدد);

    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        av_max_alloc(1);
        env = av_ambient_viewing_environment_create_side_معلومات(چوکاټ);
        چاپ_کړه("side_data OOM: %s\n", env ? "FAIL" : "OK");
        av_max_alloc(لوی_عدد);
        av_چوکاټ_free(&چوکاټ);
    }

    أرجع 0;
}

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
    لکو("illuminance=%d/%d, light_x=%d/%d, light_y=%d/%d\n",
           env->ambient_illuminance.انگ, env->ambient_illuminance.den,
           env->ambient_light_x.انگ,     env->ambient_light_x.den,
           env->ambient_light_y.انگ,     env->ambient_light_y.den);
}

صحيح مکيه(فراغ)
{
    AVAmbientViewingEnvironment *env;
    AVFrame *چوکٺو;
    size_t سائيز = 0;

    /* av_ambient_viewing_environment_alloc with size out-param */
    لکو("Testing av_ambient_viewing_environment_alloc(&size)\n");
    env = av_ambient_viewing_environment_alloc(&سائيز);
    إذا (env) {
        لکو("alloc: OK, size_set=%s\n", سائيز == حجم(*env) ? "yes" : "no");
        print_env(env);
        av_free(env);
    } وإلا {
        لکو("alloc: FAIL\n");
    }

    /* av_ambient_viewing_environment_alloc with NULL size */
    لکو("\nTesting av_ambient_viewing_environment_alloc(NULL)\n");
    env = av_ambient_viewing_environment_alloc(عدم);
    إذا (env) {
        لکو("alloc(NULL): OK\n");
        print_env(env);
        av_free(env);
    } وإلا {
        لکو("alloc(NULL): FAIL\n");
    }

    /* write and read back */
    لکو("\nTesting write/read back\n");
    env = av_ambient_viewing_environment_alloc(عدم);
    إذا (env) {
        env->ambient_illuminance = (AVRational){ 314, 10 };
        env->ambient_light_x     = (AVRational){ 15635, 50000 };
        env->ambient_light_y     = (AVRational){ 16450, 50000 };
        print_env(env);
        av_free(env);
    }

    /* av_ambient_viewing_environment_create_side_data */
    لکو("\nTesting av_ambient_viewing_environment_create_side_data()\n");
    چوکٺو = av_چوکٺو_alloc();
    إذا (چوکٺو) {
        env = av_ambient_viewing_environment_create_side_معلومات(چوکٺو);
        إذا (env) {
            لکو("side_data: OK\n");
            print_env(env);
        } وإلا {
            لکو("side_data: FAIL\n");
        }
        av_چوکٺو_free(&چوکٺو);
    }

    /* OOM paths via av_max_alloc */
    لکو("\nTesting OOM paths\n");
    av_max_alloc(1);
    env = av_ambient_viewing_environment_alloc(&سائيز);
    لکو("alloc OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    env = av_ambient_viewing_environment_alloc(عدم);
    لکو("alloc(NULL) OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    av_max_alloc(وڌ_کان_وڌ_عدد);

    چوکٺو = av_چوکٺو_alloc();
    إذا (چوکٺو) {
        av_max_alloc(1);
        env = av_ambient_viewing_environment_create_side_معلومات(چوکٺو);
        لکو("side_data OOM: %s\n", env ? "FAIL" : "OK");
        av_max_alloc(وڌ_کان_وڌ_عدد);
        av_چوکٺو_free(&چوکٺو);
    }

    أرجع 0;
}

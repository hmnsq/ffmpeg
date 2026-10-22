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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/ambient_viewing_environment.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਸਥਿਰ ਖਾਲੀ print_env(ਅਚਲ AVAmbientViewingEnvironment *env)
{
    ਲਿਖੋ("illuminance=%d/%d, light_x=%d/%d, light_y=%d/%d\n",
           env->ambient_illuminance.ਅੰਕ, env->ambient_illuminance.den,
           env->ambient_light_x.ਅੰਕ,     env->ambient_light_x.den,
           env->ambient_light_y.ਅੰਕ,     env->ambient_light_y.den);
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVAmbientViewingEnvironment *env;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ = 0;

    /* av_ambient_viewing_environment_alloc with size out-param */
    ਲਿਖੋ("Testing av_ambient_viewing_environment_alloc(&size)\n");
    env = av_ambient_viewing_environment_alloc(&ਮਾਪ);
    ਜੇ (env) {
        ਲਿਖੋ("alloc: OK, size_set=%s\n", ਮਾਪ == ਆਕਾਰ(*env) ? "yes" : "no");
        print_env(env);
        av_free(env);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("alloc: FAIL\n");
    }

    /* av_ambient_viewing_environment_alloc with NULL size */
    ਲਿਖੋ("\nTesting av_ambient_viewing_environment_alloc(NULL)\n");
    env = av_ambient_viewing_environment_alloc(ਨਿਰਾ);
    ਜੇ (env) {
        ਲਿਖੋ("alloc(NULL): OK\n");
        print_env(env);
        av_free(env);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("alloc(NULL): FAIL\n");
    }

    /* write and read back */
    ਲਿਖੋ("\nTesting write/read back\n");
    env = av_ambient_viewing_environment_alloc(ਨਿਰਾ);
    ਜੇ (env) {
        env->ambient_illuminance = (AVRational){ 314, 10 };
        env->ambient_light_x     = (AVRational){ 15635, 50000 };
        env->ambient_light_y     = (AVRational){ 16450, 50000 };
        print_env(env);
        av_free(env);
    }

    /* av_ambient_viewing_environment_create_side_data */
    ਲਿਖੋ("\nTesting av_ambient_viewing_environment_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        env = av_ambient_viewing_environment_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਜੇ (env) {
            ਲਿਖੋ("side_data: OK\n");
            print_env(env);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("side_data: FAIL\n");
        }
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    /* OOM paths via av_max_alloc */
    ਲਿਖੋ("\nTesting OOM paths\n");
    av_max_alloc(1);
    env = av_ambient_viewing_environment_alloc(&ਮਾਪ);
    ਲਿਖੋ("alloc OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    env = av_ambient_viewing_environment_alloc(ਨਿਰਾ);
    ਲਿਖੋ("alloc(NULL) OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);

    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        av_max_alloc(1);
        env = av_ambient_viewing_environment_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਲਿਖੋ("side_data OOM: %s\n", env ? "FAIL" : "OK");
        av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    ਵਾਪਸ 0;
}

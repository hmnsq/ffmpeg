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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/ambient_viewing_environment.h"
#ಅನ್ತರ್ಭಾವ "libavutil/frame.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಸ್ಥಿರ ಶೂನ್ಯ print_env(ಸ್ಥಿರಾಂಕ AVAmbientViewingEnvironment *env)
{
    ಬರೆ("illuminance=%d/%d, light_x=%d/%d, light_y=%d/%d\n",
           env->ambient_illuminance.ಅಂಕೆ, env->ambient_illuminance.den,
           env->ambient_light_x.ಅಂಕೆ,     env->ambient_light_x.den,
           env->ambient_light_y.ಅಂಕೆ,     env->ambient_light_y.den);
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVAmbientViewingEnvironment *env;
    AVFrame *ಚೌಕಟ್ಟು;
    size_t ಗಾತ್ರ_2 = 0;

    /* av_ambient_viewing_environment_alloc with size out-param */
    ಬರೆ("Testing av_ambient_viewing_environment_alloc(&size)\n");
    env = av_ambient_viewing_environment_alloc(&ಗಾತ್ರ_2);
    ಆದರೆ (env) {
        ಬರೆ("alloc: OK, size_set=%s\n", ಗಾತ್ರ_2 == ಗಾತ್ರ(*env) ? "yes" : "no");
        print_env(env);
        av_free(env);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಬರೆ("alloc: FAIL\n");
    }

    /* av_ambient_viewing_environment_alloc with NULL size */
    ಬರೆ("\nTesting av_ambient_viewing_environment_alloc(NULL)\n");
    env = av_ambient_viewing_environment_alloc(ಖಾಲಿ);
    ಆದರೆ (env) {
        ಬರೆ("alloc(NULL): OK\n");
        print_env(env);
        av_free(env);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಬರೆ("alloc(NULL): FAIL\n");
    }

    /* write and read back */
    ಬರೆ("\nTesting write/read back\n");
    env = av_ambient_viewing_environment_alloc(ಖಾಲಿ);
    ಆದರೆ (env) {
        env->ambient_illuminance = (AVRational){ 314, 10 };
        env->ambient_light_x     = (AVRational){ 15635, 50000 };
        env->ambient_light_y     = (AVRational){ 16450, 50000 };
        print_env(env);
        av_free(env);
    }

    /* av_ambient_viewing_environment_create_side_data */
    ಬರೆ("\nTesting av_ambient_viewing_environment_create_side_data()\n");
    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        env = av_ambient_viewing_environment_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಆದರೆ (env) {
            ಬರೆ("side_data: OK\n");
            print_env(env);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("side_data: FAIL\n");
        }
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    /* OOM paths via av_max_alloc */
    ಬರೆ("\nTesting OOM paths\n");
    av_max_alloc(1);
    env = av_ambient_viewing_environment_alloc(&ಗಾತ್ರ_2);
    ಬರೆ("alloc OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    env = av_ambient_viewing_environment_alloc(ಖಾಲಿ);
    ಬರೆ("alloc(NULL) OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);

    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        av_max_alloc(1);
        env = av_ambient_viewing_environment_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಬರೆ("side_data OOM: %s\n", env ? "FAIL" : "OK");
        av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    ಹಿಂತಿರುಗಿ 0;
}

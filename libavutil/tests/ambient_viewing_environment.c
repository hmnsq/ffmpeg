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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/ambient_viewing_environment.h"
#అన్తర్భావ "libavutil/frame.h"
#అన్తర్భావ "libavutil/mem.h"

స్థిర శూన్య print_env(స్థిరరాశి AVAmbientViewingEnvironment *env)
{
    రాయి("illuminance=%d/%d, light_x=%d/%d, light_y=%d/%d\n",
           env->ambient_illuminance.అంకె, env->ambient_illuminance.den,
           env->ambient_light_x.అంకె,     env->ambient_light_x.den,
           env->ambient_light_y.అంకె,     env->ambient_light_y.den);
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVAmbientViewingEnvironment *env;
    AVFrame *చట్రం;
    size_t కొలత = 0;

    /* av_ambient_viewing_environment_alloc with size out-param */
    రాయి("Testing av_ambient_viewing_environment_alloc(&size)\n");
    env = av_ambient_viewing_environment_alloc(&కొలత);
    ఒకవేళ (env) {
        రాయి("alloc: OK, size_set=%s\n", కొలత == పరిమాణం(*env) ? "yes" : "no");
        print_env(env);
        av_free(env);
    } లేకపోతే {
        రాయి("alloc: FAIL\n");
    }

    /* av_ambient_viewing_environment_alloc with NULL size */
    రాయి("\nTesting av_ambient_viewing_environment_alloc(NULL)\n");
    env = av_ambient_viewing_environment_alloc(ఖాళీ);
    ఒకవేళ (env) {
        రాయి("alloc(NULL): OK\n");
        print_env(env);
        av_free(env);
    } లేకపోతే {
        రాయి("alloc(NULL): FAIL\n");
    }

    /* write and read back */
    రాయి("\nTesting write/read back\n");
    env = av_ambient_viewing_environment_alloc(ఖాళీ);
    ఒకవేళ (env) {
        env->ambient_illuminance = (AVRational){ 314, 10 };
        env->ambient_light_x     = (AVRational){ 15635, 50000 };
        env->ambient_light_y     = (AVRational){ 16450, 50000 };
        print_env(env);
        av_free(env);
    }

    /* av_ambient_viewing_environment_create_side_data */
    రాయి("\nTesting av_ambient_viewing_environment_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        env = av_ambient_viewing_environment_create_side_దత్తాంశం(చట్రం);
        ఒకవేళ (env) {
            రాయి("side_data: OK\n");
            print_env(env);
        } లేకపోతే {
            రాయి("side_data: FAIL\n");
        }
        av_చట్రం_free(&చట్రం);
    }

    /* OOM paths via av_max_alloc */
    రాయి("\nTesting OOM paths\n");
    av_max_alloc(1);
    env = av_ambient_viewing_environment_alloc(&కొలత);
    రాయి("alloc OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    env = av_ambient_viewing_environment_alloc(ఖాళీ);
    రాయి("alloc(NULL) OOM: %s\n", env ? "FAIL" : "OK");
    av_free(env);
    av_max_alloc(గరిష్ఠ_పూర్ణాంకం);

    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        av_max_alloc(1);
        env = av_ambient_viewing_environment_create_side_దత్తాంశం(చట్రం);
        రాయి("side_data OOM: %s\n", env ? "FAIL" : "OK");
        av_max_alloc(గరిష్ఠ_పూర్ణాంకం);
        av_చట్రం_free(&చట్రం);
    }

    తిరిగి 0;
}

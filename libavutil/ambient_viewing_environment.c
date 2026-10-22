/*
 * Copyright (c) 2023 Jan Ekström <jeebjp@gmail.com>
 *
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

#అన్తర్భావ "ambient_viewing_environment.h"
#అన్తర్భావ "mem.h"

స్థిర శూన్య get_defaults(AVAmbientViewingEnvironment *env)
{
    env->ambient_illuminance =
    env->ambient_light_x     =
    env->ambient_light_y     = (AVRational) { 0, 1 };
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_alloc(size_t *కొలత)
{
    AVAmbientViewingEnvironment *env =
        av_mallocz(పరిమాణం(AVAmbientViewingEnvironment));

    ఒకవేళ (కొలత)
        *కొలత = env ? పరిమాణం(*env) : 0;

    ఒకవేళ (!env)
        తిరిగి ఖాళీ;

    get_defaults(env);

    తిరిగి env;
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_create_side_దత్తాంశం(AVFrame *చట్రం)
{
    AVFrame_Side_దత్తాంశం *side_దత్తాంశం =
        av_చట్రం_new_side_దత్తాంశం(చట్రం,
                               AV_చట్రం_దత్తాంశం_AMBIENT_VIEWING_ENVIRONMENT,
                               పరిమాణం(AVAmbientViewingEnvironment));
    ఒకవేళ (!side_దత్తాంశం)
        తిరిగి ఖాళీ;

    memset(side_దత్తాంశం->దత్తాంశం, 0, side_దత్తాంశం->కొలత);
    get_defaults((AVAmbientViewingEnvironment *)side_దత్తాంశం->దత్తాంశం);

    తిరిగి (AVAmbientViewingEnvironment *)side_దత్తాంశం->దత్తాంశం;
}

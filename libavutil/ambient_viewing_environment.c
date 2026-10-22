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

#ضمن "ambient_viewing_environment.h"
#ضمن "mem.h"

ساكن فراغ get_defaults(AVAmbientViewingEnvironment *env)
{
    env->ambient_illuminance =
    env->ambient_light_x     =
    env->ambient_light_y     = (AVRational) { 0, 1 };
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_alloc(size_t *سائيز)
{
    AVAmbientViewingEnvironment *env =
        av_mallocz(حجم(AVAmbientViewingEnvironment));

    إذا (سائيز)
        *سائيز = env ? حجم(*env) : 0;

    إذا (!env)
        أرجع عدم;

    get_defaults(env);

    أرجع env;
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_create_side_معلومات(AVFrame *چوکٺو)
{
    AVFrame_Side_معلومات *side_معلومات =
        av_چوکٺو_new_side_معلومات(چوکٺو,
                               AV_چوکٺو_معلومات_AMBIENT_VIEWING_ENVIRONMENT,
                               حجم(AVAmbientViewingEnvironment));
    إذا (!side_معلومات)
        أرجع عدم;

    memset(side_معلومات->معلومات, 0, side_معلومات->سائيز);
    get_defaults((AVAmbientViewingEnvironment *)side_معلومات->معلومات);

    أرجع (AVAmbientViewingEnvironment *)side_معلومات->معلومات;
}

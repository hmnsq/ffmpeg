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

#شامل "ambient_viewing_environment.h"
#شامل "mem.h"

ساکن خالی get_defaults(AVAmbientViewingEnvironment *env)
{
    env->ambient_illuminance =
    env->ambient_light_x     =
    env->ambient_light_y     = (AVRational) { 0, 1 };
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_alloc(size_t *سائز)
{
    AVAmbientViewingEnvironment *env =
        av_mallocz(حجم(AVAmbientViewingEnvironment));

    اگر (سائز)
        *سائز = env ? حجم(*env) : 0;

    اگر (!env)
        واپس تہی;

    get_defaults(env);

    واپس env;
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_create_side_ڈیٹا(AVFrame *چوکھٹا)
{
    AVFrame_Side_ڈیٹا *side_ڈیٹا =
        av_چوکھٹا_new_side_ڈیٹا(چوکھٹا,
                               AV_چوکھٹا_ڈیٹا_AMBIENT_VIEWING_ENVIRONMENT,
                               حجم(AVAmbientViewingEnvironment));
    اگر (!side_ڈیٹا)
        واپس تہی;

    memset(side_ڈیٹا->ڈیٹا, 0, side_ڈیٹا->سائز);
    get_defaults((AVAmbientViewingEnvironment *)side_ڈیٹا->ڈیٹا);

    واپس (AVAmbientViewingEnvironment *)side_ڈیٹا->ڈیٹا;
}

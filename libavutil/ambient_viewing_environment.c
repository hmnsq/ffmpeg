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

#ਅਨ੍ਤਰ੍ਭਾਵ "ambient_viewing_environment.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

ਸਥਿਰ ਖਾਲੀ get_defaults(AVAmbientViewingEnvironment *env)
{
    env->ambient_illuminance =
    env->ambient_light_x     =
    env->ambient_light_y     = (AVRational) { 0, 1 };
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_alloc(size_t *ਮਾਪ)
{
    AVAmbientViewingEnvironment *env =
        av_mallocz(ਆਕਾਰ(AVAmbientViewingEnvironment));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = env ? ਆਕਾਰ(*env) : 0;

    ਜੇ (!env)
        ਵਾਪਸ ਨਿਰਾ;

    get_defaults(env);

    ਵਾਪਸ env;
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ =
        av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ,
                               AV_ਚੌਖਟਾ_ਅੰਕੜੇ_AMBIENT_VIEWING_ENVIRONMENT,
                               ਆਕਾਰ(AVAmbientViewingEnvironment));
    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    memset(side_ਅੰਕੜੇ->ਅੰਕੜੇ, 0, side_ਅੰਕੜੇ->ਮਾਪ);
    get_defaults((AVAmbientViewingEnvironment *)side_ਅੰਕੜੇ->ਅੰਕੜੇ);

    ਵਾਪਸ (AVAmbientViewingEnvironment *)side_ਅੰਕੜੇ->ਅੰਕੜੇ;
}

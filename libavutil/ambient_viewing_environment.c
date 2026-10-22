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

#அந்தர்பாவ "ambient_viewing_environment.h"
#அந்தர்பாவ "mem.h"

நிலையான வெறுமை get_defaults(AVAmbientViewingEnvironment *env)
{
    env->ambient_illuminance =
    env->ambient_light_x     =
    env->ambient_light_y     = (AVRational) { 0, 1 };
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_alloc(size_t *size)
{
    AVAmbientViewingEnvironment *env =
        av_mallocz(அளவு(AVAmbientViewingEnvironment));

    எனில் (size)
        *size = env ? அளவு(*env) : 0;

    எனில் (!env)
        திரும்பு வெற்று;

    get_defaults(env);

    திரும்பு env;
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data =
        av_frame_new_side_data(frame,
                               AV_FRAME_DATA_AMBIENT_VIEWING_ENVIRONMENT,
                               அளவு(AVAmbientViewingEnvironment));
    எனில் (!side_data)
        திரும்பு வெற்று;

    memset(side_data->data, 0, side_data->size);
    get_defaults((AVAmbientViewingEnvironment *)side_data->data);

    திரும்பு (AVAmbientViewingEnvironment *)side_data->data;
}

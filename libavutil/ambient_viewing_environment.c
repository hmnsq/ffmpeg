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

#अन्तर्भाव "ambient_viewing_environment.h"
#अन्तर्भाव "mem.h"

स्थिर शून्य get_defaults(AVAmbientViewingEnvironment *env)
{
    env->ambient_illuminance =
    env->ambient_light_x     =
    env->ambient_light_y     = (AVRational) { 0, 1 };
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_alloc(size_t *आकार)
{
    AVAmbientViewingEnvironment *env =
        av_mallocz(परिमाण(AVAmbientViewingEnvironment));

    यदि (आकार)
        *आकार = env ? परिमाण(*env) : 0;

    यदि (!env)
        प्रत्यागम रिक्त;

    get_defaults(env);

    प्रत्यागम env;
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_create_side_दत्त(AVFrame *frame)
{
    AVFrame_Side_दत्त *side_दत्त =
        av_frame_new_side_दत्त(frame,
                               AV_FRAME_दत्त_AMBIENT_VIEWING_ENVIRONMENT,
                               परिमाण(AVAmbientViewingEnvironment));
    यदि (!side_दत्त)
        प्रत्यागम रिक्त;

    स्मृतिं_पूरय(side_दत्त->दत्त, 0, side_दत्त->आकार);
    get_defaults((AVAmbientViewingEnvironment *)side_दत्त->दत्त);

    प्रत्यागम (AVAmbientViewingEnvironment *)side_दत्त->दत्त;
}

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

#समावेश "ambient_viewing_environment.h"
#समावेश "mem.h"

अटल व्योम get_defaults(AVAmbientViewingEnvironment *env)
{
    env->ambient_illuminance =
    env->ambient_light_x     =
    env->ambient_light_y     = (AVRational) { 0, 1 };
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_alloc(माप_प्रकार *आकार)
{
    AVAmbientViewingEnvironment *env =
        av_mallocz(माप(AVAmbientViewingEnvironment));

    अगर (आकार)
        *आकार = env ? माप(*env) : 0;

    अगर (!env)
        वापस शून्य;

    get_defaults(env);

    वापस env;
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_create_side_तथ्य(AVFrame *frame)
{
    AVFrame_Side_तथ्य *side_तथ्य =
        av_frame_new_side_तथ्य(frame,
                               AV_FRAME_तथ्य_AMBIENT_VIEWING_ENVIRONMENT,
                               माप(AVAmbientViewingEnvironment));
    अगर (!side_तथ्य)
        वापस शून्य;

    स_रखो(side_तथ्य->तथ्य, 0, side_तथ्य->आकार);
    get_defaults((AVAmbientViewingEnvironment *)side_तथ्य->तथ्य);

    वापस (AVAmbientViewingEnvironment *)side_तथ्य->तथ्य;
}

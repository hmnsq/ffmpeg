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

#অন্তর্ভাব "ambient_viewing_environment.h"
#অন্তর্ভাব "mem.h"

স্থির শূন্য get_defaults(AVAmbientViewingEnvironment *env)
{
    env->ambient_illuminance =
    env->ambient_light_x     =
    env->ambient_light_y     = (AVRational) { 0, 1 };
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_alloc(size_t *আকার_2)
{
    AVAmbientViewingEnvironment *env =
        av_mallocz(আকার(AVAmbientViewingEnvironment));

    যদি (আকার_2)
        *আকার_2 = env ? আকার(*env) : 0;

    যদি (!env)
        ফেরত ফাঁকা;

    get_defaults(env);

    ফেরত env;
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_create_side_তথ্য(AVFrame *frame)
{
    AVFrame_Side_তথ্য *side_তথ্য =
        av_frame_new_side_তথ্য(frame,
                               AV_FRAME_তথ্য_AMBIENT_VIEWING_ENVIRONMENT,
                               আকার(AVAmbientViewingEnvironment));
    যদি (!side_তথ্য)
        ফেরত ফাঁকা;

    memset(side_তথ্য->তথ্য, 0, side_তথ্য->আকার_2);
    get_defaults((AVAmbientViewingEnvironment *)side_তথ্য->তথ্য);

    ফেরত (AVAmbientViewingEnvironment *)side_তথ্য->তথ্য;
}

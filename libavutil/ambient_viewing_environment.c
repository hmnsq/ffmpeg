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

#ಅನ್ತರ್ಭಾವ "ambient_viewing_environment.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

ಸ್ಥಿರ ಶೂನ್ಯ get_defaults(AVAmbientViewingEnvironment *env)
{
    env->ambient_illuminance =
    env->ambient_light_x     =
    env->ambient_light_y     = (AVRational) { 0, 1 };
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_alloc(size_t *ಗಾತ್ರ_2)
{
    AVAmbientViewingEnvironment *env =
        av_mallocz(ಗಾತ್ರ(AVAmbientViewingEnvironment));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = env ? ಗಾತ್ರ(*env) : 0;

    ಆದರೆ (!env)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    get_defaults(env);

    ಹಿಂತಿರುಗಿ env;
}

AVAmbientViewingEnvironment *av_ambient_viewing_environment_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFrame_Side_ದತ್ತಾಂಶ *side_ದತ್ತಾಂಶ =
        av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು,
                               AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_AMBIENT_VIEWING_ENVIRONMENT,
                               ಗಾತ್ರ(AVAmbientViewingEnvironment));
    ಆದರೆ (!side_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    memset(side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ, 0, side_ದತ್ತಾಂಶ->ಗಾತ್ರ_2);
    get_defaults((AVAmbientViewingEnvironment *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ);

    ಹಿಂತಿರುಗಿ (AVAmbientViewingEnvironment *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ;
}

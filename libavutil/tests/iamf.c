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

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/iamf.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "libavutil/opt.h"

ಸ್ಥಿರ ಶೂನ್ಯ print_class_ವೃಕ್ಷ(ಧ್ರುವ AVClass *class, ಪೂರ್ಣಾಙ್ಕ depth)
{
    ಧ್ರುವ AVClass *child;
    ಶೂನ್ಯ *iter = ರಿಕ್ತ;

    printf("%*s%s\n", depth * 2, "", class->class_name);
    ಯದಿ (depth >= 8)
        ಪ್ರತ್ಯಾಗಮ;
    ಯಾವತ್ ((child = av_opt_child_class_iterate(class, &iter)))
        print_class_ವೃಕ್ಷ(child, depth + 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ find_option(ಧ್ರುವ AVClass *class, ಧ್ರುವ ವರ್ಣ *name)
{
    ಧ್ರುವ AVOption *o = av_opt_find2(&class, name, ರಿಕ್ತ, 0,
                                     AV_OPT_ಹುಡುಕು_CHILDREN | AV_OPT_ಹುಡುಕು_FAKE_OBJ,
                                     ರಿಕ್ತ);
    printf("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    ಧ್ರುವ AVClass *audio_element = av_iamf_audio_element_get_class();
    ಧ್ರುವ AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    ಧ್ರುವ AVClass *param_definition = av_iamf_param_definition_get_class();

    printf("Testing av_opt_child_class_iterate()\n");
    print_class_ವೃಕ್ಷ(audio_element, 0);
    print_class_ವೃಕ್ಷ(mix_presentation, 0);
    print_class_ವೃಕ್ಷ(param_definition, 0);

    printf("\nTesting av_opt_find2() with AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ\n");
    find_option(audio_element, "default_w");
    find_option(audio_element, "ch_layout");
    find_option(mix_presentation, "annotations");
    find_option(mix_presentation, "default_mix_gain");
    find_option(mix_presentation, "headphones_rendering_mode");
    find_option(mix_presentation, "sound_system");
    find_option(mix_presentation, "parameter_rate");
    find_option(param_definition, "parameter_rate");
    find_option(param_definition, "subblock_duration");

    ಪ್ರತ್ಯಾಗಮ 0;
}

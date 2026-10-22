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

ಸ್ಥಿರ ಶೂನ್ಯ print_class_ವೃಕ್ಷ(ಸ್ಥಿರಾಂಕ AVClass *class, ಪೂರ್ಣಾಂಕ ಆಳ)
{
    ಸ್ಥಿರಾಂಕ AVClass *ಮಗು;
    ಶೂನ್ಯ *iter = ಖಾಲಿ;

    ಬರೆ("%*s%s\n", ಆಳ * 2, "", class->class_name);
    ಆದರೆ (ಆಳ >= 8)
        ಹಿಂತಿರುಗಿ;
    ಆಗ ((ಮಗು = av_opt_ಮಗು_class_iterate(class, &iter)))
        print_class_ವೃಕ್ಷ(ಮಗು, ಆಳ + 1);
}

ಸ್ಥಿರ ಶೂನ್ಯ ಕಂಡುಹಿಡಿ_option(ಸ್ಥಿರಾಂಕ AVClass *class, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name)
{
    ಸ್ಥಿರಾಂಕ AVOption *o = av_opt_find2(&class, name, ಖಾಲಿ, 0,
                                     AV_OPT_ಹುಡುಕು_CHILDREN | AV_OPT_ಹುಡುಕು_FAKE_OBJ,
                                     ಖಾಲಿ);
    ಬರೆ("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಸ್ಥಿರಾಂಕ AVClass *audio_element = av_iamf_audio_element_get_class();
    ಸ್ಥಿರಾಂಕ AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    ಸ್ಥಿರಾಂಕ AVClass *param_definition = av_iamf_param_definition_get_class();

    ಬರೆ("Testing av_opt_child_class_iterate()\n");
    print_class_ವೃಕ್ಷ(audio_element, 0);
    print_class_ವೃಕ್ಷ(mix_presentation, 0);
    print_class_ವೃಕ್ಷ(param_definition, 0);

    ಬರೆ("\nTesting av_opt_find2() with AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ\n");
    ಕಂಡುಹಿಡಿ_option(audio_element, "default_w");
    ಕಂಡುಹಿಡಿ_option(audio_element, "ch_layout");
    ಕಂಡುಹಿಡಿ_option(mix_presentation, "annotations");
    ಕಂಡುಹಿಡಿ_option(mix_presentation, "default_mix_gain");
    ಕಂಡುಹಿಡಿ_option(mix_presentation, "headphones_rendering_mode");
    ಕಂಡುಹಿಡಿ_option(mix_presentation, "sound_system");
    ಕಂಡುಹಿಡಿ_option(mix_presentation, "parameter_rate");
    ಕಂಡುಹಿಡಿ_option(param_definition, "parameter_rate");
    ಕಂಡುಹಿಡಿ_option(param_definition, "subblock_duration");

    ಹಿಂತಿರುಗಿ 0;
}

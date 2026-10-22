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

#അന്തര്ഭാവ <stdio.h>

#അന്തര്ഭാവ "libavutil/iamf.h"
#അന്തര്ഭാവ "libavutil/log.h"
#അന്തര്ഭാവ "libavutil/opt.h"

സ്ഥിതം ശൂന്യം print_class_വൃക്ഷം(സ്ഥിരം AVClass *class, പൂർണ്ണസംഖ്യ depth)
{
    സ്ഥിരം AVClass *child;
    ശൂന്യം *iter = ശൂന്യ;

    printf("%*s%s\n", depth * 2, "", class->class_name);
    എങ്കിൽ (depth >= 8)
        തിരികെ;
    ആകുമ്പോൾ ((child = av_opt_child_class_iterate(class, &iter)))
        print_class_വൃക്ഷം(child, depth + 1);
}

സ്ഥിതം ശൂന്യം find_option(സ്ഥിരം AVClass *class, സ്ഥിരം അക്ഷരം *name)
{
    സ്ഥിരം AVOption *o = av_opt_find2(&class, name, ശൂന്യ, 0,
                                     AV_OPT_തിരയൽ_CHILDREN | AV_OPT_തിരയൽ_FAKE_OBJ,
                                     ശൂന്യ);
    printf("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    സ്ഥിരം AVClass *audio_element = av_iamf_audio_element_get_class();
    സ്ഥിരം AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    സ്ഥിരം AVClass *param_definition = av_iamf_param_definition_get_class();

    printf("Testing av_opt_child_class_iterate()\n");
    print_class_വൃക്ഷം(audio_element, 0);
    print_class_വൃക്ഷം(mix_presentation, 0);
    print_class_വൃക്ഷം(param_definition, 0);

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

    തിരികെ 0;
}

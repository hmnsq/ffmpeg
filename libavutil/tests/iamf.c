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

#ଅନ୍ତର୍ଭାଵ <stdio.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/iamf.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/log.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/opt.h"

ସ୍ଥିର ଶୂନ୍ୟ print_class_ବୃକ୍ଷ(ଅଚଳ AVClass *class, ପୂର୍ଣ୍ଣସଂଖ୍ୟା depth)
{
    ଅଚଳ AVClass *child;
    ଶୂନ୍ୟ *iter = ଖାଲି;

    printf("%*s%s\n", depth * 2, "", class->class_name);
    ଯଦି (depth >= 8)
        ଫେରନ୍ତୁ;
    ଯେତେବେଳେ ((child = av_opt_child_class_iterate(class, &iter)))
        print_class_ବୃକ୍ଷ(child, depth + 1);
}

ସ୍ଥିର ଶୂନ୍ୟ find_option(ଅଚଳ AVClass *class, ଅଚଳ ଅକ୍ଷର *name)
{
    ଅଚଳ AVOption *o = av_opt_find2(&class, name, ଖାଲି, 0,
                                     AV_OPT_ସନ୍ଧାନ_CHILDREN | AV_OPT_ସନ୍ଧାନ_FAKE_OBJ,
                                     ଖାଲି);
    printf("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    ଅଚଳ AVClass *audio_element = av_iamf_audio_element_get_class();
    ଅଚଳ AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    ଅଚଳ AVClass *param_definition = av_iamf_param_definition_get_class();

    printf("Testing av_opt_child_class_iterate()\n");
    print_class_ବୃକ୍ଷ(audio_element, 0);
    print_class_ବୃକ୍ଷ(mix_presentation, 0);
    print_class_ବୃକ୍ଷ(param_definition, 0);

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

    ଫେରନ୍ତୁ 0;
}

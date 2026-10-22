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

#ضمن <stdio.h>

#ضمن "libavutil/iamf.h"
#ضمن "libavutil/log.h"
#ضمن "libavutil/opt.h"

ساكن فراغ print_class_tree(ثابت AVClass *class, صحيح depth)
{
    ثابت AVClass *child;
    فراغ *iter = عدم;

    printf("%*s%s\n", depth * 2, "", class->class_name);
    אם (depth >= 8)
        החזר;
    כלעוד ((child = av_opt_child_class_iterate(class, &iter)))
        print_class_tree(child, depth + 1);
}

ساكن فراغ find_option(ثابت AVClass *class, ثابت حرف *name)
{
    ثابت AVOption *o = av_opt_find2(&class, name, عدم, 0,
                                     AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ,
                                     عدم);
    printf("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

صحيح main(فراغ)
{
    ثابت AVClass *audio_element = av_iamf_audio_element_get_class();
    ثابت AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    ثابت AVClass *param_definition = av_iamf_param_definition_get_class();

    printf("Testing av_opt_child_class_iterate()\n");
    print_class_tree(audio_element, 0);
    print_class_tree(mix_presentation, 0);
    print_class_tree(param_definition, 0);

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

    החזר 0;
}

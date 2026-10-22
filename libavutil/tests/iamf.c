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

#समावेश <stdio.h>

#समावेश "libavutil/iamf.h"
#समावेश "libavutil/log.h"
#समावेश "libavutil/opt.h"

अटल व्योम print_class_वृक्ष(स्थिर AVClass *class, पूर्णांक depth)
{
    स्थिर AVClass *child;
    व्योम *iter = शून्य;

    म_लिखो("%*s%s\n", depth * 2, "", class->class_name);
    अगर (depth >= 8)
        वापस;
    जबतक ((child = av_opt_child_class_iterate(class, &iter)))
        print_class_वृक्ष(child, depth + 1);
}

अटल व्योम find_option(स्थिर AVClass *class, स्थिर अक्षर *name)
{
    स्थिर AVOption *o = av_opt_find2(&class, name, शून्य, 0,
                                     AV_OPT_खोज_CHILDREN | AV_OPT_खोज_FAKE_OBJ,
                                     शून्य);
    म_लिखो("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

पूर्णांक मुख्य(व्योम)
{
    स्थिर AVClass *audio_element = av_iamf_audio_element_get_class();
    स्थिर AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    स्थिर AVClass *param_definition = av_iamf_param_definition_get_class();

    म_लिखो("Testing av_opt_child_class_iterate()\n");
    print_class_वृक्ष(audio_element, 0);
    print_class_वृक्ष(mix_presentation, 0);
    print_class_वृक्ष(param_definition, 0);

    म_लिखो("\nTesting av_opt_find2() with AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ\n");
    find_option(audio_element, "default_w");
    find_option(audio_element, "ch_layout");
    find_option(mix_presentation, "annotations");
    find_option(mix_presentation, "default_mix_gain");
    find_option(mix_presentation, "headphones_rendering_mode");
    find_option(mix_presentation, "sound_system");
    find_option(mix_presentation, "parameter_rate");
    find_option(param_definition, "parameter_rate");
    find_option(param_definition, "subblock_duration");

    वापस 0;
}

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

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/iamf.h"
#अन्तर्भाव "libavutil/log.h"
#अन्तर्भाव "libavutil/opt.h"

स्थिर शून्य print_class_वृक्ष(स्थिरांक AVClass *class, पूर्णांक depth)
{
    स्थिरांक AVClass *child;
    शून्य *iter = रिक्त;

    म_लिखो("%*s%s\n", depth * 2, "", class->class_name);
    जर (depth >= 8)
        परत;
    पर्यंत ((child = av_opt_child_class_iterate(class, &iter)))
        print_class_वृक्ष(child, depth + 1);
}

स्थिर शून्य find_option(स्थिरांक AVClass *class, स्थिरांक अक्षर *name)
{
    स्थिरांक AVOption *o = av_opt_find2(&class, name, रिक्त, 0,
                                     AV_OPT_शोध_CHILDREN | AV_OPT_शोध_FAKE_OBJ,
                                     रिक्त);
    म_लिखो("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

पूर्णांक main(शून्य)
{
    स्थिरांक AVClass *audio_element = av_iamf_audio_element_get_class();
    स्थिरांक AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    स्थिरांक AVClass *param_definition = av_iamf_param_definition_get_class();

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

    परत 0;
}

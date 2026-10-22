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

स्थिर शून्य print_class_वृक्षः(ध्रुव AVClass *class, पूर्णाङ्क गभीरता)
{
    ध्रुव AVClass *child;
    शून्य *iter = रिक्त;

    प्रारूप_लिख("%*s%s\n", गभीरता * 2, "", class->class_name);
    यदि (गभीरता >= 8)
        प्रत्यागम;
    यावत् ((child = av_opt_child_class_iterate(class, &iter)))
        print_class_वृक्षः(child, गभीरता + 1);
}

स्थिर शून्य find_option(ध्रुव AVClass *class, ध्रुव वर्ण *name)
{
    ध्रुव AVOption *o = av_opt_find2(&class, name, रिक्त, 0,
                                     AV_OPT_अन्वेषणम्_CHILDREN | AV_OPT_अन्वेषणम्_FAKE_OBJ,
                                     रिक्त);
    प्रारूप_लिख("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    ध्रुव AVClass *audio_element = av_iamf_audio_element_get_class();
    ध्रुव AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    ध्रुव AVClass *param_definition = av_iamf_param_definition_get_class();

    प्रारूप_लिख("Testing av_opt_child_class_iterate()\n");
    print_class_वृक्षः(audio_element, 0);
    print_class_वृक्षः(mix_presentation, 0);
    print_class_वृक्षः(param_definition, 0);

    प्रारूप_लिख("\nTesting av_opt_find2() with AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ\n");
    find_option(audio_element, "default_w");
    find_option(audio_element, "ch_layout");
    find_option(mix_presentation, "annotations");
    find_option(mix_presentation, "default_mix_gain");
    find_option(mix_presentation, "headphones_rendering_mode");
    find_option(mix_presentation, "sound_system");
    find_option(mix_presentation, "parameter_rate");
    find_option(param_definition, "parameter_rate");
    find_option(param_definition, "subblock_duration");

    प्रत्यागम 0;
}

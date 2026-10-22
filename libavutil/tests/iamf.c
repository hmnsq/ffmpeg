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

ساكن فراغ print_class_ونه(ثابت AVClass *class, صحيح ژوروالی)
{
    ثابت AVClass *ماشوم;
    فراغ *iter = عدم;

    چاپ_کړه("%*s%s\n", ژوروالی * 2, "", class->class_name);
    إذا (ژوروالی >= 8)
        أرجع;
    طالما ((ماشوم = av_opt_ماشوم_class_iterate(class, &iter)))
        print_class_ونه(ماشوم, ژوروالی + 1);
}

ساكن فراغ پیدا_کړه_option(ثابت AVClass *class, ثابت حرف *name)
{
    ثابت AVOption *o = av_opt_find2(&class, name, عدم, 0,
                                     AV_OPT_پلټنه_CHILDREN | AV_OPT_پلټنه_FAKE_OBJ,
                                     عدم);
    چاپ_کړه("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

صحيح اصلي(فراغ)
{
    ثابت AVClass *audio_element = av_iamf_audio_element_get_class();
    ثابت AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    ثابت AVClass *param_definition = av_iamf_param_definition_get_class();

    چاپ_کړه("Testing av_opt_child_class_iterate()\n");
    print_class_ونه(audio_element, 0);
    print_class_ونه(mix_presentation, 0);
    print_class_ونه(param_definition, 0);

    چاپ_کړه("\nTesting av_opt_find2() with AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ\n");
    پیدا_کړه_option(audio_element, "default_w");
    پیدا_کړه_option(audio_element, "ch_layout");
    پیدا_کړه_option(mix_presentation, "annotations");
    پیدا_کړه_option(mix_presentation, "default_mix_gain");
    پیدا_کړه_option(mix_presentation, "headphones_rendering_mode");
    پیدا_کړه_option(mix_presentation, "sound_system");
    پیدا_کړه_option(mix_presentation, "parameter_rate");
    پیدا_کړه_option(param_definition, "parameter_rate");
    پیدا_کړه_option(param_definition, "subblock_duration");

    أرجع 0;
}

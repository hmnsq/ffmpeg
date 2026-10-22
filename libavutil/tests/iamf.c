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

#شامل <stdio.h>

#شامل "libavutil/iamf.h"
#شامل "libavutil/log.h"
#شامل "libavutil/opt.h"

ساکن خالی print_class_درخت(ثابت AVClass *class, صحیح گہرائی)
{
    ثابت AVClass *بچہ;
    خالی *iter = تہی;

    لکھو("%*s%s\n", گہرائی * 2, "", class->class_name);
    اگر (گہرائی >= 8)
        واپس;
    جب ((بچہ = av_opt_بچہ_class_iterate(class, &iter)))
        print_class_درخت(بچہ, گہرائی + 1);
}

ساکن خالی ڈھونڈو_option(ثابت AVClass *class, ثابت حرف *name)
{
    ثابت AVOption *o = av_opt_find2(&class, name, تہی, 0,
                                     AV_OPT_تلاش_CHILDREN | AV_OPT_تلاش_FAKE_OBJ,
                                     تہی);
    لکھو("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

صحیح مین(خالی)
{
    ثابت AVClass *audio_element = av_iamf_audio_element_get_class();
    ثابت AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    ثابت AVClass *param_definition = av_iamf_param_definition_get_class();

    لکھو("Testing av_opt_child_class_iterate()\n");
    print_class_درخت(audio_element, 0);
    print_class_درخت(mix_presentation, 0);
    print_class_درخت(param_definition, 0);

    لکھو("\nTesting av_opt_find2() with AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ\n");
    ڈھونڈو_option(audio_element, "default_w");
    ڈھونڈو_option(audio_element, "ch_layout");
    ڈھونڈو_option(mix_presentation, "annotations");
    ڈھونڈو_option(mix_presentation, "default_mix_gain");
    ڈھونڈو_option(mix_presentation, "headphones_rendering_mode");
    ڈھونڈو_option(mix_presentation, "sound_system");
    ڈھونڈو_option(mix_presentation, "parameter_rate");
    ڈھونڈو_option(param_definition, "parameter_rate");
    ڈھونڈو_option(param_definition, "subblock_duration");

    واپس 0;
}

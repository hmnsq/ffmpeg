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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/iamf.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/opt.h"

ਸਥਿਰ ਖਾਲੀ print_class_ਰੁੱਖ(ਅਚਲ AVClass *class, ਪੂਰਨ ਡੂੰਘਾਈ)
{
    ਅਚਲ AVClass *ਬੱਚਾ;
    ਖਾਲੀ *iter = ਨਿਰਾ;

    ਲਿਖੋ("%*s%s\n", ਡੂੰਘਾਈ * 2, "", class->class_name);
    ਜੇ (ਡੂੰਘਾਈ >= 8)
        ਵਾਪਸ;
    ਜਦੋਂ ((ਬੱਚਾ = av_opt_ਬੱਚਾ_class_iterate(class, &iter)))
        print_class_ਰੁੱਖ(ਬੱਚਾ, ਡੂੰਘਾਈ + 1);
}

ਸਥਿਰ ਖਾਲੀ ਲੱਭੋ_option(ਅਚਲ AVClass *class, ਅਚਲ ਅੱਖਰ *name)
{
    ਅਚਲ AVOption *o = av_opt_find2(&class, name, ਨਿਰਾ, 0,
                                     AV_OPT_ਖੋਜ_CHILDREN | AV_OPT_ਖੋਜ_FAKE_OBJ,
                                     ਨਿਰਾ);
    ਲਿਖੋ("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਅਚਲ AVClass *audio_element = av_iamf_audio_element_get_class();
    ਅਚਲ AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    ਅਚਲ AVClass *param_definition = av_iamf_param_definition_get_class();

    ਲਿਖੋ("Testing av_opt_child_class_iterate()\n");
    print_class_ਰੁੱਖ(audio_element, 0);
    print_class_ਰੁੱਖ(mix_presentation, 0);
    print_class_ਰੁੱਖ(param_definition, 0);

    ਲਿਖੋ("\nTesting av_opt_find2() with AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ\n");
    ਲੱਭੋ_option(audio_element, "default_w");
    ਲੱਭੋ_option(audio_element, "ch_layout");
    ਲੱਭੋ_option(mix_presentation, "annotations");
    ਲੱਭੋ_option(mix_presentation, "default_mix_gain");
    ਲੱਭੋ_option(mix_presentation, "headphones_rendering_mode");
    ਲੱਭੋ_option(mix_presentation, "sound_system");
    ਲੱਭੋ_option(mix_presentation, "parameter_rate");
    ਲੱਭੋ_option(param_definition, "parameter_rate");
    ਲੱਭੋ_option(param_definition, "subblock_duration");

    ਵਾਪਸ 0;
}

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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/iamf.h"
#అన్తర్భావ "libavutil/log.h"
#అన్తర్భావ "libavutil/opt.h"

స్థిర శూన్య print_class_వృక్షం(స్థిరరాశి AVClass *class, పూర్ణాంకం లోతు)
{
    స్థిరరాశి AVClass *బిడ్డ;
    శూన్య *iter = ఖాళీ;

    రాయి("%*s%s\n", లోతు * 2, "", class->class_name);
    ఒకవేళ (లోతు >= 8)
        తిరిగి;
    అయితే ((బిడ్డ = av_opt_బిడ్డ_class_iterate(class, &iter)))
        print_class_వృక్షం(బిడ్డ, లోతు + 1);
}

స్థిర శూన్య కనుగొను_option(స్థిరరాశి AVClass *class, స్థిరరాశి అక్షరం *name)
{
    స్థిరరాశి AVOption *o = av_opt_find2(&class, name, ఖాళీ, 0,
                                     AV_OPT_శోధన_CHILDREN | AV_OPT_శోధన_FAKE_OBJ,
                                     ఖాళీ);
    రాయి("%s: %s %s\n", class->class_name, name, o ? "found" : "not found");
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    స్థిరరాశి AVClass *audio_element = av_iamf_audio_element_get_class();
    స్థిరరాశి AVClass *mix_presentation = av_iamf_mix_presentation_get_class();
    స్థిరరాశి AVClass *param_definition = av_iamf_param_definition_get_class();

    రాయి("Testing av_opt_child_class_iterate()\n");
    print_class_వృక్షం(audio_element, 0);
    print_class_వృక్షం(mix_presentation, 0);
    print_class_వృక్షం(param_definition, 0);

    రాయి("\nTesting av_opt_find2() with AV_OPT_SEARCH_CHILDREN | AV_OPT_SEARCH_FAKE_OBJ\n");
    కనుగొను_option(audio_element, "default_w");
    కనుగొను_option(audio_element, "ch_layout");
    కనుగొను_option(mix_presentation, "annotations");
    కనుగొను_option(mix_presentation, "default_mix_gain");
    కనుగొను_option(mix_presentation, "headphones_rendering_mode");
    కనుగొను_option(mix_presentation, "sound_system");
    కనుగొను_option(mix_presentation, "parameter_rate");
    కనుగొను_option(param_definition, "parameter_rate");
    కనుగొను_option(param_definition, "subblock_duration");

    తిరిగి 0;
}

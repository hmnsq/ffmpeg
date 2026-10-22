/*
 * Immersive Audio Model and Formats helper functions and defines
 *
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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "iamf.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "opt.h"

#నిర్వచించు IAMF_కూడు_FUNC_TEMPLATE(మాతృ_type, మాతృ_name, బిడ్డ_type, బిడ్డ_name, suffix)                   \
బిడ్డ_type *av_iamf_ ## మాతృ_name ## కూడు ## బిడ్డ_name(మాతృ_type *మాతృ_name)                       \
{                                                                                                          \
    బిడ్డ_type **బిడ్డ_name ## suffix, *బిడ్డ_name;                                                        \
                                                                                                           \
    ఒకవేళ (మాతృ_name->nb_## బిడ్డ_name ## suffix == UINT_MAX)                                               \
        తిరిగి ఖాళీ;                                                                                       \
                                                                                                           \
    బిడ్డ_name ## suffix = av_realloc_array(మాతృ_name->బిడ్డ_name ## suffix,                             \
                                            మాతృ_name->nb_## బిడ్డ_name ## suffix + 1,                   \
                                            పరిమాణం(*మాతృ_name->బిడ్డ_name ## suffix));                   \
    ఒకవేళ (!బిడ్డ_name ## suffix)                                                                             \
        తిరిగి ఖాళీ;                                                                                       \
                                                                                                           \
    మాతృ_name->బిడ్డ_name ## suffix = బిడ్డ_name ## suffix;                                              \
                                                                                                           \
    బిడ్డ_name = మాతృ_name->బిడ్డ_name ## suffix[మాతృ_name->nb_## బిడ్డ_name ## suffix]                \
               = av_mallocz(పరిమాణం(*బిడ్డ_name));                                                          \
    ఒకవేళ (!బిడ్డ_name)                                                                                       \
        తిరిగి ఖాళీ;                                                                                       \
                                                                                                           \
    బిడ్డ_name->av_class = &బిడ్డ_name ## _class;                                                          \
    av_opt_సమితి_defaults(బిడ్డ_name);                                                                       \
    మాతృ_name->nb_## బిడ్డ_name ## suffix++;                                                             \
                                                                                                           \
    తిరిగి బిడ్డ_name;                                                                                     \
}

#నిర్వచించు FLAGS AV_OPT_FLAG_ENCODING_PARAM

//
// Param Definition
//
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFMixGain, x)
స్థిర స్థిరరాశి AVOption mix_gain_options[] = {
    { "subblock_duration", "set subblock_duration", స్థానభ్రంశం_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "animation_type", "set animation_type", స్థానభ్రంశం_2(animation_type), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 2, FLAGS },
    { "start_point_value", "set start_point_value", స్థానభ్రంశం_2(ప్రారంభం_బిందువు_విలువ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "end_point_value", "set end_point_value", స్థానభ్రంశం_2(చివర_బిందువు_విలువ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_value", "set control_point_value", స్థానభ్రంశం_2(control_బిందువు_విలువ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_relative_time", "set control_point_relative_time", స్థానభ్రంశం_2(control_బిందువు_relative_సమయం), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, 0.0, 1.0, FLAGS },
    { ఖాళీ },
};

స్థిర స్థిరరాశి AVClass mix_gain_class = {
    .class_name     = "AVIAMFMixGain",
    .అంశం_name      = av_default_అంశం_name,
    .సంస్కరణ        = LIBAVUTIL_సంస్కరణ_INT,
    .option         = mix_gain_options,
};

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFDemixingInfo, x)
స్థిర స్థిరరాశి AVOption demixing_info_options[] = {
    { "subblock_duration", "set subblock_duration", స్థానభ్రంశం_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "dmixp_mode", "set dmixp_mode", స్థానభ్రంశం_2(dmixp_బహుళకం), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 6, FLAGS },
    { ఖాళీ },
};

స్థిర స్థిరరాశి AVClass demixing_info_class = {
    .class_name     = "AVIAMFDemixingInfo",
    .అంశం_name      = av_default_అంశం_name,
    .సంస్కరణ        = LIBAVUTIL_సంస్కరణ_INT,
    .option         = demixing_info_options,
};

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFReconGain, x)
స్థిర స్థిరరాశి AVOption recon_gain_options[] = {
    { "subblock_duration", "set subblock_duration", స్థానభ్రంశం_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { ఖాళీ },
};

స్థిర స్థిరరాశి AVClass recon_gain_class = {
    .class_name     = "AVIAMFReconGain",
    .అంశం_name      = av_default_అంశం_name,
    .సంస్కరణ        = LIBAVUTIL_సంస్కరణ_INT,
    .option         = recon_gain_options,
};

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFParamDefinition, x)
స్థిర స్థిరరాశి AVOption param_definition_options[] = {
    { "parameter_id", "set parameter_id", స్థానభ్రంశం_2(parameter_id), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "parameter_rate", "set parameter_rate", స్థానభ్రంశం_2(parameter_రేటు), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "duration", "set duration", స్థానభ్రంశం_2(duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "constant_subblock_duration", "set constant_subblock_duration", స్థానభ్రంశం_2(constant_subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { ఖాళీ },
};

స్థిర స్థిరరాశి AVClass *param_definition_బిడ్డ_iterate(శూన్య **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    స్థిరరాశి AVClass *ret = ఖాళీ;

    ఎంపిక(i) {
    స్థితి AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        ret = &mix_gain_class;
        ఆపు;
    స్థితి AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        ret = &demixing_info_class;
        ఆపు;
    స్థితి AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        ret = &recon_gain_class;
        ఆపు;
    అప్రమేయ:
        ఆపు;
    }

    ఒకవేళ (ret)
        *opaque = (శూన్య*)(i + 1);
    తిరిగి ret;
}

స్థిర స్థిరరాశి AVClass param_definition_class = {
    .class_name          = "AVIAMFParamDefinition",
    .అంశం_name           = av_default_అంశం_name,
    .సంస్కరణ             = LIBAVUTIL_సంస్కరణ_INT,
    .option              = param_definition_options,
    .బిడ్డ_class_iterate = param_definition_బిడ్డ_iterate,
};

స్థిరరాశి AVClass *av_iamf_param_definition_get_class(శూన్య)
{
    తిరిగి &param_definition_class;
}

AVIAMFParamDefinition *av_iamf_param_definition_alloc(గణన AVIAMFParamDefinitionType type,
                                                      గుర్తులేని పూర్ణాంకం nb_subblocks, size_t *బహిర్గతం_కొలత)
{

    నిర్మాణం MixGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFMixGain m;
    };
    నిర్మాణం DemixStruct {
        AVIAMFParamDefinition p;
        AVIAMFDemixingInfo d;
    };
    నిర్మాణం ReconGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFReconGain r;
    };
    size_t subblocks_స్థానభ్రంశం, subblock_కొలత;
    size_t కొలత;
    AVIAMFParamDefinition *par;

    ఎంపిక (type) {
    స్థితి AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        subblocks_స్థానభ్రంశం = offsetof(నిర్మాణం MixGainStruct, m);
        subblock_కొలత = పరిమాణం(AVIAMFMixGain);
        ఆపు;
    స్థితి AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        subblocks_స్థానభ్రంశం = offsetof(నిర్మాణం DemixStruct, d);
        subblock_కొలత = పరిమాణం(AVIAMFDemixingInfo);
        ఆపు;
    స్థితి AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        subblocks_స్థానభ్రంశం = offsetof(నిర్మాణం ReconGainStruct, r);
        subblock_కొలత = పరిమాణం(AVIAMFReconGain);
        ఆపు;
    అప్రమేయ:
        తిరిగి ఖాళీ;
    }

    కొలత = subblocks_స్థానభ్రంశం;
    ఒకవేళ (nb_subblocks > (SIZE_MAX - కొలత) / subblock_కొలత)
        తిరిగి ఖాళీ;
    కొలత += subblock_కొలత * nb_subblocks;

    par = av_mallocz(కొలత);
    ఒకవేళ (!par)
        తిరిగి ఖాళీ;

    par->av_class = &param_definition_class;
    av_opt_సమితి_defaults(par);

    par->type = type;
    par->nb_subblocks = nb_subblocks;
    par->subblock_కొలత = subblock_కొలత;
    par->subblocks_స్థానభ్రంశం = subblocks_స్థానభ్రంశం;

    కొరకు (పూర్ణాంకం i = 0; i < nb_subblocks; i++) {
        శూన్య *subblock = av_iamf_param_definition_get_subblock(par, i);

        ఎంపిక (type) {
        స్థితి AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
            ((AVIAMFMixGain *)subblock)->av_class = &mix_gain_class;
            ఆపు;
        స్థితి AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
            ((AVIAMFDemixingInfo *)subblock)->av_class = &demixing_info_class;
            ఆపు;
        స్థితి AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
            ((AVIAMFReconGain *)subblock)->av_class = &recon_gain_class;
            ఆపు;
        అప్రమేయ:
            av_assert0(0);
        }
    }

    ఒకవేళ (బహిర్గతం_కొలత)
        *బహిర్గతం_కొలత = కొలత;

    తిరిగి par;
}

//
// Audio Element
//
స్థిర స్థిరరాశి AVOptionArrayDef demixing_మాతృక_def = { .కొలత_max = (255 + 255) * 255, .sep = '|' };

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFLayer, x)
స్థిర స్థిరరాశి AVOption layer_options[] = {
    { "ch_layout", "set ch_layout", స్థానభ్రంశం_2(ch_layout), AV_OPT_TYPE_CHLAYOUT, {.str = ఖాళీ }, 0, 0, FLAGS },
    { "flags", "set flags", స్థానభ్రంశం_2(flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, AV_IAMF_LAYER_FLAG_RECON_GAIN, FLAGS, .unit = "flags" },
            {"recon_gain",  "Recon gain is present", 0, AV_OPT_TYPE_CONST,
                {.i64 = AV_IAMF_LAYER_FLAG_RECON_GAIN }, INT_MIN, గరిష్ఠ_పూర్ణాంకం, FLAGS, .unit = "flags"},
    { "output_gain_flags", "set output_gain_flags", స్థానభ్రంశం_2(output_gain_flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, (1 << 6) - 1, FLAGS, .unit = "output_gain_flags" },
            {"FL",  "Left channel",            0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 5 }, INT_MIN, గరిష్ఠ_పూర్ణాంకం, FLAGS, .unit = "output_gain_flags"},
            {"FR",  "Right channel",           0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 4 }, INT_MIN, గరిష్ఠ_పూర్ణాంకం, FLAGS, .unit = "output_gain_flags"},
            {"BL",  "Left surround channel",   0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 3 }, INT_MIN, గరిష్ఠ_పూర్ణాంకం, FLAGS, .unit = "output_gain_flags"},
            {"BR",  "Right surround channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 2 }, INT_MIN, గరిష్ఠ_పూర్ణాంకం, FLAGS, .unit = "output_gain_flags"},
            {"TFL", "Left top front channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 1 }, INT_MIN, గరిష్ఠ_పూర్ణాంకం, FLAGS, .unit = "output_gain_flags"},
            {"TFR", "Right top front channel", 0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 0 }, INT_MIN, గరిష్ఠ_పూర్ణాంకం, FLAGS, .unit = "output_gain_flags"},
    { "output_gain", "set output_gain", స్థానభ్రంశం_2(output_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "ambisonics_mode", "set ambisonics_mode", స్థానభ్రంశం_2(ambisonics_బహుళకం), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_AMBISONICS_బహుళకం_MONO },
            AV_IAMF_AMBISONICS_బహుళకం_MONO, AV_IAMF_AMBISONICS_బహుళకం_PROJECTION, FLAGS, .unit = "ambisonics_mode" },
        { "mono",       ఖాళీ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_బహుళకం_MONO },       .unit = "ambisonics_mode" },
        { "projection", ఖాళీ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_బహుళకం_PROJECTION }, .unit = "ambisonics_mode" },
    { "demixing_matrix", "set demixing_matrix", స్థానభ్రంశం_2(demixing_మాతృక), AV_OPT_TYPE_RATIONAL | AV_OPT_TYPE_FLAG_ARRAY,
            { .arr = &demixing_మాతృక_def }, -1.0, 1.0, FLAGS },
    { ఖాళీ },
};

స్థిర స్థిరరాశి AVClass layer_class = {
    .class_name     = "AVIAMFLayer",
    .అంశం_name      = av_default_అంశం_name,
    .సంస్కరణ        = LIBAVUTIL_సంస్కరణ_INT,
    .option         = layer_options,
};

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFAudioElement, x)
స్థిర స్థిరరాశి AVOption audio_element_options[] = {
    { "audio_element_type", "set audio_element_type", స్థానభ్రంశం_2(audio_element_type), AV_OPT_TYPE_INT,
            {.i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL },
            AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, FLAGS, .unit = "audio_element_type" },
        { "channel", ఖాళీ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL }, .unit = "audio_element_type" },
        { "scene",   ఖాళీ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE },   .unit = "audio_element_type" },
    { "default_w", "set default_w", స్థానభ్రంశం_2(default_w), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 10, FLAGS },
    { ఖాళీ },
};

స్థిర స్థిరరాశి AVClass *audio_element_బిడ్డ_iterate(శూన్య **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    స్థిరరాశి AVClass *ret = ఖాళీ;

    ఒకవేళ (!i)
        ret = &layer_class;

    ఒకవేళ (ret)
        *opaque = (శూన్య*)(i + 1);
    తిరిగి ret;
}

స్థిర స్థిరరాశి AVClass audio_element_class = {
    .class_name          = "AVIAMFAudioElement",
    .అంశం_name           = av_default_అంశం_name,
    .సంస్కరణ             = LIBAVUTIL_సంస్కరణ_INT,
    .option              = audio_element_options,
    .బిడ్డ_class_iterate = audio_element_బిడ్డ_iterate,
};

స్థిరరాశి AVClass *av_iamf_audio_element_get_class(శూన్య)
{
    తిరిగి &audio_element_class;
}

AVIAMFAudioElement *av_iamf_audio_element_alloc(శూన్య)
{
    AVIAMFAudioElement *audio_element = av_mallocz(పరిమాణం(*audio_element));

    ఒకవేళ (audio_element) {
        audio_element->av_class = &audio_element_class;
        av_opt_సమితి_defaults(audio_element);
    }

    తిరిగి audio_element;
}

IAMF_కూడు_FUNC_TEMPLATE(AVIAMFAudioElement, audio_element, AVIAMFLayer, layer, s)

శూన్య av_iamf_audio_element_free(AVIAMFAudioElement **paudio_element)
{
    AVIAMFAudioElement *audio_element = *paudio_element;

    ఒకవేళ (!audio_element)
        తిరిగి;

    కొరకు (పూర్ణాంకం i = 0; i < audio_element->nb_layers; i++) {
        AVIAMFLayer *layer = audio_element->layers[i];
        av_opt_free(layer);
        av_free(layer->demixing_మాతృక);
        av_free(layer);
    }
    av_free(audio_element->layers);

    av_free(audio_element->demixing_info);
    av_free(audio_element->recon_gain_info);
    av_freep(paudio_element);
}

//
// Mix Presentation
//
#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFSubmixElement, x)
స్థిర స్థిరరాశి AVOption submix_element_options[] = {
    { "headphones_rendering_mode", "Headphones rendering mode", స్థానభ్రంశం_2(headphones_rendering_బహుళకం), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_HEADPHONES_బహుళకం_STEREO },
            AV_IAMF_HEADPHONES_బహుళకం_STEREO, AV_IAMF_HEADPHONES_బహుళకం_BINAURAL, FLAGS, .unit = "headphones_rendering_mode" },
        { "stereo",   ఖాళీ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_బహుళకం_STEREO },   .unit = "headphones_rendering_mode" },
        { "binaural", ఖాళీ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_బహుళకం_BINAURAL }, .unit = "headphones_rendering_mode" },
    { "default_mix_gain", "Default mix gain", స్థానభ్రంశం_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "annotations", "Annotations", స్థానభ్రంశం_2(annotations), AV_OPT_TYPE_DICT, { .str = ఖాళీ }, 0, 0, FLAGS },
    { ఖాళీ },
};

స్థిర శూన్య *submix_element_బిడ్డ_తదుపరి(శూన్య *obj, శూన్య *prev)
{
    AVIAMFSubmixElement *submix_element = obj;
    ఒకవేళ (!prev)
        తిరిగి submix_element->element_mix_config;

    తిరిగి ఖాళీ;
}

స్థిర స్థిరరాశి AVClass *submix_element_బిడ్డ_iterate(శూన్య **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    స్థిరరాశి AVClass *ret = ఖాళీ;

    ఒకవేళ (!i)
        ret = &param_definition_class;

    ఒకవేళ (ret)
        *opaque = (శూన్య*)(i + 1);
    తిరిగి ret;
}

స్థిర స్థిరరాశి AVClass element_class = {
    .class_name          = "AVIAMFSubmixElement",
    .అంశం_name           = av_default_అంశం_name,
    .సంస్కరణ             = LIBAVUTIL_సంస్కరణ_INT,
    .option              = submix_element_options,
    .బిడ్డ_తదుపరి          = submix_element_బిడ్డ_తదుపరి,
    .బిడ్డ_class_iterate = submix_element_బిడ్డ_iterate,
};

IAMF_కూడు_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixElement, element, s)

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFSubmixLayout, x)
స్థిర స్థిరరాశి AVOption submix_layout_options[] = {
    { "layout_type", "Layout type", స్థానభ్రంశం_2(layout_type), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS },
            AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS, AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL, FLAGS, .unit = "layout_type" },
        { "loudspeakers", ఖాళీ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS }, .unit = "layout_type" },
        { "binaural",     ఖాళీ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL },     .unit = "layout_type" },
    { "sound_system", "Sound System", స్థానభ్రంశం_2(sound_system), AV_OPT_TYPE_CHLAYOUT, { .str = ఖాళీ }, 0, 0, FLAGS },
    { "integrated_loudness", "Integrated loudness", స్థానభ్రంశం_2(integrated_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "digital_peak", "Digital peak", స్థానభ్రంశం_2(digital_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "true_peak", "True peak", స్థానభ్రంశం_2(true_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "dialog_anchored_loudness", "Anchored loudness (Dialog)", స్థానభ్రంశం_2(dialogue_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "album_anchored_loudness", "Anchored loudness (Album)", స్థానభ్రంశం_2(album_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { ఖాళీ },
};

స్థిర స్థిరరాశి AVClass layout_class = {
    .class_name     = "AVIAMFSubmixLayout",
    .అంశం_name      = av_default_అంశం_name,
    .సంస్కరణ        = LIBAVUTIL_సంస్కరణ_INT,
    .option         = submix_layout_options,
};

IAMF_కూడు_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixLayout, layout, s)

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFSubmix, x)
స్థిర స్థిరరాశి AVOption submix_presentation_options[] = {
    { "default_mix_gain", "Default mix gain", స్థానభ్రంశం_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { ఖాళీ },
};

స్థిర శూన్య *submix_presentation_బిడ్డ_తదుపరి(శూన్య *obj, శూన్య *prev)
{
    AVIAMFSubmix *sub_mix = obj;
    ఒకవేళ (!prev)
        తిరిగి sub_mix->output_mix_config;

    తిరిగి ఖాళీ;
}

స్థిర స్థిరరాశి AVClass *submix_presentation_బిడ్డ_iterate(శూన్య **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    స్థిరరాశి AVClass *ret = ఖాళీ;

    ఎంపిక(i) {
    స్థితి 0:
        ret = &element_class;
        ఆపు;
    స్థితి 1:
        ret = &layout_class;
        ఆపు;
    స్థితి 2:
        ret = &param_definition_class;
        ఆపు;
    అప్రమేయ:
        ఆపు;
    }

    ఒకవేళ (ret)
        *opaque = (శూన్య*)(i + 1);
    తిరిగి ret;
}

స్థిర స్థిరరాశి AVClass submix_class = {
    .class_name          = "AVIAMFSubmix",
    .అంశం_name           = av_default_అంశం_name,
    .సంస్కరణ             = LIBAVUTIL_సంస్కరణ_INT,
    .option              = submix_presentation_options,
    .బిడ్డ_తదుపరి          = submix_presentation_బిడ్డ_తదుపరి,
    .బిడ్డ_class_iterate = submix_presentation_బిడ్డ_iterate,
};

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచించు స్థానభ్రంశం_2(x) offsetof(AVIAMFMixPresentation, x)
స్థిర స్థిరరాశి AVOption mix_presentation_options[] = {
    { "annotations", "set annotations", స్థానభ్రంశం_2(annotations), AV_OPT_TYPE_DICT, {.str = ఖాళీ }, 0, 0, FLAGS },
    { ఖాళీ },
};

#నిర్వచనం_రద్దు స్థానభ్రంశం_2
#నిర్వచనం_రద్దు FLAGS

స్థిర స్థిరరాశి AVClass *mix_presentation_బిడ్డ_iterate(శూన్య **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    స్థిరరాశి AVClass *ret = ఖాళీ;

    ఒకవేళ (!i)
        ret = &submix_class;

    ఒకవేళ (ret)
        *opaque = (శూన్య*)(i + 1);
    తిరిగి ret;
}

స్థిర స్థిరరాశి AVClass mix_presentation_class = {
    .class_name          = "AVIAMFMixPresentation",
    .అంశం_name           = av_default_అంశం_name,
    .సంస్కరణ             = LIBAVUTIL_సంస్కరణ_INT,
    .option              = mix_presentation_options,
    .బిడ్డ_class_iterate = mix_presentation_బిడ్డ_iterate,
};

స్థిరరాశి AVClass *av_iamf_mix_presentation_get_class(శూన్య)
{
    తిరిగి &mix_presentation_class;
}

AVIAMFMixPresentation *av_iamf_mix_presentation_alloc(శూన్య)
{
    AVIAMFMixPresentation *mix_presentation = av_mallocz(పరిమాణం(*mix_presentation));

    ఒకవేళ (mix_presentation) {
        mix_presentation->av_class = &mix_presentation_class;
        av_opt_సమితి_defaults(mix_presentation);
    }

    తిరిగి mix_presentation;
}

IAMF_కూడు_FUNC_TEMPLATE(AVIAMFMixPresentation, mix_presentation, AVIAMFSubmix, submix, es)

శూన్య av_iamf_mix_presentation_free(AVIAMFMixPresentation **pmix_presentation)
{
    AVIAMFMixPresentation *mix_presentation = *pmix_presentation;

    ఒకవేళ (!mix_presentation)
        తిరిగి;

    కొరకు (పూర్ణాంకం i = 0; i < mix_presentation->nb_submixes; i++) {
        AVIAMFSubmix *sub_mix = mix_presentation->submixes[i];
        కొరకు (పూర్ణాంకం j = 0; j < sub_mix->nb_elements; j++) {
            AVIAMFSubmixElement *submix_element = sub_mix->elements[j];
            av_opt_free(submix_element);
            av_free(submix_element->element_mix_config);
            av_free(submix_element);
        }
        av_free(sub_mix->elements);
        కొరకు (పూర్ణాంకం j = 0; j < sub_mix->nb_layouts; j++) {
            AVIAMFSubmixLayout *submix_layout = sub_mix->layouts[j];
            av_opt_free(submix_layout);
            av_free(submix_layout);
        }
        av_free(sub_mix->layouts);
        av_free(sub_mix->output_mix_config);
        av_free(sub_mix);
    }
    av_opt_free(mix_presentation);
    av_free(mix_presentation->submixes);

    av_freep(pmix_presentation);
}

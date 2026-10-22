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

#شامل <limits.h>
#شامل <stddef.h>
#شامل <stdint.h>

#شامل "avassert.h"
#شامل "error.h"
#شامل "iamf.h"
#شامل "log.h"
#شامل "mem.h"
#شامل "opt.h"

#تعریف_کرو IAMF_جوڑو_FUNC_TEMPLATE(والد_type, والد_name, بچہ_type, بچہ_name, suffix)                   \
بچہ_type *av_iamf_ ## والد_name ## جوڑو ## بچہ_name(والد_type *والد_name)                       \
{                                                                                                          \
    بچہ_type **بچہ_name ## suffix, *بچہ_name;                                                        \
                                                                                                           \
    اگر (والد_name->nb_## بچہ_name ## suffix == UINT_MAX)                                               \
        واپس تہی;                                                                                       \
                                                                                                           \
    بچہ_name ## suffix = av_realloc_array(والد_name->بچہ_name ## suffix,                             \
                                            والد_name->nb_## بچہ_name ## suffix + 1,                   \
                                            حجم(*والد_name->بچہ_name ## suffix));                   \
    اگر (!بچہ_name ## suffix)                                                                             \
        واپس تہی;                                                                                       \
                                                                                                           \
    والد_name->بچہ_name ## suffix = بچہ_name ## suffix;                                              \
                                                                                                           \
    بچہ_name = والد_name->بچہ_name ## suffix[والد_name->nb_## بچہ_name ## suffix]                \
               = av_mallocz(حجم(*بچہ_name));                                                          \
    اگر (!بچہ_name)                                                                                       \
        واپس تہی;                                                                                       \
                                                                                                           \
    بچہ_name->av_class = &بچہ_name ## _class;                                                          \
    av_opt_سیٹ_defaults(بچہ_name);                                                                       \
    والد_name->nb_## بچہ_name ## suffix++;                                                             \
                                                                                                           \
    واپس بچہ_name;                                                                                     \
}

#تعریف_کرو FLAGS AV_OPT_FLAG_ENCODING_PARAM

//
// Param Definition
//
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFMixGain, x)
ساکن ثابت AVOption mix_gain_options[] = {
    { "subblock_duration", "set subblock_duration", انحراف_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "animation_type", "set animation_type", انحراف_2(animation_type), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 2, FLAGS },
    { "start_point_value", "set start_point_value", انحراف_2(آغاز_نقطہ_قدر), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "end_point_value", "set end_point_value", انحراف_2(انتہا_نقطہ_قدر), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_value", "set control_point_value", انحراف_2(control_نقطہ_قدر), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_relative_time", "set control_point_relative_time", انحراف_2(control_نقطہ_relative_وقت), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, 0.0, 1.0, FLAGS },
    { تہی },
};

ساکن ثابت AVClass mix_gain_class = {
    .class_name     = "AVIAMFMixGain",
    .شے_name      = av_default_شے_name,
    .نسخہ        = LIBAVUTIL_نسخہ_INT,
    .option         = mix_gain_options,
};

#تعریف_منسوخ انحراف_2
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFDemixingInfo, x)
ساکن ثابت AVOption demixing_info_options[] = {
    { "subblock_duration", "set subblock_duration", انحراف_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "dmixp_mode", "set dmixp_mode", انحراف_2(dmixp_منوال), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 6, FLAGS },
    { تہی },
};

ساکن ثابت AVClass demixing_info_class = {
    .class_name     = "AVIAMFDemixingInfo",
    .شے_name      = av_default_شے_name,
    .نسخہ        = LIBAVUTIL_نسخہ_INT,
    .option         = demixing_info_options,
};

#تعریف_منسوخ انحراف_2
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFReconGain, x)
ساکن ثابت AVOption recon_gain_options[] = {
    { "subblock_duration", "set subblock_duration", انحراف_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { تہی },
};

ساکن ثابت AVClass recon_gain_class = {
    .class_name     = "AVIAMFReconGain",
    .شے_name      = av_default_شے_name,
    .نسخہ        = LIBAVUTIL_نسخہ_INT,
    .option         = recon_gain_options,
};

#تعریف_منسوخ انحراف_2
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFParamDefinition, x)
ساکن ثابت AVOption param_definition_options[] = {
    { "parameter_id", "set parameter_id", انحراف_2(parameter_id), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "parameter_rate", "set parameter_rate", انحراف_2(parameter_شرح), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "duration", "set duration", انحراف_2(duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "constant_subblock_duration", "set constant_subblock_duration", انحراف_2(constant_subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { تہی },
};

ساکن ثابت AVClass *param_definition_بچہ_iterate(خالی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = تہی;

    انتخاب(i) {
    حالت AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        ret = &mix_gain_class;
        توڑو;
    حالت AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        ret = &demixing_info_class;
        توڑو;
    حالت AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        ret = &recon_gain_class;
        توڑو;
    طےشدہ:
        توڑو;
    }

    اگر (ret)
        *opaque = (خالی*)(i + 1);
    واپس ret;
}

ساکن ثابت AVClass param_definition_class = {
    .class_name          = "AVIAMFParamDefinition",
    .شے_name           = av_default_شے_name,
    .نسخہ             = LIBAVUTIL_نسخہ_INT,
    .option              = param_definition_options,
    .بچہ_class_iterate = param_definition_بچہ_iterate,
};

ثابت AVClass *av_iamf_param_definition_get_class(خالی)
{
    واپس &param_definition_class;
}

AVIAMFParamDefinition *av_iamf_param_definition_alloc(شمار AVIAMFParamDefinitionType type,
                                                      غیرعلامتی صحیح nb_subblocks, size_t *برآمد_سائز)
{

    ساخت MixGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFMixGain m;
    };
    ساخت DemixStruct {
        AVIAMFParamDefinition p;
        AVIAMFDemixingInfo d;
    };
    ساخت ReconGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFReconGain r;
    };
    size_t subblocks_انحراف, subblock_سائز;
    size_t سائز;
    AVIAMFParamDefinition *par;

    انتخاب (type) {
    حالت AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        subblocks_انحراف = offsetof(ساخت MixGainStruct, m);
        subblock_سائز = حجم(AVIAMFMixGain);
        توڑو;
    حالت AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        subblocks_انحراف = offsetof(ساخت DemixStruct, d);
        subblock_سائز = حجم(AVIAMFDemixingInfo);
        توڑو;
    حالت AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        subblocks_انحراف = offsetof(ساخت ReconGainStruct, r);
        subblock_سائز = حجم(AVIAMFReconGain);
        توڑو;
    طےشدہ:
        واپس تہی;
    }

    سائز = subblocks_انحراف;
    اگر (nb_subblocks > (SIZE_MAX - سائز) / subblock_سائز)
        واپس تہی;
    سائز += subblock_سائز * nb_subblocks;

    par = av_mallocz(سائز);
    اگر (!par)
        واپس تہی;

    par->av_class = &param_definition_class;
    av_opt_سیٹ_defaults(par);

    par->type = type;
    par->nb_subblocks = nb_subblocks;
    par->subblock_سائز = subblock_سائز;
    par->subblocks_انحراف = subblocks_انحراف;

    برائے (صحیح i = 0; i < nb_subblocks; i++) {
        خالی *subblock = av_iamf_param_definition_get_subblock(par, i);

        انتخاب (type) {
        حالت AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
            ((AVIAMFMixGain *)subblock)->av_class = &mix_gain_class;
            توڑو;
        حالت AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
            ((AVIAMFDemixingInfo *)subblock)->av_class = &demixing_info_class;
            توڑو;
        حالت AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
            ((AVIAMFReconGain *)subblock)->av_class = &recon_gain_class;
            توڑو;
        طےشدہ:
            av_assert0(0);
        }
    }

    اگر (برآمد_سائز)
        *برآمد_سائز = سائز;

    واپس par;
}

//
// Audio Element
//
ساکن ثابت AVOptionArrayDef demixing_میٹرکس_def = { .سائز_max = (255 + 255) * 255, .sep = '|' };

#تعریف_منسوخ انحراف_2
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFLayer, x)
ساکن ثابت AVOption layer_options[] = {
    { "ch_layout", "set ch_layout", انحراف_2(ch_layout), AV_OPT_TYPE_CHLAYOUT, {.str = تہی }, 0, 0, FLAGS },
    { "flags", "set flags", انحراف_2(flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, AV_IAMF_LAYER_FLAG_RECON_GAIN, FLAGS, .unit = "flags" },
            {"recon_gain",  "Recon gain is present", 0, AV_OPT_TYPE_CONST,
                {.i64 = AV_IAMF_LAYER_FLAG_RECON_GAIN }, INT_MIN, زیادہ_سے_زیادہ_عدد, FLAGS, .unit = "flags"},
    { "output_gain_flags", "set output_gain_flags", انحراف_2(output_gain_flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, (1 << 6) - 1, FLAGS, .unit = "output_gain_flags" },
            {"FL",  "Left channel",            0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 5 }, INT_MIN, زیادہ_سے_زیادہ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"FR",  "Right channel",           0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 4 }, INT_MIN, زیادہ_سے_زیادہ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"BL",  "Left surround channel",   0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 3 }, INT_MIN, زیادہ_سے_زیادہ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"BR",  "Right surround channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 2 }, INT_MIN, زیادہ_سے_زیادہ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"TFL", "Left top front channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 1 }, INT_MIN, زیادہ_سے_زیادہ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"TFR", "Right top front channel", 0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 0 }, INT_MIN, زیادہ_سے_زیادہ_عدد, FLAGS, .unit = "output_gain_flags"},
    { "output_gain", "set output_gain", انحراف_2(output_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "ambisonics_mode", "set ambisonics_mode", انحراف_2(ambisonics_منوال), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_AMBISONICS_منوال_MONO },
            AV_IAMF_AMBISONICS_منوال_MONO, AV_IAMF_AMBISONICS_منوال_PROJECTION, FLAGS, .unit = "ambisonics_mode" },
        { "mono",       تہی, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_منوال_MONO },       .unit = "ambisonics_mode" },
        { "projection", تہی, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_منوال_PROJECTION }, .unit = "ambisonics_mode" },
    { "demixing_matrix", "set demixing_matrix", انحراف_2(demixing_میٹرکس), AV_OPT_TYPE_RATIONAL | AV_OPT_TYPE_FLAG_ARRAY,
            { .arr = &demixing_میٹرکس_def }, -1.0, 1.0, FLAGS },
    { تہی },
};

ساکن ثابت AVClass layer_class = {
    .class_name     = "AVIAMFLayer",
    .شے_name      = av_default_شے_name,
    .نسخہ        = LIBAVUTIL_نسخہ_INT,
    .option         = layer_options,
};

#تعریف_منسوخ انحراف_2
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFAudioElement, x)
ساکن ثابت AVOption audio_element_options[] = {
    { "audio_element_type", "set audio_element_type", انحراف_2(audio_element_type), AV_OPT_TYPE_INT,
            {.i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL },
            AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, FLAGS, .unit = "audio_element_type" },
        { "channel", تہی, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL }, .unit = "audio_element_type" },
        { "scene",   تہی, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE },   .unit = "audio_element_type" },
    { "default_w", "set default_w", انحراف_2(default_w), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 10, FLAGS },
    { تہی },
};

ساکن ثابت AVClass *audio_element_بچہ_iterate(خالی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = تہی;

    اگر (!i)
        ret = &layer_class;

    اگر (ret)
        *opaque = (خالی*)(i + 1);
    واپس ret;
}

ساکن ثابت AVClass audio_element_class = {
    .class_name          = "AVIAMFAudioElement",
    .شے_name           = av_default_شے_name,
    .نسخہ             = LIBAVUTIL_نسخہ_INT,
    .option              = audio_element_options,
    .بچہ_class_iterate = audio_element_بچہ_iterate,
};

ثابت AVClass *av_iamf_audio_element_get_class(خالی)
{
    واپس &audio_element_class;
}

AVIAMFAudioElement *av_iamf_audio_element_alloc(خالی)
{
    AVIAMFAudioElement *audio_element = av_mallocz(حجم(*audio_element));

    اگر (audio_element) {
        audio_element->av_class = &audio_element_class;
        av_opt_سیٹ_defaults(audio_element);
    }

    واپس audio_element;
}

IAMF_جوڑو_FUNC_TEMPLATE(AVIAMFAudioElement, audio_element, AVIAMFLayer, layer, s)

خالی av_iamf_audio_element_free(AVIAMFAudioElement **paudio_element)
{
    AVIAMFAudioElement *audio_element = *paudio_element;

    اگر (!audio_element)
        واپس;

    برائے (صحیح i = 0; i < audio_element->nb_layers; i++) {
        AVIAMFLayer *layer = audio_element->layers[i];
        av_opt_free(layer);
        av_free(layer->demixing_میٹرکس);
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
#تعریف_منسوخ انحراف_2
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFSubmixElement, x)
ساکن ثابت AVOption submix_element_options[] = {
    { "headphones_rendering_mode", "Headphones rendering mode", انحراف_2(headphones_rendering_منوال), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_HEADPHONES_منوال_STEREO },
            AV_IAMF_HEADPHONES_منوال_STEREO, AV_IAMF_HEADPHONES_منوال_BINAURAL, FLAGS, .unit = "headphones_rendering_mode" },
        { "stereo",   تہی, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_منوال_STEREO },   .unit = "headphones_rendering_mode" },
        { "binaural", تہی, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_منوال_BINAURAL }, .unit = "headphones_rendering_mode" },
    { "default_mix_gain", "Default mix gain", انحراف_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "annotations", "Annotations", انحراف_2(annotations), AV_OPT_TYPE_DICT, { .str = تہی }, 0, 0, FLAGS },
    { تہی },
};

ساکن خالی *submix_element_بچہ_اگلا(خالی *obj, خالی *پچھلا)
{
    AVIAMFSubmixElement *submix_element = obj;
    اگر (!پچھلا)
        واپس submix_element->element_mix_config;

    واپس تہی;
}

ساکن ثابت AVClass *submix_element_بچہ_iterate(خالی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = تہی;

    اگر (!i)
        ret = &param_definition_class;

    اگر (ret)
        *opaque = (خالی*)(i + 1);
    واپس ret;
}

ساکن ثابت AVClass element_class = {
    .class_name          = "AVIAMFSubmixElement",
    .شے_name           = av_default_شے_name,
    .نسخہ             = LIBAVUTIL_نسخہ_INT,
    .option              = submix_element_options,
    .بچہ_اگلا          = submix_element_بچہ_اگلا,
    .بچہ_class_iterate = submix_element_بچہ_iterate,
};

IAMF_جوڑو_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixElement, element, s)

#تعریف_منسوخ انحراف_2
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFSubmixLayout, x)
ساکن ثابت AVOption submix_layout_options[] = {
    { "layout_type", "Layout type", انحراف_2(layout_type), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS },
            AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS, AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL, FLAGS, .unit = "layout_type" },
        { "loudspeakers", تہی, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS }, .unit = "layout_type" },
        { "binaural",     تہی, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL },     .unit = "layout_type" },
    { "sound_system", "Sound System", انحراف_2(sound_system), AV_OPT_TYPE_CHLAYOUT, { .str = تہی }, 0, 0, FLAGS },
    { "integrated_loudness", "Integrated loudness", انحراف_2(integrated_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "digital_peak", "Digital peak", انحراف_2(digital_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "true_peak", "True peak", انحراف_2(true_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "dialog_anchored_loudness", "Anchored loudness (Dialog)", انحراف_2(dialogue_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "album_anchored_loudness", "Anchored loudness (Album)", انحراف_2(album_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { تہی },
};

ساکن ثابت AVClass layout_class = {
    .class_name     = "AVIAMFSubmixLayout",
    .شے_name      = av_default_شے_name,
    .نسخہ        = LIBAVUTIL_نسخہ_INT,
    .option         = submix_layout_options,
};

IAMF_جوڑو_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixLayout, layout, s)

#تعریف_منسوخ انحراف_2
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFSubmix, x)
ساکن ثابت AVOption submix_presentation_options[] = {
    { "default_mix_gain", "Default mix gain", انحراف_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { تہی },
};

ساکن خالی *submix_presentation_بچہ_اگلا(خالی *obj, خالی *پچھلا)
{
    AVIAMFSubmix *sub_mix = obj;
    اگر (!پچھلا)
        واپس sub_mix->output_mix_config;

    واپس تہی;
}

ساکن ثابت AVClass *submix_presentation_بچہ_iterate(خالی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = تہی;

    انتخاب(i) {
    حالت 0:
        ret = &element_class;
        توڑو;
    حالت 1:
        ret = &layout_class;
        توڑو;
    حالت 2:
        ret = &param_definition_class;
        توڑو;
    طےشدہ:
        توڑو;
    }

    اگر (ret)
        *opaque = (خالی*)(i + 1);
    واپس ret;
}

ساکن ثابت AVClass submix_class = {
    .class_name          = "AVIAMFSubmix",
    .شے_name           = av_default_شے_name,
    .نسخہ             = LIBAVUTIL_نسخہ_INT,
    .option              = submix_presentation_options,
    .بچہ_اگلا          = submix_presentation_بچہ_اگلا,
    .بچہ_class_iterate = submix_presentation_بچہ_iterate,
};

#تعریف_منسوخ انحراف_2
#تعریف_کرو انحراف_2(x) offsetof(AVIAMFMixPresentation, x)
ساکن ثابت AVOption mix_presentation_options[] = {
    { "annotations", "set annotations", انحراف_2(annotations), AV_OPT_TYPE_DICT, {.str = تہی }, 0, 0, FLAGS },
    { تہی },
};

#تعریف_منسوخ انحراف_2
#تعریف_منسوخ FLAGS

ساکن ثابت AVClass *mix_presentation_بچہ_iterate(خالی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = تہی;

    اگر (!i)
        ret = &submix_class;

    اگر (ret)
        *opaque = (خالی*)(i + 1);
    واپس ret;
}

ساکن ثابت AVClass mix_presentation_class = {
    .class_name          = "AVIAMFMixPresentation",
    .شے_name           = av_default_شے_name,
    .نسخہ             = LIBAVUTIL_نسخہ_INT,
    .option              = mix_presentation_options,
    .بچہ_class_iterate = mix_presentation_بچہ_iterate,
};

ثابت AVClass *av_iamf_mix_presentation_get_class(خالی)
{
    واپس &mix_presentation_class;
}

AVIAMFMixPresentation *av_iamf_mix_presentation_alloc(خالی)
{
    AVIAMFMixPresentation *mix_presentation = av_mallocz(حجم(*mix_presentation));

    اگر (mix_presentation) {
        mix_presentation->av_class = &mix_presentation_class;
        av_opt_سیٹ_defaults(mix_presentation);
    }

    واپس mix_presentation;
}

IAMF_جوڑو_FUNC_TEMPLATE(AVIAMFMixPresentation, mix_presentation, AVIAMFSubmix, submix, es)

خالی av_iamf_mix_presentation_free(AVIAMFMixPresentation **pmix_presentation)
{
    AVIAMFMixPresentation *mix_presentation = *pmix_presentation;

    اگر (!mix_presentation)
        واپس;

    برائے (صحیح i = 0; i < mix_presentation->nb_submixes; i++) {
        AVIAMFSubmix *sub_mix = mix_presentation->submixes[i];
        برائے (صحیح j = 0; j < sub_mix->nb_elements; j++) {
            AVIAMFSubmixElement *submix_element = sub_mix->elements[j];
            av_opt_free(submix_element);
            av_free(submix_element->element_mix_config);
            av_free(submix_element);
        }
        av_free(sub_mix->elements);
        برائے (صحیح j = 0; j < sub_mix->nb_layouts; j++) {
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

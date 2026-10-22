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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "iamf.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "opt.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ IAMF_ਜੋੜੋ_FUNC_TEMPLATE(ਮਾਪਾ_type, ਮਾਪਾ_name, ਬੱਚਾ_type, ਬੱਚਾ_name, suffix)                   \
ਬੱਚਾ_type *av_iamf_ ## ਮਾਪਾ_name ## ਜੋੜੋ ## ਬੱਚਾ_name(ਮਾਪਾ_type *ਮਾਪਾ_name)                       \
{                                                                                                          \
    ਬੱਚਾ_type **ਬੱਚਾ_name ## suffix, *ਬੱਚਾ_name;                                                        \
                                                                                                           \
    ਜੇ (ਮਾਪਾ_name->nb_## ਬੱਚਾ_name ## suffix == UINT_MAX)                                               \
        ਵਾਪਸ ਨਿਰਾ;                                                                                       \
                                                                                                           \
    ਬੱਚਾ_name ## suffix = av_realloc_array(ਮਾਪਾ_name->ਬੱਚਾ_name ## suffix,                             \
                                            ਮਾਪਾ_name->nb_## ਬੱਚਾ_name ## suffix + 1,                   \
                                            ਆਕਾਰ(*ਮਾਪਾ_name->ਬੱਚਾ_name ## suffix));                   \
    ਜੇ (!ਬੱਚਾ_name ## suffix)                                                                             \
        ਵਾਪਸ ਨਿਰਾ;                                                                                       \
                                                                                                           \
    ਮਾਪਾ_name->ਬੱਚਾ_name ## suffix = ਬੱਚਾ_name ## suffix;                                              \
                                                                                                           \
    ਬੱਚਾ_name = ਮਾਪਾ_name->ਬੱਚਾ_name ## suffix[ਮਾਪਾ_name->nb_## ਬੱਚਾ_name ## suffix]                \
               = av_mallocz(ਆਕਾਰ(*ਬੱਚਾ_name));                                                          \
    ਜੇ (!ਬੱਚਾ_name)                                                                                       \
        ਵਾਪਸ ਨਿਰਾ;                                                                                       \
                                                                                                           \
    ਬੱਚਾ_name->av_class = &ਬੱਚਾ_name ## _class;                                                          \
    av_opt_ਸੈੱਟ_defaults(ਬੱਚਾ_name);                                                                       \
    ਮਾਪਾ_name->nb_## ਬੱਚਾ_name ## suffix++;                                                             \
                                                                                                           \
    ਵਾਪਸ ਬੱਚਾ_name;                                                                                     \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FLAGS AV_OPT_FLAG_ENCODING_PARAM

//
// Param Definition
//
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFMixGain, x)
ਸਥਿਰ ਅਚਲ AVOption mix_gain_options[] = {
    { "subblock_duration", "set subblock_duration", ਵਿੱਥ_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "animation_type", "set animation_type", ਵਿੱਥ_2(animation_type), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 2, FLAGS },
    { "start_point_value", "set start_point_value", ਵਿੱਥ_2(ਸ਼ੁਰੂ_ਬਿੰਦੂ_ਮੁੱਲ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "end_point_value", "set end_point_value", ਵਿੱਥ_2(ਸਿਰਾ_ਬਿੰਦੂ_ਮੁੱਲ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_value", "set control_point_value", ਵਿੱਥ_2(control_ਬਿੰਦੂ_ਮੁੱਲ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_relative_time", "set control_point_relative_time", ਵਿੱਥ_2(control_ਬਿੰਦੂ_relative_ਸਮਾਂ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, 0.0, 1.0, FLAGS },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਅਚਲ AVClass mix_gain_class = {
    .class_name     = "AVIAMFMixGain",
    .ਵਸਤੂ_name      = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ        = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option         = mix_gain_options,
};

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFDemixingInfo, x)
ਸਥਿਰ ਅਚਲ AVOption demixing_info_options[] = {
    { "subblock_duration", "set subblock_duration", ਵਿੱਥ_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "dmixp_mode", "set dmixp_mode", ਵਿੱਥ_2(dmixp_ਬਹੁਲਕ), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 6, FLAGS },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਅਚਲ AVClass demixing_info_class = {
    .class_name     = "AVIAMFDemixingInfo",
    .ਵਸਤੂ_name      = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ        = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option         = demixing_info_options,
};

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFReconGain, x)
ਸਥਿਰ ਅਚਲ AVOption recon_gain_options[] = {
    { "subblock_duration", "set subblock_duration", ਵਿੱਥ_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਅਚਲ AVClass recon_gain_class = {
    .class_name     = "AVIAMFReconGain",
    .ਵਸਤੂ_name      = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ        = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option         = recon_gain_options,
};

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFParamDefinition, x)
ਸਥਿਰ ਅਚਲ AVOption param_definition_options[] = {
    { "parameter_id", "set parameter_id", ਵਿੱਥ_2(parameter_id), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "parameter_rate", "set parameter_rate", ਵਿੱਥ_2(parameter_ਦਰ), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "duration", "set duration", ਵਿੱਥ_2(duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "constant_subblock_duration", "set constant_subblock_duration", ਵਿੱਥ_2(constant_subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਅਚਲ AVClass *param_definition_ਬੱਚਾ_iterate(ਖਾਲੀ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ਅਚਲ AVClass *ret = ਨਿਰਾ;

    ਚੋਣ(i) {
    ਹਾਲਤ AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        ret = &mix_gain_class;
        ਰੋਕੋ;
    ਹਾਲਤ AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        ret = &demixing_info_class;
        ਰੋਕੋ;
    ਹਾਲਤ AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        ret = &recon_gain_class;
        ਰੋਕੋ;
    ਮੂਲ:
        ਰੋਕੋ;
    }

    ਜੇ (ret)
        *opaque = (ਖਾਲੀ*)(i + 1);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਅਚਲ AVClass param_definition_class = {
    .class_name          = "AVIAMFParamDefinition",
    .ਵਸਤੂ_name           = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ             = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option              = param_definition_options,
    .ਬੱਚਾ_class_iterate = param_definition_ਬੱਚਾ_iterate,
};

ਅਚਲ AVClass *av_iamf_param_definition_get_class(ਖਾਲੀ)
{
    ਵਾਪਸ &param_definition_class;
}

AVIAMFParamDefinition *av_iamf_param_definition_alloc(ਗਿਣਤੀ AVIAMFParamDefinitionType type,
                                                      ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nb_subblocks, size_t *ਬਾਹਰਲਾ_ਮਾਪ)
{

    ਬਣਤਰ MixGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFMixGain m;
    };
    ਬਣਤਰ DemixStruct {
        AVIAMFParamDefinition p;
        AVIAMFDemixingInfo d;
    };
    ਬਣਤਰ ReconGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFReconGain r;
    };
    size_t subblocks_ਵਿੱਥ, subblock_ਮਾਪ;
    size_t ਮਾਪ;
    AVIAMFParamDefinition *par;

    ਚੋਣ (type) {
    ਹਾਲਤ AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        subblocks_ਵਿੱਥ = offsetof(ਬਣਤਰ MixGainStruct, m);
        subblock_ਮਾਪ = ਆਕਾਰ(AVIAMFMixGain);
        ਰੋਕੋ;
    ਹਾਲਤ AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        subblocks_ਵਿੱਥ = offsetof(ਬਣਤਰ DemixStruct, d);
        subblock_ਮਾਪ = ਆਕਾਰ(AVIAMFDemixingInfo);
        ਰੋਕੋ;
    ਹਾਲਤ AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        subblocks_ਵਿੱਥ = offsetof(ਬਣਤਰ ReconGainStruct, r);
        subblock_ਮਾਪ = ਆਕਾਰ(AVIAMFReconGain);
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਮਾਪ = subblocks_ਵਿੱਥ;
    ਜੇ (nb_subblocks > (SIZE_MAX - ਮਾਪ) / subblock_ਮਾਪ)
        ਵਾਪਸ ਨਿਰਾ;
    ਮਾਪ += subblock_ਮਾਪ * nb_subblocks;

    par = av_mallocz(ਮਾਪ);
    ਜੇ (!par)
        ਵਾਪਸ ਨਿਰਾ;

    par->av_class = &param_definition_class;
    av_opt_ਸੈੱਟ_defaults(par);

    par->type = type;
    par->nb_subblocks = nb_subblocks;
    par->subblock_ਮਾਪ = subblock_ਮਾਪ;
    par->subblocks_ਵਿੱਥ = subblocks_ਵਿੱਥ;

    ਲਈ (ਪੂਰਨ i = 0; i < nb_subblocks; i++) {
        ਖਾਲੀ *subblock = av_iamf_param_definition_get_subblock(par, i);

        ਚੋਣ (type) {
        ਹਾਲਤ AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
            ((AVIAMFMixGain *)subblock)->av_class = &mix_gain_class;
            ਰੋਕੋ;
        ਹਾਲਤ AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
            ((AVIAMFDemixingInfo *)subblock)->av_class = &demixing_info_class;
            ਰੋਕੋ;
        ਹਾਲਤ AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
            ((AVIAMFReconGain *)subblock)->av_class = &recon_gain_class;
            ਰੋਕੋ;
        ਮੂਲ:
            av_assert0(0);
        }
    }

    ਜੇ (ਬਾਹਰਲਾ_ਮਾਪ)
        *ਬਾਹਰਲਾ_ਮਾਪ = ਮਾਪ;

    ਵਾਪਸ par;
}

//
// Audio Element
//
ਸਥਿਰ ਅਚਲ AVOptionArrayDef demixing_ਮੈਟ੍ਰਿਕਸ_def = { .ਮਾਪ_max = (255 + 255) * 255, .sep = '|' };

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFLayer, x)
ਸਥਿਰ ਅਚਲ AVOption layer_options[] = {
    { "ch_layout", "set ch_layout", ਵਿੱਥ_2(ch_layout), AV_OPT_TYPE_CHLAYOUT, {.str = ਨਿਰਾ }, 0, 0, FLAGS },
    { "flags", "set flags", ਵਿੱਥ_2(flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, AV_IAMF_LAYER_FLAG_RECON_GAIN, FLAGS, .unit = "flags" },
            {"recon_gain",  "Recon gain is present", 0, AV_OPT_TYPE_CONST,
                {.i64 = AV_IAMF_LAYER_FLAG_RECON_GAIN }, INT_MIN, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, FLAGS, .unit = "flags"},
    { "output_gain_flags", "set output_gain_flags", ਵਿੱਥ_2(output_gain_flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, (1 << 6) - 1, FLAGS, .unit = "output_gain_flags" },
            {"FL",  "Left channel",            0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 5 }, INT_MIN, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, FLAGS, .unit = "output_gain_flags"},
            {"FR",  "Right channel",           0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 4 }, INT_MIN, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, FLAGS, .unit = "output_gain_flags"},
            {"BL",  "Left surround channel",   0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 3 }, INT_MIN, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, FLAGS, .unit = "output_gain_flags"},
            {"BR",  "Right surround channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 2 }, INT_MIN, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, FLAGS, .unit = "output_gain_flags"},
            {"TFL", "Left top front channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 1 }, INT_MIN, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, FLAGS, .unit = "output_gain_flags"},
            {"TFR", "Right top front channel", 0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 0 }, INT_MIN, ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, FLAGS, .unit = "output_gain_flags"},
    { "output_gain", "set output_gain", ਵਿੱਥ_2(output_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "ambisonics_mode", "set ambisonics_mode", ਵਿੱਥ_2(ambisonics_ਬਹੁਲਕ), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_AMBISONICS_ਬਹੁਲਕ_MONO },
            AV_IAMF_AMBISONICS_ਬਹੁਲਕ_MONO, AV_IAMF_AMBISONICS_ਬਹੁਲਕ_PROJECTION, FLAGS, .unit = "ambisonics_mode" },
        { "mono",       ਨਿਰਾ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_ਬਹੁਲਕ_MONO },       .unit = "ambisonics_mode" },
        { "projection", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_ਬਹੁਲਕ_PROJECTION }, .unit = "ambisonics_mode" },
    { "demixing_matrix", "set demixing_matrix", ਵਿੱਥ_2(demixing_ਮੈਟ੍ਰਿਕਸ), AV_OPT_TYPE_RATIONAL | AV_OPT_TYPE_FLAG_ARRAY,
            { .arr = &demixing_ਮੈਟ੍ਰਿਕਸ_def }, -1.0, 1.0, FLAGS },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਅਚਲ AVClass layer_class = {
    .class_name     = "AVIAMFLayer",
    .ਵਸਤੂ_name      = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ        = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option         = layer_options,
};

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFAudioElement, x)
ਸਥਿਰ ਅਚਲ AVOption audio_element_options[] = {
    { "audio_element_type", "set audio_element_type", ਵਿੱਥ_2(audio_element_type), AV_OPT_TYPE_INT,
            {.i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL },
            AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, FLAGS, .unit = "audio_element_type" },
        { "channel", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL }, .unit = "audio_element_type" },
        { "scene",   ਨਿਰਾ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE },   .unit = "audio_element_type" },
    { "default_w", "set default_w", ਵਿੱਥ_2(default_w), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 10, FLAGS },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਅਚਲ AVClass *audio_element_ਬੱਚਾ_iterate(ਖਾਲੀ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ਅਚਲ AVClass *ret = ਨਿਰਾ;

    ਜੇ (!i)
        ret = &layer_class;

    ਜੇ (ret)
        *opaque = (ਖਾਲੀ*)(i + 1);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਅਚਲ AVClass audio_element_class = {
    .class_name          = "AVIAMFAudioElement",
    .ਵਸਤੂ_name           = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ             = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option              = audio_element_options,
    .ਬੱਚਾ_class_iterate = audio_element_ਬੱਚਾ_iterate,
};

ਅਚਲ AVClass *av_iamf_audio_element_get_class(ਖਾਲੀ)
{
    ਵਾਪਸ &audio_element_class;
}

AVIAMFAudioElement *av_iamf_audio_element_alloc(ਖਾਲੀ)
{
    AVIAMFAudioElement *audio_element = av_mallocz(ਆਕਾਰ(*audio_element));

    ਜੇ (audio_element) {
        audio_element->av_class = &audio_element_class;
        av_opt_ਸੈੱਟ_defaults(audio_element);
    }

    ਵਾਪਸ audio_element;
}

IAMF_ਜੋੜੋ_FUNC_TEMPLATE(AVIAMFAudioElement, audio_element, AVIAMFLayer, layer, s)

ਖਾਲੀ av_iamf_audio_element_free(AVIAMFAudioElement **paudio_element)
{
    AVIAMFAudioElement *audio_element = *paudio_element;

    ਜੇ (!audio_element)
        ਵਾਪਸ;

    ਲਈ (ਪੂਰਨ i = 0; i < audio_element->nb_layers; i++) {
        AVIAMFLayer *layer = audio_element->layers[i];
        av_opt_free(layer);
        av_free(layer->demixing_ਮੈਟ੍ਰਿਕਸ);
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
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFSubmixElement, x)
ਸਥਿਰ ਅਚਲ AVOption submix_element_options[] = {
    { "headphones_rendering_mode", "Headphones rendering mode", ਵਿੱਥ_2(headphones_rendering_ਬਹੁਲਕ), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_HEADPHONES_ਬਹੁਲਕ_STEREO },
            AV_IAMF_HEADPHONES_ਬਹੁਲਕ_STEREO, AV_IAMF_HEADPHONES_ਬਹੁਲਕ_BINAURAL, FLAGS, .unit = "headphones_rendering_mode" },
        { "stereo",   ਨਿਰਾ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_ਬਹੁਲਕ_STEREO },   .unit = "headphones_rendering_mode" },
        { "binaural", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_ਬਹੁਲਕ_BINAURAL }, .unit = "headphones_rendering_mode" },
    { "default_mix_gain", "Default mix gain", ਵਿੱਥ_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "annotations", "Annotations", ਵਿੱਥ_2(annotations), AV_OPT_TYPE_DICT, { .str = ਨਿਰਾ }, 0, 0, FLAGS },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਖਾਲੀ *submix_element_ਬੱਚਾ_ਅਗਲਾ(ਖਾਲੀ *obj, ਖਾਲੀ *prev)
{
    AVIAMFSubmixElement *submix_element = obj;
    ਜੇ (!prev)
        ਵਾਪਸ submix_element->element_mix_config;

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਅਚਲ AVClass *submix_element_ਬੱਚਾ_iterate(ਖਾਲੀ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ਅਚਲ AVClass *ret = ਨਿਰਾ;

    ਜੇ (!i)
        ret = &param_definition_class;

    ਜੇ (ret)
        *opaque = (ਖਾਲੀ*)(i + 1);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਅਚਲ AVClass element_class = {
    .class_name          = "AVIAMFSubmixElement",
    .ਵਸਤੂ_name           = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ             = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option              = submix_element_options,
    .ਬੱਚਾ_ਅਗਲਾ          = submix_element_ਬੱਚਾ_ਅਗਲਾ,
    .ਬੱਚਾ_class_iterate = submix_element_ਬੱਚਾ_iterate,
};

IAMF_ਜੋੜੋ_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixElement, element, s)

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFSubmixLayout, x)
ਸਥਿਰ ਅਚਲ AVOption submix_layout_options[] = {
    { "layout_type", "Layout type", ਵਿੱਥ_2(layout_type), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS },
            AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS, AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL, FLAGS, .unit = "layout_type" },
        { "loudspeakers", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS }, .unit = "layout_type" },
        { "binaural",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL },     .unit = "layout_type" },
    { "sound_system", "Sound System", ਵਿੱਥ_2(sound_system), AV_OPT_TYPE_CHLAYOUT, { .str = ਨਿਰਾ }, 0, 0, FLAGS },
    { "integrated_loudness", "Integrated loudness", ਵਿੱਥ_2(integrated_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "digital_peak", "Digital peak", ਵਿੱਥ_2(digital_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "true_peak", "True peak", ਵਿੱਥ_2(true_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "dialog_anchored_loudness", "Anchored loudness (Dialog)", ਵਿੱਥ_2(dialogue_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "album_anchored_loudness", "Anchored loudness (Album)", ਵਿੱਥ_2(album_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਅਚਲ AVClass layout_class = {
    .class_name     = "AVIAMFSubmixLayout",
    .ਵਸਤੂ_name      = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ        = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option         = submix_layout_options,
};

IAMF_ਜੋੜੋ_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixLayout, layout, s)

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFSubmix, x)
ਸਥਿਰ ਅਚਲ AVOption submix_presentation_options[] = {
    { "default_mix_gain", "Default mix gain", ਵਿੱਥ_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { ਨਿਰਾ },
};

ਸਥਿਰ ਖਾਲੀ *submix_presentation_ਬੱਚਾ_ਅਗਲਾ(ਖਾਲੀ *obj, ਖਾਲੀ *prev)
{
    AVIAMFSubmix *sub_mix = obj;
    ਜੇ (!prev)
        ਵਾਪਸ sub_mix->output_mix_config;

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਅਚਲ AVClass *submix_presentation_ਬੱਚਾ_iterate(ਖਾਲੀ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ਅਚਲ AVClass *ret = ਨਿਰਾ;

    ਚੋਣ(i) {
    ਹਾਲਤ 0:
        ret = &element_class;
        ਰੋਕੋ;
    ਹਾਲਤ 1:
        ret = &layout_class;
        ਰੋਕੋ;
    ਹਾਲਤ 2:
        ret = &param_definition_class;
        ਰੋਕੋ;
    ਮੂਲ:
        ਰੋਕੋ;
    }

    ਜੇ (ret)
        *opaque = (ਖਾਲੀ*)(i + 1);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਅਚਲ AVClass submix_class = {
    .class_name          = "AVIAMFSubmix",
    .ਵਸਤੂ_name           = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ             = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option              = submix_presentation_options,
    .ਬੱਚਾ_ਅਗਲਾ          = submix_presentation_ਬੱਚਾ_ਅਗਲਾ,
    .ਬੱਚਾ_class_iterate = submix_presentation_ਬੱਚਾ_iterate,
};

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(x) offsetof(AVIAMFMixPresentation, x)
ਸਥਿਰ ਅਚਲ AVOption mix_presentation_options[] = {
    { "annotations", "set annotations", ਵਿੱਥ_2(annotations), AV_OPT_TYPE_DICT, {.str = ਨਿਰਾ }, 0, 0, FLAGS },
    { ਨਿਰਾ },
};

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਵਿੱਥ_2
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ FLAGS

ਸਥਿਰ ਅਚਲ AVClass *mix_presentation_ਬੱਚਾ_iterate(ਖਾਲੀ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ਅਚਲ AVClass *ret = ਨਿਰਾ;

    ਜੇ (!i)
        ret = &submix_class;

    ਜੇ (ret)
        *opaque = (ਖਾਲੀ*)(i + 1);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਅਚਲ AVClass mix_presentation_class = {
    .class_name          = "AVIAMFMixPresentation",
    .ਵਸਤੂ_name           = av_default_ਵਸਤੂ_name,
    .ਸੰਸਕਰਣ             = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .option              = mix_presentation_options,
    .ਬੱਚਾ_class_iterate = mix_presentation_ਬੱਚਾ_iterate,
};

ਅਚਲ AVClass *av_iamf_mix_presentation_get_class(ਖਾਲੀ)
{
    ਵਾਪਸ &mix_presentation_class;
}

AVIAMFMixPresentation *av_iamf_mix_presentation_alloc(ਖਾਲੀ)
{
    AVIAMFMixPresentation *mix_presentation = av_mallocz(ਆਕਾਰ(*mix_presentation));

    ਜੇ (mix_presentation) {
        mix_presentation->av_class = &mix_presentation_class;
        av_opt_ਸੈੱਟ_defaults(mix_presentation);
    }

    ਵਾਪਸ mix_presentation;
}

IAMF_ਜੋੜੋ_FUNC_TEMPLATE(AVIAMFMixPresentation, mix_presentation, AVIAMFSubmix, submix, es)

ਖਾਲੀ av_iamf_mix_presentation_free(AVIAMFMixPresentation **pmix_presentation)
{
    AVIAMFMixPresentation *mix_presentation = *pmix_presentation;

    ਜੇ (!mix_presentation)
        ਵਾਪਸ;

    ਲਈ (ਪੂਰਨ i = 0; i < mix_presentation->nb_submixes; i++) {
        AVIAMFSubmix *sub_mix = mix_presentation->submixes[i];
        ਲਈ (ਪੂਰਨ j = 0; j < sub_mix->nb_elements; j++) {
            AVIAMFSubmixElement *submix_element = sub_mix->elements[j];
            av_opt_free(submix_element);
            av_free(submix_element->element_mix_config);
            av_free(submix_element);
        }
        av_free(sub_mix->elements);
        ਲਈ (ਪੂਰਨ j = 0; j < sub_mix->nb_layouts; j++) {
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

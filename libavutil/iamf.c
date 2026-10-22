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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "iamf.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "opt.h"

#ವ್ಯಾಖ್ಯಾನಿಸು IAMF_ಕೂಡಿಸು_FUNC_TEMPLATE(ಪೋಷಕ_type, ಪೋಷಕ_name, ಮಗು_type, ಮಗು_name, suffix)                   \
ಮಗು_type *av_iamf_ ## ಪೋಷಕ_name ## ಕೂಡಿಸು ## ಮಗು_name(ಪೋಷಕ_type *ಪೋಷಕ_name)                       \
{                                                                                                          \
    ಮಗು_type **ಮಗು_name ## suffix, *ಮಗು_name;                                                        \
                                                                                                           \
    ಆದರೆ (ಪೋಷಕ_name->nb_## ಮಗು_name ## suffix == UINT_MAX)                                               \
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;                                                                                       \
                                                                                                           \
    ಮಗು_name ## suffix = av_realloc_array(ಪೋಷಕ_name->ಮಗು_name ## suffix,                             \
                                            ಪೋಷಕ_name->nb_## ಮಗು_name ## suffix + 1,                   \
                                            ಗಾತ್ರ(*ಪೋಷಕ_name->ಮಗು_name ## suffix));                   \
    ಆದರೆ (!ಮಗು_name ## suffix)                                                                             \
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;                                                                                       \
                                                                                                           \
    ಪೋಷಕ_name->ಮಗು_name ## suffix = ಮಗು_name ## suffix;                                              \
                                                                                                           \
    ಮಗು_name = ಪೋಷಕ_name->ಮಗು_name ## suffix[ಪೋಷಕ_name->nb_## ಮಗು_name ## suffix]                \
               = av_mallocz(ಗಾತ್ರ(*ಮಗು_name));                                                          \
    ಆದರೆ (!ಮಗು_name)                                                                                       \
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;                                                                                       \
                                                                                                           \
    ಮಗು_name->av_class = &ಮಗು_name ## _class;                                                          \
    av_opt_ಗಣ_defaults(ಮಗು_name);                                                                       \
    ಪೋಷಕ_name->nb_## ಮಗು_name ## suffix++;                                                             \
                                                                                                           \
    ಹಿಂತಿರುಗಿ ಮಗು_name;                                                                                     \
}

#ವ್ಯಾಖ್ಯಾನಿಸು FLAGS AV_OPT_FLAG_ENCODING_PARAM

//
// Param Definition
//
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFMixGain, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption mix_gain_options[] = {
    { "subblock_duration", "set subblock_duration", ಸ್ಥಾನಾಂತರ_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "animation_type", "set animation_type", ಸ್ಥಾನಾಂತರ_2(animation_type), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 2, FLAGS },
    { "start_point_value", "set start_point_value", ಸ್ಥಾನಾಂತರ_2(ಆರಂಭ_ಬಿಂದು_ಮೌಲ್ಯ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "end_point_value", "set end_point_value", ಸ್ಥಾನಾಂತರ_2(ಕೊನೆ_ಬಿಂದು_ಮೌಲ್ಯ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_value", "set control_point_value", ಸ್ಥಾನಾಂತರ_2(control_ಬಿಂದು_ಮೌಲ್ಯ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_relative_time", "set control_point_relative_time", ಸ್ಥಾನಾಂತರ_2(control_ಬಿಂದು_relative_ಸಮಯ), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, 0.0, 1.0, FLAGS },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass mix_gain_class = {
    .class_name     = "AVIAMFMixGain",
    .ಅಂಶ_name      = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ        = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option         = mix_gain_options,
};

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFDemixingInfo, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption demixing_info_options[] = {
    { "subblock_duration", "set subblock_duration", ಸ್ಥಾನಾಂತರ_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "dmixp_mode", "set dmixp_mode", ಸ್ಥಾನಾಂತರ_2(dmixp_ಬಹುಲಕ), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 6, FLAGS },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass demixing_info_class = {
    .class_name     = "AVIAMFDemixingInfo",
    .ಅಂಶ_name      = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ        = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option         = demixing_info_options,
};

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFReconGain, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption recon_gain_options[] = {
    { "subblock_duration", "set subblock_duration", ಸ್ಥಾನಾಂತರ_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass recon_gain_class = {
    .class_name     = "AVIAMFReconGain",
    .ಅಂಶ_name      = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ        = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option         = recon_gain_options,
};

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFParamDefinition, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption param_definition_options[] = {
    { "parameter_id", "set parameter_id", ಸ್ಥಾನಾಂತರ_2(parameter_id), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "parameter_rate", "set parameter_rate", ಸ್ಥಾನಾಂತರ_2(parameter_ದರ), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "duration", "set duration", ಸ್ಥಾನಾಂತರ_2(duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "constant_subblock_duration", "set constant_subblock_duration", ಸ್ಥಾನಾಂತರ_2(constant_subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass *param_definition_ಮಗು_iterate(ಶೂನ್ಯ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ಸ್ಥಿರಾಂಕ AVClass *ret = ಖಾಲಿ;

    ಆಯ್ಕೆ(i) {
    ಸ್ಥಿತಿ AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        ret = &mix_gain_class;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        ret = &demixing_info_class;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        ret = &recon_gain_class;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (ret)
        *opaque = (ಶೂನ್ಯ*)(i + 1);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass param_definition_class = {
    .class_name          = "AVIAMFParamDefinition",
    .ಅಂಶ_name           = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ             = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option              = param_definition_options,
    .ಮಗು_class_iterate = param_definition_ಮಗು_iterate,
};

ಸ್ಥಿರಾಂಕ AVClass *av_iamf_param_definition_get_class(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ &param_definition_class;
}

AVIAMFParamDefinition *av_iamf_param_definition_alloc(ಎಣಿಕೆ AVIAMFParamDefinitionType type,
                                                      ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ nb_subblocks, size_t *ಹೊರಹೋಗು_ಗಾತ್ರ)
{

    ರಚನೆ MixGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFMixGain m;
    };
    ರಚನೆ DemixStruct {
        AVIAMFParamDefinition p;
        AVIAMFDemixingInfo d;
    };
    ರಚನೆ ReconGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFReconGain r;
    };
    size_t subblocks_ಸ್ಥಾನಾಂತರ, subblock_ಗಾತ್ರ;
    size_t ಗಾತ್ರ_2;
    AVIAMFParamDefinition *par;

    ಆಯ್ಕೆ (type) {
    ಸ್ಥಿತಿ AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        subblocks_ಸ್ಥಾನಾಂತರ = offsetof(ರಚನೆ MixGainStruct, m);
        subblock_ಗಾತ್ರ = ಗಾತ್ರ(AVIAMFMixGain);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        subblocks_ಸ್ಥಾನಾಂತರ = offsetof(ರಚನೆ DemixStruct, d);
        subblock_ಗಾತ್ರ = ಗಾತ್ರ(AVIAMFDemixingInfo);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        subblocks_ಸ್ಥಾನಾಂತರ = offsetof(ರಚನೆ ReconGainStruct, r);
        subblock_ಗಾತ್ರ = ಗಾತ್ರ(AVIAMFReconGain);
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಗಾತ್ರ_2 = subblocks_ಸ್ಥಾನಾಂತರ;
    ಆದರೆ (nb_subblocks > (SIZE_MAX - ಗಾತ್ರ_2) / subblock_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಗಾತ್ರ_2 += subblock_ಗಾತ್ರ * nb_subblocks;

    par = av_mallocz(ಗಾತ್ರ_2);
    ಆದರೆ (!par)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    par->av_class = &param_definition_class;
    av_opt_ಗಣ_defaults(par);

    par->type = type;
    par->nb_subblocks = nb_subblocks;
    par->subblock_ಗಾತ್ರ = subblock_ಗಾತ್ರ;
    par->subblocks_ಸ್ಥಾನಾಂತರ = subblocks_ಸ್ಥಾನಾಂತರ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < nb_subblocks; i++) {
        ಶೂನ್ಯ *subblock = av_iamf_param_definition_get_subblock(par, i);

        ಆಯ್ಕೆ (type) {
        ಸ್ಥಿತಿ AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
            ((AVIAMFMixGain *)subblock)->av_class = &mix_gain_class;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
            ((AVIAMFDemixingInfo *)subblock)->av_class = &demixing_info_class;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
            ((AVIAMFReconGain *)subblock)->av_class = &recon_gain_class;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            av_assert0(0);
        }
    }

    ಆದರೆ (ಹೊರಹೋಗು_ಗಾತ್ರ)
        *ಹೊರಹೋಗು_ಗಾತ್ರ = ಗಾತ್ರ_2;

    ಹಿಂತಿರುಗಿ par;
}

//
// Audio Element
//
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOptionArrayDef demixing_ಮಾತೃಕೆ_def = { .ಗಾತ್ರ_max = (255 + 255) * 255, .sep = '|' };

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFLayer, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption layer_options[] = {
    { "ch_layout", "set ch_layout", ಸ್ಥಾನಾಂತರ_2(ch_layout), AV_OPT_TYPE_CHLAYOUT, {.str = ಖಾಲಿ }, 0, 0, FLAGS },
    { "flags", "set flags", ಸ್ಥಾನಾಂತರ_2(flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, AV_IAMF_LAYER_FLAG_RECON_GAIN, FLAGS, .unit = "flags" },
            {"recon_gain",  "Recon gain is present", 0, AV_OPT_TYPE_CONST,
                {.i64 = AV_IAMF_LAYER_FLAG_RECON_GAIN }, INT_MIN, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, FLAGS, .unit = "flags"},
    { "output_gain_flags", "set output_gain_flags", ಸ್ಥಾನಾಂತರ_2(output_gain_flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, (1 << 6) - 1, FLAGS, .unit = "output_gain_flags" },
            {"FL",  "Left channel",            0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 5 }, INT_MIN, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, FLAGS, .unit = "output_gain_flags"},
            {"FR",  "Right channel",           0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 4 }, INT_MIN, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, FLAGS, .unit = "output_gain_flags"},
            {"BL",  "Left surround channel",   0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 3 }, INT_MIN, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, FLAGS, .unit = "output_gain_flags"},
            {"BR",  "Right surround channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 2 }, INT_MIN, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, FLAGS, .unit = "output_gain_flags"},
            {"TFL", "Left top front channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 1 }, INT_MIN, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, FLAGS, .unit = "output_gain_flags"},
            {"TFR", "Right top front channel", 0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 0 }, INT_MIN, ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, FLAGS, .unit = "output_gain_flags"},
    { "output_gain", "set output_gain", ಸ್ಥಾನಾಂತರ_2(output_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "ambisonics_mode", "set ambisonics_mode", ಸ್ಥಾನಾಂತರ_2(ambisonics_ಬಹುಲಕ), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_AMBISONICS_ಬಹುಲಕ_MONO },
            AV_IAMF_AMBISONICS_ಬಹುಲಕ_MONO, AV_IAMF_AMBISONICS_ಬಹುಲಕ_PROJECTION, FLAGS, .unit = "ambisonics_mode" },
        { "mono",       ಖಾಲಿ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_ಬಹುಲಕ_MONO },       .unit = "ambisonics_mode" },
        { "projection", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_ಬಹುಲಕ_PROJECTION }, .unit = "ambisonics_mode" },
    { "demixing_matrix", "set demixing_matrix", ಸ್ಥಾನಾಂತರ_2(demixing_ಮಾತೃಕೆ), AV_OPT_TYPE_RATIONAL | AV_OPT_TYPE_FLAG_ARRAY,
            { .arr = &demixing_ಮಾತೃಕೆ_def }, -1.0, 1.0, FLAGS },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass layer_class = {
    .class_name     = "AVIAMFLayer",
    .ಅಂಶ_name      = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ        = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option         = layer_options,
};

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFAudioElement, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption audio_element_options[] = {
    { "audio_element_type", "set audio_element_type", ಸ್ಥಾನಾಂತರ_2(audio_element_type), AV_OPT_TYPE_INT,
            {.i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL },
            AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, FLAGS, .unit = "audio_element_type" },
        { "channel", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL }, .unit = "audio_element_type" },
        { "scene",   ಖಾಲಿ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE },   .unit = "audio_element_type" },
    { "default_w", "set default_w", ಸ್ಥಾನಾಂತರ_2(default_w), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 10, FLAGS },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass *audio_element_ಮಗು_iterate(ಶೂನ್ಯ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ಸ್ಥಿರಾಂಕ AVClass *ret = ಖಾಲಿ;

    ಆದರೆ (!i)
        ret = &layer_class;

    ಆದರೆ (ret)
        *opaque = (ಶೂನ್ಯ*)(i + 1);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass audio_element_class = {
    .class_name          = "AVIAMFAudioElement",
    .ಅಂಶ_name           = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ             = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option              = audio_element_options,
    .ಮಗು_class_iterate = audio_element_ಮಗು_iterate,
};

ಸ್ಥಿರಾಂಕ AVClass *av_iamf_audio_element_get_class(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ &audio_element_class;
}

AVIAMFAudioElement *av_iamf_audio_element_alloc(ಶೂನ್ಯ)
{
    AVIAMFAudioElement *audio_element = av_mallocz(ಗಾತ್ರ(*audio_element));

    ಆದರೆ (audio_element) {
        audio_element->av_class = &audio_element_class;
        av_opt_ಗಣ_defaults(audio_element);
    }

    ಹಿಂತಿರುಗಿ audio_element;
}

IAMF_ಕೂಡಿಸು_FUNC_TEMPLATE(AVIAMFAudioElement, audio_element, AVIAMFLayer, layer, s)

ಶೂನ್ಯ av_iamf_audio_element_free(AVIAMFAudioElement **paudio_element)
{
    AVIAMFAudioElement *audio_element = *paudio_element;

    ಆದರೆ (!audio_element)
        ಹಿಂತಿರುಗಿ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < audio_element->nb_layers; i++) {
        AVIAMFLayer *layer = audio_element->layers[i];
        av_opt_free(layer);
        av_free(layer->demixing_ಮಾತೃಕೆ);
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
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFSubmixElement, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption submix_element_options[] = {
    { "headphones_rendering_mode", "Headphones rendering mode", ಸ್ಥಾನಾಂತರ_2(headphones_rendering_ಬಹುಲಕ), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_HEADPHONES_ಬಹುಲಕ_STEREO },
            AV_IAMF_HEADPHONES_ಬಹುಲಕ_STEREO, AV_IAMF_HEADPHONES_ಬಹುಲಕ_BINAURAL, FLAGS, .unit = "headphones_rendering_mode" },
        { "stereo",   ಖಾಲಿ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_ಬಹುಲಕ_STEREO },   .unit = "headphones_rendering_mode" },
        { "binaural", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_ಬಹುಲಕ_BINAURAL }, .unit = "headphones_rendering_mode" },
    { "default_mix_gain", "Default mix gain", ಸ್ಥಾನಾಂತರ_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "annotations", "Annotations", ಸ್ಥಾನಾಂತರ_2(annotations), AV_OPT_TYPE_DICT, { .str = ಖಾಲಿ }, 0, 0, FLAGS },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಶೂನ್ಯ *submix_element_ಮಗು_ಮುಂದಿನ(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *prev)
{
    AVIAMFSubmixElement *submix_element = obj;
    ಆದರೆ (!prev)
        ಹಿಂತಿರುಗಿ submix_element->element_mix_config;

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass *submix_element_ಮಗು_iterate(ಶೂನ್ಯ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ಸ್ಥಿರಾಂಕ AVClass *ret = ಖಾಲಿ;

    ಆದರೆ (!i)
        ret = &param_definition_class;

    ಆದರೆ (ret)
        *opaque = (ಶೂನ್ಯ*)(i + 1);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass element_class = {
    .class_name          = "AVIAMFSubmixElement",
    .ಅಂಶ_name           = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ             = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option              = submix_element_options,
    .ಮಗು_ಮುಂದಿನ          = submix_element_ಮಗು_ಮುಂದಿನ,
    .ಮಗು_class_iterate = submix_element_ಮಗು_iterate,
};

IAMF_ಕೂಡಿಸು_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixElement, element, s)

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFSubmixLayout, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption submix_layout_options[] = {
    { "layout_type", "Layout type", ಸ್ಥಾನಾಂತರ_2(layout_type), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS },
            AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS, AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL, FLAGS, .unit = "layout_type" },
        { "loudspeakers", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS }, .unit = "layout_type" },
        { "binaural",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL },     .unit = "layout_type" },
    { "sound_system", "Sound System", ಸ್ಥಾನಾಂತರ_2(sound_system), AV_OPT_TYPE_CHLAYOUT, { .str = ಖಾಲಿ }, 0, 0, FLAGS },
    { "integrated_loudness", "Integrated loudness", ಸ್ಥಾನಾಂತರ_2(integrated_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "digital_peak", "Digital peak", ಸ್ಥಾನಾಂತರ_2(digital_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "true_peak", "True peak", ಸ್ಥಾನಾಂತರ_2(true_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "dialog_anchored_loudness", "Anchored loudness (Dialog)", ಸ್ಥಾನಾಂತರ_2(dialogue_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "album_anchored_loudness", "Anchored loudness (Album)", ಸ್ಥಾನಾಂತರ_2(album_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass layout_class = {
    .class_name     = "AVIAMFSubmixLayout",
    .ಅಂಶ_name      = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ        = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option         = submix_layout_options,
};

IAMF_ಕೂಡಿಸು_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixLayout, layout, s)

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFSubmix, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption submix_presentation_options[] = {
    { "default_mix_gain", "Default mix gain", ಸ್ಥಾನಾಂತರ_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { ಖಾಲಿ },
};

ಸ್ಥಿರ ಶೂನ್ಯ *submix_presentation_ಮಗು_ಮುಂದಿನ(ಶೂನ್ಯ *obj, ಶೂನ್ಯ *prev)
{
    AVIAMFSubmix *sub_mix = obj;
    ಆದರೆ (!prev)
        ಹಿಂತಿರುಗಿ sub_mix->output_mix_config;

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass *submix_presentation_ಮಗು_iterate(ಶೂನ್ಯ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ಸ್ಥಿರಾಂಕ AVClass *ret = ಖಾಲಿ;

    ಆಯ್ಕೆ(i) {
    ಸ್ಥಿತಿ 0:
        ret = &element_class;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 1:
        ret = &layout_class;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
        ret = &param_definition_class;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }

    ಆದರೆ (ret)
        *opaque = (ಶೂನ್ಯ*)(i + 1);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass submix_class = {
    .class_name          = "AVIAMFSubmix",
    .ಅಂಶ_name           = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ             = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option              = submix_presentation_options,
    .ಮಗು_ಮುಂದಿನ          = submix_presentation_ಮಗು_ಮುಂದಿನ,
    .ಮಗು_class_iterate = submix_presentation_ಮಗು_iterate,
};

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(x) offsetof(AVIAMFMixPresentation, x)
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption mix_presentation_options[] = {
    { "annotations", "set annotations", ಸ್ಥಾನಾಂತರ_2(annotations), AV_OPT_TYPE_DICT, {.str = ಖಾಲಿ }, 0, 0, FLAGS },
    { ಖಾಲಿ },
};

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ಸ್ಥಾನಾಂತರ_2
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು FLAGS

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass *mix_presentation_ಮಗು_iterate(ಶೂನ್ಯ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ಸ್ಥಿರಾಂಕ AVClass *ret = ಖಾಲಿ;

    ಆದರೆ (!i)
        ret = &submix_class;

    ಆದರೆ (ret)
        *opaque = (ಶೂನ್ಯ*)(i + 1);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass mix_presentation_class = {
    .class_name          = "AVIAMFMixPresentation",
    .ಅಂಶ_name           = av_default_ಅಂಶ_name,
    .ಆವೃತ್ತಿ             = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .option              = mix_presentation_options,
    .ಮಗು_class_iterate = mix_presentation_ಮಗು_iterate,
};

ಸ್ಥಿರಾಂಕ AVClass *av_iamf_mix_presentation_get_class(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ &mix_presentation_class;
}

AVIAMFMixPresentation *av_iamf_mix_presentation_alloc(ಶೂನ್ಯ)
{
    AVIAMFMixPresentation *mix_presentation = av_mallocz(ಗಾತ್ರ(*mix_presentation));

    ಆದರೆ (mix_presentation) {
        mix_presentation->av_class = &mix_presentation_class;
        av_opt_ಗಣ_defaults(mix_presentation);
    }

    ಹಿಂತಿರುಗಿ mix_presentation;
}

IAMF_ಕೂಡಿಸು_FUNC_TEMPLATE(AVIAMFMixPresentation, mix_presentation, AVIAMFSubmix, submix, es)

ಶೂನ್ಯ av_iamf_mix_presentation_free(AVIAMFMixPresentation **pmix_presentation)
{
    AVIAMFMixPresentation *mix_presentation = *pmix_presentation;

    ಆದರೆ (!mix_presentation)
        ಹಿಂತಿರುಗಿ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < mix_presentation->nb_submixes; i++) {
        AVIAMFSubmix *sub_mix = mix_presentation->submixes[i];
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < sub_mix->nb_elements; j++) {
            AVIAMFSubmixElement *submix_element = sub_mix->elements[j];
            av_opt_free(submix_element);
            av_free(submix_element->element_mix_config);
            av_free(submix_element);
        }
        av_free(sub_mix->elements);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < sub_mix->nb_layouts; j++) {
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

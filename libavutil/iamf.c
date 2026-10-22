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

#define IAMF_ADD_FUNC_TEMPLATE(parent_type, parent_name, child_type, child_name, suffix)                   \
child_type *av_iamf_ ## parent_name ## _add_ ## child_name(parent_type *parent_name)                       \
{                                                                                                          \
    child_type **child_name ## suffix, *child_name;                                                        \
                                                                                                           \
    اگر (parent_name->nb_## child_name ## suffix == UINT_MAX)                                               \
        بازگشت پوچ;                                                                                       \
                                                                                                           \
    child_name ## suffix = av_realloc_array(parent_name->child_name ## suffix,                             \
                                            parent_name->nb_## child_name ## suffix + 1,                   \
                                            اندازه(*parent_name->child_name ## suffix));                   \
    اگر (!child_name ## suffix)                                                                             \
        بازگشت پوچ;                                                                                       \
                                                                                                           \
    parent_name->child_name ## suffix = child_name ## suffix;                                              \
                                                                                                           \
    child_name = parent_name->child_name ## suffix[parent_name->nb_## child_name ## suffix]                \
               = av_mallocz(اندازه(*child_name));                                                          \
    اگر (!child_name)                                                                                       \
        بازگشت پوچ;                                                                                       \
                                                                                                           \
    child_name->av_class = &child_name ## _class;                                                          \
    av_opt_set_defaults(child_name);                                                                       \
    parent_name->nb_## child_name ## suffix++;                                                             \
                                                                                                           \
    بازگشت child_name;                                                                                     \
}

#define FLAGS AV_OPT_FLAG_ENCODING_PARAM

//
// Param Definition
//
#define OFFSET(x) offsetof(AVIAMFMixGain, x)
ایستا ثابت AVOption mix_gain_options[] = {
    { "subblock_duration", "set subblock_duration", OFFSET(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "animation_type", "set animation_type", OFFSET(animation_type), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 2, FLAGS },
    { "start_point_value", "set start_point_value", OFFSET(start_point_مقدار), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "end_point_value", "set end_point_value", OFFSET(end_point_مقدار), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_value", "set control_point_value", OFFSET(control_point_مقدار), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_relative_time", "set control_point_relative_time", OFFSET(control_point_relative_time), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, 0.0, 1.0, FLAGS },
    { پوچ },
};

ایستا ثابت AVClass mix_gain_class = {
    .class_name     = "AVIAMFMixGain",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = mix_gain_options,
};

#undef OFFSET
#define OFFSET(x) offsetof(AVIAMFDemixingInfo, x)
ایستا ثابت AVOption demixing_info_options[] = {
    { "subblock_duration", "set subblock_duration", OFFSET(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "dmixp_mode", "set dmixp_mode", OFFSET(dmixp_mode), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 6, FLAGS },
    { پوچ },
};

ایستا ثابت AVClass demixing_info_class = {
    .class_name     = "AVIAMFDemixingInfo",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = demixing_info_options,
};

#undef OFFSET
#define OFFSET(x) offsetof(AVIAMFReconGain, x)
ایستا ثابت AVOption recon_gain_options[] = {
    { "subblock_duration", "set subblock_duration", OFFSET(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { پوچ },
};

ایستا ثابت AVClass recon_gain_class = {
    .class_name     = "AVIAMFReconGain",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = recon_gain_options,
};

#undef OFFSET
#define OFFSET(x) offsetof(AVIAMFParamDefinition, x)
ایستا ثابت AVOption param_definition_options[] = {
    { "parameter_id", "set parameter_id", OFFSET(parameter_id), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "parameter_rate", "set parameter_rate", OFFSET(parameter_rate), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "duration", "set duration", OFFSET(duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "constant_subblock_duration", "set constant_subblock_duration", OFFSET(constant_subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { پوچ },
};

ایستا ثابت AVClass *param_definition_child_iterate(تهی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = پوچ;

    انتخاب(i) {
    حالت AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        ret = &mix_gain_class;
        بشکن;
    حالت AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        ret = &demixing_info_class;
        بشکن;
    حالت AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        ret = &recon_gain_class;
        بشکن;
    پیشفرض:
        بشکن;
    }

    اگر (ret)
        *opaque = (تهی*)(i + 1);
    بازگشت ret;
}

ایستا ثابت AVClass param_definition_class = {
    .class_name          = "AVIAMFParamDefinition",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = param_definition_options,
    .child_class_iterate = param_definition_child_iterate,
};

ثابت AVClass *av_iamf_param_definition_get_class(تهی)
{
    بازگشت &param_definition_class;
}

AVIAMFParamDefinition *av_iamf_param_definition_alloc(شمارش AVIAMFParamDefinitionType type,
                                                      unsigned صحیح nb_subblocks, size_t *out_size)
{

    ساختار MixGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFMixGain m;
    };
    ساختار DemixStruct {
        AVIAMFParamDefinition p;
        AVIAMFDemixingInfo d;
    };
    ساختار ReconGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFReconGain r;
    };
    size_t subblocks_offset, subblock_size;
    size_t size;
    AVIAMFParamDefinition *par;

    انتخاب (type) {
    حالت AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        subblocks_offset = offsetof(ساختار MixGainStruct, m);
        subblock_size = اندازه(AVIAMFMixGain);
        بشکن;
    حالت AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        subblocks_offset = offsetof(ساختار DemixStruct, d);
        subblock_size = اندازه(AVIAMFDemixingInfo);
        بشکن;
    حالت AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        subblocks_offset = offsetof(ساختار ReconGainStruct, r);
        subblock_size = اندازه(AVIAMFReconGain);
        بشکن;
    پیشفرض:
        بازگشت پوچ;
    }

    size = subblocks_offset;
    اگر (nb_subblocks > (SIZE_MAX - size) / subblock_size)
        بازگشت پوچ;
    size += subblock_size * nb_subblocks;

    par = av_mallocz(size);
    اگر (!par)
        بازگشت پوچ;

    par->av_class = &param_definition_class;
    av_opt_set_defaults(par);

    par->type = type;
    par->nb_subblocks = nb_subblocks;
    par->subblock_size = subblock_size;
    par->subblocks_offset = subblocks_offset;

    برای (صحیح i = 0; i < nb_subblocks; i++) {
        تهی *subblock = av_iamf_param_definition_get_subblock(par, i);

        انتخاب (type) {
        حالت AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
            ((AVIAMFMixGain *)subblock)->av_class = &mix_gain_class;
            بشکن;
        حالت AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
            ((AVIAMFDemixingInfo *)subblock)->av_class = &demixing_info_class;
            بشکن;
        حالت AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
            ((AVIAMFReconGain *)subblock)->av_class = &recon_gain_class;
            بشکن;
        پیشفرض:
            av_assert0(0);
        }
    }

    اگر (out_size)
        *out_size = size;

    بازگشت par;
}

//
// Audio Element
//
ایستا ثابت AVOptionArrayDef demixing_matrix_def = { .size_max = (255 + 255) * 255, .sep = '|' };

#undef OFFSET
#define OFFSET(x) offsetof(AVIAMFLayer, x)
ایستا ثابت AVOption layer_options[] = {
    { "ch_layout", "set ch_layout", OFFSET(ch_layout), AV_OPT_TYPE_CHLAYOUT, {.str = پوچ }, 0, 0, FLAGS },
    { "flags", "set flags", OFFSET(flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, AV_IAMF_LAYER_FLAG_RECON_GAIN, FLAGS, .unit = "flags" },
            {"recon_gain",  "Recon gain is present", 0, AV_OPT_TYPE_CONST,
                {.i64 = AV_IAMF_LAYER_FLAG_RECON_GAIN }, INT_MIN, INT_MAX, FLAGS, .unit = "flags"},
    { "output_gain_flags", "set output_gain_flags", OFFSET(output_gain_flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, (1 << 6) - 1, FLAGS, .unit = "output_gain_flags" },
            {"FL",  "Left channel",            0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 5 }, INT_MIN, INT_MAX, FLAGS, .unit = "output_gain_flags"},
            {"FR",  "Right channel",           0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 4 }, INT_MIN, INT_MAX, FLAGS, .unit = "output_gain_flags"},
            {"BL",  "Left surround channel",   0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 3 }, INT_MIN, INT_MAX, FLAGS, .unit = "output_gain_flags"},
            {"BR",  "Right surround channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 2 }, INT_MIN, INT_MAX, FLAGS, .unit = "output_gain_flags"},
            {"TFL", "Left top front channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 1 }, INT_MIN, INT_MAX, FLAGS, .unit = "output_gain_flags"},
            {"TFR", "Right top front channel", 0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 0 }, INT_MIN, INT_MAX, FLAGS, .unit = "output_gain_flags"},
    { "output_gain", "set output_gain", OFFSET(output_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "ambisonics_mode", "set ambisonics_mode", OFFSET(ambisonics_mode), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_AMBISONICS_MODE_MONO },
            AV_IAMF_AMBISONICS_MODE_MONO, AV_IAMF_AMBISONICS_MODE_PROJECTION, FLAGS, .unit = "ambisonics_mode" },
        { "mono",       پوچ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_MODE_MONO },       .unit = "ambisonics_mode" },
        { "projection", پوچ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_MODE_PROJECTION }, .unit = "ambisonics_mode" },
    { "demixing_matrix", "set demixing_matrix", OFFSET(demixing_matrix), AV_OPT_TYPE_RATIONAL | AV_OPT_TYPE_FLAG_ARRAY,
            { .arr = &demixing_matrix_def }, -1.0, 1.0, FLAGS },
    { پوچ },
};

ایستا ثابت AVClass layer_class = {
    .class_name     = "AVIAMFLayer",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = layer_options,
};

#undef OFFSET
#define OFFSET(x) offsetof(AVIAMFAudioElement, x)
ایستا ثابت AVOption audio_element_options[] = {
    { "audio_element_type", "set audio_element_type", OFFSET(audio_element_type), AV_OPT_TYPE_INT,
            {.i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL },
            AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, FLAGS, .unit = "audio_element_type" },
        { "channel", پوچ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL }, .unit = "audio_element_type" },
        { "scene",   پوچ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE },   .unit = "audio_element_type" },
    { "default_w", "set default_w", OFFSET(default_w), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 10, FLAGS },
    { پوچ },
};

ایستا ثابت AVClass *audio_element_child_iterate(تهی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = پوچ;

    اگر (!i)
        ret = &layer_class;

    اگر (ret)
        *opaque = (تهی*)(i + 1);
    بازگشت ret;
}

ایستا ثابت AVClass audio_element_class = {
    .class_name          = "AVIAMFAudioElement",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = audio_element_options,
    .child_class_iterate = audio_element_child_iterate,
};

ثابت AVClass *av_iamf_audio_element_get_class(تهی)
{
    بازگشت &audio_element_class;
}

AVIAMFAudioElement *av_iamf_audio_element_alloc(تهی)
{
    AVIAMFAudioElement *audio_element = av_mallocz(اندازه(*audio_element));

    اگر (audio_element) {
        audio_element->av_class = &audio_element_class;
        av_opt_set_defaults(audio_element);
    }

    بازگشت audio_element;
}

IAMF_ADD_FUNC_TEMPLATE(AVIAMFAudioElement, audio_element, AVIAMFLayer, layer, s)

تهی av_iamf_audio_element_free(AVIAMFAudioElement **paudio_element)
{
    AVIAMFAudioElement *audio_element = *paudio_element;

    اگر (!audio_element)
        بازگشت;

    برای (صحیح i = 0; i < audio_element->nb_layers; i++) {
        AVIAMFLayer *layer = audio_element->layers[i];
        av_opt_free(layer);
        av_free(layer->demixing_matrix);
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
#undef OFFSET
#define OFFSET(x) offsetof(AVIAMFSubmixElement, x)
ایستا ثابت AVOption submix_element_options[] = {
    { "headphones_rendering_mode", "Headphones rendering mode", OFFSET(headphones_rendering_mode), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_HEADPHONES_MODE_STEREO },
            AV_IAMF_HEADPHONES_MODE_STEREO, AV_IAMF_HEADPHONES_MODE_BINAURAL, FLAGS, .unit = "headphones_rendering_mode" },
        { "stereo",   پوچ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_MODE_STEREO },   .unit = "headphones_rendering_mode" },
        { "binaural", پوچ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_MODE_BINAURAL }, .unit = "headphones_rendering_mode" },
    { "default_mix_gain", "Default mix gain", OFFSET(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "annotations", "Annotations", OFFSET(annotations), AV_OPT_TYPE_DICT, { .str = پوچ }, 0, 0, FLAGS },
    { پوچ },
};

ایستا تهی *submix_element_child_next(تهی *obj, تهی *prev)
{
    AVIAMFSubmixElement *submix_element = obj;
    اگر (!prev)
        بازگشت submix_element->element_mix_config;

    بازگشت پوچ;
}

ایستا ثابت AVClass *submix_element_child_iterate(تهی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = پوچ;

    اگر (!i)
        ret = &param_definition_class;

    اگر (ret)
        *opaque = (تهی*)(i + 1);
    بازگشت ret;
}

ایستا ثابت AVClass element_class = {
    .class_name          = "AVIAMFSubmixElement",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = submix_element_options,
    .child_next          = submix_element_child_next,
    .child_class_iterate = submix_element_child_iterate,
};

IAMF_ADD_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixElement, element, s)

#undef OFFSET
#define OFFSET(x) offsetof(AVIAMFSubmixLayout, x)
ایستا ثابت AVOption submix_layout_options[] = {
    { "layout_type", "Layout type", OFFSET(layout_type), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS },
            AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS, AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL, FLAGS, .unit = "layout_type" },
        { "loudspeakers", پوچ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS }, .unit = "layout_type" },
        { "binaural",     پوچ, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL },     .unit = "layout_type" },
    { "sound_system", "Sound System", OFFSET(sound_system), AV_OPT_TYPE_CHLAYOUT, { .str = پوچ }, 0, 0, FLAGS },
    { "integrated_loudness", "Integrated loudness", OFFSET(integrated_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "digital_peak", "Digital peak", OFFSET(digital_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "true_peak", "True peak", OFFSET(true_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "dialog_anchored_loudness", "Anchored loudness (Dialog)", OFFSET(dialogue_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "album_anchored_loudness", "Anchored loudness (Album)", OFFSET(album_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { پوچ },
};

ایستا ثابت AVClass layout_class = {
    .class_name     = "AVIAMFSubmixLayout",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = submix_layout_options,
};

IAMF_ADD_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixLayout, layout, s)

#undef OFFSET
#define OFFSET(x) offsetof(AVIAMFSubmix, x)
ایستا ثابت AVOption submix_presentation_options[] = {
    { "default_mix_gain", "Default mix gain", OFFSET(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { پوچ },
};

ایستا تهی *submix_presentation_child_next(تهی *obj, تهی *prev)
{
    AVIAMFSubmix *sub_mix = obj;
    اگر (!prev)
        بازگشت sub_mix->output_mix_config;

    بازگشت پوچ;
}

ایستا ثابت AVClass *submix_presentation_child_iterate(تهی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = پوچ;

    انتخاب(i) {
    حالت 0:
        ret = &element_class;
        بشکن;
    حالت 1:
        ret = &layout_class;
        بشکن;
    حالت 2:
        ret = &param_definition_class;
        بشکن;
    پیشفرض:
        بشکن;
    }

    اگر (ret)
        *opaque = (تهی*)(i + 1);
    بازگشت ret;
}

ایستا ثابت AVClass submix_class = {
    .class_name          = "AVIAMFSubmix",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = submix_presentation_options,
    .child_next          = submix_presentation_child_next,
    .child_class_iterate = submix_presentation_child_iterate,
};

#undef OFFSET
#define OFFSET(x) offsetof(AVIAMFMixPresentation, x)
ایستا ثابت AVOption mix_presentation_options[] = {
    { "annotations", "set annotations", OFFSET(annotations), AV_OPT_TYPE_DICT, {.str = پوچ }, 0, 0, FLAGS },
    { پوچ },
};

#undef OFFSET
#undef FLAGS

ایستا ثابت AVClass *mix_presentation_child_iterate(تهی **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = پوچ;

    اگر (!i)
        ret = &submix_class;

    اگر (ret)
        *opaque = (تهی*)(i + 1);
    بازگشت ret;
}

ایستا ثابت AVClass mix_presentation_class = {
    .class_name          = "AVIAMFMixPresentation",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = mix_presentation_options,
    .child_class_iterate = mix_presentation_child_iterate,
};

ثابت AVClass *av_iamf_mix_presentation_get_class(تهی)
{
    بازگشت &mix_presentation_class;
}

AVIAMFMixPresentation *av_iamf_mix_presentation_alloc(تهی)
{
    AVIAMFMixPresentation *mix_presentation = av_mallocz(اندازه(*mix_presentation));

    اگر (mix_presentation) {
        mix_presentation->av_class = &mix_presentation_class;
        av_opt_set_defaults(mix_presentation);
    }

    بازگشت mix_presentation;
}

IAMF_ADD_FUNC_TEMPLATE(AVIAMFMixPresentation, mix_presentation, AVIAMFSubmix, submix, es)

تهی av_iamf_mix_presentation_free(AVIAMFMixPresentation **pmix_presentation)
{
    AVIAMFMixPresentation *mix_presentation = *pmix_presentation;

    اگر (!mix_presentation)
        بازگشت;

    برای (صحیح i = 0; i < mix_presentation->nb_submixes; i++) {
        AVIAMFSubmix *sub_mix = mix_presentation->submixes[i];
        برای (صحیح j = 0; j < sub_mix->nb_elements; j++) {
            AVIAMFSubmixElement *submix_element = sub_mix->elements[j];
            av_opt_free(submix_element);
            av_free(submix_element->element_mix_config);
            av_free(submix_element);
        }
        av_free(sub_mix->elements);
        برای (صحیح j = 0; j < sub_mix->nb_layouts; j++) {
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

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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "iamf.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "opt.h"

#परिभाषय IAMF_सङ्कलय_FUNC_TEMPLATE(parent_type, parent_name, child_type, child_name, suffix)                   \
child_type *av_iamf_ ## parent_name ## सङ्कलय ## child_name(parent_type *parent_name)                       \
{                                                                                                          \
    child_type **child_name ## suffix, *child_name;                                                        \
                                                                                                           \
    यदि (parent_name->nb_## child_name ## suffix == UINT_MAX)                                               \
        प्रत्यागम रिक्त;                                                                                       \
                                                                                                           \
    child_name ## suffix = av_realloc_array(parent_name->child_name ## suffix,                             \
                                            parent_name->nb_## child_name ## suffix + 1,                   \
                                            परिमाण(*parent_name->child_name ## suffix));                   \
    यदि (!child_name ## suffix)                                                                             \
        प्रत्यागम रिक्त;                                                                                       \
                                                                                                           \
    parent_name->child_name ## suffix = child_name ## suffix;                                              \
                                                                                                           \
    child_name = parent_name->child_name ## suffix[parent_name->nb_## child_name ## suffix]                \
               = av_mallocz(परिमाण(*child_name));                                                          \
    यदि (!child_name)                                                                                       \
        प्रत्यागम रिक्त;                                                                                       \
                                                                                                           \
    child_name->av_class = &child_name ## _class;                                                          \
    av_opt_समुच्चयः_defaults(child_name);                                                                       \
    parent_name->nb_## child_name ## suffix++;                                                             \
                                                                                                           \
    प्रत्यागम child_name;                                                                                     \
}

#परिभाषय FLAGS AV_OPT_FLAG_ENCODING_PARAM

//
// Param Definition
//
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFMixGain, x)
स्थिर ध्रुव AVOption mix_gain_options[] = {
    { "subblock_duration", "set subblock_duration", विस्थापनम्_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "animation_type", "set animation_type", विस्थापनम्_2(animation_type), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 2, FLAGS },
    { "start_point_value", "set start_point_value", विस्थापनम्_2(start_point_मानम्), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "end_point_value", "set end_point_value", विस्थापनम्_2(अन्तः_point_मानम्), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_value", "set control_point_value", विस्थापनम्_2(control_point_मानम्), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_relative_time", "set control_point_relative_time", विस्थापनम्_2(control_point_relative_time), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, 0.0, 1.0, FLAGS },
    { रिक्त },
};

स्थिर ध्रुव AVClass mix_gain_class = {
    .class_name     = "AVIAMFMixGain",
    .item_name      = av_default_item_name,
    .संस्करणम्        = LIBAVUTIL_संस्करणम्_INT,
    .option         = mix_gain_options,
};

#अपरिभाषय विस्थापनम्_2
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFDemixingInfo, x)
स्थिर ध्रुव AVOption demixing_info_options[] = {
    { "subblock_duration", "set subblock_duration", विस्थापनम्_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "dmixp_mode", "set dmixp_mode", विस्थापनम्_2(dmixp_बहुलकम्), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 6, FLAGS },
    { रिक्त },
};

स्थिर ध्रुव AVClass demixing_info_class = {
    .class_name     = "AVIAMFDemixingInfo",
    .item_name      = av_default_item_name,
    .संस्करणम्        = LIBAVUTIL_संस्करणम्_INT,
    .option         = demixing_info_options,
};

#अपरिभाषय विस्थापनम्_2
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFReconGain, x)
स्थिर ध्रुव AVOption recon_gain_options[] = {
    { "subblock_duration", "set subblock_duration", विस्थापनम्_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { रिक्त },
};

स्थिर ध्रुव AVClass recon_gain_class = {
    .class_name     = "AVIAMFReconGain",
    .item_name      = av_default_item_name,
    .संस्करणम्        = LIBAVUTIL_संस्करणम्_INT,
    .option         = recon_gain_options,
};

#अपरिभाषय विस्थापनम्_2
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFParamDefinition, x)
स्थिर ध्रुव AVOption param_definition_options[] = {
    { "parameter_id", "set parameter_id", विस्थापनम्_2(parameter_id), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "parameter_rate", "set parameter_rate", विस्थापनम्_2(parameter_दरः), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "duration", "set duration", विस्थापनम्_2(duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "constant_subblock_duration", "set constant_subblock_duration", विस्थापनम्_2(constant_subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { रिक्त },
};

स्थिर ध्रुव AVClass *param_definition_child_iterate(शून्य **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ध्रुव AVClass *ret = रिक्त;

    विकल्प(i) {
    पक्ष AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        ret = &mix_gain_class;
        भङ्ग;
    पक्ष AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        ret = &demixing_info_class;
        भङ्ग;
    पक्ष AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        ret = &recon_gain_class;
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }

    यदि (ret)
        *opaque = (शून्य*)(i + 1);
    प्रत्यागम ret;
}

स्थिर ध्रुव AVClass param_definition_class = {
    .class_name          = "AVIAMFParamDefinition",
    .item_name           = av_default_item_name,
    .संस्करणम्             = LIBAVUTIL_संस्करणम्_INT,
    .option              = param_definition_options,
    .child_class_iterate = param_definition_child_iterate,
};

ध्रुव AVClass *av_iamf_param_definition_get_class(शून्य)
{
    प्रत्यागम &param_definition_class;
}

AVIAMFParamDefinition *av_iamf_param_definition_alloc(गणना AVIAMFParamDefinitionType type,
                                                      अचिह्नित पूर्णाङ्क nb_subblocks, size_t *बहिर्गमनम्_आकार)
{

    संरचना MixGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFMixGain m;
    };
    संरचना DemixStruct {
        AVIAMFParamDefinition p;
        AVIAMFDemixingInfo d;
    };
    संरचना ReconGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFReconGain r;
    };
    size_t subblocks_विस्थापनम्, subblock_आकार;
    size_t आकार;
    AVIAMFParamDefinition *par;

    विकल्प (type) {
    पक्ष AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        subblocks_विस्थापनम् = offsetof(संरचना MixGainStruct, m);
        subblock_आकार = परिमाण(AVIAMFMixGain);
        भङ्ग;
    पक्ष AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        subblocks_विस्थापनम् = offsetof(संरचना DemixStruct, d);
        subblock_आकार = परिमाण(AVIAMFDemixingInfo);
        भङ्ग;
    पक्ष AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        subblocks_विस्थापनम् = offsetof(संरचना ReconGainStruct, r);
        subblock_आकार = परिमाण(AVIAMFReconGain);
        भङ्ग;
    स्वभाव:
        प्रत्यागम रिक्त;
    }

    आकार = subblocks_विस्थापनम्;
    यदि (nb_subblocks > (SIZE_MAX - आकार) / subblock_आकार)
        प्रत्यागम रिक्त;
    आकार += subblock_आकार * nb_subblocks;

    par = av_mallocz(आकार);
    यदि (!par)
        प्रत्यागम रिक्त;

    par->av_class = &param_definition_class;
    av_opt_समुच्चयः_defaults(par);

    par->type = type;
    par->nb_subblocks = nb_subblocks;
    par->subblock_आकार = subblock_आकार;
    par->subblocks_विस्थापनम् = subblocks_विस्थापनम्;

    प्रति (पूर्णाङ्क i = 0; i < nb_subblocks; i++) {
        शून्य *subblock = av_iamf_param_definition_get_subblock(par, i);

        विकल्प (type) {
        पक्ष AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
            ((AVIAMFMixGain *)subblock)->av_class = &mix_gain_class;
            भङ्ग;
        पक्ष AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
            ((AVIAMFDemixingInfo *)subblock)->av_class = &demixing_info_class;
            भङ्ग;
        पक्ष AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
            ((AVIAMFReconGain *)subblock)->av_class = &recon_gain_class;
            भङ्ग;
        स्वभाव:
            av_assert0(0);
        }
    }

    यदि (बहिर्गमनम्_आकार)
        *बहिर्गमनम्_आकार = आकार;

    प्रत्यागम par;
}

//
// Audio Element
//
स्थिर ध्रुव AVOptionArrayDef demixing_matrix_def = { .आकार_max = (255 + 255) * 255, .sep = '|' };

#अपरिभाषय विस्थापनम्_2
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFLayer, x)
स्थिर ध्रुव AVOption layer_options[] = {
    { "ch_layout", "set ch_layout", विस्थापनम्_2(ch_layout), AV_OPT_TYPE_CHLAYOUT, {.str = रिक्त }, 0, 0, FLAGS },
    { "flags", "set flags", विस्थापनम्_2(flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, AV_IAMF_LAYER_FLAG_RECON_GAIN, FLAGS, .unit = "flags" },
            {"recon_gain",  "Recon gain is present", 0, AV_OPT_TYPE_CONST,
                {.i64 = AV_IAMF_LAYER_FLAG_RECON_GAIN }, INT_MIN, अधिकतम_पूर्णाङ्कः, FLAGS, .unit = "flags"},
    { "output_gain_flags", "set output_gain_flags", विस्थापनम्_2(output_gain_flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, (1 << 6) - 1, FLAGS, .unit = "output_gain_flags" },
            {"FL",  "Left channel",            0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 5 }, INT_MIN, अधिकतम_पूर्णाङ्कः, FLAGS, .unit = "output_gain_flags"},
            {"FR",  "Right channel",           0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 4 }, INT_MIN, अधिकतम_पूर्णाङ्कः, FLAGS, .unit = "output_gain_flags"},
            {"BL",  "Left surround channel",   0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 3 }, INT_MIN, अधिकतम_पूर्णाङ्कः, FLAGS, .unit = "output_gain_flags"},
            {"BR",  "Right surround channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 2 }, INT_MIN, अधिकतम_पूर्णाङ्कः, FLAGS, .unit = "output_gain_flags"},
            {"TFL", "Left top front channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 1 }, INT_MIN, अधिकतम_पूर्णाङ्कः, FLAGS, .unit = "output_gain_flags"},
            {"TFR", "Right top front channel", 0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 0 }, INT_MIN, अधिकतम_पूर्णाङ्कः, FLAGS, .unit = "output_gain_flags"},
    { "output_gain", "set output_gain", विस्थापनम्_2(output_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "ambisonics_mode", "set ambisonics_mode", विस्थापनम्_2(ambisonics_बहुलकम्), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_AMBISONICS_बहुलकम्_MONO },
            AV_IAMF_AMBISONICS_बहुलकम्_MONO, AV_IAMF_AMBISONICS_बहुलकम्_PROJECTION, FLAGS, .unit = "ambisonics_mode" },
        { "mono",       रिक्त, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_बहुलकम्_MONO },       .unit = "ambisonics_mode" },
        { "projection", रिक्त, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_बहुलकम्_PROJECTION }, .unit = "ambisonics_mode" },
    { "demixing_matrix", "set demixing_matrix", विस्थापनम्_2(demixing_matrix), AV_OPT_TYPE_RATIONAL | AV_OPT_TYPE_FLAG_ARRAY,
            { .arr = &demixing_matrix_def }, -1.0, 1.0, FLAGS },
    { रिक्त },
};

स्थिर ध्रुव AVClass layer_class = {
    .class_name     = "AVIAMFLayer",
    .item_name      = av_default_item_name,
    .संस्करणम्        = LIBAVUTIL_संस्करणम्_INT,
    .option         = layer_options,
};

#अपरिभाषय विस्थापनम्_2
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFAudioElement, x)
स्थिर ध्रुव AVOption audio_element_options[] = {
    { "audio_element_type", "set audio_element_type", विस्थापनम्_2(audio_element_type), AV_OPT_TYPE_INT,
            {.i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL },
            AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, FLAGS, .unit = "audio_element_type" },
        { "channel", रिक्त, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL }, .unit = "audio_element_type" },
        { "scene",   रिक्त, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE },   .unit = "audio_element_type" },
    { "default_w", "set default_w", विस्थापनम्_2(default_w), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 10, FLAGS },
    { रिक्त },
};

स्थिर ध्रुव AVClass *audio_element_child_iterate(शून्य **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ध्रुव AVClass *ret = रिक्त;

    यदि (!i)
        ret = &layer_class;

    यदि (ret)
        *opaque = (शून्य*)(i + 1);
    प्रत्यागम ret;
}

स्थिर ध्रुव AVClass audio_element_class = {
    .class_name          = "AVIAMFAudioElement",
    .item_name           = av_default_item_name,
    .संस्करणम्             = LIBAVUTIL_संस्करणम्_INT,
    .option              = audio_element_options,
    .child_class_iterate = audio_element_child_iterate,
};

ध्रुव AVClass *av_iamf_audio_element_get_class(शून्य)
{
    प्रत्यागम &audio_element_class;
}

AVIAMFAudioElement *av_iamf_audio_element_alloc(शून्य)
{
    AVIAMFAudioElement *audio_element = av_mallocz(परिमाण(*audio_element));

    यदि (audio_element) {
        audio_element->av_class = &audio_element_class;
        av_opt_समुच्चयः_defaults(audio_element);
    }

    प्रत्यागम audio_element;
}

IAMF_सङ्कलय_FUNC_TEMPLATE(AVIAMFAudioElement, audio_element, AVIAMFLayer, layer, s)

शून्य av_iamf_audio_element_free(AVIAMFAudioElement **paudio_element)
{
    AVIAMFAudioElement *audio_element = *paudio_element;

    यदि (!audio_element)
        प्रत्यागम;

    प्रति (पूर्णाङ्क i = 0; i < audio_element->nb_layers; i++) {
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
#अपरिभाषय विस्थापनम्_2
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFSubmixElement, x)
स्थिर ध्रुव AVOption submix_element_options[] = {
    { "headphones_rendering_mode", "Headphones rendering mode", विस्थापनम्_2(headphones_rendering_बहुलकम्), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_HEADPHONES_बहुलकम्_STEREO },
            AV_IAMF_HEADPHONES_बहुलकम्_STEREO, AV_IAMF_HEADPHONES_बहुलकम्_BINAURAL, FLAGS, .unit = "headphones_rendering_mode" },
        { "stereo",   रिक्त, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_बहुलकम्_STEREO },   .unit = "headphones_rendering_mode" },
        { "binaural", रिक्त, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_बहुलकम्_BINAURAL }, .unit = "headphones_rendering_mode" },
    { "default_mix_gain", "Default mix gain", विस्थापनम्_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "annotations", "Annotations", विस्थापनम्_2(annotations), AV_OPT_TYPE_DICT, { .str = रिक्त }, 0, 0, FLAGS },
    { रिक्त },
};

स्थिर शून्य *submix_element_child_अग्र(शून्य *obj, शून्य *पूर्व)
{
    AVIAMFSubmixElement *submix_element = obj;
    यदि (!पूर्व)
        प्रत्यागम submix_element->element_mix_config;

    प्रत्यागम रिक्त;
}

स्थिर ध्रुव AVClass *submix_element_child_iterate(शून्य **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ध्रुव AVClass *ret = रिक्त;

    यदि (!i)
        ret = &param_definition_class;

    यदि (ret)
        *opaque = (शून्य*)(i + 1);
    प्रत्यागम ret;
}

स्थिर ध्रुव AVClass element_class = {
    .class_name          = "AVIAMFSubmixElement",
    .item_name           = av_default_item_name,
    .संस्करणम्             = LIBAVUTIL_संस्करणम्_INT,
    .option              = submix_element_options,
    .child_अग्र          = submix_element_child_अग्र,
    .child_class_iterate = submix_element_child_iterate,
};

IAMF_सङ्कलय_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixElement, element, s)

#अपरिभाषय विस्थापनम्_2
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFSubmixLayout, x)
स्थिर ध्रुव AVOption submix_layout_options[] = {
    { "layout_type", "Layout type", विस्थापनम्_2(layout_type), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS },
            AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS, AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL, FLAGS, .unit = "layout_type" },
        { "loudspeakers", रिक्त, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS }, .unit = "layout_type" },
        { "binaural",     रिक्त, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL },     .unit = "layout_type" },
    { "sound_system", "Sound System", विस्थापनम्_2(sound_system), AV_OPT_TYPE_CHLAYOUT, { .str = रिक्त }, 0, 0, FLAGS },
    { "integrated_loudness", "Integrated loudness", विस्थापनम्_2(integrated_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "digital_peak", "Digital peak", विस्थापनम्_2(digital_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "true_peak", "True peak", विस्थापनम्_2(true_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "dialog_anchored_loudness", "Anchored loudness (Dialog)", विस्थापनम्_2(dialogue_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "album_anchored_loudness", "Anchored loudness (Album)", विस्थापनम्_2(album_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { रिक्त },
};

स्थिर ध्रुव AVClass layout_class = {
    .class_name     = "AVIAMFSubmixLayout",
    .item_name      = av_default_item_name,
    .संस्करणम्        = LIBAVUTIL_संस्करणम्_INT,
    .option         = submix_layout_options,
};

IAMF_सङ्कलय_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixLayout, layout, s)

#अपरिभाषय विस्थापनम्_2
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFSubmix, x)
स्थिर ध्रुव AVOption submix_presentation_options[] = {
    { "default_mix_gain", "Default mix gain", विस्थापनम्_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { रिक्त },
};

स्थिर शून्य *submix_presentation_child_अग्र(शून्य *obj, शून्य *पूर्व)
{
    AVIAMFSubmix *sub_mix = obj;
    यदि (!पूर्व)
        प्रत्यागम sub_mix->output_mix_config;

    प्रत्यागम रिक्त;
}

स्थिर ध्रुव AVClass *submix_presentation_child_iterate(शून्य **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ध्रुव AVClass *ret = रिक्त;

    विकल्प(i) {
    पक्ष 0:
        ret = &element_class;
        भङ्ग;
    पक्ष 1:
        ret = &layout_class;
        भङ्ग;
    पक्ष 2:
        ret = &param_definition_class;
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }

    यदि (ret)
        *opaque = (शून्य*)(i + 1);
    प्रत्यागम ret;
}

स्थिर ध्रुव AVClass submix_class = {
    .class_name          = "AVIAMFSubmix",
    .item_name           = av_default_item_name,
    .संस्करणम्             = LIBAVUTIL_संस्करणम्_INT,
    .option              = submix_presentation_options,
    .child_अग्र          = submix_presentation_child_अग्र,
    .child_class_iterate = submix_presentation_child_iterate,
};

#अपरिभाषय विस्थापनम्_2
#परिभाषय विस्थापनम्_2(x) offsetof(AVIAMFMixPresentation, x)
स्थिर ध्रुव AVOption mix_presentation_options[] = {
    { "annotations", "set annotations", विस्थापनम्_2(annotations), AV_OPT_TYPE_DICT, {.str = रिक्त }, 0, 0, FLAGS },
    { रिक्त },
};

#अपरिभाषय विस्थापनम्_2
#अपरिभाषय FLAGS

स्थिर ध्रुव AVClass *mix_presentation_child_iterate(शून्य **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ध्रुव AVClass *ret = रिक्त;

    यदि (!i)
        ret = &submix_class;

    यदि (ret)
        *opaque = (शून्य*)(i + 1);
    प्रत्यागम ret;
}

स्थिर ध्रुव AVClass mix_presentation_class = {
    .class_name          = "AVIAMFMixPresentation",
    .item_name           = av_default_item_name,
    .संस्करणम्             = LIBAVUTIL_संस्करणम्_INT,
    .option              = mix_presentation_options,
    .child_class_iterate = mix_presentation_child_iterate,
};

ध्रुव AVClass *av_iamf_mix_presentation_get_class(शून्य)
{
    प्रत्यागम &mix_presentation_class;
}

AVIAMFMixPresentation *av_iamf_mix_presentation_alloc(शून्य)
{
    AVIAMFMixPresentation *mix_presentation = av_mallocz(परिमाण(*mix_presentation));

    यदि (mix_presentation) {
        mix_presentation->av_class = &mix_presentation_class;
        av_opt_समुच्चयः_defaults(mix_presentation);
    }

    प्रत्यागम mix_presentation;
}

IAMF_सङ्कलय_FUNC_TEMPLATE(AVIAMFMixPresentation, mix_presentation, AVIAMFSubmix, submix, es)

शून्य av_iamf_mix_presentation_free(AVIAMFMixPresentation **pmix_presentation)
{
    AVIAMFMixPresentation *mix_presentation = *pmix_presentation;

    यदि (!mix_presentation)
        प्रत्यागम;

    प्रति (पूर्णाङ्क i = 0; i < mix_presentation->nb_submixes; i++) {
        AVIAMFSubmix *sub_mix = mix_presentation->submixes[i];
        प्रति (पूर्णाङ्क j = 0; j < sub_mix->nb_elements; j++) {
            AVIAMFSubmixElement *submix_element = sub_mix->elements[j];
            av_opt_free(submix_element);
            av_free(submix_element->element_mix_config);
            av_free(submix_element);
        }
        av_free(sub_mix->elements);
        प्रति (पूर्णाङ्क j = 0; j < sub_mix->nb_layouts; j++) {
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

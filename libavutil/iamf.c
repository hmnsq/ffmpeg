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

#समावेश <limits.h>
#समावेश <stddef.h>
#समावेश <stdint.h>

#समावेश "avassert.h"
#समावेश "error.h"
#समावेश "iamf.h"
#समावेश "log.h"
#समावेश "mem.h"
#समावेश "opt.h"

#घोषणा IAMF_ADD_FUNC_TEMPLATE(parent_type, parent_name, child_type, child_name, suffix)                   \
child_type *av_iamf_ ## parent_name ## _add_ ## child_name(parent_type *parent_name)                       \
{                                                                                                          \
    child_type **child_name ## suffix, *child_name;                                                        \
                                                                                                           \
    अगर (parent_name->nb_## child_name ## suffix == अच_पूर्णांक_उच्च)                                               \
        वापस शून्य;                                                                                       \
                                                                                                           \
    child_name ## suffix = av_realloc_array(parent_name->child_name ## suffix,                             \
                                            parent_name->nb_## child_name ## suffix + 1,                   \
                                            माप(*parent_name->child_name ## suffix));                   \
    अगर (!child_name ## suffix)                                                                             \
        वापस शून्य;                                                                                       \
                                                                                                           \
    parent_name->child_name ## suffix = child_name ## suffix;                                              \
                                                                                                           \
    child_name = parent_name->child_name ## suffix[parent_name->nb_## child_name ## suffix]                \
               = av_mallocz(माप(*child_name));                                                          \
    अगर (!child_name)                                                                                       \
        वापस शून्य;                                                                                       \
                                                                                                           \
    child_name->av_class = &child_name ## _class;                                                          \
    av_opt_set_defaults(child_name);                                                                       \
    parent_name->nb_## child_name ## suffix++;                                                             \
                                                                                                           \
    वापस child_name;                                                                                     \
}

#घोषणा FLAGS AV_OPT_FLAG_ENCODING_PARAM

//
// Param Definition
//
#घोषणा OFFSET(x) दुरत्व(AVIAMFMixGain, x)
अटल स्थिर AVOption mix_gain_options[] = {
    { "subblock_duration", "set subblock_duration", OFFSET(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, अच_पूर्णांक_उच्च, FLAGS },
    { "animation_type", "set animation_type", OFFSET(animation_type), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 2, FLAGS },
    { "start_point_value", "set start_point_value", OFFSET(start_point_मूल्य), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "end_point_value", "set end_point_value", OFFSET(end_point_मूल्य), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_value", "set control_point_value", OFFSET(control_point_मूल्य), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_relative_time", "set control_point_relative_time", OFFSET(control_point_relative_time), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, 0.0, 1.0, FLAGS },
    { शून्य },
};

अटल स्थिर AVClass mix_gain_class = {
    .class_name     = "AVIAMFMixGain",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = mix_gain_options,
};

#अघोषित OFFSET
#घोषणा OFFSET(x) दुरत्व(AVIAMFDemixingInfo, x)
अटल स्थिर AVOption demixing_info_options[] = {
    { "subblock_duration", "set subblock_duration", OFFSET(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, अच_पूर्णांक_उच्च, FLAGS },
    { "dmixp_mode", "set dmixp_mode", OFFSET(dmixp_mode), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 6, FLAGS },
    { शून्य },
};

अटल स्थिर AVClass demixing_info_class = {
    .class_name     = "AVIAMFDemixingInfo",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = demixing_info_options,
};

#अघोषित OFFSET
#घोषणा OFFSET(x) दुरत्व(AVIAMFReconGain, x)
अटल स्थिर AVOption recon_gain_options[] = {
    { "subblock_duration", "set subblock_duration", OFFSET(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, अच_पूर्णांक_उच्च, FLAGS },
    { शून्य },
};

अटल स्थिर AVClass recon_gain_class = {
    .class_name     = "AVIAMFReconGain",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = recon_gain_options,
};

#अघोषित OFFSET
#घोषणा OFFSET(x) दुरत्व(AVIAMFParamDefinition, x)
अटल स्थिर AVOption param_definition_options[] = {
    { "parameter_id", "set parameter_id", OFFSET(parameter_id), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, अच_पूर्णांक_उच्च, FLAGS },
    { "parameter_rate", "set parameter_rate", OFFSET(parameter_rate), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, अच_पूर्णांक_उच्च, FLAGS },
    { "duration", "set duration", OFFSET(duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, अच_पूर्णांक_उच्च, FLAGS },
    { "constant_subblock_duration", "set constant_subblock_duration", OFFSET(constant_subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, अच_पूर्णांक_उच्च, FLAGS },
    { शून्य },
};

अटल स्थिर AVClass *param_definition_child_iterate(व्योम **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    स्थिर AVClass *ret = शून्य;

    चयन(i) {
    हाल AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        ret = &mix_gain_class;
        अवरोध;
    हाल AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        ret = &demixing_info_class;
        अवरोध;
    हाल AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        ret = &recon_gain_class;
        अवरोध;
    शेष:
        अवरोध;
    }

    अगर (ret)
        *opaque = (व्योम*)(i + 1);
    वापस ret;
}

अटल स्थिर AVClass param_definition_class = {
    .class_name          = "AVIAMFParamDefinition",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = param_definition_options,
    .child_class_iterate = param_definition_child_iterate,
};

स्थिर AVClass *av_iamf_param_definition_get_class(व्योम)
{
    वापस &param_definition_class;
}

AVIAMFParamDefinition *av_iamf_param_definition_alloc(क्रमागत AVIAMFParamDefinitionType type,
                                                      अचिन्हित पूर्णांक nb_subblocks, माप_प्रकार *out_आकार)
{

    काष्ठा MixGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFMixGain m;
    };
    काष्ठा DemixStruct {
        AVIAMFParamDefinition p;
        AVIAMFDemixingInfo d;
    };
    काष्ठा ReconGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFReconGain r;
    };
    माप_प्रकार subblocks_offset, subblock_आकार;
    माप_प्रकार आकार;
    AVIAMFParamDefinition *par;

    चयन (type) {
    हाल AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        subblocks_offset = दुरत्व(काष्ठा MixGainStruct, m);
        subblock_आकार = माप(AVIAMFMixGain);
        अवरोध;
    हाल AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        subblocks_offset = दुरत्व(काष्ठा DemixStruct, d);
        subblock_आकार = माप(AVIAMFDemixingInfo);
        अवरोध;
    हाल AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        subblocks_offset = दुरत्व(काष्ठा ReconGainStruct, r);
        subblock_आकार = माप(AVIAMFReconGain);
        अवरोध;
    शेष:
        वापस शून्य;
    }

    आकार = subblocks_offset;
    अगर (nb_subblocks > (SIZE_MAX - आकार) / subblock_आकार)
        वापस शून्य;
    आकार += subblock_आकार * nb_subblocks;

    par = av_mallocz(आकार);
    अगर (!par)
        वापस शून्य;

    par->av_class = &param_definition_class;
    av_opt_set_defaults(par);

    par->type = type;
    par->nb_subblocks = nb_subblocks;
    par->subblock_आकार = subblock_आकार;
    par->subblocks_offset = subblocks_offset;

    क्रम (पूर्णांक i = 0; i < nb_subblocks; i++) {
        व्योम *subblock = av_iamf_param_definition_get_subblock(par, i);

        चयन (type) {
        हाल AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
            ((AVIAMFMixGain *)subblock)->av_class = &mix_gain_class;
            अवरोध;
        हाल AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
            ((AVIAMFDemixingInfo *)subblock)->av_class = &demixing_info_class;
            अवरोध;
        हाल AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
            ((AVIAMFReconGain *)subblock)->av_class = &recon_gain_class;
            अवरोध;
        शेष:
            av_assert0(0);
        }
    }

    अगर (out_आकार)
        *out_आकार = आकार;

    वापस par;
}

//
// Audio Element
//
अटल स्थिर AVOptionArrayDef demixing_matrix_def = { .आकार_max = (255 + 255) * 255, .sep = '|' };

#अघोषित OFFSET
#घोषणा OFFSET(x) दुरत्व(AVIAMFLayer, x)
अटल स्थिर AVOption layer_options[] = {
    { "ch_layout", "set ch_layout", OFFSET(ch_layout), AV_OPT_TYPE_CHLAYOUT, {.str = शून्य }, 0, 0, FLAGS },
    { "flags", "set flags", OFFSET(flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, AV_IAMF_LAYER_FLAG_RECON_GAIN, FLAGS, .unit = "flags" },
            {"recon_gain",  "Recon gain is present", 0, AV_OPT_TYPE_CONST,
                {.i64 = AV_IAMF_LAYER_FLAG_RECON_GAIN }, पूर्णांक_न्यून, पूर्णांक_उच्च, FLAGS, .unit = "flags"},
    { "output_gain_flags", "set output_gain_flags", OFFSET(output_gain_flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, (1 << 6) - 1, FLAGS, .unit = "output_gain_flags" },
            {"FL",  "Left channel",            0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 5 }, पूर्णांक_न्यून, पूर्णांक_उच्च, FLAGS, .unit = "output_gain_flags"},
            {"FR",  "Right channel",           0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 4 }, पूर्णांक_न्यून, पूर्णांक_उच्च, FLAGS, .unit = "output_gain_flags"},
            {"BL",  "Left surround channel",   0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 3 }, पूर्णांक_न्यून, पूर्णांक_उच्च, FLAGS, .unit = "output_gain_flags"},
            {"BR",  "Right surround channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 2 }, पूर्णांक_न्यून, पूर्णांक_उच्च, FLAGS, .unit = "output_gain_flags"},
            {"TFL", "Left top front channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 1 }, पूर्णांक_न्यून, पूर्णांक_उच्च, FLAGS, .unit = "output_gain_flags"},
            {"TFR", "Right top front channel", 0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 0 }, पूर्णांक_न्यून, पूर्णांक_उच्च, FLAGS, .unit = "output_gain_flags"},
    { "output_gain", "set output_gain", OFFSET(output_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "ambisonics_mode", "set ambisonics_mode", OFFSET(ambisonics_mode), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_AMBISONICS_MODE_MONO },
            AV_IAMF_AMBISONICS_MODE_MONO, AV_IAMF_AMBISONICS_MODE_PROJECTION, FLAGS, .unit = "ambisonics_mode" },
        { "mono",       शून्य, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_MODE_MONO },       .unit = "ambisonics_mode" },
        { "projection", शून्य, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_MODE_PROJECTION }, .unit = "ambisonics_mode" },
    { "demixing_matrix", "set demixing_matrix", OFFSET(demixing_matrix), AV_OPT_TYPE_RATIONAL | AV_OPT_TYPE_FLAG_ARRAY,
            { .arr = &demixing_matrix_def }, -1.0, 1.0, FLAGS },
    { शून्य },
};

अटल स्थिर AVClass layer_class = {
    .class_name     = "AVIAMFLayer",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = layer_options,
};

#अघोषित OFFSET
#घोषणा OFFSET(x) दुरत्व(AVIAMFAudioElement, x)
अटल स्थिर AVOption audio_element_options[] = {
    { "audio_element_type", "set audio_element_type", OFFSET(audio_element_type), AV_OPT_TYPE_INT,
            {.i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL },
            AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, FLAGS, .unit = "audio_element_type" },
        { "channel", शून्य, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL }, .unit = "audio_element_type" },
        { "scene",   शून्य, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE },   .unit = "audio_element_type" },
    { "default_w", "set default_w", OFFSET(default_w), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 10, FLAGS },
    { शून्य },
};

अटल स्थिर AVClass *audio_element_child_iterate(व्योम **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    स्थिर AVClass *ret = शून्य;

    अगर (!i)
        ret = &layer_class;

    अगर (ret)
        *opaque = (व्योम*)(i + 1);
    वापस ret;
}

अटल स्थिर AVClass audio_element_class = {
    .class_name          = "AVIAMFAudioElement",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = audio_element_options,
    .child_class_iterate = audio_element_child_iterate,
};

स्थिर AVClass *av_iamf_audio_element_get_class(व्योम)
{
    वापस &audio_element_class;
}

AVIAMFAudioElement *av_iamf_audio_element_alloc(व्योम)
{
    AVIAMFAudioElement *audio_element = av_mallocz(माप(*audio_element));

    अगर (audio_element) {
        audio_element->av_class = &audio_element_class;
        av_opt_set_defaults(audio_element);
    }

    वापस audio_element;
}

IAMF_ADD_FUNC_TEMPLATE(AVIAMFAudioElement, audio_element, AVIAMFLayer, layer, s)

व्योम av_iamf_audio_element_free(AVIAMFAudioElement **paudio_element)
{
    AVIAMFAudioElement *audio_element = *paudio_element;

    अगर (!audio_element)
        वापस;

    क्रम (पूर्णांक i = 0; i < audio_element->nb_layers; i++) {
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
#अघोषित OFFSET
#घोषणा OFFSET(x) दुरत्व(AVIAMFSubmixElement, x)
अटल स्थिर AVOption submix_element_options[] = {
    { "headphones_rendering_mode", "Headphones rendering mode", OFFSET(headphones_rendering_mode), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_HEADPHONES_MODE_STEREO },
            AV_IAMF_HEADPHONES_MODE_STEREO, AV_IAMF_HEADPHONES_MODE_BINAURAL, FLAGS, .unit = "headphones_rendering_mode" },
        { "stereo",   शून्य, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_MODE_STEREO },   .unit = "headphones_rendering_mode" },
        { "binaural", शून्य, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_MODE_BINAURAL }, .unit = "headphones_rendering_mode" },
    { "default_mix_gain", "Default mix gain", OFFSET(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "annotations", "Annotations", OFFSET(annotations), AV_OPT_TYPE_DICT, { .str = शून्य }, 0, 0, FLAGS },
    { शून्य },
};

अटल व्योम *submix_element_child_अग्र(व्योम *obj, व्योम *पूर्व)
{
    AVIAMFSubmixElement *submix_element = obj;
    अगर (!पूर्व)
        वापस submix_element->element_mix_config;

    वापस शून्य;
}

अटल स्थिर AVClass *submix_element_child_iterate(व्योम **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    स्थिर AVClass *ret = शून्य;

    अगर (!i)
        ret = &param_definition_class;

    अगर (ret)
        *opaque = (व्योम*)(i + 1);
    वापस ret;
}

अटल स्थिर AVClass element_class = {
    .class_name          = "AVIAMFSubmixElement",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = submix_element_options,
    .child_अग्र          = submix_element_child_अग्र,
    .child_class_iterate = submix_element_child_iterate,
};

IAMF_ADD_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixElement, element, s)

#अघोषित OFFSET
#घोषणा OFFSET(x) दुरत्व(AVIAMFSubmixLayout, x)
अटल स्थिर AVOption submix_layout_options[] = {
    { "layout_type", "Layout type", OFFSET(layout_type), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS },
            AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS, AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL, FLAGS, .unit = "layout_type" },
        { "loudspeakers", शून्य, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS }, .unit = "layout_type" },
        { "binaural",     शून्य, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL },     .unit = "layout_type" },
    { "sound_system", "Sound System", OFFSET(sound_system), AV_OPT_TYPE_CHLAYOUT, { .str = शून्य }, 0, 0, FLAGS },
    { "integrated_loudness", "Integrated loudness", OFFSET(integrated_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "digital_peak", "Digital peak", OFFSET(digital_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "true_peak", "True peak", OFFSET(true_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "dialog_anchored_loudness", "Anchored loudness (Dialog)", OFFSET(dialogue_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "album_anchored_loudness", "Anchored loudness (Album)", OFFSET(album_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { शून्य },
};

अटल स्थिर AVClass layout_class = {
    .class_name     = "AVIAMFSubmixLayout",
    .item_name      = av_default_item_name,
    .version        = LIBAVUTIL_VERSION_INT,
    .option         = submix_layout_options,
};

IAMF_ADD_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixLayout, layout, s)

#अघोषित OFFSET
#घोषणा OFFSET(x) दुरत्व(AVIAMFSubmix, x)
अटल स्थिर AVOption submix_presentation_options[] = {
    { "default_mix_gain", "Default mix gain", OFFSET(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { शून्य },
};

अटल व्योम *submix_presentation_child_अग्र(व्योम *obj, व्योम *पूर्व)
{
    AVIAMFSubmix *sub_mix = obj;
    अगर (!पूर्व)
        वापस sub_mix->output_mix_config;

    वापस शून्य;
}

अटल स्थिर AVClass *submix_presentation_child_iterate(व्योम **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    स्थिर AVClass *ret = शून्य;

    चयन(i) {
    हाल 0:
        ret = &element_class;
        अवरोध;
    हाल 1:
        ret = &layout_class;
        अवरोध;
    हाल 2:
        ret = &param_definition_class;
        अवरोध;
    शेष:
        अवरोध;
    }

    अगर (ret)
        *opaque = (व्योम*)(i + 1);
    वापस ret;
}

अटल स्थिर AVClass submix_class = {
    .class_name          = "AVIAMFSubmix",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = submix_presentation_options,
    .child_अग्र          = submix_presentation_child_अग्र,
    .child_class_iterate = submix_presentation_child_iterate,
};

#अघोषित OFFSET
#घोषणा OFFSET(x) दुरत्व(AVIAMFMixPresentation, x)
अटल स्थिर AVOption mix_presentation_options[] = {
    { "annotations", "set annotations", OFFSET(annotations), AV_OPT_TYPE_DICT, {.str = शून्य }, 0, 0, FLAGS },
    { शून्य },
};

#अघोषित OFFSET
#अघोषित FLAGS

अटल स्थिर AVClass *mix_presentation_child_iterate(व्योम **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    स्थिर AVClass *ret = शून्य;

    अगर (!i)
        ret = &submix_class;

    अगर (ret)
        *opaque = (व्योम*)(i + 1);
    वापस ret;
}

अटल स्थिर AVClass mix_presentation_class = {
    .class_name          = "AVIAMFMixPresentation",
    .item_name           = av_default_item_name,
    .version             = LIBAVUTIL_VERSION_INT,
    .option              = mix_presentation_options,
    .child_class_iterate = mix_presentation_child_iterate,
};

स्थिर AVClass *av_iamf_mix_presentation_get_class(व्योम)
{
    वापस &mix_presentation_class;
}

AVIAMFMixPresentation *av_iamf_mix_presentation_alloc(व्योम)
{
    AVIAMFMixPresentation *mix_presentation = av_mallocz(माप(*mix_presentation));

    अगर (mix_presentation) {
        mix_presentation->av_class = &mix_presentation_class;
        av_opt_set_defaults(mix_presentation);
    }

    वापस mix_presentation;
}

IAMF_ADD_FUNC_TEMPLATE(AVIAMFMixPresentation, mix_presentation, AVIAMFSubmix, submix, es)

व्योम av_iamf_mix_presentation_free(AVIAMFMixPresentation **pmix_presentation)
{
    AVIAMFMixPresentation *mix_presentation = *pmix_presentation;

    अगर (!mix_presentation)
        वापस;

    क्रम (पूर्णांक i = 0; i < mix_presentation->nb_submixes; i++) {
        AVIAMFSubmix *sub_mix = mix_presentation->submixes[i];
        क्रम (पूर्णांक j = 0; j < sub_mix->nb_elements; j++) {
            AVIAMFSubmixElement *submix_element = sub_mix->elements[j];
            av_opt_free(submix_element);
            av_free(submix_element->element_mix_config);
            av_free(submix_element);
        }
        av_free(sub_mix->elements);
        क्रम (पूर्णांक j = 0; j < sub_mix->nb_layouts; j++) {
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

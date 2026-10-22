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

#ضمن <limits.h>
#ضمن <stddef.h>
#ضمن <stdint.h>

#ضمن "avassert.h"
#ضمن "error.h"
#ضمن "iamf.h"
#ضمن "log.h"
#ضمن "mem.h"
#ضمن "opt.h"

#وصف_ڪريو IAMF_جوڙيو_FUNC_TEMPLATE(والد_type, والد_name, ٻار_type, ٻار_name, suffix)                   \
ٻار_type *av_iamf_ ## والد_name ## جوڙيو ## ٻار_name(والد_type *والد_name)                       \
{                                                                                                          \
    ٻار_type **ٻار_name ## suffix, *ٻار_name;                                                        \
                                                                                                           \
    إذا (والد_name->nb_## ٻار_name ## suffix == UINT_MAX)                                               \
        أرجع عدم;                                                                                       \
                                                                                                           \
    ٻار_name ## suffix = av_realloc_array(والد_name->ٻار_name ## suffix,                             \
                                            والد_name->nb_## ٻار_name ## suffix + 1,                   \
                                            حجم(*والد_name->ٻار_name ## suffix));                   \
    إذا (!ٻار_name ## suffix)                                                                             \
        أرجع عدم;                                                                                       \
                                                                                                           \
    والد_name->ٻار_name ## suffix = ٻار_name ## suffix;                                              \
                                                                                                           \
    ٻار_name = والد_name->ٻار_name ## suffix[والد_name->nb_## ٻار_name ## suffix]                \
               = av_mallocz(حجم(*ٻار_name));                                                          \
    إذا (!ٻار_name)                                                                                       \
        أرجع عدم;                                                                                       \
                                                                                                           \
    ٻار_name->av_class = &ٻار_name ## _class;                                                          \
    av_opt_سيٽ_defaults(ٻار_name);                                                                       \
    والد_name->nb_## ٻار_name ## suffix++;                                                             \
                                                                                                           \
    أرجع ٻار_name;                                                                                     \
}

#وصف_ڪريو FLAGS AV_OPT_FLAG_ENCODING_PARAM

//
// Param Definition
//
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFMixGain, x)
ساكن ثابت AVOption mix_gain_options[] = {
    { "subblock_duration", "set subblock_duration", وٿي_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "animation_type", "set animation_type", وٿي_2(animation_type), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 2, FLAGS },
    { "start_point_value", "set start_point_value", وٿي_2(شروعات_نقطو_قدر), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "end_point_value", "set end_point_value", وٿي_2(پڇاڙي_نقطو_قدر), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_value", "set control_point_value", وٿي_2(control_نقطو_قدر), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, -128.0, 128.0, FLAGS },
    { "control_point_relative_time", "set control_point_relative_time", وٿي_2(control_نقطو_relative_وقت), AV_OPT_TYPE_RATIONAL, {.dbl = 0 }, 0.0, 1.0, FLAGS },
    { عدم },
};

ساكن ثابت AVClass mix_gain_class = {
    .class_name     = "AVIAMFMixGain",
    .شي_name      = av_default_شي_name,
    .نسخو        = LIBAVUTIL_نسخو_INT,
    .option         = mix_gain_options,
};

#وصف_رد وٿي_2
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFDemixingInfo, x)
ساكن ثابت AVOption demixing_info_options[] = {
    { "subblock_duration", "set subblock_duration", وٿي_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { "dmixp_mode", "set dmixp_mode", وٿي_2(dmixp_گهڻائي), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 6, FLAGS },
    { عدم },
};

ساكن ثابت AVClass demixing_info_class = {
    .class_name     = "AVIAMFDemixingInfo",
    .شي_name      = av_default_شي_name,
    .نسخو        = LIBAVUTIL_نسخو_INT,
    .option         = demixing_info_options,
};

#وصف_رد وٿي_2
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFReconGain, x)
ساكن ثابت AVOption recon_gain_options[] = {
    { "subblock_duration", "set subblock_duration", وٿي_2(subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 1 }, 1, UINT_MAX, FLAGS },
    { عدم },
};

ساكن ثابت AVClass recon_gain_class = {
    .class_name     = "AVIAMFReconGain",
    .شي_name      = av_default_شي_name,
    .نسخو        = LIBAVUTIL_نسخو_INT,
    .option         = recon_gain_options,
};

#وصف_رد وٿي_2
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFParamDefinition, x)
ساكن ثابت AVOption param_definition_options[] = {
    { "parameter_id", "set parameter_id", وٿي_2(parameter_id), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "parameter_rate", "set parameter_rate", وٿي_2(parameter_شرح), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "duration", "set duration", وٿي_2(duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { "constant_subblock_duration", "set constant_subblock_duration", وٿي_2(constant_subblock_duration), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, UINT_MAX, FLAGS },
    { عدم },
};

ساكن ثابت AVClass *param_definition_ٻار_iterate(فراغ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = عدم;

    بدل(i) {
    حالة AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        ret = &mix_gain_class;
        اكسر;
    حالة AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        ret = &demixing_info_class;
        اكسر;
    حالة AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        ret = &recon_gain_class;
        اكسر;
    افتراضي:
        اكسر;
    }

    إذا (ret)
        *opaque = (فراغ*)(i + 1);
    أرجع ret;
}

ساكن ثابت AVClass param_definition_class = {
    .class_name          = "AVIAMFParamDefinition",
    .شي_name           = av_default_شي_name,
    .نسخو             = LIBAVUTIL_نسخو_INT,
    .option              = param_definition_options,
    .ٻار_class_iterate = param_definition_ٻار_iterate,
};

ثابت AVClass *av_iamf_param_definition_get_class(فراغ)
{
    أرجع &param_definition_class;
}

AVIAMFParamDefinition *av_iamf_param_definition_alloc(تعداد AVIAMFParamDefinitionType type,
                                                      بنانشان صحيح nb_subblocks, size_t *ٻاهريون_سائيز)
{

    بنية MixGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFMixGain m;
    };
    بنية DemixStruct {
        AVIAMFParamDefinition p;
        AVIAMFDemixingInfo d;
    };
    بنية ReconGainStruct {
        AVIAMFParamDefinition p;
        AVIAMFReconGain r;
    };
    size_t subblocks_وٿي, subblock_سائيز;
    size_t سائيز;
    AVIAMFParamDefinition *par;

    بدل (type) {
    حالة AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
        subblocks_وٿي = offsetof(بنية MixGainStruct, m);
        subblock_سائيز = حجم(AVIAMFMixGain);
        اكسر;
    حالة AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
        subblocks_وٿي = offsetof(بنية DemixStruct, d);
        subblock_سائيز = حجم(AVIAMFDemixingInfo);
        اكسر;
    حالة AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
        subblocks_وٿي = offsetof(بنية ReconGainStruct, r);
        subblock_سائيز = حجم(AVIAMFReconGain);
        اكسر;
    افتراضي:
        أرجع عدم;
    }

    سائيز = subblocks_وٿي;
    إذا (nb_subblocks > (SIZE_MAX - سائيز) / subblock_سائيز)
        أرجع عدم;
    سائيز += subblock_سائيز * nb_subblocks;

    par = av_mallocz(سائيز);
    إذا (!par)
        أرجع عدم;

    par->av_class = &param_definition_class;
    av_opt_سيٽ_defaults(par);

    par->type = type;
    par->nb_subblocks = nb_subblocks;
    par->subblock_سائيز = subblock_سائيز;
    par->subblocks_وٿي = subblocks_وٿي;

    لكل (صحيح i = 0; i < nb_subblocks; i++) {
        فراغ *subblock = av_iamf_param_definition_get_subblock(par, i);

        بدل (type) {
        حالة AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN:
            ((AVIAMFMixGain *)subblock)->av_class = &mix_gain_class;
            اكسر;
        حالة AV_IAMF_PARAMETER_DEFINITION_DEMIXING:
            ((AVIAMFDemixingInfo *)subblock)->av_class = &demixing_info_class;
            اكسر;
        حالة AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN:
            ((AVIAMFReconGain *)subblock)->av_class = &recon_gain_class;
            اكسر;
        افتراضي:
            av_assert0(0);
        }
    }

    إذا (ٻاهريون_سائيز)
        *ٻاهريون_سائيز = سائيز;

    أرجع par;
}

//
// Audio Element
//
ساكن ثابت AVOptionArrayDef demixing_ميٽرڪس_def = { .سائيز_max = (255 + 255) * 255, .sep = '|' };

#وصف_رد وٿي_2
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFLayer, x)
ساكن ثابت AVOption layer_options[] = {
    { "ch_layout", "set ch_layout", وٿي_2(ch_layout), AV_OPT_TYPE_CHLAYOUT, {.str = عدم }, 0, 0, FLAGS },
    { "flags", "set flags", وٿي_2(flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, AV_IAMF_LAYER_FLAG_RECON_GAIN, FLAGS, .unit = "flags" },
            {"recon_gain",  "Recon gain is present", 0, AV_OPT_TYPE_CONST,
                {.i64 = AV_IAMF_LAYER_FLAG_RECON_GAIN }, INT_MIN, وڌ_کان_وڌ_عدد, FLAGS, .unit = "flags"},
    { "output_gain_flags", "set output_gain_flags", وٿي_2(output_gain_flags), AV_OPT_TYPE_FLAGS,
        {.i64 = 0 }, 0, (1 << 6) - 1, FLAGS, .unit = "output_gain_flags" },
            {"FL",  "Left channel",            0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 5 }, INT_MIN, وڌ_کان_وڌ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"FR",  "Right channel",           0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 4 }, INT_MIN, وڌ_کان_وڌ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"BL",  "Left surround channel",   0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 3 }, INT_MIN, وڌ_کان_وڌ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"BR",  "Right surround channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 2 }, INT_MIN, وڌ_کان_وڌ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"TFL", "Left top front channel",  0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 1 }, INT_MIN, وڌ_کان_وڌ_عدد, FLAGS, .unit = "output_gain_flags"},
            {"TFR", "Right top front channel", 0, AV_OPT_TYPE_CONST,
                {.i64 = 1 << 0 }, INT_MIN, وڌ_کان_وڌ_عدد, FLAGS, .unit = "output_gain_flags"},
    { "output_gain", "set output_gain", وٿي_2(output_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "ambisonics_mode", "set ambisonics_mode", وٿي_2(ambisonics_گهڻائي), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_AMBISONICS_گهڻائي_MONO },
            AV_IAMF_AMBISONICS_گهڻائي_MONO, AV_IAMF_AMBISONICS_گهڻائي_PROJECTION, FLAGS, .unit = "ambisonics_mode" },
        { "mono",       عدم, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_گهڻائي_MONO },       .unit = "ambisonics_mode" },
        { "projection", عدم, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AMBISONICS_گهڻائي_PROJECTION }, .unit = "ambisonics_mode" },
    { "demixing_matrix", "set demixing_matrix", وٿي_2(demixing_ميٽرڪس), AV_OPT_TYPE_RATIONAL | AV_OPT_TYPE_FLAG_ARRAY,
            { .arr = &demixing_ميٽرڪس_def }, -1.0, 1.0, FLAGS },
    { عدم },
};

ساكن ثابت AVClass layer_class = {
    .class_name     = "AVIAMFLayer",
    .شي_name      = av_default_شي_name,
    .نسخو        = LIBAVUTIL_نسخو_INT,
    .option         = layer_options,
};

#وصف_رد وٿي_2
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFAudioElement, x)
ساكن ثابت AVOption audio_element_options[] = {
    { "audio_element_type", "set audio_element_type", وٿي_2(audio_element_type), AV_OPT_TYPE_INT,
            {.i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL },
            AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, FLAGS, .unit = "audio_element_type" },
        { "channel", عدم, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL }, .unit = "audio_element_type" },
        { "scene",   عدم, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE },   .unit = "audio_element_type" },
    { "default_w", "set default_w", وٿي_2(default_w), AV_OPT_TYPE_UINT, {.i64 = 0 }, 0, 10, FLAGS },
    { عدم },
};

ساكن ثابت AVClass *audio_element_ٻار_iterate(فراغ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = عدم;

    إذا (!i)
        ret = &layer_class;

    إذا (ret)
        *opaque = (فراغ*)(i + 1);
    أرجع ret;
}

ساكن ثابت AVClass audio_element_class = {
    .class_name          = "AVIAMFAudioElement",
    .شي_name           = av_default_شي_name,
    .نسخو             = LIBAVUTIL_نسخو_INT,
    .option              = audio_element_options,
    .ٻار_class_iterate = audio_element_ٻار_iterate,
};

ثابت AVClass *av_iamf_audio_element_get_class(فراغ)
{
    أرجع &audio_element_class;
}

AVIAMFAudioElement *av_iamf_audio_element_alloc(فراغ)
{
    AVIAMFAudioElement *audio_element = av_mallocz(حجم(*audio_element));

    إذا (audio_element) {
        audio_element->av_class = &audio_element_class;
        av_opt_سيٽ_defaults(audio_element);
    }

    أرجع audio_element;
}

IAMF_جوڙيو_FUNC_TEMPLATE(AVIAMFAudioElement, audio_element, AVIAMFLayer, layer, s)

فراغ av_iamf_audio_element_free(AVIAMFAudioElement **paudio_element)
{
    AVIAMFAudioElement *audio_element = *paudio_element;

    إذا (!audio_element)
        أرجع;

    لكل (صحيح i = 0; i < audio_element->nb_layers; i++) {
        AVIAMFLayer *layer = audio_element->layers[i];
        av_opt_free(layer);
        av_free(layer->demixing_ميٽرڪس);
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
#وصف_رد وٿي_2
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFSubmixElement, x)
ساكن ثابت AVOption submix_element_options[] = {
    { "headphones_rendering_mode", "Headphones rendering mode", وٿي_2(headphones_rendering_گهڻائي), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_HEADPHONES_گهڻائي_STEREO },
            AV_IAMF_HEADPHONES_گهڻائي_STEREO, AV_IAMF_HEADPHONES_گهڻائي_BINAURAL, FLAGS, .unit = "headphones_rendering_mode" },
        { "stereo",   عدم, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_گهڻائي_STEREO },   .unit = "headphones_rendering_mode" },
        { "binaural", عدم, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_HEADPHONES_گهڻائي_BINAURAL }, .unit = "headphones_rendering_mode" },
    { "default_mix_gain", "Default mix gain", وٿي_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "annotations", "Annotations", وٿي_2(annotations), AV_OPT_TYPE_DICT, { .str = عدم }, 0, 0, FLAGS },
    { عدم },
};

ساكن فراغ *submix_element_ٻار_ايندڙ(فراغ *obj, فراغ *prev)
{
    AVIAMFSubmixElement *submix_element = obj;
    إذا (!prev)
        أرجع submix_element->element_mix_config;

    أرجع عدم;
}

ساكن ثابت AVClass *submix_element_ٻار_iterate(فراغ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = عدم;

    إذا (!i)
        ret = &param_definition_class;

    إذا (ret)
        *opaque = (فراغ*)(i + 1);
    أرجع ret;
}

ساكن ثابت AVClass element_class = {
    .class_name          = "AVIAMFSubmixElement",
    .شي_name           = av_default_شي_name,
    .نسخو             = LIBAVUTIL_نسخو_INT,
    .option              = submix_element_options,
    .ٻار_ايندڙ          = submix_element_ٻار_ايندڙ,
    .ٻار_class_iterate = submix_element_ٻار_iterate,
};

IAMF_جوڙيو_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixElement, element, s)

#وصف_رد وٿي_2
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFSubmixLayout, x)
ساكن ثابت AVOption submix_layout_options[] = {
    { "layout_type", "Layout type", وٿي_2(layout_type), AV_OPT_TYPE_INT,
            { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS },
            AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS, AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL, FLAGS, .unit = "layout_type" },
        { "loudspeakers", عدم, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS }, .unit = "layout_type" },
        { "binaural",     عدم, 0, AV_OPT_TYPE_CONST,
                   { .i64 = AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL },     .unit = "layout_type" },
    { "sound_system", "Sound System", وٿي_2(sound_system), AV_OPT_TYPE_CHLAYOUT, { .str = عدم }, 0, 0, FLAGS },
    { "integrated_loudness", "Integrated loudness", وٿي_2(integrated_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "digital_peak", "Digital peak", وٿي_2(digital_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "true_peak", "True peak", وٿي_2(true_peak), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "dialog_anchored_loudness", "Anchored loudness (Dialog)", وٿي_2(dialogue_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { "album_anchored_loudness", "Anchored loudness (Album)", وٿي_2(album_anchored_loudness), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { عدم },
};

ساكن ثابت AVClass layout_class = {
    .class_name     = "AVIAMFSubmixLayout",
    .شي_name      = av_default_شي_name,
    .نسخو        = LIBAVUTIL_نسخو_INT,
    .option         = submix_layout_options,
};

IAMF_جوڙيو_FUNC_TEMPLATE(AVIAMFSubmix, submix, AVIAMFSubmixLayout, layout, s)

#وصف_رد وٿي_2
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFSubmix, x)
ساكن ثابت AVOption submix_presentation_options[] = {
    { "default_mix_gain", "Default mix gain", وٿي_2(default_mix_gain), AV_OPT_TYPE_RATIONAL, { .dbl = 0 }, -128.0, 128.0, FLAGS },
    { عدم },
};

ساكن فراغ *submix_presentation_ٻار_ايندڙ(فراغ *obj, فراغ *prev)
{
    AVIAMFSubmix *sub_mix = obj;
    إذا (!prev)
        أرجع sub_mix->output_mix_config;

    أرجع عدم;
}

ساكن ثابت AVClass *submix_presentation_ٻار_iterate(فراغ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = عدم;

    بدل(i) {
    حالة 0:
        ret = &element_class;
        اكسر;
    حالة 1:
        ret = &layout_class;
        اكسر;
    حالة 2:
        ret = &param_definition_class;
        اكسر;
    افتراضي:
        اكسر;
    }

    إذا (ret)
        *opaque = (فراغ*)(i + 1);
    أرجع ret;
}

ساكن ثابت AVClass submix_class = {
    .class_name          = "AVIAMFSubmix",
    .شي_name           = av_default_شي_name,
    .نسخو             = LIBAVUTIL_نسخو_INT,
    .option              = submix_presentation_options,
    .ٻار_ايندڙ          = submix_presentation_ٻار_ايندڙ,
    .ٻار_class_iterate = submix_presentation_ٻار_iterate,
};

#وصف_رد وٿي_2
#وصف_ڪريو وٿي_2(x) offsetof(AVIAMFMixPresentation, x)
ساكن ثابت AVOption mix_presentation_options[] = {
    { "annotations", "set annotations", وٿي_2(annotations), AV_OPT_TYPE_DICT, {.str = عدم }, 0, 0, FLAGS },
    { عدم },
};

#وصف_رد وٿي_2
#وصف_رد FLAGS

ساكن ثابت AVClass *mix_presentation_ٻار_iterate(فراغ **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    ثابت AVClass *ret = عدم;

    إذا (!i)
        ret = &submix_class;

    إذا (ret)
        *opaque = (فراغ*)(i + 1);
    أرجع ret;
}

ساكن ثابت AVClass mix_presentation_class = {
    .class_name          = "AVIAMFMixPresentation",
    .شي_name           = av_default_شي_name,
    .نسخو             = LIBAVUTIL_نسخو_INT,
    .option              = mix_presentation_options,
    .ٻار_class_iterate = mix_presentation_ٻار_iterate,
};

ثابت AVClass *av_iamf_mix_presentation_get_class(فراغ)
{
    أرجع &mix_presentation_class;
}

AVIAMFMixPresentation *av_iamf_mix_presentation_alloc(فراغ)
{
    AVIAMFMixPresentation *mix_presentation = av_mallocz(حجم(*mix_presentation));

    إذا (mix_presentation) {
        mix_presentation->av_class = &mix_presentation_class;
        av_opt_سيٽ_defaults(mix_presentation);
    }

    أرجع mix_presentation;
}

IAMF_جوڙيو_FUNC_TEMPLATE(AVIAMFMixPresentation, mix_presentation, AVIAMFSubmix, submix, es)

فراغ av_iamf_mix_presentation_free(AVIAMFMixPresentation **pmix_presentation)
{
    AVIAMFMixPresentation *mix_presentation = *pmix_presentation;

    إذا (!mix_presentation)
        أرجع;

    لكل (صحيح i = 0; i < mix_presentation->nb_submixes; i++) {
        AVIAMFSubmix *sub_mix = mix_presentation->submixes[i];
        لكل (صحيح j = 0; j < sub_mix->nb_elements; j++) {
            AVIAMFSubmixElement *submix_element = sub_mix->elements[j];
            av_opt_free(submix_element);
            av_free(submix_element->element_mix_config);
            av_free(submix_element);
        }
        av_free(sub_mix->elements);
        لكل (صحيح j = 0; j < sub_mix->nb_layouts; j++) {
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

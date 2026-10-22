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

#اگر_تعریف_نشده AVUTIL_IAMF_H
#تعریف_کن AVUTIL_IAMF_H

/**
 * @file
 * Immersive Audio Model and Formats API header
 * @see <a href="https://aomediacodec.github.io/iamf/">Immersive Audio Model and Formats</a>
 */

#ضمن <stdint.h>
#ضمن <stddef.h>

#ضمن "attributes.h"
#ضمن "avassert.h"
#ضمن "channel_layout.h"
#ضمن "dict.h"
#ضمن "rational.h"

/**
 * @defgroup lavu_iamf Immersive Audio Model and Formats
 * @ingroup lavu_audio
 *
 * Immersive Audio Model and Formats related functions and defines
 *
 * @defgroup lavu_iamf_params Parameter Definition
 * @ingroup lavu_iamf
 * @{
 * Parameters as defined in section 3.6.1 and 3.8 of IAMF.
 * @}
 *
 * @defgroup lavu_iamf_audio Audio Element
 * @ingroup lavu_iamf
 * @{
 * Audio Elements as defined in section 3.6 of IAMF.
 * @}
 *
 * @defgroup lavu_iamf_mix Mix Presentation
 * @ingroup lavu_iamf
 * @{
 * Mix Presentations as defined in section 3.7 of IAMF.
 * @}
 *
 * @addtogroup lavu_iamf_params
 * @{
 */
تعداد AVIAMFAnimationType {
    AV_IAMF_ANIMATION_TYPE_گام,
    AV_IAMF_ANIMATION_TYPE_خطی,
    AV_IAMF_ANIMATION_TYPE_BEZIER,
};

/**
 * Mix Gain Parameter Data as defined in section 3.8.1 of IAMF.
 *
 * @note This struct's size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFMixGain {
    ثابت AVClass *av_class;

    /**
     * Duration for the given subblock, in units of
     * 1 / @ref AVIAMFParamDefinition.parameter_rate "parameter_rate".
     * It must not be 0.
     */
    بیعلامت صحيح subblock_duration;
    /**
     * The type of animation applied to the parameter values.
     */
    تعداد AVIAMFAnimationType animation_type;
    /**
     * Parameter value that is applied at the start of the subblock.
     * Applies to all defined Animation Types.
     *
     * Valid range of values is -128.0 to 128.0
     */
    AVRational شروع_نقطه_مقدار;
    /**
     * Parameter value that is applied at the end of the subblock.
     * Applies only to AV_IAMF_ANIMATION_TYPE_LINEAR and
     * AV_IAMF_ANIMATION_TYPE_BEZIER Animation Types.
     *
     * Valid range of values is -128.0 to 128.0
     */
    AVRational انتها_نقطه_مقدار;
    /**
     * Parameter value of the middle control point of a quadratic Bezier
     * curve, i.e., its y-axis value.
     * Applies only to AV_IAMF_ANIMATION_TYPE_BEZIER Animation Type.
     *
     * Valid range of values is -128.0 to 128.0
     */
    AVRational control_نقطه_مقدار;
    /**
     * Parameter value of the time of the middle control point of a
     * quadratic Bezier curve, i.e., its x-axis value.
     * Applies only to AV_IAMF_ANIMATION_TYPE_BEZIER Animation Type.
     *
     * Valid range of values is 0.0 to 1.0
     */
    AVRational control_نقطه_relative_زمان;
} AVIAMFMixGain;

/**
 * Demixing Info Parameter Data as defined in section 3.8.2 of IAMF.
 *
 * @note This struct's size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFDemixingInfo {
    ثابت AVClass *av_class;

    /**
     * Duration for the given subblock, in units of
     * 1 / @ref AVIAMFParamDefinition.parameter_rate "parameter_rate".
     * It must not be 0.
     */
    بیعلامت صحيح subblock_duration;
    /**
     * Pre-defined combination of demixing parameters.
     */
    بیعلامت صحيح dmixp_نما;
} AVIAMFDemixingInfo;

/**
 * Recon Gain Info Parameter Data as defined in section 3.8.3 of IAMF.
 *
 * @note This struct's size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFReconGain {
    ثابت AVClass *av_class;

    /**
     * Duration for the given subblock, in units of
     * 1 / @ref AVIAMFParamDefinition.parameter_rate "parameter_rate".
     * It must not be 0.
     */
    بیعلامت صحيح subblock_duration;

    /**
     * Array of gain values to be applied to each channel for each layer
     * defined in the Audio Element referencing the parent Parameter Definition.
     * Values for layers where the AV_IAMF_LAYER_FLAG_RECON_GAIN flag is not set
     * are undefined.
     *
     * Channel order is: FL, C, FR, SL, SR, TFL, TFR, BL, BR, TBL, TBR, LFE
     */
    uint8_t recon_gain[6][12];
} AVIAMFReconGain;

تعداد AVIAMFParamDefinitionType {
   /**
    * Subblocks are of struct type AVIAMFMixGain
    */
    AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN,
   /**
    * Subblocks are of struct type AVIAMFDemixingInfo
    */
    AV_IAMF_PARAMETER_DEFINITION_DEMIXING,
   /**
    * Subblocks are of struct type AVIAMFReconGain
    */
    AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN,
};

/**
 * Parameters as defined in section 3.6.1 of IAMF.
 *
 * The struct is allocated by av_iamf_param_definition_alloc() along with an
 * array of subblocks, its type depending on the value of type.
 * This array is placed subblocks_offset bytes after the start of this struct.
 *
 * @note This struct's size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFParamDefinition {
    ثابت AVClass *av_class;

    /**
     * Offset in bytes from the start of this struct, at which the subblocks
     * array is located.
     */
    size_t subblocks_جابه_جایی;
    /**
     * Size in bytes of each element in the subblocks array.
     */
    size_t subblock_اندازه;
    /**
     * Number of subblocks in the array.
     */
    بیعلامت صحيح nb_subblocks;

    /**
     * Parameters type. Determines the type of the subblock elements.
     */
    تعداد AVIAMFParamDefinitionType type;

    /**
     * Identifier for the parameter substream.
     */
    بیعلامت صحيح parameter_id;
    /**
     * Sample rate for the parameter substream. It must not be 0.
     */
    بیعلامت صحيح parameter_نرخ;

    /**
     * The accumulated duration of all blocks in this parameter definition,
     * in units of 1 / @ref parameter_rate.
     *
     * May be 0, in which case all duration values should be specified in
     * another parameter definition referencing the same parameter_id.
     */
    بیعلامت صحيح duration;
    /**
     * The duration of every subblock in the case where all subblocks, with
     * the optional exception of the last subblock, have equal durations.
     *
     * Must be 0 if subblocks have different durations.
     */
    بیعلامت صحيح constant_subblock_duration;
} AVIAMFParamDefinition;

ثابت AVClass *av_iamf_param_definition_get_class(فراغ);

/**
 * Allocates memory for AVIAMFParamDefinition, plus an array of {@code nb_subblocks}
 * amount of subblocks of the given type and initializes the variables. Can be
 * freed with a normal av_free() call.
 *
 * @param size if non-NULL, the size in bytes of the resulting data array is written here.
 */
AVIAMFParamDefinition *av_iamf_param_definition_alloc(تعداد AVIAMFParamDefinitionType type,
                                                      بیعلامت صحيح nb_subblocks, size_t *اندازه);

/**
 * Get the subblock at the specified {@code idx}. Must be between 0 and nb_subblocks - 1.
 *
 * The @ref AVIAMFParamDefinition.type "param definition type" defines
 * the struct type of the returned pointer.
 */
ساكن av_always_inline فراغ*
av_iamf_param_definition_get_subblock(ثابت AVIAMFParamDefinition *par, بیعلامت صحيح idx)
{
    av_assert0(idx < par->nb_subblocks);
    أرجع (فراغ *)((uint8_t *)par + par->subblocks_جابه_جایی + idx * par->subblock_اندازه);
}

/**
 * @}
 * @addtogroup lavu_iamf_audio
 * @{
 */

تعداد AVIAMFAmbisonics_نما {
    AV_IAMF_AMBISONICS_نما_MONO,
    AV_IAMF_AMBISONICS_نما_PROJECTION,
};

/**
 * Recon gain information for the layer is present in AVIAMFReconGain
 */
#تعریف_کن AV_IAMF_LAYER_FLAG_RECON_GAIN (1 << 0)

/**
 * A layer defining a Channel Layout in the Audio Element.
 *
 * When @ref AVIAMFAudioElement.audio_element_type "the parent's Audio Element type"
 * is AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, this corresponds to an Scalable Channel
 * Layout layer as defined in section 3.6.2 of IAMF.
 * For AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, it is an Ambisonics channel
 * layout as defined in section 3.6.3 of IAMF.
 *
 * @note The struct should be allocated with av_iamf_audio_element_add_layer()
 *       and its size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFLayer {
    ثابت AVClass *av_class;

    AVChannelLayout ch_layout;

    /**
     * A bitmask which may contain a combination of AV_IAMF_LAYER_FLAG_* flags.
     */
    بیعلامت صحيح flags;
    /**
     * Output gain channel flags as defined in section 3.6.2 of IAMF.
     *
     * This field is defined only if @ref AVIAMFAudioElement.audio_element_type
     * "the parent's Audio Element type" is AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL,
     * must be 0 otherwise.
     */
    بیعلامت صحيح output_gain_flags;
    /**
     * Output gain as defined in section 3.6.2 of IAMF.
     *
     * Must be 0 if @ref output_gain_flags is 0.
     */
    AVRational output_gain;
    /**
     * Ambisonics mode as defined in section 3.6.3 of IAMF.
     *
     * This field is defined only if @ref AVIAMFAudioElement.audio_element_type
     * "the parent's Audio Element type" is AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE.
     *
     * If AV_IAMF_AMBISONICS_MODE_MONO, channel_mapping is defined implicitly
     * (Ambisonic Order) or explicitly (Custom Order with ambi channels) in
     * @ref ch_layout.
     * If AV_IAMF_AMBISONICS_MODE_PROJECTION, @ref demixing_matrix must be set.
     */
    تعداد AVIAMFAmbisonics_نما ambisonics_نما;

    /**
     * Demixing matrix as defined in section 3.6.3 of IAMF.
     *
     * May be set only if @ref ambisonics_mode == AV_IAMF_AMBISONICS_MODE_PROJECTION,
     * must be NULL otherwise.
     */
    AVRational *demixing_ماتریس;

    /**
     * The length of the Demixing matrix array. Must be ch_layout.nb_channels multiplied
     * by the sum of the amount of streams in the group plus the amount of streams in
     * the group that are stereo.
     */
    بیعلامت صحيح nb_demixing_ماتریس;
} AVIAMFLayer;


تعداد AVIAMFAudioElementType {
    AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL,
    AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE,
};

/**
 * Information on how to combine one or more audio streams, as defined in
 * section 3.6 of IAMF.
 *
 * @note The struct should be allocated with av_iamf_audio_element_alloc()
 *       and its size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFAudioElement {
    ثابت AVClass *av_class;

    AVIAMFLayer **layers;
    /**
     * Number of layers, or channel groups, in the Audio Element.
     * There may be 6 layers at most, and for @ref audio_element_type
     * AV_IAMF_AUDIO_ELEMENT_TYPE_SCENE, there may be exactly 1.
     *
     * Set by av_iamf_audio_element_add_layer(), must not be
     * modified by any other code.
     */
    بیعلامت صحيح nb_layers;

    /**
     * Demixing information used to reconstruct a scalable channel audio
     * representation.
     * The @ref AVIAMFParamDefinition.type "type" must be
     * AV_IAMF_PARAMETER_DEFINITION_DEMIXING.
     */
    AVIAMFParamDefinition *demixing_info;
    /**
     * Recon gain information used to reconstruct a scalable channel audio
     * representation.
     * The @ref AVIAMFParamDefinition.type "type" must be
     * AV_IAMF_PARAMETER_DEFINITION_RECON_GAIN.
     */
    AVIAMFParamDefinition *recon_gain_info;

    /**
     * Audio element type as defined in section 3.6 of IAMF.
     */
    تعداد AVIAMFAudioElementType audio_element_type;

    /**
     * Default weight value as defined in section 3.6 of IAMF.
     */
    بیعلامت صحيح default_w;
} AVIAMFAudioElement;

ثابت AVClass *av_iamf_audio_element_get_class(فراغ);

/**
 * Allocates a AVIAMFAudioElement, and initializes its fields with default values.
 * No layers are allocated. Must be freed with av_iamf_audio_element_free().
 *
 * @see av_iamf_audio_element_add_layer()
 */
AVIAMFAudioElement *av_iamf_audio_element_alloc(فراغ);

/**
 * Allocate a layer and add it to a given AVIAMFAudioElement.
 * It is freed by av_iamf_audio_element_free() alongside the rest of the parent
 * AVIAMFAudioElement.
 *
 * @return a pointer to the allocated layer.
 */
AVIAMFLayer *av_iamf_audio_element_جمع_کن_layer(AVIAMFAudioElement *audio_element);

/**
 * Free an AVIAMFAudioElement and all its contents.
 *
 * @param audio_element pointer to pointer to an allocated AVIAMFAudioElement.
 *                      upon return, *audio_element will be set to NULL.
 */
فراغ av_iamf_audio_element_free(AVIAMFAudioElement **audio_element);

/**
 * @}
 * @addtogroup lavu_iamf_mix
 * @{
 */

تعداد AVIAMFHeadphones_نما {
    /**
     * The referenced Audio Element shall be rendered to stereo loudspeakers.
     */
    AV_IAMF_HEADPHONES_نما_STEREO,
    /**
     * The referenced Audio Element shall be rendered with a binaural renderer.
     */
    AV_IAMF_HEADPHONES_نما_BINAURAL,
};

/**
 * Submix element as defined in section 3.7 of IAMF.
 *
 * @note The struct should be allocated with av_iamf_submix_add_element()
 *       and its size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFSubmixElement {
    ثابت AVClass *av_class;

    /**
     * The id of the Audio Element this submix element references.
     */
    بیعلامت صحيح audio_element_id;

    /**
     * Information required required for applying any processing to the
     * referenced and rendered Audio Element before being summed with other
     * processed Audio Elements.
     * The @ref AVIAMFParamDefinition.type "type" must be
     * AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN.
     */
    AVIAMFParamDefinition *element_mix_config;

    /**
     * Default mix gain value to apply when there are no AVIAMFParamDefinition
     * with @ref element_mix_config "element_mix_config's"
     * @ref AVIAMFParamDefinition.parameter_id "parameter_id" available for a
     * given audio frame.
     */
    AVRational default_mix_gain;

    /**
     * A value that indicates whether the referenced channel-based Audio Element
     * shall be rendered to stereo loudspeakers or spatialized with a binaural
     * renderer when played back on headphones.
     * If the Audio Element is not of @ref AVIAMFAudioElement.audio_element_type
     * "type" AV_IAMF_AUDIO_ELEMENT_TYPE_CHANNEL, then this field is undefined.
     */
    تعداد AVIAMFHeadphones_نما headphones_rendering_نما;

    /**
     * A dictionary of strings describing the submix in different languages.
     * Must have the same amount of entries as
     * @ref AVIAMFMixPresentation.annotations "the mix's annotations", stored
     * in the same order, and with the same key strings.
     *
     * @ref AVDictionaryEntry.key "key" is a string conforming to BCP-47 that
     * specifies the language for the string stored in
     * @ref AVDictionaryEntry.value "value".
     */
    AVDictionary *annotations;
} AVIAMFSubmixElement;

تعداد AVIAMFSubmixLayoutType {
    /**
     * The layout follows the loudspeaker sound system convention of ITU-2051-3.
     * @ref AVIAMFSubmixLayout.sound_system must be set.
     */
    AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS = 2,
    /**
     * The layout is binaural.
     *
     * @note @ref AVIAMFSubmixLayout.sound_system may be set to
     * AV_CHANNEL_LAYOUT_BINAURAL to simplify API usage, but it's not mandatory.
     */
    AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL = 3,
};

/**
 * Submix layout as defined in section 3.7.6 of IAMF.
 *
 * @note The struct should be allocated with av_iamf_submix_add_layout()
 *       and its size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFSubmixLayout {
    ثابت AVClass *av_class;

    تعداد AVIAMFSubmixLayoutType layout_type;

    /**
     * Channel layout matching one of Sound Systems A to J of ITU-2051-3, plus
     * 7.1.2ch, 3.1.2ch, and binaural.
     * If layout_type is not AV_IAMF_SUBMIX_LAYOUT_TYPE_LOUDSPEAKERS or
     * AV_IAMF_SUBMIX_LAYOUT_TYPE_BINAURAL, this field is undefined.
     */
    AVChannelLayout sound_system;
    /**
     * The program integrated loudness information, as defined in
     * ITU-1770-4.
     */
    AVRational integrated_loudness;
    /**
     * The digital (sampled) peak value of the audio signal, as defined
     * in ITU-1770-4.
     */
    AVRational digital_peak;
    /**
     * The true peak of the audio signal, as defined in ITU-1770-4.
     */
    AVRational true_peak;
    /**
     * The Dialogue loudness information, as defined in ITU-1770-4.
     */
    AVRational dialogue_anchored_loudness;
    /**
     * The Album loudness information, as defined in ITU-1770-4.
     */
    AVRational album_anchored_loudness;
} AVIAMFSubmixLayout;

/**
 * Submix layout as defined in section 3.7 of IAMF.
 *
 * @note The struct should be allocated with av_iamf_mix_presentation_add_submix()
 *       and its size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFSubmix {
    ثابت AVClass *av_class;

    /**
     * Array of submix elements.
     *
     * Set by av_iamf_submix_add_element(), must not be modified by any
     * other code.
     */
    AVIAMFSubmixElement **elements;
    /**
     * Number of elements in the submix.
     *
     * Set by av_iamf_submix_add_element(), must not be modified by any
     * other code.
     */
    بیعلامت صحيح nb_elements;

    /**
     * Array of submix layouts.
     *
     * Set by av_iamf_submix_add_layout(), must not be modified by any
     * other code.
     */
    AVIAMFSubmixLayout **layouts;
    /**
     * Number of layouts in the submix.
     *
     * Set by av_iamf_submix_add_layout(), must not be modified by any
     * other code.
     */
    بیعلامت صحيح nb_layouts;

    /**
     * Information required for post-processing the mixed audio signal to
     * generate the audio signal for playback.
     * The @ref AVIAMFParamDefinition.type "type" must be
     * AV_IAMF_PARAMETER_DEFINITION_MIX_GAIN.
     */
    AVIAMFParamDefinition *output_mix_config;

    /**
     * Default mix gain value to apply when there are no AVIAMFParamDefinition
     * with @ref output_mix_config "output_mix_config's"
     * @ref AVIAMFParamDefinition.parameter_id "parameter_id" available for a
     * given audio frame.
     */
    AVRational default_mix_gain;
} AVIAMFSubmix;

/**
 * Information on how to render and mix one or more AVIAMFAudioElement to generate
 * the final audio output, as defined in section 3.7 of IAMF.
 *
 * @note The struct should be allocated with av_iamf_mix_presentation_alloc()
 *       and its size is not a part of the public ABI.
 */
تعريفنوع بنية AVIAMFMixPresentation {
    ثابت AVClass *av_class;

    /**
     * Array of submixes.
     *
     * Set by av_iamf_mix_presentation_add_submix(), must not be modified
     * by any other code.
     */
    AVIAMFSubmix **submixes;
    /**
     * Number of submixes in the presentation.
     *
     * Set by av_iamf_mix_presentation_add_submix(), must not be modified
     * by any other code.
     */
    بیعلامت صحيح nb_submixes;

    /**
     * A dictionary of strings describing the mix in different languages.
     * Must have the same amount of entries as every
     * @ref AVIAMFSubmixElement.annotations "Submix element annotations",
     * stored in the same order, and with the same key strings.
     *
     * @ref AVDictionaryEntry.key "key" is a string conforming to BCP-47
     * that specifies the language for the string stored in
     * @ref AVDictionaryEntry.value "value".
     */
    AVDictionary *annotations;
} AVIAMFMixPresentation;

ثابت AVClass *av_iamf_mix_presentation_get_class(فراغ);

/**
 * Allocates a AVIAMFMixPresentation, and initializes its fields with default
 * values. No submixes are allocated.
 * Must be freed with av_iamf_mix_presentation_free().
 *
 * @see av_iamf_mix_presentation_add_submix()
 */
AVIAMFMixPresentation *av_iamf_mix_presentation_alloc(فراغ);

/**
 * Allocate a submix and add it to a given AVIAMFMixPresentation.
 * It is freed by av_iamf_mix_presentation_free() alongside the rest of the
 * parent AVIAMFMixPresentation.
 *
 * @return a pointer to the allocated submix.
 */
AVIAMFSubmix *av_iamf_mix_presentation_جمع_کن_submix(AVIAMFMixPresentation *mix_presentation);

/**
 * Allocate a submix element and add it to a given AVIAMFSubmix.
 * It is freed by av_iamf_mix_presentation_free() alongside the rest of the
 * parent AVIAMFSubmix.
 *
 * @return a pointer to the allocated submix.
 */
AVIAMFSubmixElement *av_iamf_submix_جمع_کن_element(AVIAMFSubmix *submix);

/**
 * Allocate a submix layout and add it to a given AVIAMFSubmix.
 * It is freed by av_iamf_mix_presentation_free() alongside the rest of the
 * parent AVIAMFSubmix.
 *
 * @return a pointer to the allocated submix.
 */
AVIAMFSubmixLayout *av_iamf_submix_جمع_کن_layout(AVIAMFSubmix *submix);

/**
 * Free an AVIAMFMixPresentation and all its contents.
 *
 * @param mix_presentation pointer to pointer to an allocated AVIAMFMixPresentation.
 *                         upon return, *mix_presentation will be set to NULL.
 */
فراغ av_iamf_mix_presentation_free(AVIAMFMixPresentation **mix_presentation);

/**
 * @}
 */

#پایان_اگر /* AVUTIL_IAMF_H */

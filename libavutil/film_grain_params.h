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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_FILM_GRAIN_PARAMS_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_FILM_GRAIN_PARAMS_H

#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"

ਗਿਣਤੀ AVFilmGrainParamsType {
    AV_FILM_GRAIN_PARAMS_NONE = 0,

    /**
     * The union is valid when interpreted as AVFilmGrainAOMParams (codec.aom)
     */
    AV_FILM_GRAIN_PARAMS_AV1,

    /**
     * The union is valid when interpreted as AVFilmGrainH274Params (codec.h274)
     */
    AV_FILM_GRAIN_PARAMS_H274,
};

/**
 * This structure describes how to handle film grain synthesis for AOM codecs.
 *
 * @note The struct must be allocated as part of AVFilmGrainParams using
 *       av_film_grain_params_alloc(). Its size is not a part of the public ABI.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVFilmGrainAOMParams {
    /**
     * Number of points, and the scale and value for each point of the
     * piecewise linear scaling function for the uma plane.
     */
    ਪੂਰਨ ਅੰਕ_y_points;
    uint8_t y_points[14][2 /* value, scaling */];

    /**
     * Signals whether to derive the chroma scaling function from the luma.
     * Not equivalent to copying the luma values and scales.
     */
    ਪੂਰਨ chroma_scaling_from_luma;

    /**
     * If chroma_scaling_from_luma is set to 0, signals the chroma scaling
     * function parameters.
     */
    ਪੂਰਨ ਅੰਕ_uv_points[2 /* cb, cr */];
    uint8_t uv_points[2 /* cb, cr */][10][2 /* value, scaling */];

    /**
     * Specifies the shift applied to the chroma components. For AV1, its within
     * [8; 11] and determines the range and quantization of the film grain.
     */
    ਪੂਰਨ scaling_ਖਿਸਕਾਓ;

    /**
     * Specifies the auto-regression lag.
     */
    ਪੂਰਨ ar_coeff_lag;

    /**
     * Luma auto-regression coefficients. The number of coefficients is given by
     * 2 * ar_coeff_lag * (ar_coeff_lag + 1).
     */
    int8_t ar_coeffs_y[24];

    /**
     * Chroma auto-regression coefficients. The number of coefficients is given by
     * 2 * ar_coeff_lag * (ar_coeff_lag + 1) + !!num_y_points.
     */
    int8_t ar_coeffs_uv[2 /* cb, cr */][25];

    /**
     * Specifies the range of the auto-regressive coefficients. Values of 6,
     * 7, 8 and so on represent a range of [-2, 2), [-1, 1), [-0.5, 0.5) and
     * so on. For AV1 must be between 6 and 9.
     */
    ਪੂਰਨ ar_coeff_ਖਿਸਕਾਓ;

    /**
     * Signals the down shift applied to the generated gaussian numbers during
     * synthesis.
     */
    ਪੂਰਨ grain_scale_ਖਿਸਕਾਓ;

    /**
     * Specifies the luma/chroma multipliers for the index to the component
     * scaling function.
     */
    ਪੂਰਨ uv_mult[2 /* cb, cr */];
    ਪੂਰਨ uv_mult_luma[2 /* cb, cr */];

    /**
     * Offset used for component scaling function. For AV1 its a 9-bit value
     * with a range [-256, 255]
     */
    ਪੂਰਨ uv_ਵਿੱਥ[2 /* cb, cr */];

    /**
     * Signals whether to overlap film grain blocks.
     */
    ਪੂਰਨ overlap_flag;

    /**
     * Signals to clip to limited color levels after film grain application.
     */
    ਪੂਰਨ ਹੱਦਬੰਦੀ_output_range;
} AVFilmGrainAOMParams;

/**
 * This structure describes how to handle film grain synthesis for codecs using
 * the ITU-T H.274 Versatile supplemental enhancement information message.
 *
 * @note The struct must be allocated as part of AVFilmGrainParams using
 *       av_film_grain_params_alloc(). Its size is not a part of the public ABI.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVFilmGrainH274Params {
    /**
     * Specifies the film grain simulation mode.
     * 0 = Frequency filtering, 1 = Auto-regression
     */
    ਪੂਰਨ model_id;

    /**
     * Specifies the blending mode used to blend the simulated film grain
     * with the decoded images.
     *
     * 0 = Additive, 1 = Multiplicative
     */
    ਪੂਰਨ blending_ਬਹੁਲਕ_id;

    /**
     * Specifies a scale factor used in the film grain characterization equations.
     */
    ਪੂਰਨ log2_scale_ਗੁਣਕ;

    /**
     * Indicates if the modelling of film grain for a given component is present.
     */
    ਪੂਰਨ component_model_present[3 /* y, cb, cr */];

    /**
     * Specifies the number of intensity intervals for which a specific set of
     * model values has been estimated, with a range of [1, 256].
     */
    uint16_t ਅੰਕ_intensity_intervals[3 /* y, cb, cr */];

    /**
     * Specifies the number of model values present for each intensity interval
     * in which the film grain has been modelled, with a range of [1, 6].
     */
    uint8_t ਅੰਕ_model_ਮੁੱਲਾਂ[3 /* y, cb, cr */];

    /**
     * Specifies the lower ounds of each intensity interval for whichthe set of
     * model values applies for the component.
     */
    uint8_t intensity_interval_ਹੇਠਲਾ_bound[3 /* y, cb, cr */][256 /* intensity interval */];

    /**
     * Specifies the upper bound of each intensity interval for which the set of
     * model values applies for the component.
     */
    uint8_t intensity_interval_ਉੱਤਲਾ_bound[3 /* y, cb, cr */][256 /* intensity interval */];

    /**
     * Specifies the model values for the component for each intensity interval.
     * - When model_id == 0, the following applies:
     *     For comp_model_value[y], the range of values is [0, 2^bit_depth_luma - 1]
     *     For comp_model_value[cb..cr], the range of values is [0, 2^bit_depth_chroma - 1]
     * - Otherwise, the following applies:
     *     For comp_model_value[y], the range of values is [-2^(bit_depth_luma - 1), 2^(bit_depth_luma - 1) - 1]
     *     For comp_model_value[cb..cr], the range of values is [-2^(bit_depth_chroma - 1), 2^(bit_depth_chroma - 1) - 1]
     */
    int16_t comp_model_ਮੁੱਲ[3 /* y, cb, cr */][256 /* intensity interval */][6 /* model value */];
} AVFilmGrainH274Params;

/**
 * This structure describes how to handle film grain synthesis in video
 * for specific codecs. Must be present on every frame where film grain is
 * meant to be synthesised for correct presentation.
 *
 * @note The struct must be allocated with av_film_grain_params_alloc() and
 *       its size is not a part of the public ABI.
 */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVFilmGrainParams {
    /**
     * Specifies the codec for which this structure is valid.
     */
    ਗਿਣਤੀ AVFilmGrainParamsType type;

    /**
     * Seed to use for the synthesis process, if the codec allows for it.
     *
     * @note For H.264, this refers to `pic_offset` as defined in
     *       SMPTE RDD 5-2006.
     */
    uint64_t ਬੀਜ;

    /**
     * Intended display resolution. May be 0 if the codec does not specify
     * any restrictions.
     */

    ਪੂਰਨ ਚੌੜਾਈ, ਉਚਾਈ;

    /**
     * Intended subsampling ratio, or 0 for luma-only streams.
     */
    ਪੂਰਨ subsampling_x, subsampling_y;

    /**
     * Intended video signal characteristics.
     */
    ਗਿਣਤੀ AVColorRange                  color_range;
    ਗਿਣਤੀ AVColorPrimaries              color_primaries;
    ਗਿਣਤੀ AVColorTransferCharacteristic color_trc;
    ਗਿਣਤੀ AVColorSpace                  color_space;

    /**
     * Intended bit depth, or 0 for unknown/unspecified.
     */
    ਪੂਰਨ ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_luma;
    ਪੂਰਨ ਦੋਆਧਾਰੀ_ਅੰਕ_ਡੂੰਘਾਈ_chroma;

    /**
     * Additional fields may be added both here and in any structure included.
     * If a codec's film grain structure differs slightly over another
     * codec's, fields within may change meaning depending on the type.
     */
    ਸੰਘ {
        AVFilmGrainAOMParams aom;
        AVFilmGrainH274Params h274;
    } codec;
} AVFilmGrainParams;

/**
 * Allocate an AVFilmGrainParams structure and set its fields to
 * default values. The resulting struct can be freed using av_freep().
 * If size is not NULL it will be set to the number of bytes allocated.
 *
 * @return An AVFilmGrainParams filled with default values or NULL
 *         on failure.
 */
AVFilmGrainParams *av_film_grain_params_alloc(size_t *ਮਾਪ);

/**
 * Allocate a complete AVFilmGrainParams and add it to the frame.
 *
 * @param frame The frame which side data is added to.
 *
 * @return The AVFilmGrainParams structure to be filled by caller.
 */
AVFilmGrainParams *av_film_grain_params_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ);

/**
 * Select the most appropriate film grain parameters set for the frame,
 * taking into account the frame's format, resolution and video signal
 * characteristics.
 *
 * @note, for H.274, this may select a film grain parameter set with
 * greater chroma resolution than the frame. Users should take care to
 * correctly adjust the chroma grain frequency to the frame.
 */
ਅਚਲ AVFilmGrainParams *av_film_grain_params_select(ਅਚਲ AVFrame *ਚੌਖਟਾ);

#ਜੇ_ਅੰਤ /* AVUTIL_FILM_GRAIN_PARAMS_H */

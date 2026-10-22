/*
 * Copyright (c) 2014 Tim Walker <tdskywalker@gmail.com>
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_DOWNMIX_INFO_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_DOWNMIX_INFO_H

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "frame.h"

/**
 * @file
 * audio downmix medatata
 */

/**
 * @addtogroup lavu_audio
 * @{
 */

/**
 * @defgroup downmix_info Audio downmix metadata
 * @{
 */

/**
 * Possible downmix types.
 */
ಎಣಿಕೆ AVDownmixType {
    AV_DOWNMIX_TYPE_UNKNOWN, /**< Not indicated. */
    AV_DOWNMIX_TYPE_LORO,    /**< Lo/Ro 2-channel downmix (Stereo). */
    AV_DOWNMIX_TYPE_LTRT,    /**< Lt/Rt 2-channel downmix, Dolby Surround compatible. */
    AV_DOWNMIX_TYPE_DPLII,   /**< Lt/Rt 2-channel downmix, Dolby Pro Logic II compatible. */
    AV_DOWNMIX_TYPE_NB       /**< Number of downmix types. Not part of ABI. */
};

/**
 * This structure describes optional metadata relevant to a downmix procedure.
 *
 * All fields are set by the decoder to the value indicated in the audio
 * bitstream (if present), or to a "sane" default otherwise.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDownmixInfo {
    /**
     * Type of downmix preferred by the mastering engineer.
     */
    ಎಣಿಕೆ AVDownmixType preferred_downmix_type;

    /**
     * Absolute scale factor representing the nominal level of the center
     * channel during a regular downmix.
     */
    ದ್ವಿಗುಣ center_mix_level;

    /**
     * Absolute scale factor representing the nominal level of the center
     * channel during an Lt/Rt compatible downmix.
     */
    ದ್ವಿಗುಣ center_mix_level_ltrt;

    /**
     * Absolute scale factor representing the nominal level of the surround
     * channels during a regular downmix.
     */
    ದ್ವಿಗುಣ surround_mix_level;

    /**
     * Absolute scale factor representing the nominal level of the surround
     * channels during an Lt/Rt compatible downmix.
     */
    ದ್ವಿಗುಣ surround_mix_level_ltrt;

    /**
     * Absolute scale factor representing the level at which the LFE data is
     * mixed into L/R channels during downmixing.
     */
    ದ್ವಿಗುಣ lfe_mix_level;
} AVDownmixInfo;

/**
 * Get a frame's AV_FRAME_DATA_DOWNMIX_INFO side data for editing.
 *
 * If the side data is absent, it is created and added to the frame.
 *
 * @param frame the frame for which the side data is to be obtained or created
 *
 * @return the AVDownmixInfo structure to be edited by the caller, or NULL if
 *         the structure cannot be allocated.
 */
AVDownmixInfo *av_downmix_info_update_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು);

/**
 * This structure describes optional metadata relevant to a downmix procedure
 * in the form of a remixing matrix allocated as an array of AVDownmixCoeff.
 * Must be allocated with @ref av_downmix_matrix_alloc.
 *
 * sizeof(AVDownmixMatrix) is not a part of the ABI and new fields may be
 * added to it.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDownmix_ಮಾತೃಕೆ {
    /**
     * Type of downmix the coeffs will produce.
     * Output channel count is derived from this value.
     */
    ಎಣಿಕೆ AVDownmixType downmix_type;

    /**
     * Input channel count.
     */
    ಪೂರ್ಣಾಂಕ ಒಳ_ch_ಎಣಿಕೆ;

    /**
     * Amount of coefficients in the matrix.
     */
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ nb_coeffs;

    /**
     * Offset in bytes from the beginning of this structure at which the array
     * of coefficients starts.
     */
    size_t coeffs_ಸ್ಥಾನಾಂತರ;
} AVDownmix_ಮಾತೃಕೆ;

/**
 * Data type for storing coefficients, which are allocated as a part of
 * AVDownmixMatrix and should be retrieved with @ref av_downmix_matrix_coeff.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದ್ವಿಗುಣ AVDownmixCoeff;

/**
 * Get a pointer to the coeff that represents the weight of input channel
 * {@code in} in output channel {@code out}.
 * in must be between 0 and @ref AVDownmixMatrix.in_ch_count "in_ch_count" - 1.
 * out must be between 0 and the implicit output channel count from
 * @ref AVDownmixMatrix.downmix_type "downmix_type" - 1.
 */
ಸ್ಥಿರ av_always_inline AVDownmixCoeff*
av_downmix_ಮಾತೃಕೆ_coeff(AVDownmix_ಮಾತೃಕೆ *dm, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಹೊರಹೋಗು, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಒಳ)
{
    AVDownmixCoeff *coeff = (AVDownmixCoeff *)((uint8_t *)dm + dm->coeffs_ಸ್ಥಾನಾಂತರ);
    ಹಿಂತಿರುಗಿ &coeff[ಒಳ + dm->ಒಳ_ch_ಎಣಿಕೆ * ಹೊರಹೋಗು];
}

/**
 * Allocates memory for AVDownmixMatrix of the given type, plus an array of
 * {@code in_ch_count} times the implicit output channel count from {@code type}
 * of AVDownmixCoeff and initializes the variables. Can be freed with a normal
 * av_free() call.
 *
 * @param out_size if non-NULL, the size in bytes of the resulting data array is
 * written here.
 */
AVDownmix_ಮಾತೃಕೆ *av_downmix_ಮಾತೃಕೆ_alloc(ಎಣಿಕೆ AVDownmixType type,
                                         ಪೂರ್ಣಾಂಕ ಒಳ_ch_ಎಣಿಕೆ, size_t *ಹೊರಹೋಗು_ಗಾತ್ರ);

/**
 * @}
 */

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_DOWNMIX_INFO_H */

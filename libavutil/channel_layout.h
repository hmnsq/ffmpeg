/*
 * Copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
 * Copyright (c) 2008 Peter Ross
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_CHANNEL_LAYOUT_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_CHANNEL_LAYOUT_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>

#ಅನ್ತರ್ಭಾವ "version.h"
#ಅನ್ತರ್ಭಾವ "attributes.h"

/**
 * @file
 * @ingroup lavu_audio_channels
 * Public libavutil channel layout APIs header.
 */


/**
 * @defgroup lavu_audio_channels Audio channels
 * @ingroup lavu_audio
 *
 * Audio channel layout utility functions
 *
 * @{
 */

ಎಣಿಕೆ AVChannel {
    /// Invalid channel index
    AV_CHAN_NONE = -1,
    AV_CHAN_FRONT_ಎಡ,
    AV_CHAN_FRONT_ಬಲ,
    AV_CHAN_FRONT_CENTER,
    AV_CHAN_ಕೆಳಗಿನ_FREQUENCY,
    AV_CHAN_ಹಿಂಭಾಗ_ಎಡ,
    AV_CHAN_ಹಿಂಭಾಗ_ಬಲ,
    AV_CHAN_FRONT_ಎಡ_ದ_CENTER,
    AV_CHAN_FRONT_ಬಲ_ದ_CENTER,
    AV_CHAN_ಹಿಂಭಾಗ_CENTER,
    AV_CHAN_SIDE_ಎಡ,
    AV_CHAN_SIDE_ಬಲ,
    AV_CHAN_ತುದಿ_CENTER,
    AV_CHAN_ತುದಿ_FRONT_ಎಡ,
    AV_CHAN_ತುದಿ_FRONT_CENTER,
    AV_CHAN_ತುದಿ_FRONT_ಬಲ,
    AV_CHAN_ತುದಿ_ಹಿಂಭಾಗ_ಎಡ,
    AV_CHAN_ತುದಿ_ಹಿಂಭಾಗ_CENTER,
    AV_CHAN_ತುದಿ_ಹಿಂಭಾಗ_ಬಲ,
    /** Stereo downmix. */
    AV_CHAN_STEREO_ಎಡ = 29,
    /** See above. */
    AV_CHAN_STEREO_ಬಲ,
    AV_CHAN_WIDE_ಎಡ,
    AV_CHAN_WIDE_ಬಲ,
    AV_CHAN_SURROUND_ನೇರ_ಎಡ,
    AV_CHAN_SURROUND_ನೇರ_ಬಲ,
    AV_CHAN_ಕೆಳಗಿನ_FREQUENCY_2,
    AV_CHAN_ತುದಿ_SIDE_ಎಡ,
    AV_CHAN_ತುದಿ_SIDE_ಬಲ,
    AV_CHAN_BOTTOM_FRONT_CENTER,
    AV_CHAN_BOTTOM_FRONT_ಎಡ,
    AV_CHAN_BOTTOM_FRONT_ಬಲ,
    AV_CHAN_SIDE_SURROUND_ಎಡ,     ///<  +90 degrees, Lss, SiL
    AV_CHAN_SIDE_SURROUND_ಬಲ,    ///<  -90 degrees, Rss, SiR
    AV_CHAN_ತುದಿ_SURROUND_ಎಡ,      ///< +110 degrees, Lvs, TpLS
    AV_CHAN_ತುದಿ_SURROUND_ಬಲ,     ///< -110 degrees, Rvs, TpRS

    AV_CHAN_BINAURAL_ಎಡ = 61,
    AV_CHAN_BINAURAL_ಬಲ,

    /** Channel is empty can be safely skipped. */
    AV_CHAN_ಬಳಸದ = 0x200,

    /** Channel contains data, but its position is unknown. */
    AV_CHAN_UNKNOWN = 0x300,

    /**
     * Range of channels between AV_CHAN_AMBISONIC_BASE and
     * AV_CHAN_AMBISONIC_END represent Ambisonic components using the ACN system.
     *
     * Given a channel id `<i>` between AV_CHAN_AMBISONIC_BASE and
     * AV_CHAN_AMBISONIC_END (inclusive), the ACN index of the channel `<n>` is
     * `<n> = <i> - AV_CHAN_AMBISONIC_BASE`.
     *
     * @note these values are only used for AV_CHANNEL_ORDER_CUSTOM channel
     * orderings, the AV_CHANNEL_ORDER_AMBISONIC ordering orders the channels
     * implicitly by their position in the stream.
     */
    AV_CHAN_AMBISONIC_ತಳ = 0x400,
    // leave space for 1024 ids, which correspond to maximum order-32 harmonics,
    // which should be enough for the foreseeable use cases
    AV_CHAN_AMBISONIC_ಕೊನೆ  = 0x7ff,
};

ಎಣಿಕೆ AVChannel_ಕ್ರಮ {
    /**
     * Only the channel count is specified, without any further information
     * about the channel order.
     */
    AV_CHANNEL_ಕ್ರಮ_UNSPEC,
    /**
     * The native channel order, i.e. the channels are in the same order in
     * which they are defined in the AVChannel enum. This supports up to 63
     * different channels.
     */
    AV_CHANNEL_ಕ್ರಮ_NATIVE,
    /**
     * The channel order does not correspond to any other predefined order and
     * is stored as an explicit map. For example, this could be used to support
     * layouts with 64 or more channels, or with empty/skipped (AV_CHAN_UNUSED)
     * channels at arbitrary positions.
     */
    AV_CHANNEL_ಕ್ರಮ_CUSTOM,
    /**
     * The audio is represented as the decomposition of the sound field into
     * spherical harmonics. Each channel corresponds to a single expansion
     * component. Channels are ordered according to ACN (Ambisonic Channel
     * Number).
     *
     * The channel with the index n in the stream contains the spherical
     * harmonic of degree l and order m given by
     * @code{.unparsed}
     *   l   = floor(sqrt(n)),
     *   m   = n - l * (l + 1).
     * @endcode
     *
     * Conversely given a spherical harmonic of degree l and order m, the
     * corresponding channel index n is given by
     * @code{.unparsed}
     *   n = l * (l + 1) + m.
     * @endcode
     *
     * Normalization is assumed to be SN3D (Schmidt Semi-Normalization)
     * as defined in AmbiX format $ 2.1.
     */
    AV_CHANNEL_ಕ್ರಮ_AMBISONIC,
    /**
     * Number of channel orders, not part of ABI/API
     */
    FF_CHANNEL_ಕ್ರಮ_NB
};


/**
 * @defgroup channel_masks Audio channel masks
 *
 * A channel layout is a 64-bits integer with a bit set for every channel.
 * The number of bits set must be equal to the number of channels.
 * The value 0 means that the channel layout is not known.
 * @note this data structure is not powerful enough to handle channels
 * combinations that have the same channel multiple times, such as
 * dual-mono.
 *
 * @{
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_FRONT_ಎಡ             (1ULL << AV_CHAN_FRONT_ಎಡ           )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_FRONT_ಬಲ            (1ULL << AV_CHAN_FRONT_ಬಲ          )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_FRONT_CENTER           (1ULL << AV_CHAN_FRONT_CENTER         )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ಕೆಳಗಿನ_FREQUENCY          (1ULL << AV_CHAN_ಕೆಳಗಿನ_FREQUENCY        )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ಹಿಂಭಾಗ_ಎಡ              (1ULL << AV_CHAN_ಹಿಂಭಾಗ_ಎಡ            )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ಹಿಂಭಾಗ_ಬಲ             (1ULL << AV_CHAN_ಹಿಂಭಾಗ_ಬಲ           )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_FRONT_ಎಡ_ದ_CENTER   (1ULL << AV_CHAN_FRONT_ಎಡ_ದ_CENTER )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_FRONT_ಬಲ_ದ_CENTER  (1ULL << AV_CHAN_FRONT_ಬಲ_ದ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ಹಿಂಭಾಗ_CENTER            (1ULL << AV_CHAN_ಹಿಂಭಾಗ_CENTER          )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_SIDE_ಎಡ              (1ULL << AV_CHAN_SIDE_ಎಡ            )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_SIDE_ಬಲ             (1ULL << AV_CHAN_SIDE_ಬಲ           )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_CENTER             (1ULL << AV_CHAN_ತುದಿ_CENTER           )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_FRONT_ಎಡ         (1ULL << AV_CHAN_ತುದಿ_FRONT_ಎಡ       )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_FRONT_CENTER       (1ULL << AV_CHAN_ತುದಿ_FRONT_CENTER     )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_FRONT_ಬಲ        (1ULL << AV_CHAN_ತುದಿ_FRONT_ಬಲ      )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಎಡ          (1ULL << AV_CHAN_ತುದಿ_ಹಿಂಭಾಗ_ಎಡ        )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_ಹಿಂಭಾಗ_CENTER        (1ULL << AV_CHAN_ತುದಿ_ಹಿಂಭಾಗ_CENTER      )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಬಲ         (1ULL << AV_CHAN_ತುದಿ_ಹಿಂಭಾಗ_ಬಲ       )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_STEREO_ಎಡ            (1ULL << AV_CHAN_STEREO_ಎಡ          )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_STEREO_ಬಲ           (1ULL << AV_CHAN_STEREO_ಬಲ         )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_WIDE_ಎಡ              (1ULL << AV_CHAN_WIDE_ಎಡ            )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_WIDE_ಬಲ             (1ULL << AV_CHAN_WIDE_ಬಲ           )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_SURROUND_ನೇರ_ಎಡ   (1ULL << AV_CHAN_SURROUND_ನೇರ_ಎಡ )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_SURROUND_ನೇರ_ಬಲ  (1ULL << AV_CHAN_SURROUND_ನೇರ_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ಕೆಳಗಿನ_FREQUENCY_2        (1ULL << AV_CHAN_ಕೆಳಗಿನ_FREQUENCY_2      )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_SIDE_ಎಡ          (1ULL << AV_CHAN_ತುದಿ_SIDE_ಎಡ        )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_SIDE_ಬಲ         (1ULL << AV_CHAN_ತುದಿ_SIDE_ಬಲ       )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_BOTTOM_FRONT_CENTER    (1ULL << AV_CHAN_BOTTOM_FRONT_CENTER  )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_BOTTOM_FRONT_ಎಡ      (1ULL << AV_CHAN_BOTTOM_FRONT_ಎಡ    )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_BOTTOM_FRONT_ಬಲ     (1ULL << AV_CHAN_BOTTOM_FRONT_ಬಲ   )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_SIDE_SURROUND_ಎಡ     (1ULL << AV_CHAN_SIDE_SURROUND_ಎಡ   )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_SIDE_SURROUND_ಬಲ    (1ULL << AV_CHAN_SIDE_SURROUND_ಬಲ  )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_SURROUND_ಎಡ      (1ULL << AV_CHAN_ತುದಿ_SURROUND_ಎಡ    )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_ತುದಿ_SURROUND_ಬಲ     (1ULL << AV_CHAN_ತುದಿ_SURROUND_ಬಲ   )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_BINAURAL_ಎಡ          (1ULL << AV_CHAN_BINAURAL_ಎಡ        )
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_BINAURAL_ಬಲ         (1ULL << AV_CHAN_BINAURAL_ಬಲ       )

/**
 * @}
 * @defgroup channel_mask_c Audio channel layouts
 * @{
 * */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_MONO              (AV_CH_FRONT_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_STEREO            (AV_CH_FRONT_ಎಡ|AV_CH_FRONT_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_2POINT1           (AV_CH_LAYOUT_STEREO|AV_CH_ಕೆಳಗಿನ_FREQUENCY)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_2_1               (AV_CH_LAYOUT_STEREO|AV_CH_ಹಿಂಭಾಗ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_SURROUND          (AV_CH_LAYOUT_STEREO|AV_CH_FRONT_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_3POINT1           (AV_CH_LAYOUT_SURROUND|AV_CH_ಕೆಳಗಿನ_FREQUENCY)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_4POINT0           (AV_CH_LAYOUT_SURROUND|AV_CH_ಹಿಂಭಾಗ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_4POINT1           (AV_CH_LAYOUT_4POINT0|AV_CH_ಕೆಳಗಿನ_FREQUENCY)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_2_2               (AV_CH_LAYOUT_STEREO|AV_CH_SIDE_ಎಡ|AV_CH_SIDE_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_QUAD              (AV_CH_LAYOUT_STEREO|AV_CH_ಹಿಂಭಾಗ_ಎಡ|AV_CH_ಹಿಂಭಾಗ_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_5POINT0           (AV_CH_LAYOUT_SURROUND|AV_CH_SIDE_ಎಡ|AV_CH_SIDE_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_5POINT1           (AV_CH_LAYOUT_5POINT0|AV_CH_ಕೆಳಗಿನ_FREQUENCY)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_5_POINT0_ಹಿಂಭಾಗ      (AV_CH_LAYOUT_SURROUND|AV_CH_ಹಿಂಭಾಗ_ಎಡ|AV_CH_ಹಿಂಭಾಗ_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_5_POINT1_ಹಿಂಭಾಗ      (AV_CH_LAYOUT_5_POINT0_ಹಿಂಭಾಗ|AV_CH_ಕೆಳಗಿನ_FREQUENCY)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_6POINT0           (AV_CH_LAYOUT_5POINT0|AV_CH_ಹಿಂಭಾಗ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_6POINT0_FRONT     (AV_CH_LAYOUT_2_2|AV_CH_FRONT_ಎಡ_ದ_CENTER|AV_CH_FRONT_ಬಲ_ದ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_HEXAGONAL         (AV_CH_LAYOUT_5_POINT0_ಹಿಂಭಾಗ|AV_CH_ಹಿಂಭಾಗ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_3POINT1POINT2     (AV_CH_LAYOUT_3POINT1|AV_CH_ತುದಿ_FRONT_ಎಡ|AV_CH_ತುದಿ_FRONT_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_6POINT1           (AV_CH_LAYOUT_5POINT1|AV_CH_ಹಿಂಭಾಗ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_6_POINT1_ಹಿಂಭಾಗ      (AV_CH_LAYOUT_5_POINT1_ಹಿಂಭಾಗ|AV_CH_ಹಿಂಭಾಗ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_6POINT1_FRONT     (AV_CH_LAYOUT_6POINT0_FRONT|AV_CH_ಕೆಳಗಿನ_FREQUENCY)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7POINT0           (AV_CH_LAYOUT_5POINT0|AV_CH_ಹಿಂಭಾಗ_ಎಡ|AV_CH_ಹಿಂಭಾಗ_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7POINT0_FRONT     (AV_CH_LAYOUT_5POINT0|AV_CH_FRONT_ಎಡ_ದ_CENTER|AV_CH_FRONT_ಬಲ_ದ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7POINT1           (AV_CH_LAYOUT_5POINT1|AV_CH_ಹಿಂಭಾಗ_ಎಡ|AV_CH_ಹಿಂಭಾಗ_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7POINT1_WIDE      (AV_CH_LAYOUT_5POINT1|AV_CH_FRONT_ಎಡ_ದ_CENTER|AV_CH_FRONT_ಬಲ_ದ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7_POINT1_WIDE_ಹಿಂಭಾಗ (AV_CH_LAYOUT_5_POINT1_ಹಿಂಭಾಗ|AV_CH_FRONT_ಎಡ_ದ_CENTER|AV_CH_FRONT_ಬಲ_ದ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_5POINT1POINT2     (AV_CH_LAYOUT_5POINT1|AV_CH_ತುದಿ_FRONT_ಎಡ|AV_CH_ತುದಿ_FRONT_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_5_POINT1_POINT2_ಹಿಂಭಾಗ (AV_CH_LAYOUT_5_POINT1_ಹಿಂಭಾಗ|AV_CH_ತುದಿ_FRONT_ಎಡ|AV_CH_ತುದಿ_FRONT_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_OCTAGONAL         (AV_CH_LAYOUT_5POINT0|AV_CH_ಹಿಂಭಾಗ_ಎಡ|AV_CH_ಹಿಂಭಾಗ_CENTER|AV_CH_ಹಿಂಭಾಗ_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_CUBE              (AV_CH_LAYOUT_QUAD|AV_CH_ತುದಿ_FRONT_ಎಡ|AV_CH_ತುದಿ_FRONT_ಬಲ|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಎಡ|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_5POINT1POINT4     (AV_CH_LAYOUT_5POINT1POINT2|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಎಡ|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_5POINT1POINT6     (AV_CH_LAYOUT_5POINT1POINT4|AV_CH_ತುದಿ_FRONT_CENTER|AV_CH_ತುದಿ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7POINT1POINT2     (AV_CH_LAYOUT_7POINT1|AV_CH_ತುದಿ_FRONT_ಎಡ|AV_CH_ತುದಿ_FRONT_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7POINT1POINT4     (AV_CH_LAYOUT_7POINT1POINT2|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಎಡ|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7POINT1POINT6     (AV_CH_LAYOUT_7POINT1POINT4|AV_CH_ತುದಿ_FRONT_CENTER|AV_CH_ತುದಿ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7POINT2POINT3     (AV_CH_LAYOUT_7POINT1POINT2|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_CENTER|AV_CH_ಕೆಳಗಿನ_FREQUENCY_2)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_9POINT1POINT4     (AV_CH_LAYOUT_7POINT1POINT4|AV_CH_FRONT_ಎಡ_ದ_CENTER|AV_CH_FRONT_ಬಲ_ದ_CENTER)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_9POINT1POINT6     (AV_CH_LAYOUT_9POINT1POINT4|AV_CH_ತುದಿ_SIDE_ಎಡ|AV_CH_ತುದಿ_SIDE_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_HEXADECAGONAL     (AV_CH_LAYOUT_OCTAGONAL|AV_CH_WIDE_ಎಡ|AV_CH_WIDE_ಬಲ|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಎಡ|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_ಬಲ|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_CENTER|AV_CH_ತುದಿ_FRONT_CENTER|AV_CH_ತುದಿ_FRONT_ಎಡ|AV_CH_ತುದಿ_FRONT_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_BINAURAL          (AV_CH_BINAURAL_ಎಡ|AV_CH_BINAURAL_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_STEREO_DOWNMIX    (AV_CH_STEREO_ಎಡ|AV_CH_STEREO_ಬಲ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_22POINT2          (AV_CH_LAYOUT_9POINT1POINT6|AV_CH_ಹಿಂಭಾಗ_CENTER|AV_CH_ಕೆಳಗಿನ_FREQUENCY_2|AV_CH_ತುದಿ_FRONT_CENTER|AV_CH_ತುದಿ_CENTER|AV_CH_ತುದಿ_ಹಿಂಭಾಗ_CENTER|AV_CH_BOTTOM_FRONT_CENTER|AV_CH_BOTTOM_FRONT_ಎಡ|AV_CH_BOTTOM_FRONT_ಬಲ)

#ಆದರೆ FF_API_CHANNEL_LAYOUT_ಹಿಂಭಾಗ
/*
 * The following layout masks are deprecated and will be removed in
 * an upcoming major bump.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_5_POINT1_POINT4_ಹಿಂಭಾಗ AV_CH_LAYOUT_5POINT1POINT4
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7_POINT1_POINT4_ಹಿಂಭಾಗ AV_CH_LAYOUT_7POINT1POINT4
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_9_POINT1_POINT4_ಹಿಂಭಾಗ AV_CH_LAYOUT_9POINT1POINT4
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CH_LAYOUT_7_POINT1_ತುದಿ_ಹಿಂಭಾಗ AV_CH_LAYOUT_5_POINT1_POINT2_ಹಿಂಭಾಗ
#ಆದರೆ_ಅಂತ್ಯ

/**
 * @}
 */

ಎಣಿಕೆ AVMatrixEncoding {
    AV_ಮಾತೃಕೆ_ENCODING_NONE,
    AV_ಮಾತೃಕೆ_ENCODING_DOLBY,
    AV_ಮಾತೃಕೆ_ENCODING_DPLII,
    AV_ಮಾತೃಕೆ_ENCODING_DPLIIX,
    AV_ಮಾತೃಕೆ_ENCODING_DPLIIZ,
    AV_ಮಾತೃಕೆ_ENCODING_DOLBYEX,
    AV_ಮಾತೃಕೆ_ENCODING_DOLBYHEADPHONE,
    AV_ಮಾತೃಕೆ_ENCODING_NB
};

/**
 * An AVChannelCustom defines a single channel within a custom order layout
 *
 * Unlike most structures in FFmpeg, sizeof(AVChannelCustom) is a part of the
 * public ABI.
 *
 * No new fields may be added to it without a major version bump.
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVChannelCustom {
    ಎಣಿಕೆ AVChannel id;
    ಅಕ್ಷರ name[16];
    ಶೂನ್ಯ *opaque;
} AVChannelCustom;

/**
 * An AVChannelLayout holds information about the channel layout of audio data.
 *
 * A channel layout here is defined as a set of channels ordered in a specific
 * way (unless the channel order is AV_CHANNEL_ORDER_UNSPEC, in which case an
 * AVChannelLayout carries only the channel count).
 * All orders may be treated as if they were AV_CHANNEL_ORDER_UNSPEC by
 * ignoring everything but the channel count, as long as av_channel_layout_check()
 * considers they are valid.
 *
 * Unlike most structures in FFmpeg, sizeof(AVChannelLayout) is a part of the
 * public ABI and may be used by the caller. E.g. it may be allocated on stack
 * or embedded in caller-defined structs.
 *
 * AVChannelLayout can be initialized as follows:
 * - default initialization with {0}, followed by setting all used fields
 *   correctly;
 * - by assigning one of the predefined AV_CHANNEL_LAYOUT_* initializers;
 * - with a constructor function, such as av_channel_layout_default(),
 *   av_channel_layout_from_mask() or av_channel_layout_from_string().
 *
 * The channel layout must be uninitialized with av_channel_layout_uninit()
 *
 * Copying an AVChannelLayout via assigning is forbidden,
 * av_channel_layout_copy() must be used instead (and its return value should
 * be checked)
 *
 * No new fields may be added to it without a major version bump, except for
 * new elements of the union fitting in sizeof(uint64_t).
 */
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVChannelLayout {
    /**
     * Channel order used in this layout.
     * This is a mandatory field.
     */
    ಎಣಿಕೆ AVChannel_ಕ್ರಮ ಕ್ರಮ;

    /**
     * Number of channels in this layout. Mandatory field.
     */
    ಪೂರ್ಣಾಂಕ nb_channels;

    /**
     * Details about which channels are present in this layout.
     * For AV_CHANNEL_ORDER_UNSPEC, this field is undefined and must not be
     * used.
     */
    ಒಕ್ಕೂಟ {
        /**
         * This member must be used for AV_CHANNEL_ORDER_NATIVE, and may be used
         * for AV_CHANNEL_ORDER_AMBISONIC to signal non-diegetic channels.
         * It is a bitmask, where the position of each set bit means that the
         * AVChannel with the corresponding value is present.
         *
         * I.e. when (mask & (1 << AV_CHAN_FOO)) is non-zero, then AV_CHAN_FOO
         * is present in the layout. Otherwise it is not present.
         *
         * @note when a channel layout using a bitmask is constructed or
         * modified manually (i.e.  not using any of the av_channel_layout_*
         * functions), the code doing it must ensure that the number of set bits
         * is equal to nb_channels.
         */
        uint64_t ಮುಖವಾಡ_2;
        /**
         * This member must be used when the channel order is
         * AV_CHANNEL_ORDER_CUSTOM. It is a nb_channels-sized array, with each
         * element signalling the presence of the AVChannel with the
         * corresponding value in map[i].id.
         *
         * I.e. when map[i].id is equal to AV_CHAN_FOO, then AV_CH_FOO is the
         * i-th channel in the audio data.
         *
         * When map[i].id is in the range between AV_CHAN_AMBISONIC_BASE and
         * AV_CHAN_AMBISONIC_END (inclusive), the channel contains an ambisonic
         * component with ACN index (as defined above)
         * n = map[i].id - AV_CHAN_AMBISONIC_BASE.
         *
         * map[i].name may be filled with a 0-terminated string, in which case
         * it will be used for the purpose of identifying the channel with the
         * convenience functions below. Otherwise it must be zeroed.
         */
        AVChannelCustom *map;
    } u;

    /**
     * For some private data of the user.
     */
    ಶೂನ್ಯ *opaque;
} AVChannelLayout;

/**
 * Macro to define native channel layouts
 *
 * @note This doesn't use designated initializers for compatibility with C++ 17 and older.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(nb, m) \
    { /* .order */ AV_CHANNEL_ಕ್ರಮ_NATIVE, \
      /* .nb_channels */  (nb), \
      /* .u.mask */ { m }, \
      /* .opaque */ ಖಾಲಿ }

/**
 * @name Common pre-defined channel layouts
 * @{
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_MONO              AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(1,  AV_CH_LAYOUT_MONO)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_STEREO            AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(2,  AV_CH_LAYOUT_STEREO)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_2POINT1           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(3,  AV_CH_LAYOUT_2POINT1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_2_1               AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(3,  AV_CH_LAYOUT_2_1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_SURROUND          AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(3,  AV_CH_LAYOUT_SURROUND)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_3POINT1           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(4,  AV_CH_LAYOUT_3POINT1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_4POINT0           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(4,  AV_CH_LAYOUT_4POINT0)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_4POINT1           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(5,  AV_CH_LAYOUT_4POINT1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_2_2               AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(4,  AV_CH_LAYOUT_2_2)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_QUAD              AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(4,  AV_CH_LAYOUT_QUAD)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_5POINT0           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(5,  AV_CH_LAYOUT_5POINT0)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_5POINT1           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(6,  AV_CH_LAYOUT_5POINT1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_5_POINT0_ಹಿಂಭಾಗ      AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(5,  AV_CH_LAYOUT_5_POINT0_ಹಿಂಭಾಗ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_5_POINT1_ಹಿಂಭಾಗ      AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(6,  AV_CH_LAYOUT_5_POINT1_ಹಿಂಭಾಗ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_6POINT0           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(6,  AV_CH_LAYOUT_6POINT0)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_6POINT0_FRONT     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(6,  AV_CH_LAYOUT_6POINT0_FRONT)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_3POINT1POINT2     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(6,  AV_CH_LAYOUT_3POINT1POINT2)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_HEXAGONAL         AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(6,  AV_CH_LAYOUT_HEXAGONAL)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_6POINT1           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(7,  AV_CH_LAYOUT_6POINT1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_6_POINT1_ಹಿಂಭಾಗ      AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(7,  AV_CH_LAYOUT_6_POINT1_ಹಿಂಭಾಗ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_6POINT1_FRONT     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(7,  AV_CH_LAYOUT_6POINT1_FRONT)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7POINT0           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(7,  AV_CH_LAYOUT_7POINT0)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7POINT0_FRONT     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(7,  AV_CH_LAYOUT_7POINT0_FRONT)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7POINT1           AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(8,  AV_CH_LAYOUT_7POINT1)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7POINT1_WIDE      AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(8,  AV_CH_LAYOUT_7POINT1_WIDE)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7_POINT1_WIDE_ಹಿಂಭಾಗ AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(8,  AV_CH_LAYOUT_7_POINT1_WIDE_ಹಿಂಭಾಗ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_5POINT1POINT2     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(8,  AV_CH_LAYOUT_5POINT1POINT2)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_5_POINT1_POINT2_ಹಿಂಭಾಗ AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(8, AV_CH_LAYOUT_5_POINT1_POINT2_ಹಿಂಭಾಗ)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_OCTAGONAL         AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(8,  AV_CH_LAYOUT_OCTAGONAL)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_CUBE              AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(8,  AV_CH_LAYOUT_CUBE)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_5POINT1POINT4     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(10, AV_CH_LAYOUT_5POINT1POINT4)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_5POINT1POINT6     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(12, AV_CH_LAYOUT_5POINT1POINT6)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7POINT1POINT2     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(10, AV_CH_LAYOUT_7POINT1POINT2)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7POINT1POINT4     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(12, AV_CH_LAYOUT_7POINT1POINT4)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7POINT1POINT6     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(14, AV_CH_LAYOUT_7POINT1POINT6)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7POINT2POINT3     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(12, AV_CH_LAYOUT_7POINT2POINT3)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_9POINT1POINT4     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(14, AV_CH_LAYOUT_9POINT1POINT4)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_9POINT1POINT6     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(16, AV_CH_LAYOUT_9POINT1POINT6)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_HEXADECAGONAL     AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(16, AV_CH_LAYOUT_HEXADECAGONAL)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_BINAURAL          AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(2,  AV_CH_LAYOUT_BINAURAL)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_STEREO_DOWNMIX    AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(2,  AV_CH_LAYOUT_STEREO_DOWNMIX)
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_22POINT2          AV_CHANNEL_LAYOUT_ಮುಖವಾಡ(24, AV_CH_LAYOUT_22POINT2)

#ಆದರೆ FF_API_CHANNEL_LAYOUT_ಹಿಂಭಾಗ
/*
 * The following layouts are deprecated and will be removed in
 * an upcoming major bump.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_5_POINT1_POINT4_ಹಿಂಭಾಗ AV_CHANNEL_LAYOUT_5POINT1POINT4
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7_POINT1_POINT4_ಹಿಂಭಾಗ AV_CHANNEL_LAYOUT_7POINT1POINT4
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_9_POINT1_POINT4_ಹಿಂಭಾಗ AV_CHANNEL_LAYOUT_9POINT1POINT4
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_7_POINT1_ತುದಿ_ಹಿಂಭಾಗ  AV_CHANNEL_LAYOUT_5_POINT1_POINT2_ಹಿಂಭಾಗ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_AMBISONIC_ಮೊದಲ_ಕ್ರಮ \
    { /* .order */ AV_CHANNEL_ಕ್ರಮ_AMBISONIC, \
      /* .nb_channels */ 4, \
      /* .u.mask */ { 0 }, \
      /* .opaque */ ಖಾಲಿ }
/** @} */

ರಚನೆ AVBPrint;

/**
 * Get a human readable string in an abbreviated form describing a given channel.
 * This is the inverse function of @ref av_channel_from_string().
 *
 * @param buf pre-allocated buffer where to put the generated string
 * @param buf_size size in bytes of the buffer.
 * @param channel the AVChannel whose name to get
 * @return amount of bytes needed to hold the output string, or a negative AVERROR
 *         on failure. If the returned value is bigger than buf_size, then the
 *         string was truncated.
 */
ಪೂರ್ಣಾಂಕ av_channel_name(ಅಕ್ಷರ *buf, size_t buf_ಗಾತ್ರ, ಎಣಿಕೆ AVChannel channel);

/**
 * bprint variant of av_channel_name().
 *
 * @note the string will be appended to the bprint buffer.
 */
ಶೂನ್ಯ av_channel_name_bprint(ರಚನೆ AVBPrint *bp, ಎಣಿಕೆ AVChannel channel_id);

/**
 * Get a human readable string describing a given channel.
 *
 * @param buf pre-allocated buffer where to put the generated string
 * @param buf_size size in bytes of the buffer.
 * @param channel the AVChannel whose description to get
 * @return amount of bytes needed to hold the output string, or a negative AVERROR
 *         on failure. If the returned value is bigger than buf_size, then the
 *         string was truncated.
 */
ಪೂರ್ಣಾಂಕ av_channel_description(ಅಕ್ಷರ *buf, size_t buf_ಗಾತ್ರ, ಎಣಿಕೆ AVChannel channel);

/**
 * bprint variant of av_channel_description().
 *
 * @note the string will be appended to the bprint buffer.
 */
ಶೂನ್ಯ av_channel_description_bprint(ರಚನೆ AVBPrint *bp, ಎಣಿಕೆ AVChannel channel_id);

/**
 * This is the inverse function of @ref av_channel_name().
 *
 * @return the channel with the given name
 *         AV_CHAN_NONE when name does not identify a known channel
 */
ಎಣಿಕೆ AVChannel av_channel_from_string(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name);

/**
 * Initialize a custom channel layout with the specified number of channels.
 * The channel map will be allocated and the designation of all channels will
 * be set to AV_CHAN_UNKNOWN.
 *
 * This is only a convenience helper function, a custom channel layout can also
 * be constructed without using this.
 *
 * @param channel_layout the layout structure to be initialized
 * @param nb_channels the number of channels
 *
 * @return 0 on success
 *         AVERROR(EINVAL) if the number of channels <= 0
 *         AVERROR(ENOMEM) if the channel map could not be allocated
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_custom_init(AVChannelLayout *channel_layout, ಪೂರ್ಣಾಂಕ nb_channels);

/**
 * Initialize a native channel layout from a bitmask indicating which channels
 * are present.
 *
 * @param channel_layout the layout structure to be initialized
 * @param mask bitmask describing the channel layout
 *
 * @return 0 on success
 *         AVERROR(EINVAL) for invalid mask values
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_from_ಮುಖವಾಡ(AVChannelLayout *channel_layout, uint64_t ಮುಖವಾಡ_2);

/**
 * Initialize a channel layout from a given string description.
 * The input string can be represented by:
 *  - the formal channel layout name (returned by av_channel_layout_describe())
 *  - single or multiple channel names (returned by av_channel_name(), eg. "FL",
 *    or concatenated with "+", each optionally containing a custom name after
 *    a "@", eg. "FL@Left+FR@Right+LFE")
 *  - a decimal or hexadecimal value of a native channel layout (eg. "4" or "0x4")
 *  - the number of channels with default layout (eg. "4c")
 *  - the number of unordered channels (eg. "4C" or "4 channels")
 *  - the ambisonic order followed by optional non-diegetic channels (eg.
 *    "ambisonic 2+stereo")
 * On error, the channel layout will remain uninitialized, but not necessarily
 * untouched.
 *
 * @param channel_layout uninitialized channel layout for the result
 * @param str string describing the channel layout
 * @return 0 on success parsing the channel layout
 *         AVERROR(EINVAL) if an invalid channel layout string was provided
 *         AVERROR(ENOMEM) if there was not enough memory
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str);

/**
 * Get the default channel layout for a given number of channels.
 *
 * @param ch_layout the layout structure to be initialized
 * @param nb_channels number of channels
 */
ಶೂನ್ಯ av_channel_layout_default(AVChannelLayout *ch_layout, ಪೂರ್ಣಾಂಕ nb_channels);

/**
 * Iterate over all standard channel layouts.
 *
 * @param opaque a pointer where libavutil will store the iteration state. Must
 *               point to NULL to start the iteration.
 *
 * @return the standard channel layout or NULL when the iteration is
 *         finished
 */
ಸ್ಥಿರಾಂಕ AVChannelLayout *av_channel_layout_standard(ಶೂನ್ಯ **opaque);

/**
 * Free any allocated data in the channel layout and reset the channel
 * count to 0.
 *
 * @param channel_layout the layout structure to be uninitialized
 */
ಶೂನ್ಯ av_channel_layout_uninit(AVChannelLayout *channel_layout);

/**
 * Make a copy of a channel layout. This differs from just assigning src to dst
 * in that it allocates and copies the map for AV_CHANNEL_ORDER_CUSTOM.
 *
 * @note the destination channel_layout will be always uninitialized before copy.
 *
 * @param dst destination channel layout
 * @param src source channel layout
 * @return 0 on success, a negative AVERROR on error.
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_copy(AVChannelLayout *dst, ಸ್ಥಿರಾಂಕ AVChannelLayout *src);

/**
 * Get a human-readable string describing the channel layout properties.
 * The string will be in the same format that is accepted by
 * @ref av_channel_layout_from_string(), allowing to rebuild the same
 * channel layout, except for opaque pointers.
 *
 * @param channel_layout channel layout to be described
 * @param buf pre-allocated buffer where to put the generated string
 * @param buf_size size in bytes of the buffer.
 * @return amount of bytes needed to hold the output string, or a negative AVERROR
 *         on failure. If the returned value is bigger than buf_size, then the
 *         string was truncated.
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_describe(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                               ಅಕ್ಷರ *buf, size_t buf_ಗಾತ್ರ);

/**
 * bprint variant of av_channel_layout_describe().
 *
 * @note the string will be appended to the bprint buffer.
 * @return 0 on success, or a negative AVERROR value on failure.
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_describe_bprint(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                      ರಚನೆ AVBPrint *bp);

/**
 * Get the channel with the given index in a channel layout.
 *
 * @param channel_layout input channel layout
 * @param idx index of the channel
 * @return channel with the index idx in channel_layout on success or
 *         AV_CHAN_NONE on failure (if idx is not valid or the channel order is
 *         unspecified)
 */
ಎಣಿಕೆ AVChannel
av_channel_layout_channel_from_ಸೂಚ್ಯಂಕ(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ idx);

/**
 * Get the index of a given channel in a channel layout. In case multiple
 * channels are found, only the first match will be returned.
 *
 * @param channel_layout input channel layout
 * @param channel the channel whose index to obtain
 * @return index of channel in channel_layout on success or a negative number if
 *         channel is not present in channel_layout.
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_ಸೂಚ್ಯಂಕ_from_channel(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                         ಎಣಿಕೆ AVChannel channel);

/**
 * Get the index in a channel layout of a channel described by the given string.
 * In case multiple channels are found, only the first match will be returned.
 *
 * This function accepts channel names in the same format as
 * @ref av_channel_from_string().
 *
 * @param channel_layout input channel layout
 * @param name string describing the channel whose index to obtain
 * @return a channel index described by the given string, or a negative AVERROR
 *         value.
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_ಸೂಚ್ಯಂಕ_from_string(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                        ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name);

/**
 * Get a channel described by the given string.
 *
 * This function accepts channel names in the same format as
 * @ref av_channel_from_string().
 *
 * @param channel_layout input channel layout
 * @param name string describing the channel to obtain
 * @return a channel described by the given string in channel_layout on success
 *         or AV_CHAN_NONE on failure (if the string is not valid or the channel
 *         order is unspecified)
 */
ಎಣಿಕೆ AVChannel
av_channel_layout_channel_from_string(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *name);

/**
 * Find out what channels from a given set are present in a channel layout,
 * without regard for their positions.
 *
 * @param channel_layout input channel layout
 * @param mask a combination of AV_CH_* representing a set of channels
 * @return a bitfield representing all the channels from mask that are present
 *         in channel_layout
 */
uint64_t av_channel_layout_subset(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout,
                                  uint64_t ಮುಖವಾಡ_2);

/**
 * Check whether a channel layout is valid, i.e. can possibly describe audio
 * data.
 *
 * @param channel_layout input channel layout
 * @return 1 if channel_layout is valid, 0 otherwise.
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_check(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout);

/**
 * Check whether two channel layouts are semantically the same, i.e. the same
 * channels are present on the same positions in both.
 *
 * If one of the channel layouts is AV_CHANNEL_ORDER_UNSPEC, while the other is
 * not, they are considered to be unequal. If both are AV_CHANNEL_ORDER_UNSPEC,
 * they are considered equal iff the channel counts are the same in both.
 *
 * @param chl input channel layout
 * @param chl1 input channel layout
 * @return 0 if chl and chl1 are equal, 1 if they are not equal. A negative
 *         AVERROR code if one or both are invalid.
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_compare(ಸ್ಥಿರಾಂಕ AVChannelLayout *chl, ಸ್ಥಿರಾಂಕ AVChannelLayout *chl1);

/**
 * Return the order if the layout is n-th order standard-order ambisonic.
 * The presence of optional extra non-diegetic channels at the end is not taken
 * into account.
 *
 * @param channel_layout input channel layout
 * @return the order of the layout, a negative error code otherwise.
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_ambisonic_ಕ್ರಮ(ಸ್ಥಿರಾಂಕ AVChannelLayout *channel_layout);

/**
 * The conversion must be lossless.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS (1 << 0)

/**
 * The specified retype target order is ignored and the simplest possible
 * (canonical) order is used for which the input layout can be losslessy
 * represented.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL (1 << 1)

/**
 * Change the AVChannelOrder of a channel layout.
 *
 * Change of AVChannelOrder can be either lossless or lossy. In case of a
 * lossless conversion all the channel designations and the associated channel
 * names (if any) are kept. On a lossy conversion the channel names and channel
 * designations might be lost depending on the capabilities of the desired
 * AVChannelOrder. Note that some conversions are simply not possible in which
 * case this function returns AVERROR(ENOSYS).
 *
 * The following conversions are supported:
 *
 * Any       -> Custom     : Always possible, always lossless.
 * Any       -> Unspecified: Always possible, lossless if channel designations
 *   are all unknown and channel names are not used, lossy otherwise.
 * Custom    -> Ambisonic  : Possible if it contains ambisonic channels with
 *   optional non-diegetic channels in the end. Lossy if the channels have
 *   custom names, lossless otherwise.
 * Custom    -> Native     : Possible if it contains native channels in native
 *     order. Lossy if the channels have custom names, lossless otherwise.
 *
 * On error this function keeps the original channel layout untouched.
 *
 * @param channel_layout channel layout which will be changed
 * @param order the desired channel layout order
 * @param flags a combination of AV_CHANNEL_LAYOUT_RETYPE_FLAG_* constants
 * @return 0 if the conversion was successful and lossless or if the channel
 *           layout was already in the desired order
 *         >0 if the conversion was successful but lossy
 *         AVERROR(ENOSYS) if the conversion was not possible (or would be
 *           lossy and AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS was specified)
 *         AVERROR(EINVAL), AVERROR(ENOMEM) on error
 */
ಪೂರ್ಣಾಂಕ av_channel_layout_retype(AVChannelLayout *channel_layout, ಎಣಿಕೆ AVChannel_ಕ್ರಮ ಕ್ರಮ, ಪೂರ್ಣಾಂಕ flags);

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_CHANNEL_LAYOUT_H */

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

#اگر_غیر_تعریف_شدہ AVUTIL_CHANNEL_LAYOUT_H
#تعریف_کرو AVUTIL_CHANNEL_LAYOUT_H

#شامل <stdint.h>
#شامل <stdlib.h>

#شامل "version.h"
#شامل "attributes.h"

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

شمار AVChannel {
    /// Invalid channel index
    AV_CHAN_NONE = -1,
    AV_CHAN_FRONT_بایاں,
    AV_CHAN_FRONT_دایاں,
    AV_CHAN_FRONT_CENTER,
    AV_CHAN_کم_FREQUENCY,
    AV_CHAN_عقب_بایاں,
    AV_CHAN_عقب_دایاں,
    AV_CHAN_FRONT_بایاں_کا_CENTER,
    AV_CHAN_FRONT_دایاں_کا_CENTER,
    AV_CHAN_عقب_CENTER,
    AV_CHAN_SIDE_بایاں,
    AV_CHAN_SIDE_دایاں,
    AV_CHAN_چوٹی_CENTER,
    AV_CHAN_چوٹی_FRONT_بایاں,
    AV_CHAN_چوٹی_FRONT_CENTER,
    AV_CHAN_چوٹی_FRONT_دایاں,
    AV_CHAN_چوٹی_عقب_بایاں,
    AV_CHAN_چوٹی_عقب_CENTER,
    AV_CHAN_چوٹی_عقب_دایاں,
    /** Stereo downmix. */
    AV_CHAN_STEREO_بایاں = 29,
    /** See above. */
    AV_CHAN_STEREO_دایاں,
    AV_CHAN_WIDE_بایاں,
    AV_CHAN_WIDE_دایاں,
    AV_CHAN_SURROUND_براہ_راست_بایاں,
    AV_CHAN_SURROUND_براہ_راست_دایاں,
    AV_CHAN_کم_FREQUENCY_2,
    AV_CHAN_چوٹی_SIDE_بایاں,
    AV_CHAN_چوٹی_SIDE_دایاں,
    AV_CHAN_BOTTOM_FRONT_CENTER,
    AV_CHAN_BOTTOM_FRONT_بایاں,
    AV_CHAN_BOTTOM_FRONT_دایاں,
    AV_CHAN_SIDE_SURROUND_بایاں,     ///<  +90 degrees, Lss, SiL
    AV_CHAN_SIDE_SURROUND_دایاں,    ///<  -90 degrees, Rss, SiR
    AV_CHAN_چوٹی_SURROUND_بایاں,      ///< +110 degrees, Lvs, TpLS
    AV_CHAN_چوٹی_SURROUND_دایاں,     ///< -110 degrees, Rvs, TpRS

    AV_CHAN_BINAURAL_بایاں = 61,
    AV_CHAN_BINAURAL_دایاں,

    /** Channel is empty can be safely skipped. */
    AV_CHAN_غیر_مستعمل = 0x200,

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
    AV_CHAN_AMBISONIC_بنیاد = 0x400,
    // leave space for 1024 ids, which correspond to maximum order-32 harmonics,
    // which should be enough for the foreseeable use cases
    AV_CHAN_AMBISONIC_انتہا  = 0x7ff,
};

شمار AVChannel_ترتیب {
    /**
     * Only the channel count is specified, without any further information
     * about the channel order.
     */
    AV_CHANNEL_ترتیب_UNSPEC,
    /**
     * The native channel order, i.e. the channels are in the same order in
     * which they are defined in the AVChannel enum. This supports up to 63
     * different channels.
     */
    AV_CHANNEL_ترتیب_NATIVE,
    /**
     * The channel order does not correspond to any other predefined order and
     * is stored as an explicit map. For example, this could be used to support
     * layouts with 64 or more channels, or with empty/skipped (AV_CHAN_UNUSED)
     * channels at arbitrary positions.
     */
    AV_CHANNEL_ترتیب_CUSTOM,
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
    AV_CHANNEL_ترتیب_AMBISONIC,
    /**
     * Number of channel orders, not part of ABI/API
     */
    FF_CHANNEL_ترتیب_NB
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
#تعریف_کرو AV_CH_FRONT_بایاں             (1ULL << AV_CHAN_FRONT_بایاں           )
#تعریف_کرو AV_CH_FRONT_دایاں            (1ULL << AV_CHAN_FRONT_دایاں          )
#تعریف_کرو AV_CH_FRONT_CENTER           (1ULL << AV_CHAN_FRONT_CENTER         )
#تعریف_کرو AV_CH_کم_FREQUENCY          (1ULL << AV_CHAN_کم_FREQUENCY        )
#تعریف_کرو AV_CH_عقب_بایاں              (1ULL << AV_CHAN_عقب_بایاں            )
#تعریف_کرو AV_CH_عقب_دایاں             (1ULL << AV_CHAN_عقب_دایاں           )
#تعریف_کرو AV_CH_FRONT_بایاں_کا_CENTER   (1ULL << AV_CHAN_FRONT_بایاں_کا_CENTER )
#تعریف_کرو AV_CH_FRONT_دایاں_کا_CENTER  (1ULL << AV_CHAN_FRONT_دایاں_کا_CENTER)
#تعریف_کرو AV_CH_عقب_CENTER            (1ULL << AV_CHAN_عقب_CENTER          )
#تعریف_کرو AV_CH_SIDE_بایاں              (1ULL << AV_CHAN_SIDE_بایاں            )
#تعریف_کرو AV_CH_SIDE_دایاں             (1ULL << AV_CHAN_SIDE_دایاں           )
#تعریف_کرو AV_CH_چوٹی_CENTER             (1ULL << AV_CHAN_چوٹی_CENTER           )
#تعریف_کرو AV_CH_چوٹی_FRONT_بایاں         (1ULL << AV_CHAN_چوٹی_FRONT_بایاں       )
#تعریف_کرو AV_CH_چوٹی_FRONT_CENTER       (1ULL << AV_CHAN_چوٹی_FRONT_CENTER     )
#تعریف_کرو AV_CH_چوٹی_FRONT_دایاں        (1ULL << AV_CHAN_چوٹی_FRONT_دایاں      )
#تعریف_کرو AV_CH_چوٹی_عقب_بایاں          (1ULL << AV_CHAN_چوٹی_عقب_بایاں        )
#تعریف_کرو AV_CH_چوٹی_عقب_CENTER        (1ULL << AV_CHAN_چوٹی_عقب_CENTER      )
#تعریف_کرو AV_CH_چوٹی_عقب_دایاں         (1ULL << AV_CHAN_چوٹی_عقب_دایاں       )
#تعریف_کرو AV_CH_STEREO_بایاں            (1ULL << AV_CHAN_STEREO_بایاں          )
#تعریف_کرو AV_CH_STEREO_دایاں           (1ULL << AV_CHAN_STEREO_دایاں         )
#تعریف_کرو AV_CH_WIDE_بایاں              (1ULL << AV_CHAN_WIDE_بایاں            )
#تعریف_کرو AV_CH_WIDE_دایاں             (1ULL << AV_CHAN_WIDE_دایاں           )
#تعریف_کرو AV_CH_SURROUND_براہ_راست_بایاں   (1ULL << AV_CHAN_SURROUND_براہ_راست_بایاں )
#تعریف_کرو AV_CH_SURROUND_براہ_راست_دایاں  (1ULL << AV_CHAN_SURROUND_براہ_راست_دایاں)
#تعریف_کرو AV_CH_کم_FREQUENCY_2        (1ULL << AV_CHAN_کم_FREQUENCY_2      )
#تعریف_کرو AV_CH_چوٹی_SIDE_بایاں          (1ULL << AV_CHAN_چوٹی_SIDE_بایاں        )
#تعریف_کرو AV_CH_چوٹی_SIDE_دایاں         (1ULL << AV_CHAN_چوٹی_SIDE_دایاں       )
#تعریف_کرو AV_CH_BOTTOM_FRONT_CENTER    (1ULL << AV_CHAN_BOTTOM_FRONT_CENTER  )
#تعریف_کرو AV_CH_BOTTOM_FRONT_بایاں      (1ULL << AV_CHAN_BOTTOM_FRONT_بایاں    )
#تعریف_کرو AV_CH_BOTTOM_FRONT_دایاں     (1ULL << AV_CHAN_BOTTOM_FRONT_دایاں   )
#تعریف_کرو AV_CH_SIDE_SURROUND_بایاں     (1ULL << AV_CHAN_SIDE_SURROUND_بایاں   )
#تعریف_کرو AV_CH_SIDE_SURROUND_دایاں    (1ULL << AV_CHAN_SIDE_SURROUND_دایاں  )
#تعریف_کرو AV_CH_چوٹی_SURROUND_بایاں      (1ULL << AV_CHAN_چوٹی_SURROUND_بایاں    )
#تعریف_کرو AV_CH_چوٹی_SURROUND_دایاں     (1ULL << AV_CHAN_چوٹی_SURROUND_دایاں   )
#تعریف_کرو AV_CH_BINAURAL_بایاں          (1ULL << AV_CHAN_BINAURAL_بایاں        )
#تعریف_کرو AV_CH_BINAURAL_دایاں         (1ULL << AV_CHAN_BINAURAL_دایاں       )

/**
 * @}
 * @defgroup channel_mask_c Audio channel layouts
 * @{
 * */
#تعریف_کرو AV_CH_LAYOUT_MONO              (AV_CH_FRONT_CENTER)
#تعریف_کرو AV_CH_LAYOUT_STEREO            (AV_CH_FRONT_بایاں|AV_CH_FRONT_دایاں)
#تعریف_کرو AV_CH_LAYOUT_2POINT1           (AV_CH_LAYOUT_STEREO|AV_CH_کم_FREQUENCY)
#تعریف_کرو AV_CH_LAYOUT_2_1               (AV_CH_LAYOUT_STEREO|AV_CH_عقب_CENTER)
#تعریف_کرو AV_CH_LAYOUT_SURROUND          (AV_CH_LAYOUT_STEREO|AV_CH_FRONT_CENTER)
#تعریف_کرو AV_CH_LAYOUT_3POINT1           (AV_CH_LAYOUT_SURROUND|AV_CH_کم_FREQUENCY)
#تعریف_کرو AV_CH_LAYOUT_4POINT0           (AV_CH_LAYOUT_SURROUND|AV_CH_عقب_CENTER)
#تعریف_کرو AV_CH_LAYOUT_4POINT1           (AV_CH_LAYOUT_4POINT0|AV_CH_کم_FREQUENCY)
#تعریف_کرو AV_CH_LAYOUT_2_2               (AV_CH_LAYOUT_STEREO|AV_CH_SIDE_بایاں|AV_CH_SIDE_دایاں)
#تعریف_کرو AV_CH_LAYOUT_QUAD              (AV_CH_LAYOUT_STEREO|AV_CH_عقب_بایاں|AV_CH_عقب_دایاں)
#تعریف_کرو AV_CH_LAYOUT_5POINT0           (AV_CH_LAYOUT_SURROUND|AV_CH_SIDE_بایاں|AV_CH_SIDE_دایاں)
#تعریف_کرو AV_CH_LAYOUT_5POINT1           (AV_CH_LAYOUT_5POINT0|AV_CH_کم_FREQUENCY)
#تعریف_کرو AV_CH_LAYOUT_5_POINT0_عقب      (AV_CH_LAYOUT_SURROUND|AV_CH_عقب_بایاں|AV_CH_عقب_دایاں)
#تعریف_کرو AV_CH_LAYOUT_5_POINT1_عقب      (AV_CH_LAYOUT_5_POINT0_عقب|AV_CH_کم_FREQUENCY)
#تعریف_کرو AV_CH_LAYOUT_6POINT0           (AV_CH_LAYOUT_5POINT0|AV_CH_عقب_CENTER)
#تعریف_کرو AV_CH_LAYOUT_6POINT0_FRONT     (AV_CH_LAYOUT_2_2|AV_CH_FRONT_بایاں_کا_CENTER|AV_CH_FRONT_دایاں_کا_CENTER)
#تعریف_کرو AV_CH_LAYOUT_HEXAGONAL         (AV_CH_LAYOUT_5_POINT0_عقب|AV_CH_عقب_CENTER)
#تعریف_کرو AV_CH_LAYOUT_3POINT1POINT2     (AV_CH_LAYOUT_3POINT1|AV_CH_چوٹی_FRONT_بایاں|AV_CH_چوٹی_FRONT_دایاں)
#تعریف_کرو AV_CH_LAYOUT_6POINT1           (AV_CH_LAYOUT_5POINT1|AV_CH_عقب_CENTER)
#تعریف_کرو AV_CH_LAYOUT_6_POINT1_عقب      (AV_CH_LAYOUT_5_POINT1_عقب|AV_CH_عقب_CENTER)
#تعریف_کرو AV_CH_LAYOUT_6POINT1_FRONT     (AV_CH_LAYOUT_6POINT0_FRONT|AV_CH_کم_FREQUENCY)
#تعریف_کرو AV_CH_LAYOUT_7POINT0           (AV_CH_LAYOUT_5POINT0|AV_CH_عقب_بایاں|AV_CH_عقب_دایاں)
#تعریف_کرو AV_CH_LAYOUT_7POINT0_FRONT     (AV_CH_LAYOUT_5POINT0|AV_CH_FRONT_بایاں_کا_CENTER|AV_CH_FRONT_دایاں_کا_CENTER)
#تعریف_کرو AV_CH_LAYOUT_7POINT1           (AV_CH_LAYOUT_5POINT1|AV_CH_عقب_بایاں|AV_CH_عقب_دایاں)
#تعریف_کرو AV_CH_LAYOUT_7POINT1_WIDE      (AV_CH_LAYOUT_5POINT1|AV_CH_FRONT_بایاں_کا_CENTER|AV_CH_FRONT_دایاں_کا_CENTER)
#تعریف_کرو AV_CH_LAYOUT_7_POINT1_WIDE_عقب (AV_CH_LAYOUT_5_POINT1_عقب|AV_CH_FRONT_بایاں_کا_CENTER|AV_CH_FRONT_دایاں_کا_CENTER)
#تعریف_کرو AV_CH_LAYOUT_5POINT1POINT2     (AV_CH_LAYOUT_5POINT1|AV_CH_چوٹی_FRONT_بایاں|AV_CH_چوٹی_FRONT_دایاں)
#تعریف_کرو AV_CH_LAYOUT_5_POINT1_POINT2_عقب (AV_CH_LAYOUT_5_POINT1_عقب|AV_CH_چوٹی_FRONT_بایاں|AV_CH_چوٹی_FRONT_دایاں)
#تعریف_کرو AV_CH_LAYOUT_OCTAGONAL         (AV_CH_LAYOUT_5POINT0|AV_CH_عقب_بایاں|AV_CH_عقب_CENTER|AV_CH_عقب_دایاں)
#تعریف_کرو AV_CH_LAYOUT_CUBE              (AV_CH_LAYOUT_QUAD|AV_CH_چوٹی_FRONT_بایاں|AV_CH_چوٹی_FRONT_دایاں|AV_CH_چوٹی_عقب_بایاں|AV_CH_چوٹی_عقب_دایاں)
#تعریف_کرو AV_CH_LAYOUT_5POINT1POINT4     (AV_CH_LAYOUT_5POINT1POINT2|AV_CH_چوٹی_عقب_بایاں|AV_CH_چوٹی_عقب_دایاں)
#تعریف_کرو AV_CH_LAYOUT_5POINT1POINT6     (AV_CH_LAYOUT_5POINT1POINT4|AV_CH_چوٹی_FRONT_CENTER|AV_CH_چوٹی_CENTER)
#تعریف_کرو AV_CH_LAYOUT_7POINT1POINT2     (AV_CH_LAYOUT_7POINT1|AV_CH_چوٹی_FRONT_بایاں|AV_CH_چوٹی_FRONT_دایاں)
#تعریف_کرو AV_CH_LAYOUT_7POINT1POINT4     (AV_CH_LAYOUT_7POINT1POINT2|AV_CH_چوٹی_عقب_بایاں|AV_CH_چوٹی_عقب_دایاں)
#تعریف_کرو AV_CH_LAYOUT_7POINT1POINT6     (AV_CH_LAYOUT_7POINT1POINT4|AV_CH_چوٹی_FRONT_CENTER|AV_CH_چوٹی_CENTER)
#تعریف_کرو AV_CH_LAYOUT_7POINT2POINT3     (AV_CH_LAYOUT_7POINT1POINT2|AV_CH_چوٹی_عقب_CENTER|AV_CH_کم_FREQUENCY_2)
#تعریف_کرو AV_CH_LAYOUT_9POINT1POINT4     (AV_CH_LAYOUT_7POINT1POINT4|AV_CH_FRONT_بایاں_کا_CENTER|AV_CH_FRONT_دایاں_کا_CENTER)
#تعریف_کرو AV_CH_LAYOUT_9POINT1POINT6     (AV_CH_LAYOUT_9POINT1POINT4|AV_CH_چوٹی_SIDE_بایاں|AV_CH_چوٹی_SIDE_دایاں)
#تعریف_کرو AV_CH_LAYOUT_HEXADECAGONAL     (AV_CH_LAYOUT_OCTAGONAL|AV_CH_WIDE_بایاں|AV_CH_WIDE_دایاں|AV_CH_چوٹی_عقب_بایاں|AV_CH_چوٹی_عقب_دایاں|AV_CH_چوٹی_عقب_CENTER|AV_CH_چوٹی_FRONT_CENTER|AV_CH_چوٹی_FRONT_بایاں|AV_CH_چوٹی_FRONT_دایاں)
#تعریف_کرو AV_CH_LAYOUT_BINAURAL          (AV_CH_BINAURAL_بایاں|AV_CH_BINAURAL_دایاں)
#تعریف_کرو AV_CH_LAYOUT_STEREO_DOWNMIX    (AV_CH_STEREO_بایاں|AV_CH_STEREO_دایاں)
#تعریف_کرو AV_CH_LAYOUT_22POINT2          (AV_CH_LAYOUT_9POINT1POINT6|AV_CH_عقب_CENTER|AV_CH_کم_FREQUENCY_2|AV_CH_چوٹی_FRONT_CENTER|AV_CH_چوٹی_CENTER|AV_CH_چوٹی_عقب_CENTER|AV_CH_BOTTOM_FRONT_CENTER|AV_CH_BOTTOM_FRONT_بایاں|AV_CH_BOTTOM_FRONT_دایاں)

#اگر FF_API_CHANNEL_LAYOUT_عقب
/*
 * The following layout masks are deprecated and will be removed in
 * an upcoming major bump.
 */
#تعریف_کرو AV_CH_LAYOUT_5_POINT1_POINT4_عقب AV_CH_LAYOUT_5POINT1POINT4
#تعریف_کرو AV_CH_LAYOUT_7_POINT1_POINT4_عقب AV_CH_LAYOUT_7POINT1POINT4
#تعریف_کرو AV_CH_LAYOUT_9_POINT1_POINT4_عقب AV_CH_LAYOUT_9POINT1POINT4
#تعریف_کرو AV_CH_LAYOUT_7_POINT1_چوٹی_عقب AV_CH_LAYOUT_5_POINT1_POINT2_عقب
#اگر_ختم

/**
 * @}
 */

شمار AVMatrixEncoding {
    AV_میٹرکس_ENCODING_NONE,
    AV_میٹرکس_ENCODING_DOLBY,
    AV_میٹرکس_ENCODING_DPLII,
    AV_میٹرکس_ENCODING_DPLIIX,
    AV_میٹرکس_ENCODING_DPLIIZ,
    AV_میٹرکس_ENCODING_DOLBYEX,
    AV_میٹرکس_ENCODING_DOLBYHEADPHONE,
    AV_میٹرکس_ENCODING_NB
};

/**
 * An AVChannelCustom defines a single channel within a custom order layout
 *
 * Unlike most structures in FFmpeg, sizeof(AVChannelCustom) is a part of the
 * public ABI.
 *
 * No new fields may be added to it without a major version bump.
 */
قسمتعریف ساخت AVChannelCustom {
    شمار AVChannel id;
    حرف name[16];
    خالی *opaque;
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
قسمتعریف ساخت AVChannelLayout {
    /**
     * Channel order used in this layout.
     * This is a mandatory field.
     */
    شمار AVChannel_ترتیب ترتیب;

    /**
     * Number of channels in this layout. Mandatory field.
     */
    صحیح nb_channels;

    /**
     * Details about which channels are present in this layout.
     * For AV_CHANNEL_ORDER_UNSPEC, this field is undefined and must not be
     * used.
     */
    اتحاد {
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
        uint64_t نقاب_2;
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
    خالی *opaque;
} AVChannelLayout;

/**
 * Macro to define native channel layouts
 *
 * @note This doesn't use designated initializers for compatibility with C++ 17 and older.
 */
#تعریف_کرو AV_CHANNEL_LAYOUT_نقاب(nb, m) \
    { /* .order */ AV_CHANNEL_ترتیب_NATIVE, \
      /* .nb_channels */  (nb), \
      /* .u.mask */ { m }, \
      /* .opaque */ تہی }

/**
 * @name Common pre-defined channel layouts
 * @{
 */
#تعریف_کرو AV_CHANNEL_LAYOUT_MONO              AV_CHANNEL_LAYOUT_نقاب(1,  AV_CH_LAYOUT_MONO)
#تعریف_کرو AV_CHANNEL_LAYOUT_STEREO            AV_CHANNEL_LAYOUT_نقاب(2,  AV_CH_LAYOUT_STEREO)
#تعریف_کرو AV_CHANNEL_LAYOUT_2POINT1           AV_CHANNEL_LAYOUT_نقاب(3,  AV_CH_LAYOUT_2POINT1)
#تعریف_کرو AV_CHANNEL_LAYOUT_2_1               AV_CHANNEL_LAYOUT_نقاب(3,  AV_CH_LAYOUT_2_1)
#تعریف_کرو AV_CHANNEL_LAYOUT_SURROUND          AV_CHANNEL_LAYOUT_نقاب(3,  AV_CH_LAYOUT_SURROUND)
#تعریف_کرو AV_CHANNEL_LAYOUT_3POINT1           AV_CHANNEL_LAYOUT_نقاب(4,  AV_CH_LAYOUT_3POINT1)
#تعریف_کرو AV_CHANNEL_LAYOUT_4POINT0           AV_CHANNEL_LAYOUT_نقاب(4,  AV_CH_LAYOUT_4POINT0)
#تعریف_کرو AV_CHANNEL_LAYOUT_4POINT1           AV_CHANNEL_LAYOUT_نقاب(5,  AV_CH_LAYOUT_4POINT1)
#تعریف_کرو AV_CHANNEL_LAYOUT_2_2               AV_CHANNEL_LAYOUT_نقاب(4,  AV_CH_LAYOUT_2_2)
#تعریف_کرو AV_CHANNEL_LAYOUT_QUAD              AV_CHANNEL_LAYOUT_نقاب(4,  AV_CH_LAYOUT_QUAD)
#تعریف_کرو AV_CHANNEL_LAYOUT_5POINT0           AV_CHANNEL_LAYOUT_نقاب(5,  AV_CH_LAYOUT_5POINT0)
#تعریف_کرو AV_CHANNEL_LAYOUT_5POINT1           AV_CHANNEL_LAYOUT_نقاب(6,  AV_CH_LAYOUT_5POINT1)
#تعریف_کرو AV_CHANNEL_LAYOUT_5_POINT0_عقب      AV_CHANNEL_LAYOUT_نقاب(5,  AV_CH_LAYOUT_5_POINT0_عقب)
#تعریف_کرو AV_CHANNEL_LAYOUT_5_POINT1_عقب      AV_CHANNEL_LAYOUT_نقاب(6,  AV_CH_LAYOUT_5_POINT1_عقب)
#تعریف_کرو AV_CHANNEL_LAYOUT_6POINT0           AV_CHANNEL_LAYOUT_نقاب(6,  AV_CH_LAYOUT_6POINT0)
#تعریف_کرو AV_CHANNEL_LAYOUT_6POINT0_FRONT     AV_CHANNEL_LAYOUT_نقاب(6,  AV_CH_LAYOUT_6POINT0_FRONT)
#تعریف_کرو AV_CHANNEL_LAYOUT_3POINT1POINT2     AV_CHANNEL_LAYOUT_نقاب(6,  AV_CH_LAYOUT_3POINT1POINT2)
#تعریف_کرو AV_CHANNEL_LAYOUT_HEXAGONAL         AV_CHANNEL_LAYOUT_نقاب(6,  AV_CH_LAYOUT_HEXAGONAL)
#تعریف_کرو AV_CHANNEL_LAYOUT_6POINT1           AV_CHANNEL_LAYOUT_نقاب(7,  AV_CH_LAYOUT_6POINT1)
#تعریف_کرو AV_CHANNEL_LAYOUT_6_POINT1_عقب      AV_CHANNEL_LAYOUT_نقاب(7,  AV_CH_LAYOUT_6_POINT1_عقب)
#تعریف_کرو AV_CHANNEL_LAYOUT_6POINT1_FRONT     AV_CHANNEL_LAYOUT_نقاب(7,  AV_CH_LAYOUT_6POINT1_FRONT)
#تعریف_کرو AV_CHANNEL_LAYOUT_7POINT0           AV_CHANNEL_LAYOUT_نقاب(7,  AV_CH_LAYOUT_7POINT0)
#تعریف_کرو AV_CHANNEL_LAYOUT_7POINT0_FRONT     AV_CHANNEL_LAYOUT_نقاب(7,  AV_CH_LAYOUT_7POINT0_FRONT)
#تعریف_کرو AV_CHANNEL_LAYOUT_7POINT1           AV_CHANNEL_LAYOUT_نقاب(8,  AV_CH_LAYOUT_7POINT1)
#تعریف_کرو AV_CHANNEL_LAYOUT_7POINT1_WIDE      AV_CHANNEL_LAYOUT_نقاب(8,  AV_CH_LAYOUT_7POINT1_WIDE)
#تعریف_کرو AV_CHANNEL_LAYOUT_7_POINT1_WIDE_عقب AV_CHANNEL_LAYOUT_نقاب(8,  AV_CH_LAYOUT_7_POINT1_WIDE_عقب)
#تعریف_کرو AV_CHANNEL_LAYOUT_5POINT1POINT2     AV_CHANNEL_LAYOUT_نقاب(8,  AV_CH_LAYOUT_5POINT1POINT2)
#تعریف_کرو AV_CHANNEL_LAYOUT_5_POINT1_POINT2_عقب AV_CHANNEL_LAYOUT_نقاب(8, AV_CH_LAYOUT_5_POINT1_POINT2_عقب)
#تعریف_کرو AV_CHANNEL_LAYOUT_OCTAGONAL         AV_CHANNEL_LAYOUT_نقاب(8,  AV_CH_LAYOUT_OCTAGONAL)
#تعریف_کرو AV_CHANNEL_LAYOUT_CUBE              AV_CHANNEL_LAYOUT_نقاب(8,  AV_CH_LAYOUT_CUBE)
#تعریف_کرو AV_CHANNEL_LAYOUT_5POINT1POINT4     AV_CHANNEL_LAYOUT_نقاب(10, AV_CH_LAYOUT_5POINT1POINT4)
#تعریف_کرو AV_CHANNEL_LAYOUT_5POINT1POINT6     AV_CHANNEL_LAYOUT_نقاب(12, AV_CH_LAYOUT_5POINT1POINT6)
#تعریف_کرو AV_CHANNEL_LAYOUT_7POINT1POINT2     AV_CHANNEL_LAYOUT_نقاب(10, AV_CH_LAYOUT_7POINT1POINT2)
#تعریف_کرو AV_CHANNEL_LAYOUT_7POINT1POINT4     AV_CHANNEL_LAYOUT_نقاب(12, AV_CH_LAYOUT_7POINT1POINT4)
#تعریف_کرو AV_CHANNEL_LAYOUT_7POINT1POINT6     AV_CHANNEL_LAYOUT_نقاب(14, AV_CH_LAYOUT_7POINT1POINT6)
#تعریف_کرو AV_CHANNEL_LAYOUT_7POINT2POINT3     AV_CHANNEL_LAYOUT_نقاب(12, AV_CH_LAYOUT_7POINT2POINT3)
#تعریف_کرو AV_CHANNEL_LAYOUT_9POINT1POINT4     AV_CHANNEL_LAYOUT_نقاب(14, AV_CH_LAYOUT_9POINT1POINT4)
#تعریف_کرو AV_CHANNEL_LAYOUT_9POINT1POINT6     AV_CHANNEL_LAYOUT_نقاب(16, AV_CH_LAYOUT_9POINT1POINT6)
#تعریف_کرو AV_CHANNEL_LAYOUT_HEXADECAGONAL     AV_CHANNEL_LAYOUT_نقاب(16, AV_CH_LAYOUT_HEXADECAGONAL)
#تعریف_کرو AV_CHANNEL_LAYOUT_BINAURAL          AV_CHANNEL_LAYOUT_نقاب(2,  AV_CH_LAYOUT_BINAURAL)
#تعریف_کرو AV_CHANNEL_LAYOUT_STEREO_DOWNMIX    AV_CHANNEL_LAYOUT_نقاب(2,  AV_CH_LAYOUT_STEREO_DOWNMIX)
#تعریف_کرو AV_CHANNEL_LAYOUT_22POINT2          AV_CHANNEL_LAYOUT_نقاب(24, AV_CH_LAYOUT_22POINT2)

#اگر FF_API_CHANNEL_LAYOUT_عقب
/*
 * The following layouts are deprecated and will be removed in
 * an upcoming major bump.
 */
#تعریف_کرو AV_CHANNEL_LAYOUT_5_POINT1_POINT4_عقب AV_CHANNEL_LAYOUT_5POINT1POINT4
#تعریف_کرو AV_CHANNEL_LAYOUT_7_POINT1_POINT4_عقب AV_CHANNEL_LAYOUT_7POINT1POINT4
#تعریف_کرو AV_CHANNEL_LAYOUT_9_POINT1_POINT4_عقب AV_CHANNEL_LAYOUT_9POINT1POINT4
#تعریف_کرو AV_CHANNEL_LAYOUT_7_POINT1_چوٹی_عقب  AV_CHANNEL_LAYOUT_5_POINT1_POINT2_عقب
#اگر_ختم

#تعریف_کرو AV_CHANNEL_LAYOUT_AMBISONIC_پہلا_ترتیب \
    { /* .order */ AV_CHANNEL_ترتیب_AMBISONIC, \
      /* .nb_channels */ 4, \
      /* .u.mask */ { 0 }, \
      /* .opaque */ تہی }
/** @} */

ساخت AVBPrint;

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
صحیح av_channel_name(حرف *buf, size_t buf_سائز, شمار AVChannel channel);

/**
 * bprint variant of av_channel_name().
 *
 * @note the string will be appended to the bprint buffer.
 */
خالی av_channel_name_bprint(ساخت AVBPrint *bp, شمار AVChannel channel_id);

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
صحیح av_channel_description(حرف *buf, size_t buf_سائز, شمار AVChannel channel);

/**
 * bprint variant of av_channel_description().
 *
 * @note the string will be appended to the bprint buffer.
 */
خالی av_channel_description_bprint(ساخت AVBPrint *bp, شمار AVChannel channel_id);

/**
 * This is the inverse function of @ref av_channel_name().
 *
 * @return the channel with the given name
 *         AV_CHAN_NONE when name does not identify a known channel
 */
شمار AVChannel av_channel_from_string(ثابت حرف *name);

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
صحیح av_channel_layout_custom_init(AVChannelLayout *channel_layout, صحیح nb_channels);

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
صحیح av_channel_layout_from_نقاب(AVChannelLayout *channel_layout, uint64_t نقاب_2);

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
صحیح av_channel_layout_from_string(AVChannelLayout *channel_layout,
                                  ثابت حرف *str);

/**
 * Get the default channel layout for a given number of channels.
 *
 * @param ch_layout the layout structure to be initialized
 * @param nb_channels number of channels
 */
خالی av_channel_layout_default(AVChannelLayout *ch_layout, صحیح nb_channels);

/**
 * Iterate over all standard channel layouts.
 *
 * @param opaque a pointer where libavutil will store the iteration state. Must
 *               point to NULL to start the iteration.
 *
 * @return the standard channel layout or NULL when the iteration is
 *         finished
 */
ثابت AVChannelLayout *av_channel_layout_standard(خالی **opaque);

/**
 * Free any allocated data in the channel layout and reset the channel
 * count to 0.
 *
 * @param channel_layout the layout structure to be uninitialized
 */
خالی av_channel_layout_uninit(AVChannelLayout *channel_layout);

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
صحیح av_channel_layout_copy(AVChannelLayout *dst, ثابت AVChannelLayout *src);

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
صحیح av_channel_layout_describe(ثابت AVChannelLayout *channel_layout,
                               حرف *buf, size_t buf_سائز);

/**
 * bprint variant of av_channel_layout_describe().
 *
 * @note the string will be appended to the bprint buffer.
 * @return 0 on success, or a negative AVERROR value on failure.
 */
صحیح av_channel_layout_describe_bprint(ثابت AVChannelLayout *channel_layout,
                                      ساخت AVBPrint *bp);

/**
 * Get the channel with the given index in a channel layout.
 *
 * @param channel_layout input channel layout
 * @param idx index of the channel
 * @return channel with the index idx in channel_layout on success or
 *         AV_CHAN_NONE on failure (if idx is not valid or the channel order is
 *         unspecified)
 */
شمار AVChannel
av_channel_layout_channel_from_اشاریہ(ثابت AVChannelLayout *channel_layout, غیرعلامتی صحیح idx);

/**
 * Get the index of a given channel in a channel layout. In case multiple
 * channels are found, only the first match will be returned.
 *
 * @param channel_layout input channel layout
 * @param channel the channel whose index to obtain
 * @return index of channel in channel_layout on success or a negative number if
 *         channel is not present in channel_layout.
 */
صحیح av_channel_layout_اشاریہ_from_channel(ثابت AVChannelLayout *channel_layout,
                                         شمار AVChannel channel);

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
صحیح av_channel_layout_اشاریہ_from_string(ثابت AVChannelLayout *channel_layout,
                                        ثابت حرف *name);

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
شمار AVChannel
av_channel_layout_channel_from_string(ثابت AVChannelLayout *channel_layout,
                                      ثابت حرف *name);

/**
 * Find out what channels from a given set are present in a channel layout,
 * without regard for their positions.
 *
 * @param channel_layout input channel layout
 * @param mask a combination of AV_CH_* representing a set of channels
 * @return a bitfield representing all the channels from mask that are present
 *         in channel_layout
 */
uint64_t av_channel_layout_subset(ثابت AVChannelLayout *channel_layout,
                                  uint64_t نقاب_2);

/**
 * Check whether a channel layout is valid, i.e. can possibly describe audio
 * data.
 *
 * @param channel_layout input channel layout
 * @return 1 if channel_layout is valid, 0 otherwise.
 */
صحیح av_channel_layout_check(ثابت AVChannelLayout *channel_layout);

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
صحیح av_channel_layout_compare(ثابت AVChannelLayout *chl, ثابت AVChannelLayout *chl1);

/**
 * Return the order if the layout is n-th order standard-order ambisonic.
 * The presence of optional extra non-diegetic channels at the end is not taken
 * into account.
 *
 * @param channel_layout input channel layout
 * @return the order of the layout, a negative error code otherwise.
 */
صحیح av_channel_layout_ambisonic_ترتیب(ثابت AVChannelLayout *channel_layout);

/**
 * The conversion must be lossless.
 */
#تعریف_کرو AV_CHANNEL_LAYOUT_RETYPE_FLAG_LOSSLESS (1 << 0)

/**
 * The specified retype target order is ignored and the simplest possible
 * (canonical) order is used for which the input layout can be losslessy
 * represented.
 */
#تعریف_کرو AV_CHANNEL_LAYOUT_RETYPE_FLAG_CANONICAL (1 << 1)

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
صحیح av_channel_layout_retype(AVChannelLayout *channel_layout, شمار AVChannel_ترتیب ترتیب, صحیح flags);

/**
 * @}
 */

#اگر_ختم /* AVUTIL_CHANNEL_LAYOUT_H */

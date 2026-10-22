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

#నిర్వచితం_కాకపోతే AVUTIL_GAIN_MAP_H
#నిర్వచించు AVUTIL_GAIN_MAP_H

#అన్తర్భావ <stddef.h>

#అన్తర్భావ "rational.h"
#అన్తర్భావ "frame.h"

#నిర్వచించు AV_ISO21496_సంస్కరణ    0
#నిర్వచించు AV_ISO21496_IDENTIFIER "urn:iso:std:iso:ts:21496:-1"

/**
 * Parameters describing how to combine a gain map rendition with its base
 * rendition to recover the alternate rendition, as defined by
 * ISO 21496-1:2025 "Digital photography - Gain map metadata for image
 * conversion".
 *
 * Note: sizeof(AVGainMapParams) is not part of the ABI. New fields may be
 * added at the end of the struct.
 */
రకనిర్వచనం నిర్మాణం AVGainMapParams {
    /**
     * The version of this gain map struct. Reserved to allow future
     * extensions of the struct. Must be <= AV_ISO21496_VERSION.
     */
    పూర్ణాంకం సంస్కరణ;

    /**
     * If non-zero, the gain map is applied in the colour space of the base
     * rendition; otherwise in that of the alternate rendition.
     */
    పూర్ణాంకం use_పునాది_color_space;

    /**
     * log2 of the display headroom at which the base rendition is shown
     * unmodified, and at which the map is applied in full.
     */
    AVRational పునాది_hdr_headroom;
    AVRational alternate_hdr_headroom;

    నిర్మాణం AVGainMapChannel {
        /**
        * log2-domain minimum and maximum gain applied by the map, i.e. the
        * values the map's 0.0 and 1.0 endpoints decode to.
        */
        AVRational gain_map_min;
        AVRational gain_map_max;

        /**
        * Encoding gamma of the stored map values. Must be > 0.
        */
        AVRational gamma;

        /**
        * Small constants added before the log-domain math to avoid a
        * singularity at zero.
        */
        AVRational పునాది_స్థానభ్రంశం;
        AVRational alternate_స్థానభ్రంశం;
    } channels[3]; /* R, G, B */

    /**
     * Must be 1 or 3. If 1, all channels share the same set of parameters.
     */
    పూర్ణాంకం nb_channels;
} AVGainMapParams;

/**
 * Parse the payload of an ISO 21496-1 gain map metadata blob.
 *
 * @param p   struct to fill; overwritten on success, untouched on failure
 * @param data payload, excluding container-specific identifiers
 * @param size size of `data` in bytes
 *
 * @return >= 0 on success, or a negative AVERROR on failure
 */
పూర్ణాంకం av_gain_map_params_from_iso21496(AVGainMapParams *p, స్థిరరాశి uint8_t *దత్తాంశం,
                                     size_t కొలత);

#నిర్వచించు AV_GAIN_MAP_MAX_PAYLOAD_కొలత 141 /* = 5 + 2*8 + 3*5*8 */

/**
 * Serialize an AVGainMapParams as an ISO 21496-1 gain map metadata blob.
 *
 * The output starts at the minimum_version field; the caller should prepend
 * whatever identifier its container requires.
 *
 * @param p   parameters to serialize
 * @param buf Byte buffer to fill with the serialized data. Must contain at
 *            least AV_GAIN_MAP_MAX_PAYLOAD_SIZE bytes.
 *
 * @return Number of bytes written on success, or a negative AVERROR on failure
 *
 * @note Always succeeds if av_gain_map_params_validate() returns >= 0.
 */
పూర్ణాంకం av_gain_map_params_గమ్యం_iso21496(స్థిరరాశి AVGainMapParams *p, uint8_t *buf);

/**
 * Returns >= 0 if the given AVGainMapParams struct contains valid data;
 * or a negative AVERROR otherwise.
 */
పూర్ణాంకం av_gain_map_params_validate(స్థిరరాశి AVGainMapParams *p);

/**
 * Returns 1 if all channels of the gain map have identical parameters,
 * 0 otherwise.
 */
పూర్ణాంకం av_gain_map_channels_identical(స్థిరరాశి AVGainMapParams *p);

/**
 * Allocate an AVGainMapParams structure and initialize it to default values.
 * The resulting pointer must be freed using av_free().
 *
 * @param size if non-NULL, set to sizeof(AVGainMapParams)
 * @return the newly allocated struct, or NULL on failure
 */
AVGainMapParams *av_gain_map_params_alloc(size_t *కొలత);

/**
 * Allocate and add an AVGainMapParams structure to an existing AVFrameSideData
 * array as AV_FRAME_DATA_GAIN_MAP_PARAMS side data.
 *
 * @return the newly allocated struct, or NULL on failure
 */
AVGainMapParams *av_gain_map_params_create_side_దత్తాంశం(AVFrame_Side_దత్తాంశం ***sd, పూర్ణాంకం *nb_sd);

#అయితే_ముగింపు /* AVUTIL_GAIN_MAP_H */

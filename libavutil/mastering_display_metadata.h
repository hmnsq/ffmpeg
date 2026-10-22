/*
 * Copyright (c) 2016 Neil Birkbeck <neil.birkbeck@gmail.com>
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

#यदि_अपरिभाषितम् AVUTIL_MASTERING_DISPLAY_METADATA_H
#परिभाषय AVUTIL_MASTERING_DISPLAY_METADATA_H

#अन्तर्भाव "frame.h"
#अन्तर्भाव "rational.h"


/**
 * Mastering display metadata capable of representing the color volume of
 * the display used to master the content (SMPTE 2086:2014).
 *
 * To be used as payload of a AVFrameSideData or AVPacketSideData with the
 * appropriate type.
 *
 * @note The struct should be allocated with av_mastering_display_metadata_alloc()
 *       and its size is not a part of the public ABI.
 */
प्रकारनिर्देश संरचना AVMasteringDisplayMetadata {
    /**
     * CIE 1931 xy chromaticity coords of color primaries (r, g, b order).
     */
    AVRational display_primaries[3][2];

    /**
     * CIE 1931 xy chromaticity coords of white point.
     */
    AVRational white_point[2];

    /**
     * Min luminance of mastering display (cd/m^2).
     */
    AVRational min_luminance;

    /**
     * Max luminance of mastering display (cd/m^2).
     */
    AVRational max_luminance;

    /**
     * Flag indicating whether the display primaries (and white point) are set.
     */
    पूर्णाङ्क has_primaries;

    /**
     * Flag indicating whether the luminance (min_ and max_) have been set.
     */
    पूर्णाङ्क has_luminance;

} AVMasteringDisplayMetadata;

/**
 * Allocate an AVMasteringDisplayMetadata structure and set its fields to
 * default values. The resulting struct can be freed using av_freep().
 *
 * @return An AVMasteringDisplayMetadata filled with default values or NULL
 *         on failure.
 */
AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(शून्य);

/**
 * Allocate an AVMasteringDisplayMetadata structure and set its fields to
 * default values. The resulting struct can be freed using av_freep().
 *
 * @return An AVMasteringDisplayMetadata filled with default values or NULL
 *         on failure.
 */
AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_आकार(size_t *आकार);

/**
 * Allocate a complete AVMasteringDisplayMetadata and add it to the frame.
 *
 * @param frame The frame which side data is added to.
 *
 * @return The AVMasteringDisplayMetadata structure to be filled by caller.
 */
AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_दत्त(AVFrame *frame);

/**
 * Content light level needed by to transmit HDR over HDMI (CTA-861.3).
 *
 * To be used as payload of a AVFrameSideData or AVPacketSideData with the
 * appropriate type.
 *
 * @note The struct should be allocated with av_content_light_metadata_alloc()
 *       and its size is not a part of the public ABI.
 */
प्रकारनिर्देश संरचना AVContentLightMetadata {
    /**
     * Max content light level (cd/m^2).
     */
    अचिह्नित MaxCLL;

    /**
     * Max average light level per frame (cd/m^2).
     */
    अचिह्नित MaxFALL;
} AVContentLightMetadata;

/**
 * Allocate an AVContentLightMetadata structure and set its fields to
 * default values. The resulting struct can be freed using av_freep().
 *
 * @return An AVContentLightMetadata filled with default values or NULL
 *         on failure.
 */
AVContentLightMetadata *av_content_light_metadata_alloc(size_t *आकार);

/**
 * Allocate a complete AVContentLightMetadata and add it to the frame.
 *
 * @param frame The frame which side data is added to.
 *
 * @return The AVContentLightMetadata structure to be filled by caller.
 */
AVContentLightMetadata *av_content_light_metadata_create_side_दत्त(AVFrame *frame);

#यदि_अन्तः /* AVUTIL_MASTERING_DISPLAY_METADATA_H */

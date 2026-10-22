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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_DETECTION_BBOX_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_DETECTION_BBOX_H

#ਅਨ੍ਤਰ੍ਭਾਵ "rational.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "frame.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVDetectionBBox {
    /**
     * Distance in pixels from the left/top edge of the frame,
     * together with width and height, defining the bounding box.
     */
    ਪੂਰਨ x;
    ਪੂਰਨ y;
    ਪੂਰਨ w;
    ਪੂਰਨ h;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_DETECTION_BBOX_LABEL_NAME_MAX_ਮਾਪ 64

    /**
     * Detect result with confidence
     */
    ਅੱਖਰ detect_label[AV_DETECTION_BBOX_LABEL_NAME_MAX_ਮਾਪ];
    AVRational detect_confidence;

    /**
     * At most 4 classifications based on the detected bounding box.
     * For example, we can get max 4 different attributes with 4 different
     * DNN models on one bounding box.
     * classify_count is zero if no classification.
     */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_ਅੰਕ_DETECTION_BBOX_CLASSIFY 4
    uint32_t classify_ਗਿਣਤੀ;
    ਅੱਖਰ classify_labels[AV_ਅੰਕ_DETECTION_BBOX_CLASSIFY][AV_DETECTION_BBOX_LABEL_NAME_MAX_ਮਾਪ];
    AVRational classify_confidences[AV_ਅੰਕ_DETECTION_BBOX_CLASSIFY];
} AVDetectionBBox;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVDetection_BBox_ਸਿਰਲੇਖ {
    /**
     * Information about how the bounding box is generated.
     * for example, the DNN model name.
     */
    ਅੱਖਰ ਸਰੋਤ[256];

    /**
     * Number of bounding boxes in the array.
     */
    uint32_t nb_bboxes;

    /**
     * Offset in bytes from the beginning of this structure at which
     * the array of bounding boxes starts.
     */
    size_t bboxes_ਵਿੱਥ;

    /**
     * Size of each bounding box in bytes.
     */
    size_t bbox_ਮਾਪ;
} AVDetection_BBox_ਸਿਰਲੇਖ;

/*
 * Get the bounding box at the specified {@code idx}. Must be between 0 and nb_bboxes.
 */
ਸਥਿਰ av_always_inline AVDetectionBBox *
av_get_detection_bbox(ਅਚਲ AVDetection_BBox_ਸਿਰਲੇਖ *ਸਿਰਲੇਖ, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ idx)
{
    av_assert0(idx < ਸਿਰਲੇਖ->nb_bboxes);
    ਵਾਪਸ (AVDetectionBBox *)((uint8_t *)ਸਿਰਲੇਖ + ਸਿਰਲੇਖ->bboxes_ਵਿੱਥ +
                               idx * ਸਿਰਲੇਖ->bbox_ਮਾਪ);
}

/**
 * Allocates memory for AVDetectionBBoxHeader, plus an array of {@code nb_bboxes}
 * AVDetectionBBox, and initializes the variables.
 * Can be freed with a normal av_free() call.
 *
 * @param nb_bboxes number of AVDetectionBBox structures to allocate
 * @param out_size if non-NULL, the size in bytes of the resulting data array is
 * written here.
 */
AVDetection_BBox_ਸਿਰਲੇਖ *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *ਬਾਹਰਲਾ_ਮਾਪ);

/**
 * Allocates memory for AVDetectionBBoxHeader, plus an array of {@code nb_bboxes}
 * AVDetectionBBox, in the given AVFrame {@code frame} as AVFrameSideData of type
 * AV_FRAME_DATA_DETECTION_BBOXES and initializes the variables.
 */
AVDetection_BBox_ਸਿਰਲੇਖ *av_detection_bbox_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ, uint32_t nb_bboxes);
#ਜੇ_ਅੰਤ

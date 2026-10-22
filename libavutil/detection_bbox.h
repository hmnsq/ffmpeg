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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_DETECTION_BBOX_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_DETECTION_BBOX_H

#ಅನ್ತರ್ಭಾವ "rational.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "frame.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDetectionBBox {
    /**
     * Distance in pixels from the left/top edge of the frame,
     * together with width and height, defining the bounding box.
     */
    ಪೂರ್ಣಾಂಕ x;
    ಪೂರ್ಣಾಂಕ y;
    ಪೂರ್ಣಾಂಕ w;
    ಪೂರ್ಣಾಂಕ h;

#ವ್ಯಾಖ್ಯಾನಿಸು AV_DETECTION_BBOX_LABEL_NAME_MAX_ಗಾತ್ರ 64

    /**
     * Detect result with confidence
     */
    ಅಕ್ಷರ detect_label[AV_DETECTION_BBOX_LABEL_NAME_MAX_ಗಾತ್ರ];
    AVRational detect_confidence;

    /**
     * At most 4 classifications based on the detected bounding box.
     * For example, we can get max 4 different attributes with 4 different
     * DNN models on one bounding box.
     * classify_count is zero if no classification.
     */
#ವ್ಯಾಖ್ಯಾನಿಸು AV_ಅಂಕೆ_DETECTION_BBOX_CLASSIFY 4
    uint32_t classify_ಎಣಿಕೆ;
    ಅಕ್ಷರ classify_labels[AV_ಅಂಕೆ_DETECTION_BBOX_CLASSIFY][AV_DETECTION_BBOX_LABEL_NAME_MAX_ಗಾತ್ರ];
    AVRational classify_confidences[AV_ಅಂಕೆ_DETECTION_BBOX_CLASSIFY];
} AVDetectionBBox;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ AVDetection_BBox_ಶೀರ್ಷಿಕೆ {
    /**
     * Information about how the bounding box is generated.
     * for example, the DNN model name.
     */
    ಅಕ್ಷರ ಮೂಲ[256];

    /**
     * Number of bounding boxes in the array.
     */
    uint32_t nb_bboxes;

    /**
     * Offset in bytes from the beginning of this structure at which
     * the array of bounding boxes starts.
     */
    size_t bboxes_ಸ್ಥಾನಾಂತರ;

    /**
     * Size of each bounding box in bytes.
     */
    size_t bbox_ಗಾತ್ರ;
} AVDetection_BBox_ಶೀರ್ಷಿಕೆ;

/*
 * Get the bounding box at the specified {@code idx}. Must be between 0 and nb_bboxes.
 */
ಸ್ಥಿರ av_always_inline AVDetectionBBox *
av_get_detection_bbox(ಸ್ಥಿರಾಂಕ AVDetection_BBox_ಶೀರ್ಷಿಕೆ *ಶೀರ್ಷಿಕೆ, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ idx)
{
    av_assert0(idx < ಶೀರ್ಷಿಕೆ->nb_bboxes);
    ಹಿಂತಿರುಗಿ (AVDetectionBBox *)((uint8_t *)ಶೀರ್ಷಿಕೆ + ಶೀರ್ಷಿಕೆ->bboxes_ಸ್ಥಾನಾಂತರ +
                               idx * ಶೀರ್ಷಿಕೆ->bbox_ಗಾತ್ರ);
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
AVDetection_BBox_ಶೀರ್ಷಿಕೆ *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *ಹೊರಹೋಗು_ಗಾತ್ರ);

/**
 * Allocates memory for AVDetectionBBoxHeader, plus an array of {@code nb_bboxes}
 * AVDetectionBBox, in the given AVFrame {@code frame} as AVFrameSideData of type
 * AV_FRAME_DATA_DETECTION_BBOXES and initializes the variables.
 */
AVDetection_BBox_ಶೀರ್ಷಿಕೆ *av_detection_bbox_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು, uint32_t nb_bboxes);
#ಆದರೆ_ಅಂತ್ಯ

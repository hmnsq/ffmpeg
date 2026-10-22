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

#ifndef AVUTIL_DETECTION_BBOX_H
#define AVUTIL_DETECTION_BBOX_H

#অন্তর্ভাব "rational.h"
#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "frame.h"

প্রকারলেখ কাঠামো AVDetectionBBox {
    /**
     * Distance in pixels from the left/top edge of the frame,
     * together with width and height, defining the bounding box.
     */
    পূর্ণসংখ্যা x;
    পূর্ণসংখ্যা y;
    পূর্ণসংখ্যা w;
    পূর্ণসংখ্যা h;

#define AV_DETECTION_BBOX_LABEL_NAME_MAX_আকার 64

    /**
     * Detect result with confidence
     */
    অক্ষর detect_label[AV_DETECTION_BBOX_LABEL_NAME_MAX_আকার];
    AVRational detect_confidence;

    /**
     * At most 4 classifications based on the detected bounding box.
     * For example, we can get max 4 different attributes with 4 different
     * DNN models on one bounding box.
     * classify_count is zero if no classification.
     */
#define AV_অঙ্ক_DETECTION_BBOX_CLASSIFY 4
    uint32_t classify_গুনতি;
    অক্ষর classify_labels[AV_অঙ্ক_DETECTION_BBOX_CLASSIFY][AV_DETECTION_BBOX_LABEL_NAME_MAX_আকার];
    AVRational classify_confidences[AV_অঙ্ক_DETECTION_BBOX_CLASSIFY];
} AVDetectionBBox;

প্রকারলেখ কাঠামো AVDetectionBBoxHeader {
    /**
     * Information about how the bounding box is generated.
     * for example, the DNN model name.
     */
    অক্ষর source[256];

    /**
     * Number of bounding boxes in the array.
     */
    uint32_t nb_bboxes;

    /**
     * Offset in bytes from the beginning of this structure at which
     * the array of bounding boxes starts.
     */
    size_t bboxes_offset;

    /**
     * Size of each bounding box in bytes.
     */
    size_t bbox_আকার;
} AVDetectionBBoxHeader;

/*
 * Get the bounding box at the specified {@code idx}. Must be between 0 and nb_bboxes.
 */
স্থির av_always_inline AVDetectionBBox *
av_get_detection_bbox(ধ্রুবক AVDetectionBBoxHeader *header, unsigned পূর্ণসংখ্যা idx)
{
    av_assert0(idx < header->nb_bboxes);
    ফেরত (AVDetectionBBox *)((uint8_t *)header + header->bboxes_offset +
                               idx * header->bbox_আকার);
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
AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *out_আকার);

/**
 * Allocates memory for AVDetectionBBoxHeader, plus an array of {@code nb_bboxes}
 * AVDetectionBBox, in the given AVFrame {@code frame} as AVFrameSideData of type
 * AV_FRAME_DATA_DETECTION_BBOXES and initializes the variables.
 */
AVDetectionBBoxHeader *av_detection_bbox_create_side_তথ্য(AVFrame *frame, uint32_t nb_bboxes);
#endif

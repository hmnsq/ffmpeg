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

#اگر_تعریف_نشده AVUTIL_DETECTION_BBOX_H
#تعریف_کن AVUTIL_DETECTION_BBOX_H

#ضمن "rational.h"
#ضمن "avassert.h"
#ضمن "frame.h"

تعريفنوع بنية AVDetectionBBox {
    /**
     * Distance in pixels from the left/top edge of the frame,
     * together with width and height, defining the bounding box.
     */
    صحيح x;
    صحيح y;
    صحيح w;
    صحيح h;

#تعریف_کن AV_DETECTION_BBOX_LABEL_NAME_MAX_اندازه 64

    /**
     * Detect result with confidence
     */
    حرف detect_label[AV_DETECTION_BBOX_LABEL_NAME_MAX_اندازه];
    AVRational detect_confidence;

    /**
     * At most 4 classifications based on the detected bounding box.
     * For example, we can get max 4 different attributes with 4 different
     * DNN models on one bounding box.
     * classify_count is zero if no classification.
     */
#تعریف_کن AV_رقم_DETECTION_BBOX_CLASSIFY 4
    uint32_t classify_شمار;
    حرف classify_labels[AV_رقم_DETECTION_BBOX_CLASSIFY][AV_DETECTION_BBOX_LABEL_NAME_MAX_اندازه];
    AVRational classify_confidences[AV_رقم_DETECTION_BBOX_CLASSIFY];
} AVDetectionBBox;

تعريفنوع بنية AVDetection_BBox_سرآیند {
    /**
     * Information about how the bounding box is generated.
     * for example, the DNN model name.
     */
    حرف منبع[256];

    /**
     * Number of bounding boxes in the array.
     */
    uint32_t nb_bboxes;

    /**
     * Offset in bytes from the beginning of this structure at which
     * the array of bounding boxes starts.
     */
    size_t bboxes_جابه_جایی;

    /**
     * Size of each bounding box in bytes.
     */
    size_t bbox_اندازه;
} AVDetection_BBox_سرآیند;

/*
 * Get the bounding box at the specified {@code idx}. Must be between 0 and nb_bboxes.
 */
ساكن av_always_inline AVDetectionBBox *
av_get_detection_bbox(ثابت AVDetection_BBox_سرآیند *سرآیند, بیعلامت صحيح idx)
{
    av_assert0(idx < سرآیند->nb_bboxes);
    أرجع (AVDetectionBBox *)((uint8_t *)سرآیند + سرآیند->bboxes_جابه_جایی +
                               idx * سرآیند->bbox_اندازه);
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
AVDetection_BBox_سرآیند *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *بیرون_اندازه);

/**
 * Allocates memory for AVDetectionBBoxHeader, plus an array of {@code nb_bboxes}
 * AVDetectionBBox, in the given AVFrame {@code frame} as AVFrameSideData of type
 * AV_FRAME_DATA_DETECTION_BBOXES and initializes the variables.
 */
AVDetection_BBox_سرآیند *av_detection_bbox_create_side_داده(AVFrame *قاب, uint32_t nb_bboxes);
#پایان_اگر

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

#నిర్వచితం_కాకపోతే AVUTIL_DETECTION_BBOX_H
#నిర్వచించు AVUTIL_DETECTION_BBOX_H

#అన్తర్భావ "rational.h"
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "frame.h"

రకనిర్వచనం నిర్మాణం AVDetectionBBox {
    /**
     * Distance in pixels from the left/top edge of the frame,
     * together with width and height, defining the bounding box.
     */
    పూర్ణాంకం x;
    పూర్ణాంకం y;
    పూర్ణాంకం w;
    పూర్ణాంకం h;

#నిర్వచించు AV_DETECTION_BBOX_LABEL_NAME_MAX_కొలత 64

    /**
     * Detect result with confidence
     */
    అక్షరం detect_label[AV_DETECTION_BBOX_LABEL_NAME_MAX_కొలత];
    AVRational detect_confidence;

    /**
     * At most 4 classifications based on the detected bounding box.
     * For example, we can get max 4 different attributes with 4 different
     * DNN models on one bounding box.
     * classify_count is zero if no classification.
     */
#నిర్వచించు AV_అంకె_DETECTION_BBOX_CLASSIFY 4
    uint32_t classify_లెక్క;
    అక్షరం classify_labels[AV_అంకె_DETECTION_BBOX_CLASSIFY][AV_DETECTION_BBOX_LABEL_NAME_MAX_కొలత];
    AVRational classify_confidences[AV_అంకె_DETECTION_BBOX_CLASSIFY];
} AVDetectionBBox;

రకనిర్వచనం నిర్మాణం AVDetection_BBox_శీర్షిక {
    /**
     * Information about how the bounding box is generated.
     * for example, the DNN model name.
     */
    అక్షరం ఆధారం[256];

    /**
     * Number of bounding boxes in the array.
     */
    uint32_t nb_bboxes;

    /**
     * Offset in bytes from the beginning of this structure at which
     * the array of bounding boxes starts.
     */
    size_t bboxes_స్థానభ్రంశం;

    /**
     * Size of each bounding box in bytes.
     */
    size_t bbox_కొలత;
} AVDetection_BBox_శీర్షిక;

/*
 * Get the bounding box at the specified {@code idx}. Must be between 0 and nb_bboxes.
 */
స్థిర av_always_inline AVDetectionBBox *
av_get_detection_bbox(స్థిరరాశి AVDetection_BBox_శీర్షిక *శీర్షిక, గుర్తులేని పూర్ణాంకం idx)
{
    av_assert0(idx < శీర్షిక->nb_bboxes);
    తిరిగి (AVDetectionBBox *)((uint8_t *)శీర్షిక + శీర్షిక->bboxes_స్థానభ్రంశం +
                               idx * శీర్షిక->bbox_కొలత);
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
AVDetection_BBox_శీర్షిక *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *బహిర్గతం_కొలత);

/**
 * Allocates memory for AVDetectionBBoxHeader, plus an array of {@code nb_bboxes}
 * AVDetectionBBox, in the given AVFrame {@code frame} as AVFrameSideData of type
 * AV_FRAME_DATA_DETECTION_BBOXES and initializes the variables.
 */
AVDetection_BBox_శీర్షిక *av_detection_bbox_create_side_దత్తాంశం(AVFrame *చట్రం, uint32_t nb_bboxes);
#అయితే_ముగింపు

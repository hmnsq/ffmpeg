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

#अन्तर्भाव "detection_bbox.h"
#अन्तर्भाव "mem.h"

AVDetection_BBox_शीर्षकम् *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *बहिर्गमनम्_आकार)
{
    size_t आकार;
    संरचना BBoxContext {
        AVDetection_BBox_शीर्षकम् शीर्षकम्;
        AVDetectionBBox boxes;
    };
    ध्रुव size_t bboxes_विस्थापनम् = offsetof(संरचना BBoxContext, boxes);
    ध्रुव size_t bbox_आकार = परिमाण(AVDetectionBBox);
    AVDetection_BBox_शीर्षकम् *शीर्षकम्;

    आकार = bboxes_विस्थापनम्;
    यदि (nb_bboxes > (SIZE_MAX - आकार) / bbox_आकार)
        प्रत्यागम रिक्त;
    आकार += bbox_आकार * nb_bboxes;

    शीर्षकम् = av_mallocz(आकार);
    यदि (!शीर्षकम्)
        प्रत्यागम रिक्त;

    शीर्षकम्->nb_bboxes     = nb_bboxes;
    शीर्षकम्->bbox_आकार     = bbox_आकार;
    शीर्षकम्->bboxes_विस्थापनम् = bboxes_विस्थापनम्;

    यदि (बहिर्गमनम्_आकार)
        *बहिर्गमनम्_आकार = आकार;

    प्रत्यागम शीर्षकम्;
}

AVDetection_BBox_शीर्षकम् *av_detection_bbox_create_side_दत्त(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetection_BBox_शीर्षकम् *शीर्षकम्;
    size_t आकार;

    शीर्षकम् = av_detection_bbox_alloc(nb_bboxes, &आकार);
    यदि (!शीर्षकम्)
        प्रत्यागम रिक्त;
    buf = av_बफर_create((uint8_t *)शीर्षकम्, आकार, रिक्त, रिक्त, 0);
    यदि (!buf) {
        av_freep(&शीर्षकम्);
        प्रत्यागम रिक्त;
    }

    यदि (!av_frame_new_side_दत्त_from_buf(frame, AV_FRAME_दत्त_DETECTION_BBOXES, buf)) {
        av_बफर_unref(&buf);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम शीर्षकम्;
}

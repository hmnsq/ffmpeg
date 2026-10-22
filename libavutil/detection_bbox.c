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

AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, माप_प्रकार *out_size)
{
    माप_प्रकार size;
    संरचना BBoxContext {
        AVDetectionBBoxHeader header;
        AVDetectionBBox boxes;
    };
    स्थिरांक माप_प्रकार bboxes_offset = दुरत्व(संरचना BBoxContext, boxes);
    स्थिरांक माप_प्रकार bbox_size = आकार(AVDetectionBBox);
    AVDetectionBBoxHeader *header;

    size = bboxes_offset;
    जर (nb_bboxes > (SIZE_MAX - size) / bbox_size)
        परत रिक्त;
    size += bbox_size * nb_bboxes;

    header = av_mallocz(size);
    जर (!header)
        परत रिक्त;

    header->nb_bboxes     = nb_bboxes;
    header->bbox_size     = bbox_size;
    header->bboxes_offset = bboxes_offset;

    जर (out_size)
        *out_size = size;

    परत header;
}

AVDetectionBBoxHeader *av_detection_bbox_create_side_data(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetectionBBoxHeader *header;
    माप_प्रकार size;

    header = av_detection_bbox_alloc(nb_bboxes, &size);
    जर (!header)
        परत रिक्त;
    buf = av_buffer_create((uint8_t *)header, size, रिक्त, रिक्त, 0);
    जर (!buf) {
        av_freep(&header);
        परत रिक्त;
    }

    जर (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_DETECTION_BBOXES, buf)) {
        av_buffer_unref(&buf);
        परत रिक्त;
    }

    परत header;
}

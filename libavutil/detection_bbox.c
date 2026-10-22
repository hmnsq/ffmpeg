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

AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *out_size)
{
    size_t size;
    संरचना BBoxContext {
        AVDetectionBBoxHeader header;
        AVDetectionBBox boxes;
    };
    ध्रुव size_t bboxes_offset = offsetof(संरचना BBoxContext, boxes);
    ध्रुव size_t bbox_size = परिमाण(AVDetectionBBox);
    AVDetectionBBoxHeader *header;

    size = bboxes_offset;
    यदि (nb_bboxes > (SIZE_MAX - size) / bbox_size)
        प्रत्यागम रिक्त;
    size += bbox_size * nb_bboxes;

    header = av_mallocz(size);
    यदि (!header)
        प्रत्यागम रिक्त;

    header->nb_bboxes     = nb_bboxes;
    header->bbox_size     = bbox_size;
    header->bboxes_offset = bboxes_offset;

    यदि (out_size)
        *out_size = size;

    प्रत्यागम header;
}

AVDetectionBBoxHeader *av_detection_bbox_create_side_data(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetectionBBoxHeader *header;
    size_t size;

    header = av_detection_bbox_alloc(nb_bboxes, &size);
    यदि (!header)
        प्रत्यागम रिक्त;
    buf = av_buffer_create((uint8_t *)header, size, रिक्त, रिक्त, 0);
    यदि (!buf) {
        av_freep(&header);
        प्रत्यागम रिक्त;
    }

    यदि (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_DETECTION_BBOXES, buf)) {
        av_buffer_unref(&buf);
        प्रत्यागम रिक्त;
    }

    प्रत्यागम header;
}

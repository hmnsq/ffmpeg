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

#ଅନ୍ତର୍ଭାଵ "detection_bbox.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *out_size)
{
    size_t size;
    ସଂରଚନା BBoxContext {
        AVDetectionBBoxHeader header;
        AVDetectionBBox boxes;
    };
    ଅଚଳ size_t bboxes_offset = offsetof(ସଂରଚନା BBoxContext, boxes);
    ଅଚଳ size_t bbox_size = ଆକାର(AVDetectionBBox);
    AVDetectionBBoxHeader *header;

    size = bboxes_offset;
    ଯଦି (nb_bboxes > (SIZE_MAX - size) / bbox_size)
        ଫେରନ୍ତୁ ଖାଲି;
    size += bbox_size * nb_bboxes;

    header = av_mallocz(size);
    ଯଦି (!header)
        ଫେରନ୍ତୁ ଖାଲି;

    header->nb_bboxes     = nb_bboxes;
    header->bbox_size     = bbox_size;
    header->bboxes_offset = bboxes_offset;

    ଯଦି (out_size)
        *out_size = size;

    ଫେରନ୍ତୁ header;
}

AVDetectionBBoxHeader *av_detection_bbox_create_side_data(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetectionBBoxHeader *header;
    size_t size;

    header = av_detection_bbox_alloc(nb_bboxes, &size);
    ଯଦି (!header)
        ଫେରନ୍ତୁ ଖାଲି;
    buf = av_buffer_create((uint8_t *)header, size, ଖାଲି, ଖାଲି, 0);
    ଯଦି (!buf) {
        av_freep(&header);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଯଦି (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_DETECTION_BBOXES, buf)) {
        av_buffer_unref(&buf);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ଫେରନ୍ତୁ header;
}

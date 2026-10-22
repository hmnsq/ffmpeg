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

#অন্তর্ভাব "detection_bbox.h"
#অন্তর্ভাব "mem.h"

AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *out_size)
{
    size_t size;
    সংরচনা BBoxContext {
        AVDetectionBBoxHeader header;
        AVDetectionBBox boxes;
    };
    ধ্রুব size_t bboxes_offset = offsetof(সংরচনা BBoxContext, boxes);
    ধ্রুব size_t bbox_size = পরিমাণ(AVDetectionBBox);
    AVDetectionBBoxHeader *header;

    size = bboxes_offset;
    যদি (nb_bboxes > (SIZE_MAX - size) / bbox_size)
        প্রত্যাগম রিক্ত;
    size += bbox_size * nb_bboxes;

    header = av_mallocz(size);
    যদি (!header)
        প্রত্যাগম রিক্ত;

    header->nb_bboxes     = nb_bboxes;
    header->bbox_size     = bbox_size;
    header->bboxes_offset = bboxes_offset;

    যদি (out_size)
        *out_size = size;

    প্রত্যাগম header;
}

AVDetectionBBoxHeader *av_detection_bbox_create_side_data(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetectionBBoxHeader *header;
    size_t size;

    header = av_detection_bbox_alloc(nb_bboxes, &size);
    যদি (!header)
        প্রত্যাগম রিক্ত;
    buf = av_buffer_create((uint8_t *)header, size, রিক্ত, রিক্ত, 0);
    যদি (!buf) {
        av_freep(&header);
        প্রত্যাগম রিক্ত;
    }

    যদি (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_DETECTION_BBOXES, buf)) {
        av_buffer_unref(&buf);
        প্রত্যাগম রিক্ত;
    }

    প্রত্যাগম header;
}

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

#അന്തര്ഭാവ "detection_bbox.h"
#അന്തര്ഭാവ "mem.h"

AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *out_size)
{
    size_t size;
    ഘടന BBoxContext {
        AVDetectionBBoxHeader header;
        AVDetectionBBox boxes;
    };
    സ്ഥിരം size_t bboxes_offset = offsetof(ഘടന BBoxContext, boxes);
    സ്ഥിരം size_t bbox_size = വലുപ്പം(AVDetectionBBox);
    AVDetectionBBoxHeader *header;

    size = bboxes_offset;
    എങ്കിൽ (nb_bboxes > (SIZE_MAX - size) / bbox_size)
        തിരികെ ശൂന്യ;
    size += bbox_size * nb_bboxes;

    header = av_mallocz(size);
    എങ്കിൽ (!header)
        തിരികെ ശൂന്യ;

    header->nb_bboxes     = nb_bboxes;
    header->bbox_size     = bbox_size;
    header->bboxes_offset = bboxes_offset;

    എങ്കിൽ (out_size)
        *out_size = size;

    തിരികെ header;
}

AVDetectionBBoxHeader *av_detection_bbox_create_side_data(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetectionBBoxHeader *header;
    size_t size;

    header = av_detection_bbox_alloc(nb_bboxes, &size);
    എങ്കിൽ (!header)
        തിരികെ ശൂന്യ;
    buf = av_buffer_create((uint8_t *)header, size, ശൂന്യ, ശൂന്യ, 0);
    എങ്കിൽ (!buf) {
        av_freep(&header);
        തിരികെ ശൂന്യ;
    }

    എങ്കിൽ (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_DETECTION_BBOXES, buf)) {
        av_buffer_unref(&buf);
        തിരികെ ശൂന്യ;
    }

    തിരികെ header;
}

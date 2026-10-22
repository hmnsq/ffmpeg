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

#include "detection_bbox.h"
#include "mem.h"

AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *out_size)
{
    size_t size;
    sa_nracanaa BBoxContext {
        AVDetectionBBoxHeader header;
        AVDetectionBBox boxes;
    };
    const size_t bboxes_offset = offsetof(sa_nracanaa BBoxContext, boxes);
    const size_t bbox_size = parimaa_na(AVDetectionBBox);
    AVDetectionBBoxHeader *header;

    size = bboxes_offset;
    ᨀᨘ (nb_bboxes > (SIZE_MAX - size) / bbox_size)
        ᨀᨘᨒ NULL;
    size += bbox_size * nb_bboxes;

    header = av_mallocz(size);
    ᨀᨘ (!header)
        ᨀᨘᨒ NULL;

    header->nb_bboxes     = nb_bboxes;
    header->bbox_size     = bbox_size;
    header->bboxes_offset = bboxes_offset;

    ᨀᨘ (out_size)
        *out_size = size;

    ᨀᨘᨒ header;
}

AVDetectionBBoxHeader *av_detection_bbox_create_side_data(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetectionBBoxHeader *header;
    size_t size;

    header = av_detection_bbox_alloc(nb_bboxes, &size);
    ᨀᨘ (!header)
        ᨀᨘᨒ NULL;
    buf = av_buffer_create((uint8_t *)header, size, NULL, NULL, 0);
    ᨀᨘ (!buf) {
        av_freep(&header);
        ᨀᨘᨒ NULL;
    }

    ᨀᨘ (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_DETECTION_BBOXES, buf)) {
        av_buffer_unref(&buf);
        ᨀᨘᨒ NULL;
    }

    ᨀᨘᨒ header;
}

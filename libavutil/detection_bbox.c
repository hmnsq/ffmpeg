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

#ಅನ್ತರ್ಭಾವ "detection_bbox.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *out_size)
{
    size_t size;
    ಸಂರಚನಾ BBoxContext {
        AVDetectionBBoxHeader header;
        AVDetectionBBox boxes;
    };
    ಧ್ರುವ size_t bboxes_offset = offsetof(ಸಂರಚನಾ BBoxContext, boxes);
    ಧ್ರುವ size_t bbox_size = ಪರಿಮಾಣ(AVDetectionBBox);
    AVDetectionBBoxHeader *header;

    size = bboxes_offset;
    ಯದಿ (nb_bboxes > (SIZE_MAX - size) / bbox_size)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    size += bbox_size * nb_bboxes;

    header = av_mallocz(size);
    ಯದಿ (!header)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    header->nb_bboxes     = nb_bboxes;
    header->bbox_size     = bbox_size;
    header->bboxes_offset = bboxes_offset;

    ಯದಿ (out_size)
        *out_size = size;

    ಪ್ರತ್ಯಾಗಮ header;
}

AVDetectionBBoxHeader *av_detection_bbox_create_side_data(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetectionBBoxHeader *header;
    size_t size;

    header = av_detection_bbox_alloc(nb_bboxes, &size);
    ಯದಿ (!header)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    buf = av_buffer_create((uint8_t *)header, size, ರಿಕ್ತ, ರಿಕ್ತ, 0);
    ಯದಿ (!buf) {
        av_freep(&header);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಯದಿ (!av_frame_new_side_data_from_buf(frame, AV_FRAME_DATA_DETECTION_BBOXES, buf)) {
        av_buffer_unref(&buf);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪ್ರತ್ಯಾಗಮ header;
}

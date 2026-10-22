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

AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *out_আকার)
{
    size_t আকার_2;
    কাঠামো BBoxContext {
        AVDetectionBBoxHeader header;
        AVDetectionBBox boxes;
    };
    ধ্রুবক size_t bboxes_offset = offsetof(কাঠামো BBoxContext, boxes);
    ধ্রুবক size_t bbox_আকার = আকার(AVDetectionBBox);
    AVDetectionBBoxHeader *header;

    আকার_2 = bboxes_offset;
    যদি (nb_bboxes > (SIZE_MAX - আকার_2) / bbox_আকার)
        ফেরত ফাঁকা;
    আকার_2 += bbox_আকার * nb_bboxes;

    header = av_mallocz(আকার_2);
    যদি (!header)
        ফেরত ফাঁকা;

    header->nb_bboxes     = nb_bboxes;
    header->bbox_আকার     = bbox_আকার;
    header->bboxes_offset = bboxes_offset;

    যদি (out_আকার)
        *out_আকার = আকার_2;

    ফেরত header;
}

AVDetectionBBoxHeader *av_detection_bbox_create_side_তথ্য(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetectionBBoxHeader *header;
    size_t আকার_2;

    header = av_detection_bbox_alloc(nb_bboxes, &আকার_2);
    যদি (!header)
        ফেরত ফাঁকা;
    buf = av_বাফার_create((uint8_t *)header, আকার_2, ফাঁকা, ফাঁকা, 0);
    যদি (!buf) {
        av_freep(&header);
        ফেরত ফাঁকা;
    }

    যদি (!av_frame_new_side_তথ্য_from_buf(frame, AV_FRAME_তথ্য_DETECTION_BBOXES, buf)) {
        av_বাফার_unref(&buf);
        ফেরত ফাঁকা;
    }

    ফেরত header;
}

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

#समावेश "detection_bbox.h"
#समावेश "mem.h"

AVDetectionBBoxHeader *av_detection_bbox_alloc(uint32_t nb_bboxes, माप_प्रकार *out_आकार)
{
    माप_प्रकार आकार;
    काष्ठा BBoxContext {
        AVDetectionBBoxHeader header;
        AVDetectionBBox boxes;
    };
    स्थिर माप_प्रकार bboxes_offset = दुरत्व(काष्ठा BBoxContext, boxes);
    स्थिर माप_प्रकार bbox_आकार = माप(AVDetectionBBox);
    AVDetectionBBoxHeader *header;

    आकार = bboxes_offset;
    अगर (nb_bboxes > (SIZE_MAX - आकार) / bbox_आकार)
        वापस शून्य;
    आकार += bbox_आकार * nb_bboxes;

    header = av_mallocz(आकार);
    अगर (!header)
        वापस शून्य;

    header->nb_bboxes     = nb_bboxes;
    header->bbox_आकार     = bbox_आकार;
    header->bboxes_offset = bboxes_offset;

    अगर (out_आकार)
        *out_आकार = आकार;

    वापस header;
}

AVDetectionBBoxHeader *av_detection_bbox_create_side_तथ्य(AVFrame *frame, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetectionBBoxHeader *header;
    माप_प्रकार आकार;

    header = av_detection_bbox_alloc(nb_bboxes, &आकार);
    अगर (!header)
        वापस शून्य;
    buf = av_बफर_create((uint8_t *)header, आकार, शून्य, शून्य, 0);
    अगर (!buf) {
        av_freep(&header);
        वापस शून्य;
    }

    अगर (!av_frame_new_side_तथ्य_from_buf(frame, AV_FRAME_तथ्य_DETECTION_BBOXES, buf)) {
        av_बफर_unref(&buf);
        वापस शून्य;
    }

    वापस header;
}

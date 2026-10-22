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

#ضمن "detection_bbox.h"
#ضمن "mem.h"

AVDetection_BBox_سرآیند *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *بیرون_اندازه)
{
    size_t اندازه;
    بنية BBoxContext {
        AVDetection_BBox_سرآیند سرآیند;
        AVDetectionBBox boxes;
    };
    ثابت size_t bboxes_جابه_جایی = offsetof(بنية BBoxContext, boxes);
    ثابت size_t bbox_اندازه = حجم(AVDetectionBBox);
    AVDetection_BBox_سرآیند *سرآیند;

    اندازه = bboxes_جابه_جایی;
    إذا (nb_bboxes > (SIZE_MAX - اندازه) / bbox_اندازه)
        أرجع عدم;
    اندازه += bbox_اندازه * nb_bboxes;

    سرآیند = av_mallocz(اندازه);
    إذا (!سرآیند)
        أرجع عدم;

    سرآیند->nb_bboxes     = nb_bboxes;
    سرآیند->bbox_اندازه     = bbox_اندازه;
    سرآیند->bboxes_جابه_جایی = bboxes_جابه_جایی;

    إذا (بیرون_اندازه)
        *بیرون_اندازه = اندازه;

    أرجع سرآیند;
}

AVDetection_BBox_سرآیند *av_detection_bbox_create_side_داده(AVFrame *قاب, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetection_BBox_سرآیند *سرآیند;
    size_t اندازه;

    سرآیند = av_detection_bbox_alloc(nb_bboxes, &اندازه);
    إذا (!سرآیند)
        أرجع عدم;
    buf = av_میانگیر_create((uint8_t *)سرآیند, اندازه, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&سرآیند);
        أرجع عدم;
    }

    إذا (!av_قاب_new_side_داده_from_buf(قاب, AV_قاب_داده_DETECTION_BBOXES, buf)) {
        av_میانگیر_unref(&buf);
        أرجع عدم;
    }

    أرجع سرآیند;
}

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

AVDetection_BBox_سرلیک *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *بهر_اندازه)
{
    size_t اندازه;
    بنية BBoxContext {
        AVDetection_BBox_سرلیک سرلیک;
        AVDetectionBBox boxes;
    };
    ثابت size_t bboxes_دننه_واټن = offsetof(بنية BBoxContext, boxes);
    ثابت size_t bbox_اندازه = حجم(AVDetectionBBox);
    AVDetection_BBox_سرلیک *سرلیک;

    اندازه = bboxes_دننه_واټن;
    إذا (nb_bboxes > (SIZE_MAX - اندازه) / bbox_اندازه)
        أرجع عدم;
    اندازه += bbox_اندازه * nb_bboxes;

    سرلیک = av_mallocz(اندازه);
    إذا (!سرلیک)
        أرجع عدم;

    سرلیک->nb_bboxes     = nb_bboxes;
    سرلیک->bbox_اندازه     = bbox_اندازه;
    سرلیک->bboxes_دننه_واټن = bboxes_دننه_واټن;

    إذا (بهر_اندازه)
        *بهر_اندازه = اندازه;

    أرجع سرلیک;
}

AVDetection_BBox_سرلیک *av_detection_bbox_create_side_معلومات(AVFrame *چوکاټ, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetection_BBox_سرلیک *سرلیک;
    size_t اندازه;

    سرلیک = av_detection_bbox_alloc(nb_bboxes, &اندازه);
    إذا (!سرلیک)
        أرجع عدم;
    buf = av_بفر_create((uint8_t *)سرلیک, اندازه, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&سرلیک);
        أرجع عدم;
    }

    إذا (!av_چوکاټ_new_side_معلومات_from_buf(چوکاټ, AV_چوکاټ_معلومات_DETECTION_BBOXES, buf)) {
        av_بفر_unref(&buf);
        أرجع عدم;
    }

    أرجع سرلیک;
}

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

AVDetection_BBox_سرو *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *ٻاهريون_سائيز)
{
    size_t سائيز;
    بنية BBoxContext {
        AVDetection_BBox_سرو سرو;
        AVDetectionBBox boxes;
    };
    ثابت size_t bboxes_وٿي = offsetof(بنية BBoxContext, boxes);
    ثابت size_t bbox_سائيز = حجم(AVDetectionBBox);
    AVDetection_BBox_سرو *سرو;

    سائيز = bboxes_وٿي;
    إذا (nb_bboxes > (SIZE_MAX - سائيز) / bbox_سائيز)
        أرجع عدم;
    سائيز += bbox_سائيز * nb_bboxes;

    سرو = av_mallocz(سائيز);
    إذا (!سرو)
        أرجع عدم;

    سرو->nb_bboxes     = nb_bboxes;
    سرو->bbox_سائيز     = bbox_سائيز;
    سرو->bboxes_وٿي = bboxes_وٿي;

    إذا (ٻاهريون_سائيز)
        *ٻاهريون_سائيز = سائيز;

    أرجع سرو;
}

AVDetection_BBox_سرو *av_detection_bbox_create_side_معلومات(AVFrame *چوکٺو, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetection_BBox_سرو *سرو;
    size_t سائيز;

    سرو = av_detection_bbox_alloc(nb_bboxes, &سائيز);
    إذا (!سرو)
        أرجع عدم;
    buf = av_بفر_create((uint8_t *)سرو, سائيز, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&سرو);
        أرجع عدم;
    }

    إذا (!av_چوکٺو_new_side_معلومات_from_buf(چوکٺو, AV_چوکٺو_معلومات_DETECTION_BBOXES, buf)) {
        av_بفر_unref(&buf);
        أرجع عدم;
    }

    أرجع سرو;
}

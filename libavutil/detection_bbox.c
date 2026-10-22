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

AVDetection_BBox_سرخی *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *باہرلا_ناپ)
{
    size_t ناپ;
    بنية BBoxContext {
        AVDetection_BBox_سرخی سرخی;
        AVDetectionBBox boxes;
    };
    ثابت size_t bboxes_وتھ = offsetof(بنية BBoxContext, boxes);
    ثابت size_t bbox_ناپ = حجم(AVDetectionBBox);
    AVDetection_BBox_سرخی *سرخی;

    ناپ = bboxes_وتھ;
    إذا (nb_bboxes > (SIZE_MAX - ناپ) / bbox_ناپ)
        أرجع عدم;
    ناپ += bbox_ناپ * nb_bboxes;

    سرخی = av_mallocz(ناپ);
    إذا (!سرخی)
        أرجع عدم;

    سرخی->nb_bboxes     = nb_bboxes;
    سرخی->bbox_ناپ     = bbox_ناپ;
    سرخی->bboxes_وتھ = bboxes_وتھ;

    إذا (باہرلا_ناپ)
        *باہرلا_ناپ = ناپ;

    أرجع سرخی;
}

AVDetection_BBox_سرخی *av_detection_bbox_create_side_انکڑے(AVFrame *چوکھٹا, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetection_BBox_سرخی *سرخی;
    size_t ناپ;

    سرخی = av_detection_bbox_alloc(nb_bboxes, &ناپ);
    إذا (!سرخی)
        أرجع عدم;
    buf = av_بفر_create((uint8_t *)سرخی, ناپ, عدم, عدم, 0);
    إذا (!buf) {
        av_freep(&سرخی);
        أرجع عدم;
    }

    إذا (!av_چوکھٹا_new_side_انکڑے_from_buf(چوکھٹا, AV_چوکھٹا_انکڑے_DETECTION_BBOXES, buf)) {
        av_بفر_unref(&buf);
        أرجع عدم;
    }

    أرجع سرخی;
}

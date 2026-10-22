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

#شامل "detection_bbox.h"
#شامل "mem.h"

AVDetection_BBox_سرخی *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *برآمد_سائز)
{
    size_t سائز;
    ساخت BBoxContext {
        AVDetection_BBox_سرخی سرخی;
        AVDetectionBBox boxes;
    };
    ثابت size_t bboxes_انحراف = offsetof(ساخت BBoxContext, boxes);
    ثابت size_t bbox_سائز = حجم(AVDetectionBBox);
    AVDetection_BBox_سرخی *سرخی;

    سائز = bboxes_انحراف;
    اگر (nb_bboxes > (SIZE_MAX - سائز) / bbox_سائز)
        واپس تہی;
    سائز += bbox_سائز * nb_bboxes;

    سرخی = av_mallocz(سائز);
    اگر (!سرخی)
        واپس تہی;

    سرخی->nb_bboxes     = nb_bboxes;
    سرخی->bbox_سائز     = bbox_سائز;
    سرخی->bboxes_انحراف = bboxes_انحراف;

    اگر (برآمد_سائز)
        *برآمد_سائز = سائز;

    واپس سرخی;
}

AVDetection_BBox_سرخی *av_detection_bbox_create_side_ڈیٹا(AVFrame *چوکھٹا, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetection_BBox_سرخی *سرخی;
    size_t سائز;

    سرخی = av_detection_bbox_alloc(nb_bboxes, &سائز);
    اگر (!سرخی)
        واپس تہی;
    buf = av_بفر_create((uint8_t *)سرخی, سائز, تہی, تہی, 0);
    اگر (!buf) {
        av_freep(&سرخی);
        واپس تہی;
    }

    اگر (!av_چوکھٹا_new_side_ڈیٹا_from_buf(چوکھٹا, AV_چوکھٹا_ڈیٹا_DETECTION_BBOXES, buf)) {
        av_بفر_unref(&buf);
        واپس تہی;
    }

    واپس سرخی;
}

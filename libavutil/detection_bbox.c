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

#ਅਨ੍ਤਰ੍ਭਾਵ "detection_bbox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

AVDetection_BBox_ਸਿਰਲੇਖ *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *ਬਾਹਰਲਾ_ਮਾਪ)
{
    size_t ਮਾਪ;
    ਬਣਤਰ BBoxContext {
        AVDetection_BBox_ਸਿਰਲੇਖ ਸਿਰਲੇਖ;
        AVDetectionBBox boxes;
    };
    ਅਚਲ size_t bboxes_ਵਿੱਥ = offsetof(ਬਣਤਰ BBoxContext, boxes);
    ਅਚਲ size_t bbox_ਮਾਪ = ਆਕਾਰ(AVDetectionBBox);
    AVDetection_BBox_ਸਿਰਲੇਖ *ਸਿਰਲੇਖ;

    ਮਾਪ = bboxes_ਵਿੱਥ;
    ਜੇ (nb_bboxes > (SIZE_MAX - ਮਾਪ) / bbox_ਮਾਪ)
        ਵਾਪਸ ਨਿਰਾ;
    ਮਾਪ += bbox_ਮਾਪ * nb_bboxes;

    ਸਿਰਲੇਖ = av_mallocz(ਮਾਪ);
    ਜੇ (!ਸਿਰਲੇਖ)
        ਵਾਪਸ ਨਿਰਾ;

    ਸਿਰਲੇਖ->nb_bboxes     = nb_bboxes;
    ਸਿਰਲੇਖ->bbox_ਮਾਪ     = bbox_ਮਾਪ;
    ਸਿਰਲੇਖ->bboxes_ਵਿੱਥ = bboxes_ਵਿੱਥ;

    ਜੇ (ਬਾਹਰਲਾ_ਮਾਪ)
        *ਬਾਹਰਲਾ_ਮਾਪ = ਮਾਪ;

    ਵਾਪਸ ਸਿਰਲੇਖ;
}

AVDetection_BBox_ਸਿਰਲੇਖ *av_detection_bbox_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetection_BBox_ਸਿਰਲੇਖ *ਸਿਰਲੇਖ;
    size_t ਮਾਪ;

    ਸਿਰਲੇਖ = av_detection_bbox_alloc(nb_bboxes, &ਮਾਪ);
    ਜੇ (!ਸਿਰਲੇਖ)
        ਵਾਪਸ ਨਿਰਾ;
    buf = av_ਬਫਰ_create((uint8_t *)ਸਿਰਲੇਖ, ਮਾਪ, ਨਿਰਾ, ਨਿਰਾ, 0);
    ਜੇ (!buf) {
        av_freep(&ਸਿਰਲੇਖ);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਜੇ (!av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ_from_buf(ਚੌਖਟਾ, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DETECTION_BBOXES, buf)) {
        av_ਬਫਰ_unref(&buf);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਵਾਪਸ ਸਿਰਲੇਖ;
}

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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/detection_bbox.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVDetection_BBox_ਸਿਰਲੇਖ *ਸਿਰਲੇਖ;
    AVDetectionBBox *bbox;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ;

    ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    ਲਿਖੋ("Testing av_detection_bbox_alloc()\n");
    ਲਈ (ਪੂਰਨ i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ nb = alloc_counts[i];
        ਸਿਰਲੇਖ = av_detection_bbox_alloc(nb, &ਮਾਪ);
        ਜੇ (ਸਿਰਲੇਖ) {
            ਲਿਖੋ("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, ਸਿਰਲੇਖ->nb_bboxes, ਮਾਪ > 0 ? "yes" : "no");
            av_free(ਸਿਰਲੇਖ);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    ਸਿਰਲੇਖ = av_detection_bbox_alloc(1, ਨਿਰਾ);
    ਲਿਖੋ("alloc (no size): %s\n", ਸਿਰਲੇਖ ? "OK" : "FAIL");
    av_free(ਸਿਰਲੇਖ);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    ਲਿਖੋ("\nTesting av_get_detection_bbox()\n");
    ਸਿਰਲੇਖ = av_detection_bbox_alloc(3, ਨਿਰਾ);
    ਜੇ (ਸਿਰਲੇਖ) {
        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(ਸਿਰਲੇਖ, i);
            ਜੇ ((uint8_t *)bbox != (uint8_t *)ਸਿਰਲੇਖ + ਸਿਰਲੇਖ->bboxes_ਵਿੱਥ +
                                   (size_t)i * ਸਿਰਲੇਖ->bbox_ਮਾਪ)
                ਲਿਖੋ("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, ਆਕਾਰ(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(ਸਿਰਲੇਖ, i);
            ਲਿਖੋ("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.ਅੰਕ,
                   bbox->detect_confidence.den);
        }
        av_free(ਸਿਰਲੇਖ);
    }

    /* classify fields */
    ਲਿਖੋ("\nTesting classify fields\n");
    ਸਿਰਲੇਖ = av_detection_bbox_alloc(1, ਨਿਰਾ);
    ਜੇ (ਸਿਰਲੇਖ) {
        bbox = av_get_detection_bbox(ਸਿਰਲੇਖ, 0);
        bbox->classify_ਗਿਣਤੀ = 2;
        snprintf(bbox->classify_labels[0], ਆਕਾਰ(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], ਆਕਾਰ(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        ਲਿਖੋ("classify_count=%u\n", bbox->classify_ਗਿਣਤੀ);
        ਲਈ (ਪੂਰਨ i = 0; i < (ਪੂਰਨ)bbox->classify_ਗਿਣਤੀ; i++)
            ਲਿਖੋ("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].ਅੰਕ,
                   bbox->classify_confidences[i].den);
        av_free(ਸਿਰਲੇਖ);
    }

    /* header source field */
    ਲਿਖੋ("\nTesting source field\n");
    ਸਿਰਲੇਖ = av_detection_bbox_alloc(1, ਨਿਰਾ);
    ਜੇ (ਸਿਰਲੇਖ) {
        snprintf(ਸਿਰਲੇਖ->ਸਰੋਤ, ਆਕਾਰ(ਸਿਰਲੇਖ->ਸਰੋਤ), "test_model_v1");
        ਲਿਖੋ("source: %s\n", ਸਿਰਲੇਖ->ਸਰੋਤ);
        av_free(ਸਿਰਲੇਖ);
    }

    /* av_detection_bbox_create_side_data */
    ਲਿਖੋ("\nTesting av_detection_bbox_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        ਸਿਰਲੇਖ = av_detection_bbox_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ, 2);
        ਜੇ (ਸਿਰਲੇਖ) {
            ਲਿਖੋ("side_data: OK, nb=%u\n", ਸਿਰਲੇਖ->nb_bboxes);
            bbox = av_get_detection_bbox(ਸਿਰਲੇਖ, 0);
            bbox->x = 10;
            bbox->y = 20;
            ਲਿਖੋ("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("side_data: FAIL\n");
        }
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    ਵਾਪਸ 0;
}

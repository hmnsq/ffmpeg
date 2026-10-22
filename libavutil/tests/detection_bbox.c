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

#ضمن <stdint.h>
#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/detection_bbox.h"
#ضمن "libavutil/frame.h"
#ضمن "libavutil/macros.h"
#ضمن "libavutil/mem.h"

صحيح مکيه(فراغ)
{
    AVDetection_BBox_سرو *سرو;
    AVDetectionBBox *bbox;
    AVFrame *چوکٺو;
    size_t سائيز;

    ساكن ثابت بنانشان صحيح alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    لکو("Testing av_detection_bbox_alloc()\n");
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        بنانشان صحيح nb = alloc_counts[i];
        سرو = av_detection_bbox_alloc(nb, &سائيز);
        إذا (سرو) {
            لکو("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, سرو->nb_bboxes, سائيز > 0 ? "yes" : "no");
            av_free(سرو);
        } وإلا {
            لکو("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    سرو = av_detection_bbox_alloc(1, عدم);
    لکو("alloc (no size): %s\n", سرو ? "OK" : "FAIL");
    av_free(سرو);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    لکو("\nTesting av_get_detection_bbox()\n");
    سرو = av_detection_bbox_alloc(3, عدم);
    إذا (سرو) {
        لكل (صحيح i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(سرو, i);
            إذا ((uint8_t *)bbox != (uint8_t *)سرو + سرو->bboxes_وٿي +
                                   (size_t)i * سرو->bbox_سائيز)
                لکو("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, حجم(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        لكل (صحيح i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(سرو, i);
            لکو("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.انگ,
                   bbox->detect_confidence.den);
        }
        av_free(سرو);
    }

    /* classify fields */
    لکو("\nTesting classify fields\n");
    سرو = av_detection_bbox_alloc(1, عدم);
    إذا (سرو) {
        bbox = av_get_detection_bbox(سرو, 0);
        bbox->classify_ڳڻپ = 2;
        snprintf(bbox->classify_labels[0], حجم(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], حجم(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        لکو("classify_count=%u\n", bbox->classify_ڳڻپ);
        لكل (صحيح i = 0; i < (صحيح)bbox->classify_ڳڻپ; i++)
            لکو("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].انگ,
                   bbox->classify_confidences[i].den);
        av_free(سرو);
    }

    /* header source field */
    لکو("\nTesting source field\n");
    سرو = av_detection_bbox_alloc(1, عدم);
    إذا (سرو) {
        snprintf(سرو->ذريعو, حجم(سرو->ذريعو), "test_model_v1");
        لکو("source: %s\n", سرو->ذريعو);
        av_free(سرو);
    }

    /* av_detection_bbox_create_side_data */
    لکو("\nTesting av_detection_bbox_create_side_data()\n");
    چوکٺو = av_چوکٺو_alloc();
    إذا (چوکٺو) {
        سرو = av_detection_bbox_create_side_معلومات(چوکٺو, 2);
        إذا (سرو) {
            لکو("side_data: OK, nb=%u\n", سرو->nb_bboxes);
            bbox = av_get_detection_bbox(سرو, 0);
            bbox->x = 10;
            bbox->y = 20;
            لکو("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } وإلا {
            لکو("side_data: FAIL\n");
        }
        av_چوکٺو_free(&چوکٺو);
    }

    أرجع 0;
}

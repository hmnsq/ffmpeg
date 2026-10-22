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

صحيح اصلي(فراغ)
{
    AVDetection_BBox_سرلیک *سرلیک;
    AVDetectionBBox *bbox;
    AVFrame *چوکاټ;
    size_t اندازه;

    ساكن ثابت بینښه صحيح alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    چاپ_کړه("Testing av_detection_bbox_alloc()\n");
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        بینښه صحيح nb = alloc_counts[i];
        سرلیک = av_detection_bbox_alloc(nb, &اندازه);
        إذا (سرلیک) {
            چاپ_کړه("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, سرلیک->nb_bboxes, اندازه > 0 ? "yes" : "no");
            av_free(سرلیک);
        } وإلا {
            چاپ_کړه("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    سرلیک = av_detection_bbox_alloc(1, عدم);
    چاپ_کړه("alloc (no size): %s\n", سرلیک ? "OK" : "FAIL");
    av_free(سرلیک);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    چاپ_کړه("\nTesting av_get_detection_bbox()\n");
    سرلیک = av_detection_bbox_alloc(3, عدم);
    إذا (سرلیک) {
        لكل (صحيح i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(سرلیک, i);
            إذا ((uint8_t *)bbox != (uint8_t *)سرلیک + سرلیک->bboxes_دننه_واټن +
                                   (size_t)i * سرلیک->bbox_اندازه)
                چاپ_کړه("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, حجم(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        لكل (صحيح i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(سرلیک, i);
            چاپ_کړه("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.عدد,
                   bbox->detect_confidence.den);
        }
        av_free(سرلیک);
    }

    /* classify fields */
    چاپ_کړه("\nTesting classify fields\n");
    سرلیک = av_detection_bbox_alloc(1, عدم);
    إذا (سرلیک) {
        bbox = av_get_detection_bbox(سرلیک, 0);
        bbox->classify_شمېر = 2;
        snprintf(bbox->classify_labels[0], حجم(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], حجم(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        چاپ_کړه("classify_count=%u\n", bbox->classify_شمېر);
        لكل (صحيح i = 0; i < (صحيح)bbox->classify_شمېر; i++)
            چاپ_کړه("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].عدد,
                   bbox->classify_confidences[i].den);
        av_free(سرلیک);
    }

    /* header source field */
    چاپ_کړه("\nTesting source field\n");
    سرلیک = av_detection_bbox_alloc(1, عدم);
    إذا (سرلیک) {
        snprintf(سرلیک->سرچینه, حجم(سرلیک->سرچینه), "test_model_v1");
        چاپ_کړه("source: %s\n", سرلیک->سرچینه);
        av_free(سرلیک);
    }

    /* av_detection_bbox_create_side_data */
    چاپ_کړه("\nTesting av_detection_bbox_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        سرلیک = av_detection_bbox_create_side_معلومات(چوکاټ, 2);
        إذا (سرلیک) {
            چاپ_کړه("side_data: OK, nb=%u\n", سرلیک->nb_bboxes);
            bbox = av_get_detection_bbox(سرلیک, 0);
            bbox->x = 10;
            bbox->y = 20;
            چاپ_کړه("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } وإلا {
            چاپ_کړه("side_data: FAIL\n");
        }
        av_چوکاټ_free(&چوکاټ);
    }

    أرجع 0;
}

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

صحيح اصلی(فراغ)
{
    AVDetection_BBox_سرآیند *سرآیند;
    AVDetectionBBox *bbox;
    AVFrame *قاب;
    size_t اندازه;

    ساكن ثابت بیعلامت صحيح alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    چاپ_کن("Testing av_detection_bbox_alloc()\n");
    لكل (صحيح i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        بیعلامت صحيح nb = alloc_counts[i];
        سرآیند = av_detection_bbox_alloc(nb, &اندازه);
        إذا (سرآیند) {
            چاپ_کن("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, سرآیند->nb_bboxes, اندازه > 0 ? "yes" : "no");
            av_free(سرآیند);
        } وإلا {
            چاپ_کن("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    سرآیند = av_detection_bbox_alloc(1, عدم);
    چاپ_کن("alloc (no size): %s\n", سرآیند ? "OK" : "FAIL");
    av_free(سرآیند);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    چاپ_کن("\nTesting av_get_detection_bbox()\n");
    سرآیند = av_detection_bbox_alloc(3, عدم);
    إذا (سرآیند) {
        لكل (صحيح i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(سرآیند, i);
            إذا ((uint8_t *)bbox != (uint8_t *)سرآیند + سرآیند->bboxes_جابه_جایی +
                                   (size_t)i * سرآیند->bbox_اندازه)
                چاپ_کن("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, حجم(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        لكل (صحيح i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(سرآیند, i);
            چاپ_کن("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.رقم,
                   bbox->detect_confidence.den);
        }
        av_free(سرآیند);
    }

    /* classify fields */
    چاپ_کن("\nTesting classify fields\n");
    سرآیند = av_detection_bbox_alloc(1, عدم);
    إذا (سرآیند) {
        bbox = av_get_detection_bbox(سرآیند, 0);
        bbox->classify_شمار = 2;
        snprintf(bbox->classify_labels[0], حجم(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], حجم(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        چاپ_کن("classify_count=%u\n", bbox->classify_شمار);
        لكل (صحيح i = 0; i < (صحيح)bbox->classify_شمار; i++)
            چاپ_کن("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].رقم,
                   bbox->classify_confidences[i].den);
        av_free(سرآیند);
    }

    /* header source field */
    چاپ_کن("\nTesting source field\n");
    سرآیند = av_detection_bbox_alloc(1, عدم);
    إذا (سرآیند) {
        snprintf(سرآیند->منبع, حجم(سرآیند->منبع), "test_model_v1");
        چاپ_کن("source: %s\n", سرآیند->منبع);
        av_free(سرآیند);
    }

    /* av_detection_bbox_create_side_data */
    چاپ_کن("\nTesting av_detection_bbox_create_side_data()\n");
    قاب = av_قاب_alloc();
    إذا (قاب) {
        سرآیند = av_detection_bbox_create_side_داده(قاب, 2);
        إذا (سرآیند) {
            چاپ_کن("side_data: OK, nb=%u\n", سرآیند->nb_bboxes);
            bbox = av_get_detection_bbox(سرآیند, 0);
            bbox->x = 10;
            bbox->y = 20;
            چاپ_کن("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } وإلا {
            چاپ_کن("side_data: FAIL\n");
        }
        av_قاب_free(&قاب);
    }

    أرجع 0;
}

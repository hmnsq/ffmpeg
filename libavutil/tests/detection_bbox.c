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

#شامل <stdint.h>
#شامل <stdio.h>
#شامل <string.h>

#شامل "libavutil/detection_bbox.h"
#شامل "libavutil/frame.h"
#شامل "libavutil/macros.h"
#شامل "libavutil/mem.h"

صحیح مین(خالی)
{
    AVDetection_BBox_سرخی *سرخی;
    AVDetectionBBox *bbox;
    AVFrame *چوکھٹا;
    size_t سائز;

    ساکن ثابت غیرعلامتی صحیح alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    لکھو("Testing av_detection_bbox_alloc()\n");
    برائے (صحیح i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        غیرعلامتی صحیح nb = alloc_counts[i];
        سرخی = av_detection_bbox_alloc(nb, &سائز);
        اگر (سرخی) {
            لکھو("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, سرخی->nb_bboxes, سائز > 0 ? "yes" : "no");
            av_free(سرخی);
        } ورنہ {
            لکھو("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    سرخی = av_detection_bbox_alloc(1, تہی);
    لکھو("alloc (no size): %s\n", سرخی ? "OK" : "FAIL");
    av_free(سرخی);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    لکھو("\nTesting av_get_detection_bbox()\n");
    سرخی = av_detection_bbox_alloc(3, تہی);
    اگر (سرخی) {
        برائے (صحیح i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(سرخی, i);
            اگر ((uint8_t *)bbox != (uint8_t *)سرخی + سرخی->bboxes_انحراف +
                                   (size_t)i * سرخی->bbox_سائز)
                لکھو("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, حجم(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        برائے (صحیح i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(سرخی, i);
            لکھو("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.عدد,
                   bbox->detect_confidence.den);
        }
        av_free(سرخی);
    }

    /* classify fields */
    لکھو("\nTesting classify fields\n");
    سرخی = av_detection_bbox_alloc(1, تہی);
    اگر (سرخی) {
        bbox = av_get_detection_bbox(سرخی, 0);
        bbox->classify_گنتی = 2;
        snprintf(bbox->classify_labels[0], حجم(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], حجم(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        لکھو("classify_count=%u\n", bbox->classify_گنتی);
        برائے (صحیح i = 0; i < (صحیح)bbox->classify_گنتی; i++)
            لکھو("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].عدد,
                   bbox->classify_confidences[i].den);
        av_free(سرخی);
    }

    /* header source field */
    لکھو("\nTesting source field\n");
    سرخی = av_detection_bbox_alloc(1, تہی);
    اگر (سرخی) {
        snprintf(سرخی->ماخذ, حجم(سرخی->ماخذ), "test_model_v1");
        لکھو("source: %s\n", سرخی->ماخذ);
        av_free(سرخی);
    }

    /* av_detection_bbox_create_side_data */
    لکھو("\nTesting av_detection_bbox_create_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    اگر (چوکھٹا) {
        سرخی = av_detection_bbox_create_side_ڈیٹا(چوکھٹا, 2);
        اگر (سرخی) {
            لکھو("side_data: OK, nb=%u\n", سرخی->nb_bboxes);
            bbox = av_get_detection_bbox(سرخی, 0);
            bbox->x = 10;
            bbox->y = 20;
            لکھو("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } ورنہ {
            لکھو("side_data: FAIL\n");
        }
        av_چوکھٹا_free(&چوکھٹا);
    }

    واپس 0;
}

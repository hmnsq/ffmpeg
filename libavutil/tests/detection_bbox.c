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

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/detection_bbox.h"
#অন্তর্ভাব "libavutil/frame.h"
#অন্তর্ভাব "libavutil/macros.h"
#অন্তর্ভাব "libavutil/mem.h"

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    AVDetectionBBoxHeader *header;
    AVDetectionBBox *bbox;
    AVFrame *frame;
    size_t আকার_2;

    স্থির ধ্রুবক unsigned পূর্ণসংখ্যা alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    printf("Testing av_detection_bbox_alloc()\n");
    জন্য (পূর্ণসংখ্যা i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        unsigned পূর্ণসংখ্যা nb = alloc_counts[i];
        header = av_detection_bbox_alloc(nb, &আকার_2);
        যদি (header) {
            printf("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, header->nb_bboxes, আকার_2 > 0 ? "yes" : "no");
            av_free(header);
        } অন্যথা {
            printf("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    header = av_detection_bbox_alloc(1, ফাঁকা);
    printf("alloc (no size): %s\n", header ? "OK" : "FAIL");
    av_free(header);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    printf("\nTesting av_get_detection_bbox()\n");
    header = av_detection_bbox_alloc(3, ফাঁকা);
    যদি (header) {
        জন্য (পূর্ণসংখ্যা i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            যদি ((uint8_t *)bbox != (uint8_t *)header + header->bboxes_offset +
                                   (size_t)i * header->bbox_আকার)
                printf("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, আকার(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        জন্য (পূর্ণসংখ্যা i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            printf("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.অঙ্ক,
                   bbox->detect_confidence.den);
        }
        av_free(header);
    }

    /* classify fields */
    printf("\nTesting classify fields\n");
    header = av_detection_bbox_alloc(1, ফাঁকা);
    যদি (header) {
        bbox = av_get_detection_bbox(header, 0);
        bbox->classify_গুনতি = 2;
        snprintf(bbox->classify_labels[0], আকার(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], আকার(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        printf("classify_count=%u\n", bbox->classify_গুনতি);
        জন্য (পূর্ণসংখ্যা i = 0; i < (পূর্ণসংখ্যা)bbox->classify_গুনতি; i++)
            printf("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].অঙ্ক,
                   bbox->classify_confidences[i].den);
        av_free(header);
    }

    /* header source field */
    printf("\nTesting source field\n");
    header = av_detection_bbox_alloc(1, ফাঁকা);
    যদি (header) {
        snprintf(header->source, আকার(header->source), "test_model_v1");
        printf("source: %s\n", header->source);
        av_free(header);
    }

    /* av_detection_bbox_create_side_data */
    printf("\nTesting av_detection_bbox_create_side_data()\n");
    frame = av_frame_alloc();
    যদি (frame) {
        header = av_detection_bbox_create_side_তথ্য(frame, 2);
        যদি (header) {
            printf("side_data: OK, nb=%u\n", header->nb_bboxes);
            bbox = av_get_detection_bbox(header, 0);
            bbox->x = 10;
            bbox->y = 20;
            printf("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } অন্যথা {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    ফেরত 0;
}

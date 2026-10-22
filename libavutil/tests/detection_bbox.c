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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/detection_bbox.h"
#ಅನ್ತರ್ಭಾವ "libavutil/frame.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    AVDetectionBBoxHeader *header;
    AVDetectionBBox *bbox;
    AVFrame *frame;
    size_t size;

    ಸ್ಥಿರ ಧ್ರುವ unsigned ಪೂರ್ಣಾಙ್ಕ alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    printf("Testing av_detection_bbox_alloc()\n");
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        unsigned ಪೂರ್ಣಾಙ್ಕ nb = alloc_counts[i];
        header = av_detection_bbox_alloc(nb, &size);
        ಯದಿ (header) {
            printf("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, header->nb_bboxes, size > 0 ? "yes" : "no");
            av_free(header);
        } ಅನ್ಯಥಾ {
            printf("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    header = av_detection_bbox_alloc(1, ರಿಕ್ತ);
    printf("alloc (no size): %s\n", header ? "OK" : "FAIL");
    av_free(header);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    printf("\nTesting av_get_detection_bbox()\n");
    header = av_detection_bbox_alloc(3, ರಿಕ್ತ);
    ಯದಿ (header) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            ಯದಿ ((uint8_t *)bbox != (uint8_t *)header + header->bboxes_offset +
                                   (size_t)i * header->bbox_size)
                printf("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, ಪರಿಮಾಣ(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            printf("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.ಅಂಕೆ,
                   bbox->detect_confidence.den);
        }
        av_free(header);
    }

    /* classify fields */
    printf("\nTesting classify fields\n");
    header = av_detection_bbox_alloc(1, ರಿಕ್ತ);
    ಯದಿ (header) {
        bbox = av_get_detection_bbox(header, 0);
        bbox->classify_ಎಣಿಕೆ = 2;
        snprintf(bbox->classify_labels[0], ಪರಿಮಾಣ(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], ಪರಿಮಾಣ(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        printf("classify_count=%u\n", bbox->classify_ಎಣಿಕೆ);
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < (ಪೂರ್ಣಾಙ್ಕ)bbox->classify_ಎಣಿಕೆ; i++)
            printf("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].ಅಂಕೆ,
                   bbox->classify_confidences[i].den);
        av_free(header);
    }

    /* header source field */
    printf("\nTesting source field\n");
    header = av_detection_bbox_alloc(1, ರಿಕ್ತ);
    ಯದಿ (header) {
        snprintf(header->source, ಪರಿಮಾಣ(header->source), "test_model_v1");
        printf("source: %s\n", header->source);
        av_free(header);
    }

    /* av_detection_bbox_create_side_data */
    printf("\nTesting av_detection_bbox_create_side_data()\n");
    frame = av_frame_alloc();
    ಯದಿ (frame) {
        header = av_detection_bbox_create_side_data(frame, 2);
        ಯದಿ (header) {
            printf("side_data: OK, nb=%u\n", header->nb_bboxes);
            bbox = av_get_detection_bbox(header, 0);
            bbox->x = 10;
            bbox->y = 20;
            printf("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } ಅನ್ಯಥಾ {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

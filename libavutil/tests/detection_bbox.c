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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/detection_bbox.h"
#अन्तर्भाव "libavutil/frame.h"
#अन्तर्भाव "libavutil/macros.h"
#अन्तर्भाव "libavutil/mem.h"

पूर्णाङ्क main(शून्य)
{
    AVDetectionBBoxHeader *header;
    AVDetectionBBox *bbox;
    AVFrame *frame;
    size_t size;

    स्थिर ध्रुव unsigned पूर्णाङ्क alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    printf("Testing av_detection_bbox_alloc()\n");
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        unsigned पूर्णाङ्क nb = alloc_counts[i];
        header = av_detection_bbox_alloc(nb, &size);
        यदि (header) {
            printf("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, header->nb_bboxes, size > 0 ? "yes" : "no");
            av_free(header);
        } अन्यथा {
            printf("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    header = av_detection_bbox_alloc(1, रिक्त);
    printf("alloc (no size): %s\n", header ? "OK" : "FAIL");
    av_free(header);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    printf("\nTesting av_get_detection_bbox()\n");
    header = av_detection_bbox_alloc(3, रिक्त);
    यदि (header) {
        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            यदि ((uint8_t *)bbox != (uint8_t *)header + header->bboxes_offset +
                                   (size_t)i * header->bbox_size)
                printf("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, परिमाण(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            printf("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.अंक,
                   bbox->detect_confidence.den);
        }
        av_free(header);
    }

    /* classify fields */
    printf("\nTesting classify fields\n");
    header = av_detection_bbox_alloc(1, रिक्त);
    यदि (header) {
        bbox = av_get_detection_bbox(header, 0);
        bbox->classify_मोजणी = 2;
        snprintf(bbox->classify_labels[0], परिमाण(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], परिमाण(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        printf("classify_count=%u\n", bbox->classify_मोजणी);
        प्रति (पूर्णाङ्क i = 0; i < (पूर्णाङ्क)bbox->classify_मोजणी; i++)
            printf("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].अंक,
                   bbox->classify_confidences[i].den);
        av_free(header);
    }

    /* header source field */
    printf("\nTesting source field\n");
    header = av_detection_bbox_alloc(1, रिक्त);
    यदि (header) {
        snprintf(header->source, परिमाण(header->source), "test_model_v1");
        printf("source: %s\n", header->source);
        av_free(header);
    }

    /* av_detection_bbox_create_side_data */
    printf("\nTesting av_detection_bbox_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        header = av_detection_bbox_create_side_data(frame, 2);
        यदि (header) {
            printf("side_data: OK, nb=%u\n", header->nb_bboxes);
            bbox = av_get_detection_bbox(header, 0);
            bbox->x = 10;
            bbox->y = 20;
            printf("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } अन्यथा {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    प्रत्यागम 0;
}

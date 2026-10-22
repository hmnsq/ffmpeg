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

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "libavutil/detection_bbox.h"
#അന്തര്ഭാവ "libavutil/frame.h"
#അന്തര്ഭാവ "libavutil/macros.h"
#അന്തര്ഭാവ "libavutil/mem.h"

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    AVDetectionBBoxHeader *header;
    AVDetectionBBox *bbox;
    AVFrame *frame;
    size_t size;

    സ്ഥിതം സ്ഥിരം unsigned പൂർണ്ണസംഖ്യ alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    printf("Testing av_detection_bbox_alloc()\n");
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        unsigned പൂർണ്ണസംഖ്യ nb = alloc_counts[i];
        header = av_detection_bbox_alloc(nb, &size);
        എങ്കിൽ (header) {
            printf("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, header->nb_bboxes, size > 0 ? "yes" : "no");
            av_free(header);
        } അല്ലെങ്കിൽ {
            printf("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    header = av_detection_bbox_alloc(1, ശൂന്യ);
    printf("alloc (no size): %s\n", header ? "OK" : "FAIL");
    av_free(header);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    printf("\nTesting av_get_detection_bbox()\n");
    header = av_detection_bbox_alloc(3, ശൂന്യ);
    എങ്കിൽ (header) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            എങ്കിൽ ((uint8_t *)bbox != (uint8_t *)header + header->bboxes_offset +
                                   (size_t)i * header->bbox_size)
                printf("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, വലുപ്പം(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            printf("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.അക്കം,
                   bbox->detect_confidence.den);
        }
        av_free(header);
    }

    /* classify fields */
    printf("\nTesting classify fields\n");
    header = av_detection_bbox_alloc(1, ശൂന്യ);
    എങ്കിൽ (header) {
        bbox = av_get_detection_bbox(header, 0);
        bbox->classify_എണ്ണം = 2;
        snprintf(bbox->classify_labels[0], വലുപ്പം(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], വലുപ്പം(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        printf("classify_count=%u\n", bbox->classify_എണ്ണം);
        വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < (പൂർണ്ണസംഖ്യ)bbox->classify_എണ്ണം; i++)
            printf("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].അക്കം,
                   bbox->classify_confidences[i].den);
        av_free(header);
    }

    /* header source field */
    printf("\nTesting source field\n");
    header = av_detection_bbox_alloc(1, ശൂന്യ);
    എങ്കിൽ (header) {
        snprintf(header->source, വലുപ്പം(header->source), "test_model_v1");
        printf("source: %s\n", header->source);
        av_free(header);
    }

    /* av_detection_bbox_create_side_data */
    printf("\nTesting av_detection_bbox_create_side_data()\n");
    frame = av_frame_alloc();
    എങ്കിൽ (frame) {
        header = av_detection_bbox_create_side_data(frame, 2);
        എങ്കിൽ (header) {
            printf("side_data: OK, nb=%u\n", header->nb_bboxes);
            bbox = av_get_detection_bbox(header, 0);
            bbox->x = 10;
            bbox->y = 20;
            printf("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } അല്ലെങ്കിൽ {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    തിരികെ 0;
}

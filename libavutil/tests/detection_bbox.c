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

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVDetection_BBox_ಶೀರ್ಷಿಕೆ *ಶೀರ್ಷಿಕೆ;
    AVDetectionBBox *bbox;
    AVFrame *ಚೌಕಟ್ಟು;
    size_t ಗಾತ್ರ_2;

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    ಬರೆ("Testing av_detection_bbox_alloc()\n");
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ nb = alloc_counts[i];
        ಶೀರ್ಷಿಕೆ = av_detection_bbox_alloc(nb, &ಗಾತ್ರ_2);
        ಆದರೆ (ಶೀರ್ಷಿಕೆ) {
            ಬರೆ("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, ಶೀರ್ಷಿಕೆ->nb_bboxes, ಗಾತ್ರ_2 > 0 ? "yes" : "no");
            av_free(ಶೀರ್ಷಿಕೆ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    ಶೀರ್ಷಿಕೆ = av_detection_bbox_alloc(1, ಖಾಲಿ);
    ಬರೆ("alloc (no size): %s\n", ಶೀರ್ಷಿಕೆ ? "OK" : "FAIL");
    av_free(ಶೀರ್ಷಿಕೆ);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    ಬರೆ("\nTesting av_get_detection_bbox()\n");
    ಶೀರ್ಷಿಕೆ = av_detection_bbox_alloc(3, ಖಾಲಿ);
    ಆದರೆ (ಶೀರ್ಷಿಕೆ) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(ಶೀರ್ಷಿಕೆ, i);
            ಆದರೆ ((uint8_t *)bbox != (uint8_t *)ಶೀರ್ಷಿಕೆ + ಶೀರ್ಷಿಕೆ->bboxes_ಸ್ಥಾನಾಂತರ +
                                   (size_t)i * ಶೀರ್ಷಿಕೆ->bbox_ಗಾತ್ರ)
                ಬರೆ("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, ಗಾತ್ರ(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(ಶೀರ್ಷಿಕೆ, i);
            ಬರೆ("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.ಅಂಕೆ,
                   bbox->detect_confidence.den);
        }
        av_free(ಶೀರ್ಷಿಕೆ);
    }

    /* classify fields */
    ಬರೆ("\nTesting classify fields\n");
    ಶೀರ್ಷಿಕೆ = av_detection_bbox_alloc(1, ಖಾಲಿ);
    ಆದರೆ (ಶೀರ್ಷಿಕೆ) {
        bbox = av_get_detection_bbox(ಶೀರ್ಷಿಕೆ, 0);
        bbox->classify_ಎಣಿಕೆ = 2;
        snprintf(bbox->classify_labels[0], ಗಾತ್ರ(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], ಗಾತ್ರ(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        ಬರೆ("classify_count=%u\n", bbox->classify_ಎಣಿಕೆ);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < (ಪೂರ್ಣಾಂಕ)bbox->classify_ಎಣಿಕೆ; i++)
            ಬರೆ("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].ಅಂಕೆ,
                   bbox->classify_confidences[i].den);
        av_free(ಶೀರ್ಷಿಕೆ);
    }

    /* header source field */
    ಬರೆ("\nTesting source field\n");
    ಶೀರ್ಷಿಕೆ = av_detection_bbox_alloc(1, ಖಾಲಿ);
    ಆದರೆ (ಶೀರ್ಷಿಕೆ) {
        snprintf(ಶೀರ್ಷಿಕೆ->ಮೂಲ, ಗಾತ್ರ(ಶೀರ್ಷಿಕೆ->ಮೂಲ), "test_model_v1");
        ಬರೆ("source: %s\n", ಶೀರ್ಷಿಕೆ->ಮೂಲ);
        av_free(ಶೀರ್ಷಿಕೆ);
    }

    /* av_detection_bbox_create_side_data */
    ಬರೆ("\nTesting av_detection_bbox_create_side_data()\n");
    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        ಶೀರ್ಷಿಕೆ = av_detection_bbox_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು, 2);
        ಆದರೆ (ಶೀರ್ಷಿಕೆ) {
            ಬರೆ("side_data: OK, nb=%u\n", ಶೀರ್ಷಿಕೆ->nb_bboxes);
            bbox = av_get_detection_bbox(ಶೀರ್ಷಿಕೆ, 0);
            bbox->x = 10;
            bbox->y = 20;
            ಬರೆ("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("side_data: FAIL\n");
        }
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    ಹಿಂತಿರುಗಿ 0;
}

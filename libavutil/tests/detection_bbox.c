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

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVDetection_BBox_शीर्षकम् *शीर्षकम्;
    AVDetectionBBox *bbox;
    AVFrame *frame;
    size_t आकार;

    स्थिर ध्रुव अचिह्नित पूर्णाङ्क alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    प्रारूप_लिख("Testing av_detection_bbox_alloc()\n");
    प्रति (पूर्णाङ्क i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        अचिह्नित पूर्णाङ्क nb = alloc_counts[i];
        शीर्षकम् = av_detection_bbox_alloc(nb, &आकार);
        यदि (शीर्षकम्) {
            प्रारूप_लिख("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, शीर्षकम्->nb_bboxes, आकार > 0 ? "yes" : "no");
            av_free(शीर्षकम्);
        } अन्यथा {
            प्रारूप_लिख("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    शीर्षकम् = av_detection_bbox_alloc(1, रिक्त);
    प्रारूप_लिख("alloc (no size): %s\n", शीर्षकम् ? "OK" : "FAIL");
    av_free(शीर्षकम्);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    प्रारूप_लिख("\nTesting av_get_detection_bbox()\n");
    शीर्षकम् = av_detection_bbox_alloc(3, रिक्त);
    यदि (शीर्षकम्) {
        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(शीर्षकम्, i);
            यदि ((uint8_t *)bbox != (uint8_t *)शीर्षकम् + शीर्षकम्->bboxes_विस्थापनम् +
                                   (size_t)i * शीर्षकम्->bbox_आकार)
                प्रारूप_लिख("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, परिमाण(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(शीर्षकम्, i);
            प्रारूप_लिख("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.अङ्कः,
                   bbox->detect_confidence.den);
        }
        av_free(शीर्षकम्);
    }

    /* classify fields */
    प्रारूप_लिख("\nTesting classify fields\n");
    शीर्षकम् = av_detection_bbox_alloc(1, रिक्त);
    यदि (शीर्षकम्) {
        bbox = av_get_detection_bbox(शीर्षकम्, 0);
        bbox->classify_गणनम् = 2;
        snprintf(bbox->classify_labels[0], परिमाण(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], परिमाण(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        प्रारूप_लिख("classify_count=%u\n", bbox->classify_गणनम्);
        प्रति (पूर्णाङ्क i = 0; i < (पूर्णाङ्क)bbox->classify_गणनम्; i++)
            प्रारूप_लिख("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].अङ्कः,
                   bbox->classify_confidences[i].den);
        av_free(शीर्षकम्);
    }

    /* header source field */
    प्रारूप_लिख("\nTesting source field\n");
    शीर्षकम् = av_detection_bbox_alloc(1, रिक्त);
    यदि (शीर्षकम्) {
        snprintf(शीर्षकम्->source, परिमाण(शीर्षकम्->source), "test_model_v1");
        प्रारूप_लिख("source: %s\n", शीर्षकम्->source);
        av_free(शीर्षकम्);
    }

    /* av_detection_bbox_create_side_data */
    प्रारूप_लिख("\nTesting av_detection_bbox_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        शीर्षकम् = av_detection_bbox_create_side_दत्त(frame, 2);
        यदि (शीर्षकम्) {
            प्रारूप_लिख("side_data: OK, nb=%u\n", शीर्षकम्->nb_bboxes);
            bbox = av_get_detection_bbox(शीर्षकम्, 0);
            bbox->x = 10;
            bbox->y = 20;
            प्रारूप_लिख("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } अन्यथा {
            प्रारूप_लिख("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    प्रत्यागम 0;
}

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

#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/detection_bbox.h"
#समावेश "libavutil/frame.h"
#समावेश "libavutil/macros.h"
#समावेश "libavutil/mem.h"

पूर्णांक मुख्य(व्योम)
{
    AVDetectionBBoxHeader *header;
    AVDetectionBBox *bbox;
    AVFrame *frame;
    माप_प्रकार आकार;

    अटल स्थिर अचिन्हित पूर्णांक alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    म_लिखो("Testing av_detection_bbox_alloc()\n");
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        अचिन्हित पूर्णांक nb = alloc_counts[i];
        header = av_detection_bbox_alloc(nb, &आकार);
        अगर (header) {
            म_लिखो("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, header->nb_bboxes, आकार > 0 ? "yes" : "no");
            av_free(header);
        } अन्यथा {
            म_लिखो("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    header = av_detection_bbox_alloc(1, शून्य);
    म_लिखो("alloc (no size): %s\n", header ? "OK" : "FAIL");
    av_free(header);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    म_लिखो("\nTesting av_get_detection_bbox()\n");
    header = av_detection_bbox_alloc(3, शून्य);
    अगर (header) {
        क्रम (पूर्णांक i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            अगर ((uint8_t *)bbox != (uint8_t *)header + header->bboxes_offset +
                                   (माप_प्रकार)i * header->bbox_आकार)
                म_लिखो("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, माप(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        क्रम (पूर्णांक i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(header, i);
            म_लिखो("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.अंक,
                   bbox->detect_confidence.den);
        }
        av_free(header);
    }

    /* classify fields */
    म_लिखो("\nTesting classify fields\n");
    header = av_detection_bbox_alloc(1, शून्य);
    अगर (header) {
        bbox = av_get_detection_bbox(header, 0);
        bbox->classify_गिनती = 2;
        snprintf(bbox->classify_labels[0], माप(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], माप(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        म_लिखो("classify_count=%u\n", bbox->classify_गिनती);
        क्रम (पूर्णांक i = 0; i < (पूर्णांक)bbox->classify_गिनती; i++)
            म_लिखो("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].अंक,
                   bbox->classify_confidences[i].den);
        av_free(header);
    }

    /* header source field */
    म_लिखो("\nTesting source field\n");
    header = av_detection_bbox_alloc(1, शून्य);
    अगर (header) {
        snprintf(header->source, माप(header->source), "test_model_v1");
        म_लिखो("source: %s\n", header->source);
        av_free(header);
    }

    /* av_detection_bbox_create_side_data */
    म_लिखो("\nTesting av_detection_bbox_create_side_data()\n");
    frame = av_frame_alloc();
    अगर (frame) {
        header = av_detection_bbox_create_side_तथ्य(frame, 2);
        अगर (header) {
            म_लिखो("side_data: OK, nb=%u\n", header->nb_bboxes);
            bbox = av_get_detection_bbox(header, 0);
            bbox->x = 10;
            bbox->y = 20;
            म_लिखो("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } अन्यथा {
            म_लिखो("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    वापस 0;
}

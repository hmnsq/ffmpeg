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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/detection_bbox.h"
#అన్తర్భావ "libavutil/frame.h"
#అన్తర్భావ "libavutil/macros.h"
#అన్తర్భావ "libavutil/mem.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVDetection_BBox_శీర్షిక *శీర్షిక;
    AVDetectionBBox *bbox;
    AVFrame *చట్రం;
    size_t కొలత;

    స్థిర స్థిరరాశి గుర్తులేని పూర్ణాంకం alloc_counts[] = { 0, 1, 4 };

    /* av_detection_bbox_alloc - various counts */
    రాయి("Testing av_detection_bbox_alloc()\n");
    కొరకు (పూర్ణాంకం i = 0; i < FF_ARRAY_ELEMS(alloc_counts); i++) {
        గుర్తులేని పూర్ణాంకం nb = alloc_counts[i];
        శీర్షిక = av_detection_bbox_alloc(nb, &కొలత);
        ఒకవేళ (శీర్షిక) {
            రాయి("alloc %u: OK, nb=%u, size>0=%s\n",
                   nb, శీర్షిక->nb_bboxes, కొలత > 0 ? "yes" : "no");
            av_free(శీర్షిక);
        } లేకపోతే {
            రాయి("alloc %u: FAIL\n", nb);
        }
    }

    /* av_detection_bbox_alloc without size */
    శీర్షిక = av_detection_bbox_alloc(1, ఖాళీ);
    రాయి("alloc (no size): %s\n", శీర్షిక ? "OK" : "FAIL");
    av_free(శీర్షిక);

    /* av_get_detection_bbox - pointer consistency and write/read back */
    రాయి("\nTesting av_get_detection_bbox()\n");
    శీర్షిక = av_detection_bbox_alloc(3, ఖాళీ);
    ఒకవేళ (శీర్షిక) {
        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(శీర్షిక, i);
            ఒకవేళ ((uint8_t *)bbox != (uint8_t *)శీర్షిక + శీర్షిక->bboxes_స్థానభ్రంశం +
                                   (size_t)i * శీర్షిక->bbox_కొలత)
                రాయి("bbox %d: pointer inconsistent with bboxes_offset/bbox_size\n", i);
            bbox->x = i * 100;
            bbox->y = i * 200;
            bbox->w = 50 + i;
            bbox->h = 60 + i;
            snprintf(bbox->detect_label, పరిమాణం(bbox->detect_label),
                     "obj%d", i);
            bbox->detect_confidence = (AVRational){ 90 + i, 100 };
        }
        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            bbox = av_get_detection_bbox(శీర్షిక, i);
            రాయి("bbox %d: x=%d y=%d w=%d h=%d label=%s conf=%d/%d\n",
                   i, bbox->x, bbox->y, bbox->w, bbox->h,
                   bbox->detect_label,
                   bbox->detect_confidence.అంకె,
                   bbox->detect_confidence.den);
        }
        av_free(శీర్షిక);
    }

    /* classify fields */
    రాయి("\nTesting classify fields\n");
    శీర్షిక = av_detection_bbox_alloc(1, ఖాళీ);
    ఒకవేళ (శీర్షిక) {
        bbox = av_get_detection_bbox(శీర్షిక, 0);
        bbox->classify_లెక్క = 2;
        snprintf(bbox->classify_labels[0], పరిమాణం(bbox->classify_labels[0]),
                 "cat");
        bbox->classify_confidences[0] = (AVRational){ 95, 100 };
        snprintf(bbox->classify_labels[1], పరిమాణం(bbox->classify_labels[1]),
                 "animal");
        bbox->classify_confidences[1] = (AVRational){ 80, 100 };
        రాయి("classify_count=%u\n", bbox->classify_లెక్క);
        కొరకు (పూర్ణాంకం i = 0; i < (పూర్ణాంకం)bbox->classify_లెక్క; i++)
            రాయి("classify %d: %s %d/%d\n", i,
                   bbox->classify_labels[i],
                   bbox->classify_confidences[i].అంకె,
                   bbox->classify_confidences[i].den);
        av_free(శీర్షిక);
    }

    /* header source field */
    రాయి("\nTesting source field\n");
    శీర్షిక = av_detection_bbox_alloc(1, ఖాళీ);
    ఒకవేళ (శీర్షిక) {
        snprintf(శీర్షిక->ఆధారం, పరిమాణం(శీర్షిక->ఆధారం), "test_model_v1");
        రాయి("source: %s\n", శీర్షిక->ఆధారం);
        av_free(శీర్షిక);
    }

    /* av_detection_bbox_create_side_data */
    రాయి("\nTesting av_detection_bbox_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        శీర్షిక = av_detection_bbox_create_side_దత్తాంశం(చట్రం, 2);
        ఒకవేళ (శీర్షిక) {
            రాయి("side_data: OK, nb=%u\n", శీర్షిక->nb_bboxes);
            bbox = av_get_detection_bbox(శీర్షిక, 0);
            bbox->x = 10;
            bbox->y = 20;
            రాయి("side_data bbox 0: x=%d y=%d\n", bbox->x, bbox->y);
        } లేకపోతే {
            రాయి("side_data: FAIL\n");
        }
        av_చట్రం_free(&చట్రం);
    }

    తిరిగి 0;
}

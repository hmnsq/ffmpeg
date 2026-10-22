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

#అన్తర్భావ "detection_bbox.h"
#అన్తర్భావ "mem.h"

AVDetection_BBox_శీర్షిక *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *బహిర్గతం_కొలత)
{
    size_t కొలత;
    నిర్మాణం BBoxContext {
        AVDetection_BBox_శీర్షిక శీర్షిక;
        AVDetectionBBox boxes;
    };
    స్థిరరాశి size_t bboxes_స్థానభ్రంశం = offsetof(నిర్మాణం BBoxContext, boxes);
    స్థిరరాశి size_t bbox_కొలత = పరిమాణం(AVDetectionBBox);
    AVDetection_BBox_శీర్షిక *శీర్షిక;

    కొలత = bboxes_స్థానభ్రంశం;
    ఒకవేళ (nb_bboxes > (SIZE_MAX - కొలత) / bbox_కొలత)
        తిరిగి ఖాళీ;
    కొలత += bbox_కొలత * nb_bboxes;

    శీర్షిక = av_mallocz(కొలత);
    ఒకవేళ (!శీర్షిక)
        తిరిగి ఖాళీ;

    శీర్షిక->nb_bboxes     = nb_bboxes;
    శీర్షిక->bbox_కొలత     = bbox_కొలత;
    శీర్షిక->bboxes_స్థానభ్రంశం = bboxes_స్థానభ్రంశం;

    ఒకవేళ (బహిర్గతం_కొలత)
        *బహిర్గతం_కొలత = కొలత;

    తిరిగి శీర్షిక;
}

AVDetection_BBox_శీర్షిక *av_detection_bbox_create_side_దత్తాంశం(AVFrame *చట్రం, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetection_BBox_శీర్షిక *శీర్షిక;
    size_t కొలత;

    శీర్షిక = av_detection_bbox_alloc(nb_bboxes, &కొలత);
    ఒకవేళ (!శీర్షిక)
        తిరిగి ఖాళీ;
    buf = av_బఫరు_create((uint8_t *)శీర్షిక, కొలత, ఖాళీ, ఖాళీ, 0);
    ఒకవేళ (!buf) {
        av_freep(&శీర్షిక);
        తిరిగి ఖాళీ;
    }

    ఒకవేళ (!av_చట్రం_new_side_దత్తాంశం_from_buf(చట్రం, AV_చట్రం_దత్తాంశం_DETECTION_BBOXES, buf)) {
        av_బఫరు_unref(&buf);
        తిరిగి ఖాళీ;
    }

    తిరిగి శీర్షిక;
}

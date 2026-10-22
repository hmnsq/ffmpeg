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

#ಅನ್ತರ್ಭಾವ "detection_bbox.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

AVDetection_BBox_ಶೀರ್ಷಿಕೆ *av_detection_bbox_alloc(uint32_t nb_bboxes, size_t *ಹೊರಹೋಗು_ಗಾತ್ರ)
{
    size_t ಗಾತ್ರ_2;
    ರಚನೆ BBoxContext {
        AVDetection_BBox_ಶೀರ್ಷಿಕೆ ಶೀರ್ಷಿಕೆ;
        AVDetectionBBox boxes;
    };
    ಸ್ಥಿರಾಂಕ size_t bboxes_ಸ್ಥಾನಾಂತರ = offsetof(ರಚನೆ BBoxContext, boxes);
    ಸ್ಥಿರಾಂಕ size_t bbox_ಗಾತ್ರ = ಗಾತ್ರ(AVDetectionBBox);
    AVDetection_BBox_ಶೀರ್ಷಿಕೆ *ಶೀರ್ಷಿಕೆ;

    ಗಾತ್ರ_2 = bboxes_ಸ್ಥಾನಾಂತರ;
    ಆದರೆ (nb_bboxes > (SIZE_MAX - ಗಾತ್ರ_2) / bbox_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಗಾತ್ರ_2 += bbox_ಗಾತ್ರ * nb_bboxes;

    ಶೀರ್ಷಿಕೆ = av_mallocz(ಗಾತ್ರ_2);
    ಆದರೆ (!ಶೀರ್ಷಿಕೆ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಶೀರ್ಷಿಕೆ->nb_bboxes     = nb_bboxes;
    ಶೀರ್ಷಿಕೆ->bbox_ಗಾತ್ರ     = bbox_ಗಾತ್ರ;
    ಶೀರ್ಷಿಕೆ->bboxes_ಸ್ಥಾನಾಂತರ = bboxes_ಸ್ಥಾನಾಂತರ;

    ಆದರೆ (ಹೊರಹೋಗು_ಗಾತ್ರ)
        *ಹೊರಹೋಗು_ಗಾತ್ರ = ಗಾತ್ರ_2;

    ಹಿಂತಿರುಗಿ ಶೀರ್ಷಿಕೆ;
}

AVDetection_BBox_ಶೀರ್ಷಿಕೆ *av_detection_bbox_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು, uint32_t nb_bboxes)
{
    AVBufferRef         *buf;
    AVDetection_BBox_ಶೀರ್ಷಿಕೆ *ಶೀರ್ಷಿಕೆ;
    size_t ಗಾತ್ರ_2;

    ಶೀರ್ಷಿಕೆ = av_detection_bbox_alloc(nb_bboxes, &ಗಾತ್ರ_2);
    ಆದರೆ (!ಶೀರ್ಷಿಕೆ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    buf = av_ಬಫರ್_create((uint8_t *)ಶೀರ್ಷಿಕೆ, ಗಾತ್ರ_2, ಖಾಲಿ, ಖಾಲಿ, 0);
    ಆದರೆ (!buf) {
        av_freep(&ಶೀರ್ಷಿಕೆ);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ_from_buf(ಚೌಕಟ್ಟು, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DETECTION_BBOXES, buf)) {
        av_ಬಫರ್_unref(&buf);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಹಿಂತಿರುಗಿ ಶೀರ್ಷಿಕೆ;
}

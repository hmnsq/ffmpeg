/**
 * Copyright (c) 2018 Mohammad Izadi <moh.izadi at gmail.com>
 *
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

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "hdr_dynamic_metadata.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "libavcodec/defs.h"
#ಅನ್ತರ್ಭಾವ "libavcodec/get_bits.h"
#ಅನ್ತರ್ಭಾವ "libavcodec/put_bits.h"

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ int64_t luminance_den = 1;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ int32_t peak_luminance_den = 15;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ int64_t rgb_den = 100000;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ int32_t fraction_pixel_den = 1000;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ int32_t knee_ಬಿಂದು_den = 4095;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ int32_t bezier_anchor_den = 1023;
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ int32_t saturation_ತೂಕ_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *ಗಾತ್ರ_2)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(ಗಾತ್ರ(AVDynamicHDRPlus));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = hdr_plus ? ಗಾತ್ರ(*hdr_plus) : 0;

    ಹಿಂತಿರುಗಿ hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFrame_Side_ದತ್ತಾಂಶ *side_ದತ್ತಾಂಶ = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು,
                                                        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DYNAMIC_HDR_PLUS,
                                                        ಗಾತ್ರ(AVDynamicHDRPlus));
    ಆದರೆ (!side_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    memset(side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(AVDynamicHDRPlus));

    ಹಿಂತಿರುಗಿ (AVDynamicHDRPlus *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ;
}

ಪೂರ್ಣಾಂಕ av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, ಸ್ಥಿರಾಂಕ uint8_t *ದತ್ತಾಂಶ,
                                 size_t ಗಾತ್ರ_2)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_ಗಾತ್ರ + AV_ಒಳಹರಿವು_ಬಫರ್_PADDING_ಗಾತ್ರ];
    Get_ಬಿಟ್_Context gbc, *gb = &gbc;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!s)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (ಗಾತ್ರ_2 > AV_HDR_PLUS_MAX_PAYLOAD_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಸ್ಮರಣೆ_ನಕಲು(padded_buf, ದತ್ತಾಂಶ, ಗಾತ್ರ_2);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + ಗಾತ್ರ_2, 0, AV_ಒಳಹರಿವು_ಬಫರ್_PADDING_ಗಾತ್ರ);

    ret = init_get_bits8(gb, padded_buf, ಗಾತ್ರ_2);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 10)
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

    s->application_ಆವೃತ್ತಿ = get_ಬಿಟ್ಟುಗಳು(gb, 8);
    s->ಅಂಕೆ_windows = get_ಬಿಟ್ಟುಗಳು(gb, 2);

    ಆದರೆ (s->ಅಂಕೆ_windows < 1 || s->ಅಂಕೆ_windows > 3) {
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
    }

    ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < ((19 * 8 + 1) * (s->ಅಂಕೆ_windows - 1)))
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 1; w < s->ಅಂಕೆ_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_x =
            (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 16), 1};
        params->ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_y =
            (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 16), 1};
        params->ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_x =
            (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 16), 1};
        params->ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_y =
            (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 16), 1};

        params->center_ದ_ellipse_x = get_ಬಿಟ್ಟುಗಳು(gb, 16);
        params->center_ದ_ellipse_y = get_ಬಿಟ್ಟುಗಳು(gb, 16);
        params->rotation_angle = get_ಬಿಟ್ಟುಗಳು(gb, 8);
        params->semimajor_axis_ಆಂತರಿಕ_ellipse = get_ಬಿಟ್ಟುಗಳು(gb, 16);
        params->semimajor_axis_external_ellipse = get_ಬಿಟ್ಟುಗಳು(gb, 16);
        params->semiminor_axis_external_ellipse = get_ಬಿಟ್ಟುಗಳು(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 28)
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

    s->targeted_system_display_ಗರಿಷ್ಠ_luminance =
        (AVRational){get_ಬಿಟ್ಟುಗಳು_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    ಆದರೆ (s->targeted_system_display_actual_peak_luminance_flag) {
        ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲುಗಳು, ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ;
        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 10)
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
        ಅಡ್ಡಸಾಲುಗಳು = get_ಬಿಟ್ಟುಗಳು(gb, 5);
        ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ = get_ಬಿಟ್ಟುಗಳು(gb, 5);
        ಆದರೆ (((ಅಡ್ಡಸಾಲುಗಳು < 2) || (ಅಡ್ಡಸಾಲುಗಳು > 25)) || ((ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ < 2) || (ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ > 25))) {
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
        }
        s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_targeted_system_display_actual_peak_luminance = ಅಡ್ಡಸಾಲುಗಳು;
        s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_targeted_system_display_actual_peak_luminance = ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ;

        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < (ಅಡ್ಡಸಾಲುಗಳು * ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ * 4))
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಡ್ಡಸಾಲುಗಳು; i++) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 4), peak_luminance_den};
            }
        }
    }
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 0; w < s->ಅಂಕೆ_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < (3 * 17 + 17 + 4))
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 17), rgb_den};
        }
        params->ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb =
            (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 17), rgb_den};
        params->ಅಂಕೆ_distribution_maxrgb_percentiles = get_ಬಿಟ್ಟುಗಳು(gb, 4);

        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) <
            (params->ಅಂಕೆ_distribution_maxrgb_percentiles * 24))
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < params->ಅಂಕೆ_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_ಬಿಟ್ಟುಗಳು(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 17), rgb_den};
        }

        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 10)
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 10), fraction_pixel_den};
    }
    ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 1)
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    ಆದರೆ (s->mastering_display_actual_peak_luminance_flag) {
        ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲುಗಳು, ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ;
        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 10)
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
        ಅಡ್ಡಸಾಲುಗಳು = get_ಬಿಟ್ಟುಗಳು(gb, 5);
        ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ = get_ಬಿಟ್ಟುಗಳು(gb, 5);
        ಆದರೆ (((ಅಡ್ಡಸಾಲುಗಳು < 2) || (ಅಡ್ಡಸಾಲುಗಳು > 25)) || ((ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ < 2) || (ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ > 25))) {
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
        }
        s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_mastering_display_actual_peak_luminance = ಅಡ್ಡಸಾಲುಗಳು;
        s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_mastering_display_actual_peak_luminance = ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ;

        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < (ಅಡ್ಡಸಾಲುಗಳು * ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ * 4))
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಡ್ಡಸಾಲುಗಳು; i++) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 4), peak_luminance_den};
            }
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 0; w < s->ಅಂಕೆ_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 1)
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        ಆದರೆ (params->tone_mapping_flag) {
            ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 28)
                ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

            params->knee_ಬಿಂದು_x =
                (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 12), knee_ಬಿಂದು_den};
            params->knee_ಬಿಂದು_y =
                (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 12), knee_ಬಿಂದು_den};
            params->ಅಂಕೆ_bezier_ವಕ್ರ_anchors = get_ಬಿಟ್ಟುಗಳು(gb, 4);

            ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < (params->ಅಂಕೆ_bezier_ವಕ್ರ_anchors * 10))
                ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < params->ಅಂಕೆ_bezier_ವಕ್ರ_anchors; i++) {
                params->bezier_ವಕ್ರ_anchors[i] =
                    (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 10), bezier_anchor_den};
            }
        }

        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 1)
            ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        ಆದರೆ (params->color_saturation_mapping_flag) {
            ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < 6)
                ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
            params->color_saturation_ತೂಕ =
                (AVRational){get_ಬಿಟ್ಟುಗಳು(gb, 6), saturation_ತೂಕ_den};
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_dynamic_hdr_plus_ಗಮ್ಯ_t35(ಸ್ಥಿರಾಂಕ AVDynamicHDRPlus *s, uint8_t **ದತ್ತಾಂಶ, size_t *ಗಾತ್ರ_2)
{
    uint8_t *buf;
    size_t ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು, ಗಾತ್ರ_ಬೈಟುಗಳು;
    Put_ಬಿಟ್_Context pbc, *pb = &pbc;

    ಆದರೆ (!s)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಆದರೆ ((!ದತ್ತಾಂಶ || *ದತ್ತಾಂಶ) && !ಗಾತ್ರ_2)
       ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    /**
     * Buffer size per CTA-861-H p.253-254:
     * 48 header bits (excluded from the serialized payload)
     * 8 bits for application_mode
     * 2 bits for num_windows
     * 153 bits for window geometry, for each window above 1
     * 27 bits for targeted_system_display_maximum_luminance
     * 1-2511 bits for targeted system display peak luminance information
     * 82-442 bits per window for pixel distribution information
     * 1-2511 bits for mastering display peak luminance information
     * 1-179 bits per window for tonemapping information
     * 1-7 bits per window for color saturation mapping information
     * Total: 123-7249 bits, excluding trimmed header bits
     */
    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು = 8;

    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 2;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 1; w < s->ಅಂಕೆ_windows; w++)
        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 153;

    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 27;

    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 1;
    ಆದರೆ (s->targeted_system_display_actual_peak_luminance_flag)
        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 10 +
                     s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_targeted_system_display_actual_peak_luminance *
                     s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_targeted_system_display_actual_peak_luminance * 4;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 0; w < s->ಅಂಕೆ_windows; w++)
        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 72 + s->params[w].ಅಂಕೆ_distribution_maxrgb_percentiles * 24 + 10;

    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 1;
    ಆದರೆ (s->mastering_display_actual_peak_luminance_flag)
        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 10 +
                     s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_mastering_display_actual_peak_luminance *
                     s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_mastering_display_actual_peak_luminance * 4;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 0; w < s->ಅಂಕೆ_windows; w++) {
        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 1;
        ಆದರೆ (s->params[w].tone_mapping_flag)
            ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 28 + s->params[w].ಅಂಕೆ_bezier_ವಕ್ರ_anchors * 10;

        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 1;
        ಆದರೆ (s->params[w].color_saturation_mapping_flag)
            ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 6;
    }

    ಗಾತ್ರ_ಬೈಟುಗಳು = (ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು + 7) / 8;

    av_assert0(ಗಾತ್ರ_ಬೈಟುಗಳು <= AV_HDR_PLUS_MAX_PAYLOAD_ಗಾತ್ರ);

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        *ಗಾತ್ರ_2 = ಗಾತ್ರ_ಬೈಟುಗಳು;
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*ದತ್ತಾಂಶ) {
        ಆದರೆ (*ಗಾತ್ರ_2 < ಗಾತ್ರ_ಬೈಟುಗಳು)
            ಹಿಂತಿರುಗಿ AVERROR_ಬಫರ್_TOO_SMALL;
        buf = *ದತ್ತಾಂಶ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        buf = av_malloc(ಗಾತ್ರ_ಬೈಟುಗಳು);
        ಆದರೆ (!buf)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    init_put_ಬಿಟ್ಟುಗಳು(pb, buf, ಗಾತ್ರ_ಬೈಟುಗಳು);

    // application_mode is set to Application Version 1
    put_ಬಿಟ್ಟುಗಳು(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_ಬಿಟ್ಟುಗಳು(pb, 2, s->ಅಂಕೆ_windows);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 1; w < s->ಅಂಕೆ_windows; w++) {
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->params[w].ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_x.ಅಂಕೆ / s->params[w].ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_x.den);
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->params[w].ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_y.ಅಂಕೆ / s->params[w].ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_y.den);
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->params[w].ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_x.ಅಂಕೆ / s->params[w].ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_x.den);
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->params[w].ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_y.ಅಂಕೆ / s->params[w].ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_y.den);
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->params[w].center_ದ_ellipse_x);
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->params[w].center_ದ_ellipse_y);
        put_ಬಿಟ್ಟುಗಳು(pb, 8, s->params[w].rotation_angle);
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->params[w].semimajor_axis_ಆಂತರಿಕ_ellipse);
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_ಬಿಟ್ಟುಗಳು(pb, 1, s->params[w].overlap_process_option);
    }

    put_ಬಿಟ್ಟುಗಳು(pb, 27, s->targeted_system_display_ಗರಿಷ್ಠ_luminance.ಅಂಕೆ * luminance_den /
        s->targeted_system_display_ಗರಿಷ್ಠ_luminance.den);
    put_ಬಿಟ್ಟುಗಳು(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    ಆದರೆ (s->targeted_system_display_actual_peak_luminance_flag) {
        put_ಬಿಟ್ಟುಗಳು(pb, 5, s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_targeted_system_display_actual_peak_luminance);
        put_ಬಿಟ್ಟುಗಳು(pb, 5, s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_targeted_system_display_actual_peak_luminance);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_targeted_system_display_actual_peak_luminance; i++) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_targeted_system_display_actual_peak_luminance; j++)
                put_ಬಿಟ್ಟುಗಳು(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].ಅಂಕೆ * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 0; w < s->ಅಂಕೆ_windows; w++) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++)
            put_ಬಿಟ್ಟುಗಳು(pb, 17, s->params[w].maxscl[i].ಅಂಕೆ * rgb_den / s->params[w].maxscl[i].den);
        put_ಬಿಟ್ಟುಗಳು(pb, 17, s->params[w].ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb.ಅಂಕೆ * rgb_den / s->params[w].ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb.den);
        put_ಬಿಟ್ಟುಗಳು(pb, 4, s->params[w].ಅಂಕೆ_distribution_maxrgb_percentiles);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->params[w].ಅಂಕೆ_distribution_maxrgb_percentiles; i++) {
            put_ಬಿಟ್ಟುಗಳು(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_ಬಿಟ್ಟುಗಳು(pb, 17, s->params[w].distribution_maxrgb[i].percentile.ಅಂಕೆ * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_ಬಿಟ್ಟುಗಳು(pb, 10, s->params[w].fraction_bright_pixels.ಅಂಕೆ * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_ಬಿಟ್ಟುಗಳು(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    ಆದರೆ (s->mastering_display_actual_peak_luminance_flag) {
        put_ಬಿಟ್ಟುಗಳು(pb, 5, s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_mastering_display_actual_peak_luminance);
        put_ಬಿಟ್ಟುಗಳು(pb, 5, s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_mastering_display_actual_peak_luminance);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_mastering_display_actual_peak_luminance; i++) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_mastering_display_actual_peak_luminance; j++)
                put_ಬಿಟ್ಟುಗಳು(pb, 4, s->mastering_display_actual_peak_luminance[i][j].ಅಂಕೆ * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 0; w < s->ಅಂಕೆ_windows; w++) {
        put_ಬಿಟ್ಟುಗಳು(pb, 1, s->params[w].tone_mapping_flag);
        ಆದರೆ (s->params[w].tone_mapping_flag) {
            put_ಬಿಟ್ಟುಗಳು(pb, 12, s->params[w].knee_ಬಿಂದು_x.ಅಂಕೆ * knee_ಬಿಂದು_den / s->params[w].knee_ಬಿಂದು_x.den);
            put_ಬಿಟ್ಟುಗಳು(pb, 12, s->params[w].knee_ಬಿಂದು_y.ಅಂಕೆ * knee_ಬಿಂದು_den / s->params[w].knee_ಬಿಂದು_y.den);
            put_ಬಿಟ್ಟುಗಳು(pb, 4, s->params[w].ಅಂಕೆ_bezier_ವಕ್ರ_anchors);
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < s->params[w].ಅಂಕೆ_bezier_ವಕ್ರ_anchors; i++)
                put_ಬಿಟ್ಟುಗಳು(pb, 10, s->params[w].bezier_ವಕ್ರ_anchors[i].ಅಂಕೆ * bezier_anchor_den /
                    s->params[w].bezier_ವಕ್ರ_anchors[i].den);
        }
        put_ಬಿಟ್ಟುಗಳು(pb, 1, s->params[w].color_saturation_mapping_flag);
        ಆದರೆ (s->params[w].color_saturation_mapping_flag)
            put_ಬಿಟ್ಟುಗಳು(pb, 6, s->params[w].color_saturation_ತೂಕ.ಅಂಕೆ * saturation_ತೂಕ_den /
                s->params[w].color_saturation_ತೂಕ.den);
    }

    flush_put_ಬಿಟ್ಟುಗಳು(pb);

    *ದತ್ತಾಂಶ = buf;
    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = ಗಾತ್ರ_ಬೈಟುಗಳು;
    ಹಿಂತಿರುಗಿ 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *ಗಾತ್ರ_2)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(ಗಾತ್ರ(AVDynamicHDRSmpte2094App5));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = smpte2094_app5 ? ಗಾತ್ರ(*smpte2094_app5) : 0;

    ಹಿಂತಿರುಗಿ smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFrame_Side_ದತ್ತಾಂಶ *side_ದತ್ತಾಂಶ = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು,
                                                        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        ಗಾತ್ರ(AVDynamicHDRSmpte2094App5));
    ಆದರೆ (!side_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    memset(side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(AVDynamicHDRSmpte2094App5));

    ಹಿಂತಿರುಗಿ (AVDynamicHDRSmpte2094App5 *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ;
}

#ವ್ಯಾಖ್ಯಾನಿಸು GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(var, n)        \
    ಮಾಡು {                                \
        ಆದರೆ (get_ಬಿಟ್ಟುಗಳು_ಎಡ(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            ಹೋಗು ಕೊನೆ;                   \
        }                               \
        var = get_ಬಿಟ್ಟುಗಳು(gb, n);          \
    } ಆಗ (0)

ಪೂರ್ಣಾಂಕ av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, ಸ್ಥಿರಾಂಕ uint8_t *ದತ್ತಾಂಶ,
                                           size_t ಗಾತ್ರ_2)
{
    Get_ಬಿಟ್_Context gbc, *gb = &gbc;
    ಪೂರ್ಣಾಂಕ ret, reserved_zero;
    size_t padded_ಗಾತ್ರ = ಗಾತ್ರ_2 + AV_ಒಳಹರಿವು_ಬಫರ್_PADDING_ಗಾತ್ರ;

    ಆದರೆ (!s)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    uint8_t *padded_ದತ್ತಾಂಶ = av_mallocz(padded_ಗಾತ್ರ);
    ಆದರೆ (!padded_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಸ್ಮರಣೆ_ನಕಲು(padded_ದತ್ತಾಂಶ, ದತ್ತಾಂಶ, ಗಾತ್ರ_2);
    ret = init_get_bits8(gb, padded_ದತ್ತಾಂಶ, ಗಾತ್ರ_2);
    ಆದರೆ (ret < 0)
        ಹೋಗು ಕೊನೆ;

    // Table C.1
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->application_ಆವೃತ್ತಿ, 3);
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->minimum_application_ಆವೃತ್ತಿ, 3);
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(reserved_zero, 2);
    ಆದರೆ (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        ಹೋಗು ಕೊನೆ;
    }

    // Table C.2
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(reserved_zero, 6);
    ಆದರೆ (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        ಹೋಗು ಕೊನೆ;
    }
    ಆದರೆ (s->has_custom_hdr_reference_white_flag)
        GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->hdr_reference_white, 16);
    ಆದರೆ (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        ಹೋಗು ಕೊನೆ;
    }

    // Table C.3
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    ಆದರೆ (s->use_reference_white_tone_mapping_flag) {
        GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        ಹೋಗು ಕೊನೆ;
    }
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->ಅಂಕೆ_alternate_images, 3);
    ಆದರೆ (s->ಅಂಕೆ_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        ಹೋಗು ಕೊನೆ;
    }
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->has_common_ವಕ್ರ_params_flag, 1);
    ಆದರೆ (s->gain_application_space_chromaticities_flag == 3)
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ r = 0; r < 8; r++)
            GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ a = 0; a < s->ಅಂಕೆ_alternate_images; a++) {
        GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        ಆದರೆ (!a || !s->has_common_component_mix_params_flag) {
            GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->component_mixing_type[a], 2);
            ಆದರೆ (s->component_mixing_type[a] != 3) {
                GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(reserved_zero, 6);
                ಆದರೆ (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    ಹೋಗು ಕೊನೆ;
                }
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < 6; k++)
                    GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < 6; k++) {
                    ಆದರೆ (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            ಆದರೆ (s->component_mixing_type[a] == 3) {
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        ಆದರೆ (!a || !s->has_common_ವಕ್ರ_params_flag) {
            GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a], 5);
            ಆದರೆ (s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                ಹೋಗು ಕೊನೆ;
            }
            GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a], 1);
            GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(reserved_zero, 2);
            ಆದರೆ (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                ಹೋಗು ಕೊನೆ;
            }
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c <= s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a]; c++) {
                GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->gain_ವಕ್ರ_control_points_x[a][c], 16);
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a] =
                    s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[0];
            s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a] = s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[0];
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c <= s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a]; c++) {
                s->gain_ವಕ್ರ_control_points_x[a][c] = s->gain_ವಕ್ರ_control_points_x[0][c];
            }
        }
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c <= s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a]; c++)
            GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->gain_ವಕ್ರ_control_points_y[a][c], 16);
        ಆದರೆ (!s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a]) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c <= s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a]; c++)
                GET_ಬಿಟ್ಟುಗಳು_OR_FAIL(s->gain_ವಕ್ರ_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
ಕೊನೆ:
    av_free(padded_ದತ್ತಾಂಶ);
    ಹಿಂತಿರುಗಿ ret;
}

ಪೂರ್ಣಾಂಕ av_dynamic_hdr_smpte2094_app5_ಗಮ್ಯ_t35(ಸ್ಥಿರಾಂಕ AVDynamicHDRSmpte2094App5 *s, uint8_t **ದತ್ತಾಂಶ,
                                         size_t *ಗಾತ್ರ_2)
{
    uint8_t *buf;
    size_t ಗಾತ್ರ_ಬೈಟುಗಳು, ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು;
    Put_ಬಿಟ್_Context pbc, *pb = &pbc;

    ಆದರೆ (!s)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    ಆದರೆ ((!ದತ್ತಾಂಶ || *ದತ್ತಾಂಶ) && !ಗಾತ್ರ_2)
       ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (s->application_ಆವೃತ್ತಿ >= 8 || s->minimum_application_ಆವೃತ್ತಿ >= 3)
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು = 0;
    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 3 + 3 + 2;
    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 1 + 1 + 6;
    ಆದರೆ (s->has_custom_hdr_reference_white_flag)
        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 16;
    ಆದರೆ (s->has_adaptive_tone_map_flag) {
        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 16 + 1;
        ಆದರೆ (s->use_reference_white_tone_mapping_flag) {
            ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 7;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 3 + 2 + 1 + 1;
            ಆದರೆ (s->gain_application_space_chromaticities_flag == 3)
                ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 16 * 8;
            ಆದರೆ (s->ಅಂಕೆ_alternate_images > 4)
                ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ a = 0; a < s->ಅಂಕೆ_alternate_images; a++) {
                ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 16;
                ಆದರೆ (!a || !s->has_common_component_mix_params_flag) {
                    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 2;
                    ಆದರೆ (s->component_mixing_type[a] != 3) {
                        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 6;
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 6;
                        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < 6; k++)
                          ಆದರೆ (s->has_component_mixing_coefficient_flag[a][k])
                            ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 16;
                    }
                }
                ಆದರೆ (!a || !s->has_common_ವಕ್ರ_params_flag) {
                    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 5 + 1 + 2;
                    ಆದರೆ (s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a] > 31)
                        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
                    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 16 * (s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a] + 1);
                }
                ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 16 * (s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a] + 1);
                ಆದರೆ (!s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a])
                    ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು += 16 * (s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a] + 1);
            }
        }
    }
    ಆದರೆ (ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು % 8)
      ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
    ಗಾತ್ರ_ಬೈಟುಗಳು = ಗಾತ್ರ_ಬಿಟ್ಟುಗಳು >> 3;

    ಆದರೆ (!ದತ್ತಾಂಶ) {
        *ಗಾತ್ರ_2 = ಗಾತ್ರ_ಬೈಟುಗಳು;
        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*ದತ್ತಾಂಶ) {
        ಆದರೆ (*ಗಾತ್ರ_2 < ಗಾತ್ರ_ಬೈಟುಗಳು)
            ಹಿಂತಿರುಗಿ AVERROR_ಬಫರ್_TOO_SMALL;
        buf = *ದತ್ತಾಂಶ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        buf = av_malloc(ಗಾತ್ರ_ಬೈಟುಗಳು);
        ಆದರೆ (!buf)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    init_put_ಬಿಟ್ಟುಗಳು(pb, buf, ಗಾತ್ರ_ಬೈಟುಗಳು);

    // Table C.1
    put_ಬಿಟ್ಟುಗಳು(pb, 3, s->application_ಆವೃತ್ತಿ);
    put_ಬಿಟ್ಟುಗಳು(pb, 3, s->minimum_application_ಆವೃತ್ತಿ);
    put_ಬಿಟ್ಟುಗಳು(pb, 2, 0); // reserved_zero

    // Table C.2
    put_ಬಿಟ್ಟುಗಳು(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_ಬಿಟ್ಟುಗಳು(pb, 1, s->has_adaptive_tone_map_flag);
    put_ಬಿಟ್ಟುಗಳು(pb, 6, 0); // reserved_zero

    ಆದರೆ (s->has_custom_hdr_reference_white_flag)
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->hdr_reference_white);

    ಆದರೆ (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->baseline_hdr_headroom);
        put_ಬಿಟ್ಟುಗಳು(pb, 1, s->use_reference_white_tone_mapping_flag);
        ಆದರೆ (s->use_reference_white_tone_mapping_flag) {
            put_ಬಿಟ್ಟುಗಳು(pb, 7, 0); // reserved_zero
        } ಇಲ್ಲದಿದ್ದರೆ {
            put_ಬಿಟ್ಟುಗಳು(pb, 3, s->ಅಂಕೆ_alternate_images);
            put_ಬಿಟ್ಟುಗಳು(pb, 2, s->gain_application_space_chromaticities_flag);
            put_ಬಿಟ್ಟುಗಳು(pb, 1, s->has_common_component_mix_params_flag);
            put_ಬಿಟ್ಟುಗಳು(pb, 1, s->has_common_ವಕ್ರ_params_flag);

            ಆದರೆ (s->gain_application_space_chromaticities_flag == 3)
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ r = 0; r < 8; r++)
                    put_ಬಿಟ್ಟುಗಳು(pb, 16, s->gain_application_space_chromaticities[r]);

            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ a = 0; a < s->ಅಂಕೆ_alternate_images; a++) {
                put_ಬಿಟ್ಟುಗಳು(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                ಆದರೆ (!a || !s->has_common_component_mix_params_flag) {
                    put_ಬಿಟ್ಟುಗಳು(pb, 2, s->component_mixing_type[a]);
                    ಆದರೆ (s->component_mixing_type[a] != 3) {
                        put_ಬಿಟ್ಟುಗಳು(pb, 6, 0); // reserved_zero
                    } ಇಲ್ಲದಿದ್ದರೆ {
                        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < 6; k++)
                            put_ಬಿಟ್ಟುಗಳು(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < 6; k++)
                            ಆದರೆ (s->has_component_mixing_coefficient_flag[a][k])
                                put_ಬಿಟ್ಟುಗಳು(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                ಆದರೆ (!a || !s->has_common_ವಕ್ರ_params_flag) {
                    put_ಬಿಟ್ಟುಗಳು(pb, 5, s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a]);
                    put_ಬಿಟ್ಟುಗಳು(pb, 1, s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a]);
                    put_ಬಿಟ್ಟುಗಳು(pb, 2, 0); // reserved_zero
                    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c <= s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a]; c++)
                        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->gain_ವಕ್ರ_control_points_x[a][c]);
                }
                ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c <= s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a]; c++)
                    put_ಬಿಟ್ಟುಗಳು(pb, 16, s->gain_ವಕ್ರ_control_points_y[a][c]);
                ಆದರೆ (!s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a]) {
                    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c <= s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a]; c++)
                        put_ಬಿಟ್ಟುಗಳು(pb, 16, s->gain_ವಕ್ರ_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_ಬಿಟ್ಟುಗಳು(pb);

    *ದತ್ತಾಂಶ = buf;
    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = ಗಾತ್ರ_ಬೈಟುಗಳು;
    ಹಿಂತಿರುಗಿ 0;
}

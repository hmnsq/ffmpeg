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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/error.h"
#ಅನ್ತರ್ಭಾವ "libavutil/frame.h"
#ಅನ್ತರ್ಭಾವ "libavutil/hdr_dynamic_metadata.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/rational.h"

/* Denominators av_dynamic_hdr_plus_to_t35() quantises to. The fixtures below
 * express every rational in these terms, so a correct round trip reproduces
 * the input exactly and the decoded values printed here can be compared
 * against the fixture directly. */
#ವ್ಯಾಖ್ಯಾನಿಸು LUMINANCE_DEN          1
#ವ್ಯಾಖ್ಯಾನಿಸು PEAK_LUMINANCE_DEN    15
#ವ್ಯಾಖ್ಯಾನಿಸು RGB_DEN           100000
#ವ್ಯಾಖ್ಯಾನಿಸು FRACTION_PIXEL_DEN  1000
#ವ್ಯಾಖ್ಯಾನಿಸು KNEE_ಬಿಂದು_DEN      4095
#ವ್ಯಾಖ್ಯಾನಿಸು BEZIER_ANCHOR_DEN   1023
#ವ್ಯಾಖ್ಯಾನಿಸು SATURATION_DEN         8

/*
 * Printers. Every field a fixture populates is printed, so that a serializer
 * or parser which drops or corrupts a value changes the FATE reference
 * instead of silently passing a flag-only check.
 */

ಸ್ಥಿರ ಶೂನ್ಯ print_peak_ಮಾತೃಕೆ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label, ಪೂರ್ಣಾಂಕ ಅಡ್ಡಸಾಲುಗಳು, ಪೂರ್ಣಾಂಕ ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ,
                              ಸ್ಥಿರಾಂಕ AVRational m[25][25])
{
    ಬರೆ("    %s %dx%d:", label, ಅಡ್ಡಸಾಲುಗಳು, ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಅಡ್ಡಸಾಲುಗಳು; i++)
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ; j++)
            ಬರೆ(" %d/%d", m[i][j].ಅಂಕೆ, m[i][j].den);
    ಬರೆ("\n");
}

ಸ್ಥಿರ ಶೂನ್ಯ print_ಕಿಟಕಿ(ಪೂರ್ಣಾಂಕ w, ಸ್ಥಿರಾಂಕ AVHDRPlusColorTransformParams *p,
                         ಪೂರ್ಣಾಂಕ geometry)
{
    ಬರೆ("  window %d:\n", w);
    /* Window 0 covers the whole frame; its geometry is not serialized. */
    ಆದರೆ (geometry) {
        ಬರೆ("    corners: ul=%d/%d,%d/%d lr=%d/%d,%d/%d\n",
               p->ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_x.ಅಂಕೆ,
               p->ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_x.den,
               p->ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_y.ಅಂಕೆ,
               p->ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_y.den,
               p->ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_x.ಅಂಕೆ,
               p->ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_x.den,
               p->ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_y.ಅಂಕೆ,
               p->ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_y.den);
        ಬರೆ("    ellipse: center=%u,%u rotation=%u semimajor_int=%u"
               " semimajor_ext=%u semiminor_ext=%u overlap=%u\n",
               p->center_ದ_ellipse_x, p->center_ದ_ellipse_y,
               p->rotation_angle, p->semimajor_axis_ಆಂತರಿಕ_ellipse,
               p->semimajor_axis_external_ellipse,
               p->semiminor_axis_external_ellipse,
               p->overlap_process_option);
    }
    ಬರೆ("    maxscl: %d/%d %d/%d %d/%d average_maxrgb=%d/%d\n",
           p->maxscl[0].ಅಂಕೆ, p->maxscl[0].den,
           p->maxscl[1].ಅಂಕೆ, p->maxscl[1].den,
           p->maxscl[2].ಅಂಕೆ, p->maxscl[2].den,
           p->ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb.ಅಂಕೆ, p->ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb.den);
    ಬರೆ("    distribution_maxrgb: n=%u",
           p->ಅಂಕೆ_distribution_maxrgb_percentiles);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < p->ಅಂಕೆ_distribution_maxrgb_percentiles; i++)
        ಬರೆ(" %u%%=%d/%d", p->distribution_maxrgb[i].percentage,
               p->distribution_maxrgb[i].percentile.ಅಂಕೆ,
               p->distribution_maxrgb[i].percentile.den);
    ಬರೆ("\n    fraction_bright_pixels=%d/%d\n",
           p->fraction_bright_pixels.ಅಂಕೆ, p->fraction_bright_pixels.den);
    ಬರೆ("    tone_mapping_flag=%u", p->tone_mapping_flag);
    ಆದರೆ (p->tone_mapping_flag) {
        ಬರೆ(" knee=%d/%d,%d/%d anchors=%u:",
               p->knee_ಬಿಂದು_x.ಅಂಕೆ, p->knee_ಬಿಂದು_x.den,
               p->knee_ಬಿಂದು_y.ಅಂಕೆ, p->knee_ಬಿಂದು_y.den,
               p->ಅಂಕೆ_bezier_ವಕ್ರ_anchors);
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < p->ಅಂಕೆ_bezier_ವಕ್ರ_anchors; i++)
            ಬರೆ(" %d/%d", p->bezier_ವಕ್ರ_anchors[i].ಅಂಕೆ,
                   p->bezier_ವಕ್ರ_anchors[i].den);
    }
    ಬರೆ("\n    color_saturation_mapping_flag=%u",
           p->color_saturation_mapping_flag);
    ಆದರೆ (p->color_saturation_mapping_flag)
        ಬರೆ(" weight=%d/%d", p->color_saturation_ತೂಕ.ಅಂಕೆ,
               p->color_saturation_ತೂಕ.den);
    ಬರೆ("\n");
}

ಸ್ಥಿರ ಶೂನ್ಯ print_hdr_plus(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label, ಸ್ಥಿರಾಂಕ AVDynamicHDRPlus *s)
{
    ಬರೆ("%s:\n", label);
    ಬರೆ("  application_version=%u num_windows=%u"
           " targeted_system_display_maximum_luminance=%d/%d\n",
           s->application_ಆವೃತ್ತಿ, s->ಅಂಕೆ_windows,
           s->targeted_system_display_ಗರಿಷ್ಠ_luminance.ಅಂಕೆ,
           s->targeted_system_display_ಗರಿಷ್ಠ_luminance.den);
    ಬರೆ("  targeted_system_display_actual_peak_luminance_flag=%u\n",
           s->targeted_system_display_actual_peak_luminance_flag);
    ಆದರೆ (s->targeted_system_display_actual_peak_luminance_flag)
        print_peak_ಮಾತೃಕೆ("targeted_peak",
                          s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_targeted_system_display_actual_peak_luminance,
                          s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_targeted_system_display_actual_peak_luminance,
                          s->targeted_system_display_actual_peak_luminance);
    ಬರೆ("  mastering_display_actual_peak_luminance_flag=%u\n",
           s->mastering_display_actual_peak_luminance_flag);
    ಆದರೆ (s->mastering_display_actual_peak_luminance_flag)
        print_peak_ಮಾತೃಕೆ("mastering_peak",
                          s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_mastering_display_actual_peak_luminance,
                          s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_mastering_display_actual_peak_luminance,
                          s->mastering_display_actual_peak_luminance);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 0; w < s->ಅಂಕೆ_windows; w++)
        print_ಕಿಟಕಿ(w, &s->params[w], w > 0);
}

ಸ್ಥಿರ ಶೂನ್ಯ print_app5(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *label, ಸ್ಥಿರಾಂಕ AVDynamicHDRSmpte2094App5 *s)
{
    ಬರೆ("%s:\n", label);
    ಬರೆ("  application_version=%u minimum_application_version=%u\n",
           s->application_ಆವೃತ್ತಿ, s->minimum_application_ಆವೃತ್ತಿ);
    ಬರೆ("  has_custom_hdr_reference_white_flag=%u",
           s->has_custom_hdr_reference_white_flag);
    ಆದರೆ (s->has_custom_hdr_reference_white_flag)
        ಬರೆ(" hdr_reference_white=0x%04x", s->hdr_reference_white);
    ಬರೆ("\n  has_adaptive_tone_map_flag=%u\n",
           s->has_adaptive_tone_map_flag);
    ಆದರೆ (!s->has_adaptive_tone_map_flag)
        ಹಿಂತಿರುಗಿ;

    ಬರೆ("  baseline_hdr_headroom=0x%04x"
           " use_reference_white_tone_mapping_flag=%u\n",
           s->baseline_hdr_headroom, s->use_reference_white_tone_mapping_flag);
    ಆದರೆ (s->use_reference_white_tone_mapping_flag)
        ಹಿಂತಿರುಗಿ;

    ಬರೆ("  num_alternate_images=%u chromaticities_flag=%u"
           " has_common_component_mix_params_flag=%u"
           " has_common_curve_params_flag=%u\n",
           s->ಅಂಕೆ_alternate_images,
           s->gain_application_space_chromaticities_flag,
           s->has_common_component_mix_params_flag,
           s->has_common_ವಕ್ರ_params_flag);
    ಆದರೆ (s->gain_application_space_chromaticities_flag == 3) {
        ಬರೆ("  chromaticities:");
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ r = 0; r < 8; r++)
            ಬರೆ(" 0x%04x", s->gain_application_space_chromaticities[r]);
        ಬರೆ("\n");
    }

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ a = 0; a < s->ಅಂಕೆ_alternate_images; a++) {
        ಪೂರ್ಣಾಂಕ n = s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a] + 1;
        ಬರೆ("  alternate %d: hdr_headroom=0x%04x component_mixing_type=%u\n",
               a, s->alternate_hdr_headrooms[a], s->component_mixing_type[a]);
        ಆದರೆ (s->component_mixing_type[a] == 3) {
            ಬರೆ("    mixing flag:coefficient:");
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < 6; k++)
                ಬರೆ(" %u:0x%04x",
                       s->has_component_mixing_coefficient_flag[a][k],
                       s->component_mixing_coefficient[a][k]);
            ಬರೆ("\n");
        }
        ಬರೆ("    curve: num_control_points=%d use_pchip_slope=%u\n", n,
               s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a]);
        ಬರೆ("    x:");
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < n; c++)
            ಬರೆ(" 0x%04x", s->gain_ವಕ್ರ_control_points_x[a][c]);
        ಬರೆ("\n    y:");
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < n; c++)
            ಬರೆ(" 0x%04x", s->gain_ವಕ್ರ_control_points_y[a][c]);
        ಬರೆ("\n");
        /* theta is only serialized when the pchip slope is not used. */
        ಆದರೆ (!s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a]) {
            ಬರೆ("    theta:");
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < n; c++)
                ಬರೆ(" 0x%04x", s->gain_ವಕ್ರ_control_points_theta[a][c]);
            ಬರೆ("\n");
        }
    }
}

/*
 * Round-trip helpers: serialize, then parse back into a zeroed struct.
 */

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ hdr_plus_ಸುತ್ತು_trip(ಸ್ಥಿರಾಂಕ AVDynamicHDRPlus *ಒಳ, AVDynamicHDRPlus *ಹೊರಹೋಗು)
{
    uint8_t *buf = ಖಾಲಿ;
    size_t ಗಾತ್ರ_2 = 0;
    ಪೂರ್ಣಾಂಕ ret;

    ret = av_dynamic_hdr_plus_ಗಮ್ಯ_t35(ಒಳ, &buf, &ಗಾತ್ರ_2);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    memset(ಹೊರಹೋಗು, 0, ಗಾತ್ರ(*ಹೊರಹೋಗು));
    ret = av_dynamic_hdr_plus_from_t35(ಹೊರಹೋಗು, buf, ಗಾತ್ರ_2);
    av_free(buf);
    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ app5_ಸುತ್ತು_trip(ಸ್ಥಿರಾಂಕ AVDynamicHDRSmpte2094App5 *ಒಳ,
                           AVDynamicHDRSmpte2094App5 *ಹೊರಹೋಗು)
{
    uint8_t *buf = ಖಾಲಿ;
    size_t ಗಾತ್ರ_2 = 0;
    ಪೂರ್ಣಾಂಕ ret;

    ret = av_dynamic_hdr_smpte2094_app5_ಗಮ್ಯ_t35(ಒಳ, &buf, &ಗಾತ್ರ_2);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    memset(ಹೊರಹೋಗು, 0, ಗಾತ್ರ(*ಹೊರಹೋಗು));
    ret = av_dynamic_hdr_smpte2094_app5_from_t35(ಹೊರಹೋಗು, buf, ಗಾತ್ರ_2);
    av_free(buf);
    ಹಿಂತಿರುಗಿ ret;
}

/*
 * Fixtures.
 */

/* A conforming ST 2094-40:2020 ApplicationVersion 1 payload: exactly one
 * processing window, neither actual-peak-luminance item and no
 * ColorSaturationWeight (§9.4 excludes all three for Version 1), and the nine
 * distribution maxrgb percentiles §8.5.4 requires for that version.
 * CTA-861-H fixes application_version at 1 for HDR10+ carried over T.35.
 *
 * The entries for 5% and 10% are not CFD percentile samples: §8.5.4 reserves
 * every value other than 0.00000 and 0.00255 for that pair. No other entry may
 * exceed the largest MaxSCL component either, since §8.3 takes MaxSCL over each
 * RGB component separately while §8.5.2 draws the distribution from the
 * per-pixel maximum component. */
ಸ್ಥಿರ ಶೂನ್ಯ fill_hdr_plus_conforming(AVDynamicHDRPlus *s)
{
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t percentages[9] = { 1, 5, 10, 25, 50, 75, 90, 95, 99 };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ percentiles[9] = {
        1000, 0, 255, 25000, 50000, 75000, 90000, 95000, 99000,
    };

    memset(s, 0, ಗಾತ್ರ(*s));

    s->application_ಆವೃತ್ತಿ = 1;
    s->ಅಂಕೆ_windows         = 1;
    s->targeted_system_display_ಗರಿಷ್ಠ_luminance =
        (AVRational){ 400, LUMINANCE_DEN };
    s->targeted_system_display_actual_peak_luminance_flag = 0;
    s->mastering_display_actual_peak_luminance_flag       = 0;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 99000, RGB_DEN };
    s->params[0].ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb = (AVRational){ 40000, RGB_DEN };

    s->params[0].ಅಂಕೆ_distribution_maxrgb_percentiles = 9;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 9; i++) {
        s->params[0].distribution_maxrgb[i].percentage = percentages[i];
        s->params[0].distribution_maxrgb[i].percentile =
            (AVRational){ percentiles[i], RGB_DEN };
    }
    s->params[0].fraction_bright_pixels =
        (AVRational){ 250, FRACTION_PIXEL_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_ಬಿಂದು_x = (AVRational){  512, KNEE_ಬಿಂದು_DEN };
    s->params[0].knee_ಬಿಂದು_y = (AVRational){ 1024, KNEE_ಬಿಂದು_DEN };
    s->params[0].ಅಂಕೆ_bezier_ವಕ್ರ_anchors = 9;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 9; i++)
        s->params[0].bezier_ವಕ್ರ_anchors[i] =
            (AVRational){ 100 * (i + 1), BEZIER_ANCHOR_DEN };

    s->params[0].color_saturation_mapping_flag = 0;
}

/* Deliberately NOT a conforming Version 1 payload: it combines a second
 * processing window, both actual-peak-luminance matrices and
 * ColorSaturationWeight, all of which §9.4 excludes for Version 1. It exists
 * only to drive the optional serializer/parser branches those fields guard. */
ಸ್ಥಿರ ಶೂನ್ಯ fill_hdr_plus_synthetic(AVDynamicHDRPlus *s)
{
    memset(s, 0, ಗಾತ್ರ(*s));

    s->application_ಆವೃತ್ತಿ = 1;
    s->ಅಂಕೆ_windows         = 2;
    s->targeted_system_display_ಗರಿಷ್ಠ_luminance =
        (AVRational){ 10000, LUMINANCE_DEN };

    s->params[1].ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_x  = (AVRational){ 100, 1 };
    s->params[1].ಕಿಟಕಿ_ಊರ್ಧ್ವ_ಎಡ_ಮೂಲೆ_y  = (AVRational){ 120, 1 };
    s->params[1].ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_x = (AVRational){ 500, 1 };
    s->params[1].ಕಿಟಕಿ_ಅಧೋ_ಬಲ_ಮೂಲೆ_y = (AVRational){ 520, 1 };
    s->params[1].center_ದ_ellipse_x             = 300;
    s->params[1].center_ದ_ellipse_y             = 320;
    s->params[1].rotation_angle                  = 45;
    s->params[1].semimajor_axis_ಆಂತರಿಕ_ellipse = 50;
    s->params[1].semimajor_axis_external_ellipse = 100;
    s->params[1].semiminor_axis_external_ellipse = 80;
    s->params[1].overlap_process_option          = 1;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 70000, RGB_DEN };
    s->params[0].ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb = (AVRational){ 40000, RGB_DEN };
    s->params[0].ಅಂಕೆ_distribution_maxrgb_percentiles = 2;
    s->params[0].distribution_maxrgb[0].percentage = 50;
    s->params[0].distribution_maxrgb[0].percentile =
        (AVRational){ 30000, RGB_DEN };
    s->params[0].distribution_maxrgb[1].percentage = 99;
    s->params[0].distribution_maxrgb[1].percentile =
        (AVRational){ 90000, RGB_DEN };
    s->params[0].fraction_bright_pixels =
        (AVRational){ 250, FRACTION_PIXEL_DEN };

    s->params[1].maxscl[0]      = (AVRational){ 20000, RGB_DEN };
    s->params[1].maxscl[1]      = (AVRational){ 30000, RGB_DEN };
    s->params[1].maxscl[2]      = (AVRational){ 40000, RGB_DEN };
    s->params[1].ಸರಾಸರಿ_ಮೌಲ್ಯ_maxrgb = (AVRational){ 25000, RGB_DEN };
    s->params[1].ಅಂಕೆ_distribution_maxrgb_percentiles = 1;
    s->params[1].distribution_maxrgb[0].percentage = 25;
    s->params[1].distribution_maxrgb[0].percentile =
        (AVRational){ 12500, RGB_DEN };
    s->params[1].fraction_bright_pixels =
        (AVRational){ 100, FRACTION_PIXEL_DEN };

    s->targeted_system_display_actual_peak_luminance_flag = 1;
    s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_targeted_system_display_actual_peak_luminance = 2;
    s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_targeted_system_display_actual_peak_luminance = 3;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 2; i++)
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < 3; j++)
            s->targeted_system_display_actual_peak_luminance[i][j] =
                (AVRational){ i * 3 + j, PEAK_LUMINANCE_DEN };

    s->mastering_display_actual_peak_luminance_flag = 1;
    s->ಅಂಕೆ_ಅಡ್ಡಸಾಲುಗಳು_mastering_display_actual_peak_luminance = 3;
    s->ಅಂಕೆ_ಲಂಬಸಾಲು_ಸಂಖ್ಯೆ_mastering_display_actual_peak_luminance = 2;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < 3; i++)
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ j = 0; j < 2; j++)
            s->mastering_display_actual_peak_luminance[i][j] =
                (AVRational){ 15 - (i * 2 + j), PEAK_LUMINANCE_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_ಬಿಂದು_x = (AVRational){ 500, KNEE_ಬಿಂದು_DEN };
    s->params[0].knee_ಬಿಂದು_y = (AVRational){ 800, KNEE_ಬಿಂದು_DEN };
    s->params[0].ಅಂಕೆ_bezier_ವಕ್ರ_anchors = 3;
    s->params[0].bezier_ವಕ್ರ_anchors[0] = (AVRational){ 100, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_ವಕ್ರ_anchors[1] = (AVRational){ 500, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_ವಕ್ರ_anchors[2] = (AVRational){ 900, BEZIER_ANCHOR_DEN };
    s->params[1].tone_mapping_flag = 0;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ w = 0; w < 2; w++) {
        s->params[w].color_saturation_mapping_flag = 1;
        s->params[w].color_saturation_ತೂಕ =
            (AVRational){ 8 + w, SATURATION_DEN };
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ test_hdr_plus(ಶೂನ್ಯ)
{
    AVDynamicHDRPlus *hdr, *hdr_rt;
    AVFrame *ಚೌಕಟ್ಟು;
    size_t ಗಾತ್ರ_2 = 0, required = 0;
    uint8_t *buf = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret;

    ಬರೆ("=== AVDynamicHDRPlus ===\n");

    ಬರೆ("Testing av_dynamic_hdr_plus_alloc()\n");
    hdr = av_dynamic_hdr_plus_alloc(&ಗಾತ್ರ_2);
    ಬರೆ("alloc: %s size>0=%s\n", hdr ? "OK" : "FAIL",
           ಗಾತ್ರ_2 > 0 ? "yes" : "no");
    av_freep(&hdr);

    hdr = av_dynamic_hdr_plus_alloc(ಖಾಲಿ);
    ಬರೆ("alloc (no size): %s\n", hdr ? "OK" : "FAIL");
    av_freep(&hdr);

    ಬರೆ("\nTesting av_dynamic_hdr_plus_create_side_data()\n");
    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        hdr = av_dynamic_hdr_plus_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಬರೆ("create_side_data: %s\n", hdr ? "OK" : "FAIL");
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    hdr    = av_dynamic_hdr_plus_alloc(ಖಾಲಿ);
    hdr_rt = av_dynamic_hdr_plus_alloc(ಖಾಲಿ);
    ಆದರೆ (!hdr || !hdr_rt) {
        av_freep(&hdr);
        av_freep(&hdr_rt);
        ಹಿಂತಿರುಗಿ;
    }
    fill_hdr_plus_conforming(hdr);

    /* Size-query mode: data=NULL, size receives the required byte count. */
    ಬರೆ("\nTesting av_dynamic_hdr_plus_to_t35() size query\n");
    required = 0;
    ret = av_dynamic_hdr_plus_ಗಮ್ಯ_t35(hdr, ಖಾಲಿ, &required);
    ಬರೆ("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    /* Allocation mode: *data=NULL, the function allocates the buffer. */
    ಬರೆ("\nTesting av_dynamic_hdr_plus_to_t35() allocation\n");
    buf  = ಖಾಲಿ;
    ಗಾತ್ರ_2 = 0;
    ret = av_dynamic_hdr_plus_ಗಮ್ಯ_t35(hdr, &buf, &ಗಾತ್ರ_2);
    ಬರೆ("alloc mode: ret=%d size_match=%s\n", ret,
           ಗಾತ್ರ_2 == required ? "yes" : "no");
    av_freep(&buf);

    /* Existing-buffer mode: a caller-owned buffer is filled in place. */
    ಬರೆ("\nTesting av_dynamic_hdr_plus_to_t35() existing buffer\n");
    buf = av_malloc(required);
    ಆದರೆ (buf) {
        uint8_t *orig = buf;
        ಗಾತ್ರ_2 = required;
        ret = av_dynamic_hdr_plus_ಗಮ್ಯ_t35(hdr, &buf, &ಗಾತ್ರ_2);
        ಬರೆ("existing buf: ret=%d same_pointer=%s size_match=%s\n", ret,
               buf == orig ? "yes" : "no",
               ಗಾತ್ರ_2 == required ? "yes" : "no");
        av_freep(&buf);
    }

    /* Buffer-too-small: caller-owned buffer shorter than required. */
    ಬರೆ("\nTesting av_dynamic_hdr_plus_to_t35() buffer too small\n");
    ಆದರೆ (required > 1) {
        buf = av_malloc(required - 1);
        ಆದರೆ (buf) {
            ಗಾತ್ರ_2 = required - 1;
            ret = av_dynamic_hdr_plus_ಗಮ್ಯ_t35(hdr, &buf, &ಗಾತ್ರ_2);
            ಬರೆ("too small: ret==AVERROR_BUFFER_TOO_SMALL=%s\n",
                   ret == AVERROR_ಬಫರ್_TOO_SMALL ? "yes" : "no");
            av_freep(&buf);
        }
    }

    ಬರೆ("\nTesting round trip, conforming ST 2094-40 Version 1 payload\n");
    ret = hdr_plus_ಸುತ್ತು_trip(hdr, hdr_rt);
    ಬರೆ("round trip: ret=%d\n", ret);
    ಆದರೆ (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    /* to_t35() ignores application_version and always writes the CTA-861-H
     * value, so the parsed field does not echo an out-of-range input. */
    ಬರೆ("\nTesting that to_t35() overrides application_version\n");
    hdr->application_ಆವೃತ್ತಿ = 7;
    ret = hdr_plus_ಸುತ್ತು_trip(hdr, hdr_rt);
    ಬರೆ("input=7 ret=%d decoded application_version=%u\n", ret,
           hdr_rt->application_ಆವೃತ್ತಿ);
    hdr->application_ಆವೃತ್ತಿ = 1;

    ಬರೆ("\nTesting round trip, synthetic payload (branch coverage only)\n");
    fill_hdr_plus_synthetic(hdr);
    ret = hdr_plus_ಸುತ್ತು_trip(hdr, hdr_rt);
    ಬರೆ("round trip: ret=%d\n", ret);
    ಆದರೆ (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    ಬರೆ("\nTesting error paths\n");
    buf  = ಖಾಲಿ;
    ಗಾತ್ರ_2 = 0;
    ret = av_dynamic_hdr_plus_ಗಮ್ಯ_t35(ಖಾಲಿ, &buf, &ಗಾತ್ರ_2);
    ಬರೆ("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_ಗಮ್ಯ_t35(hdr, ಖಾಲಿ, ಖಾಲಿ);
    ಬರೆ("to_t35 no data no size: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_from_t35(ಖಾಲಿ, (ಸ್ಥಿರಾಂಕ uint8_t *)"", 0);
    ಬರೆ("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    {
        /* Oversized input is rejected before parsing. */
        size_t big = AV_HDR_PLUS_MAX_PAYLOAD_ಗಾತ್ರ + 1;
        uint8_t *oversized = av_mallocz(big);
        ಆದರೆ (oversized) {
            ret = av_dynamic_hdr_plus_from_t35(hdr_rt, oversized, big);
            ಬರೆ("from_t35 oversized: ret==AVERROR(EINVAL)=%s\n",
                   ret == AVERROR(EINVAL) ? "yes" : "no");
            av_free(oversized);
        }
    }

    av_freep(&hdr);
    av_freep(&hdr_rt);

    ಬರೆ("\nTesting OOM path\n");
    av_max_alloc(1);
    hdr = av_dynamic_hdr_plus_alloc(&ಗಾತ್ರ_2);
    ಬರೆ("alloc OOM: %s\n", hdr ? "FAIL" : "OK");
    av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
    av_freep(&hdr);
}

/* Table C.2 early-out: no adaptive tone map, custom reference white only. */
ಸ್ಥಿರ ಶೂನ್ಯ fill_app5_ಕನಿಷ್ಠತಮ(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, ಗಾತ್ರ(*s));
    s->application_ಆವೃತ್ತಿ         = 1;
    s->minimum_application_ಆವೃತ್ತಿ = 0;
    s->has_custom_hdr_reference_white_flag = 1;
    s->hdr_reference_white         = 0x0203;
    s->has_adaptive_tone_map_flag  = 0;
}

/* Table C.3 early-out: reference-white tone mapping, no alternate images. */
ಸ್ಥಿರ ಶೂನ್ಯ fill_app5_reference_white(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, ಗಾತ್ರ(*s));
    s->application_ಆವೃತ್ತಿ        = 2;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->use_reference_white_tone_mapping_flag = 1;
}

/* Per-image parameters: explicit gain application space chromaticities,
 * component mixing type 3 with a mix of present and absent coefficients, and
 * explicit control point slopes (theta). */
ಸ್ಥಿರ ಶೂನ್ಯ fill_app5_ಪ್ರತಿ_image(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, ಗಾತ್ರ(*s));
    s->application_ಆವೃತ್ತಿ        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->ಅಂಕೆ_alternate_images       = 2;
    s->gain_application_space_chromaticities_flag = 3;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ r = 0; r < 8; r++)
        s->gain_application_space_chromaticities[r] = 100 * (r + 1);
    s->has_common_component_mix_params_flag = 0;
    s->has_common_ವಕ್ರ_params_flag         = 0;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ a = 0; a < 2; a++) {
        s->alternate_hdr_headrooms[a] = 0x0100 + a;
        s->component_mixing_type[a]   = 3;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ k = 0; k < 6; k++) {
            s->has_component_mixing_coefficient_flag[a][k] = k & 1;
            s->component_mixing_coefficient[a][k] = 0x1000 + 0x10 * a + k;
        }
        s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a] = 1;
        s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a]       = 0;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < 2; c++) {
            s->gain_ವಕ್ರ_control_points_x[a][c]     = 0x2000 + 0x10 * a + c;
            s->gain_ವಕ್ರ_control_points_y[a][c]     = 0x3000 + 0x10 * a + c;
            s->gain_ವಕ್ರ_control_points_theta[a][c] = 0x4000 + 0x10 * a + c;
        }
    }
}

/* The complementary selectors: no explicit chromaticities, a component mixing
 * type other than 3, mixing and curve parameters shared from alternate 0, and
 * the pchip slope, which omits theta from the payload.
 *
 * The common_* flags make the parser copy alternate 0's parameters to the
 * other alternates, so the fixture sets them identically everywhere; only
 * alternate_hdr_headrooms and the y control points stay per-image. */
ಸ್ಥಿರ ಶೂನ್ಯ fill_app5_common(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, ಗಾತ್ರ(*s));
    s->application_ಆವೃತ್ತಿ        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0def;
    s->ಅಂಕೆ_alternate_images       = 3;
    s->gain_application_space_chromaticities_flag = 0;
    s->has_common_component_mix_params_flag = 1;
    s->has_common_ವಕ್ರ_params_flag         = 1;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ a = 0; a < 3; a++) {
        s->alternate_hdr_headrooms[a] = 0x0200 + a;
        s->component_mixing_type[a]   = 1;
        s->gain_ವಕ್ರ_ಅಂಕೆ_control_points_minus_1[a] = 2;
        s->gain_ವಕ್ರ_use_pchip_ಇಳಿಜಾರು_flag[a]       = 1;
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < 3; c++) {
            s->gain_ವಕ್ರ_control_points_x[a][c] = 0x5000 + c;
            s->gain_ವಕ್ರ_control_points_y[a][c] = 0x6000 + 0x10 * a + c;
        }
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ test_app5(ಶೂನ್ಯ)
{
    AVDynamicHDRSmpte2094App5 *app5, *app5_rt;
    AVFrame *ಚೌಕಟ್ಟು;
    size_t ಗಾತ್ರ_2 = 0, required = 0;
    uint8_t *buf = ಖಾಲಿ;
    ಪೂರ್ಣಾಂಕ ret;

    ಬರೆ("\n=== AVDynamicHDRSmpte2094App5 ===\n");
    ಬರೆ("Testing av_dynamic_hdr_smpte2094_app5_alloc()\n");
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&ಗಾತ್ರ_2);
    ಬರೆ("alloc: %s size>0=%s\n", app5 ? "OK" : "FAIL",
           ಗಾತ್ರ_2 > 0 ? "yes" : "no");
    av_freep(&app5);

    ಬರೆ("\nTesting av_dynamic_hdr_smpte2094_app5_create_side_data()\n");
    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        app5 = av_dynamic_hdr_smpte2094_app5_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಬರೆ("create_side_data: %s\n", app5 ? "OK" : "FAIL");
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    app5    = av_dynamic_hdr_smpte2094_app5_alloc(ಖಾಲಿ);
    app5_rt = av_dynamic_hdr_smpte2094_app5_alloc(ಖಾಲಿ);
    ಆದರೆ (!app5 || !app5_rt) {
        av_freep(&app5);
        av_freep(&app5_rt);
        ಹಿಂತಿರುಗಿ;
    }
    fill_app5_ಕನಿಷ್ಠತಮ(app5);

    ಬರೆ("\nTesting av_dynamic_hdr_smpte2094_app5_to_t35()\n");
    required = 0;
    ret = av_dynamic_hdr_smpte2094_app5_ಗಮ್ಯ_t35(app5, ಖಾಲಿ, &required);
    ಬರೆ("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    buf  = ಖಾಲಿ;
    ಗಾತ್ರ_2 = 0;
    ret = av_dynamic_hdr_smpte2094_app5_ಗಮ್ಯ_t35(app5, &buf, &ಗಾತ್ರ_2);
    ಬರೆ("alloc mode: ret=%d size_match=%s\n", ret,
           ಗಾತ್ರ_2 == required ? "yes" : "no");
    av_freep(&buf);

    ಬರೆ("\nTesting round trip, no adaptive tone map\n");
    ret = app5_ಸುತ್ತು_trip(app5, app5_rt);
    ಬರೆ("round trip: ret=%d\n", ret);
    ಆದರೆ (ret >= 0)
        print_app5("decoded", app5_rt);

    ಬರೆ("\nTesting round trip, reference-white tone mapping\n");
    fill_app5_reference_white(app5);
    ret = app5_ಸುತ್ತು_trip(app5, app5_rt);
    ಬರೆ("round trip: ret=%d\n", ret);
    ಆದರೆ (ret >= 0)
        print_app5("decoded", app5_rt);

    ಬರೆ("\nTesting round trip, per-image mixing and curve parameters\n");
    fill_app5_ಪ್ರತಿ_image(app5);
    ret = app5_ಸುತ್ತು_trip(app5, app5_rt);
    ಬರೆ("round trip: ret=%d\n", ret);
    ಆದರೆ (ret >= 0)
        print_app5("decoded", app5_rt);

    ಬರೆ("\nTesting round trip, common mixing and curve parameters\n");
    fill_app5_common(app5);
    ret = app5_ಸುತ್ತು_trip(app5, app5_rt);
    ಬರೆ("round trip: ret=%d\n", ret);
    ಆದರೆ (ret >= 0)
        print_app5("decoded", app5_rt);

    ಬರೆ("\nTesting error paths\n");
    buf  = ಖಾಲಿ;
    ಗಾತ್ರ_2 = 0;
    ret = av_dynamic_hdr_smpte2094_app5_ಗಮ್ಯ_t35(ಖಾಲಿ, &buf, &ಗಾತ್ರ_2);
    ಬರೆ("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_smpte2094_app5_from_t35(ಖಾಲಿ, (ಸ್ಥಿರಾಂಕ uint8_t *)"", 0);
    ಬರೆ("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    /* application_version does not fit the 3-bit field. */
    app5->application_ಆವೃತ್ತಿ = 8;
    ret = av_dynamic_hdr_smpte2094_app5_ಗಮ್ಯ_t35(app5, ಖಾಲಿ, &ಗಾತ್ರ_2);
    ಬರೆ("to_t35 invalid application_version: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->application_ಆವೃತ್ತಿ = 1;

    /* minimum_application_version above the documented maximum. */
    app5->minimum_application_ಆವೃತ್ತಿ = 3;
    ret = av_dynamic_hdr_smpte2094_app5_ಗಮ್ಯ_t35(app5, ಖಾಲಿ, &ಗಾತ್ರ_2);
    ಬರೆ("to_t35 invalid minimum_application_version:"
           " ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->minimum_application_ಆವೃತ್ತಿ = 0;

    /* More alternate images than the 3-bit count admits. */
    app5->ಅಂಕೆ_alternate_images = 5;
    ret = av_dynamic_hdr_smpte2094_app5_ಗಮ್ಯ_t35(app5, ಖಾಲಿ, &ಗಾತ್ರ_2);
    ಬರೆ("to_t35 too many alternate images: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");

    av_freep(&app5);
    av_freep(&app5_rt);

    ಬರೆ("\nTesting OOM path\n");
    av_max_alloc(1);
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&ಗಾತ್ರ_2);
    ಬರೆ("alloc OOM: %s\n", app5 ? "FAIL" : "OK");
    av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
    av_freep(&app5);
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    test_hdr_plus();
    test_app5();
    ಹಿಂತಿರುಗಿ 0;
}

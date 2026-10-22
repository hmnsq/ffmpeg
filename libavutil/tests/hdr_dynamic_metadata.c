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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hdr_dynamic_metadata.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/rational.h"

/* Denominators av_dynamic_hdr_plus_to_t35() quantises to. The fixtures below
 * express every rational in these terms, so a correct round trip reproduces
 * the input exactly and the decoded values printed here can be compared
 * against the fixture directly. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LUMINANCE_DEN          1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PEAK_LUMINANCE_DEN    15
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RGB_DEN           100000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FRACTION_PIXEL_DEN  1000
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ KNEE_ਬਿੰਦੂ_DEN      4095
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BEZIER_ANCHOR_DEN   1023
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SATURATION_DEN         8

/*
 * Printers. Every field a fixture populates is printed, so that a serializer
 * or parser which drops or corrupts a value changes the FATE reference
 * instead of silently passing a flag-only check.
 */

ਸਥਿਰ ਖਾਲੀ print_peak_ਮੈਟ੍ਰਿਕਸ(ਅਚਲ ਅੱਖਰ *label, ਪੂਰਨ ਪੰਕਤੀਆਂ, ਪੂਰਨ ਖਾਨੇ_ਗਿਣਤੀ,
                              ਅਚਲ AVRational m[25][25])
{
    ਲਿਖੋ("    %s %dx%d:", label, ਪੰਕਤੀਆਂ, ਖਾਨੇ_ਗਿਣਤੀ);
    ਲਈ (ਪੂਰਨ i = 0; i < ਪੰਕਤੀਆਂ; i++)
        ਲਈ (ਪੂਰਨ j = 0; j < ਖਾਨੇ_ਗਿਣਤੀ; j++)
            ਲਿਖੋ(" %d/%d", m[i][j].ਅੰਕ, m[i][j].den);
    ਲਿਖੋ("\n");
}

ਸਥਿਰ ਖਾਲੀ print_ਖਿੜਕੀ(ਪੂਰਨ w, ਅਚਲ AVHDRPlusColorTransformParams *p,
                         ਪੂਰਨ geometry)
{
    ਲਿਖੋ("  window %d:\n", w);
    /* Window 0 covers the whole frame; its geometry is not serialized. */
    ਜੇ (geometry) {
        ਲਿਖੋ("    corners: ul=%d/%d,%d/%d lr=%d/%d,%d/%d\n",
               p->ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_x.ਅੰਕ,
               p->ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_x.den,
               p->ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_y.ਅੰਕ,
               p->ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_y.den,
               p->ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_x.ਅੰਕ,
               p->ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_x.den,
               p->ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_y.ਅੰਕ,
               p->ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_y.den);
        ਲਿਖੋ("    ellipse: center=%u,%u rotation=%u semimajor_int=%u"
               " semimajor_ext=%u semiminor_ext=%u overlap=%u\n",
               p->center_ਦਾ_ellipse_x, p->center_ਦਾ_ellipse_y,
               p->rotation_angle, p->semimajor_axis_ਅੰਦਰੂਨੀ_ellipse,
               p->semimajor_axis_external_ellipse,
               p->semiminor_axis_external_ellipse,
               p->overlap_process_option);
    }
    ਲਿਖੋ("    maxscl: %d/%d %d/%d %d/%d average_maxrgb=%d/%d\n",
           p->maxscl[0].ਅੰਕ, p->maxscl[0].den,
           p->maxscl[1].ਅੰਕ, p->maxscl[1].den,
           p->maxscl[2].ਅੰਕ, p->maxscl[2].den,
           p->ਔਸਤਨ_maxrgb.ਅੰਕ, p->ਔਸਤਨ_maxrgb.den);
    ਲਿਖੋ("    distribution_maxrgb: n=%u",
           p->ਅੰਕ_distribution_maxrgb_percentiles);
    ਲਈ (ਪੂਰਨ i = 0; i < p->ਅੰਕ_distribution_maxrgb_percentiles; i++)
        ਲਿਖੋ(" %u%%=%d/%d", p->distribution_maxrgb[i].percentage,
               p->distribution_maxrgb[i].percentile.ਅੰਕ,
               p->distribution_maxrgb[i].percentile.den);
    ਲਿਖੋ("\n    fraction_bright_pixels=%d/%d\n",
           p->fraction_bright_pixels.ਅੰਕ, p->fraction_bright_pixels.den);
    ਲਿਖੋ("    tone_mapping_flag=%u", p->tone_mapping_flag);
    ਜੇ (p->tone_mapping_flag) {
        ਲਿਖੋ(" knee=%d/%d,%d/%d anchors=%u:",
               p->knee_ਬਿੰਦੂ_x.ਅੰਕ, p->knee_ਬਿੰਦੂ_x.den,
               p->knee_ਬਿੰਦੂ_y.ਅੰਕ, p->knee_ਬਿੰਦੂ_y.den,
               p->ਅੰਕ_bezier_ਵਕਰ_anchors);
        ਲਈ (ਪੂਰਨ i = 0; i < p->ਅੰਕ_bezier_ਵਕਰ_anchors; i++)
            ਲਿਖੋ(" %d/%d", p->bezier_ਵਕਰ_anchors[i].ਅੰਕ,
                   p->bezier_ਵਕਰ_anchors[i].den);
    }
    ਲਿਖੋ("\n    color_saturation_mapping_flag=%u",
           p->color_saturation_mapping_flag);
    ਜੇ (p->color_saturation_mapping_flag)
        ਲਿਖੋ(" weight=%d/%d", p->color_saturation_ਭਾਰ.ਅੰਕ,
               p->color_saturation_ਭਾਰ.den);
    ਲਿਖੋ("\n");
}

ਸਥਿਰ ਖਾਲੀ print_hdr_plus(ਅਚਲ ਅੱਖਰ *label, ਅਚਲ AVDynamicHDRPlus *s)
{
    ਲਿਖੋ("%s:\n", label);
    ਲਿਖੋ("  application_version=%u num_windows=%u"
           " targeted_system_display_maximum_luminance=%d/%d\n",
           s->application_ਸੰਸਕਰਣ, s->ਅੰਕ_windows,
           s->targeted_system_display_ਵੱਧ_ਤੋਂ_ਵੱਧ_luminance.ਅੰਕ,
           s->targeted_system_display_ਵੱਧ_ਤੋਂ_ਵੱਧ_luminance.den);
    ਲਿਖੋ("  targeted_system_display_actual_peak_luminance_flag=%u\n",
           s->targeted_system_display_actual_peak_luminance_flag);
    ਜੇ (s->targeted_system_display_actual_peak_luminance_flag)
        print_peak_ਮੈਟ੍ਰਿਕਸ("targeted_peak",
                          s->ਅੰਕ_ਪੰਕਤੀਆਂ_targeted_system_display_actual_peak_luminance,
                          s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_targeted_system_display_actual_peak_luminance,
                          s->targeted_system_display_actual_peak_luminance);
    ਲਿਖੋ("  mastering_display_actual_peak_luminance_flag=%u\n",
           s->mastering_display_actual_peak_luminance_flag);
    ਜੇ (s->mastering_display_actual_peak_luminance_flag)
        print_peak_ਮੈਟ੍ਰਿਕਸ("mastering_peak",
                          s->ਅੰਕ_ਪੰਕਤੀਆਂ_mastering_display_actual_peak_luminance,
                          s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_mastering_display_actual_peak_luminance,
                          s->mastering_display_actual_peak_luminance);
    ਲਈ (ਪੂਰਨ w = 0; w < s->ਅੰਕ_windows; w++)
        print_ਖਿੜਕੀ(w, &s->params[w], w > 0);
}

ਸਥਿਰ ਖਾਲੀ print_app5(ਅਚਲ ਅੱਖਰ *label, ਅਚਲ AVDynamicHDRSmpte2094App5 *s)
{
    ਲਿਖੋ("%s:\n", label);
    ਲਿਖੋ("  application_version=%u minimum_application_version=%u\n",
           s->application_ਸੰਸਕਰਣ, s->minimum_application_ਸੰਸਕਰਣ);
    ਲਿਖੋ("  has_custom_hdr_reference_white_flag=%u",
           s->has_custom_hdr_reference_white_flag);
    ਜੇ (s->has_custom_hdr_reference_white_flag)
        ਲਿਖੋ(" hdr_reference_white=0x%04x", s->hdr_reference_white);
    ਲਿਖੋ("\n  has_adaptive_tone_map_flag=%u\n",
           s->has_adaptive_tone_map_flag);
    ਜੇ (!s->has_adaptive_tone_map_flag)
        ਵਾਪਸ;

    ਲਿਖੋ("  baseline_hdr_headroom=0x%04x"
           " use_reference_white_tone_mapping_flag=%u\n",
           s->baseline_hdr_headroom, s->use_reference_white_tone_mapping_flag);
    ਜੇ (s->use_reference_white_tone_mapping_flag)
        ਵਾਪਸ;

    ਲਿਖੋ("  num_alternate_images=%u chromaticities_flag=%u"
           " has_common_component_mix_params_flag=%u"
           " has_common_curve_params_flag=%u\n",
           s->ਅੰਕ_alternate_images,
           s->gain_application_space_chromaticities_flag,
           s->has_common_component_mix_params_flag,
           s->has_common_ਵਕਰ_params_flag);
    ਜੇ (s->gain_application_space_chromaticities_flag == 3) {
        ਲਿਖੋ("  chromaticities:");
        ਲਈ (ਪੂਰਨ r = 0; r < 8; r++)
            ਲਿਖੋ(" 0x%04x", s->gain_application_space_chromaticities[r]);
        ਲਿਖੋ("\n");
    }

    ਲਈ (ਪੂਰਨ a = 0; a < s->ਅੰਕ_alternate_images; a++) {
        ਪੂਰਨ n = s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a] + 1;
        ਲਿਖੋ("  alternate %d: hdr_headroom=0x%04x component_mixing_type=%u\n",
               a, s->alternate_hdr_headrooms[a], s->component_mixing_type[a]);
        ਜੇ (s->component_mixing_type[a] == 3) {
            ਲਿਖੋ("    mixing flag:coefficient:");
            ਲਈ (ਪੂਰਨ k = 0; k < 6; k++)
                ਲਿਖੋ(" %u:0x%04x",
                       s->has_component_mixing_coefficient_flag[a][k],
                       s->component_mixing_coefficient[a][k]);
            ਲਿਖੋ("\n");
        }
        ਲਿਖੋ("    curve: num_control_points=%d use_pchip_slope=%u\n", n,
               s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a]);
        ਲਿਖੋ("    x:");
        ਲਈ (ਪੂਰਨ c = 0; c < n; c++)
            ਲਿਖੋ(" 0x%04x", s->gain_ਵਕਰ_control_points_x[a][c]);
        ਲਿਖੋ("\n    y:");
        ਲਈ (ਪੂਰਨ c = 0; c < n; c++)
            ਲਿਖੋ(" 0x%04x", s->gain_ਵਕਰ_control_points_y[a][c]);
        ਲਿਖੋ("\n");
        /* theta is only serialized when the pchip slope is not used. */
        ਜੇ (!s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a]) {
            ਲਿਖੋ("    theta:");
            ਲਈ (ਪੂਰਨ c = 0; c < n; c++)
                ਲਿਖੋ(" 0x%04x", s->gain_ਵਕਰ_control_points_theta[a][c]);
            ਲਿਖੋ("\n");
        }
    }
}

/*
 * Round-trip helpers: serialize, then parse back into a zeroed struct.
 */

ਸਥਿਰ ਪੂਰਨ hdr_plus_ਗੇੜਾ_trip(ਅਚਲ AVDynamicHDRPlus *ਵਿੱਚ_2, AVDynamicHDRPlus *ਬਾਹਰਲਾ)
{
    uint8_t *buf = ਨਿਰਾ;
    size_t ਮਾਪ = 0;
    ਪੂਰਨ ret;

    ret = av_dynamic_hdr_plus_ਮੰਜ਼ਿਲ_t35(ਵਿੱਚ_2, &buf, &ਮਾਪ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    memset(ਬਾਹਰਲਾ, 0, ਆਕਾਰ(*ਬਾਹਰਲਾ));
    ret = av_dynamic_hdr_plus_from_t35(ਬਾਹਰਲਾ, buf, ਮਾਪ);
    av_free(buf);
    ਵਾਪਸ ret;
}

ਸਥਿਰ ਪੂਰਨ app5_ਗੇੜਾ_trip(ਅਚਲ AVDynamicHDRSmpte2094App5 *ਵਿੱਚ_2,
                           AVDynamicHDRSmpte2094App5 *ਬਾਹਰਲਾ)
{
    uint8_t *buf = ਨਿਰਾ;
    size_t ਮਾਪ = 0;
    ਪੂਰਨ ret;

    ret = av_dynamic_hdr_smpte2094_app5_ਮੰਜ਼ਿਲ_t35(ਵਿੱਚ_2, &buf, &ਮਾਪ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    memset(ਬਾਹਰਲਾ, 0, ਆਕਾਰ(*ਬਾਹਰਲਾ));
    ret = av_dynamic_hdr_smpte2094_app5_from_t35(ਬਾਹਰਲਾ, buf, ਮਾਪ);
    av_free(buf);
    ਵਾਪਸ ret;
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
ਸਥਿਰ ਖਾਲੀ fill_hdr_plus_conforming(AVDynamicHDRPlus *s)
{
    ਸਥਿਰ ਅਚਲ uint8_t percentages[9] = { 1, 5, 10, 25, 50, 75, 90, 95, 99 };
    ਸਥਿਰ ਅਚਲ ਪੂਰਨ percentiles[9] = {
        1000, 0, 255, 25000, 50000, 75000, 90000, 95000, 99000,
    };

    memset(s, 0, ਆਕਾਰ(*s));

    s->application_ਸੰਸਕਰਣ = 1;
    s->ਅੰਕ_windows         = 1;
    s->targeted_system_display_ਵੱਧ_ਤੋਂ_ਵੱਧ_luminance =
        (AVRational){ 400, LUMINANCE_DEN };
    s->targeted_system_display_actual_peak_luminance_flag = 0;
    s->mastering_display_actual_peak_luminance_flag       = 0;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 99000, RGB_DEN };
    s->params[0].ਔਸਤਨ_maxrgb = (AVRational){ 40000, RGB_DEN };

    s->params[0].ਅੰਕ_distribution_maxrgb_percentiles = 9;
    ਲਈ (ਪੂਰਨ i = 0; i < 9; i++) {
        s->params[0].distribution_maxrgb[i].percentage = percentages[i];
        s->params[0].distribution_maxrgb[i].percentile =
            (AVRational){ percentiles[i], RGB_DEN };
    }
    s->params[0].fraction_bright_pixels =
        (AVRational){ 250, FRACTION_PIXEL_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_ਬਿੰਦੂ_x = (AVRational){  512, KNEE_ਬਿੰਦੂ_DEN };
    s->params[0].knee_ਬਿੰਦੂ_y = (AVRational){ 1024, KNEE_ਬਿੰਦੂ_DEN };
    s->params[0].ਅੰਕ_bezier_ਵਕਰ_anchors = 9;
    ਲਈ (ਪੂਰਨ i = 0; i < 9; i++)
        s->params[0].bezier_ਵਕਰ_anchors[i] =
            (AVRational){ 100 * (i + 1), BEZIER_ANCHOR_DEN };

    s->params[0].color_saturation_mapping_flag = 0;
}

/* Deliberately NOT a conforming Version 1 payload: it combines a second
 * processing window, both actual-peak-luminance matrices and
 * ColorSaturationWeight, all of which §9.4 excludes for Version 1. It exists
 * only to drive the optional serializer/parser branches those fields guard. */
ਸਥਿਰ ਖਾਲੀ fill_hdr_plus_synthetic(AVDynamicHDRPlus *s)
{
    memset(s, 0, ਆਕਾਰ(*s));

    s->application_ਸੰਸਕਰਣ = 1;
    s->ਅੰਕ_windows         = 2;
    s->targeted_system_display_ਵੱਧ_ਤੋਂ_ਵੱਧ_luminance =
        (AVRational){ 10000, LUMINANCE_DEN };

    s->params[1].ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_x  = (AVRational){ 100, 1 };
    s->params[1].ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_y  = (AVRational){ 120, 1 };
    s->params[1].ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_x = (AVRational){ 500, 1 };
    s->params[1].ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_y = (AVRational){ 520, 1 };
    s->params[1].center_ਦਾ_ellipse_x             = 300;
    s->params[1].center_ਦਾ_ellipse_y             = 320;
    s->params[1].rotation_angle                  = 45;
    s->params[1].semimajor_axis_ਅੰਦਰੂਨੀ_ellipse = 50;
    s->params[1].semimajor_axis_external_ellipse = 100;
    s->params[1].semiminor_axis_external_ellipse = 80;
    s->params[1].overlap_process_option          = 1;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 70000, RGB_DEN };
    s->params[0].ਔਸਤਨ_maxrgb = (AVRational){ 40000, RGB_DEN };
    s->params[0].ਅੰਕ_distribution_maxrgb_percentiles = 2;
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
    s->params[1].ਔਸਤਨ_maxrgb = (AVRational){ 25000, RGB_DEN };
    s->params[1].ਅੰਕ_distribution_maxrgb_percentiles = 1;
    s->params[1].distribution_maxrgb[0].percentage = 25;
    s->params[1].distribution_maxrgb[0].percentile =
        (AVRational){ 12500, RGB_DEN };
    s->params[1].fraction_bright_pixels =
        (AVRational){ 100, FRACTION_PIXEL_DEN };

    s->targeted_system_display_actual_peak_luminance_flag = 1;
    s->ਅੰਕ_ਪੰਕਤੀਆਂ_targeted_system_display_actual_peak_luminance = 2;
    s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_targeted_system_display_actual_peak_luminance = 3;
    ਲਈ (ਪੂਰਨ i = 0; i < 2; i++)
        ਲਈ (ਪੂਰਨ j = 0; j < 3; j++)
            s->targeted_system_display_actual_peak_luminance[i][j] =
                (AVRational){ i * 3 + j, PEAK_LUMINANCE_DEN };

    s->mastering_display_actual_peak_luminance_flag = 1;
    s->ਅੰਕ_ਪੰਕਤੀਆਂ_mastering_display_actual_peak_luminance = 3;
    s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_mastering_display_actual_peak_luminance = 2;
    ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
        ਲਈ (ਪੂਰਨ j = 0; j < 2; j++)
            s->mastering_display_actual_peak_luminance[i][j] =
                (AVRational){ 15 - (i * 2 + j), PEAK_LUMINANCE_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_ਬਿੰਦੂ_x = (AVRational){ 500, KNEE_ਬਿੰਦੂ_DEN };
    s->params[0].knee_ਬਿੰਦੂ_y = (AVRational){ 800, KNEE_ਬਿੰਦੂ_DEN };
    s->params[0].ਅੰਕ_bezier_ਵਕਰ_anchors = 3;
    s->params[0].bezier_ਵਕਰ_anchors[0] = (AVRational){ 100, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_ਵਕਰ_anchors[1] = (AVRational){ 500, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_ਵਕਰ_anchors[2] = (AVRational){ 900, BEZIER_ANCHOR_DEN };
    s->params[1].tone_mapping_flag = 0;

    ਲਈ (ਪੂਰਨ w = 0; w < 2; w++) {
        s->params[w].color_saturation_mapping_flag = 1;
        s->params[w].color_saturation_ਭਾਰ =
            (AVRational){ 8 + w, SATURATION_DEN };
    }
}

ਸਥਿਰ ਖਾਲੀ test_hdr_plus(ਖਾਲੀ)
{
    AVDynamicHDRPlus *hdr, *hdr_rt;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ = 0, required = 0;
    uint8_t *buf = ਨਿਰਾ;
    ਪੂਰਨ ret;

    ਲਿਖੋ("=== AVDynamicHDRPlus ===\n");

    ਲਿਖੋ("Testing av_dynamic_hdr_plus_alloc()\n");
    hdr = av_dynamic_hdr_plus_alloc(&ਮਾਪ);
    ਲਿਖੋ("alloc: %s size>0=%s\n", hdr ? "OK" : "FAIL",
           ਮਾਪ > 0 ? "yes" : "no");
    av_freep(&hdr);

    hdr = av_dynamic_hdr_plus_alloc(ਨਿਰਾ);
    ਲਿਖੋ("alloc (no size): %s\n", hdr ? "OK" : "FAIL");
    av_freep(&hdr);

    ਲਿਖੋ("\nTesting av_dynamic_hdr_plus_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        hdr = av_dynamic_hdr_plus_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਲਿਖੋ("create_side_data: %s\n", hdr ? "OK" : "FAIL");
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    hdr    = av_dynamic_hdr_plus_alloc(ਨਿਰਾ);
    hdr_rt = av_dynamic_hdr_plus_alloc(ਨਿਰਾ);
    ਜੇ (!hdr || !hdr_rt) {
        av_freep(&hdr);
        av_freep(&hdr_rt);
        ਵਾਪਸ;
    }
    fill_hdr_plus_conforming(hdr);

    /* Size-query mode: data=NULL, size receives the required byte count. */
    ਲਿਖੋ("\nTesting av_dynamic_hdr_plus_to_t35() size query\n");
    required = 0;
    ret = av_dynamic_hdr_plus_ਮੰਜ਼ਿਲ_t35(hdr, ਨਿਰਾ, &required);
    ਲਿਖੋ("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    /* Allocation mode: *data=NULL, the function allocates the buffer. */
    ਲਿਖੋ("\nTesting av_dynamic_hdr_plus_to_t35() allocation\n");
    buf  = ਨਿਰਾ;
    ਮਾਪ = 0;
    ret = av_dynamic_hdr_plus_ਮੰਜ਼ਿਲ_t35(hdr, &buf, &ਮਾਪ);
    ਲਿਖੋ("alloc mode: ret=%d size_match=%s\n", ret,
           ਮਾਪ == required ? "yes" : "no");
    av_freep(&buf);

    /* Existing-buffer mode: a caller-owned buffer is filled in place. */
    ਲਿਖੋ("\nTesting av_dynamic_hdr_plus_to_t35() existing buffer\n");
    buf = av_malloc(required);
    ਜੇ (buf) {
        uint8_t *orig = buf;
        ਮਾਪ = required;
        ret = av_dynamic_hdr_plus_ਮੰਜ਼ਿਲ_t35(hdr, &buf, &ਮਾਪ);
        ਲਿਖੋ("existing buf: ret=%d same_pointer=%s size_match=%s\n", ret,
               buf == orig ? "yes" : "no",
               ਮਾਪ == required ? "yes" : "no");
        av_freep(&buf);
    }

    /* Buffer-too-small: caller-owned buffer shorter than required. */
    ਲਿਖੋ("\nTesting av_dynamic_hdr_plus_to_t35() buffer too small\n");
    ਜੇ (required > 1) {
        buf = av_malloc(required - 1);
        ਜੇ (buf) {
            ਮਾਪ = required - 1;
            ret = av_dynamic_hdr_plus_ਮੰਜ਼ਿਲ_t35(hdr, &buf, &ਮਾਪ);
            ਲਿਖੋ("too small: ret==AVERROR_BUFFER_TOO_SMALL=%s\n",
                   ret == AVERROR_ਬਫਰ_TOO_SMALL ? "yes" : "no");
            av_freep(&buf);
        }
    }

    ਲਿਖੋ("\nTesting round trip, conforming ST 2094-40 Version 1 payload\n");
    ret = hdr_plus_ਗੇੜਾ_trip(hdr, hdr_rt);
    ਲਿਖੋ("round trip: ret=%d\n", ret);
    ਜੇ (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    /* to_t35() ignores application_version and always writes the CTA-861-H
     * value, so the parsed field does not echo an out-of-range input. */
    ਲਿਖੋ("\nTesting that to_t35() overrides application_version\n");
    hdr->application_ਸੰਸਕਰਣ = 7;
    ret = hdr_plus_ਗੇੜਾ_trip(hdr, hdr_rt);
    ਲਿਖੋ("input=7 ret=%d decoded application_version=%u\n", ret,
           hdr_rt->application_ਸੰਸਕਰਣ);
    hdr->application_ਸੰਸਕਰਣ = 1;

    ਲਿਖੋ("\nTesting round trip, synthetic payload (branch coverage only)\n");
    fill_hdr_plus_synthetic(hdr);
    ret = hdr_plus_ਗੇੜਾ_trip(hdr, hdr_rt);
    ਲਿਖੋ("round trip: ret=%d\n", ret);
    ਜੇ (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    ਲਿਖੋ("\nTesting error paths\n");
    buf  = ਨਿਰਾ;
    ਮਾਪ = 0;
    ret = av_dynamic_hdr_plus_ਮੰਜ਼ਿਲ_t35(ਨਿਰਾ, &buf, &ਮਾਪ);
    ਲਿਖੋ("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_ਮੰਜ਼ਿਲ_t35(hdr, ਨਿਰਾ, ਨਿਰਾ);
    ਲਿਖੋ("to_t35 no data no size: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_from_t35(ਨਿਰਾ, (ਅਚਲ uint8_t *)"", 0);
    ਲਿਖੋ("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    {
        /* Oversized input is rejected before parsing. */
        size_t big = AV_HDR_PLUS_MAX_PAYLOAD_ਮਾਪ + 1;
        uint8_t *oversized = av_mallocz(big);
        ਜੇ (oversized) {
            ret = av_dynamic_hdr_plus_from_t35(hdr_rt, oversized, big);
            ਲਿਖੋ("from_t35 oversized: ret==AVERROR(EINVAL)=%s\n",
                   ret == AVERROR(EINVAL) ? "yes" : "no");
            av_free(oversized);
        }
    }

    av_freep(&hdr);
    av_freep(&hdr_rt);

    ਲਿਖੋ("\nTesting OOM path\n");
    av_max_alloc(1);
    hdr = av_dynamic_hdr_plus_alloc(&ਮਾਪ);
    ਲਿਖੋ("alloc OOM: %s\n", hdr ? "FAIL" : "OK");
    av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
    av_freep(&hdr);
}

/* Table C.2 early-out: no adaptive tone map, custom reference white only. */
ਸਥਿਰ ਖਾਲੀ fill_app5_ਨਿਊਨਤਮ(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, ਆਕਾਰ(*s));
    s->application_ਸੰਸਕਰਣ         = 1;
    s->minimum_application_ਸੰਸਕਰਣ = 0;
    s->has_custom_hdr_reference_white_flag = 1;
    s->hdr_reference_white         = 0x0203;
    s->has_adaptive_tone_map_flag  = 0;
}

/* Table C.3 early-out: reference-white tone mapping, no alternate images. */
ਸਥਿਰ ਖਾਲੀ fill_app5_reference_white(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, ਆਕਾਰ(*s));
    s->application_ਸੰਸਕਰਣ        = 2;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->use_reference_white_tone_mapping_flag = 1;
}

/* Per-image parameters: explicit gain application space chromaticities,
 * component mixing type 3 with a mix of present and absent coefficients, and
 * explicit control point slopes (theta). */
ਸਥਿਰ ਖਾਲੀ fill_app5_ਪ੍ਰਤੀ_image(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, ਆਕਾਰ(*s));
    s->application_ਸੰਸਕਰਣ        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->ਅੰਕ_alternate_images       = 2;
    s->gain_application_space_chromaticities_flag = 3;
    ਲਈ (ਪੂਰਨ r = 0; r < 8; r++)
        s->gain_application_space_chromaticities[r] = 100 * (r + 1);
    s->has_common_component_mix_params_flag = 0;
    s->has_common_ਵਕਰ_params_flag         = 0;
    ਲਈ (ਪੂਰਨ a = 0; a < 2; a++) {
        s->alternate_hdr_headrooms[a] = 0x0100 + a;
        s->component_mixing_type[a]   = 3;
        ਲਈ (ਪੂਰਨ k = 0; k < 6; k++) {
            s->has_component_mixing_coefficient_flag[a][k] = k & 1;
            s->component_mixing_coefficient[a][k] = 0x1000 + 0x10 * a + k;
        }
        s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a] = 1;
        s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a]       = 0;
        ਲਈ (ਪੂਰਨ c = 0; c < 2; c++) {
            s->gain_ਵਕਰ_control_points_x[a][c]     = 0x2000 + 0x10 * a + c;
            s->gain_ਵਕਰ_control_points_y[a][c]     = 0x3000 + 0x10 * a + c;
            s->gain_ਵਕਰ_control_points_theta[a][c] = 0x4000 + 0x10 * a + c;
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
ਸਥਿਰ ਖਾਲੀ fill_app5_common(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, ਆਕਾਰ(*s));
    s->application_ਸੰਸਕਰਣ        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0def;
    s->ਅੰਕ_alternate_images       = 3;
    s->gain_application_space_chromaticities_flag = 0;
    s->has_common_component_mix_params_flag = 1;
    s->has_common_ਵਕਰ_params_flag         = 1;
    ਲਈ (ਪੂਰਨ a = 0; a < 3; a++) {
        s->alternate_hdr_headrooms[a] = 0x0200 + a;
        s->component_mixing_type[a]   = 1;
        s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a] = 2;
        s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a]       = 1;
        ਲਈ (ਪੂਰਨ c = 0; c < 3; c++) {
            s->gain_ਵਕਰ_control_points_x[a][c] = 0x5000 + c;
            s->gain_ਵਕਰ_control_points_y[a][c] = 0x6000 + 0x10 * a + c;
        }
    }
}

ਸਥਿਰ ਖਾਲੀ test_app5(ਖਾਲੀ)
{
    AVDynamicHDRSmpte2094App5 *app5, *app5_rt;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ = 0, required = 0;
    uint8_t *buf = ਨਿਰਾ;
    ਪੂਰਨ ret;

    ਲਿਖੋ("\n=== AVDynamicHDRSmpte2094App5 ===\n");
    ਲਿਖੋ("Testing av_dynamic_hdr_smpte2094_app5_alloc()\n");
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&ਮਾਪ);
    ਲਿਖੋ("alloc: %s size>0=%s\n", app5 ? "OK" : "FAIL",
           ਮਾਪ > 0 ? "yes" : "no");
    av_freep(&app5);

    ਲਿਖੋ("\nTesting av_dynamic_hdr_smpte2094_app5_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        app5 = av_dynamic_hdr_smpte2094_app5_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਲਿਖੋ("create_side_data: %s\n", app5 ? "OK" : "FAIL");
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    app5    = av_dynamic_hdr_smpte2094_app5_alloc(ਨਿਰਾ);
    app5_rt = av_dynamic_hdr_smpte2094_app5_alloc(ਨਿਰਾ);
    ਜੇ (!app5 || !app5_rt) {
        av_freep(&app5);
        av_freep(&app5_rt);
        ਵਾਪਸ;
    }
    fill_app5_ਨਿਊਨਤਮ(app5);

    ਲਿਖੋ("\nTesting av_dynamic_hdr_smpte2094_app5_to_t35()\n");
    required = 0;
    ret = av_dynamic_hdr_smpte2094_app5_ਮੰਜ਼ਿਲ_t35(app5, ਨਿਰਾ, &required);
    ਲਿਖੋ("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    buf  = ਨਿਰਾ;
    ਮਾਪ = 0;
    ret = av_dynamic_hdr_smpte2094_app5_ਮੰਜ਼ਿਲ_t35(app5, &buf, &ਮਾਪ);
    ਲਿਖੋ("alloc mode: ret=%d size_match=%s\n", ret,
           ਮਾਪ == required ? "yes" : "no");
    av_freep(&buf);

    ਲਿਖੋ("\nTesting round trip, no adaptive tone map\n");
    ret = app5_ਗੇੜਾ_trip(app5, app5_rt);
    ਲਿਖੋ("round trip: ret=%d\n", ret);
    ਜੇ (ret >= 0)
        print_app5("decoded", app5_rt);

    ਲਿਖੋ("\nTesting round trip, reference-white tone mapping\n");
    fill_app5_reference_white(app5);
    ret = app5_ਗੇੜਾ_trip(app5, app5_rt);
    ਲਿਖੋ("round trip: ret=%d\n", ret);
    ਜੇ (ret >= 0)
        print_app5("decoded", app5_rt);

    ਲਿਖੋ("\nTesting round trip, per-image mixing and curve parameters\n");
    fill_app5_ਪ੍ਰਤੀ_image(app5);
    ret = app5_ਗੇੜਾ_trip(app5, app5_rt);
    ਲਿਖੋ("round trip: ret=%d\n", ret);
    ਜੇ (ret >= 0)
        print_app5("decoded", app5_rt);

    ਲਿਖੋ("\nTesting round trip, common mixing and curve parameters\n");
    fill_app5_common(app5);
    ret = app5_ਗੇੜਾ_trip(app5, app5_rt);
    ਲਿਖੋ("round trip: ret=%d\n", ret);
    ਜੇ (ret >= 0)
        print_app5("decoded", app5_rt);

    ਲਿਖੋ("\nTesting error paths\n");
    buf  = ਨਿਰਾ;
    ਮਾਪ = 0;
    ret = av_dynamic_hdr_smpte2094_app5_ਮੰਜ਼ਿਲ_t35(ਨਿਰਾ, &buf, &ਮਾਪ);
    ਲਿਖੋ("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_smpte2094_app5_from_t35(ਨਿਰਾ, (ਅਚਲ uint8_t *)"", 0);
    ਲਿਖੋ("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    /* application_version does not fit the 3-bit field. */
    app5->application_ਸੰਸਕਰਣ = 8;
    ret = av_dynamic_hdr_smpte2094_app5_ਮੰਜ਼ਿਲ_t35(app5, ਨਿਰਾ, &ਮਾਪ);
    ਲਿਖੋ("to_t35 invalid application_version: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->application_ਸੰਸਕਰਣ = 1;

    /* minimum_application_version above the documented maximum. */
    app5->minimum_application_ਸੰਸਕਰਣ = 3;
    ret = av_dynamic_hdr_smpte2094_app5_ਮੰਜ਼ਿਲ_t35(app5, ਨਿਰਾ, &ਮਾਪ);
    ਲਿਖੋ("to_t35 invalid minimum_application_version:"
           " ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->minimum_application_ਸੰਸਕਰਣ = 0;

    /* More alternate images than the 3-bit count admits. */
    app5->ਅੰਕ_alternate_images = 5;
    ret = av_dynamic_hdr_smpte2094_app5_ਮੰਜ਼ਿਲ_t35(app5, ਨਿਰਾ, &ਮਾਪ);
    ਲਿਖੋ("to_t35 too many alternate images: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");

    av_freep(&app5);
    av_freep(&app5_rt);

    ਲਿਖੋ("\nTesting OOM path\n");
    av_max_alloc(1);
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&ਮਾਪ);
    ਲਿਖੋ("alloc OOM: %s\n", app5 ? "FAIL" : "OK");
    av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
    av_freep(&app5);
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    test_hdr_plus();
    test_app5();
    ਵਾਪਸ 0;
}

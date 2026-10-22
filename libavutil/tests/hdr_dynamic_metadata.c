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

#ضمن <limits.h>
#ضمن <stdio.h>
#ضمن <string.h>

#ضمن "libavutil/error.h"
#ضمن "libavutil/frame.h"
#ضمن "libavutil/hdr_dynamic_metadata.h"
#ضمن "libavutil/mem.h"
#ضمن "libavutil/rational.h"

/* Denominators av_dynamic_hdr_plus_to_t35() quantises to. The fixtures below
 * express every rational in these terms, so a correct round trip reproduces
 * the input exactly and the decoded values printed here can be compared
 * against the fixture directly. */
#تعریف_کړه LUMINANCE_DEN          1
#تعریف_کړه PEAK_LUMINANCE_DEN    15
#تعریف_کړه RGB_DEN           100000
#تعریف_کړه FRACTION_PIXEL_DEN  1000
#تعریف_کړه KNEE_ټکی_DEN      4095
#تعریف_کړه BEZIER_ANCHOR_DEN   1023
#تعریف_کړه SATURATION_DEN         8

/*
 * Printers. Every field a fixture populates is printed, so that a serializer
 * or parser which drops or corrupts a value changes the FATE reference
 * instead of silently passing a flag-only check.
 */

ساكن فراغ print_peak_ماتریکس(ثابت حرف *label, صحيح لیکې, صحيح ستون_شمېر,
                              ثابت AVRational m[25][25])
{
    چاپ_کړه("    %s %dx%d:", label, لیکې, ستون_شمېر);
    لكل (صحيح i = 0; i < لیکې; i++)
        لكل (صحيح j = 0; j < ستون_شمېر; j++)
            چاپ_کړه(" %d/%d", m[i][j].عدد, m[i][j].den);
    چاپ_کړه("\n");
}

ساكن فراغ print_کړکۍ(صحيح w, ثابت AVHDRPlusColorTransformParams *p,
                         صحيح geometry)
{
    چاپ_کړه("  window %d:\n", w);
    /* Window 0 covers the whole frame; its geometry is not serialized. */
    إذا (geometry) {
        چاپ_کړه("    corners: ul=%d/%d,%d/%d lr=%d/%d,%d/%d\n",
               p->کړکۍ_پاسنی_کیڼ_کونج_x.عدد,
               p->کړکۍ_پاسنی_کیڼ_کونج_x.den,
               p->کړکۍ_پاسنی_کیڼ_کونج_y.عدد,
               p->کړکۍ_پاسنی_کیڼ_کونج_y.den,
               p->کړکۍ_ښکتنی_ښی_کونج_x.عدد,
               p->کړکۍ_ښکتنی_ښی_کونج_x.den,
               p->کړکۍ_ښکتنی_ښی_کونج_y.عدد,
               p->کړکۍ_ښکتنی_ښی_کونج_y.den);
        چاپ_کړه("    ellipse: center=%u,%u rotation=%u semimajor_int=%u"
               " semimajor_ext=%u semiminor_ext=%u overlap=%u\n",
               p->center_د_ellipse_x, p->center_د_ellipse_y,
               p->rotation_angle, p->semimajor_axis_دننی_ellipse,
               p->semimajor_axis_external_ellipse,
               p->semiminor_axis_external_ellipse,
               p->overlap_process_option);
    }
    چاپ_کړه("    maxscl: %d/%d %d/%d %d/%d average_maxrgb=%d/%d\n",
           p->maxscl[0].عدد, p->maxscl[0].den,
           p->maxscl[1].عدد, p->maxscl[1].den,
           p->maxscl[2].عدد, p->maxscl[2].den,
           p->اوسط_maxrgb.عدد, p->اوسط_maxrgb.den);
    چاپ_کړه("    distribution_maxrgb: n=%u",
           p->عدد_distribution_maxrgb_percentiles);
    لكل (صحيح i = 0; i < p->عدد_distribution_maxrgb_percentiles; i++)
        چاپ_کړه(" %u%%=%d/%d", p->distribution_maxrgb[i].percentage,
               p->distribution_maxrgb[i].percentile.عدد,
               p->distribution_maxrgb[i].percentile.den);
    چاپ_کړه("\n    fraction_bright_pixels=%d/%d\n",
           p->fraction_bright_pixels.عدد, p->fraction_bright_pixels.den);
    چاپ_کړه("    tone_mapping_flag=%u", p->tone_mapping_flag);
    إذا (p->tone_mapping_flag) {
        چاپ_کړه(" knee=%d/%d,%d/%d anchors=%u:",
               p->knee_ټکی_x.عدد, p->knee_ټکی_x.den,
               p->knee_ټکی_y.عدد, p->knee_ټکی_y.den,
               p->عدد_bezier_منحني_anchors);
        لكل (صحيح i = 0; i < p->عدد_bezier_منحني_anchors; i++)
            چاپ_کړه(" %d/%d", p->bezier_منحني_anchors[i].عدد,
                   p->bezier_منحني_anchors[i].den);
    }
    چاپ_کړه("\n    color_saturation_mapping_flag=%u",
           p->color_saturation_mapping_flag);
    إذا (p->color_saturation_mapping_flag)
        چاپ_کړه(" weight=%d/%d", p->color_saturation_وزن.عدد,
               p->color_saturation_وزن.den);
    چاپ_کړه("\n");
}

ساكن فراغ print_hdr_plus(ثابت حرف *label, ثابت AVDynamicHDRPlus *s)
{
    چاپ_کړه("%s:\n", label);
    چاپ_کړه("  application_version=%u num_windows=%u"
           " targeted_system_display_maximum_luminance=%d/%d\n",
           s->application_نسخه, s->عدد_windows,
           s->targeted_system_display_اعظمي_luminance.عدد,
           s->targeted_system_display_اعظمي_luminance.den);
    چاپ_کړه("  targeted_system_display_actual_peak_luminance_flag=%u\n",
           s->targeted_system_display_actual_peak_luminance_flag);
    إذا (s->targeted_system_display_actual_peak_luminance_flag)
        print_peak_ماتریکس("targeted_peak",
                          s->عدد_لیکې_targeted_system_display_actual_peak_luminance,
                          s->عدد_ستون_شمېر_targeted_system_display_actual_peak_luminance,
                          s->targeted_system_display_actual_peak_luminance);
    چاپ_کړه("  mastering_display_actual_peak_luminance_flag=%u\n",
           s->mastering_display_actual_peak_luminance_flag);
    إذا (s->mastering_display_actual_peak_luminance_flag)
        print_peak_ماتریکس("mastering_peak",
                          s->عدد_لیکې_mastering_display_actual_peak_luminance,
                          s->عدد_ستون_شمېر_mastering_display_actual_peak_luminance,
                          s->mastering_display_actual_peak_luminance);
    لكل (صحيح w = 0; w < s->عدد_windows; w++)
        print_کړکۍ(w, &s->params[w], w > 0);
}

ساكن فراغ print_app5(ثابت حرف *label, ثابت AVDynamicHDRSmpte2094App5 *s)
{
    چاپ_کړه("%s:\n", label);
    چاپ_کړه("  application_version=%u minimum_application_version=%u\n",
           s->application_نسخه, s->minimum_application_نسخه);
    چاپ_کړه("  has_custom_hdr_reference_white_flag=%u",
           s->has_custom_hdr_reference_white_flag);
    إذا (s->has_custom_hdr_reference_white_flag)
        چاپ_کړه(" hdr_reference_white=0x%04x", s->hdr_reference_white);
    چاپ_کړه("\n  has_adaptive_tone_map_flag=%u\n",
           s->has_adaptive_tone_map_flag);
    إذا (!s->has_adaptive_tone_map_flag)
        أرجع;

    چاپ_کړه("  baseline_hdr_headroom=0x%04x"
           " use_reference_white_tone_mapping_flag=%u\n",
           s->baseline_hdr_headroom, s->use_reference_white_tone_mapping_flag);
    إذا (s->use_reference_white_tone_mapping_flag)
        أرجع;

    چاپ_کړه("  num_alternate_images=%u chromaticities_flag=%u"
           " has_common_component_mix_params_flag=%u"
           " has_common_curve_params_flag=%u\n",
           s->عدد_alternate_images,
           s->gain_application_space_chromaticities_flag,
           s->has_common_component_mix_params_flag,
           s->has_common_منحني_params_flag);
    إذا (s->gain_application_space_chromaticities_flag == 3) {
        چاپ_کړه("  chromaticities:");
        لكل (صحيح r = 0; r < 8; r++)
            چاپ_کړه(" 0x%04x", s->gain_application_space_chromaticities[r]);
        چاپ_کړه("\n");
    }

    لكل (صحيح a = 0; a < s->عدد_alternate_images; a++) {
        صحيح n = s->gain_منحني_عدد_control_points_minus_1[a] + 1;
        چاپ_کړه("  alternate %d: hdr_headroom=0x%04x component_mixing_type=%u\n",
               a, s->alternate_hdr_headrooms[a], s->component_mixing_type[a]);
        إذا (s->component_mixing_type[a] == 3) {
            چاپ_کړه("    mixing flag:coefficient:");
            لكل (صحيح k = 0; k < 6; k++)
                چاپ_کړه(" %u:0x%04x",
                       s->has_component_mixing_coefficient_flag[a][k],
                       s->component_mixing_coefficient[a][k]);
            چاپ_کړه("\n");
        }
        چاپ_کړه("    curve: num_control_points=%d use_pchip_slope=%u\n", n,
               s->gain_منحني_use_pchip_میلان_flag[a]);
        چاپ_کړه("    x:");
        لكل (صحيح c = 0; c < n; c++)
            چاپ_کړه(" 0x%04x", s->gain_منحني_control_points_x[a][c]);
        چاپ_کړه("\n    y:");
        لكل (صحيح c = 0; c < n; c++)
            چاپ_کړه(" 0x%04x", s->gain_منحني_control_points_y[a][c]);
        چاپ_کړه("\n");
        /* theta is only serialized when the pchip slope is not used. */
        إذا (!s->gain_منحني_use_pchip_میلان_flag[a]) {
            چاپ_کړه("    theta:");
            لكل (صحيح c = 0; c < n; c++)
                چاپ_کړه(" 0x%04x", s->gain_منحني_control_points_theta[a][c]);
            چاپ_کړه("\n");
        }
    }
}

/*
 * Round-trip helpers: serialize, then parse back into a zeroed struct.
 */

ساكن صحيح hdr_plus_پړاو_trip(ثابت AVDynamicHDRPlus *دننه, AVDynamicHDRPlus *بهر)
{
    uint8_t *buf = عدم;
    size_t اندازه = 0;
    صحيح ret;

    ret = av_dynamic_hdr_plus_منزل_t35(دننه, &buf, &اندازه);
    إذا (ret < 0)
        أرجع ret;

    memset(بهر, 0, حجم(*بهر));
    ret = av_dynamic_hdr_plus_from_t35(بهر, buf, اندازه);
    av_free(buf);
    أرجع ret;
}

ساكن صحيح app5_پړاو_trip(ثابت AVDynamicHDRSmpte2094App5 *دننه,
                           AVDynamicHDRSmpte2094App5 *بهر)
{
    uint8_t *buf = عدم;
    size_t اندازه = 0;
    صحيح ret;

    ret = av_dynamic_hdr_smpte2094_app5_منزل_t35(دننه, &buf, &اندازه);
    إذا (ret < 0)
        أرجع ret;

    memset(بهر, 0, حجم(*بهر));
    ret = av_dynamic_hdr_smpte2094_app5_from_t35(بهر, buf, اندازه);
    av_free(buf);
    أرجع ret;
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
ساكن فراغ fill_hdr_plus_conforming(AVDynamicHDRPlus *s)
{
    ساكن ثابت uint8_t percentages[9] = { 1, 5, 10, 25, 50, 75, 90, 95, 99 };
    ساكن ثابت صحيح percentiles[9] = {
        1000, 0, 255, 25000, 50000, 75000, 90000, 95000, 99000,
    };

    memset(s, 0, حجم(*s));

    s->application_نسخه = 1;
    s->عدد_windows         = 1;
    s->targeted_system_display_اعظمي_luminance =
        (AVRational){ 400, LUMINANCE_DEN };
    s->targeted_system_display_actual_peak_luminance_flag = 0;
    s->mastering_display_actual_peak_luminance_flag       = 0;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 99000, RGB_DEN };
    s->params[0].اوسط_maxrgb = (AVRational){ 40000, RGB_DEN };

    s->params[0].عدد_distribution_maxrgb_percentiles = 9;
    لكل (صحيح i = 0; i < 9; i++) {
        s->params[0].distribution_maxrgb[i].percentage = percentages[i];
        s->params[0].distribution_maxrgb[i].percentile =
            (AVRational){ percentiles[i], RGB_DEN };
    }
    s->params[0].fraction_bright_pixels =
        (AVRational){ 250, FRACTION_PIXEL_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_ټکی_x = (AVRational){  512, KNEE_ټکی_DEN };
    s->params[0].knee_ټکی_y = (AVRational){ 1024, KNEE_ټکی_DEN };
    s->params[0].عدد_bezier_منحني_anchors = 9;
    لكل (صحيح i = 0; i < 9; i++)
        s->params[0].bezier_منحني_anchors[i] =
            (AVRational){ 100 * (i + 1), BEZIER_ANCHOR_DEN };

    s->params[0].color_saturation_mapping_flag = 0;
}

/* Deliberately NOT a conforming Version 1 payload: it combines a second
 * processing window, both actual-peak-luminance matrices and
 * ColorSaturationWeight, all of which §9.4 excludes for Version 1. It exists
 * only to drive the optional serializer/parser branches those fields guard. */
ساكن فراغ fill_hdr_plus_synthetic(AVDynamicHDRPlus *s)
{
    memset(s, 0, حجم(*s));

    s->application_نسخه = 1;
    s->عدد_windows         = 2;
    s->targeted_system_display_اعظمي_luminance =
        (AVRational){ 10000, LUMINANCE_DEN };

    s->params[1].کړکۍ_پاسنی_کیڼ_کونج_x  = (AVRational){ 100, 1 };
    s->params[1].کړکۍ_پاسنی_کیڼ_کونج_y  = (AVRational){ 120, 1 };
    s->params[1].کړکۍ_ښکتنی_ښی_کونج_x = (AVRational){ 500, 1 };
    s->params[1].کړکۍ_ښکتنی_ښی_کونج_y = (AVRational){ 520, 1 };
    s->params[1].center_د_ellipse_x             = 300;
    s->params[1].center_د_ellipse_y             = 320;
    s->params[1].rotation_angle                  = 45;
    s->params[1].semimajor_axis_دننی_ellipse = 50;
    s->params[1].semimajor_axis_external_ellipse = 100;
    s->params[1].semiminor_axis_external_ellipse = 80;
    s->params[1].overlap_process_option          = 1;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 70000, RGB_DEN };
    s->params[0].اوسط_maxrgb = (AVRational){ 40000, RGB_DEN };
    s->params[0].عدد_distribution_maxrgb_percentiles = 2;
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
    s->params[1].اوسط_maxrgb = (AVRational){ 25000, RGB_DEN };
    s->params[1].عدد_distribution_maxrgb_percentiles = 1;
    s->params[1].distribution_maxrgb[0].percentage = 25;
    s->params[1].distribution_maxrgb[0].percentile =
        (AVRational){ 12500, RGB_DEN };
    s->params[1].fraction_bright_pixels =
        (AVRational){ 100, FRACTION_PIXEL_DEN };

    s->targeted_system_display_actual_peak_luminance_flag = 1;
    s->عدد_لیکې_targeted_system_display_actual_peak_luminance = 2;
    s->عدد_ستون_شمېر_targeted_system_display_actual_peak_luminance = 3;
    لكل (صحيح i = 0; i < 2; i++)
        لكل (صحيح j = 0; j < 3; j++)
            s->targeted_system_display_actual_peak_luminance[i][j] =
                (AVRational){ i * 3 + j, PEAK_LUMINANCE_DEN };

    s->mastering_display_actual_peak_luminance_flag = 1;
    s->عدد_لیکې_mastering_display_actual_peak_luminance = 3;
    s->عدد_ستون_شمېر_mastering_display_actual_peak_luminance = 2;
    لكل (صحيح i = 0; i < 3; i++)
        لكل (صحيح j = 0; j < 2; j++)
            s->mastering_display_actual_peak_luminance[i][j] =
                (AVRational){ 15 - (i * 2 + j), PEAK_LUMINANCE_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_ټکی_x = (AVRational){ 500, KNEE_ټکی_DEN };
    s->params[0].knee_ټکی_y = (AVRational){ 800, KNEE_ټکی_DEN };
    s->params[0].عدد_bezier_منحني_anchors = 3;
    s->params[0].bezier_منحني_anchors[0] = (AVRational){ 100, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_منحني_anchors[1] = (AVRational){ 500, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_منحني_anchors[2] = (AVRational){ 900, BEZIER_ANCHOR_DEN };
    s->params[1].tone_mapping_flag = 0;

    لكل (صحيح w = 0; w < 2; w++) {
        s->params[w].color_saturation_mapping_flag = 1;
        s->params[w].color_saturation_وزن =
            (AVRational){ 8 + w, SATURATION_DEN };
    }
}

ساكن فراغ test_hdr_plus(فراغ)
{
    AVDynamicHDRPlus *hdr, *hdr_rt;
    AVFrame *چوکاټ;
    size_t اندازه = 0, required = 0;
    uint8_t *buf = عدم;
    صحيح ret;

    چاپ_کړه("=== AVDynamicHDRPlus ===\n");

    چاپ_کړه("Testing av_dynamic_hdr_plus_alloc()\n");
    hdr = av_dynamic_hdr_plus_alloc(&اندازه);
    چاپ_کړه("alloc: %s size>0=%s\n", hdr ? "OK" : "FAIL",
           اندازه > 0 ? "yes" : "no");
    av_freep(&hdr);

    hdr = av_dynamic_hdr_plus_alloc(عدم);
    چاپ_کړه("alloc (no size): %s\n", hdr ? "OK" : "FAIL");
    av_freep(&hdr);

    چاپ_کړه("\nTesting av_dynamic_hdr_plus_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        hdr = av_dynamic_hdr_plus_create_side_معلومات(چوکاټ);
        چاپ_کړه("create_side_data: %s\n", hdr ? "OK" : "FAIL");
        av_چوکاټ_free(&چوکاټ);
    }

    hdr    = av_dynamic_hdr_plus_alloc(عدم);
    hdr_rt = av_dynamic_hdr_plus_alloc(عدم);
    إذا (!hdr || !hdr_rt) {
        av_freep(&hdr);
        av_freep(&hdr_rt);
        أرجع;
    }
    fill_hdr_plus_conforming(hdr);

    /* Size-query mode: data=NULL, size receives the required byte count. */
    چاپ_کړه("\nTesting av_dynamic_hdr_plus_to_t35() size query\n");
    required = 0;
    ret = av_dynamic_hdr_plus_منزل_t35(hdr, عدم, &required);
    چاپ_کړه("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    /* Allocation mode: *data=NULL, the function allocates the buffer. */
    چاپ_کړه("\nTesting av_dynamic_hdr_plus_to_t35() allocation\n");
    buf  = عدم;
    اندازه = 0;
    ret = av_dynamic_hdr_plus_منزل_t35(hdr, &buf, &اندازه);
    چاپ_کړه("alloc mode: ret=%d size_match=%s\n", ret,
           اندازه == required ? "yes" : "no");
    av_freep(&buf);

    /* Existing-buffer mode: a caller-owned buffer is filled in place. */
    چاپ_کړه("\nTesting av_dynamic_hdr_plus_to_t35() existing buffer\n");
    buf = av_malloc(required);
    إذا (buf) {
        uint8_t *orig = buf;
        اندازه = required;
        ret = av_dynamic_hdr_plus_منزل_t35(hdr, &buf, &اندازه);
        چاپ_کړه("existing buf: ret=%d same_pointer=%s size_match=%s\n", ret,
               buf == orig ? "yes" : "no",
               اندازه == required ? "yes" : "no");
        av_freep(&buf);
    }

    /* Buffer-too-small: caller-owned buffer shorter than required. */
    چاپ_کړه("\nTesting av_dynamic_hdr_plus_to_t35() buffer too small\n");
    إذا (required > 1) {
        buf = av_malloc(required - 1);
        إذا (buf) {
            اندازه = required - 1;
            ret = av_dynamic_hdr_plus_منزل_t35(hdr, &buf, &اندازه);
            چاپ_کړه("too small: ret==AVERROR_BUFFER_TOO_SMALL=%s\n",
                   ret == AVERROR_بفر_TOO_SMALL ? "yes" : "no");
            av_freep(&buf);
        }
    }

    چاپ_کړه("\nTesting round trip, conforming ST 2094-40 Version 1 payload\n");
    ret = hdr_plus_پړاو_trip(hdr, hdr_rt);
    چاپ_کړه("round trip: ret=%d\n", ret);
    إذا (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    /* to_t35() ignores application_version and always writes the CTA-861-H
     * value, so the parsed field does not echo an out-of-range input. */
    چاپ_کړه("\nTesting that to_t35() overrides application_version\n");
    hdr->application_نسخه = 7;
    ret = hdr_plus_پړاو_trip(hdr, hdr_rt);
    چاپ_کړه("input=7 ret=%d decoded application_version=%u\n", ret,
           hdr_rt->application_نسخه);
    hdr->application_نسخه = 1;

    چاپ_کړه("\nTesting round trip, synthetic payload (branch coverage only)\n");
    fill_hdr_plus_synthetic(hdr);
    ret = hdr_plus_پړاو_trip(hdr, hdr_rt);
    چاپ_کړه("round trip: ret=%d\n", ret);
    إذا (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    چاپ_کړه("\nTesting error paths\n");
    buf  = عدم;
    اندازه = 0;
    ret = av_dynamic_hdr_plus_منزل_t35(عدم, &buf, &اندازه);
    چاپ_کړه("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_منزل_t35(hdr, عدم, عدم);
    چاپ_کړه("to_t35 no data no size: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_from_t35(عدم, (ثابت uint8_t *)"", 0);
    چاپ_کړه("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    {
        /* Oversized input is rejected before parsing. */
        size_t big = AV_HDR_PLUS_MAX_PAYLOAD_اندازه + 1;
        uint8_t *oversized = av_mallocz(big);
        إذا (oversized) {
            ret = av_dynamic_hdr_plus_from_t35(hdr_rt, oversized, big);
            چاپ_کړه("from_t35 oversized: ret==AVERROR(EINVAL)=%s\n",
                   ret == AVERROR(EINVAL) ? "yes" : "no");
            av_free(oversized);
        }
    }

    av_freep(&hdr);
    av_freep(&hdr_rt);

    چاپ_کړه("\nTesting OOM path\n");
    av_max_alloc(1);
    hdr = av_dynamic_hdr_plus_alloc(&اندازه);
    چاپ_کړه("alloc OOM: %s\n", hdr ? "FAIL" : "OK");
    av_max_alloc(لوی_عدد);
    av_freep(&hdr);
}

/* Table C.2 early-out: no adaptive tone map, custom reference white only. */
ساكن فراغ fill_app5_اصغري(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, حجم(*s));
    s->application_نسخه         = 1;
    s->minimum_application_نسخه = 0;
    s->has_custom_hdr_reference_white_flag = 1;
    s->hdr_reference_white         = 0x0203;
    s->has_adaptive_tone_map_flag  = 0;
}

/* Table C.3 early-out: reference-white tone mapping, no alternate images. */
ساكن فراغ fill_app5_reference_white(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, حجم(*s));
    s->application_نسخه        = 2;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->use_reference_white_tone_mapping_flag = 1;
}

/* Per-image parameters: explicit gain application space chromaticities,
 * component mixing type 3 with a mix of present and absent coefficients, and
 * explicit control point slopes (theta). */
ساكن فراغ fill_app5_فی_image(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, حجم(*s));
    s->application_نسخه        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->عدد_alternate_images       = 2;
    s->gain_application_space_chromaticities_flag = 3;
    لكل (صحيح r = 0; r < 8; r++)
        s->gain_application_space_chromaticities[r] = 100 * (r + 1);
    s->has_common_component_mix_params_flag = 0;
    s->has_common_منحني_params_flag         = 0;
    لكل (صحيح a = 0; a < 2; a++) {
        s->alternate_hdr_headrooms[a] = 0x0100 + a;
        s->component_mixing_type[a]   = 3;
        لكل (صحيح k = 0; k < 6; k++) {
            s->has_component_mixing_coefficient_flag[a][k] = k & 1;
            s->component_mixing_coefficient[a][k] = 0x1000 + 0x10 * a + k;
        }
        s->gain_منحني_عدد_control_points_minus_1[a] = 1;
        s->gain_منحني_use_pchip_میلان_flag[a]       = 0;
        لكل (صحيح c = 0; c < 2; c++) {
            s->gain_منحني_control_points_x[a][c]     = 0x2000 + 0x10 * a + c;
            s->gain_منحني_control_points_y[a][c]     = 0x3000 + 0x10 * a + c;
            s->gain_منحني_control_points_theta[a][c] = 0x4000 + 0x10 * a + c;
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
ساكن فراغ fill_app5_common(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, حجم(*s));
    s->application_نسخه        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0def;
    s->عدد_alternate_images       = 3;
    s->gain_application_space_chromaticities_flag = 0;
    s->has_common_component_mix_params_flag = 1;
    s->has_common_منحني_params_flag         = 1;
    لكل (صحيح a = 0; a < 3; a++) {
        s->alternate_hdr_headrooms[a] = 0x0200 + a;
        s->component_mixing_type[a]   = 1;
        s->gain_منحني_عدد_control_points_minus_1[a] = 2;
        s->gain_منحني_use_pchip_میلان_flag[a]       = 1;
        لكل (صحيح c = 0; c < 3; c++) {
            s->gain_منحني_control_points_x[a][c] = 0x5000 + c;
            s->gain_منحني_control_points_y[a][c] = 0x6000 + 0x10 * a + c;
        }
    }
}

ساكن فراغ test_app5(فراغ)
{
    AVDynamicHDRSmpte2094App5 *app5, *app5_rt;
    AVFrame *چوکاټ;
    size_t اندازه = 0, required = 0;
    uint8_t *buf = عدم;
    صحيح ret;

    چاپ_کړه("\n=== AVDynamicHDRSmpte2094App5 ===\n");
    چاپ_کړه("Testing av_dynamic_hdr_smpte2094_app5_alloc()\n");
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&اندازه);
    چاپ_کړه("alloc: %s size>0=%s\n", app5 ? "OK" : "FAIL",
           اندازه > 0 ? "yes" : "no");
    av_freep(&app5);

    چاپ_کړه("\nTesting av_dynamic_hdr_smpte2094_app5_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        app5 = av_dynamic_hdr_smpte2094_app5_create_side_معلومات(چوکاټ);
        چاپ_کړه("create_side_data: %s\n", app5 ? "OK" : "FAIL");
        av_چوکاټ_free(&چوکاټ);
    }

    app5    = av_dynamic_hdr_smpte2094_app5_alloc(عدم);
    app5_rt = av_dynamic_hdr_smpte2094_app5_alloc(عدم);
    إذا (!app5 || !app5_rt) {
        av_freep(&app5);
        av_freep(&app5_rt);
        أرجع;
    }
    fill_app5_اصغري(app5);

    چاپ_کړه("\nTesting av_dynamic_hdr_smpte2094_app5_to_t35()\n");
    required = 0;
    ret = av_dynamic_hdr_smpte2094_app5_منزل_t35(app5, عدم, &required);
    چاپ_کړه("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    buf  = عدم;
    اندازه = 0;
    ret = av_dynamic_hdr_smpte2094_app5_منزل_t35(app5, &buf, &اندازه);
    چاپ_کړه("alloc mode: ret=%d size_match=%s\n", ret,
           اندازه == required ? "yes" : "no");
    av_freep(&buf);

    چاپ_کړه("\nTesting round trip, no adaptive tone map\n");
    ret = app5_پړاو_trip(app5, app5_rt);
    چاپ_کړه("round trip: ret=%d\n", ret);
    إذا (ret >= 0)
        print_app5("decoded", app5_rt);

    چاپ_کړه("\nTesting round trip, reference-white tone mapping\n");
    fill_app5_reference_white(app5);
    ret = app5_پړاو_trip(app5, app5_rt);
    چاپ_کړه("round trip: ret=%d\n", ret);
    إذا (ret >= 0)
        print_app5("decoded", app5_rt);

    چاپ_کړه("\nTesting round trip, per-image mixing and curve parameters\n");
    fill_app5_فی_image(app5);
    ret = app5_پړاو_trip(app5, app5_rt);
    چاپ_کړه("round trip: ret=%d\n", ret);
    إذا (ret >= 0)
        print_app5("decoded", app5_rt);

    چاپ_کړه("\nTesting round trip, common mixing and curve parameters\n");
    fill_app5_common(app5);
    ret = app5_پړاو_trip(app5, app5_rt);
    چاپ_کړه("round trip: ret=%d\n", ret);
    إذا (ret >= 0)
        print_app5("decoded", app5_rt);

    چاپ_کړه("\nTesting error paths\n");
    buf  = عدم;
    اندازه = 0;
    ret = av_dynamic_hdr_smpte2094_app5_منزل_t35(عدم, &buf, &اندازه);
    چاپ_کړه("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_smpte2094_app5_from_t35(عدم, (ثابت uint8_t *)"", 0);
    چاپ_کړه("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    /* application_version does not fit the 3-bit field. */
    app5->application_نسخه = 8;
    ret = av_dynamic_hdr_smpte2094_app5_منزل_t35(app5, عدم, &اندازه);
    چاپ_کړه("to_t35 invalid application_version: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->application_نسخه = 1;

    /* minimum_application_version above the documented maximum. */
    app5->minimum_application_نسخه = 3;
    ret = av_dynamic_hdr_smpte2094_app5_منزل_t35(app5, عدم, &اندازه);
    چاپ_کړه("to_t35 invalid minimum_application_version:"
           " ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->minimum_application_نسخه = 0;

    /* More alternate images than the 3-bit count admits. */
    app5->عدد_alternate_images = 5;
    ret = av_dynamic_hdr_smpte2094_app5_منزل_t35(app5, عدم, &اندازه);
    چاپ_کړه("to_t35 too many alternate images: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");

    av_freep(&app5);
    av_freep(&app5_rt);

    چاپ_کړه("\nTesting OOM path\n");
    av_max_alloc(1);
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&اندازه);
    چاپ_کړه("alloc OOM: %s\n", app5 ? "FAIL" : "OK");
    av_max_alloc(لوی_عدد);
    av_freep(&app5);
}

صحيح اصلي(فراغ)
{
    test_hdr_plus();
    test_app5();
    أرجع 0;
}

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

#شامل <limits.h>
#شامل <stdio.h>
#شامل <string.h>

#شامل "libavutil/error.h"
#شامل "libavutil/frame.h"
#شامل "libavutil/hdr_dynamic_metadata.h"
#شامل "libavutil/mem.h"
#شامل "libavutil/rational.h"

/* Denominators av_dynamic_hdr_plus_to_t35() quantises to. The fixtures below
 * express every rational in these terms, so a correct round trip reproduces
 * the input exactly and the decoded values printed here can be compared
 * against the fixture directly. */
#تعریف_کرو LUMINANCE_DEN          1
#تعریف_کرو PEAK_LUMINANCE_DEN    15
#تعریف_کرو RGB_DEN           100000
#تعریف_کرو FRACTION_PIXEL_DEN  1000
#تعریف_کرو KNEE_نقطہ_DEN      4095
#تعریف_کرو BEZIER_ANCHOR_DEN   1023
#تعریف_کرو SATURATION_DEN         8

/*
 * Printers. Every field a fixture populates is printed, so that a serializer
 * or parser which drops or corrupts a value changes the FATE reference
 * instead of silently passing a flag-only check.
 */

ساکن خالی print_peak_میٹرکس(ثابت حرف *label, صحیح صفیں, صحیح ستون_تعداد,
                              ثابت AVRational m[25][25])
{
    لکھو("    %s %dx%d:", label, صفیں, ستون_تعداد);
    برائے (صحیح i = 0; i < صفیں; i++)
        برائے (صحیح j = 0; j < ستون_تعداد; j++)
            لکھو(" %d/%d", m[i][j].عدد, m[i][j].den);
    لکھو("\n");
}

ساکن خالی print_کھڑکی(صحیح w, ثابت AVHDRPlusColorTransformParams *p,
                         صحیح geometry)
{
    لکھو("  window %d:\n", w);
    /* Window 0 covers the whole frame; its geometry is not serialized. */
    اگر (geometry) {
        لکھو("    corners: ul=%d/%d,%d/%d lr=%d/%d,%d/%d\n",
               p->کھڑکی_بالائی_بایاں_کونا_x.عدد,
               p->کھڑکی_بالائی_بایاں_کونا_x.den,
               p->کھڑکی_بالائی_بایاں_کونا_y.عدد,
               p->کھڑکی_بالائی_بایاں_کونا_y.den,
               p->کھڑکی_زیریں_دایاں_کونا_x.عدد,
               p->کھڑکی_زیریں_دایاں_کونا_x.den,
               p->کھڑکی_زیریں_دایاں_کونا_y.عدد,
               p->کھڑکی_زیریں_دایاں_کونا_y.den);
        لکھو("    ellipse: center=%u,%u rotation=%u semimajor_int=%u"
               " semimajor_ext=%u semiminor_ext=%u overlap=%u\n",
               p->center_کا_ellipse_x, p->center_کا_ellipse_y,
               p->rotation_angle, p->semimajor_axis_اندرونی_ellipse,
               p->semimajor_axis_external_ellipse,
               p->semiminor_axis_external_ellipse,
               p->overlap_process_option);
    }
    لکھو("    maxscl: %d/%d %d/%d %d/%d average_maxrgb=%d/%d\n",
           p->maxscl[0].عدد, p->maxscl[0].den,
           p->maxscl[1].عدد, p->maxscl[1].den,
           p->maxscl[2].عدد, p->maxscl[2].den,
           p->اوسط_قدر_maxrgb.عدد, p->اوسط_قدر_maxrgb.den);
    لکھو("    distribution_maxrgb: n=%u",
           p->عدد_distribution_maxrgb_percentiles);
    برائے (صحیح i = 0; i < p->عدد_distribution_maxrgb_percentiles; i++)
        لکھو(" %u%%=%d/%d", p->distribution_maxrgb[i].percentage,
               p->distribution_maxrgb[i].percentile.عدد,
               p->distribution_maxrgb[i].percentile.den);
    لکھو("\n    fraction_bright_pixels=%d/%d\n",
           p->fraction_bright_pixels.عدد, p->fraction_bright_pixels.den);
    لکھو("    tone_mapping_flag=%u", p->tone_mapping_flag);
    اگر (p->tone_mapping_flag) {
        لکھو(" knee=%d/%d,%d/%d anchors=%u:",
               p->knee_نقطہ_x.عدد, p->knee_نقطہ_x.den,
               p->knee_نقطہ_y.عدد, p->knee_نقطہ_y.den,
               p->عدد_bezier_خم_anchors);
        برائے (صحیح i = 0; i < p->عدد_bezier_خم_anchors; i++)
            لکھو(" %d/%d", p->bezier_خم_anchors[i].عدد,
                   p->bezier_خم_anchors[i].den);
    }
    لکھو("\n    color_saturation_mapping_flag=%u",
           p->color_saturation_mapping_flag);
    اگر (p->color_saturation_mapping_flag)
        لکھو(" weight=%d/%d", p->color_saturation_وزن.عدد,
               p->color_saturation_وزن.den);
    لکھو("\n");
}

ساکن خالی print_hdr_plus(ثابت حرف *label, ثابت AVDynamicHDRPlus *s)
{
    لکھو("%s:\n", label);
    لکھو("  application_version=%u num_windows=%u"
           " targeted_system_display_maximum_luminance=%d/%d\n",
           s->application_نسخہ, s->عدد_windows,
           s->targeted_system_display_زیادہ_سے_زیادہ_luminance.عدد,
           s->targeted_system_display_زیادہ_سے_زیادہ_luminance.den);
    لکھو("  targeted_system_display_actual_peak_luminance_flag=%u\n",
           s->targeted_system_display_actual_peak_luminance_flag);
    اگر (s->targeted_system_display_actual_peak_luminance_flag)
        print_peak_میٹرکس("targeted_peak",
                          s->عدد_صفیں_targeted_system_display_actual_peak_luminance,
                          s->عدد_ستون_تعداد_targeted_system_display_actual_peak_luminance,
                          s->targeted_system_display_actual_peak_luminance);
    لکھو("  mastering_display_actual_peak_luminance_flag=%u\n",
           s->mastering_display_actual_peak_luminance_flag);
    اگر (s->mastering_display_actual_peak_luminance_flag)
        print_peak_میٹرکس("mastering_peak",
                          s->عدد_صفیں_mastering_display_actual_peak_luminance,
                          s->عدد_ستون_تعداد_mastering_display_actual_peak_luminance,
                          s->mastering_display_actual_peak_luminance);
    برائے (صحیح w = 0; w < s->عدد_windows; w++)
        print_کھڑکی(w, &s->params[w], w > 0);
}

ساکن خالی print_app5(ثابت حرف *label, ثابت AVDynamicHDRSmpte2094App5 *s)
{
    لکھو("%s:\n", label);
    لکھو("  application_version=%u minimum_application_version=%u\n",
           s->application_نسخہ, s->minimum_application_نسخہ);
    لکھو("  has_custom_hdr_reference_white_flag=%u",
           s->has_custom_hdr_reference_white_flag);
    اگر (s->has_custom_hdr_reference_white_flag)
        لکھو(" hdr_reference_white=0x%04x", s->hdr_reference_white);
    لکھو("\n  has_adaptive_tone_map_flag=%u\n",
           s->has_adaptive_tone_map_flag);
    اگر (!s->has_adaptive_tone_map_flag)
        واپس;

    لکھو("  baseline_hdr_headroom=0x%04x"
           " use_reference_white_tone_mapping_flag=%u\n",
           s->baseline_hdr_headroom, s->use_reference_white_tone_mapping_flag);
    اگر (s->use_reference_white_tone_mapping_flag)
        واپس;

    لکھو("  num_alternate_images=%u chromaticities_flag=%u"
           " has_common_component_mix_params_flag=%u"
           " has_common_curve_params_flag=%u\n",
           s->عدد_alternate_images,
           s->gain_application_space_chromaticities_flag,
           s->has_common_component_mix_params_flag,
           s->has_common_خم_params_flag);
    اگر (s->gain_application_space_chromaticities_flag == 3) {
        لکھو("  chromaticities:");
        برائے (صحیح r = 0; r < 8; r++)
            لکھو(" 0x%04x", s->gain_application_space_chromaticities[r]);
        لکھو("\n");
    }

    برائے (صحیح a = 0; a < s->عدد_alternate_images; a++) {
        صحیح n = s->gain_خم_عدد_control_points_minus_1[a] + 1;
        لکھو("  alternate %d: hdr_headroom=0x%04x component_mixing_type=%u\n",
               a, s->alternate_hdr_headrooms[a], s->component_mixing_type[a]);
        اگر (s->component_mixing_type[a] == 3) {
            لکھو("    mixing flag:coefficient:");
            برائے (صحیح k = 0; k < 6; k++)
                لکھو(" %u:0x%04x",
                       s->has_component_mixing_coefficient_flag[a][k],
                       s->component_mixing_coefficient[a][k]);
            لکھو("\n");
        }
        لکھو("    curve: num_control_points=%d use_pchip_slope=%u\n", n,
               s->gain_خم_use_pchip_ڈھلان_flag[a]);
        لکھو("    x:");
        برائے (صحیح c = 0; c < n; c++)
            لکھو(" 0x%04x", s->gain_خم_control_points_x[a][c]);
        لکھو("\n    y:");
        برائے (صحیح c = 0; c < n; c++)
            لکھو(" 0x%04x", s->gain_خم_control_points_y[a][c]);
        لکھو("\n");
        /* theta is only serialized when the pchip slope is not used. */
        اگر (!s->gain_خم_use_pchip_ڈھلان_flag[a]) {
            لکھو("    theta:");
            برائے (صحیح c = 0; c < n; c++)
                لکھو(" 0x%04x", s->gain_خم_control_points_theta[a][c]);
            لکھو("\n");
        }
    }
}

/*
 * Round-trip helpers: serialize, then parse back into a zeroed struct.
 */

ساکن صحیح hdr_plus_باری_trip(ثابت AVDynamicHDRPlus *اندر, AVDynamicHDRPlus *برآمد)
{
    uint8_t *buf = تہی;
    size_t سائز = 0;
    صحیح ret;

    ret = av_dynamic_hdr_plus_مقصد_t35(اندر, &buf, &سائز);
    اگر (ret < 0)
        واپس ret;

    memset(برآمد, 0, حجم(*برآمد));
    ret = av_dynamic_hdr_plus_from_t35(برآمد, buf, سائز);
    av_free(buf);
    واپس ret;
}

ساکن صحیح app5_باری_trip(ثابت AVDynamicHDRSmpte2094App5 *اندر,
                           AVDynamicHDRSmpte2094App5 *برآمد)
{
    uint8_t *buf = تہی;
    size_t سائز = 0;
    صحیح ret;

    ret = av_dynamic_hdr_smpte2094_app5_مقصد_t35(اندر, &buf, &سائز);
    اگر (ret < 0)
        واپس ret;

    memset(برآمد, 0, حجم(*برآمد));
    ret = av_dynamic_hdr_smpte2094_app5_from_t35(برآمد, buf, سائز);
    av_free(buf);
    واپس ret;
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
ساکن خالی fill_hdr_plus_conforming(AVDynamicHDRPlus *s)
{
    ساکن ثابت uint8_t percentages[9] = { 1, 5, 10, 25, 50, 75, 90, 95, 99 };
    ساکن ثابت صحیح percentiles[9] = {
        1000, 0, 255, 25000, 50000, 75000, 90000, 95000, 99000,
    };

    memset(s, 0, حجم(*s));

    s->application_نسخہ = 1;
    s->عدد_windows         = 1;
    s->targeted_system_display_زیادہ_سے_زیادہ_luminance =
        (AVRational){ 400, LUMINANCE_DEN };
    s->targeted_system_display_actual_peak_luminance_flag = 0;
    s->mastering_display_actual_peak_luminance_flag       = 0;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 99000, RGB_DEN };
    s->params[0].اوسط_قدر_maxrgb = (AVRational){ 40000, RGB_DEN };

    s->params[0].عدد_distribution_maxrgb_percentiles = 9;
    برائے (صحیح i = 0; i < 9; i++) {
        s->params[0].distribution_maxrgb[i].percentage = percentages[i];
        s->params[0].distribution_maxrgb[i].percentile =
            (AVRational){ percentiles[i], RGB_DEN };
    }
    s->params[0].fraction_bright_pixels =
        (AVRational){ 250, FRACTION_PIXEL_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_نقطہ_x = (AVRational){  512, KNEE_نقطہ_DEN };
    s->params[0].knee_نقطہ_y = (AVRational){ 1024, KNEE_نقطہ_DEN };
    s->params[0].عدد_bezier_خم_anchors = 9;
    برائے (صحیح i = 0; i < 9; i++)
        s->params[0].bezier_خم_anchors[i] =
            (AVRational){ 100 * (i + 1), BEZIER_ANCHOR_DEN };

    s->params[0].color_saturation_mapping_flag = 0;
}

/* Deliberately NOT a conforming Version 1 payload: it combines a second
 * processing window, both actual-peak-luminance matrices and
 * ColorSaturationWeight, all of which §9.4 excludes for Version 1. It exists
 * only to drive the optional serializer/parser branches those fields guard. */
ساکن خالی fill_hdr_plus_synthetic(AVDynamicHDRPlus *s)
{
    memset(s, 0, حجم(*s));

    s->application_نسخہ = 1;
    s->عدد_windows         = 2;
    s->targeted_system_display_زیادہ_سے_زیادہ_luminance =
        (AVRational){ 10000, LUMINANCE_DEN };

    s->params[1].کھڑکی_بالائی_بایاں_کونا_x  = (AVRational){ 100, 1 };
    s->params[1].کھڑکی_بالائی_بایاں_کونا_y  = (AVRational){ 120, 1 };
    s->params[1].کھڑکی_زیریں_دایاں_کونا_x = (AVRational){ 500, 1 };
    s->params[1].کھڑکی_زیریں_دایاں_کونا_y = (AVRational){ 520, 1 };
    s->params[1].center_کا_ellipse_x             = 300;
    s->params[1].center_کا_ellipse_y             = 320;
    s->params[1].rotation_angle                  = 45;
    s->params[1].semimajor_axis_اندرونی_ellipse = 50;
    s->params[1].semimajor_axis_external_ellipse = 100;
    s->params[1].semiminor_axis_external_ellipse = 80;
    s->params[1].overlap_process_option          = 1;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 70000, RGB_DEN };
    s->params[0].اوسط_قدر_maxrgb = (AVRational){ 40000, RGB_DEN };
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
    s->params[1].اوسط_قدر_maxrgb = (AVRational){ 25000, RGB_DEN };
    s->params[1].عدد_distribution_maxrgb_percentiles = 1;
    s->params[1].distribution_maxrgb[0].percentage = 25;
    s->params[1].distribution_maxrgb[0].percentile =
        (AVRational){ 12500, RGB_DEN };
    s->params[1].fraction_bright_pixels =
        (AVRational){ 100, FRACTION_PIXEL_DEN };

    s->targeted_system_display_actual_peak_luminance_flag = 1;
    s->عدد_صفیں_targeted_system_display_actual_peak_luminance = 2;
    s->عدد_ستون_تعداد_targeted_system_display_actual_peak_luminance = 3;
    برائے (صحیح i = 0; i < 2; i++)
        برائے (صحیح j = 0; j < 3; j++)
            s->targeted_system_display_actual_peak_luminance[i][j] =
                (AVRational){ i * 3 + j, PEAK_LUMINANCE_DEN };

    s->mastering_display_actual_peak_luminance_flag = 1;
    s->عدد_صفیں_mastering_display_actual_peak_luminance = 3;
    s->عدد_ستون_تعداد_mastering_display_actual_peak_luminance = 2;
    برائے (صحیح i = 0; i < 3; i++)
        برائے (صحیح j = 0; j < 2; j++)
            s->mastering_display_actual_peak_luminance[i][j] =
                (AVRational){ 15 - (i * 2 + j), PEAK_LUMINANCE_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_نقطہ_x = (AVRational){ 500, KNEE_نقطہ_DEN };
    s->params[0].knee_نقطہ_y = (AVRational){ 800, KNEE_نقطہ_DEN };
    s->params[0].عدد_bezier_خم_anchors = 3;
    s->params[0].bezier_خم_anchors[0] = (AVRational){ 100, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_خم_anchors[1] = (AVRational){ 500, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_خم_anchors[2] = (AVRational){ 900, BEZIER_ANCHOR_DEN };
    s->params[1].tone_mapping_flag = 0;

    برائے (صحیح w = 0; w < 2; w++) {
        s->params[w].color_saturation_mapping_flag = 1;
        s->params[w].color_saturation_وزن =
            (AVRational){ 8 + w, SATURATION_DEN };
    }
}

ساکن خالی test_hdr_plus(خالی)
{
    AVDynamicHDRPlus *hdr, *hdr_rt;
    AVFrame *چوکھٹا;
    size_t سائز = 0, required = 0;
    uint8_t *buf = تہی;
    صحیح ret;

    لکھو("=== AVDynamicHDRPlus ===\n");

    لکھو("Testing av_dynamic_hdr_plus_alloc()\n");
    hdr = av_dynamic_hdr_plus_alloc(&سائز);
    لکھو("alloc: %s size>0=%s\n", hdr ? "OK" : "FAIL",
           سائز > 0 ? "yes" : "no");
    av_freep(&hdr);

    hdr = av_dynamic_hdr_plus_alloc(تہی);
    لکھو("alloc (no size): %s\n", hdr ? "OK" : "FAIL");
    av_freep(&hdr);

    لکھو("\nTesting av_dynamic_hdr_plus_create_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    اگر (چوکھٹا) {
        hdr = av_dynamic_hdr_plus_create_side_ڈیٹا(چوکھٹا);
        لکھو("create_side_data: %s\n", hdr ? "OK" : "FAIL");
        av_چوکھٹا_free(&چوکھٹا);
    }

    hdr    = av_dynamic_hdr_plus_alloc(تہی);
    hdr_rt = av_dynamic_hdr_plus_alloc(تہی);
    اگر (!hdr || !hdr_rt) {
        av_freep(&hdr);
        av_freep(&hdr_rt);
        واپس;
    }
    fill_hdr_plus_conforming(hdr);

    /* Size-query mode: data=NULL, size receives the required byte count. */
    لکھو("\nTesting av_dynamic_hdr_plus_to_t35() size query\n");
    required = 0;
    ret = av_dynamic_hdr_plus_مقصد_t35(hdr, تہی, &required);
    لکھو("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    /* Allocation mode: *data=NULL, the function allocates the buffer. */
    لکھو("\nTesting av_dynamic_hdr_plus_to_t35() allocation\n");
    buf  = تہی;
    سائز = 0;
    ret = av_dynamic_hdr_plus_مقصد_t35(hdr, &buf, &سائز);
    لکھو("alloc mode: ret=%d size_match=%s\n", ret,
           سائز == required ? "yes" : "no");
    av_freep(&buf);

    /* Existing-buffer mode: a caller-owned buffer is filled in place. */
    لکھو("\nTesting av_dynamic_hdr_plus_to_t35() existing buffer\n");
    buf = av_malloc(required);
    اگر (buf) {
        uint8_t *orig = buf;
        سائز = required;
        ret = av_dynamic_hdr_plus_مقصد_t35(hdr, &buf, &سائز);
        لکھو("existing buf: ret=%d same_pointer=%s size_match=%s\n", ret,
               buf == orig ? "yes" : "no",
               سائز == required ? "yes" : "no");
        av_freep(&buf);
    }

    /* Buffer-too-small: caller-owned buffer shorter than required. */
    لکھو("\nTesting av_dynamic_hdr_plus_to_t35() buffer too small\n");
    اگر (required > 1) {
        buf = av_malloc(required - 1);
        اگر (buf) {
            سائز = required - 1;
            ret = av_dynamic_hdr_plus_مقصد_t35(hdr, &buf, &سائز);
            لکھو("too small: ret==AVERROR_BUFFER_TOO_SMALL=%s\n",
                   ret == AVERROR_بفر_TOO_SMALL ? "yes" : "no");
            av_freep(&buf);
        }
    }

    لکھو("\nTesting round trip, conforming ST 2094-40 Version 1 payload\n");
    ret = hdr_plus_باری_trip(hdr, hdr_rt);
    لکھو("round trip: ret=%d\n", ret);
    اگر (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    /* to_t35() ignores application_version and always writes the CTA-861-H
     * value, so the parsed field does not echo an out-of-range input. */
    لکھو("\nTesting that to_t35() overrides application_version\n");
    hdr->application_نسخہ = 7;
    ret = hdr_plus_باری_trip(hdr, hdr_rt);
    لکھو("input=7 ret=%d decoded application_version=%u\n", ret,
           hdr_rt->application_نسخہ);
    hdr->application_نسخہ = 1;

    لکھو("\nTesting round trip, synthetic payload (branch coverage only)\n");
    fill_hdr_plus_synthetic(hdr);
    ret = hdr_plus_باری_trip(hdr, hdr_rt);
    لکھو("round trip: ret=%d\n", ret);
    اگر (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    لکھو("\nTesting error paths\n");
    buf  = تہی;
    سائز = 0;
    ret = av_dynamic_hdr_plus_مقصد_t35(تہی, &buf, &سائز);
    لکھو("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_مقصد_t35(hdr, تہی, تہی);
    لکھو("to_t35 no data no size: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_from_t35(تہی, (ثابت uint8_t *)"", 0);
    لکھو("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    {
        /* Oversized input is rejected before parsing. */
        size_t big = AV_HDR_PLUS_MAX_PAYLOAD_سائز + 1;
        uint8_t *oversized = av_mallocz(big);
        اگر (oversized) {
            ret = av_dynamic_hdr_plus_from_t35(hdr_rt, oversized, big);
            لکھو("from_t35 oversized: ret==AVERROR(EINVAL)=%s\n",
                   ret == AVERROR(EINVAL) ? "yes" : "no");
            av_free(oversized);
        }
    }

    av_freep(&hdr);
    av_freep(&hdr_rt);

    لکھو("\nTesting OOM path\n");
    av_max_alloc(1);
    hdr = av_dynamic_hdr_plus_alloc(&سائز);
    لکھو("alloc OOM: %s\n", hdr ? "FAIL" : "OK");
    av_max_alloc(زیادہ_سے_زیادہ_عدد);
    av_freep(&hdr);
}

/* Table C.2 early-out: no adaptive tone map, custom reference white only. */
ساکن خالی fill_app5_اقل(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, حجم(*s));
    s->application_نسخہ         = 1;
    s->minimum_application_نسخہ = 0;
    s->has_custom_hdr_reference_white_flag = 1;
    s->hdr_reference_white         = 0x0203;
    s->has_adaptive_tone_map_flag  = 0;
}

/* Table C.3 early-out: reference-white tone mapping, no alternate images. */
ساکن خالی fill_app5_reference_white(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, حجم(*s));
    s->application_نسخہ        = 2;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->use_reference_white_tone_mapping_flag = 1;
}

/* Per-image parameters: explicit gain application space chromaticities,
 * component mixing type 3 with a mix of present and absent coefficients, and
 * explicit control point slopes (theta). */
ساکن خالی fill_app5_فی_image(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, حجم(*s));
    s->application_نسخہ        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->عدد_alternate_images       = 2;
    s->gain_application_space_chromaticities_flag = 3;
    برائے (صحیح r = 0; r < 8; r++)
        s->gain_application_space_chromaticities[r] = 100 * (r + 1);
    s->has_common_component_mix_params_flag = 0;
    s->has_common_خم_params_flag         = 0;
    برائے (صحیح a = 0; a < 2; a++) {
        s->alternate_hdr_headrooms[a] = 0x0100 + a;
        s->component_mixing_type[a]   = 3;
        برائے (صحیح k = 0; k < 6; k++) {
            s->has_component_mixing_coefficient_flag[a][k] = k & 1;
            s->component_mixing_coefficient[a][k] = 0x1000 + 0x10 * a + k;
        }
        s->gain_خم_عدد_control_points_minus_1[a] = 1;
        s->gain_خم_use_pchip_ڈھلان_flag[a]       = 0;
        برائے (صحیح c = 0; c < 2; c++) {
            s->gain_خم_control_points_x[a][c]     = 0x2000 + 0x10 * a + c;
            s->gain_خم_control_points_y[a][c]     = 0x3000 + 0x10 * a + c;
            s->gain_خم_control_points_theta[a][c] = 0x4000 + 0x10 * a + c;
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
ساکن خالی fill_app5_common(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, حجم(*s));
    s->application_نسخہ        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0def;
    s->عدد_alternate_images       = 3;
    s->gain_application_space_chromaticities_flag = 0;
    s->has_common_component_mix_params_flag = 1;
    s->has_common_خم_params_flag         = 1;
    برائے (صحیح a = 0; a < 3; a++) {
        s->alternate_hdr_headrooms[a] = 0x0200 + a;
        s->component_mixing_type[a]   = 1;
        s->gain_خم_عدد_control_points_minus_1[a] = 2;
        s->gain_خم_use_pchip_ڈھلان_flag[a]       = 1;
        برائے (صحیح c = 0; c < 3; c++) {
            s->gain_خم_control_points_x[a][c] = 0x5000 + c;
            s->gain_خم_control_points_y[a][c] = 0x6000 + 0x10 * a + c;
        }
    }
}

ساکن خالی test_app5(خالی)
{
    AVDynamicHDRSmpte2094App5 *app5, *app5_rt;
    AVFrame *چوکھٹا;
    size_t سائز = 0, required = 0;
    uint8_t *buf = تہی;
    صحیح ret;

    لکھو("\n=== AVDynamicHDRSmpte2094App5 ===\n");
    لکھو("Testing av_dynamic_hdr_smpte2094_app5_alloc()\n");
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&سائز);
    لکھو("alloc: %s size>0=%s\n", app5 ? "OK" : "FAIL",
           سائز > 0 ? "yes" : "no");
    av_freep(&app5);

    لکھو("\nTesting av_dynamic_hdr_smpte2094_app5_create_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    اگر (چوکھٹا) {
        app5 = av_dynamic_hdr_smpte2094_app5_create_side_ڈیٹا(چوکھٹا);
        لکھو("create_side_data: %s\n", app5 ? "OK" : "FAIL");
        av_چوکھٹا_free(&چوکھٹا);
    }

    app5    = av_dynamic_hdr_smpte2094_app5_alloc(تہی);
    app5_rt = av_dynamic_hdr_smpte2094_app5_alloc(تہی);
    اگر (!app5 || !app5_rt) {
        av_freep(&app5);
        av_freep(&app5_rt);
        واپس;
    }
    fill_app5_اقل(app5);

    لکھو("\nTesting av_dynamic_hdr_smpte2094_app5_to_t35()\n");
    required = 0;
    ret = av_dynamic_hdr_smpte2094_app5_مقصد_t35(app5, تہی, &required);
    لکھو("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    buf  = تہی;
    سائز = 0;
    ret = av_dynamic_hdr_smpte2094_app5_مقصد_t35(app5, &buf, &سائز);
    لکھو("alloc mode: ret=%d size_match=%s\n", ret,
           سائز == required ? "yes" : "no");
    av_freep(&buf);

    لکھو("\nTesting round trip, no adaptive tone map\n");
    ret = app5_باری_trip(app5, app5_rt);
    لکھو("round trip: ret=%d\n", ret);
    اگر (ret >= 0)
        print_app5("decoded", app5_rt);

    لکھو("\nTesting round trip, reference-white tone mapping\n");
    fill_app5_reference_white(app5);
    ret = app5_باری_trip(app5, app5_rt);
    لکھو("round trip: ret=%d\n", ret);
    اگر (ret >= 0)
        print_app5("decoded", app5_rt);

    لکھو("\nTesting round trip, per-image mixing and curve parameters\n");
    fill_app5_فی_image(app5);
    ret = app5_باری_trip(app5, app5_rt);
    لکھو("round trip: ret=%d\n", ret);
    اگر (ret >= 0)
        print_app5("decoded", app5_rt);

    لکھو("\nTesting round trip, common mixing and curve parameters\n");
    fill_app5_common(app5);
    ret = app5_باری_trip(app5, app5_rt);
    لکھو("round trip: ret=%d\n", ret);
    اگر (ret >= 0)
        print_app5("decoded", app5_rt);

    لکھو("\nTesting error paths\n");
    buf  = تہی;
    سائز = 0;
    ret = av_dynamic_hdr_smpte2094_app5_مقصد_t35(تہی, &buf, &سائز);
    لکھو("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_smpte2094_app5_from_t35(تہی, (ثابت uint8_t *)"", 0);
    لکھو("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    /* application_version does not fit the 3-bit field. */
    app5->application_نسخہ = 8;
    ret = av_dynamic_hdr_smpte2094_app5_مقصد_t35(app5, تہی, &سائز);
    لکھو("to_t35 invalid application_version: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->application_نسخہ = 1;

    /* minimum_application_version above the documented maximum. */
    app5->minimum_application_نسخہ = 3;
    ret = av_dynamic_hdr_smpte2094_app5_مقصد_t35(app5, تہی, &سائز);
    لکھو("to_t35 invalid minimum_application_version:"
           " ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->minimum_application_نسخہ = 0;

    /* More alternate images than the 3-bit count admits. */
    app5->عدد_alternate_images = 5;
    ret = av_dynamic_hdr_smpte2094_app5_مقصد_t35(app5, تہی, &سائز);
    لکھو("to_t35 too many alternate images: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");

    av_freep(&app5);
    av_freep(&app5_rt);

    لکھو("\nTesting OOM path\n");
    av_max_alloc(1);
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&سائز);
    لکھو("alloc OOM: %s\n", app5 ? "FAIL" : "OK");
    av_max_alloc(زیادہ_سے_زیادہ_عدد);
    av_freep(&app5);
}

صحیح مین(خالی)
{
    test_hdr_plus();
    test_app5();
    واپس 0;
}

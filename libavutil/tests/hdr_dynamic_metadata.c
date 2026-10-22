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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/error.h"
#అన్తర్భావ "libavutil/frame.h"
#అన్తర్భావ "libavutil/hdr_dynamic_metadata.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/rational.h"

/* Denominators av_dynamic_hdr_plus_to_t35() quantises to. The fixtures below
 * express every rational in these terms, so a correct round trip reproduces
 * the input exactly and the decoded values printed here can be compared
 * against the fixture directly. */
#నిర్వచించు LUMINANCE_DEN          1
#నిర్వచించు PEAK_LUMINANCE_DEN    15
#నిర్వచించు RGB_DEN           100000
#నిర్వచించు FRACTION_PIXEL_DEN  1000
#నిర్వచించు KNEE_బిందువు_DEN      4095
#నిర్వచించు BEZIER_ANCHOR_DEN   1023
#నిర్వచించు SATURATION_DEN         8

/*
 * Printers. Every field a fixture populates is printed, so that a serializer
 * or parser which drops or corrupts a value changes the FATE reference
 * instead of silently passing a flag-only check.
 */

స్థిర శూన్య print_peak_మాతృక(స్థిరరాశి అక్షరం *label, పూర్ణాంకం అడ్డువరుసలు, పూర్ణాంకం నిలువుల_సంఖ్య,
                              స్థిరరాశి AVRational m[25][25])
{
    రాయి("    %s %dx%d:", label, అడ్డువరుసలు, నిలువుల_సంఖ్య);
    కొరకు (పూర్ణాంకం i = 0; i < అడ్డువరుసలు; i++)
        కొరకు (పూర్ణాంకం j = 0; j < నిలువుల_సంఖ్య; j++)
            రాయి(" %d/%d", m[i][j].అంకె, m[i][j].den);
    రాయి("\n");
}

స్థిర శూన్య print_కిటికీ(పూర్ణాంకం w, స్థిరరాశి AVHDRPlusColorTransformParams *p,
                         పూర్ణాంకం geometry)
{
    రాయి("  window %d:\n", w);
    /* Window 0 covers the whole frame; its geometry is not serialized. */
    ఒకవేళ (geometry) {
        రాయి("    corners: ul=%d/%d,%d/%d lr=%d/%d,%d/%d\n",
               p->కిటికీ_పై_ఎడమ_మూల_x.అంకె,
               p->కిటికీ_పై_ఎడమ_మూల_x.den,
               p->కిటికీ_పై_ఎడమ_మూల_y.అంకె,
               p->కిటికీ_పై_ఎడమ_మూల_y.den,
               p->కిటికీ_క్రింది_కుడి_మూల_x.అంకె,
               p->కిటికీ_క్రింది_కుడి_మూల_x.den,
               p->కిటికీ_క్రింది_కుడి_మూల_y.అంకె,
               p->కిటికీ_క్రింది_కుడి_మూల_y.den);
        రాయి("    ellipse: center=%u,%u rotation=%u semimajor_int=%u"
               " semimajor_ext=%u semiminor_ext=%u overlap=%u\n",
               p->center_యొక్క_ellipse_x, p->center_యొక్క_ellipse_y,
               p->rotation_angle, p->semimajor_axis_అంతర్గత_ellipse,
               p->semimajor_axis_external_ellipse,
               p->semiminor_axis_external_ellipse,
               p->overlap_process_option);
    }
    రాయి("    maxscl: %d/%d %d/%d %d/%d average_maxrgb=%d/%d\n",
           p->maxscl[0].అంకె, p->maxscl[0].den,
           p->maxscl[1].అంకె, p->maxscl[1].den,
           p->maxscl[2].అంకె, p->maxscl[2].den,
           p->సరాసరి_maxrgb.అంకె, p->సరాసరి_maxrgb.den);
    రాయి("    distribution_maxrgb: n=%u",
           p->అంకె_distribution_maxrgb_percentiles);
    కొరకు (పూర్ణాంకం i = 0; i < p->అంకె_distribution_maxrgb_percentiles; i++)
        రాయి(" %u%%=%d/%d", p->distribution_maxrgb[i].percentage,
               p->distribution_maxrgb[i].percentile.అంకె,
               p->distribution_maxrgb[i].percentile.den);
    రాయి("\n    fraction_bright_pixels=%d/%d\n",
           p->fraction_bright_pixels.అంకె, p->fraction_bright_pixels.den);
    రాయి("    tone_mapping_flag=%u", p->tone_mapping_flag);
    ఒకవేళ (p->tone_mapping_flag) {
        రాయి(" knee=%d/%d,%d/%d anchors=%u:",
               p->knee_బిందువు_x.అంకె, p->knee_బిందువు_x.den,
               p->knee_బిందువు_y.అంకె, p->knee_బిందువు_y.den,
               p->అంకె_bezier_వక్రం_anchors);
        కొరకు (పూర్ణాంకం i = 0; i < p->అంకె_bezier_వక్రం_anchors; i++)
            రాయి(" %d/%d", p->bezier_వక్రం_anchors[i].అంకె,
                   p->bezier_వక్రం_anchors[i].den);
    }
    రాయి("\n    color_saturation_mapping_flag=%u",
           p->color_saturation_mapping_flag);
    ఒకవేళ (p->color_saturation_mapping_flag)
        రాయి(" weight=%d/%d", p->color_saturation_బరువు.అంకె,
               p->color_saturation_బరువు.den);
    రాయి("\n");
}

స్థిర శూన్య print_hdr_plus(స్థిరరాశి అక్షరం *label, స్థిరరాశి AVDynamicHDRPlus *s)
{
    రాయి("%s:\n", label);
    రాయి("  application_version=%u num_windows=%u"
           " targeted_system_display_maximum_luminance=%d/%d\n",
           s->application_సంస్కరణ, s->అంకె_windows,
           s->targeted_system_display_గరిష్ఠ_luminance.అంకె,
           s->targeted_system_display_గరిష్ఠ_luminance.den);
    రాయి("  targeted_system_display_actual_peak_luminance_flag=%u\n",
           s->targeted_system_display_actual_peak_luminance_flag);
    ఒకవేళ (s->targeted_system_display_actual_peak_luminance_flag)
        print_peak_మాతృక("targeted_peak",
                          s->అంకె_అడ్డువరుసలు_targeted_system_display_actual_peak_luminance,
                          s->అంకె_నిలువుల_సంఖ్య_targeted_system_display_actual_peak_luminance,
                          s->targeted_system_display_actual_peak_luminance);
    రాయి("  mastering_display_actual_peak_luminance_flag=%u\n",
           s->mastering_display_actual_peak_luminance_flag);
    ఒకవేళ (s->mastering_display_actual_peak_luminance_flag)
        print_peak_మాతృక("mastering_peak",
                          s->అంకె_అడ్డువరుసలు_mastering_display_actual_peak_luminance,
                          s->అంకె_నిలువుల_సంఖ్య_mastering_display_actual_peak_luminance,
                          s->mastering_display_actual_peak_luminance);
    కొరకు (పూర్ణాంకం w = 0; w < s->అంకె_windows; w++)
        print_కిటికీ(w, &s->params[w], w > 0);
}

స్థిర శూన్య print_app5(స్థిరరాశి అక్షరం *label, స్థిరరాశి AVDynamicHDRSmpte2094App5 *s)
{
    రాయి("%s:\n", label);
    రాయి("  application_version=%u minimum_application_version=%u\n",
           s->application_సంస్కరణ, s->minimum_application_సంస్కరణ);
    రాయి("  has_custom_hdr_reference_white_flag=%u",
           s->has_custom_hdr_reference_white_flag);
    ఒకవేళ (s->has_custom_hdr_reference_white_flag)
        రాయి(" hdr_reference_white=0x%04x", s->hdr_reference_white);
    రాయి("\n  has_adaptive_tone_map_flag=%u\n",
           s->has_adaptive_tone_map_flag);
    ఒకవేళ (!s->has_adaptive_tone_map_flag)
        తిరిగి;

    రాయి("  baseline_hdr_headroom=0x%04x"
           " use_reference_white_tone_mapping_flag=%u\n",
           s->baseline_hdr_headroom, s->use_reference_white_tone_mapping_flag);
    ఒకవేళ (s->use_reference_white_tone_mapping_flag)
        తిరిగి;

    రాయి("  num_alternate_images=%u chromaticities_flag=%u"
           " has_common_component_mix_params_flag=%u"
           " has_common_curve_params_flag=%u\n",
           s->అంకె_alternate_images,
           s->gain_application_space_chromaticities_flag,
           s->has_common_component_mix_params_flag,
           s->has_common_వక్రం_params_flag);
    ఒకవేళ (s->gain_application_space_chromaticities_flag == 3) {
        రాయి("  chromaticities:");
        కొరకు (పూర్ణాంకం r = 0; r < 8; r++)
            రాయి(" 0x%04x", s->gain_application_space_chromaticities[r]);
        రాయి("\n");
    }

    కొరకు (పూర్ణాంకం a = 0; a < s->అంకె_alternate_images; a++) {
        పూర్ణాంకం n = s->gain_వక్రం_అంకె_control_points_minus_1[a] + 1;
        రాయి("  alternate %d: hdr_headroom=0x%04x component_mixing_type=%u\n",
               a, s->alternate_hdr_headrooms[a], s->component_mixing_type[a]);
        ఒకవేళ (s->component_mixing_type[a] == 3) {
            రాయి("    mixing flag:coefficient:");
            కొరకు (పూర్ణాంకం k = 0; k < 6; k++)
                రాయి(" %u:0x%04x",
                       s->has_component_mixing_coefficient_flag[a][k],
                       s->component_mixing_coefficient[a][k]);
            రాయి("\n");
        }
        రాయి("    curve: num_control_points=%d use_pchip_slope=%u\n", n,
               s->gain_వక్రం_use_pchip_వాలు_flag[a]);
        రాయి("    x:");
        కొరకు (పూర్ణాంకం c = 0; c < n; c++)
            రాయి(" 0x%04x", s->gain_వక్రం_control_points_x[a][c]);
        రాయి("\n    y:");
        కొరకు (పూర్ణాంకం c = 0; c < n; c++)
            రాయి(" 0x%04x", s->gain_వక్రం_control_points_y[a][c]);
        రాయి("\n");
        /* theta is only serialized when the pchip slope is not used. */
        ఒకవేళ (!s->gain_వక్రం_use_pchip_వాలు_flag[a]) {
            రాయి("    theta:");
            కొరకు (పూర్ణాంకం c = 0; c < n; c++)
                రాయి(" 0x%04x", s->gain_వక్రం_control_points_theta[a][c]);
            రాయి("\n");
        }
    }
}

/*
 * Round-trip helpers: serialize, then parse back into a zeroed struct.
 */

స్థిర పూర్ణాంకం hdr_plus_విడత_trip(స్థిరరాశి AVDynamicHDRPlus *లోపల, AVDynamicHDRPlus *బహిర్గతం)
{
    uint8_t *buf = ఖాళీ;
    size_t కొలత = 0;
    పూర్ణాంకం ret;

    ret = av_dynamic_hdr_plus_గమ్యం_t35(లోపల, &buf, &కొలత);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    memset(బహిర్గతం, 0, పరిమాణం(*బహిర్గతం));
    ret = av_dynamic_hdr_plus_from_t35(బహిర్గతం, buf, కొలత);
    av_free(buf);
    తిరిగి ret;
}

స్థిర పూర్ణాంకం app5_విడత_trip(స్థిరరాశి AVDynamicHDRSmpte2094App5 *లోపల,
                           AVDynamicHDRSmpte2094App5 *బహిర్గతం)
{
    uint8_t *buf = ఖాళీ;
    size_t కొలత = 0;
    పూర్ణాంకం ret;

    ret = av_dynamic_hdr_smpte2094_app5_గమ్యం_t35(లోపల, &buf, &కొలత);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    memset(బహిర్గతం, 0, పరిమాణం(*బహిర్గతం));
    ret = av_dynamic_hdr_smpte2094_app5_from_t35(బహిర్గతం, buf, కొలత);
    av_free(buf);
    తిరిగి ret;
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
స్థిర శూన్య fill_hdr_plus_conforming(AVDynamicHDRPlus *s)
{
    స్థిర స్థిరరాశి uint8_t percentages[9] = { 1, 5, 10, 25, 50, 75, 90, 95, 99 };
    స్థిర స్థిరరాశి పూర్ణాంకం percentiles[9] = {
        1000, 0, 255, 25000, 50000, 75000, 90000, 95000, 99000,
    };

    memset(s, 0, పరిమాణం(*s));

    s->application_సంస్కరణ = 1;
    s->అంకె_windows         = 1;
    s->targeted_system_display_గరిష్ఠ_luminance =
        (AVRational){ 400, LUMINANCE_DEN };
    s->targeted_system_display_actual_peak_luminance_flag = 0;
    s->mastering_display_actual_peak_luminance_flag       = 0;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 99000, RGB_DEN };
    s->params[0].సరాసరి_maxrgb = (AVRational){ 40000, RGB_DEN };

    s->params[0].అంకె_distribution_maxrgb_percentiles = 9;
    కొరకు (పూర్ణాంకం i = 0; i < 9; i++) {
        s->params[0].distribution_maxrgb[i].percentage = percentages[i];
        s->params[0].distribution_maxrgb[i].percentile =
            (AVRational){ percentiles[i], RGB_DEN };
    }
    s->params[0].fraction_bright_pixels =
        (AVRational){ 250, FRACTION_PIXEL_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_బిందువు_x = (AVRational){  512, KNEE_బిందువు_DEN };
    s->params[0].knee_బిందువు_y = (AVRational){ 1024, KNEE_బిందువు_DEN };
    s->params[0].అంకె_bezier_వక్రం_anchors = 9;
    కొరకు (పూర్ణాంకం i = 0; i < 9; i++)
        s->params[0].bezier_వక్రం_anchors[i] =
            (AVRational){ 100 * (i + 1), BEZIER_ANCHOR_DEN };

    s->params[0].color_saturation_mapping_flag = 0;
}

/* Deliberately NOT a conforming Version 1 payload: it combines a second
 * processing window, both actual-peak-luminance matrices and
 * ColorSaturationWeight, all of which §9.4 excludes for Version 1. It exists
 * only to drive the optional serializer/parser branches those fields guard. */
స్థిర శూన్య fill_hdr_plus_synthetic(AVDynamicHDRPlus *s)
{
    memset(s, 0, పరిమాణం(*s));

    s->application_సంస్కరణ = 1;
    s->అంకె_windows         = 2;
    s->targeted_system_display_గరిష్ఠ_luminance =
        (AVRational){ 10000, LUMINANCE_DEN };

    s->params[1].కిటికీ_పై_ఎడమ_మూల_x  = (AVRational){ 100, 1 };
    s->params[1].కిటికీ_పై_ఎడమ_మూల_y  = (AVRational){ 120, 1 };
    s->params[1].కిటికీ_క్రింది_కుడి_మూల_x = (AVRational){ 500, 1 };
    s->params[1].కిటికీ_క్రింది_కుడి_మూల_y = (AVRational){ 520, 1 };
    s->params[1].center_యొక్క_ellipse_x             = 300;
    s->params[1].center_యొక్క_ellipse_y             = 320;
    s->params[1].rotation_angle                  = 45;
    s->params[1].semimajor_axis_అంతర్గత_ellipse = 50;
    s->params[1].semimajor_axis_external_ellipse = 100;
    s->params[1].semiminor_axis_external_ellipse = 80;
    s->params[1].overlap_process_option          = 1;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 70000, RGB_DEN };
    s->params[0].సరాసరి_maxrgb = (AVRational){ 40000, RGB_DEN };
    s->params[0].అంకె_distribution_maxrgb_percentiles = 2;
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
    s->params[1].సరాసరి_maxrgb = (AVRational){ 25000, RGB_DEN };
    s->params[1].అంకె_distribution_maxrgb_percentiles = 1;
    s->params[1].distribution_maxrgb[0].percentage = 25;
    s->params[1].distribution_maxrgb[0].percentile =
        (AVRational){ 12500, RGB_DEN };
    s->params[1].fraction_bright_pixels =
        (AVRational){ 100, FRACTION_PIXEL_DEN };

    s->targeted_system_display_actual_peak_luminance_flag = 1;
    s->అంకె_అడ్డువరుసలు_targeted_system_display_actual_peak_luminance = 2;
    s->అంకె_నిలువుల_సంఖ్య_targeted_system_display_actual_peak_luminance = 3;
    కొరకు (పూర్ణాంకం i = 0; i < 2; i++)
        కొరకు (పూర్ణాంకం j = 0; j < 3; j++)
            s->targeted_system_display_actual_peak_luminance[i][j] =
                (AVRational){ i * 3 + j, PEAK_LUMINANCE_DEN };

    s->mastering_display_actual_peak_luminance_flag = 1;
    s->అంకె_అడ్డువరుసలు_mastering_display_actual_peak_luminance = 3;
    s->అంకె_నిలువుల_సంఖ్య_mastering_display_actual_peak_luminance = 2;
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        కొరకు (పూర్ణాంకం j = 0; j < 2; j++)
            s->mastering_display_actual_peak_luminance[i][j] =
                (AVRational){ 15 - (i * 2 + j), PEAK_LUMINANCE_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_బిందువు_x = (AVRational){ 500, KNEE_బిందువు_DEN };
    s->params[0].knee_బిందువు_y = (AVRational){ 800, KNEE_బిందువు_DEN };
    s->params[0].అంకె_bezier_వక్రం_anchors = 3;
    s->params[0].bezier_వక్రం_anchors[0] = (AVRational){ 100, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_వక్రం_anchors[1] = (AVRational){ 500, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_వక్రం_anchors[2] = (AVRational){ 900, BEZIER_ANCHOR_DEN };
    s->params[1].tone_mapping_flag = 0;

    కొరకు (పూర్ణాంకం w = 0; w < 2; w++) {
        s->params[w].color_saturation_mapping_flag = 1;
        s->params[w].color_saturation_బరువు =
            (AVRational){ 8 + w, SATURATION_DEN };
    }
}

స్థిర శూన్య test_hdr_plus(శూన్య)
{
    AVDynamicHDRPlus *hdr, *hdr_rt;
    AVFrame *చట్రం;
    size_t కొలత = 0, required = 0;
    uint8_t *buf = ఖాళీ;
    పూర్ణాంకం ret;

    రాయి("=== AVDynamicHDRPlus ===\n");

    రాయి("Testing av_dynamic_hdr_plus_alloc()\n");
    hdr = av_dynamic_hdr_plus_alloc(&కొలత);
    రాయి("alloc: %s size>0=%s\n", hdr ? "OK" : "FAIL",
           కొలత > 0 ? "yes" : "no");
    av_freep(&hdr);

    hdr = av_dynamic_hdr_plus_alloc(ఖాళీ);
    రాయి("alloc (no size): %s\n", hdr ? "OK" : "FAIL");
    av_freep(&hdr);

    రాయి("\nTesting av_dynamic_hdr_plus_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        hdr = av_dynamic_hdr_plus_create_side_దత్తాంశం(చట్రం);
        రాయి("create_side_data: %s\n", hdr ? "OK" : "FAIL");
        av_చట్రం_free(&చట్రం);
    }

    hdr    = av_dynamic_hdr_plus_alloc(ఖాళీ);
    hdr_rt = av_dynamic_hdr_plus_alloc(ఖాళీ);
    ఒకవేళ (!hdr || !hdr_rt) {
        av_freep(&hdr);
        av_freep(&hdr_rt);
        తిరిగి;
    }
    fill_hdr_plus_conforming(hdr);

    /* Size-query mode: data=NULL, size receives the required byte count. */
    రాయి("\nTesting av_dynamic_hdr_plus_to_t35() size query\n");
    required = 0;
    ret = av_dynamic_hdr_plus_గమ్యం_t35(hdr, ఖాళీ, &required);
    రాయి("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    /* Allocation mode: *data=NULL, the function allocates the buffer. */
    రాయి("\nTesting av_dynamic_hdr_plus_to_t35() allocation\n");
    buf  = ఖాళీ;
    కొలత = 0;
    ret = av_dynamic_hdr_plus_గమ్యం_t35(hdr, &buf, &కొలత);
    రాయి("alloc mode: ret=%d size_match=%s\n", ret,
           కొలత == required ? "yes" : "no");
    av_freep(&buf);

    /* Existing-buffer mode: a caller-owned buffer is filled in place. */
    రాయి("\nTesting av_dynamic_hdr_plus_to_t35() existing buffer\n");
    buf = av_malloc(required);
    ఒకవేళ (buf) {
        uint8_t *orig = buf;
        కొలత = required;
        ret = av_dynamic_hdr_plus_గమ్యం_t35(hdr, &buf, &కొలత);
        రాయి("existing buf: ret=%d same_pointer=%s size_match=%s\n", ret,
               buf == orig ? "yes" : "no",
               కొలత == required ? "yes" : "no");
        av_freep(&buf);
    }

    /* Buffer-too-small: caller-owned buffer shorter than required. */
    రాయి("\nTesting av_dynamic_hdr_plus_to_t35() buffer too small\n");
    ఒకవేళ (required > 1) {
        buf = av_malloc(required - 1);
        ఒకవేళ (buf) {
            కొలత = required - 1;
            ret = av_dynamic_hdr_plus_గమ్యం_t35(hdr, &buf, &కొలత);
            రాయి("too small: ret==AVERROR_BUFFER_TOO_SMALL=%s\n",
                   ret == AVERROR_బఫరు_TOO_SMALL ? "yes" : "no");
            av_freep(&buf);
        }
    }

    రాయి("\nTesting round trip, conforming ST 2094-40 Version 1 payload\n");
    ret = hdr_plus_విడత_trip(hdr, hdr_rt);
    రాయి("round trip: ret=%d\n", ret);
    ఒకవేళ (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    /* to_t35() ignores application_version and always writes the CTA-861-H
     * value, so the parsed field does not echo an out-of-range input. */
    రాయి("\nTesting that to_t35() overrides application_version\n");
    hdr->application_సంస్కరణ = 7;
    ret = hdr_plus_విడత_trip(hdr, hdr_rt);
    రాయి("input=7 ret=%d decoded application_version=%u\n", ret,
           hdr_rt->application_సంస్కరణ);
    hdr->application_సంస్కరణ = 1;

    రాయి("\nTesting round trip, synthetic payload (branch coverage only)\n");
    fill_hdr_plus_synthetic(hdr);
    ret = hdr_plus_విడత_trip(hdr, hdr_rt);
    రాయి("round trip: ret=%d\n", ret);
    ఒకవేళ (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    రాయి("\nTesting error paths\n");
    buf  = ఖాళీ;
    కొలత = 0;
    ret = av_dynamic_hdr_plus_గమ్యం_t35(ఖాళీ, &buf, &కొలత);
    రాయి("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_గమ్యం_t35(hdr, ఖాళీ, ఖాళీ);
    రాయి("to_t35 no data no size: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_from_t35(ఖాళీ, (స్థిరరాశి uint8_t *)"", 0);
    రాయి("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    {
        /* Oversized input is rejected before parsing. */
        size_t big = AV_HDR_PLUS_MAX_PAYLOAD_కొలత + 1;
        uint8_t *oversized = av_mallocz(big);
        ఒకవేళ (oversized) {
            ret = av_dynamic_hdr_plus_from_t35(hdr_rt, oversized, big);
            రాయి("from_t35 oversized: ret==AVERROR(EINVAL)=%s\n",
                   ret == AVERROR(EINVAL) ? "yes" : "no");
            av_free(oversized);
        }
    }

    av_freep(&hdr);
    av_freep(&hdr_rt);

    రాయి("\nTesting OOM path\n");
    av_max_alloc(1);
    hdr = av_dynamic_hdr_plus_alloc(&కొలత);
    రాయి("alloc OOM: %s\n", hdr ? "FAIL" : "OK");
    av_max_alloc(గరిష్ఠ_పూర్ణాంకం);
    av_freep(&hdr);
}

/* Table C.2 early-out: no adaptive tone map, custom reference white only. */
స్థిర శూన్య fill_app5_కనీస(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, పరిమాణం(*s));
    s->application_సంస్కరణ         = 1;
    s->minimum_application_సంస్కరణ = 0;
    s->has_custom_hdr_reference_white_flag = 1;
    s->hdr_reference_white         = 0x0203;
    s->has_adaptive_tone_map_flag  = 0;
}

/* Table C.3 early-out: reference-white tone mapping, no alternate images. */
స్థిర శూన్య fill_app5_reference_white(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, పరిమాణం(*s));
    s->application_సంస్కరణ        = 2;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->use_reference_white_tone_mapping_flag = 1;
}

/* Per-image parameters: explicit gain application space chromaticities,
 * component mixing type 3 with a mix of present and absent coefficients, and
 * explicit control point slopes (theta). */
స్థిర శూన్య fill_app5_చొప్పున_image(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, పరిమాణం(*s));
    s->application_సంస్కరణ        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->అంకె_alternate_images       = 2;
    s->gain_application_space_chromaticities_flag = 3;
    కొరకు (పూర్ణాంకం r = 0; r < 8; r++)
        s->gain_application_space_chromaticities[r] = 100 * (r + 1);
    s->has_common_component_mix_params_flag = 0;
    s->has_common_వక్రం_params_flag         = 0;
    కొరకు (పూర్ణాంకం a = 0; a < 2; a++) {
        s->alternate_hdr_headrooms[a] = 0x0100 + a;
        s->component_mixing_type[a]   = 3;
        కొరకు (పూర్ణాంకం k = 0; k < 6; k++) {
            s->has_component_mixing_coefficient_flag[a][k] = k & 1;
            s->component_mixing_coefficient[a][k] = 0x1000 + 0x10 * a + k;
        }
        s->gain_వక్రం_అంకె_control_points_minus_1[a] = 1;
        s->gain_వక్రం_use_pchip_వాలు_flag[a]       = 0;
        కొరకు (పూర్ణాంకం c = 0; c < 2; c++) {
            s->gain_వక్రం_control_points_x[a][c]     = 0x2000 + 0x10 * a + c;
            s->gain_వక్రం_control_points_y[a][c]     = 0x3000 + 0x10 * a + c;
            s->gain_వక్రం_control_points_theta[a][c] = 0x4000 + 0x10 * a + c;
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
స్థిర శూన్య fill_app5_common(AVDynamicHDRSmpte2094App5 *s)
{
    memset(s, 0, పరిమాణం(*s));
    s->application_సంస్కరణ        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0def;
    s->అంకె_alternate_images       = 3;
    s->gain_application_space_chromaticities_flag = 0;
    s->has_common_component_mix_params_flag = 1;
    s->has_common_వక్రం_params_flag         = 1;
    కొరకు (పూర్ణాంకం a = 0; a < 3; a++) {
        s->alternate_hdr_headrooms[a] = 0x0200 + a;
        s->component_mixing_type[a]   = 1;
        s->gain_వక్రం_అంకె_control_points_minus_1[a] = 2;
        s->gain_వక్రం_use_pchip_వాలు_flag[a]       = 1;
        కొరకు (పూర్ణాంకం c = 0; c < 3; c++) {
            s->gain_వక్రం_control_points_x[a][c] = 0x5000 + c;
            s->gain_వక్రం_control_points_y[a][c] = 0x6000 + 0x10 * a + c;
        }
    }
}

స్థిర శూన్య test_app5(శూన్య)
{
    AVDynamicHDRSmpte2094App5 *app5, *app5_rt;
    AVFrame *చట్రం;
    size_t కొలత = 0, required = 0;
    uint8_t *buf = ఖాళీ;
    పూర్ణాంకం ret;

    రాయి("\n=== AVDynamicHDRSmpte2094App5 ===\n");
    రాయి("Testing av_dynamic_hdr_smpte2094_app5_alloc()\n");
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&కొలత);
    రాయి("alloc: %s size>0=%s\n", app5 ? "OK" : "FAIL",
           కొలత > 0 ? "yes" : "no");
    av_freep(&app5);

    రాయి("\nTesting av_dynamic_hdr_smpte2094_app5_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        app5 = av_dynamic_hdr_smpte2094_app5_create_side_దత్తాంశం(చట్రం);
        రాయి("create_side_data: %s\n", app5 ? "OK" : "FAIL");
        av_చట్రం_free(&చట్రం);
    }

    app5    = av_dynamic_hdr_smpte2094_app5_alloc(ఖాళీ);
    app5_rt = av_dynamic_hdr_smpte2094_app5_alloc(ఖాళీ);
    ఒకవేళ (!app5 || !app5_rt) {
        av_freep(&app5);
        av_freep(&app5_rt);
        తిరిగి;
    }
    fill_app5_కనీస(app5);

    రాయి("\nTesting av_dynamic_hdr_smpte2094_app5_to_t35()\n");
    required = 0;
    ret = av_dynamic_hdr_smpte2094_app5_గమ్యం_t35(app5, ఖాళీ, &required);
    రాయి("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    buf  = ఖాళీ;
    కొలత = 0;
    ret = av_dynamic_hdr_smpte2094_app5_గమ్యం_t35(app5, &buf, &కొలత);
    రాయి("alloc mode: ret=%d size_match=%s\n", ret,
           కొలత == required ? "yes" : "no");
    av_freep(&buf);

    రాయి("\nTesting round trip, no adaptive tone map\n");
    ret = app5_విడత_trip(app5, app5_rt);
    రాయి("round trip: ret=%d\n", ret);
    ఒకవేళ (ret >= 0)
        print_app5("decoded", app5_rt);

    రాయి("\nTesting round trip, reference-white tone mapping\n");
    fill_app5_reference_white(app5);
    ret = app5_విడత_trip(app5, app5_rt);
    రాయి("round trip: ret=%d\n", ret);
    ఒకవేళ (ret >= 0)
        print_app5("decoded", app5_rt);

    రాయి("\nTesting round trip, per-image mixing and curve parameters\n");
    fill_app5_చొప్పున_image(app5);
    ret = app5_విడత_trip(app5, app5_rt);
    రాయి("round trip: ret=%d\n", ret);
    ఒకవేళ (ret >= 0)
        print_app5("decoded", app5_rt);

    రాయి("\nTesting round trip, common mixing and curve parameters\n");
    fill_app5_common(app5);
    ret = app5_విడత_trip(app5, app5_rt);
    రాయి("round trip: ret=%d\n", ret);
    ఒకవేళ (ret >= 0)
        print_app5("decoded", app5_rt);

    రాయి("\nTesting error paths\n");
    buf  = ఖాళీ;
    కొలత = 0;
    ret = av_dynamic_hdr_smpte2094_app5_గమ్యం_t35(ఖాళీ, &buf, &కొలత);
    రాయి("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_smpte2094_app5_from_t35(ఖాళీ, (స్థిరరాశి uint8_t *)"", 0);
    రాయి("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    /* application_version does not fit the 3-bit field. */
    app5->application_సంస్కరణ = 8;
    ret = av_dynamic_hdr_smpte2094_app5_గమ్యం_t35(app5, ఖాళీ, &కొలత);
    రాయి("to_t35 invalid application_version: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->application_సంస్కరణ = 1;

    /* minimum_application_version above the documented maximum. */
    app5->minimum_application_సంస్కరణ = 3;
    ret = av_dynamic_hdr_smpte2094_app5_గమ్యం_t35(app5, ఖాళీ, &కొలత);
    రాయి("to_t35 invalid minimum_application_version:"
           " ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->minimum_application_సంస్కరణ = 0;

    /* More alternate images than the 3-bit count admits. */
    app5->అంకె_alternate_images = 5;
    ret = av_dynamic_hdr_smpte2094_app5_గమ్యం_t35(app5, ఖాళీ, &కొలత);
    రాయి("to_t35 too many alternate images: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");

    av_freep(&app5);
    av_freep(&app5_rt);

    రాయి("\nTesting OOM path\n");
    av_max_alloc(1);
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&కొలత);
    రాయి("alloc OOM: %s\n", app5 ? "FAIL" : "OK");
    av_max_alloc(గరిష్ఠ_పూర్ణాంకం);
    av_freep(&app5);
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    test_hdr_plus();
    test_app5();
    తిరిగి 0;
}

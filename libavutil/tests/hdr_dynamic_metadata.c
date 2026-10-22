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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/error.h"
#अन्तर्भाव "libavutil/frame.h"
#अन्तर्भाव "libavutil/hdr_dynamic_metadata.h"
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/rational.h"

/* Denominators av_dynamic_hdr_plus_to_t35() quantises to. The fixtures below
 * express every rational in these terms, so a correct round trip reproduces
 * the input exactly and the decoded values printed here can be compared
 * against the fixture directly. */
#define LUMINANCE_DEN          1
#define PEAK_LUMINANCE_DEN    15
#define RGB_DEN           100000
#define FRACTION_PIXEL_DEN  1000
#define KNEE_POINT_DEN      4095
#define BEZIER_ANCHOR_DEN   1023
#define SATURATION_DEN         8

/*
 * Printers. Every field a fixture populates is printed, so that a serializer
 * or parser which drops or corrupts a value changes the FATE reference
 * instead of silently passing a flag-only check.
 */

स्थिर शून्य print_peak_matrix(ध्रुव वर्ण *label, पूर्णाङ्क rows, पूर्णाङ्क cols,
                              ध्रुव AVRational m[25][25])
{
    म_लिखो("    %s %dx%d:", label, rows, cols);
    प्रति (पूर्णाङ्क i = 0; i < rows; i++)
        प्रति (पूर्णाङ्क j = 0; j < cols; j++)
            म_लिखो(" %d/%d", m[i][j].अंक, m[i][j].den);
    म_लिखो("\n");
}

स्थिर शून्य print_window(पूर्णाङ्क w, ध्रुव AVHDRPlusColorTransformParams *p,
                         पूर्णाङ्क geometry)
{
    म_लिखो("  window %d:\n", w);
    /* Window 0 covers the whole frame; its geometry is not serialized. */
    यदि (geometry) {
        म_लिखो("    corners: ul=%d/%d,%d/%d lr=%d/%d,%d/%d\n",
               p->window_upper_बायाँ_corner_x.अंक,
               p->window_upper_बायाँ_corner_x.den,
               p->window_upper_बायाँ_corner_y.अंक,
               p->window_upper_बायाँ_corner_y.den,
               p->window_lower_दायाँ_corner_x.अंक,
               p->window_lower_दायाँ_corner_x.den,
               p->window_lower_दायाँ_corner_y.अंक,
               p->window_lower_दायाँ_corner_y.den);
        म_लिखो("    ellipse: center=%u,%u rotation=%u semimajor_int=%u"
               " semimajor_ext=%u semiminor_ext=%u overlap=%u\n",
               p->center_of_ellipse_x, p->center_of_ellipse_y,
               p->rotation_angle, p->semimajor_axis_internal_ellipse,
               p->semimajor_axis_external_ellipse,
               p->semiminor_axis_external_ellipse,
               p->overlap_process_option);
    }
    म_लिखो("    maxscl: %d/%d %d/%d %d/%d average_maxrgb=%d/%d\n",
           p->maxscl[0].अंक, p->maxscl[0].den,
           p->maxscl[1].अंक, p->maxscl[1].den,
           p->maxscl[2].अंक, p->maxscl[2].den,
           p->average_maxrgb.अंक, p->average_maxrgb.den);
    म_लिखो("    distribution_maxrgb: n=%u",
           p->अंक_distribution_maxrgb_percentiles);
    प्रति (पूर्णाङ्क i = 0; i < p->अंक_distribution_maxrgb_percentiles; i++)
        म_लिखो(" %u%%=%d/%d", p->distribution_maxrgb[i].percentage,
               p->distribution_maxrgb[i].percentile.अंक,
               p->distribution_maxrgb[i].percentile.den);
    म_लिखो("\n    fraction_bright_pixels=%d/%d\n",
           p->fraction_bright_pixels.अंक, p->fraction_bright_pixels.den);
    म_लिखो("    tone_mapping_flag=%u", p->tone_mapping_flag);
    यदि (p->tone_mapping_flag) {
        म_लिखो(" knee=%d/%d,%d/%d anchors=%u:",
               p->knee_point_x.अंक, p->knee_point_x.den,
               p->knee_point_y.अंक, p->knee_point_y.den,
               p->अंक_bezier_curve_anchors);
        प्रति (पूर्णाङ्क i = 0; i < p->अंक_bezier_curve_anchors; i++)
            म_लिखो(" %d/%d", p->bezier_curve_anchors[i].अंक,
                   p->bezier_curve_anchors[i].den);
    }
    म_लिखो("\n    color_saturation_mapping_flag=%u",
           p->color_saturation_mapping_flag);
    यदि (p->color_saturation_mapping_flag)
        म_लिखो(" weight=%d/%d", p->color_saturation_weight.अंक,
               p->color_saturation_weight.den);
    म_लिखो("\n");
}

स्थिर शून्य print_hdr_plus(ध्रुव वर्ण *label, ध्रुव AVDynamicHDRPlus *s)
{
    म_लिखो("%s:\n", label);
    म_लिखो("  application_version=%u num_windows=%u"
           " targeted_system_display_maximum_luminance=%d/%d\n",
           s->application_version, s->अंक_windows,
           s->targeted_system_display_maximum_luminance.अंक,
           s->targeted_system_display_maximum_luminance.den);
    म_लिखो("  targeted_system_display_actual_peak_luminance_flag=%u\n",
           s->targeted_system_display_actual_peak_luminance_flag);
    यदि (s->targeted_system_display_actual_peak_luminance_flag)
        print_peak_matrix("targeted_peak",
                          s->अंक_rows_targeted_system_display_actual_peak_luminance,
                          s->अंक_cols_targeted_system_display_actual_peak_luminance,
                          s->targeted_system_display_actual_peak_luminance);
    म_लिखो("  mastering_display_actual_peak_luminance_flag=%u\n",
           s->mastering_display_actual_peak_luminance_flag);
    यदि (s->mastering_display_actual_peak_luminance_flag)
        print_peak_matrix("mastering_peak",
                          s->अंक_rows_mastering_display_actual_peak_luminance,
                          s->अंक_cols_mastering_display_actual_peak_luminance,
                          s->mastering_display_actual_peak_luminance);
    प्रति (पूर्णाङ्क w = 0; w < s->अंक_windows; w++)
        print_window(w, &s->params[w], w > 0);
}

स्थिर शून्य print_app5(ध्रुव वर्ण *label, ध्रुव AVDynamicHDRSmpte2094App5 *s)
{
    म_लिखो("%s:\n", label);
    म_लिखो("  application_version=%u minimum_application_version=%u\n",
           s->application_version, s->minimum_application_version);
    म_लिखो("  has_custom_hdr_reference_white_flag=%u",
           s->has_custom_hdr_reference_white_flag);
    यदि (s->has_custom_hdr_reference_white_flag)
        म_लिखो(" hdr_reference_white=0x%04x", s->hdr_reference_white);
    म_लिखो("\n  has_adaptive_tone_map_flag=%u\n",
           s->has_adaptive_tone_map_flag);
    यदि (!s->has_adaptive_tone_map_flag)
        प्रत्यागम;

    म_लिखो("  baseline_hdr_headroom=0x%04x"
           " use_reference_white_tone_mapping_flag=%u\n",
           s->baseline_hdr_headroom, s->use_reference_white_tone_mapping_flag);
    यदि (s->use_reference_white_tone_mapping_flag)
        प्रत्यागम;

    म_लिखो("  num_alternate_images=%u chromaticities_flag=%u"
           " has_common_component_mix_params_flag=%u"
           " has_common_curve_params_flag=%u\n",
           s->अंक_alternate_images,
           s->gain_application_space_chromaticities_flag,
           s->has_common_component_mix_params_flag,
           s->has_common_curve_params_flag);
    यदि (s->gain_application_space_chromaticities_flag == 3) {
        म_लिखो("  chromaticities:");
        प्रति (पूर्णाङ्क r = 0; r < 8; r++)
            म_लिखो(" 0x%04x", s->gain_application_space_chromaticities[r]);
        म_लिखो("\n");
    }

    प्रति (पूर्णाङ्क a = 0; a < s->अंक_alternate_images; a++) {
        पूर्णाङ्क n = s->gain_curve_अंक_control_points_minus_1[a] + 1;
        म_लिखो("  alternate %d: hdr_headroom=0x%04x component_mixing_type=%u\n",
               a, s->alternate_hdr_headrooms[a], s->component_mixing_type[a]);
        यदि (s->component_mixing_type[a] == 3) {
            म_लिखो("    mixing flag:coefficient:");
            प्रति (पूर्णाङ्क k = 0; k < 6; k++)
                म_लिखो(" %u:0x%04x",
                       s->has_component_mixing_coefficient_flag[a][k],
                       s->component_mixing_coefficient[a][k]);
            म_लिखो("\n");
        }
        म_लिखो("    curve: num_control_points=%d use_pchip_slope=%u\n", n,
               s->gain_curve_use_pchip_slope_flag[a]);
        म_लिखो("    x:");
        प्रति (पूर्णाङ्क c = 0; c < n; c++)
            म_लिखो(" 0x%04x", s->gain_curve_control_points_x[a][c]);
        म_लिखो("\n    y:");
        प्रति (पूर्णाङ्क c = 0; c < n; c++)
            म_लिखो(" 0x%04x", s->gain_curve_control_points_y[a][c]);
        म_लिखो("\n");
        /* theta is only serialized when the pchip slope is not used. */
        यदि (!s->gain_curve_use_pchip_slope_flag[a]) {
            म_लिखो("    theta:");
            प्रति (पूर्णाङ्क c = 0; c < n; c++)
                म_लिखो(" 0x%04x", s->gain_curve_control_points_theta[a][c]);
            म_लिखो("\n");
        }
    }
}

/*
 * Round-trip helpers: serialize, then parse back into a zeroed struct.
 */

स्थिर पूर्णाङ्क hdr_plus_round_trip(ध्रुव AVDynamicHDRPlus *in, AVDynamicHDRPlus *out)
{
    uint8_t *buf = रिक्त;
    माप_प्रकार size = 0;
    पूर्णाङ्क ret;

    ret = av_dynamic_hdr_plus_to_t35(in, &buf, &size);
    यदि (ret < 0)
        प्रत्यागम ret;

    स_रखो(out, 0, परिमाण(*out));
    ret = av_dynamic_hdr_plus_from_t35(out, buf, size);
    av_free(buf);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क app5_round_trip(ध्रुव AVDynamicHDRSmpte2094App5 *in,
                           AVDynamicHDRSmpte2094App5 *out)
{
    uint8_t *buf = रिक्त;
    माप_प्रकार size = 0;
    पूर्णाङ्क ret;

    ret = av_dynamic_hdr_smpte2094_app5_to_t35(in, &buf, &size);
    यदि (ret < 0)
        प्रत्यागम ret;

    स_रखो(out, 0, परिमाण(*out));
    ret = av_dynamic_hdr_smpte2094_app5_from_t35(out, buf, size);
    av_free(buf);
    प्रत्यागम ret;
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
स्थिर शून्य fill_hdr_plus_conforming(AVDynamicHDRPlus *s)
{
    स्थिर ध्रुव uint8_t percentages[9] = { 1, 5, 10, 25, 50, 75, 90, 95, 99 };
    स्थिर ध्रुव पूर्णाङ्क percentiles[9] = {
        1000, 0, 255, 25000, 50000, 75000, 90000, 95000, 99000,
    };

    स_रखो(s, 0, परिमाण(*s));

    s->application_version = 1;
    s->अंक_windows         = 1;
    s->targeted_system_display_maximum_luminance =
        (AVRational){ 400, LUMINANCE_DEN };
    s->targeted_system_display_actual_peak_luminance_flag = 0;
    s->mastering_display_actual_peak_luminance_flag       = 0;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 99000, RGB_DEN };
    s->params[0].average_maxrgb = (AVRational){ 40000, RGB_DEN };

    s->params[0].अंक_distribution_maxrgb_percentiles = 9;
    प्रति (पूर्णाङ्क i = 0; i < 9; i++) {
        s->params[0].distribution_maxrgb[i].percentage = percentages[i];
        s->params[0].distribution_maxrgb[i].percentile =
            (AVRational){ percentiles[i], RGB_DEN };
    }
    s->params[0].fraction_bright_pixels =
        (AVRational){ 250, FRACTION_PIXEL_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_point_x = (AVRational){  512, KNEE_POINT_DEN };
    s->params[0].knee_point_y = (AVRational){ 1024, KNEE_POINT_DEN };
    s->params[0].अंक_bezier_curve_anchors = 9;
    प्रति (पूर्णाङ्क i = 0; i < 9; i++)
        s->params[0].bezier_curve_anchors[i] =
            (AVRational){ 100 * (i + 1), BEZIER_ANCHOR_DEN };

    s->params[0].color_saturation_mapping_flag = 0;
}

/* Deliberately NOT a conforming Version 1 payload: it combines a second
 * processing window, both actual-peak-luminance matrices and
 * ColorSaturationWeight, all of which §9.4 excludes for Version 1. It exists
 * only to drive the optional serializer/parser branches those fields guard. */
स्थिर शून्य fill_hdr_plus_synthetic(AVDynamicHDRPlus *s)
{
    स_रखो(s, 0, परिमाण(*s));

    s->application_version = 1;
    s->अंक_windows         = 2;
    s->targeted_system_display_maximum_luminance =
        (AVRational){ 10000, LUMINANCE_DEN };

    s->params[1].window_upper_बायाँ_corner_x  = (AVRational){ 100, 1 };
    s->params[1].window_upper_बायाँ_corner_y  = (AVRational){ 120, 1 };
    s->params[1].window_lower_दायाँ_corner_x = (AVRational){ 500, 1 };
    s->params[1].window_lower_दायाँ_corner_y = (AVRational){ 520, 1 };
    s->params[1].center_of_ellipse_x             = 300;
    s->params[1].center_of_ellipse_y             = 320;
    s->params[1].rotation_angle                  = 45;
    s->params[1].semimajor_axis_internal_ellipse = 50;
    s->params[1].semimajor_axis_external_ellipse = 100;
    s->params[1].semiminor_axis_external_ellipse = 80;
    s->params[1].overlap_process_option          = 1;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 70000, RGB_DEN };
    s->params[0].average_maxrgb = (AVRational){ 40000, RGB_DEN };
    s->params[0].अंक_distribution_maxrgb_percentiles = 2;
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
    s->params[1].average_maxrgb = (AVRational){ 25000, RGB_DEN };
    s->params[1].अंक_distribution_maxrgb_percentiles = 1;
    s->params[1].distribution_maxrgb[0].percentage = 25;
    s->params[1].distribution_maxrgb[0].percentile =
        (AVRational){ 12500, RGB_DEN };
    s->params[1].fraction_bright_pixels =
        (AVRational){ 100, FRACTION_PIXEL_DEN };

    s->targeted_system_display_actual_peak_luminance_flag = 1;
    s->अंक_rows_targeted_system_display_actual_peak_luminance = 2;
    s->अंक_cols_targeted_system_display_actual_peak_luminance = 3;
    प्रति (पूर्णाङ्क i = 0; i < 2; i++)
        प्रति (पूर्णाङ्क j = 0; j < 3; j++)
            s->targeted_system_display_actual_peak_luminance[i][j] =
                (AVRational){ i * 3 + j, PEAK_LUMINANCE_DEN };

    s->mastering_display_actual_peak_luminance_flag = 1;
    s->अंक_rows_mastering_display_actual_peak_luminance = 3;
    s->अंक_cols_mastering_display_actual_peak_luminance = 2;
    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        प्रति (पूर्णाङ्क j = 0; j < 2; j++)
            s->mastering_display_actual_peak_luminance[i][j] =
                (AVRational){ 15 - (i * 2 + j), PEAK_LUMINANCE_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_point_x = (AVRational){ 500, KNEE_POINT_DEN };
    s->params[0].knee_point_y = (AVRational){ 800, KNEE_POINT_DEN };
    s->params[0].अंक_bezier_curve_anchors = 3;
    s->params[0].bezier_curve_anchors[0] = (AVRational){ 100, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_curve_anchors[1] = (AVRational){ 500, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_curve_anchors[2] = (AVRational){ 900, BEZIER_ANCHOR_DEN };
    s->params[1].tone_mapping_flag = 0;

    प्रति (पूर्णाङ्क w = 0; w < 2; w++) {
        s->params[w].color_saturation_mapping_flag = 1;
        s->params[w].color_saturation_weight =
            (AVRational){ 8 + w, SATURATION_DEN };
    }
}

स्थिर शून्य test_hdr_plus(शून्य)
{
    AVDynamicHDRPlus *hdr, *hdr_rt;
    AVFrame *frame;
    माप_प्रकार size = 0, required = 0;
    uint8_t *buf = रिक्त;
    पूर्णाङ्क ret;

    म_लिखो("=== AVDynamicHDRPlus ===\n");

    म_लिखो("Testing av_dynamic_hdr_plus_alloc()\n");
    hdr = av_dynamic_hdr_plus_alloc(&size);
    म_लिखो("alloc: %s size>0=%s\n", hdr ? "OK" : "FAIL",
           size > 0 ? "yes" : "no");
    av_freep(&hdr);

    hdr = av_dynamic_hdr_plus_alloc(रिक्त);
    म_लिखो("alloc (no size): %s\n", hdr ? "OK" : "FAIL");
    av_freep(&hdr);

    म_लिखो("\nTesting av_dynamic_hdr_plus_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        hdr = av_dynamic_hdr_plus_create_side_data(frame);
        म_लिखो("create_side_data: %s\n", hdr ? "OK" : "FAIL");
        av_frame_free(&frame);
    }

    hdr    = av_dynamic_hdr_plus_alloc(रिक्त);
    hdr_rt = av_dynamic_hdr_plus_alloc(रिक्त);
    यदि (!hdr || !hdr_rt) {
        av_freep(&hdr);
        av_freep(&hdr_rt);
        प्रत्यागम;
    }
    fill_hdr_plus_conforming(hdr);

    /* Size-query mode: data=NULL, size receives the required byte count. */
    म_लिखो("\nTesting av_dynamic_hdr_plus_to_t35() size query\n");
    required = 0;
    ret = av_dynamic_hdr_plus_to_t35(hdr, रिक्त, &required);
    म_लिखो("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    /* Allocation mode: *data=NULL, the function allocates the buffer. */
    म_लिखो("\nTesting av_dynamic_hdr_plus_to_t35() allocation\n");
    buf  = रिक्त;
    size = 0;
    ret = av_dynamic_hdr_plus_to_t35(hdr, &buf, &size);
    म_लिखो("alloc mode: ret=%d size_match=%s\n", ret,
           size == required ? "yes" : "no");
    av_freep(&buf);

    /* Existing-buffer mode: a caller-owned buffer is filled in place. */
    म_लिखो("\nTesting av_dynamic_hdr_plus_to_t35() existing buffer\n");
    buf = av_malloc(required);
    यदि (buf) {
        uint8_t *orig = buf;
        size = required;
        ret = av_dynamic_hdr_plus_to_t35(hdr, &buf, &size);
        म_लिखो("existing buf: ret=%d same_pointer=%s size_match=%s\n", ret,
               buf == orig ? "yes" : "no",
               size == required ? "yes" : "no");
        av_freep(&buf);
    }

    /* Buffer-too-small: caller-owned buffer shorter than required. */
    म_लिखो("\nTesting av_dynamic_hdr_plus_to_t35() buffer too small\n");
    यदि (required > 1) {
        buf = av_malloc(required - 1);
        यदि (buf) {
            size = required - 1;
            ret = av_dynamic_hdr_plus_to_t35(hdr, &buf, &size);
            म_लिखो("too small: ret==AVERROR_BUFFER_TOO_SMALL=%s\n",
                   ret == AVERROR_BUFFER_TOO_SMALL ? "yes" : "no");
            av_freep(&buf);
        }
    }

    म_लिखो("\nTesting round trip, conforming ST 2094-40 Version 1 payload\n");
    ret = hdr_plus_round_trip(hdr, hdr_rt);
    म_लिखो("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    /* to_t35() ignores application_version and always writes the CTA-861-H
     * value, so the parsed field does not echo an out-of-range input. */
    म_लिखो("\nTesting that to_t35() overrides application_version\n");
    hdr->application_version = 7;
    ret = hdr_plus_round_trip(hdr, hdr_rt);
    म_लिखो("input=7 ret=%d decoded application_version=%u\n", ret,
           hdr_rt->application_version);
    hdr->application_version = 1;

    म_लिखो("\nTesting round trip, synthetic payload (branch coverage only)\n");
    fill_hdr_plus_synthetic(hdr);
    ret = hdr_plus_round_trip(hdr, hdr_rt);
    म_लिखो("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    म_लिखो("\nTesting error paths\n");
    buf  = रिक्त;
    size = 0;
    ret = av_dynamic_hdr_plus_to_t35(रिक्त, &buf, &size);
    म_लिखो("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_to_t35(hdr, रिक्त, रिक्त);
    म_लिखो("to_t35 no data no size: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_from_t35(रिक्त, (ध्रुव uint8_t *)"", 0);
    म_लिखो("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    {
        /* Oversized input is rejected before parsing. */
        माप_प्रकार big = AV_HDR_PLUS_MAX_PAYLOAD_SIZE + 1;
        uint8_t *oversized = av_mallocz(big);
        यदि (oversized) {
            ret = av_dynamic_hdr_plus_from_t35(hdr_rt, oversized, big);
            म_लिखो("from_t35 oversized: ret==AVERROR(EINVAL)=%s\n",
                   ret == AVERROR(EINVAL) ? "yes" : "no");
            av_free(oversized);
        }
    }

    av_freep(&hdr);
    av_freep(&hdr_rt);

    म_लिखो("\nTesting OOM path\n");
    av_max_alloc(1);
    hdr = av_dynamic_hdr_plus_alloc(&size);
    म_लिखो("alloc OOM: %s\n", hdr ? "FAIL" : "OK");
    av_max_alloc(पूर्णांक_उच्च);
    av_freep(&hdr);
}

/* Table C.2 early-out: no adaptive tone map, custom reference white only. */
स्थिर शून्य fill_app5_minimal(AVDynamicHDRSmpte2094App5 *s)
{
    स_रखो(s, 0, परिमाण(*s));
    s->application_version         = 1;
    s->minimum_application_version = 0;
    s->has_custom_hdr_reference_white_flag = 1;
    s->hdr_reference_white         = 0x0203;
    s->has_adaptive_tone_map_flag  = 0;
}

/* Table C.3 early-out: reference-white tone mapping, no alternate images. */
स्थिर शून्य fill_app5_reference_white(AVDynamicHDRSmpte2094App5 *s)
{
    स_रखो(s, 0, परिमाण(*s));
    s->application_version        = 2;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->use_reference_white_tone_mapping_flag = 1;
}

/* Per-image parameters: explicit gain application space chromaticities,
 * component mixing type 3 with a mix of present and absent coefficients, and
 * explicit control point slopes (theta). */
स्थिर शून्य fill_app5_per_image(AVDynamicHDRSmpte2094App5 *s)
{
    स_रखो(s, 0, परिमाण(*s));
    s->application_version        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->अंक_alternate_images       = 2;
    s->gain_application_space_chromaticities_flag = 3;
    प्रति (पूर्णाङ्क r = 0; r < 8; r++)
        s->gain_application_space_chromaticities[r] = 100 * (r + 1);
    s->has_common_component_mix_params_flag = 0;
    s->has_common_curve_params_flag         = 0;
    प्रति (पूर्णाङ्क a = 0; a < 2; a++) {
        s->alternate_hdr_headrooms[a] = 0x0100 + a;
        s->component_mixing_type[a]   = 3;
        प्रति (पूर्णाङ्क k = 0; k < 6; k++) {
            s->has_component_mixing_coefficient_flag[a][k] = k & 1;
            s->component_mixing_coefficient[a][k] = 0x1000 + 0x10 * a + k;
        }
        s->gain_curve_अंक_control_points_minus_1[a] = 1;
        s->gain_curve_use_pchip_slope_flag[a]       = 0;
        प्रति (पूर्णाङ्क c = 0; c < 2; c++) {
            s->gain_curve_control_points_x[a][c]     = 0x2000 + 0x10 * a + c;
            s->gain_curve_control_points_y[a][c]     = 0x3000 + 0x10 * a + c;
            s->gain_curve_control_points_theta[a][c] = 0x4000 + 0x10 * a + c;
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
स्थिर शून्य fill_app5_common(AVDynamicHDRSmpte2094App5 *s)
{
    स_रखो(s, 0, परिमाण(*s));
    s->application_version        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0def;
    s->अंक_alternate_images       = 3;
    s->gain_application_space_chromaticities_flag = 0;
    s->has_common_component_mix_params_flag = 1;
    s->has_common_curve_params_flag         = 1;
    प्रति (पूर्णाङ्क a = 0; a < 3; a++) {
        s->alternate_hdr_headrooms[a] = 0x0200 + a;
        s->component_mixing_type[a]   = 1;
        s->gain_curve_अंक_control_points_minus_1[a] = 2;
        s->gain_curve_use_pchip_slope_flag[a]       = 1;
        प्रति (पूर्णाङ्क c = 0; c < 3; c++) {
            s->gain_curve_control_points_x[a][c] = 0x5000 + c;
            s->gain_curve_control_points_y[a][c] = 0x6000 + 0x10 * a + c;
        }
    }
}

स्थिर शून्य test_app5(शून्य)
{
    AVDynamicHDRSmpte2094App5 *app5, *app5_rt;
    AVFrame *frame;
    माप_प्रकार size = 0, required = 0;
    uint8_t *buf = रिक्त;
    पूर्णाङ्क ret;

    म_लिखो("\n=== AVDynamicHDRSmpte2094App5 ===\n");
    म_लिखो("Testing av_dynamic_hdr_smpte2094_app5_alloc()\n");
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&size);
    म_लिखो("alloc: %s size>0=%s\n", app5 ? "OK" : "FAIL",
           size > 0 ? "yes" : "no");
    av_freep(&app5);

    म_लिखो("\nTesting av_dynamic_hdr_smpte2094_app5_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        app5 = av_dynamic_hdr_smpte2094_app5_create_side_data(frame);
        म_लिखो("create_side_data: %s\n", app5 ? "OK" : "FAIL");
        av_frame_free(&frame);
    }

    app5    = av_dynamic_hdr_smpte2094_app5_alloc(रिक्त);
    app5_rt = av_dynamic_hdr_smpte2094_app5_alloc(रिक्त);
    यदि (!app5 || !app5_rt) {
        av_freep(&app5);
        av_freep(&app5_rt);
        प्रत्यागम;
    }
    fill_app5_minimal(app5);

    म_लिखो("\nTesting av_dynamic_hdr_smpte2094_app5_to_t35()\n");
    required = 0;
    ret = av_dynamic_hdr_smpte2094_app5_to_t35(app5, रिक्त, &required);
    म_लिखो("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    buf  = रिक्त;
    size = 0;
    ret = av_dynamic_hdr_smpte2094_app5_to_t35(app5, &buf, &size);
    म_लिखो("alloc mode: ret=%d size_match=%s\n", ret,
           size == required ? "yes" : "no");
    av_freep(&buf);

    म_लिखो("\nTesting round trip, no adaptive tone map\n");
    ret = app5_round_trip(app5, app5_rt);
    म_लिखो("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_app5("decoded", app5_rt);

    म_लिखो("\nTesting round trip, reference-white tone mapping\n");
    fill_app5_reference_white(app5);
    ret = app5_round_trip(app5, app5_rt);
    म_लिखो("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_app5("decoded", app5_rt);

    म_लिखो("\nTesting round trip, per-image mixing and curve parameters\n");
    fill_app5_per_image(app5);
    ret = app5_round_trip(app5, app5_rt);
    म_लिखो("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_app5("decoded", app5_rt);

    म_लिखो("\nTesting round trip, common mixing and curve parameters\n");
    fill_app5_common(app5);
    ret = app5_round_trip(app5, app5_rt);
    म_लिखो("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_app5("decoded", app5_rt);

    म_लिखो("\nTesting error paths\n");
    buf  = रिक्त;
    size = 0;
    ret = av_dynamic_hdr_smpte2094_app5_to_t35(रिक्त, &buf, &size);
    म_लिखो("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_smpte2094_app5_from_t35(रिक्त, (ध्रुव uint8_t *)"", 0);
    म_लिखो("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    /* application_version does not fit the 3-bit field. */
    app5->application_version = 8;
    ret = av_dynamic_hdr_smpte2094_app5_to_t35(app5, रिक्त, &size);
    म_लिखो("to_t35 invalid application_version: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->application_version = 1;

    /* minimum_application_version above the documented maximum. */
    app5->minimum_application_version = 3;
    ret = av_dynamic_hdr_smpte2094_app5_to_t35(app5, रिक्त, &size);
    म_लिखो("to_t35 invalid minimum_application_version:"
           " ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->minimum_application_version = 0;

    /* More alternate images than the 3-bit count admits. */
    app5->अंक_alternate_images = 5;
    ret = av_dynamic_hdr_smpte2094_app5_to_t35(app5, रिक्त, &size);
    म_लिखो("to_t35 too many alternate images: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");

    av_freep(&app5);
    av_freep(&app5_rt);

    म_लिखो("\nTesting OOM path\n");
    av_max_alloc(1);
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&size);
    म_लिखो("alloc OOM: %s\n", app5 ? "FAIL" : "OK");
    av_max_alloc(पूर्णांक_उच्च);
    av_freep(&app5);
}

पूर्णाङ्क main(शून्य)
{
    test_hdr_plus();
    test_app5();
    प्रत्यागम 0;
}

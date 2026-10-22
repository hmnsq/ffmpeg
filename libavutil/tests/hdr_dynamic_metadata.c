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
#परिभाषय LUMINANCE_DEN          1
#परिभाषय PEAK_LUMINANCE_DEN    15
#परिभाषय RGB_DEN           100000
#परिभाषय FRACTION_PIXEL_DEN  1000
#परिभाषय KNEE_POINT_DEN      4095
#परिभाषय BEZIER_ANCHOR_DEN   1023
#परिभाषय SATURATION_DEN         8

/*
 * Printers. Every field a fixture populates is printed, so that a serializer
 * or parser which drops or corrupts a value changes the FATE reference
 * instead of silently passing a flag-only check.
 */

स्थिर शून्य print_peak_matrix(ध्रुव वर्ण *label, पूर्णाङ्क पङ्क्तिकाः, पूर्णाङ्क स्तम्भसङ्ख्या,
                              ध्रुव AVRational m[25][25])
{
    प्रारूप_लिख("    %s %dx%d:", label, पङ्क्तिकाः, स्तम्भसङ्ख्या);
    प्रति (पूर्णाङ्क i = 0; i < पङ्क्तिकाः; i++)
        प्रति (पूर्णाङ्क j = 0; j < स्तम्भसङ्ख्या; j++)
            प्रारूप_लिख(" %d/%d", m[i][j].अङ्कः, m[i][j].den);
    प्रारूप_लिख("\n");
}

स्थिर शून्य print_गवाक्षः(पूर्णाङ्क w, ध्रुव AVHDRPlusColorTransformParams *p,
                         पूर्णाङ्क geometry)
{
    प्रारूप_लिख("  window %d:\n", w);
    /* Window 0 covers the whole frame; its geometry is not serialized. */
    यदि (geometry) {
        प्रारूप_लिख("    corners: ul=%d/%d,%d/%d lr=%d/%d,%d/%d\n",
               p->गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_x.अङ्कः,
               p->गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_x.den,
               p->गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_y.अङ्कः,
               p->गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_y.den,
               p->गवाक्षः_अधस्तनम्_दक्षिणः_corner_x.अङ्कः,
               p->गवाक्षः_अधस्तनम्_दक्षिणः_corner_x.den,
               p->गवाक्षः_अधस्तनम्_दक्षिणः_corner_y.अङ्कः,
               p->गवाक्षः_अधस्तनम्_दक्षिणः_corner_y.den);
        प्रारूप_लिख("    ellipse: center=%u,%u rotation=%u semimajor_int=%u"
               " semimajor_ext=%u semiminor_ext=%u overlap=%u\n",
               p->center_सम्बन्धि_ellipse_x, p->center_सम्बन्धि_ellipse_y,
               p->rotation_angle, p->semimajor_axis_आन्तरिकम्_ellipse,
               p->semimajor_axis_external_ellipse,
               p->semiminor_axis_external_ellipse,
               p->overlap_process_option);
    }
    प्रारूप_लिख("    maxscl: %d/%d %d/%d %d/%d average_maxrgb=%d/%d\n",
           p->maxscl[0].अङ्कः, p->maxscl[0].den,
           p->maxscl[1].अङ्कः, p->maxscl[1].den,
           p->maxscl[2].अङ्कः, p->maxscl[2].den,
           p->मध्यमानम्_maxrgb.अङ्कः, p->मध्यमानम्_maxrgb.den);
    प्रारूप_लिख("    distribution_maxrgb: n=%u",
           p->अङ्कः_distribution_maxrgb_percentiles);
    प्रति (पूर्णाङ्क i = 0; i < p->अङ्कः_distribution_maxrgb_percentiles; i++)
        प्रारूप_लिख(" %u%%=%d/%d", p->distribution_maxrgb[i].percentage,
               p->distribution_maxrgb[i].percentile.अङ्कः,
               p->distribution_maxrgb[i].percentile.den);
    प्रारूप_लिख("\n    fraction_bright_pixels=%d/%d\n",
           p->fraction_bright_pixels.अङ्कः, p->fraction_bright_pixels.den);
    प्रारूप_लिख("    tone_mapping_flag=%u", p->tone_mapping_flag);
    यदि (p->tone_mapping_flag) {
        प्रारूप_लिख(" knee=%d/%d,%d/%d anchors=%u:",
               p->knee_point_x.अङ्कः, p->knee_point_x.den,
               p->knee_point_y.अङ्कः, p->knee_point_y.den,
               p->अङ्कः_bezier_वक्रम्_anchors);
        प्रति (पूर्णाङ्क i = 0; i < p->अङ्कः_bezier_वक्रम्_anchors; i++)
            प्रारूप_लिख(" %d/%d", p->bezier_वक्रम्_anchors[i].अङ्कः,
                   p->bezier_वक्रम्_anchors[i].den);
    }
    प्रारूप_लिख("\n    color_saturation_mapping_flag=%u",
           p->color_saturation_mapping_flag);
    यदि (p->color_saturation_mapping_flag)
        प्रारूप_लिख(" weight=%d/%d", p->color_saturation_weight.अङ्कः,
               p->color_saturation_weight.den);
    प्रारूप_लिख("\n");
}

स्थिर शून्य print_hdr_plus(ध्रुव वर्ण *label, ध्रुव AVDynamicHDRPlus *s)
{
    प्रारूप_लिख("%s:\n", label);
    प्रारूप_लिख("  application_version=%u num_windows=%u"
           " targeted_system_display_maximum_luminance=%d/%d\n",
           s->application_संस्करणम्, s->अङ्कः_windows,
           s->targeted_system_display_अधिकतमम्_luminance.अङ्कः,
           s->targeted_system_display_अधिकतमम्_luminance.den);
    प्रारूप_लिख("  targeted_system_display_actual_peak_luminance_flag=%u\n",
           s->targeted_system_display_actual_peak_luminance_flag);
    यदि (s->targeted_system_display_actual_peak_luminance_flag)
        print_peak_matrix("targeted_peak",
                          s->अङ्कः_पङ्क्तिकाः_targeted_system_display_actual_peak_luminance,
                          s->अङ्कः_स्तम्भसङ्ख्या_targeted_system_display_actual_peak_luminance,
                          s->targeted_system_display_actual_peak_luminance);
    प्रारूप_लिख("  mastering_display_actual_peak_luminance_flag=%u\n",
           s->mastering_display_actual_peak_luminance_flag);
    यदि (s->mastering_display_actual_peak_luminance_flag)
        print_peak_matrix("mastering_peak",
                          s->अङ्कः_पङ्क्तिकाः_mastering_display_actual_peak_luminance,
                          s->अङ्कः_स्तम्भसङ्ख्या_mastering_display_actual_peak_luminance,
                          s->mastering_display_actual_peak_luminance);
    प्रति (पूर्णाङ्क w = 0; w < s->अङ्कः_windows; w++)
        print_गवाक्षः(w, &s->params[w], w > 0);
}

स्थिर शून्य print_app5(ध्रुव वर्ण *label, ध्रुव AVDynamicHDRSmpte2094App5 *s)
{
    प्रारूप_लिख("%s:\n", label);
    प्रारूप_लिख("  application_version=%u minimum_application_version=%u\n",
           s->application_संस्करणम्, s->minimum_application_संस्करणम्);
    प्रारूप_लिख("  has_custom_hdr_reference_white_flag=%u",
           s->has_custom_hdr_reference_white_flag);
    यदि (s->has_custom_hdr_reference_white_flag)
        प्रारूप_लिख(" hdr_reference_white=0x%04x", s->hdr_reference_white);
    प्रारूप_लिख("\n  has_adaptive_tone_map_flag=%u\n",
           s->has_adaptive_tone_map_flag);
    यदि (!s->has_adaptive_tone_map_flag)
        प्रत्यागम;

    प्रारूप_लिख("  baseline_hdr_headroom=0x%04x"
           " use_reference_white_tone_mapping_flag=%u\n",
           s->baseline_hdr_headroom, s->use_reference_white_tone_mapping_flag);
    यदि (s->use_reference_white_tone_mapping_flag)
        प्रत्यागम;

    प्रारूप_लिख("  num_alternate_images=%u chromaticities_flag=%u"
           " has_common_component_mix_params_flag=%u"
           " has_common_curve_params_flag=%u\n",
           s->अङ्कः_alternate_images,
           s->gain_application_space_chromaticities_flag,
           s->has_common_component_mix_params_flag,
           s->has_common_वक्रम्_params_flag);
    यदि (s->gain_application_space_chromaticities_flag == 3) {
        प्रारूप_लिख("  chromaticities:");
        प्रति (पूर्णाङ्क r = 0; r < 8; r++)
            प्रारूप_लिख(" 0x%04x", s->gain_application_space_chromaticities[r]);
        प्रारूप_लिख("\n");
    }

    प्रति (पूर्णाङ्क a = 0; a < s->अङ्कः_alternate_images; a++) {
        पूर्णाङ्क n = s->gain_वक्रम्_अङ्कः_control_points_minus_1[a] + 1;
        प्रारूप_लिख("  alternate %d: hdr_headroom=0x%04x component_mixing_type=%u\n",
               a, s->alternate_hdr_headrooms[a], s->component_mixing_type[a]);
        यदि (s->component_mixing_type[a] == 3) {
            प्रारूप_लिख("    mixing flag:coefficient:");
            प्रति (पूर्णाङ्क k = 0; k < 6; k++)
                प्रारूप_लिख(" %u:0x%04x",
                       s->has_component_mixing_coefficient_flag[a][k],
                       s->component_mixing_coefficient[a][k]);
            प्रारूप_लिख("\n");
        }
        प्रारूप_लिख("    curve: num_control_points=%d use_pchip_slope=%u\n", n,
               s->gain_वक्रम्_use_pchip_नतिः_flag[a]);
        प्रारूप_लिख("    x:");
        प्रति (पूर्णाङ्क c = 0; c < n; c++)
            प्रारूप_लिख(" 0x%04x", s->gain_वक्रम्_control_points_x[a][c]);
        प्रारूप_लिख("\n    y:");
        प्रति (पूर्णाङ्क c = 0; c < n; c++)
            प्रारूप_लिख(" 0x%04x", s->gain_वक्रम्_control_points_y[a][c]);
        प्रारूप_लिख("\n");
        /* theta is only serialized when the pchip slope is not used. */
        यदि (!s->gain_वक्रम्_use_pchip_नतिः_flag[a]) {
            प्रारूप_लिख("    theta:");
            प्रति (पूर्णाङ्क c = 0; c < n; c++)
                प्रारूप_लिख(" 0x%04x", s->gain_वक्रम्_control_points_theta[a][c]);
            प्रारूप_लिख("\n");
        }
    }
}

/*
 * Round-trip helpers: serialize, then parse back into a zeroed struct.
 */

स्थिर पूर्णाङ्क hdr_plus_आवर्तनम्_trip(ध्रुव AVDynamicHDRPlus *अन्तर्, AVDynamicHDRPlus *बहिर्गमनम्)
{
    uint8_t *buf = रिक्त;
    size_t आकार = 0;
    पूर्णाङ्क ret;

    ret = av_dynamic_hdr_plus_गन्तव्यम्_t35(अन्तर्, &buf, &आकार);
    यदि (ret < 0)
        प्रत्यागम ret;

    स्मृतिं_पूरय(बहिर्गमनम्, 0, परिमाण(*बहिर्गमनम्));
    ret = av_dynamic_hdr_plus_from_t35(बहिर्गमनम्, buf, आकार);
    av_free(buf);
    प्रत्यागम ret;
}

स्थिर पूर्णाङ्क app5_आवर्तनम्_trip(ध्रुव AVDynamicHDRSmpte2094App5 *अन्तर्,
                           AVDynamicHDRSmpte2094App5 *बहिर्गमनम्)
{
    uint8_t *buf = रिक्त;
    size_t आकार = 0;
    पूर्णाङ्क ret;

    ret = av_dynamic_hdr_smpte2094_app5_गन्तव्यम्_t35(अन्तर्, &buf, &आकार);
    यदि (ret < 0)
        प्रत्यागम ret;

    स्मृतिं_पूरय(बहिर्गमनम्, 0, परिमाण(*बहिर्गमनम्));
    ret = av_dynamic_hdr_smpte2094_app5_from_t35(बहिर्गमनम्, buf, आकार);
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

    स्मृतिं_पूरय(s, 0, परिमाण(*s));

    s->application_संस्करणम् = 1;
    s->अङ्कः_windows         = 1;
    s->targeted_system_display_अधिकतमम्_luminance =
        (AVRational){ 400, LUMINANCE_DEN };
    s->targeted_system_display_actual_peak_luminance_flag = 0;
    s->mastering_display_actual_peak_luminance_flag       = 0;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 99000, RGB_DEN };
    s->params[0].मध्यमानम्_maxrgb = (AVRational){ 40000, RGB_DEN };

    s->params[0].अङ्कः_distribution_maxrgb_percentiles = 9;
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
    s->params[0].अङ्कः_bezier_वक्रम्_anchors = 9;
    प्रति (पूर्णाङ्क i = 0; i < 9; i++)
        s->params[0].bezier_वक्रम्_anchors[i] =
            (AVRational){ 100 * (i + 1), BEZIER_ANCHOR_DEN };

    s->params[0].color_saturation_mapping_flag = 0;
}

/* Deliberately NOT a conforming Version 1 payload: it combines a second
 * processing window, both actual-peak-luminance matrices and
 * ColorSaturationWeight, all of which §9.4 excludes for Version 1. It exists
 * only to drive the optional serializer/parser branches those fields guard. */
स्थिर शून्य fill_hdr_plus_synthetic(AVDynamicHDRPlus *s)
{
    स्मृतिं_पूरय(s, 0, परिमाण(*s));

    s->application_संस्करणम् = 1;
    s->अङ्कः_windows         = 2;
    s->targeted_system_display_अधिकतमम्_luminance =
        (AVRational){ 10000, LUMINANCE_DEN };

    s->params[1].गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_x  = (AVRational){ 100, 1 };
    s->params[1].गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_y  = (AVRational){ 120, 1 };
    s->params[1].गवाक्षः_अधस्तनम्_दक्षिणः_corner_x = (AVRational){ 500, 1 };
    s->params[1].गवाक्षः_अधस्तनम्_दक्षिणः_corner_y = (AVRational){ 520, 1 };
    s->params[1].center_सम्बन्धि_ellipse_x             = 300;
    s->params[1].center_सम्बन्धि_ellipse_y             = 320;
    s->params[1].rotation_angle                  = 45;
    s->params[1].semimajor_axis_आन्तरिकम्_ellipse = 50;
    s->params[1].semimajor_axis_external_ellipse = 100;
    s->params[1].semiminor_axis_external_ellipse = 80;
    s->params[1].overlap_process_option          = 1;

    s->params[0].maxscl[0]      = (AVRational){ 50000, RGB_DEN };
    s->params[0].maxscl[1]      = (AVRational){ 60000, RGB_DEN };
    s->params[0].maxscl[2]      = (AVRational){ 70000, RGB_DEN };
    s->params[0].मध्यमानम्_maxrgb = (AVRational){ 40000, RGB_DEN };
    s->params[0].अङ्कः_distribution_maxrgb_percentiles = 2;
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
    s->params[1].मध्यमानम्_maxrgb = (AVRational){ 25000, RGB_DEN };
    s->params[1].अङ्कः_distribution_maxrgb_percentiles = 1;
    s->params[1].distribution_maxrgb[0].percentage = 25;
    s->params[1].distribution_maxrgb[0].percentile =
        (AVRational){ 12500, RGB_DEN };
    s->params[1].fraction_bright_pixels =
        (AVRational){ 100, FRACTION_PIXEL_DEN };

    s->targeted_system_display_actual_peak_luminance_flag = 1;
    s->अङ्कः_पङ्क्तिकाः_targeted_system_display_actual_peak_luminance = 2;
    s->अङ्कः_स्तम्भसङ्ख्या_targeted_system_display_actual_peak_luminance = 3;
    प्रति (पूर्णाङ्क i = 0; i < 2; i++)
        प्रति (पूर्णाङ्क j = 0; j < 3; j++)
            s->targeted_system_display_actual_peak_luminance[i][j] =
                (AVRational){ i * 3 + j, PEAK_LUMINANCE_DEN };

    s->mastering_display_actual_peak_luminance_flag = 1;
    s->अङ्कः_पङ्क्तिकाः_mastering_display_actual_peak_luminance = 3;
    s->अङ्कः_स्तम्भसङ्ख्या_mastering_display_actual_peak_luminance = 2;
    प्रति (पूर्णाङ्क i = 0; i < 3; i++)
        प्रति (पूर्णाङ्क j = 0; j < 2; j++)
            s->mastering_display_actual_peak_luminance[i][j] =
                (AVRational){ 15 - (i * 2 + j), PEAK_LUMINANCE_DEN };

    s->params[0].tone_mapping_flag = 1;
    s->params[0].knee_point_x = (AVRational){ 500, KNEE_POINT_DEN };
    s->params[0].knee_point_y = (AVRational){ 800, KNEE_POINT_DEN };
    s->params[0].अङ्कः_bezier_वक्रम्_anchors = 3;
    s->params[0].bezier_वक्रम्_anchors[0] = (AVRational){ 100, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_वक्रम्_anchors[1] = (AVRational){ 500, BEZIER_ANCHOR_DEN };
    s->params[0].bezier_वक्रम्_anchors[2] = (AVRational){ 900, BEZIER_ANCHOR_DEN };
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
    size_t आकार = 0, required = 0;
    uint8_t *buf = रिक्त;
    पूर्णाङ्क ret;

    प्रारूप_लिख("=== AVDynamicHDRPlus ===\n");

    प्रारूप_लिख("Testing av_dynamic_hdr_plus_alloc()\n");
    hdr = av_dynamic_hdr_plus_alloc(&आकार);
    प्रारूप_लिख("alloc: %s size>0=%s\n", hdr ? "OK" : "FAIL",
           आकार > 0 ? "yes" : "no");
    av_freep(&hdr);

    hdr = av_dynamic_hdr_plus_alloc(रिक्त);
    प्रारूप_लिख("alloc (no size): %s\n", hdr ? "OK" : "FAIL");
    av_freep(&hdr);

    प्रारूप_लिख("\nTesting av_dynamic_hdr_plus_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        hdr = av_dynamic_hdr_plus_create_side_दत्त(frame);
        प्रारूप_लिख("create_side_data: %s\n", hdr ? "OK" : "FAIL");
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
    प्रारूप_लिख("\nTesting av_dynamic_hdr_plus_to_t35() size query\n");
    required = 0;
    ret = av_dynamic_hdr_plus_गन्तव्यम्_t35(hdr, रिक्त, &required);
    प्रारूप_लिख("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    /* Allocation mode: *data=NULL, the function allocates the buffer. */
    प्रारूप_लिख("\nTesting av_dynamic_hdr_plus_to_t35() allocation\n");
    buf  = रिक्त;
    आकार = 0;
    ret = av_dynamic_hdr_plus_गन्तव्यम्_t35(hdr, &buf, &आकार);
    प्रारूप_लिख("alloc mode: ret=%d size_match=%s\n", ret,
           आकार == required ? "yes" : "no");
    av_freep(&buf);

    /* Existing-buffer mode: a caller-owned buffer is filled in place. */
    प्रारूप_लिख("\nTesting av_dynamic_hdr_plus_to_t35() existing buffer\n");
    buf = av_malloc(required);
    यदि (buf) {
        uint8_t *orig = buf;
        आकार = required;
        ret = av_dynamic_hdr_plus_गन्तव्यम्_t35(hdr, &buf, &आकार);
        प्रारूप_लिख("existing buf: ret=%d same_pointer=%s size_match=%s\n", ret,
               buf == orig ? "yes" : "no",
               आकार == required ? "yes" : "no");
        av_freep(&buf);
    }

    /* Buffer-too-small: caller-owned buffer shorter than required. */
    प्रारूप_लिख("\nTesting av_dynamic_hdr_plus_to_t35() buffer too small\n");
    यदि (required > 1) {
        buf = av_malloc(required - 1);
        यदि (buf) {
            आकार = required - 1;
            ret = av_dynamic_hdr_plus_गन्तव्यम्_t35(hdr, &buf, &आकार);
            प्रारूप_लिख("too small: ret==AVERROR_BUFFER_TOO_SMALL=%s\n",
                   ret == AVERROR_बफर_TOO_SMALL ? "yes" : "no");
            av_freep(&buf);
        }
    }

    प्रारूप_लिख("\nTesting round trip, conforming ST 2094-40 Version 1 payload\n");
    ret = hdr_plus_आवर्तनम्_trip(hdr, hdr_rt);
    प्रारूप_लिख("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    /* to_t35() ignores application_version and always writes the CTA-861-H
     * value, so the parsed field does not echo an out-of-range input. */
    प्रारूप_लिख("\nTesting that to_t35() overrides application_version\n");
    hdr->application_संस्करणम् = 7;
    ret = hdr_plus_आवर्तनम्_trip(hdr, hdr_rt);
    प्रारूप_लिख("input=7 ret=%d decoded application_version=%u\n", ret,
           hdr_rt->application_संस्करणम्);
    hdr->application_संस्करणम् = 1;

    प्रारूप_लिख("\nTesting round trip, synthetic payload (branch coverage only)\n");
    fill_hdr_plus_synthetic(hdr);
    ret = hdr_plus_आवर्तनम्_trip(hdr, hdr_rt);
    प्रारूप_लिख("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_hdr_plus("decoded", hdr_rt);

    प्रारूप_लिख("\nTesting error paths\n");
    buf  = रिक्त;
    आकार = 0;
    ret = av_dynamic_hdr_plus_गन्तव्यम्_t35(रिक्त, &buf, &आकार);
    प्रारूप_लिख("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_गन्तव्यम्_t35(hdr, रिक्त, रिक्त);
    प्रारूप_लिख("to_t35 no data no size: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_plus_from_t35(रिक्त, (ध्रुव uint8_t *)"", 0);
    प्रारूप_लिख("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    {
        /* Oversized input is rejected before parsing. */
        size_t big = AV_HDR_PLUS_MAX_PAYLOAD_आकार + 1;
        uint8_t *oversized = av_mallocz(big);
        यदि (oversized) {
            ret = av_dynamic_hdr_plus_from_t35(hdr_rt, oversized, big);
            प्रारूप_लिख("from_t35 oversized: ret==AVERROR(EINVAL)=%s\n",
                   ret == AVERROR(EINVAL) ? "yes" : "no");
            av_free(oversized);
        }
    }

    av_freep(&hdr);
    av_freep(&hdr_rt);

    प्रारूप_लिख("\nTesting OOM path\n");
    av_max_alloc(1);
    hdr = av_dynamic_hdr_plus_alloc(&आकार);
    प्रारूप_लिख("alloc OOM: %s\n", hdr ? "FAIL" : "OK");
    av_max_alloc(अधिकतम_पूर्णाङ्कः);
    av_freep(&hdr);
}

/* Table C.2 early-out: no adaptive tone map, custom reference white only. */
स्थिर शून्य fill_app5_अल्पिष्ठम्(AVDynamicHDRSmpte2094App5 *s)
{
    स्मृतिं_पूरय(s, 0, परिमाण(*s));
    s->application_संस्करणम्         = 1;
    s->minimum_application_संस्करणम् = 0;
    s->has_custom_hdr_reference_white_flag = 1;
    s->hdr_reference_white         = 0x0203;
    s->has_adaptive_tone_map_flag  = 0;
}

/* Table C.3 early-out: reference-white tone mapping, no alternate images. */
स्थिर शून्य fill_app5_reference_white(AVDynamicHDRSmpte2094App5 *s)
{
    स्मृतिं_पूरय(s, 0, परिमाण(*s));
    s->application_संस्करणम्        = 2;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->use_reference_white_tone_mapping_flag = 1;
}

/* Per-image parameters: explicit gain application space chromaticities,
 * component mixing type 3 with a mix of present and absent coefficients, and
 * explicit control point slopes (theta). */
स्थिर शून्य fill_app5_प्रत्येकम्_image(AVDynamicHDRSmpte2094App5 *s)
{
    स्मृतिं_पूरय(s, 0, परिमाण(*s));
    s->application_संस्करणम्        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0abc;
    s->अङ्कः_alternate_images       = 2;
    s->gain_application_space_chromaticities_flag = 3;
    प्रति (पूर्णाङ्क r = 0; r < 8; r++)
        s->gain_application_space_chromaticities[r] = 100 * (r + 1);
    s->has_common_component_mix_params_flag = 0;
    s->has_common_वक्रम्_params_flag         = 0;
    प्रति (पूर्णाङ्क a = 0; a < 2; a++) {
        s->alternate_hdr_headrooms[a] = 0x0100 + a;
        s->component_mixing_type[a]   = 3;
        प्रति (पूर्णाङ्क k = 0; k < 6; k++) {
            s->has_component_mixing_coefficient_flag[a][k] = k & 1;
            s->component_mixing_coefficient[a][k] = 0x1000 + 0x10 * a + k;
        }
        s->gain_वक्रम्_अङ्कः_control_points_minus_1[a] = 1;
        s->gain_वक्रम्_use_pchip_नतिः_flag[a]       = 0;
        प्रति (पूर्णाङ्क c = 0; c < 2; c++) {
            s->gain_वक्रम्_control_points_x[a][c]     = 0x2000 + 0x10 * a + c;
            s->gain_वक्रम्_control_points_y[a][c]     = 0x3000 + 0x10 * a + c;
            s->gain_वक्रम्_control_points_theta[a][c] = 0x4000 + 0x10 * a + c;
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
    स्मृतिं_पूरय(s, 0, परिमाण(*s));
    s->application_संस्करणम्        = 1;
    s->has_adaptive_tone_map_flag = 1;
    s->baseline_hdr_headroom      = 0x0def;
    s->अङ्कः_alternate_images       = 3;
    s->gain_application_space_chromaticities_flag = 0;
    s->has_common_component_mix_params_flag = 1;
    s->has_common_वक्रम्_params_flag         = 1;
    प्रति (पूर्णाङ्क a = 0; a < 3; a++) {
        s->alternate_hdr_headrooms[a] = 0x0200 + a;
        s->component_mixing_type[a]   = 1;
        s->gain_वक्रम्_अङ्कः_control_points_minus_1[a] = 2;
        s->gain_वक्रम्_use_pchip_नतिः_flag[a]       = 1;
        प्रति (पूर्णाङ्क c = 0; c < 3; c++) {
            s->gain_वक्रम्_control_points_x[a][c] = 0x5000 + c;
            s->gain_वक्रम्_control_points_y[a][c] = 0x6000 + 0x10 * a + c;
        }
    }
}

स्थिर शून्य test_app5(शून्य)
{
    AVDynamicHDRSmpte2094App5 *app5, *app5_rt;
    AVFrame *frame;
    size_t आकार = 0, required = 0;
    uint8_t *buf = रिक्त;
    पूर्णाङ्क ret;

    प्रारूप_लिख("\n=== AVDynamicHDRSmpte2094App5 ===\n");
    प्रारूप_लिख("Testing av_dynamic_hdr_smpte2094_app5_alloc()\n");
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&आकार);
    प्रारूप_लिख("alloc: %s size>0=%s\n", app5 ? "OK" : "FAIL",
           आकार > 0 ? "yes" : "no");
    av_freep(&app5);

    प्रारूप_लिख("\nTesting av_dynamic_hdr_smpte2094_app5_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        app5 = av_dynamic_hdr_smpte2094_app5_create_side_दत्त(frame);
        प्रारूप_लिख("create_side_data: %s\n", app5 ? "OK" : "FAIL");
        av_frame_free(&frame);
    }

    app5    = av_dynamic_hdr_smpte2094_app5_alloc(रिक्त);
    app5_rt = av_dynamic_hdr_smpte2094_app5_alloc(रिक्त);
    यदि (!app5 || !app5_rt) {
        av_freep(&app5);
        av_freep(&app5_rt);
        प्रत्यागम;
    }
    fill_app5_अल्पिष्ठम्(app5);

    प्रारूप_लिख("\nTesting av_dynamic_hdr_smpte2094_app5_to_t35()\n");
    required = 0;
    ret = av_dynamic_hdr_smpte2094_app5_गन्तव्यम्_t35(app5, रिक्त, &required);
    प्रारूप_लिख("size query: ret=%d required>0=%s\n", ret,
           required > 0 ? "yes" : "no");

    buf  = रिक्त;
    आकार = 0;
    ret = av_dynamic_hdr_smpte2094_app5_गन्तव्यम्_t35(app5, &buf, &आकार);
    प्रारूप_लिख("alloc mode: ret=%d size_match=%s\n", ret,
           आकार == required ? "yes" : "no");
    av_freep(&buf);

    प्रारूप_लिख("\nTesting round trip, no adaptive tone map\n");
    ret = app5_आवर्तनम्_trip(app5, app5_rt);
    प्रारूप_लिख("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_app5("decoded", app5_rt);

    प्रारूप_लिख("\nTesting round trip, reference-white tone mapping\n");
    fill_app5_reference_white(app5);
    ret = app5_आवर्तनम्_trip(app5, app5_rt);
    प्रारूप_लिख("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_app5("decoded", app5_rt);

    प्रारूप_लिख("\nTesting round trip, per-image mixing and curve parameters\n");
    fill_app5_प्रत्येकम्_image(app5);
    ret = app5_आवर्तनम्_trip(app5, app5_rt);
    प्रारूप_लिख("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_app5("decoded", app5_rt);

    प्रारूप_लिख("\nTesting round trip, common mixing and curve parameters\n");
    fill_app5_common(app5);
    ret = app5_आवर्तनम्_trip(app5, app5_rt);
    प्रारूप_लिख("round trip: ret=%d\n", ret);
    यदि (ret >= 0)
        print_app5("decoded", app5_rt);

    प्रारूप_लिख("\nTesting error paths\n");
    buf  = रिक्त;
    आकार = 0;
    ret = av_dynamic_hdr_smpte2094_app5_गन्तव्यम्_t35(रिक्त, &buf, &आकार);
    प्रारूप_लिख("to_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    ret = av_dynamic_hdr_smpte2094_app5_from_t35(रिक्त, (ध्रुव uint8_t *)"", 0);
    प्रारूप_लिख("from_t35 NULL s: ret==AVERROR(EINVAL)=%s\n",
           ret == AVERROR(EINVAL) ? "yes" : "no");

    /* application_version does not fit the 3-bit field. */
    app5->application_संस्करणम् = 8;
    ret = av_dynamic_hdr_smpte2094_app5_गन्तव्यम्_t35(app5, रिक्त, &आकार);
    प्रारूप_लिख("to_t35 invalid application_version: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->application_संस्करणम् = 1;

    /* minimum_application_version above the documented maximum. */
    app5->minimum_application_संस्करणम् = 3;
    ret = av_dynamic_hdr_smpte2094_app5_गन्तव्यम्_t35(app5, रिक्त, &आकार);
    प्रारूप_लिख("to_t35 invalid minimum_application_version:"
           " ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");
    app5->minimum_application_संस्करणम् = 0;

    /* More alternate images than the 3-bit count admits. */
    app5->अङ्कः_alternate_images = 5;
    ret = av_dynamic_hdr_smpte2094_app5_गन्तव्यम्_t35(app5, रिक्त, &आकार);
    प्रारूप_लिख("to_t35 too many alternate images: ret==AVERROR_INVALIDDATA=%s\n",
           ret == AVERROR_INVALIDDATA ? "yes" : "no");

    av_freep(&app5);
    av_freep(&app5_rt);

    प्रारूप_लिख("\nTesting OOM path\n");
    av_max_alloc(1);
    app5 = av_dynamic_hdr_smpte2094_app5_alloc(&आकार);
    प्रारूप_लिख("alloc OOM: %s\n", app5 ? "FAIL" : "OK");
    av_max_alloc(अधिकतम_पूर्णाङ्कः);
    av_freep(&app5);
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    test_hdr_plus();
    test_app5();
    प्रत्यागम 0;
}

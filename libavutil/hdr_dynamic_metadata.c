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

#समावेश "avassert.h"
#समावेश "hdr_dynamic_metadata.h"
#समावेश "mem.h"
#समावेश "libavcodec/defs.h"
#समावेश "libavcodec/get_bits.h"
#समावेश "libavcodec/put_bits.h"

अटल स्थिर int64_t luminance_den = 1;
अटल स्थिर int32_t peak_luminance_den = 15;
अटल स्थिर int64_t rgb_den = 100000;
अटल स्थिर int32_t fraction_pixel_den = 1000;
अटल स्थिर int32_t knee_point_den = 4095;
अटल स्थिर int32_t bezier_anchor_den = 1023;
अटल स्थिर int32_t saturation_weight_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(माप_प्रकार *आकार)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(माप(AVDynamicHDRPlus));

    अगर (आकार)
        *आकार = hdr_plus ? माप(*hdr_plus) : 0;

    वापस hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_तथ्य(AVFrame *frame)
{
    AVFrame_Side_तथ्य *side_तथ्य = av_frame_new_side_तथ्य(frame,
                                                        AV_FRAME_तथ्य_DYNAMIC_HDR_PLUS,
                                                        माप(AVDynamicHDRPlus));
    अगर (!side_तथ्य)
        वापस शून्य;

    स_रखो(side_तथ्य->तथ्य, 0, माप(AVDynamicHDRPlus));

    वापस (AVDynamicHDRPlus *)side_तथ्य->तथ्य;
}

पूर्णांक av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, स्थिर uint8_t *तथ्य,
                                 माप_प्रकार आकार)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_आकार + AV_निवेश_बफर_PADDING_आकार];
    GetBitContext gbc, *gb = &gbc;
    पूर्णांक ret;

    अगर (!s)
        वापस AVERROR(EINVAL);

    अगर (आकार > AV_HDR_PLUS_MAX_PAYLOAD_आकार)
        वापस AVERROR(EINVAL);

    स_नकल(padded_buf, तथ्य, आकार);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    स_रखो(padded_buf + आकार, 0, AV_निवेश_बफर_PADDING_आकार);

    ret = init_get_bits8(gb, padded_buf, आकार);
    अगर (ret < 0)
        वापस ret;

    अगर (get_bits_बायाँ(gb) < 10)
        वापस AVERROR_INVALIDDATA;

    s->application_version = get_bits(gb, 8);
    s->अंक_windows = get_bits(gb, 2);

    अगर (s->अंक_windows < 1 || s->अंक_windows > 3) {
        वापस AVERROR_INVALIDDATA;
    }

    अगर (get_bits_बायाँ(gb) < ((19 * 8 + 1) * (s->अंक_windows - 1)))
        वापस AVERROR_INVALIDDATA;

    क्रम (पूर्णांक w = 1; w < s->अंक_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->window_upper_बायाँ_corner_x =
            (AVRational){get_bits(gb, 16), 1};
        params->window_upper_बायाँ_corner_y =
            (AVRational){get_bits(gb, 16), 1};
        params->window_lower_दायाँ_corner_x =
            (AVRational){get_bits(gb, 16), 1};
        params->window_lower_दायाँ_corner_y =
            (AVRational){get_bits(gb, 16), 1};

        params->center_of_ellipse_x = get_bits(gb, 16);
        params->center_of_ellipse_y = get_bits(gb, 16);
        params->rotation_angle = get_bits(gb, 8);
        params->semimajor_axis_internal_ellipse = get_bits(gb, 16);
        params->semimajor_axis_external_ellipse = get_bits(gb, 16);
        params->semiminor_axis_external_ellipse = get_bits(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    अगर (get_bits_बायाँ(gb) < 28)
        वापस AVERROR_INVALIDDATA;

    s->targeted_system_display_maximum_luminance =
        (AVRational){get_bits_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    अगर (s->targeted_system_display_actual_peak_luminance_flag) {
        पूर्णांक rows, cols;
        अगर (get_bits_बायाँ(gb) < 10)
            वापस AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        अगर (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            वापस AVERROR_INVALIDDATA;
        }
        s->अंक_rows_targeted_system_display_actual_peak_luminance = rows;
        s->अंक_cols_targeted_system_display_actual_peak_luminance = cols;

        अगर (get_bits_बायाँ(gb) < (rows * cols * 4))
            वापस AVERROR_INVALIDDATA;

        क्रम (पूर्णांक i = 0; i < rows; i++) {
            क्रम (पूर्णांक j = 0; j < cols; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }
    क्रम (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        अगर (get_bits_बायाँ(gb) < (3 * 17 + 17 + 4))
            वापस AVERROR_INVALIDDATA;

        क्रम (पूर्णांक i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_bits(gb, 17), rgb_den};
        }
        params->average_maxrgb =
            (AVRational){get_bits(gb, 17), rgb_den};
        params->अंक_distribution_maxrgb_percentiles = get_bits(gb, 4);

        अगर (get_bits_बायाँ(gb) <
            (params->अंक_distribution_maxrgb_percentiles * 24))
            वापस AVERROR_INVALIDDATA;

        क्रम (पूर्णांक i = 0; i < params->अंक_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_bits(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_bits(gb, 17), rgb_den};
        }

        अगर (get_bits_बायाँ(gb) < 10)
            वापस AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_bits(gb, 10), fraction_pixel_den};
    }
    अगर (get_bits_बायाँ(gb) < 1)
        वापस AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    अगर (s->mastering_display_actual_peak_luminance_flag) {
        पूर्णांक rows, cols;
        अगर (get_bits_बायाँ(gb) < 10)
            वापस AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        अगर (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            वापस AVERROR_INVALIDDATA;
        }
        s->अंक_rows_mastering_display_actual_peak_luminance = rows;
        s->अंक_cols_mastering_display_actual_peak_luminance = cols;

        अगर (get_bits_बायाँ(gb) < (rows * cols * 4))
            वापस AVERROR_INVALIDDATA;

        क्रम (पूर्णांक i = 0; i < rows; i++) {
            क्रम (पूर्णांक j = 0; j < cols; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }

    क्रम (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        अगर (get_bits_बायाँ(gb) < 1)
            वापस AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        अगर (params->tone_mapping_flag) {
            अगर (get_bits_बायाँ(gb) < 28)
                वापस AVERROR_INVALIDDATA;

            params->knee_point_x =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->knee_point_y =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->अंक_bezier_curve_anchors = get_bits(gb, 4);

            अगर (get_bits_बायाँ(gb) < (params->अंक_bezier_curve_anchors * 10))
                वापस AVERROR_INVALIDDATA;

            क्रम (पूर्णांक i = 0; i < params->अंक_bezier_curve_anchors; i++) {
                params->bezier_curve_anchors[i] =
                    (AVRational){get_bits(gb, 10), bezier_anchor_den};
            }
        }

        अगर (get_bits_बायाँ(gb) < 1)
            वापस AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        अगर (params->color_saturation_mapping_flag) {
            अगर (get_bits_बायाँ(gb) < 6)
                वापस AVERROR_INVALIDDATA;
            params->color_saturation_weight =
                (AVRational){get_bits(gb, 6), saturation_weight_den};
        }
    }

    वापस 0;
}

पूर्णांक av_dynamic_hdr_plus_to_t35(स्थिर AVDynamicHDRPlus *s, uint8_t **तथ्य, माप_प्रकार *आकार)
{
    uint8_t *buf;
    माप_प्रकार आकार_bits, आकार_bytes;
    PutBitContext pbc, *pb = &pbc;

    अगर (!s)
        वापस AVERROR(EINVAL);
    अगर ((!तथ्य || *तथ्य) && !आकार)
       वापस AVERROR(EINVAL);

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
    आकार_bits = 8;

    आकार_bits += 2;

    क्रम (पूर्णांक w = 1; w < s->अंक_windows; w++)
        आकार_bits += 153;

    आकार_bits += 27;

    आकार_bits += 1;
    अगर (s->targeted_system_display_actual_peak_luminance_flag)
        आकार_bits += 10 +
                     s->अंक_rows_targeted_system_display_actual_peak_luminance *
                     s->अंक_cols_targeted_system_display_actual_peak_luminance * 4;

    क्रम (पूर्णांक w = 0; w < s->अंक_windows; w++)
        आकार_bits += 72 + s->params[w].अंक_distribution_maxrgb_percentiles * 24 + 10;

    आकार_bits += 1;
    अगर (s->mastering_display_actual_peak_luminance_flag)
        आकार_bits += 10 +
                     s->अंक_rows_mastering_display_actual_peak_luminance *
                     s->अंक_cols_mastering_display_actual_peak_luminance * 4;

    क्रम (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        आकार_bits += 1;
        अगर (s->params[w].tone_mapping_flag)
            आकार_bits += 28 + s->params[w].अंक_bezier_curve_anchors * 10;

        आकार_bits += 1;
        अगर (s->params[w].color_saturation_mapping_flag)
            आकार_bits += 6;
    }

    आकार_bytes = (आकार_bits + 7) / 8;

    av_assert0(आकार_bytes <= AV_HDR_PLUS_MAX_PAYLOAD_आकार);

    अगर (!तथ्य) {
        *आकार = आकार_bytes;
        वापस 0;
    } अन्यथा अगर (*तथ्य) {
        अगर (*आकार < आकार_bytes)
            वापस AVERROR_बफर_TOO_SMALL;
        buf = *तथ्य;
    } अन्यथा {
        buf = av_malloc(आकार_bytes);
        अगर (!buf)
            वापस AVERROR(ENOMEM);
    }

    init_put_bits(pb, buf, आकार_bytes);

    // application_mode is set to Application Version 1
    put_bits(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_bits(pb, 2, s->अंक_windows);

    क्रम (पूर्णांक w = 1; w < s->अंक_windows; w++) {
        put_bits(pb, 16, s->params[w].window_upper_बायाँ_corner_x.अंक / s->params[w].window_upper_बायाँ_corner_x.den);
        put_bits(pb, 16, s->params[w].window_upper_बायाँ_corner_y.अंक / s->params[w].window_upper_बायाँ_corner_y.den);
        put_bits(pb, 16, s->params[w].window_lower_दायाँ_corner_x.अंक / s->params[w].window_lower_दायाँ_corner_x.den);
        put_bits(pb, 16, s->params[w].window_lower_दायाँ_corner_y.अंक / s->params[w].window_lower_दायाँ_corner_y.den);
        put_bits(pb, 16, s->params[w].center_of_ellipse_x);
        put_bits(pb, 16, s->params[w].center_of_ellipse_y);
        put_bits(pb, 8, s->params[w].rotation_angle);
        put_bits(pb, 16, s->params[w].semimajor_axis_internal_ellipse);
        put_bits(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_bits(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_bits(pb, 1, s->params[w].overlap_process_option);
    }

    put_bits(pb, 27, s->targeted_system_display_maximum_luminance.अंक * luminance_den /
        s->targeted_system_display_maximum_luminance.den);
    put_bits(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    अगर (s->targeted_system_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->अंक_rows_targeted_system_display_actual_peak_luminance);
        put_bits(pb, 5, s->अंक_cols_targeted_system_display_actual_peak_luminance);
        क्रम (पूर्णांक i = 0; i < s->अंक_rows_targeted_system_display_actual_peak_luminance; i++) {
            क्रम (पूर्णांक j = 0; j < s->अंक_cols_targeted_system_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].अंक * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    क्रम (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        क्रम (पूर्णांक i = 0; i < 3; i++)
            put_bits(pb, 17, s->params[w].maxscl[i].अंक * rgb_den / s->params[w].maxscl[i].den);
        put_bits(pb, 17, s->params[w].average_maxrgb.अंक * rgb_den / s->params[w].average_maxrgb.den);
        put_bits(pb, 4, s->params[w].अंक_distribution_maxrgb_percentiles);
        क्रम (पूर्णांक i = 0; i < s->params[w].अंक_distribution_maxrgb_percentiles; i++) {
            put_bits(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_bits(pb, 17, s->params[w].distribution_maxrgb[i].percentile.अंक * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_bits(pb, 10, s->params[w].fraction_bright_pixels.अंक * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_bits(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    अगर (s->mastering_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->अंक_rows_mastering_display_actual_peak_luminance);
        put_bits(pb, 5, s->अंक_cols_mastering_display_actual_peak_luminance);
        क्रम (पूर्णांक i = 0; i < s->अंक_rows_mastering_display_actual_peak_luminance; i++) {
            क्रम (पूर्णांक j = 0; j < s->अंक_cols_mastering_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->mastering_display_actual_peak_luminance[i][j].अंक * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    क्रम (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        put_bits(pb, 1, s->params[w].tone_mapping_flag);
        अगर (s->params[w].tone_mapping_flag) {
            put_bits(pb, 12, s->params[w].knee_point_x.अंक * knee_point_den / s->params[w].knee_point_x.den);
            put_bits(pb, 12, s->params[w].knee_point_y.अंक * knee_point_den / s->params[w].knee_point_y.den);
            put_bits(pb, 4, s->params[w].अंक_bezier_curve_anchors);
            क्रम (पूर्णांक i = 0; i < s->params[w].अंक_bezier_curve_anchors; i++)
                put_bits(pb, 10, s->params[w].bezier_curve_anchors[i].अंक * bezier_anchor_den /
                    s->params[w].bezier_curve_anchors[i].den);
        }
        put_bits(pb, 1, s->params[w].color_saturation_mapping_flag);
        अगर (s->params[w].color_saturation_mapping_flag)
            put_bits(pb, 6, s->params[w].color_saturation_weight.अंक * saturation_weight_den /
                s->params[w].color_saturation_weight.den);
    }

    flush_put_bits(pb);

    *तथ्य = buf;
    अगर (आकार)
        *आकार = आकार_bytes;
    वापस 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(माप_प्रकार *आकार)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(माप(AVDynamicHDRSmpte2094App5));

    अगर (आकार)
        *आकार = smpte2094_app5 ? माप(*smpte2094_app5) : 0;

    वापस smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_तथ्य(AVFrame *frame)
{
    AVFrame_Side_तथ्य *side_तथ्य = av_frame_new_side_तथ्य(frame,
                                                        AV_FRAME_तथ्य_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        माप(AVDynamicHDRSmpte2094App5));
    अगर (!side_तथ्य)
        वापस शून्य;

    स_रखो(side_तथ्य->तथ्य, 0, माप(AVDynamicHDRSmpte2094App5));

    वापस (AVDynamicHDRSmpte2094App5 *)side_तथ्य->तथ्य;
}

#घोषणा GET_BITS_OR_FAIL(var, n)        \
    करो {                                \
        अगर (get_bits_बायाँ(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            जाओ end;                   \
        }                               \
        var = get_bits(gb, n);          \
    } जबतक (0)

पूर्णांक av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, स्थिर uint8_t *तथ्य,
                                           माप_प्रकार आकार)
{
    GetBitContext gbc, *gb = &gbc;
    पूर्णांक ret, reserved_zero;
    माप_प्रकार padded_आकार = आकार + AV_निवेश_बफर_PADDING_आकार;

    अगर (!s)
        वापस AVERROR(EINVAL);

    uint8_t *padded_तथ्य = av_mallocz(padded_आकार);
    अगर (!padded_तथ्य)
        वापस AVERROR(ENOMEM);

    स_नकल(padded_तथ्य, तथ्य, आकार);
    ret = init_get_bits8(gb, padded_तथ्य, आकार);
    अगर (ret < 0)
        जाओ end;

    // Table C.1
    GET_BITS_OR_FAIL(s->application_version, 3);
    GET_BITS_OR_FAIL(s->minimum_application_version, 3);
    GET_BITS_OR_FAIL(reserved_zero, 2);
    अगर (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        जाओ end;
    }

    // Table C.2
    GET_BITS_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_BITS_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_BITS_OR_FAIL(reserved_zero, 6);
    अगर (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        जाओ end;
    }
    अगर (s->has_custom_hdr_reference_white_flag)
        GET_BITS_OR_FAIL(s->hdr_reference_white, 16);
    अगर (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        जाओ end;
    }

    // Table C.3
    GET_BITS_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_BITS_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    अगर (s->use_reference_white_tone_mapping_flag) {
        GET_BITS_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        जाओ end;
    }
    GET_BITS_OR_FAIL(s->अंक_alternate_images, 3);
    अगर (s->अंक_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        जाओ end;
    }
    GET_BITS_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_BITS_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_BITS_OR_FAIL(s->has_common_curve_params_flag, 1);
    अगर (s->gain_application_space_chromaticities_flag == 3)
        क्रम (पूर्णांक r = 0; r < 8; r++)
            GET_BITS_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    क्रम (पूर्णांक a = 0; a < s->अंक_alternate_images; a++) {
        GET_BITS_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        अगर (!a || !s->has_common_component_mix_params_flag) {
            GET_BITS_OR_FAIL(s->component_mixing_type[a], 2);
            अगर (s->component_mixing_type[a] != 3) {
                GET_BITS_OR_FAIL(reserved_zero, 6);
                अगर (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    जाओ end;
                }
            } अन्यथा {
                क्रम (पूर्णांक k = 0; k < 6; k++)
                    GET_BITS_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                क्रम (पूर्णांक k = 0; k < 6; k++) {
                    अगर (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_BITS_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } अन्यथा {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } अन्यथा {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            अगर (s->component_mixing_type[a] == 3) {
                क्रम (पूर्णांक k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        अगर (!a || !s->has_common_curve_params_flag) {
            GET_BITS_OR_FAIL(s->gain_curve_अंक_control_points_minus_1[a], 5);
            अगर (s->gain_curve_अंक_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                जाओ end;
            }
            GET_BITS_OR_FAIL(s->gain_curve_use_pchip_slope_flag[a], 1);
            GET_BITS_OR_FAIL(reserved_zero, 2);
            अगर (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                जाओ end;
            }
            क्रम (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++) {
                GET_BITS_OR_FAIL(s->gain_curve_control_points_x[a][c], 16);
            }
        } अन्यथा {
            s->gain_curve_अंक_control_points_minus_1[a] =
                    s->gain_curve_अंक_control_points_minus_1[0];
            s->gain_curve_use_pchip_slope_flag[a] = s->gain_curve_use_pchip_slope_flag[0];
            क्रम (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++) {
                s->gain_curve_control_points_x[a][c] = s->gain_curve_control_points_x[0][c];
            }
        }
        क्रम (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
            GET_BITS_OR_FAIL(s->gain_curve_control_points_y[a][c], 16);
        अगर (!s->gain_curve_use_pchip_slope_flag[a]) {
            क्रम (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
                GET_BITS_OR_FAIL(s->gain_curve_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
end:
    av_free(padded_तथ्य);
    वापस ret;
}

पूर्णांक av_dynamic_hdr_smpte2094_app5_to_t35(स्थिर AVDynamicHDRSmpte2094App5 *s, uint8_t **तथ्य,
                                         माप_प्रकार *आकार)
{
    uint8_t *buf;
    माप_प्रकार आकार_bytes, आकार_bits;
    PutBitContext pbc, *pb = &pbc;

    अगर (!s)
        वापस AVERROR(EINVAL);
    अगर ((!तथ्य || *तथ्य) && !आकार)
       वापस AVERROR(EINVAL);

    अगर (s->application_version >= 8 || s->minimum_application_version >= 3)
        वापस AVERROR_INVALIDDATA;
    आकार_bits = 0;
    आकार_bits += 3 + 3 + 2;
    आकार_bits += 1 + 1 + 6;
    अगर (s->has_custom_hdr_reference_white_flag)
        आकार_bits += 16;
    अगर (s->has_adaptive_tone_map_flag) {
        आकार_bits += 16 + 1;
        अगर (s->use_reference_white_tone_mapping_flag) {
            आकार_bits += 7;
        } अन्यथा {
            आकार_bits += 3 + 2 + 1 + 1;
            अगर (s->gain_application_space_chromaticities_flag == 3)
                आकार_bits += 16 * 8;
            अगर (s->अंक_alternate_images > 4)
                वापस AVERROR_INVALIDDATA;
            क्रम (पूर्णांक a = 0; a < s->अंक_alternate_images; a++) {
                आकार_bits += 16;
                अगर (!a || !s->has_common_component_mix_params_flag) {
                    आकार_bits += 2;
                    अगर (s->component_mixing_type[a] != 3) {
                        आकार_bits += 6;
                    } अन्यथा {
                        आकार_bits += 6;
                        क्रम (पूर्णांक k = 0; k < 6; k++)
                          अगर (s->has_component_mixing_coefficient_flag[a][k])
                            आकार_bits += 16;
                    }
                }
                अगर (!a || !s->has_common_curve_params_flag) {
                    आकार_bits += 5 + 1 + 2;
                    अगर (s->gain_curve_अंक_control_points_minus_1[a] > 31)
                        वापस AVERROR_INVALIDDATA;
                    आकार_bits += 16 * (s->gain_curve_अंक_control_points_minus_1[a] + 1);
                }
                आकार_bits += 16 * (s->gain_curve_अंक_control_points_minus_1[a] + 1);
                अगर (!s->gain_curve_use_pchip_slope_flag[a])
                    आकार_bits += 16 * (s->gain_curve_अंक_control_points_minus_1[a] + 1);
            }
        }
    }
    अगर (आकार_bits % 8)
      वापस AVERROR_INVALIDDATA;
    आकार_bytes = आकार_bits >> 3;

    अगर (!तथ्य) {
        *आकार = आकार_bytes;
        वापस 0;
    } अन्यथा अगर (*तथ्य) {
        अगर (*आकार < आकार_bytes)
            वापस AVERROR_बफर_TOO_SMALL;
        buf = *तथ्य;
    } अन्यथा {
        buf = av_malloc(आकार_bytes);
        अगर (!buf)
            वापस AVERROR(ENOMEM);
    }

    init_put_bits(pb, buf, आकार_bytes);

    // Table C.1
    put_bits(pb, 3, s->application_version);
    put_bits(pb, 3, s->minimum_application_version);
    put_bits(pb, 2, 0); // reserved_zero

    // Table C.2
    put_bits(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_bits(pb, 1, s->has_adaptive_tone_map_flag);
    put_bits(pb, 6, 0); // reserved_zero

    अगर (s->has_custom_hdr_reference_white_flag)
        put_bits(pb, 16, s->hdr_reference_white);

    अगर (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_bits(pb, 16, s->baseline_hdr_headroom);
        put_bits(pb, 1, s->use_reference_white_tone_mapping_flag);
        अगर (s->use_reference_white_tone_mapping_flag) {
            put_bits(pb, 7, 0); // reserved_zero
        } अन्यथा {
            put_bits(pb, 3, s->अंक_alternate_images);
            put_bits(pb, 2, s->gain_application_space_chromaticities_flag);
            put_bits(pb, 1, s->has_common_component_mix_params_flag);
            put_bits(pb, 1, s->has_common_curve_params_flag);

            अगर (s->gain_application_space_chromaticities_flag == 3)
                क्रम (पूर्णांक r = 0; r < 8; r++)
                    put_bits(pb, 16, s->gain_application_space_chromaticities[r]);

            क्रम (पूर्णांक a = 0; a < s->अंक_alternate_images; a++) {
                put_bits(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                अगर (!a || !s->has_common_component_mix_params_flag) {
                    put_bits(pb, 2, s->component_mixing_type[a]);
                    अगर (s->component_mixing_type[a] != 3) {
                        put_bits(pb, 6, 0); // reserved_zero
                    } अन्यथा {
                        क्रम (पूर्णांक k = 0; k < 6; k++)
                            put_bits(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        क्रम (पूर्णांक k = 0; k < 6; k++)
                            अगर (s->has_component_mixing_coefficient_flag[a][k])
                                put_bits(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                अगर (!a || !s->has_common_curve_params_flag) {
                    put_bits(pb, 5, s->gain_curve_अंक_control_points_minus_1[a]);
                    put_bits(pb, 1, s->gain_curve_use_pchip_slope_flag[a]);
                    put_bits(pb, 2, 0); // reserved_zero
                    क्रम (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_x[a][c]);
                }
                क्रम (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
                    put_bits(pb, 16, s->gain_curve_control_points_y[a][c]);
                अगर (!s->gain_curve_use_pchip_slope_flag[a]) {
                    क्रम (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_bits(pb);

    *तथ्य = buf;
    अगर (आकार)
        *आकार = आकार_bytes;
    वापस 0;
}

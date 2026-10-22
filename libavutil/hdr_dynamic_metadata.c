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

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "hdr_dynamic_metadata.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "libavcodec/defs.h"
#अन्तर्भाव "libavcodec/get_bits.h"
#अन्तर्भाव "libavcodec/put_bits.h"

स्थिर स्थिरांक int64_t luminance_den = 1;
स्थिर स्थिरांक int32_t peak_luminance_den = 15;
स्थिर स्थिरांक int64_t rgb_den = 100000;
स्थिर स्थिरांक int32_t fraction_pixel_den = 1000;
स्थिर स्थिरांक int32_t knee_point_den = 4095;
स्थिर स्थिरांक int32_t bezier_anchor_den = 1023;
स्थिर स्थिरांक int32_t saturation_weight_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(माप_प्रकार *size)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(आकार(AVDynamicHDRPlus));

    जर (size)
        *size = hdr_plus ? आकार(*hdr_plus) : 0;

    परत hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_DYNAMIC_HDR_PLUS,
                                                        आकार(AVDynamicHDRPlus));
    जर (!side_data)
        परत रिक्त;

    स_रखो(side_data->data, 0, आकार(AVDynamicHDRPlus));

    परत (AVDynamicHDRPlus *)side_data->data;
}

पूर्णांक av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, स्थिरांक uint8_t *data,
                                 माप_प्रकार size)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_SIZE + AV_आदान_BUFFER_PADDING_SIZE];
    GetBitContext gbc, *gb = &gbc;
    पूर्णांक ret;

    जर (!s)
        परत AVERROR(EINVAL);

    जर (size > AV_HDR_PLUS_MAX_PAYLOAD_SIZE)
        परत AVERROR(EINVAL);

    स_नकल(padded_buf, data, size);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    स_रखो(padded_buf + size, 0, AV_आदान_BUFFER_PADDING_SIZE);

    ret = init_get_bits8(gb, padded_buf, size);
    जर (ret < 0)
        परत ret;

    जर (get_bits_डावा(gb) < 10)
        परत AVERROR_INVALIDDATA;

    s->application_version = get_bits(gb, 8);
    s->अंक_windows = get_bits(gb, 2);

    जर (s->अंक_windows < 1 || s->अंक_windows > 3) {
        परत AVERROR_INVALIDDATA;
    }

    जर (get_bits_डावा(gb) < ((19 * 8 + 1) * (s->अंक_windows - 1)))
        परत AVERROR_INVALIDDATA;

    साठी (पूर्णांक w = 1; w < s->अंक_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->window_upper_डावा_corner_x =
            (AVRational){get_bits(gb, 16), 1};
        params->window_upper_डावा_corner_y =
            (AVRational){get_bits(gb, 16), 1};
        params->window_lower_उजवा_corner_x =
            (AVRational){get_bits(gb, 16), 1};
        params->window_lower_उजवा_corner_y =
            (AVRational){get_bits(gb, 16), 1};

        params->center_of_ellipse_x = get_bits(gb, 16);
        params->center_of_ellipse_y = get_bits(gb, 16);
        params->rotation_angle = get_bits(gb, 8);
        params->semimajor_axis_internal_ellipse = get_bits(gb, 16);
        params->semimajor_axis_external_ellipse = get_bits(gb, 16);
        params->semiminor_axis_external_ellipse = get_bits(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    जर (get_bits_डावा(gb) < 28)
        परत AVERROR_INVALIDDATA;

    s->targeted_system_display_maximum_luminance =
        (AVRational){get_bits_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    जर (s->targeted_system_display_actual_peak_luminance_flag) {
        पूर्णांक rows, cols;
        जर (get_bits_डावा(gb) < 10)
            परत AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        जर (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            परत AVERROR_INVALIDDATA;
        }
        s->अंक_rows_targeted_system_display_actual_peak_luminance = rows;
        s->अंक_cols_targeted_system_display_actual_peak_luminance = cols;

        जर (get_bits_डावा(gb) < (rows * cols * 4))
            परत AVERROR_INVALIDDATA;

        साठी (पूर्णांक i = 0; i < rows; i++) {
            साठी (पूर्णांक j = 0; j < cols; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }
    साठी (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        जर (get_bits_डावा(gb) < (3 * 17 + 17 + 4))
            परत AVERROR_INVALIDDATA;

        साठी (पूर्णांक i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_bits(gb, 17), rgb_den};
        }
        params->average_maxrgb =
            (AVRational){get_bits(gb, 17), rgb_den};
        params->अंक_distribution_maxrgb_percentiles = get_bits(gb, 4);

        जर (get_bits_डावा(gb) <
            (params->अंक_distribution_maxrgb_percentiles * 24))
            परत AVERROR_INVALIDDATA;

        साठी (पूर्णांक i = 0; i < params->अंक_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_bits(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_bits(gb, 17), rgb_den};
        }

        जर (get_bits_डावा(gb) < 10)
            परत AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_bits(gb, 10), fraction_pixel_den};
    }
    जर (get_bits_डावा(gb) < 1)
        परत AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    जर (s->mastering_display_actual_peak_luminance_flag) {
        पूर्णांक rows, cols;
        जर (get_bits_डावा(gb) < 10)
            परत AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        जर (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            परत AVERROR_INVALIDDATA;
        }
        s->अंक_rows_mastering_display_actual_peak_luminance = rows;
        s->अंक_cols_mastering_display_actual_peak_luminance = cols;

        जर (get_bits_डावा(gb) < (rows * cols * 4))
            परत AVERROR_INVALIDDATA;

        साठी (पूर्णांक i = 0; i < rows; i++) {
            साठी (पूर्णांक j = 0; j < cols; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }

    साठी (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        जर (get_bits_डावा(gb) < 1)
            परत AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        जर (params->tone_mapping_flag) {
            जर (get_bits_डावा(gb) < 28)
                परत AVERROR_INVALIDDATA;

            params->knee_point_x =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->knee_point_y =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->अंक_bezier_curve_anchors = get_bits(gb, 4);

            जर (get_bits_डावा(gb) < (params->अंक_bezier_curve_anchors * 10))
                परत AVERROR_INVALIDDATA;

            साठी (पूर्णांक i = 0; i < params->अंक_bezier_curve_anchors; i++) {
                params->bezier_curve_anchors[i] =
                    (AVRational){get_bits(gb, 10), bezier_anchor_den};
            }
        }

        जर (get_bits_डावा(gb) < 1)
            परत AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        जर (params->color_saturation_mapping_flag) {
            जर (get_bits_डावा(gb) < 6)
                परत AVERROR_INVALIDDATA;
            params->color_saturation_weight =
                (AVRational){get_bits(gb, 6), saturation_weight_den};
        }
    }

    परत 0;
}

पूर्णांक av_dynamic_hdr_plus_to_t35(स्थिरांक AVDynamicHDRPlus *s, uint8_t **data, माप_प्रकार *size)
{
    uint8_t *buf;
    माप_प्रकार size_bits, size_bytes;
    PutBitContext pbc, *pb = &pbc;

    जर (!s)
        परत AVERROR(EINVAL);
    जर ((!data || *data) && !size)
       परत AVERROR(EINVAL);

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
    size_bits = 8;

    size_bits += 2;

    साठी (पूर्णांक w = 1; w < s->अंक_windows; w++)
        size_bits += 153;

    size_bits += 27;

    size_bits += 1;
    जर (s->targeted_system_display_actual_peak_luminance_flag)
        size_bits += 10 +
                     s->अंक_rows_targeted_system_display_actual_peak_luminance *
                     s->अंक_cols_targeted_system_display_actual_peak_luminance * 4;

    साठी (पूर्णांक w = 0; w < s->अंक_windows; w++)
        size_bits += 72 + s->params[w].अंक_distribution_maxrgb_percentiles * 24 + 10;

    size_bits += 1;
    जर (s->mastering_display_actual_peak_luminance_flag)
        size_bits += 10 +
                     s->अंक_rows_mastering_display_actual_peak_luminance *
                     s->अंक_cols_mastering_display_actual_peak_luminance * 4;

    साठी (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        size_bits += 1;
        जर (s->params[w].tone_mapping_flag)
            size_bits += 28 + s->params[w].अंक_bezier_curve_anchors * 10;

        size_bits += 1;
        जर (s->params[w].color_saturation_mapping_flag)
            size_bits += 6;
    }

    size_bytes = (size_bits + 7) / 8;

    av_assert0(size_bytes <= AV_HDR_PLUS_MAX_PAYLOAD_SIZE);

    जर (!data) {
        *size = size_bytes;
        परत 0;
    } अन्यथा जर (*data) {
        जर (*size < size_bytes)
            परत AVERROR_BUFFER_TOO_SMALL;
        buf = *data;
    } अन्यथा {
        buf = av_malloc(size_bytes);
        जर (!buf)
            परत AVERROR(ENOMEM);
    }

    init_put_bits(pb, buf, size_bytes);

    // application_mode is set to Application Version 1
    put_bits(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_bits(pb, 2, s->अंक_windows);

    साठी (पूर्णांक w = 1; w < s->अंक_windows; w++) {
        put_bits(pb, 16, s->params[w].window_upper_डावा_corner_x.अंक / s->params[w].window_upper_डावा_corner_x.den);
        put_bits(pb, 16, s->params[w].window_upper_डावा_corner_y.अंक / s->params[w].window_upper_डावा_corner_y.den);
        put_bits(pb, 16, s->params[w].window_lower_उजवा_corner_x.अंक / s->params[w].window_lower_उजवा_corner_x.den);
        put_bits(pb, 16, s->params[w].window_lower_उजवा_corner_y.अंक / s->params[w].window_lower_उजवा_corner_y.den);
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
    जर (s->targeted_system_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->अंक_rows_targeted_system_display_actual_peak_luminance);
        put_bits(pb, 5, s->अंक_cols_targeted_system_display_actual_peak_luminance);
        साठी (पूर्णांक i = 0; i < s->अंक_rows_targeted_system_display_actual_peak_luminance; i++) {
            साठी (पूर्णांक j = 0; j < s->अंक_cols_targeted_system_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].अंक * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    साठी (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        साठी (पूर्णांक i = 0; i < 3; i++)
            put_bits(pb, 17, s->params[w].maxscl[i].अंक * rgb_den / s->params[w].maxscl[i].den);
        put_bits(pb, 17, s->params[w].average_maxrgb.अंक * rgb_den / s->params[w].average_maxrgb.den);
        put_bits(pb, 4, s->params[w].अंक_distribution_maxrgb_percentiles);
        साठी (पूर्णांक i = 0; i < s->params[w].अंक_distribution_maxrgb_percentiles; i++) {
            put_bits(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_bits(pb, 17, s->params[w].distribution_maxrgb[i].percentile.अंक * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_bits(pb, 10, s->params[w].fraction_bright_pixels.अंक * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_bits(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    जर (s->mastering_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->अंक_rows_mastering_display_actual_peak_luminance);
        put_bits(pb, 5, s->अंक_cols_mastering_display_actual_peak_luminance);
        साठी (पूर्णांक i = 0; i < s->अंक_rows_mastering_display_actual_peak_luminance; i++) {
            साठी (पूर्णांक j = 0; j < s->अंक_cols_mastering_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->mastering_display_actual_peak_luminance[i][j].अंक * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    साठी (पूर्णांक w = 0; w < s->अंक_windows; w++) {
        put_bits(pb, 1, s->params[w].tone_mapping_flag);
        जर (s->params[w].tone_mapping_flag) {
            put_bits(pb, 12, s->params[w].knee_point_x.अंक * knee_point_den / s->params[w].knee_point_x.den);
            put_bits(pb, 12, s->params[w].knee_point_y.अंक * knee_point_den / s->params[w].knee_point_y.den);
            put_bits(pb, 4, s->params[w].अंक_bezier_curve_anchors);
            साठी (पूर्णांक i = 0; i < s->params[w].अंक_bezier_curve_anchors; i++)
                put_bits(pb, 10, s->params[w].bezier_curve_anchors[i].अंक * bezier_anchor_den /
                    s->params[w].bezier_curve_anchors[i].den);
        }
        put_bits(pb, 1, s->params[w].color_saturation_mapping_flag);
        जर (s->params[w].color_saturation_mapping_flag)
            put_bits(pb, 6, s->params[w].color_saturation_weight.अंक * saturation_weight_den /
                s->params[w].color_saturation_weight.den);
    }

    flush_put_bits(pb);

    *data = buf;
    जर (size)
        *size = size_bytes;
    परत 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(माप_प्रकार *size)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(आकार(AVDynamicHDRSmpte2094App5));

    जर (size)
        *size = smpte2094_app5 ? आकार(*smpte2094_app5) : 0;

    परत smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        आकार(AVDynamicHDRSmpte2094App5));
    जर (!side_data)
        परत रिक्त;

    स_रखो(side_data->data, 0, आकार(AVDynamicHDRSmpte2094App5));

    परत (AVDynamicHDRSmpte2094App5 *)side_data->data;
}

#define GET_BITS_OR_FAIL(var, n)        \
    करा {                                \
        जर (get_bits_डावा(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            जा end;                   \
        }                               \
        var = get_bits(gb, n);          \
    } पर्यंत (0)

पूर्णांक av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, स्थिरांक uint8_t *data,
                                           माप_प्रकार size)
{
    GetBitContext gbc, *gb = &gbc;
    पूर्णांक ret, reserved_zero;
    माप_प्रकार padded_size = size + AV_आदान_BUFFER_PADDING_SIZE;

    जर (!s)
        परत AVERROR(EINVAL);

    uint8_t *padded_data = av_mallocz(padded_size);
    जर (!padded_data)
        परत AVERROR(ENOMEM);

    स_नकल(padded_data, data, size);
    ret = init_get_bits8(gb, padded_data, size);
    जर (ret < 0)
        जा end;

    // Table C.1
    GET_BITS_OR_FAIL(s->application_version, 3);
    GET_BITS_OR_FAIL(s->minimum_application_version, 3);
    GET_BITS_OR_FAIL(reserved_zero, 2);
    जर (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        जा end;
    }

    // Table C.2
    GET_BITS_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_BITS_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_BITS_OR_FAIL(reserved_zero, 6);
    जर (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        जा end;
    }
    जर (s->has_custom_hdr_reference_white_flag)
        GET_BITS_OR_FAIL(s->hdr_reference_white, 16);
    जर (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        जा end;
    }

    // Table C.3
    GET_BITS_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_BITS_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    जर (s->use_reference_white_tone_mapping_flag) {
        GET_BITS_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        जा end;
    }
    GET_BITS_OR_FAIL(s->अंक_alternate_images, 3);
    जर (s->अंक_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        जा end;
    }
    GET_BITS_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_BITS_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_BITS_OR_FAIL(s->has_common_curve_params_flag, 1);
    जर (s->gain_application_space_chromaticities_flag == 3)
        साठी (पूर्णांक r = 0; r < 8; r++)
            GET_BITS_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    साठी (पूर्णांक a = 0; a < s->अंक_alternate_images; a++) {
        GET_BITS_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        जर (!a || !s->has_common_component_mix_params_flag) {
            GET_BITS_OR_FAIL(s->component_mixing_type[a], 2);
            जर (s->component_mixing_type[a] != 3) {
                GET_BITS_OR_FAIL(reserved_zero, 6);
                जर (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    जा end;
                }
            } अन्यथा {
                साठी (पूर्णांक k = 0; k < 6; k++)
                    GET_BITS_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                साठी (पूर्णांक k = 0; k < 6; k++) {
                    जर (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_BITS_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } अन्यथा {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } अन्यथा {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            जर (s->component_mixing_type[a] == 3) {
                साठी (पूर्णांक k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        जर (!a || !s->has_common_curve_params_flag) {
            GET_BITS_OR_FAIL(s->gain_curve_अंक_control_points_minus_1[a], 5);
            जर (s->gain_curve_अंक_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                जा end;
            }
            GET_BITS_OR_FAIL(s->gain_curve_use_pchip_slope_flag[a], 1);
            GET_BITS_OR_FAIL(reserved_zero, 2);
            जर (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                जा end;
            }
            साठी (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++) {
                GET_BITS_OR_FAIL(s->gain_curve_control_points_x[a][c], 16);
            }
        } अन्यथा {
            s->gain_curve_अंक_control_points_minus_1[a] =
                    s->gain_curve_अंक_control_points_minus_1[0];
            s->gain_curve_use_pchip_slope_flag[a] = s->gain_curve_use_pchip_slope_flag[0];
            साठी (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++) {
                s->gain_curve_control_points_x[a][c] = s->gain_curve_control_points_x[0][c];
            }
        }
        साठी (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
            GET_BITS_OR_FAIL(s->gain_curve_control_points_y[a][c], 16);
        जर (!s->gain_curve_use_pchip_slope_flag[a]) {
            साठी (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
                GET_BITS_OR_FAIL(s->gain_curve_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
end:
    av_free(padded_data);
    परत ret;
}

पूर्णांक av_dynamic_hdr_smpte2094_app5_to_t35(स्थिरांक AVDynamicHDRSmpte2094App5 *s, uint8_t **data,
                                         माप_प्रकार *size)
{
    uint8_t *buf;
    माप_प्रकार size_bytes, size_bits;
    PutBitContext pbc, *pb = &pbc;

    जर (!s)
        परत AVERROR(EINVAL);
    जर ((!data || *data) && !size)
       परत AVERROR(EINVAL);

    जर (s->application_version >= 8 || s->minimum_application_version >= 3)
        परत AVERROR_INVALIDDATA;
    size_bits = 0;
    size_bits += 3 + 3 + 2;
    size_bits += 1 + 1 + 6;
    जर (s->has_custom_hdr_reference_white_flag)
        size_bits += 16;
    जर (s->has_adaptive_tone_map_flag) {
        size_bits += 16 + 1;
        जर (s->use_reference_white_tone_mapping_flag) {
            size_bits += 7;
        } अन्यथा {
            size_bits += 3 + 2 + 1 + 1;
            जर (s->gain_application_space_chromaticities_flag == 3)
                size_bits += 16 * 8;
            जर (s->अंक_alternate_images > 4)
                परत AVERROR_INVALIDDATA;
            साठी (पूर्णांक a = 0; a < s->अंक_alternate_images; a++) {
                size_bits += 16;
                जर (!a || !s->has_common_component_mix_params_flag) {
                    size_bits += 2;
                    जर (s->component_mixing_type[a] != 3) {
                        size_bits += 6;
                    } अन्यथा {
                        size_bits += 6;
                        साठी (पूर्णांक k = 0; k < 6; k++)
                          जर (s->has_component_mixing_coefficient_flag[a][k])
                            size_bits += 16;
                    }
                }
                जर (!a || !s->has_common_curve_params_flag) {
                    size_bits += 5 + 1 + 2;
                    जर (s->gain_curve_अंक_control_points_minus_1[a] > 31)
                        परत AVERROR_INVALIDDATA;
                    size_bits += 16 * (s->gain_curve_अंक_control_points_minus_1[a] + 1);
                }
                size_bits += 16 * (s->gain_curve_अंक_control_points_minus_1[a] + 1);
                जर (!s->gain_curve_use_pchip_slope_flag[a])
                    size_bits += 16 * (s->gain_curve_अंक_control_points_minus_1[a] + 1);
            }
        }
    }
    जर (size_bits % 8)
      परत AVERROR_INVALIDDATA;
    size_bytes = size_bits >> 3;

    जर (!data) {
        *size = size_bytes;
        परत 0;
    } अन्यथा जर (*data) {
        जर (*size < size_bytes)
            परत AVERROR_BUFFER_TOO_SMALL;
        buf = *data;
    } अन्यथा {
        buf = av_malloc(size_bytes);
        जर (!buf)
            परत AVERROR(ENOMEM);
    }

    init_put_bits(pb, buf, size_bytes);

    // Table C.1
    put_bits(pb, 3, s->application_version);
    put_bits(pb, 3, s->minimum_application_version);
    put_bits(pb, 2, 0); // reserved_zero

    // Table C.2
    put_bits(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_bits(pb, 1, s->has_adaptive_tone_map_flag);
    put_bits(pb, 6, 0); // reserved_zero

    जर (s->has_custom_hdr_reference_white_flag)
        put_bits(pb, 16, s->hdr_reference_white);

    जर (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_bits(pb, 16, s->baseline_hdr_headroom);
        put_bits(pb, 1, s->use_reference_white_tone_mapping_flag);
        जर (s->use_reference_white_tone_mapping_flag) {
            put_bits(pb, 7, 0); // reserved_zero
        } अन्यथा {
            put_bits(pb, 3, s->अंक_alternate_images);
            put_bits(pb, 2, s->gain_application_space_chromaticities_flag);
            put_bits(pb, 1, s->has_common_component_mix_params_flag);
            put_bits(pb, 1, s->has_common_curve_params_flag);

            जर (s->gain_application_space_chromaticities_flag == 3)
                साठी (पूर्णांक r = 0; r < 8; r++)
                    put_bits(pb, 16, s->gain_application_space_chromaticities[r]);

            साठी (पूर्णांक a = 0; a < s->अंक_alternate_images; a++) {
                put_bits(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                जर (!a || !s->has_common_component_mix_params_flag) {
                    put_bits(pb, 2, s->component_mixing_type[a]);
                    जर (s->component_mixing_type[a] != 3) {
                        put_bits(pb, 6, 0); // reserved_zero
                    } अन्यथा {
                        साठी (पूर्णांक k = 0; k < 6; k++)
                            put_bits(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        साठी (पूर्णांक k = 0; k < 6; k++)
                            जर (s->has_component_mixing_coefficient_flag[a][k])
                                put_bits(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                जर (!a || !s->has_common_curve_params_flag) {
                    put_bits(pb, 5, s->gain_curve_अंक_control_points_minus_1[a]);
                    put_bits(pb, 1, s->gain_curve_use_pchip_slope_flag[a]);
                    put_bits(pb, 2, 0); // reserved_zero
                    साठी (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_x[a][c]);
                }
                साठी (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
                    put_bits(pb, 16, s->gain_curve_control_points_y[a][c]);
                जर (!s->gain_curve_use_pchip_slope_flag[a]) {
                    साठी (पूर्णांक c = 0; c <= s->gain_curve_अंक_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_bits(pb);

    *data = buf;
    जर (size)
        *size = size_bytes;
    परत 0;
}

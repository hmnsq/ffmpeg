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

#include "avassert.h"
#include "hdr_dynamic_metadata.h"
#include "mem.h"
#include "libavcodec/defs.h"
#include "libavcodec/get_bits.h"
#include "libavcodec/put_bits.h"

static const int64_t luminance_den = 1;
static const int32_t peak_luminance_den = 15;
static const int64_t rgb_den = 100000;
static const int32_t fraction_pixel_den = 1000;
static const int32_t knee_point_den = 4095;
static const int32_t bezier_anchor_den = 1023;
static const int32_t saturation_weight_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *size)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(sizeof(AVDynamicHDRPlus));

    もし (size)
        *size = hdr_plus ? sizeof(*hdr_plus) : 0;

    戻る hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_DYNAMIC_HDR_PLUS,
                                                        sizeof(AVDynamicHDRPlus));
    もし (!side_data)
        戻る NULL;

    memset(side_data->data, 0, sizeof(AVDynamicHDRPlus));

    戻る (AVDynamicHDRPlus *)side_data->data;
}

整数 av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, const uint8_t *data,
                                 size_t size)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    GetBitContext gbc, *gb = &gbc;
    整数 ret;

    もし (!s)
        戻る AVERROR(EINVAL);

    もし (size > AV_HDR_PLUS_MAX_PAYLOAD_SIZE)
        戻る AVERROR(EINVAL);

    memcpy(padded_buf, data, size);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    ret = init_get_bits8(gb, padded_buf, size);
    もし (ret < 0)
        戻る ret;

    もし (get_bits_left(gb) < 10)
        戻る AVERROR_INVALIDDATA;

    s->application_version = get_bits(gb, 8);
    s->num_windows = get_bits(gb, 2);

    もし (s->num_windows < 1 || s->num_windows > 3) {
        戻る AVERROR_INVALIDDATA;
    }

    もし (get_bits_left(gb) < ((19 * 8 + 1) * (s->num_windows - 1)))
        戻る AVERROR_INVALIDDATA;

    ために (整数 w = 1; w < s->num_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->window_upper_left_corner_x =
            (AVRational){get_bits(gb, 16), 1};
        params->window_upper_left_corner_y =
            (AVRational){get_bits(gb, 16), 1};
        params->window_lower_right_corner_x =
            (AVRational){get_bits(gb, 16), 1};
        params->window_lower_right_corner_y =
            (AVRational){get_bits(gb, 16), 1};

        params->center_of_ellipse_x = get_bits(gb, 16);
        params->center_of_ellipse_y = get_bits(gb, 16);
        params->rotation_angle = get_bits(gb, 8);
        params->semimajor_axis_internal_ellipse = get_bits(gb, 16);
        params->semimajor_axis_external_ellipse = get_bits(gb, 16);
        params->semiminor_axis_external_ellipse = get_bits(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    もし (get_bits_left(gb) < 28)
        戻る AVERROR_INVALIDDATA;

    s->targeted_system_display_maximum_luminance =
        (AVRational){get_bits_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    もし (s->targeted_system_display_actual_peak_luminance_flag) {
        整数 rows, cols;
        もし (get_bits_left(gb) < 10)
            戻る AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        もし (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            戻る AVERROR_INVALIDDATA;
        }
        s->num_rows_targeted_system_display_actual_peak_luminance = rows;
        s->num_cols_targeted_system_display_actual_peak_luminance = cols;

        もし (get_bits_left(gb) < (rows * cols * 4))
            戻る AVERROR_INVALIDDATA;

        ために (整数 i = 0; i < rows; i++) {
            ために (整数 j = 0; j < cols; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }
    ために (整数 w = 0; w < s->num_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        もし (get_bits_left(gb) < (3 * 17 + 17 + 4))
            戻る AVERROR_INVALIDDATA;

        ために (整数 i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_bits(gb, 17), rgb_den};
        }
        params->average_maxrgb =
            (AVRational){get_bits(gb, 17), rgb_den};
        params->num_distribution_maxrgb_percentiles = get_bits(gb, 4);

        もし (get_bits_left(gb) <
            (params->num_distribution_maxrgb_percentiles * 24))
            戻る AVERROR_INVALIDDATA;

        ために (整数 i = 0; i < params->num_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_bits(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_bits(gb, 17), rgb_den};
        }

        もし (get_bits_left(gb) < 10)
            戻る AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_bits(gb, 10), fraction_pixel_den};
    }
    もし (get_bits_left(gb) < 1)
        戻る AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    もし (s->mastering_display_actual_peak_luminance_flag) {
        整数 rows, cols;
        もし (get_bits_left(gb) < 10)
            戻る AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        もし (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            戻る AVERROR_INVALIDDATA;
        }
        s->num_rows_mastering_display_actual_peak_luminance = rows;
        s->num_cols_mastering_display_actual_peak_luminance = cols;

        もし (get_bits_left(gb) < (rows * cols * 4))
            戻る AVERROR_INVALIDDATA;

        ために (整数 i = 0; i < rows; i++) {
            ために (整数 j = 0; j < cols; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }

    ために (整数 w = 0; w < s->num_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        もし (get_bits_left(gb) < 1)
            戻る AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        もし (params->tone_mapping_flag) {
            もし (get_bits_left(gb) < 28)
                戻る AVERROR_INVALIDDATA;

            params->knee_point_x =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->knee_point_y =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->num_bezier_curve_anchors = get_bits(gb, 4);

            もし (get_bits_left(gb) < (params->num_bezier_curve_anchors * 10))
                戻る AVERROR_INVALIDDATA;

            ために (整数 i = 0; i < params->num_bezier_curve_anchors; i++) {
                params->bezier_curve_anchors[i] =
                    (AVRational){get_bits(gb, 10), bezier_anchor_den};
            }
        }

        もし (get_bits_left(gb) < 1)
            戻る AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        もし (params->color_saturation_mapping_flag) {
            もし (get_bits_left(gb) < 6)
                戻る AVERROR_INVALIDDATA;
            params->color_saturation_weight =
                (AVRational){get_bits(gb, 6), saturation_weight_den};
        }
    }

    戻る 0;
}

整数 av_dynamic_hdr_plus_to_t35(const AVDynamicHDRPlus *s, uint8_t **data, size_t *size)
{
    uint8_t *buf;
    size_t size_bits, size_bytes;
    PutBitContext pbc, *pb = &pbc;

    もし (!s)
        戻る AVERROR(EINVAL);
    もし ((!data || *data) && !size)
       戻る AVERROR(EINVAL);

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

    ために (整数 w = 1; w < s->num_windows; w++)
        size_bits += 153;

    size_bits += 27;

    size_bits += 1;
    もし (s->targeted_system_display_actual_peak_luminance_flag)
        size_bits += 10 +
                     s->num_rows_targeted_system_display_actual_peak_luminance *
                     s->num_cols_targeted_system_display_actual_peak_luminance * 4;

    ために (整数 w = 0; w < s->num_windows; w++)
        size_bits += 72 + s->params[w].num_distribution_maxrgb_percentiles * 24 + 10;

    size_bits += 1;
    もし (s->mastering_display_actual_peak_luminance_flag)
        size_bits += 10 +
                     s->num_rows_mastering_display_actual_peak_luminance *
                     s->num_cols_mastering_display_actual_peak_luminance * 4;

    ために (整数 w = 0; w < s->num_windows; w++) {
        size_bits += 1;
        もし (s->params[w].tone_mapping_flag)
            size_bits += 28 + s->params[w].num_bezier_curve_anchors * 10;

        size_bits += 1;
        もし (s->params[w].color_saturation_mapping_flag)
            size_bits += 6;
    }

    size_bytes = (size_bits + 7) / 8;

    av_assert0(size_bytes <= AV_HDR_PLUS_MAX_PAYLOAD_SIZE);

    もし (!data) {
        *size = size_bytes;
        戻る 0;
    } 否则 もし (*data) {
        もし (*size < size_bytes)
            戻る AVERROR_BUFFER_TOO_SMALL;
        buf = *data;
    } 否则 {
        buf = av_malloc(size_bytes);
        もし (!buf)
            戻る AVERROR(ENOMEM);
    }

    init_put_bits(pb, buf, size_bytes);

    // application_mode is set to Application Version 1
    put_bits(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_bits(pb, 2, s->num_windows);

    ために (整数 w = 1; w < s->num_windows; w++) {
        put_bits(pb, 16, s->params[w].window_upper_left_corner_x.num / s->params[w].window_upper_left_corner_x.den);
        put_bits(pb, 16, s->params[w].window_upper_left_corner_y.num / s->params[w].window_upper_left_corner_y.den);
        put_bits(pb, 16, s->params[w].window_lower_right_corner_x.num / s->params[w].window_lower_right_corner_x.den);
        put_bits(pb, 16, s->params[w].window_lower_right_corner_y.num / s->params[w].window_lower_right_corner_y.den);
        put_bits(pb, 16, s->params[w].center_of_ellipse_x);
        put_bits(pb, 16, s->params[w].center_of_ellipse_y);
        put_bits(pb, 8, s->params[w].rotation_angle);
        put_bits(pb, 16, s->params[w].semimajor_axis_internal_ellipse);
        put_bits(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_bits(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_bits(pb, 1, s->params[w].overlap_process_option);
    }

    put_bits(pb, 27, s->targeted_system_display_maximum_luminance.num * luminance_den /
        s->targeted_system_display_maximum_luminance.den);
    put_bits(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    もし (s->targeted_system_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->num_rows_targeted_system_display_actual_peak_luminance);
        put_bits(pb, 5, s->num_cols_targeted_system_display_actual_peak_luminance);
        ために (整数 i = 0; i < s->num_rows_targeted_system_display_actual_peak_luminance; i++) {
            ために (整数 j = 0; j < s->num_cols_targeted_system_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].num * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    ために (整数 w = 0; w < s->num_windows; w++) {
        ために (整数 i = 0; i < 3; i++)
            put_bits(pb, 17, s->params[w].maxscl[i].num * rgb_den / s->params[w].maxscl[i].den);
        put_bits(pb, 17, s->params[w].average_maxrgb.num * rgb_den / s->params[w].average_maxrgb.den);
        put_bits(pb, 4, s->params[w].num_distribution_maxrgb_percentiles);
        ために (整数 i = 0; i < s->params[w].num_distribution_maxrgb_percentiles; i++) {
            put_bits(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_bits(pb, 17, s->params[w].distribution_maxrgb[i].percentile.num * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_bits(pb, 10, s->params[w].fraction_bright_pixels.num * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_bits(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    もし (s->mastering_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->num_rows_mastering_display_actual_peak_luminance);
        put_bits(pb, 5, s->num_cols_mastering_display_actual_peak_luminance);
        ために (整数 i = 0; i < s->num_rows_mastering_display_actual_peak_luminance; i++) {
            ために (整数 j = 0; j < s->num_cols_mastering_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->mastering_display_actual_peak_luminance[i][j].num * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    ために (整数 w = 0; w < s->num_windows; w++) {
        put_bits(pb, 1, s->params[w].tone_mapping_flag);
        もし (s->params[w].tone_mapping_flag) {
            put_bits(pb, 12, s->params[w].knee_point_x.num * knee_point_den / s->params[w].knee_point_x.den);
            put_bits(pb, 12, s->params[w].knee_point_y.num * knee_point_den / s->params[w].knee_point_y.den);
            put_bits(pb, 4, s->params[w].num_bezier_curve_anchors);
            ために (整数 i = 0; i < s->params[w].num_bezier_curve_anchors; i++)
                put_bits(pb, 10, s->params[w].bezier_curve_anchors[i].num * bezier_anchor_den /
                    s->params[w].bezier_curve_anchors[i].den);
        }
        put_bits(pb, 1, s->params[w].color_saturation_mapping_flag);
        もし (s->params[w].color_saturation_mapping_flag)
            put_bits(pb, 6, s->params[w].color_saturation_weight.num * saturation_weight_den /
                s->params[w].color_saturation_weight.den);
    }

    flush_put_bits(pb);

    *data = buf;
    もし (size)
        *size = size_bytes;
    戻る 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *size)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(sizeof(AVDynamicHDRSmpte2094App5));

    もし (size)
        *size = smpte2094_app5 ? sizeof(*smpte2094_app5) : 0;

    戻る smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        sizeof(AVDynamicHDRSmpte2094App5));
    もし (!side_data)
        戻る NULL;

    memset(side_data->data, 0, sizeof(AVDynamicHDRSmpte2094App5));

    戻る (AVDynamicHDRSmpte2094App5 *)side_data->data;
}

#define GET_BITS_OR_FAIL(var, n)        \
    do {                                \
        もし (get_bits_left(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            goto end;                   \
        }                               \
        var = get_bits(gb, n);          \
    } ながら (0)

整数 av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, const uint8_t *data,
                                           size_t size)
{
    GetBitContext gbc, *gb = &gbc;
    整数 ret, reserved_zero;
    size_t padded_size = size + AV_INPUT_BUFFER_PADDING_SIZE;

    もし (!s)
        戻る AVERROR(EINVAL);

    uint8_t *padded_data = av_mallocz(padded_size);
    もし (!padded_data)
        戻る AVERROR(ENOMEM);

    memcpy(padded_data, data, size);
    ret = init_get_bits8(gb, padded_data, size);
    もし (ret < 0)
        goto end;

    // Table C.1
    GET_BITS_OR_FAIL(s->application_version, 3);
    GET_BITS_OR_FAIL(s->minimum_application_version, 3);
    GET_BITS_OR_FAIL(reserved_zero, 2);
    もし (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        goto end;
    }

    // Table C.2
    GET_BITS_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_BITS_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_BITS_OR_FAIL(reserved_zero, 6);
    もし (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        goto end;
    }
    もし (s->has_custom_hdr_reference_white_flag)
        GET_BITS_OR_FAIL(s->hdr_reference_white, 16);
    もし (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        goto end;
    }

    // Table C.3
    GET_BITS_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_BITS_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    もし (s->use_reference_white_tone_mapping_flag) {
        GET_BITS_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        goto end;
    }
    GET_BITS_OR_FAIL(s->num_alternate_images, 3);
    もし (s->num_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        goto end;
    }
    GET_BITS_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_BITS_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_BITS_OR_FAIL(s->has_common_curve_params_flag, 1);
    もし (s->gain_application_space_chromaticities_flag == 3)
        ために (整数 r = 0; r < 8; r++)
            GET_BITS_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    ために (整数 a = 0; a < s->num_alternate_images; a++) {
        GET_BITS_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        もし (!a || !s->has_common_component_mix_params_flag) {
            GET_BITS_OR_FAIL(s->component_mixing_type[a], 2);
            もし (s->component_mixing_type[a] != 3) {
                GET_BITS_OR_FAIL(reserved_zero, 6);
                もし (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    goto end;
                }
            } 否则 {
                ために (整数 k = 0; k < 6; k++)
                    GET_BITS_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                ために (整数 k = 0; k < 6; k++) {
                    もし (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_BITS_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } 否则 {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } 否则 {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            もし (s->component_mixing_type[a] == 3) {
                ために (整数 k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        もし (!a || !s->has_common_curve_params_flag) {
            GET_BITS_OR_FAIL(s->gain_curve_num_control_points_minus_1[a], 5);
            もし (s->gain_curve_num_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                goto end;
            }
            GET_BITS_OR_FAIL(s->gain_curve_use_pchip_slope_flag[a], 1);
            GET_BITS_OR_FAIL(reserved_zero, 2);
            もし (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                goto end;
            }
            ために (整数 c = 0; c <= s->gain_curve_num_control_points_minus_1[a]; c++) {
                GET_BITS_OR_FAIL(s->gain_curve_control_points_x[a][c], 16);
            }
        } 否则 {
            s->gain_curve_num_control_points_minus_1[a] =
                    s->gain_curve_num_control_points_minus_1[0];
            s->gain_curve_use_pchip_slope_flag[a] = s->gain_curve_use_pchip_slope_flag[0];
            ために (整数 c = 0; c <= s->gain_curve_num_control_points_minus_1[a]; c++) {
                s->gain_curve_control_points_x[a][c] = s->gain_curve_control_points_x[0][c];
            }
        }
        ために (整数 c = 0; c <= s->gain_curve_num_control_points_minus_1[a]; c++)
            GET_BITS_OR_FAIL(s->gain_curve_control_points_y[a][c], 16);
        もし (!s->gain_curve_use_pchip_slope_flag[a]) {
            ために (整数 c = 0; c <= s->gain_curve_num_control_points_minus_1[a]; c++)
                GET_BITS_OR_FAIL(s->gain_curve_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
end:
    av_free(padded_data);
    戻る ret;
}

整数 av_dynamic_hdr_smpte2094_app5_to_t35(const AVDynamicHDRSmpte2094App5 *s, uint8_t **data,
                                         size_t *size)
{
    uint8_t *buf;
    size_t size_bytes, size_bits;
    PutBitContext pbc, *pb = &pbc;

    もし (!s)
        戻る AVERROR(EINVAL);
    もし ((!data || *data) && !size)
       戻る AVERROR(EINVAL);

    もし (s->application_version >= 8 || s->minimum_application_version >= 3)
        戻る AVERROR_INVALIDDATA;
    size_bits = 0;
    size_bits += 3 + 3 + 2;
    size_bits += 1 + 1 + 6;
    もし (s->has_custom_hdr_reference_white_flag)
        size_bits += 16;
    もし (s->has_adaptive_tone_map_flag) {
        size_bits += 16 + 1;
        もし (s->use_reference_white_tone_mapping_flag) {
            size_bits += 7;
        } 否则 {
            size_bits += 3 + 2 + 1 + 1;
            もし (s->gain_application_space_chromaticities_flag == 3)
                size_bits += 16 * 8;
            もし (s->num_alternate_images > 4)
                戻る AVERROR_INVALIDDATA;
            ために (整数 a = 0; a < s->num_alternate_images; a++) {
                size_bits += 16;
                もし (!a || !s->has_common_component_mix_params_flag) {
                    size_bits += 2;
                    もし (s->component_mixing_type[a] != 3) {
                        size_bits += 6;
                    } 否则 {
                        size_bits += 6;
                        ために (整数 k = 0; k < 6; k++)
                          もし (s->has_component_mixing_coefficient_flag[a][k])
                            size_bits += 16;
                    }
                }
                もし (!a || !s->has_common_curve_params_flag) {
                    size_bits += 5 + 1 + 2;
                    もし (s->gain_curve_num_control_points_minus_1[a] > 31)
                        戻る AVERROR_INVALIDDATA;
                    size_bits += 16 * (s->gain_curve_num_control_points_minus_1[a] + 1);
                }
                size_bits += 16 * (s->gain_curve_num_control_points_minus_1[a] + 1);
                もし (!s->gain_curve_use_pchip_slope_flag[a])
                    size_bits += 16 * (s->gain_curve_num_control_points_minus_1[a] + 1);
            }
        }
    }
    もし (size_bits % 8)
      戻る AVERROR_INVALIDDATA;
    size_bytes = size_bits >> 3;

    もし (!data) {
        *size = size_bytes;
        戻る 0;
    } 否则 もし (*data) {
        もし (*size < size_bytes)
            戻る AVERROR_BUFFER_TOO_SMALL;
        buf = *data;
    } 否则 {
        buf = av_malloc(size_bytes);
        もし (!buf)
            戻る AVERROR(ENOMEM);
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

    もし (s->has_custom_hdr_reference_white_flag)
        put_bits(pb, 16, s->hdr_reference_white);

    もし (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_bits(pb, 16, s->baseline_hdr_headroom);
        put_bits(pb, 1, s->use_reference_white_tone_mapping_flag);
        もし (s->use_reference_white_tone_mapping_flag) {
            put_bits(pb, 7, 0); // reserved_zero
        } 否则 {
            put_bits(pb, 3, s->num_alternate_images);
            put_bits(pb, 2, s->gain_application_space_chromaticities_flag);
            put_bits(pb, 1, s->has_common_component_mix_params_flag);
            put_bits(pb, 1, s->has_common_curve_params_flag);

            もし (s->gain_application_space_chromaticities_flag == 3)
                ために (整数 r = 0; r < 8; r++)
                    put_bits(pb, 16, s->gain_application_space_chromaticities[r]);

            ために (整数 a = 0; a < s->num_alternate_images; a++) {
                put_bits(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                もし (!a || !s->has_common_component_mix_params_flag) {
                    put_bits(pb, 2, s->component_mixing_type[a]);
                    もし (s->component_mixing_type[a] != 3) {
                        put_bits(pb, 6, 0); // reserved_zero
                    } 否则 {
                        ために (整数 k = 0; k < 6; k++)
                            put_bits(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        ために (整数 k = 0; k < 6; k++)
                            もし (s->has_component_mixing_coefficient_flag[a][k])
                                put_bits(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                もし (!a || !s->has_common_curve_params_flag) {
                    put_bits(pb, 5, s->gain_curve_num_control_points_minus_1[a]);
                    put_bits(pb, 1, s->gain_curve_use_pchip_slope_flag[a]);
                    put_bits(pb, 2, 0); // reserved_zero
                    ために (整数 c = 0; c <= s->gain_curve_num_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_x[a][c]);
                }
                ために (整数 c = 0; c <= s->gain_curve_num_control_points_minus_1[a]; c++)
                    put_bits(pb, 16, s->gain_curve_control_points_y[a][c]);
                もし (!s->gain_curve_use_pchip_slope_flag[a]) {
                    ために (整数 c = 0; c <= s->gain_curve_num_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_bits(pb);

    *data = buf;
    もし (size)
        *size = size_bytes;
    戻る 0;
}

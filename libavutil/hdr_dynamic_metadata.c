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

स्थिर अचर int64_t luminance_den = 1;
स्थिर अचर int32_t peak_luminance_den = 15;
स्थिर अचर int64_t rgb_den = 100000;
स्थिर अचर int32_t fraction_pixel_den = 1000;
स्थिर अचर int32_t knee_point_den = 4095;
स्थिर अचर int32_t bezier_anchor_den = 1023;
स्थिर अचर int32_t saturation_weight_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(माप_प्रकार *size)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(परिमाण(AVDynamicHDRPlus));

    यदि (size)
        *size = hdr_plus ? परिमाण(*hdr_plus) : 0;

    फर्काऊ hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_DYNAMIC_HDR_PLUS,
                                                        परिमाण(AVDynamicHDRPlus));
    यदि (!side_data)
        फर्काऊ रिक्त;

    स_रखो(side_data->data, 0, परिमाण(AVDynamicHDRPlus));

    फर्काऊ (AVDynamicHDRPlus *)side_data->data;
}

पूर्णाङ्क av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, अचर uint8_t *data,
                                 माप_प्रकार size)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_SIZE + AV_आगत_BUFFER_PADDING_SIZE];
    GetBitContext gbc, *gb = &gbc;
    पूर्णाङ्क ret;

    यदि (!s)
        फर्काऊ AVERROR(EINVAL);

    यदि (size > AV_HDR_PLUS_MAX_PAYLOAD_SIZE)
        फर्काऊ AVERROR(EINVAL);

    स_नकल(padded_buf, data, size);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    स_रखो(padded_buf + size, 0, AV_आगत_BUFFER_PADDING_SIZE);

    ret = init_get_bits8(gb, padded_buf, size);
    यदि (ret < 0)
        फर्काऊ ret;

    यदि (get_bits_बायाँ(gb) < 10)
        फर्काऊ AVERROR_INVALIDDATA;

    s->application_version = get_bits(gb, 8);
    s->अङ्क_windows = get_bits(gb, 2);

    यदि (s->अङ्क_windows < 1 || s->अङ्क_windows > 3) {
        फर्काऊ AVERROR_INVALIDDATA;
    }

    यदि (get_bits_बायाँ(gb) < ((19 * 8 + 1) * (s->अङ्क_windows - 1)))
        फर्काऊ AVERROR_INVALIDDATA;

    लागि (पूर्णाङ्क w = 1; w < s->अङ्क_windows; w++) {
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

    यदि (get_bits_बायाँ(gb) < 28)
        फर्काऊ AVERROR_INVALIDDATA;

    s->targeted_system_display_maximum_luminance =
        (AVRational){get_bits_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    यदि (s->targeted_system_display_actual_peak_luminance_flag) {
        पूर्णाङ्क rows, cols;
        यदि (get_bits_बायाँ(gb) < 10)
            फर्काऊ AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        यदि (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            फर्काऊ AVERROR_INVALIDDATA;
        }
        s->अङ्क_rows_targeted_system_display_actual_peak_luminance = rows;
        s->अङ्क_cols_targeted_system_display_actual_peak_luminance = cols;

        यदि (get_bits_बायाँ(gb) < (rows * cols * 4))
            फर्काऊ AVERROR_INVALIDDATA;

        लागि (पूर्णाङ्क i = 0; i < rows; i++) {
            लागि (पूर्णाङ्क j = 0; j < cols; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }
    लागि (पूर्णाङ्क w = 0; w < s->अङ्क_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        यदि (get_bits_बायाँ(gb) < (3 * 17 + 17 + 4))
            फर्काऊ AVERROR_INVALIDDATA;

        लागि (पूर्णाङ्क i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_bits(gb, 17), rgb_den};
        }
        params->average_maxrgb =
            (AVRational){get_bits(gb, 17), rgb_den};
        params->अङ्क_distribution_maxrgb_percentiles = get_bits(gb, 4);

        यदि (get_bits_बायाँ(gb) <
            (params->अङ्क_distribution_maxrgb_percentiles * 24))
            फर्काऊ AVERROR_INVALIDDATA;

        लागि (पूर्णाङ्क i = 0; i < params->अङ्क_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_bits(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_bits(gb, 17), rgb_den};
        }

        यदि (get_bits_बायाँ(gb) < 10)
            फर्काऊ AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_bits(gb, 10), fraction_pixel_den};
    }
    यदि (get_bits_बायाँ(gb) < 1)
        फर्काऊ AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    यदि (s->mastering_display_actual_peak_luminance_flag) {
        पूर्णाङ्क rows, cols;
        यदि (get_bits_बायाँ(gb) < 10)
            फर्काऊ AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        यदि (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            फर्काऊ AVERROR_INVALIDDATA;
        }
        s->अङ्क_rows_mastering_display_actual_peak_luminance = rows;
        s->अङ्क_cols_mastering_display_actual_peak_luminance = cols;

        यदि (get_bits_बायाँ(gb) < (rows * cols * 4))
            फर्काऊ AVERROR_INVALIDDATA;

        लागि (पूर्णाङ्क i = 0; i < rows; i++) {
            लागि (पूर्णाङ्क j = 0; j < cols; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }

    लागि (पूर्णाङ्क w = 0; w < s->अङ्क_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        यदि (get_bits_बायाँ(gb) < 1)
            फर्काऊ AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        यदि (params->tone_mapping_flag) {
            यदि (get_bits_बायाँ(gb) < 28)
                फर्काऊ AVERROR_INVALIDDATA;

            params->knee_point_x =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->knee_point_y =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->अङ्क_bezier_curve_anchors = get_bits(gb, 4);

            यदि (get_bits_बायाँ(gb) < (params->अङ्क_bezier_curve_anchors * 10))
                फर्काऊ AVERROR_INVALIDDATA;

            लागि (पूर्णाङ्क i = 0; i < params->अङ्क_bezier_curve_anchors; i++) {
                params->bezier_curve_anchors[i] =
                    (AVRational){get_bits(gb, 10), bezier_anchor_den};
            }
        }

        यदि (get_bits_बायाँ(gb) < 1)
            फर्काऊ AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        यदि (params->color_saturation_mapping_flag) {
            यदि (get_bits_बायाँ(gb) < 6)
                फर्काऊ AVERROR_INVALIDDATA;
            params->color_saturation_weight =
                (AVRational){get_bits(gb, 6), saturation_weight_den};
        }
    }

    फर्काऊ 0;
}

पूर्णाङ्क av_dynamic_hdr_plus_to_t35(अचर AVDynamicHDRPlus *s, uint8_t **data, माप_प्रकार *size)
{
    uint8_t *buf;
    माप_प्रकार size_bits, size_bytes;
    PutBitContext pbc, *pb = &pbc;

    यदि (!s)
        फर्काऊ AVERROR(EINVAL);
    यदि ((!data || *data) && !size)
       फर्काऊ AVERROR(EINVAL);

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

    लागि (पूर्णाङ्क w = 1; w < s->अङ्क_windows; w++)
        size_bits += 153;

    size_bits += 27;

    size_bits += 1;
    यदि (s->targeted_system_display_actual_peak_luminance_flag)
        size_bits += 10 +
                     s->अङ्क_rows_targeted_system_display_actual_peak_luminance *
                     s->अङ्क_cols_targeted_system_display_actual_peak_luminance * 4;

    लागि (पूर्णाङ्क w = 0; w < s->अङ्क_windows; w++)
        size_bits += 72 + s->params[w].अङ्क_distribution_maxrgb_percentiles * 24 + 10;

    size_bits += 1;
    यदि (s->mastering_display_actual_peak_luminance_flag)
        size_bits += 10 +
                     s->अङ्क_rows_mastering_display_actual_peak_luminance *
                     s->अङ्क_cols_mastering_display_actual_peak_luminance * 4;

    लागि (पूर्णाङ्क w = 0; w < s->अङ्क_windows; w++) {
        size_bits += 1;
        यदि (s->params[w].tone_mapping_flag)
            size_bits += 28 + s->params[w].अङ्क_bezier_curve_anchors * 10;

        size_bits += 1;
        यदि (s->params[w].color_saturation_mapping_flag)
            size_bits += 6;
    }

    size_bytes = (size_bits + 7) / 8;

    av_assert0(size_bytes <= AV_HDR_PLUS_MAX_PAYLOAD_SIZE);

    यदि (!data) {
        *size = size_bytes;
        फर्काऊ 0;
    } अन्यथा यदि (*data) {
        यदि (*size < size_bytes)
            फर्काऊ AVERROR_BUFFER_TOO_SMALL;
        buf = *data;
    } अन्यथा {
        buf = av_malloc(size_bytes);
        यदि (!buf)
            फर्काऊ AVERROR(ENOMEM);
    }

    init_put_bits(pb, buf, size_bytes);

    // application_mode is set to Application Version 1
    put_bits(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_bits(pb, 2, s->अङ्क_windows);

    लागि (पूर्णाङ्क w = 1; w < s->अङ्क_windows; w++) {
        put_bits(pb, 16, s->params[w].window_upper_बायाँ_corner_x.अङ्क / s->params[w].window_upper_बायाँ_corner_x.den);
        put_bits(pb, 16, s->params[w].window_upper_बायाँ_corner_y.अङ्क / s->params[w].window_upper_बायाँ_corner_y.den);
        put_bits(pb, 16, s->params[w].window_lower_दायाँ_corner_x.अङ्क / s->params[w].window_lower_दायाँ_corner_x.den);
        put_bits(pb, 16, s->params[w].window_lower_दायाँ_corner_y.अङ्क / s->params[w].window_lower_दायाँ_corner_y.den);
        put_bits(pb, 16, s->params[w].center_of_ellipse_x);
        put_bits(pb, 16, s->params[w].center_of_ellipse_y);
        put_bits(pb, 8, s->params[w].rotation_angle);
        put_bits(pb, 16, s->params[w].semimajor_axis_internal_ellipse);
        put_bits(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_bits(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_bits(pb, 1, s->params[w].overlap_process_option);
    }

    put_bits(pb, 27, s->targeted_system_display_maximum_luminance.अङ्क * luminance_den /
        s->targeted_system_display_maximum_luminance.den);
    put_bits(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    यदि (s->targeted_system_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->अङ्क_rows_targeted_system_display_actual_peak_luminance);
        put_bits(pb, 5, s->अङ्क_cols_targeted_system_display_actual_peak_luminance);
        लागि (पूर्णाङ्क i = 0; i < s->अङ्क_rows_targeted_system_display_actual_peak_luminance; i++) {
            लागि (पूर्णाङ्क j = 0; j < s->अङ्क_cols_targeted_system_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].अङ्क * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    लागि (पूर्णाङ्क w = 0; w < s->अङ्क_windows; w++) {
        लागि (पूर्णाङ्क i = 0; i < 3; i++)
            put_bits(pb, 17, s->params[w].maxscl[i].अङ्क * rgb_den / s->params[w].maxscl[i].den);
        put_bits(pb, 17, s->params[w].average_maxrgb.अङ्क * rgb_den / s->params[w].average_maxrgb.den);
        put_bits(pb, 4, s->params[w].अङ्क_distribution_maxrgb_percentiles);
        लागि (पूर्णाङ्क i = 0; i < s->params[w].अङ्क_distribution_maxrgb_percentiles; i++) {
            put_bits(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_bits(pb, 17, s->params[w].distribution_maxrgb[i].percentile.अङ्क * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_bits(pb, 10, s->params[w].fraction_bright_pixels.अङ्क * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_bits(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    यदि (s->mastering_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->अङ्क_rows_mastering_display_actual_peak_luminance);
        put_bits(pb, 5, s->अङ्क_cols_mastering_display_actual_peak_luminance);
        लागि (पूर्णाङ्क i = 0; i < s->अङ्क_rows_mastering_display_actual_peak_luminance; i++) {
            लागि (पूर्णाङ्क j = 0; j < s->अङ्क_cols_mastering_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->mastering_display_actual_peak_luminance[i][j].अङ्क * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    लागि (पूर्णाङ्क w = 0; w < s->अङ्क_windows; w++) {
        put_bits(pb, 1, s->params[w].tone_mapping_flag);
        यदि (s->params[w].tone_mapping_flag) {
            put_bits(pb, 12, s->params[w].knee_point_x.अङ्क * knee_point_den / s->params[w].knee_point_x.den);
            put_bits(pb, 12, s->params[w].knee_point_y.अङ्क * knee_point_den / s->params[w].knee_point_y.den);
            put_bits(pb, 4, s->params[w].अङ्क_bezier_curve_anchors);
            लागि (पूर्णाङ्क i = 0; i < s->params[w].अङ्क_bezier_curve_anchors; i++)
                put_bits(pb, 10, s->params[w].bezier_curve_anchors[i].अङ्क * bezier_anchor_den /
                    s->params[w].bezier_curve_anchors[i].den);
        }
        put_bits(pb, 1, s->params[w].color_saturation_mapping_flag);
        यदि (s->params[w].color_saturation_mapping_flag)
            put_bits(pb, 6, s->params[w].color_saturation_weight.अङ्क * saturation_weight_den /
                s->params[w].color_saturation_weight.den);
    }

    flush_put_bits(pb);

    *data = buf;
    यदि (size)
        *size = size_bytes;
    फर्काऊ 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(माप_प्रकार *size)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(परिमाण(AVDynamicHDRSmpte2094App5));

    यदि (size)
        *size = smpte2094_app5 ? परिमाण(*smpte2094_app5) : 0;

    फर्काऊ smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        परिमाण(AVDynamicHDRSmpte2094App5));
    यदि (!side_data)
        फर्काऊ रिक्त;

    स_रखो(side_data->data, 0, परिमाण(AVDynamicHDRSmpte2094App5));

    फर्काऊ (AVDynamicHDRSmpte2094App5 *)side_data->data;
}

#define GET_BITS_OR_FAIL(var, n)        \
    गर {                                \
        यदि (get_bits_बायाँ(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            गच्छ end;                   \
        }                               \
        var = get_bits(gb, n);          \
    } जबसम्म (0)

पूर्णाङ्क av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, अचर uint8_t *data,
                                           माप_प्रकार size)
{
    GetBitContext gbc, *gb = &gbc;
    पूर्णाङ्क ret, reserved_zero;
    माप_प्रकार padded_size = size + AV_आगत_BUFFER_PADDING_SIZE;

    यदि (!s)
        फर्काऊ AVERROR(EINVAL);

    uint8_t *padded_data = av_mallocz(padded_size);
    यदि (!padded_data)
        फर्काऊ AVERROR(ENOMEM);

    स_नकल(padded_data, data, size);
    ret = init_get_bits8(gb, padded_data, size);
    यदि (ret < 0)
        गच्छ end;

    // Table C.1
    GET_BITS_OR_FAIL(s->application_version, 3);
    GET_BITS_OR_FAIL(s->minimum_application_version, 3);
    GET_BITS_OR_FAIL(reserved_zero, 2);
    यदि (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        गच्छ end;
    }

    // Table C.2
    GET_BITS_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_BITS_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_BITS_OR_FAIL(reserved_zero, 6);
    यदि (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        गच्छ end;
    }
    यदि (s->has_custom_hdr_reference_white_flag)
        GET_BITS_OR_FAIL(s->hdr_reference_white, 16);
    यदि (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        गच्छ end;
    }

    // Table C.3
    GET_BITS_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_BITS_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    यदि (s->use_reference_white_tone_mapping_flag) {
        GET_BITS_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        गच्छ end;
    }
    GET_BITS_OR_FAIL(s->अङ्क_alternate_images, 3);
    यदि (s->अङ्क_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        गच्छ end;
    }
    GET_BITS_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_BITS_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_BITS_OR_FAIL(s->has_common_curve_params_flag, 1);
    यदि (s->gain_application_space_chromaticities_flag == 3)
        लागि (पूर्णाङ्क r = 0; r < 8; r++)
            GET_BITS_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    लागि (पूर्णाङ्क a = 0; a < s->अङ्क_alternate_images; a++) {
        GET_BITS_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        यदि (!a || !s->has_common_component_mix_params_flag) {
            GET_BITS_OR_FAIL(s->component_mixing_type[a], 2);
            यदि (s->component_mixing_type[a] != 3) {
                GET_BITS_OR_FAIL(reserved_zero, 6);
                यदि (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    गच्छ end;
                }
            } अन्यथा {
                लागि (पूर्णाङ्क k = 0; k < 6; k++)
                    GET_BITS_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                लागि (पूर्णाङ्क k = 0; k < 6; k++) {
                    यदि (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_BITS_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } अन्यथा {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } अन्यथा {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            यदि (s->component_mixing_type[a] == 3) {
                लागि (पूर्णाङ्क k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        यदि (!a || !s->has_common_curve_params_flag) {
            GET_BITS_OR_FAIL(s->gain_curve_अङ्क_control_points_minus_1[a], 5);
            यदि (s->gain_curve_अङ्क_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                गच्छ end;
            }
            GET_BITS_OR_FAIL(s->gain_curve_use_pchip_slope_flag[a], 1);
            GET_BITS_OR_FAIL(reserved_zero, 2);
            यदि (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                गच्छ end;
            }
            लागि (पूर्णाङ्क c = 0; c <= s->gain_curve_अङ्क_control_points_minus_1[a]; c++) {
                GET_BITS_OR_FAIL(s->gain_curve_control_points_x[a][c], 16);
            }
        } अन्यथा {
            s->gain_curve_अङ्क_control_points_minus_1[a] =
                    s->gain_curve_अङ्क_control_points_minus_1[0];
            s->gain_curve_use_pchip_slope_flag[a] = s->gain_curve_use_pchip_slope_flag[0];
            लागि (पूर्णाङ्क c = 0; c <= s->gain_curve_अङ्क_control_points_minus_1[a]; c++) {
                s->gain_curve_control_points_x[a][c] = s->gain_curve_control_points_x[0][c];
            }
        }
        लागि (पूर्णाङ्क c = 0; c <= s->gain_curve_अङ्क_control_points_minus_1[a]; c++)
            GET_BITS_OR_FAIL(s->gain_curve_control_points_y[a][c], 16);
        यदि (!s->gain_curve_use_pchip_slope_flag[a]) {
            लागि (पूर्णाङ्क c = 0; c <= s->gain_curve_अङ्क_control_points_minus_1[a]; c++)
                GET_BITS_OR_FAIL(s->gain_curve_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
end:
    av_free(padded_data);
    फर्काऊ ret;
}

पूर्णाङ्क av_dynamic_hdr_smpte2094_app5_to_t35(अचर AVDynamicHDRSmpte2094App5 *s, uint8_t **data,
                                         माप_प्रकार *size)
{
    uint8_t *buf;
    माप_प्रकार size_bytes, size_bits;
    PutBitContext pbc, *pb = &pbc;

    यदि (!s)
        फर्काऊ AVERROR(EINVAL);
    यदि ((!data || *data) && !size)
       फर्काऊ AVERROR(EINVAL);

    यदि (s->application_version >= 8 || s->minimum_application_version >= 3)
        फर्काऊ AVERROR_INVALIDDATA;
    size_bits = 0;
    size_bits += 3 + 3 + 2;
    size_bits += 1 + 1 + 6;
    यदि (s->has_custom_hdr_reference_white_flag)
        size_bits += 16;
    यदि (s->has_adaptive_tone_map_flag) {
        size_bits += 16 + 1;
        यदि (s->use_reference_white_tone_mapping_flag) {
            size_bits += 7;
        } अन्यथा {
            size_bits += 3 + 2 + 1 + 1;
            यदि (s->gain_application_space_chromaticities_flag == 3)
                size_bits += 16 * 8;
            यदि (s->अङ्क_alternate_images > 4)
                फर्काऊ AVERROR_INVALIDDATA;
            लागि (पूर्णाङ्क a = 0; a < s->अङ्क_alternate_images; a++) {
                size_bits += 16;
                यदि (!a || !s->has_common_component_mix_params_flag) {
                    size_bits += 2;
                    यदि (s->component_mixing_type[a] != 3) {
                        size_bits += 6;
                    } अन्यथा {
                        size_bits += 6;
                        लागि (पूर्णाङ्क k = 0; k < 6; k++)
                          यदि (s->has_component_mixing_coefficient_flag[a][k])
                            size_bits += 16;
                    }
                }
                यदि (!a || !s->has_common_curve_params_flag) {
                    size_bits += 5 + 1 + 2;
                    यदि (s->gain_curve_अङ्क_control_points_minus_1[a] > 31)
                        फर्काऊ AVERROR_INVALIDDATA;
                    size_bits += 16 * (s->gain_curve_अङ्क_control_points_minus_1[a] + 1);
                }
                size_bits += 16 * (s->gain_curve_अङ्क_control_points_minus_1[a] + 1);
                यदि (!s->gain_curve_use_pchip_slope_flag[a])
                    size_bits += 16 * (s->gain_curve_अङ्क_control_points_minus_1[a] + 1);
            }
        }
    }
    यदि (size_bits % 8)
      फर्काऊ AVERROR_INVALIDDATA;
    size_bytes = size_bits >> 3;

    यदि (!data) {
        *size = size_bytes;
        फर्काऊ 0;
    } अन्यथा यदि (*data) {
        यदि (*size < size_bytes)
            फर्काऊ AVERROR_BUFFER_TOO_SMALL;
        buf = *data;
    } अन्यथा {
        buf = av_malloc(size_bytes);
        यदि (!buf)
            फर्काऊ AVERROR(ENOMEM);
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

    यदि (s->has_custom_hdr_reference_white_flag)
        put_bits(pb, 16, s->hdr_reference_white);

    यदि (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_bits(pb, 16, s->baseline_hdr_headroom);
        put_bits(pb, 1, s->use_reference_white_tone_mapping_flag);
        यदि (s->use_reference_white_tone_mapping_flag) {
            put_bits(pb, 7, 0); // reserved_zero
        } अन्यथा {
            put_bits(pb, 3, s->अङ्क_alternate_images);
            put_bits(pb, 2, s->gain_application_space_chromaticities_flag);
            put_bits(pb, 1, s->has_common_component_mix_params_flag);
            put_bits(pb, 1, s->has_common_curve_params_flag);

            यदि (s->gain_application_space_chromaticities_flag == 3)
                लागि (पूर्णाङ्क r = 0; r < 8; r++)
                    put_bits(pb, 16, s->gain_application_space_chromaticities[r]);

            लागि (पूर्णाङ्क a = 0; a < s->अङ्क_alternate_images; a++) {
                put_bits(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                यदि (!a || !s->has_common_component_mix_params_flag) {
                    put_bits(pb, 2, s->component_mixing_type[a]);
                    यदि (s->component_mixing_type[a] != 3) {
                        put_bits(pb, 6, 0); // reserved_zero
                    } अन्यथा {
                        लागि (पूर्णाङ्क k = 0; k < 6; k++)
                            put_bits(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        लागि (पूर्णाङ्क k = 0; k < 6; k++)
                            यदि (s->has_component_mixing_coefficient_flag[a][k])
                                put_bits(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                यदि (!a || !s->has_common_curve_params_flag) {
                    put_bits(pb, 5, s->gain_curve_अङ्क_control_points_minus_1[a]);
                    put_bits(pb, 1, s->gain_curve_use_pchip_slope_flag[a]);
                    put_bits(pb, 2, 0); // reserved_zero
                    लागि (पूर्णाङ्क c = 0; c <= s->gain_curve_अङ्क_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_x[a][c]);
                }
                लागि (पूर्णाङ्क c = 0; c <= s->gain_curve_अङ्क_control_points_minus_1[a]; c++)
                    put_bits(pb, 16, s->gain_curve_control_points_y[a][c]);
                यदि (!s->gain_curve_use_pchip_slope_flag[a]) {
                    लागि (पूर्णाङ्क c = 0; c <= s->gain_curve_अङ्क_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_bits(pb);

    *data = buf;
    यदि (size)
        *size = size_bytes;
    फर्काऊ 0;
}

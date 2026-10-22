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

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "hdr_dynamic_metadata.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "libavcodec/defs.h"
#ଅନ୍ତର୍ଭାଵ "libavcodec/get_bits.h"
#ଅନ୍ତର୍ଭାଵ "libavcodec/put_bits.h"

ସ୍ଥିର ଅଚଳ int64_t luminance_den = 1;
ସ୍ଥିର ଅଚଳ int32_t peak_luminance_den = 15;
ସ୍ଥିର ଅଚଳ int64_t rgb_den = 100000;
ସ୍ଥିର ଅଚଳ int32_t fraction_pixel_den = 1000;
ସ୍ଥିର ଅଚଳ int32_t knee_point_den = 4095;
ସ୍ଥିର ଅଚଳ int32_t bezier_anchor_den = 1023;
ସ୍ଥିର ଅଚଳ int32_t saturation_weight_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *size)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(ଆକାର(AVDynamicHDRPlus));

    ଯଦି (size)
        *size = hdr_plus ? ଆକାର(*hdr_plus) : 0;

    ଫେରନ୍ତୁ hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_DYNAMIC_HDR_PLUS,
                                                        ଆକାର(AVDynamicHDRPlus));
    ଯଦି (!side_data)
        ଫେରନ୍ତୁ ଖାଲି;

    memset(side_data->data, 0, ଆକାର(AVDynamicHDRPlus));

    ଫେରନ୍ତୁ (AVDynamicHDRPlus *)side_data->data;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, ଅଚଳ uint8_t *data,
                                 size_t size)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_SIZE + AV_ନିବେଶ_BUFFER_PADDING_SIZE];
    GetBitContext gbc, *gb = &gbc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!s)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (size > AV_HDR_PLUS_MAX_PAYLOAD_SIZE)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    memcpy(padded_buf, data, size);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + size, 0, AV_ନିବେଶ_BUFFER_PADDING_SIZE);

    ret = init_get_bits8(gb, padded_buf, size);
    ଯଦି (ret < 0)
        ଫେରନ୍ତୁ ret;

    ଯଦି (get_bits_ବାମ(gb) < 10)
        ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

    s->application_version = get_bits(gb, 8);
    s->ଅଙ୍କ_windows = get_bits(gb, 2);

    ଯଦି (s->ଅଙ୍କ_windows < 1 || s->ଅଙ୍କ_windows > 3) {
        ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
    }

    ଯଦି (get_bits_ବାମ(gb) < ((19 * 8 + 1) * (s->ଅଙ୍କ_windows - 1)))
        ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 1; w < s->ଅଙ୍କ_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->window_upper_ବାମ_corner_x =
            (AVRational){get_bits(gb, 16), 1};
        params->window_upper_ବାମ_corner_y =
            (AVRational){get_bits(gb, 16), 1};
        params->window_lower_ଡାହାଣ_corner_x =
            (AVRational){get_bits(gb, 16), 1};
        params->window_lower_ଡାହାଣ_corner_y =
            (AVRational){get_bits(gb, 16), 1};

        params->center_of_ellipse_x = get_bits(gb, 16);
        params->center_of_ellipse_y = get_bits(gb, 16);
        params->rotation_angle = get_bits(gb, 8);
        params->semimajor_axis_internal_ellipse = get_bits(gb, 16);
        params->semimajor_axis_external_ellipse = get_bits(gb, 16);
        params->semiminor_axis_external_ellipse = get_bits(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    ଯଦି (get_bits_ବାମ(gb) < 28)
        ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

    s->targeted_system_display_maximum_luminance =
        (AVRational){get_bits_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    ଯଦି (s->targeted_system_display_actual_peak_luminance_flag) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା rows, cols;
        ଯଦି (get_bits_ବାମ(gb) < 10)
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        ଯଦି (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
        }
        s->ଅଙ୍କ_rows_targeted_system_display_actual_peak_luminance = rows;
        s->ଅଙ୍କ_cols_targeted_system_display_actual_peak_luminance = cols;

        ଯଦି (get_bits_ବାମ(gb) < (rows * cols * 4))
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < rows; i++) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < cols; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 0; w < s->ଅଙ୍କ_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        ଯଦି (get_bits_ବାମ(gb) < (3 * 17 + 17 + 4))
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_bits(gb, 17), rgb_den};
        }
        params->average_maxrgb =
            (AVRational){get_bits(gb, 17), rgb_den};
        params->ଅଙ୍କ_distribution_maxrgb_percentiles = get_bits(gb, 4);

        ଯଦି (get_bits_ବାମ(gb) <
            (params->ଅଙ୍କ_distribution_maxrgb_percentiles * 24))
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < params->ଅଙ୍କ_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_bits(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_bits(gb, 17), rgb_den};
        }

        ଯଦି (get_bits_ବାମ(gb) < 10)
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_bits(gb, 10), fraction_pixel_den};
    }
    ଯଦି (get_bits_ବାମ(gb) < 1)
        ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    ଯଦି (s->mastering_display_actual_peak_luminance_flag) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା rows, cols;
        ଯଦି (get_bits_ବାମ(gb) < 10)
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
        rows = get_bits(gb, 5);
        cols = get_bits(gb, 5);
        ଯଦି (((rows < 2) || (rows > 25)) || ((cols < 2) || (cols > 25))) {
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
        }
        s->ଅଙ୍କ_rows_mastering_display_actual_peak_luminance = rows;
        s->ଅଙ୍କ_cols_mastering_display_actual_peak_luminance = cols;

        ଯଦି (get_bits_ବାମ(gb) < (rows * cols * 4))
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < rows; i++) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < cols; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_bits(gb, 4), peak_luminance_den};
            }
        }
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 0; w < s->ଅଙ୍କ_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        ଯଦି (get_bits_ବାମ(gb) < 1)
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        ଯଦି (params->tone_mapping_flag) {
            ଯଦି (get_bits_ବାମ(gb) < 28)
                ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

            params->knee_point_x =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->knee_point_y =
                (AVRational){get_bits(gb, 12), knee_point_den};
            params->ଅଙ୍କ_bezier_curve_anchors = get_bits(gb, 4);

            ଯଦି (get_bits_ବାମ(gb) < (params->ଅଙ୍କ_bezier_curve_anchors * 10))
                ଫେରନ୍ତୁ AVERROR_INVALIDDATA;

            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < params->ଅଙ୍କ_bezier_curve_anchors; i++) {
                params->bezier_curve_anchors[i] =
                    (AVRational){get_bits(gb, 10), bezier_anchor_den};
            }
        }

        ଯଦି (get_bits_ବାମ(gb) < 1)
            ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        ଯଦି (params->color_saturation_mapping_flag) {
            ଯଦି (get_bits_ବାମ(gb) < 6)
                ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
            params->color_saturation_weight =
                (AVRational){get_bits(gb, 6), saturation_weight_den};
        }
    }

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dynamic_hdr_plus_to_t35(ଅଚଳ AVDynamicHDRPlus *s, uint8_t **data, size_t *size)
{
    uint8_t *buf;
    size_t size_bits, size_bytes;
    PutBitContext pbc, *pb = &pbc;

    ଯଦି (!s)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ଯଦି ((!data || *data) && !size)
       ଫେରନ୍ତୁ AVERROR(EINVAL);

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

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 1; w < s->ଅଙ୍କ_windows; w++)
        size_bits += 153;

    size_bits += 27;

    size_bits += 1;
    ଯଦି (s->targeted_system_display_actual_peak_luminance_flag)
        size_bits += 10 +
                     s->ଅଙ୍କ_rows_targeted_system_display_actual_peak_luminance *
                     s->ଅଙ୍କ_cols_targeted_system_display_actual_peak_luminance * 4;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 0; w < s->ଅଙ୍କ_windows; w++)
        size_bits += 72 + s->params[w].ଅଙ୍କ_distribution_maxrgb_percentiles * 24 + 10;

    size_bits += 1;
    ଯଦି (s->mastering_display_actual_peak_luminance_flag)
        size_bits += 10 +
                     s->ଅଙ୍କ_rows_mastering_display_actual_peak_luminance *
                     s->ଅଙ୍କ_cols_mastering_display_actual_peak_luminance * 4;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 0; w < s->ଅଙ୍କ_windows; w++) {
        size_bits += 1;
        ଯଦି (s->params[w].tone_mapping_flag)
            size_bits += 28 + s->params[w].ଅଙ୍କ_bezier_curve_anchors * 10;

        size_bits += 1;
        ଯଦି (s->params[w].color_saturation_mapping_flag)
            size_bits += 6;
    }

    size_bytes = (size_bits + 7) / 8;

    av_assert0(size_bytes <= AV_HDR_PLUS_MAX_PAYLOAD_SIZE);

    ଯଦି (!data) {
        *size = size_bytes;
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା ଯଦି (*data) {
        ଯଦି (*size < size_bytes)
            ଫେରନ୍ତୁ AVERROR_BUFFER_TOO_SMALL;
        buf = *data;
    } ଅନ୍ୟଥା {
        buf = av_malloc(size_bytes);
        ଯଦି (!buf)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    init_put_bits(pb, buf, size_bytes);

    // application_mode is set to Application Version 1
    put_bits(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_bits(pb, 2, s->ଅଙ୍କ_windows);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 1; w < s->ଅଙ୍କ_windows; w++) {
        put_bits(pb, 16, s->params[w].window_upper_ବାମ_corner_x.ଅଙ୍କ / s->params[w].window_upper_ବାମ_corner_x.den);
        put_bits(pb, 16, s->params[w].window_upper_ବାମ_corner_y.ଅଙ୍କ / s->params[w].window_upper_ବାମ_corner_y.den);
        put_bits(pb, 16, s->params[w].window_lower_ଡାହାଣ_corner_x.ଅଙ୍କ / s->params[w].window_lower_ଡାହାଣ_corner_x.den);
        put_bits(pb, 16, s->params[w].window_lower_ଡାହାଣ_corner_y.ଅଙ୍କ / s->params[w].window_lower_ଡାହାଣ_corner_y.den);
        put_bits(pb, 16, s->params[w].center_of_ellipse_x);
        put_bits(pb, 16, s->params[w].center_of_ellipse_y);
        put_bits(pb, 8, s->params[w].rotation_angle);
        put_bits(pb, 16, s->params[w].semimajor_axis_internal_ellipse);
        put_bits(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_bits(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_bits(pb, 1, s->params[w].overlap_process_option);
    }

    put_bits(pb, 27, s->targeted_system_display_maximum_luminance.ଅଙ୍କ * luminance_den /
        s->targeted_system_display_maximum_luminance.den);
    put_bits(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    ଯଦି (s->targeted_system_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->ଅଙ୍କ_rows_targeted_system_display_actual_peak_luminance);
        put_bits(pb, 5, s->ଅଙ୍କ_cols_targeted_system_display_actual_peak_luminance);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->ଅଙ୍କ_rows_targeted_system_display_actual_peak_luminance; i++) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < s->ଅଙ୍କ_cols_targeted_system_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].ଅଙ୍କ * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 0; w < s->ଅଙ୍କ_windows; w++) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < 3; i++)
            put_bits(pb, 17, s->params[w].maxscl[i].ଅଙ୍କ * rgb_den / s->params[w].maxscl[i].den);
        put_bits(pb, 17, s->params[w].average_maxrgb.ଅଙ୍କ * rgb_den / s->params[w].average_maxrgb.den);
        put_bits(pb, 4, s->params[w].ଅଙ୍କ_distribution_maxrgb_percentiles);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->params[w].ଅଙ୍କ_distribution_maxrgb_percentiles; i++) {
            put_bits(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_bits(pb, 17, s->params[w].distribution_maxrgb[i].percentile.ଅଙ୍କ * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_bits(pb, 10, s->params[w].fraction_bright_pixels.ଅଙ୍କ * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_bits(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    ଯଦି (s->mastering_display_actual_peak_luminance_flag) {
        put_bits(pb, 5, s->ଅଙ୍କ_rows_mastering_display_actual_peak_luminance);
        put_bits(pb, 5, s->ଅଙ୍କ_cols_mastering_display_actual_peak_luminance);
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->ଅଙ୍କ_rows_mastering_display_actual_peak_luminance; i++) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା j = 0; j < s->ଅଙ୍କ_cols_mastering_display_actual_peak_luminance; j++)
                put_bits(pb, 4, s->mastering_display_actual_peak_luminance[i][j].ଅଙ୍କ * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = 0; w < s->ଅଙ୍କ_windows; w++) {
        put_bits(pb, 1, s->params[w].tone_mapping_flag);
        ଯଦି (s->params[w].tone_mapping_flag) {
            put_bits(pb, 12, s->params[w].knee_point_x.ଅଙ୍କ * knee_point_den / s->params[w].knee_point_x.den);
            put_bits(pb, 12, s->params[w].knee_point_y.ଅଙ୍କ * knee_point_den / s->params[w].knee_point_y.den);
            put_bits(pb, 4, s->params[w].ଅଙ୍କ_bezier_curve_anchors);
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < s->params[w].ଅଙ୍କ_bezier_curve_anchors; i++)
                put_bits(pb, 10, s->params[w].bezier_curve_anchors[i].ଅଙ୍କ * bezier_anchor_den /
                    s->params[w].bezier_curve_anchors[i].den);
        }
        put_bits(pb, 1, s->params[w].color_saturation_mapping_flag);
        ଯଦି (s->params[w].color_saturation_mapping_flag)
            put_bits(pb, 6, s->params[w].color_saturation_weight.ଅଙ୍କ * saturation_weight_den /
                s->params[w].color_saturation_weight.den);
    }

    flush_put_bits(pb);

    *data = buf;
    ଯଦି (size)
        *size = size_bytes;
    ଫେରନ୍ତୁ 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *size)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(ଆକାର(AVDynamicHDRSmpte2094App5));

    ଯଦି (size)
        *size = smpte2094_app5 ? ଆକାର(*smpte2094_app5) : 0;

    ଫେରନ୍ତୁ smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        ଆକାର(AVDynamicHDRSmpte2094App5));
    ଯଦି (!side_data)
        ଫେରନ୍ତୁ ଖାଲି;

    memset(side_data->data, 0, ଆକାର(AVDynamicHDRSmpte2094App5));

    ଫେରନ୍ତୁ (AVDynamicHDRSmpte2094App5 *)side_data->data;
}

#define GET_BITS_OR_FAIL(var, n)        \
    କର {                                \
        ଯଦି (get_bits_ବାମ(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            ଯାଅ end;                   \
        }                               \
        var = get_bits(gb, n);          \
    } ଯେତେବେଳେ (0)

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, ଅଚଳ uint8_t *data,
                                           size_t size)
{
    GetBitContext gbc, *gb = &gbc;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret, reserved_zero;
    size_t padded_size = size + AV_ନିବେଶ_BUFFER_PADDING_SIZE;

    ଯଦି (!s)
        ଫେରନ୍ତୁ AVERROR(EINVAL);

    uint8_t *padded_data = av_mallocz(padded_size);
    ଯଦି (!padded_data)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    memcpy(padded_data, data, size);
    ret = init_get_bits8(gb, padded_data, size);
    ଯଦି (ret < 0)
        ଯାଅ end;

    // Table C.1
    GET_BITS_OR_FAIL(s->application_version, 3);
    GET_BITS_OR_FAIL(s->minimum_application_version, 3);
    GET_BITS_OR_FAIL(reserved_zero, 2);
    ଯଦି (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        ଯାଅ end;
    }

    // Table C.2
    GET_BITS_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_BITS_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_BITS_OR_FAIL(reserved_zero, 6);
    ଯଦି (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        ଯାଅ end;
    }
    ଯଦି (s->has_custom_hdr_reference_white_flag)
        GET_BITS_OR_FAIL(s->hdr_reference_white, 16);
    ଯଦି (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        ଯାଅ end;
    }

    // Table C.3
    GET_BITS_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_BITS_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    ଯଦି (s->use_reference_white_tone_mapping_flag) {
        GET_BITS_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        ଯାଅ end;
    }
    GET_BITS_OR_FAIL(s->ଅଙ୍କ_alternate_images, 3);
    ଯଦି (s->ଅଙ୍କ_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        ଯାଅ end;
    }
    GET_BITS_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_BITS_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_BITS_OR_FAIL(s->has_common_curve_params_flag, 1);
    ଯଦି (s->gain_application_space_chromaticities_flag == 3)
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା r = 0; r < 8; r++)
            GET_BITS_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା a = 0; a < s->ଅଙ୍କ_alternate_images; a++) {
        GET_BITS_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        ଯଦି (!a || !s->has_common_component_mix_params_flag) {
            GET_BITS_OR_FAIL(s->component_mixing_type[a], 2);
            ଯଦି (s->component_mixing_type[a] != 3) {
                GET_BITS_OR_FAIL(reserved_zero, 6);
                ଯଦି (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    ଯାଅ end;
                }
            } ଅନ୍ୟଥା {
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା k = 0; k < 6; k++)
                    GET_BITS_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା k = 0; k < 6; k++) {
                    ଯଦି (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_BITS_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } ଅନ୍ୟଥା {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } ଅନ୍ୟଥା {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            ଯଦି (s->component_mixing_type[a] == 3) {
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        ଯଦି (!a || !s->has_common_curve_params_flag) {
            GET_BITS_OR_FAIL(s->gain_curve_ଅଙ୍କ_control_points_minus_1[a], 5);
            ଯଦି (s->gain_curve_ଅଙ୍କ_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                ଯାଅ end;
            }
            GET_BITS_OR_FAIL(s->gain_curve_use_pchip_slope_flag[a], 1);
            GET_BITS_OR_FAIL(reserved_zero, 2);
            ଯଦି (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                ଯାଅ end;
            }
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c <= s->gain_curve_ଅଙ୍କ_control_points_minus_1[a]; c++) {
                GET_BITS_OR_FAIL(s->gain_curve_control_points_x[a][c], 16);
            }
        } ଅନ୍ୟଥା {
            s->gain_curve_ଅଙ୍କ_control_points_minus_1[a] =
                    s->gain_curve_ଅଙ୍କ_control_points_minus_1[0];
            s->gain_curve_use_pchip_slope_flag[a] = s->gain_curve_use_pchip_slope_flag[0];
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c <= s->gain_curve_ଅଙ୍କ_control_points_minus_1[a]; c++) {
                s->gain_curve_control_points_x[a][c] = s->gain_curve_control_points_x[0][c];
            }
        }
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c <= s->gain_curve_ଅଙ୍କ_control_points_minus_1[a]; c++)
            GET_BITS_OR_FAIL(s->gain_curve_control_points_y[a][c], 16);
        ଯଦି (!s->gain_curve_use_pchip_slope_flag[a]) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c <= s->gain_curve_ଅଙ୍କ_control_points_minus_1[a]; c++)
                GET_BITS_OR_FAIL(s->gain_curve_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
end:
    av_free(padded_data);
    ଫେରନ୍ତୁ ret;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dynamic_hdr_smpte2094_app5_to_t35(ଅଚଳ AVDynamicHDRSmpte2094App5 *s, uint8_t **data,
                                         size_t *size)
{
    uint8_t *buf;
    size_t size_bytes, size_bits;
    PutBitContext pbc, *pb = &pbc;

    ଯଦି (!s)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    ଯଦି ((!data || *data) && !size)
       ଫେରନ୍ତୁ AVERROR(EINVAL);

    ଯଦି (s->application_version >= 8 || s->minimum_application_version >= 3)
        ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
    size_bits = 0;
    size_bits += 3 + 3 + 2;
    size_bits += 1 + 1 + 6;
    ଯଦି (s->has_custom_hdr_reference_white_flag)
        size_bits += 16;
    ଯଦି (s->has_adaptive_tone_map_flag) {
        size_bits += 16 + 1;
        ଯଦି (s->use_reference_white_tone_mapping_flag) {
            size_bits += 7;
        } ଅନ୍ୟଥା {
            size_bits += 3 + 2 + 1 + 1;
            ଯଦି (s->gain_application_space_chromaticities_flag == 3)
                size_bits += 16 * 8;
            ଯଦି (s->ଅଙ୍କ_alternate_images > 4)
                ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା a = 0; a < s->ଅଙ୍କ_alternate_images; a++) {
                size_bits += 16;
                ଯଦି (!a || !s->has_common_component_mix_params_flag) {
                    size_bits += 2;
                    ଯଦି (s->component_mixing_type[a] != 3) {
                        size_bits += 6;
                    } ଅନ୍ୟଥା {
                        size_bits += 6;
                        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା k = 0; k < 6; k++)
                          ଯଦି (s->has_component_mixing_coefficient_flag[a][k])
                            size_bits += 16;
                    }
                }
                ଯଦି (!a || !s->has_common_curve_params_flag) {
                    size_bits += 5 + 1 + 2;
                    ଯଦି (s->gain_curve_ଅଙ୍କ_control_points_minus_1[a] > 31)
                        ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
                    size_bits += 16 * (s->gain_curve_ଅଙ୍କ_control_points_minus_1[a] + 1);
                }
                size_bits += 16 * (s->gain_curve_ଅଙ୍କ_control_points_minus_1[a] + 1);
                ଯଦି (!s->gain_curve_use_pchip_slope_flag[a])
                    size_bits += 16 * (s->gain_curve_ଅଙ୍କ_control_points_minus_1[a] + 1);
            }
        }
    }
    ଯଦି (size_bits % 8)
      ଫେରନ୍ତୁ AVERROR_INVALIDDATA;
    size_bytes = size_bits >> 3;

    ଯଦି (!data) {
        *size = size_bytes;
        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା ଯଦି (*data) {
        ଯଦି (*size < size_bytes)
            ଫେରନ୍ତୁ AVERROR_BUFFER_TOO_SMALL;
        buf = *data;
    } ଅନ୍ୟଥା {
        buf = av_malloc(size_bytes);
        ଯଦି (!buf)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
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

    ଯଦି (s->has_custom_hdr_reference_white_flag)
        put_bits(pb, 16, s->hdr_reference_white);

    ଯଦି (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_bits(pb, 16, s->baseline_hdr_headroom);
        put_bits(pb, 1, s->use_reference_white_tone_mapping_flag);
        ଯଦି (s->use_reference_white_tone_mapping_flag) {
            put_bits(pb, 7, 0); // reserved_zero
        } ଅନ୍ୟଥା {
            put_bits(pb, 3, s->ଅଙ୍କ_alternate_images);
            put_bits(pb, 2, s->gain_application_space_chromaticities_flag);
            put_bits(pb, 1, s->has_common_component_mix_params_flag);
            put_bits(pb, 1, s->has_common_curve_params_flag);

            ଯଦି (s->gain_application_space_chromaticities_flag == 3)
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା r = 0; r < 8; r++)
                    put_bits(pb, 16, s->gain_application_space_chromaticities[r]);

            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା a = 0; a < s->ଅଙ୍କ_alternate_images; a++) {
                put_bits(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                ଯଦି (!a || !s->has_common_component_mix_params_flag) {
                    put_bits(pb, 2, s->component_mixing_type[a]);
                    ଯଦି (s->component_mixing_type[a] != 3) {
                        put_bits(pb, 6, 0); // reserved_zero
                    } ଅନ୍ୟଥା {
                        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା k = 0; k < 6; k++)
                            put_bits(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା k = 0; k < 6; k++)
                            ଯଦି (s->has_component_mixing_coefficient_flag[a][k])
                                put_bits(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                ଯଦି (!a || !s->has_common_curve_params_flag) {
                    put_bits(pb, 5, s->gain_curve_ଅଙ୍କ_control_points_minus_1[a]);
                    put_bits(pb, 1, s->gain_curve_use_pchip_slope_flag[a]);
                    put_bits(pb, 2, 0); // reserved_zero
                    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c <= s->gain_curve_ଅଙ୍କ_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_x[a][c]);
                }
                ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c <= s->gain_curve_ଅଙ୍କ_control_points_minus_1[a]; c++)
                    put_bits(pb, 16, s->gain_curve_control_points_y[a][c]);
                ଯଦି (!s->gain_curve_use_pchip_slope_flag[a]) {
                    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = 0; c <= s->gain_curve_ଅଙ୍କ_control_points_minus_1[a]; c++)
                        put_bits(pb, 16, s->gain_curve_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_bits(pb);

    *data = buf;
    ଯଦି (size)
        *size = size_bytes;
    ଫେରନ୍ତୁ 0;
}

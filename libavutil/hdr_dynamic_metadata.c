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

#شامل "avassert.h"
#شامل "hdr_dynamic_metadata.h"
#شامل "mem.h"
#شامل "libavcodec/defs.h"
#شامل "libavcodec/get_bits.h"
#شامل "libavcodec/put_bits.h"

ساکن ثابت int64_t luminance_den = 1;
ساکن ثابت int32_t peak_luminance_den = 15;
ساکن ثابت int64_t rgb_den = 100000;
ساکن ثابت int32_t fraction_pixel_den = 1000;
ساکن ثابت int32_t knee_نقطہ_den = 4095;
ساکن ثابت int32_t bezier_anchor_den = 1023;
ساکن ثابت int32_t saturation_وزن_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *سائز)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(حجم(AVDynamicHDRPlus));

    اگر (سائز)
        *سائز = hdr_plus ? حجم(*hdr_plus) : 0;

    واپس hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_ڈیٹا(AVFrame *چوکھٹا)
{
    AVFrame_Side_ڈیٹا *side_ڈیٹا = av_چوکھٹا_new_side_ڈیٹا(چوکھٹا,
                                                        AV_چوکھٹا_ڈیٹا_DYNAMIC_HDR_PLUS,
                                                        حجم(AVDynamicHDRPlus));
    اگر (!side_ڈیٹا)
        واپس تہی;

    memset(side_ڈیٹا->ڈیٹا, 0, حجم(AVDynamicHDRPlus));

    واپس (AVDynamicHDRPlus *)side_ڈیٹا->ڈیٹا;
}

صحیح av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, ثابت uint8_t *ڈیٹا,
                                 size_t سائز)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_سائز + AV_داخلہ_بفر_PADDING_سائز];
    Get_ثنائی_ہندسہ_Context gbc, *gb = &gbc;
    صحیح ret;

    اگر (!s)
        واپس AVERROR(EINVAL);

    اگر (سائز > AV_HDR_PLUS_MAX_PAYLOAD_سائز)
        واپس AVERROR(EINVAL);

    حافظہ_نقل(padded_buf, ڈیٹا, سائز);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + سائز, 0, AV_داخلہ_بفر_PADDING_سائز);

    ret = init_get_bits8(gb, padded_buf, سائز);
    اگر (ret < 0)
        واپس ret;

    اگر (get_بٹ_بایاں(gb) < 10)
        واپس AVERROR_INVALIDDATA;

    s->application_نسخہ = get_بٹ(gb, 8);
    s->عدد_windows = get_بٹ(gb, 2);

    اگر (s->عدد_windows < 1 || s->عدد_windows > 3) {
        واپس AVERROR_INVALIDDATA;
    }

    اگر (get_بٹ_بایاں(gb) < ((19 * 8 + 1) * (s->عدد_windows - 1)))
        واپس AVERROR_INVALIDDATA;

    برائے (صحیح w = 1; w < s->عدد_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->کھڑکی_بالائی_بایاں_کونا_x =
            (AVRational){get_بٹ(gb, 16), 1};
        params->کھڑکی_بالائی_بایاں_کونا_y =
            (AVRational){get_بٹ(gb, 16), 1};
        params->کھڑکی_زیریں_دایاں_کونا_x =
            (AVRational){get_بٹ(gb, 16), 1};
        params->کھڑکی_زیریں_دایاں_کونا_y =
            (AVRational){get_بٹ(gb, 16), 1};

        params->center_کا_ellipse_x = get_بٹ(gb, 16);
        params->center_کا_ellipse_y = get_بٹ(gb, 16);
        params->rotation_angle = get_بٹ(gb, 8);
        params->semimajor_axis_اندرونی_ellipse = get_بٹ(gb, 16);
        params->semimajor_axis_external_ellipse = get_بٹ(gb, 16);
        params->semiminor_axis_external_ellipse = get_بٹ(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    اگر (get_بٹ_بایاں(gb) < 28)
        واپس AVERROR_INVALIDDATA;

    s->targeted_system_display_زیادہ_سے_زیادہ_luminance =
        (AVRational){get_بٹ_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    اگر (s->targeted_system_display_actual_peak_luminance_flag) {
        صحیح صفیں, ستون_تعداد;
        اگر (get_بٹ_بایاں(gb) < 10)
            واپس AVERROR_INVALIDDATA;
        صفیں = get_بٹ(gb, 5);
        ستون_تعداد = get_بٹ(gb, 5);
        اگر (((صفیں < 2) || (صفیں > 25)) || ((ستون_تعداد < 2) || (ستون_تعداد > 25))) {
            واپس AVERROR_INVALIDDATA;
        }
        s->عدد_صفیں_targeted_system_display_actual_peak_luminance = صفیں;
        s->عدد_ستون_تعداد_targeted_system_display_actual_peak_luminance = ستون_تعداد;

        اگر (get_بٹ_بایاں(gb) < (صفیں * ستون_تعداد * 4))
            واپس AVERROR_INVALIDDATA;

        برائے (صحیح i = 0; i < صفیں; i++) {
            برائے (صحیح j = 0; j < ستون_تعداد; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بٹ(gb, 4), peak_luminance_den};
            }
        }
    }
    برائے (صحیح w = 0; w < s->عدد_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        اگر (get_بٹ_بایاں(gb) < (3 * 17 + 17 + 4))
            واپس AVERROR_INVALIDDATA;

        برائے (صحیح i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_بٹ(gb, 17), rgb_den};
        }
        params->اوسط_قدر_maxrgb =
            (AVRational){get_بٹ(gb, 17), rgb_den};
        params->عدد_distribution_maxrgb_percentiles = get_بٹ(gb, 4);

        اگر (get_بٹ_بایاں(gb) <
            (params->عدد_distribution_maxrgb_percentiles * 24))
            واپس AVERROR_INVALIDDATA;

        برائے (صحیح i = 0; i < params->عدد_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_بٹ(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_بٹ(gb, 17), rgb_den};
        }

        اگر (get_بٹ_بایاں(gb) < 10)
            واپس AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_بٹ(gb, 10), fraction_pixel_den};
    }
    اگر (get_بٹ_بایاں(gb) < 1)
        واپس AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    اگر (s->mastering_display_actual_peak_luminance_flag) {
        صحیح صفیں, ستون_تعداد;
        اگر (get_بٹ_بایاں(gb) < 10)
            واپس AVERROR_INVALIDDATA;
        صفیں = get_بٹ(gb, 5);
        ستون_تعداد = get_بٹ(gb, 5);
        اگر (((صفیں < 2) || (صفیں > 25)) || ((ستون_تعداد < 2) || (ستون_تعداد > 25))) {
            واپس AVERROR_INVALIDDATA;
        }
        s->عدد_صفیں_mastering_display_actual_peak_luminance = صفیں;
        s->عدد_ستون_تعداد_mastering_display_actual_peak_luminance = ستون_تعداد;

        اگر (get_بٹ_بایاں(gb) < (صفیں * ستون_تعداد * 4))
            واپس AVERROR_INVALIDDATA;

        برائے (صحیح i = 0; i < صفیں; i++) {
            برائے (صحیح j = 0; j < ستون_تعداد; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بٹ(gb, 4), peak_luminance_den};
            }
        }
    }

    برائے (صحیح w = 0; w < s->عدد_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        اگر (get_بٹ_بایاں(gb) < 1)
            واپس AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        اگر (params->tone_mapping_flag) {
            اگر (get_بٹ_بایاں(gb) < 28)
                واپس AVERROR_INVALIDDATA;

            params->knee_نقطہ_x =
                (AVRational){get_بٹ(gb, 12), knee_نقطہ_den};
            params->knee_نقطہ_y =
                (AVRational){get_بٹ(gb, 12), knee_نقطہ_den};
            params->عدد_bezier_خم_anchors = get_بٹ(gb, 4);

            اگر (get_بٹ_بایاں(gb) < (params->عدد_bezier_خم_anchors * 10))
                واپس AVERROR_INVALIDDATA;

            برائے (صحیح i = 0; i < params->عدد_bezier_خم_anchors; i++) {
                params->bezier_خم_anchors[i] =
                    (AVRational){get_بٹ(gb, 10), bezier_anchor_den};
            }
        }

        اگر (get_بٹ_بایاں(gb) < 1)
            واپس AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        اگر (params->color_saturation_mapping_flag) {
            اگر (get_بٹ_بایاں(gb) < 6)
                واپس AVERROR_INVALIDDATA;
            params->color_saturation_وزن =
                (AVRational){get_بٹ(gb, 6), saturation_وزن_den};
        }
    }

    واپس 0;
}

صحیح av_dynamic_hdr_plus_مقصد_t35(ثابت AVDynamicHDRPlus *s, uint8_t **ڈیٹا, size_t *سائز)
{
    uint8_t *buf;
    size_t سائز_بٹ, سائز_بائٹیں;
    Put_ثنائی_ہندسہ_Context pbc, *pb = &pbc;

    اگر (!s)
        واپس AVERROR(EINVAL);
    اگر ((!ڈیٹا || *ڈیٹا) && !سائز)
       واپس AVERROR(EINVAL);

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
    سائز_بٹ = 8;

    سائز_بٹ += 2;

    برائے (صحیح w = 1; w < s->عدد_windows; w++)
        سائز_بٹ += 153;

    سائز_بٹ += 27;

    سائز_بٹ += 1;
    اگر (s->targeted_system_display_actual_peak_luminance_flag)
        سائز_بٹ += 10 +
                     s->عدد_صفیں_targeted_system_display_actual_peak_luminance *
                     s->عدد_ستون_تعداد_targeted_system_display_actual_peak_luminance * 4;

    برائے (صحیح w = 0; w < s->عدد_windows; w++)
        سائز_بٹ += 72 + s->params[w].عدد_distribution_maxrgb_percentiles * 24 + 10;

    سائز_بٹ += 1;
    اگر (s->mastering_display_actual_peak_luminance_flag)
        سائز_بٹ += 10 +
                     s->عدد_صفیں_mastering_display_actual_peak_luminance *
                     s->عدد_ستون_تعداد_mastering_display_actual_peak_luminance * 4;

    برائے (صحیح w = 0; w < s->عدد_windows; w++) {
        سائز_بٹ += 1;
        اگر (s->params[w].tone_mapping_flag)
            سائز_بٹ += 28 + s->params[w].عدد_bezier_خم_anchors * 10;

        سائز_بٹ += 1;
        اگر (s->params[w].color_saturation_mapping_flag)
            سائز_بٹ += 6;
    }

    سائز_بائٹیں = (سائز_بٹ + 7) / 8;

    av_assert0(سائز_بائٹیں <= AV_HDR_PLUS_MAX_PAYLOAD_سائز);

    اگر (!ڈیٹا) {
        *سائز = سائز_بائٹیں;
        واپس 0;
    } ورنہ اگر (*ڈیٹا) {
        اگر (*سائز < سائز_بائٹیں)
            واپس AVERROR_بفر_TOO_SMALL;
        buf = *ڈیٹا;
    } ورنہ {
        buf = av_malloc(سائز_بائٹیں);
        اگر (!buf)
            واپس AVERROR(ENOMEM);
    }

    init_put_بٹ(pb, buf, سائز_بائٹیں);

    // application_mode is set to Application Version 1
    put_بٹ(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_بٹ(pb, 2, s->عدد_windows);

    برائے (صحیح w = 1; w < s->عدد_windows; w++) {
        put_بٹ(pb, 16, s->params[w].کھڑکی_بالائی_بایاں_کونا_x.عدد / s->params[w].کھڑکی_بالائی_بایاں_کونا_x.den);
        put_بٹ(pb, 16, s->params[w].کھڑکی_بالائی_بایاں_کونا_y.عدد / s->params[w].کھڑکی_بالائی_بایاں_کونا_y.den);
        put_بٹ(pb, 16, s->params[w].کھڑکی_زیریں_دایاں_کونا_x.عدد / s->params[w].کھڑکی_زیریں_دایاں_کونا_x.den);
        put_بٹ(pb, 16, s->params[w].کھڑکی_زیریں_دایاں_کونا_y.عدد / s->params[w].کھڑکی_زیریں_دایاں_کونا_y.den);
        put_بٹ(pb, 16, s->params[w].center_کا_ellipse_x);
        put_بٹ(pb, 16, s->params[w].center_کا_ellipse_y);
        put_بٹ(pb, 8, s->params[w].rotation_angle);
        put_بٹ(pb, 16, s->params[w].semimajor_axis_اندرونی_ellipse);
        put_بٹ(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_بٹ(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_بٹ(pb, 1, s->params[w].overlap_process_option);
    }

    put_بٹ(pb, 27, s->targeted_system_display_زیادہ_سے_زیادہ_luminance.عدد * luminance_den /
        s->targeted_system_display_زیادہ_سے_زیادہ_luminance.den);
    put_بٹ(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    اگر (s->targeted_system_display_actual_peak_luminance_flag) {
        put_بٹ(pb, 5, s->عدد_صفیں_targeted_system_display_actual_peak_luminance);
        put_بٹ(pb, 5, s->عدد_ستون_تعداد_targeted_system_display_actual_peak_luminance);
        برائے (صحیح i = 0; i < s->عدد_صفیں_targeted_system_display_actual_peak_luminance; i++) {
            برائے (صحیح j = 0; j < s->عدد_ستون_تعداد_targeted_system_display_actual_peak_luminance; j++)
                put_بٹ(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].عدد * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    برائے (صحیح w = 0; w < s->عدد_windows; w++) {
        برائے (صحیح i = 0; i < 3; i++)
            put_بٹ(pb, 17, s->params[w].maxscl[i].عدد * rgb_den / s->params[w].maxscl[i].den);
        put_بٹ(pb, 17, s->params[w].اوسط_قدر_maxrgb.عدد * rgb_den / s->params[w].اوسط_قدر_maxrgb.den);
        put_بٹ(pb, 4, s->params[w].عدد_distribution_maxrgb_percentiles);
        برائے (صحیح i = 0; i < s->params[w].عدد_distribution_maxrgb_percentiles; i++) {
            put_بٹ(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_بٹ(pb, 17, s->params[w].distribution_maxrgb[i].percentile.عدد * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_بٹ(pb, 10, s->params[w].fraction_bright_pixels.عدد * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_بٹ(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    اگر (s->mastering_display_actual_peak_luminance_flag) {
        put_بٹ(pb, 5, s->عدد_صفیں_mastering_display_actual_peak_luminance);
        put_بٹ(pb, 5, s->عدد_ستون_تعداد_mastering_display_actual_peak_luminance);
        برائے (صحیح i = 0; i < s->عدد_صفیں_mastering_display_actual_peak_luminance; i++) {
            برائے (صحیح j = 0; j < s->عدد_ستون_تعداد_mastering_display_actual_peak_luminance; j++)
                put_بٹ(pb, 4, s->mastering_display_actual_peak_luminance[i][j].عدد * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    برائے (صحیح w = 0; w < s->عدد_windows; w++) {
        put_بٹ(pb, 1, s->params[w].tone_mapping_flag);
        اگر (s->params[w].tone_mapping_flag) {
            put_بٹ(pb, 12, s->params[w].knee_نقطہ_x.عدد * knee_نقطہ_den / s->params[w].knee_نقطہ_x.den);
            put_بٹ(pb, 12, s->params[w].knee_نقطہ_y.عدد * knee_نقطہ_den / s->params[w].knee_نقطہ_y.den);
            put_بٹ(pb, 4, s->params[w].عدد_bezier_خم_anchors);
            برائے (صحیح i = 0; i < s->params[w].عدد_bezier_خم_anchors; i++)
                put_بٹ(pb, 10, s->params[w].bezier_خم_anchors[i].عدد * bezier_anchor_den /
                    s->params[w].bezier_خم_anchors[i].den);
        }
        put_بٹ(pb, 1, s->params[w].color_saturation_mapping_flag);
        اگر (s->params[w].color_saturation_mapping_flag)
            put_بٹ(pb, 6, s->params[w].color_saturation_وزن.عدد * saturation_وزن_den /
                s->params[w].color_saturation_وزن.den);
    }

    flush_put_بٹ(pb);

    *ڈیٹا = buf;
    اگر (سائز)
        *سائز = سائز_بائٹیں;
    واپس 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *سائز)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(حجم(AVDynamicHDRSmpte2094App5));

    اگر (سائز)
        *سائز = smpte2094_app5 ? حجم(*smpte2094_app5) : 0;

    واپس smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_ڈیٹا(AVFrame *چوکھٹا)
{
    AVFrame_Side_ڈیٹا *side_ڈیٹا = av_چوکھٹا_new_side_ڈیٹا(چوکھٹا,
                                                        AV_چوکھٹا_ڈیٹا_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        حجم(AVDynamicHDRSmpte2094App5));
    اگر (!side_ڈیٹا)
        واپس تہی;

    memset(side_ڈیٹا->ڈیٹا, 0, حجم(AVDynamicHDRSmpte2094App5));

    واپس (AVDynamicHDRSmpte2094App5 *)side_ڈیٹا->ڈیٹا;
}

#تعریف_کرو GET_بٹ_OR_FAIL(var, n)        \
    کرو {                                \
        اگر (get_بٹ_بایاں(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            جاؤ انتہا;                   \
        }                               \
        var = get_بٹ(gb, n);          \
    } جب (0)

صحیح av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, ثابت uint8_t *ڈیٹا,
                                           size_t سائز)
{
    Get_ثنائی_ہندسہ_Context gbc, *gb = &gbc;
    صحیح ret, reserved_zero;
    size_t padded_سائز = سائز + AV_داخلہ_بفر_PADDING_سائز;

    اگر (!s)
        واپس AVERROR(EINVAL);

    uint8_t *padded_ڈیٹا = av_mallocz(padded_سائز);
    اگر (!padded_ڈیٹا)
        واپس AVERROR(ENOMEM);

    حافظہ_نقل(padded_ڈیٹا, ڈیٹا, سائز);
    ret = init_get_bits8(gb, padded_ڈیٹا, سائز);
    اگر (ret < 0)
        جاؤ انتہا;

    // Table C.1
    GET_بٹ_OR_FAIL(s->application_نسخہ, 3);
    GET_بٹ_OR_FAIL(s->minimum_application_نسخہ, 3);
    GET_بٹ_OR_FAIL(reserved_zero, 2);
    اگر (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        جاؤ انتہا;
    }

    // Table C.2
    GET_بٹ_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_بٹ_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_بٹ_OR_FAIL(reserved_zero, 6);
    اگر (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        جاؤ انتہا;
    }
    اگر (s->has_custom_hdr_reference_white_flag)
        GET_بٹ_OR_FAIL(s->hdr_reference_white, 16);
    اگر (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        جاؤ انتہا;
    }

    // Table C.3
    GET_بٹ_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_بٹ_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    اگر (s->use_reference_white_tone_mapping_flag) {
        GET_بٹ_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        جاؤ انتہا;
    }
    GET_بٹ_OR_FAIL(s->عدد_alternate_images, 3);
    اگر (s->عدد_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        جاؤ انتہا;
    }
    GET_بٹ_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_بٹ_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_بٹ_OR_FAIL(s->has_common_خم_params_flag, 1);
    اگر (s->gain_application_space_chromaticities_flag == 3)
        برائے (صحیح r = 0; r < 8; r++)
            GET_بٹ_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    برائے (صحیح a = 0; a < s->عدد_alternate_images; a++) {
        GET_بٹ_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        اگر (!a || !s->has_common_component_mix_params_flag) {
            GET_بٹ_OR_FAIL(s->component_mixing_type[a], 2);
            اگر (s->component_mixing_type[a] != 3) {
                GET_بٹ_OR_FAIL(reserved_zero, 6);
                اگر (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    جاؤ انتہا;
                }
            } ورنہ {
                برائے (صحیح k = 0; k < 6; k++)
                    GET_بٹ_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                برائے (صحیح k = 0; k < 6; k++) {
                    اگر (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_بٹ_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } ورنہ {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } ورنہ {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            اگر (s->component_mixing_type[a] == 3) {
                برائے (صحیح k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        اگر (!a || !s->has_common_خم_params_flag) {
            GET_بٹ_OR_FAIL(s->gain_خم_عدد_control_points_minus_1[a], 5);
            اگر (s->gain_خم_عدد_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                جاؤ انتہا;
            }
            GET_بٹ_OR_FAIL(s->gain_خم_use_pchip_ڈھلان_flag[a], 1);
            GET_بٹ_OR_FAIL(reserved_zero, 2);
            اگر (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                جاؤ انتہا;
            }
            برائے (صحیح c = 0; c <= s->gain_خم_عدد_control_points_minus_1[a]; c++) {
                GET_بٹ_OR_FAIL(s->gain_خم_control_points_x[a][c], 16);
            }
        } ورنہ {
            s->gain_خم_عدد_control_points_minus_1[a] =
                    s->gain_خم_عدد_control_points_minus_1[0];
            s->gain_خم_use_pchip_ڈھلان_flag[a] = s->gain_خم_use_pchip_ڈھلان_flag[0];
            برائے (صحیح c = 0; c <= s->gain_خم_عدد_control_points_minus_1[a]; c++) {
                s->gain_خم_control_points_x[a][c] = s->gain_خم_control_points_x[0][c];
            }
        }
        برائے (صحیح c = 0; c <= s->gain_خم_عدد_control_points_minus_1[a]; c++)
            GET_بٹ_OR_FAIL(s->gain_خم_control_points_y[a][c], 16);
        اگر (!s->gain_خم_use_pchip_ڈھلان_flag[a]) {
            برائے (صحیح c = 0; c <= s->gain_خم_عدد_control_points_minus_1[a]; c++)
                GET_بٹ_OR_FAIL(s->gain_خم_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
انتہا:
    av_free(padded_ڈیٹا);
    واپس ret;
}

صحیح av_dynamic_hdr_smpte2094_app5_مقصد_t35(ثابت AVDynamicHDRSmpte2094App5 *s, uint8_t **ڈیٹا,
                                         size_t *سائز)
{
    uint8_t *buf;
    size_t سائز_بائٹیں, سائز_بٹ;
    Put_ثنائی_ہندسہ_Context pbc, *pb = &pbc;

    اگر (!s)
        واپس AVERROR(EINVAL);
    اگر ((!ڈیٹا || *ڈیٹا) && !سائز)
       واپس AVERROR(EINVAL);

    اگر (s->application_نسخہ >= 8 || s->minimum_application_نسخہ >= 3)
        واپس AVERROR_INVALIDDATA;
    سائز_بٹ = 0;
    سائز_بٹ += 3 + 3 + 2;
    سائز_بٹ += 1 + 1 + 6;
    اگر (s->has_custom_hdr_reference_white_flag)
        سائز_بٹ += 16;
    اگر (s->has_adaptive_tone_map_flag) {
        سائز_بٹ += 16 + 1;
        اگر (s->use_reference_white_tone_mapping_flag) {
            سائز_بٹ += 7;
        } ورنہ {
            سائز_بٹ += 3 + 2 + 1 + 1;
            اگر (s->gain_application_space_chromaticities_flag == 3)
                سائز_بٹ += 16 * 8;
            اگر (s->عدد_alternate_images > 4)
                واپس AVERROR_INVALIDDATA;
            برائے (صحیح a = 0; a < s->عدد_alternate_images; a++) {
                سائز_بٹ += 16;
                اگر (!a || !s->has_common_component_mix_params_flag) {
                    سائز_بٹ += 2;
                    اگر (s->component_mixing_type[a] != 3) {
                        سائز_بٹ += 6;
                    } ورنہ {
                        سائز_بٹ += 6;
                        برائے (صحیح k = 0; k < 6; k++)
                          اگر (s->has_component_mixing_coefficient_flag[a][k])
                            سائز_بٹ += 16;
                    }
                }
                اگر (!a || !s->has_common_خم_params_flag) {
                    سائز_بٹ += 5 + 1 + 2;
                    اگر (s->gain_خم_عدد_control_points_minus_1[a] > 31)
                        واپس AVERROR_INVALIDDATA;
                    سائز_بٹ += 16 * (s->gain_خم_عدد_control_points_minus_1[a] + 1);
                }
                سائز_بٹ += 16 * (s->gain_خم_عدد_control_points_minus_1[a] + 1);
                اگر (!s->gain_خم_use_pchip_ڈھلان_flag[a])
                    سائز_بٹ += 16 * (s->gain_خم_عدد_control_points_minus_1[a] + 1);
            }
        }
    }
    اگر (سائز_بٹ % 8)
      واپس AVERROR_INVALIDDATA;
    سائز_بائٹیں = سائز_بٹ >> 3;

    اگر (!ڈیٹا) {
        *سائز = سائز_بائٹیں;
        واپس 0;
    } ورنہ اگر (*ڈیٹا) {
        اگر (*سائز < سائز_بائٹیں)
            واپس AVERROR_بفر_TOO_SMALL;
        buf = *ڈیٹا;
    } ورنہ {
        buf = av_malloc(سائز_بائٹیں);
        اگر (!buf)
            واپس AVERROR(ENOMEM);
    }

    init_put_بٹ(pb, buf, سائز_بائٹیں);

    // Table C.1
    put_بٹ(pb, 3, s->application_نسخہ);
    put_بٹ(pb, 3, s->minimum_application_نسخہ);
    put_بٹ(pb, 2, 0); // reserved_zero

    // Table C.2
    put_بٹ(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_بٹ(pb, 1, s->has_adaptive_tone_map_flag);
    put_بٹ(pb, 6, 0); // reserved_zero

    اگر (s->has_custom_hdr_reference_white_flag)
        put_بٹ(pb, 16, s->hdr_reference_white);

    اگر (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_بٹ(pb, 16, s->baseline_hdr_headroom);
        put_بٹ(pb, 1, s->use_reference_white_tone_mapping_flag);
        اگر (s->use_reference_white_tone_mapping_flag) {
            put_بٹ(pb, 7, 0); // reserved_zero
        } ورنہ {
            put_بٹ(pb, 3, s->عدد_alternate_images);
            put_بٹ(pb, 2, s->gain_application_space_chromaticities_flag);
            put_بٹ(pb, 1, s->has_common_component_mix_params_flag);
            put_بٹ(pb, 1, s->has_common_خم_params_flag);

            اگر (s->gain_application_space_chromaticities_flag == 3)
                برائے (صحیح r = 0; r < 8; r++)
                    put_بٹ(pb, 16, s->gain_application_space_chromaticities[r]);

            برائے (صحیح a = 0; a < s->عدد_alternate_images; a++) {
                put_بٹ(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                اگر (!a || !s->has_common_component_mix_params_flag) {
                    put_بٹ(pb, 2, s->component_mixing_type[a]);
                    اگر (s->component_mixing_type[a] != 3) {
                        put_بٹ(pb, 6, 0); // reserved_zero
                    } ورنہ {
                        برائے (صحیح k = 0; k < 6; k++)
                            put_بٹ(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        برائے (صحیح k = 0; k < 6; k++)
                            اگر (s->has_component_mixing_coefficient_flag[a][k])
                                put_بٹ(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                اگر (!a || !s->has_common_خم_params_flag) {
                    put_بٹ(pb, 5, s->gain_خم_عدد_control_points_minus_1[a]);
                    put_بٹ(pb, 1, s->gain_خم_use_pchip_ڈھلان_flag[a]);
                    put_بٹ(pb, 2, 0); // reserved_zero
                    برائے (صحیح c = 0; c <= s->gain_خم_عدد_control_points_minus_1[a]; c++)
                        put_بٹ(pb, 16, s->gain_خم_control_points_x[a][c]);
                }
                برائے (صحیح c = 0; c <= s->gain_خم_عدد_control_points_minus_1[a]; c++)
                    put_بٹ(pb, 16, s->gain_خم_control_points_y[a][c]);
                اگر (!s->gain_خم_use_pchip_ڈھلان_flag[a]) {
                    برائے (صحیح c = 0; c <= s->gain_خم_عدد_control_points_minus_1[a]; c++)
                        put_بٹ(pb, 16, s->gain_خم_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_بٹ(pb);

    *ڈیٹا = buf;
    اگر (سائز)
        *سائز = سائز_بائٹیں;
    واپس 0;
}

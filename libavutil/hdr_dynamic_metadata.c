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

#ضمن "avassert.h"
#ضمن "hdr_dynamic_metadata.h"
#ضمن "mem.h"
#ضمن "libavcodec/defs.h"
#ضمن "libavcodec/get_bits.h"
#ضمن "libavcodec/put_bits.h"

ساكن ثابت int64_t luminance_den = 1;
ساكن ثابت int32_t peak_luminance_den = 15;
ساكن ثابت int64_t rgb_den = 100000;
ساكن ثابت int32_t fraction_pixel_den = 1000;
ساكن ثابت int32_t knee_نقطہ_den = 4095;
ساكن ثابت int32_t bezier_anchor_den = 1023;
ساكن ثابت int32_t saturation_بھار_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *ناپ)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(حجم(AVDynamicHDRPlus));

    إذا (ناپ)
        *ناپ = hdr_plus ? حجم(*hdr_plus) : 0;

    أرجع hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_انکڑے(AVFrame *چوکھٹا)
{
    AVFrame_Side_انکڑے *side_انکڑے = av_چوکھٹا_new_side_انکڑے(چوکھٹا,
                                                        AV_چوکھٹا_انکڑے_DYNAMIC_HDR_PLUS,
                                                        حجم(AVDynamicHDRPlus));
    إذا (!side_انکڑے)
        أرجع عدم;

    memset(side_انکڑے->انکڑے, 0, حجم(AVDynamicHDRPlus));

    أرجع (AVDynamicHDRPlus *)side_انکڑے->انکڑے;
}

صحيح av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, ثابت uint8_t *انکڑے,
                                 size_t ناپ)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_ناپ + AV_داخلہ_بفر_PADDING_ناپ];
    Get_ثنائی_ہندسہ_Context gbc, *gb = &gbc;
    صحيح ret;

    إذا (!s)
        أرجع AVERROR(EINVAL);

    إذا (ناپ > AV_HDR_PLUS_MAX_PAYLOAD_ناپ)
        أرجع AVERROR(EINVAL);

    حافظہ_نقل(padded_buf, انکڑے, ناپ);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + ناپ, 0, AV_داخلہ_بفر_PADDING_ناپ);

    ret = init_get_bits8(gb, padded_buf, ناپ);
    إذا (ret < 0)
        أرجع ret;

    إذا (get_بٹ_بایاں(gb) < 10)
        أرجع AVERROR_INVALIDDATA;

    s->application_نسخہ = get_بٹ(gb, 8);
    s->عدد_windows = get_بٹ(gb, 2);

    إذا (s->عدد_windows < 1 || s->عدد_windows > 3) {
        أرجع AVERROR_INVALIDDATA;
    }

    إذا (get_بٹ_بایاں(gb) < ((19 * 8 + 1) * (s->عدد_windows - 1)))
        أرجع AVERROR_INVALIDDATA;

    لكل (صحيح w = 1; w < s->عدد_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->کھڑکی_اتلا_بایاں_کونا_x =
            (AVRational){get_بٹ(gb, 16), 1};
        params->کھڑکی_اتلا_بایاں_کونا_y =
            (AVRational){get_بٹ(gb, 16), 1};
        params->کھڑکی_ہیٹھلا_دایاں_کونا_x =
            (AVRational){get_بٹ(gb, 16), 1};
        params->کھڑکی_ہیٹھلا_دایاں_کونا_y =
            (AVRational){get_بٹ(gb, 16), 1};

        params->center_دا_ellipse_x = get_بٹ(gb, 16);
        params->center_دا_ellipse_y = get_بٹ(gb, 16);
        params->rotation_angle = get_بٹ(gb, 8);
        params->semimajor_axis_اندرونی_ellipse = get_بٹ(gb, 16);
        params->semimajor_axis_external_ellipse = get_بٹ(gb, 16);
        params->semiminor_axis_external_ellipse = get_بٹ(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    إذا (get_بٹ_بایاں(gb) < 28)
        أرجع AVERROR_INVALIDDATA;

    s->targeted_system_display_ودھ_توں_ودھ_luminance =
        (AVRational){get_بٹ_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    إذا (s->targeted_system_display_actual_peak_luminance_flag) {
        صحيح صفاں, خانے_گنتی;
        إذا (get_بٹ_بایاں(gb) < 10)
            أرجع AVERROR_INVALIDDATA;
        صفاں = get_بٹ(gb, 5);
        خانے_گنتی = get_بٹ(gb, 5);
        إذا (((صفاں < 2) || (صفاں > 25)) || ((خانے_گنتی < 2) || (خانے_گنتی > 25))) {
            أرجع AVERROR_INVALIDDATA;
        }
        s->عدد_صفاں_targeted_system_display_actual_peak_luminance = صفاں;
        s->عدد_خانے_گنتی_targeted_system_display_actual_peak_luminance = خانے_گنتی;

        إذا (get_بٹ_بایاں(gb) < (صفاں * خانے_گنتی * 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < صفاں; i++) {
            لكل (صحيح j = 0; j < خانے_گنتی; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بٹ(gb, 4), peak_luminance_den};
            }
        }
    }
    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        إذا (get_بٹ_بایاں(gb) < (3 * 17 + 17 + 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_بٹ(gb, 17), rgb_den};
        }
        params->اوسطن_maxrgb =
            (AVRational){get_بٹ(gb, 17), rgb_den};
        params->عدد_distribution_maxrgb_percentiles = get_بٹ(gb, 4);

        إذا (get_بٹ_بایاں(gb) <
            (params->عدد_distribution_maxrgb_percentiles * 24))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < params->عدد_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_بٹ(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_بٹ(gb, 17), rgb_den};
        }

        إذا (get_بٹ_بایاں(gb) < 10)
            أرجع AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_بٹ(gb, 10), fraction_pixel_den};
    }
    إذا (get_بٹ_بایاں(gb) < 1)
        أرجع AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    إذا (s->mastering_display_actual_peak_luminance_flag) {
        صحيح صفاں, خانے_گنتی;
        إذا (get_بٹ_بایاں(gb) < 10)
            أرجع AVERROR_INVALIDDATA;
        صفاں = get_بٹ(gb, 5);
        خانے_گنتی = get_بٹ(gb, 5);
        إذا (((صفاں < 2) || (صفاں > 25)) || ((خانے_گنتی < 2) || (خانے_گنتی > 25))) {
            أرجع AVERROR_INVALIDDATA;
        }
        s->عدد_صفاں_mastering_display_actual_peak_luminance = صفاں;
        s->عدد_خانے_گنتی_mastering_display_actual_peak_luminance = خانے_گنتی;

        إذا (get_بٹ_بایاں(gb) < (صفاں * خانے_گنتی * 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < صفاں; i++) {
            لكل (صحيح j = 0; j < خانے_گنتی; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بٹ(gb, 4), peak_luminance_den};
            }
        }
    }

    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        إذا (get_بٹ_بایاں(gb) < 1)
            أرجع AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        إذا (params->tone_mapping_flag) {
            إذا (get_بٹ_بایاں(gb) < 28)
                أرجع AVERROR_INVALIDDATA;

            params->knee_نقطہ_x =
                (AVRational){get_بٹ(gb, 12), knee_نقطہ_den};
            params->knee_نقطہ_y =
                (AVRational){get_بٹ(gb, 12), knee_نقطہ_den};
            params->عدد_bezier_ونگ_anchors = get_بٹ(gb, 4);

            إذا (get_بٹ_بایاں(gb) < (params->عدد_bezier_ونگ_anchors * 10))
                أرجع AVERROR_INVALIDDATA;

            لكل (صحيح i = 0; i < params->عدد_bezier_ونگ_anchors; i++) {
                params->bezier_ونگ_anchors[i] =
                    (AVRational){get_بٹ(gb, 10), bezier_anchor_den};
            }
        }

        إذا (get_بٹ_بایاں(gb) < 1)
            أرجع AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        إذا (params->color_saturation_mapping_flag) {
            إذا (get_بٹ_بایاں(gb) < 6)
                أرجع AVERROR_INVALIDDATA;
            params->color_saturation_بھار =
                (AVRational){get_بٹ(gb, 6), saturation_بھار_den};
        }
    }

    أرجع 0;
}

صحيح av_dynamic_hdr_plus_منزل_t35(ثابت AVDynamicHDRPlus *s, uint8_t **انکڑے, size_t *ناپ)
{
    uint8_t *buf;
    size_t ناپ_بٹ, ناپ_بائٹاں;
    Put_ثنائی_ہندسہ_Context pbc, *pb = &pbc;

    إذا (!s)
        أرجع AVERROR(EINVAL);
    إذا ((!انکڑے || *انکڑے) && !ناپ)
       أرجع AVERROR(EINVAL);

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
    ناپ_بٹ = 8;

    ناپ_بٹ += 2;

    لكل (صحيح w = 1; w < s->عدد_windows; w++)
        ناپ_بٹ += 153;

    ناپ_بٹ += 27;

    ناپ_بٹ += 1;
    إذا (s->targeted_system_display_actual_peak_luminance_flag)
        ناپ_بٹ += 10 +
                     s->عدد_صفاں_targeted_system_display_actual_peak_luminance *
                     s->عدد_خانے_گنتی_targeted_system_display_actual_peak_luminance * 4;

    لكل (صحيح w = 0; w < s->عدد_windows; w++)
        ناپ_بٹ += 72 + s->params[w].عدد_distribution_maxrgb_percentiles * 24 + 10;

    ناپ_بٹ += 1;
    إذا (s->mastering_display_actual_peak_luminance_flag)
        ناپ_بٹ += 10 +
                     s->عدد_صفاں_mastering_display_actual_peak_luminance *
                     s->عدد_خانے_گنتی_mastering_display_actual_peak_luminance * 4;

    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        ناپ_بٹ += 1;
        إذا (s->params[w].tone_mapping_flag)
            ناپ_بٹ += 28 + s->params[w].عدد_bezier_ونگ_anchors * 10;

        ناپ_بٹ += 1;
        إذا (s->params[w].color_saturation_mapping_flag)
            ناپ_بٹ += 6;
    }

    ناپ_بائٹاں = (ناپ_بٹ + 7) / 8;

    av_assert0(ناپ_بائٹاں <= AV_HDR_PLUS_MAX_PAYLOAD_ناپ);

    إذا (!انکڑے) {
        *ناپ = ناپ_بائٹاں;
        أرجع 0;
    } وإلا إذا (*انکڑے) {
        إذا (*ناپ < ناپ_بائٹاں)
            أرجع AVERROR_بفر_TOO_SMALL;
        buf = *انکڑے;
    } وإلا {
        buf = av_malloc(ناپ_بائٹاں);
        إذا (!buf)
            أرجع AVERROR(ENOMEM);
    }

    init_put_بٹ(pb, buf, ناپ_بائٹاں);

    // application_mode is set to Application Version 1
    put_بٹ(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_بٹ(pb, 2, s->عدد_windows);

    لكل (صحيح w = 1; w < s->عدد_windows; w++) {
        put_بٹ(pb, 16, s->params[w].کھڑکی_اتلا_بایاں_کونا_x.عدد / s->params[w].کھڑکی_اتلا_بایاں_کونا_x.den);
        put_بٹ(pb, 16, s->params[w].کھڑکی_اتلا_بایاں_کونا_y.عدد / s->params[w].کھڑکی_اتلا_بایاں_کونا_y.den);
        put_بٹ(pb, 16, s->params[w].کھڑکی_ہیٹھلا_دایاں_کونا_x.عدد / s->params[w].کھڑکی_ہیٹھلا_دایاں_کونا_x.den);
        put_بٹ(pb, 16, s->params[w].کھڑکی_ہیٹھلا_دایاں_کونا_y.عدد / s->params[w].کھڑکی_ہیٹھلا_دایاں_کونا_y.den);
        put_بٹ(pb, 16, s->params[w].center_دا_ellipse_x);
        put_بٹ(pb, 16, s->params[w].center_دا_ellipse_y);
        put_بٹ(pb, 8, s->params[w].rotation_angle);
        put_بٹ(pb, 16, s->params[w].semimajor_axis_اندرونی_ellipse);
        put_بٹ(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_بٹ(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_بٹ(pb, 1, s->params[w].overlap_process_option);
    }

    put_بٹ(pb, 27, s->targeted_system_display_ودھ_توں_ودھ_luminance.عدد * luminance_den /
        s->targeted_system_display_ودھ_توں_ودھ_luminance.den);
    put_بٹ(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    إذا (s->targeted_system_display_actual_peak_luminance_flag) {
        put_بٹ(pb, 5, s->عدد_صفاں_targeted_system_display_actual_peak_luminance);
        put_بٹ(pb, 5, s->عدد_خانے_گنتی_targeted_system_display_actual_peak_luminance);
        لكل (صحيح i = 0; i < s->عدد_صفاں_targeted_system_display_actual_peak_luminance; i++) {
            لكل (صحيح j = 0; j < s->عدد_خانے_گنتی_targeted_system_display_actual_peak_luminance; j++)
                put_بٹ(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].عدد * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        لكل (صحيح i = 0; i < 3; i++)
            put_بٹ(pb, 17, s->params[w].maxscl[i].عدد * rgb_den / s->params[w].maxscl[i].den);
        put_بٹ(pb, 17, s->params[w].اوسطن_maxrgb.عدد * rgb_den / s->params[w].اوسطن_maxrgb.den);
        put_بٹ(pb, 4, s->params[w].عدد_distribution_maxrgb_percentiles);
        لكل (صحيح i = 0; i < s->params[w].عدد_distribution_maxrgb_percentiles; i++) {
            put_بٹ(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_بٹ(pb, 17, s->params[w].distribution_maxrgb[i].percentile.عدد * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_بٹ(pb, 10, s->params[w].fraction_bright_pixels.عدد * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_بٹ(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    إذا (s->mastering_display_actual_peak_luminance_flag) {
        put_بٹ(pb, 5, s->عدد_صفاں_mastering_display_actual_peak_luminance);
        put_بٹ(pb, 5, s->عدد_خانے_گنتی_mastering_display_actual_peak_luminance);
        لكل (صحيح i = 0; i < s->عدد_صفاں_mastering_display_actual_peak_luminance; i++) {
            لكل (صحيح j = 0; j < s->عدد_خانے_گنتی_mastering_display_actual_peak_luminance; j++)
                put_بٹ(pb, 4, s->mastering_display_actual_peak_luminance[i][j].عدد * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        put_بٹ(pb, 1, s->params[w].tone_mapping_flag);
        إذا (s->params[w].tone_mapping_flag) {
            put_بٹ(pb, 12, s->params[w].knee_نقطہ_x.عدد * knee_نقطہ_den / s->params[w].knee_نقطہ_x.den);
            put_بٹ(pb, 12, s->params[w].knee_نقطہ_y.عدد * knee_نقطہ_den / s->params[w].knee_نقطہ_y.den);
            put_بٹ(pb, 4, s->params[w].عدد_bezier_ونگ_anchors);
            لكل (صحيح i = 0; i < s->params[w].عدد_bezier_ونگ_anchors; i++)
                put_بٹ(pb, 10, s->params[w].bezier_ونگ_anchors[i].عدد * bezier_anchor_den /
                    s->params[w].bezier_ونگ_anchors[i].den);
        }
        put_بٹ(pb, 1, s->params[w].color_saturation_mapping_flag);
        إذا (s->params[w].color_saturation_mapping_flag)
            put_بٹ(pb, 6, s->params[w].color_saturation_بھار.عدد * saturation_بھار_den /
                s->params[w].color_saturation_بھار.den);
    }

    flush_put_بٹ(pb);

    *انکڑے = buf;
    إذا (ناپ)
        *ناپ = ناپ_بائٹاں;
    أرجع 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *ناپ)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(حجم(AVDynamicHDRSmpte2094App5));

    إذا (ناپ)
        *ناپ = smpte2094_app5 ? حجم(*smpte2094_app5) : 0;

    أرجع smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_انکڑے(AVFrame *چوکھٹا)
{
    AVFrame_Side_انکڑے *side_انکڑے = av_چوکھٹا_new_side_انکڑے(چوکھٹا,
                                                        AV_چوکھٹا_انکڑے_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        حجم(AVDynamicHDRSmpte2094App5));
    إذا (!side_انکڑے)
        أرجع عدم;

    memset(side_انکڑے->انکڑے, 0, حجم(AVDynamicHDRSmpte2094App5));

    أرجع (AVDynamicHDRSmpte2094App5 *)side_انکڑے->انکڑے;
}

#تعریف_کرو GET_بٹ_OR_FAIL(var, n)        \
    افعل {                                \
        إذا (get_بٹ_بایاں(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            اذهب سرا;                   \
        }                               \
        var = get_بٹ(gb, n);          \
    } طالما (0)

صحيح av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, ثابت uint8_t *انکڑے,
                                           size_t ناپ)
{
    Get_ثنائی_ہندسہ_Context gbc, *gb = &gbc;
    صحيح ret, reserved_zero;
    size_t padded_ناپ = ناپ + AV_داخلہ_بفر_PADDING_ناپ;

    إذا (!s)
        أرجع AVERROR(EINVAL);

    uint8_t *padded_انکڑے = av_mallocz(padded_ناپ);
    إذا (!padded_انکڑے)
        أرجع AVERROR(ENOMEM);

    حافظہ_نقل(padded_انکڑے, انکڑے, ناپ);
    ret = init_get_bits8(gb, padded_انکڑے, ناپ);
    إذا (ret < 0)
        اذهب سرا;

    // Table C.1
    GET_بٹ_OR_FAIL(s->application_نسخہ, 3);
    GET_بٹ_OR_FAIL(s->minimum_application_نسخہ, 3);
    GET_بٹ_OR_FAIL(reserved_zero, 2);
    إذا (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        اذهب سرا;
    }

    // Table C.2
    GET_بٹ_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_بٹ_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_بٹ_OR_FAIL(reserved_zero, 6);
    إذا (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        اذهب سرا;
    }
    إذا (s->has_custom_hdr_reference_white_flag)
        GET_بٹ_OR_FAIL(s->hdr_reference_white, 16);
    إذا (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        اذهب سرا;
    }

    // Table C.3
    GET_بٹ_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_بٹ_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    إذا (s->use_reference_white_tone_mapping_flag) {
        GET_بٹ_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        اذهب سرا;
    }
    GET_بٹ_OR_FAIL(s->عدد_alternate_images, 3);
    إذا (s->عدد_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        اذهب سرا;
    }
    GET_بٹ_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_بٹ_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_بٹ_OR_FAIL(s->has_common_ونگ_params_flag, 1);
    إذا (s->gain_application_space_chromaticities_flag == 3)
        لكل (صحيح r = 0; r < 8; r++)
            GET_بٹ_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    لكل (صحيح a = 0; a < s->عدد_alternate_images; a++) {
        GET_بٹ_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        إذا (!a || !s->has_common_component_mix_params_flag) {
            GET_بٹ_OR_FAIL(s->component_mixing_type[a], 2);
            إذا (s->component_mixing_type[a] != 3) {
                GET_بٹ_OR_FAIL(reserved_zero, 6);
                إذا (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    اذهب سرا;
                }
            } وإلا {
                لكل (صحيح k = 0; k < 6; k++)
                    GET_بٹ_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                لكل (صحيح k = 0; k < 6; k++) {
                    إذا (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_بٹ_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } وإلا {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } وإلا {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            إذا (s->component_mixing_type[a] == 3) {
                لكل (صحيح k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        إذا (!a || !s->has_common_ونگ_params_flag) {
            GET_بٹ_OR_FAIL(s->gain_ونگ_عدد_control_points_minus_1[a], 5);
            إذا (s->gain_ونگ_عدد_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                اذهب سرا;
            }
            GET_بٹ_OR_FAIL(s->gain_ونگ_use_pchip_ڈھلوان_flag[a], 1);
            GET_بٹ_OR_FAIL(reserved_zero, 2);
            إذا (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                اذهب سرا;
            }
            لكل (صحيح c = 0; c <= s->gain_ونگ_عدد_control_points_minus_1[a]; c++) {
                GET_بٹ_OR_FAIL(s->gain_ونگ_control_points_x[a][c], 16);
            }
        } وإلا {
            s->gain_ونگ_عدد_control_points_minus_1[a] =
                    s->gain_ونگ_عدد_control_points_minus_1[0];
            s->gain_ونگ_use_pchip_ڈھلوان_flag[a] = s->gain_ونگ_use_pchip_ڈھلوان_flag[0];
            لكل (صحيح c = 0; c <= s->gain_ونگ_عدد_control_points_minus_1[a]; c++) {
                s->gain_ونگ_control_points_x[a][c] = s->gain_ونگ_control_points_x[0][c];
            }
        }
        لكل (صحيح c = 0; c <= s->gain_ونگ_عدد_control_points_minus_1[a]; c++)
            GET_بٹ_OR_FAIL(s->gain_ونگ_control_points_y[a][c], 16);
        إذا (!s->gain_ونگ_use_pchip_ڈھلوان_flag[a]) {
            لكل (صحيح c = 0; c <= s->gain_ونگ_عدد_control_points_minus_1[a]; c++)
                GET_بٹ_OR_FAIL(s->gain_ونگ_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
سرا:
    av_free(padded_انکڑے);
    أرجع ret;
}

صحيح av_dynamic_hdr_smpte2094_app5_منزل_t35(ثابت AVDynamicHDRSmpte2094App5 *s, uint8_t **انکڑے,
                                         size_t *ناپ)
{
    uint8_t *buf;
    size_t ناپ_بائٹاں, ناپ_بٹ;
    Put_ثنائی_ہندسہ_Context pbc, *pb = &pbc;

    إذا (!s)
        أرجع AVERROR(EINVAL);
    إذا ((!انکڑے || *انکڑے) && !ناپ)
       أرجع AVERROR(EINVAL);

    إذا (s->application_نسخہ >= 8 || s->minimum_application_نسخہ >= 3)
        أرجع AVERROR_INVALIDDATA;
    ناپ_بٹ = 0;
    ناپ_بٹ += 3 + 3 + 2;
    ناپ_بٹ += 1 + 1 + 6;
    إذا (s->has_custom_hdr_reference_white_flag)
        ناپ_بٹ += 16;
    إذا (s->has_adaptive_tone_map_flag) {
        ناپ_بٹ += 16 + 1;
        إذا (s->use_reference_white_tone_mapping_flag) {
            ناپ_بٹ += 7;
        } وإلا {
            ناپ_بٹ += 3 + 2 + 1 + 1;
            إذا (s->gain_application_space_chromaticities_flag == 3)
                ناپ_بٹ += 16 * 8;
            إذا (s->عدد_alternate_images > 4)
                أرجع AVERROR_INVALIDDATA;
            لكل (صحيح a = 0; a < s->عدد_alternate_images; a++) {
                ناپ_بٹ += 16;
                إذا (!a || !s->has_common_component_mix_params_flag) {
                    ناپ_بٹ += 2;
                    إذا (s->component_mixing_type[a] != 3) {
                        ناپ_بٹ += 6;
                    } وإلا {
                        ناپ_بٹ += 6;
                        لكل (صحيح k = 0; k < 6; k++)
                          إذا (s->has_component_mixing_coefficient_flag[a][k])
                            ناپ_بٹ += 16;
                    }
                }
                إذا (!a || !s->has_common_ونگ_params_flag) {
                    ناپ_بٹ += 5 + 1 + 2;
                    إذا (s->gain_ونگ_عدد_control_points_minus_1[a] > 31)
                        أرجع AVERROR_INVALIDDATA;
                    ناپ_بٹ += 16 * (s->gain_ونگ_عدد_control_points_minus_1[a] + 1);
                }
                ناپ_بٹ += 16 * (s->gain_ونگ_عدد_control_points_minus_1[a] + 1);
                إذا (!s->gain_ونگ_use_pchip_ڈھلوان_flag[a])
                    ناپ_بٹ += 16 * (s->gain_ونگ_عدد_control_points_minus_1[a] + 1);
            }
        }
    }
    إذا (ناپ_بٹ % 8)
      أرجع AVERROR_INVALIDDATA;
    ناپ_بائٹاں = ناپ_بٹ >> 3;

    إذا (!انکڑے) {
        *ناپ = ناپ_بائٹاں;
        أرجع 0;
    } وإلا إذا (*انکڑے) {
        إذا (*ناپ < ناپ_بائٹاں)
            أرجع AVERROR_بفر_TOO_SMALL;
        buf = *انکڑے;
    } وإلا {
        buf = av_malloc(ناپ_بائٹاں);
        إذا (!buf)
            أرجع AVERROR(ENOMEM);
    }

    init_put_بٹ(pb, buf, ناپ_بائٹاں);

    // Table C.1
    put_بٹ(pb, 3, s->application_نسخہ);
    put_بٹ(pb, 3, s->minimum_application_نسخہ);
    put_بٹ(pb, 2, 0); // reserved_zero

    // Table C.2
    put_بٹ(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_بٹ(pb, 1, s->has_adaptive_tone_map_flag);
    put_بٹ(pb, 6, 0); // reserved_zero

    إذا (s->has_custom_hdr_reference_white_flag)
        put_بٹ(pb, 16, s->hdr_reference_white);

    إذا (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_بٹ(pb, 16, s->baseline_hdr_headroom);
        put_بٹ(pb, 1, s->use_reference_white_tone_mapping_flag);
        إذا (s->use_reference_white_tone_mapping_flag) {
            put_بٹ(pb, 7, 0); // reserved_zero
        } وإلا {
            put_بٹ(pb, 3, s->عدد_alternate_images);
            put_بٹ(pb, 2, s->gain_application_space_chromaticities_flag);
            put_بٹ(pb, 1, s->has_common_component_mix_params_flag);
            put_بٹ(pb, 1, s->has_common_ونگ_params_flag);

            إذا (s->gain_application_space_chromaticities_flag == 3)
                لكل (صحيح r = 0; r < 8; r++)
                    put_بٹ(pb, 16, s->gain_application_space_chromaticities[r]);

            لكل (صحيح a = 0; a < s->عدد_alternate_images; a++) {
                put_بٹ(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                إذا (!a || !s->has_common_component_mix_params_flag) {
                    put_بٹ(pb, 2, s->component_mixing_type[a]);
                    إذا (s->component_mixing_type[a] != 3) {
                        put_بٹ(pb, 6, 0); // reserved_zero
                    } وإلا {
                        لكل (صحيح k = 0; k < 6; k++)
                            put_بٹ(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        لكل (صحيح k = 0; k < 6; k++)
                            إذا (s->has_component_mixing_coefficient_flag[a][k])
                                put_بٹ(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                إذا (!a || !s->has_common_ونگ_params_flag) {
                    put_بٹ(pb, 5, s->gain_ونگ_عدد_control_points_minus_1[a]);
                    put_بٹ(pb, 1, s->gain_ونگ_use_pchip_ڈھلوان_flag[a]);
                    put_بٹ(pb, 2, 0); // reserved_zero
                    لكل (صحيح c = 0; c <= s->gain_ونگ_عدد_control_points_minus_1[a]; c++)
                        put_بٹ(pb, 16, s->gain_ونگ_control_points_x[a][c]);
                }
                لكل (صحيح c = 0; c <= s->gain_ونگ_عدد_control_points_minus_1[a]; c++)
                    put_بٹ(pb, 16, s->gain_ونگ_control_points_y[a][c]);
                إذا (!s->gain_ونگ_use_pchip_ڈھلوان_flag[a]) {
                    لكل (صحيح c = 0; c <= s->gain_ونگ_عدد_control_points_minus_1[a]; c++)
                        put_بٹ(pb, 16, s->gain_ونگ_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_بٹ(pb);

    *انکڑے = buf;
    إذا (ناپ)
        *ناپ = ناپ_بائٹاں;
    أرجع 0;
}

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
ساكن ثابت int32_t knee_ټکی_den = 4095;
ساكن ثابت int32_t bezier_anchor_den = 1023;
ساكن ثابت int32_t saturation_وزن_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *اندازه)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(حجم(AVDynamicHDRPlus));

    إذا (اندازه)
        *اندازه = hdr_plus ? حجم(*hdr_plus) : 0;

    أرجع hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_معلومات(AVFrame *چوکاټ)
{
    AVFrame_Side_معلومات *side_معلومات = av_چوکاټ_new_side_معلومات(چوکاټ,
                                                        AV_چوکاټ_معلومات_DYNAMIC_HDR_PLUS,
                                                        حجم(AVDynamicHDRPlus));
    إذا (!side_معلومات)
        أرجع عدم;

    memset(side_معلومات->معلومات, 0, حجم(AVDynamicHDRPlus));

    أرجع (AVDynamicHDRPlus *)side_معلومات->معلومات;
}

صحيح av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, ثابت uint8_t *معلومات,
                                 size_t اندازه)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_اندازه + AV_ننوت_بفر_PADDING_اندازه];
    Get_بټ_Context gbc, *gb = &gbc;
    صحيح ret;

    إذا (!s)
        أرجع AVERROR(EINVAL);

    إذا (اندازه > AV_HDR_PLUS_MAX_PAYLOAD_اندازه)
        أرجع AVERROR(EINVAL);

    حافظه_نقل(padded_buf, معلومات, اندازه);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + اندازه, 0, AV_ننوت_بفر_PADDING_اندازه);

    ret = init_get_bits8(gb, padded_buf, اندازه);
    إذا (ret < 0)
        أرجع ret;

    إذا (get_بټونه_کیڼ(gb) < 10)
        أرجع AVERROR_INVALIDDATA;

    s->application_نسخه = get_بټونه(gb, 8);
    s->عدد_windows = get_بټونه(gb, 2);

    إذا (s->عدد_windows < 1 || s->عدد_windows > 3) {
        أرجع AVERROR_INVALIDDATA;
    }

    إذا (get_بټونه_کیڼ(gb) < ((19 * 8 + 1) * (s->عدد_windows - 1)))
        أرجع AVERROR_INVALIDDATA;

    لكل (صحيح w = 1; w < s->عدد_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->کړکۍ_پاسنی_کیڼ_کونج_x =
            (AVRational){get_بټونه(gb, 16), 1};
        params->کړکۍ_پاسنی_کیڼ_کونج_y =
            (AVRational){get_بټونه(gb, 16), 1};
        params->کړکۍ_ښکتنی_ښی_کونج_x =
            (AVRational){get_بټونه(gb, 16), 1};
        params->کړکۍ_ښکتنی_ښی_کونج_y =
            (AVRational){get_بټونه(gb, 16), 1};

        params->center_د_ellipse_x = get_بټونه(gb, 16);
        params->center_د_ellipse_y = get_بټونه(gb, 16);
        params->rotation_angle = get_بټونه(gb, 8);
        params->semimajor_axis_دننی_ellipse = get_بټونه(gb, 16);
        params->semimajor_axis_external_ellipse = get_بټونه(gb, 16);
        params->semiminor_axis_external_ellipse = get_بټونه(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    إذا (get_بټونه_کیڼ(gb) < 28)
        أرجع AVERROR_INVALIDDATA;

    s->targeted_system_display_اعظمي_luminance =
        (AVRational){get_بټونه_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    إذا (s->targeted_system_display_actual_peak_luminance_flag) {
        صحيح لیکې, ستون_شمېر;
        إذا (get_بټونه_کیڼ(gb) < 10)
            أرجع AVERROR_INVALIDDATA;
        لیکې = get_بټونه(gb, 5);
        ستون_شمېر = get_بټونه(gb, 5);
        إذا (((لیکې < 2) || (لیکې > 25)) || ((ستون_شمېر < 2) || (ستون_شمېر > 25))) {
            أرجع AVERROR_INVALIDDATA;
        }
        s->عدد_لیکې_targeted_system_display_actual_peak_luminance = لیکې;
        s->عدد_ستون_شمېر_targeted_system_display_actual_peak_luminance = ستون_شمېر;

        إذا (get_بټونه_کیڼ(gb) < (لیکې * ستون_شمېر * 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < لیکې; i++) {
            لكل (صحيح j = 0; j < ستون_شمېر; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بټونه(gb, 4), peak_luminance_den};
            }
        }
    }
    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        إذا (get_بټونه_کیڼ(gb) < (3 * 17 + 17 + 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_بټونه(gb, 17), rgb_den};
        }
        params->اوسط_maxrgb =
            (AVRational){get_بټونه(gb, 17), rgb_den};
        params->عدد_distribution_maxrgb_percentiles = get_بټونه(gb, 4);

        إذا (get_بټونه_کیڼ(gb) <
            (params->عدد_distribution_maxrgb_percentiles * 24))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < params->عدد_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_بټونه(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_بټونه(gb, 17), rgb_den};
        }

        إذا (get_بټونه_کیڼ(gb) < 10)
            أرجع AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_بټونه(gb, 10), fraction_pixel_den};
    }
    إذا (get_بټونه_کیڼ(gb) < 1)
        أرجع AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    إذا (s->mastering_display_actual_peak_luminance_flag) {
        صحيح لیکې, ستون_شمېر;
        إذا (get_بټونه_کیڼ(gb) < 10)
            أرجع AVERROR_INVALIDDATA;
        لیکې = get_بټونه(gb, 5);
        ستون_شمېر = get_بټونه(gb, 5);
        إذا (((لیکې < 2) || (لیکې > 25)) || ((ستون_شمېر < 2) || (ستون_شمېر > 25))) {
            أرجع AVERROR_INVALIDDATA;
        }
        s->عدد_لیکې_mastering_display_actual_peak_luminance = لیکې;
        s->عدد_ستون_شمېر_mastering_display_actual_peak_luminance = ستون_شمېر;

        إذا (get_بټونه_کیڼ(gb) < (لیکې * ستون_شمېر * 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < لیکې; i++) {
            لكل (صحيح j = 0; j < ستون_شمېر; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بټونه(gb, 4), peak_luminance_den};
            }
        }
    }

    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        إذا (get_بټونه_کیڼ(gb) < 1)
            أرجع AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        إذا (params->tone_mapping_flag) {
            إذا (get_بټونه_کیڼ(gb) < 28)
                أرجع AVERROR_INVALIDDATA;

            params->knee_ټکی_x =
                (AVRational){get_بټونه(gb, 12), knee_ټکی_den};
            params->knee_ټکی_y =
                (AVRational){get_بټونه(gb, 12), knee_ټکی_den};
            params->عدد_bezier_منحني_anchors = get_بټونه(gb, 4);

            إذا (get_بټونه_کیڼ(gb) < (params->عدد_bezier_منحني_anchors * 10))
                أرجع AVERROR_INVALIDDATA;

            لكل (صحيح i = 0; i < params->عدد_bezier_منحني_anchors; i++) {
                params->bezier_منحني_anchors[i] =
                    (AVRational){get_بټونه(gb, 10), bezier_anchor_den};
            }
        }

        إذا (get_بټونه_کیڼ(gb) < 1)
            أرجع AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        إذا (params->color_saturation_mapping_flag) {
            إذا (get_بټونه_کیڼ(gb) < 6)
                أرجع AVERROR_INVALIDDATA;
            params->color_saturation_وزن =
                (AVRational){get_بټونه(gb, 6), saturation_وزن_den};
        }
    }

    أرجع 0;
}

صحيح av_dynamic_hdr_plus_منزل_t35(ثابت AVDynamicHDRPlus *s, uint8_t **معلومات, size_t *اندازه)
{
    uint8_t *buf;
    size_t اندازه_بټونه, اندازه_بایټونه;
    Put_بټ_Context pbc, *pb = &pbc;

    إذا (!s)
        أرجع AVERROR(EINVAL);
    إذا ((!معلومات || *معلومات) && !اندازه)
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
    اندازه_بټونه = 8;

    اندازه_بټونه += 2;

    لكل (صحيح w = 1; w < s->عدد_windows; w++)
        اندازه_بټونه += 153;

    اندازه_بټونه += 27;

    اندازه_بټونه += 1;
    إذا (s->targeted_system_display_actual_peak_luminance_flag)
        اندازه_بټونه += 10 +
                     s->عدد_لیکې_targeted_system_display_actual_peak_luminance *
                     s->عدد_ستون_شمېر_targeted_system_display_actual_peak_luminance * 4;

    لكل (صحيح w = 0; w < s->عدد_windows; w++)
        اندازه_بټونه += 72 + s->params[w].عدد_distribution_maxrgb_percentiles * 24 + 10;

    اندازه_بټونه += 1;
    إذا (s->mastering_display_actual_peak_luminance_flag)
        اندازه_بټونه += 10 +
                     s->عدد_لیکې_mastering_display_actual_peak_luminance *
                     s->عدد_ستون_شمېر_mastering_display_actual_peak_luminance * 4;

    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        اندازه_بټونه += 1;
        إذا (s->params[w].tone_mapping_flag)
            اندازه_بټونه += 28 + s->params[w].عدد_bezier_منحني_anchors * 10;

        اندازه_بټونه += 1;
        إذا (s->params[w].color_saturation_mapping_flag)
            اندازه_بټونه += 6;
    }

    اندازه_بایټونه = (اندازه_بټونه + 7) / 8;

    av_assert0(اندازه_بایټونه <= AV_HDR_PLUS_MAX_PAYLOAD_اندازه);

    إذا (!معلومات) {
        *اندازه = اندازه_بایټونه;
        أرجع 0;
    } وإلا إذا (*معلومات) {
        إذا (*اندازه < اندازه_بایټونه)
            أرجع AVERROR_بفر_TOO_SMALL;
        buf = *معلومات;
    } وإلا {
        buf = av_malloc(اندازه_بایټونه);
        إذا (!buf)
            أرجع AVERROR(ENOMEM);
    }

    init_put_بټونه(pb, buf, اندازه_بایټونه);

    // application_mode is set to Application Version 1
    put_بټونه(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_بټونه(pb, 2, s->عدد_windows);

    لكل (صحيح w = 1; w < s->عدد_windows; w++) {
        put_بټونه(pb, 16, s->params[w].کړکۍ_پاسنی_کیڼ_کونج_x.عدد / s->params[w].کړکۍ_پاسنی_کیڼ_کونج_x.den);
        put_بټونه(pb, 16, s->params[w].کړکۍ_پاسنی_کیڼ_کونج_y.عدد / s->params[w].کړکۍ_پاسنی_کیڼ_کونج_y.den);
        put_بټونه(pb, 16, s->params[w].کړکۍ_ښکتنی_ښی_کونج_x.عدد / s->params[w].کړکۍ_ښکتنی_ښی_کونج_x.den);
        put_بټونه(pb, 16, s->params[w].کړکۍ_ښکتنی_ښی_کونج_y.عدد / s->params[w].کړکۍ_ښکتنی_ښی_کونج_y.den);
        put_بټونه(pb, 16, s->params[w].center_د_ellipse_x);
        put_بټونه(pb, 16, s->params[w].center_د_ellipse_y);
        put_بټونه(pb, 8, s->params[w].rotation_angle);
        put_بټونه(pb, 16, s->params[w].semimajor_axis_دننی_ellipse);
        put_بټونه(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_بټونه(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_بټونه(pb, 1, s->params[w].overlap_process_option);
    }

    put_بټونه(pb, 27, s->targeted_system_display_اعظمي_luminance.عدد * luminance_den /
        s->targeted_system_display_اعظمي_luminance.den);
    put_بټونه(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    إذا (s->targeted_system_display_actual_peak_luminance_flag) {
        put_بټونه(pb, 5, s->عدد_لیکې_targeted_system_display_actual_peak_luminance);
        put_بټونه(pb, 5, s->عدد_ستون_شمېر_targeted_system_display_actual_peak_luminance);
        لكل (صحيح i = 0; i < s->عدد_لیکې_targeted_system_display_actual_peak_luminance; i++) {
            لكل (صحيح j = 0; j < s->عدد_ستون_شمېر_targeted_system_display_actual_peak_luminance; j++)
                put_بټونه(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].عدد * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        لكل (صحيح i = 0; i < 3; i++)
            put_بټونه(pb, 17, s->params[w].maxscl[i].عدد * rgb_den / s->params[w].maxscl[i].den);
        put_بټونه(pb, 17, s->params[w].اوسط_maxrgb.عدد * rgb_den / s->params[w].اوسط_maxrgb.den);
        put_بټونه(pb, 4, s->params[w].عدد_distribution_maxrgb_percentiles);
        لكل (صحيح i = 0; i < s->params[w].عدد_distribution_maxrgb_percentiles; i++) {
            put_بټونه(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_بټونه(pb, 17, s->params[w].distribution_maxrgb[i].percentile.عدد * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_بټونه(pb, 10, s->params[w].fraction_bright_pixels.عدد * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_بټونه(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    إذا (s->mastering_display_actual_peak_luminance_flag) {
        put_بټونه(pb, 5, s->عدد_لیکې_mastering_display_actual_peak_luminance);
        put_بټونه(pb, 5, s->عدد_ستون_شمېر_mastering_display_actual_peak_luminance);
        لكل (صحيح i = 0; i < s->عدد_لیکې_mastering_display_actual_peak_luminance; i++) {
            لكل (صحيح j = 0; j < s->عدد_ستون_شمېر_mastering_display_actual_peak_luminance; j++)
                put_بټونه(pb, 4, s->mastering_display_actual_peak_luminance[i][j].عدد * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    لكل (صحيح w = 0; w < s->عدد_windows; w++) {
        put_بټونه(pb, 1, s->params[w].tone_mapping_flag);
        إذا (s->params[w].tone_mapping_flag) {
            put_بټونه(pb, 12, s->params[w].knee_ټکی_x.عدد * knee_ټکی_den / s->params[w].knee_ټکی_x.den);
            put_بټونه(pb, 12, s->params[w].knee_ټکی_y.عدد * knee_ټکی_den / s->params[w].knee_ټکی_y.den);
            put_بټونه(pb, 4, s->params[w].عدد_bezier_منحني_anchors);
            لكل (صحيح i = 0; i < s->params[w].عدد_bezier_منحني_anchors; i++)
                put_بټونه(pb, 10, s->params[w].bezier_منحني_anchors[i].عدد * bezier_anchor_den /
                    s->params[w].bezier_منحني_anchors[i].den);
        }
        put_بټونه(pb, 1, s->params[w].color_saturation_mapping_flag);
        إذا (s->params[w].color_saturation_mapping_flag)
            put_بټونه(pb, 6, s->params[w].color_saturation_وزن.عدد * saturation_وزن_den /
                s->params[w].color_saturation_وزن.den);
    }

    flush_put_بټونه(pb);

    *معلومات = buf;
    إذا (اندازه)
        *اندازه = اندازه_بایټونه;
    أرجع 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *اندازه)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(حجم(AVDynamicHDRSmpte2094App5));

    إذا (اندازه)
        *اندازه = smpte2094_app5 ? حجم(*smpte2094_app5) : 0;

    أرجع smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_معلومات(AVFrame *چوکاټ)
{
    AVFrame_Side_معلومات *side_معلومات = av_چوکاټ_new_side_معلومات(چوکاټ,
                                                        AV_چوکاټ_معلومات_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        حجم(AVDynamicHDRSmpte2094App5));
    إذا (!side_معلومات)
        أرجع عدم;

    memset(side_معلومات->معلومات, 0, حجم(AVDynamicHDRSmpte2094App5));

    أرجع (AVDynamicHDRSmpte2094App5 *)side_معلومات->معلومات;
}

#تعریف_کړه GET_بټونه_OR_FAIL(var, n)        \
    افعل {                                \
        إذا (get_بټونه_کیڼ(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            اذهب پای_ټکی;                   \
        }                               \
        var = get_بټونه(gb, n);          \
    } طالما (0)

صحيح av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, ثابت uint8_t *معلومات,
                                           size_t اندازه)
{
    Get_بټ_Context gbc, *gb = &gbc;
    صحيح ret, reserved_zero;
    size_t padded_اندازه = اندازه + AV_ننوت_بفر_PADDING_اندازه;

    إذا (!s)
        أرجع AVERROR(EINVAL);

    uint8_t *padded_معلومات = av_mallocz(padded_اندازه);
    إذا (!padded_معلومات)
        أرجع AVERROR(ENOMEM);

    حافظه_نقل(padded_معلومات, معلومات, اندازه);
    ret = init_get_bits8(gb, padded_معلومات, اندازه);
    إذا (ret < 0)
        اذهب پای_ټکی;

    // Table C.1
    GET_بټونه_OR_FAIL(s->application_نسخه, 3);
    GET_بټونه_OR_FAIL(s->minimum_application_نسخه, 3);
    GET_بټونه_OR_FAIL(reserved_zero, 2);
    إذا (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        اذهب پای_ټکی;
    }

    // Table C.2
    GET_بټونه_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_بټونه_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_بټونه_OR_FAIL(reserved_zero, 6);
    إذا (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        اذهب پای_ټکی;
    }
    إذا (s->has_custom_hdr_reference_white_flag)
        GET_بټونه_OR_FAIL(s->hdr_reference_white, 16);
    إذا (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        اذهب پای_ټکی;
    }

    // Table C.3
    GET_بټونه_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_بټونه_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    إذا (s->use_reference_white_tone_mapping_flag) {
        GET_بټونه_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        اذهب پای_ټکی;
    }
    GET_بټونه_OR_FAIL(s->عدد_alternate_images, 3);
    إذا (s->عدد_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        اذهب پای_ټکی;
    }
    GET_بټونه_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_بټونه_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_بټونه_OR_FAIL(s->has_common_منحني_params_flag, 1);
    إذا (s->gain_application_space_chromaticities_flag == 3)
        لكل (صحيح r = 0; r < 8; r++)
            GET_بټونه_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    لكل (صحيح a = 0; a < s->عدد_alternate_images; a++) {
        GET_بټونه_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        إذا (!a || !s->has_common_component_mix_params_flag) {
            GET_بټونه_OR_FAIL(s->component_mixing_type[a], 2);
            إذا (s->component_mixing_type[a] != 3) {
                GET_بټونه_OR_FAIL(reserved_zero, 6);
                إذا (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    اذهب پای_ټکی;
                }
            } وإلا {
                لكل (صحيح k = 0; k < 6; k++)
                    GET_بټونه_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                لكل (صحيح k = 0; k < 6; k++) {
                    إذا (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_بټونه_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
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
        إذا (!a || !s->has_common_منحني_params_flag) {
            GET_بټونه_OR_FAIL(s->gain_منحني_عدد_control_points_minus_1[a], 5);
            إذا (s->gain_منحني_عدد_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                اذهب پای_ټکی;
            }
            GET_بټونه_OR_FAIL(s->gain_منحني_use_pchip_میلان_flag[a], 1);
            GET_بټونه_OR_FAIL(reserved_zero, 2);
            إذا (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                اذهب پای_ټکی;
            }
            لكل (صحيح c = 0; c <= s->gain_منحني_عدد_control_points_minus_1[a]; c++) {
                GET_بټونه_OR_FAIL(s->gain_منحني_control_points_x[a][c], 16);
            }
        } وإلا {
            s->gain_منحني_عدد_control_points_minus_1[a] =
                    s->gain_منحني_عدد_control_points_minus_1[0];
            s->gain_منحني_use_pchip_میلان_flag[a] = s->gain_منحني_use_pchip_میلان_flag[0];
            لكل (صحيح c = 0; c <= s->gain_منحني_عدد_control_points_minus_1[a]; c++) {
                s->gain_منحني_control_points_x[a][c] = s->gain_منحني_control_points_x[0][c];
            }
        }
        لكل (صحيح c = 0; c <= s->gain_منحني_عدد_control_points_minus_1[a]; c++)
            GET_بټونه_OR_FAIL(s->gain_منحني_control_points_y[a][c], 16);
        إذا (!s->gain_منحني_use_pchip_میلان_flag[a]) {
            لكل (صحيح c = 0; c <= s->gain_منحني_عدد_control_points_minus_1[a]; c++)
                GET_بټونه_OR_FAIL(s->gain_منحني_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
پای_ټکی:
    av_free(padded_معلومات);
    أرجع ret;
}

صحيح av_dynamic_hdr_smpte2094_app5_منزل_t35(ثابت AVDynamicHDRSmpte2094App5 *s, uint8_t **معلومات,
                                         size_t *اندازه)
{
    uint8_t *buf;
    size_t اندازه_بایټونه, اندازه_بټونه;
    Put_بټ_Context pbc, *pb = &pbc;

    إذا (!s)
        أرجع AVERROR(EINVAL);
    إذا ((!معلومات || *معلومات) && !اندازه)
       أرجع AVERROR(EINVAL);

    إذا (s->application_نسخه >= 8 || s->minimum_application_نسخه >= 3)
        أرجع AVERROR_INVALIDDATA;
    اندازه_بټونه = 0;
    اندازه_بټونه += 3 + 3 + 2;
    اندازه_بټونه += 1 + 1 + 6;
    إذا (s->has_custom_hdr_reference_white_flag)
        اندازه_بټونه += 16;
    إذا (s->has_adaptive_tone_map_flag) {
        اندازه_بټونه += 16 + 1;
        إذا (s->use_reference_white_tone_mapping_flag) {
            اندازه_بټونه += 7;
        } وإلا {
            اندازه_بټونه += 3 + 2 + 1 + 1;
            إذا (s->gain_application_space_chromaticities_flag == 3)
                اندازه_بټونه += 16 * 8;
            إذا (s->عدد_alternate_images > 4)
                أرجع AVERROR_INVALIDDATA;
            لكل (صحيح a = 0; a < s->عدد_alternate_images; a++) {
                اندازه_بټونه += 16;
                إذا (!a || !s->has_common_component_mix_params_flag) {
                    اندازه_بټونه += 2;
                    إذا (s->component_mixing_type[a] != 3) {
                        اندازه_بټونه += 6;
                    } وإلا {
                        اندازه_بټونه += 6;
                        لكل (صحيح k = 0; k < 6; k++)
                          إذا (s->has_component_mixing_coefficient_flag[a][k])
                            اندازه_بټونه += 16;
                    }
                }
                إذا (!a || !s->has_common_منحني_params_flag) {
                    اندازه_بټونه += 5 + 1 + 2;
                    إذا (s->gain_منحني_عدد_control_points_minus_1[a] > 31)
                        أرجع AVERROR_INVALIDDATA;
                    اندازه_بټونه += 16 * (s->gain_منحني_عدد_control_points_minus_1[a] + 1);
                }
                اندازه_بټونه += 16 * (s->gain_منحني_عدد_control_points_minus_1[a] + 1);
                إذا (!s->gain_منحني_use_pchip_میلان_flag[a])
                    اندازه_بټونه += 16 * (s->gain_منحني_عدد_control_points_minus_1[a] + 1);
            }
        }
    }
    إذا (اندازه_بټونه % 8)
      أرجع AVERROR_INVALIDDATA;
    اندازه_بایټونه = اندازه_بټونه >> 3;

    إذا (!معلومات) {
        *اندازه = اندازه_بایټونه;
        أرجع 0;
    } وإلا إذا (*معلومات) {
        إذا (*اندازه < اندازه_بایټونه)
            أرجع AVERROR_بفر_TOO_SMALL;
        buf = *معلومات;
    } وإلا {
        buf = av_malloc(اندازه_بایټونه);
        إذا (!buf)
            أرجع AVERROR(ENOMEM);
    }

    init_put_بټونه(pb, buf, اندازه_بایټونه);

    // Table C.1
    put_بټونه(pb, 3, s->application_نسخه);
    put_بټونه(pb, 3, s->minimum_application_نسخه);
    put_بټونه(pb, 2, 0); // reserved_zero

    // Table C.2
    put_بټونه(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_بټونه(pb, 1, s->has_adaptive_tone_map_flag);
    put_بټونه(pb, 6, 0); // reserved_zero

    إذا (s->has_custom_hdr_reference_white_flag)
        put_بټونه(pb, 16, s->hdr_reference_white);

    إذا (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_بټونه(pb, 16, s->baseline_hdr_headroom);
        put_بټونه(pb, 1, s->use_reference_white_tone_mapping_flag);
        إذا (s->use_reference_white_tone_mapping_flag) {
            put_بټونه(pb, 7, 0); // reserved_zero
        } وإلا {
            put_بټونه(pb, 3, s->عدد_alternate_images);
            put_بټونه(pb, 2, s->gain_application_space_chromaticities_flag);
            put_بټونه(pb, 1, s->has_common_component_mix_params_flag);
            put_بټونه(pb, 1, s->has_common_منحني_params_flag);

            إذا (s->gain_application_space_chromaticities_flag == 3)
                لكل (صحيح r = 0; r < 8; r++)
                    put_بټونه(pb, 16, s->gain_application_space_chromaticities[r]);

            لكل (صحيح a = 0; a < s->عدد_alternate_images; a++) {
                put_بټونه(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                إذا (!a || !s->has_common_component_mix_params_flag) {
                    put_بټونه(pb, 2, s->component_mixing_type[a]);
                    إذا (s->component_mixing_type[a] != 3) {
                        put_بټونه(pb, 6, 0); // reserved_zero
                    } وإلا {
                        لكل (صحيح k = 0; k < 6; k++)
                            put_بټونه(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        لكل (صحيح k = 0; k < 6; k++)
                            إذا (s->has_component_mixing_coefficient_flag[a][k])
                                put_بټونه(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                إذا (!a || !s->has_common_منحني_params_flag) {
                    put_بټونه(pb, 5, s->gain_منحني_عدد_control_points_minus_1[a]);
                    put_بټونه(pb, 1, s->gain_منحني_use_pchip_میلان_flag[a]);
                    put_بټونه(pb, 2, 0); // reserved_zero
                    لكل (صحيح c = 0; c <= s->gain_منحني_عدد_control_points_minus_1[a]; c++)
                        put_بټونه(pb, 16, s->gain_منحني_control_points_x[a][c]);
                }
                لكل (صحيح c = 0; c <= s->gain_منحني_عدد_control_points_minus_1[a]; c++)
                    put_بټونه(pb, 16, s->gain_منحني_control_points_y[a][c]);
                إذا (!s->gain_منحني_use_pchip_میلان_flag[a]) {
                    لكل (صحيح c = 0; c <= s->gain_منحني_عدد_control_points_minus_1[a]; c++)
                        put_بټونه(pb, 16, s->gain_منحني_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_بټونه(pb);

    *معلومات = buf;
    إذا (اندازه)
        *اندازه = اندازه_بایټونه;
    أرجع 0;
}

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
ساكن ثابت int32_t knee_نقطه_den = 4095;
ساكن ثابت int32_t bezier_anchor_den = 1023;
ساكن ثابت int32_t saturation_وزن_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *اندازه)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(حجم(AVDynamicHDRPlus));

    إذا (اندازه)
        *اندازه = hdr_plus ? حجم(*hdr_plus) : 0;

    أرجع hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_داده(AVFrame *قاب)
{
    AVFrame_Side_داده *side_داده = av_قاب_new_side_داده(قاب,
                                                        AV_قاب_داده_DYNAMIC_HDR_PLUS,
                                                        حجم(AVDynamicHDRPlus));
    إذا (!side_داده)
        أرجع عدم;

    memset(side_داده->داده, 0, حجم(AVDynamicHDRPlus));

    أرجع (AVDynamicHDRPlus *)side_داده->داده;
}

صحيح av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, ثابت uint8_t *داده,
                                 size_t اندازه)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_اندازه + AV_درون_داد_میانگیر_PADDING_اندازه];
    Get_بیت_Context gbc, *gb = &gbc;
    صحيح ret;

    إذا (!s)
        أرجع AVERROR(EINVAL);

    إذا (اندازه > AV_HDR_PLUS_MAX_PAYLOAD_اندازه)
        أرجع AVERROR(EINVAL);

    کپی_حافظه(padded_buf, داده, اندازه);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + اندازه, 0, AV_درون_داد_میانگیر_PADDING_اندازه);

    ret = init_get_bits8(gb, padded_buf, اندازه);
    إذا (ret < 0)
        أرجع ret;

    إذا (get_بیتها_چپ(gb) < 10)
        أرجع AVERROR_INVALIDDATA;

    s->application_نسخه = get_بیتها(gb, 8);
    s->رقم_windows = get_بیتها(gb, 2);

    إذا (s->رقم_windows < 1 || s->رقم_windows > 3) {
        أرجع AVERROR_INVALIDDATA;
    }

    إذا (get_بیتها_چپ(gb) < ((19 * 8 + 1) * (s->رقم_windows - 1)))
        أرجع AVERROR_INVALIDDATA;

    لكل (صحيح w = 1; w < s->رقم_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->پنجره_فوقانی_چپ_گوشه_x =
            (AVRational){get_بیتها(gb, 16), 1};
        params->پنجره_فوقانی_چپ_گوشه_y =
            (AVRational){get_بیتها(gb, 16), 1};
        params->پنجره_پایینی_راست_گوشه_x =
            (AVRational){get_بیتها(gb, 16), 1};
        params->پنجره_پایینی_راست_گوشه_y =
            (AVRational){get_بیتها(gb, 16), 1};

        params->center_از_ellipse_x = get_بیتها(gb, 16);
        params->center_از_ellipse_y = get_بیتها(gb, 16);
        params->rotation_angle = get_بیتها(gb, 8);
        params->semimajor_axis_داخلی_ellipse = get_بیتها(gb, 16);
        params->semimajor_axis_external_ellipse = get_بیتها(gb, 16);
        params->semiminor_axis_external_ellipse = get_بیتها(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    إذا (get_بیتها_چپ(gb) < 28)
        أرجع AVERROR_INVALIDDATA;

    s->targeted_system_display_بیشینه_luminance =
        (AVRational){get_بیتها_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    إذا (s->targeted_system_display_actual_peak_luminance_flag) {
        صحيح ردیفها, تعداد_ستون;
        إذا (get_بیتها_چپ(gb) < 10)
            أرجع AVERROR_INVALIDDATA;
        ردیفها = get_بیتها(gb, 5);
        تعداد_ستون = get_بیتها(gb, 5);
        إذا (((ردیفها < 2) || (ردیفها > 25)) || ((تعداد_ستون < 2) || (تعداد_ستون > 25))) {
            أرجع AVERROR_INVALIDDATA;
        }
        s->رقم_ردیفها_targeted_system_display_actual_peak_luminance = ردیفها;
        s->رقم_تعداد_ستون_targeted_system_display_actual_peak_luminance = تعداد_ستون;

        إذا (get_بیتها_چپ(gb) < (ردیفها * تعداد_ستون * 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < ردیفها; i++) {
            لكل (صحيح j = 0; j < تعداد_ستون; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بیتها(gb, 4), peak_luminance_den};
            }
        }
    }
    لكل (صحيح w = 0; w < s->رقم_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        إذا (get_بیتها_چپ(gb) < (3 * 17 + 17 + 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_بیتها(gb, 17), rgb_den};
        }
        params->معدل_maxrgb =
            (AVRational){get_بیتها(gb, 17), rgb_den};
        params->رقم_distribution_maxrgb_percentiles = get_بیتها(gb, 4);

        إذا (get_بیتها_چپ(gb) <
            (params->رقم_distribution_maxrgb_percentiles * 24))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < params->رقم_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_بیتها(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_بیتها(gb, 17), rgb_den};
        }

        إذا (get_بیتها_چپ(gb) < 10)
            أرجع AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_بیتها(gb, 10), fraction_pixel_den};
    }
    إذا (get_بیتها_چپ(gb) < 1)
        أرجع AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    إذا (s->mastering_display_actual_peak_luminance_flag) {
        صحيح ردیفها, تعداد_ستون;
        إذا (get_بیتها_چپ(gb) < 10)
            أرجع AVERROR_INVALIDDATA;
        ردیفها = get_بیتها(gb, 5);
        تعداد_ستون = get_بیتها(gb, 5);
        إذا (((ردیفها < 2) || (ردیفها > 25)) || ((تعداد_ستون < 2) || (تعداد_ستون > 25))) {
            أرجع AVERROR_INVALIDDATA;
        }
        s->رقم_ردیفها_mastering_display_actual_peak_luminance = ردیفها;
        s->رقم_تعداد_ستون_mastering_display_actual_peak_luminance = تعداد_ستون;

        إذا (get_بیتها_چپ(gb) < (ردیفها * تعداد_ستون * 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < ردیفها; i++) {
            لكل (صحيح j = 0; j < تعداد_ستون; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بیتها(gb, 4), peak_luminance_den};
            }
        }
    }

    لكل (صحيح w = 0; w < s->رقم_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        إذا (get_بیتها_چپ(gb) < 1)
            أرجع AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        إذا (params->tone_mapping_flag) {
            إذا (get_بیتها_چپ(gb) < 28)
                أرجع AVERROR_INVALIDDATA;

            params->knee_نقطه_x =
                (AVRational){get_بیتها(gb, 12), knee_نقطه_den};
            params->knee_نقطه_y =
                (AVRational){get_بیتها(gb, 12), knee_نقطه_den};
            params->رقم_bezier_منحنی_anchors = get_بیتها(gb, 4);

            إذا (get_بیتها_چپ(gb) < (params->رقم_bezier_منحنی_anchors * 10))
                أرجع AVERROR_INVALIDDATA;

            لكل (صحيح i = 0; i < params->رقم_bezier_منحنی_anchors; i++) {
                params->bezier_منحنی_anchors[i] =
                    (AVRational){get_بیتها(gb, 10), bezier_anchor_den};
            }
        }

        إذا (get_بیتها_چپ(gb) < 1)
            أرجع AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        إذا (params->color_saturation_mapping_flag) {
            إذا (get_بیتها_چپ(gb) < 6)
                أرجع AVERROR_INVALIDDATA;
            params->color_saturation_وزن =
                (AVRational){get_بیتها(gb, 6), saturation_وزن_den};
        }
    }

    أرجع 0;
}

صحيح av_dynamic_hdr_plus_مقصد_t35(ثابت AVDynamicHDRPlus *s, uint8_t **داده, size_t *اندازه)
{
    uint8_t *buf;
    size_t اندازه_بیتها, اندازه_بایتها;
    Put_بیت_Context pbc, *pb = &pbc;

    إذا (!s)
        أرجع AVERROR(EINVAL);
    إذا ((!داده || *داده) && !اندازه)
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
    اندازه_بیتها = 8;

    اندازه_بیتها += 2;

    لكل (صحيح w = 1; w < s->رقم_windows; w++)
        اندازه_بیتها += 153;

    اندازه_بیتها += 27;

    اندازه_بیتها += 1;
    إذا (s->targeted_system_display_actual_peak_luminance_flag)
        اندازه_بیتها += 10 +
                     s->رقم_ردیفها_targeted_system_display_actual_peak_luminance *
                     s->رقم_تعداد_ستون_targeted_system_display_actual_peak_luminance * 4;

    لكل (صحيح w = 0; w < s->رقم_windows; w++)
        اندازه_بیتها += 72 + s->params[w].رقم_distribution_maxrgb_percentiles * 24 + 10;

    اندازه_بیتها += 1;
    إذا (s->mastering_display_actual_peak_luminance_flag)
        اندازه_بیتها += 10 +
                     s->رقم_ردیفها_mastering_display_actual_peak_luminance *
                     s->رقم_تعداد_ستون_mastering_display_actual_peak_luminance * 4;

    لكل (صحيح w = 0; w < s->رقم_windows; w++) {
        اندازه_بیتها += 1;
        إذا (s->params[w].tone_mapping_flag)
            اندازه_بیتها += 28 + s->params[w].رقم_bezier_منحنی_anchors * 10;

        اندازه_بیتها += 1;
        إذا (s->params[w].color_saturation_mapping_flag)
            اندازه_بیتها += 6;
    }

    اندازه_بایتها = (اندازه_بیتها + 7) / 8;

    av_assert0(اندازه_بایتها <= AV_HDR_PLUS_MAX_PAYLOAD_اندازه);

    إذا (!داده) {
        *اندازه = اندازه_بایتها;
        أرجع 0;
    } وإلا إذا (*داده) {
        إذا (*اندازه < اندازه_بایتها)
            أرجع AVERROR_میانگیر_TOO_SMALL;
        buf = *داده;
    } وإلا {
        buf = av_malloc(اندازه_بایتها);
        إذا (!buf)
            أرجع AVERROR(ENOMEM);
    }

    init_put_بیتها(pb, buf, اندازه_بایتها);

    // application_mode is set to Application Version 1
    put_بیتها(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_بیتها(pb, 2, s->رقم_windows);

    لكل (صحيح w = 1; w < s->رقم_windows; w++) {
        put_بیتها(pb, 16, s->params[w].پنجره_فوقانی_چپ_گوشه_x.رقم / s->params[w].پنجره_فوقانی_چپ_گوشه_x.den);
        put_بیتها(pb, 16, s->params[w].پنجره_فوقانی_چپ_گوشه_y.رقم / s->params[w].پنجره_فوقانی_چپ_گوشه_y.den);
        put_بیتها(pb, 16, s->params[w].پنجره_پایینی_راست_گوشه_x.رقم / s->params[w].پنجره_پایینی_راست_گوشه_x.den);
        put_بیتها(pb, 16, s->params[w].پنجره_پایینی_راست_گوشه_y.رقم / s->params[w].پنجره_پایینی_راست_گوشه_y.den);
        put_بیتها(pb, 16, s->params[w].center_از_ellipse_x);
        put_بیتها(pb, 16, s->params[w].center_از_ellipse_y);
        put_بیتها(pb, 8, s->params[w].rotation_angle);
        put_بیتها(pb, 16, s->params[w].semimajor_axis_داخلی_ellipse);
        put_بیتها(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_بیتها(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_بیتها(pb, 1, s->params[w].overlap_process_option);
    }

    put_بیتها(pb, 27, s->targeted_system_display_بیشینه_luminance.رقم * luminance_den /
        s->targeted_system_display_بیشینه_luminance.den);
    put_بیتها(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    إذا (s->targeted_system_display_actual_peak_luminance_flag) {
        put_بیتها(pb, 5, s->رقم_ردیفها_targeted_system_display_actual_peak_luminance);
        put_بیتها(pb, 5, s->رقم_تعداد_ستون_targeted_system_display_actual_peak_luminance);
        لكل (صحيح i = 0; i < s->رقم_ردیفها_targeted_system_display_actual_peak_luminance; i++) {
            لكل (صحيح j = 0; j < s->رقم_تعداد_ستون_targeted_system_display_actual_peak_luminance; j++)
                put_بیتها(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].رقم * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    لكل (صحيح w = 0; w < s->رقم_windows; w++) {
        لكل (صحيح i = 0; i < 3; i++)
            put_بیتها(pb, 17, s->params[w].maxscl[i].رقم * rgb_den / s->params[w].maxscl[i].den);
        put_بیتها(pb, 17, s->params[w].معدل_maxrgb.رقم * rgb_den / s->params[w].معدل_maxrgb.den);
        put_بیتها(pb, 4, s->params[w].رقم_distribution_maxrgb_percentiles);
        لكل (صحيح i = 0; i < s->params[w].رقم_distribution_maxrgb_percentiles; i++) {
            put_بیتها(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_بیتها(pb, 17, s->params[w].distribution_maxrgb[i].percentile.رقم * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_بیتها(pb, 10, s->params[w].fraction_bright_pixels.رقم * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_بیتها(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    إذا (s->mastering_display_actual_peak_luminance_flag) {
        put_بیتها(pb, 5, s->رقم_ردیفها_mastering_display_actual_peak_luminance);
        put_بیتها(pb, 5, s->رقم_تعداد_ستون_mastering_display_actual_peak_luminance);
        لكل (صحيح i = 0; i < s->رقم_ردیفها_mastering_display_actual_peak_luminance; i++) {
            لكل (صحيح j = 0; j < s->رقم_تعداد_ستون_mastering_display_actual_peak_luminance; j++)
                put_بیتها(pb, 4, s->mastering_display_actual_peak_luminance[i][j].رقم * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    لكل (صحيح w = 0; w < s->رقم_windows; w++) {
        put_بیتها(pb, 1, s->params[w].tone_mapping_flag);
        إذا (s->params[w].tone_mapping_flag) {
            put_بیتها(pb, 12, s->params[w].knee_نقطه_x.رقم * knee_نقطه_den / s->params[w].knee_نقطه_x.den);
            put_بیتها(pb, 12, s->params[w].knee_نقطه_y.رقم * knee_نقطه_den / s->params[w].knee_نقطه_y.den);
            put_بیتها(pb, 4, s->params[w].رقم_bezier_منحنی_anchors);
            لكل (صحيح i = 0; i < s->params[w].رقم_bezier_منحنی_anchors; i++)
                put_بیتها(pb, 10, s->params[w].bezier_منحنی_anchors[i].رقم * bezier_anchor_den /
                    s->params[w].bezier_منحنی_anchors[i].den);
        }
        put_بیتها(pb, 1, s->params[w].color_saturation_mapping_flag);
        إذا (s->params[w].color_saturation_mapping_flag)
            put_بیتها(pb, 6, s->params[w].color_saturation_وزن.رقم * saturation_وزن_den /
                s->params[w].color_saturation_وزن.den);
    }

    flush_put_بیتها(pb);

    *داده = buf;
    إذا (اندازه)
        *اندازه = اندازه_بایتها;
    أرجع 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *اندازه)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(حجم(AVDynamicHDRSmpte2094App5));

    إذا (اندازه)
        *اندازه = smpte2094_app5 ? حجم(*smpte2094_app5) : 0;

    أرجع smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_داده(AVFrame *قاب)
{
    AVFrame_Side_داده *side_داده = av_قاب_new_side_داده(قاب,
                                                        AV_قاب_داده_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        حجم(AVDynamicHDRSmpte2094App5));
    إذا (!side_داده)
        أرجع عدم;

    memset(side_داده->داده, 0, حجم(AVDynamicHDRSmpte2094App5));

    أرجع (AVDynamicHDRSmpte2094App5 *)side_داده->داده;
}

#تعریف_کن GET_بیتها_OR_FAIL(var, n)        \
    افعل {                                \
        إذا (get_بیتها_چپ(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            اذهب انتها;                   \
        }                               \
        var = get_بیتها(gb, n);          \
    } طالما (0)

صحيح av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, ثابت uint8_t *داده,
                                           size_t اندازه)
{
    Get_بیت_Context gbc, *gb = &gbc;
    صحيح ret, reserved_zero;
    size_t padded_اندازه = اندازه + AV_درون_داد_میانگیر_PADDING_اندازه;

    إذا (!s)
        أرجع AVERROR(EINVAL);

    uint8_t *padded_داده = av_mallocz(padded_اندازه);
    إذا (!padded_داده)
        أرجع AVERROR(ENOMEM);

    کپی_حافظه(padded_داده, داده, اندازه);
    ret = init_get_bits8(gb, padded_داده, اندازه);
    إذا (ret < 0)
        اذهب انتها;

    // Table C.1
    GET_بیتها_OR_FAIL(s->application_نسخه, 3);
    GET_بیتها_OR_FAIL(s->minimum_application_نسخه, 3);
    GET_بیتها_OR_FAIL(reserved_zero, 2);
    إذا (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        اذهب انتها;
    }

    // Table C.2
    GET_بیتها_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_بیتها_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_بیتها_OR_FAIL(reserved_zero, 6);
    إذا (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        اذهب انتها;
    }
    إذا (s->has_custom_hdr_reference_white_flag)
        GET_بیتها_OR_FAIL(s->hdr_reference_white, 16);
    إذا (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        اذهب انتها;
    }

    // Table C.3
    GET_بیتها_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_بیتها_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    إذا (s->use_reference_white_tone_mapping_flag) {
        GET_بیتها_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        اذهب انتها;
    }
    GET_بیتها_OR_FAIL(s->رقم_alternate_images, 3);
    إذا (s->رقم_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        اذهب انتها;
    }
    GET_بیتها_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_بیتها_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_بیتها_OR_FAIL(s->has_common_منحنی_params_flag, 1);
    إذا (s->gain_application_space_chromaticities_flag == 3)
        لكل (صحيح r = 0; r < 8; r++)
            GET_بیتها_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    لكل (صحيح a = 0; a < s->رقم_alternate_images; a++) {
        GET_بیتها_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        إذا (!a || !s->has_common_component_mix_params_flag) {
            GET_بیتها_OR_FAIL(s->component_mixing_type[a], 2);
            إذا (s->component_mixing_type[a] != 3) {
                GET_بیتها_OR_FAIL(reserved_zero, 6);
                إذا (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    اذهب انتها;
                }
            } وإلا {
                لكل (صحيح k = 0; k < 6; k++)
                    GET_بیتها_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                لكل (صحيح k = 0; k < 6; k++) {
                    إذا (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_بیتها_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
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
        إذا (!a || !s->has_common_منحنی_params_flag) {
            GET_بیتها_OR_FAIL(s->gain_منحنی_رقم_control_points_minus_1[a], 5);
            إذا (s->gain_منحنی_رقم_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                اذهب انتها;
            }
            GET_بیتها_OR_FAIL(s->gain_منحنی_use_pchip_شیب_flag[a], 1);
            GET_بیتها_OR_FAIL(reserved_zero, 2);
            إذا (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                اذهب انتها;
            }
            لكل (صحيح c = 0; c <= s->gain_منحنی_رقم_control_points_minus_1[a]; c++) {
                GET_بیتها_OR_FAIL(s->gain_منحنی_control_points_x[a][c], 16);
            }
        } وإلا {
            s->gain_منحنی_رقم_control_points_minus_1[a] =
                    s->gain_منحنی_رقم_control_points_minus_1[0];
            s->gain_منحنی_use_pchip_شیب_flag[a] = s->gain_منحنی_use_pchip_شیب_flag[0];
            لكل (صحيح c = 0; c <= s->gain_منحنی_رقم_control_points_minus_1[a]; c++) {
                s->gain_منحنی_control_points_x[a][c] = s->gain_منحنی_control_points_x[0][c];
            }
        }
        لكل (صحيح c = 0; c <= s->gain_منحنی_رقم_control_points_minus_1[a]; c++)
            GET_بیتها_OR_FAIL(s->gain_منحنی_control_points_y[a][c], 16);
        إذا (!s->gain_منحنی_use_pchip_شیب_flag[a]) {
            لكل (صحيح c = 0; c <= s->gain_منحنی_رقم_control_points_minus_1[a]; c++)
                GET_بیتها_OR_FAIL(s->gain_منحنی_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
انتها:
    av_free(padded_داده);
    أرجع ret;
}

صحيح av_dynamic_hdr_smpte2094_app5_مقصد_t35(ثابت AVDynamicHDRSmpte2094App5 *s, uint8_t **داده,
                                         size_t *اندازه)
{
    uint8_t *buf;
    size_t اندازه_بایتها, اندازه_بیتها;
    Put_بیت_Context pbc, *pb = &pbc;

    إذا (!s)
        أرجع AVERROR(EINVAL);
    إذا ((!داده || *داده) && !اندازه)
       أرجع AVERROR(EINVAL);

    إذا (s->application_نسخه >= 8 || s->minimum_application_نسخه >= 3)
        أرجع AVERROR_INVALIDDATA;
    اندازه_بیتها = 0;
    اندازه_بیتها += 3 + 3 + 2;
    اندازه_بیتها += 1 + 1 + 6;
    إذا (s->has_custom_hdr_reference_white_flag)
        اندازه_بیتها += 16;
    إذا (s->has_adaptive_tone_map_flag) {
        اندازه_بیتها += 16 + 1;
        إذا (s->use_reference_white_tone_mapping_flag) {
            اندازه_بیتها += 7;
        } وإلا {
            اندازه_بیتها += 3 + 2 + 1 + 1;
            إذا (s->gain_application_space_chromaticities_flag == 3)
                اندازه_بیتها += 16 * 8;
            إذا (s->رقم_alternate_images > 4)
                أرجع AVERROR_INVALIDDATA;
            لكل (صحيح a = 0; a < s->رقم_alternate_images; a++) {
                اندازه_بیتها += 16;
                إذا (!a || !s->has_common_component_mix_params_flag) {
                    اندازه_بیتها += 2;
                    إذا (s->component_mixing_type[a] != 3) {
                        اندازه_بیتها += 6;
                    } وإلا {
                        اندازه_بیتها += 6;
                        لكل (صحيح k = 0; k < 6; k++)
                          إذا (s->has_component_mixing_coefficient_flag[a][k])
                            اندازه_بیتها += 16;
                    }
                }
                إذا (!a || !s->has_common_منحنی_params_flag) {
                    اندازه_بیتها += 5 + 1 + 2;
                    إذا (s->gain_منحنی_رقم_control_points_minus_1[a] > 31)
                        أرجع AVERROR_INVALIDDATA;
                    اندازه_بیتها += 16 * (s->gain_منحنی_رقم_control_points_minus_1[a] + 1);
                }
                اندازه_بیتها += 16 * (s->gain_منحنی_رقم_control_points_minus_1[a] + 1);
                إذا (!s->gain_منحنی_use_pchip_شیب_flag[a])
                    اندازه_بیتها += 16 * (s->gain_منحنی_رقم_control_points_minus_1[a] + 1);
            }
        }
    }
    إذا (اندازه_بیتها % 8)
      أرجع AVERROR_INVALIDDATA;
    اندازه_بایتها = اندازه_بیتها >> 3;

    إذا (!داده) {
        *اندازه = اندازه_بایتها;
        أرجع 0;
    } وإلا إذا (*داده) {
        إذا (*اندازه < اندازه_بایتها)
            أرجع AVERROR_میانگیر_TOO_SMALL;
        buf = *داده;
    } وإلا {
        buf = av_malloc(اندازه_بایتها);
        إذا (!buf)
            أرجع AVERROR(ENOMEM);
    }

    init_put_بیتها(pb, buf, اندازه_بایتها);

    // Table C.1
    put_بیتها(pb, 3, s->application_نسخه);
    put_بیتها(pb, 3, s->minimum_application_نسخه);
    put_بیتها(pb, 2, 0); // reserved_zero

    // Table C.2
    put_بیتها(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_بیتها(pb, 1, s->has_adaptive_tone_map_flag);
    put_بیتها(pb, 6, 0); // reserved_zero

    إذا (s->has_custom_hdr_reference_white_flag)
        put_بیتها(pb, 16, s->hdr_reference_white);

    إذا (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_بیتها(pb, 16, s->baseline_hdr_headroom);
        put_بیتها(pb, 1, s->use_reference_white_tone_mapping_flag);
        إذا (s->use_reference_white_tone_mapping_flag) {
            put_بیتها(pb, 7, 0); // reserved_zero
        } وإلا {
            put_بیتها(pb, 3, s->رقم_alternate_images);
            put_بیتها(pb, 2, s->gain_application_space_chromaticities_flag);
            put_بیتها(pb, 1, s->has_common_component_mix_params_flag);
            put_بیتها(pb, 1, s->has_common_منحنی_params_flag);

            إذا (s->gain_application_space_chromaticities_flag == 3)
                لكل (صحيح r = 0; r < 8; r++)
                    put_بیتها(pb, 16, s->gain_application_space_chromaticities[r]);

            لكل (صحيح a = 0; a < s->رقم_alternate_images; a++) {
                put_بیتها(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                إذا (!a || !s->has_common_component_mix_params_flag) {
                    put_بیتها(pb, 2, s->component_mixing_type[a]);
                    إذا (s->component_mixing_type[a] != 3) {
                        put_بیتها(pb, 6, 0); // reserved_zero
                    } وإلا {
                        لكل (صحيح k = 0; k < 6; k++)
                            put_بیتها(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        لكل (صحيح k = 0; k < 6; k++)
                            إذا (s->has_component_mixing_coefficient_flag[a][k])
                                put_بیتها(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                إذا (!a || !s->has_common_منحنی_params_flag) {
                    put_بیتها(pb, 5, s->gain_منحنی_رقم_control_points_minus_1[a]);
                    put_بیتها(pb, 1, s->gain_منحنی_use_pchip_شیب_flag[a]);
                    put_بیتها(pb, 2, 0); // reserved_zero
                    لكل (صحيح c = 0; c <= s->gain_منحنی_رقم_control_points_minus_1[a]; c++)
                        put_بیتها(pb, 16, s->gain_منحنی_control_points_x[a][c]);
                }
                لكل (صحيح c = 0; c <= s->gain_منحنی_رقم_control_points_minus_1[a]; c++)
                    put_بیتها(pb, 16, s->gain_منحنی_control_points_y[a][c]);
                إذا (!s->gain_منحنی_use_pchip_شیب_flag[a]) {
                    لكل (صحيح c = 0; c <= s->gain_منحنی_رقم_control_points_minus_1[a]; c++)
                        put_بیتها(pb, 16, s->gain_منحنی_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_بیتها(pb);

    *داده = buf;
    إذا (اندازه)
        *اندازه = اندازه_بایتها;
    أرجع 0;
}

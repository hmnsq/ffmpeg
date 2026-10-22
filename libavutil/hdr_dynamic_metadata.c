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
ساكن ثابت int32_t knee_نقطو_den = 4095;
ساكن ثابت int32_t bezier_anchor_den = 1023;
ساكن ثابت int32_t saturation_وزن_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *سائيز)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(حجم(AVDynamicHDRPlus));

    إذا (سائيز)
        *سائيز = hdr_plus ? حجم(*hdr_plus) : 0;

    أرجع hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_معلومات(AVFrame *چوکٺو)
{
    AVFrame_Side_معلومات *side_معلومات = av_چوکٺو_new_side_معلومات(چوکٺو,
                                                        AV_چوکٺو_معلومات_DYNAMIC_HDR_PLUS,
                                                        حجم(AVDynamicHDRPlus));
    إذا (!side_معلومات)
        أرجع عدم;

    memset(side_معلومات->معلومات, 0, حجم(AVDynamicHDRPlus));

    أرجع (AVDynamicHDRPlus *)side_معلومات->معلومات;
}

صحيح av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, ثابت uint8_t *معلومات,
                                 size_t سائيز)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_سائيز + AV_داخلا_بفر_PADDING_سائيز];
    Get_ٻٽو_انگ_Context gbc, *gb = &gbc;
    صحيح ret;

    إذا (!s)
        أرجع AVERROR(EINVAL);

    إذا (سائيز > AV_HDR_PLUS_MAX_PAYLOAD_سائيز)
        أرجع AVERROR(EINVAL);

    يادگيري_نقل(padded_buf, معلومات, سائيز);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + سائيز, 0, AV_داخلا_بفر_PADDING_سائيز);

    ret = init_get_bits8(gb, padded_buf, سائيز);
    إذا (ret < 0)
        أرجع ret;

    إذا (get_بٽ_کاٻو(gb) < 10)
        أرجع AVERROR_INVALIDDATA;

    s->application_نسخو = get_بٽ(gb, 8);
    s->انگ_windows = get_بٽ(gb, 2);

    إذا (s->انگ_windows < 1 || s->انگ_windows > 3) {
        أرجع AVERROR_INVALIDDATA;
    }

    إذا (get_بٽ_کاٻو(gb) < ((19 * 8 + 1) * (s->انگ_windows - 1)))
        أرجع AVERROR_INVALIDDATA;

    لكل (صحيح w = 1; w < s->انگ_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->دري_مٿانهون_کاٻو_ڪنڊ_x =
            (AVRational){get_بٽ(gb, 16), 1};
        params->دري_مٿانهون_کاٻو_ڪنڊ_y =
            (AVRational){get_بٽ(gb, 16), 1};
        params->دري_هيٺاهون_ساڄو_ڪنڊ_x =
            (AVRational){get_بٽ(gb, 16), 1};
        params->دري_هيٺاهون_ساڄو_ڪنڊ_y =
            (AVRational){get_بٽ(gb, 16), 1};

        params->center_جو_ellipse_x = get_بٽ(gb, 16);
        params->center_جو_ellipse_y = get_بٽ(gb, 16);
        params->rotation_angle = get_بٽ(gb, 8);
        params->semimajor_axis_اندروني_ellipse = get_بٽ(gb, 16);
        params->semimajor_axis_external_ellipse = get_بٽ(gb, 16);
        params->semiminor_axis_external_ellipse = get_بٽ(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    إذا (get_بٽ_کاٻو(gb) < 28)
        أرجع AVERROR_INVALIDDATA;

    s->targeted_system_display_وڌ_کان_وڌ_luminance =
        (AVRational){get_بٽ_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    إذا (s->targeted_system_display_actual_peak_luminance_flag) {
        صحيح صفون, کانن_ڳڻپ;
        إذا (get_بٽ_کاٻو(gb) < 10)
            أرجع AVERROR_INVALIDDATA;
        صفون = get_بٽ(gb, 5);
        کانن_ڳڻپ = get_بٽ(gb, 5);
        إذا (((صفون < 2) || (صفون > 25)) || ((کانن_ڳڻپ < 2) || (کانن_ڳڻپ > 25))) {
            أرجع AVERROR_INVALIDDATA;
        }
        s->انگ_صفون_targeted_system_display_actual_peak_luminance = صفون;
        s->انگ_کانن_ڳڻپ_targeted_system_display_actual_peak_luminance = کانن_ڳڻپ;

        إذا (get_بٽ_کاٻو(gb) < (صفون * کانن_ڳڻپ * 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < صفون; i++) {
            لكل (صحيح j = 0; j < کانن_ڳڻپ; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بٽ(gb, 4), peak_luminance_den};
            }
        }
    }
    لكل (صحيح w = 0; w < s->انگ_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        إذا (get_بٽ_کاٻو(gb) < (3 * 17 + 17 + 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_بٽ(gb, 17), rgb_den};
        }
        params->اوسط_maxrgb =
            (AVRational){get_بٽ(gb, 17), rgb_den};
        params->انگ_distribution_maxrgb_percentiles = get_بٽ(gb, 4);

        إذا (get_بٽ_کاٻو(gb) <
            (params->انگ_distribution_maxrgb_percentiles * 24))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < params->انگ_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_بٽ(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_بٽ(gb, 17), rgb_den};
        }

        إذا (get_بٽ_کاٻو(gb) < 10)
            أرجع AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_بٽ(gb, 10), fraction_pixel_den};
    }
    إذا (get_بٽ_کاٻو(gb) < 1)
        أرجع AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    إذا (s->mastering_display_actual_peak_luminance_flag) {
        صحيح صفون, کانن_ڳڻپ;
        إذا (get_بٽ_کاٻو(gb) < 10)
            أرجع AVERROR_INVALIDDATA;
        صفون = get_بٽ(gb, 5);
        کانن_ڳڻپ = get_بٽ(gb, 5);
        إذا (((صفون < 2) || (صفون > 25)) || ((کانن_ڳڻپ < 2) || (کانن_ڳڻپ > 25))) {
            أرجع AVERROR_INVALIDDATA;
        }
        s->انگ_صفون_mastering_display_actual_peak_luminance = صفون;
        s->انگ_کانن_ڳڻپ_mastering_display_actual_peak_luminance = کانن_ڳڻپ;

        إذا (get_بٽ_کاٻو(gb) < (صفون * کانن_ڳڻپ * 4))
            أرجع AVERROR_INVALIDDATA;

        لكل (صحيح i = 0; i < صفون; i++) {
            لكل (صحيح j = 0; j < کانن_ڳڻپ; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_بٽ(gb, 4), peak_luminance_den};
            }
        }
    }

    لكل (صحيح w = 0; w < s->انگ_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        إذا (get_بٽ_کاٻو(gb) < 1)
            أرجع AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        إذا (params->tone_mapping_flag) {
            إذا (get_بٽ_کاٻو(gb) < 28)
                أرجع AVERROR_INVALIDDATA;

            params->knee_نقطو_x =
                (AVRational){get_بٽ(gb, 12), knee_نقطو_den};
            params->knee_نقطو_y =
                (AVRational){get_بٽ(gb, 12), knee_نقطو_den};
            params->انگ_bezier_وڪر_anchors = get_بٽ(gb, 4);

            إذا (get_بٽ_کاٻو(gb) < (params->انگ_bezier_وڪر_anchors * 10))
                أرجع AVERROR_INVALIDDATA;

            لكل (صحيح i = 0; i < params->انگ_bezier_وڪر_anchors; i++) {
                params->bezier_وڪر_anchors[i] =
                    (AVRational){get_بٽ(gb, 10), bezier_anchor_den};
            }
        }

        إذا (get_بٽ_کاٻو(gb) < 1)
            أرجع AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        إذا (params->color_saturation_mapping_flag) {
            إذا (get_بٽ_کاٻو(gb) < 6)
                أرجع AVERROR_INVALIDDATA;
            params->color_saturation_وزن =
                (AVRational){get_بٽ(gb, 6), saturation_وزن_den};
        }
    }

    أرجع 0;
}

صحيح av_dynamic_hdr_plus_منزل_t35(ثابت AVDynamicHDRPlus *s, uint8_t **معلومات, size_t *سائيز)
{
    uint8_t *buf;
    size_t سائيز_بٽ, سائيز_بائيٽون;
    Put_ٻٽو_انگ_Context pbc, *pb = &pbc;

    إذا (!s)
        أرجع AVERROR(EINVAL);
    إذا ((!معلومات || *معلومات) && !سائيز)
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
    سائيز_بٽ = 8;

    سائيز_بٽ += 2;

    لكل (صحيح w = 1; w < s->انگ_windows; w++)
        سائيز_بٽ += 153;

    سائيز_بٽ += 27;

    سائيز_بٽ += 1;
    إذا (s->targeted_system_display_actual_peak_luminance_flag)
        سائيز_بٽ += 10 +
                     s->انگ_صفون_targeted_system_display_actual_peak_luminance *
                     s->انگ_کانن_ڳڻپ_targeted_system_display_actual_peak_luminance * 4;

    لكل (صحيح w = 0; w < s->انگ_windows; w++)
        سائيز_بٽ += 72 + s->params[w].انگ_distribution_maxrgb_percentiles * 24 + 10;

    سائيز_بٽ += 1;
    إذا (s->mastering_display_actual_peak_luminance_flag)
        سائيز_بٽ += 10 +
                     s->انگ_صفون_mastering_display_actual_peak_luminance *
                     s->انگ_کانن_ڳڻپ_mastering_display_actual_peak_luminance * 4;

    لكل (صحيح w = 0; w < s->انگ_windows; w++) {
        سائيز_بٽ += 1;
        إذا (s->params[w].tone_mapping_flag)
            سائيز_بٽ += 28 + s->params[w].انگ_bezier_وڪر_anchors * 10;

        سائيز_بٽ += 1;
        إذا (s->params[w].color_saturation_mapping_flag)
            سائيز_بٽ += 6;
    }

    سائيز_بائيٽون = (سائيز_بٽ + 7) / 8;

    av_assert0(سائيز_بائيٽون <= AV_HDR_PLUS_MAX_PAYLOAD_سائيز);

    إذا (!معلومات) {
        *سائيز = سائيز_بائيٽون;
        أرجع 0;
    } وإلا إذا (*معلومات) {
        إذا (*سائيز < سائيز_بائيٽون)
            أرجع AVERROR_بفر_TOO_SMALL;
        buf = *معلومات;
    } وإلا {
        buf = av_malloc(سائيز_بائيٽون);
        إذا (!buf)
            أرجع AVERROR(ENOMEM);
    }

    init_put_بٽ(pb, buf, سائيز_بائيٽون);

    // application_mode is set to Application Version 1
    put_بٽ(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_بٽ(pb, 2, s->انگ_windows);

    لكل (صحيح w = 1; w < s->انگ_windows; w++) {
        put_بٽ(pb, 16, s->params[w].دري_مٿانهون_کاٻو_ڪنڊ_x.انگ / s->params[w].دري_مٿانهون_کاٻو_ڪنڊ_x.den);
        put_بٽ(pb, 16, s->params[w].دري_مٿانهون_کاٻو_ڪنڊ_y.انگ / s->params[w].دري_مٿانهون_کاٻو_ڪنڊ_y.den);
        put_بٽ(pb, 16, s->params[w].دري_هيٺاهون_ساڄو_ڪنڊ_x.انگ / s->params[w].دري_هيٺاهون_ساڄو_ڪنڊ_x.den);
        put_بٽ(pb, 16, s->params[w].دري_هيٺاهون_ساڄو_ڪنڊ_y.انگ / s->params[w].دري_هيٺاهون_ساڄو_ڪنڊ_y.den);
        put_بٽ(pb, 16, s->params[w].center_جو_ellipse_x);
        put_بٽ(pb, 16, s->params[w].center_جو_ellipse_y);
        put_بٽ(pb, 8, s->params[w].rotation_angle);
        put_بٽ(pb, 16, s->params[w].semimajor_axis_اندروني_ellipse);
        put_بٽ(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_بٽ(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_بٽ(pb, 1, s->params[w].overlap_process_option);
    }

    put_بٽ(pb, 27, s->targeted_system_display_وڌ_کان_وڌ_luminance.انگ * luminance_den /
        s->targeted_system_display_وڌ_کان_وڌ_luminance.den);
    put_بٽ(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    إذا (s->targeted_system_display_actual_peak_luminance_flag) {
        put_بٽ(pb, 5, s->انگ_صفون_targeted_system_display_actual_peak_luminance);
        put_بٽ(pb, 5, s->انگ_کانن_ڳڻپ_targeted_system_display_actual_peak_luminance);
        لكل (صحيح i = 0; i < s->انگ_صفون_targeted_system_display_actual_peak_luminance; i++) {
            لكل (صحيح j = 0; j < s->انگ_کانن_ڳڻپ_targeted_system_display_actual_peak_luminance; j++)
                put_بٽ(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].انگ * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    لكل (صحيح w = 0; w < s->انگ_windows; w++) {
        لكل (صحيح i = 0; i < 3; i++)
            put_بٽ(pb, 17, s->params[w].maxscl[i].انگ * rgb_den / s->params[w].maxscl[i].den);
        put_بٽ(pb, 17, s->params[w].اوسط_maxrgb.انگ * rgb_den / s->params[w].اوسط_maxrgb.den);
        put_بٽ(pb, 4, s->params[w].انگ_distribution_maxrgb_percentiles);
        لكل (صحيح i = 0; i < s->params[w].انگ_distribution_maxrgb_percentiles; i++) {
            put_بٽ(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_بٽ(pb, 17, s->params[w].distribution_maxrgb[i].percentile.انگ * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_بٽ(pb, 10, s->params[w].fraction_bright_pixels.انگ * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_بٽ(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    إذا (s->mastering_display_actual_peak_luminance_flag) {
        put_بٽ(pb, 5, s->انگ_صفون_mastering_display_actual_peak_luminance);
        put_بٽ(pb, 5, s->انگ_کانن_ڳڻپ_mastering_display_actual_peak_luminance);
        لكل (صحيح i = 0; i < s->انگ_صفون_mastering_display_actual_peak_luminance; i++) {
            لكل (صحيح j = 0; j < s->انگ_کانن_ڳڻپ_mastering_display_actual_peak_luminance; j++)
                put_بٽ(pb, 4, s->mastering_display_actual_peak_luminance[i][j].انگ * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    لكل (صحيح w = 0; w < s->انگ_windows; w++) {
        put_بٽ(pb, 1, s->params[w].tone_mapping_flag);
        إذا (s->params[w].tone_mapping_flag) {
            put_بٽ(pb, 12, s->params[w].knee_نقطو_x.انگ * knee_نقطو_den / s->params[w].knee_نقطو_x.den);
            put_بٽ(pb, 12, s->params[w].knee_نقطو_y.انگ * knee_نقطو_den / s->params[w].knee_نقطو_y.den);
            put_بٽ(pb, 4, s->params[w].انگ_bezier_وڪر_anchors);
            لكل (صحيح i = 0; i < s->params[w].انگ_bezier_وڪر_anchors; i++)
                put_بٽ(pb, 10, s->params[w].bezier_وڪر_anchors[i].انگ * bezier_anchor_den /
                    s->params[w].bezier_وڪر_anchors[i].den);
        }
        put_بٽ(pb, 1, s->params[w].color_saturation_mapping_flag);
        إذا (s->params[w].color_saturation_mapping_flag)
            put_بٽ(pb, 6, s->params[w].color_saturation_وزن.انگ * saturation_وزن_den /
                s->params[w].color_saturation_وزن.den);
    }

    flush_put_بٽ(pb);

    *معلومات = buf;
    إذا (سائيز)
        *سائيز = سائيز_بائيٽون;
    أرجع 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *سائيز)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(حجم(AVDynamicHDRSmpte2094App5));

    إذا (سائيز)
        *سائيز = smpte2094_app5 ? حجم(*smpte2094_app5) : 0;

    أرجع smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_معلومات(AVFrame *چوکٺو)
{
    AVFrame_Side_معلومات *side_معلومات = av_چوکٺو_new_side_معلومات(چوکٺو,
                                                        AV_چوکٺو_معلومات_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        حجم(AVDynamicHDRSmpte2094App5));
    إذا (!side_معلومات)
        أرجع عدم;

    memset(side_معلومات->معلومات, 0, حجم(AVDynamicHDRSmpte2094App5));

    أرجع (AVDynamicHDRSmpte2094App5 *)side_معلومات->معلومات;
}

#وصف_ڪريو GET_بٽ_OR_FAIL(var, n)        \
    افعل {                                \
        إذا (get_بٽ_کاٻو(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            اذهب پڇاڙي;                   \
        }                               \
        var = get_بٽ(gb, n);          \
    } طالما (0)

صحيح av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, ثابت uint8_t *معلومات,
                                           size_t سائيز)
{
    Get_ٻٽو_انگ_Context gbc, *gb = &gbc;
    صحيح ret, reserved_zero;
    size_t padded_سائيز = سائيز + AV_داخلا_بفر_PADDING_سائيز;

    إذا (!s)
        أرجع AVERROR(EINVAL);

    uint8_t *padded_معلومات = av_mallocz(padded_سائيز);
    إذا (!padded_معلومات)
        أرجع AVERROR(ENOMEM);

    يادگيري_نقل(padded_معلومات, معلومات, سائيز);
    ret = init_get_bits8(gb, padded_معلومات, سائيز);
    إذا (ret < 0)
        اذهب پڇاڙي;

    // Table C.1
    GET_بٽ_OR_FAIL(s->application_نسخو, 3);
    GET_بٽ_OR_FAIL(s->minimum_application_نسخو, 3);
    GET_بٽ_OR_FAIL(reserved_zero, 2);
    إذا (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        اذهب پڇاڙي;
    }

    // Table C.2
    GET_بٽ_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_بٽ_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_بٽ_OR_FAIL(reserved_zero, 6);
    إذا (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        اذهب پڇاڙي;
    }
    إذا (s->has_custom_hdr_reference_white_flag)
        GET_بٽ_OR_FAIL(s->hdr_reference_white, 16);
    إذا (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        اذهب پڇاڙي;
    }

    // Table C.3
    GET_بٽ_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_بٽ_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    إذا (s->use_reference_white_tone_mapping_flag) {
        GET_بٽ_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        اذهب پڇاڙي;
    }
    GET_بٽ_OR_FAIL(s->انگ_alternate_images, 3);
    إذا (s->انگ_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        اذهب پڇاڙي;
    }
    GET_بٽ_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_بٽ_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_بٽ_OR_FAIL(s->has_common_وڪر_params_flag, 1);
    إذا (s->gain_application_space_chromaticities_flag == 3)
        لكل (صحيح r = 0; r < 8; r++)
            GET_بٽ_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    لكل (صحيح a = 0; a < s->انگ_alternate_images; a++) {
        GET_بٽ_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        إذا (!a || !s->has_common_component_mix_params_flag) {
            GET_بٽ_OR_FAIL(s->component_mixing_type[a], 2);
            إذا (s->component_mixing_type[a] != 3) {
                GET_بٽ_OR_FAIL(reserved_zero, 6);
                إذا (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    اذهب پڇاڙي;
                }
            } وإلا {
                لكل (صحيح k = 0; k < 6; k++)
                    GET_بٽ_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                لكل (صحيح k = 0; k < 6; k++) {
                    إذا (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_بٽ_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
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
        إذا (!a || !s->has_common_وڪر_params_flag) {
            GET_بٽ_OR_FAIL(s->gain_وڪر_انگ_control_points_minus_1[a], 5);
            إذا (s->gain_وڪر_انگ_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                اذهب پڇاڙي;
            }
            GET_بٽ_OR_FAIL(s->gain_وڪر_use_pchip_لاهي_flag[a], 1);
            GET_بٽ_OR_FAIL(reserved_zero, 2);
            إذا (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                اذهب پڇاڙي;
            }
            لكل (صحيح c = 0; c <= s->gain_وڪر_انگ_control_points_minus_1[a]; c++) {
                GET_بٽ_OR_FAIL(s->gain_وڪر_control_points_x[a][c], 16);
            }
        } وإلا {
            s->gain_وڪر_انگ_control_points_minus_1[a] =
                    s->gain_وڪر_انگ_control_points_minus_1[0];
            s->gain_وڪر_use_pchip_لاهي_flag[a] = s->gain_وڪر_use_pchip_لاهي_flag[0];
            لكل (صحيح c = 0; c <= s->gain_وڪر_انگ_control_points_minus_1[a]; c++) {
                s->gain_وڪر_control_points_x[a][c] = s->gain_وڪر_control_points_x[0][c];
            }
        }
        لكل (صحيح c = 0; c <= s->gain_وڪر_انگ_control_points_minus_1[a]; c++)
            GET_بٽ_OR_FAIL(s->gain_وڪر_control_points_y[a][c], 16);
        إذا (!s->gain_وڪر_use_pchip_لاهي_flag[a]) {
            لكل (صحيح c = 0; c <= s->gain_وڪر_انگ_control_points_minus_1[a]; c++)
                GET_بٽ_OR_FAIL(s->gain_وڪر_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
پڇاڙي:
    av_free(padded_معلومات);
    أرجع ret;
}

صحيح av_dynamic_hdr_smpte2094_app5_منزل_t35(ثابت AVDynamicHDRSmpte2094App5 *s, uint8_t **معلومات,
                                         size_t *سائيز)
{
    uint8_t *buf;
    size_t سائيز_بائيٽون, سائيز_بٽ;
    Put_ٻٽو_انگ_Context pbc, *pb = &pbc;

    إذا (!s)
        أرجع AVERROR(EINVAL);
    إذا ((!معلومات || *معلومات) && !سائيز)
       أرجع AVERROR(EINVAL);

    إذا (s->application_نسخو >= 8 || s->minimum_application_نسخو >= 3)
        أرجع AVERROR_INVALIDDATA;
    سائيز_بٽ = 0;
    سائيز_بٽ += 3 + 3 + 2;
    سائيز_بٽ += 1 + 1 + 6;
    إذا (s->has_custom_hdr_reference_white_flag)
        سائيز_بٽ += 16;
    إذا (s->has_adaptive_tone_map_flag) {
        سائيز_بٽ += 16 + 1;
        إذا (s->use_reference_white_tone_mapping_flag) {
            سائيز_بٽ += 7;
        } وإلا {
            سائيز_بٽ += 3 + 2 + 1 + 1;
            إذا (s->gain_application_space_chromaticities_flag == 3)
                سائيز_بٽ += 16 * 8;
            إذا (s->انگ_alternate_images > 4)
                أرجع AVERROR_INVALIDDATA;
            لكل (صحيح a = 0; a < s->انگ_alternate_images; a++) {
                سائيز_بٽ += 16;
                إذا (!a || !s->has_common_component_mix_params_flag) {
                    سائيز_بٽ += 2;
                    إذا (s->component_mixing_type[a] != 3) {
                        سائيز_بٽ += 6;
                    } وإلا {
                        سائيز_بٽ += 6;
                        لكل (صحيح k = 0; k < 6; k++)
                          إذا (s->has_component_mixing_coefficient_flag[a][k])
                            سائيز_بٽ += 16;
                    }
                }
                إذا (!a || !s->has_common_وڪر_params_flag) {
                    سائيز_بٽ += 5 + 1 + 2;
                    إذا (s->gain_وڪر_انگ_control_points_minus_1[a] > 31)
                        أرجع AVERROR_INVALIDDATA;
                    سائيز_بٽ += 16 * (s->gain_وڪر_انگ_control_points_minus_1[a] + 1);
                }
                سائيز_بٽ += 16 * (s->gain_وڪر_انگ_control_points_minus_1[a] + 1);
                إذا (!s->gain_وڪر_use_pchip_لاهي_flag[a])
                    سائيز_بٽ += 16 * (s->gain_وڪر_انگ_control_points_minus_1[a] + 1);
            }
        }
    }
    إذا (سائيز_بٽ % 8)
      أرجع AVERROR_INVALIDDATA;
    سائيز_بائيٽون = سائيز_بٽ >> 3;

    إذا (!معلومات) {
        *سائيز = سائيز_بائيٽون;
        أرجع 0;
    } وإلا إذا (*معلومات) {
        إذا (*سائيز < سائيز_بائيٽون)
            أرجع AVERROR_بفر_TOO_SMALL;
        buf = *معلومات;
    } وإلا {
        buf = av_malloc(سائيز_بائيٽون);
        إذا (!buf)
            أرجع AVERROR(ENOMEM);
    }

    init_put_بٽ(pb, buf, سائيز_بائيٽون);

    // Table C.1
    put_بٽ(pb, 3, s->application_نسخو);
    put_بٽ(pb, 3, s->minimum_application_نسخو);
    put_بٽ(pb, 2, 0); // reserved_zero

    // Table C.2
    put_بٽ(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_بٽ(pb, 1, s->has_adaptive_tone_map_flag);
    put_بٽ(pb, 6, 0); // reserved_zero

    إذا (s->has_custom_hdr_reference_white_flag)
        put_بٽ(pb, 16, s->hdr_reference_white);

    إذا (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_بٽ(pb, 16, s->baseline_hdr_headroom);
        put_بٽ(pb, 1, s->use_reference_white_tone_mapping_flag);
        إذا (s->use_reference_white_tone_mapping_flag) {
            put_بٽ(pb, 7, 0); // reserved_zero
        } وإلا {
            put_بٽ(pb, 3, s->انگ_alternate_images);
            put_بٽ(pb, 2, s->gain_application_space_chromaticities_flag);
            put_بٽ(pb, 1, s->has_common_component_mix_params_flag);
            put_بٽ(pb, 1, s->has_common_وڪر_params_flag);

            إذا (s->gain_application_space_chromaticities_flag == 3)
                لكل (صحيح r = 0; r < 8; r++)
                    put_بٽ(pb, 16, s->gain_application_space_chromaticities[r]);

            لكل (صحيح a = 0; a < s->انگ_alternate_images; a++) {
                put_بٽ(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                إذا (!a || !s->has_common_component_mix_params_flag) {
                    put_بٽ(pb, 2, s->component_mixing_type[a]);
                    إذا (s->component_mixing_type[a] != 3) {
                        put_بٽ(pb, 6, 0); // reserved_zero
                    } وإلا {
                        لكل (صحيح k = 0; k < 6; k++)
                            put_بٽ(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        لكل (صحيح k = 0; k < 6; k++)
                            إذا (s->has_component_mixing_coefficient_flag[a][k])
                                put_بٽ(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                إذا (!a || !s->has_common_وڪر_params_flag) {
                    put_بٽ(pb, 5, s->gain_وڪر_انگ_control_points_minus_1[a]);
                    put_بٽ(pb, 1, s->gain_وڪر_use_pchip_لاهي_flag[a]);
                    put_بٽ(pb, 2, 0); // reserved_zero
                    لكل (صحيح c = 0; c <= s->gain_وڪر_انگ_control_points_minus_1[a]; c++)
                        put_بٽ(pb, 16, s->gain_وڪر_control_points_x[a][c]);
                }
                لكل (صحيح c = 0; c <= s->gain_وڪر_انگ_control_points_minus_1[a]; c++)
                    put_بٽ(pb, 16, s->gain_وڪر_control_points_y[a][c]);
                إذا (!s->gain_وڪر_use_pchip_لاهي_flag[a]) {
                    لكل (صحيح c = 0; c <= s->gain_وڪر_انگ_control_points_minus_1[a]; c++)
                        put_بٽ(pb, 16, s->gain_وڪر_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_بٽ(pb);

    *معلومات = buf;
    إذا (سائيز)
        *سائيز = سائيز_بائيٽون;
    أرجع 0;
}

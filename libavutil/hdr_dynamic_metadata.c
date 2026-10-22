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

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "hdr_dynamic_metadata.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavcodec/defs.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavcodec/get_bits.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavcodec/put_bits.h"

ਸਥਿਰ ਅਚਲ int64_t luminance_den = 1;
ਸਥਿਰ ਅਚਲ int32_t peak_luminance_den = 15;
ਸਥਿਰ ਅਚਲ int64_t rgb_den = 100000;
ਸਥਿਰ ਅਚਲ int32_t fraction_pixel_den = 1000;
ਸਥਿਰ ਅਚਲ int32_t knee_ਬਿੰਦੂ_den = 4095;
ਸਥਿਰ ਅਚਲ int32_t bezier_anchor_den = 1023;
ਸਥਿਰ ਅਚਲ int32_t saturation_ਭਾਰ_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *ਮਾਪ)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(ਆਕਾਰ(AVDynamicHDRPlus));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = hdr_plus ? ਆਕਾਰ(*hdr_plus) : 0;

    ਵਾਪਸ hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ,
                                                        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DYNAMIC_HDR_PLUS,
                                                        ਆਕਾਰ(AVDynamicHDRPlus));
    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    memset(side_ਅੰਕੜੇ->ਅੰਕੜੇ, 0, ਆਕਾਰ(AVDynamicHDRPlus));

    ਵਾਪਸ (AVDynamicHDRPlus *)side_ਅੰਕੜੇ->ਅੰਕੜੇ;
}

ਪੂਰਨ av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, ਅਚਲ uint8_t *ਅੰਕੜੇ,
                                 size_t ਮਾਪ)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_ਮਾਪ + AV_ਨਿਵੇਸ਼_ਬਫਰ_PADDING_ਮਾਪ];
    Get_ਦੋਆਧਾਰੀ_ਅੰਕ_Context gbc, *gb = &gbc;
    ਪੂਰਨ ret;

    ਜੇ (!s)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (ਮਾਪ > AV_HDR_PLUS_MAX_PAYLOAD_ਮਾਪ)
        ਵਾਪਸ AVERROR(EINVAL);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(padded_buf, ਅੰਕੜੇ, ਮਾਪ);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + ਮਾਪ, 0, AV_ਨਿਵੇਸ਼_ਬਫਰ_PADDING_ਮਾਪ);

    ret = init_get_bits8(gb, padded_buf, ਮਾਪ);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 10)
        ਵਾਪਸ AVERROR_INVALIDDATA;

    s->application_ਸੰਸਕਰਣ = get_ਬਿੱਟ(gb, 8);
    s->ਅੰਕ_windows = get_ਬਿੱਟ(gb, 2);

    ਜੇ (s->ਅੰਕ_windows < 1 || s->ਅੰਕ_windows > 3) {
        ਵਾਪਸ AVERROR_INVALIDDATA;
    }

    ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < ((19 * 8 + 1) * (s->ਅੰਕ_windows - 1)))
        ਵਾਪਸ AVERROR_INVALIDDATA;

    ਲਈ (ਪੂਰਨ w = 1; w < s->ਅੰਕ_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_x =
            (AVRational){get_ਬਿੱਟ(gb, 16), 1};
        params->ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_y =
            (AVRational){get_ਬਿੱਟ(gb, 16), 1};
        params->ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_x =
            (AVRational){get_ਬਿੱਟ(gb, 16), 1};
        params->ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_y =
            (AVRational){get_ਬਿੱਟ(gb, 16), 1};

        params->center_ਦਾ_ellipse_x = get_ਬਿੱਟ(gb, 16);
        params->center_ਦਾ_ellipse_y = get_ਬਿੱਟ(gb, 16);
        params->rotation_angle = get_ਬਿੱਟ(gb, 8);
        params->semimajor_axis_ਅੰਦਰੂਨੀ_ellipse = get_ਬਿੱਟ(gb, 16);
        params->semimajor_axis_external_ellipse = get_ਬਿੱਟ(gb, 16);
        params->semiminor_axis_external_ellipse = get_ਬਿੱਟ(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 28)
        ਵਾਪਸ AVERROR_INVALIDDATA;

    s->targeted_system_display_ਵੱਧ_ਤੋਂ_ਵੱਧ_luminance =
        (AVRational){get_ਬਿੱਟ_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    ਜੇ (s->targeted_system_display_actual_peak_luminance_flag) {
        ਪੂਰਨ ਪੰਕਤੀਆਂ, ਖਾਨੇ_ਗਿਣਤੀ;
        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 10)
            ਵਾਪਸ AVERROR_INVALIDDATA;
        ਪੰਕਤੀਆਂ = get_ਬਿੱਟ(gb, 5);
        ਖਾਨੇ_ਗਿਣਤੀ = get_ਬਿੱਟ(gb, 5);
        ਜੇ (((ਪੰਕਤੀਆਂ < 2) || (ਪੰਕਤੀਆਂ > 25)) || ((ਖਾਨੇ_ਗਿਣਤੀ < 2) || (ਖਾਨੇ_ਗਿਣਤੀ > 25))) {
            ਵਾਪਸ AVERROR_INVALIDDATA;
        }
        s->ਅੰਕ_ਪੰਕਤੀਆਂ_targeted_system_display_actual_peak_luminance = ਪੰਕਤੀਆਂ;
        s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_targeted_system_display_actual_peak_luminance = ਖਾਨੇ_ਗਿਣਤੀ;

        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < (ਪੰਕਤੀਆਂ * ਖਾਨੇ_ਗਿਣਤੀ * 4))
            ਵਾਪਸ AVERROR_INVALIDDATA;

        ਲਈ (ਪੂਰਨ i = 0; i < ਪੰਕਤੀਆਂ; i++) {
            ਲਈ (ਪੂਰਨ j = 0; j < ਖਾਨੇ_ਗਿਣਤੀ; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_ਬਿੱਟ(gb, 4), peak_luminance_den};
            }
        }
    }
    ਲਈ (ਪੂਰਨ w = 0; w < s->ਅੰਕ_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < (3 * 17 + 17 + 4))
            ਵਾਪਸ AVERROR_INVALIDDATA;

        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_ਬਿੱਟ(gb, 17), rgb_den};
        }
        params->ਔਸਤਨ_maxrgb =
            (AVRational){get_ਬਿੱਟ(gb, 17), rgb_den};
        params->ਅੰਕ_distribution_maxrgb_percentiles = get_ਬਿੱਟ(gb, 4);

        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) <
            (params->ਅੰਕ_distribution_maxrgb_percentiles * 24))
            ਵਾਪਸ AVERROR_INVALIDDATA;

        ਲਈ (ਪੂਰਨ i = 0; i < params->ਅੰਕ_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_ਬਿੱਟ(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_ਬਿੱਟ(gb, 17), rgb_den};
        }

        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 10)
            ਵਾਪਸ AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_ਬਿੱਟ(gb, 10), fraction_pixel_den};
    }
    ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 1)
        ਵਾਪਸ AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    ਜੇ (s->mastering_display_actual_peak_luminance_flag) {
        ਪੂਰਨ ਪੰਕਤੀਆਂ, ਖਾਨੇ_ਗਿਣਤੀ;
        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 10)
            ਵਾਪਸ AVERROR_INVALIDDATA;
        ਪੰਕਤੀਆਂ = get_ਬਿੱਟ(gb, 5);
        ਖਾਨੇ_ਗਿਣਤੀ = get_ਬਿੱਟ(gb, 5);
        ਜੇ (((ਪੰਕਤੀਆਂ < 2) || (ਪੰਕਤੀਆਂ > 25)) || ((ਖਾਨੇ_ਗਿਣਤੀ < 2) || (ਖਾਨੇ_ਗਿਣਤੀ > 25))) {
            ਵਾਪਸ AVERROR_INVALIDDATA;
        }
        s->ਅੰਕ_ਪੰਕਤੀਆਂ_mastering_display_actual_peak_luminance = ਪੰਕਤੀਆਂ;
        s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_mastering_display_actual_peak_luminance = ਖਾਨੇ_ਗਿਣਤੀ;

        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < (ਪੰਕਤੀਆਂ * ਖਾਨੇ_ਗਿਣਤੀ * 4))
            ਵਾਪਸ AVERROR_INVALIDDATA;

        ਲਈ (ਪੂਰਨ i = 0; i < ਪੰਕਤੀਆਂ; i++) {
            ਲਈ (ਪੂਰਨ j = 0; j < ਖਾਨੇ_ਗਿਣਤੀ; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_ਬਿੱਟ(gb, 4), peak_luminance_den};
            }
        }
    }

    ਲਈ (ਪੂਰਨ w = 0; w < s->ਅੰਕ_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 1)
            ਵਾਪਸ AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        ਜੇ (params->tone_mapping_flag) {
            ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 28)
                ਵਾਪਸ AVERROR_INVALIDDATA;

            params->knee_ਬਿੰਦੂ_x =
                (AVRational){get_ਬਿੱਟ(gb, 12), knee_ਬਿੰਦੂ_den};
            params->knee_ਬਿੰਦੂ_y =
                (AVRational){get_ਬਿੱਟ(gb, 12), knee_ਬਿੰਦੂ_den};
            params->ਅੰਕ_bezier_ਵਕਰ_anchors = get_ਬਿੱਟ(gb, 4);

            ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < (params->ਅੰਕ_bezier_ਵਕਰ_anchors * 10))
                ਵਾਪਸ AVERROR_INVALIDDATA;

            ਲਈ (ਪੂਰਨ i = 0; i < params->ਅੰਕ_bezier_ਵਕਰ_anchors; i++) {
                params->bezier_ਵਕਰ_anchors[i] =
                    (AVRational){get_ਬਿੱਟ(gb, 10), bezier_anchor_den};
            }
        }

        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 1)
            ਵਾਪਸ AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        ਜੇ (params->color_saturation_mapping_flag) {
            ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < 6)
                ਵਾਪਸ AVERROR_INVALIDDATA;
            params->color_saturation_ਭਾਰ =
                (AVRational){get_ਬਿੱਟ(gb, 6), saturation_ਭਾਰ_den};
        }
    }

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_dynamic_hdr_plus_ਮੰਜ਼ਿਲ_t35(ਅਚਲ AVDynamicHDRPlus *s, uint8_t **ਅੰਕੜੇ, size_t *ਮਾਪ)
{
    uint8_t *buf;
    size_t ਮਾਪ_ਬਿੱਟ, ਮਾਪ_ਬਾਈਟਾਂ;
    Put_ਦੋਆਧਾਰੀ_ਅੰਕ_Context pbc, *pb = &pbc;

    ਜੇ (!s)
        ਵਾਪਸ AVERROR(EINVAL);
    ਜੇ ((!ਅੰਕੜੇ || *ਅੰਕੜੇ) && !ਮਾਪ)
       ਵਾਪਸ AVERROR(EINVAL);

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
    ਮਾਪ_ਬਿੱਟ = 8;

    ਮਾਪ_ਬਿੱਟ += 2;

    ਲਈ (ਪੂਰਨ w = 1; w < s->ਅੰਕ_windows; w++)
        ਮਾਪ_ਬਿੱਟ += 153;

    ਮਾਪ_ਬਿੱਟ += 27;

    ਮਾਪ_ਬਿੱਟ += 1;
    ਜੇ (s->targeted_system_display_actual_peak_luminance_flag)
        ਮਾਪ_ਬਿੱਟ += 10 +
                     s->ਅੰਕ_ਪੰਕਤੀਆਂ_targeted_system_display_actual_peak_luminance *
                     s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_targeted_system_display_actual_peak_luminance * 4;

    ਲਈ (ਪੂਰਨ w = 0; w < s->ਅੰਕ_windows; w++)
        ਮਾਪ_ਬਿੱਟ += 72 + s->params[w].ਅੰਕ_distribution_maxrgb_percentiles * 24 + 10;

    ਮਾਪ_ਬਿੱਟ += 1;
    ਜੇ (s->mastering_display_actual_peak_luminance_flag)
        ਮਾਪ_ਬਿੱਟ += 10 +
                     s->ਅੰਕ_ਪੰਕਤੀਆਂ_mastering_display_actual_peak_luminance *
                     s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_mastering_display_actual_peak_luminance * 4;

    ਲਈ (ਪੂਰਨ w = 0; w < s->ਅੰਕ_windows; w++) {
        ਮਾਪ_ਬਿੱਟ += 1;
        ਜੇ (s->params[w].tone_mapping_flag)
            ਮਾਪ_ਬਿੱਟ += 28 + s->params[w].ਅੰਕ_bezier_ਵਕਰ_anchors * 10;

        ਮਾਪ_ਬਿੱਟ += 1;
        ਜੇ (s->params[w].color_saturation_mapping_flag)
            ਮਾਪ_ਬਿੱਟ += 6;
    }

    ਮਾਪ_ਬਾਈਟਾਂ = (ਮਾਪ_ਬਿੱਟ + 7) / 8;

    av_assert0(ਮਾਪ_ਬਾਈਟਾਂ <= AV_HDR_PLUS_MAX_PAYLOAD_ਮਾਪ);

    ਜੇ (!ਅੰਕੜੇ) {
        *ਮਾਪ = ਮਾਪ_ਬਾਈਟਾਂ;
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ ਜੇ (*ਅੰਕੜੇ) {
        ਜੇ (*ਮਾਪ < ਮਾਪ_ਬਾਈਟਾਂ)
            ਵਾਪਸ AVERROR_ਬਫਰ_TOO_SMALL;
        buf = *ਅੰਕੜੇ;
    } ਨਹੀਂਤਾਂ {
        buf = av_malloc(ਮਾਪ_ਬਾਈਟਾਂ);
        ਜੇ (!buf)
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    init_put_ਬਿੱਟ(pb, buf, ਮਾਪ_ਬਾਈਟਾਂ);

    // application_mode is set to Application Version 1
    put_ਬਿੱਟ(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_ਬਿੱਟ(pb, 2, s->ਅੰਕ_windows);

    ਲਈ (ਪੂਰਨ w = 1; w < s->ਅੰਕ_windows; w++) {
        put_ਬਿੱਟ(pb, 16, s->params[w].ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_x.ਅੰਕ / s->params[w].ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_x.den);
        put_ਬਿੱਟ(pb, 16, s->params[w].ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_y.ਅੰਕ / s->params[w].ਖਿੜਕੀ_ਉੱਤਲਾ_ਖੱਬਾ_ਕੋਨਾ_y.den);
        put_ਬਿੱਟ(pb, 16, s->params[w].ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_x.ਅੰਕ / s->params[w].ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_x.den);
        put_ਬਿੱਟ(pb, 16, s->params[w].ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_y.ਅੰਕ / s->params[w].ਖਿੜਕੀ_ਹੇਠਲਾ_ਸੱਜਾ_ਕੋਨਾ_y.den);
        put_ਬਿੱਟ(pb, 16, s->params[w].center_ਦਾ_ellipse_x);
        put_ਬਿੱਟ(pb, 16, s->params[w].center_ਦਾ_ellipse_y);
        put_ਬਿੱਟ(pb, 8, s->params[w].rotation_angle);
        put_ਬਿੱਟ(pb, 16, s->params[w].semimajor_axis_ਅੰਦਰੂਨੀ_ellipse);
        put_ਬਿੱਟ(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_ਬਿੱਟ(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_ਬਿੱਟ(pb, 1, s->params[w].overlap_process_option);
    }

    put_ਬਿੱਟ(pb, 27, s->targeted_system_display_ਵੱਧ_ਤੋਂ_ਵੱਧ_luminance.ਅੰਕ * luminance_den /
        s->targeted_system_display_ਵੱਧ_ਤੋਂ_ਵੱਧ_luminance.den);
    put_ਬਿੱਟ(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    ਜੇ (s->targeted_system_display_actual_peak_luminance_flag) {
        put_ਬਿੱਟ(pb, 5, s->ਅੰਕ_ਪੰਕਤੀਆਂ_targeted_system_display_actual_peak_luminance);
        put_ਬਿੱਟ(pb, 5, s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_targeted_system_display_actual_peak_luminance);
        ਲਈ (ਪੂਰਨ i = 0; i < s->ਅੰਕ_ਪੰਕਤੀਆਂ_targeted_system_display_actual_peak_luminance; i++) {
            ਲਈ (ਪੂਰਨ j = 0; j < s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_targeted_system_display_actual_peak_luminance; j++)
                put_ਬਿੱਟ(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].ਅੰਕ * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    ਲਈ (ਪੂਰਨ w = 0; w < s->ਅੰਕ_windows; w++) {
        ਲਈ (ਪੂਰਨ i = 0; i < 3; i++)
            put_ਬਿੱਟ(pb, 17, s->params[w].maxscl[i].ਅੰਕ * rgb_den / s->params[w].maxscl[i].den);
        put_ਬਿੱਟ(pb, 17, s->params[w].ਔਸਤਨ_maxrgb.ਅੰਕ * rgb_den / s->params[w].ਔਸਤਨ_maxrgb.den);
        put_ਬਿੱਟ(pb, 4, s->params[w].ਅੰਕ_distribution_maxrgb_percentiles);
        ਲਈ (ਪੂਰਨ i = 0; i < s->params[w].ਅੰਕ_distribution_maxrgb_percentiles; i++) {
            put_ਬਿੱਟ(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_ਬਿੱਟ(pb, 17, s->params[w].distribution_maxrgb[i].percentile.ਅੰਕ * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_ਬਿੱਟ(pb, 10, s->params[w].fraction_bright_pixels.ਅੰਕ * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_ਬਿੱਟ(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    ਜੇ (s->mastering_display_actual_peak_luminance_flag) {
        put_ਬਿੱਟ(pb, 5, s->ਅੰਕ_ਪੰਕਤੀਆਂ_mastering_display_actual_peak_luminance);
        put_ਬਿੱਟ(pb, 5, s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_mastering_display_actual_peak_luminance);
        ਲਈ (ਪੂਰਨ i = 0; i < s->ਅੰਕ_ਪੰਕਤੀਆਂ_mastering_display_actual_peak_luminance; i++) {
            ਲਈ (ਪੂਰਨ j = 0; j < s->ਅੰਕ_ਖਾਨੇ_ਗਿਣਤੀ_mastering_display_actual_peak_luminance; j++)
                put_ਬਿੱਟ(pb, 4, s->mastering_display_actual_peak_luminance[i][j].ਅੰਕ * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    ਲਈ (ਪੂਰਨ w = 0; w < s->ਅੰਕ_windows; w++) {
        put_ਬਿੱਟ(pb, 1, s->params[w].tone_mapping_flag);
        ਜੇ (s->params[w].tone_mapping_flag) {
            put_ਬਿੱਟ(pb, 12, s->params[w].knee_ਬਿੰਦੂ_x.ਅੰਕ * knee_ਬਿੰਦੂ_den / s->params[w].knee_ਬਿੰਦੂ_x.den);
            put_ਬਿੱਟ(pb, 12, s->params[w].knee_ਬਿੰਦੂ_y.ਅੰਕ * knee_ਬਿੰਦੂ_den / s->params[w].knee_ਬਿੰਦੂ_y.den);
            put_ਬਿੱਟ(pb, 4, s->params[w].ਅੰਕ_bezier_ਵਕਰ_anchors);
            ਲਈ (ਪੂਰਨ i = 0; i < s->params[w].ਅੰਕ_bezier_ਵਕਰ_anchors; i++)
                put_ਬਿੱਟ(pb, 10, s->params[w].bezier_ਵਕਰ_anchors[i].ਅੰਕ * bezier_anchor_den /
                    s->params[w].bezier_ਵਕਰ_anchors[i].den);
        }
        put_ਬਿੱਟ(pb, 1, s->params[w].color_saturation_mapping_flag);
        ਜੇ (s->params[w].color_saturation_mapping_flag)
            put_ਬਿੱਟ(pb, 6, s->params[w].color_saturation_ਭਾਰ.ਅੰਕ * saturation_ਭਾਰ_den /
                s->params[w].color_saturation_ਭਾਰ.den);
    }

    flush_put_ਬਿੱਟ(pb);

    *ਅੰਕੜੇ = buf;
    ਜੇ (ਮਾਪ)
        *ਮਾਪ = ਮਾਪ_ਬਾਈਟਾਂ;
    ਵਾਪਸ 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *ਮਾਪ)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(ਆਕਾਰ(AVDynamicHDRSmpte2094App5));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = smpte2094_app5 ? ਆਕਾਰ(*smpte2094_app5) : 0;

    ਵਾਪਸ smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ,
                                                        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        ਆਕਾਰ(AVDynamicHDRSmpte2094App5));
    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    memset(side_ਅੰਕੜੇ->ਅੰਕੜੇ, 0, ਆਕਾਰ(AVDynamicHDRSmpte2094App5));

    ਵਾਪਸ (AVDynamicHDRSmpte2094App5 *)side_ਅੰਕੜੇ->ਅੰਕੜੇ;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ GET_ਬਿੱਟ_OR_FAIL(var, n)        \
    ਕਰੋ {                                \
        ਜੇ (get_ਬਿੱਟ_ਖੱਬਾ(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            ਜਾਓ ਸਿਰਾ;                   \
        }                               \
        var = get_ਬਿੱਟ(gb, n);          \
    } ਜਦੋਂ (0)

ਪੂਰਨ av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, ਅਚਲ uint8_t *ਅੰਕੜੇ,
                                           size_t ਮਾਪ)
{
    Get_ਦੋਆਧਾਰੀ_ਅੰਕ_Context gbc, *gb = &gbc;
    ਪੂਰਨ ret, reserved_zero;
    size_t padded_ਮਾਪ = ਮਾਪ + AV_ਨਿਵੇਸ਼_ਬਫਰ_PADDING_ਮਾਪ;

    ਜੇ (!s)
        ਵਾਪਸ AVERROR(EINVAL);

    uint8_t *padded_ਅੰਕੜੇ = av_mallocz(padded_ਮਾਪ);
    ਜੇ (!padded_ਅੰਕੜੇ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(padded_ਅੰਕੜੇ, ਅੰਕੜੇ, ਮਾਪ);
    ret = init_get_bits8(gb, padded_ਅੰਕੜੇ, ਮਾਪ);
    ਜੇ (ret < 0)
        ਜਾਓ ਸਿਰਾ;

    // Table C.1
    GET_ਬਿੱਟ_OR_FAIL(s->application_ਸੰਸਕਰਣ, 3);
    GET_ਬਿੱਟ_OR_FAIL(s->minimum_application_ਸੰਸਕਰਣ, 3);
    GET_ਬਿੱਟ_OR_FAIL(reserved_zero, 2);
    ਜੇ (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        ਜਾਓ ਸਿਰਾ;
    }

    // Table C.2
    GET_ਬਿੱਟ_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_ਬਿੱਟ_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_ਬਿੱਟ_OR_FAIL(reserved_zero, 6);
    ਜੇ (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        ਜਾਓ ਸਿਰਾ;
    }
    ਜੇ (s->has_custom_hdr_reference_white_flag)
        GET_ਬਿੱਟ_OR_FAIL(s->hdr_reference_white, 16);
    ਜੇ (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        ਜਾਓ ਸਿਰਾ;
    }

    // Table C.3
    GET_ਬਿੱਟ_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_ਬਿੱਟ_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    ਜੇ (s->use_reference_white_tone_mapping_flag) {
        GET_ਬਿੱਟ_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        ਜਾਓ ਸਿਰਾ;
    }
    GET_ਬਿੱਟ_OR_FAIL(s->ਅੰਕ_alternate_images, 3);
    ਜੇ (s->ਅੰਕ_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        ਜਾਓ ਸਿਰਾ;
    }
    GET_ਬਿੱਟ_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_ਬਿੱਟ_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_ਬਿੱਟ_OR_FAIL(s->has_common_ਵਕਰ_params_flag, 1);
    ਜੇ (s->gain_application_space_chromaticities_flag == 3)
        ਲਈ (ਪੂਰਨ r = 0; r < 8; r++)
            GET_ਬਿੱਟ_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    ਲਈ (ਪੂਰਨ a = 0; a < s->ਅੰਕ_alternate_images; a++) {
        GET_ਬਿੱਟ_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        ਜੇ (!a || !s->has_common_component_mix_params_flag) {
            GET_ਬਿੱਟ_OR_FAIL(s->component_mixing_type[a], 2);
            ਜੇ (s->component_mixing_type[a] != 3) {
                GET_ਬਿੱਟ_OR_FAIL(reserved_zero, 6);
                ਜੇ (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    ਜਾਓ ਸਿਰਾ;
                }
            } ਨਹੀਂਤਾਂ {
                ਲਈ (ਪੂਰਨ k = 0; k < 6; k++)
                    GET_ਬਿੱਟ_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                ਲਈ (ਪੂਰਨ k = 0; k < 6; k++) {
                    ਜੇ (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_ਬਿੱਟ_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } ਨਹੀਂਤਾਂ {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } ਨਹੀਂਤਾਂ {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            ਜੇ (s->component_mixing_type[a] == 3) {
                ਲਈ (ਪੂਰਨ k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        ਜੇ (!a || !s->has_common_ਵਕਰ_params_flag) {
            GET_ਬਿੱਟ_OR_FAIL(s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a], 5);
            ਜੇ (s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                ਜਾਓ ਸਿਰਾ;
            }
            GET_ਬਿੱਟ_OR_FAIL(s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a], 1);
            GET_ਬਿੱਟ_OR_FAIL(reserved_zero, 2);
            ਜੇ (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                ਜਾਓ ਸਿਰਾ;
            }
            ਲਈ (ਪੂਰਨ c = 0; c <= s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a]; c++) {
                GET_ਬਿੱਟ_OR_FAIL(s->gain_ਵਕਰ_control_points_x[a][c], 16);
            }
        } ਨਹੀਂਤਾਂ {
            s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a] =
                    s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[0];
            s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a] = s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[0];
            ਲਈ (ਪੂਰਨ c = 0; c <= s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a]; c++) {
                s->gain_ਵਕਰ_control_points_x[a][c] = s->gain_ਵਕਰ_control_points_x[0][c];
            }
        }
        ਲਈ (ਪੂਰਨ c = 0; c <= s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a]; c++)
            GET_ਬਿੱਟ_OR_FAIL(s->gain_ਵਕਰ_control_points_y[a][c], 16);
        ਜੇ (!s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a]) {
            ਲਈ (ਪੂਰਨ c = 0; c <= s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a]; c++)
                GET_ਬਿੱਟ_OR_FAIL(s->gain_ਵਕਰ_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
ਸਿਰਾ:
    av_free(padded_ਅੰਕੜੇ);
    ਵਾਪਸ ret;
}

ਪੂਰਨ av_dynamic_hdr_smpte2094_app5_ਮੰਜ਼ਿਲ_t35(ਅਚਲ AVDynamicHDRSmpte2094App5 *s, uint8_t **ਅੰਕੜੇ,
                                         size_t *ਮਾਪ)
{
    uint8_t *buf;
    size_t ਮਾਪ_ਬਾਈਟਾਂ, ਮਾਪ_ਬਿੱਟ;
    Put_ਦੋਆਧਾਰੀ_ਅੰਕ_Context pbc, *pb = &pbc;

    ਜੇ (!s)
        ਵਾਪਸ AVERROR(EINVAL);
    ਜੇ ((!ਅੰਕੜੇ || *ਅੰਕੜੇ) && !ਮਾਪ)
       ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (s->application_ਸੰਸਕਰਣ >= 8 || s->minimum_application_ਸੰਸਕਰਣ >= 3)
        ਵਾਪਸ AVERROR_INVALIDDATA;
    ਮਾਪ_ਬਿੱਟ = 0;
    ਮਾਪ_ਬਿੱਟ += 3 + 3 + 2;
    ਮਾਪ_ਬਿੱਟ += 1 + 1 + 6;
    ਜੇ (s->has_custom_hdr_reference_white_flag)
        ਮਾਪ_ਬਿੱਟ += 16;
    ਜੇ (s->has_adaptive_tone_map_flag) {
        ਮਾਪ_ਬਿੱਟ += 16 + 1;
        ਜੇ (s->use_reference_white_tone_mapping_flag) {
            ਮਾਪ_ਬਿੱਟ += 7;
        } ਨਹੀਂਤਾਂ {
            ਮਾਪ_ਬਿੱਟ += 3 + 2 + 1 + 1;
            ਜੇ (s->gain_application_space_chromaticities_flag == 3)
                ਮਾਪ_ਬਿੱਟ += 16 * 8;
            ਜੇ (s->ਅੰਕ_alternate_images > 4)
                ਵਾਪਸ AVERROR_INVALIDDATA;
            ਲਈ (ਪੂਰਨ a = 0; a < s->ਅੰਕ_alternate_images; a++) {
                ਮਾਪ_ਬਿੱਟ += 16;
                ਜੇ (!a || !s->has_common_component_mix_params_flag) {
                    ਮਾਪ_ਬਿੱਟ += 2;
                    ਜੇ (s->component_mixing_type[a] != 3) {
                        ਮਾਪ_ਬਿੱਟ += 6;
                    } ਨਹੀਂਤਾਂ {
                        ਮਾਪ_ਬਿੱਟ += 6;
                        ਲਈ (ਪੂਰਨ k = 0; k < 6; k++)
                          ਜੇ (s->has_component_mixing_coefficient_flag[a][k])
                            ਮਾਪ_ਬਿੱਟ += 16;
                    }
                }
                ਜੇ (!a || !s->has_common_ਵਕਰ_params_flag) {
                    ਮਾਪ_ਬਿੱਟ += 5 + 1 + 2;
                    ਜੇ (s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a] > 31)
                        ਵਾਪਸ AVERROR_INVALIDDATA;
                    ਮਾਪ_ਬਿੱਟ += 16 * (s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a] + 1);
                }
                ਮਾਪ_ਬਿੱਟ += 16 * (s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a] + 1);
                ਜੇ (!s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a])
                    ਮਾਪ_ਬਿੱਟ += 16 * (s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a] + 1);
            }
        }
    }
    ਜੇ (ਮਾਪ_ਬਿੱਟ % 8)
      ਵਾਪਸ AVERROR_INVALIDDATA;
    ਮਾਪ_ਬਾਈਟਾਂ = ਮਾਪ_ਬਿੱਟ >> 3;

    ਜੇ (!ਅੰਕੜੇ) {
        *ਮਾਪ = ਮਾਪ_ਬਾਈਟਾਂ;
        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ ਜੇ (*ਅੰਕੜੇ) {
        ਜੇ (*ਮਾਪ < ਮਾਪ_ਬਾਈਟਾਂ)
            ਵਾਪਸ AVERROR_ਬਫਰ_TOO_SMALL;
        buf = *ਅੰਕੜੇ;
    } ਨਹੀਂਤਾਂ {
        buf = av_malloc(ਮਾਪ_ਬਾਈਟਾਂ);
        ਜੇ (!buf)
            ਵਾਪਸ AVERROR(ENOMEM);
    }

    init_put_ਬਿੱਟ(pb, buf, ਮਾਪ_ਬਾਈਟਾਂ);

    // Table C.1
    put_ਬਿੱਟ(pb, 3, s->application_ਸੰਸਕਰਣ);
    put_ਬਿੱਟ(pb, 3, s->minimum_application_ਸੰਸਕਰਣ);
    put_ਬਿੱਟ(pb, 2, 0); // reserved_zero

    // Table C.2
    put_ਬਿੱਟ(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_ਬਿੱਟ(pb, 1, s->has_adaptive_tone_map_flag);
    put_ਬਿੱਟ(pb, 6, 0); // reserved_zero

    ਜੇ (s->has_custom_hdr_reference_white_flag)
        put_ਬਿੱਟ(pb, 16, s->hdr_reference_white);

    ਜੇ (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_ਬਿੱਟ(pb, 16, s->baseline_hdr_headroom);
        put_ਬਿੱਟ(pb, 1, s->use_reference_white_tone_mapping_flag);
        ਜੇ (s->use_reference_white_tone_mapping_flag) {
            put_ਬਿੱਟ(pb, 7, 0); // reserved_zero
        } ਨਹੀਂਤਾਂ {
            put_ਬਿੱਟ(pb, 3, s->ਅੰਕ_alternate_images);
            put_ਬਿੱਟ(pb, 2, s->gain_application_space_chromaticities_flag);
            put_ਬਿੱਟ(pb, 1, s->has_common_component_mix_params_flag);
            put_ਬਿੱਟ(pb, 1, s->has_common_ਵਕਰ_params_flag);

            ਜੇ (s->gain_application_space_chromaticities_flag == 3)
                ਲਈ (ਪੂਰਨ r = 0; r < 8; r++)
                    put_ਬਿੱਟ(pb, 16, s->gain_application_space_chromaticities[r]);

            ਲਈ (ਪੂਰਨ a = 0; a < s->ਅੰਕ_alternate_images; a++) {
                put_ਬਿੱਟ(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                ਜੇ (!a || !s->has_common_component_mix_params_flag) {
                    put_ਬਿੱਟ(pb, 2, s->component_mixing_type[a]);
                    ਜੇ (s->component_mixing_type[a] != 3) {
                        put_ਬਿੱਟ(pb, 6, 0); // reserved_zero
                    } ਨਹੀਂਤਾਂ {
                        ਲਈ (ਪੂਰਨ k = 0; k < 6; k++)
                            put_ਬਿੱਟ(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        ਲਈ (ਪੂਰਨ k = 0; k < 6; k++)
                            ਜੇ (s->has_component_mixing_coefficient_flag[a][k])
                                put_ਬਿੱਟ(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                ਜੇ (!a || !s->has_common_ਵਕਰ_params_flag) {
                    put_ਬਿੱਟ(pb, 5, s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a]);
                    put_ਬਿੱਟ(pb, 1, s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a]);
                    put_ਬਿੱਟ(pb, 2, 0); // reserved_zero
                    ਲਈ (ਪੂਰਨ c = 0; c <= s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a]; c++)
                        put_ਬਿੱਟ(pb, 16, s->gain_ਵਕਰ_control_points_x[a][c]);
                }
                ਲਈ (ਪੂਰਨ c = 0; c <= s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a]; c++)
                    put_ਬਿੱਟ(pb, 16, s->gain_ਵਕਰ_control_points_y[a][c]);
                ਜੇ (!s->gain_ਵਕਰ_use_pchip_ਢਲਾਨ_flag[a]) {
                    ਲਈ (ਪੂਰਨ c = 0; c <= s->gain_ਵਕਰ_ਅੰਕ_control_points_minus_1[a]; c++)
                        put_ਬਿੱਟ(pb, 16, s->gain_ਵਕਰ_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_ਬਿੱਟ(pb);

    *ਅੰਕੜੇ = buf;
    ਜੇ (ਮਾਪ)
        *ਮਾਪ = ਮਾਪ_ਬਾਈਟਾਂ;
    ਵਾਪਸ 0;
}

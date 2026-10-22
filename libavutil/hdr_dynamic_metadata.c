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

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "hdr_dynamic_metadata.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "libavcodec/defs.h"
#అన్తర్భావ "libavcodec/get_bits.h"
#అన్తర్భావ "libavcodec/put_bits.h"

స్థిర స్థిరరాశి int64_t luminance_den = 1;
స్థిర స్థిరరాశి int32_t peak_luminance_den = 15;
స్థిర స్థిరరాశి int64_t rgb_den = 100000;
స్థిర స్థిరరాశి int32_t fraction_pixel_den = 1000;
స్థిర స్థిరరాశి int32_t knee_బిందువు_den = 4095;
స్థిర స్థిరరాశి int32_t bezier_anchor_den = 1023;
స్థిర స్థిరరాశి int32_t saturation_బరువు_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *కొలత)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(పరిమాణం(AVDynamicHDRPlus));

    ఒకవేళ (కొలత)
        *కొలత = hdr_plus ? పరిమాణం(*hdr_plus) : 0;

    తిరిగి hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_దత్తాంశం(AVFrame *చట్రం)
{
    AVFrame_Side_దత్తాంశం *side_దత్తాంశం = av_చట్రం_new_side_దత్తాంశం(చట్రం,
                                                        AV_చట్రం_దత్తాంశం_DYNAMIC_HDR_PLUS,
                                                        పరిమాణం(AVDynamicHDRPlus));
    ఒకవేళ (!side_దత్తాంశం)
        తిరిగి ఖాళీ;

    memset(side_దత్తాంశం->దత్తాంశం, 0, పరిమాణం(AVDynamicHDRPlus));

    తిరిగి (AVDynamicHDRPlus *)side_దత్తాంశం->దత్తాంశం;
}

పూర్ణాంకం av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, స్థిరరాశి uint8_t *దత్తాంశం,
                                 size_t కొలత)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_కొలత + AV_ఆదానం_బఫరు_PADDING_కొలత];
    Get_బిట్టు_Context gbc, *gb = &gbc;
    పూర్ణాంకం ret;

    ఒకవేళ (!s)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (కొలత > AV_HDR_PLUS_MAX_PAYLOAD_కొలత)
        తిరిగి AVERROR(EINVAL);

    జ్ఞాపకం_నకలు(padded_buf, దత్తాంశం, కొలత);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    memset(padded_buf + కొలత, 0, AV_ఆదానం_బఫరు_PADDING_కొలత);

    ret = init_get_bits8(gb, padded_buf, కొలత);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 10)
        తిరిగి AVERROR_INVALIDDATA;

    s->application_సంస్కరణ = get_బిట్లు(gb, 8);
    s->అంకె_windows = get_బిట్లు(gb, 2);

    ఒకవేళ (s->అంకె_windows < 1 || s->అంకె_windows > 3) {
        తిరిగి AVERROR_INVALIDDATA;
    }

    ఒకవేళ (get_బిట్లు_ఎడమ(gb) < ((19 * 8 + 1) * (s->అంకె_windows - 1)))
        తిరిగి AVERROR_INVALIDDATA;

    కొరకు (పూర్ణాంకం w = 1; w < s->అంకె_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->కిటికీ_పై_ఎడమ_మూల_x =
            (AVRational){get_బిట్లు(gb, 16), 1};
        params->కిటికీ_పై_ఎడమ_మూల_y =
            (AVRational){get_బిట్లు(gb, 16), 1};
        params->కిటికీ_క్రింది_కుడి_మూల_x =
            (AVRational){get_బిట్లు(gb, 16), 1};
        params->కిటికీ_క్రింది_కుడి_మూల_y =
            (AVRational){get_బిట్లు(gb, 16), 1};

        params->center_యొక్క_ellipse_x = get_బిట్లు(gb, 16);
        params->center_యొక్క_ellipse_y = get_బిట్లు(gb, 16);
        params->rotation_angle = get_బిట్లు(gb, 8);
        params->semimajor_axis_అంతర్గత_ellipse = get_బిట్లు(gb, 16);
        params->semimajor_axis_external_ellipse = get_బిట్లు(gb, 16);
        params->semiminor_axis_external_ellipse = get_బిట్లు(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 28)
        తిరిగి AVERROR_INVALIDDATA;

    s->targeted_system_display_గరిష్ఠ_luminance =
        (AVRational){get_బిట్లు_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    ఒకవేళ (s->targeted_system_display_actual_peak_luminance_flag) {
        పూర్ణాంకం అడ్డువరుసలు, నిలువుల_సంఖ్య;
        ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 10)
            తిరిగి AVERROR_INVALIDDATA;
        అడ్డువరుసలు = get_బిట్లు(gb, 5);
        నిలువుల_సంఖ్య = get_బిట్లు(gb, 5);
        ఒకవేళ (((అడ్డువరుసలు < 2) || (అడ్డువరుసలు > 25)) || ((నిలువుల_సంఖ్య < 2) || (నిలువుల_సంఖ్య > 25))) {
            తిరిగి AVERROR_INVALIDDATA;
        }
        s->అంకె_అడ్డువరుసలు_targeted_system_display_actual_peak_luminance = అడ్డువరుసలు;
        s->అంకె_నిలువుల_సంఖ్య_targeted_system_display_actual_peak_luminance = నిలువుల_సంఖ్య;

        ఒకవేళ (get_బిట్లు_ఎడమ(gb) < (అడ్డువరుసలు * నిలువుల_సంఖ్య * 4))
            తిరిగి AVERROR_INVALIDDATA;

        కొరకు (పూర్ణాంకం i = 0; i < అడ్డువరుసలు; i++) {
            కొరకు (పూర్ణాంకం j = 0; j < నిలువుల_సంఖ్య; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_బిట్లు(gb, 4), peak_luminance_den};
            }
        }
    }
    కొరకు (పూర్ణాంకం w = 0; w < s->అంకె_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        ఒకవేళ (get_బిట్లు_ఎడమ(gb) < (3 * 17 + 17 + 4))
            తిరిగి AVERROR_INVALIDDATA;

        కొరకు (పూర్ణాంకం i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_బిట్లు(gb, 17), rgb_den};
        }
        params->సరాసరి_maxrgb =
            (AVRational){get_బిట్లు(gb, 17), rgb_den};
        params->అంకె_distribution_maxrgb_percentiles = get_బిట్లు(gb, 4);

        ఒకవేళ (get_బిట్లు_ఎడమ(gb) <
            (params->అంకె_distribution_maxrgb_percentiles * 24))
            తిరిగి AVERROR_INVALIDDATA;

        కొరకు (పూర్ణాంకం i = 0; i < params->అంకె_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_బిట్లు(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_బిట్లు(gb, 17), rgb_den};
        }

        ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 10)
            తిరిగి AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_బిట్లు(gb, 10), fraction_pixel_den};
    }
    ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 1)
        తిరిగి AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    ఒకవేళ (s->mastering_display_actual_peak_luminance_flag) {
        పూర్ణాంకం అడ్డువరుసలు, నిలువుల_సంఖ్య;
        ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 10)
            తిరిగి AVERROR_INVALIDDATA;
        అడ్డువరుసలు = get_బిట్లు(gb, 5);
        నిలువుల_సంఖ్య = get_బిట్లు(gb, 5);
        ఒకవేళ (((అడ్డువరుసలు < 2) || (అడ్డువరుసలు > 25)) || ((నిలువుల_సంఖ్య < 2) || (నిలువుల_సంఖ్య > 25))) {
            తిరిగి AVERROR_INVALIDDATA;
        }
        s->అంకె_అడ్డువరుసలు_mastering_display_actual_peak_luminance = అడ్డువరుసలు;
        s->అంకె_నిలువుల_సంఖ్య_mastering_display_actual_peak_luminance = నిలువుల_సంఖ్య;

        ఒకవేళ (get_బిట్లు_ఎడమ(gb) < (అడ్డువరుసలు * నిలువుల_సంఖ్య * 4))
            తిరిగి AVERROR_INVALIDDATA;

        కొరకు (పూర్ణాంకం i = 0; i < అడ్డువరుసలు; i++) {
            కొరకు (పూర్ణాంకం j = 0; j < నిలువుల_సంఖ్య; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_బిట్లు(gb, 4), peak_luminance_den};
            }
        }
    }

    కొరకు (పూర్ణాంకం w = 0; w < s->అంకె_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 1)
            తిరిగి AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        ఒకవేళ (params->tone_mapping_flag) {
            ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 28)
                తిరిగి AVERROR_INVALIDDATA;

            params->knee_బిందువు_x =
                (AVRational){get_బిట్లు(gb, 12), knee_బిందువు_den};
            params->knee_బిందువు_y =
                (AVRational){get_బిట్లు(gb, 12), knee_బిందువు_den};
            params->అంకె_bezier_వక్రం_anchors = get_బిట్లు(gb, 4);

            ఒకవేళ (get_బిట్లు_ఎడమ(gb) < (params->అంకె_bezier_వక్రం_anchors * 10))
                తిరిగి AVERROR_INVALIDDATA;

            కొరకు (పూర్ణాంకం i = 0; i < params->అంకె_bezier_వక్రం_anchors; i++) {
                params->bezier_వక్రం_anchors[i] =
                    (AVRational){get_బిట్లు(gb, 10), bezier_anchor_den};
            }
        }

        ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 1)
            తిరిగి AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        ఒకవేళ (params->color_saturation_mapping_flag) {
            ఒకవేళ (get_బిట్లు_ఎడమ(gb) < 6)
                తిరిగి AVERROR_INVALIDDATA;
            params->color_saturation_బరువు =
                (AVRational){get_బిట్లు(gb, 6), saturation_బరువు_den};
        }
    }

    తిరిగి 0;
}

పూర్ణాంకం av_dynamic_hdr_plus_గమ్యం_t35(స్థిరరాశి AVDynamicHDRPlus *s, uint8_t **దత్తాంశం, size_t *కొలత)
{
    uint8_t *buf;
    size_t కొలత_బిట్లు, కొలత_బైట్లు;
    Put_బిట్టు_Context pbc, *pb = &pbc;

    ఒకవేళ (!s)
        తిరిగి AVERROR(EINVAL);
    ఒకవేళ ((!దత్తాంశం || *దత్తాంశం) && !కొలత)
       తిరిగి AVERROR(EINVAL);

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
    కొలత_బిట్లు = 8;

    కొలత_బిట్లు += 2;

    కొరకు (పూర్ణాంకం w = 1; w < s->అంకె_windows; w++)
        కొలత_బిట్లు += 153;

    కొలత_బిట్లు += 27;

    కొలత_బిట్లు += 1;
    ఒకవేళ (s->targeted_system_display_actual_peak_luminance_flag)
        కొలత_బిట్లు += 10 +
                     s->అంకె_అడ్డువరుసలు_targeted_system_display_actual_peak_luminance *
                     s->అంకె_నిలువుల_సంఖ్య_targeted_system_display_actual_peak_luminance * 4;

    కొరకు (పూర్ణాంకం w = 0; w < s->అంకె_windows; w++)
        కొలత_బిట్లు += 72 + s->params[w].అంకె_distribution_maxrgb_percentiles * 24 + 10;

    కొలత_బిట్లు += 1;
    ఒకవేళ (s->mastering_display_actual_peak_luminance_flag)
        కొలత_బిట్లు += 10 +
                     s->అంకె_అడ్డువరుసలు_mastering_display_actual_peak_luminance *
                     s->అంకె_నిలువుల_సంఖ్య_mastering_display_actual_peak_luminance * 4;

    కొరకు (పూర్ణాంకం w = 0; w < s->అంకె_windows; w++) {
        కొలత_బిట్లు += 1;
        ఒకవేళ (s->params[w].tone_mapping_flag)
            కొలత_బిట్లు += 28 + s->params[w].అంకె_bezier_వక్రం_anchors * 10;

        కొలత_బిట్లు += 1;
        ఒకవేళ (s->params[w].color_saturation_mapping_flag)
            కొలత_బిట్లు += 6;
    }

    కొలత_బైట్లు = (కొలత_బిట్లు + 7) / 8;

    av_assert0(కొలత_బైట్లు <= AV_HDR_PLUS_MAX_PAYLOAD_కొలత);

    ఒకవేళ (!దత్తాంశం) {
        *కొలత = కొలత_బైట్లు;
        తిరిగి 0;
    } లేకపోతే ఒకవేళ (*దత్తాంశం) {
        ఒకవేళ (*కొలత < కొలత_బైట్లు)
            తిరిగి AVERROR_బఫరు_TOO_SMALL;
        buf = *దత్తాంశం;
    } లేకపోతే {
        buf = av_malloc(కొలత_బైట్లు);
        ఒకవేళ (!buf)
            తిరిగి AVERROR(ENOMEM);
    }

    init_put_బిట్లు(pb, buf, కొలత_బైట్లు);

    // application_mode is set to Application Version 1
    put_బిట్లు(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_బిట్లు(pb, 2, s->అంకె_windows);

    కొరకు (పూర్ణాంకం w = 1; w < s->అంకె_windows; w++) {
        put_బిట్లు(pb, 16, s->params[w].కిటికీ_పై_ఎడమ_మూల_x.అంకె / s->params[w].కిటికీ_పై_ఎడమ_మూల_x.den);
        put_బిట్లు(pb, 16, s->params[w].కిటికీ_పై_ఎడమ_మూల_y.అంకె / s->params[w].కిటికీ_పై_ఎడమ_మూల_y.den);
        put_బిట్లు(pb, 16, s->params[w].కిటికీ_క్రింది_కుడి_మూల_x.అంకె / s->params[w].కిటికీ_క్రింది_కుడి_మూల_x.den);
        put_బిట్లు(pb, 16, s->params[w].కిటికీ_క్రింది_కుడి_మూల_y.అంకె / s->params[w].కిటికీ_క్రింది_కుడి_మూల_y.den);
        put_బిట్లు(pb, 16, s->params[w].center_యొక్క_ellipse_x);
        put_బిట్లు(pb, 16, s->params[w].center_యొక్క_ellipse_y);
        put_బిట్లు(pb, 8, s->params[w].rotation_angle);
        put_బిట్లు(pb, 16, s->params[w].semimajor_axis_అంతర్గత_ellipse);
        put_బిట్లు(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_బిట్లు(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_బిట్లు(pb, 1, s->params[w].overlap_process_option);
    }

    put_బిట్లు(pb, 27, s->targeted_system_display_గరిష్ఠ_luminance.అంకె * luminance_den /
        s->targeted_system_display_గరిష్ఠ_luminance.den);
    put_బిట్లు(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    ఒకవేళ (s->targeted_system_display_actual_peak_luminance_flag) {
        put_బిట్లు(pb, 5, s->అంకె_అడ్డువరుసలు_targeted_system_display_actual_peak_luminance);
        put_బిట్లు(pb, 5, s->అంకె_నిలువుల_సంఖ్య_targeted_system_display_actual_peak_luminance);
        కొరకు (పూర్ణాంకం i = 0; i < s->అంకె_అడ్డువరుసలు_targeted_system_display_actual_peak_luminance; i++) {
            కొరకు (పూర్ణాంకం j = 0; j < s->అంకె_నిలువుల_సంఖ్య_targeted_system_display_actual_peak_luminance; j++)
                put_బిట్లు(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].అంకె * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    కొరకు (పూర్ణాంకం w = 0; w < s->అంకె_windows; w++) {
        కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
            put_బిట్లు(pb, 17, s->params[w].maxscl[i].అంకె * rgb_den / s->params[w].maxscl[i].den);
        put_బిట్లు(pb, 17, s->params[w].సరాసరి_maxrgb.అంకె * rgb_den / s->params[w].సరాసరి_maxrgb.den);
        put_బిట్లు(pb, 4, s->params[w].అంకె_distribution_maxrgb_percentiles);
        కొరకు (పూర్ణాంకం i = 0; i < s->params[w].అంకె_distribution_maxrgb_percentiles; i++) {
            put_బిట్లు(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_బిట్లు(pb, 17, s->params[w].distribution_maxrgb[i].percentile.అంకె * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_బిట్లు(pb, 10, s->params[w].fraction_bright_pixels.అంకె * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_బిట్లు(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    ఒకవేళ (s->mastering_display_actual_peak_luminance_flag) {
        put_బిట్లు(pb, 5, s->అంకె_అడ్డువరుసలు_mastering_display_actual_peak_luminance);
        put_బిట్లు(pb, 5, s->అంకె_నిలువుల_సంఖ్య_mastering_display_actual_peak_luminance);
        కొరకు (పూర్ణాంకం i = 0; i < s->అంకె_అడ్డువరుసలు_mastering_display_actual_peak_luminance; i++) {
            కొరకు (పూర్ణాంకం j = 0; j < s->అంకె_నిలువుల_సంఖ్య_mastering_display_actual_peak_luminance; j++)
                put_బిట్లు(pb, 4, s->mastering_display_actual_peak_luminance[i][j].అంకె * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    కొరకు (పూర్ణాంకం w = 0; w < s->అంకె_windows; w++) {
        put_బిట్లు(pb, 1, s->params[w].tone_mapping_flag);
        ఒకవేళ (s->params[w].tone_mapping_flag) {
            put_బిట్లు(pb, 12, s->params[w].knee_బిందువు_x.అంకె * knee_బిందువు_den / s->params[w].knee_బిందువు_x.den);
            put_బిట్లు(pb, 12, s->params[w].knee_బిందువు_y.అంకె * knee_బిందువు_den / s->params[w].knee_బిందువు_y.den);
            put_బిట్లు(pb, 4, s->params[w].అంకె_bezier_వక్రం_anchors);
            కొరకు (పూర్ణాంకం i = 0; i < s->params[w].అంకె_bezier_వక్రం_anchors; i++)
                put_బిట్లు(pb, 10, s->params[w].bezier_వక్రం_anchors[i].అంకె * bezier_anchor_den /
                    s->params[w].bezier_వక్రం_anchors[i].den);
        }
        put_బిట్లు(pb, 1, s->params[w].color_saturation_mapping_flag);
        ఒకవేళ (s->params[w].color_saturation_mapping_flag)
            put_బిట్లు(pb, 6, s->params[w].color_saturation_బరువు.అంకె * saturation_బరువు_den /
                s->params[w].color_saturation_బరువు.den);
    }

    flush_put_బిట్లు(pb);

    *దత్తాంశం = buf;
    ఒకవేళ (కొలత)
        *కొలత = కొలత_బైట్లు;
    తిరిగి 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *కొలత)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(పరిమాణం(AVDynamicHDRSmpte2094App5));

    ఒకవేళ (కొలత)
        *కొలత = smpte2094_app5 ? పరిమాణం(*smpte2094_app5) : 0;

    తిరిగి smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_దత్తాంశం(AVFrame *చట్రం)
{
    AVFrame_Side_దత్తాంశం *side_దత్తాంశం = av_చట్రం_new_side_దత్తాంశం(చట్రం,
                                                        AV_చట్రం_దత్తాంశం_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        పరిమాణం(AVDynamicHDRSmpte2094App5));
    ఒకవేళ (!side_దత్తాంశం)
        తిరిగి ఖాళీ;

    memset(side_దత్తాంశం->దత్తాంశం, 0, పరిమాణం(AVDynamicHDRSmpte2094App5));

    తిరిగి (AVDynamicHDRSmpte2094App5 *)side_దత్తాంశం->దత్తాంశం;
}

#నిర్వచించు GET_బిట్లు_OR_FAIL(var, n)        \
    చేయి {                                \
        ఒకవేళ (get_బిట్లు_ఎడమ(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            వెళ్ళు చివర;                   \
        }                               \
        var = get_బిట్లు(gb, n);          \
    } అయితే (0)

పూర్ణాంకం av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, స్థిరరాశి uint8_t *దత్తాంశం,
                                           size_t కొలత)
{
    Get_బిట్టు_Context gbc, *gb = &gbc;
    పూర్ణాంకం ret, reserved_zero;
    size_t padded_కొలత = కొలత + AV_ఆదానం_బఫరు_PADDING_కొలత;

    ఒకవేళ (!s)
        తిరిగి AVERROR(EINVAL);

    uint8_t *padded_దత్తాంశం = av_mallocz(padded_కొలత);
    ఒకవేళ (!padded_దత్తాంశం)
        తిరిగి AVERROR(ENOMEM);

    జ్ఞాపకం_నకలు(padded_దత్తాంశం, దత్తాంశం, కొలత);
    ret = init_get_bits8(gb, padded_దత్తాంశం, కొలత);
    ఒకవేళ (ret < 0)
        వెళ్ళు చివర;

    // Table C.1
    GET_బిట్లు_OR_FAIL(s->application_సంస్కరణ, 3);
    GET_బిట్లు_OR_FAIL(s->minimum_application_సంస్కరణ, 3);
    GET_బిట్లు_OR_FAIL(reserved_zero, 2);
    ఒకవేళ (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        వెళ్ళు చివర;
    }

    // Table C.2
    GET_బిట్లు_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_బిట్లు_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_బిట్లు_OR_FAIL(reserved_zero, 6);
    ఒకవేళ (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        వెళ్ళు చివర;
    }
    ఒకవేళ (s->has_custom_hdr_reference_white_flag)
        GET_బిట్లు_OR_FAIL(s->hdr_reference_white, 16);
    ఒకవేళ (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        వెళ్ళు చివర;
    }

    // Table C.3
    GET_బిట్లు_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_బిట్లు_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    ఒకవేళ (s->use_reference_white_tone_mapping_flag) {
        GET_బిట్లు_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        వెళ్ళు చివర;
    }
    GET_బిట్లు_OR_FAIL(s->అంకె_alternate_images, 3);
    ఒకవేళ (s->అంకె_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        వెళ్ళు చివర;
    }
    GET_బిట్లు_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_బిట్లు_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_బిట్లు_OR_FAIL(s->has_common_వక్రం_params_flag, 1);
    ఒకవేళ (s->gain_application_space_chromaticities_flag == 3)
        కొరకు (పూర్ణాంకం r = 0; r < 8; r++)
            GET_బిట్లు_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    కొరకు (పూర్ణాంకం a = 0; a < s->అంకె_alternate_images; a++) {
        GET_బిట్లు_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        ఒకవేళ (!a || !s->has_common_component_mix_params_flag) {
            GET_బిట్లు_OR_FAIL(s->component_mixing_type[a], 2);
            ఒకవేళ (s->component_mixing_type[a] != 3) {
                GET_బిట్లు_OR_FAIL(reserved_zero, 6);
                ఒకవేళ (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    వెళ్ళు చివర;
                }
            } లేకపోతే {
                కొరకు (పూర్ణాంకం k = 0; k < 6; k++)
                    GET_బిట్లు_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                కొరకు (పూర్ణాంకం k = 0; k < 6; k++) {
                    ఒకవేళ (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_బిట్లు_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } లేకపోతే {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } లేకపోతే {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            ఒకవేళ (s->component_mixing_type[a] == 3) {
                కొరకు (పూర్ణాంకం k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        ఒకవేళ (!a || !s->has_common_వక్రం_params_flag) {
            GET_బిట్లు_OR_FAIL(s->gain_వక్రం_అంకె_control_points_minus_1[a], 5);
            ఒకవేళ (s->gain_వక్రం_అంకె_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                వెళ్ళు చివర;
            }
            GET_బిట్లు_OR_FAIL(s->gain_వక్రం_use_pchip_వాలు_flag[a], 1);
            GET_బిట్లు_OR_FAIL(reserved_zero, 2);
            ఒకవేళ (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                వెళ్ళు చివర;
            }
            కొరకు (పూర్ణాంకం c = 0; c <= s->gain_వక్రం_అంకె_control_points_minus_1[a]; c++) {
                GET_బిట్లు_OR_FAIL(s->gain_వక్రం_control_points_x[a][c], 16);
            }
        } లేకపోతే {
            s->gain_వక్రం_అంకె_control_points_minus_1[a] =
                    s->gain_వక్రం_అంకె_control_points_minus_1[0];
            s->gain_వక్రం_use_pchip_వాలు_flag[a] = s->gain_వక్రం_use_pchip_వాలు_flag[0];
            కొరకు (పూర్ణాంకం c = 0; c <= s->gain_వక్రం_అంకె_control_points_minus_1[a]; c++) {
                s->gain_వక్రం_control_points_x[a][c] = s->gain_వక్రం_control_points_x[0][c];
            }
        }
        కొరకు (పూర్ణాంకం c = 0; c <= s->gain_వక్రం_అంకె_control_points_minus_1[a]; c++)
            GET_బిట్లు_OR_FAIL(s->gain_వక్రం_control_points_y[a][c], 16);
        ఒకవేళ (!s->gain_వక్రం_use_pchip_వాలు_flag[a]) {
            కొరకు (పూర్ణాంకం c = 0; c <= s->gain_వక్రం_అంకె_control_points_minus_1[a]; c++)
                GET_బిట్లు_OR_FAIL(s->gain_వక్రం_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
చివర:
    av_free(padded_దత్తాంశం);
    తిరిగి ret;
}

పూర్ణాంకం av_dynamic_hdr_smpte2094_app5_గమ్యం_t35(స్థిరరాశి AVDynamicHDRSmpte2094App5 *s, uint8_t **దత్తాంశం,
                                         size_t *కొలత)
{
    uint8_t *buf;
    size_t కొలత_బైట్లు, కొలత_బిట్లు;
    Put_బిట్టు_Context pbc, *pb = &pbc;

    ఒకవేళ (!s)
        తిరిగి AVERROR(EINVAL);
    ఒకవేళ ((!దత్తాంశం || *దత్తాంశం) && !కొలత)
       తిరిగి AVERROR(EINVAL);

    ఒకవేళ (s->application_సంస్కరణ >= 8 || s->minimum_application_సంస్కరణ >= 3)
        తిరిగి AVERROR_INVALIDDATA;
    కొలత_బిట్లు = 0;
    కొలత_బిట్లు += 3 + 3 + 2;
    కొలత_బిట్లు += 1 + 1 + 6;
    ఒకవేళ (s->has_custom_hdr_reference_white_flag)
        కొలత_బిట్లు += 16;
    ఒకవేళ (s->has_adaptive_tone_map_flag) {
        కొలత_బిట్లు += 16 + 1;
        ఒకవేళ (s->use_reference_white_tone_mapping_flag) {
            కొలత_బిట్లు += 7;
        } లేకపోతే {
            కొలత_బిట్లు += 3 + 2 + 1 + 1;
            ఒకవేళ (s->gain_application_space_chromaticities_flag == 3)
                కొలత_బిట్లు += 16 * 8;
            ఒకవేళ (s->అంకె_alternate_images > 4)
                తిరిగి AVERROR_INVALIDDATA;
            కొరకు (పూర్ణాంకం a = 0; a < s->అంకె_alternate_images; a++) {
                కొలత_బిట్లు += 16;
                ఒకవేళ (!a || !s->has_common_component_mix_params_flag) {
                    కొలత_బిట్లు += 2;
                    ఒకవేళ (s->component_mixing_type[a] != 3) {
                        కొలత_బిట్లు += 6;
                    } లేకపోతే {
                        కొలత_బిట్లు += 6;
                        కొరకు (పూర్ణాంకం k = 0; k < 6; k++)
                          ఒకవేళ (s->has_component_mixing_coefficient_flag[a][k])
                            కొలత_బిట్లు += 16;
                    }
                }
                ఒకవేళ (!a || !s->has_common_వక్రం_params_flag) {
                    కొలత_బిట్లు += 5 + 1 + 2;
                    ఒకవేళ (s->gain_వక్రం_అంకె_control_points_minus_1[a] > 31)
                        తిరిగి AVERROR_INVALIDDATA;
                    కొలత_బిట్లు += 16 * (s->gain_వక్రం_అంకె_control_points_minus_1[a] + 1);
                }
                కొలత_బిట్లు += 16 * (s->gain_వక్రం_అంకె_control_points_minus_1[a] + 1);
                ఒకవేళ (!s->gain_వక్రం_use_pchip_వాలు_flag[a])
                    కొలత_బిట్లు += 16 * (s->gain_వక్రం_అంకె_control_points_minus_1[a] + 1);
            }
        }
    }
    ఒకవేళ (కొలత_బిట్లు % 8)
      తిరిగి AVERROR_INVALIDDATA;
    కొలత_బైట్లు = కొలత_బిట్లు >> 3;

    ఒకవేళ (!దత్తాంశం) {
        *కొలత = కొలత_బైట్లు;
        తిరిగి 0;
    } లేకపోతే ఒకవేళ (*దత్తాంశం) {
        ఒకవేళ (*కొలత < కొలత_బైట్లు)
            తిరిగి AVERROR_బఫరు_TOO_SMALL;
        buf = *దత్తాంశం;
    } లేకపోతే {
        buf = av_malloc(కొలత_బైట్లు);
        ఒకవేళ (!buf)
            తిరిగి AVERROR(ENOMEM);
    }

    init_put_బిట్లు(pb, buf, కొలత_బైట్లు);

    // Table C.1
    put_బిట్లు(pb, 3, s->application_సంస్కరణ);
    put_బిట్లు(pb, 3, s->minimum_application_సంస్కరణ);
    put_బిట్లు(pb, 2, 0); // reserved_zero

    // Table C.2
    put_బిట్లు(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_బిట్లు(pb, 1, s->has_adaptive_tone_map_flag);
    put_బిట్లు(pb, 6, 0); // reserved_zero

    ఒకవేళ (s->has_custom_hdr_reference_white_flag)
        put_బిట్లు(pb, 16, s->hdr_reference_white);

    ఒకవేళ (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_బిట్లు(pb, 16, s->baseline_hdr_headroom);
        put_బిట్లు(pb, 1, s->use_reference_white_tone_mapping_flag);
        ఒకవేళ (s->use_reference_white_tone_mapping_flag) {
            put_బిట్లు(pb, 7, 0); // reserved_zero
        } లేకపోతే {
            put_బిట్లు(pb, 3, s->అంకె_alternate_images);
            put_బిట్లు(pb, 2, s->gain_application_space_chromaticities_flag);
            put_బిట్లు(pb, 1, s->has_common_component_mix_params_flag);
            put_బిట్లు(pb, 1, s->has_common_వక్రం_params_flag);

            ఒకవేళ (s->gain_application_space_chromaticities_flag == 3)
                కొరకు (పూర్ణాంకం r = 0; r < 8; r++)
                    put_బిట్లు(pb, 16, s->gain_application_space_chromaticities[r]);

            కొరకు (పూర్ణాంకం a = 0; a < s->అంకె_alternate_images; a++) {
                put_బిట్లు(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                ఒకవేళ (!a || !s->has_common_component_mix_params_flag) {
                    put_బిట్లు(pb, 2, s->component_mixing_type[a]);
                    ఒకవేళ (s->component_mixing_type[a] != 3) {
                        put_బిట్లు(pb, 6, 0); // reserved_zero
                    } లేకపోతే {
                        కొరకు (పూర్ణాంకం k = 0; k < 6; k++)
                            put_బిట్లు(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        కొరకు (పూర్ణాంకం k = 0; k < 6; k++)
                            ఒకవేళ (s->has_component_mixing_coefficient_flag[a][k])
                                put_బిట్లు(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                ఒకవేళ (!a || !s->has_common_వక్రం_params_flag) {
                    put_బిట్లు(pb, 5, s->gain_వక్రం_అంకె_control_points_minus_1[a]);
                    put_బిట్లు(pb, 1, s->gain_వక్రం_use_pchip_వాలు_flag[a]);
                    put_బిట్లు(pb, 2, 0); // reserved_zero
                    కొరకు (పూర్ణాంకం c = 0; c <= s->gain_వక్రం_అంకె_control_points_minus_1[a]; c++)
                        put_బిట్లు(pb, 16, s->gain_వక్రం_control_points_x[a][c]);
                }
                కొరకు (పూర్ణాంకం c = 0; c <= s->gain_వక్రం_అంకె_control_points_minus_1[a]; c++)
                    put_బిట్లు(pb, 16, s->gain_వక్రం_control_points_y[a][c]);
                ఒకవేళ (!s->gain_వక్రం_use_pchip_వాలు_flag[a]) {
                    కొరకు (పూర్ణాంకం c = 0; c <= s->gain_వక్రం_అంకె_control_points_minus_1[a]; c++)
                        put_బిట్లు(pb, 16, s->gain_వక్రం_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_బిట్లు(pb);

    *దత్తాంశం = buf;
    ఒకవేళ (కొలత)
        *కొలత = కొలత_బైట్లు;
    తిరిగి 0;
}

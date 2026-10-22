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

स्थिर ध्रुव int64_t luminance_den = 1;
स्थिर ध्रुव int32_t peak_luminance_den = 15;
स्थिर ध्रुव int64_t rgb_den = 100000;
स्थिर ध्रुव int32_t fraction_pixel_den = 1000;
स्थिर ध्रुव int32_t knee_point_den = 4095;
स्थिर ध्रुव int32_t bezier_anchor_den = 1023;
स्थिर ध्रुव int32_t saturation_weight_den = 8;

AVDynamicHDRPlus *av_dynamic_hdr_plus_alloc(size_t *आकार)
{
    AVDynamicHDRPlus *hdr_plus = av_mallocz(परिमाण(AVDynamicHDRPlus));

    यदि (आकार)
        *आकार = hdr_plus ? परिमाण(*hdr_plus) : 0;

    प्रत्यागम hdr_plus;
}

AVDynamicHDRPlus *av_dynamic_hdr_plus_create_side_दत्त(AVFrame *frame)
{
    AVFrame_Side_दत्त *side_दत्त = av_frame_new_side_दत्त(frame,
                                                        AV_FRAME_दत्त_DYNAMIC_HDR_PLUS,
                                                        परिमाण(AVDynamicHDRPlus));
    यदि (!side_दत्त)
        प्रत्यागम रिक्त;

    स्मृतिं_पूरय(side_दत्त->दत्त, 0, परिमाण(AVDynamicHDRPlus));

    प्रत्यागम (AVDynamicHDRPlus *)side_दत्त->दत्त;
}

पूर्णाङ्क av_dynamic_hdr_plus_from_t35(AVDynamicHDRPlus *s, ध्रुव uint8_t *दत्त,
                                 size_t आकार)
{
    uint8_t padded_buf[AV_HDR_PLUS_MAX_PAYLOAD_आकार + AV_निवेशः_बफर_PADDING_आकार];
    GetBitContext gbc, *gb = &gbc;
    पूर्णाङ्क ret;

    यदि (!s)
        प्रत्यागम AVERROR(EINVAL);

    यदि (आकार > AV_HDR_PLUS_MAX_PAYLOAD_आकार)
        प्रत्यागम AVERROR(EINVAL);

    स्मृतिं_प्रतिलिख(padded_buf, दत्त, आकार);
    // Zero-initialize the buffer padding to avoid overreads into uninitialized data.
    स्मृतिं_पूरय(padded_buf + आकार, 0, AV_निवेशः_बफर_PADDING_आकार);

    ret = init_get_bits8(gb, padded_buf, आकार);
    यदि (ret < 0)
        प्रत्यागम ret;

    यदि (get_द्वयङ्काः_वामः(gb) < 10)
        प्रत्यागम AVERROR_INVALIDDATA;

    s->application_संस्करणम् = get_द्वयङ्काः(gb, 8);
    s->अङ्कः_windows = get_द्वयङ्काः(gb, 2);

    यदि (s->अङ्कः_windows < 1 || s->अङ्कः_windows > 3) {
        प्रत्यागम AVERROR_INVALIDDATA;
    }

    यदि (get_द्वयङ्काः_वामः(gb) < ((19 * 8 + 1) * (s->अङ्कः_windows - 1)))
        प्रत्यागम AVERROR_INVALIDDATA;

    प्रति (पूर्णाङ्क w = 1; w < s->अङ्कः_windows; w++) {
        // The corners are set to absolute coordinates here. They should be
        // converted to the relative coordinates (in [0, 1]) in the decoder.
        AVHDRPlusColorTransformParams *params = &s->params[w];
        params->गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_x =
            (AVRational){get_द्वयङ्काः(gb, 16), 1};
        params->गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_y =
            (AVRational){get_द्वयङ्काः(gb, 16), 1};
        params->गवाक्षः_अधस्तनम्_दक्षिणः_corner_x =
            (AVRational){get_द्वयङ्काः(gb, 16), 1};
        params->गवाक्षः_अधस्तनम्_दक्षिणः_corner_y =
            (AVRational){get_द्वयङ्काः(gb, 16), 1};

        params->center_सम्बन्धि_ellipse_x = get_द्वयङ्काः(gb, 16);
        params->center_सम्बन्धि_ellipse_y = get_द्वयङ्काः(gb, 16);
        params->rotation_angle = get_द्वयङ्काः(gb, 8);
        params->semimajor_axis_आन्तरिकम्_ellipse = get_द्वयङ्काः(gb, 16);
        params->semimajor_axis_external_ellipse = get_द्वयङ्काः(gb, 16);
        params->semiminor_axis_external_ellipse = get_द्वयङ्काः(gb, 16);
        params->overlap_process_option = get_bits1(gb);
    }

    यदि (get_द्वयङ्काः_वामः(gb) < 28)
        प्रत्यागम AVERROR_INVALIDDATA;

    s->targeted_system_display_अधिकतमम्_luminance =
        (AVRational){get_द्वयङ्काः_long(gb, 27), luminance_den};
    s->targeted_system_display_actual_peak_luminance_flag = get_bits1(gb);

    यदि (s->targeted_system_display_actual_peak_luminance_flag) {
        पूर्णाङ्क पङ्क्तिकाः, स्तम्भसङ्ख्या;
        यदि (get_द्वयङ्काः_वामः(gb) < 10)
            प्रत्यागम AVERROR_INVALIDDATA;
        पङ्क्तिकाः = get_द्वयङ्काः(gb, 5);
        स्तम्भसङ्ख्या = get_द्वयङ्काः(gb, 5);
        यदि (((पङ्क्तिकाः < 2) || (पङ्क्तिकाः > 25)) || ((स्तम्भसङ्ख्या < 2) || (स्तम्भसङ्ख्या > 25))) {
            प्रत्यागम AVERROR_INVALIDDATA;
        }
        s->अङ्कः_पङ्क्तिकाः_targeted_system_display_actual_peak_luminance = पङ्क्तिकाः;
        s->अङ्कः_स्तम्भसङ्ख्या_targeted_system_display_actual_peak_luminance = स्तम्भसङ्ख्या;

        यदि (get_द्वयङ्काः_वामः(gb) < (पङ्क्तिकाः * स्तम्भसङ्ख्या * 4))
            प्रत्यागम AVERROR_INVALIDDATA;

        प्रति (पूर्णाङ्क i = 0; i < पङ्क्तिकाः; i++) {
            प्रति (पूर्णाङ्क j = 0; j < स्तम्भसङ्ख्या; j++) {
                s->targeted_system_display_actual_peak_luminance[i][j] =
                    (AVRational){get_द्वयङ्काः(gb, 4), peak_luminance_den};
            }
        }
    }
    प्रति (पूर्णाङ्क w = 0; w < s->अङ्कः_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        यदि (get_द्वयङ्काः_वामः(gb) < (3 * 17 + 17 + 4))
            प्रत्यागम AVERROR_INVALIDDATA;

        प्रति (पूर्णाङ्क i = 0; i < 3; i++) {
            params->maxscl[i] =
                (AVRational){get_द्वयङ्काः(gb, 17), rgb_den};
        }
        params->मध्यमानम्_maxrgb =
            (AVRational){get_द्वयङ्काः(gb, 17), rgb_den};
        params->अङ्कः_distribution_maxrgb_percentiles = get_द्वयङ्काः(gb, 4);

        यदि (get_द्वयङ्काः_वामः(gb) <
            (params->अङ्कः_distribution_maxrgb_percentiles * 24))
            प्रत्यागम AVERROR_INVALIDDATA;

        प्रति (पूर्णाङ्क i = 0; i < params->अङ्कः_distribution_maxrgb_percentiles; i++) {
            params->distribution_maxrgb[i].percentage = get_द्वयङ्काः(gb, 7);
            params->distribution_maxrgb[i].percentile =
                (AVRational){get_द्वयङ्काः(gb, 17), rgb_den};
        }

        यदि (get_द्वयङ्काः_वामः(gb) < 10)
            प्रत्यागम AVERROR_INVALIDDATA;

        params->fraction_bright_pixels = (AVRational){get_द्वयङ्काः(gb, 10), fraction_pixel_den};
    }
    यदि (get_द्वयङ्काः_वामः(gb) < 1)
        प्रत्यागम AVERROR_INVALIDDATA;
    s->mastering_display_actual_peak_luminance_flag = get_bits1(gb);
    यदि (s->mastering_display_actual_peak_luminance_flag) {
        पूर्णाङ्क पङ्क्तिकाः, स्तम्भसङ्ख्या;
        यदि (get_द्वयङ्काः_वामः(gb) < 10)
            प्रत्यागम AVERROR_INVALIDDATA;
        पङ्क्तिकाः = get_द्वयङ्काः(gb, 5);
        स्तम्भसङ्ख्या = get_द्वयङ्काः(gb, 5);
        यदि (((पङ्क्तिकाः < 2) || (पङ्क्तिकाः > 25)) || ((स्तम्भसङ्ख्या < 2) || (स्तम्भसङ्ख्या > 25))) {
            प्रत्यागम AVERROR_INVALIDDATA;
        }
        s->अङ्कः_पङ्क्तिकाः_mastering_display_actual_peak_luminance = पङ्क्तिकाः;
        s->अङ्कः_स्तम्भसङ्ख्या_mastering_display_actual_peak_luminance = स्तम्भसङ्ख्या;

        यदि (get_द्वयङ्काः_वामः(gb) < (पङ्क्तिकाः * स्तम्भसङ्ख्या * 4))
            प्रत्यागम AVERROR_INVALIDDATA;

        प्रति (पूर्णाङ्क i = 0; i < पङ्क्तिकाः; i++) {
            प्रति (पूर्णाङ्क j = 0; j < स्तम्भसङ्ख्या; j++) {
                s->mastering_display_actual_peak_luminance[i][j] =
                    (AVRational){get_द्वयङ्काः(gb, 4), peak_luminance_den};
            }
        }
    }

    प्रति (पूर्णाङ्क w = 0; w < s->अङ्कः_windows; w++) {
        AVHDRPlusColorTransformParams *params = &s->params[w];
        यदि (get_द्वयङ्काः_वामः(gb) < 1)
            प्रत्यागम AVERROR_INVALIDDATA;

        params->tone_mapping_flag = get_bits1(gb);
        यदि (params->tone_mapping_flag) {
            यदि (get_द्वयङ्काः_वामः(gb) < 28)
                प्रत्यागम AVERROR_INVALIDDATA;

            params->knee_point_x =
                (AVRational){get_द्वयङ्काः(gb, 12), knee_point_den};
            params->knee_point_y =
                (AVRational){get_द्वयङ्काः(gb, 12), knee_point_den};
            params->अङ्कः_bezier_वक्रम्_anchors = get_द्वयङ्काः(gb, 4);

            यदि (get_द्वयङ्काः_वामः(gb) < (params->अङ्कः_bezier_वक्रम्_anchors * 10))
                प्रत्यागम AVERROR_INVALIDDATA;

            प्रति (पूर्णाङ्क i = 0; i < params->अङ्कः_bezier_वक्रम्_anchors; i++) {
                params->bezier_वक्रम्_anchors[i] =
                    (AVRational){get_द्वयङ्काः(gb, 10), bezier_anchor_den};
            }
        }

        यदि (get_द्वयङ्काः_वामः(gb) < 1)
            प्रत्यागम AVERROR_INVALIDDATA;
        params->color_saturation_mapping_flag = get_bits1(gb);
        यदि (params->color_saturation_mapping_flag) {
            यदि (get_द्वयङ्काः_वामः(gb) < 6)
                प्रत्यागम AVERROR_INVALIDDATA;
            params->color_saturation_weight =
                (AVRational){get_द्वयङ्काः(gb, 6), saturation_weight_den};
        }
    }

    प्रत्यागम 0;
}

पूर्णाङ्क av_dynamic_hdr_plus_गन्तव्यम्_t35(ध्रुव AVDynamicHDRPlus *s, uint8_t **दत्त, size_t *आकार)
{
    uint8_t *buf;
    size_t आकार_द्वयङ्काः, आकार_अष्टकानि;
    PutBitContext pbc, *pb = &pbc;

    यदि (!s)
        प्रत्यागम AVERROR(EINVAL);
    यदि ((!दत्त || *दत्त) && !आकार)
       प्रत्यागम AVERROR(EINVAL);

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
    आकार_द्वयङ्काः = 8;

    आकार_द्वयङ्काः += 2;

    प्रति (पूर्णाङ्क w = 1; w < s->अङ्कः_windows; w++)
        आकार_द्वयङ्काः += 153;

    आकार_द्वयङ्काः += 27;

    आकार_द्वयङ्काः += 1;
    यदि (s->targeted_system_display_actual_peak_luminance_flag)
        आकार_द्वयङ्काः += 10 +
                     s->अङ्कः_पङ्क्तिकाः_targeted_system_display_actual_peak_luminance *
                     s->अङ्कः_स्तम्भसङ्ख्या_targeted_system_display_actual_peak_luminance * 4;

    प्रति (पूर्णाङ्क w = 0; w < s->अङ्कः_windows; w++)
        आकार_द्वयङ्काः += 72 + s->params[w].अङ्कः_distribution_maxrgb_percentiles * 24 + 10;

    आकार_द्वयङ्काः += 1;
    यदि (s->mastering_display_actual_peak_luminance_flag)
        आकार_द्वयङ्काः += 10 +
                     s->अङ्कः_पङ्क्तिकाः_mastering_display_actual_peak_luminance *
                     s->अङ्कः_स्तम्भसङ्ख्या_mastering_display_actual_peak_luminance * 4;

    प्रति (पूर्णाङ्क w = 0; w < s->अङ्कः_windows; w++) {
        आकार_द्वयङ्काः += 1;
        यदि (s->params[w].tone_mapping_flag)
            आकार_द्वयङ्काः += 28 + s->params[w].अङ्कः_bezier_वक्रम्_anchors * 10;

        आकार_द्वयङ्काः += 1;
        यदि (s->params[w].color_saturation_mapping_flag)
            आकार_द्वयङ्काः += 6;
    }

    आकार_अष्टकानि = (आकार_द्वयङ्काः + 7) / 8;

    av_assert0(आकार_अष्टकानि <= AV_HDR_PLUS_MAX_PAYLOAD_आकार);

    यदि (!दत्त) {
        *आकार = आकार_अष्टकानि;
        प्रत्यागम 0;
    } अन्यथा यदि (*दत्त) {
        यदि (*आकार < आकार_अष्टकानि)
            प्रत्यागम AVERROR_बफर_TOO_SMALL;
        buf = *दत्त;
    } अन्यथा {
        buf = av_malloc(आकार_अष्टकानि);
        यदि (!buf)
            प्रत्यागम AVERROR(ENOMEM);
    }

    init_put_द्वयङ्काः(pb, buf, आकार_अष्टकानि);

    // application_mode is set to Application Version 1
    put_द्वयङ्काः(pb, 8, 1);

    // Payload as per CTA-861-H p.253-254
    put_द्वयङ्काः(pb, 2, s->अङ्कः_windows);

    प्रति (पूर्णाङ्क w = 1; w < s->अङ्कः_windows; w++) {
        put_द्वयङ्काः(pb, 16, s->params[w].गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_x.अङ्कः / s->params[w].गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_x.den);
        put_द्वयङ्काः(pb, 16, s->params[w].गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_y.अङ्कः / s->params[w].गवाक्षः_ऊर्ध्वस्थम्_वामः_corner_y.den);
        put_द्वयङ्काः(pb, 16, s->params[w].गवाक्षः_अधस्तनम्_दक्षिणः_corner_x.अङ्कः / s->params[w].गवाक्षः_अधस्तनम्_दक्षिणः_corner_x.den);
        put_द्वयङ्काः(pb, 16, s->params[w].गवाक्षः_अधस्तनम्_दक्षिणः_corner_y.अङ्कः / s->params[w].गवाक्षः_अधस्तनम्_दक्षिणः_corner_y.den);
        put_द्वयङ्काः(pb, 16, s->params[w].center_सम्बन्धि_ellipse_x);
        put_द्वयङ्काः(pb, 16, s->params[w].center_सम्बन्धि_ellipse_y);
        put_द्वयङ्काः(pb, 8, s->params[w].rotation_angle);
        put_द्वयङ्काः(pb, 16, s->params[w].semimajor_axis_आन्तरिकम्_ellipse);
        put_द्वयङ्काः(pb, 16, s->params[w].semimajor_axis_external_ellipse);
        put_द्वयङ्काः(pb, 16, s->params[w].semiminor_axis_external_ellipse);
        put_द्वयङ्काः(pb, 1, s->params[w].overlap_process_option);
    }

    put_द्वयङ्काः(pb, 27, s->targeted_system_display_अधिकतमम्_luminance.अङ्कः * luminance_den /
        s->targeted_system_display_अधिकतमम्_luminance.den);
    put_द्वयङ्काः(pb, 1, s->targeted_system_display_actual_peak_luminance_flag);
    यदि (s->targeted_system_display_actual_peak_luminance_flag) {
        put_द्वयङ्काः(pb, 5, s->अङ्कः_पङ्क्तिकाः_targeted_system_display_actual_peak_luminance);
        put_द्वयङ्काः(pb, 5, s->अङ्कः_स्तम्भसङ्ख्या_targeted_system_display_actual_peak_luminance);
        प्रति (पूर्णाङ्क i = 0; i < s->अङ्कः_पङ्क्तिकाः_targeted_system_display_actual_peak_luminance; i++) {
            प्रति (पूर्णाङ्क j = 0; j < s->अङ्कः_स्तम्भसङ्ख्या_targeted_system_display_actual_peak_luminance; j++)
                put_द्वयङ्काः(pb, 4, s->targeted_system_display_actual_peak_luminance[i][j].अङ्कः * peak_luminance_den /
                    s->targeted_system_display_actual_peak_luminance[i][j].den);
        }
    }

    प्रति (पूर्णाङ्क w = 0; w < s->अङ्कः_windows; w++) {
        प्रति (पूर्णाङ्क i = 0; i < 3; i++)
            put_द्वयङ्काः(pb, 17, s->params[w].maxscl[i].अङ्कः * rgb_den / s->params[w].maxscl[i].den);
        put_द्वयङ्काः(pb, 17, s->params[w].मध्यमानम्_maxrgb.अङ्कः * rgb_den / s->params[w].मध्यमानम्_maxrgb.den);
        put_द्वयङ्काः(pb, 4, s->params[w].अङ्कः_distribution_maxrgb_percentiles);
        प्रति (पूर्णाङ्क i = 0; i < s->params[w].अङ्कः_distribution_maxrgb_percentiles; i++) {
            put_द्वयङ्काः(pb, 7, s->params[w].distribution_maxrgb[i].percentage);
            put_द्वयङ्काः(pb, 17, s->params[w].distribution_maxrgb[i].percentile.अङ्कः * rgb_den /
                s->params[w].distribution_maxrgb[i].percentile.den);
        }
        put_द्वयङ्काः(pb, 10, s->params[w].fraction_bright_pixels.अङ्कः * fraction_pixel_den /
            s->params[w].fraction_bright_pixels.den);
    }

    put_द्वयङ्काः(pb, 1, s->mastering_display_actual_peak_luminance_flag);
    यदि (s->mastering_display_actual_peak_luminance_flag) {
        put_द्वयङ्काः(pb, 5, s->अङ्कः_पङ्क्तिकाः_mastering_display_actual_peak_luminance);
        put_द्वयङ्काः(pb, 5, s->अङ्कः_स्तम्भसङ्ख्या_mastering_display_actual_peak_luminance);
        प्रति (पूर्णाङ्क i = 0; i < s->अङ्कः_पङ्क्तिकाः_mastering_display_actual_peak_luminance; i++) {
            प्रति (पूर्णाङ्क j = 0; j < s->अङ्कः_स्तम्भसङ्ख्या_mastering_display_actual_peak_luminance; j++)
                put_द्वयङ्काः(pb, 4, s->mastering_display_actual_peak_luminance[i][j].अङ्कः * peak_luminance_den /
                    s->mastering_display_actual_peak_luminance[i][j].den);
        }
    }

    प्रति (पूर्णाङ्क w = 0; w < s->अङ्कः_windows; w++) {
        put_द्वयङ्काः(pb, 1, s->params[w].tone_mapping_flag);
        यदि (s->params[w].tone_mapping_flag) {
            put_द्वयङ्काः(pb, 12, s->params[w].knee_point_x.अङ्कः * knee_point_den / s->params[w].knee_point_x.den);
            put_द्वयङ्काः(pb, 12, s->params[w].knee_point_y.अङ्कः * knee_point_den / s->params[w].knee_point_y.den);
            put_द्वयङ्काः(pb, 4, s->params[w].अङ्कः_bezier_वक्रम्_anchors);
            प्रति (पूर्णाङ्क i = 0; i < s->params[w].अङ्कः_bezier_वक्रम्_anchors; i++)
                put_द्वयङ्काः(pb, 10, s->params[w].bezier_वक्रम्_anchors[i].अङ्कः * bezier_anchor_den /
                    s->params[w].bezier_वक्रम्_anchors[i].den);
        }
        put_द्वयङ्काः(pb, 1, s->params[w].color_saturation_mapping_flag);
        यदि (s->params[w].color_saturation_mapping_flag)
            put_द्वयङ्काः(pb, 6, s->params[w].color_saturation_weight.अङ्कः * saturation_weight_den /
                s->params[w].color_saturation_weight.den);
    }

    flush_put_द्वयङ्काः(pb);

    *दत्त = buf;
    यदि (आकार)
        *आकार = आकार_अष्टकानि;
    प्रत्यागम 0;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_alloc(size_t *आकार)
{
    AVDynamicHDRSmpte2094App5 *smpte2094_app5 = av_mallocz(परिमाण(AVDynamicHDRSmpte2094App5));

    यदि (आकार)
        *आकार = smpte2094_app5 ? परिमाण(*smpte2094_app5) : 0;

    प्रत्यागम smpte2094_app5;
}

AVDynamicHDRSmpte2094App5 *av_dynamic_hdr_smpte2094_app5_create_side_दत्त(AVFrame *frame)
{
    AVFrame_Side_दत्त *side_दत्त = av_frame_new_side_दत्त(frame,
                                                        AV_FRAME_दत्त_DYNAMIC_HDR_SMPTE_2094_APP5,
                                                        परिमाण(AVDynamicHDRSmpte2094App5));
    यदि (!side_दत्त)
        प्रत्यागम रिक्त;

    स्मृतिं_पूरय(side_दत्त->दत्त, 0, परिमाण(AVDynamicHDRSmpte2094App5));

    प्रत्यागम (AVDynamicHDRSmpte2094App5 *)side_दत्त->दत्त;
}

#परिभाषय GET_द्वयङ्काः_OR_FAIL(var, n)        \
    कुरु {                                \
        यदि (get_द्वयङ्काः_वामः(gb) < n) {    \
            ret = AVERROR_INVALIDDATA;  \
            गच्छ अन्तः_2;                   \
        }                               \
        var = get_द्वयङ्काः(gb, n);          \
    } यावत् (0)

पूर्णाङ्क av_dynamic_hdr_smpte2094_app5_from_t35(AVDynamicHDRSmpte2094App5 *s, ध्रुव uint8_t *दत्त,
                                           size_t आकार)
{
    GetBitContext gbc, *gb = &gbc;
    पूर्णाङ्क ret, reserved_zero;
    size_t padded_आकार = आकार + AV_निवेशः_बफर_PADDING_आकार;

    यदि (!s)
        प्रत्यागम AVERROR(EINVAL);

    uint8_t *padded_दत्त = av_mallocz(padded_आकार);
    यदि (!padded_दत्त)
        प्रत्यागम AVERROR(ENOMEM);

    स्मृतिं_प्रतिलिख(padded_दत्त, दत्त, आकार);
    ret = init_get_bits8(gb, padded_दत्त, आकार);
    यदि (ret < 0)
        गच्छ अन्तः_2;

    // Table C.1
    GET_द्वयङ्काः_OR_FAIL(s->application_संस्करणम्, 3);
    GET_द्वयङ्काः_OR_FAIL(s->minimum_application_संस्करणम्, 3);
    GET_द्वयङ्काः_OR_FAIL(reserved_zero, 2);
    यदि (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        गच्छ अन्तः_2;
    }

    // Table C.2
    GET_द्वयङ्काः_OR_FAIL(s->has_custom_hdr_reference_white_flag, 1);
    GET_द्वयङ्काः_OR_FAIL(s->has_adaptive_tone_map_flag, 1);
    GET_द्वयङ्काः_OR_FAIL(reserved_zero, 6);
    यदि (reserved_zero) {
        ret = AVERROR_INVALIDDATA;
        गच्छ अन्तः_2;
    }
    यदि (s->has_custom_hdr_reference_white_flag)
        GET_द्वयङ्काः_OR_FAIL(s->hdr_reference_white, 16);
    यदि (!s->has_adaptive_tone_map_flag) {
        ret = 0;
        गच्छ अन्तः_2;
    }

    // Table C.3
    GET_द्वयङ्काः_OR_FAIL(s->baseline_hdr_headroom, 16);
    GET_द्वयङ्काः_OR_FAIL(s->use_reference_white_tone_mapping_flag, 1);
    यदि (s->use_reference_white_tone_mapping_flag) {
        GET_द्वयङ्काः_OR_FAIL(reserved_zero, 7);
        ret = reserved_zero ? AVERROR_INVALIDDATA : 0;
        गच्छ अन्तः_2;
    }
    GET_द्वयङ्काः_OR_FAIL(s->अङ्कः_alternate_images, 3);
    यदि (s->अङ्कः_alternate_images > 4) {
        ret = AVERROR_INVALIDDATA;
        गच्छ अन्तः_2;
    }
    GET_द्वयङ्काः_OR_FAIL(s->gain_application_space_chromaticities_flag, 2);
    GET_द्वयङ्काः_OR_FAIL(s->has_common_component_mix_params_flag, 1);
    GET_द्वयङ्काः_OR_FAIL(s->has_common_वक्रम्_params_flag, 1);
    यदि (s->gain_application_space_chromaticities_flag == 3)
        प्रति (पूर्णाङ्क r = 0; r < 8; r++)
            GET_द्वयङ्काः_OR_FAIL(s->gain_application_space_chromaticities[r], 16);

    प्रति (पूर्णाङ्क a = 0; a < s->अङ्कः_alternate_images; a++) {
        GET_द्वयङ्काः_OR_FAIL(s->alternate_hdr_headrooms[a], 16);

        // Table C.4
        यदि (!a || !s->has_common_component_mix_params_flag) {
            GET_द्वयङ्काः_OR_FAIL(s->component_mixing_type[a], 2);
            यदि (s->component_mixing_type[a] != 3) {
                GET_द्वयङ्काः_OR_FAIL(reserved_zero, 6);
                यदि (reserved_zero) {
                    ret = AVERROR_INVALIDDATA;
                    गच्छ अन्तः_2;
                }
            } अन्यथा {
                प्रति (पूर्णाङ्क k = 0; k < 6; k++)
                    GET_द्वयङ्काः_OR_FAIL(s->has_component_mixing_coefficient_flag[a][k], 1);
                प्रति (पूर्णाङ्क k = 0; k < 6; k++) {
                    यदि (s->has_component_mixing_coefficient_flag[a][k]) {
                        GET_द्वयङ्काः_OR_FAIL(s->component_mixing_coefficient[a][k], 16);
                    } अन्यथा {
                        s->component_mixing_coefficient[a][k] = 0;
                    }
                }
            }
        } अन्यथा {
            s->component_mixing_type[a] = s->component_mixing_type[0];
            यदि (s->component_mixing_type[a] == 3) {
                प्रति (पूर्णाङ्क k = 0; k < 6; k++) {
                    s->has_component_mixing_coefficient_flag[a][k] =
                            s->has_component_mixing_coefficient_flag[0][k];
                    s->component_mixing_coefficient[a][k] = s->component_mixing_coefficient[0][k];
                }
            }
        }

        // Table C.5
        यदि (!a || !s->has_common_वक्रम्_params_flag) {
            GET_द्वयङ्काः_OR_FAIL(s->gain_वक्रम्_अङ्कः_control_points_minus_1[a], 5);
            यदि (s->gain_वक्रम्_अङ्कः_control_points_minus_1[a] > 31) {
                ret = AVERROR_INVALIDDATA;
                गच्छ अन्तः_2;
            }
            GET_द्वयङ्काः_OR_FAIL(s->gain_वक्रम्_use_pchip_नतिः_flag[a], 1);
            GET_द्वयङ्काः_OR_FAIL(reserved_zero, 2);
            यदि (reserved_zero) {
                ret = AVERROR_INVALIDDATA;
                गच्छ अन्तः_2;
            }
            प्रति (पूर्णाङ्क c = 0; c <= s->gain_वक्रम्_अङ्कः_control_points_minus_1[a]; c++) {
                GET_द्वयङ्काः_OR_FAIL(s->gain_वक्रम्_control_points_x[a][c], 16);
            }
        } अन्यथा {
            s->gain_वक्रम्_अङ्कः_control_points_minus_1[a] =
                    s->gain_वक्रम्_अङ्कः_control_points_minus_1[0];
            s->gain_वक्रम्_use_pchip_नतिः_flag[a] = s->gain_वक्रम्_use_pchip_नतिः_flag[0];
            प्रति (पूर्णाङ्क c = 0; c <= s->gain_वक्रम्_अङ्कः_control_points_minus_1[a]; c++) {
                s->gain_वक्रम्_control_points_x[a][c] = s->gain_वक्रम्_control_points_x[0][c];
            }
        }
        प्रति (पूर्णाङ्क c = 0; c <= s->gain_वक्रम्_अङ्कः_control_points_minus_1[a]; c++)
            GET_द्वयङ्काः_OR_FAIL(s->gain_वक्रम्_control_points_y[a][c], 16);
        यदि (!s->gain_वक्रम्_use_pchip_नतिः_flag[a]) {
            प्रति (पूर्णाङ्क c = 0; c <= s->gain_वक्रम्_अङ्कः_control_points_minus_1[a]; c++)
                GET_द्वयङ्काः_OR_FAIL(s->gain_वक्रम्_control_points_theta[a][c], 16);
        }
    }
    ret = 0;
अन्तः_2:
    av_free(padded_दत्त);
    प्रत्यागम ret;
}

पूर्णाङ्क av_dynamic_hdr_smpte2094_app5_गन्तव्यम्_t35(ध्रुव AVDynamicHDRSmpte2094App5 *s, uint8_t **दत्त,
                                         size_t *आकार)
{
    uint8_t *buf;
    size_t आकार_अष्टकानि, आकार_द्वयङ्काः;
    PutBitContext pbc, *pb = &pbc;

    यदि (!s)
        प्रत्यागम AVERROR(EINVAL);
    यदि ((!दत्त || *दत्त) && !आकार)
       प्रत्यागम AVERROR(EINVAL);

    यदि (s->application_संस्करणम् >= 8 || s->minimum_application_संस्करणम् >= 3)
        प्रत्यागम AVERROR_INVALIDDATA;
    आकार_द्वयङ्काः = 0;
    आकार_द्वयङ्काः += 3 + 3 + 2;
    आकार_द्वयङ्काः += 1 + 1 + 6;
    यदि (s->has_custom_hdr_reference_white_flag)
        आकार_द्वयङ्काः += 16;
    यदि (s->has_adaptive_tone_map_flag) {
        आकार_द्वयङ्काः += 16 + 1;
        यदि (s->use_reference_white_tone_mapping_flag) {
            आकार_द्वयङ्काः += 7;
        } अन्यथा {
            आकार_द्वयङ्काः += 3 + 2 + 1 + 1;
            यदि (s->gain_application_space_chromaticities_flag == 3)
                आकार_द्वयङ्काः += 16 * 8;
            यदि (s->अङ्कः_alternate_images > 4)
                प्रत्यागम AVERROR_INVALIDDATA;
            प्रति (पूर्णाङ्क a = 0; a < s->अङ्कः_alternate_images; a++) {
                आकार_द्वयङ्काः += 16;
                यदि (!a || !s->has_common_component_mix_params_flag) {
                    आकार_द्वयङ्काः += 2;
                    यदि (s->component_mixing_type[a] != 3) {
                        आकार_द्वयङ्काः += 6;
                    } अन्यथा {
                        आकार_द्वयङ्काः += 6;
                        प्रति (पूर्णाङ्क k = 0; k < 6; k++)
                          यदि (s->has_component_mixing_coefficient_flag[a][k])
                            आकार_द्वयङ्काः += 16;
                    }
                }
                यदि (!a || !s->has_common_वक्रम्_params_flag) {
                    आकार_द्वयङ्काः += 5 + 1 + 2;
                    यदि (s->gain_वक्रम्_अङ्कः_control_points_minus_1[a] > 31)
                        प्रत्यागम AVERROR_INVALIDDATA;
                    आकार_द्वयङ्काः += 16 * (s->gain_वक्रम्_अङ्कः_control_points_minus_1[a] + 1);
                }
                आकार_द्वयङ्काः += 16 * (s->gain_वक्रम्_अङ्कः_control_points_minus_1[a] + 1);
                यदि (!s->gain_वक्रम्_use_pchip_नतिः_flag[a])
                    आकार_द्वयङ्काः += 16 * (s->gain_वक्रम्_अङ्कः_control_points_minus_1[a] + 1);
            }
        }
    }
    यदि (आकार_द्वयङ्काः % 8)
      प्रत्यागम AVERROR_INVALIDDATA;
    आकार_अष्टकानि = आकार_द्वयङ्काः >> 3;

    यदि (!दत्त) {
        *आकार = आकार_अष्टकानि;
        प्रत्यागम 0;
    } अन्यथा यदि (*दत्त) {
        यदि (*आकार < आकार_अष्टकानि)
            प्रत्यागम AVERROR_बफर_TOO_SMALL;
        buf = *दत्त;
    } अन्यथा {
        buf = av_malloc(आकार_अष्टकानि);
        यदि (!buf)
            प्रत्यागम AVERROR(ENOMEM);
    }

    init_put_द्वयङ्काः(pb, buf, आकार_अष्टकानि);

    // Table C.1
    put_द्वयङ्काः(pb, 3, s->application_संस्करणम्);
    put_द्वयङ्काः(pb, 3, s->minimum_application_संस्करणम्);
    put_द्वयङ्काः(pb, 2, 0); // reserved_zero

    // Table C.2
    put_द्वयङ्काः(pb, 1, s->has_custom_hdr_reference_white_flag);
    put_द्वयङ्काः(pb, 1, s->has_adaptive_tone_map_flag);
    put_द्वयङ्काः(pb, 6, 0); // reserved_zero

    यदि (s->has_custom_hdr_reference_white_flag)
        put_द्वयङ्काः(pb, 16, s->hdr_reference_white);

    यदि (s->has_adaptive_tone_map_flag) {
        // Table C.3
        put_द्वयङ्काः(pb, 16, s->baseline_hdr_headroom);
        put_द्वयङ्काः(pb, 1, s->use_reference_white_tone_mapping_flag);
        यदि (s->use_reference_white_tone_mapping_flag) {
            put_द्वयङ्काः(pb, 7, 0); // reserved_zero
        } अन्यथा {
            put_द्वयङ्काः(pb, 3, s->अङ्कः_alternate_images);
            put_द्वयङ्काः(pb, 2, s->gain_application_space_chromaticities_flag);
            put_द्वयङ्काः(pb, 1, s->has_common_component_mix_params_flag);
            put_द्वयङ्काः(pb, 1, s->has_common_वक्रम्_params_flag);

            यदि (s->gain_application_space_chromaticities_flag == 3)
                प्रति (पूर्णाङ्क r = 0; r < 8; r++)
                    put_द्वयङ्काः(pb, 16, s->gain_application_space_chromaticities[r]);

            प्रति (पूर्णाङ्क a = 0; a < s->अङ्कः_alternate_images; a++) {
                put_द्वयङ्काः(pb, 16, s->alternate_hdr_headrooms[a]);

                // Table C.4
                यदि (!a || !s->has_common_component_mix_params_flag) {
                    put_द्वयङ्काः(pb, 2, s->component_mixing_type[a]);
                    यदि (s->component_mixing_type[a] != 3) {
                        put_द्वयङ्काः(pb, 6, 0); // reserved_zero
                    } अन्यथा {
                        प्रति (पूर्णाङ्क k = 0; k < 6; k++)
                            put_द्वयङ्काः(pb, 1, s->has_component_mixing_coefficient_flag[a][k]);
                        प्रति (पूर्णाङ्क k = 0; k < 6; k++)
                            यदि (s->has_component_mixing_coefficient_flag[a][k])
                                put_द्वयङ्काः(pb, 16, s->component_mixing_coefficient[a][k]);
                    }
                }

                // Table C.5
                यदि (!a || !s->has_common_वक्रम्_params_flag) {
                    put_द्वयङ्काः(pb, 5, s->gain_वक्रम्_अङ्कः_control_points_minus_1[a]);
                    put_द्वयङ्काः(pb, 1, s->gain_वक्रम्_use_pchip_नतिः_flag[a]);
                    put_द्वयङ्काः(pb, 2, 0); // reserved_zero
                    प्रति (पूर्णाङ्क c = 0; c <= s->gain_वक्रम्_अङ्कः_control_points_minus_1[a]; c++)
                        put_द्वयङ्काः(pb, 16, s->gain_वक्रम्_control_points_x[a][c]);
                }
                प्रति (पूर्णाङ्क c = 0; c <= s->gain_वक्रम्_अङ्कः_control_points_minus_1[a]; c++)
                    put_द्वयङ्काः(pb, 16, s->gain_वक्रम्_control_points_y[a][c]);
                यदि (!s->gain_वक्रम्_use_pchip_नतिः_flag[a]) {
                    प्रति (पूर्णाङ्क c = 0; c <= s->gain_वक्रम्_अङ्कः_control_points_minus_1[a]; c++)
                        put_द्वयङ्काः(pb, 16, s->gain_वक्रम्_control_points_theta[a][c]);
                }
            }
        }
    }

    flush_put_द्वयङ्काः(pb);

    *दत्त = buf;
    यदि (आकार)
        *आकार = आकार_अष्टकानि;
    प्रत्यागम 0;
}

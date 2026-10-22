/*
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

#अन्तर्भाव "gain_map.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "libavcodec/bytestream.h"

स्थिर शून्य gain_map_params_default(AVGainMapParams *p)
{
    *p = (AVGainMapParams) {
        .आधारः_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    प्रति (पूर्णाङ्क c = 0; c < 3; c++) {
        p->channels[c] = (संरचना AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .आधारः_विस्थापनम्        = { 1, 64 },
            .alternate_विस्थापनम्   = { 1, 64 },
        };
    }
}

#परिभाषय CHECK(cond) कुरु { यदि (!(cond)) प्रत्यागम AVERROR_INVALIDDATA; } यावत् (0)
#परिभाषय CHECK_SIGNED(q)   CHECK((q).den > 0);
#परिभाषय CHECK_UNSIGNED(q) CHECK((q).अङ्कः >= 0 && (q).den > 0);

पूर्णाङ्क av_gain_map_params_validate(ध्रुव AVGainMapParams *p)
{
    CHECK(0 <= p->संस्करणम् && p->संस्करणम् <= AV_ISO21496_संस्करणम्);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->आधारः_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    प्रति (पूर्णाङ्क c = 0; c < p->nb_channels; c++) {
        ध्रुव संरचना AVGainMapChannel *ध्रुव ch = &p->channels[c];
        CHECK_SIGNED(ch->gain_map_min);
        CHECK_SIGNED(ch->gain_map_max);
        CHECK_UNSIGNED(ch->gamma);
        CHECK(ch->gamma.अङ्कः != 0);
        /**
         * Note: The ISO spec declares these as signed, but a negative value
         * makes no numeric sense and would result in infinities in the
         * middle of the valid signal range; so just constrain them to be
         * unsigned as a safeguard. Note that the Adobe hdrgm spec explicitly
         * requires them to be nonnegative as well, so this avoids an
         * inconsistency.
         */
        CHECK_UNSIGNED(ch->आधारः_विस्थापनम्);
        CHECK_UNSIGNED(ch->alternate_विस्थापनम्);
        CHECK(av_cmp_q(ch->gain_map_min, ch->gain_map_max) <= 0);
    }

    प्रत्यागम 0;
}

#परिभाषय ISO21496_शीर्षकम्_आकार 5

#परिभाषय ISO21496_FLAG_MULTICHANNEL (1 << 7)
#परिभाषय ISO21496_FLAG_USE_आधारः_CG  (1 << 6)
#परिभाषय ISO21496_FLAG_RESERVED     0x3f

स्थिर size_t iso21496_payload_आकार(पूर्णाङ्क nb_channels)
{
    प्रत्यागम 4 * 4 + (size_t) nb_channels * 10 * 4;
}

स्थिर पूर्णाङ्क make_q(int64_t अङ्कः, uint32_t den, AVRational *बहिर्गमनम्)
{
    यदि (!den)
        प्रत्यागम AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&बहिर्गमनम्->अङ्कः, &बहिर्गमनम्->den, अङ्कः, den, INT32_MAX);
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क get_sq(GetByteContext *gb, AVRational *बहिर्गमनम्)
{
    int32_t  अङ्कः = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    प्रत्यागम make_q(अङ्कः, den, बहिर्गमनम्);
}

स्थिर पूर्णाङ्क get_uq(GetByteContext *gb, AVRational *बहिर्गमनम्)
{
    uint32_t अङ्कः = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    प्रत्यागम make_q(अङ्कः, den, बहिर्गमनम्);
}

पूर्णाङ्क av_gain_map_params_from_iso21496(AVGainMapParams *सीमित p,
                                     ध्रुव uint8_t *दत्त, size_t आकार)
{
    पूर्णाङ्क ret;
    यदि (!p || !दत्त)
        प्रत्यागम AVERROR(EINVAL);

    यदि (आकार < ISO21496_शीर्षकम्_आकार || आकार > अधिकतम_पूर्णाङ्कः)
        प्रत्यागम AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, दत्त, आकार);

    /* Parse header */
    ध्रुव uint16_t minimum_संस्करणम् = bytestream2_get_be16(&gb);
    ध्रुव uint16_t writer_संस्करणम्  = bytestream2_get_be16(&gb);
    यदि (minimum_संस्करणम् > AV_ISO21496_संस्करणम् || writer_संस्करणम् < minimum_संस्करणम्)
        प्रत्यागम AVERROR_PATCHWELCOME;
    ध्रुव uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    यदि (writer_संस्करणम् == 0 && (flags & ISO21496_FLAG_RESERVED))
        प्रत्यागम AVERROR_INVALIDDATA;

    p->संस्करणम्              = AV_ISO21496_संस्करणम्;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_आधारः_color_space = !!(flags & ISO21496_FLAG_USE_आधारः_CG);

    /* Parse payload */
    यदि (bytestream2_get_अष्टकानि_वामः(&gb) < iso21496_payload_आकार(p->nb_channels))
        प्रत्यागम AVERROR_INVALIDDATA;

    यदि ((ret = get_uq(&gb, &p->आधारः_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        प्रत्यागम ret;

    प्रति (पूर्णाङ्क c = 0; c < p->nb_channels; c++) {
        संरचना AVGainMapChannel *ध्रुव ch = &p->channels[c];
        यदि ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->आधारः_विस्थापनम्))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_विस्थापनम्)) < 0)
            प्रत्यागम ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    प्रति (पूर्णाङ्क c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    प्रत्यागम av_gain_map_params_validate(p);
}

स्थिर शून्य put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (अचिह्नित) q.अङ्कः);
    bytestream2_put_be32(pb, (अचिह्नित) q.den);
}

पूर्णाङ्क av_gain_map_params_गन्तव्यम्_iso21496(ध्रुव AVGainMapParams *p, uint8_t *buf)
{
    यदि (!p || !buf)
        प्रत्यागम AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    पूर्णाङ्क ret = av_gain_map_params_validate(p);
    यदि (ret < 0)
        प्रत्यागम ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_आकार);

    पूर्णाङ्क channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    यदि (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    यदि (p->use_आधारः_color_space)
        flags |= ISO21496_FLAG_USE_आधारः_CG;

    bytestream2_put_be16(&pb, p->संस्करणम्); /* minimum_version */
    bytestream2_put_be16(&pb, p->संस्करणम्); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->आधारः_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    प्रति (पूर्णाङ्क c = 0; c < channels; c++) {
        ध्रुव संरचना AVGainMapChannel *ध्रुव ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->आधारः_विस्थापनम्);
        put_q(&pb, ch->alternate_विस्थापनम्);
    }

    प्रत्यागम bytestream2_tell_p(&pb);
}

पूर्णाङ्क av_gain_map_channels_identical(ध्रुव AVGainMapParams *p)
{
    static_assert(परिमाण(p->channels[0]) == परिमाण(पूर्णाङ्क[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    प्रत्यागम !memcmp(&p->channels[0], &p->channels[1], परिमाण(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], परिमाण(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *आकार)
{
    AVGainMapParams *p = av_malloc(परिमाण(AVGainMapParams));
    यदि (!p)
        प्रत्यागम रिक्त;

    gain_map_params_default(p);

    यदि (आकार)
        *आकार = परिमाण(*p);

    प्रत्यागम p;
}

AVGainMapParams *av_gain_map_params_create_side_दत्त(AVFrame_Side_दत्त ***fsd, पूर्णाङ्क *nb_sd)
{
    AVFrame_Side_दत्त *sd;
    sd = av_frame_side_दत्त_new(fsd, nb_sd, AV_FRAME_दत्त_GAIN_MAP_PARAMS,
                                परिमाण(AVGainMapParams),
                                AV_FRAME_SIDE_दत्त_FLAG_REPLACE);
    यदि (!sd)
        प्रत्यागम रिक्त;

    AVGainMapParams *ध्रुव p = (AVGainMapParams *) sd->दत्त;
    gain_map_params_default(p);
    प्रत्यागम p;
}

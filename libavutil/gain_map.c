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

#অন্তর্ভাব "gain_map.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "libavcodec/bytestream.h"

স্থির শূন্য gain_map_params_default(AVGainMapParams *p)
{
    *p = (AVGainMapParams) {
        .base_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    জন্য (পূর্ণসংখ্যা c = 0; c < 3; c++) {
        p->channels[c] = (কাঠামো AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .base_offset        = { 1, 64 },
            .alternate_offset   = { 1, 64 },
        };
    }
}

#define CHECK(cond) করো { যদি (!(cond)) ফেরত AVERROR_INVALIDDATA; } যখন (0)
#define CHECK_SIGNED(q)   CHECK((q).den > 0);
#define CHECK_UNSIGNED(q) CHECK((q).অঙ্ক >= 0 && (q).den > 0);

পূর্ণসংখ্যা av_gain_map_params_validate(ধ্রুবক AVGainMapParams *p)
{
    CHECK(0 <= p->version && p->version <= AV_ISO21496_VERSION);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->base_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    জন্য (পূর্ণসংখ্যা c = 0; c < p->nb_channels; c++) {
        ধ্রুবক কাঠামো AVGainMapChannel *ধ্রুবক ch = &p->channels[c];
        CHECK_SIGNED(ch->gain_map_min);
        CHECK_SIGNED(ch->gain_map_max);
        CHECK_UNSIGNED(ch->gamma);
        CHECK(ch->gamma.অঙ্ক != 0);
        /**
         * Note: The ISO spec declares these as signed, but a negative value
         * makes no numeric sense and would result in infinities in the
         * middle of the valid signal range; so just constrain them to be
         * unsigned as a safeguard. Note that the Adobe hdrgm spec explicitly
         * requires them to be nonnegative as well, so this avoids an
         * inconsistency.
         */
        CHECK_UNSIGNED(ch->base_offset);
        CHECK_UNSIGNED(ch->alternate_offset);
        CHECK(av_cmp_q(ch->gain_map_min, ch->gain_map_max) <= 0);
    }

    ফেরত 0;
}

#define ISO21496_HEADER_আকার 5

#define ISO21496_FLAG_MULTICHANNEL (1 << 7)
#define ISO21496_FLAG_USE_BASE_CG  (1 << 6)
#define ISO21496_FLAG_RESERVED     0x3f

স্থির size_t iso21496_payload_আকার(পূর্ণসংখ্যা nb_channels)
{
    ফেরত 4 * 4 + (size_t) nb_channels * 10 * 4;
}

স্থির পূর্ণসংখ্যা make_q(int64_t অঙ্ক, uint32_t den, AVRational *out)
{
    যদি (!den)
        ফেরত AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&out->অঙ্ক, &out->den, অঙ্ক, den, INT32_MAX);
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা get_sq(GetByteContext *gb, AVRational *out)
{
    int32_t  অঙ্ক = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    ফেরত make_q(অঙ্ক, den, out);
}

স্থির পূর্ণসংখ্যা get_uq(GetByteContext *gb, AVRational *out)
{
    uint32_t অঙ্ক = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    ফেরত make_q(অঙ্ক, den, out);
}

পূর্ণসংখ্যা av_gain_map_params_from_iso21496(AVGainMapParams *restrict p,
                                     ধ্রুবক uint8_t *তথ্য, size_t আকার_2)
{
    পূর্ণসংখ্যা ret;
    যদি (!p || !তথ্য)
        ফেরত AVERROR(EINVAL);

    যদি (আকার_2 < ISO21496_HEADER_আকার || আকার_2 > INT_MAX)
        ফেরত AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, তথ্য, আকার_2);

    /* Parse header */
    ধ্রুবক uint16_t minimum_version = bytestream2_get_be16(&gb);
    ধ্রুবক uint16_t writer_version  = bytestream2_get_be16(&gb);
    যদি (minimum_version > AV_ISO21496_VERSION || writer_version < minimum_version)
        ফেরত AVERROR_PATCHWELCOME;
    ধ্রুবক uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    যদি (writer_version == 0 && (flags & ISO21496_FLAG_RESERVED))
        ফেরত AVERROR_INVALIDDATA;

    p->version              = AV_ISO21496_VERSION;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_base_color_space = !!(flags & ISO21496_FLAG_USE_BASE_CG);

    /* Parse payload */
    যদি (bytestream2_get_bytes_বাম(&gb) < iso21496_payload_আকার(p->nb_channels))
        ফেরত AVERROR_INVALIDDATA;

    যদি ((ret = get_uq(&gb, &p->base_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        ফেরত ret;

    জন্য (পূর্ণসংখ্যা c = 0; c < p->nb_channels; c++) {
        কাঠামো AVGainMapChannel *ধ্রুবক ch = &p->channels[c];
        যদি ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->base_offset))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_offset)) < 0)
            ফেরত ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    জন্য (পূর্ণসংখ্যা c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    ফেরত av_gain_map_params_validate(p);
}

স্থির শূন্য put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (unsigned) q.অঙ্ক);
    bytestream2_put_be32(pb, (unsigned) q.den);
}

পূর্ণসংখ্যা av_gain_map_params_to_iso21496(ধ্রুবক AVGainMapParams *p, uint8_t *buf)
{
    যদি (!p || !buf)
        ফেরত AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    পূর্ণসংখ্যা ret = av_gain_map_params_validate(p);
    যদি (ret < 0)
        ফেরত ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_আকার);

    পূর্ণসংখ্যা channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    যদি (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    যদি (p->use_base_color_space)
        flags |= ISO21496_FLAG_USE_BASE_CG;

    bytestream2_put_be16(&pb, p->version); /* minimum_version */
    bytestream2_put_be16(&pb, p->version); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->base_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    জন্য (পূর্ণসংখ্যা c = 0; c < channels; c++) {
        ধ্রুবক কাঠামো AVGainMapChannel *ধ্রুবক ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->base_offset);
        put_q(&pb, ch->alternate_offset);
    }

    ফেরত bytestream2_tell_p(&pb);
}

পূর্ণসংখ্যা av_gain_map_channels_identical(ধ্রুবক AVGainMapParams *p)
{
    static_assert(আকার(p->channels[0]) == আকার(পূর্ণসংখ্যা[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    ফেরত !memcmp(&p->channels[0], &p->channels[1], আকার(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], আকার(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *আকার_2)
{
    AVGainMapParams *p = av_malloc(আকার(AVGainMapParams));
    যদি (!p)
        ফেরত ফাঁকা;

    gain_map_params_default(p);

    যদি (আকার_2)
        *আকার_2 = আকার(*p);

    ফেরত p;
}

AVGainMapParams *av_gain_map_params_create_side_তথ্য(AVFrame_Side_তথ্য ***fsd, পূর্ণসংখ্যা *nb_sd)
{
    AVFrame_Side_তথ্য *sd;
    sd = av_frame_side_তথ্য_new(fsd, nb_sd, AV_FRAME_তথ্য_GAIN_MAP_PARAMS,
                                আকার(AVGainMapParams),
                                AV_FRAME_SIDE_তথ্য_FLAG_REPLACE);
    যদি (!sd)
        ফেরত ফাঁকা;

    AVGainMapParams *ধ্রুবক p = (AVGainMapParams *) sd->তথ্য;
    gain_map_params_default(p);
    ফেরত p;
}

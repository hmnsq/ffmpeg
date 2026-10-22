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
    প্রতি (পূর্ণাঙ্ক c = 0; c < 3; c++) {
        p->channels[c] = (সংরচনা AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .base_offset        = { 1, 64 },
            .alternate_offset   = { 1, 64 },
        };
    }
}

#define CHECK(cond) কুরু { যদি (!(cond)) প্রত্যাগম AVERROR_INVALIDDATA; } যাবত্ (0)
#define CHECK_SIGNED(q)   CHECK((q).den > 0);
#define CHECK_UNSIGNED(q) CHECK((q).অঙ্ক >= 0 && (q).den > 0);

পূর্ণাঙ্ক av_gain_map_params_validate(ধ্রুব AVGainMapParams *p)
{
    CHECK(0 <= p->version && p->version <= AV_ISO21496_VERSION);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->base_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    প্রতি (পূর্ণাঙ্ক c = 0; c < p->nb_channels; c++) {
        ধ্রুব সংরচনা AVGainMapChannel *ধ্রুব ch = &p->channels[c];
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

    প্রত্যাগম 0;
}

#define ISO21496_HEADER_SIZE 5

#define ISO21496_FLAG_MULTICHANNEL (1 << 7)
#define ISO21496_FLAG_USE_BASE_CG  (1 << 6)
#define ISO21496_FLAG_RESERVED     0x3f

স্থির size_t iso21496_payload_size(পূর্ণাঙ্ক nb_channels)
{
    প্রত্যাগম 4 * 4 + (size_t) nb_channels * 10 * 4;
}

স্থির পূর্ণাঙ্ক make_q(int64_t অঙ্ক, uint32_t den, AVRational *out)
{
    যদি (!den)
        প্রত্যাগম AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&out->অঙ্ক, &out->den, অঙ্ক, den, INT32_MAX);
    প্রত্যাগম 0;
}

স্থির পূর্ণাঙ্ক get_sq(GetByteContext *gb, AVRational *out)
{
    int32_t  অঙ্ক = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    প্রত্যাগম make_q(অঙ্ক, den, out);
}

স্থির পূর্ণাঙ্ক get_uq(GetByteContext *gb, AVRational *out)
{
    uint32_t অঙ্ক = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    প্রত্যাগম make_q(অঙ্ক, den, out);
}

পূর্ণাঙ্ক av_gain_map_params_from_iso21496(AVGainMapParams *restrict p,
                                     ধ্রুব uint8_t *data, size_t size)
{
    পূর্ণাঙ্ক ret;
    যদি (!p || !data)
        প্রত্যাগম AVERROR(EINVAL);

    যদি (size < ISO21496_HEADER_SIZE || size > INT_MAX)
        প্রত্যাগম AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, data, size);

    /* Parse header */
    ধ্রুব uint16_t minimum_version = bytestream2_get_be16(&gb);
    ধ্রুব uint16_t writer_version  = bytestream2_get_be16(&gb);
    যদি (minimum_version > AV_ISO21496_VERSION || writer_version < minimum_version)
        প্রত্যাগম AVERROR_PATCHWELCOME;
    ধ্রুব uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    যদি (writer_version == 0 && (flags & ISO21496_FLAG_RESERVED))
        প্রত্যাগম AVERROR_INVALIDDATA;

    p->version              = AV_ISO21496_VERSION;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_base_color_space = !!(flags & ISO21496_FLAG_USE_BASE_CG);

    /* Parse payload */
    যদি (bytestream2_get_bytes_বাম(&gb) < iso21496_payload_size(p->nb_channels))
        প্রত্যাগম AVERROR_INVALIDDATA;

    যদি ((ret = get_uq(&gb, &p->base_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        প্রত্যাগম ret;

    প্রতি (পূর্ণাঙ্ক c = 0; c < p->nb_channels; c++) {
        সংরচনা AVGainMapChannel *ধ্রুব ch = &p->channels[c];
        যদি ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->base_offset))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_offset)) < 0)
            প্রত্যাগম ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    প্রতি (পূর্ণাঙ্ক c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    প্রত্যাগম av_gain_map_params_validate(p);
}

স্থির শূন্য put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (unsigned) q.অঙ্ক);
    bytestream2_put_be32(pb, (unsigned) q.den);
}

পূর্ণাঙ্ক av_gain_map_params_to_iso21496(ধ্রুব AVGainMapParams *p, uint8_t *buf)
{
    যদি (!p || !buf)
        প্রত্যাগম AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    পূর্ণাঙ্ক ret = av_gain_map_params_validate(p);
    যদি (ret < 0)
        প্রত্যাগম ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_SIZE);

    পূর্ণাঙ্ক channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
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

    প্রতি (পূর্ণাঙ্ক c = 0; c < channels; c++) {
        ধ্রুব সংরচনা AVGainMapChannel *ধ্রুব ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->base_offset);
        put_q(&pb, ch->alternate_offset);
    }

    প্রত্যাগম bytestream2_tell_p(&pb);
}

পূর্ণাঙ্ক av_gain_map_channels_identical(ধ্রুব AVGainMapParams *p)
{
    static_assert(পরিমাণ(p->channels[0]) == পরিমাণ(পূর্ণাঙ্ক[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    প্রত্যাগম !memcmp(&p->channels[0], &p->channels[1], পরিমাণ(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], পরিমাণ(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *size)
{
    AVGainMapParams *p = av_malloc(পরিমাণ(AVGainMapParams));
    যদি (!p)
        প্রত্যাগম রিক্ত;

    gain_map_params_default(p);

    যদি (size)
        *size = পরিমাণ(*p);

    প্রত্যাগম p;
}

AVGainMapParams *av_gain_map_params_create_side_data(AVFrameSideData ***fsd, পূর্ণাঙ্ক *nb_sd)
{
    AVFrameSideData *sd;
    sd = av_frame_side_data_new(fsd, nb_sd, AV_FRAME_DATA_GAIN_MAP_PARAMS,
                                পরিমাণ(AVGainMapParams),
                                AV_FRAME_SIDE_DATA_FLAG_REPLACE);
    যদি (!sd)
        প্রত্যাগম রিক্ত;

    AVGainMapParams *ধ্রুব p = (AVGainMapParams *) sd->data;
    gain_map_params_default(p);
    প্রত্যাগম p;
}

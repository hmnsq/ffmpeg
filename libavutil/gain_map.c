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

#அந்தர்பாவ "gain_map.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "libavcodec/bytestream.h"

நிலையான வெறுமை gain_map_params_default(AVGainMapParams *p)
{
    *p = (AVGainMapParams) {
        .base_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    க்கு (முழு c = 0; c < 3; c++) {
        p->channels[c] = (கட்டமைப்பு AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .base_offset        = { 1, 64 },
            .alternate_offset   = { 1, 64 },
        };
    }
}

#define CHECK(cond) செய் { எனில் (!(cond)) திரும்பு AVERROR_INVALIDDATA; } போது (0)
#define CHECK_SIGNED(q)   CHECK((q).den > 0);
#define CHECK_UNSIGNED(q) CHECK((q).இலக்கம் >= 0 && (q).den > 0);

முழு av_gain_map_params_validate(மாறிலி AVGainMapParams *p)
{
    CHECK(0 <= p->version && p->version <= AV_ISO21496_VERSION);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->base_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    க்கு (முழு c = 0; c < p->nb_channels; c++) {
        மாறிலி கட்டமைப்பு AVGainMapChannel *மாறிலி ch = &p->channels[c];
        CHECK_SIGNED(ch->gain_map_min);
        CHECK_SIGNED(ch->gain_map_max);
        CHECK_UNSIGNED(ch->gamma);
        CHECK(ch->gamma.இலக்கம் != 0);
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

    திரும்பு 0;
}

#define ISO21496_HEADER_SIZE 5

#define ISO21496_FLAG_MULTICHANNEL (1 << 7)
#define ISO21496_FLAG_USE_BASE_CG  (1 << 6)
#define ISO21496_FLAG_RESERVED     0x3f

நிலையான size_t iso21496_payload_size(முழு nb_channels)
{
    திரும்பு 4 * 4 + (size_t) nb_channels * 10 * 4;
}

நிலையான முழு make_q(int64_t இலக்கம், uint32_t den, AVRational *out)
{
    எனில் (!den)
        திரும்பு AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&out->இலக்கம், &out->den, இலக்கம், den, INT32_MAX);
    திரும்பு 0;
}

நிலையான முழு get_sq(GetByteContext *gb, AVRational *out)
{
    int32_t  இலக்கம் = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    திரும்பு make_q(இலக்கம், den, out);
}

நிலையான முழு get_uq(GetByteContext *gb, AVRational *out)
{
    uint32_t இலக்கம் = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    திரும்பு make_q(இலக்கம், den, out);
}

முழு av_gain_map_params_from_iso21496(AVGainMapParams *restrict p,
                                     மாறிலி uint8_t *data, size_t size)
{
    முழு ret;
    எனில் (!p || !data)
        திரும்பு AVERROR(EINVAL);

    எனில் (size < ISO21496_HEADER_SIZE || size > INT_MAX)
        திரும்பு AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, data, size);

    /* Parse header */
    மாறிலி uint16_t minimum_version = bytestream2_get_be16(&gb);
    மாறிலி uint16_t writer_version  = bytestream2_get_be16(&gb);
    எனில் (minimum_version > AV_ISO21496_VERSION || writer_version < minimum_version)
        திரும்பு AVERROR_PATCHWELCOME;
    மாறிலி uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    எனில் (writer_version == 0 && (flags & ISO21496_FLAG_RESERVED))
        திரும்பு AVERROR_INVALIDDATA;

    p->version              = AV_ISO21496_VERSION;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_base_color_space = !!(flags & ISO21496_FLAG_USE_BASE_CG);

    /* Parse payload */
    எனில் (bytestream2_get_bytes_இடது(&gb) < iso21496_payload_size(p->nb_channels))
        திரும்பு AVERROR_INVALIDDATA;

    எனில் ((ret = get_uq(&gb, &p->base_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        திரும்பு ret;

    க்கு (முழு c = 0; c < p->nb_channels; c++) {
        கட்டமைப்பு AVGainMapChannel *மாறிலி ch = &p->channels[c];
        எனில் ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->base_offset))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_offset)) < 0)
            திரும்பு ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    க்கு (முழு c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    திரும்பு av_gain_map_params_validate(p);
}

நிலையான வெறுமை put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (unsigned) q.இலக்கம்);
    bytestream2_put_be32(pb, (unsigned) q.den);
}

முழு av_gain_map_params_to_iso21496(மாறிலி AVGainMapParams *p, uint8_t *buf)
{
    எனில் (!p || !buf)
        திரும்பு AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    முழு ret = av_gain_map_params_validate(p);
    எனில் (ret < 0)
        திரும்பு ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_SIZE);

    முழு channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    எனில் (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    எனில் (p->use_base_color_space)
        flags |= ISO21496_FLAG_USE_BASE_CG;

    bytestream2_put_be16(&pb, p->version); /* minimum_version */
    bytestream2_put_be16(&pb, p->version); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->base_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    க்கு (முழு c = 0; c < channels; c++) {
        மாறிலி கட்டமைப்பு AVGainMapChannel *மாறிலி ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->base_offset);
        put_q(&pb, ch->alternate_offset);
    }

    திரும்பு bytestream2_tell_p(&pb);
}

முழு av_gain_map_channels_identical(மாறிலி AVGainMapParams *p)
{
    static_assert(அளவு(p->channels[0]) == அளவு(முழு[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    திரும்பு !memcmp(&p->channels[0], &p->channels[1], அளவு(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], அளவு(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *size)
{
    AVGainMapParams *p = av_malloc(அளவு(AVGainMapParams));
    எனில் (!p)
        திரும்பு வெற்று;

    gain_map_params_default(p);

    எனில் (size)
        *size = அளவு(*p);

    திரும்பு p;
}

AVGainMapParams *av_gain_map_params_create_side_data(AVFrameSideData ***fsd, முழு *nb_sd)
{
    AVFrameSideData *sd;
    sd = av_frame_side_data_new(fsd, nb_sd, AV_FRAME_DATA_GAIN_MAP_PARAMS,
                                அளவு(AVGainMapParams),
                                AV_FRAME_SIDE_DATA_FLAG_REPLACE);
    எனில் (!sd)
        திரும்பு வெற்று;

    AVGainMapParams *மாறிலி p = (AVGainMapParams *) sd->data;
    gain_map_params_default(p);
    திரும்பு p;
}

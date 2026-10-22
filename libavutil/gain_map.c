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

#ಅನ್ತರ್ಭಾವ "gain_map.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "libavcodec/bytestream.h"

ಸ್ಥಿರ ಶೂನ್ಯ gain_map_params_default(AVGainMapParams *p)
{
    *p = (AVGainMapParams) {
        .base_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ c = 0; c < 3; c++) {
        p->channels[c] = (ಸಂರಚನಾ AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .base_offset        = { 1, 64 },
            .alternate_offset   = { 1, 64 },
        };
    }
}

#define CHECK(cond) ಕುರು { ಯದಿ (!(cond)) ಪ್ರತ್ಯಾಗಮ AVERROR_INVALIDDATA; } ಯಾವತ್ (0)
#define CHECK_SIGNED(q)   CHECK((q).den > 0);
#define CHECK_UNSIGNED(q) CHECK((q).ಅಂಕೆ >= 0 && (q).den > 0);

ಪೂರ್ಣಾಙ್ಕ av_gain_map_params_validate(ಧ್ರುವ AVGainMapParams *p)
{
    CHECK(0 <= p->version && p->version <= AV_ISO21496_VERSION);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->base_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ c = 0; c < p->nb_channels; c++) {
        ಧ್ರುವ ಸಂರಚನಾ AVGainMapChannel *ಧ್ರುವ ch = &p->channels[c];
        CHECK_SIGNED(ch->gain_map_min);
        CHECK_SIGNED(ch->gain_map_max);
        CHECK_UNSIGNED(ch->gamma);
        CHECK(ch->gamma.ಅಂಕೆ != 0);
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

    ಪ್ರತ್ಯಾಗಮ 0;
}

#define ISO21496_HEADER_SIZE 5

#define ISO21496_FLAG_MULTICHANNEL (1 << 7)
#define ISO21496_FLAG_USE_BASE_CG  (1 << 6)
#define ISO21496_FLAG_RESERVED     0x3f

ಸ್ಥಿರ size_t iso21496_payload_size(ಪೂರ್ಣಾಙ್ಕ nb_channels)
{
    ಪ್ರತ್ಯಾಗಮ 4 * 4 + (size_t) nb_channels * 10 * 4;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ make_q(int64_t ಅಂಕೆ, uint32_t den, AVRational *out)
{
    ಯದಿ (!den)
        ಪ್ರತ್ಯಾಗಮ AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&out->ಅಂಕೆ, &out->den, ಅಂಕೆ, den, INT32_MAX);
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_sq(GetByteContext *gb, AVRational *out)
{
    int32_t  ಅಂಕೆ = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    ಪ್ರತ್ಯಾಗಮ make_q(ಅಂಕೆ, den, out);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_uq(GetByteContext *gb, AVRational *out)
{
    uint32_t ಅಂಕೆ = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    ಪ್ರತ್ಯಾಗಮ make_q(ಅಂಕೆ, den, out);
}

ಪೂರ್ಣಾಙ್ಕ av_gain_map_params_from_iso21496(AVGainMapParams *restrict p,
                                     ಧ್ರುವ uint8_t *data, size_t size)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    ಯದಿ (!p || !data)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    ಯದಿ (size < ISO21496_HEADER_SIZE || size > INT_MAX)
        ಪ್ರತ್ಯಾಗಮ AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, data, size);

    /* Parse header */
    ಧ್ರುವ uint16_t minimum_version = bytestream2_get_be16(&gb);
    ಧ್ರುವ uint16_t writer_version  = bytestream2_get_be16(&gb);
    ಯದಿ (minimum_version > AV_ISO21496_VERSION || writer_version < minimum_version)
        ಪ್ರತ್ಯಾಗಮ AVERROR_PATCHWELCOME;
    ಧ್ರುವ uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    ಯದಿ (writer_version == 0 && (flags & ISO21496_FLAG_RESERVED))
        ಪ್ರತ್ಯಾಗಮ AVERROR_INVALIDDATA;

    p->version              = AV_ISO21496_VERSION;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_base_color_space = !!(flags & ISO21496_FLAG_USE_BASE_CG);

    /* Parse payload */
    ಯದಿ (bytestream2_get_bytes_ಎಡ(&gb) < iso21496_payload_size(p->nb_channels))
        ಪ್ರತ್ಯಾಗಮ AVERROR_INVALIDDATA;

    ಯದಿ ((ret = get_uq(&gb, &p->base_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ c = 0; c < p->nb_channels; c++) {
        ಸಂರಚನಾ AVGainMapChannel *ಧ್ರುವ ch = &p->channels[c];
        ಯದಿ ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->base_offset))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_offset)) < 0)
            ಪ್ರತ್ಯಾಗಮ ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    ಪ್ರತ್ಯಾಗಮ av_gain_map_params_validate(p);
}

ಸ್ಥಿರ ಶೂನ್ಯ put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (unsigned) q.ಅಂಕೆ);
    bytestream2_put_be32(pb, (unsigned) q.den);
}

ಪೂರ್ಣಾಙ್ಕ av_gain_map_params_to_iso21496(ಧ್ರುವ AVGainMapParams *p, uint8_t *buf)
{
    ಯದಿ (!p || !buf)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    ಪೂರ್ಣಾಙ್ಕ ret = av_gain_map_params_validate(p);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_SIZE);

    ಪೂರ್ಣಾಙ್ಕ channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    ಯದಿ (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    ಯದಿ (p->use_base_color_space)
        flags |= ISO21496_FLAG_USE_BASE_CG;

    bytestream2_put_be16(&pb, p->version); /* minimum_version */
    bytestream2_put_be16(&pb, p->version); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->base_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ c = 0; c < channels; c++) {
        ಧ್ರುವ ಸಂರಚನಾ AVGainMapChannel *ಧ್ರುವ ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->base_offset);
        put_q(&pb, ch->alternate_offset);
    }

    ಪ್ರತ್ಯಾಗಮ bytestream2_tell_p(&pb);
}

ಪೂರ್ಣಾಙ್ಕ av_gain_map_channels_identical(ಧ್ರುವ AVGainMapParams *p)
{
    static_assert(ಪರಿಮಾಣ(p->channels[0]) == ಪರಿಮಾಣ(ಪೂರ್ಣಾಙ್ಕ[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    ಪ್ರತ್ಯಾಗಮ !memcmp(&p->channels[0], &p->channels[1], ಪರಿಮಾಣ(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], ಪರಿಮಾಣ(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *size)
{
    AVGainMapParams *p = av_malloc(ಪರಿಮಾಣ(AVGainMapParams));
    ಯದಿ (!p)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    gain_map_params_default(p);

    ಯದಿ (size)
        *size = ಪರಿಮಾಣ(*p);

    ಪ್ರತ್ಯಾಗಮ p;
}

AVGainMapParams *av_gain_map_params_create_side_data(AVFrameSideData ***fsd, ಪೂರ್ಣಾಙ್ಕ *nb_sd)
{
    AVFrameSideData *sd;
    sd = av_frame_side_data_new(fsd, nb_sd, AV_FRAME_DATA_GAIN_MAP_PARAMS,
                                ಪರಿಮಾಣ(AVGainMapParams),
                                AV_FRAME_SIDE_DATA_FLAG_REPLACE);
    ಯದಿ (!sd)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    AVGainMapParams *ಧ್ರುವ p = (AVGainMapParams *) sd->data;
    gain_map_params_default(p);
    ಪ್ರತ್ಯಾಗಮ p;
}

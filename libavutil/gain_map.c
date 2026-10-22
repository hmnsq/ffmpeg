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

#ਅਨ੍ਤਰ੍ਭਾਵ "gain_map.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavcodec/bytestream.h"

ਸਥਿਰ ਖਾਲੀ gain_map_params_default(AVGainMapParams *p)
{
    *p = (AVGainMapParams) {
        .ਅਧਾਰ_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    ਲਈ (ਪੂਰਨ c = 0; c < 3; c++) {
        p->channels[c] = (ਬਣਤਰ AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .ਅਧਾਰ_ਵਿੱਥ        = { 1, 64 },
            .alternate_ਵਿੱਥ   = { 1, 64 },
        };
    }
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK(cond) ਕਰੋ { ਜੇ (!(cond)) ਵਾਪਸ AVERROR_INVALIDDATA; } ਜਦੋਂ (0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_SIGNED(q)   CHECK((q).den > 0);
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_UNSIGNED(q) CHECK((q).ਅੰਕ >= 0 && (q).den > 0);

ਪੂਰਨ av_gain_map_params_validate(ਅਚਲ AVGainMapParams *p)
{
    CHECK(0 <= p->ਸੰਸਕਰਣ && p->ਸੰਸਕਰਣ <= AV_ISO21496_ਸੰਸਕਰਣ);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->ਅਧਾਰ_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    ਲਈ (ਪੂਰਨ c = 0; c < p->nb_channels; c++) {
        ਅਚਲ ਬਣਤਰ AVGainMapChannel *ਅਚਲ ch = &p->channels[c];
        CHECK_SIGNED(ch->gain_map_min);
        CHECK_SIGNED(ch->gain_map_max);
        CHECK_UNSIGNED(ch->gamma);
        CHECK(ch->gamma.ਅੰਕ != 0);
        /**
         * Note: The ISO spec declares these as signed, but a negative value
         * makes no numeric sense and would result in infinities in the
         * middle of the valid signal range; so just constrain them to be
         * unsigned as a safeguard. Note that the Adobe hdrgm spec explicitly
         * requires them to be nonnegative as well, so this avoids an
         * inconsistency.
         */
        CHECK_UNSIGNED(ch->ਅਧਾਰ_ਵਿੱਥ);
        CHECK_UNSIGNED(ch->alternate_ਵਿੱਥ);
        CHECK(av_cmp_q(ch->gain_map_min, ch->gain_map_max) <= 0);
    }

    ਵਾਪਸ 0;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ISO21496_ਸਿਰਲੇਖ_ਮਾਪ 5

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ISO21496_FLAG_MULTICHANNEL (1 << 7)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ISO21496_FLAG_USE_ਅਧਾਰ_CG  (1 << 6)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ISO21496_FLAG_RESERVED     0x3f

ਸਥਿਰ size_t iso21496_payload_ਮਾਪ(ਪੂਰਨ nb_channels)
{
    ਵਾਪਸ 4 * 4 + (size_t) nb_channels * 10 * 4;
}

ਸਥਿਰ ਪੂਰਨ make_q(int64_t ਅੰਕ, uint32_t den, AVRational *ਬਾਹਰਲਾ)
{
    ਜੇ (!den)
        ਵਾਪਸ AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&ਬਾਹਰਲਾ->ਅੰਕ, &ਬਾਹਰਲਾ->den, ਅੰਕ, den, INT32_MAX);
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ get_sq(GetByteContext *gb, AVRational *ਬਾਹਰਲਾ)
{
    int32_t  ਅੰਕ = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    ਵਾਪਸ make_q(ਅੰਕ, den, ਬਾਹਰਲਾ);
}

ਸਥਿਰ ਪੂਰਨ get_uq(GetByteContext *gb, AVRational *ਬਾਹਰਲਾ)
{
    uint32_t ਅੰਕ = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    ਵਾਪਸ make_q(ਅੰਕ, den, ਬਾਹਰਲਾ);
}

ਪੂਰਨ av_gain_map_params_from_iso21496(AVGainMapParams *ਸੀਮਿਤ p,
                                     ਅਚਲ uint8_t *ਅੰਕੜੇ, size_t ਮਾਪ)
{
    ਪੂਰਨ ret;
    ਜੇ (!p || !ਅੰਕੜੇ)
        ਵਾਪਸ AVERROR(EINVAL);

    ਜੇ (ਮਾਪ < ISO21496_ਸਿਰਲੇਖ_ਮਾਪ || ਮਾਪ > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
        ਵਾਪਸ AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, ਅੰਕੜੇ, ਮਾਪ);

    /* Parse header */
    ਅਚਲ uint16_t minimum_ਸੰਸਕਰਣ = bytestream2_get_be16(&gb);
    ਅਚਲ uint16_t writer_ਸੰਸਕਰਣ  = bytestream2_get_be16(&gb);
    ਜੇ (minimum_ਸੰਸਕਰਣ > AV_ISO21496_ਸੰਸਕਰਣ || writer_ਸੰਸਕਰਣ < minimum_ਸੰਸਕਰਣ)
        ਵਾਪਸ AVERROR_PATCHWELCOME;
    ਅਚਲ uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    ਜੇ (writer_ਸੰਸਕਰਣ == 0 && (flags & ISO21496_FLAG_RESERVED))
        ਵਾਪਸ AVERROR_INVALIDDATA;

    p->ਸੰਸਕਰਣ              = AV_ISO21496_ਸੰਸਕਰਣ;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_ਅਧਾਰ_color_space = !!(flags & ISO21496_FLAG_USE_ਅਧਾਰ_CG);

    /* Parse payload */
    ਜੇ (bytestream2_get_ਬਾਈਟਾਂ_ਖੱਬਾ(&gb) < iso21496_payload_ਮਾਪ(p->nb_channels))
        ਵਾਪਸ AVERROR_INVALIDDATA;

    ਜੇ ((ret = get_uq(&gb, &p->ਅਧਾਰ_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        ਵਾਪਸ ret;

    ਲਈ (ਪੂਰਨ c = 0; c < p->nb_channels; c++) {
        ਬਣਤਰ AVGainMapChannel *ਅਚਲ ch = &p->channels[c];
        ਜੇ ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->ਅਧਾਰ_ਵਿੱਥ))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_ਵਿੱਥ)) < 0)
            ਵਾਪਸ ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    ਲਈ (ਪੂਰਨ c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    ਵਾਪਸ av_gain_map_params_validate(p);
}

ਸਥਿਰ ਖਾਲੀ put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (ਬਿਨਾਨਿਸ਼ਾਨੀ) q.ਅੰਕ);
    bytestream2_put_be32(pb, (ਬਿਨਾਨਿਸ਼ਾਨੀ) q.den);
}

ਪੂਰਨ av_gain_map_params_ਮੰਜ਼ਿਲ_iso21496(ਅਚਲ AVGainMapParams *p, uint8_t *buf)
{
    ਜੇ (!p || !buf)
        ਵਾਪਸ AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    ਪੂਰਨ ret = av_gain_map_params_validate(p);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_ਮਾਪ);

    ਪੂਰਨ channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    ਜੇ (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    ਜੇ (p->use_ਅਧਾਰ_color_space)
        flags |= ISO21496_FLAG_USE_ਅਧਾਰ_CG;

    bytestream2_put_be16(&pb, p->ਸੰਸਕਰਣ); /* minimum_version */
    bytestream2_put_be16(&pb, p->ਸੰਸਕਰਣ); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->ਅਧਾਰ_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    ਲਈ (ਪੂਰਨ c = 0; c < channels; c++) {
        ਅਚਲ ਬਣਤਰ AVGainMapChannel *ਅਚਲ ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->ਅਧਾਰ_ਵਿੱਥ);
        put_q(&pb, ch->alternate_ਵਿੱਥ);
    }

    ਵਾਪਸ bytestream2_tell_p(&pb);
}

ਪੂਰਨ av_gain_map_channels_identical(ਅਚਲ AVGainMapParams *p)
{
    static_assert(ਆਕਾਰ(p->channels[0]) == ਆਕਾਰ(ਪੂਰਨ[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    ਵਾਪਸ !memcmp(&p->channels[0], &p->channels[1], ਆਕਾਰ(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], ਆਕਾਰ(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *ਮਾਪ)
{
    AVGainMapParams *p = av_malloc(ਆਕਾਰ(AVGainMapParams));
    ਜੇ (!p)
        ਵਾਪਸ ਨਿਰਾ;

    gain_map_params_default(p);

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = ਆਕਾਰ(*p);

    ਵਾਪਸ p;
}

AVGainMapParams *av_gain_map_params_create_side_ਅੰਕੜੇ(AVFrame_Side_ਅੰਕੜੇ ***fsd, ਪੂਰਨ *nb_sd)
{
    AVFrame_Side_ਅੰਕੜੇ *sd;
    sd = av_ਚੌਖਟਾ_side_ਅੰਕੜੇ_new(fsd, nb_sd, AV_ਚੌਖਟਾ_ਅੰਕੜੇ_GAIN_MAP_PARAMS,
                                ਆਕਾਰ(AVGainMapParams),
                                AV_ਚੌਖਟਾ_SIDE_ਅੰਕੜੇ_FLAG_REPLACE);
    ਜੇ (!sd)
        ਵਾਪਸ ਨਿਰਾ;

    AVGainMapParams *ਅਚਲ p = (AVGainMapParams *) sd->ਅੰਕੜੇ;
    gain_map_params_default(p);
    ਵਾਪਸ p;
}

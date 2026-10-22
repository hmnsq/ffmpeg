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
        .ತಳ_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < 3; c++) {
        p->channels[c] = (ರಚನೆ AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .ತಳ_ಸ್ಥಾನಾಂತರ        = { 1, 64 },
            .alternate_ಸ್ಥಾನಾಂತರ   = { 1, 64 },
        };
    }
}

#ವ್ಯಾಖ್ಯಾನಿಸು CHECK(cond) ಮಾಡು { ಆದರೆ (!(cond)) ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA; } ಆಗ (0)
#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_SIGNED(q)   CHECK((q).den > 0);
#ವ್ಯಾಖ್ಯಾನಿಸು CHECK_UNSIGNED(q) CHECK((q).ಅಂಕೆ >= 0 && (q).den > 0);

ಪೂರ್ಣಾಂಕ av_gain_map_params_validate(ಸ್ಥಿರಾಂಕ AVGainMapParams *p)
{
    CHECK(0 <= p->ಆವೃತ್ತಿ && p->ಆವೃತ್ತಿ <= AV_ISO21496_ಆವೃತ್ತಿ);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->ತಳ_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < p->nb_channels; c++) {
        ಸ್ಥಿರಾಂಕ ರಚನೆ AVGainMapChannel *ಸ್ಥಿರಾಂಕ ch = &p->channels[c];
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
        CHECK_UNSIGNED(ch->ತಳ_ಸ್ಥಾನಾಂತರ);
        CHECK_UNSIGNED(ch->alternate_ಸ್ಥಾನಾಂತರ);
        CHECK(av_cmp_q(ch->gain_map_min, ch->gain_map_max) <= 0);
    }

    ಹಿಂತಿರುಗಿ 0;
}

#ವ್ಯಾಖ್ಯಾನಿಸು ISO21496_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ 5

#ವ್ಯಾಖ್ಯಾನಿಸು ISO21496_FLAG_MULTICHANNEL (1 << 7)
#ವ್ಯಾಖ್ಯಾನಿಸು ISO21496_FLAG_USE_ತಳ_CG  (1 << 6)
#ವ್ಯಾಖ್ಯಾನಿಸು ISO21496_FLAG_RESERVED     0x3f

ಸ್ಥಿರ size_t iso21496_payload_ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ nb_channels)
{
    ಹಿಂತಿರುಗಿ 4 * 4 + (size_t) nb_channels * 10 * 4;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ make_q(int64_t ಅಂಕೆ, uint32_t den, AVRational *ಹೊರಹೋಗು)
{
    ಆದರೆ (!den)
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&ಹೊರಹೋಗು->ಅಂಕೆ, &ಹೊರಹೋಗು->den, ಅಂಕೆ, den, INT32_MAX);
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_sq(GetByteContext *gb, AVRational *ಹೊರಹೋಗು)
{
    int32_t  ಅಂಕೆ = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    ಹಿಂತಿರುಗಿ make_q(ಅಂಕೆ, den, ಹೊರಹೋಗು);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_uq(GetByteContext *gb, AVRational *ಹೊರಹೋಗು)
{
    uint32_t ಅಂಕೆ = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    ಹಿಂತಿರುಗಿ make_q(ಅಂಕೆ, den, ಹೊರಹೋಗು);
}

ಪೂರ್ಣಾಂಕ av_gain_map_params_from_iso21496(AVGainMapParams *ಸೀಮಿತ p,
                                     ಸ್ಥಿರಾಂಕ uint8_t *ದತ್ತಾಂಶ, size_t ಗಾತ್ರ_2)
{
    ಪೂರ್ಣಾಂಕ ret;
    ಆದರೆ (!p || !ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    ಆದರೆ (ಗಾತ್ರ_2 < ISO21496_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ || ಗಾತ್ರ_2 > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ)
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, ದತ್ತಾಂಶ, ಗಾತ್ರ_2);

    /* Parse header */
    ಸ್ಥಿರಾಂಕ uint16_t minimum_ಆವೃತ್ತಿ = bytestream2_get_be16(&gb);
    ಸ್ಥಿರಾಂಕ uint16_t writer_ಆವೃತ್ತಿ  = bytestream2_get_be16(&gb);
    ಆದರೆ (minimum_ಆವೃತ್ತಿ > AV_ISO21496_ಆವೃತ್ತಿ || writer_ಆವೃತ್ತಿ < minimum_ಆವೃತ್ತಿ)
        ಹಿಂತಿರುಗಿ AVERROR_PATCHWELCOME;
    ಸ್ಥಿರಾಂಕ uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    ಆದರೆ (writer_ಆವೃತ್ತಿ == 0 && (flags & ISO21496_FLAG_RESERVED))
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

    p->ಆವೃತ್ತಿ              = AV_ISO21496_ಆವೃತ್ತಿ;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_ತಳ_color_space = !!(flags & ISO21496_FLAG_USE_ತಳ_CG);

    /* Parse payload */
    ಆದರೆ (bytestream2_get_ಬೈಟುಗಳು_ಎಡ(&gb) < iso21496_payload_ಗಾತ್ರ(p->nb_channels))
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;

    ಆದರೆ ((ret = get_uq(&gb, &p->ತಳ_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        ಹಿಂತಿರುಗಿ ret;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < p->nb_channels; c++) {
        ರಚನೆ AVGainMapChannel *ಸ್ಥಿರಾಂಕ ch = &p->channels[c];
        ಆದರೆ ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->ತಳ_ಸ್ಥಾನಾಂತರ))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_ಸ್ಥಾನಾಂತರ)) < 0)
            ಹಿಂತಿರುಗಿ ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    ಹಿಂತಿರುಗಿ av_gain_map_params_validate(p);
}

ಸ್ಥಿರ ಶೂನ್ಯ put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (ಚಿಹ್ನೆರಹಿತ) q.ಅಂಕೆ);
    bytestream2_put_be32(pb, (ಚಿಹ್ನೆರಹಿತ) q.den);
}

ಪೂರ್ಣಾಂಕ av_gain_map_params_ಗಮ್ಯ_iso21496(ಸ್ಥಿರಾಂಕ AVGainMapParams *p, uint8_t *buf)
{
    ಆದರೆ (!p || !buf)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    ಪೂರ್ಣಾಂಕ ret = av_gain_map_params_validate(p);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_ಗಾತ್ರ);

    ಪೂರ್ಣಾಂಕ channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    ಆದರೆ (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    ಆದರೆ (p->use_ತಳ_color_space)
        flags |= ISO21496_FLAG_USE_ತಳ_CG;

    bytestream2_put_be16(&pb, p->ಆವೃತ್ತಿ); /* minimum_version */
    bytestream2_put_be16(&pb, p->ಆವೃತ್ತಿ); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->ತಳ_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ c = 0; c < channels; c++) {
        ಸ್ಥಿರಾಂಕ ರಚನೆ AVGainMapChannel *ಸ್ಥಿರಾಂಕ ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->ತಳ_ಸ್ಥಾನಾಂತರ);
        put_q(&pb, ch->alternate_ಸ್ಥಾನಾಂತರ);
    }

    ಹಿಂತಿರುಗಿ bytestream2_tell_p(&pb);
}

ಪೂರ್ಣಾಂಕ av_gain_map_channels_identical(ಸ್ಥಿರಾಂಕ AVGainMapParams *p)
{
    static_assert(ಗಾತ್ರ(p->channels[0]) == ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    ಹಿಂತಿರುಗಿ !memcmp(&p->channels[0], &p->channels[1], ಗಾತ್ರ(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], ಗಾತ್ರ(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *ಗಾತ್ರ_2)
{
    AVGainMapParams *p = av_malloc(ಗಾತ್ರ(AVGainMapParams));
    ಆದರೆ (!p)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    gain_map_params_default(p);

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = ಗಾತ್ರ(*p);

    ಹಿಂತಿರುಗಿ p;
}

AVGainMapParams *av_gain_map_params_create_side_ದತ್ತಾಂಶ(AVFrame_Side_ದತ್ತಾಂಶ ***fsd, ಪೂರ್ಣಾಂಕ *nb_sd)
{
    AVFrame_Side_ದತ್ತಾಂಶ *sd;
    sd = av_ಚೌಕಟ್ಟು_side_ದತ್ತಾಂಶ_new(fsd, nb_sd, AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_GAIN_MAP_PARAMS,
                                ಗಾತ್ರ(AVGainMapParams),
                                AV_ಚೌಕಟ್ಟು_SIDE_ದತ್ತಾಂಶ_FLAG_REPLACE);
    ಆದರೆ (!sd)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    AVGainMapParams *ಸ್ಥಿರಾಂಕ p = (AVGainMapParams *) sd->ದತ್ತಾಂಶ;
    gain_map_params_default(p);
    ಹಿಂತಿರುಗಿ p;
}

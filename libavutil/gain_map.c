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

#ضمن "gain_map.h"
#ضمن "mem.h"
#ضمن "libavcodec/bytestream.h"

ساكن فراغ gain_map_params_default(AVGainMapParams *p)
{
    *p = (AVGainMapParams) {
        .ادھار_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    لكل (صحيح c = 0; c < 3; c++) {
        p->channels[c] = (بنية AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .ادھار_وتھ        = { 1, 64 },
            .alternate_وتھ   = { 1, 64 },
        };
    }
}

#تعریف_کرو CHECK(cond) افعل { إذا (!(cond)) أرجع AVERROR_INVALIDDATA; } طالما (0)
#تعریف_کرو CHECK_SIGNED(q)   CHECK((q).den > 0);
#تعریف_کرو CHECK_UNSIGNED(q) CHECK((q).عدد >= 0 && (q).den > 0);

صحيح av_gain_map_params_validate(ثابت AVGainMapParams *p)
{
    CHECK(0 <= p->نسخہ && p->نسخہ <= AV_ISO21496_نسخہ);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->ادھار_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    لكل (صحيح c = 0; c < p->nb_channels; c++) {
        ثابت بنية AVGainMapChannel *ثابت ch = &p->channels[c];
        CHECK_SIGNED(ch->gain_map_min);
        CHECK_SIGNED(ch->gain_map_max);
        CHECK_UNSIGNED(ch->gamma);
        CHECK(ch->gamma.عدد != 0);
        /**
         * Note: The ISO spec declares these as signed, but a negative value
         * makes no numeric sense and would result in infinities in the
         * middle of the valid signal range; so just constrain them to be
         * unsigned as a safeguard. Note that the Adobe hdrgm spec explicitly
         * requires them to be nonnegative as well, so this avoids an
         * inconsistency.
         */
        CHECK_UNSIGNED(ch->ادھار_وتھ);
        CHECK_UNSIGNED(ch->alternate_وتھ);
        CHECK(av_cmp_q(ch->gain_map_min, ch->gain_map_max) <= 0);
    }

    أرجع 0;
}

#تعریف_کرو ISO21496_سرخی_ناپ 5

#تعریف_کرو ISO21496_FLAG_MULTICHANNEL (1 << 7)
#تعریف_کرو ISO21496_FLAG_USE_ادھار_CG  (1 << 6)
#تعریف_کرو ISO21496_FLAG_RESERVED     0x3f

ساكن size_t iso21496_payload_ناپ(صحيح nb_channels)
{
    أرجع 4 * 4 + (size_t) nb_channels * 10 * 4;
}

ساكن صحيح make_q(int64_t عدد, uint32_t den, AVRational *باہرلا)
{
    إذا (!den)
        أرجع AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&باہرلا->عدد, &باہرلا->den, عدد, den, INT32_MAX);
    أرجع 0;
}

ساكن صحيح get_sq(GetByteContext *gb, AVRational *باہرلا)
{
    int32_t  عدد = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    أرجع make_q(عدد, den, باہرلا);
}

ساكن صحيح get_uq(GetByteContext *gb, AVRational *باہرلا)
{
    uint32_t عدد = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    أرجع make_q(عدد, den, باہرلا);
}

صحيح av_gain_map_params_from_iso21496(AVGainMapParams *محدود p,
                                     ثابت uint8_t *انکڑے, size_t ناپ)
{
    صحيح ret;
    إذا (!p || !انکڑے)
        أرجع AVERROR(EINVAL);

    إذا (ناپ < ISO21496_سرخی_ناپ || ناپ > ودھ_توں_ودھ_عدد)
        أرجع AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, انکڑے, ناپ);

    /* Parse header */
    ثابت uint16_t minimum_نسخہ = bytestream2_get_be16(&gb);
    ثابت uint16_t writer_نسخہ  = bytestream2_get_be16(&gb);
    إذا (minimum_نسخہ > AV_ISO21496_نسخہ || writer_نسخہ < minimum_نسخہ)
        أرجع AVERROR_PATCHWELCOME;
    ثابت uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    إذا (writer_نسخہ == 0 && (flags & ISO21496_FLAG_RESERVED))
        أرجع AVERROR_INVALIDDATA;

    p->نسخہ              = AV_ISO21496_نسخہ;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_ادھار_color_space = !!(flags & ISO21496_FLAG_USE_ادھار_CG);

    /* Parse payload */
    إذا (bytestream2_get_بائٹاں_بایاں(&gb) < iso21496_payload_ناپ(p->nb_channels))
        أرجع AVERROR_INVALIDDATA;

    إذا ((ret = get_uq(&gb, &p->ادھار_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        أرجع ret;

    لكل (صحيح c = 0; c < p->nb_channels; c++) {
        بنية AVGainMapChannel *ثابت ch = &p->channels[c];
        إذا ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->ادھار_وتھ))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_وتھ)) < 0)
            أرجع ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    لكل (صحيح c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    أرجع av_gain_map_params_validate(p);
}

ساكن فراغ put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (بنانشانی) q.عدد);
    bytestream2_put_be32(pb, (بنانشانی) q.den);
}

صحيح av_gain_map_params_منزل_iso21496(ثابت AVGainMapParams *p, uint8_t *buf)
{
    إذا (!p || !buf)
        أرجع AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    صحيح ret = av_gain_map_params_validate(p);
    إذا (ret < 0)
        أرجع ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_ناپ);

    صحيح channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    إذا (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    إذا (p->use_ادھار_color_space)
        flags |= ISO21496_FLAG_USE_ادھار_CG;

    bytestream2_put_be16(&pb, p->نسخہ); /* minimum_version */
    bytestream2_put_be16(&pb, p->نسخہ); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->ادھار_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    لكل (صحيح c = 0; c < channels; c++) {
        ثابت بنية AVGainMapChannel *ثابت ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->ادھار_وتھ);
        put_q(&pb, ch->alternate_وتھ);
    }

    أرجع bytestream2_tell_p(&pb);
}

صحيح av_gain_map_channels_identical(ثابت AVGainMapParams *p)
{
    static_assert(حجم(p->channels[0]) == حجم(صحيح[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    أرجع !memcmp(&p->channels[0], &p->channels[1], حجم(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], حجم(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *ناپ)
{
    AVGainMapParams *p = av_malloc(حجم(AVGainMapParams));
    إذا (!p)
        أرجع عدم;

    gain_map_params_default(p);

    إذا (ناپ)
        *ناپ = حجم(*p);

    أرجع p;
}

AVGainMapParams *av_gain_map_params_create_side_انکڑے(AVFrame_Side_انکڑے ***fsd, صحيح *nb_sd)
{
    AVFrame_Side_انکڑے *sd;
    sd = av_چوکھٹا_side_انکڑے_new(fsd, nb_sd, AV_چوکھٹا_انکڑے_GAIN_MAP_PARAMS,
                                حجم(AVGainMapParams),
                                AV_چوکھٹا_SIDE_انکڑے_FLAG_REPLACE);
    إذا (!sd)
        أرجع عدم;

    AVGainMapParams *ثابت p = (AVGainMapParams *) sd->انکڑے;
    gain_map_params_default(p);
    أرجع p;
}

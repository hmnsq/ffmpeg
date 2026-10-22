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

#شامل "gain_map.h"
#شامل "mem.h"
#شامل "libavcodec/bytestream.h"

ساکن خالی gain_map_params_default(AVGainMapParams *p)
{
    *p = (AVGainMapParams) {
        .بنیاد_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    برائے (صحیح c = 0; c < 3; c++) {
        p->channels[c] = (ساخت AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .بنیاد_انحراف        = { 1, 64 },
            .alternate_انحراف   = { 1, 64 },
        };
    }
}

#تعریف_کرو CHECK(cond) کرو { اگر (!(cond)) واپس AVERROR_INVALIDDATA; } جب (0)
#تعریف_کرو CHECK_SIGNED(q)   CHECK((q).den > 0);
#تعریف_کرو CHECK_UNSIGNED(q) CHECK((q).عدد >= 0 && (q).den > 0);

صحیح av_gain_map_params_validate(ثابت AVGainMapParams *p)
{
    CHECK(0 <= p->نسخہ && p->نسخہ <= AV_ISO21496_نسخہ);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->بنیاد_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    برائے (صحیح c = 0; c < p->nb_channels; c++) {
        ثابت ساخت AVGainMapChannel *ثابت ch = &p->channels[c];
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
        CHECK_UNSIGNED(ch->بنیاد_انحراف);
        CHECK_UNSIGNED(ch->alternate_انحراف);
        CHECK(av_cmp_q(ch->gain_map_min, ch->gain_map_max) <= 0);
    }

    واپس 0;
}

#تعریف_کرو ISO21496_سرخی_سائز 5

#تعریف_کرو ISO21496_FLAG_MULTICHANNEL (1 << 7)
#تعریف_کرو ISO21496_FLAG_USE_بنیاد_CG  (1 << 6)
#تعریف_کرو ISO21496_FLAG_RESERVED     0x3f

ساکن size_t iso21496_payload_سائز(صحیح nb_channels)
{
    واپس 4 * 4 + (size_t) nb_channels * 10 * 4;
}

ساکن صحیح make_q(int64_t عدد, uint32_t den, AVRational *برآمد)
{
    اگر (!den)
        واپس AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&برآمد->عدد, &برآمد->den, عدد, den, INT32_MAX);
    واپس 0;
}

ساکن صحیح get_sq(GetByteContext *gb, AVRational *برآمد)
{
    int32_t  عدد = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    واپس make_q(عدد, den, برآمد);
}

ساکن صحیح get_uq(GetByteContext *gb, AVRational *برآمد)
{
    uint32_t عدد = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    واپس make_q(عدد, den, برآمد);
}

صحیح av_gain_map_params_from_iso21496(AVGainMapParams *محدود p,
                                     ثابت uint8_t *ڈیٹا, size_t سائز)
{
    صحیح ret;
    اگر (!p || !ڈیٹا)
        واپس AVERROR(EINVAL);

    اگر (سائز < ISO21496_سرخی_سائز || سائز > زیادہ_سے_زیادہ_عدد)
        واپس AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, ڈیٹا, سائز);

    /* Parse header */
    ثابت uint16_t minimum_نسخہ = bytestream2_get_be16(&gb);
    ثابت uint16_t writer_نسخہ  = bytestream2_get_be16(&gb);
    اگر (minimum_نسخہ > AV_ISO21496_نسخہ || writer_نسخہ < minimum_نسخہ)
        واپس AVERROR_PATCHWELCOME;
    ثابت uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    اگر (writer_نسخہ == 0 && (flags & ISO21496_FLAG_RESERVED))
        واپس AVERROR_INVALIDDATA;

    p->نسخہ              = AV_ISO21496_نسخہ;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_بنیاد_color_space = !!(flags & ISO21496_FLAG_USE_بنیاد_CG);

    /* Parse payload */
    اگر (bytestream2_get_بائٹیں_بایاں(&gb) < iso21496_payload_سائز(p->nb_channels))
        واپس AVERROR_INVALIDDATA;

    اگر ((ret = get_uq(&gb, &p->بنیاد_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        واپس ret;

    برائے (صحیح c = 0; c < p->nb_channels; c++) {
        ساخت AVGainMapChannel *ثابت ch = &p->channels[c];
        اگر ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->بنیاد_انحراف))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_انحراف)) < 0)
            واپس ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    برائے (صحیح c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    واپس av_gain_map_params_validate(p);
}

ساکن خالی put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (غیرعلامتی) q.عدد);
    bytestream2_put_be32(pb, (غیرعلامتی) q.den);
}

صحیح av_gain_map_params_مقصد_iso21496(ثابت AVGainMapParams *p, uint8_t *buf)
{
    اگر (!p || !buf)
        واپس AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    صحیح ret = av_gain_map_params_validate(p);
    اگر (ret < 0)
        واپس ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_سائز);

    صحیح channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    اگر (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    اگر (p->use_بنیاد_color_space)
        flags |= ISO21496_FLAG_USE_بنیاد_CG;

    bytestream2_put_be16(&pb, p->نسخہ); /* minimum_version */
    bytestream2_put_be16(&pb, p->نسخہ); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->بنیاد_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    برائے (صحیح c = 0; c < channels; c++) {
        ثابت ساخت AVGainMapChannel *ثابت ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->بنیاد_انحراف);
        put_q(&pb, ch->alternate_انحراف);
    }

    واپس bytestream2_tell_p(&pb);
}

صحیح av_gain_map_channels_identical(ثابت AVGainMapParams *p)
{
    static_assert(حجم(p->channels[0]) == حجم(صحیح[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    واپس !memcmp(&p->channels[0], &p->channels[1], حجم(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], حجم(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *سائز)
{
    AVGainMapParams *p = av_malloc(حجم(AVGainMapParams));
    اگر (!p)
        واپس تہی;

    gain_map_params_default(p);

    اگر (سائز)
        *سائز = حجم(*p);

    واپس p;
}

AVGainMapParams *av_gain_map_params_create_side_ڈیٹا(AVFrame_Side_ڈیٹا ***fsd, صحیح *nb_sd)
{
    AVFrame_Side_ڈیٹا *sd;
    sd = av_چوکھٹا_side_ڈیٹا_new(fsd, nb_sd, AV_چوکھٹا_ڈیٹا_GAIN_MAP_PARAMS,
                                حجم(AVGainMapParams),
                                AV_چوکھٹا_SIDE_ڈیٹا_FLAG_REPLACE);
    اگر (!sd)
        واپس تہی;

    AVGainMapParams *ثابت p = (AVGainMapParams *) sd->ڈیٹا;
    gain_map_params_default(p);
    واپس p;
}

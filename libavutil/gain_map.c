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
        .پایه_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    لكل (صحيح c = 0; c < 3; c++) {
        p->channels[c] = (بنية AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .پایه_جابه_جایی        = { 1, 64 },
            .alternate_جابه_جایی   = { 1, 64 },
        };
    }
}

#تعریف_کن CHECK(cond) افعل { إذا (!(cond)) أرجع AVERROR_INVALIDDATA; } طالما (0)
#تعریف_کن CHECK_SIGNED(q)   CHECK((q).den > 0);
#تعریف_کن CHECK_UNSIGNED(q) CHECK((q).رقم >= 0 && (q).den > 0);

صحيح av_gain_map_params_validate(ثابت AVGainMapParams *p)
{
    CHECK(0 <= p->نسخه && p->نسخه <= AV_ISO21496_نسخه);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->پایه_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    لكل (صحيح c = 0; c < p->nb_channels; c++) {
        ثابت بنية AVGainMapChannel *ثابت ch = &p->channels[c];
        CHECK_SIGNED(ch->gain_map_min);
        CHECK_SIGNED(ch->gain_map_max);
        CHECK_UNSIGNED(ch->gamma);
        CHECK(ch->gamma.رقم != 0);
        /**
         * Note: The ISO spec declares these as signed, but a negative value
         * makes no numeric sense and would result in infinities in the
         * middle of the valid signal range; so just constrain them to be
         * unsigned as a safeguard. Note that the Adobe hdrgm spec explicitly
         * requires them to be nonnegative as well, so this avoids an
         * inconsistency.
         */
        CHECK_UNSIGNED(ch->پایه_جابه_جایی);
        CHECK_UNSIGNED(ch->alternate_جابه_جایی);
        CHECK(av_cmp_q(ch->gain_map_min, ch->gain_map_max) <= 0);
    }

    أرجع 0;
}

#تعریف_کن ISO21496_سرآیند_اندازه 5

#تعریف_کن ISO21496_FLAG_MULTICHANNEL (1 << 7)
#تعریف_کن ISO21496_FLAG_USE_پایه_CG  (1 << 6)
#تعریف_کن ISO21496_FLAG_RESERVED     0x3f

ساكن size_t iso21496_payload_اندازه(صحيح nb_channels)
{
    أرجع 4 * 4 + (size_t) nb_channels * 10 * 4;
}

ساكن صحيح make_q(int64_t رقم, uint32_t den, AVRational *بیرون)
{
    إذا (!den)
        أرجع AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&بیرون->رقم, &بیرون->den, رقم, den, INT32_MAX);
    أرجع 0;
}

ساكن صحيح get_sq(GetByteContext *gb, AVRational *بیرون)
{
    int32_t  رقم = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    أرجع make_q(رقم, den, بیرون);
}

ساكن صحيح get_uq(GetByteContext *gb, AVRational *بیرون)
{
    uint32_t رقم = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    أرجع make_q(رقم, den, بیرون);
}

صحيح av_gain_map_params_from_iso21496(AVGainMapParams *محدود p,
                                     ثابت uint8_t *داده, size_t اندازه)
{
    صحيح ret;
    إذا (!p || !داده)
        أرجع AVERROR(EINVAL);

    إذا (اندازه < ISO21496_سرآیند_اندازه || اندازه > بیشترین_صحیح)
        أرجع AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, داده, اندازه);

    /* Parse header */
    ثابت uint16_t minimum_نسخه = bytestream2_get_be16(&gb);
    ثابت uint16_t writer_نسخه  = bytestream2_get_be16(&gb);
    إذا (minimum_نسخه > AV_ISO21496_نسخه || writer_نسخه < minimum_نسخه)
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
    إذا (writer_نسخه == 0 && (flags & ISO21496_FLAG_RESERVED))
        أرجع AVERROR_INVALIDDATA;

    p->نسخه              = AV_ISO21496_نسخه;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_پایه_color_space = !!(flags & ISO21496_FLAG_USE_پایه_CG);

    /* Parse payload */
    إذا (bytestream2_get_بایتها_چپ(&gb) < iso21496_payload_اندازه(p->nb_channels))
        أرجع AVERROR_INVALIDDATA;

    إذا ((ret = get_uq(&gb, &p->پایه_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        أرجع ret;

    لكل (صحيح c = 0; c < p->nb_channels; c++) {
        بنية AVGainMapChannel *ثابت ch = &p->channels[c];
        إذا ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->پایه_جابه_جایی))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_جابه_جایی)) < 0)
            أرجع ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    لكل (صحيح c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    أرجع av_gain_map_params_validate(p);
}

ساكن فراغ put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (بیعلامت) q.رقم);
    bytestream2_put_be32(pb, (بیعلامت) q.den);
}

صحيح av_gain_map_params_مقصد_iso21496(ثابت AVGainMapParams *p, uint8_t *buf)
{
    إذا (!p || !buf)
        أرجع AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    صحيح ret = av_gain_map_params_validate(p);
    إذا (ret < 0)
        أرجع ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_اندازه);

    صحيح channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    إذا (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    إذا (p->use_پایه_color_space)
        flags |= ISO21496_FLAG_USE_پایه_CG;

    bytestream2_put_be16(&pb, p->نسخه); /* minimum_version */
    bytestream2_put_be16(&pb, p->نسخه); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->پایه_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    لكل (صحيح c = 0; c < channels; c++) {
        ثابت بنية AVGainMapChannel *ثابت ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->پایه_جابه_جایی);
        put_q(&pb, ch->alternate_جابه_جایی);
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

AVGainMapParams *av_gain_map_params_alloc(size_t *اندازه)
{
    AVGainMapParams *p = av_malloc(حجم(AVGainMapParams));
    إذا (!p)
        أرجع عدم;

    gain_map_params_default(p);

    إذا (اندازه)
        *اندازه = حجم(*p);

    أرجع p;
}

AVGainMapParams *av_gain_map_params_create_side_داده(AVFrame_Side_داده ***fsd, صحيح *nb_sd)
{
    AVFrame_Side_داده *sd;
    sd = av_قاب_side_داده_new(fsd, nb_sd, AV_قاب_داده_GAIN_MAP_PARAMS,
                                حجم(AVGainMapParams),
                                AV_قاب_SIDE_داده_FLAG_REPLACE);
    إذا (!sd)
        أرجع عدم;

    AVGainMapParams *ثابت p = (AVGainMapParams *) sd->داده;
    gain_map_params_default(p);
    أرجع p;
}

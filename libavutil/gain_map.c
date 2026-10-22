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

#समावेश "gain_map.h"
#समावेश "mem.h"
#समावेश "libavcodec/bytestream.h"

अटल व्योम gain_map_params_default(AVGainMapParams *p)
{
    *p = (AVGainMapParams) {
        .base_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    क्रम (पूर्णांक c = 0; c < 3; c++) {
        p->channels[c] = (काष्ठा AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .base_offset        = { 1, 64 },
            .alternate_offset   = { 1, 64 },
        };
    }
}

#घोषणा CHECK(cond) करो { अगर (!(cond)) वापस AVERROR_INVALIDDATA; } जबतक (0)
#घोषणा CHECK_SIGNED(q)   CHECK((q).den > 0);
#घोषणा CHECK_UNSIGNED(q) CHECK((q).अंक >= 0 && (q).den > 0);

पूर्णांक av_gain_map_params_validate(स्थिर AVGainMapParams *p)
{
    CHECK(0 <= p->version && p->version <= AV_ISO21496_VERSION);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->base_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    क्रम (पूर्णांक c = 0; c < p->nb_channels; c++) {
        स्थिर काष्ठा AVGainMapChannel *स्थिर ch = &p->channels[c];
        CHECK_SIGNED(ch->gain_map_min);
        CHECK_SIGNED(ch->gain_map_max);
        CHECK_UNSIGNED(ch->gamma);
        CHECK(ch->gamma.अंक != 0);
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

    वापस 0;
}

#घोषणा ISO21496_HEADER_आकार 5

#घोषणा ISO21496_FLAG_MULTICHANNEL (1 << 7)
#घोषणा ISO21496_FLAG_USE_BASE_CG  (1 << 6)
#घोषणा ISO21496_FLAG_RESERVED     0x3f

अटल माप_प्रकार iso21496_payload_आकार(पूर्णांक nb_channels)
{
    वापस 4 * 4 + (माप_प्रकार) nb_channels * 10 * 4;
}

अटल पूर्णांक make_q(int64_t अंक, uint32_t den, AVRational *out)
{
    अगर (!den)
        वापस AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&out->अंक, &out->den, अंक, den, INT32_MAX);
    वापस 0;
}

अटल पूर्णांक get_sq(GetByteContext *gb, AVRational *out)
{
    int32_t  अंक = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    वापस make_q(अंक, den, out);
}

अटल पूर्णांक get_uq(GetByteContext *gb, AVRational *out)
{
    uint32_t अंक = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    वापस make_q(अंक, den, out);
}

पूर्णांक av_gain_map_params_from_iso21496(AVGainMapParams *restrict p,
                                     स्थिर uint8_t *तथ्य, माप_प्रकार आकार)
{
    पूर्णांक ret;
    अगर (!p || !तथ्य)
        वापस AVERROR(EINVAL);

    अगर (आकार < ISO21496_HEADER_आकार || आकार > पूर्णांक_उच्च)
        वापस AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, तथ्य, आकार);

    /* Parse header */
    स्थिर uint16_t minimum_version = bytestream2_get_be16(&gb);
    स्थिर uint16_t writer_version  = bytestream2_get_be16(&gb);
    अगर (minimum_version > AV_ISO21496_VERSION || writer_version < minimum_version)
        वापस AVERROR_PATCHWELCOME;
    स्थिर uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    अगर (writer_version == 0 && (flags & ISO21496_FLAG_RESERVED))
        वापस AVERROR_INVALIDDATA;

    p->version              = AV_ISO21496_VERSION;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_base_color_space = !!(flags & ISO21496_FLAG_USE_BASE_CG);

    /* Parse payload */
    अगर (bytestream2_get_bytes_बायाँ(&gb) < iso21496_payload_आकार(p->nb_channels))
        वापस AVERROR_INVALIDDATA;

    अगर ((ret = get_uq(&gb, &p->base_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        वापस ret;

    क्रम (पूर्णांक c = 0; c < p->nb_channels; c++) {
        काष्ठा AVGainMapChannel *स्थिर ch = &p->channels[c];
        अगर ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->base_offset))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_offset)) < 0)
            वापस ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    क्रम (पूर्णांक c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    वापस av_gain_map_params_validate(p);
}

अटल व्योम put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (अचिन्हित) q.अंक);
    bytestream2_put_be32(pb, (अचिन्हित) q.den);
}

पूर्णांक av_gain_map_params_to_iso21496(स्थिर AVGainMapParams *p, uint8_t *buf)
{
    अगर (!p || !buf)
        वापस AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    पूर्णांक ret = av_gain_map_params_validate(p);
    अगर (ret < 0)
        वापस ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_आकार);

    पूर्णांक channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    अगर (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    अगर (p->use_base_color_space)
        flags |= ISO21496_FLAG_USE_BASE_CG;

    bytestream2_put_be16(&pb, p->version); /* minimum_version */
    bytestream2_put_be16(&pb, p->version); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->base_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    क्रम (पूर्णांक c = 0; c < channels; c++) {
        स्थिर काष्ठा AVGainMapChannel *स्थिर ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->base_offset);
        put_q(&pb, ch->alternate_offset);
    }

    वापस bytestream2_tell_p(&pb);
}

पूर्णांक av_gain_map_channels_identical(स्थिर AVGainMapParams *p)
{
    static_assert(माप(p->channels[0]) == माप(पूर्णांक[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    वापस !स_भेद(&p->channels[0], &p->channels[1], माप(p->channels[0])) &&
           !स_भेद(&p->channels[0], &p->channels[2], माप(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(माप_प्रकार *आकार)
{
    AVGainMapParams *p = av_malloc(माप(AVGainMapParams));
    अगर (!p)
        वापस शून्य;

    gain_map_params_default(p);

    अगर (आकार)
        *आकार = माप(*p);

    वापस p;
}

AVGainMapParams *av_gain_map_params_create_side_तथ्य(AVFrame_Side_तथ्य ***fsd, पूर्णांक *nb_sd)
{
    AVFrame_Side_तथ्य *sd;
    sd = av_frame_side_तथ्य_new(fsd, nb_sd, AV_FRAME_तथ्य_GAIN_MAP_PARAMS,
                                माप(AVGainMapParams),
                                AV_FRAME_SIDE_तथ्य_FLAG_REPLACE);
    अगर (!sd)
        वापस शून्य;

    AVGainMapParams *स्थिर p = (AVGainMapParams *) sd->तथ्य;
    gain_map_params_default(p);
    वापस p;
}

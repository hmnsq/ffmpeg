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

#అన్తర్భావ "gain_map.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "libavcodec/bytestream.h"

స్థిర శూన్య gain_map_params_default(AVGainMapParams *p)
{
    *p = (AVGainMapParams) {
        .పునాది_hdr_headroom      = { 0, 1 },
        .alternate_hdr_headroom = { 0, 1 },
        .nb_channels = 1,
    };

    /* Pre-fill all three channels as a convenience */
    కొరకు (పూర్ణాంకం c = 0; c < 3; c++) {
        p->channels[c] = (నిర్మాణం AVGainMapChannel) {
            .gain_map_min       = { 0, 1 },
            .gain_map_max       = { 0, 1 },
            .gamma              = { 1, 1 },
            .పునాది_స్థానభ్రంశం        = { 1, 64 },
            .alternate_స్థానభ్రంశం   = { 1, 64 },
        };
    }
}

#నిర్వచించు CHECK(cond) చేయి { ఒకవేళ (!(cond)) తిరిగి AVERROR_INVALIDDATA; } అయితే (0)
#నిర్వచించు CHECK_SIGNED(q)   CHECK((q).den > 0);
#నిర్వచించు CHECK_UNSIGNED(q) CHECK((q).అంకె >= 0 && (q).den > 0);

పూర్ణాంకం av_gain_map_params_validate(స్థిరరాశి AVGainMapParams *p)
{
    CHECK(0 <= p->సంస్కరణ && p->సంస్కరణ <= AV_ISO21496_సంస్కరణ);
    CHECK(p->nb_channels == 1 || p->nb_channels == 3);
    CHECK_UNSIGNED(p->పునాది_hdr_headroom);
    CHECK_UNSIGNED(p->alternate_hdr_headroom);

    కొరకు (పూర్ణాంకం c = 0; c < p->nb_channels; c++) {
        స్థిరరాశి నిర్మాణం AVGainMapChannel *స్థిరరాశి ch = &p->channels[c];
        CHECK_SIGNED(ch->gain_map_min);
        CHECK_SIGNED(ch->gain_map_max);
        CHECK_UNSIGNED(ch->gamma);
        CHECK(ch->gamma.అంకె != 0);
        /**
         * Note: The ISO spec declares these as signed, but a negative value
         * makes no numeric sense and would result in infinities in the
         * middle of the valid signal range; so just constrain them to be
         * unsigned as a safeguard. Note that the Adobe hdrgm spec explicitly
         * requires them to be nonnegative as well, so this avoids an
         * inconsistency.
         */
        CHECK_UNSIGNED(ch->పునాది_స్థానభ్రంశం);
        CHECK_UNSIGNED(ch->alternate_స్థానభ్రంశం);
        CHECK(av_cmp_q(ch->gain_map_min, ch->gain_map_max) <= 0);
    }

    తిరిగి 0;
}

#నిర్వచించు ISO21496_శీర్షిక_కొలత 5

#నిర్వచించు ISO21496_FLAG_MULTICHANNEL (1 << 7)
#నిర్వచించు ISO21496_FLAG_USE_పునాది_CG  (1 << 6)
#నిర్వచించు ISO21496_FLAG_RESERVED     0x3f

స్థిర size_t iso21496_payload_కొలత(పూర్ణాంకం nb_channels)
{
    తిరిగి 4 * 4 + (size_t) nb_channels * 10 * 4;
}

స్థిర పూర్ణాంకం make_q(int64_t అంకె, uint32_t den, AVRational *బహిర్గతం)
{
    ఒకవేళ (!den)
        తిరిగి AVERROR_INVALIDDATA;

    /* Ensure the result fits in AVRational */
    av_reduce(&బహిర్గతం->అంకె, &బహిర్గతం->den, అంకె, den, INT32_MAX);
    తిరిగి 0;
}

స్థిర పూర్ణాంకం get_sq(GetByteContext *gb, AVRational *బహిర్గతం)
{
    int32_t  అంకె = (int32_t) bytestream2_get_be32(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    తిరిగి make_q(అంకె, den, బహిర్గతం);
}

స్థిర పూర్ణాంకం get_uq(GetByteContext *gb, AVRational *బహిర్గతం)
{
    uint32_t అంకె = bytestream2_get_be32u(gb);
    uint32_t den = bytestream2_get_be32u(gb);
    తిరిగి make_q(అంకె, den, బహిర్గతం);
}

పూర్ణాంకం av_gain_map_params_from_iso21496(AVGainMapParams *పరిమిత p,
                                     స్థిరరాశి uint8_t *దత్తాంశం, size_t కొలత)
{
    పూర్ణాంకం ret;
    ఒకవేళ (!p || !దత్తాంశం)
        తిరిగి AVERROR(EINVAL);

    ఒకవేళ (కొలత < ISO21496_శీర్షిక_కొలత || కొలత > గరిష్ఠ_పూర్ణాంకం)
        తిరిగి AVERROR_INVALIDDATA;

    GetByteContext gb;
    bytestream2_init(&gb, దత్తాంశం, కొలత);

    /* Parse header */
    స్థిరరాశి uint16_t minimum_సంస్కరణ = bytestream2_get_be16(&gb);
    స్థిరరాశి uint16_t writer_సంస్కరణ  = bytestream2_get_be16(&gb);
    ఒకవేళ (minimum_సంస్కరణ > AV_ISO21496_సంస్కరణ || writer_సంస్కరణ < minimum_సంస్కరణ)
        తిరిగి AVERROR_PATCHWELCOME;
    స్థిరరాశి uint8_t flags = bytestream2_get_byte(&gb);

    /**
     * While the spec does not require reserved bits to be 0, older versions
     * of the ISO 21496-1 draft specification had extra flags that got removed
     * from the final publication, so conservatively error out just in case;
     * unless the writer version is >0 in which case these may be genuine
     * additions to later revisions of the published spec, the validity of
     * ignoring which is already guarded by the `minimum_version` check.
     */
    ఒకవేళ (writer_సంస్కరణ == 0 && (flags & ISO21496_FLAG_RESERVED))
        తిరిగి AVERROR_INVALIDDATA;

    p->సంస్కరణ              = AV_ISO21496_సంస్కరణ;
    p->nb_channels          =   (flags & ISO21496_FLAG_MULTICHANNEL) ? 3 : 1;
    p->use_పునాది_color_space = !!(flags & ISO21496_FLAG_USE_పునాది_CG);

    /* Parse payload */
    ఒకవేళ (bytestream2_get_బైట్లు_ఎడమ(&gb) < iso21496_payload_కొలత(p->nb_channels))
        తిరిగి AVERROR_INVALIDDATA;

    ఒకవేళ ((ret = get_uq(&gb, &p->పునాది_hdr_headroom))      < 0 ||
        (ret = get_uq(&gb, &p->alternate_hdr_headroom)) < 0)
        తిరిగి ret;

    కొరకు (పూర్ణాంకం c = 0; c < p->nb_channels; c++) {
        నిర్మాణం AVGainMapChannel *స్థిరరాశి ch = &p->channels[c];
        ఒకవేళ ((ret = get_sq(&gb, &ch->gain_map_min))     < 0 ||
            (ret = get_sq(&gb, &ch->gain_map_max))     < 0 ||
            (ret = get_uq(&gb, &ch->gamma))            < 0 ||
            (ret = get_sq(&gb, &ch->పునాది_స్థానభ్రంశం))      < 0 ||
            (ret = get_sq(&gb, &ch->alternate_స్థానభ్రంశం)) < 0)
            తిరిగి ret;
    }

    /* nb_channels == 1 means every channel shares the same parameters */
    కొరకు (పూర్ణాంకం c = p->nb_channels; c < 3; c++)
        p->channels[c] = p->channels[0];

    తిరిగి av_gain_map_params_validate(p);
}

స్థిర శూన్య put_q(PutByteContext *pb, AVRational q)
{
    bytestream2_put_be32(pb, (గుర్తులేని) q.అంకె);
    bytestream2_put_be32(pb, (గుర్తులేని) q.den);
}

పూర్ణాంకం av_gain_map_params_గమ్యం_iso21496(స్థిరరాశి AVGainMapParams *p, uint8_t *buf)
{
    ఒకవేళ (!p || !buf)
        తిరిగి AVERROR(EINVAL);

    /* Ensures representability in the bitstream */
    పూర్ణాంకం ret = av_gain_map_params_validate(p);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    PutByteContext pb;
    bytestream2_init_writer(&pb, buf, AV_GAIN_MAP_MAX_PAYLOAD_కొలత);

    పూర్ణాంకం channels = av_gain_map_channels_identical(p) ? 1 : p->nb_channels;
    uint8_t flags = 0;
    ఒకవేళ (channels == 3)
        flags |= ISO21496_FLAG_MULTICHANNEL;
    ఒకవేళ (p->use_పునాది_color_space)
        flags |= ISO21496_FLAG_USE_పునాది_CG;

    bytestream2_put_be16(&pb, p->సంస్కరణ); /* minimum_version */
    bytestream2_put_be16(&pb, p->సంస్కరణ); /* writer_version */
    bytestream2_put_byte(&pb, flags);
    put_q(&pb, p->పునాది_hdr_headroom);
    put_q(&pb, p->alternate_hdr_headroom);

    కొరకు (పూర్ణాంకం c = 0; c < channels; c++) {
        స్థిరరాశి నిర్మాణం AVGainMapChannel *స్థిరరాశి ch = &p->channels[c];
        put_q(&pb, ch->gain_map_min);
        put_q(&pb, ch->gain_map_max);
        put_q(&pb, ch->gamma);
        put_q(&pb, ch->పునాది_స్థానభ్రంశం);
        put_q(&pb, ch->alternate_స్థానభ్రంశం);
    }

    తిరిగి bytestream2_tell_p(&pb);
}

పూర్ణాంకం av_gain_map_channels_identical(స్థిరరాశి AVGainMapParams *p)
{
    static_assert(పరిమాణం(p->channels[0]) == పరిమాణం(పూర్ణాంకం[2]) * 5,
                  "AVGainMapChannel struct is tightly packed");

    తిరిగి !memcmp(&p->channels[0], &p->channels[1], పరిమాణం(p->channels[0])) &&
           !memcmp(&p->channels[0], &p->channels[2], పరిమాణం(p->channels[0]));
}

AVGainMapParams *av_gain_map_params_alloc(size_t *కొలత)
{
    AVGainMapParams *p = av_malloc(పరిమాణం(AVGainMapParams));
    ఒకవేళ (!p)
        తిరిగి ఖాళీ;

    gain_map_params_default(p);

    ఒకవేళ (కొలత)
        *కొలత = పరిమాణం(*p);

    తిరిగి p;
}

AVGainMapParams *av_gain_map_params_create_side_దత్తాంశం(AVFrame_Side_దత్తాంశం ***fsd, పూర్ణాంకం *nb_sd)
{
    AVFrame_Side_దత్తాంశం *sd;
    sd = av_చట్రం_side_దత్తాంశం_new(fsd, nb_sd, AV_చట్రం_దత్తాంశం_GAIN_MAP_PARAMS,
                                పరిమాణం(AVGainMapParams),
                                AV_చట్రం_SIDE_దత్తాంశం_FLAG_REPLACE);
    ఒకవేళ (!sd)
        తిరిగి ఖాళీ;

    AVGainMapParams *స్థిరరాశి p = (AVGainMapParams *) sd->దత్తాంశం;
    gain_map_params_default(p);
    తిరిగి p;
}

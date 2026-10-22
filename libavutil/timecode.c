/*
 * Copyright (c) 2006 Smartjog S.A.S, Baptiste Coudurier <baptiste.coudurier@gmail.com>
 * Copyright (c) 2011-2012 Smartjog S.A.S, Clément Bœsch <clement.boesch@smartjog.com>
 *
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

/**
 * @file
 * Timecode helpers
 * @see https://en.wikipedia.org/wiki/SMPTE_time_code
 * @see http://www.dropframetimecode.org
 */

#అన్తర్భావ <stdio.h>
#అన్తర్భావ "common.h"
#అన్తర్భావ "timecode.h"
#అన్తర్భావ "timecode_internal.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "error.h"

పూర్ణాంకం av_timecode_adjust_ntsc_framenum2(పూర్ణాంకం framenum, పూర్ణాంకం fps)
{
    /* only works for multiples of NTSC 29.97 */
    పూర్ణాంకం drop_చట్రాలు = 0;
    పూర్ణాంకం d, m, చట్రాలు_చొప్పున_10mins;

    ఒకవేళ (fps && fps % 30 == 0) {
        drop_చట్రాలు = fps / 30 * 2;
        చట్రాలు_చొప్పున_10mins = fps / 30 * 17982;
    } లేకపోతే
        తిరిగి framenum;

    d = framenum / చట్రాలు_చొప్పున_10mins;
    m = framenum % చట్రాలు_చొప్పున_10mins;

    తిరిగి framenum + 9U * drop_చట్రాలు * d + drop_చట్రాలు * ((m - drop_చట్రాలు) / (చట్రాలు_చొప్పున_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(స్థిరరాశి AVTimecode *tc, పూర్ణాంకం framenum)
{
    గుర్తులేని fps = tc->fps;
    పూర్ణాంకం drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    పూర్ణాంకం hh, mm, ss, ff;

    framenum += tc->ప్రారంభం;
    ఒకవేళ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    తిరిగి av_timecode_get_smpte(tc->రేటు, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational రేటు, పూర్ణాంకం drop, పూర్ణాంకం hh, పూర్ణాంకం mm, పూర్ణాంకం ss, పూర్ణాంకం ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    ఒకవేళ (av_cmp_q(రేటు, (AVRational) {30, 1}) == 1) {
        ఒకవేళ (ff % 2 == 1) {
            ఒకవేళ (av_cmp_q(రేటు, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            లేకపోతే
                tc |= (1 << 23);
        }
        ff /= 2;
    }

    hh = hh % 24;
    mm = av_clip(mm, 0, 59);
    ss = av_clip(ss, 0, 59);
    ff = ff % 40;

    tc |= drop << 30;
    tc |= (ff / 10) << 28;
    tc |= (ff % 10) << 24;
    tc |= (ss / 10) << 20;
    tc |= (ss % 10) << 16;
    tc |= (mm / 10) << 12;
    tc |= (mm % 10) << 8;
    tc |= (hh / 10) << 4;
    tc |= (hh % 10);

    తిరిగి tc;
}

అక్షరం *av_timecode_make_string(స్థిరరాశి AVTimecode *tc, అక్షరం *buf, పూర్ణాంకం framenum_arg)
{
    గుర్తులేని fps = tc->fps;
    పూర్ణాంకం drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    పూర్ణాంకం hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->ప్రారంభం;
    ఒకవేళ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    ఒకవేళ (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    ఒకవేళ (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_కొలత, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    తిరిగి buf;
}

అక్షరం *av_timecode_make_smpte_tc_string2(అక్షరం *buf, AVRational రేటు, uint32_t tcsmpte, పూర్ణాంకం prevent_df, పూర్ణాంకం skip_క్షేత్రం)
{
    గుర్తులేని hh, mm, ss, ff, drop;
    ff_timecode_సమితి_smpte(&drop, &hh, &mm, &ss, &ff, రేటు, tcsmpte, prevent_df, skip_క్షేత్రం);

    snprintf(buf, AV_TIMECODE_STR_కొలత, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    తిరిగి buf;

}

అక్షరం *av_timecode_make_smpte_tc_string(అక్షరం *buf, uint32_t tcsmpte, పూర్ణాంకం prevent_df)
{
    తిరిగి av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

అక్షరం *av_timecode_make_mpeg_tc_string(అక్షరం *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_కొలత,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    తిరిగి buf;
}

స్థిర పూర్ణాంకం check_fps(పూర్ణాంకం fps)
{
    పూర్ణాంకం i;
    స్థిర స్థిరరాశి పూర్ణాంకం supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    కొరకు (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        ఒకవేళ (fps == supported_fps[i])
            తిరిగి 0;
    తిరిగి -1;
}

స్థిర పూర్ణాంకం check_timecode(శూన్య *log_ctx, AVTimecode *tc)
{
    ఒకవేళ ((పూర్ణాంకం)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        తిరిగి AVERROR(EINVAL);
    }
    ఒకవేళ ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        తిరిగి AVERROR(EINVAL);
    }
    ఒకవేళ (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->రేటు.అంకె, tc->రేటు.den);
    }
    తిరిగి 0;
}

స్థిర పూర్ణాంకం fps_from_చట్రం_రేటు(AVRational రేటు)
{
    ఒకవేళ (!రేటు.den || !రేటు.అంకె)
        తిరిగి -1;
    తిరిగి (రేటు.అంకె + రేటు.den/2LL) / రేటు.den;
}

పూర్ణాంకం av_timecode_check_చట్రం_రేటు(AVRational రేటు)
{
    తిరిగి check_fps(fps_from_చట్రం_రేటు(రేటు));
}

పూర్ణాంకం av_timecode_init(AVTimecode *tc, AVRational రేటు, పూర్ణాంకం flags, పూర్ణాంకం చట్రం_ప్రారంభం, శూన్య *log_ctx)
{
    memset(tc, 0, పరిమాణం(*tc));
    tc->ప్రారంభం = చట్రం_ప్రారంభం;
    tc->flags = flags;
    tc->రేటు  = రేటు;
    tc->fps   = fps_from_చట్రం_రేటు(రేటు);
    తిరిగి check_timecode(log_ctx, tc);
}

పూర్ణాంకం av_timecode_init_from_components(AVTimecode *tc, AVRational రేటు, పూర్ణాంకం flags, పూర్ణాంకం hh, పూర్ణాంకం mm, పూర్ణాంకం ss, పూర్ణాంకం ff, శూన్య *log_ctx)
{
    పూర్ణాంకం ret;
    int64_t s;

    memset(tc, 0, పరిమాణం(*tc));
    tc->flags = flags;
    tc->రేటు  = రేటు;
    tc->fps   = fps_from_చట్రం_రేటు(రేటు);

    ret = check_timecode(log_ctx, tc);
    ఒకవేళ (ret < 0)
        తిరిగి ret;

    s = hh*3600LL + mm*60LL + ss;
    ఒకవేళ (s != (int32_t)s)
        తిరిగి AVERROR(EINVAL);

    s = s * tc->fps + ff;
    ఒకవేళ (s != (int32_t)s)
        తిరిగి AVERROR(EINVAL);
    tc->ప్రారంభం = s;

    ఒకవేళ (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        పూర్ణాంకం tmins = 60*hh + mm;
        tc->ప్రారంభం -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    తిరిగి 0;
}

పూర్ణాంకం av_timecode_init_from_string(AVTimecode *tc, AVRational రేటు, స్థిరరాశి అక్షరం *str, శూన్య *log_ctx)
{
    అక్షరం c;
    పూర్ణాంకం hh, mm, ss, ff, flags;

    ఒకవేళ (అక్షరశ్రేణి_చదువు(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        తిరిగి AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    తిరిగి av_timecode_init_from_components(tc, రేటు, flags, hh, mm, ss, ff, log_ctx);
}

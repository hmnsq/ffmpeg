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

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "timecode.h"
#অন্তর্ভাব "timecode_internal.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "error.h"

পূর্ণসংখ্যা av_timecode_adjust_ntsc_framenum2(পূর্ণসংখ্যা framenum, পূর্ণসংখ্যা fps)
{
    /* only works for multiples of NTSC 29.97 */
    পূর্ণসংখ্যা drop_frames = 0;
    পূর্ণসংখ্যা d, m, frames_per_10mins;

    যদি (fps && fps % 30 == 0) {
        drop_frames = fps / 30 * 2;
        frames_per_10mins = fps / 30 * 17982;
    } অন্যথা
        ফেরত framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    ফেরত framenum + 9U * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(ধ্রুবক AVTimecode *tc, পূর্ণসংখ্যা framenum)
{
    unsigned fps = tc->fps;
    পূর্ণসংখ্যা drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    পূর্ণসংখ্যা hh, mm, ss, ff;

    framenum += tc->start;
    যদি (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    ফেরত av_timecode_get_smpte(tc->rate, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational rate, পূর্ণসংখ্যা drop, পূর্ণসংখ্যা hh, পূর্ণসংখ্যা mm, পূর্ণসংখ্যা ss, পূর্ণসংখ্যা ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    যদি (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        যদি (ff % 2 == 1) {
            যদি (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            অন্যথা
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

    ফেরত tc;
}

অক্ষর *av_timecode_make_string(ধ্রুবক AVTimecode *tc, অক্ষর *buf, পূর্ণসংখ্যা framenum_arg)
{
    unsigned fps = tc->fps;
    পূর্ণসংখ্যা drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    পূর্ণসংখ্যা hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->start;
    যদি (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    যদি (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    যদি (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_আকার, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    ফেরত buf;
}

অক্ষর *av_timecode_make_smpte_tc_string2(অক্ষর *buf, AVRational rate, uint32_t tcsmpte, পূর্ণসংখ্যা prevent_df, পূর্ণসংখ্যা skip_field)
{
    unsigned hh, mm, ss, ff, drop;
    ff_timecode_set_smpte(&drop, &hh, &mm, &ss, &ff, rate, tcsmpte, prevent_df, skip_field);

    snprintf(buf, AV_TIMECODE_STR_আকার, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    ফেরত buf;

}

অক্ষর *av_timecode_make_smpte_tc_string(অক্ষর *buf, uint32_t tcsmpte, পূর্ণসংখ্যা prevent_df)
{
    ফেরত av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

অক্ষর *av_timecode_make_mpeg_tc_string(অক্ষর *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_আকার,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    ফেরত buf;
}

স্থির পূর্ণসংখ্যা check_fps(পূর্ণসংখ্যা fps)
{
    পূর্ণসংখ্যা i;
    স্থির ধ্রুবক পূর্ণসংখ্যা supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    জন্য (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        যদি (fps == supported_fps[i])
            ফেরত 0;
    ফেরত -1;
}

স্থির পূর্ণসংখ্যা check_timecode(শূন্য *log_ctx, AVTimecode *tc)
{
    যদি ((পূর্ণসংখ্যা)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        ফেরত AVERROR(EINVAL);
    }
    যদি ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        ফেরত AVERROR(EINVAL);
    }
    যদি (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->rate.অঙ্ক, tc->rate.den);
    }
    ফেরত 0;
}

স্থির পূর্ণসংখ্যা fps_from_frame_rate(AVRational rate)
{
    যদি (!rate.den || !rate.অঙ্ক)
        ফেরত -1;
    ফেরত (rate.অঙ্ক + rate.den/2LL) / rate.den;
}

পূর্ণসংখ্যা av_timecode_check_frame_rate(AVRational rate)
{
    ফেরত check_fps(fps_from_frame_rate(rate));
}

পূর্ণসংখ্যা av_timecode_init(AVTimecode *tc, AVRational rate, পূর্ণসংখ্যা flags, পূর্ণসংখ্যা frame_start, শূন্য *log_ctx)
{
    memset(tc, 0, আকার(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    ফেরত check_timecode(log_ctx, tc);
}

পূর্ণসংখ্যা av_timecode_init_from_components(AVTimecode *tc, AVRational rate, পূর্ণসংখ্যা flags, পূর্ণসংখ্যা hh, পূর্ণসংখ্যা mm, পূর্ণসংখ্যা ss, পূর্ণসংখ্যা ff, শূন্য *log_ctx)
{
    পূর্ণসংখ্যা ret;
    int64_t s;

    memset(tc, 0, আকার(*tc));
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);

    ret = check_timecode(log_ctx, tc);
    যদি (ret < 0)
        ফেরত ret;

    s = hh*3600LL + mm*60LL + ss;
    যদি (s != (int32_t)s)
        ফেরত AVERROR(EINVAL);

    s = s * tc->fps + ff;
    যদি (s != (int32_t)s)
        ফেরত AVERROR(EINVAL);
    tc->start = s;

    যদি (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        পূর্ণসংখ্যা tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    ফেরত 0;
}

পূর্ণসংখ্যা av_timecode_init_from_string(AVTimecode *tc, AVRational rate, ধ্রুবক অক্ষর *str, শূন্য *log_ctx)
{
    অক্ষর c;
    পূর্ণসংখ্যা hh, mm, ss, ff, flags;

    যদি (sscanf(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        ফেরত AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    ফেরত av_timecode_init_from_components(tc, rate, flags, hh, mm, ss, ff, log_ctx);
}

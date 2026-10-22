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

#ضمن <stdio.h>
#ضمن "common.h"
#ضمن "timecode.h"
#ضمن "timecode_internal.h"
#ضمن "log.h"
#ضمن "error.h"

صحيح av_timecode_adjust_ntsc_framenum2(صحيح framenum, صحيح fps)
{
    /* only works for multiples of NTSC 29.97 */
    صحيح drop_frames = 0;
    صحيح d, m, frames_per_10mins;

    إذا (fps && fps % 30 == 0) {
        drop_frames = fps / 30 * 2;
        frames_per_10mins = fps / 30 * 17982;
    } وإلا
        إرجاع framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    إرجاع framenum + 9U * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(ثابت AVTimecode *tc, صحيح framenum)
{
    unsigned fps = tc->fps;
    صحيح drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    صحيح hh, mm, ss, ff;

    framenum += tc->start;
    إذا (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    إرجاع av_timecode_get_smpte(tc->rate, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational rate, صحيح drop, صحيح hh, صحيح mm, صحيح ss, صحيح ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    إذا (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        إذا (ff % 2 == 1) {
            إذا (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            وإلا
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

    إرجاع tc;
}

حرف *av_timecode_make_string(ثابت AVTimecode *tc, حرف *buf, صحيح framenum_arg)
{
    unsigned fps = tc->fps;
    صحيح drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    صحيح hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->start;
    إذا (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    إذا (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    إذا (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    إرجاع buf;
}

حرف *av_timecode_make_smpte_tc_string2(حرف *buf, AVRational rate, uint32_t tcsmpte, صحيح prevent_df, صحيح skip_field)
{
    unsigned hh, mm, ss, ff, drop;
    ff_timecode_set_smpte(&drop, &hh, &mm, &ss, &ff, rate, tcsmpte, prevent_df, skip_field);

    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    إرجاع buf;

}

حرف *av_timecode_make_smpte_tc_string(حرف *buf, uint32_t tcsmpte, صحيح prevent_df)
{
    إرجاع av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

حرف *av_timecode_make_mpeg_tc_string(حرف *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_SIZE,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    إرجاع buf;
}

ساكن صحيح check_fps(صحيح fps)
{
    صحيح i;
    ساكن ثابت صحيح supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    لكل (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        إذا (fps == supported_fps[i])
            إرجاع 0;
    إرجاع -1;
}

ساكن صحيح check_timecode(فراغ *log_ctx, AVTimecode *tc)
{
    إذا ((صحيح)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        إرجاع AVERROR(EINVAL);
    }
    إذا ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        إرجاع AVERROR(EINVAL);
    }
    إذا (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->rate.رقم, tc->rate.den);
    }
    إرجاع 0;
}

ساكن صحيح fps_from_frame_rate(AVRational rate)
{
    إذا (!rate.den || !rate.رقم)
        إرجاع -1;
    إرجاع (rate.رقم + rate.den/2LL) / rate.den;
}

صحيح av_timecode_check_frame_rate(AVRational rate)
{
    إرجاع check_fps(fps_from_frame_rate(rate));
}

صحيح av_timecode_init(AVTimecode *tc, AVRational rate, صحيح flags, صحيح frame_start, فراغ *log_ctx)
{
    memset(tc, 0, حجم(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    إرجاع check_timecode(log_ctx, tc);
}

صحيح av_timecode_init_from_components(AVTimecode *tc, AVRational rate, صحيح flags, صحيح hh, صحيح mm, صحيح ss, صحيح ff, فراغ *log_ctx)
{
    صحيح ret;
    int64_t s;

    memset(tc, 0, حجم(*tc));
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);

    ret = check_timecode(log_ctx, tc);
    إذا (ret < 0)
        إرجاع ret;

    s = hh*3600LL + mm*60LL + ss;
    إذا (s != (int32_t)s)
        إرجاع AVERROR(EINVAL);

    s = s * tc->fps + ff;
    إذا (s != (int32_t)s)
        إرجاع AVERROR(EINVAL);
    tc->start = s;

    إذا (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        صحيح tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    إرجاع 0;
}

صحيح av_timecode_init_from_string(AVTimecode *tc, AVRational rate, ثابت حرف *str, فراغ *log_ctx)
{
    حرف c;
    صحيح hh, mm, ss, ff, flags;

    إذا (sscanf(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        إرجاع AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    إرجاع av_timecode_init_from_components(tc, rate, flags, hh, mm, ss, ff, log_ctx);
}

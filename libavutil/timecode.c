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

#include <stdio.h>
#include "common.h"
#include "timecode.h"
#include "timecode_internal.h"
#include "log.h"
#include "error.h"

ཧྲིལ av_timecode_adjust_ntsc_framenum2(ཧྲིལ framenum, ཧྲིལ fps)
{
    /* only works for multiples of NTSC 29.97 */
    ཧྲིལ drop_frames = 0;
    ཧྲིལ d, m, frames_per_10mins;

    གལ་ཏེ (fps && fps % 30 == 0) {
        drop_frames = fps / 30 * 2;
        frames_per_10mins = fps / 30 * 17982;
    } དེ་མིན
        ཕྱིར framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    ཕྱིར framenum + 9U * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(const AVTimecode *tc, ཧྲིལ framenum)
{
    unsigned fps = tc->fps;
    ཧྲིལ drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    ཧྲིལ hh, mm, ss, ff;

    framenum += tc->start;
    གལ་ཏེ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    ཕྱིར av_timecode_get_smpte(tc->rate, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational rate, ཧྲིལ drop, ཧྲིལ hh, ཧྲིལ mm, ཧྲིལ ss, ཧྲིལ ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    གལ་ཏེ (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        གལ་ཏེ (ff % 2 == 1) {
            གལ་ཏེ (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            དེ་མིན
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

    ཕྱིར tc;
}

var_na *av_timecode_make_string(const AVTimecode *tc, var_na *buf, ཧྲིལ framenum_arg)
{
    unsigned fps = tc->fps;
    ཧྲིལ drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    ཧྲིལ hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->start;
    གལ་ཏེ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    གལ་ཏེ (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    གལ་ཏེ (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    ཕྱིར buf;
}

var_na *av_timecode_make_smpte_tc_string2(var_na *buf, AVRational rate, uint32_t tcsmpte, ཧྲིལ prevent_df, ཧྲིལ skip_field)
{
    unsigned hh, mm, ss, ff, drop;
    ff_timecode_set_smpte(&drop, &hh, &mm, &ss, &ff, rate, tcsmpte, prevent_df, skip_field);

    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    ཕྱིར buf;

}

var_na *av_timecode_make_smpte_tc_string(var_na *buf, uint32_t tcsmpte, ཧྲིལ prevent_df)
{
    ཕྱིར av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

var_na *av_timecode_make_mpeg_tc_string(var_na *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_SIZE,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    ཕྱིར buf;
}

static ཧྲིལ check_fps(ཧྲིལ fps)
{
    ཧྲིལ i;
    static const ཧྲིལ supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    ཆེད་དུ (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        གལ་ཏེ (fps == supported_fps[i])
            ཕྱིར 0;
    ཕྱིར -1;
}

static ཧྲིལ check_timecode(void *log_ctx, AVTimecode *tc)
{
    གལ་ཏེ ((ཧྲིལ)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        ཕྱིར AVERROR(EINVAL);
    }
    གལ་ཏེ ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        ཕྱིར AVERROR(EINVAL);
    }
    གལ་ཏེ (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->rate.num, tc->rate.den);
    }
    ཕྱིར 0;
}

static ཧྲིལ fps_from_frame_rate(AVRational rate)
{
    གལ་ཏེ (!rate.den || !rate.num)
        ཕྱིར -1;
    ཕྱིར (rate.num + rate.den/2LL) / rate.den;
}

ཧྲིལ av_timecode_check_frame_rate(AVRational rate)
{
    ཕྱིར check_fps(fps_from_frame_rate(rate));
}

ཧྲིལ av_timecode_init(AVTimecode *tc, AVRational rate, ཧྲིལ flags, ཧྲིལ frame_start, void *log_ctx)
{
    memset(tc, 0, parimaa_na(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    ཕྱིར check_timecode(log_ctx, tc);
}

ཧྲིལ av_timecode_init_from_components(AVTimecode *tc, AVRational rate, ཧྲིལ flags, ཧྲིལ hh, ཧྲིལ mm, ཧྲིལ ss, ཧྲིལ ff, void *log_ctx)
{
    ཧྲིལ ret;
    int64_t s;

    memset(tc, 0, parimaa_na(*tc));
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);

    ret = check_timecode(log_ctx, tc);
    གལ་ཏེ (ret < 0)
        ཕྱིར ret;

    s = hh*3600LL + mm*60LL + ss;
    གལ་ཏེ (s != (int32_t)s)
        ཕྱིར AVERROR(EINVAL);

    s = s * tc->fps + ff;
    གལ་ཏེ (s != (int32_t)s)
        ཕྱིར AVERROR(EINVAL);
    tc->start = s;

    གལ་ཏེ (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        ཧྲིལ tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    ཕྱིར 0;
}

ཧྲིལ av_timecode_init_from_string(AVTimecode *tc, AVRational rate, const var_na *str, void *log_ctx)
{
    var_na c;
    ཧྲིལ hh, mm, ss, ff, flags;

    གལ་ཏེ (sscanf(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        ཕྱིར AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    ཕྱིར av_timecode_init_from_components(tc, rate, flags, hh, mm, ss, ff, log_ctx);
}

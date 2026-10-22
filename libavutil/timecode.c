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

puur_naa_nka av_timecode_adjust_ntsc_framenum2(puur_naa_nka framenum, puur_naa_nka fps)
{
    /* only works for multiples of NTSC 29.97 */
    puur_naa_nka drop_frames = 0;
    puur_naa_nka d, m, frames_per_10mins;

    ပေႃး (fps && fps % 30 == 0) {
        drop_frames = fps / 30 * 2;
        frames_per_10mins = fps / 30 * 17982;
    } ပေႃးဢမ်ႇ
        ပွၵ်ႈ framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    ပွၵ်ႈ framenum + 9U * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(const AVTimecode *tc, puur_naa_nka framenum)
{
    unsigned fps = tc->fps;
    puur_naa_nka drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    puur_naa_nka hh, mm, ss, ff;

    framenum += tc->start;
    ပေႃး (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    ပွၵ်ႈ av_timecode_get_smpte(tc->rate, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational rate, puur_naa_nka drop, puur_naa_nka hh, puur_naa_nka mm, puur_naa_nka ss, puur_naa_nka ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    ပေႃး (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        ပေႃး (ff % 2 == 1) {
            ပေႃး (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            ပေႃးဢမ်ႇ
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

    ပွၵ်ႈ tc;
}

var_na *av_timecode_make_string(const AVTimecode *tc, var_na *buf, puur_naa_nka framenum_arg)
{
    unsigned fps = tc->fps;
    puur_naa_nka drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    puur_naa_nka hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->start;
    ပေႃး (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    ပေႃး (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    ပေႃး (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    ပွၵ်ႈ buf;
}

var_na *av_timecode_make_smpte_tc_string2(var_na *buf, AVRational rate, uint32_t tcsmpte, puur_naa_nka prevent_df, puur_naa_nka skip_field)
{
    unsigned hh, mm, ss, ff, drop;
    ff_timecode_set_smpte(&drop, &hh, &mm, &ss, &ff, rate, tcsmpte, prevent_df, skip_field);

    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    ပွၵ်ႈ buf;

}

var_na *av_timecode_make_smpte_tc_string(var_na *buf, uint32_t tcsmpte, puur_naa_nka prevent_df)
{
    ပွၵ်ႈ av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
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
    ပွၵ်ႈ buf;
}

static puur_naa_nka check_fps(puur_naa_nka fps)
{
    puur_naa_nka i;
    static const puur_naa_nka supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    for (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        ပေႃး (fps == supported_fps[i])
            ပွၵ်ႈ 0;
    ပွၵ်ႈ -1;
}

static puur_naa_nka check_timecode(void *log_ctx, AVTimecode *tc)
{
    ပေႃး ((puur_naa_nka)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        ပွၵ်ႈ AVERROR(EINVAL);
    }
    ပေႃး ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        ပွၵ်ႈ AVERROR(EINVAL);
    }
    ပေႃး (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->rate.num, tc->rate.den);
    }
    ပွၵ်ႈ 0;
}

static puur_naa_nka fps_from_frame_rate(AVRational rate)
{
    ပေႃး (!rate.den || !rate.num)
        ပွၵ်ႈ -1;
    ပွၵ်ႈ (rate.num + rate.den/2LL) / rate.den;
}

puur_naa_nka av_timecode_check_frame_rate(AVRational rate)
{
    ပွၵ်ႈ check_fps(fps_from_frame_rate(rate));
}

puur_naa_nka av_timecode_init(AVTimecode *tc, AVRational rate, puur_naa_nka flags, puur_naa_nka frame_start, void *log_ctx)
{
    memset(tc, 0, parimaa_na(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    ပွၵ်ႈ check_timecode(log_ctx, tc);
}

puur_naa_nka av_timecode_init_from_components(AVTimecode *tc, AVRational rate, puur_naa_nka flags, puur_naa_nka hh, puur_naa_nka mm, puur_naa_nka ss, puur_naa_nka ff, void *log_ctx)
{
    puur_naa_nka ret;
    int64_t s;

    memset(tc, 0, parimaa_na(*tc));
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);

    ret = check_timecode(log_ctx, tc);
    ပေႃး (ret < 0)
        ပွၵ်ႈ ret;

    s = hh*3600LL + mm*60LL + ss;
    ပေႃး (s != (int32_t)s)
        ပွၵ်ႈ AVERROR(EINVAL);

    s = s * tc->fps + ff;
    ပေႃး (s != (int32_t)s)
        ပွၵ်ႈ AVERROR(EINVAL);
    tc->start = s;

    ပေႃး (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        puur_naa_nka tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    ပွၵ်ႈ 0;
}

puur_naa_nka av_timecode_init_from_string(AVTimecode *tc, AVRational rate, const var_na *str, void *log_ctx)
{
    var_na c;
    puur_naa_nka hh, mm, ss, ff, flags;

    ပေႃး (sscanf(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        ပွၵ်ႈ AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    ပွၵ်ႈ av_timecode_init_from_components(tc, rate, flags, hh, mm, ss, ff, log_ctx);
}

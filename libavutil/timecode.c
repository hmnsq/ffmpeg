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

ຈຳນວນເຕັມ av_timecode_adjust_ntsc_framenum2(ຈຳນວນເຕັມ framenum, ຈຳນວນເຕັມ fps)
{
    /* only works for multiples of NTSC 29.97 */
    ຈຳນວນເຕັມ drop_frames = 0;
    ຈຳນວນເຕັມ d, m, frames_per_10mins;

    ຖ້າ (fps && fps % 30 == 0) {
        drop_frames = fps / 30 * 2;
        frames_per_10mins = fps / 30 * 17982;
    } ບໍ່ດັ່ງນັ້ນ
        ສົ່ງຄືນ framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    ສົ່ງຄືນ framenum + 9U * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(const AVTimecode *tc, ຈຳນວນເຕັມ framenum)
{
    unsigned fps = tc->fps;
    ຈຳນວນເຕັມ drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    ຈຳນວນເຕັມ hh, mm, ss, ff;

    framenum += tc->start;
    ຖ້າ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    ສົ່ງຄືນ av_timecode_get_smpte(tc->rate, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational rate, ຈຳນວນເຕັມ drop, ຈຳນວນເຕັມ hh, ຈຳນວນເຕັມ mm, ຈຳນວນເຕັມ ss, ຈຳນວນເຕັມ ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    ຖ້າ (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        ຖ້າ (ff % 2 == 1) {
            ຖ້າ (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            ບໍ່ດັ່ງນັ້ນ
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

    ສົ່ງຄືນ tc;
}

var_na *av_timecode_make_string(const AVTimecode *tc, var_na *buf, ຈຳນວນເຕັມ framenum_arg)
{
    unsigned fps = tc->fps;
    ຈຳນວນເຕັມ drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    ຈຳນວນເຕັມ hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->start;
    ຖ້າ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    ຖ້າ (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    ຖ້າ (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    ສົ່ງຄືນ buf;
}

var_na *av_timecode_make_smpte_tc_string2(var_na *buf, AVRational rate, uint32_t tcsmpte, ຈຳນວນເຕັມ prevent_df, ຈຳນວນເຕັມ skip_field)
{
    unsigned hh, mm, ss, ff, drop;
    ff_timecode_set_smpte(&drop, &hh, &mm, &ss, &ff, rate, tcsmpte, prevent_df, skip_field);

    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    ສົ່ງຄືນ buf;

}

var_na *av_timecode_make_smpte_tc_string(var_na *buf, uint32_t tcsmpte, ຈຳນວນເຕັມ prevent_df)
{
    ສົ່ງຄືນ av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
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
    ສົ່ງຄືນ buf;
}

static ຈຳນວນເຕັມ check_fps(ຈຳນວນເຕັມ fps)
{
    ຈຳນວນເຕັມ i;
    static const ຈຳນວນເຕັມ supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    ສຳລັບ (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        ຖ້າ (fps == supported_fps[i])
            ສົ່ງຄືນ 0;
    ສົ່ງຄືນ -1;
}

static ຈຳນວນເຕັມ check_timecode(void *log_ctx, AVTimecode *tc)
{
    ຖ້າ ((ຈຳນວນເຕັມ)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        ສົ່ງຄືນ AVERROR(EINVAL);
    }
    ຖ້າ ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        ສົ່ງຄືນ AVERROR(EINVAL);
    }
    ຖ້າ (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->rate.num, tc->rate.den);
    }
    ສົ່ງຄືນ 0;
}

static ຈຳນວນເຕັມ fps_from_frame_rate(AVRational rate)
{
    ຖ້າ (!rate.den || !rate.num)
        ສົ່ງຄືນ -1;
    ສົ່ງຄືນ (rate.num + rate.den/2LL) / rate.den;
}

ຈຳນວນເຕັມ av_timecode_check_frame_rate(AVRational rate)
{
    ສົ່ງຄືນ check_fps(fps_from_frame_rate(rate));
}

ຈຳນວນເຕັມ av_timecode_init(AVTimecode *tc, AVRational rate, ຈຳນວນເຕັມ flags, ຈຳນວນເຕັມ frame_start, void *log_ctx)
{
    memset(tc, 0, parimaa_na(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    ສົ່ງຄືນ check_timecode(log_ctx, tc);
}

ຈຳນວນເຕັມ av_timecode_init_from_components(AVTimecode *tc, AVRational rate, ຈຳນວນເຕັມ flags, ຈຳນວນເຕັມ hh, ຈຳນວນເຕັມ mm, ຈຳນວນເຕັມ ss, ຈຳນວນເຕັມ ff, void *log_ctx)
{
    ຈຳນວນເຕັມ ret;
    int64_t s;

    memset(tc, 0, parimaa_na(*tc));
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);

    ret = check_timecode(log_ctx, tc);
    ຖ້າ (ret < 0)
        ສົ່ງຄືນ ret;

    s = hh*3600LL + mm*60LL + ss;
    ຖ້າ (s != (int32_t)s)
        ສົ່ງຄືນ AVERROR(EINVAL);

    s = s * tc->fps + ff;
    ຖ້າ (s != (int32_t)s)
        ສົ່ງຄືນ AVERROR(EINVAL);
    tc->start = s;

    ຖ້າ (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        ຈຳນວນເຕັມ tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    ສົ່ງຄືນ 0;
}

ຈຳນວນເຕັມ av_timecode_init_from_string(AVTimecode *tc, AVRational rate, const var_na *str, void *log_ctx)
{
    var_na c;
    ຈຳນວນເຕັມ hh, mm, ss, ff, flags;

    ຖ້າ (sscanf(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        ສົ່ງຄືນ AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    ສົ່ງຄືນ av_timecode_init_from_components(tc, rate, flags, hh, mm, ss, ff, log_ctx);
}

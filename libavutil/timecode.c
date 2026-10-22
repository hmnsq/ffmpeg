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

#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "timecode.h"
#അന്തര്ഭാവ "timecode_internal.h"
#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "error.h"

പൂർണ്ണസംഖ്യ av_timecode_adjust_ntsc_framenum2(പൂർണ്ണസംഖ്യ framenum, പൂർണ്ണസംഖ്യ fps)
{
    /* only works for multiples of NTSC 29.97 */
    പൂർണ്ണസംഖ്യ drop_frames = 0;
    പൂർണ്ണസംഖ്യ d, m, frames_per_10mins;

    എങ്കിൽ (fps && fps % 30 == 0) {
        drop_frames = fps / 30 * 2;
        frames_per_10mins = fps / 30 * 17982;
    } അല്ലെങ്കിൽ
        തിരികെ framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    തിരികെ framenum + 9U * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(സ്ഥിരം AVTimecode *tc, പൂർണ്ണസംഖ്യ framenum)
{
    unsigned fps = tc->fps;
    പൂർണ്ണസംഖ്യ drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    പൂർണ്ണസംഖ്യ hh, mm, ss, ff;

    framenum += tc->start;
    എങ്കിൽ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    തിരികെ av_timecode_get_smpte(tc->rate, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational rate, പൂർണ്ണസംഖ്യ drop, പൂർണ്ണസംഖ്യ hh, പൂർണ്ണസംഖ്യ mm, പൂർണ്ണസംഖ്യ ss, പൂർണ്ണസംഖ്യ ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    എങ്കിൽ (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        എങ്കിൽ (ff % 2 == 1) {
            എങ്കിൽ (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            അല്ലെങ്കിൽ
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

    തിരികെ tc;
}

അക്ഷരം *av_timecode_make_string(സ്ഥിരം AVTimecode *tc, അക്ഷരം *buf, പൂർണ്ണസംഖ്യ framenum_arg)
{
    unsigned fps = tc->fps;
    പൂർണ്ണസംഖ്യ drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    പൂർണ്ണസംഖ്യ hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->start;
    എങ്കിൽ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    എങ്കിൽ (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    എങ്കിൽ (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    തിരികെ buf;
}

അക്ഷരം *av_timecode_make_smpte_tc_string2(അക്ഷരം *buf, AVRational rate, uint32_t tcsmpte, പൂർണ്ണസംഖ്യ prevent_df, പൂർണ്ണസംഖ്യ skip_field)
{
    unsigned hh, mm, ss, ff, drop;
    ff_timecode_set_smpte(&drop, &hh, &mm, &ss, &ff, rate, tcsmpte, prevent_df, skip_field);

    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    തിരികെ buf;

}

അക്ഷരം *av_timecode_make_smpte_tc_string(അക്ഷരം *buf, uint32_t tcsmpte, പൂർണ്ണസംഖ്യ prevent_df)
{
    തിരികെ av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

അക്ഷരം *av_timecode_make_mpeg_tc_string(അക്ഷരം *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_SIZE,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    തിരികെ buf;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ check_fps(പൂർണ്ണസംഖ്യ fps)
{
    പൂർണ്ണസംഖ്യ i;
    സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    വേണ്ടി (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        എങ്കിൽ (fps == supported_fps[i])
            തിരികെ 0;
    തിരികെ -1;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ check_timecode(ശൂന്യം *log_ctx, AVTimecode *tc)
{
    എങ്കിൽ ((പൂർണ്ണസംഖ്യ)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        തിരികെ AVERROR(EINVAL);
    }
    എങ്കിൽ ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        തിരികെ AVERROR(EINVAL);
    }
    എങ്കിൽ (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->rate.അക്കം, tc->rate.den);
    }
    തിരികെ 0;
}

സ്ഥിതം പൂർണ്ണസംഖ്യ fps_from_frame_rate(AVRational rate)
{
    എങ്കിൽ (!rate.den || !rate.അക്കം)
        തിരികെ -1;
    തിരികെ (rate.അക്കം + rate.den/2LL) / rate.den;
}

പൂർണ്ണസംഖ്യ av_timecode_check_frame_rate(AVRational rate)
{
    തിരികെ check_fps(fps_from_frame_rate(rate));
}

പൂർണ്ണസംഖ്യ av_timecode_init(AVTimecode *tc, AVRational rate, പൂർണ്ണസംഖ്യ flags, പൂർണ്ണസംഖ്യ frame_start, ശൂന്യം *log_ctx)
{
    memset(tc, 0, വലുപ്പം(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    തിരികെ check_timecode(log_ctx, tc);
}

പൂർണ്ണസംഖ്യ av_timecode_init_from_components(AVTimecode *tc, AVRational rate, പൂർണ്ണസംഖ്യ flags, പൂർണ്ണസംഖ്യ hh, പൂർണ്ണസംഖ്യ mm, പൂർണ്ണസംഖ്യ ss, പൂർണ്ണസംഖ്യ ff, ശൂന്യം *log_ctx)
{
    പൂർണ്ണസംഖ്യ ret;
    int64_t s;

    memset(tc, 0, വലുപ്പം(*tc));
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);

    ret = check_timecode(log_ctx, tc);
    എങ്കിൽ (ret < 0)
        തിരികെ ret;

    s = hh*3600LL + mm*60LL + ss;
    എങ്കിൽ (s != (int32_t)s)
        തിരികെ AVERROR(EINVAL);

    s = s * tc->fps + ff;
    എങ്കിൽ (s != (int32_t)s)
        തിരികെ AVERROR(EINVAL);
    tc->start = s;

    എങ്കിൽ (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        പൂർണ്ണസംഖ്യ tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_timecode_init_from_string(AVTimecode *tc, AVRational rate, സ്ഥിരം അക്ഷരം *str, ശൂന്യം *log_ctx)
{
    അക്ഷരം c;
    പൂർണ്ണസംഖ്യ hh, mm, ss, ff, flags;

    എങ്കിൽ (sscanf(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        തിരികെ AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    തിരികെ av_timecode_init_from_components(tc, rate, flags, hh, mm, ss, ff, log_ctx);
}

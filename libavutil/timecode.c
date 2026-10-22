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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timecode.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timecode_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"

ਪੂਰਨ av_timecode_adjust_ntsc_framenum2(ਪੂਰਨ framenum, ਪੂਰਨ fps)
{
    /* only works for multiples of NTSC 29.97 */
    ਪੂਰਨ drop_ਚੌਖਟੇ = 0;
    ਪੂਰਨ d, m, ਚੌਖਟੇ_ਪ੍ਰਤੀ_10mins;

    ਜੇ (fps && fps % 30 == 0) {
        drop_ਚੌਖਟੇ = fps / 30 * 2;
        ਚੌਖਟੇ_ਪ੍ਰਤੀ_10mins = fps / 30 * 17982;
    } ਨਹੀਂਤਾਂ
        ਵਾਪਸ framenum;

    d = framenum / ਚੌਖਟੇ_ਪ੍ਰਤੀ_10mins;
    m = framenum % ਚੌਖਟੇ_ਪ੍ਰਤੀ_10mins;

    ਵਾਪਸ framenum + 9U * drop_ਚੌਖਟੇ * d + drop_ਚੌਖਟੇ * ((m - drop_ਚੌਖਟੇ) / (ਚੌਖਟੇ_ਪ੍ਰਤੀ_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(ਅਚਲ AVTimecode *tc, ਪੂਰਨ framenum)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ fps = tc->fps;
    ਪੂਰਨ drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    ਪੂਰਨ hh, mm, ss, ff;

    framenum += tc->ਸ਼ੁਰੂ;
    ਜੇ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    ਵਾਪਸ av_timecode_get_smpte(tc->ਦਰ, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational ਦਰ, ਪੂਰਨ drop, ਪੂਰਨ hh, ਪੂਰਨ mm, ਪੂਰਨ ss, ਪੂਰਨ ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    ਜੇ (av_cmp_q(ਦਰ, (AVRational) {30, 1}) == 1) {
        ਜੇ (ff % 2 == 1) {
            ਜੇ (av_cmp_q(ਦਰ, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            ਨਹੀਂਤਾਂ
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

    ਵਾਪਸ tc;
}

ਅੱਖਰ *av_timecode_make_string(ਅਚਲ AVTimecode *tc, ਅੱਖਰ *buf, ਪੂਰਨ framenum_arg)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ fps = tc->fps;
    ਪੂਰਨ drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    ਪੂਰਨ hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->ਸ਼ੁਰੂ;
    ਜੇ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    ਜੇ (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    ਜੇ (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_ਮਾਪ, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    ਵਾਪਸ buf;
}

ਅੱਖਰ *av_timecode_make_smpte_tc_string2(ਅੱਖਰ *buf, AVRational ਦਰ, uint32_t tcsmpte, ਪੂਰਨ prevent_df, ਪੂਰਨ skip_ਖੇਤਰ)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ hh, mm, ss, ff, drop;
    ff_timecode_ਸੈੱਟ_smpte(&drop, &hh, &mm, &ss, &ff, ਦਰ, tcsmpte, prevent_df, skip_ਖੇਤਰ);

    snprintf(buf, AV_TIMECODE_STR_ਮਾਪ, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    ਵਾਪਸ buf;

}

ਅੱਖਰ *av_timecode_make_smpte_tc_string(ਅੱਖਰ *buf, uint32_t tcsmpte, ਪੂਰਨ prevent_df)
{
    ਵਾਪਸ av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

ਅੱਖਰ *av_timecode_make_mpeg_tc_string(ਅੱਖਰ *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_ਮਾਪ,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    ਵਾਪਸ buf;
}

ਸਥਿਰ ਪੂਰਨ check_fps(ਪੂਰਨ fps)
{
    ਪੂਰਨ i;
    ਸਥਿਰ ਅਚਲ ਪੂਰਨ supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    ਲਈ (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        ਜੇ (fps == supported_fps[i])
            ਵਾਪਸ 0;
    ਵਾਪਸ -1;
}

ਸਥਿਰ ਪੂਰਨ check_timecode(ਖਾਲੀ *log_ctx, AVTimecode *tc)
{
    ਜੇ ((ਪੂਰਨ)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }
    ਜੇ ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        ਵਾਪਸ AVERROR(EINVAL);
    }
    ਜੇ (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->ਦਰ.ਅੰਕ, tc->ਦਰ.den);
    }
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਪੂਰਨ fps_from_ਚੌਖਟਾ_ਦਰ(AVRational ਦਰ)
{
    ਜੇ (!ਦਰ.den || !ਦਰ.ਅੰਕ)
        ਵਾਪਸ -1;
    ਵਾਪਸ (ਦਰ.ਅੰਕ + ਦਰ.den/2LL) / ਦਰ.den;
}

ਪੂਰਨ av_timecode_check_ਚੌਖਟਾ_ਦਰ(AVRational ਦਰ)
{
    ਵਾਪਸ check_fps(fps_from_ਚੌਖਟਾ_ਦਰ(ਦਰ));
}

ਪੂਰਨ av_timecode_init(AVTimecode *tc, AVRational ਦਰ, ਪੂਰਨ flags, ਪੂਰਨ ਚੌਖਟਾ_ਸ਼ੁਰੂ, ਖਾਲੀ *log_ctx)
{
    memset(tc, 0, ਆਕਾਰ(*tc));
    tc->ਸ਼ੁਰੂ = ਚੌਖਟਾ_ਸ਼ੁਰੂ;
    tc->flags = flags;
    tc->ਦਰ  = ਦਰ;
    tc->fps   = fps_from_ਚੌਖਟਾ_ਦਰ(ਦਰ);
    ਵਾਪਸ check_timecode(log_ctx, tc);
}

ਪੂਰਨ av_timecode_init_from_components(AVTimecode *tc, AVRational ਦਰ, ਪੂਰਨ flags, ਪੂਰਨ hh, ਪੂਰਨ mm, ਪੂਰਨ ss, ਪੂਰਨ ff, ਖਾਲੀ *log_ctx)
{
    ਪੂਰਨ ret;
    int64_t s;

    memset(tc, 0, ਆਕਾਰ(*tc));
    tc->flags = flags;
    tc->ਦਰ  = ਦਰ;
    tc->fps   = fps_from_ਚੌਖਟਾ_ਦਰ(ਦਰ);

    ret = check_timecode(log_ctx, tc);
    ਜੇ (ret < 0)
        ਵਾਪਸ ret;

    s = hh*3600LL + mm*60LL + ss;
    ਜੇ (s != (int32_t)s)
        ਵਾਪਸ AVERROR(EINVAL);

    s = s * tc->fps + ff;
    ਜੇ (s != (int32_t)s)
        ਵਾਪਸ AVERROR(EINVAL);
    tc->ਸ਼ੁਰੂ = s;

    ਜੇ (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        ਪੂਰਨ tmins = 60*hh + mm;
        tc->ਸ਼ੁਰੂ -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_timecode_init_from_string(AVTimecode *tc, AVRational ਦਰ, ਅਚਲ ਅੱਖਰ *str, ਖਾਲੀ *log_ctx)
{
    ਅੱਖਰ c;
    ਪੂਰਨ hh, mm, ss, ff, flags;

    ਜੇ (ਲੜੀ_ਤੋਂ_ਪੜ੍ਹੋ(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        ਵਾਪਸ AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    ਵਾਪਸ av_timecode_init_from_components(tc, ਦਰ, flags, hh, mm, ss, ff, log_ctx);
}

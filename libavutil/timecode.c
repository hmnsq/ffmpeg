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

#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "timecode.h"
#ಅನ್ತರ್ಭಾವ "timecode_internal.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "error.h"

ಪೂರ್ಣಾಙ್ಕ av_timecode_adjust_ntsc_framenum2(ಪೂರ್ಣಾಙ್ಕ framenum, ಪೂರ್ಣಾಙ್ಕ fps)
{
    /* only works for multiples of NTSC 29.97 */
    ಪೂರ್ಣಾಙ್ಕ drop_frames = 0;
    ಪೂರ್ಣಾಙ್ಕ d, m, frames_per_10mins;

    ಯದಿ (fps && fps % 30 == 0) {
        drop_frames = fps / 30 * 2;
        frames_per_10mins = fps / 30 * 17982;
    } ಅನ್ಯಥಾ
        ಪ್ರತ್ಯಾಗಮ framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    ಪ್ರತ್ಯಾಗಮ framenum + 9U * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(ಧ್ರುವ AVTimecode *tc, ಪೂರ್ಣಾಙ್ಕ framenum)
{
    unsigned fps = tc->fps;
    ಪೂರ್ಣಾಙ್ಕ drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    ಪೂರ್ಣಾಙ್ಕ hh, mm, ss, ff;

    framenum += tc->start;
    ಯದಿ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    ಪ್ರತ್ಯಾಗಮ av_timecode_get_smpte(tc->rate, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational rate, ಪೂರ್ಣಾಙ್ಕ drop, ಪೂರ್ಣಾಙ್ಕ hh, ಪೂರ್ಣಾಙ್ಕ mm, ಪೂರ್ಣಾಙ್ಕ ss, ಪೂರ್ಣಾಙ್ಕ ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    ಯದಿ (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        ಯದಿ (ff % 2 == 1) {
            ಯದಿ (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            ಅನ್ಯಥಾ
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

    ಪ್ರತ್ಯಾಗಮ tc;
}

ವರ್ಣ *av_timecode_make_string(ಧ್ರುವ AVTimecode *tc, ವರ್ಣ *buf, ಪೂರ್ಣಾಙ್ಕ framenum_arg)
{
    unsigned fps = tc->fps;
    ಪೂರ್ಣಾಙ್ಕ drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    ಪೂರ್ಣಾಙ್ಕ hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->start;
    ಯದಿ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    ಯದಿ (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    ಯದಿ (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    ಪ್ರತ್ಯಾಗಮ buf;
}

ವರ್ಣ *av_timecode_make_smpte_tc_string2(ವರ್ಣ *buf, AVRational rate, uint32_t tcsmpte, ಪೂರ್ಣಾಙ್ಕ prevent_df, ಪೂರ್ಣಾಙ್ಕ skip_field)
{
    unsigned hh, mm, ss, ff, drop;
    ff_timecode_set_smpte(&drop, &hh, &mm, &ss, &ff, rate, tcsmpte, prevent_df, skip_field);

    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    ಪ್ರತ್ಯಾಗಮ buf;

}

ವರ್ಣ *av_timecode_make_smpte_tc_string(ವರ್ಣ *buf, uint32_t tcsmpte, ಪೂರ್ಣಾಙ್ಕ prevent_df)
{
    ಪ್ರತ್ಯಾಗಮ av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

ವರ್ಣ *av_timecode_make_mpeg_tc_string(ವರ್ಣ *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_SIZE,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    ಪ್ರತ್ಯಾಗಮ buf;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ check_fps(ಪೂರ್ಣಾಙ್ಕ fps)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    ಪ್ರತಿ (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        ಯದಿ (fps == supported_fps[i])
            ಪ್ರತ್ಯಾಗಮ 0;
    ಪ್ರತ್ಯಾಗಮ -1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ check_timecode(ಶೂನ್ಯ *log_ctx, AVTimecode *tc)
{
    ಯದಿ ((ಪೂರ್ಣಾಙ್ಕ)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    ಯದಿ ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    ಯದಿ (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->rate.ಅಂಕೆ, tc->rate.den);
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ fps_from_frame_rate(AVRational rate)
{
    ಯದಿ (!rate.den || !rate.ಅಂಕೆ)
        ಪ್ರತ್ಯಾಗಮ -1;
    ಪ್ರತ್ಯಾಗಮ (rate.ಅಂಕೆ + rate.den/2LL) / rate.den;
}

ಪೂರ್ಣಾಙ್ಕ av_timecode_check_frame_rate(AVRational rate)
{
    ಪ್ರತ್ಯಾಗಮ check_fps(fps_from_frame_rate(rate));
}

ಪೂರ್ಣಾಙ್ಕ av_timecode_init(AVTimecode *tc, AVRational rate, ಪೂರ್ಣಾಙ್ಕ flags, ಪೂರ್ಣಾಙ್ಕ frame_start, ಶೂನ್ಯ *log_ctx)
{
    memset(tc, 0, ಪರಿಮಾಣ(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    ಪ್ರತ್ಯಾಗಮ check_timecode(log_ctx, tc);
}

ಪೂರ್ಣಾಙ್ಕ av_timecode_init_from_components(AVTimecode *tc, AVRational rate, ಪೂರ್ಣಾಙ್ಕ flags, ಪೂರ್ಣಾಙ್ಕ hh, ಪೂರ್ಣಾಙ್ಕ mm, ಪೂರ್ಣಾಙ್ಕ ss, ಪೂರ್ಣಾಙ್ಕ ff, ಶೂನ್ಯ *log_ctx)
{
    ಪೂರ್ಣಾಙ್ಕ ret;
    int64_t s;

    memset(tc, 0, ಪರಿಮಾಣ(*tc));
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);

    ret = check_timecode(log_ctx, tc);
    ಯದಿ (ret < 0)
        ಪ್ರತ್ಯಾಗಮ ret;

    s = hh*3600LL + mm*60LL + ss;
    ಯದಿ (s != (int32_t)s)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);

    s = s * tc->fps + ff;
    ಯದಿ (s != (int32_t)s)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    tc->start = s;

    ಯದಿ (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        ಪೂರ್ಣಾಙ್ಕ tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_timecode_init_from_string(AVTimecode *tc, AVRational rate, ಧ್ರುವ ವರ್ಣ *str, ಶೂನ್ಯ *log_ctx)
{
    ವರ್ಣ c;
    ಪೂರ್ಣಾಙ್ಕ hh, mm, ss, ff, flags;

    ಯದಿ (sscanf(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    ಪ್ರತ್ಯಾಗಮ av_timecode_init_from_components(tc, rate, flags, hh, mm, ss, ff, log_ctx);
}

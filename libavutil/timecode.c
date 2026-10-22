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

ಪೂರ್ಣಾಂಕ av_timecode_adjust_ntsc_framenum2(ಪೂರ್ಣಾಂಕ framenum, ಪೂರ್ಣಾಂಕ fps)
{
    /* only works for multiples of NTSC 29.97 */
    ಪೂರ್ಣಾಂಕ drop_ಚೌಕಟ್ಟುಗಳು = 0;
    ಪೂರ್ಣಾಂಕ d, m, ಚೌಕಟ್ಟುಗಳು_ಪ್ರತಿ_10mins;

    ಆದರೆ (fps && fps % 30 == 0) {
        drop_ಚೌಕಟ್ಟುಗಳು = fps / 30 * 2;
        ಚೌಕಟ್ಟುಗಳು_ಪ್ರತಿ_10mins = fps / 30 * 17982;
    } ಇಲ್ಲದಿದ್ದರೆ
        ಹಿಂತಿರುಗಿ framenum;

    d = framenum / ಚೌಕಟ್ಟುಗಳು_ಪ್ರತಿ_10mins;
    m = framenum % ಚೌಕಟ್ಟುಗಳು_ಪ್ರತಿ_10mins;

    ಹಿಂತಿರುಗಿ framenum + 9U * drop_ಚೌಕಟ್ಟುಗಳು * d + drop_ಚೌಕಟ್ಟುಗಳು * ((m - drop_ಚೌಕಟ್ಟುಗಳು) / (ಚೌಕಟ್ಟುಗಳು_ಪ್ರತಿ_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(ಸ್ಥಿರಾಂಕ AVTimecode *tc, ಪೂರ್ಣಾಂಕ framenum)
{
    ಚಿಹ್ನೆರಹಿತ fps = tc->fps;
    ಪೂರ್ಣಾಂಕ drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    ಪೂರ್ಣಾಂಕ hh, mm, ss, ff;

    framenum += tc->ಆರಂಭ;
    ಆದರೆ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    ಹಿಂತಿರುಗಿ av_timecode_get_smpte(tc->ದರ, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational ದರ, ಪೂರ್ಣಾಂಕ drop, ಪೂರ್ಣಾಂಕ hh, ಪೂರ್ಣಾಂಕ mm, ಪೂರ್ಣಾಂಕ ss, ಪೂರ್ಣಾಂಕ ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    ಆದರೆ (av_cmp_q(ದರ, (AVRational) {30, 1}) == 1) {
        ಆದರೆ (ff % 2 == 1) {
            ಆದರೆ (av_cmp_q(ದರ, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            ಇಲ್ಲದಿದ್ದರೆ
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

    ಹಿಂತಿರುಗಿ tc;
}

ಅಕ್ಷರ *av_timecode_make_string(ಸ್ಥಿರಾಂಕ AVTimecode *tc, ಅಕ್ಷರ *buf, ಪೂರ್ಣಾಂಕ framenum_arg)
{
    ಚಿಹ್ನೆರಹಿತ fps = tc->fps;
    ಪೂರ್ಣಾಂಕ drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    ಪೂರ್ಣಾಂಕ hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->ಆರಂಭ;
    ಆದರೆ (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    ಆದರೆ (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    ಆದರೆ (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_ಗಾತ್ರ, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    ಹಿಂತಿರುಗಿ buf;
}

ಅಕ್ಷರ *av_timecode_make_smpte_tc_string2(ಅಕ್ಷರ *buf, AVRational ದರ, uint32_t tcsmpte, ಪೂರ್ಣಾಂಕ prevent_df, ಪೂರ್ಣಾಂಕ skip_ಕ್ಷೇತ್ರ)
{
    ಚಿಹ್ನೆರಹಿತ hh, mm, ss, ff, drop;
    ff_timecode_ಗಣ_smpte(&drop, &hh, &mm, &ss, &ff, ದರ, tcsmpte, prevent_df, skip_ಕ್ಷೇತ್ರ);

    snprintf(buf, AV_TIMECODE_STR_ಗಾತ್ರ, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    ಹಿಂತಿರುಗಿ buf;

}

ಅಕ್ಷರ *av_timecode_make_smpte_tc_string(ಅಕ್ಷರ *buf, uint32_t tcsmpte, ಪೂರ್ಣಾಂಕ prevent_df)
{
    ಹಿಂತಿರುಗಿ av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

ಅಕ್ಷರ *av_timecode_make_mpeg_tc_string(ಅಕ್ಷರ *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_ಗಾತ್ರ,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    ಹಿಂತಿರುಗಿ buf;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ check_fps(ಪೂರ್ಣಾಂಕ fps)
{
    ಪೂರ್ಣಾಂಕ i;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    ಗಾಗಿ (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        ಆದರೆ (fps == supported_fps[i])
            ಹಿಂತಿರುಗಿ 0;
    ಹಿಂತಿರುಗಿ -1;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ check_timecode(ಶೂನ್ಯ *log_ctx, AVTimecode *tc)
{
    ಆದರೆ ((ಪೂರ್ಣಾಂಕ)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    ಆದರೆ ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    ಆದರೆ (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->ದರ.ಅಂಕೆ, tc->ದರ.den);
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ fps_from_ಚೌಕಟ್ಟು_ದರ(AVRational ದರ)
{
    ಆದರೆ (!ದರ.den || !ದರ.ಅಂಕೆ)
        ಹಿಂತಿರುಗಿ -1;
    ಹಿಂತಿರುಗಿ (ದರ.ಅಂಕೆ + ದರ.den/2LL) / ದರ.den;
}

ಪೂರ್ಣಾಂಕ av_timecode_check_ಚೌಕಟ್ಟು_ದರ(AVRational ದರ)
{
    ಹಿಂತಿರುಗಿ check_fps(fps_from_ಚೌಕಟ್ಟು_ದರ(ದರ));
}

ಪೂರ್ಣಾಂಕ av_timecode_init(AVTimecode *tc, AVRational ದರ, ಪೂರ್ಣಾಂಕ flags, ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_ಆರಂಭ, ಶೂನ್ಯ *log_ctx)
{
    memset(tc, 0, ಗಾತ್ರ(*tc));
    tc->ಆರಂಭ = ಚೌಕಟ್ಟು_ಆರಂಭ;
    tc->flags = flags;
    tc->ದರ  = ದರ;
    tc->fps   = fps_from_ಚೌಕಟ್ಟು_ದರ(ದರ);
    ಹಿಂತಿರುಗಿ check_timecode(log_ctx, tc);
}

ಪೂರ್ಣಾಂಕ av_timecode_init_from_components(AVTimecode *tc, AVRational ದರ, ಪೂರ್ಣಾಂಕ flags, ಪೂರ್ಣಾಂಕ hh, ಪೂರ್ಣಾಂಕ mm, ಪೂರ್ಣಾಂಕ ss, ಪೂರ್ಣಾಂಕ ff, ಶೂನ್ಯ *log_ctx)
{
    ಪೂರ್ಣಾಂಕ ret;
    int64_t s;

    memset(tc, 0, ಗಾತ್ರ(*tc));
    tc->flags = flags;
    tc->ದರ  = ದರ;
    tc->fps   = fps_from_ಚೌಕಟ್ಟು_ದರ(ದರ);

    ret = check_timecode(log_ctx, tc);
    ಆದರೆ (ret < 0)
        ಹಿಂತಿರುಗಿ ret;

    s = hh*3600LL + mm*60LL + ss;
    ಆದರೆ (s != (int32_t)s)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);

    s = s * tc->fps + ff;
    ಆದರೆ (s != (int32_t)s)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    tc->ಆರಂಭ = s;

    ಆದರೆ (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        ಪೂರ್ಣಾಂಕ tmins = 60*hh + mm;
        tc->ಆರಂಭ -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_timecode_init_from_string(AVTimecode *tc, AVRational ದರ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *str, ಶೂನ್ಯ *log_ctx)
{
    ಅಕ್ಷರ c;
    ಪೂರ್ಣಾಂಕ hh, mm, ss, ff, flags;

    ಆದರೆ (ಅಕ್ಷರಸರಣಿ_ಓದು(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        ಹಿಂತಿರುಗಿ AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    ಹಿಂತಿರುಗಿ av_timecode_init_from_components(tc, ದರ, flags, hh, mm, ss, ff, log_ctx);
}

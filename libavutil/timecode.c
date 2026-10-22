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

#अन्तर्भाव <stdio.h>
#अन्तर्भाव "common.h"
#अन्तर्भाव "timecode.h"
#अन्तर्भाव "timecode_internal.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "error.h"

पूर्णाङ्क av_timecode_adjust_ntsc_framenum2(पूर्णाङ्क framenum, पूर्णाङ्क fps)
{
    /* only works for multiples of NTSC 29.97 */
    पूर्णाङ्क drop_frames = 0;
    पूर्णाङ्क d, m, frames_per_10mins;

    सचे (fps && fps % 30 == 0) {
        drop_frames = fps / 30 * 2;
        frames_per_10mins = fps / 30 * 17982;
    } अञ्ञथा
        पटिनिवत्त framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    पटिनिवत्त framenum + 9U * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(ध्रुव AVTimecode *tc, पूर्णाङ्क framenum)
{
    unsigned fps = tc->fps;
    पूर्णाङ्क drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    पूर्णाङ्क hh, mm, ss, ff;

    framenum += tc->start;
    सचे (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    पटिनिवत्त av_timecode_get_smpte(tc->rate, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational rate, पूर्णाङ्क drop, पूर्णाङ्क hh, पूर्णाङ्क mm, पूर्णाङ्क ss, पूर्णाङ्क ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    सचे (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        सचे (ff % 2 == 1) {
            सचे (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            अञ्ञथा
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

    पटिनिवत्त tc;
}

वर्ण *av_timecode_make_string(ध्रुव AVTimecode *tc, वर्ण *buf, पूर्णाङ्क framenum_arg)
{
    unsigned fps = tc->fps;
    पूर्णाङ्क drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    पूर्णाङ्क hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->start;
    सचे (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    सचे (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    सचे (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    पटिनिवत्त buf;
}

वर्ण *av_timecode_make_smpte_tc_string2(वर्ण *buf, AVRational rate, uint32_t tcsmpte, पूर्णाङ्क prevent_df, पूर्णाङ्क skip_field)
{
    unsigned hh, mm, ss, ff, drop;
    ff_timecode_set_smpte(&drop, &hh, &mm, &ss, &ff, rate, tcsmpte, prevent_df, skip_field);

    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    पटिनिवत्त buf;

}

वर्ण *av_timecode_make_smpte_tc_string(वर्ण *buf, uint32_t tcsmpte, पूर्णाङ्क prevent_df)
{
    पटिनिवत्त av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

वर्ण *av_timecode_make_mpeg_tc_string(वर्ण *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_SIZE,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    पटिनिवत्त buf;
}

स्थिर पूर्णाङ्क check_fps(पूर्णाङ्क fps)
{
    पूर्णाङ्क i;
    स्थिर ध्रुव पूर्णाङ्क supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    अत्थाय (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        सचे (fps == supported_fps[i])
            पटिनिवत्त 0;
    पटिनिवत्त -1;
}

स्थिर पूर्णाङ्क check_timecode(शून्य *log_ctx, AVTimecode *tc)
{
    सचे ((पूर्णाङ्क)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        पटिनिवत्त AVERROR(EINVAL);
    }
    सचे ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        पटिनिवत्त AVERROR(EINVAL);
    }
    सचे (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->rate.अङ्कः, tc->rate.den);
    }
    पटिनिवत्त 0;
}

स्थिर पूर्णाङ्क fps_from_frame_rate(AVRational rate)
{
    सचे (!rate.den || !rate.अङ्कः)
        पटिनिवत्त -1;
    पटिनिवत्त (rate.अङ्कः + rate.den/2LL) / rate.den;
}

पूर्णाङ्क av_timecode_check_frame_rate(AVRational rate)
{
    पटिनिवत्त check_fps(fps_from_frame_rate(rate));
}

पूर्णाङ्क av_timecode_init(AVTimecode *tc, AVRational rate, पूर्णाङ्क flags, पूर्णाङ्क frame_start, शून्य *log_ctx)
{
    memset(tc, 0, परिमाण(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    पटिनिवत्त check_timecode(log_ctx, tc);
}

पूर्णाङ्क av_timecode_init_from_components(AVTimecode *tc, AVRational rate, पूर्णाङ्क flags, पूर्णाङ्क hh, पूर्णाङ्क mm, पूर्णाङ्क ss, पूर्णाङ्क ff, शून्य *log_ctx)
{
    पूर्णाङ्क ret;
    int64_t s;

    memset(tc, 0, परिमाण(*tc));
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);

    ret = check_timecode(log_ctx, tc);
    सचे (ret < 0)
        पटिनिवत्त ret;

    s = hh*3600LL + mm*60LL + ss;
    सचे (s != (int32_t)s)
        पटिनिवत्त AVERROR(EINVAL);

    s = s * tc->fps + ff;
    सचे (s != (int32_t)s)
        पटिनिवत्त AVERROR(EINVAL);
    tc->start = s;

    सचे (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        पूर्णाङ्क tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    पटिनिवत्त 0;
}

पूर्णाङ्क av_timecode_init_from_string(AVTimecode *tc, AVRational rate, ध्रुव वर्ण *str, शून्य *log_ctx)
{
    वर्ण c;
    पूर्णाङ्क hh, mm, ss, ff, flags;

    सचे (sscanf(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        पटिनिवत्त AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    पटिनिवत्त av_timecode_init_from_components(tc, rate, flags, hh, mm, ss, ff, log_ctx);
}

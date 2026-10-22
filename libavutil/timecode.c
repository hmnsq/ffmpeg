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

    यदि (fps && fps % 30 == 0) {
        drop_frames = fps / 30 * 2;
        frames_per_10mins = fps / 30 * 17982;
    } अन्यथा
        फर्काऊ framenum;

    d = framenum / frames_per_10mins;
    m = framenum % frames_per_10mins;

    फर्काऊ framenum + 9U * drop_frames * d + drop_frames * ((m - drop_frames) / (frames_per_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(अचर AVTimecode *tc, पूर्णाङ्क framenum)
{
    अचिन्हित fps = tc->fps;
    पूर्णाङ्क drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    पूर्णाङ्क hh, mm, ss, ff;

    framenum += tc->start;
    यदि (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    फर्काऊ av_timecode_get_smpte(tc->rate, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational rate, पूर्णाङ्क drop, पूर्णाङ्क hh, पूर्णाङ्क mm, पूर्णाङ्क ss, पूर्णाङ्क ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    यदि (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        यदि (ff % 2 == 1) {
            यदि (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            अन्यथा
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

    फर्काऊ tc;
}

वर्ण *av_timecode_make_string(अचर AVTimecode *tc, वर्ण *buf, पूर्णाङ्क framenum_arg)
{
    अचिन्हित fps = tc->fps;
    पूर्णाङ्क drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    पूर्णाङ्क hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->start;
    यदि (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    यदि (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    यदि (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_SIZE, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    फर्काऊ buf;
}

वर्ण *av_timecode_make_smpte_tc_string2(वर्ण *buf, AVRational rate, uint32_t tcsmpte, पूर्णाङ्क prevent_df, पूर्णाङ्क skip_field)
{
    अचिन्हित hh, mm, ss, ff, drop;
    ff_timecode_set_smpte(&drop, &hh, &mm, &ss, &ff, rate, tcsmpte, prevent_df, skip_field);

    snprintf(buf, AV_TIMECODE_STR_SIZE, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    फर्काऊ buf;

}

वर्ण *av_timecode_make_smpte_tc_string(वर्ण *buf, uint32_t tcsmpte, पूर्णाङ्क prevent_df)
{
    फर्काऊ av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
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
    फर्काऊ buf;
}

स्थिर पूर्णाङ्क check_fps(पूर्णाङ्क fps)
{
    पूर्णाङ्क i;
    स्थिर अचर पूर्णाङ्क supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    लागि (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        यदि (fps == supported_fps[i])
            फर्काऊ 0;
    फर्काऊ -1;
}

स्थिर पूर्णाङ्क check_timecode(शून्य *log_ctx, AVTimecode *tc)
{
    यदि ((पूर्णाङ्क)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        फर्काऊ AVERROR(EINVAL);
    }
    यदि ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        फर्काऊ AVERROR(EINVAL);
    }
    यदि (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->rate.अङ्क, tc->rate.den);
    }
    फर्काऊ 0;
}

स्थिर पूर्णाङ्क fps_from_frame_rate(AVRational rate)
{
    यदि (!rate.den || !rate.अङ्क)
        फर्काऊ -1;
    फर्काऊ (rate.अङ्क + rate.den/2LL) / rate.den;
}

पूर्णाङ्क av_timecode_check_frame_rate(AVRational rate)
{
    फर्काऊ check_fps(fps_from_frame_rate(rate));
}

पूर्णाङ्क av_timecode_init(AVTimecode *tc, AVRational rate, पूर्णाङ्क flags, पूर्णाङ्क frame_start, शून्य *log_ctx)
{
    स_रखो(tc, 0, परिमाण(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);
    फर्काऊ check_timecode(log_ctx, tc);
}

पूर्णाङ्क av_timecode_init_from_components(AVTimecode *tc, AVRational rate, पूर्णाङ्क flags, पूर्णाङ्क hh, पूर्णाङ्क mm, पूर्णाङ्क ss, पूर्णाङ्क ff, शून्य *log_ctx)
{
    पूर्णाङ्क ret;
    int64_t s;

    स_रखो(tc, 0, परिमाण(*tc));
    tc->flags = flags;
    tc->rate  = rate;
    tc->fps   = fps_from_frame_rate(rate);

    ret = check_timecode(log_ctx, tc);
    यदि (ret < 0)
        फर्काऊ ret;

    s = hh*3600LL + mm*60LL + ss;
    यदि (s != (int32_t)s)
        फर्काऊ AVERROR(EINVAL);

    s = s * tc->fps + ff;
    यदि (s != (int32_t)s)
        फर्काऊ AVERROR(EINVAL);
    tc->start = s;

    यदि (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        पूर्णाङ्क tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    फर्काऊ 0;
}

पूर्णाङ्क av_timecode_init_from_string(AVTimecode *tc, AVRational rate, अचर वर्ण *str, शून्य *log_ctx)
{
    वर्ण c;
    पूर्णाङ्क hh, mm, ss, ff, flags;

    यदि (माला_पूछो(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        फर्काऊ AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    फर्काऊ av_timecode_init_from_components(tc, rate, flags, hh, mm, ss, ff, log_ctx);
}

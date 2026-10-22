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
    पूर्णाङ्क drop_चौकटाः = 0;
    पूर्णाङ्क d, m, चौकटाः_प्रत्येकम्_10mins;

    यदि (fps && fps % 30 == 0) {
        drop_चौकटाः = fps / 30 * 2;
        चौकटाः_प्रत्येकम्_10mins = fps / 30 * 17982;
    } अन्यथा
        प्रत्यागम framenum;

    d = framenum / चौकटाः_प्रत्येकम्_10mins;
    m = framenum % चौकटाः_प्रत्येकम्_10mins;

    प्रत्यागम framenum + 9U * drop_चौकटाः * d + drop_चौकटाः * ((m - drop_चौकटाः) / (चौकटाः_प्रत्येकम्_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(ध्रुव AVTimecode *tc, पूर्णाङ्क framenum)
{
    अचिह्नित fps = tc->fps;
    पूर्णाङ्क drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    पूर्णाङ्क hh, mm, ss, ff;

    framenum += tc->start;
    यदि (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    प्रत्यागम av_timecode_get_smpte(tc->दरः, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational दरः, पूर्णाङ्क drop, पूर्णाङ्क hh, पूर्णाङ्क mm, पूर्णाङ्क ss, पूर्णाङ्क ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    यदि (av_cmp_q(दरः, (AVRational) {30, 1}) == 1) {
        यदि (ff % 2 == 1) {
            यदि (av_cmp_q(दरः, (AVRational) {50, 1}) == 0)
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

    प्रत्यागम tc;
}

वर्ण *av_timecode_make_string(ध्रुव AVTimecode *tc, वर्ण *buf, पूर्णाङ्क framenum_arg)
{
    अचिह्नित fps = tc->fps;
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
    snprintf(buf, AV_TIMECODE_STR_आकार, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    प्रत्यागम buf;
}

वर्ण *av_timecode_make_smpte_tc_string2(वर्ण *buf, AVRational दरः, uint32_t tcsmpte, पूर्णाङ्क prevent_df, पूर्णाङ्क skip_क्षेत्रम्)
{
    अचिह्नित hh, mm, ss, ff, drop;
    ff_timecode_समुच्चयः_smpte(&drop, &hh, &mm, &ss, &ff, दरः, tcsmpte, prevent_df, skip_क्षेत्रम्);

    snprintf(buf, AV_TIMECODE_STR_आकार, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    प्रत्यागम buf;

}

वर्ण *av_timecode_make_smpte_tc_string(वर्ण *buf, uint32_t tcsmpte, पूर्णाङ्क prevent_df)
{
    प्रत्यागम av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

वर्ण *av_timecode_make_mpeg_tc_string(वर्ण *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_आकार,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    प्रत्यागम buf;
}

स्थिर पूर्णाङ्क check_fps(पूर्णाङ्क fps)
{
    पूर्णाङ्क i;
    स्थिर ध्रुव पूर्णाङ्क supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    प्रति (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        यदि (fps == supported_fps[i])
            प्रत्यागम 0;
    प्रत्यागम -1;
}

स्थिर पूर्णाङ्क check_timecode(शून्य *log_ctx, AVTimecode *tc)
{
    यदि ((पूर्णाङ्क)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        प्रत्यागम AVERROR(EINVAL);
    }
    यदि ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        प्रत्यागम AVERROR(EINVAL);
    }
    यदि (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->दरः.अङ्कः, tc->दरः.den);
    }
    प्रत्यागम 0;
}

स्थिर पूर्णाङ्क fps_from_frame_दरः(AVRational दरः)
{
    यदि (!दरः.den || !दरः.अङ्कः)
        प्रत्यागम -1;
    प्रत्यागम (दरः.अङ्कः + दरः.den/2LL) / दरः.den;
}

पूर्णाङ्क av_timecode_check_frame_दरः(AVRational दरः)
{
    प्रत्यागम check_fps(fps_from_frame_दरः(दरः));
}

पूर्णाङ्क av_timecode_init(AVTimecode *tc, AVRational दरः, पूर्णाङ्क flags, पूर्णाङ्क frame_start, शून्य *log_ctx)
{
    स्मृतिं_पूरय(tc, 0, परिमाण(*tc));
    tc->start = frame_start;
    tc->flags = flags;
    tc->दरः  = दरः;
    tc->fps   = fps_from_frame_दरः(दरः);
    प्रत्यागम check_timecode(log_ctx, tc);
}

पूर्णाङ्क av_timecode_init_from_components(AVTimecode *tc, AVRational दरः, पूर्णाङ्क flags, पूर्णाङ्क hh, पूर्णाङ्क mm, पूर्णाङ्क ss, पूर्णाङ्क ff, शून्य *log_ctx)
{
    पूर्णाङ्क ret;
    int64_t s;

    स्मृतिं_पूरय(tc, 0, परिमाण(*tc));
    tc->flags = flags;
    tc->दरः  = दरः;
    tc->fps   = fps_from_frame_दरः(दरः);

    ret = check_timecode(log_ctx, tc);
    यदि (ret < 0)
        प्रत्यागम ret;

    s = hh*3600LL + mm*60LL + ss;
    यदि (s != (int32_t)s)
        प्रत्यागम AVERROR(EINVAL);

    s = s * tc->fps + ff;
    यदि (s != (int32_t)s)
        प्रत्यागम AVERROR(EINVAL);
    tc->start = s;

    यदि (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        पूर्णाङ्क tmins = 60*hh + mm;
        tc->start -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    प्रत्यागम 0;
}

पूर्णाङ्क av_timecode_init_from_string(AVTimecode *tc, AVRational दरः, ध्रुव वर्ण *str, शून्य *log_ctx)
{
    वर्ण c;
    पूर्णाङ्क hh, mm, ss, ff, flags;

    यदि (वाक्यात्_पठ(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        प्रत्यागम AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    प्रत्यागम av_timecode_init_from_components(tc, दरः, flags, hh, mm, ss, ff, log_ctx);
}

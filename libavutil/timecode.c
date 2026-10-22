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

#شامل <stdio.h>
#شامل "common.h"
#شامل "timecode.h"
#شامل "timecode_internal.h"
#شامل "log.h"
#شامل "error.h"

صحیح av_timecode_adjust_ntsc_framenum2(صحیح framenum, صحیح fps)
{
    /* only works for multiples of NTSC 29.97 */
    صحیح drop_چوکھٹے = 0;
    صحیح d, m, چوکھٹے_فی_10mins;

    اگر (fps && fps % 30 == 0) {
        drop_چوکھٹے = fps / 30 * 2;
        چوکھٹے_فی_10mins = fps / 30 * 17982;
    } ورنہ
        واپس framenum;

    d = framenum / چوکھٹے_فی_10mins;
    m = framenum % چوکھٹے_فی_10mins;

    واپس framenum + 9U * drop_چوکھٹے * d + drop_چوکھٹے * ((m - drop_چوکھٹے) / (چوکھٹے_فی_10mins / 10));
}

uint32_t av_timecode_get_smpte_from_framenum(ثابت AVTimecode *tc, صحیح framenum)
{
    غیرعلامتی fps = tc->fps;
    صحیح drop = !!(tc->flags & AV_TIMECODE_FLAG_DROPFRAME);
    صحیح hh, mm, ss, ff;

    framenum += tc->آغاز;
    اگر (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, tc->fps);
    ff = framenum % fps;
    ss = framenum / fps      % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL) % 24;
    واپس av_timecode_get_smpte(tc->شرح, drop, hh, mm, ss, ff);
}

uint32_t av_timecode_get_smpte(AVRational شرح, صحیح drop, صحیح hh, صحیح mm, صحیح ss, صحیح ff)
{
    uint32_t tc = 0;

    /* For SMPTE 12-M timecodes, frame count is a special case if > 30 FPS.
       See SMPTE ST 12-1:2014 Sec 12.1 for more info. */
    اگر (av_cmp_q(شرح, (AVRational) {30, 1}) == 1) {
        اگر (ff % 2 == 1) {
            اگر (av_cmp_q(شرح, (AVRational) {50, 1}) == 0)
                tc |= (1 << 7);
            ورنہ
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

    واپس tc;
}

حرف *av_timecode_make_string(ثابت AVTimecode *tc, حرف *buf, صحیح framenum_arg)
{
    غیرعلامتی fps = tc->fps;
    صحیح drop = tc->flags & AV_TIMECODE_FLAG_DROPFRAME;
    صحیح hh, mm, ss, ff, ff_len, neg = 0;
    int64_t framenum = framenum_arg;

    framenum += tc->آغاز;
    اگر (drop)
        framenum = av_timecode_adjust_ntsc_framenum2(framenum, fps);
    اگر (framenum < 0) {
        framenum = -framenum;
        neg = tc->flags & AV_TIMECODE_FLAG_ALLOWNEGATIVE;
    }
    ff = framenum % fps;
    ss = framenum / fps        % 60;
    mm = framenum / (fps*60LL) % 60;
    hh = framenum / (fps*3600LL);
    اگر (tc->flags & AV_TIMECODE_FLAG_24HOURSMAX)
        hh = hh % 24;
    ff_len = fps > 10000 ? 5 : fps > 1000 ? 4 : fps > 100 ? 3 : fps > 10 ? 2 : 1;
    snprintf(buf, AV_TIMECODE_STR_سائز, "%s%02d:%02d:%02d%c%0*d",
             neg ? "-" : "",
             hh, mm, ss, drop ? ';' : ':', ff_len, ff);
    واپس buf;
}

حرف *av_timecode_make_smpte_tc_string2(حرف *buf, AVRational شرح, uint32_t tcsmpte, صحیح prevent_df, صحیح skip_میدان)
{
    غیرعلامتی hh, mm, ss, ff, drop;
    ff_timecode_سیٹ_smpte(&drop, &hh, &mm, &ss, &ff, شرح, tcsmpte, prevent_df, skip_میدان);

    snprintf(buf, AV_TIMECODE_STR_سائز, "%02u:%02u:%02u%c%02u",
             hh, mm, ss, drop ? ';' : ':', ff);
    واپس buf;

}

حرف *av_timecode_make_smpte_tc_string(حرف *buf, uint32_t tcsmpte, صحیح prevent_df)
{
    واپس av_timecode_make_smpte_tc_string2(buf, (AVRational){30, 1}, tcsmpte, prevent_df, 1);
}

حرف *av_timecode_make_mpeg_tc_string(حرف *buf, uint32_t tc25bit)
{
    snprintf(buf, AV_TIMECODE_STR_سائز,
             "%02"PRIu32":%02"PRIu32":%02"PRIu32"%c%02"PRIu32,
             tc25bit>>19 & 0x1f,              // 5-bit hours
             tc25bit>>13 & 0x3f,              // 6-bit minutes
             tc25bit>>6  & 0x3f,              // 6-bit seconds
             tc25bit     & 1<<24 ? ';' : ':', // 1-bit drop flag
             tc25bit     & 0x3f);             // 6-bit frames
    واپس buf;
}

ساکن صحیح check_fps(صحیح fps)
{
    صحیح i;
    ساکن ثابت صحیح supported_fps[] = {
        24, 25, 30, 48, 50, 60, 100, 120, 150,
    };

    برائے (i = 0; i < FF_ARRAY_ELEMS(supported_fps); i++)
        اگر (fps == supported_fps[i])
            واپس 0;
    واپس -1;
}

ساکن صحیح check_timecode(خالی *log_ctx, AVTimecode *tc)
{
    اگر ((صحیح)tc->fps <= 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Valid timecode frame rate must be specified. Minimum value is 1\n");
        واپس AVERROR(EINVAL);
    }
    اگر ((tc->flags & AV_TIMECODE_FLAG_DROPFRAME) && tc->fps % 30 != 0) {
        av_log(log_ctx, AV_LOG_ERROR, "Drop frame is only allowed with multiples of 30000/1001 FPS\n");
        واپس AVERROR(EINVAL);
    }
    اگر (check_fps(tc->fps) < 0) {
        av_log(log_ctx, AV_LOG_WARNING, "Using non-standard frame rate %d/%d\n",
               tc->شرح.عدد, tc->شرح.den);
    }
    واپس 0;
}

ساکن صحیح fps_from_چوکھٹا_شرح(AVRational شرح)
{
    اگر (!شرح.den || !شرح.عدد)
        واپس -1;
    واپس (شرح.عدد + شرح.den/2LL) / شرح.den;
}

صحیح av_timecode_check_چوکھٹا_شرح(AVRational شرح)
{
    واپس check_fps(fps_from_چوکھٹا_شرح(شرح));
}

صحیح av_timecode_init(AVTimecode *tc, AVRational شرح, صحیح flags, صحیح چوکھٹا_آغاز, خالی *log_ctx)
{
    memset(tc, 0, حجم(*tc));
    tc->آغاز = چوکھٹا_آغاز;
    tc->flags = flags;
    tc->شرح  = شرح;
    tc->fps   = fps_from_چوکھٹا_شرح(شرح);
    واپس check_timecode(log_ctx, tc);
}

صحیح av_timecode_init_from_components(AVTimecode *tc, AVRational شرح, صحیح flags, صحیح hh, صحیح mm, صحیح ss, صحیح ff, خالی *log_ctx)
{
    صحیح ret;
    int64_t s;

    memset(tc, 0, حجم(*tc));
    tc->flags = flags;
    tc->شرح  = شرح;
    tc->fps   = fps_from_چوکھٹا_شرح(شرح);

    ret = check_timecode(log_ctx, tc);
    اگر (ret < 0)
        واپس ret;

    s = hh*3600LL + mm*60LL + ss;
    اگر (s != (int32_t)s)
        واپس AVERROR(EINVAL);

    s = s * tc->fps + ff;
    اگر (s != (int32_t)s)
        واپس AVERROR(EINVAL);
    tc->آغاز = s;

    اگر (tc->flags & AV_TIMECODE_FLAG_DROPFRAME) { /* adjust frame number */
        صحیح tmins = 60*hh + mm;
        tc->آغاز -= (tc->fps / 30 * 2) * (tmins - tmins/10);
    }
    واپس 0;
}

صحیح av_timecode_init_from_string(AVTimecode *tc, AVRational شرح, ثابت حرف *str, خالی *log_ctx)
{
    حرف c;
    صحیح hh, mm, ss, ff, flags;

    اگر (لڑی_سے_پڑھو(str, "%d:%d:%d%c%d", &hh, &mm, &ss, &c, &ff) != 5) {
        av_log(log_ctx, AV_LOG_ERROR, "Unable to parse timecode, "
                                      "syntax: hh:mm:ss[:;.]ff\n");
        واپس AVERROR_INVALIDDATA;
    }
    flags = c != ':' ? AV_TIMECODE_FLAG_DROPFRAME : 0; // drop if ';', '.', ...

    واپس av_timecode_init_from_components(tc, شرح, flags, hh, mm, ss, ff, log_ctx);
}

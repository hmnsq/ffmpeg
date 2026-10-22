/*
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

#شامل "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
ساکن ثابت ساخت {
    صحیح عدد;
    ثابت حرف *لیبل;
} ffmpeg_codes[] = {
#تعریف_کرو ERROR_لیبل(رمز_2, DESC)         { AVERROR_ ## رمز_2, #CODE },
#تعریف_کرو ERROR_TAG2(رمز_2, CODE2, DESC) { AVERROR_ ## رمز_2, #CODE },
    AVERROR_LIST(ERROR_لیبل, ERROR_TAG2)
};

ساکن ثابت صحیح errno_codes[] = {
#تعریف_کرو ERRNO_رمز(رمز_2, DESC) AVERROR(رمز_2),
    STRERROR_LIST(ERRNO_رمز)
};

صحیح مین(خالی)
{
    حرف buf[AV_ERROR_MAX_STRING_سائز];
    صحیح ret = 0;

    برائے (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        صحیح عدد = ffmpeg_codes[i].عدد;

        اگر (av_strerror(عدد, buf, حجم(buf)) < 0) {
            لکھو("%d: lookup failed [%s]\n", عدد, ffmpeg_codes[i].لیبل);
            ret = 1;
            جاری;
        }
        لکھو("%d: %s [%s]\n", عدد, buf, ffmpeg_codes[i].لیبل);
    }

    برائے (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        اگر (av_strerror(errno_codes[i], buf, حجم(buf)) < 0) {
            لکھو("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    واپس ret;
}

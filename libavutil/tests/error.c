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

#ضمن "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
ساكن ثابت بنية {
    صحيح رقم;
    ثابت حرف *برچسب;
} ffmpeg_codes[] = {
#تعریف_کن ERROR_برچسب(کد_2, DESC)         { AVERROR_ ## کد_2, #CODE },
#تعریف_کن ERROR_TAG2(کد_2, CODE2, DESC) { AVERROR_ ## کد_2, #CODE },
    AVERROR_LIST(ERROR_برچسب, ERROR_TAG2)
};

ساكن ثابت صحيح errno_codes[] = {
#تعریف_کن ERRNO_کد(کد_2, DESC) AVERROR(کد_2),
    STRERROR_LIST(ERRNO_کد)
};

صحيح اصلی(فراغ)
{
    حرف buf[AV_ERROR_MAX_STRING_اندازه];
    صحيح ret = 0;

    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        صحيح رقم = ffmpeg_codes[i].رقم;

        إذا (av_strerror(رقم, buf, حجم(buf)) < 0) {
            چاپ_کن("%d: lookup failed [%s]\n", رقم, ffmpeg_codes[i].برچسب);
            ret = 1;
            استمر;
        }
        چاپ_کن("%d: %s [%s]\n", رقم, buf, ffmpeg_codes[i].برچسب);
    }

    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        إذا (av_strerror(errno_codes[i], buf, حجم(buf)) < 0) {
            چاپ_کن("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    أرجع ret;
}

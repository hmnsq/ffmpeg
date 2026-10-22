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
    صحيح عدد;
    ثابت حرف *نښان;
} ffmpeg_codes[] = {
#تعریف_کړه ERROR_نښان(کوډ_2, DESC)         { AVERROR_ ## کوډ_2, #CODE },
#تعریف_کړه ERROR_TAG2(کوډ_2, CODE2, DESC) { AVERROR_ ## کوډ_2, #CODE },
    AVERROR_LIST(ERROR_نښان, ERROR_TAG2)
};

ساكن ثابت صحيح errno_codes[] = {
#تعریف_کړه ERRNO_کوډ(کوډ_2, DESC) AVERROR(کوډ_2),
    STRERROR_LIST(ERRNO_کوډ)
};

صحيح اصلي(فراغ)
{
    حرف buf[AV_ERROR_MAX_STRING_اندازه];
    صحيح ret = 0;

    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        صحيح عدد = ffmpeg_codes[i].عدد;

        إذا (av_strerror(عدد, buf, حجم(buf)) < 0) {
            چاپ_کړه("%d: lookup failed [%s]\n", عدد, ffmpeg_codes[i].نښان);
            ret = 1;
            استمر;
        }
        چاپ_کړه("%d: %s [%s]\n", عدد, buf, ffmpeg_codes[i].نښان);
    }

    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        إذا (av_strerror(errno_codes[i], buf, حجم(buf)) < 0) {
            چاپ_کړه("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    أرجع ret;
}

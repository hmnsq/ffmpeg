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
    صحيح انگ;
    ثابت حرف *ٽيگ;
} ffmpeg_codes[] = {
#وصف_ڪريو ERROR_ٽيگ(ڪوڊ_2, DESC)         { AVERROR_ ## ڪوڊ_2, #CODE },
#وصف_ڪريو ERROR_TAG2(ڪوڊ_2, CODE2, DESC) { AVERROR_ ## ڪوڊ_2, #CODE },
    AVERROR_LIST(ERROR_ٽيگ, ERROR_TAG2)
};

ساكن ثابت صحيح errno_codes[] = {
#وصف_ڪريو ERRNO_ڪوڊ(ڪوڊ_2, DESC) AVERROR(ڪوڊ_2),
    STRERROR_LIST(ERRNO_ڪوڊ)
};

صحيح مکيه(فراغ)
{
    حرف buf[AV_ERROR_MAX_STRING_سائيز];
    صحيح ret = 0;

    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        صحيح انگ = ffmpeg_codes[i].انگ;

        إذا (av_strerror(انگ, buf, حجم(buf)) < 0) {
            لکو("%d: lookup failed [%s]\n", انگ, ffmpeg_codes[i].ٽيگ);
            ret = 1;
            استمر;
        }
        لکو("%d: %s [%s]\n", انگ, buf, ffmpeg_codes[i].ٽيگ);
    }

    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        إذا (av_strerror(errno_codes[i], buf, حجم(buf)) < 0) {
            لکو("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    أرجع ret;
}

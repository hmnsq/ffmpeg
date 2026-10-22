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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    ਪੂਰਨ ਅੰਕ;
    ਅਚਲ ਅੱਖਰ *ਟੈਗ;
} ffmpeg_codes[] = {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ERROR_ਟੈਗ(ਕੋਡ_2, DESC)         { AVERROR_ ## ਕੋਡ_2, #CODE },
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ERROR_TAG2(ਕੋਡ_2, CODE2, DESC) { AVERROR_ ## ਕੋਡ_2, #CODE },
    AVERROR_LIST(ERROR_ਟੈਗ, ERROR_TAG2)
};

ਸਥਿਰ ਅਚਲ ਪੂਰਨ errno_codes[] = {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ERRNO_ਕੋਡ(ਕੋਡ_2, DESC) AVERROR(ਕੋਡ_2),
    STRERROR_LIST(ERRNO_ਕੋਡ)
};

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    ਅੱਖਰ buf[AV_ERROR_MAX_STRING_ਮਾਪ];
    ਪੂਰਨ ret = 0;

    ਲਈ (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        ਪੂਰਨ ਅੰਕ = ffmpeg_codes[i].ਅੰਕ;

        ਜੇ (av_strerror(ਅੰਕ, buf, ਆਕਾਰ(buf)) < 0) {
            ਲਿਖੋ("%d: lookup failed [%s]\n", ਅੰਕ, ffmpeg_codes[i].ਟੈਗ);
            ret = 1;
            ਜਾਰੀ;
        }
        ਲਿਖੋ("%d: %s [%s]\n", ਅੰਕ, buf, ffmpeg_codes[i].ਟੈਗ);
    }

    ਲਈ (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        ਜੇ (av_strerror(errno_codes[i], buf, ਆਕਾਰ(buf)) < 0) {
            ਲਿਖੋ("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    ਵਾਪਸ ret;
}

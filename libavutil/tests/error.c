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

#അന്തര്ഭാവ "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
സ്ഥിതം സ്ഥിരം ഘടന {
    പൂർണ്ണസംഖ്യ അക്കം;
    സ്ഥിരം അക്ഷരം *tag;
} ffmpeg_codes[] = {
#define ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#define ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ errno_codes[] = {
#define ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    അക്ഷരം buf[AV_ERROR_MAX_STRING_SIZE];
    പൂർണ്ണസംഖ്യ ret = 0;

    വേണ്ടി (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        പൂർണ്ണസംഖ്യ അക്കം = ffmpeg_codes[i].അക്കം;

        എങ്കിൽ (av_strerror(അക്കം, buf, വലുപ്പം(buf)) < 0) {
            printf("%d: lookup failed [%s]\n", അക്കം, ffmpeg_codes[i].tag);
            ret = 1;
            തുടരുക;
        }
        printf("%d: %s [%s]\n", അക്കം, buf, ffmpeg_codes[i].tag);
    }

    വേണ്ടി (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        എങ്കിൽ (av_strerror(errno_codes[i], buf, വലുപ്പം(buf)) < 0) {
            printf("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    തിരികെ ret;
}

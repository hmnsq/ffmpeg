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

#અન્તર્ભાવ "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
સ્થિર અચલ સંરચના {
    પૂર્ણાંક અંક;
    અચલ અક્ષર *tag;
} ffmpeg_codes[] = {
#define ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#define ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

સ્થિર અચલ પૂર્ણાંક errno_codes[] = {
#define ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

પૂર્ણાંક મુખ્ય(શૂન્ય)
{
    અક્ષર buf[AV_ERROR_MAX_STRING_SIZE];
    પૂર્ણાંક ret = 0;

    માટે (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        પૂર્ણાંક અંક = ffmpeg_codes[i].અંક;

        જો (av_strerror(અંક, buf, કદ(buf)) < 0) {
            printf("%d: lookup failed [%s]\n", અંક, ffmpeg_codes[i].tag);
            ret = 1;
            ચાલુ;
        }
        printf("%d: %s [%s]\n", અંક, buf, ffmpeg_codes[i].tag);
    }

    માટે (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        જો (av_strerror(errno_codes[i], buf, કદ(buf)) < 0) {
            printf("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    પાછા ret;
}

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

#அந்தர்பாவ "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
நிலையான மாறிலி கட்டமைப்பு {
    முழு இலக்கம்;
    மாறிலி எழுத்து *tag;
} ffmpeg_codes[] = {
#define ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#define ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

நிலையான மாறிலி முழு errno_codes[] = {
#define ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

முழு முதன்மை(வெறுமை)
{
    எழுத்து buf[AV_ERROR_MAX_STRING_SIZE];
    முழு ret = 0;

    க்கு (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        முழு இலக்கம் = ffmpeg_codes[i].இலக்கம்;

        எனில் (av_strerror(இலக்கம், buf, அளவு(buf)) < 0) {
            printf("%d: lookup failed [%s]\n", இலக்கம், ffmpeg_codes[i].tag);
            ret = 1;
            தொடர்;
        }
        printf("%d: %s [%s]\n", இலக்கம், buf, ffmpeg_codes[i].tag);
    }

    க்கு (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        எனில் (av_strerror(errno_codes[i], buf, அளவு(buf)) < 0) {
            printf("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    திரும்பு ret;
}

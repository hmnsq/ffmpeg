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

#ଅନ୍ତର୍ଭାଵ "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ;
    ଅଚଳ ଅକ୍ଷର *tag;
} ffmpeg_codes[] = {
#define ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#define ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

ସ୍ଥିର ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା errno_codes[] = {
#define ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    ଅକ୍ଷର buf[AV_ERROR_MAX_STRING_SIZE];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = 0;

    ପାଇଁ (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ = ffmpeg_codes[i].ଅଙ୍କ;

        ଯଦି (av_strerror(ଅଙ୍କ, buf, ଆକାର(buf)) < 0) {
            printf("%d: lookup failed [%s]\n", ଅଙ୍କ, ffmpeg_codes[i].tag);
            ret = 1;
            ଜାରି;
        }
        printf("%d: %s [%s]\n", ଅଙ୍କ, buf, ffmpeg_codes[i].tag);
    }

    ପାଇଁ (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        ଯଦି (av_strerror(errno_codes[i], buf, ଆକାର(buf)) < 0) {
            printf("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    ଫେରନ୍ତୁ ret;
}

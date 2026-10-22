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

#include "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
static const struct {
    số_nguyên num;
    const char *tag;
} ffmpeg_codes[] = {
#define ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#define ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

static const số_nguyên errno_codes[] = {
#define ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

số_nguyên main(void)
{
    char buf[AV_ERROR_MAX_STRING_SIZE];
    số_nguyên ret = 0;

    cho (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        số_nguyên num = ffmpeg_codes[i].num;

        nếu (av_strerror(num, buf, sizeof(buf)) < 0) {
            printf("%d: lookup failed [%s]\n", num, ffmpeg_codes[i].tag);
            ret = 1;
            continue;
        }
        printf("%d: %s [%s]\n", num, buf, ffmpeg_codes[i].tag);
    }

    cho (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        nếu (av_strerror(errno_codes[i], buf, sizeof(buf)) < 0) {
            printf("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    trả_về ret;
}

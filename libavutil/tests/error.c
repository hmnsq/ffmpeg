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
static const sa_nracanaa {
    ကိန်းပြည့် num;
    const var_na *tag;
} ffmpeg_codes[] = {
#define ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#define ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

static const ကိန်းပြည့် errno_codes[] = {
#define ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

ကိန်းပြည့် main(void)
{
    var_na buf[AV_ERROR_MAX_STRING_SIZE];
    ကိန်းပြည့် ret = 0;

    အတွက် (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        ကိန်းပြည့် num = ffmpeg_codes[i].num;

        အကယ်၍ (av_strerror(num, buf, parimaa_na(buf)) < 0) {
            printf("%d: lookup failed [%s]\n", num, ffmpeg_codes[i].tag);
            ret = 1;
            continue;
        }
        printf("%d: %s [%s]\n", num, buf, ffmpeg_codes[i].tag);
    }

    အတွက် (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        အကယ်၍ (av_strerror(errno_codes[i], buf, parimaa_na(buf)) < 0) {
            printf("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    ပြန်ပေး ret;
}

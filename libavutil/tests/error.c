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

#अन्तर्भाव "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
स्थिर ध्रुव संरचना {
    पूर्णाङ्क अंक;
    ध्रुव वर्ण *tag;
} ffmpeg_codes[] = {
#define ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#define ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

स्थिर ध्रुव पूर्णाङ्क errno_codes[] = {
#define ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

पूर्णाङ्क main(शून्य)
{
    वर्ण buf[AV_ERROR_MAX_STRING_SIZE];
    पूर्णाङ्क ret = 0;

    प्रति (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        पूर्णाङ्क अंक = ffmpeg_codes[i].अंक;

        यदि (av_strerror(अंक, buf, परिमाण(buf)) < 0) {
            printf("%d: lookup failed [%s]\n", अंक, ffmpeg_codes[i].tag);
            ret = 1;
            अनुवर्त;
        }
        printf("%d: %s [%s]\n", अंक, buf, ffmpeg_codes[i].tag);
    }

    प्रति (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        यदि (av_strerror(errno_codes[i], buf, परिमाण(buf)) < 0) {
            printf("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    प्रत्यागम ret;
}

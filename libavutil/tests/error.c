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

#অন্তর্ভাৱ "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
স্থির ধ্রুৱ সংরচনা {
    পূর্ণাঙ্ক অঙ্ক;
    ধ্রুৱ ৱর্ণ *tag;
} ffmpeg_codes[] = {
#define ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#define ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

স্থির ধ্রুৱ পূর্ণাঙ্ক errno_codes[] = {
#define ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

পূর্ণাঙ্ক main(শূন্য)
{
    ৱর্ণ buf[AV_ERROR_MAX_STRING_SIZE];
    পূর্ণাঙ্ক ret = 0;

    বাবে (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        পূর্ণাঙ্ক অঙ্ক = ffmpeg_codes[i].অঙ্ক;

        যদি (av_strerror(অঙ্ক, buf, পরিমাণ(buf)) < 0) {
            printf("%d: lookup failed [%s]\n", অঙ্ক, ffmpeg_codes[i].tag);
            ret = 1;
            অনুৱর্ত;
        }
        printf("%d: %s [%s]\n", অঙ্ক, buf, ffmpeg_codes[i].tag);
    }

    বাবে (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        যদি (av_strerror(errno_codes[i], buf, পরিমাণ(buf)) < 0) {
            printf("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    ঘূৰাই ret;
}

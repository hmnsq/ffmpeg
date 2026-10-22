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

#ಅನ್ತರ್ಭಾವ "libavutil/error.c"

/* errno descriptions depend on the C library, so those are only looked up */
ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ;
    ಧ್ರುವ ವರ್ಣ *tag;
} ffmpeg_codes[] = {
#define ERROR_TAG(CODE, DESC)         { AVERROR_ ## CODE, #CODE },
#define ERROR_TAG2(CODE, CODE2, DESC) { AVERROR_ ## CODE, #CODE },
    AVERROR_LIST(ERROR_TAG, ERROR_TAG2)
};

ಸ್ಥಿರ ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ errno_codes[] = {
#define ERRNO_CODE(CODE, DESC) AVERROR(CODE),
    STRERROR_LIST(ERRNO_CODE)
};

ಪೂರ್ಣಾಙ್ಕ main(ಶೂನ್ಯ)
{
    ವರ್ಣ buf[AV_ERROR_MAX_STRING_SIZE];
    ಪೂರ್ಣಾಙ್ಕ ret = 0;

    ಪ್ರತಿ (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ = ffmpeg_codes[i].ಅಂಕೆ;

        ಯದಿ (av_strerror(ಅಂಕೆ, buf, ಪರಿಮಾಣ(buf)) < 0) {
            printf("%d: lookup failed [%s]\n", ಅಂಕೆ, ffmpeg_codes[i].tag);
            ret = 1;
            ಅನುವರ್ತ;
        }
        printf("%d: %s [%s]\n", ಅಂಕೆ, buf, ffmpeg_codes[i].tag);
    }

    ಪ್ರತಿ (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        ಯದಿ (av_strerror(errno_codes[i], buf, ಪರಿಮಾಣ(buf)) < 0) {
            printf("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    ಪ್ರತ್ಯಾಗಮ ret;
}

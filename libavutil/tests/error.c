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
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಟ್ಯಾಗ್;
} ffmpeg_codes[] = {
#ವ್ಯಾಖ್ಯಾನಿಸು ERROR_ಟ್ಯಾಗ್(ಸಂಕೇತ_3, DESC)         { AVERROR_ ## ಸಂಕೇತ_3, #CODE },
#ವ್ಯಾಖ್ಯಾನಿಸು ERROR_TAG2(ಸಂಕೇತ_3, CODE2, DESC) { AVERROR_ ## ಸಂಕೇತ_3, #CODE },
    AVERROR_LIST(ERROR_ಟ್ಯಾಗ್, ERROR_TAG2)
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ errno_codes[] = {
#ವ್ಯಾಖ್ಯಾನಿಸು ERRNO_ಸಂಕೇತ(ಸಂಕೇತ_3, DESC) AVERROR(ಸಂಕೇತ_3),
    STRERROR_LIST(ERRNO_ಸಂಕೇತ)
};

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    ಅಕ್ಷರ buf[AV_ERROR_MAX_STRING_ಗಾತ್ರ];
    ಪೂರ್ಣಾಂಕ ret = 0;

    ಗಾಗಿ (size_t i = 0; i < FF_ARRAY_ELEMS(ffmpeg_codes); i++) {
        ಪೂರ್ಣಾಂಕ ಅಂಕೆ = ffmpeg_codes[i].ಅಂಕೆ;

        ಆದರೆ (av_strerror(ಅಂಕೆ, buf, ಗಾತ್ರ(buf)) < 0) {
            ಬರೆ("%d: lookup failed [%s]\n", ಅಂಕೆ, ffmpeg_codes[i].ಟ್ಯಾಗ್);
            ret = 1;
            ಮುಂದುವರಿ;
        }
        ಬರೆ("%d: %s [%s]\n", ಅಂಕೆ, buf, ffmpeg_codes[i].ಟ್ಯಾಗ್);
    }

    ಗಾಗಿ (size_t i = 0; i < FF_ARRAY_ELEMS(errno_codes); i++) {
        ಆದರೆ (av_strerror(errno_codes[i], buf, ಗಾತ್ರ(buf)) < 0) {
            ಬರೆ("errno %d: lookup failed\n", AVUNERROR(errno_codes[i]));
            ret = 1;
        }
    }

    ಹಿಂತಿರುಗಿ ret;
}

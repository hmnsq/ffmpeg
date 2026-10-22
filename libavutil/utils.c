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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "avutil.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"

/**
 * @file
 * various utility functions
 */

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_get_media_type_string(ಎಣಿಕೆ AVMediaType media_type)
{
    ಆಯ್ಕೆ (media_type) {
    ಸ್ಥಿತಿ AVMEDIA_TYPE_VIDEO:      ಹಿಂತಿರುಗಿ "video";
    ಸ್ಥಿತಿ AVMEDIA_TYPE_AUDIO:      ಹಿಂತಿರುಗಿ "audio";
    ಸ್ಥಿತಿ AVMEDIA_TYPE_ದತ್ತಾಂಶ:       ಹಿಂತಿರುಗಿ "data";
    ಸ್ಥಿತಿ AVMEDIA_TYPE_SUBTITLE:   ಹಿಂತಿರುಗಿ "subtitle";
    ಸ್ಥಿತಿ AVMEDIA_TYPE_ATTACHMENT: ಹಿಂತಿರುಗಿ "attachment";
    ಪೂರ್ವನಿಯೋಜಿತ:                      ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
}

ಅಕ್ಷರ av_get_picture_type_char(ಎಣಿಕೆ AVPictureType pict_type)
{
    ಆಯ್ಕೆ (pict_type) {
    ಸ್ಥಿತಿ AV_PICTURE_TYPE_I:  ಹಿಂತಿರುಗಿ 'I';
    ಸ್ಥಿತಿ AV_PICTURE_TYPE_P:  ಹಿಂತಿರುಗಿ 'P';
    ಸ್ಥಿತಿ AV_PICTURE_TYPE_B:  ಹಿಂತಿರುಗಿ 'B';
    ಸ್ಥಿತಿ AV_PICTURE_TYPE_S:  ಹಿಂತಿರುಗಿ 'S';
    ಸ್ಥಿತಿ AV_PICTURE_TYPE_SI: ಹಿಂತಿರುಗಿ 'i';
    ಸ್ಥಿತಿ AV_PICTURE_TYPE_SP: ಹಿಂತಿರುಗಿ 'p';
    ಸ್ಥಿತಿ AV_PICTURE_TYPE_BI: ಹಿಂತಿರುಗಿ 'b';
    ಪೂರ್ವನಿಯೋಜಿತ:                 ಹಿಂತಿರುಗಿ '?';
    }
}

ಅಕ್ಷರ *av_fourcc_make_string(ಅಕ್ಷರ *buf, uint32_t fourcc)
{
    ಪೂರ್ಣಾಂಕ i;
    ಅಕ್ಷರ *orig_buf = buf;
    size_t buf_ಗಾತ್ರ = AV_FOURCC_MAX_STRING_ಗಾತ್ರ;

    ಗಾಗಿ (i = 0; i < 4; i++) {
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ c = fourcc & 0xff;
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ len = snprintf(buf, buf_ಗಾತ್ರ, print_chr ? "%c" : "[%d]", c);
        ಆದರೆ (len < 0)
            ನಿಲ್ಲಿಸು;
        buf += len;
        buf_ಗಾತ್ರ = buf_ಗಾತ್ರ > len ? buf_ಗಾತ್ರ - len : 0;
        fourcc >>= 8;
    }

    ಹಿಂತಿರುಗಿ orig_buf;
}

AVRational av_get_ಸಮಯ_ತಳ_q(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ (AVRational){1, AV_ಸಮಯ_ತಳ};
}
#ಆದರೆ FF_API_ASSERT_FPU
ಶೂನ್ಯ av_assert0_fpu(ಶೂನ್ಯ) {
#ಆದರೆ HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ ಅಸ್ಥಿರ (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#ಆದರೆ_ಅಂತ್ಯ
}
#ಆದರೆ_ಅಂತ್ಯ

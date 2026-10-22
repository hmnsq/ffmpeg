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

ಧ್ರುವ ವರ್ಣ *av_get_media_type_string(ಗಣನಾ AVMediaType media_type)
{
    ವಿಕಲ್ಪ (media_type) {
    ಪಕ್ಷ AVMEDIA_TYPE_VIDEO:      ಪ್ರತ್ಯಾಗಮ "video";
    ಪಕ್ಷ AVMEDIA_TYPE_AUDIO:      ಪ್ರತ್ಯಾಗಮ "audio";
    ಪಕ್ಷ AVMEDIA_TYPE_DATA:       ಪ್ರತ್ಯಾಗಮ "data";
    ಪಕ್ಷ AVMEDIA_TYPE_SUBTITLE:   ಪ್ರತ್ಯಾಗಮ "subtitle";
    ಪಕ್ಷ AVMEDIA_TYPE_ATTACHMENT: ಪ್ರತ್ಯಾಗಮ "attachment";
    ಸ್ವಭಾವ:                      ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
}

ವರ್ಣ av_get_picture_type_char(ಗಣನಾ AVPictureType pict_type)
{
    ವಿಕಲ್ಪ (pict_type) {
    ಪಕ್ಷ AV_PICTURE_TYPE_I:  ಪ್ರತ್ಯಾಗಮ 'I';
    ಪಕ್ಷ AV_PICTURE_TYPE_P:  ಪ್ರತ್ಯಾಗಮ 'P';
    ಪಕ್ಷ AV_PICTURE_TYPE_B:  ಪ್ರತ್ಯಾಗಮ 'B';
    ಪಕ್ಷ AV_PICTURE_TYPE_S:  ಪ್ರತ್ಯಾಗಮ 'S';
    ಪಕ್ಷ AV_PICTURE_TYPE_SI: ಪ್ರತ್ಯಾಗಮ 'i';
    ಪಕ್ಷ AV_PICTURE_TYPE_SP: ಪ್ರತ್ಯಾಗಮ 'p';
    ಪಕ್ಷ AV_PICTURE_TYPE_BI: ಪ್ರತ್ಯಾಗಮ 'b';
    ಸ್ವಭಾವ:                 ಪ್ರತ್ಯಾಗಮ '?';
    }
}

ವರ್ಣ *av_fourcc_make_string(ವರ್ಣ *buf, uint32_t fourcc)
{
    ಪೂರ್ಣಾಙ್ಕ i;
    ವರ್ಣ *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    ಪ್ರತಿ (i = 0; i < 4; i++) {
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ c = fourcc & 0xff;
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        ಯದಿ (len < 0)
            ಭಙ್ಗ;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    ಪ್ರತ್ಯಾಗಮ orig_buf;
}

AVRational av_get_time_base_q(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ (AVRational){1, AV_TIME_BASE};
}
#ಯದಿ FF_API_ASSERT_FPU
ಶೂನ್ಯ av_assert0_fpu(ಶೂನ್ಯ) {
#ಯದಿ HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ ಚಞ್ಚಲ (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

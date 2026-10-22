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

#include "config.h"
#include "avutil.h"
#include "avassert.h"

/**
 * @file
 * various utility functions
 */

const char *av_get_media_type_string(enum AVMediaType media_type)
{
    switch (media_type) {
    case AVMEDIA_TYPE_VIDEO:      반환 "video";
    case AVMEDIA_TYPE_AUDIO:      반환 "audio";
    case AVMEDIA_TYPE_DATA:       반환 "data";
    case AVMEDIA_TYPE_SUBTITLE:   반환 "subtitle";
    case AVMEDIA_TYPE_ATTACHMENT: 반환 "attachment";
    default:                      반환 NULL;
    }
}

char av_get_picture_type_char(enum AVPictureType pict_type)
{
    switch (pict_type) {
    case AV_PICTURE_TYPE_I:  반환 'I';
    case AV_PICTURE_TYPE_P:  반환 'P';
    case AV_PICTURE_TYPE_B:  반환 'B';
    case AV_PICTURE_TYPE_S:  반환 'S';
    case AV_PICTURE_TYPE_SI: 반환 'i';
    case AV_PICTURE_TYPE_SP: 반환 'p';
    case AV_PICTURE_TYPE_BI: 반환 'b';
    default:                 반환 '?';
    }
}

char *av_fourcc_make_string(char *buf, uint32_t fourcc)
{
    정수 i;
    char *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    위해 (i = 0; i < 4; i++) {
        const 정수 c = fourcc & 0xff;
        const 정수 print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        const 정수 len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        만약 (len < 0)
            break;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    반환 orig_buf;
}

AVRational av_get_time_base_q(void)
{
    반환 (AVRational){1, AV_TIME_BASE};
}
#만약 FF_API_ASSERT_FPU
void av_assert0_fpu(void) {
#만약 HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ volatile (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

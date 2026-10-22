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
    case AVMEDIA_TYPE_VIDEO:      戻る "video";
    case AVMEDIA_TYPE_AUDIO:      戻る "audio";
    case AVMEDIA_TYPE_DATA:       戻る "data";
    case AVMEDIA_TYPE_SUBTITLE:   戻る "subtitle";
    case AVMEDIA_TYPE_ATTACHMENT: 戻る "attachment";
    default:                      戻る NULL;
    }
}

char av_get_picture_type_char(enum AVPictureType pict_type)
{
    switch (pict_type) {
    case AV_PICTURE_TYPE_I:  戻る 'I';
    case AV_PICTURE_TYPE_P:  戻る 'P';
    case AV_PICTURE_TYPE_B:  戻る 'B';
    case AV_PICTURE_TYPE_S:  戻る 'S';
    case AV_PICTURE_TYPE_SI: 戻る 'i';
    case AV_PICTURE_TYPE_SP: 戻る 'p';
    case AV_PICTURE_TYPE_BI: 戻る 'b';
    default:                 戻る '?';
    }
}

char *av_fourcc_make_string(char *buf, uint32_t fourcc)
{
    整数 i;
    char *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    ために (i = 0; i < 4; i++) {
        const 整数 c = fourcc & 0xff;
        const 整数 print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        const 整数 len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        もし (len < 0)
            break;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    戻る orig_buf;
}

AVRational av_get_time_base_q(void)
{
    戻る (AVRational){1, AV_TIME_BASE};
}
#もし FF_API_ASSERT_FPU
void av_assert0_fpu(void) {
#もし HAVE_MMX_INLINE
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

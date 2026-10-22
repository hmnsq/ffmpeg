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

#شامل "config.h"
#شامل "avutil.h"
#شامل "avassert.h"

/**
 * @file
 * various utility functions
 */

ثابت حرف *av_get_media_type_string(شمار AVMediaType media_type)
{
    انتخاب (media_type) {
    حالت AVMEDIA_TYPE_VIDEO:      واپس "video";
    حالت AVMEDIA_TYPE_AUDIO:      واپس "audio";
    حالت AVMEDIA_TYPE_ڈیٹا:       واپس "data";
    حالت AVMEDIA_TYPE_SUBTITLE:   واپس "subtitle";
    حالت AVMEDIA_TYPE_ATTACHMENT: واپس "attachment";
    طےشدہ:                      واپس تہی;
    }
}

حرف av_get_picture_type_char(شمار AVPictureType pict_type)
{
    انتخاب (pict_type) {
    حالت AV_PICTURE_TYPE_I:  واپس 'I';
    حالت AV_PICTURE_TYPE_P:  واپس 'P';
    حالت AV_PICTURE_TYPE_B:  واپس 'B';
    حالت AV_PICTURE_TYPE_S:  واپس 'S';
    حالت AV_PICTURE_TYPE_SI: واپس 'i';
    حالت AV_PICTURE_TYPE_SP: واپس 'p';
    حالت AV_PICTURE_TYPE_BI: واپس 'b';
    طےشدہ:                 واپس '?';
    }
}

حرف *av_fourcc_make_string(حرف *buf, uint32_t fourcc)
{
    صحیح i;
    حرف *orig_buf = buf;
    size_t buf_سائز = AV_FOURCC_MAX_STRING_سائز;

    برائے (i = 0; i < 4; i++) {
        ثابت صحیح c = fourcc & 0xff;
        ثابت صحیح print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ثابت صحیح len = snprintf(buf, buf_سائز, print_chr ? "%c" : "[%d]", c);
        اگر (len < 0)
            توڑو;
        buf += len;
        buf_سائز = buf_سائز > len ? buf_سائز - len : 0;
        fourcc >>= 8;
    }

    واپس orig_buf;
}

AVRational av_get_وقت_بنیاد_q(خالی)
{
    واپس (AVRational){1, AV_وقت_بنیاد};
}
#اگر FF_API_ASSERT_FPU
خالی av_assert0_fpu(خالی) {
#اگر HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ متلون (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#اگر_ختم
}
#اگر_ختم

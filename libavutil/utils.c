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

#ضمن "config.h"
#ضمن "avutil.h"
#ضمن "avassert.h"

/**
 * @file
 * various utility functions
 */

ثابت حرف *av_get_media_type_string(تعداد AVMediaType media_type)
{
    بدل (media_type) {
    حالة AVMEDIA_TYPE_VIDEO:      أرجع "video";
    حالة AVMEDIA_TYPE_AUDIO:      أرجع "audio";
    حالة AVMEDIA_TYPE_معلومات:       أرجع "data";
    حالة AVMEDIA_TYPE_SUBTITLE:   أرجع "subtitle";
    حالة AVMEDIA_TYPE_ATTACHMENT: أرجع "attachment";
    افتراضي:                      أرجع عدم;
    }
}

حرف av_get_picture_type_char(تعداد AVPictureType pict_type)
{
    بدل (pict_type) {
    حالة AV_PICTURE_TYPE_I:  أرجع 'I';
    حالة AV_PICTURE_TYPE_P:  أرجع 'P';
    حالة AV_PICTURE_TYPE_B:  أرجع 'B';
    حالة AV_PICTURE_TYPE_S:  أرجع 'S';
    حالة AV_PICTURE_TYPE_SI: أرجع 'i';
    حالة AV_PICTURE_TYPE_SP: أرجع 'p';
    حالة AV_PICTURE_TYPE_BI: أرجع 'b';
    افتراضي:                 أرجع '?';
    }
}

حرف *av_fourcc_make_string(حرف *buf, uint32_t fourcc)
{
    صحيح i;
    حرف *orig_buf = buf;
    size_t buf_سائيز = AV_FOURCC_MAX_STRING_سائيز;

    لكل (i = 0; i < 4; i++) {
        ثابت صحيح c = fourcc & 0xff;
        ثابت صحيح print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ثابت صحيح len = snprintf(buf, buf_سائيز, print_chr ? "%c" : "[%d]", c);
        إذا (len < 0)
            اكسر;
        buf += len;
        buf_سائيز = buf_سائيز > len ? buf_سائيز - len : 0;
        fourcc >>= 8;
    }

    أرجع orig_buf;
}

AVRational av_get_وقت_بنياد_q(فراغ)
{
    أرجع (AVRational){1, AV_وقت_بنياد};
}
#إذا FF_API_ASSERT_FPU
فراغ av_assert0_fpu(فراغ) {
#إذا HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ متطاير (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#جيڪڏهن_پورو
}
#جيڪڏهن_پورو

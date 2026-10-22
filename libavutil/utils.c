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
    حالة AVMEDIA_TYPE_VIDEO:      إرجاع "video";
    حالة AVMEDIA_TYPE_AUDIO:      إرجاع "audio";
    حالة AVMEDIA_TYPE_DATA:       إرجاع "data";
    حالة AVMEDIA_TYPE_SUBTITLE:   إرجاع "subtitle";
    حالة AVMEDIA_TYPE_ATTACHMENT: إرجاع "attachment";
    افتراضي:                      إرجاع عدم;
    }
}

حرف av_get_picture_type_char(تعداد AVPictureType pict_type)
{
    بدل (pict_type) {
    حالة AV_PICTURE_TYPE_I:  إرجاع 'I';
    حالة AV_PICTURE_TYPE_P:  إرجاع 'P';
    حالة AV_PICTURE_TYPE_B:  إرجاع 'B';
    حالة AV_PICTURE_TYPE_S:  إرجاع 'S';
    حالة AV_PICTURE_TYPE_SI: إرجاع 'i';
    حالة AV_PICTURE_TYPE_SP: إرجاع 'p';
    حالة AV_PICTURE_TYPE_BI: إرجاع 'b';
    افتراضي:                 إرجاع '?';
    }
}

حرف *av_fourcc_make_string(حرف *buf, uint32_t fourcc)
{
    صحيح i;
    حرف *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    لكل (i = 0; i < 4; i++) {
        ثابت صحيح c = fourcc & 0xff;
        ثابت صحيح print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ثابت صحيح len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        إذا (len < 0)
            اكسر;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    إرجاع orig_buf;
}

AVRational av_get_time_base_q(فراغ)
{
    إرجاع (AVRational){1, AV_TIME_BASE};
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
#endif
}
#endif

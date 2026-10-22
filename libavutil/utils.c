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

ثابت نویسه *av_get_media_type_string(شمارش AVMediaType media_type)
{
    انتخاب (media_type) {
    حالت AVMEDIA_TYPE_VIDEO:      بازگشت "video";
    حالت AVMEDIA_TYPE_AUDIO:      بازگشت "audio";
    حالت AVMEDIA_TYPE_DATA:       بازگشت "data";
    حالت AVMEDIA_TYPE_SUBTITLE:   بازگشت "subtitle";
    حالت AVMEDIA_TYPE_ATTACHMENT: بازگشت "attachment";
    پیشفرض:                      بازگشت پوچ;
    }
}

نویسه av_get_picture_type_char(شمارش AVPictureType pict_type)
{
    انتخاب (pict_type) {
    حالت AV_PICTURE_TYPE_I:  بازگشت 'I';
    حالت AV_PICTURE_TYPE_P:  بازگشت 'P';
    حالت AV_PICTURE_TYPE_B:  بازگشت 'B';
    حالت AV_PICTURE_TYPE_S:  بازگشت 'S';
    حالت AV_PICTURE_TYPE_SI: بازگشت 'i';
    حالت AV_PICTURE_TYPE_SP: بازگشت 'p';
    حالت AV_PICTURE_TYPE_BI: بازگشت 'b';
    پیشفرض:                 بازگشت '?';
    }
}

نویسه *av_fourcc_make_string(نویسه *buf, uint32_t fourcc)
{
    صحیح i;
    نویسه *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    برای (i = 0; i < 4; i++) {
        ثابت صحیح c = fourcc & 0xff;
        ثابت صحیح print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ثابت صحیح len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        اگر (len < 0)
            بشکن;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    بازگشت orig_buf;
}

AVRational av_get_time_base_q(تهی)
{
    بازگشت (AVRational){1, AV_TIME_BASE};
}
#اگر FF_API_ASSERT_FPU
تهی av_assert0_fpu(تهی) {
#اگر HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ فرار (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

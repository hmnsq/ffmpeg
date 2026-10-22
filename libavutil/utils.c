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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "avutil.h"
#অন্তর্ভাব "avassert.h"

/**
 * @file
 * various utility functions
 */

ধ্রুব বর্ণ *av_get_media_type_string(গণনা AVMediaType media_type)
{
    বিকল্প (media_type) {
    পক্ষ AVMEDIA_TYPE_VIDEO:      প্রত্যাগম "video";
    পক্ষ AVMEDIA_TYPE_AUDIO:      প্রত্যাগম "audio";
    পক্ষ AVMEDIA_TYPE_DATA:       প্রত্যাগম "data";
    পক্ষ AVMEDIA_TYPE_SUBTITLE:   প্রত্যাগম "subtitle";
    পক্ষ AVMEDIA_TYPE_ATTACHMENT: প্রত্যাগম "attachment";
    স্বভাব:                      প্রত্যাগম রিক্ত;
    }
}

বর্ণ av_get_picture_type_char(গণনা AVPictureType pict_type)
{
    বিকল্প (pict_type) {
    পক্ষ AV_PICTURE_TYPE_I:  প্রত্যাগম 'I';
    পক্ষ AV_PICTURE_TYPE_P:  প্রত্যাগম 'P';
    পক্ষ AV_PICTURE_TYPE_B:  প্রত্যাগম 'B';
    পক্ষ AV_PICTURE_TYPE_S:  প্রত্যাগম 'S';
    পক্ষ AV_PICTURE_TYPE_SI: প্রত্যাগম 'i';
    পক্ষ AV_PICTURE_TYPE_SP: প্রত্যাগম 'p';
    পক্ষ AV_PICTURE_TYPE_BI: প্রত্যাগম 'b';
    স্বভাব:                 প্রত্যাগম '?';
    }
}

বর্ণ *av_fourcc_make_string(বর্ণ *buf, uint32_t fourcc)
{
    পূর্ণাঙ্ক i;
    বর্ণ *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    প্রতি (i = 0; i < 4; i++) {
        ধ্রুব পূর্ণাঙ্ক c = fourcc & 0xff;
        ধ্রুব পূর্ণাঙ্ক print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ধ্রুব পূর্ণাঙ্ক len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        যদি (len < 0)
            ভঙ্গ;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    প্রত্যাগম orig_buf;
}

AVRational av_get_time_base_q(শূন্য)
{
    প্রত্যাগম (AVRational){1, AV_TIME_BASE};
}
#যদি FF_API_ASSERT_FPU
শূন্য av_assert0_fpu(শূন্য) {
#যদি HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ চঞ্চল (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

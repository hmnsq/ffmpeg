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

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "avutil.h"
#অন্তর্ভাৱ "avassert.h"

/**
 * @file
 * various utility functions
 */

ধ্রুৱ ৱর্ণ *av_get_media_type_string(গণনা AVMediaType media_type)
{
    ৱিকল্প (media_type) {
    পক্ষ AVMEDIA_TYPE_VIDEO:      ঘূৰাই "video";
    পক্ষ AVMEDIA_TYPE_AUDIO:      ঘূৰাই "audio";
    পক্ষ AVMEDIA_TYPE_DATA:       ঘূৰাই "data";
    পক্ষ AVMEDIA_TYPE_SUBTITLE:   ঘূৰাই "subtitle";
    পক্ষ AVMEDIA_TYPE_ATTACHMENT: ঘূৰাই "attachment";
    স্ৱভাৱ:                      ঘূৰাই রিক্ত;
    }
}

ৱর্ণ av_get_picture_type_char(গণনা AVPictureType pict_type)
{
    ৱিকল্প (pict_type) {
    পক্ষ AV_PICTURE_TYPE_I:  ঘূৰাই 'I';
    পক্ষ AV_PICTURE_TYPE_P:  ঘূৰাই 'P';
    পক্ষ AV_PICTURE_TYPE_B:  ঘূৰাই 'B';
    পক্ষ AV_PICTURE_TYPE_S:  ঘূৰাই 'S';
    পক্ষ AV_PICTURE_TYPE_SI: ঘূৰাই 'i';
    পক্ষ AV_PICTURE_TYPE_SP: ঘূৰাই 'p';
    পক্ষ AV_PICTURE_TYPE_BI: ঘূৰাই 'b';
    স্ৱভাৱ:                 ঘূৰাই '?';
    }
}

ৱর্ণ *av_fourcc_make_string(ৱর্ণ *buf, uint32_t fourcc)
{
    পূর্ণাঙ্ক i;
    ৱর্ণ *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    বাবে (i = 0; i < 4; i++) {
        ধ্রুৱ পূর্ণাঙ্ক c = fourcc & 0xff;
        ধ্রুৱ পূর্ণাঙ্ক print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ধ্রুৱ পূর্ণাঙ্ক len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        যদি (len < 0)
            ভঙ্গ;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    ঘূৰাই orig_buf;
}

AVRational av_get_time_base_q(শূন্য)
{
    ঘূৰাই (AVRational){1, AV_TIME_BASE};
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

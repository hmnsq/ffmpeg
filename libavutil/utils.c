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

ধ্রুবক অক্ষর *av_get_media_type_string(গণনা AVMediaType media_type)
{
    নির্বাচন (media_type) {
    ক্ষেত্র AVMEDIA_TYPE_VIDEO:      ফেরত "video";
    ক্ষেত্র AVMEDIA_TYPE_AUDIO:      ফেরত "audio";
    ক্ষেত্র AVMEDIA_TYPE_তথ্য:       ফেরত "data";
    ক্ষেত্র AVMEDIA_TYPE_SUBTITLE:   ফেরত "subtitle";
    ক্ষেত্র AVMEDIA_TYPE_ATTACHMENT: ফেরত "attachment";
    পূর্বনির্ধারিত:                      ফেরত ফাঁকা;
    }
}

অক্ষর av_get_picture_type_char(গণনা AVPictureType pict_type)
{
    নির্বাচন (pict_type) {
    ক্ষেত্র AV_PICTURE_TYPE_I:  ফেরত 'I';
    ক্ষেত্র AV_PICTURE_TYPE_P:  ফেরত 'P';
    ক্ষেত্র AV_PICTURE_TYPE_B:  ফেরত 'B';
    ক্ষেত্র AV_PICTURE_TYPE_S:  ফেরত 'S';
    ক্ষেত্র AV_PICTURE_TYPE_SI: ফেরত 'i';
    ক্ষেত্র AV_PICTURE_TYPE_SP: ফেরত 'p';
    ক্ষেত্র AV_PICTURE_TYPE_BI: ফেরত 'b';
    পূর্বনির্ধারিত:                 ফেরত '?';
    }
}

অক্ষর *av_fourcc_make_string(অক্ষর *buf, uint32_t fourcc)
{
    পূর্ণসংখ্যা i;
    অক্ষর *orig_buf = buf;
    size_t buf_আকার = AV_FOURCC_MAX_STRING_আকার;

    জন্য (i = 0; i < 4; i++) {
        ধ্রুবক পূর্ণসংখ্যা c = fourcc & 0xff;
        ধ্রুবক পূর্ণসংখ্যা print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ধ্রুবক পূর্ণসংখ্যা len = snprintf(buf, buf_আকার, print_chr ? "%c" : "[%d]", c);
        যদি (len < 0)
            বিরতি;
        buf += len;
        buf_আকার = buf_আকার > len ? buf_আকার - len : 0;
        fourcc >>= 8;
    }

    ফেরত orig_buf;
}

AVRational av_get_time_base_q(শূন্য)
{
    ফেরত (AVRational){1, AV_TIME_BASE};
}
#যদি FF_API_ASSERT_FPU
শূন্য av_assert0_fpu(শূন্য) {
#যদি HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ অস্থির (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

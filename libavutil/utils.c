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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "avutil.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"

/**
 * @file
 * various utility functions
 */

ଅଚଳ ଅକ୍ଷର *av_get_media_type_string(ଗଣନା AVMediaType media_type)
{
    ବାଛ (media_type) {
    ସ୍ଥିତି AVMEDIA_TYPE_VIDEO:      ଫେରନ୍ତୁ "video";
    ସ୍ଥିତି AVMEDIA_TYPE_AUDIO:      ଫେରନ୍ତୁ "audio";
    ସ୍ଥିତି AVMEDIA_TYPE_DATA:       ଫେରନ୍ତୁ "data";
    ସ୍ଥିତି AVMEDIA_TYPE_SUBTITLE:   ଫେରନ୍ତୁ "subtitle";
    ସ୍ଥିତି AVMEDIA_TYPE_ATTACHMENT: ଫେରନ୍ତୁ "attachment";
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:                      ଫେରନ୍ତୁ ଖାଲି;
    }
}

ଅକ୍ଷର av_get_picture_type_char(ଗଣନା AVPictureType pict_type)
{
    ବାଛ (pict_type) {
    ସ୍ଥିତି AV_PICTURE_TYPE_I:  ଫେରନ୍ତୁ 'I';
    ସ୍ଥିତି AV_PICTURE_TYPE_P:  ଫେରନ୍ତୁ 'P';
    ସ୍ଥିତି AV_PICTURE_TYPE_B:  ଫେରନ୍ତୁ 'B';
    ସ୍ଥିତି AV_PICTURE_TYPE_S:  ଫେରନ୍ତୁ 'S';
    ସ୍ଥିତି AV_PICTURE_TYPE_SI: ଫେରନ୍ତୁ 'i';
    ସ୍ଥିତି AV_PICTURE_TYPE_SP: ଫେରନ୍ତୁ 'p';
    ସ୍ଥିତି AV_PICTURE_TYPE_BI: ଫେରନ୍ତୁ 'b';
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:                 ଫେରନ୍ତୁ '?';
    }
}

ଅକ୍ଷର *av_fourcc_make_string(ଅକ୍ଷର *buf, uint32_t fourcc)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ଅକ୍ଷର *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    ପାଇଁ (i = 0; i < 4; i++) {
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = fourcc & 0xff;
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        ଯଦି (len < 0)
            ଭାଙ୍ଗ;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    ଫେରନ୍ତୁ orig_buf;
}

AVRational av_get_time_base_q(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ (AVRational){1, AV_TIME_BASE};
}
#ଯଦି FF_API_ASSERT_FPU
ଶୂନ୍ୟ av_assert0_fpu(ଶୂନ୍ୟ) {
#ଯଦି HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ ଅସ୍ଥିର (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

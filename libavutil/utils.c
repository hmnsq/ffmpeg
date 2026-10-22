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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "avutil.h"
#અન્તર્ભાવ "avassert.h"

/**
 * @file
 * various utility functions
 */

અચલ અક્ષર *av_get_media_type_string(ગણના AVMediaType media_type)
{
    પસંદગી (media_type) {
    સ્થિતિ AVMEDIA_TYPE_VIDEO:      પાછા "video";
    સ્થિતિ AVMEDIA_TYPE_AUDIO:      પાછા "audio";
    સ્થિતિ AVMEDIA_TYPE_DATA:       પાછા "data";
    સ્થિતિ AVMEDIA_TYPE_SUBTITLE:   પાછા "subtitle";
    સ્થિતિ AVMEDIA_TYPE_ATTACHMENT: પાછા "attachment";
    મૂળભૂત:                      પાછા ખાલી;
    }
}

અક્ષર av_get_picture_type_char(ગણના AVPictureType pict_type)
{
    પસંદગી (pict_type) {
    સ્થિતિ AV_PICTURE_TYPE_I:  પાછા 'I';
    સ્થિતિ AV_PICTURE_TYPE_P:  પાછા 'P';
    સ્થિતિ AV_PICTURE_TYPE_B:  પાછા 'B';
    સ્થિતિ AV_PICTURE_TYPE_S:  પાછા 'S';
    સ્થિતિ AV_PICTURE_TYPE_SI: પાછા 'i';
    સ્થિતિ AV_PICTURE_TYPE_SP: પાછા 'p';
    સ્થિતિ AV_PICTURE_TYPE_BI: પાછા 'b';
    મૂળભૂત:                 પાછા '?';
    }
}

અક્ષર *av_fourcc_make_string(અક્ષર *buf, uint32_t fourcc)
{
    પૂર્ણાંક i;
    અક્ષર *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    માટે (i = 0; i < 4; i++) {
        અચલ પૂર્ણાંક c = fourcc & 0xff;
        અચલ પૂર્ણાંક print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        અચલ પૂર્ણાંક len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        જો (len < 0)
            તોડો;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    પાછા orig_buf;
}

AVRational av_get_time_base_q(શૂન્ય)
{
    પાછા (AVRational){1, AV_TIME_BASE};
}
#જો FF_API_ASSERT_FPU
શૂન્ય av_assert0_fpu(શૂન્ય) {
#જો HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ અસ્થિર (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

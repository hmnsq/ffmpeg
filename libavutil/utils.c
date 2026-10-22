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

#अन्तर्भाव "config.h"
#अन्तर्भाव "avutil.h"
#अन्तर्भाव "avassert.h"

/**
 * @file
 * various utility functions
 */

ध्रुव वर्ण *av_get_media_type_string(गणना AVMediaType media_type)
{
    विकल्प (media_type) {
    पक्ष AVMEDIA_TYPE_VIDEO:      प्रत्यागम "video";
    पक्ष AVMEDIA_TYPE_AUDIO:      प्रत्यागम "audio";
    पक्ष AVMEDIA_TYPE_DATA:       प्रत्यागम "data";
    पक्ष AVMEDIA_TYPE_SUBTITLE:   प्रत्यागम "subtitle";
    पक्ष AVMEDIA_TYPE_ATTACHMENT: प्रत्यागम "attachment";
    स्वभाव:                      प्रत्यागम रिक्त;
    }
}

वर्ण av_get_picture_type_char(गणना AVPictureType pict_type)
{
    विकल्प (pict_type) {
    पक्ष AV_PICTURE_TYPE_I:  प्रत्यागम 'I';
    पक्ष AV_PICTURE_TYPE_P:  प्रत्यागम 'P';
    पक्ष AV_PICTURE_TYPE_B:  प्रत्यागम 'B';
    पक्ष AV_PICTURE_TYPE_S:  प्रत्यागम 'S';
    पक्ष AV_PICTURE_TYPE_SI: प्रत्यागम 'i';
    पक्ष AV_PICTURE_TYPE_SP: प्रत्यागम 'p';
    पक्ष AV_PICTURE_TYPE_BI: प्रत्यागम 'b';
    स्वभाव:                 प्रत्यागम '?';
    }
}

वर्ण *av_fourcc_make_string(वर्ण *buf, uint32_t fourcc)
{
    पूर्णाङ्क i;
    वर्ण *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    प्रति (i = 0; i < 4; i++) {
        ध्रुव पूर्णाङ्क c = fourcc & 0xff;
        ध्रुव पूर्णाङ्क print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ध्रुव पूर्णाङ्क len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        यदि (len < 0)
            भङ्ग;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    प्रत्यागम orig_buf;
}

AVRational av_get_time_base_q(शून्य)
{
    प्रत्यागम (AVRational){1, AV_TIME_BASE};
}
#यदि FF_API_ASSERT_FPU
शून्य av_assert0_fpu(शून्य) {
#यदि HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ चञ्चल (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

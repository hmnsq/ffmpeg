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

स्थिरांक अक्षर *av_get_media_type_string(गणना AVMediaType media_type)
{
    निवड (media_type) {
    स्थिती AVMEDIA_TYPE_VIDEO:      परत "video";
    स्थिती AVMEDIA_TYPE_AUDIO:      परत "audio";
    स्थिती AVMEDIA_TYPE_DATA:       परत "data";
    स्थिती AVMEDIA_TYPE_SUBTITLE:   परत "subtitle";
    स्थिती AVMEDIA_TYPE_ATTACHMENT: परत "attachment";
    पूर्वनिर्धारित:                      परत रिक्त;
    }
}

अक्षर av_get_picture_type_char(गणना AVPictureType pict_type)
{
    निवड (pict_type) {
    स्थिती AV_PICTURE_TYPE_I:  परत 'I';
    स्थिती AV_PICTURE_TYPE_P:  परत 'P';
    स्थिती AV_PICTURE_TYPE_B:  परत 'B';
    स्थिती AV_PICTURE_TYPE_S:  परत 'S';
    स्थिती AV_PICTURE_TYPE_SI: परत 'i';
    स्थिती AV_PICTURE_TYPE_SP: परत 'p';
    स्थिती AV_PICTURE_TYPE_BI: परत 'b';
    पूर्वनिर्धारित:                 परत '?';
    }
}

अक्षर *av_fourcc_make_string(अक्षर *buf, uint32_t fourcc)
{
    पूर्णांक i;
    अक्षर *orig_buf = buf;
    माप_प्रकार buf_size = AV_FOURCC_MAX_STRING_SIZE;

    साठी (i = 0; i < 4; i++) {
        स्थिरांक पूर्णांक c = fourcc & 0xff;
        स्थिरांक पूर्णांक print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && म_अक्षर(". -_", c));
        स्थिरांक पूर्णांक len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        जर (len < 0)
            थांबा;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    परत orig_buf;
}

AVRational av_get_time_base_q(शून्य)
{
    परत (AVRational){1, AV_TIME_BASE};
}
#जर FF_API_ASSERT_FPU
शून्य av_assert0_fpu(शून्य) {
#जर HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ अस्थिर (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

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

#समावेश "config.h"
#समावेश "avutil.h"
#समावेश "avassert.h"

/**
 * @file
 * various utility functions
 */

स्थिर अक्षर *av_get_media_type_string(क्रमागत AVMediaType media_type)
{
    चयन (media_type) {
    हाल AVMEDIA_TYPE_VIDEO:      वापस "video";
    हाल AVMEDIA_TYPE_AUDIO:      वापस "audio";
    हाल AVMEDIA_TYPE_तथ्य:       वापस "data";
    हाल AVMEDIA_TYPE_SUBTITLE:   वापस "subtitle";
    हाल AVMEDIA_TYPE_ATTACHMENT: वापस "attachment";
    शेष:                      वापस शून्य;
    }
}

अक्षर av_get_picture_type_char(क्रमागत AVPictureType pict_type)
{
    चयन (pict_type) {
    हाल AV_PICTURE_TYPE_I:  वापस 'I';
    हाल AV_PICTURE_TYPE_P:  वापस 'P';
    हाल AV_PICTURE_TYPE_B:  वापस 'B';
    हाल AV_PICTURE_TYPE_S:  वापस 'S';
    हाल AV_PICTURE_TYPE_SI: वापस 'i';
    हाल AV_PICTURE_TYPE_SP: वापस 'p';
    हाल AV_PICTURE_TYPE_BI: वापस 'b';
    शेष:                 वापस '?';
    }
}

अक्षर *av_fourcc_make_string(अक्षर *buf, uint32_t fourcc)
{
    पूर्णांक i;
    अक्षर *orig_buf = buf;
    माप_प्रकार buf_आकार = AV_FOURCC_MAX_STRING_आकार;

    क्रम (i = 0; i < 4; i++) {
        स्थिर पूर्णांक c = fourcc & 0xff;
        स्थिर पूर्णांक print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && म_अक्षर(". -_", c));
        स्थिर पूर्णांक len = snprintf(buf, buf_आकार, print_chr ? "%c" : "[%d]", c);
        अगर (len < 0)
            अवरोध;
        buf += len;
        buf_आकार = buf_आकार > len ? buf_आकार - len : 0;
        fourcc >>= 8;
    }

    वापस orig_buf;
}

AVRational av_get_time_base_q(व्योम)
{
    वापस (AVRational){1, AV_TIME_BASE};
}
#अगर FF_API_ASSERT_FPU
व्योम av_assert0_fpu(व्योम) {
#अगर HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ अस्थिर (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#पूर्ण_अगर
}
#पूर्ण_अगर

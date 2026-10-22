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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "avutil.h"
#അന്തര്ഭാവ "avassert.h"

/**
 * @file
 * various utility functions
 */

സ്ഥിരം അക്ഷരം *av_get_media_type_string(എണ്ണൽ AVMediaType media_type)
{
    തിരഞ്ഞെടുപ്പ് (media_type) {
    അവസ്ഥ AVMEDIA_TYPE_VIDEO:      തിരികെ "video";
    അവസ്ഥ AVMEDIA_TYPE_AUDIO:      തിരികെ "audio";
    അവസ്ഥ AVMEDIA_TYPE_DATA:       തിരികെ "data";
    അവസ്ഥ AVMEDIA_TYPE_SUBTITLE:   തിരികെ "subtitle";
    അവസ്ഥ AVMEDIA_TYPE_ATTACHMENT: തിരികെ "attachment";
    സ്ഥിരസ്ഥിതി:                      തിരികെ ശൂന്യ;
    }
}

അക്ഷരം av_get_picture_type_char(എണ്ണൽ AVPictureType pict_type)
{
    തിരഞ്ഞെടുപ്പ് (pict_type) {
    അവസ്ഥ AV_PICTURE_TYPE_I:  തിരികെ 'I';
    അവസ്ഥ AV_PICTURE_TYPE_P:  തിരികെ 'P';
    അവസ്ഥ AV_PICTURE_TYPE_B:  തിരികെ 'B';
    അവസ്ഥ AV_PICTURE_TYPE_S:  തിരികെ 'S';
    അവസ്ഥ AV_PICTURE_TYPE_SI: തിരികെ 'i';
    അവസ്ഥ AV_PICTURE_TYPE_SP: തിരികെ 'p';
    അവസ്ഥ AV_PICTURE_TYPE_BI: തിരികെ 'b';
    സ്ഥിരസ്ഥിതി:                 തിരികെ '?';
    }
}

അക്ഷരം *av_fourcc_make_string(അക്ഷരം *buf, uint32_t fourcc)
{
    പൂർണ്ണസംഖ്യ i;
    അക്ഷരം *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    വേണ്ടി (i = 0; i < 4; i++) {
        സ്ഥിരം പൂർണ്ണസംഖ്യ c = fourcc & 0xff;
        സ്ഥിരം പൂർണ്ണസംഖ്യ print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        സ്ഥിരം പൂർണ്ണസംഖ്യ len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        എങ്കിൽ (len < 0)
            നിർത്തുക;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    തിരികെ orig_buf;
}

AVRational av_get_time_base_q(ശൂന്യം)
{
    തിരികെ (AVRational){1, AV_TIME_BASE};
}
#എങ്കിൽ FF_API_ASSERT_FPU
ശൂന്യം av_assert0_fpu(ശൂന്യം) {
#എങ്കിൽ HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ അസ്ഥിര (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

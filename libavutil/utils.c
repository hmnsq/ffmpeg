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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avutil.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"

/**
 * @file
 * various utility functions
 */

ਅਚਲ ਅੱਖਰ *av_get_media_type_string(ਗਿਣਤੀ AVMediaType media_type)
{
    ਚੋਣ (media_type) {
    ਹਾਲਤ AVMEDIA_TYPE_VIDEO:      ਵਾਪਸ "video";
    ਹਾਲਤ AVMEDIA_TYPE_AUDIO:      ਵਾਪਸ "audio";
    ਹਾਲਤ AVMEDIA_TYPE_ਅੰਕੜੇ:       ਵਾਪਸ "data";
    ਹਾਲਤ AVMEDIA_TYPE_SUBTITLE:   ਵਾਪਸ "subtitle";
    ਹਾਲਤ AVMEDIA_TYPE_ATTACHMENT: ਵਾਪਸ "attachment";
    ਮੂਲ:                      ਵਾਪਸ ਨਿਰਾ;
    }
}

ਅੱਖਰ av_get_picture_type_char(ਗਿਣਤੀ AVPictureType pict_type)
{
    ਚੋਣ (pict_type) {
    ਹਾਲਤ AV_PICTURE_TYPE_I:  ਵਾਪਸ 'I';
    ਹਾਲਤ AV_PICTURE_TYPE_P:  ਵਾਪਸ 'P';
    ਹਾਲਤ AV_PICTURE_TYPE_B:  ਵਾਪਸ 'B';
    ਹਾਲਤ AV_PICTURE_TYPE_S:  ਵਾਪਸ 'S';
    ਹਾਲਤ AV_PICTURE_TYPE_SI: ਵਾਪਸ 'i';
    ਹਾਲਤ AV_PICTURE_TYPE_SP: ਵਾਪਸ 'p';
    ਹਾਲਤ AV_PICTURE_TYPE_BI: ਵਾਪਸ 'b';
    ਮੂਲ:                 ਵਾਪਸ '?';
    }
}

ਅੱਖਰ *av_fourcc_make_string(ਅੱਖਰ *buf, uint32_t fourcc)
{
    ਪੂਰਨ i;
    ਅੱਖਰ *orig_buf = buf;
    size_t buf_ਮਾਪ = AV_FOURCC_MAX_STRING_ਮਾਪ;

    ਲਈ (i = 0; i < 4; i++) {
        ਅਚਲ ਪੂਰਨ c = fourcc & 0xff;
        ਅਚਲ ਪੂਰਨ print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        ਅਚਲ ਪੂਰਨ len = snprintf(buf, buf_ਮਾਪ, print_chr ? "%c" : "[%d]", c);
        ਜੇ (len < 0)
            ਰੋਕੋ;
        buf += len;
        buf_ਮਾਪ = buf_ਮਾਪ > len ? buf_ਮਾਪ - len : 0;
        fourcc >>= 8;
    }

    ਵਾਪਸ orig_buf;
}

AVRational av_get_ਸਮਾਂ_ਅਧਾਰ_q(ਖਾਲੀ)
{
    ਵਾਪਸ (AVRational){1, AV_ਸਮਾਂ_ਅਧਾਰ};
}
#ਜੇ FF_API_ASSERT_FPU
ਖਾਲੀ av_assert0_fpu(ਖਾਲੀ) {
#ਜੇ HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ ਅਸਥਿਰ (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#ਜੇ_ਅੰਤ
}
#ਜੇ_ਅੰਤ

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

#include "config.h"
#include "avutil.h"
#include "avassert.h"

/**
 * @file
 * various utility functions
 */

const var_na *av_get_media_type_string(ga_nanaa AVMediaType media_type)
{
    switch (media_type) {
    pak_sa AVMEDIA_TYPE_VIDEO:      ᤀᤡᤴ "video";
    pak_sa AVMEDIA_TYPE_AUDIO:      ᤀᤡᤴ "audio";
    pak_sa AVMEDIA_TYPE_DATA:       ᤀᤡᤴ "data";
    pak_sa AVMEDIA_TYPE_SUBTITLE:   ᤀᤡᤴ "subtitle";
    pak_sa AVMEDIA_TYPE_ATTACHMENT: ᤀᤡᤴ "attachment";
    default:                      ᤀᤡᤴ NULL;
    }
}

var_na av_get_picture_type_char(ga_nanaa AVPictureType pict_type)
{
    switch (pict_type) {
    pak_sa AV_PICTURE_TYPE_I:  ᤀᤡᤴ 'I';
    pak_sa AV_PICTURE_TYPE_P:  ᤀᤡᤴ 'P';
    pak_sa AV_PICTURE_TYPE_B:  ᤀᤡᤴ 'B';
    pak_sa AV_PICTURE_TYPE_S:  ᤀᤡᤴ 'S';
    pak_sa AV_PICTURE_TYPE_SI: ᤀᤡᤴ 'i';
    pak_sa AV_PICTURE_TYPE_SP: ᤀᤡᤴ 'p';
    pak_sa AV_PICTURE_TYPE_BI: ᤀᤡᤴ 'b';
    default:                 ᤀᤡᤴ '?';
    }
}

var_na *av_fourcc_make_string(var_na *buf, uint32_t fourcc)
{
    puur_naa_nka i;
    var_na *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    for (i = 0; i < 4; i++) {
        const puur_naa_nka c = fourcc & 0xff;
        const puur_naa_nka print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        const puur_naa_nka len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        ᤀᤡ᤺ (len < 0)
            bha_nga;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    ᤀᤡᤴ orig_buf;
}

AVRational av_get_time_base_q(void)
{
    ᤀᤡᤴ (AVRational){1, AV_TIME_BASE};
}
#ᤀᤡ᤺ FF_API_ASSERT_FPU
void av_assert0_fpu(void) {
#ᤀᤡ᤺ HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ ca_ncala (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

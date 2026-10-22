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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "avutil.h"
#அந்தர்பாவ "avassert.h"

/**
 * @file
 * various utility functions
 */

மாறிலி எழுத்து *av_get_media_type_string(எண்ணிக்கை AVMediaType media_type)
{
    தேர்வு (media_type) {
    நிலை AVMEDIA_TYPE_VIDEO:      திரும்பு "video";
    நிலை AVMEDIA_TYPE_AUDIO:      திரும்பு "audio";
    நிலை AVMEDIA_TYPE_DATA:       திரும்பு "data";
    நிலை AVMEDIA_TYPE_SUBTITLE:   திரும்பு "subtitle";
    நிலை AVMEDIA_TYPE_ATTACHMENT: திரும்பு "attachment";
    இயல்பு:                      திரும்பு வெற்று;
    }
}

எழுத்து av_get_picture_type_char(எண்ணிக்கை AVPictureType pict_type)
{
    தேர்வு (pict_type) {
    நிலை AV_PICTURE_TYPE_I:  திரும்பு 'I';
    நிலை AV_PICTURE_TYPE_P:  திரும்பு 'P';
    நிலை AV_PICTURE_TYPE_B:  திரும்பு 'B';
    நிலை AV_PICTURE_TYPE_S:  திரும்பு 'S';
    நிலை AV_PICTURE_TYPE_SI: திரும்பு 'i';
    நிலை AV_PICTURE_TYPE_SP: திரும்பு 'p';
    நிலை AV_PICTURE_TYPE_BI: திரும்பு 'b';
    இயல்பு:                 திரும்பு '?';
    }
}

எழுத்து *av_fourcc_make_string(எழுத்து *buf, uint32_t fourcc)
{
    முழு i;
    எழுத்து *orig_buf = buf;
    size_t buf_size = AV_FOURCC_MAX_STRING_SIZE;

    க்கு (i = 0; i < 4; i++) {
        மாறிலி முழு c = fourcc & 0xff;
        மாறிலி முழு print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        மாறிலி முழு len = snprintf(buf, buf_size, print_chr ? "%c" : "[%d]", c);
        எனில் (len < 0)
            நிறுத்து;
        buf += len;
        buf_size = buf_size > len ? buf_size - len : 0;
        fourcc >>= 8;
    }

    திரும்பு orig_buf;
}

AVRational av_get_time_base_q(வெறுமை)
{
    திரும்பு (AVRational){1, AV_TIME_BASE};
}
#எனில் FF_API_ASSERT_FPU
வெறுமை av_assert0_fpu(வெறுமை) {
#எனில் HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ நிலையற்ற (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#endif
}
#endif

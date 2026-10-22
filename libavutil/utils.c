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

#అన్తర్భావ "config.h"
#అన్తర్భావ "avutil.h"
#అన్తర్భావ "avassert.h"

/**
 * @file
 * various utility functions
 */

స్థిరరాశి అక్షరం *av_get_media_type_string(గణన AVMediaType media_type)
{
    ఎంపిక (media_type) {
    స్థితి AVMEDIA_TYPE_VIDEO:      తిరిగి "video";
    స్థితి AVMEDIA_TYPE_AUDIO:      తిరిగి "audio";
    స్థితి AVMEDIA_TYPE_దత్తాంశం:       తిరిగి "data";
    స్థితి AVMEDIA_TYPE_SUBTITLE:   తిరిగి "subtitle";
    స్థితి AVMEDIA_TYPE_ATTACHMENT: తిరిగి "attachment";
    అప్రమేయ:                      తిరిగి ఖాళీ;
    }
}

అక్షరం av_get_picture_type_char(గణన AVPictureType pict_type)
{
    ఎంపిక (pict_type) {
    స్థితి AV_PICTURE_TYPE_I:  తిరిగి 'I';
    స్థితి AV_PICTURE_TYPE_P:  తిరిగి 'P';
    స్థితి AV_PICTURE_TYPE_B:  తిరిగి 'B';
    స్థితి AV_PICTURE_TYPE_S:  తిరిగి 'S';
    స్థితి AV_PICTURE_TYPE_SI: తిరిగి 'i';
    స్థితి AV_PICTURE_TYPE_SP: తిరిగి 'p';
    స్థితి AV_PICTURE_TYPE_BI: తిరిగి 'b';
    అప్రమేయ:                 తిరిగి '?';
    }
}

అక్షరం *av_fourcc_make_string(అక్షరం *buf, uint32_t fourcc)
{
    పూర్ణాంకం i;
    అక్షరం *orig_buf = buf;
    size_t buf_కొలత = AV_FOURCC_MAX_STRING_కొలత;

    కొరకు (i = 0; i < 4; i++) {
        స్థిరరాశి పూర్ణాంకం c = fourcc & 0xff;
        స్థిరరాశి పూర్ణాంకం print_chr = (c >= '0' && c <= '9') ||
                              (c >= 'a' && c <= 'z') ||
                              (c >= 'A' && c <= 'Z') ||
                              (c && strchr(". -_", c));
        స్థిరరాశి పూర్ణాంకం len = snprintf(buf, buf_కొలత, print_chr ? "%c" : "[%d]", c);
        ఒకవేళ (len < 0)
            ఆపు;
        buf += len;
        buf_కొలత = buf_కొలత > len ? buf_కొలత - len : 0;
        fourcc >>= 8;
    }

    తిరిగి orig_buf;
}

AVRational av_get_సమయం_పునాది_q(శూన్య)
{
    తిరిగి (AVRational){1, AV_సమయం_పునాది};
}
#ఒకవేళ FF_API_ASSERT_FPU
శూన్య av_assert0_fpu(శూన్య) {
#ఒకవేళ HAVE_MMX_INLINE
    uint16_t state[14];
     __asm__ అస్థిర (
        "fstenv %0 \n\t"
        : "+m" (state)
        :
        : "memory"
    );
    av_assert0((state[4] & 3) == 3);
#అయితే_ముగింపు
}
#అయితే_ముగింపు

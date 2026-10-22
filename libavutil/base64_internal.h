/*
 * Copyright (c) 2006 Ryan Martell. (rdm4@martellventures.com)
 *
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

#اگر_تعریف_نشده AVUTIL_BASE64_داخلی_H
#تعریف_کن AVUTIL_BASE64_داخلی_H

#ضمن <stdint.h>
#ضمن "intreadwrite.h"

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

ساكن مضمن حرف *ff_base64_encode_c(حرف *بیرون, ثابت uint8_t *درون, صحيح درون_اندازه, ثابت حرف *b64)
{
    حرف *ret, *dst;
    بیعلامت i_بیتها = 0;
    صحيح i_لغزش = 0;
    صحيح بایتها_مانده = درون_اندازه;

    ret = dst = بیرون;
    طالما (بایتها_مانده > 3) {
        i_بیتها = AV_RB32(درون);
        درون += 3; بایتها_مانده -= 3;
        *dst++ = b64[ i_بیتها>>26        ];
        *dst++ = b64[(i_بیتها>>20) & 0x3F];
        *dst++ = b64[(i_بیتها>>14) & 0x3F];
        *dst++ = b64[(i_بیتها>>8 ) & 0x3F];
    }
    i_بیتها = 0;
    طالما (بایتها_مانده) {
        i_بیتها = (i_بیتها << 8) + *درون++;
        بایتها_مانده--;
        i_لغزش += 8;
    }
    طالما (i_لغزش > 0) {
        *dst++ = b64[(i_بیتها << 6 >> i_لغزش) & 0x3f];
        i_لغزش -= 6;
    }
    طالما ((dst - ret) & 3)
        *dst++ = '=';
    *dst = '\0';

    أرجع ret;
}

#پایان_اگر /* AVUTIL_BASE64_INTERNAL_H */

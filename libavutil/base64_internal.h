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

#که_نه_تعریف_شوی AVUTIL_BASE64_دننی_H
#تعریف_کړه AVUTIL_BASE64_دننی_H

#ضمن <stdint.h>
#ضمن "intreadwrite.h"

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

ساكن مضمن حرف *ff_base64_encode_c(حرف *بهر, ثابت uint8_t *دننه, صحيح دننه_اندازه, ثابت حرف *b64)
{
    حرف *ret, *dst;
    بینښه i_بټونه = 0;
    صحيح i_ښويدنه = 0;
    صحيح بایټونه_پاتې_شوی = دننه_اندازه;

    ret = dst = بهر;
    طالما (بایټونه_پاتې_شوی > 3) {
        i_بټونه = AV_RB32(دننه);
        دننه += 3; بایټونه_پاتې_شوی -= 3;
        *dst++ = b64[ i_بټونه>>26        ];
        *dst++ = b64[(i_بټونه>>20) & 0x3F];
        *dst++ = b64[(i_بټونه>>14) & 0x3F];
        *dst++ = b64[(i_بټونه>>8 ) & 0x3F];
    }
    i_بټونه = 0;
    طالما (بایټونه_پاتې_شوی) {
        i_بټونه = (i_بټونه << 8) + *دننه++;
        بایټونه_پاتې_شوی--;
        i_ښويدنه += 8;
    }
    طالما (i_ښويدنه > 0) {
        *dst++ = b64[(i_بټونه << 6 >> i_ښويدنه) & 0x3f];
        i_ښويدنه -= 6;
    }
    طالما ((dst - ret) & 3)
        *dst++ = '=';
    *dst = '\0';

    أرجع ret;
}

#د_که_پای /* AVUTIL_BASE64_INTERNAL_H */

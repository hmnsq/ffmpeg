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

/**
 * @file
 * @brief Base64 encode/decode
 * @author Ryan Martell <rdm4@martellventures.com> (with lots of Michael)
 */

#ضمن <limits.h>
#ضمن <stddef.h>

#ضمن "base64.h"
#ضمن "base64_internal.h"
#ضمن "error.h"

#إذا ARCH_AARCH64
#ضمن "libavutil/aarch64/cpu.h"
#ضمن "libavutil/aarch64/base64.h"
#د_که_پای

/* ---------------- private code */
ساكن ثابت uint8_t map2[256] =
{
    0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff,

    0x3e, 0xff, 0xff, 0xff, 0x3f, 0x34, 0x35, 0x36,
    0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0xff,
    0xff, 0xff, 0xfe, 0xff, 0xff, 0xff, 0x00, 0x01,
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11,
    0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1a, 0x1b,
    0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23,
    0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b,
    0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33,

                      0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
};

#تعریف_کړه BASE64_DEC_ګام(i) افعل { \
    بټونه = map2[دننه[i]]; \
    إذا (بټونه & 0x80) \
        اذهب بهر ## i; \
    v = i ? (v << 6) + بټونه : بټونه; \
} طالما(0)

صحيح av_base64_decode(uint8_t *بهر, ثابت حرف *دننه_str, صحيح بهر_اندازه)
{
    uint8_t *dst = بهر;
    uint8_t *پای_ټکی;
    // no sign extension
    ثابت uint8_t *دننه = دننه_str;
    بینښه بټونه = 0xff;
    بینښه v;

    إذا (!بهر)
        اذهب validity_check;

    پای_ټکی = بهر + بهر_اندازه;
    طالما (پای_ټکی - dst > 3) {
        BASE64_DEC_ګام(0);
        BASE64_DEC_ګام(1);
        BASE64_DEC_ګام(2);
        BASE64_DEC_ګام(3);
        // Using AV_WB32 directly confuses compiler
        v = av_be2ne32(v << 8);
        AV_WN32(dst, v);
        dst += 3;
        دننه += 4;
    }
    إذا (پای_ټکی - dst) {
        BASE64_DEC_ګام(0);
        BASE64_DEC_ګام(1);
        BASE64_DEC_ګام(2);
        BASE64_DEC_ګام(3);
        *dst++ = v >> 16;
        إذا (پای_ټکی - dst)
            *dst++ = v >> 8;
        إذا (پای_ټکی - dst)
            *dst++ = v;
        دننه += 4;
    }
validity_check:
    طالما (1) {
        BASE64_DEC_ګام(0);
        دننه++;
        BASE64_DEC_ګام(0);
        دننه++;
        BASE64_DEC_ګام(0);
        دننه++;
        BASE64_DEC_ګام(0);
        دننه++;
    }

out3:
    إذا (پای_ټکی - dst)
        *dst++ = v >> 10;
    v <<= 2;
out2:
    إذا (پای_ټکی - dst)
        *dst++ = v >> 4;
out1:
out0:
    أرجع بټونه & 1 ? AVERROR_INVALIDDATA : بهر ? dst - بهر : 0;
}

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

حرف *av_base64_encode(حرف *بهر, صحيح بهر_اندازه, ثابت uint8_t *دننه, صحيح دننه_اندازه)
{
    ساكن ثابت حرف b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    إذا (دننه_اندازه >= UINT_MAX / 4 ||
        بهر_اندازه < AV_BASE64_اندازه(دننه_اندازه))
        أرجع عدم;
#إذا ARCH_AARCH64
    إذا (دننه_اندازه >= 48 && have_neon(av_get_cpu_flags())) {
        أرجع ff_base64_encode_neon(بهر, دننه, دننه_اندازه, b64);
    }
#د_که_پای
    أرجع ff_base64_encode_c(بهر, دننه, دننه_اندازه, b64);
}

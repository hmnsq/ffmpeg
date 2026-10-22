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
#جيڪڏهن_پورو

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

#وصف_ڪريو BASE64_DEC_قدم(i) افعل { \
    بٽ = map2[اندريون[i]]; \
    إذا (بٽ & 0x80) \
        اذهب ٻاهريون ## i; \
    v = i ? (v << 6) + بٽ : بٽ; \
} طالما(0)

صحيح av_base64_decode(uint8_t *ٻاهريون, ثابت حرف *اندريون_str, صحيح ٻاهريون_سائيز)
{
    uint8_t *dst = ٻاهريون;
    uint8_t *پڇاڙي;
    // no sign extension
    ثابت uint8_t *اندريون = اندريون_str;
    بنانشان بٽ = 0xff;
    بنانشان v;

    إذا (!ٻاهريون)
        اذهب validity_check;

    پڇاڙي = ٻاهريون + ٻاهريون_سائيز;
    طالما (پڇاڙي - dst > 3) {
        BASE64_DEC_قدم(0);
        BASE64_DEC_قدم(1);
        BASE64_DEC_قدم(2);
        BASE64_DEC_قدم(3);
        // Using AV_WB32 directly confuses compiler
        v = av_be2ne32(v << 8);
        AV_WN32(dst, v);
        dst += 3;
        اندريون += 4;
    }
    إذا (پڇاڙي - dst) {
        BASE64_DEC_قدم(0);
        BASE64_DEC_قدم(1);
        BASE64_DEC_قدم(2);
        BASE64_DEC_قدم(3);
        *dst++ = v >> 16;
        إذا (پڇاڙي - dst)
            *dst++ = v >> 8;
        إذا (پڇاڙي - dst)
            *dst++ = v;
        اندريون += 4;
    }
validity_check:
    طالما (1) {
        BASE64_DEC_قدم(0);
        اندريون++;
        BASE64_DEC_قدم(0);
        اندريون++;
        BASE64_DEC_قدم(0);
        اندريون++;
        BASE64_DEC_قدم(0);
        اندريون++;
    }

out3:
    إذا (پڇاڙي - dst)
        *dst++ = v >> 10;
    v <<= 2;
out2:
    إذا (پڇاڙي - dst)
        *dst++ = v >> 4;
out1:
out0:
    أرجع بٽ & 1 ? AVERROR_INVALIDDATA : ٻاهريون ? dst - ٻاهريون : 0;
}

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

حرف *av_base64_encode(حرف *ٻاهريون, صحيح ٻاهريون_سائيز, ثابت uint8_t *اندريون, صحيح اندريون_سائيز)
{
    ساكن ثابت حرف b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    إذا (اندريون_سائيز >= UINT_MAX / 4 ||
        ٻاهريون_سائيز < AV_BASE64_سائيز(اندريون_سائيز))
        أرجع عدم;
#إذا ARCH_AARCH64
    إذا (اندريون_سائيز >= 48 && have_neon(av_get_cpu_flags())) {
        أرجع ff_base64_encode_neon(ٻاهريون, اندريون, اندريون_سائيز, b64);
    }
#جيڪڏهن_پورو
    أرجع ff_base64_encode_c(ٻاهريون, اندريون, اندريون_سائيز, b64);
}

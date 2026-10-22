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

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stddef.h>

#অন্তর্ভাব "base64.h"
#অন্তর্ভাব "base64_internal.h"
#অন্তর্ভাব "error.h"

#যদি ARCH_AARCH64
#অন্তর্ভাব "libavutil/aarch64/cpu.h"
#অন্তর্ভাব "libavutil/aarch64/base64.h"
#endif

/* ---------------- private code */
স্থির ধ্রুবক uint8_t map2[256] =
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

#define BASE64_DEC_STEP(i) করো { \
    bits = map2[in[i]]; \
    যদি (bits & 0x80) \
        যাও out ## i; \
    v = i ? (v << 6) + bits : bits; \
} যখন(0)

পূর্ণসংখ্যা av_base64_decode(uint8_t *out, ধ্রুবক অক্ষর *in_str, পূর্ণসংখ্যা out_আকার)
{
    uint8_t *dst = out;
    uint8_t *end;
    // no sign extension
    ধ্রুবক uint8_t *in = in_str;
    unsigned bits = 0xff;
    unsigned v;

    যদি (!out)
        যাও validity_check;

    end = out + out_আকার;
    যখন (end - dst > 3) {
        BASE64_DEC_STEP(0);
        BASE64_DEC_STEP(1);
        BASE64_DEC_STEP(2);
        BASE64_DEC_STEP(3);
        // Using AV_WB32 directly confuses compiler
        v = av_be2ne32(v << 8);
        AV_WN32(dst, v);
        dst += 3;
        in += 4;
    }
    যদি (end - dst) {
        BASE64_DEC_STEP(0);
        BASE64_DEC_STEP(1);
        BASE64_DEC_STEP(2);
        BASE64_DEC_STEP(3);
        *dst++ = v >> 16;
        যদি (end - dst)
            *dst++ = v >> 8;
        যদি (end - dst)
            *dst++ = v;
        in += 4;
    }
validity_check:
    যখন (1) {
        BASE64_DEC_STEP(0);
        in++;
        BASE64_DEC_STEP(0);
        in++;
        BASE64_DEC_STEP(0);
        in++;
        BASE64_DEC_STEP(0);
        in++;
    }

out3:
    যদি (end - dst)
        *dst++ = v >> 10;
    v <<= 2;
out2:
    যদি (end - dst)
        *dst++ = v >> 4;
out1:
out0:
    ফেরত bits & 1 ? AVERROR_INVALIDDATA : out ? dst - out : 0;
}

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

অক্ষর *av_base64_encode(অক্ষর *out, পূর্ণসংখ্যা out_আকার, ধ্রুবক uint8_t *in, পূর্ণসংখ্যা in_আকার)
{
    স্থির ধ্রুবক অক্ষর b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    যদি (in_আকার >= UINT_MAX / 4 ||
        out_আকার < AV_BASE64_আকার(in_আকার))
        ফেরত ফাঁকা;
#যদি ARCH_AARCH64
    যদি (in_আকার >= 48 && have_neon(av_get_cpu_flags())) {
        ফেরত ff_base64_encode_neon(out, in, in_আকার, b64);
    }
#endif
    ফেরত ff_base64_encode_c(out, in, in_আকার, b64);
}

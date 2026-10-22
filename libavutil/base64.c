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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "base64.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "base64_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"

#ਜੇ ARCH_AARCH64
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/aarch64/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/aarch64/base64.h"
#ਜੇ_ਅੰਤ

/* ---------------- private code */
ਸਥਿਰ ਅਚਲ uint8_t map2[256] =
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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BASE64_DEC_ਕਦਮ(i) ਕਰੋ { \
    ਬਿੱਟ = map2[ਵਿੱਚ_2[i]]; \
    ਜੇ (ਬਿੱਟ & 0x80) \
        ਜਾਓ ਬਾਹਰਲਾ ## i; \
    v = i ? (v << 6) + ਬਿੱਟ : ਬਿੱਟ; \
} ਜਦੋਂ(0)

ਪੂਰਨ av_base64_decode(uint8_t *ਬਾਹਰਲਾ, ਅਚਲ ਅੱਖਰ *ਵਿੱਚ_str, ਪੂਰਨ ਬਾਹਰਲਾ_ਮਾਪ)
{
    uint8_t *dst = ਬਾਹਰਲਾ;
    uint8_t *ਸਿਰਾ;
    // no sign extension
    ਅਚਲ uint8_t *ਵਿੱਚ_2 = ਵਿੱਚ_str;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਬਿੱਟ = 0xff;
    ਬਿਨਾਨਿਸ਼ਾਨੀ v;

    ਜੇ (!ਬਾਹਰਲਾ)
        ਜਾਓ validity_check;

    ਸਿਰਾ = ਬਾਹਰਲਾ + ਬਾਹਰਲਾ_ਮਾਪ;
    ਜਦੋਂ (ਸਿਰਾ - dst > 3) {
        BASE64_DEC_ਕਦਮ(0);
        BASE64_DEC_ਕਦਮ(1);
        BASE64_DEC_ਕਦਮ(2);
        BASE64_DEC_ਕਦਮ(3);
        // Using AV_WB32 directly confuses compiler
        v = av_be2ne32(v << 8);
        AV_WN32(dst, v);
        dst += 3;
        ਵਿੱਚ_2 += 4;
    }
    ਜੇ (ਸਿਰਾ - dst) {
        BASE64_DEC_ਕਦਮ(0);
        BASE64_DEC_ਕਦਮ(1);
        BASE64_DEC_ਕਦਮ(2);
        BASE64_DEC_ਕਦਮ(3);
        *dst++ = v >> 16;
        ਜੇ (ਸਿਰਾ - dst)
            *dst++ = v >> 8;
        ਜੇ (ਸਿਰਾ - dst)
            *dst++ = v;
        ਵਿੱਚ_2 += 4;
    }
validity_check:
    ਜਦੋਂ (1) {
        BASE64_DEC_ਕਦਮ(0);
        ਵਿੱਚ_2++;
        BASE64_DEC_ਕਦਮ(0);
        ਵਿੱਚ_2++;
        BASE64_DEC_ਕਦਮ(0);
        ਵਿੱਚ_2++;
        BASE64_DEC_ਕਦਮ(0);
        ਵਿੱਚ_2++;
    }

out3:
    ਜੇ (ਸਿਰਾ - dst)
        *dst++ = v >> 10;
    v <<= 2;
out2:
    ਜੇ (ਸਿਰਾ - dst)
        *dst++ = v >> 4;
out1:
out0:
    ਵਾਪਸ ਬਿੱਟ & 1 ? AVERROR_INVALIDDATA : ਬਾਹਰਲਾ ? dst - ਬਾਹਰਲਾ : 0;
}

/*****************************************************************************
* b64_encode: Stolen from VLC's http.c.
* Simplified by Michael.
* Fixed edge cases and made it work from data (vs. strings) by Ryan.
*****************************************************************************/

ਅੱਖਰ *av_base64_encode(ਅੱਖਰ *ਬਾਹਰਲਾ, ਪੂਰਨ ਬਾਹਰਲਾ_ਮਾਪ, ਅਚਲ uint8_t *ਵਿੱਚ_2, ਪੂਰਨ ਵਿੱਚ_ਮਾਪ)
{
    ਸਥਿਰ ਅਚਲ ਅੱਖਰ b64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    ਜੇ (ਵਿੱਚ_ਮਾਪ >= UINT_MAX / 4 ||
        ਬਾਹਰਲਾ_ਮਾਪ < AV_BASE64_ਮਾਪ(ਵਿੱਚ_ਮਾਪ))
        ਵਾਪਸ ਨਿਰਾ;
#ਜੇ ARCH_AARCH64
    ਜੇ (ਵਿੱਚ_ਮਾਪ >= 48 && have_neon(av_get_cpu_flags())) {
        ਵਾਪਸ ff_base64_encode_neon(ਬਾਹਰਲਾ, ਵਿੱਚ_2, ਵਿੱਚ_ਮਾਪ, b64);
    }
#ਜੇ_ਅੰਤ
    ਵਾਪਸ ff_base64_encode_c(ਬਾਹਰਲਾ, ਵਿੱਚ_2, ਵਿੱਚ_ਮਾਪ, b64);
}

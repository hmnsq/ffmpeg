/*
 * Copyright (C) 2007 Michael Niedermayer <michaelni@gmx.at>
 * Copyright (C) 2013 James Almer
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

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bswap.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "ripemd.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

/** hash context */
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ AVRIPEMD {
    uint8_t  digest_len;  ///< digest length in 32-bit words
    uint64_t ਗਿਣਤੀ_2;       ///< number of bytes in buffer
    uint8_t  ਬਫਰ[64];  ///< 512-bit buffer of input values used in hash updating
    uint32_t state[10];   ///< current hash value
    /** function used to update hash for 512-bit input block */
    ਖਾਲੀ     (*transform)(uint32_t *state, ਅਚਲ uint8_t ਬਫਰ[64]);
} AVRIPEMD;

ਅਚਲ ਪੂਰਨ av_ripemd_ਮਾਪ = ਆਕਾਰ(AVRIPEMD);

ਬਣਤਰ AVRIPEMD *av_ripemd_alloc(ਖਾਲੀ)
{
    ਵਾਪਸ av_mallocz(ਆਕਾਰ(ਬਣਤਰ AVRIPEMD));
}

ਸਥਿਰ ਅਚਲ uint32_t KA[4] = {
    0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xa953fd4e
};

ਸਥਿਰ ਅਚਲ uint32_t KB[4] = {
    0x50a28be6, 0x5c4dd124, 0x6d703ef3, 0x7a6d76e9
};

ਸਥਿਰ ਅਚਲ ਪੂਰਨ ROTA[80] = {
    11, 14, 15, 12,  5,  8,  7 , 9, 11, 13, 14, 15,  6,  7,  9,  8,
     7 , 6,  8, 13, 11,  9,  7, 15,  7, 12, 15,  9, 11,  7, 13, 12,
    11, 13,  6,  7, 14,  9, 13, 15, 14,  8, 13,  6,  5, 12,  7,  5,
    11, 12, 14, 15, 14, 15,  9,  8,  9, 14,  5,  6,  8,  6,  5, 12,
     9, 15,  5, 11,  6,  8, 13, 12,  5, 12, 13, 14, 11,  8,  5,  6
};

ਸਥਿਰ ਅਚਲ ਪੂਰਨ ROTB[80] = {
     8,  9,  9, 11, 13, 15, 15,  5,  7,  7,  8, 11, 14, 14, 12,  6,
     9, 13, 15,  7, 12,  8,  9, 11,  7,  7, 12,  7,  6, 15, 13, 11,
     9,  7, 15, 11,  8,  6,  6, 14, 12, 13,  5, 14, 13, 13,  7,  5,
    15,  5,  8, 11, 14, 14,  6, 14,  6,  9, 12,  9, 12,  5, 15,  8,
     8,  5, 12,  9, 12,  5, 14,  6,  8, 13,  6,  5, 15, 13, 11, 11
};

ਸਥਿਰ ਅਚਲ ਪੂਰਨ WA[80] = {
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
     7,  4, 13,  1, 10,  6, 15,  3, 12,  0,  9,  5,  2, 14, 11,  8,
     3, 10, 14,  4,  9, 15,  8,  1,  2,  7,  0,  6, 13, 11,  5, 12,
     1,  9, 11, 10,  0,  8, 12,  4, 13,  3,  7, 15, 14,  5,  6,  2,
     4,  0,  5,  9,  7, 12,  2, 10, 14,  1,  3,  8, 11,  6, 15, 13
};

ਸਥਿਰ ਅਚਲ ਪੂਰਨ WB[80] = {
     5, 14,  7,  0,  9,  2, 11,  4, 13,  6, 15,  8,  1, 10,  3, 12,
     6, 11,  3,  7,  0, 13,  5, 10, 14, 15,  8, 12,  4,  9,  1,  2,
    15,  5,  1,  3,  7, 14,  6,  9, 11,  8, 12,  2, 10,  0,  4, 13,
     8,  6,  4,  1,  3, 11, 15,  0,  5, 12,  2, 13,  9,  7, 10, 14,
    12, 15, 10,  4,  1,  5,  8,  7,  6,  2, 13, 14,  0,  3,  9, 11
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ rol(ਮੁੱਲ, ਬਿੱਟ) (((ਮੁੱਲ) << (ਬਿੱਟ)) | ((ਮੁੱਲ) >> (32 - (ਬਿੱਟ))))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUND128_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h)                               \
    a = rol(a + ((  b ^ c  ^ d)      + ਖੰਡ[WA[n]]),         ROTA[n]); \
    e = rol(e + ((((f ^ g) & h) ^ g) + ਖੰਡ[WB[n]] + KB[0]), ROTB[n]); \
    n++

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUND128_16_ਮੰਜ਼ਿਲ_31(a,b,c,d,e,f,g,h)                              \
    a = rol(a + ((((c ^ d) & b) ^ d) + ਖੰਡ[WA[n]] + KA[0]), ROTA[n]); \
    e = rol(e + (((~g | f) ^ h)      + ਖੰਡ[WB[n]] + KB[1]), ROTB[n]); \
    n++

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUND128_32_ਮੰਜ਼ਿਲ_47(a,b,c,d,e,f,g,h)                              \
    a = rol(a + (((~c | b) ^ d)      + ਖੰਡ[WA[n]] + KA[1]), ROTA[n]); \
    e = rol(e + ((((g ^ h) & f) ^ h) + ਖੰਡ[WB[n]] + KB[2]), ROTB[n]); \
    n++

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUND128_48_ਮੰਜ਼ਿਲ_63(a,b,c,d,e,f,g,h)                              \
    a = rol(a + ((((b ^ c) & d) ^ c) + ਖੰਡ[WA[n]] + KA[2]), ROTA[n]); \
    e = rol(e + ((  f ^ g  ^ h)      + ਖੰਡ[WB[n]]),         ROTB[n]); \
    n++

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ R128_0                          \
    ROUND128_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h);  \
    ROUND128_0_ਮੰਜ਼ਿਲ_15(d,a,b,c,h,e,f,g);  \
    ROUND128_0_ਮੰਜ਼ਿਲ_15(c,d,a,b,g,h,e,f);  \
    ROUND128_0_ਮੰਜ਼ਿਲ_15(b,c,d,a,f,g,h,e)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ R128_16                         \
    ROUND128_16_ਮੰਜ਼ਿਲ_31(a,b,c,d,e,f,g,h); \
    ROUND128_16_ਮੰਜ਼ਿਲ_31(d,a,b,c,h,e,f,g); \
    ROUND128_16_ਮੰਜ਼ਿਲ_31(c,d,a,b,g,h,e,f); \
    ROUND128_16_ਮੰਜ਼ਿਲ_31(b,c,d,a,f,g,h,e)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ R128_32                         \
    ROUND128_32_ਮੰਜ਼ਿਲ_47(a,b,c,d,e,f,g,h); \
    ROUND128_32_ਮੰਜ਼ਿਲ_47(d,a,b,c,h,e,f,g); \
    ROUND128_32_ਮੰਜ਼ਿਲ_47(c,d,a,b,g,h,e,f); \
    ROUND128_32_ਮੰਜ਼ਿਲ_47(b,c,d,a,f,g,h,e)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ R128_48                         \
    ROUND128_48_ਮੰਜ਼ਿਲ_63(a,b,c,d,e,f,g,h); \
    ROUND128_48_ਮੰਜ਼ਿਲ_63(d,a,b,c,h,e,f,g); \
    ROUND128_48_ਮੰਜ਼ਿਲ_63(c,d,a,b,g,h,e,f); \
    ROUND128_48_ਮੰਜ਼ਿਲ_63(b,c,d,a,f,g,h,e)

ਸਥਿਰ ਖਾਲੀ ripemd128_transform(uint32_t *state, ਅਚਲ uint8_t ਬਫਰ[64])
{
    uint32_t a, b, c, d, e, f, g, h, t av_ਅਣਵਰਤਿਆ;
    uint32_t ਖੰਡ[16];
    ਪੂਰਨ n;

    a = e = state[0];
    b = f = state[1];
    c = g = state[2];
    d = h = state[3];

    ਲਈ (n = 0; n < 16; n++)
        ਖੰਡ[n] = AV_RL32(ਬਫਰ + 4 * n);
    n = 0;

#ਜੇ CONFIG_SMALL
    ਲਈ (; n < 16;) {
        ROUND128_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h);
        t = d; d = c; c = b; b = a; a = t;
        t = h; h = g; g = f; f = e; e = t;
    }

    ਲਈ (; n < 32;) {
        ROUND128_16_ਮੰਜ਼ਿਲ_31(a,b,c,d,e,f,g,h);
        t = d; d = c; c = b; b = a; a = t;
        t = h; h = g; g = f; f = e; e = t;
    }

    ਲਈ (; n < 48;) {
        ROUND128_32_ਮੰਜ਼ਿਲ_47(a,b,c,d,e,f,g,h);
        t = d; d = c; c = b; b = a; a = t;
        t = h; h = g; g = f; f = e; e = t;
    }

    ਲਈ (; n < 64;) {
        ROUND128_48_ਮੰਜ਼ਿਲ_63(a,b,c,d,e,f,g,h);
        t = d; d = c; c = b; b = a; a = t;
        t = h; h = g; g = f; f = e; e = t;
    }
#ਨਹੀਂਤਾਂ

    R128_0; R128_0; R128_0; R128_0;

    R128_16; R128_16; R128_16; R128_16;

    R128_32; R128_32; R128_32; R128_32;

    R128_48; R128_48; R128_48; R128_48;
#ਜੇ_ਅੰਤ

    h += c + state[1];
    state[1] = state[2] + d + e;
    state[2] = state[3] + a + f;
    state[3] = state[0] + b + g;
    state[0] = h;
}

ਸਥਿਰ ਖਾਲੀ ripemd256_transform(uint32_t *state, ਅਚਲ uint8_t ਬਫਰ[64])
{
    uint32_t a, b, c, d, e, f, g, h, t av_ਅਣਵਰਤਿਆ;
    uint32_t ਖੰਡ[16];
    ਪੂਰਨ n;

    a = state[0]; b = state[1]; c = state[2]; d = state[3];
    e = state[4]; f = state[5]; g = state[6]; h = state[7];

    ਲਈ (n = 0; n < 16; n++)
        ਖੰਡ[n] = AV_RL32(ਬਫਰ + 4 * n);
    n = 0;

#ਜੇ CONFIG_SMALL
    ਲਈ (; n < 16;) {
        ROUND128_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h);
        t = d; d = c; c = b; b = a; a = t;
        t = h; h = g; g = f; f = e; e = t;
    }
    FFSWAP(uint32_t, a, e);

    ਲਈ (; n < 32;) {
        ROUND128_16_ਮੰਜ਼ਿਲ_31(a,b,c,d,e,f,g,h);
        t = d; d = c; c = b; b = a; a = t;
        t = h; h = g; g = f; f = e; e = t;
    }
    FFSWAP(uint32_t, b, f);

    ਲਈ (; n < 48;) {
        ROUND128_32_ਮੰਜ਼ਿਲ_47(a,b,c,d,e,f,g,h);
        t = d; d = c; c = b; b = a; a = t;
        t = h; h = g; g = f; f = e; e = t;
    }
    FFSWAP(uint32_t, c, g);

    ਲਈ (; n < 64;) {
        ROUND128_48_ਮੰਜ਼ਿਲ_63(a,b,c,d,e,f,g,h);
        t = d; d = c; c = b; b = a; a = t;
        t = h; h = g; g = f; f = e; e = t;
    }
    FFSWAP(uint32_t, d, h);
#ਨਹੀਂਤਾਂ

    R128_0; R128_0; R128_0; R128_0;
    FFSWAP(uint32_t, a, e);

    R128_16; R128_16; R128_16; R128_16;
    FFSWAP(uint32_t, b, f);

    R128_32; R128_32; R128_32; R128_32;
    FFSWAP(uint32_t, c, g);

    R128_48; R128_48; R128_48; R128_48;
    FFSWAP(uint32_t, d, h);
#ਜੇ_ਅੰਤ

    state[0] += a; state[1] += b; state[2] += c; state[3] += d;
    state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROTATE(x,y) \
    x = rol(x, 10); \
    y = rol(y, 10); \
    n++

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUND160_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h,i,j)                               \
    a = rol(a + ((  b ^ c  ^ d)      + ਖੰਡ[WA[n]]),         ROTA[n]) + e; \
    f = rol(f + (((~i | h) ^ g)      + ਖੰਡ[WB[n]] + KB[0]), ROTB[n]) + j; \
    ROTATE(c,h)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUND160_16_ਮੰਜ਼ਿਲ_31(a,b,c,d,e,f,g,h,i,j)                              \
    a = rol(a + ((((c ^ d) & b) ^ d) + ਖੰਡ[WA[n]] + KA[0]), ROTA[n]) + e; \
    f = rol(f + ((((g ^ h) & i) ^ h) + ਖੰਡ[WB[n]] + KB[1]), ROTB[n]) + j; \
    ROTATE(c,h)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUND160_32_ਮੰਜ਼ਿਲ_47(a,b,c,d,e,f,g,h,i,j)                              \
    a = rol(a + (((~c | b) ^ d)      + ਖੰਡ[WA[n]] + KA[1]), ROTA[n]) + e; \
    f = rol(f + (((~h | g) ^ i)      + ਖੰਡ[WB[n]] + KB[2]), ROTB[n]) + j; \
    ROTATE(c,h)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUND160_48_ਮੰਜ਼ਿਲ_63(a,b,c,d,e,f,g,h,i,j)                              \
    a = rol(a + ((((b ^ c) & d) ^ c) + ਖੰਡ[WA[n]] + KA[2]), ROTA[n]) + e; \
    f = rol(f + ((((h ^ i) & g) ^ i) + ਖੰਡ[WB[n]] + KB[3]), ROTB[n]) + j; \
    ROTATE(c,h)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ROUND160_64_ਮੰਜ਼ਿਲ_79(a,b,c,d,e,f,g,h,i,j)                              \
    a = rol(a + (((~d | c) ^ b)      + ਖੰਡ[WA[n]] + KA[3]), ROTA[n]) + e; \
    f = rol(f + ((  g ^ h  ^ i)      + ਖੰਡ[WB[n]]),         ROTB[n]) + j; \
    ROTATE(c,h)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ R160_0                              \
    ROUND160_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h,i,j);  \
    ROUND160_0_ਮੰਜ਼ਿਲ_15(e,a,b,c,d,j,f,g,h,i);  \
    ROUND160_0_ਮੰਜ਼ਿਲ_15(d,e,a,b,c,i,j,f,g,h);  \
    ROUND160_0_ਮੰਜ਼ਿਲ_15(c,d,e,a,b,h,i,j,f,g);  \
    ROUND160_0_ਮੰਜ਼ਿਲ_15(b,c,d,e,a,g,h,i,j,f)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ R160_16                             \
    ROUND160_16_ਮੰਜ਼ਿਲ_31(e,a,b,c,d,j,f,g,h,i); \
    ROUND160_16_ਮੰਜ਼ਿਲ_31(d,e,a,b,c,i,j,f,g,h); \
    ROUND160_16_ਮੰਜ਼ਿਲ_31(c,d,e,a,b,h,i,j,f,g); \
    ROUND160_16_ਮੰਜ਼ਿਲ_31(b,c,d,e,a,g,h,i,j,f); \
    ROUND160_16_ਮੰਜ਼ਿਲ_31(a,b,c,d,e,f,g,h,i,j)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ R160_32                             \
    ROUND160_32_ਮੰਜ਼ਿਲ_47(d,e,a,b,c,i,j,f,g,h); \
    ROUND160_32_ਮੰਜ਼ਿਲ_47(c,d,e,a,b,h,i,j,f,g); \
    ROUND160_32_ਮੰਜ਼ਿਲ_47(b,c,d,e,a,g,h,i,j,f); \
    ROUND160_32_ਮੰਜ਼ਿਲ_47(a,b,c,d,e,f,g,h,i,j); \
    ROUND160_32_ਮੰਜ਼ਿਲ_47(e,a,b,c,d,j,f,g,h,i)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ R160_48                             \
    ROUND160_48_ਮੰਜ਼ਿਲ_63(c,d,e,a,b,h,i,j,f,g); \
    ROUND160_48_ਮੰਜ਼ਿਲ_63(b,c,d,e,a,g,h,i,j,f); \
    ROUND160_48_ਮੰਜ਼ਿਲ_63(a,b,c,d,e,f,g,h,i,j); \
    ROUND160_48_ਮੰਜ਼ਿਲ_63(e,a,b,c,d,j,f,g,h,i); \
    ROUND160_48_ਮੰਜ਼ਿਲ_63(d,e,a,b,c,i,j,f,g,h)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ R160_64                             \
    ROUND160_64_ਮੰਜ਼ਿਲ_79(b,c,d,e,a,g,h,i,j,f); \
    ROUND160_64_ਮੰਜ਼ਿਲ_79(a,b,c,d,e,f,g,h,i,j); \
    ROUND160_64_ਮੰਜ਼ਿਲ_79(e,a,b,c,d,j,f,g,h,i); \
    ROUND160_64_ਮੰਜ਼ਿਲ_79(d,e,a,b,c,i,j,f,g,h); \
    ROUND160_64_ਮੰਜ਼ਿਲ_79(c,d,e,a,b,h,i,j,f,g)

ਸਥਿਰ ਖਾਲੀ ripemd160_transform(uint32_t *state, ਅਚਲ uint8_t ਬਫਰ[64])
{
    uint32_t a, b, c, d, e, f, g, h, i, j, t av_ਅਣਵਰਤਿਆ;
    uint32_t ਖੰਡ[16];
    ਪੂਰਨ n;

    a = f = state[0];
    b = g = state[1];
    c = h = state[2];
    d = i = state[3];
    e = j = state[4];

    ਲਈ (n = 0; n < 16; n++)
        ਖੰਡ[n] = AV_RL32(ਬਫਰ + 4 * n);
    n = 0;

#ਜੇ CONFIG_SMALL
    ਲਈ (; n < 16;) {
        ROUND160_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }

    ਲਈ (; n < 32;) {
        ROUND160_16_ਮੰਜ਼ਿਲ_31(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }

    ਲਈ (; n < 48;) {
        ROUND160_32_ਮੰਜ਼ਿਲ_47(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }

    ਲਈ (; n < 64;) {
        ROUND160_48_ਮੰਜ਼ਿਲ_63(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }

    ਲਈ (; n < 80;) {
        ROUND160_64_ਮੰਜ਼ਿਲ_79(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }
#ਨਹੀਂਤਾਂ

    R160_0; R160_0; R160_0;
    ROUND160_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h,i,j);

    R160_16; R160_16; R160_16;
    ROUND160_16_ਮੰਜ਼ਿਲ_31(e,a,b,c,d,j,f,g,h,i);

    R160_32; R160_32; R160_32;
    ROUND160_32_ਮੰਜ਼ਿਲ_47(d,e,a,b,c,i,j,f,g,h);

    R160_48; R160_48; R160_48;
    ROUND160_48_ਮੰਜ਼ਿਲ_63(c,d,e,a,b,h,i,j,f,g);

    R160_64; R160_64; R160_64;
    ROUND160_64_ਮੰਜ਼ਿਲ_79(b,c,d,e,a,g,h,i,j,f);
#ਜੇ_ਅੰਤ

    i += c + state[1];
    state[1] = state[2] + d + j;
    state[2] = state[3] + e + f;
    state[3] = state[4] + a + g;
    state[4] = state[0] + b + h;
    state[0] = i;
}

ਸਥਿਰ ਖਾਲੀ ripemd320_transform(uint32_t *state, ਅਚਲ uint8_t ਬਫਰ[64])
{
    uint32_t a, b, c, d, e, f, g, h, i, j, t av_ਅਣਵਰਤਿਆ;
    uint32_t ਖੰਡ[16];
    ਪੂਰਨ n;

    a = state[0]; b = state[1]; c = state[2]; d = state[3]; e = state[4];
    f = state[5]; g = state[6]; h = state[7]; i = state[8]; j = state[9];

    ਲਈ (n = 0; n < 16; n++)
        ਖੰਡ[n] = AV_RL32(ਬਫਰ + 4 * n);
    n = 0;

#ਜੇ CONFIG_SMALL
    ਲਈ (; n < 16;) {
        ROUND160_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }
    FFSWAP(uint32_t, b, g);

    ਲਈ (; n < 32;) {
        ROUND160_16_ਮੰਜ਼ਿਲ_31(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }
    FFSWAP(uint32_t, d, i);

    ਲਈ (; n < 48;) {
        ROUND160_32_ਮੰਜ਼ਿਲ_47(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }
    FFSWAP(uint32_t, a, f);

    ਲਈ (; n < 64;) {
        ROUND160_48_ਮੰਜ਼ਿਲ_63(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }
    FFSWAP(uint32_t, c, h);

    ਲਈ (; n < 80;) {
        ROUND160_64_ਮੰਜ਼ਿਲ_79(a,b,c,d,e,f,g,h,i,j);
        t = e; e = d; d = c; c = b; b = a; a = t;
        t = j; j = i; i = h; h = g; g = f; f = t;
    }
    FFSWAP(uint32_t, e, j);
#ਨਹੀਂਤਾਂ

    R160_0; R160_0; R160_0;
    ROUND160_0_ਮੰਜ਼ਿਲ_15(a,b,c,d,e,f,g,h,i,j);
    FFSWAP(uint32_t, a, f);

    R160_16; R160_16; R160_16;
    ROUND160_16_ਮੰਜ਼ਿਲ_31(e,a,b,c,d,j,f,g,h,i);
    FFSWAP(uint32_t, b, g);

    R160_32; R160_32; R160_32;
    ROUND160_32_ਮੰਜ਼ਿਲ_47(d,e,a,b,c,i,j,f,g,h);
    FFSWAP(uint32_t, c, h);

    R160_48; R160_48; R160_48;
    ROUND160_48_ਮੰਜ਼ਿਲ_63(c,d,e,a,b,h,i,j,f,g);
    FFSWAP(uint32_t, d, i);

    R160_64; R160_64; R160_64;
    ROUND160_64_ਮੰਜ਼ਿਲ_79(b,c,d,e,a,g,h,i,j,f);
    FFSWAP(uint32_t, e, j);
#ਜੇ_ਅੰਤ

    state[0] += a; state[1] += b; state[2] += c; state[3] += d; state[4] += e;
    state[5] += f; state[6] += g; state[7] += h; state[8] += i; state[9] += j;
}

av_cold ਪੂਰਨ av_ripemd_init(AVRIPEMD *ctx, ਪੂਰਨ ਬਿੱਟ)
{
    ctx->digest_len = ਬਿੱਟ >> 5;
    ਚੋਣ (ਬਿੱਟ) {
    ਹਾਲਤ 128: // RIPEMD-128
        ctx->state[0] = 0x67452301;
        ctx->state[1] = 0xEFCDAB89;
        ctx->state[2] = 0x98BADCFE;
        ctx->state[3] = 0x10325476;
        ctx->transform = ripemd128_transform;
        ਰੋਕੋ;
    ਹਾਲਤ 160: // RIPEMD-160
        ctx->state[0] = 0x67452301;
        ctx->state[1] = 0xEFCDAB89;
        ctx->state[2] = 0x98BADCFE;
        ctx->state[3] = 0x10325476;
        ctx->state[4] = 0xC3D2E1F0;
        ctx->transform = ripemd160_transform;
        ਰੋਕੋ;
    ਹਾਲਤ 256: // RIPEMD-256
        ctx->state[0] = 0x67452301;
        ctx->state[1] = 0xEFCDAB89;
        ctx->state[2] = 0x98BADCFE;
        ctx->state[3] = 0x10325476;
        ctx->state[4] = 0x76543210;
        ctx->state[5] = 0xFEDCBA98;
        ctx->state[6] = 0x89ABCDEF;
        ctx->state[7] = 0x01234567;
        ctx->transform = ripemd256_transform;
        ਰੋਕੋ;
    ਹਾਲਤ 320: // RIPEMD-320
        ctx->state[0] = 0x67452301;
        ctx->state[1] = 0xEFCDAB89;
        ctx->state[2] = 0x98BADCFE;
        ctx->state[3] = 0x10325476;
        ctx->state[4] = 0xC3D2E1F0;
        ctx->state[5] = 0x76543210;
        ctx->state[6] = 0xFEDCBA98;
        ctx->state[7] = 0x89ABCDEF;
        ctx->state[8] = 0x01234567;
        ctx->state[9] = 0x3C2D1E0F;
        ctx->transform = ripemd320_transform;
        ਰੋਕੋ;
    ਮੂਲ:
        ਵਾਪਸ AVERROR(EINVAL);
    }
    ctx->ਗਿਣਤੀ_2 = 0;
    ਵਾਪਸ 0;
}

ਖਾਲੀ av_ripemd_update(AVRIPEMD* ctx, ਅਚਲ uint8_t* ਅੰਕੜੇ, size_t len)
{
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ j;
    size_t i;

    j = ctx->ਗਿਣਤੀ_2 & 63;
    ctx->ਗਿਣਤੀ_2 += len;
#ਜੇ CONFIG_SMALL
    ਲਈ (i = 0; i < len; i++) {
        ctx->ਬਫਰ[j++] = ਅੰਕੜੇ[i];
        ਜੇ (64 == j) {
            ctx->transform(ctx->state, ctx->ਬਫਰ);
            j = 0;
        }
    }
#ਨਹੀਂਤਾਂ
    ਜੇ (len >= 64 - j) {
        ਅਚਲ uint8_t *ਸਿਰਾ;
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(&ctx->ਬਫਰ[j], ਅੰਕੜੇ, (i = 64 - j));
        ctx->transform(ctx->state, ctx->ਬਫਰ);
        ਅੰਕੜੇ += i;
        len  -= i;
        ਸਿਰਾ   = ਅੰਕੜੇ + (len & ~63);
        len   = len % 64;
        ਲਈ (; ਅੰਕੜੇ < ਸਿਰਾ; ਅੰਕੜੇ += 64)
            ctx->transform(ctx->state, ਅੰਕੜੇ);
        j = 0;
    }
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(&ctx->ਬਫਰ[j], ਅੰਕੜੇ, len);
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ av_ripemd_final(AVRIPEMD* ctx, uint8_t *digest)
{
    ਪੂਰਨ i;
    uint64_t finalcount = av_le2ne64(ctx->ਗਿਣਤੀ_2 << 3);

    av_ripemd_update(ctx, "\200", 1);
    ਜਦੋਂ ((ctx->ਗਿਣਤੀ_2 & 63) != 56)
        av_ripemd_update(ctx, "", 1);
    av_ripemd_update(ctx, (uint8_t *)&finalcount, 8); /* Should cause a transform() */
    ਲਈ (i = 0; i < ctx->digest_len; i++)
        AV_WL32(digest + i*4, ctx->state[i]);
}

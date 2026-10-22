/*
 * Copyright (C) 2013 Reimar Döffinger <Reimar.Doeffinger@gmx.de>
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

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव "mem.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "murmur3.h"

प्रकारनिर्देश संरचना AVMurMur3 {
    uint64_t h1, h2;
    uint8_t state[16];
    पूर्णाङ्क state_pos;
    uint64_t len;
} AVMurMur3;

AVMurMur3 *av_murmur3_alloc(शून्य)
{
    प्रत्यागम av_mallocz(परिमाण(AVMurMur3));
}

शून्य av_murmur3_init_seeded(AVMurMur3 *c, uint64_t seed)
{
    स_रखो(c, 0, परिमाण(*c));
    c->h1 = c->h2 = seed;
}

शून्य av_murmur3_init(AVMurMur3 *c)
{
    // arbitrary random number as seed
    av_murmur3_init_seeded(c, 0x725acc55daddca55);
}

स्थिर ध्रुव uint64_t c1 = UINT64_C(0x87c37b91114253d5);
स्थिर ध्रुव uint64_t c2 = UINT64_C(0x4cf5ad432745937f);

#define ROT(a, b) (((a) << (b)) | ((a) >> (64 - (b))))

स्थिर uint64_t अन्तःस्थ get_k1(ध्रुव uint8_t *src)
{
    uint64_t k = AV_RL64(src);
    k *= c1;
    k = ROT(k, 31);
    k *= c2;
    प्रत्यागम k;
}

स्थिर अन्तःस्थ uint64_t get_k2(ध्रुव uint8_t *src)
{
    uint64_t k = AV_RL64(src + 8);
    k *= c2;
    k = ROT(k, 33);
    k *= c1;
    प्रत्यागम k;
}

स्थिर अन्तःस्थ uint64_t update_h1(uint64_t k, uint64_t h1, uint64_t h2)
{
    k ^= h1;
    k = ROT(k, 27);
    k += h2;
    k *= 5;
    k += 0x52dce729;
    प्रत्यागम k;
}

स्थिर अन्तःस्थ uint64_t update_h2(uint64_t k, uint64_t h1, uint64_t h2)
{
    k ^= h2;
    k = ROT(k, 31);
    k += h1;
    k *= 5;
    k += 0x38495ab5;
    प्रत्यागम k;
}

शून्य av_murmur3_update(AVMurMur3 *c, ध्रुव uint8_t *src, माप_प्रकार len)
{
    ध्रुव uint8_t *end;
    uint64_t h1 = c->h1, h2 = c->h2;
    uint64_t k1, k2;
    यदि (len <= 0) प्रत्यागम;
    c->len += len;
    यदि (c->state_pos > 0) {
        यावत् (c->state_pos < 16) {
            c->state[c->state_pos++] = *src++;
            यदि (--len <= 0) प्रत्यागम;
        }
        c->state_pos = 0;
        k1 = get_k1(c->state);
        k2 = get_k2(c->state);
        h1 = update_h1(k1, h1, h2);
        h2 = update_h2(k2, h1, h2);
    }

    end = src + (len & ~15);
    यावत् (src < end) {
        // These could be done sequentially instead
        // of interleaved, but like this is over 10% faster
        k1 = get_k1(src);
        k2 = get_k2(src);
        h1 = update_h1(k1, h1, h2);
        h2 = update_h2(k2, h1, h2);
        src += 16;
    }
    c->h1 = h1;
    c->h2 = h2;

    len &= 15;
    यदि (len > 0) {
        स_नकल(c->state, src, len);
        c->state_pos = len;
    }
}

स्थिर अन्तःस्थ uint64_t fmix(uint64_t k)
{
    k ^= k >> 33;
    k *= UINT64_C(0xff51afd7ed558ccd);
    k ^= k >> 33;
    k *= UINT64_C(0xc4ceb9fe1a85ec53);
    k ^= k >> 33;
    प्रत्यागम k;
}

शून्य av_murmur3_final(AVMurMur3 *c, uint8_t dst[16])
{
    uint64_t h1 = c->h1, h2 = c->h2;
    स_रखो(c->state + c->state_pos, 0, परिमाण(c->state) - c->state_pos);
    h1 ^= get_k1(c->state) ^ c->len;
    h2 ^= get_k2(c->state) ^ c->len;
    h1 += h2;
    h2 += h1;
    h1 = fmix(h1);
    h2 = fmix(h2);
    h1 += h2;
    h2 += h1;
    AV_WL64(dst, h1);
    AV_WL64(dst + 8, h2);
}

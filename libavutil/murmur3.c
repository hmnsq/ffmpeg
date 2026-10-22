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

#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश <string.h>
#समावेश "mem.h"
#समावेश "intreadwrite.h"
#समावेश "murmur3.h"

प्रकार काष्ठा AVMurMur3 {
    uint64_t h1, h2;
    uint8_t state[16];
    पूर्णांक state_pos;
    uint64_t len;
} AVMurMur3;

AVMurMur3 *av_murmur3_alloc(व्योम)
{
    वापस av_mallocz(माप(AVMurMur3));
}

व्योम av_murmur3_init_seeded(AVMurMur3 *c, uint64_t seed)
{
    स_रखो(c, 0, माप(*c));
    c->h1 = c->h2 = seed;
}

व्योम av_murmur3_init(AVMurMur3 *c)
{
    // arbitrary random number as seed
    av_murmur3_init_seeded(c, 0x725acc55daddca55);
}

अटल स्थिर uint64_t c1 = UINT64_C(0x87c37b91114253d5);
अटल स्थिर uint64_t c2 = UINT64_C(0x4cf5ad432745937f);

#घोषणा ROT(a, b) (((a) << (b)) | ((a) >> (64 - (b))))

अटल uint64_t अंतरभूत get_k1(स्थिर uint8_t *src)
{
    uint64_t k = AV_RL64(src);
    k *= c1;
    k = ROT(k, 31);
    k *= c2;
    वापस k;
}

अटल अंतरभूत uint64_t get_k2(स्थिर uint8_t *src)
{
    uint64_t k = AV_RL64(src + 8);
    k *= c2;
    k = ROT(k, 33);
    k *= c1;
    वापस k;
}

अटल अंतरभूत uint64_t update_h1(uint64_t k, uint64_t h1, uint64_t h2)
{
    k ^= h1;
    k = ROT(k, 27);
    k += h2;
    k *= 5;
    k += 0x52dce729;
    वापस k;
}

अटल अंतरभूत uint64_t update_h2(uint64_t k, uint64_t h1, uint64_t h2)
{
    k ^= h2;
    k = ROT(k, 31);
    k += h1;
    k *= 5;
    k += 0x38495ab5;
    वापस k;
}

व्योम av_murmur3_update(AVMurMur3 *c, स्थिर uint8_t *src, माप_प्रकार len)
{
    स्थिर uint8_t *end;
    uint64_t h1 = c->h1, h2 = c->h2;
    uint64_t k1, k2;
    अगर (len <= 0) वापस;
    c->len += len;
    अगर (c->state_pos > 0) {
        जबतक (c->state_pos < 16) {
            c->state[c->state_pos++] = *src++;
            अगर (--len <= 0) वापस;
        }
        c->state_pos = 0;
        k1 = get_k1(c->state);
        k2 = get_k2(c->state);
        h1 = update_h1(k1, h1, h2);
        h2 = update_h2(k2, h1, h2);
    }

    end = src + (len & ~15);
    जबतक (src < end) {
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
    अगर (len > 0) {
        स_नकल(c->state, src, len);
        c->state_pos = len;
    }
}

अटल अंतरभूत uint64_t fmix(uint64_t k)
{
    k ^= k >> 33;
    k *= UINT64_C(0xff51afd7ed558ccd);
    k ^= k >> 33;
    k *= UINT64_C(0xc4ceb9fe1a85ec53);
    k ^= k >> 33;
    वापस k;
}

व्योम av_murmur3_final(AVMurMur3 *c, uint8_t dst[16])
{
    uint64_t h1 = c->h1, h2 = c->h2;
    स_रखो(c->state + c->state_pos, 0, माप(c->state) - c->state_pos);
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

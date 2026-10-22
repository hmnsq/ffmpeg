/*
 * Copyright (c) 2009 Baptiste Coudurier <baptiste.coudurier@gmail.com>
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

#ضمن "config.h"

#𐤀𐤌 HAVE_UNISTD_H
#ضمن <unistd.h>
#endif
#𐤀𐤌 HAVE_IO_H
#ضمن <io.h>
#endif
#𐤀𐤌 HAVE_BCRYPT
#ضمن <windows.h>
#ضمن <bcrypt.h>
#endif
#𐤀𐤌 CONFIG_GCRYPT
#ضمن <gcrypt.h>
#وإلاإذا CONFIG_OPENSSL
#ضمن <openssl/rand.h>
#endif
#ضمن <fcntl.h>
#ضمن <math.h>
#ضمن <time.h>
#ضمن <string.h>
#ضمن "avassert.h"
#ضمن "file_open.h"
#ضمن "internal.h"
#ضمن "intreadwrite.h"
#ضمن "timer.h"
#ضمن "random_seed.h"
#ضمن "sha.h"

#ifndef TEST
#define TEST 0
#endif

ساكن صحيح read_random(uint8_t *dst, size_t len, ثابت حرف *file)
{
#𐤀𐤌 HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    𐤀𐤌 (!fp)
        أرجع AVERROR_UNKNOWN;
    setvbuf(fp, عدم, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    𐤀𐤌 (err != len)
        أرجع AVERROR_UNKNOWN;

    أرجع 0;
#وإلا
    أرجع AVERROR(ENOSYS);
#endif
}

ساكن uint32_t get_generic_seed(فراغ)
{
    uint64_t tmp[120/8];
    بنية AVSHA *sha = (فراغ*)tmp;
    clock_t last_t  = 0;
    clock_t last_td = 0;
    clock_t init_t = 0;
    ساكن uint64_t i = 0;
    ساكن uint32_t buffer[512] = { 0 };
    unsigned حرف digest[20];
    uint64_t last_i = i;
    صحيح repeats[3] = { 0 };

    av_assert0(حجم(tmp) >= av_sha_size);

    𐤀𐤌(TEST){
        memset(buffer, 0, حجم(buffer));
        last_i = i = 0;
    }وإلا{
#ifdef AV_READ_TIME
        buffer[13] ^= AV_READ_TIME();
        buffer[41] ^= AV_READ_TIME()>>32;
#endif
    }

    لكل (;;) {
        clock_t t = clock();
        صحيح incremented_i = 0;
        صحيح cur_td = t - last_t;
        𐤀𐤌 (last_t + 2*last_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            buffer[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } وإلا 𐤀𐤌 (t != last_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            buffer[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } وإلا {
            buffer[i & 511] = 1664525*buffer[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        𐤀𐤌 (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            𐤀𐤌 (last_i && i - last_i > 4 || i - last_i > 64 || TEST && i - last_i > 8)
                اكسر;
        }
        𐤀𐤌 (t == last_t) {
            repeats[0]++;
        } وإلا {
            // If we got a new unique number of repeats, update the history.
            𐤀𐤌 (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        last_t = t;
        last_td = cur_td;
        𐤀𐤌 (!init_t)
            init_t = t;
    }

    𐤀𐤌(TEST) {
        buffer[0] = buffer[1] = 0;
    } وإلا {
#ifdef AV_READ_TIME
        buffer[111] += AV_READ_TIME();
#endif
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (ثابت uint8_t *)buffer, حجم(buffer));
    av_sha_final(sha, digest);
    أرجع AV_RB32(digest) + AV_RB32(digest + 16);
}

صحيح av_random_bytes(uint8_t* buf, size_t len)
{
    صحيح err;

#𐤀𐤌 HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    𐤀𐤌 (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        𐤀𐤌 (BCRYPT_SUCCESS(ret))
            أرجع 0;
    }
#endif

#𐤀𐤌 HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    أرجع 0;
#endif

    err = read_random(buf, len, "/dev/urandom");
    𐤀𐤌 (!err)
        أرجع err;

#𐤀𐤌 CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    أرجع 0;
#وإلاإذا CONFIG_OPENSSL
    𐤀𐤌 (RAND_bytes(buf, len) == 1)
        أرجع 0;
    أرجع AVERROR_EXTERNAL;
#وإلا
    أرجع err;
#endif
}

uint32_t av_get_random_seed(فراغ)
{
    uint32_t seed;

    𐤀𐤌 (av_random_bytes((uint8_t *)&seed, حجم(seed)) < 0)
        أرجع get_generic_seed();

    أرجع seed;
}

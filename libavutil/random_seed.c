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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_UNISTD_H
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_IO_H
#ਅਨ੍ਤਰ੍ਭਾਵ <io.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_BCRYPT
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <bcrypt.h>
#ਜੇ_ਅੰਤ
#ਜੇ CONFIG_GCRYPT
#ਅਨ੍ਤਰ੍ਭਾਵ <gcrypt.h>
#ਜਾਂਜੇ CONFIG_OPENSSL
#ਅਨ੍ਤਰ੍ਭਾਵ <openssl/rand.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <math.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <time.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "file_open.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "random_seed.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sha.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ TEST
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TEST 0
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਪੂਰਨ read_random(uint8_t *dst, size_t len, ਅਚਲ ਅੱਖਰ *file)
{
#ਜੇ HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    ਜੇ (!fp)
        ਵਾਪਸ AVERROR_UNKNOWN;
    setvbuf(fp, ਨਿਰਾ, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    ਜੇ (err != len)
        ਵਾਪਸ AVERROR_UNKNOWN;

    ਵਾਪਸ 0;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ uint32_t get_generic_ਬੀਜ(ਖਾਲੀ)
{
    uint64_t tmp[120/8];
    ਬਣਤਰ AVSHA *sha = (ਖਾਲੀ*)tmp;
    clock_t ਆਖਰੀ_t  = 0;
    clock_t ਆਖਰੀ_td = 0;
    clock_t init_t = 0;
    ਸਥਿਰ uint64_t i = 0;
    ਸਥਿਰ uint32_t ਬਫਰ[512] = { 0 };
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ digest[20];
    uint64_t ਆਖਰੀ_i = i;
    ਪੂਰਨ repeats[3] = { 0 };

    av_assert0(ਆਕਾਰ(tmp) >= av_sha_ਮਾਪ);

    ਜੇ(TEST){
        memset(ਬਫਰ, 0, ਆਕਾਰ(ਬਫਰ));
        ਆਖਰੀ_i = i = 0;
    }ਨਹੀਂਤਾਂ{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ AV_READ_ਸਮਾਂ
        ਬਫਰ[13] ^= AV_READ_ਸਮਾਂ();
        ਬਫਰ[41] ^= AV_READ_ਸਮਾਂ()>>32;
#ਜੇ_ਅੰਤ
    }

    ਲਈ (;;) {
        clock_t t = clock();
        ਪੂਰਨ incremented_i = 0;
        ਪੂਰਨ cur_td = t - ਆਖਰੀ_t;
        ਜੇ (ਆਖਰੀ_t + 2*ਆਖਰੀ_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            ਬਫਰ[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } ਨਹੀਂਤਾਂ ਜੇ (t != ਆਖਰੀ_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            ਬਫਰ[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } ਨਹੀਂਤਾਂ {
            ਬਫਰ[i & 511] = 1664525*ਬਫਰ[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        ਜੇ (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            ਜੇ (ਆਖਰੀ_i && i - ਆਖਰੀ_i > 4 || i - ਆਖਰੀ_i > 64 || TEST && i - ਆਖਰੀ_i > 8)
                ਰੋਕੋ;
        }
        ਜੇ (t == ਆਖਰੀ_t) {
            repeats[0]++;
        } ਨਹੀਂਤਾਂ {
            // If we got a new unique number of repeats, update the history.
            ਜੇ (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        ਆਖਰੀ_t = t;
        ਆਖਰੀ_td = cur_td;
        ਜੇ (!init_t)
            init_t = t;
    }

    ਜੇ(TEST) {
        ਬਫਰ[0] = ਬਫਰ[1] = 0;
    } ਨਹੀਂਤਾਂ {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ AV_READ_ਸਮਾਂ
        ਬਫਰ[111] += AV_READ_ਸਮਾਂ();
#ਜੇ_ਅੰਤ
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (ਅਚਲ uint8_t *)ਬਫਰ, ਆਕਾਰ(ਬਫਰ));
    av_sha_final(sha, digest);
    ਵਾਪਸ AV_RB32(digest) + AV_RB32(digest + 16);
}

ਪੂਰਨ av_random_ਬਾਈਟਾਂ(uint8_t* buf, size_t len)
{
    ਪੂਰਨ err;

#ਜੇ HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    ਜੇ (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        ਜੇ (BCRYPT_SUCCESS(ret))
            ਵਾਪਸ 0;
    }
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    ਵਾਪਸ 0;
#ਜੇ_ਅੰਤ

    err = read_random(buf, len, "/dev/urandom");
    ਜੇ (!err)
        ਵਾਪਸ err;

#ਜੇ CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    ਵਾਪਸ 0;
#ਜਾਂਜੇ CONFIG_OPENSSL
    ਜੇ (RAND_ਬਾਈਟਾਂ(buf, len) == 1)
        ਵਾਪਸ 0;
    ਵਾਪਸ AVERROR_EXTERNAL;
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ err;
#ਜੇ_ਅੰਤ
}

uint32_t av_get_random_ਬੀਜ(ਖਾਲੀ)
{
    uint32_t ਬੀਜ;

    ਜੇ (av_random_ਬਾਈਟਾਂ((uint8_t *)&ਬੀਜ, ਆਕਾਰ(ਬੀਜ)) < 0)
        ਵਾਪਸ get_generic_ਬੀਜ();

    ਵਾਪਸ ਬੀਜ;
}

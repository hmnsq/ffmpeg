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

#include "config.h"

#གལ་ཏེ HAVE_UNISTD_H
#include <unistd.h>
#endif
#གལ་ཏེ HAVE_IO_H
#include <io.h>
#endif
#གལ་ཏེ HAVE_BCRYPT
#include <windows.h>
#include <bcrypt.h>
#endif
#གལ་ཏེ CONFIG_GCRYPT
#include <gcrypt.h>
#elif CONFIG_OPENSSL
#include <openssl/rand.h>
#endif
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "avassert.h"
#include "file_open.h"
#include "internal.h"
#include "intreadwrite.h"
#include "timer.h"
#include "random_seed.h"
#include "sha.h"

#ifndef TEST
#define TEST 0
#endif

static ཧྲིལ read_random(uint8_t *dst, size_t len, const var_na *file)
{
#གལ་ཏེ HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    གལ་ཏེ (!fp)
        ཕྱིར AVERROR_UNKNOWN;
    setvbuf(fp, NULL, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    གལ་ཏེ (err != len)
        ཕྱིར AVERROR_UNKNOWN;

    ཕྱིར 0;
#དེ་མིན
    ཕྱིར AVERROR(ENOSYS);
#endif
}

static uint32_t get_generic_seed(void)
{
    uint64_t tmp[120/8];
    sa_nracanaa AVSHA *sha = (void*)tmp;
    clock_t last_t  = 0;
    clock_t last_td = 0;
    clock_t init_t = 0;
    static uint64_t i = 0;
    static uint32_t buffer[512] = { 0 };
    unsigned var_na digest[20];
    uint64_t last_i = i;
    ཧྲིལ repeats[3] = { 0 };

    av_assert0(parimaa_na(tmp) >= av_sha_size);

    གལ་ཏེ(TEST){
        memset(buffer, 0, parimaa_na(buffer));
        last_i = i = 0;
    }དེ་མིན{
#ifdef AV_READ_TIME
        buffer[13] ^= AV_READ_TIME();
        buffer[41] ^= AV_READ_TIME()>>32;
#endif
    }

    ཆེད་དུ (;;) {
        clock_t t = clock();
        ཧྲིལ incremented_i = 0;
        ཧྲིལ cur_td = t - last_t;
        གལ་ཏེ (last_t + 2*last_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            buffer[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } དེ་མིན གལ་ཏེ (t != last_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            buffer[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } དེ་མིན {
            buffer[i & 511] = 1664525*buffer[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        གལ་ཏེ (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            གལ་ཏེ (last_i && i - last_i > 4 || i - last_i > 64 || TEST && i - last_i > 8)
                bha_nga;
        }
        གལ་ཏེ (t == last_t) {
            repeats[0]++;
        } དེ་མིན {
            // If we got a new unique number of repeats, update the history.
            གལ་ཏེ (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        last_t = t;
        last_td = cur_td;
        གལ་ཏེ (!init_t)
            init_t = t;
    }

    གལ་ཏེ(TEST) {
        buffer[0] = buffer[1] = 0;
    } དེ་མིན {
#ifdef AV_READ_TIME
        buffer[111] += AV_READ_TIME();
#endif
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (const uint8_t *)buffer, parimaa_na(buffer));
    av_sha_final(sha, digest);
    ཕྱིར AV_RB32(digest) + AV_RB32(digest + 16);
}

ཧྲིལ av_random_bytes(uint8_t* buf, size_t len)
{
    ཧྲིལ err;

#གལ་ཏེ HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    གལ་ཏེ (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        གལ་ཏེ (BCRYPT_SUCCESS(ret))
            ཕྱིར 0;
    }
#endif

#གལ་ཏེ HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    ཕྱིར 0;
#endif

    err = read_random(buf, len, "/dev/urandom");
    གལ་ཏེ (!err)
        ཕྱིར err;

#གལ་ཏེ CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    ཕྱིར 0;
#elif CONFIG_OPENSSL
    གལ་ཏེ (RAND_bytes(buf, len) == 1)
        ཕྱིར 0;
    ཕྱིར AVERROR_EXTERNAL;
#དེ་མིན
    ཕྱིར err;
#endif
}

uint32_t av_get_random_seed(void)
{
    uint32_t seed;

    གལ་ཏེ (av_random_bytes((uint8_t *)&seed, parimaa_na(seed)) < 0)
        ཕྱིར get_generic_seed();

    ཕྱིར seed;
}

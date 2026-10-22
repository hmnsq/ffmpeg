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

#அந்தர்பாவ "config.h"

#எனில் HAVE_UNISTD_H
#அந்தர்பாவ <unistd.h>
#endif
#எனில் HAVE_IO_H
#அந்தர்பாவ <io.h>
#endif
#எனில் HAVE_BCRYPT
#அந்தர்பாவ <windows.h>
#அந்தர்பாவ <bcrypt.h>
#endif
#எனில் CONFIG_GCRYPT
#அந்தர்பாவ <gcrypt.h>
#அல்லதெனில் CONFIG_OPENSSL
#அந்தர்பாவ <openssl/rand.h>
#endif
#அந்தர்பாவ <fcntl.h>
#அந்தர்பாவ <math.h>
#அந்தர்பாவ <time.h>
#அந்தர்பாவ <string.h>
#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "file_open.h"
#அந்தர்பாவ "internal.h"
#அந்தர்பாவ "intreadwrite.h"
#அந்தர்பாவ "timer.h"
#அந்தர்பாவ "random_seed.h"
#அந்தர்பாவ "sha.h"

#ifndef TEST
#define TEST 0
#endif

நிலையான முழு read_random(uint8_t *dst, size_t len, மாறிலி எழுத்து *file)
{
#எனில் HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    எனில் (!fp)
        திரும்பு AVERROR_UNKNOWN;
    setvbuf(fp, வெற்று, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    எனில் (err != len)
        திரும்பு AVERROR_UNKNOWN;

    திரும்பு 0;
#இல்லையெனில்
    திரும்பு AVERROR(ENOSYS);
#endif
}

நிலையான uint32_t get_generic_seed(வெறுமை)
{
    uint64_t tmp[120/8];
    கட்டமைப்பு AVSHA *sha = (வெறுமை*)tmp;
    clock_t last_t  = 0;
    clock_t last_td = 0;
    clock_t init_t = 0;
    நிலையான uint64_t i = 0;
    நிலையான uint32_t buffer[512] = { 0 };
    unsigned எழுத்து digest[20];
    uint64_t last_i = i;
    முழு repeats[3] = { 0 };

    av_assert0(அளவு(tmp) >= av_sha_size);

    எனில்(TEST){
        memset(buffer, 0, அளவு(buffer));
        last_i = i = 0;
    }இல்லையெனில்{
#ifdef AV_READ_TIME
        buffer[13] ^= AV_READ_TIME();
        buffer[41] ^= AV_READ_TIME()>>32;
#endif
    }

    க்கு (;;) {
        clock_t t = clock();
        முழு incremented_i = 0;
        முழு cur_td = t - last_t;
        எனில் (last_t + 2*last_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            buffer[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } இல்லையெனில் எனில் (t != last_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            buffer[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } இல்லையெனில் {
            buffer[i & 511] = 1664525*buffer[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        எனில் (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            எனில் (last_i && i - last_i > 4 || i - last_i > 64 || TEST && i - last_i > 8)
                நிறுத்து;
        }
        எனில் (t == last_t) {
            repeats[0]++;
        } இல்லையெனில் {
            // If we got a new unique number of repeats, update the history.
            எனில் (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        last_t = t;
        last_td = cur_td;
        எனில் (!init_t)
            init_t = t;
    }

    எனில்(TEST) {
        buffer[0] = buffer[1] = 0;
    } இல்லையெனில் {
#ifdef AV_READ_TIME
        buffer[111] += AV_READ_TIME();
#endif
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (மாறிலி uint8_t *)buffer, அளவு(buffer));
    av_sha_final(sha, digest);
    திரும்பு AV_RB32(digest) + AV_RB32(digest + 16);
}

முழு av_random_bytes(uint8_t* buf, size_t len)
{
    முழு err;

#எனில் HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    எனில் (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        எனில் (BCRYPT_SUCCESS(ret))
            திரும்பு 0;
    }
#endif

#எனில் HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    திரும்பு 0;
#endif

    err = read_random(buf, len, "/dev/urandom");
    எனில் (!err)
        திரும்பு err;

#எனில் CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    திரும்பு 0;
#அல்லதெனில் CONFIG_OPENSSL
    எனில் (RAND_bytes(buf, len) == 1)
        திரும்பு 0;
    திரும்பு AVERROR_EXTERNAL;
#இல்லையெனில்
    திரும்பு err;
#endif
}

uint32_t av_get_random_seed(வெறுமை)
{
    uint32_t seed;

    எனில் (av_random_bytes((uint8_t *)&seed, அளவு(seed)) < 0)
        திரும்பு get_generic_seed();

    திரும்பு seed;
}

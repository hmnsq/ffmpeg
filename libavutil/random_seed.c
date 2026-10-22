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

#અન્તર્ભાવ "config.h"

#જો HAVE_UNISTD_H
#અન્તર્ભાવ <unistd.h>
#endif
#જો HAVE_IO_H
#અન્તર્ભાવ <io.h>
#endif
#જો HAVE_BCRYPT
#અન્તર્ભાવ <windows.h>
#અન્તર્ભાવ <bcrypt.h>
#endif
#જો CONFIG_GCRYPT
#અન્તર્ભાવ <gcrypt.h>
#અથવાજો CONFIG_OPENSSL
#અન્તર્ભાવ <openssl/rand.h>
#endif
#અન્તર્ભાવ <fcntl.h>
#અન્તર્ભાવ <math.h>
#અન્તર્ભાવ <time.h>
#અન્તર્ભાવ <string.h>
#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "file_open.h"
#અન્તર્ભાવ "internal.h"
#અન્તર્ભાવ "intreadwrite.h"
#અન્તર્ભાવ "timer.h"
#અન્તર્ભાવ "random_seed.h"
#અન્તર્ભાવ "sha.h"

#ifndef TEST
#define TEST 0
#endif

સ્થિર પૂર્ણાંક read_random(uint8_t *dst, size_t len, અચલ અક્ષર *file)
{
#જો HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    જો (!fp)
        પાછા AVERROR_UNKNOWN;
    setvbuf(fp, ખાલી, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    જો (err != len)
        પાછા AVERROR_UNKNOWN;

    પાછા 0;
#નહીંતર
    પાછા AVERROR(ENOSYS);
#endif
}

સ્થિર uint32_t get_generic_seed(શૂન્ય)
{
    uint64_t tmp[120/8];
    સંરચના AVSHA *sha = (શૂન્ય*)tmp;
    clock_t last_t  = 0;
    clock_t last_td = 0;
    clock_t init_t = 0;
    સ્થિર uint64_t i = 0;
    સ્થિર uint32_t buffer[512] = { 0 };
    unsigned અક્ષર digest[20];
    uint64_t last_i = i;
    પૂર્ણાંક repeats[3] = { 0 };

    av_assert0(કદ(tmp) >= av_sha_size);

    જો(TEST){
        memset(buffer, 0, કદ(buffer));
        last_i = i = 0;
    }નહીંતર{
#ifdef AV_READ_TIME
        buffer[13] ^= AV_READ_TIME();
        buffer[41] ^= AV_READ_TIME()>>32;
#endif
    }

    માટે (;;) {
        clock_t t = clock();
        પૂર્ણાંક incremented_i = 0;
        પૂર્ણાંક cur_td = t - last_t;
        જો (last_t + 2*last_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            buffer[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } નહીંતર જો (t != last_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            buffer[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } નહીંતર {
            buffer[i & 511] = 1664525*buffer[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        જો (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            જો (last_i && i - last_i > 4 || i - last_i > 64 || TEST && i - last_i > 8)
                તોડો;
        }
        જો (t == last_t) {
            repeats[0]++;
        } નહીંતર {
            // If we got a new unique number of repeats, update the history.
            જો (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        last_t = t;
        last_td = cur_td;
        જો (!init_t)
            init_t = t;
    }

    જો(TEST) {
        buffer[0] = buffer[1] = 0;
    } નહીંતર {
#ifdef AV_READ_TIME
        buffer[111] += AV_READ_TIME();
#endif
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (અચલ uint8_t *)buffer, કદ(buffer));
    av_sha_final(sha, digest);
    પાછા AV_RB32(digest) + AV_RB32(digest + 16);
}

પૂર્ણાંક av_random_bytes(uint8_t* buf, size_t len)
{
    પૂર્ણાંક err;

#જો HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    જો (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        જો (BCRYPT_SUCCESS(ret))
            પાછા 0;
    }
#endif

#જો HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    પાછા 0;
#endif

    err = read_random(buf, len, "/dev/urandom");
    જો (!err)
        પાછા err;

#જો CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    પાછા 0;
#અથવાજો CONFIG_OPENSSL
    જો (RAND_bytes(buf, len) == 1)
        પાછા 0;
    પાછા AVERROR_EXTERNAL;
#નહીંતર
    પાછા err;
#endif
}

uint32_t av_get_random_seed(શૂન્ય)
{
    uint32_t seed;

    જો (av_random_bytes((uint8_t *)&seed, કદ(seed)) < 0)
        પાછા get_generic_seed();

    પાછા seed;
}

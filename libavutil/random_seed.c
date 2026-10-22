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

#شامل "config.h"

#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#endif
#اگر HAVE_IO_H
#شامل <io.h>
#endif
#اگر HAVE_BCRYPT
#شامل <windows.h>
#شامل <bcrypt.h>
#endif
#اگر CONFIG_GCRYPT
#شامل <gcrypt.h>
#وگرنهاگر CONFIG_OPENSSL
#شامل <openssl/rand.h>
#endif
#شامل <fcntl.h>
#شامل <math.h>
#شامل <time.h>
#شامل <string.h>
#شامل "avassert.h"
#شامل "file_open.h"
#شامل "internal.h"
#شامل "intreadwrite.h"
#شامل "timer.h"
#شامل "random_seed.h"
#شامل "sha.h"

#ifndef TEST
#define TEST 0
#endif

ایستا صحیح read_random(uint8_t *dst, size_t len, ثابت نویسه *file)
{
#اگر HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    اگر (!fp)
        بازگشت AVERROR_UNKNOWN;
    setvbuf(fp, پوچ, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    اگر (err != len)
        بازگشت AVERROR_UNKNOWN;

    بازگشت 0;
#وگرنه
    بازگشت AVERROR(ENOSYS);
#endif
}

ایستا uint32_t get_generic_seed(تهی)
{
    uint64_t tmp[120/8];
    ساختار AVSHA *sha = (تهی*)tmp;
    clock_t last_t  = 0;
    clock_t last_td = 0;
    clock_t init_t = 0;
    ایستا uint64_t i = 0;
    ایستا uint32_t buffer[512] = { 0 };
    unsigned نویسه digest[20];
    uint64_t last_i = i;
    صحیح repeats[3] = { 0 };

    av_assert0(اندازه(tmp) >= av_sha_size);

    اگر(TEST){
        memset(buffer, 0, اندازه(buffer));
        last_i = i = 0;
    }وگرنه{
#ifdef AV_READ_TIME
        buffer[13] ^= AV_READ_TIME();
        buffer[41] ^= AV_READ_TIME()>>32;
#endif
    }

    برای (;;) {
        clock_t t = clock();
        صحیح incremented_i = 0;
        صحیح cur_td = t - last_t;
        اگر (last_t + 2*last_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            buffer[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } وگرنه اگر (t != last_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            buffer[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } وگرنه {
            buffer[i & 511] = 1664525*buffer[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        اگر (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            اگر (last_i && i - last_i > 4 || i - last_i > 64 || TEST && i - last_i > 8)
                بشکن;
        }
        اگر (t == last_t) {
            repeats[0]++;
        } وگرنه {
            // If we got a new unique number of repeats, update the history.
            اگر (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        last_t = t;
        last_td = cur_td;
        اگر (!init_t)
            init_t = t;
    }

    اگر(TEST) {
        buffer[0] = buffer[1] = 0;
    } وگرنه {
#ifdef AV_READ_TIME
        buffer[111] += AV_READ_TIME();
#endif
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (ثابت uint8_t *)buffer, اندازه(buffer));
    av_sha_final(sha, digest);
    بازگشت AV_RB32(digest) + AV_RB32(digest + 16);
}

صحیح av_random_bytes(uint8_t* buf, size_t len)
{
    صحیح err;

#اگر HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    اگر (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        اگر (BCRYPT_SUCCESS(ret))
            بازگشت 0;
    }
#endif

#اگر HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    بازگشت 0;
#endif

    err = read_random(buf, len, "/dev/urandom");
    اگر (!err)
        بازگشت err;

#اگر CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    بازگشت 0;
#وگرنهاگر CONFIG_OPENSSL
    اگر (RAND_bytes(buf, len) == 1)
        بازگشت 0;
    بازگشت AVERROR_EXTERNAL;
#وگرنه
    بازگشت err;
#endif
}

uint32_t av_get_random_seed(تهی)
{
    uint32_t seed;

    اگر (av_random_bytes((uint8_t *)&seed, اندازه(seed)) < 0)
        بازگشت get_generic_seed();

    بازگشت seed;
}

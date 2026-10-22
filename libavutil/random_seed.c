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
#اگر_ختم
#اگر HAVE_IO_H
#شامل <io.h>
#اگر_ختم
#اگر HAVE_BCRYPT
#شامل <windows.h>
#شامل <bcrypt.h>
#اگر_ختم
#اگر CONFIG_GCRYPT
#شامل <gcrypt.h>
#وگرنہ_اگر CONFIG_OPENSSL
#شامل <openssl/rand.h>
#اگر_ختم
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

#اگر_غیر_تعریف_شدہ TEST
#تعریف_کرو TEST 0
#اگر_ختم

ساکن صحیح read_random(uint8_t *dst, size_t len, ثابت حرف *file)
{
#اگر HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    اگر (!fp)
        واپس AVERROR_UNKNOWN;
    setvbuf(fp, تہی, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    اگر (err != len)
        واپس AVERROR_UNKNOWN;

    واپس 0;
#ورنہ
    واپس AVERROR(ENOSYS);
#اگر_ختم
}

ساکن uint32_t get_generic_بیج(خالی)
{
    uint64_t tmp[120/8];
    ساخت AVSHA *sha = (خالی*)tmp;
    clock_t آخری_t  = 0;
    clock_t آخری_td = 0;
    clock_t init_t = 0;
    ساکن uint64_t i = 0;
    ساکن uint32_t بفر[512] = { 0 };
    غیرعلامتی حرف digest[20];
    uint64_t آخری_i = i;
    صحیح repeats[3] = { 0 };

    av_assert0(حجم(tmp) >= av_sha_سائز);

    اگر(TEST){
        memset(بفر, 0, حجم(بفر));
        آخری_i = i = 0;
    }ورنہ{
#اگر_تعریف_شدہ AV_READ_وقت
        بفر[13] ^= AV_READ_وقت();
        بفر[41] ^= AV_READ_وقت()>>32;
#اگر_ختم
    }

    برائے (;;) {
        clock_t t = clock();
        صحیح incremented_i = 0;
        صحیح cur_td = t - آخری_t;
        اگر (آخری_t + 2*آخری_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            بفر[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } ورنہ اگر (t != آخری_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            بفر[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } ورنہ {
            بفر[i & 511] = 1664525*بفر[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        اگر (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            اگر (آخری_i && i - آخری_i > 4 || i - آخری_i > 64 || TEST && i - آخری_i > 8)
                توڑو;
        }
        اگر (t == آخری_t) {
            repeats[0]++;
        } ورنہ {
            // If we got a new unique number of repeats, update the history.
            اگر (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        آخری_t = t;
        آخری_td = cur_td;
        اگر (!init_t)
            init_t = t;
    }

    اگر(TEST) {
        بفر[0] = بفر[1] = 0;
    } ورنہ {
#اگر_تعریف_شدہ AV_READ_وقت
        بفر[111] += AV_READ_وقت();
#اگر_ختم
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (ثابت uint8_t *)بفر, حجم(بفر));
    av_sha_final(sha, digest);
    واپس AV_RB32(digest) + AV_RB32(digest + 16);
}

صحیح av_random_بائٹیں(uint8_t* buf, size_t len)
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
            واپس 0;
    }
#اگر_ختم

#اگر HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    واپس 0;
#اگر_ختم

    err = read_random(buf, len, "/dev/urandom");
    اگر (!err)
        واپس err;

#اگر CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    واپس 0;
#وگرنہ_اگر CONFIG_OPENSSL
    اگر (RAND_بائٹیں(buf, len) == 1)
        واپس 0;
    واپس AVERROR_EXTERNAL;
#ورنہ
    واپس err;
#اگر_ختم
}

uint32_t av_get_random_بیج(خالی)
{
    uint32_t بیج;

    اگر (av_random_بائٹیں((uint8_t *)&بیج, حجم(بیج)) < 0)
        واپس get_generic_بیج();

    واپس بیج;
}

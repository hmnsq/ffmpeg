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

#إذا HAVE_UNISTD_H
#ضمن <unistd.h>
#پایان_اگر
#إذا HAVE_IO_H
#ضمن <io.h>
#پایان_اگر
#إذا HAVE_BCRYPT
#ضمن <windows.h>
#ضمن <bcrypt.h>
#پایان_اگر
#إذا CONFIG_GCRYPT
#ضمن <gcrypt.h>
#وإلاإذا CONFIG_OPENSSL
#ضمن <openssl/rand.h>
#پایان_اگر
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

#اگر_تعریف_نشده TEST
#تعریف_کن TEST 0
#پایان_اگر

ساكن صحيح read_random(uint8_t *dst, size_t len, ثابت حرف *file)
{
#إذا HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    إذا (!fp)
        أرجع AVERROR_UNKNOWN;
    setvbuf(fp, عدم, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    إذا (err != len)
        أرجع AVERROR_UNKNOWN;

    أرجع 0;
#وإلا
    أرجع AVERROR(ENOSYS);
#پایان_اگر
}

ساكن uint32_t get_generic_دانه(فراغ)
{
    uint64_t tmp[120/8];
    بنية AVSHA *sha = (فراغ*)tmp;
    clock_t آخرین_t  = 0;
    clock_t آخرین_td = 0;
    clock_t init_t = 0;
    ساكن uint64_t i = 0;
    ساكن uint32_t میانگیر[512] = { 0 };
    بیعلامت حرف digest[20];
    uint64_t آخرین_i = i;
    صحيح repeats[3] = { 0 };

    av_assert0(حجم(tmp) >= av_sha_اندازه);

    إذا(TEST){
        memset(میانگیر, 0, حجم(میانگیر));
        آخرین_i = i = 0;
    }وإلا{
#اگر_تعریف_شده AV_READ_زمان
        میانگیر[13] ^= AV_READ_زمان();
        میانگیر[41] ^= AV_READ_زمان()>>32;
#پایان_اگر
    }

    لكل (;;) {
        clock_t t = clock();
        صحيح incremented_i = 0;
        صحيح cur_td = t - آخرین_t;
        إذا (آخرین_t + 2*آخرین_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            میانگیر[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } وإلا إذا (t != آخرین_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            میانگیر[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } وإلا {
            میانگیر[i & 511] = 1664525*میانگیر[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        إذا (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            إذا (آخرین_i && i - آخرین_i > 4 || i - آخرین_i > 64 || TEST && i - آخرین_i > 8)
                اكسر;
        }
        إذا (t == آخرین_t) {
            repeats[0]++;
        } وإلا {
            // If we got a new unique number of repeats, update the history.
            إذا (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        آخرین_t = t;
        آخرین_td = cur_td;
        إذا (!init_t)
            init_t = t;
    }

    إذا(TEST) {
        میانگیر[0] = میانگیر[1] = 0;
    } وإلا {
#اگر_تعریف_شده AV_READ_زمان
        میانگیر[111] += AV_READ_زمان();
#پایان_اگر
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (ثابت uint8_t *)میانگیر, حجم(میانگیر));
    av_sha_final(sha, digest);
    أرجع AV_RB32(digest) + AV_RB32(digest + 16);
}

صحيح av_random_بایتها(uint8_t* buf, size_t len)
{
    صحيح err;

#إذا HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    إذا (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        إذا (BCRYPT_SUCCESS(ret))
            أرجع 0;
    }
#پایان_اگر

#إذا HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    أرجع 0;
#پایان_اگر

    err = read_random(buf, len, "/dev/urandom");
    إذا (!err)
        أرجع err;

#إذا CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    أرجع 0;
#وإلاإذا CONFIG_OPENSSL
    إذا (RAND_بایتها(buf, len) == 1)
        أرجع 0;
    أرجع AVERROR_EXTERNAL;
#وإلا
    أرجع err;
#پایان_اگر
}

uint32_t av_get_random_دانه(فراغ)
{
    uint32_t دانه;

    إذا (av_random_بایتها((uint8_t *)&دانه, حجم(دانه)) < 0)
        أرجع get_generic_دانه();

    أرجع دانه;
}

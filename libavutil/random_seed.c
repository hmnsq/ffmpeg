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
#جے_انت
#إذا HAVE_IO_H
#ضمن <io.h>
#جے_انت
#إذا HAVE_BCRYPT
#ضمن <windows.h>
#ضمن <bcrypt.h>
#جے_انت
#إذا CONFIG_GCRYPT
#ضمن <gcrypt.h>
#وإلاإذا CONFIG_OPENSSL
#ضمن <openssl/rand.h>
#جے_انت
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

#جے_بنا_تعریف TEST
#تعریف_کرو TEST 0
#جے_انت

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
#جے_انت
}

ساكن uint32_t get_generic_بیج(فراغ)
{
    uint64_t tmp[120/8];
    بنية AVSHA *sha = (فراغ*)tmp;
    clock_t آخری_t  = 0;
    clock_t آخری_td = 0;
    clock_t init_t = 0;
    ساكن uint64_t i = 0;
    ساكن uint32_t بفر[512] = { 0 };
    بنانشانی حرف digest[20];
    uint64_t آخری_i = i;
    صحيح repeats[3] = { 0 };

    av_assert0(حجم(tmp) >= av_sha_ناپ);

    إذا(TEST){
        memset(بفر, 0, حجم(بفر));
        آخری_i = i = 0;
    }وإلا{
#جے_تعریف_شدہ AV_READ_ویلا
        بفر[13] ^= AV_READ_ویلا();
        بفر[41] ^= AV_READ_ویلا()>>32;
#جے_انت
    }

    لكل (;;) {
        clock_t t = clock();
        صحيح incremented_i = 0;
        صحيح cur_td = t - آخری_t;
        إذا (آخری_t + 2*آخری_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            بفر[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } وإلا إذا (t != آخری_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            بفر[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } وإلا {
            بفر[i & 511] = 1664525*بفر[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        إذا (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            إذا (آخری_i && i - آخری_i > 4 || i - آخری_i > 64 || TEST && i - آخری_i > 8)
                اكسر;
        }
        إذا (t == آخری_t) {
            repeats[0]++;
        } وإلا {
            // If we got a new unique number of repeats, update the history.
            إذا (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        آخری_t = t;
        آخری_td = cur_td;
        إذا (!init_t)
            init_t = t;
    }

    إذا(TEST) {
        بفر[0] = بفر[1] = 0;
    } وإلا {
#جے_تعریف_شدہ AV_READ_ویلا
        بفر[111] += AV_READ_ویلا();
#جے_انت
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (ثابت uint8_t *)بفر, حجم(بفر));
    av_sha_final(sha, digest);
    أرجع AV_RB32(digest) + AV_RB32(digest + 16);
}

صحيح av_random_بائٹاں(uint8_t* buf, size_t len)
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
#جے_انت

#إذا HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    أرجع 0;
#جے_انت

    err = read_random(buf, len, "/dev/urandom");
    إذا (!err)
        أرجع err;

#إذا CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    أرجع 0;
#وإلاإذا CONFIG_OPENSSL
    إذا (RAND_بائٹاں(buf, len) == 1)
        أرجع 0;
    أرجع AVERROR_EXTERNAL;
#وإلا
    أرجع err;
#جے_انت
}

uint32_t av_get_random_بیج(فراغ)
{
    uint32_t بیج;

    إذا (av_random_بائٹاں((uint8_t *)&بیج, حجم(بیج)) < 0)
        أرجع get_generic_بیج();

    أرجع بیج;
}

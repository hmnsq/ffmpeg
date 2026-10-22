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
#د_که_پای
#إذا HAVE_IO_H
#ضمن <io.h>
#د_که_پای
#إذا HAVE_BCRYPT
#ضمن <windows.h>
#ضمن <bcrypt.h>
#د_که_پای
#إذا CONFIG_GCRYPT
#ضمن <gcrypt.h>
#وإلاإذا CONFIG_OPENSSL
#ضمن <openssl/rand.h>
#د_که_پای
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

#که_نه_تعریف_شوی TEST
#تعریف_کړه TEST 0
#د_که_پای

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
#د_که_پای
}

ساكن uint32_t get_generic_تخم(فراغ)
{
    uint64_t tmp[120/8];
    بنية AVSHA *sha = (فراغ*)tmp;
    clock_t وروستی_t  = 0;
    clock_t وروستی_td = 0;
    clock_t init_t = 0;
    ساكن uint64_t i = 0;
    ساكن uint32_t بفر[512] = { 0 };
    بینښه حرف digest[20];
    uint64_t وروستی_i = i;
    صحيح repeats[3] = { 0 };

    av_assert0(حجم(tmp) >= av_sha_اندازه);

    إذا(TEST){
        memset(بفر, 0, حجم(بفر));
        وروستی_i = i = 0;
    }وإلا{
#که_تعریف_شوی AV_READ_وخت
        بفر[13] ^= AV_READ_وخت();
        بفر[41] ^= AV_READ_وخت()>>32;
#د_که_پای
    }

    لكل (;;) {
        clock_t t = clock();
        صحيح incremented_i = 0;
        صحيح cur_td = t - وروستی_t;
        إذا (وروستی_t + 2*وروستی_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            بفر[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } وإلا إذا (t != وروستی_t && repeats[0] > 0 && repeats[1] > 0 &&
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
            إذا (وروستی_i && i - وروستی_i > 4 || i - وروستی_i > 64 || TEST && i - وروستی_i > 8)
                اكسر;
        }
        إذا (t == وروستی_t) {
            repeats[0]++;
        } وإلا {
            // If we got a new unique number of repeats, update the history.
            إذا (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        وروستی_t = t;
        وروستی_td = cur_td;
        إذا (!init_t)
            init_t = t;
    }

    إذا(TEST) {
        بفر[0] = بفر[1] = 0;
    } وإلا {
#که_تعریف_شوی AV_READ_وخت
        بفر[111] += AV_READ_وخت();
#د_که_پای
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (ثابت uint8_t *)بفر, حجم(بفر));
    av_sha_final(sha, digest);
    أرجع AV_RB32(digest) + AV_RB32(digest + 16);
}

صحيح av_random_بایټونه(uint8_t* buf, size_t len)
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
#د_که_پای

#إذا HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    أرجع 0;
#د_که_پای

    err = read_random(buf, len, "/dev/urandom");
    إذا (!err)
        أرجع err;

#إذا CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    أرجع 0;
#وإلاإذا CONFIG_OPENSSL
    إذا (RAND_بایټونه(buf, len) == 1)
        أرجع 0;
    أرجع AVERROR_EXTERNAL;
#وإلا
    أرجع err;
#د_که_پای
}

uint32_t av_get_random_تخم(فراغ)
{
    uint32_t تخم;

    إذا (av_random_بایټونه((uint8_t *)&تخم, حجم(تخم)) < 0)
        أرجع get_generic_تخم();

    أرجع تخم;
}

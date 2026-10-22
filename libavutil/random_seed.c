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

#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_UNISTD_H
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_IO_H
#అన్తర్భావ <io.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_BCRYPT
#అన్తర్భావ <windows.h>
#అన్తర్భావ <bcrypt.h>
#అయితే_ముగింపు
#ఒకవేళ CONFIG_GCRYPT
#అన్తర్భావ <gcrypt.h>
#లేదావేళ CONFIG_OPENSSL
#అన్తర్భావ <openssl/rand.h>
#అయితే_ముగింపు
#అన్తర్భావ <fcntl.h>
#అన్తర్భావ <math.h>
#అన్తర్భావ <time.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "file_open.h"
#అన్తర్భావ "internal.h"
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "timer.h"
#అన్తర్భావ "random_seed.h"
#అన్తర్భావ "sha.h"

#నిర్వచితం_కాకపోతే TEST
#నిర్వచించు TEST 0
#అయితే_ముగింపు

స్థిర పూర్ణాంకం read_random(uint8_t *dst, size_t len, స్థిరరాశి అక్షరం *file)
{
#ఒకవేళ HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    ఒకవేళ (!fp)
        తిరిగి AVERROR_UNKNOWN;
    setvbuf(fp, ఖాళీ, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    ఒకవేళ (err != len)
        తిరిగి AVERROR_UNKNOWN;

    తిరిగి 0;
#లేకపోతే
    తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు
}

స్థిర uint32_t get_generic_విత్తనం(శూన్య)
{
    uint64_t tmp[120/8];
    నిర్మాణం AVSHA *sha = (శూన్య*)tmp;
    clock_t చివరి_t  = 0;
    clock_t చివరి_td = 0;
    clock_t init_t = 0;
    స్థిర uint64_t i = 0;
    స్థిర uint32_t బఫరు[512] = { 0 };
    గుర్తులేని అక్షరం digest[20];
    uint64_t చివరి_i = i;
    పూర్ణాంకం repeats[3] = { 0 };

    av_assert0(పరిమాణం(tmp) >= av_sha_కొలత);

    ఒకవేళ(TEST){
        memset(బఫరు, 0, పరిమాణం(బఫరు));
        చివరి_i = i = 0;
    }లేకపోతే{
#నిర్వచితమైతే AV_READ_సమయం
        బఫరు[13] ^= AV_READ_సమయం();
        బఫరు[41] ^= AV_READ_సమయం()>>32;
#అయితే_ముగింపు
    }

    కొరకు (;;) {
        clock_t t = clock();
        పూర్ణాంకం incremented_i = 0;
        పూర్ణాంకం cur_td = t - చివరి_t;
        ఒకవేళ (చివరి_t + 2*చివరి_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            బఫరు[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } లేకపోతే ఒకవేళ (t != చివరి_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            బఫరు[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } లేకపోతే {
            బఫరు[i & 511] = 1664525*బఫరు[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        ఒకవేళ (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            ఒకవేళ (చివరి_i && i - చివరి_i > 4 || i - చివరి_i > 64 || TEST && i - చివరి_i > 8)
                ఆపు;
        }
        ఒకవేళ (t == చివరి_t) {
            repeats[0]++;
        } లేకపోతే {
            // If we got a new unique number of repeats, update the history.
            ఒకవేళ (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        చివరి_t = t;
        చివరి_td = cur_td;
        ఒకవేళ (!init_t)
            init_t = t;
    }

    ఒకవేళ(TEST) {
        బఫరు[0] = బఫరు[1] = 0;
    } లేకపోతే {
#నిర్వచితమైతే AV_READ_సమయం
        బఫరు[111] += AV_READ_సమయం();
#అయితే_ముగింపు
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (స్థిరరాశి uint8_t *)బఫరు, పరిమాణం(బఫరు));
    av_sha_final(sha, digest);
    తిరిగి AV_RB32(digest) + AV_RB32(digest + 16);
}

పూర్ణాంకం av_random_బైట్లు(uint8_t* buf, size_t len)
{
    పూర్ణాంకం err;

#ఒకవేళ HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    ఒకవేళ (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        ఒకవేళ (BCRYPT_SUCCESS(ret))
            తిరిగి 0;
    }
#అయితే_ముగింపు

#ఒకవేళ HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    తిరిగి 0;
#అయితే_ముగింపు

    err = read_random(buf, len, "/dev/urandom");
    ఒకవేళ (!err)
        తిరిగి err;

#ఒకవేళ CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    తిరిగి 0;
#లేదావేళ CONFIG_OPENSSL
    ఒకవేళ (RAND_బైట్లు(buf, len) == 1)
        తిరిగి 0;
    తిరిగి AVERROR_EXTERNAL;
#లేకపోతే
    తిరిగి err;
#అయితే_ముగింపు
}

uint32_t av_get_random_విత్తనం(శూన్య)
{
    uint32_t విత్తనం;

    ఒకవేళ (av_random_బైట్లు((uint8_t *)&విత్తనం, పరిమాణం(విత్తనం)) < 0)
        తిరిగి get_generic_విత్తనం();

    తిరిగి విత్తనం;
}

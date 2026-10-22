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

#अन्तर्भाव "config.h"

#जइ HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#जइ HAVE_IO_H
#अन्तर्भाव <io.h>
#endif
#जइ HAVE_BCRYPT
#अन्तर्भाव <windows.h>
#अन्तर्भाव <bcrypt.h>
#endif
#जइ CONFIG_GCRYPT
#अन्तर्भाव <gcrypt.h>
#नोचेद्यदि CONFIG_OPENSSL
#अन्तर्भाव <openssl/rand.h>
#endif
#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <math.h>
#अन्तर्भाव <time.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "file_open.h"
#अन्तर्भाव "internal.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "timer.h"
#अन्तर्भाव "random_seed.h"
#अन्तर्भाव "sha.h"

#ifndef TEST
#define TEST 0
#endif

स्थिर पूर्णाङ्क read_random(uint8_t *dst, size_t len, ध्रुव वर्ण *file)
{
#जइ HAVE_UNISTD_H
    FILE *fp = avpriv_fopen_utf8(file, "r");
    size_t err;

    जइ (!fp)
        प्रत्यागम AVERROR_UNKNOWN;
    setvbuf(fp, रिक्त, _IONBF, 0);
    err = fread(dst, 1, len, fp);
    fclose(fp);

    जइ (err != len)
        प्रत्यागम AVERROR_UNKNOWN;

    प्रत्यागम 0;
#अण्णहा
    प्रत्यागम AVERROR(ENOSYS);
#endif
}

स्थिर uint32_t get_generic_seed(शून्य)
{
    uint64_t tmp[120/8];
    संरचना AVSHA *sha = (शून्य*)tmp;
    clock_t last_t  = 0;
    clock_t last_td = 0;
    clock_t init_t = 0;
    स्थिर uint64_t i = 0;
    स्थिर uint32_t buffer[512] = { 0 };
    unsigned वर्ण digest[20];
    uint64_t last_i = i;
    पूर्णाङ्क repeats[3] = { 0 };

    av_assert0(परिमाण(tmp) >= av_sha_size);

    जइ(TEST){
        memset(buffer, 0, परिमाण(buffer));
        last_i = i = 0;
    }अण्णहा{
#ifdef AV_READ_TIME
        buffer[13] ^= AV_READ_TIME();
        buffer[41] ^= AV_READ_TIME()>>32;
#endif
    }

    प्रति (;;) {
        clock_t t = clock();
        पूर्णाङ्क incremented_i = 0;
        पूर्णाङ्क cur_td = t - last_t;
        जइ (last_t + 2*last_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            buffer[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } अण्णहा जइ (t != last_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            buffer[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } अण्णहा {
            buffer[i & 511] = 1664525*buffer[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        जइ (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            जइ (last_i && i - last_i > 4 || i - last_i > 64 || TEST && i - last_i > 8)
                भङ्ग;
        }
        जइ (t == last_t) {
            repeats[0]++;
        } अण्णहा {
            // If we got a new unique number of repeats, update the history.
            जइ (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        last_t = t;
        last_td = cur_td;
        जइ (!init_t)
            init_t = t;
    }

    जइ(TEST) {
        buffer[0] = buffer[1] = 0;
    } अण्णहा {
#ifdef AV_READ_TIME
        buffer[111] += AV_READ_TIME();
#endif
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (ध्रुव uint8_t *)buffer, परिमाण(buffer));
    av_sha_final(sha, digest);
    प्रत्यागम AV_RB32(digest) + AV_RB32(digest + 16);
}

पूर्णाङ्क av_random_bytes(uint8_t* buf, size_t len)
{
    पूर्णाङ्क err;

#जइ HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    जइ (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        जइ (BCRYPT_SUCCESS(ret))
            प्रत्यागम 0;
    }
#endif

#जइ HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    प्रत्यागम 0;
#endif

    err = read_random(buf, len, "/dev/urandom");
    जइ (!err)
        प्रत्यागम err;

#जइ CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    प्रत्यागम 0;
#नोचेद्यदि CONFIG_OPENSSL
    जइ (RAND_bytes(buf, len) == 1)
        प्रत्यागम 0;
    प्रत्यागम AVERROR_EXTERNAL;
#अण्णहा
    प्रत्यागम err;
#endif
}

uint32_t av_get_random_seed(शून्य)
{
    uint32_t seed;

    जइ (av_random_bytes((uint8_t *)&seed, परिमाण(seed)) < 0)
        प्रत्यागम get_generic_seed();

    प्रत्यागम seed;
}

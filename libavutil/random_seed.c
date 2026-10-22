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

#समावेश "config.h"

#अगर HAVE_UNISTD_H
#समावेश <unistd.h>
#पूर्ण_अगर
#अगर HAVE_IO_H
#समावेश <io.h>
#पूर्ण_अगर
#अगर HAVE_BCRYPT
#समावेश <windows.h>
#समावेश <bcrypt.h>
#पूर्ण_अगर
#अगर CONFIG_GCRYPT
#समावेश <gcrypt.h>
#या_अगर CONFIG_OPENSSL
#समावेश <openssl/rand.h>
#पूर्ण_अगर
#समावेश <fcntl.h>
#समावेश <math.h>
#समावेश <time.h>
#समावेश <string.h>
#समावेश "avassert.h"
#समावेश "file_open.h"
#समावेश "internal.h"
#समावेश "intreadwrite.h"
#समावेश "timer.h"
#समावेश "random_seed.h"
#समावेश "sha.h"

#अगर_अघोषित TEST
#घोषणा TEST 0
#पूर्ण_अगर

अटल पूर्णांक read_random(uint8_t *dst, माप_प्रकार len, स्थिर अक्षर *file)
{
#अगर HAVE_UNISTD_H
    खाता *fp = avpriv_fopen_utf8(file, "r");
    माप_प्रकार err;

    अगर (!fp)
        वापस AVERROR_UNKNOWN;
    रखो_भबफ(fp, शून्य, _IONBF, 0);
    err = ख_पढ़ो(dst, 1, len, fp);
    ख_बंद(fp);

    अगर (err != len)
        वापस AVERROR_UNKNOWN;

    वापस 0;
#अन्यथा
    वापस AVERROR(ENOSYS);
#पूर्ण_अगर
}

अटल uint32_t get_generic_seed(व्योम)
{
    uint64_t tmp[120/8];
    काष्ठा AVSHA *sha = (व्योम*)tmp;
    घड़ी_प्रकार last_t  = 0;
    घड़ी_प्रकार last_td = 0;
    घड़ी_प्रकार init_t = 0;
    अटल uint64_t i = 0;
    अटल uint32_t बफर[512] = { 0 };
    अचिन्हित अक्षर digest[20];
    uint64_t last_i = i;
    पूर्णांक repeats[3] = { 0 };

    av_assert0(माप(tmp) >= av_sha_आकार);

    अगर(TEST){
        स_रखो(बफर, 0, माप(बफर));
        last_i = i = 0;
    }अन्यथा{
#अगर_घोषित AV_READ_TIME
        बफर[13] ^= AV_READ_TIME();
        बफर[41] ^= AV_READ_TIME()>>32;
#पूर्ण_अगर
    }

    क्रम (;;) {
        घड़ी_प्रकार t = घड़ी();
        पूर्णांक incremented_i = 0;
        पूर्णांक cur_td = t - last_t;
        अगर (last_t + 2*last_td + (CLOCKS_PER_SEC > 1000) < t) {
            // If the timer incremented by more than 2*last_td at once,
            // we may e.g. have had a context switch. If the timer resolution
            // is high (CLOCKS_PER_SEC > 1000), require that the timer
            // incremented by more than 1. If the timer resolution is low,
            // it is enough that the timer incremented at all.
            बफर[++i & 511] += cur_td % 3294638521U;
            incremented_i = 1;
        } अन्यथा अगर (t != last_t && repeats[0] > 0 && repeats[1] > 0 &&
                   repeats[2] > 0 && repeats[0] != repeats[1] &&
                   repeats[0] != repeats[2]) {
            // If the timer resolution is high, and we get the same timer
            // value multiple times, use variances in the number of repeats
            // of each timer value as entropy. If we get a different number of
            // repeats than the last two unique cases, count that as entropy
            // and proceed to the next index.
            बफर[++i & 511] += (repeats[0] + repeats[1] + repeats[2]) % 3294638521U;
            incremented_i = 1;
        } अन्यथा {
            बफर[i & 511] = 1664525*बफर[i & 511] + 1013904223 + (cur_td % 3294638521U);
        }
        अगर (incremented_i && (t - init_t) >= CLOCKS_PER_SEC>>5) {
            अगर (last_i && i - last_i > 4 || i - last_i > 64 || TEST && i - last_i > 8)
                अवरोध;
        }
        अगर (t == last_t) {
            repeats[0]++;
        } अन्यथा {
            // If we got a new unique number of repeats, update the history.
            अगर (repeats[0] != repeats[1]) {
                repeats[2] = repeats[1];
                repeats[1] = repeats[0];
            }
            repeats[0] = 0;
        }
        last_t = t;
        last_td = cur_td;
        अगर (!init_t)
            init_t = t;
    }

    अगर(TEST) {
        बफर[0] = बफर[1] = 0;
    } अन्यथा {
#अगर_घोषित AV_READ_TIME
        बफर[111] += AV_READ_TIME();
#पूर्ण_अगर
    }

    av_sha_init(sha, 160);
    av_sha_update(sha, (स्थिर uint8_t *)बफर, माप(बफर));
    av_sha_final(sha, digest);
    वापस AV_RB32(digest) + AV_RB32(digest + 16);
}

पूर्णांक av_random_bytes(uint8_t* buf, माप_प्रकार len)
{
    पूर्णांक err;

#अगर HAVE_BCRYPT
    BCRYPT_ALG_HANDLE algo_handle;
    NTSTATUS ret = BCryptOpenAlgorithmProvider(&algo_handle, BCRYPT_RNG_ALGORITHM,
                                               MS_PRIMITIVE_PROVIDER, 0);
    अगर (BCRYPT_SUCCESS(ret)) {
        NTSTATUS ret = BCryptGenRandom(algo_handle, (PUCHAR)buf, len, 0);
        BCryptCloseAlgorithmProvider(algo_handle, 0);
        अगर (BCRYPT_SUCCESS(ret))
            वापस 0;
    }
#पूर्ण_अगर

#अगर HAVE_ARC4RANDOM_BUF
    arc4random_buf(buf, len);
    वापस 0;
#पूर्ण_अगर

    err = read_random(buf, len, "/dev/urandom");
    अगर (!err)
        वापस err;

#अगर CONFIG_GCRYPT
    gcry_randomize(buf, len, GCRY_VERY_STRONG_RANDOM);
    वापस 0;
#या_अगर CONFIG_OPENSSL
    अगर (RAND_bytes(buf, len) == 1)
        वापस 0;
    वापस AVERROR_EXTERNAL;
#अन्यथा
    वापस err;
#पूर्ण_अगर
}

uint32_t av_get_random_seed(व्योम)
{
    uint32_t seed;

    अगर (av_random_bytes((uint8_t *)&seed, माप(seed)) < 0)
        वापस get_generic_seed();

    वापस seed;
}

/*
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

#include "libavutil/hmac.c"

#include <stdio.h>
#include <string.h>

static void test(AVHMAC *hmac, const uint8_t *key, ຈຳນວນເຕັມ keylen,
                 const uint8_t *data, ຈຳນວນເຕັມ datalen)
{
    uint8_t buf[MAX_HASHLEN];
    ຈຳນວນເຕັມ out, i;
    // Some of the test vectors are strings, where sizeof() includes the
    // trailing null byte - remove that.
    ຖ້າ (!key[keylen - 1])
        keylen--;
    ຖ້າ (!data[datalen - 1])
        datalen--;
    out = av_hmac_calc(hmac, data, datalen, key, keylen, buf, parimaa_na(buf));
    ສຳລັບ (i = 0; i < out; i++)
        printf("%02x", buf[i]);
    printf("\n");
}

ຈຳນວນເຕັມ main(void)
{
    uint8_t key1[20], key3[131], data3[50];
    AVHMAC *hmac;
    ga_nanaa AVHMACType i;
    static const uint8_t key2[]  = "Jefe";
    static const uint8_t data1[] = "Hi There";
    static const uint8_t data2[] = "what do ya want for nothing?";
    static const uint8_t data4[] = "Test Using Larger Than Block-Size Key - Hash Key First";
    static const uint8_t data5[] = "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
    static const uint8_t data6[] = "This is a test using a larger than block-size key and a larger "
                            "than block-size data. The key needs to be hashed before being used"
                            " by the HMAC algorithm.";
    memset(key1, 0x0b, parimaa_na(key1));
    memset(key3, 0xaa, parimaa_na(key3));
    memset(data3, 0xdd, parimaa_na(data3));

    /* MD5, SHA-1 */
    ສຳລັບ (i = AV_HMAC_MD5; i <= AV_HMAC_SHA1; i++) {
        hmac = av_hmac_alloc(i);
        ຖ້າ (!hmac)
            ສົ່ງຄືນ 1;
        // RFC 2202 test vectors
        test(hmac, key1, hmac->hashlen, data1, parimaa_na(data1));
        test(hmac, key2, parimaa_na(key2),  data2, parimaa_na(data2));
        test(hmac, key3, hmac->hashlen, data3, parimaa_na(data3));
        test(hmac, key3, 80,            data4, parimaa_na(data4));
        test(hmac, key3, 80,            data5, parimaa_na(data5));
        av_hmac_free(hmac);
    }

    /* SHA-2 */
    ສຳລັບ (i = AV_HMAC_SHA224; i <= AV_HMAC_SHA512; i++) {
        hmac = av_hmac_alloc(i);
        ຖ້າ (!hmac)
            ສົ່ງຄືນ 1;
        // RFC 4231 test vectors
        test(hmac, key1, parimaa_na(key1), data1, parimaa_na(data1));
        test(hmac, key2, parimaa_na(key2), data2, parimaa_na(data2));
        test(hmac, key3, 20,           data3, parimaa_na(data3));
        test(hmac, key3, parimaa_na(key3), data4, parimaa_na(data4));
        test(hmac, key3, parimaa_na(key3), data6, parimaa_na(data6));
        av_hmac_free(hmac);
    }

    ສົ່ງຄືນ 0;
}

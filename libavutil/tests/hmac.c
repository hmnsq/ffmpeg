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

#অন্তর্ভাব "libavutil/hmac.c"

#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <string.h>

স্থির শূন্য test(AVHMAC *hmac, ধ্রুবক uint8_t *চাবি, পূর্ণসংখ্যা keylen,
                 ধ্রুবক uint8_t *তথ্য, পূর্ণসংখ্যা datalen)
{
    uint8_t buf[MAX_HASHLEN];
    পূর্ণসংখ্যা out, i;
    // Some of the test vectors are strings, where sizeof() includes the
    // trailing null byte - remove that.
    যদি (!চাবি[keylen - 1])
        keylen--;
    যদি (!তথ্য[datalen - 1])
        datalen--;
    out = av_hmac_calc(hmac, তথ্য, datalen, চাবি, keylen, buf, আকার(buf));
    জন্য (i = 0; i < out; i++)
        printf("%02x", buf[i]);
    printf("\n");
}

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    uint8_t key1[20], key3[131], data3[50];
    AVHMAC *hmac;
    গণনা AVHMACType i;
    স্থির ধ্রুবক uint8_t key2[]  = "Jefe";
    স্থির ধ্রুবক uint8_t data1[] = "Hi There";
    স্থির ধ্রুবক uint8_t data2[] = "what do ya want for nothing?";
    স্থির ধ্রুবক uint8_t data4[] = "Test Using Larger Than Block-Size Key - Hash Key First";
    স্থির ধ্রুবক uint8_t data5[] = "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
    স্থির ধ্রুবক uint8_t data6[] = "This is a test using a larger than block-size key and a larger "
                            "than block-size data. The key needs to be hashed before being used"
                            " by the HMAC algorithm.";
    memset(key1, 0x0b, আকার(key1));
    memset(key3, 0xaa, আকার(key3));
    memset(data3, 0xdd, আকার(data3));

    /* MD5, SHA-1 */
    জন্য (i = AV_HMAC_MD5; i <= AV_HMAC_SHA1; i++) {
        hmac = av_hmac_alloc(i);
        যদি (!hmac)
            ফেরত 1;
        // RFC 2202 test vectors
        test(hmac, key1, hmac->hashlen, data1, আকার(data1));
        test(hmac, key2, আকার(key2),  data2, আকার(data2));
        test(hmac, key3, hmac->hashlen, data3, আকার(data3));
        test(hmac, key3, 80,            data4, আকার(data4));
        test(hmac, key3, 80,            data5, আকার(data5));
        av_hmac_free(hmac);
    }

    /* SHA-2 */
    জন্য (i = AV_HMAC_SHA224; i <= AV_HMAC_SHA512; i++) {
        hmac = av_hmac_alloc(i);
        যদি (!hmac)
            ফেরত 1;
        // RFC 4231 test vectors
        test(hmac, key1, আকার(key1), data1, আকার(data1));
        test(hmac, key2, আকার(key2), data2, আকার(data2));
        test(hmac, key3, 20,           data3, আকার(data3));
        test(hmac, key3, আকার(key3), data4, আকার(data4));
        test(hmac, key3, আকার(key3), data6, আকার(data6));
        av_hmac_free(hmac);
    }

    ফেরত 0;
}

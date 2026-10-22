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

#அந்தர்பாவ "libavutil/hmac.c"

#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <string.h>

நிலையான வெறுமை test(AVHMAC *hmac, மாறிலி uint8_t *சாவி, முழு keylen,
                 மாறிலி uint8_t *data, முழு datalen)
{
    uint8_t buf[MAX_HASHLEN];
    முழு out, i;
    // Some of the test vectors are strings, where sizeof() includes the
    // trailing null byte - remove that.
    எனில் (!சாவி[keylen - 1])
        keylen--;
    எனில் (!data[datalen - 1])
        datalen--;
    out = av_hmac_calc(hmac, data, datalen, சாவி, keylen, buf, அளவு(buf));
    க்கு (i = 0; i < out; i++)
        printf("%02x", buf[i]);
    printf("\n");
}

முழு முதன்மை(வெறுமை)
{
    uint8_t key1[20], key3[131], data3[50];
    AVHMAC *hmac;
    எண்ணிக்கை AVHMACType i;
    நிலையான மாறிலி uint8_t key2[]  = "Jefe";
    நிலையான மாறிலி uint8_t data1[] = "Hi There";
    நிலையான மாறிலி uint8_t data2[] = "what do ya want for nothing?";
    நிலையான மாறிலி uint8_t data4[] = "Test Using Larger Than Block-Size Key - Hash Key First";
    நிலையான மாறிலி uint8_t data5[] = "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
    நிலையான மாறிலி uint8_t data6[] = "This is a test using a larger than block-size key and a larger "
                            "than block-size data. The key needs to be hashed before being used"
                            " by the HMAC algorithm.";
    memset(key1, 0x0b, அளவு(key1));
    memset(key3, 0xaa, அளவு(key3));
    memset(data3, 0xdd, அளவு(data3));

    /* MD5, SHA-1 */
    க்கு (i = AV_HMAC_MD5; i <= AV_HMAC_SHA1; i++) {
        hmac = av_hmac_alloc(i);
        எனில் (!hmac)
            திரும்பு 1;
        // RFC 2202 test vectors
        test(hmac, key1, hmac->hashlen, data1, அளவு(data1));
        test(hmac, key2, அளவு(key2),  data2, அளவு(data2));
        test(hmac, key3, hmac->hashlen, data3, அளவு(data3));
        test(hmac, key3, 80,            data4, அளவு(data4));
        test(hmac, key3, 80,            data5, அளவு(data5));
        av_hmac_free(hmac);
    }

    /* SHA-2 */
    க்கு (i = AV_HMAC_SHA224; i <= AV_HMAC_SHA512; i++) {
        hmac = av_hmac_alloc(i);
        எனில் (!hmac)
            திரும்பு 1;
        // RFC 4231 test vectors
        test(hmac, key1, அளவு(key1), data1, அளவு(data1));
        test(hmac, key2, அளவு(key2), data2, அளவு(data2));
        test(hmac, key3, 20,           data3, அளவு(data3));
        test(hmac, key3, அளவு(key3), data4, அளவு(data4));
        test(hmac, key3, அளவு(key3), data6, அளவு(data6));
        av_hmac_free(hmac);
    }

    திரும்பு 0;
}

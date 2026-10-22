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

#ଅନ୍ତର୍ଭାଵ "libavutil/hmac.c"

#ଅନ୍ତର୍ଭାଵ <stdio.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

ସ୍ଥିର ଶୂନ୍ୟ test(AVHMAC *hmac, ଅଚଳ uint8_t *ଚାବି, ପୂର୍ଣ୍ଣସଂଖ୍ୟା keylen,
                 ଅଚଳ uint8_t *data, ପୂର୍ଣ୍ଣସଂଖ୍ୟା datalen)
{
    uint8_t buf[MAX_HASHLEN];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା out, i;
    // Some of the test vectors are strings, where sizeof() includes the
    // trailing null byte - remove that.
    ଯଦି (!ଚାବି[keylen - 1])
        keylen--;
    ଯଦି (!data[datalen - 1])
        datalen--;
    out = av_hmac_calc(hmac, data, datalen, ଚାବି, keylen, buf, ଆକାର(buf));
    ପାଇଁ (i = 0; i < out; i++)
        printf("%02x", buf[i]);
    printf("\n");
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ଶୂନ୍ୟ)
{
    uint8_t key1[20], key3[131], data3[50];
    AVHMAC *hmac;
    ଗଣନା AVHMACType i;
    ସ୍ଥିର ଅଚଳ uint8_t key2[]  = "Jefe";
    ସ୍ଥିର ଅଚଳ uint8_t data1[] = "Hi There";
    ସ୍ଥିର ଅଚଳ uint8_t data2[] = "what do ya want for nothing?";
    ସ୍ଥିର ଅଚଳ uint8_t data4[] = "Test Using Larger Than Block-Size Key - Hash Key First";
    ସ୍ଥିର ଅଚଳ uint8_t data5[] = "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
    ସ୍ଥିର ଅଚଳ uint8_t data6[] = "This is a test using a larger than block-size key and a larger "
                            "than block-size data. The key needs to be hashed before being used"
                            " by the HMAC algorithm.";
    memset(key1, 0x0b, ଆକାର(key1));
    memset(key3, 0xaa, ଆକାର(key3));
    memset(data3, 0xdd, ଆକାର(data3));

    /* MD5, SHA-1 */
    ପାଇଁ (i = AV_HMAC_MD5; i <= AV_HMAC_SHA1; i++) {
        hmac = av_hmac_alloc(i);
        ଯଦି (!hmac)
            ଫେରନ୍ତୁ 1;
        // RFC 2202 test vectors
        test(hmac, key1, hmac->hashlen, data1, ଆକାର(data1));
        test(hmac, key2, ଆକାର(key2),  data2, ଆକାର(data2));
        test(hmac, key3, hmac->hashlen, data3, ଆକାର(data3));
        test(hmac, key3, 80,            data4, ଆକାର(data4));
        test(hmac, key3, 80,            data5, ଆକାର(data5));
        av_hmac_free(hmac);
    }

    /* SHA-2 */
    ପାଇଁ (i = AV_HMAC_SHA224; i <= AV_HMAC_SHA512; i++) {
        hmac = av_hmac_alloc(i);
        ଯଦି (!hmac)
            ଫେରନ୍ତୁ 1;
        // RFC 4231 test vectors
        test(hmac, key1, ଆକାର(key1), data1, ଆକାର(data1));
        test(hmac, key2, ଆକାର(key2), data2, ଆକାର(data2));
        test(hmac, key3, 20,           data3, ଆକାର(data3));
        test(hmac, key3, ଆକାର(key3), data4, ଆକାର(data4));
        test(hmac, key3, ଆକାର(key3), data6, ଆକାର(data6));
        av_hmac_free(hmac);
    }

    ଫେରନ୍ତୁ 0;
}

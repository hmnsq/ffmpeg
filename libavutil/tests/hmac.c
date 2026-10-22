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

#అన్తర్భావ "libavutil/hmac.c"

#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>

స్థిర శూన్య test(AVHMAC *hmac, స్థిరరాశి uint8_t *కీలకం, పూర్ణాంకం keylen,
                 స్థిరరాశి uint8_t *దత్తాంశం, పూర్ణాంకం datalen)
{
    uint8_t buf[MAX_HASHLEN];
    పూర్ణాంకం బహిర్గతం, i;
    // Some of the test vectors are strings, where sizeof() includes the
    // trailing null byte - remove that.
    ఒకవేళ (!కీలకం[keylen - 1])
        keylen--;
    ఒకవేళ (!దత్తాంశం[datalen - 1])
        datalen--;
    బహిర్గతం = av_hmac_calc(hmac, దత్తాంశం, datalen, కీలకం, keylen, buf, పరిమాణం(buf));
    కొరకు (i = 0; i < బహిర్గతం; i++)
        రాయి("%02x", buf[i]);
    రాయి("\n");
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    uint8_t key1[20], key3[131], data3[50];
    AVHMAC *hmac;
    గణన AVHMACType i;
    స్థిర స్థిరరాశి uint8_t key2[]  = "Jefe";
    స్థిర స్థిరరాశి uint8_t data1[] = "Hi There";
    స్థిర స్థిరరాశి uint8_t data2[] = "what do ya want for nothing?";
    స్థిర స్థిరరాశి uint8_t data4[] = "Test Using Larger Than Block-Size Key - Hash Key First";
    స్థిర స్థిరరాశి uint8_t data5[] = "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
    స్థిర స్థిరరాశి uint8_t data6[] = "This is a test using a larger than block-size key and a larger "
                            "than block-size data. The key needs to be hashed before being used"
                            " by the HMAC algorithm.";
    memset(key1, 0x0b, పరిమాణం(key1));
    memset(key3, 0xaa, పరిమాణం(key3));
    memset(data3, 0xdd, పరిమాణం(data3));

    /* MD5, SHA-1 */
    కొరకు (i = AV_HMAC_MD5; i <= AV_HMAC_SHA1; i++) {
        hmac = av_hmac_alloc(i);
        ఒకవేళ (!hmac)
            తిరిగి 1;
        // RFC 2202 test vectors
        test(hmac, key1, hmac->hashlen, data1, పరిమాణం(data1));
        test(hmac, key2, పరిమాణం(key2),  data2, పరిమాణం(data2));
        test(hmac, key3, hmac->hashlen, data3, పరిమాణం(data3));
        test(hmac, key3, 80,            data4, పరిమాణం(data4));
        test(hmac, key3, 80,            data5, పరిమాణం(data5));
        av_hmac_free(hmac);
    }

    /* SHA-2 */
    కొరకు (i = AV_HMAC_SHA224; i <= AV_HMAC_SHA512; i++) {
        hmac = av_hmac_alloc(i);
        ఒకవేళ (!hmac)
            తిరిగి 1;
        // RFC 4231 test vectors
        test(hmac, key1, పరిమాణం(key1), data1, పరిమాణం(data1));
        test(hmac, key2, పరిమాణం(key2), data2, పరిమాణం(data2));
        test(hmac, key3, 20,           data3, పరిమాణం(data3));
        test(hmac, key3, పరిమాణం(key3), data4, పరిమాణం(data4));
        test(hmac, key3, పరిమాణం(key3), data6, పరిమాణం(data6));
        av_hmac_free(hmac);
    }

    తిరిగి 0;
}

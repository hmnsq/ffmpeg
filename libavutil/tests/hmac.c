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

#अन्तर्भाव "libavutil/hmac.c"

#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>

स्थिर शून्य test(AVHMAC *hmac, स्थिरांक uint8_t *किल्ली, पूर्णांक keylen,
                 स्थिरांक uint8_t *data, पूर्णांक datalen)
{
    uint8_t buf[MAX_HASHLEN];
    पूर्णांक out, i;
    // Some of the test vectors are strings, where sizeof() includes the
    // trailing null byte - remove that.
    जर (!किल्ली[keylen - 1])
        keylen--;
    जर (!data[datalen - 1])
        datalen--;
    out = av_hmac_calc(hmac, data, datalen, किल्ली, keylen, buf, आकार(buf));
    साठी (i = 0; i < out; i++)
        म_लिखो("%02x", buf[i]);
    म_लिखो("\n");
}

पूर्णांक main(शून्य)
{
    uint8_t key1[20], key3[131], data3[50];
    AVHMAC *hmac;
    गणना AVHMACType i;
    स्थिर स्थिरांक uint8_t key2[]  = "Jefe";
    स्थिर स्थिरांक uint8_t data1[] = "Hi There";
    स्थिर स्थिरांक uint8_t data2[] = "what do ya want for nothing?";
    स्थिर स्थिरांक uint8_t data4[] = "Test Using Larger Than Block-Size Key - Hash Key First";
    स्थिर स्थिरांक uint8_t data5[] = "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
    स्थिर स्थिरांक uint8_t data6[] = "This is a test using a larger than block-size key and a larger "
                            "than block-size data. The key needs to be hashed before being used"
                            " by the HMAC algorithm.";
    स_रखो(key1, 0x0b, आकार(key1));
    स_रखो(key3, 0xaa, आकार(key3));
    स_रखो(data3, 0xdd, आकार(data3));

    /* MD5, SHA-1 */
    साठी (i = AV_HMAC_MD5; i <= AV_HMAC_SHA1; i++) {
        hmac = av_hmac_alloc(i);
        जर (!hmac)
            परत 1;
        // RFC 2202 test vectors
        test(hmac, key1, hmac->hashlen, data1, आकार(data1));
        test(hmac, key2, आकार(key2),  data2, आकार(data2));
        test(hmac, key3, hmac->hashlen, data3, आकार(data3));
        test(hmac, key3, 80,            data4, आकार(data4));
        test(hmac, key3, 80,            data5, आकार(data5));
        av_hmac_free(hmac);
    }

    /* SHA-2 */
    साठी (i = AV_HMAC_SHA224; i <= AV_HMAC_SHA512; i++) {
        hmac = av_hmac_alloc(i);
        जर (!hmac)
            परत 1;
        // RFC 4231 test vectors
        test(hmac, key1, आकार(key1), data1, आकार(data1));
        test(hmac, key2, आकार(key2), data2, आकार(data2));
        test(hmac, key3, 20,           data3, आकार(data3));
        test(hmac, key3, आकार(key3), data4, आकार(data4));
        test(hmac, key3, आकार(key3), data6, आकार(data6));
        av_hmac_free(hmac);
    }

    परत 0;
}

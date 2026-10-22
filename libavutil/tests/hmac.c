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

#समावेश "libavutil/hmac.c"

#समावेश <stdio.h>
#समावेश <string.h>

अटल व्योम test(AVHMAC *hmac, स्थिर uint8_t *कुंजी, पूर्णांक keylen,
                 स्थिर uint8_t *तथ्य, पूर्णांक datalen)
{
    uint8_t buf[MAX_HASHLEN];
    पूर्णांक out, i;
    // Some of the test vectors are strings, where sizeof() includes the
    // trailing null byte - remove that.
    अगर (!कुंजी[keylen - 1])
        keylen--;
    अगर (!तथ्य[datalen - 1])
        datalen--;
    out = av_hmac_calc(hmac, तथ्य, datalen, कुंजी, keylen, buf, माप(buf));
    क्रम (i = 0; i < out; i++)
        म_लिखो("%02x", buf[i]);
    म_लिखो("\n");
}

पूर्णांक मुख्य(व्योम)
{
    uint8_t key1[20], key3[131], data3[50];
    AVHMAC *hmac;
    क्रमागत AVHMACType i;
    अटल स्थिर uint8_t key2[]  = "Jefe";
    अटल स्थिर uint8_t data1[] = "Hi There";
    अटल स्थिर uint8_t data2[] = "what do ya want for nothing?";
    अटल स्थिर uint8_t data4[] = "Test Using Larger Than Block-Size Key - Hash Key First";
    अटल स्थिर uint8_t data5[] = "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
    अटल स्थिर uint8_t data6[] = "This is a test using a larger than block-size key and a larger "
                            "than block-size data. The key needs to be hashed before being used"
                            " by the HMAC algorithm.";
    स_रखो(key1, 0x0b, माप(key1));
    स_रखो(key3, 0xaa, माप(key3));
    स_रखो(data3, 0xdd, माप(data3));

    /* MD5, SHA-1 */
    क्रम (i = AV_HMAC_MD5; i <= AV_HMAC_SHA1; i++) {
        hmac = av_hmac_alloc(i);
        अगर (!hmac)
            वापस 1;
        // RFC 2202 test vectors
        test(hmac, key1, hmac->hashlen, data1, माप(data1));
        test(hmac, key2, माप(key2),  data2, माप(data2));
        test(hmac, key3, hmac->hashlen, data3, माप(data3));
        test(hmac, key3, 80,            data4, माप(data4));
        test(hmac, key3, 80,            data5, माप(data5));
        av_hmac_free(hmac);
    }

    /* SHA-2 */
    क्रम (i = AV_HMAC_SHA224; i <= AV_HMAC_SHA512; i++) {
        hmac = av_hmac_alloc(i);
        अगर (!hmac)
            वापस 1;
        // RFC 4231 test vectors
        test(hmac, key1, माप(key1), data1, माप(data1));
        test(hmac, key2, माप(key2), data2, माप(data2));
        test(hmac, key3, 20,           data3, माप(data3));
        test(hmac, key3, माप(key3), data4, माप(data4));
        test(hmac, key3, माप(key3), data6, माप(data6));
        av_hmac_free(hmac);
    }

    वापस 0;
}

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

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/hmac.c"

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

ਸਥਿਰ ਖਾਲੀ test(AVHMAC *hmac, ਅਚਲ uint8_t *ਕੁੰਜੀ, ਪੂਰਨ keylen,
                 ਅਚਲ uint8_t *ਅੰਕੜੇ, ਪੂਰਨ datalen)
{
    uint8_t buf[MAX_HASHLEN];
    ਪੂਰਨ ਬਾਹਰਲਾ, i;
    // Some of the test vectors are strings, where sizeof() includes the
    // trailing null byte - remove that.
    ਜੇ (!ਕੁੰਜੀ[keylen - 1])
        keylen--;
    ਜੇ (!ਅੰਕੜੇ[datalen - 1])
        datalen--;
    ਬਾਹਰਲਾ = av_hmac_calc(hmac, ਅੰਕੜੇ, datalen, ਕੁੰਜੀ, keylen, buf, ਆਕਾਰ(buf));
    ਲਈ (i = 0; i < ਬਾਹਰਲਾ; i++)
        ਲਿਖੋ("%02x", buf[i]);
    ਲਿਖੋ("\n");
}

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    uint8_t key1[20], key3[131], data3[50];
    AVHMAC *hmac;
    ਗਿਣਤੀ AVHMACType i;
    ਸਥਿਰ ਅਚਲ uint8_t key2[]  = "Jefe";
    ਸਥਿਰ ਅਚਲ uint8_t data1[] = "Hi There";
    ਸਥਿਰ ਅਚਲ uint8_t data2[] = "what do ya want for nothing?";
    ਸਥਿਰ ਅਚਲ uint8_t data4[] = "Test Using Larger Than Block-Size Key - Hash Key First";
    ਸਥਿਰ ਅਚਲ uint8_t data5[] = "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
    ਸਥਿਰ ਅਚਲ uint8_t data6[] = "This is a test using a larger than block-size key and a larger "
                            "than block-size data. The key needs to be hashed before being used"
                            " by the HMAC algorithm.";
    memset(key1, 0x0b, ਆਕਾਰ(key1));
    memset(key3, 0xaa, ਆਕਾਰ(key3));
    memset(data3, 0xdd, ਆਕਾਰ(data3));

    /* MD5, SHA-1 */
    ਲਈ (i = AV_HMAC_MD5; i <= AV_HMAC_SHA1; i++) {
        hmac = av_hmac_alloc(i);
        ਜੇ (!hmac)
            ਵਾਪਸ 1;
        // RFC 2202 test vectors
        test(hmac, key1, hmac->hashlen, data1, ਆਕਾਰ(data1));
        test(hmac, key2, ਆਕਾਰ(key2),  data2, ਆਕਾਰ(data2));
        test(hmac, key3, hmac->hashlen, data3, ਆਕਾਰ(data3));
        test(hmac, key3, 80,            data4, ਆਕਾਰ(data4));
        test(hmac, key3, 80,            data5, ਆਕਾਰ(data5));
        av_hmac_free(hmac);
    }

    /* SHA-2 */
    ਲਈ (i = AV_HMAC_SHA224; i <= AV_HMAC_SHA512; i++) {
        hmac = av_hmac_alloc(i);
        ਜੇ (!hmac)
            ਵਾਪਸ 1;
        // RFC 4231 test vectors
        test(hmac, key1, ਆਕਾਰ(key1), data1, ਆਕਾਰ(data1));
        test(hmac, key2, ਆਕਾਰ(key2), data2, ਆਕਾਰ(data2));
        test(hmac, key3, 20,           data3, ਆਕਾਰ(data3));
        test(hmac, key3, ਆਕਾਰ(key3), data4, ਆਕਾਰ(data4));
        test(hmac, key3, ਆਕਾਰ(key3), data6, ਆਕਾਰ(data6));
        av_hmac_free(hmac);
    }

    ਵਾਪਸ 0;
}

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

#അന്തര്ഭാവ "libavutil/hmac.c"

#അന്തര്ഭാവ <stdio.h>
#അന്തര്ഭാവ <string.h>

സ്ഥിതം ശൂന്യം test(AVHMAC *hmac, സ്ഥിരം uint8_t *താക്കോൽ, പൂർണ്ണസംഖ്യ keylen,
                 സ്ഥിരം uint8_t *data, പൂർണ്ണസംഖ്യ datalen)
{
    uint8_t buf[MAX_HASHLEN];
    പൂർണ്ണസംഖ്യ out, i;
    // Some of the test vectors are strings, where sizeof() includes the
    // trailing null byte - remove that.
    എങ്കിൽ (!താക്കോൽ[keylen - 1])
        keylen--;
    എങ്കിൽ (!data[datalen - 1])
        datalen--;
    out = av_hmac_calc(hmac, data, datalen, താക്കോൽ, keylen, buf, വലുപ്പം(buf));
    വേണ്ടി (i = 0; i < out; i++)
        printf("%02x", buf[i]);
    printf("\n");
}

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    uint8_t key1[20], key3[131], data3[50];
    AVHMAC *hmac;
    എണ്ണൽ AVHMACType i;
    സ്ഥിതം സ്ഥിരം uint8_t key2[]  = "Jefe";
    സ്ഥിതം സ്ഥിരം uint8_t data1[] = "Hi There";
    സ്ഥിതം സ്ഥിരം uint8_t data2[] = "what do ya want for nothing?";
    സ്ഥിതം സ്ഥിരം uint8_t data4[] = "Test Using Larger Than Block-Size Key - Hash Key First";
    സ്ഥിതം സ്ഥിരം uint8_t data5[] = "Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data";
    സ്ഥിതം സ്ഥിരം uint8_t data6[] = "This is a test using a larger than block-size key and a larger "
                            "than block-size data. The key needs to be hashed before being used"
                            " by the HMAC algorithm.";
    memset(key1, 0x0b, വലുപ്പം(key1));
    memset(key3, 0xaa, വലുപ്പം(key3));
    memset(data3, 0xdd, വലുപ്പം(data3));

    /* MD5, SHA-1 */
    വേണ്ടി (i = AV_HMAC_MD5; i <= AV_HMAC_SHA1; i++) {
        hmac = av_hmac_alloc(i);
        എങ്കിൽ (!hmac)
            തിരികെ 1;
        // RFC 2202 test vectors
        test(hmac, key1, hmac->hashlen, data1, വലുപ്പം(data1));
        test(hmac, key2, വലുപ്പം(key2),  data2, വലുപ്പം(data2));
        test(hmac, key3, hmac->hashlen, data3, വലുപ്പം(data3));
        test(hmac, key3, 80,            data4, വലുപ്പം(data4));
        test(hmac, key3, 80,            data5, വലുപ്പം(data5));
        av_hmac_free(hmac);
    }

    /* SHA-2 */
    വേണ്ടി (i = AV_HMAC_SHA224; i <= AV_HMAC_SHA512; i++) {
        hmac = av_hmac_alloc(i);
        എങ്കിൽ (!hmac)
            തിരികെ 1;
        // RFC 4231 test vectors
        test(hmac, key1, വലുപ്പം(key1), data1, വലുപ്പം(data1));
        test(hmac, key2, വലുപ്പം(key2), data2, വലുപ്പം(data2));
        test(hmac, key3, 20,           data3, വലുപ്പം(data3));
        test(hmac, key3, വലുപ്പം(key3), data4, വലുപ്പം(data4));
        test(hmac, key3, വലുപ്പം(key3), data6, വലുപ്പം(data6));
        av_hmac_free(hmac);
    }

    തിരികെ 0;
}

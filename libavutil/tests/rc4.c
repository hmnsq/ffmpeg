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

#समावेश <stdint.h>
#समावेश <stdio.h>
#समावेश <string.h>

#समावेश "libavutil/attributes_internal.h"
#समावेश "libavutil/macros.h"
#समावेश "libavutil/mem.h"
#समावेश "libavutil/rc4.h"

/* RFC 6229 test vectors */
अटल स्थिर काष्ठा {
    पूर्णांक कुंजी_bits;
    स्थिर uint8_t कुंजी[16];
    स्थिर uint8_t keystream[8]; /* first 8 bytes of output */
} test_vectors[] = {
    /* 40-bit key: 0x0102030405 */
    { 40,
      { 0x01, 0x02, 0x03, 0x04, 0x05 },
      { 0xb2, 0x39, 0x63, 0x05, 0xf0, 0x3d, 0xc0, 0x27 } },
    /* 56-bit key: 0x01020304050607 */
    { 56,
      { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 },
      { 0x29, 0x3f, 0x02, 0xd4, 0x7f, 0x37, 0xc9, 0xb6 } },
    /* 64-bit key: 0x0102030405060708 */
    { 64,
      { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },
      { 0x97, 0xab, 0x8a, 0x1b, 0xf0, 0xaf, 0xb9, 0x61 } },
    /* 128-bit key: 0x0102030405060708090a0b0c0d0e0f10 */
    { 128,
      { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
        0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10 },
      { 0x9a, 0xc7, 0xcc, 0x9a, 0x60, 0x9d, 0x1e, 0xf7 } },
};

पूर्णांक मुख्य(व्योम)
{
    AVRC4 *ctx;
    uint8_t buf[8], encrypted[8], decrypted[8];

    ctx = av_rc4_alloc();
    अगर (!ctx)
        वापस 1;

    /* test keystream output (src=NULL) against known vectors */
    क्रम (पूर्णांक i = 0; i < FF_ARRAY_ELEMS(test_vectors); i++) {
        av_rc4_init(ctx, test_vectors[i].कुंजी, test_vectors[i].कुंजी_bits, 0);
        av_rc4_crypt(ctx, buf, शून्य, माप(buf), शून्य, 0);
        अगर (स_भेद(buf, test_vectors[i].keystream, माप(buf))) {
            म_लिखो("Keystream test %d (%d-bit key) failed.\n",
                   i, test_vectors[i].कुंजी_bits);
            av_free(ctx);
            वापस 1;
        }
    }

    /* test encrypt then decrypt round-trip */
    {
        स्थिर uint8_t कुंजी[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
        अटल attribute_nonstring स्थिर uint8_t plaintext[8] = "TestData";

        av_rc4_init(ctx, कुंजी, 40, 0);
        av_rc4_crypt(ctx, encrypted, plaintext, माप(plaintext), शून्य, 0);

        /* RC4 is symmetric: re-init and encrypt again to decrypt */
        av_rc4_init(ctx, कुंजी, 40, 0);
        av_rc4_crypt(ctx, decrypted, encrypted, माप(encrypted), शून्य, 0);

        अगर (स_भेद(decrypted, plaintext, माप(plaintext))) {
            म_लिखो("Round-trip test failed.\n");
            av_free(ctx);
            वापस 1;
        }
    }

    /* test inplace encrypt/decrypt */
    {
        स्थिर uint8_t कुंजी[] = { 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };
        अटल attribute_nonstring स्थिर uint8_t plaintext[8] = "InPlace!";

        स_नकल(buf, plaintext, माप(plaintext));
        av_rc4_init(ctx, कुंजी, 64, 0);
        av_rc4_crypt(ctx, buf, buf, माप(buf), शून्य, 0);

        av_rc4_init(ctx, कुंजी, 64, 0);
        av_rc4_crypt(ctx, buf, buf, माप(buf), शून्य, 0);

        अगर (स_भेद(buf, plaintext, माप(plaintext))) {
            म_लिखो("Inplace round-trip test failed.\n");
            av_free(ctx);
            वापस 1;
        }
    }

    /* test invalid key_bits (not multiple of 8) */
    अगर (av_rc4_init(ctx, (स्थिर uint8_t[]){ 0x01 }, 7, 0) >= 0) {
        म_लिखो("Invalid key_bits should return error.\n");
        av_free(ctx);
        वापस 1;
    }

    म_लिखो("Test encryption/decryption success.\n");
    av_free(ctx);

    वापस 0;
}

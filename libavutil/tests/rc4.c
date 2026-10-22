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

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/attributes_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/macros.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"
#ಅನ್ತರ್ಭಾವ "libavutil/rc4.h"

/* RFC 6229 test vectors */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ {
    ಪೂರ್ಣಾಂಕ ಕೀಲಿ_ಬಿಟ್ಟುಗಳು;
    ಸ್ಥಿರಾಂಕ uint8_t ಕೀಲಿ[16];
    ಸ್ಥಿರಾಂಕ uint8_t keystream[8]; /* first 8 bytes of output */
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

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVRC4 *ctx;
    uint8_t buf[8], encrypted[8], decrypted[8];

    ctx = av_rc4_alloc();
    ಆದರೆ (!ctx)
        ಹಿಂತಿರುಗಿ 1;

    /* test keystream output (src=NULL) against known vectors */
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < FF_ARRAY_ELEMS(test_vectors); i++) {
        av_rc4_init(ctx, test_vectors[i].ಕೀಲಿ, test_vectors[i].ಕೀಲಿ_ಬಿಟ್ಟುಗಳು, 0);
        av_rc4_crypt(ctx, buf, ಖಾಲಿ, ಗಾತ್ರ(buf), ಖಾಲಿ, 0);
        ಆದರೆ (memcmp(buf, test_vectors[i].keystream, ಗಾತ್ರ(buf))) {
            ಬರೆ("Keystream test %d (%d-bit key) failed.\n",
                   i, test_vectors[i].ಕೀಲಿ_ಬಿಟ್ಟುಗಳು);
            av_free(ctx);
            ಹಿಂತಿರುಗಿ 1;
        }
    }

    /* test encrypt then decrypt round-trip */
    {
        ಸ್ಥಿರಾಂಕ uint8_t ಕೀಲಿ[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };
        ಸ್ಥಿರ attribute_nonstring ಸ್ಥಿರಾಂಕ uint8_t plaintext[8] = "TestData";

        av_rc4_init(ctx, ಕೀಲಿ, 40, 0);
        av_rc4_crypt(ctx, encrypted, plaintext, ಗಾತ್ರ(plaintext), ಖಾಲಿ, 0);

        /* RC4 is symmetric: re-init and encrypt again to decrypt */
        av_rc4_init(ctx, ಕೀಲಿ, 40, 0);
        av_rc4_crypt(ctx, decrypted, encrypted, ಗಾತ್ರ(encrypted), ಖಾಲಿ, 0);

        ಆದರೆ (memcmp(decrypted, plaintext, ಗಾತ್ರ(plaintext))) {
            ಬರೆ("Round-trip test failed.\n");
            av_free(ctx);
            ಹಿಂತಿರುಗಿ 1;
        }
    }

    /* test inplace encrypt/decrypt */
    {
        ಸ್ಥಿರಾಂಕ uint8_t ಕೀಲಿ[] = { 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };
        ಸ್ಥಿರ attribute_nonstring ಸ್ಥಿರಾಂಕ uint8_t plaintext[8] = "InPlace!";

        ಸ್ಮರಣೆ_ನಕಲು(buf, plaintext, ಗಾತ್ರ(plaintext));
        av_rc4_init(ctx, ಕೀಲಿ, 64, 0);
        av_rc4_crypt(ctx, buf, buf, ಗಾತ್ರ(buf), ಖಾಲಿ, 0);

        av_rc4_init(ctx, ಕೀಲಿ, 64, 0);
        av_rc4_crypt(ctx, buf, buf, ಗಾತ್ರ(buf), ಖಾಲಿ, 0);

        ಆದರೆ (memcmp(buf, plaintext, ಗಾತ್ರ(plaintext))) {
            ಬರೆ("Inplace round-trip test failed.\n");
            av_free(ctx);
            ಹಿಂತಿರುಗಿ 1;
        }
    }

    /* test invalid key_bits (not multiple of 8) */
    ಆದರೆ (av_rc4_init(ctx, (ಸ್ಥಿರಾಂಕ uint8_t[]){ 0x01 }, 7, 0) >= 0) {
        ಬರೆ("Invalid key_bits should return error.\n");
        av_free(ctx);
        ಹಿಂತಿರುಗಿ 1;
    }

    ಬರೆ("Test encryption/decryption success.\n");
    av_free(ctx);

    ಹಿಂತಿರುಗಿ 0;
}

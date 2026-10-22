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

#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "libavutil/intreadwrite.h"
#अन्तर्भाव "libavutil/mem.h"
#अन्तर्भाव "libavutil/xtea.h"

#परिभाषय XTEA_अङ्कः_TESTS 6

स्थिर ध्रुव uint8_t xtea_test_कुञ्चिका[XTEA_अङ्कः_TESTS][16] = {
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
    { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
      0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

स्थिर ध्रुव uint8_t xtea_test_pt[XTEA_अङ्कः_TESTS][8] = {
    { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 },
    { 0x5a, 0x5b, 0x6e, 0x27, 0x89, 0x48, 0xd7, 0x7f },
    { 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48 },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 },
    { 0x70, 0xe1, 0x22, 0x5d, 0x6e, 0x4e, 0x76, 0x55 }
};

स्थिर ध्रुव uint8_t xtea_test_ct[XTEA_अङ्कः_TESTS][8] = {
    { 0x49, 0x7d, 0xf3, 0xd0, 0x72, 0x61, 0x2c, 0xb5 },
    { 0xe7, 0x8f, 0x2d, 0x13, 0x74, 0x43, 0x41, 0xd8 },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 },
    { 0xa0, 0x39, 0x05, 0x89, 0xf8, 0xb8, 0xef, 0xa5 },
    { 0xed, 0x23, 0x37, 0x5a, 0x82, 0x1a, 0x8c, 0x2d },
    { 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41 }
};

स्थिर शून्य test_xtea(AVXTEA *ctx, uint8_t *dst, ध्रुव uint8_t *src,
                      ध्रुव uint8_t *ref, पूर्णाङ्क len, uint8_t *iv, पूर्णाङ्क dir,
                      ध्रुव वर्ण *test,
                      शून्य (*crypt)(AVXTEA *, uint8_t *, ध्रुव uint8_t *, पूर्णाङ्क, uint8_t *, पूर्णाङ्क))
{
    crypt(ctx, dst, src, len, iv, dir);
    यदि (memcmp(dst, ref, 8*len)) {
        पूर्णाङ्क i;
        प्रारूप_लिख("%s failed\ngot      ", test);
        प्रति (i = 0; i < 8*len; i++)
            प्रारूप_लिख("%02x ", dst[i]);
        प्रारूप_लिख("\nexpected ");
        प्रति (i = 0; i < 8*len; i++)
            प्रारूप_लिख("%02x ", ref[i]);
        प्रारूप_लिख("\n");
        निर्गच्छ(1);
    }
}

पूर्णाङ्क मुख्यम्(शून्य)
{
    uint8_t buf[16], iv[8];
    पूर्णाङ्क i, j;
    स्थिर ध्रुव uint8_t src[32] = "HelloWorldHelloWorldHelloWorld";
    uint8_t ct[32];
    uint8_t pl[32];
    AVXTEA *ctx = av_xtea_alloc();
    यदि (!ctx)
        प्रत्यागम 1;

    प्रति (i = 0; i < XTEA_अङ्कः_TESTS; i++) {
        av_xtea_init(ctx, xtea_test_कुञ्चिका[i]);

        test_xtea(ctx, buf, xtea_test_pt[i], xtea_test_ct[i], 1, रिक्त, 0, "encryption", av_xtea_crypt);
        test_xtea(ctx, buf, xtea_test_ct[i], xtea_test_pt[i], 1, रिक्त, 1, "decryption", av_xtea_crypt);

        प्रति (j = 0; j < 4; j++)
            AV_WL32(&buf[4*j], AV_RB32(&xtea_test_कुञ्चिका[i][4*j]));
        av_xtea_le_init(ctx, buf);
        प्रति (j = 0; j < 2; j++) {
            AV_WL32(&ct[4*j], AV_RB32(&xtea_test_ct[i][4*j]));
            AV_WL32(&pl[4*j], AV_RB32(&xtea_test_pt[i][4*j]));
        }
        test_xtea(ctx, buf, pl, ct, 1, रिक्त, 0, "encryption", av_xtea_le_crypt);
        test_xtea(ctx, buf, ct, pl, 1, रिक्त, 1, "decryption", av_xtea_le_crypt);

        /* encrypt */
        स्मृतिं_प्रतिलिख(iv, "HALLO123", 8);
        av_xtea_crypt(ctx, ct, src, 4, iv, 0);

        /* decrypt into pl */
        स्मृतिं_प्रतिलिख(iv, "HALLO123", 8);
        test_xtea(ctx, pl, ct, src, 4, iv, 1, "CBC decryption", av_xtea_crypt);

        स्मृतिं_प्रतिलिख(iv, "HALLO123", 8);
        test_xtea(ctx, ct, ct, src, 4, iv, 1, "CBC inplace decryption", av_xtea_crypt);
    }

    प्रारूप_लिख("Test encryption/decryption success.\n");
    av_free(ctx);

    प्रत्यागम 0;
}

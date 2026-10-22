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

#অন্তর্ভাব "libavutil/mem_internal.h"
#অন্তর্ভাব "libavutil/timer.h"

#অন্তর্ভাব "libavutil/des.c"

#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdio.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/time.h"

স্থির uint64_t rand64(শূন্য)
{
    uint64_t r = rand();
    r = (r << 32) | rand();
    ফেরত r;
}

স্থির ধ্রুবক uint8_t test_চাবি[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
স্থির ধ্রুবক DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
স্থির ধ্রুবক DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
স্থির DECLARE_ALIGNED(8, uint8_t, tmp)[8];
স্থির DECLARE_ALIGNED(8, uint8_t, large_বাফার)[10002][8];
স্থির ধ্রুবক uint8_t cbc_চাবি[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

স্থির পূর্ণসংখ্যা run_test(পূর্ণসংখ্যা cbc, পূর্ণসংখ্যা decrypt)
{
    AVDES d;
    পূর্ণসংখ্যা delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_বাফার[0], 0x4e6f772069732074ULL);
    AV_WB64(large_বাফার[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_চাবি, 192, decrypt);
    av_des_crypt(&d, large_বাফার[delay], large_বাফার[0], 10000, cbc ? tmp : ফাঁকা, decrypt);
    res = AV_RB64(large_বাফার[9999 + delay]);
    যদি (cbc) {
        যদি (decrypt)
            ফেরত res == 0xc5cecf63ecec514cULL;
        অন্যথা
            ফেরত res == 0xcb191f85d1ed8439ULL;
    } অন্যথা {
        যদি (decrypt)
            ফেরত res == 0x8325397644091a0aULL;
        অন্যথা
            ফেরত res == 0xdd17e8b8b437d232ULL;
    }
}

সংঘ word_byte {
    uint64_t word;
    uint8_t byte[8];
};

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    AVDES d;
    পূর্ণসংখ্যা i;
    সংঘ word_byte চাবি[3], তথ্য, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    চাবি[0].word = AV_RB64(test_চাবি);
    তথ্য.word   = AV_RB64(plain);
    gen_roundkeys(roundkeys, চাবি[0].word);
    যদি (des_encdec(তথ্য.word, roundkeys, 0) != AV_RB64(crypt_ref)) {
        printf("Test 1 failed\n");
        ফেরত 1;
    }
    av_des_init(&d, test_চাবি, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, ফাঁকা, 0);
    যদি (memcmp(tmp, crypt_ref, আকার(crypt_ref))) {
        printf("Public API decryption failed\n");
        ফেরত 1;
    }
    যদি (!run_test(0, 0) || !run_test(0, 1) || !run_test(1, 0) || !run_test(1, 1)) {
        printf("Partial Monte-Carlo test failed\n");
        ফেরত 1;
    }
    জন্য (i = 0; i < 1000; i++) {
        চাবি[0].word = rand64();
        চাবি[1].word = rand64();
        চাবি[2].word = rand64();
        তথ্য.word   = rand64();
        av_des_init(&d, চাবি[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, তথ্য.byte, 1, ফাঁকা, 0);
        av_des_init(&d, চাবি[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, ফাঁকা, 1);
        যদি (ct.word != তথ্য.word) {
            printf("Test 2 failed\n");
            ফেরত 1;
        }
    }
#ifdef GENTABLES
    printf("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    জন্য (i = 0; i < 8; i++) {
        পূর্ণসংখ্যা j;
        printf("    {");
        জন্য (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, আকার(P_shuffle));
            printf((j & 7) == 0 ? "\n    " : " ");
            printf("0x%08X,", v);
        }
        printf("\n    },\n");
    }
    printf("};\n");
#endif
    ফেরত 0;
}

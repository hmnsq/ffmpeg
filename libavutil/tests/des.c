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

#شامل "libavutil/mem_internal.h"
#شامل "libavutil/timer.h"

#شامل "libavutil/des.c"

#شامل <stdint.h>
#شامل <stdio.h>
#شامل <stdlib.h>
#شامل <string.h>

#شامل "libavutil/time.h"

ایستا uint64_t rand64(تهی)
{
    uint64_t r = rand();
    r = (r << 32) | rand();
    بازگشت r;
}

ایستا ثابت uint8_t test_کلید[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
ایستا ثابت DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
ایستا ثابت DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
ایستا DECLARE_ALIGNED(8, uint8_t, tmp)[8];
ایستا DECLARE_ALIGNED(8, uint8_t, large_buffer)[10002][8];
ایستا ثابت uint8_t cbc_کلید[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

ایستا صحیح run_test(صحیح cbc, صحیح decrypt)
{
    AVDES d;
    صحیح delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_buffer[0], 0x4e6f772069732074ULL);
    AV_WB64(large_buffer[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_کلید, 192, decrypt);
    av_des_crypt(&d, large_buffer[delay], large_buffer[0], 10000, cbc ? tmp : پوچ, decrypt);
    res = AV_RB64(large_buffer[9999 + delay]);
    اگر (cbc) {
        اگر (decrypt)
            بازگشت res == 0xc5cecf63ecec514cULL;
        وگرنه
            بازگشت res == 0xcb191f85d1ed8439ULL;
    } وگرنه {
        اگر (decrypt)
            بازگشت res == 0x8325397644091a0aULL;
        وگرنه
            بازگشت res == 0xdd17e8b8b437d232ULL;
    }
}

اجتماع word_byte {
    uint64_t word;
    uint8_t byte[8];
};

صحیح اصلی(تهی)
{
    AVDES d;
    صحیح i;
    اجتماع word_byte کلید[3], data, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    کلید[0].word = AV_RB64(test_کلید);
    data.word   = AV_RB64(plain);
    gen_roundkeys(roundkeys, کلید[0].word);
    اگر (des_encdec(data.word, roundkeys, 0) != AV_RB64(crypt_ref)) {
        printf("Test 1 failed\n");
        بازگشت 1;
    }
    av_des_init(&d, test_کلید, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, پوچ, 0);
    اگر (memcmp(tmp, crypt_ref, اندازه(crypt_ref))) {
        printf("Public API decryption failed\n");
        بازگشت 1;
    }
    اگر (!run_test(0, 0) || !run_test(0, 1) || !run_test(1, 0) || !run_test(1, 1)) {
        printf("Partial Monte-Carlo test failed\n");
        بازگشت 1;
    }
    برای (i = 0; i < 1000; i++) {
        کلید[0].word = rand64();
        کلید[1].word = rand64();
        کلید[2].word = rand64();
        data.word   = rand64();
        av_des_init(&d, کلید[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, data.byte, 1, پوچ, 0);
        av_des_init(&d, کلید[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, پوچ, 1);
        اگر (ct.word != data.word) {
            printf("Test 2 failed\n");
            بازگشت 1;
        }
    }
#ifdef GENTABLES
    printf("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    برای (i = 0; i < 8; i++) {
        صحیح j;
        printf("    {");
        برای (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, اندازه(P_shuffle));
            printf((j & 7) == 0 ? "\n    " : " ");
            printf("0x%08X,", v);
        }
        printf("\n    },\n");
    }
    printf("};\n");
#endif
    بازگشت 0;
}

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

#அந்தர்பாவ "libavutil/mem_internal.h"
#அந்தர்பாவ "libavutil/timer.h"

#அந்தர்பாவ "libavutil/des.c"

#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdio.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "libavutil/time.h"

நிலையான uint64_t rand64(வெறுமை)
{
    uint64_t r = rand();
    r = (r << 32) | rand();
    திரும்பு r;
}

நிலையான மாறிலி uint8_t test_சாவி[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
நிலையான மாறிலி DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
நிலையான மாறிலி DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
நிலையான DECLARE_ALIGNED(8, uint8_t, tmp)[8];
நிலையான DECLARE_ALIGNED(8, uint8_t, large_buffer)[10002][8];
நிலையான மாறிலி uint8_t cbc_சாவி[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

நிலையான முழு run_test(முழு cbc, முழு decrypt)
{
    AVDES d;
    முழு delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_buffer[0], 0x4e6f772069732074ULL);
    AV_WB64(large_buffer[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_சாவி, 192, decrypt);
    av_des_crypt(&d, large_buffer[delay], large_buffer[0], 10000, cbc ? tmp : வெற்று, decrypt);
    res = AV_RB64(large_buffer[9999 + delay]);
    எனில் (cbc) {
        எனில் (decrypt)
            திரும்பு res == 0xc5cecf63ecec514cULL;
        இல்லையெனில்
            திரும்பு res == 0xcb191f85d1ed8439ULL;
    } இல்லையெனில் {
        எனில் (decrypt)
            திரும்பு res == 0x8325397644091a0aULL;
        இல்லையெனில்
            திரும்பு res == 0xdd17e8b8b437d232ULL;
    }
}

ஒன்றிப்பு word_byte {
    uint64_t word;
    uint8_t byte[8];
};

முழு முதன்மை(வெறுமை)
{
    AVDES d;
    முழு i;
    ஒன்றிப்பு word_byte சாவி[3], data, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    சாவி[0].word = AV_RB64(test_சாவி);
    data.word   = AV_RB64(plain);
    gen_roundkeys(roundkeys, சாவி[0].word);
    எனில் (des_encdec(data.word, roundkeys, 0) != AV_RB64(crypt_ref)) {
        printf("Test 1 failed\n");
        திரும்பு 1;
    }
    av_des_init(&d, test_சாவி, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, வெற்று, 0);
    எனில் (memcmp(tmp, crypt_ref, அளவு(crypt_ref))) {
        printf("Public API decryption failed\n");
        திரும்பு 1;
    }
    எனில் (!run_test(0, 0) || !run_test(0, 1) || !run_test(1, 0) || !run_test(1, 1)) {
        printf("Partial Monte-Carlo test failed\n");
        திரும்பு 1;
    }
    க்கு (i = 0; i < 1000; i++) {
        சாவி[0].word = rand64();
        சாவி[1].word = rand64();
        சாவி[2].word = rand64();
        data.word   = rand64();
        av_des_init(&d, சாவி[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, data.byte, 1, வெற்று, 0);
        av_des_init(&d, சாவி[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, வெற்று, 1);
        எனில் (ct.word != data.word) {
            printf("Test 2 failed\n");
            திரும்பு 1;
        }
    }
#ifdef GENTABLES
    printf("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    க்கு (i = 0; i < 8; i++) {
        முழு j;
        printf("    {");
        க்கு (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, அளவு(P_shuffle));
            printf((j & 7) == 0 ? "\n    " : " ");
            printf("0x%08X,", v);
        }
        printf("\n    },\n");
    }
    printf("};\n");
#endif
    திரும்பு 0;
}

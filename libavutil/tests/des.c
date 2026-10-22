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

#అన్తర్భావ "libavutil/mem_internal.h"
#అన్తర్భావ "libavutil/timer.h"

#అన్తర్భావ "libavutil/des.c"

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "libavutil/time.h"

స్థిర uint64_t rand64(శూన్య)
{
    uint64_t r = rand();
    r = (r << 32) | rand();
    తిరిగి r;
}

స్థిర స్థిరరాశి uint8_t test_కీలకం[] = { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 };
స్థిర స్థిరరాశి DECLARE_ALIGNED(8, uint8_t, plain)[] = { 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10 };
స్థిర స్థిరరాశి DECLARE_ALIGNED(8, uint8_t, crypt_ref)[] = { 0x4a, 0xb6, 0x5b, 0x3d, 0x4b, 0x06, 0x15, 0x18 };
స్థిర DECLARE_ALIGNED(8, uint8_t, tmp)[8];
స్థిర DECLARE_ALIGNED(8, uint8_t, large_బఫరు)[10002][8];
స్థిర స్థిరరాశి uint8_t cbc_కీలకం[] = {
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
    0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01,
    0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0x01, 0x23
};

స్థిర పూర్ణాంకం నిరంతరం_test(పూర్ణాంకం cbc, పూర్ణాంకం decrypt)
{
    AVDES d;
    పూర్ణాంకం delay = cbc && !decrypt ? 2 : 1;
    uint64_t res;
    AV_WB64(large_బఫరు[0], 0x4e6f772069732074ULL);
    AV_WB64(large_బఫరు[1], 0x1234567890abcdefULL);
    AV_WB64(tmp,             0x1234567890abcdefULL);
    av_des_init(&d, cbc_కీలకం, 192, decrypt);
    av_des_crypt(&d, large_బఫరు[delay], large_బఫరు[0], 10000, cbc ? tmp : ఖాళీ, decrypt);
    res = AV_RB64(large_బఫరు[9999 + delay]);
    ఒకవేళ (cbc) {
        ఒకవేళ (decrypt)
            తిరిగి res == 0xc5cecf63ecec514cULL;
        లేకపోతే
            తిరిగి res == 0xcb191f85d1ed8439ULL;
    } లేకపోతే {
        ఒకవేళ (decrypt)
            తిరిగి res == 0x8325397644091a0aULL;
        లేకపోతే
            తిరిగి res == 0xdd17e8b8b437d232ULL;
    }
}

సంఘం మాట_byte {
    uint64_t మాట_4;
    uint8_t byte[8];
};

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVDES d;
    పూర్ణాంకం i;
    సంఘం మాట_byte కీలకం[3], దత్తాంశం, ct;
    uint64_t roundkeys[16];
    srand(av_gettime());
    కీలకం[0].మాట_4 = AV_RB64(test_కీలకం);
    దత్తాంశం.మాట_4   = AV_RB64(plain);
    gen_roundkeys(roundkeys, కీలకం[0].మాట_4);
    ఒకవేళ (des_encdec(దత్తాంశం.మాట_4, roundkeys, 0) != AV_RB64(crypt_ref)) {
        రాయి("Test 1 failed\n");
        తిరిగి 1;
    }
    av_des_init(&d, test_కీలకం, 64, 0);
    av_des_crypt(&d, tmp, plain, 1, ఖాళీ, 0);
    ఒకవేళ (memcmp(tmp, crypt_ref, పరిమాణం(crypt_ref))) {
        రాయి("Public API decryption failed\n");
        తిరిగి 1;
    }
    ఒకవేళ (!నిరంతరం_test(0, 0) || !నిరంతరం_test(0, 1) || !నిరంతరం_test(1, 0) || !నిరంతరం_test(1, 1)) {
        రాయి("Partial Monte-Carlo test failed\n");
        తిరిగి 1;
    }
    కొరకు (i = 0; i < 1000; i++) {
        కీలకం[0].మాట_4 = rand64();
        కీలకం[1].మాట_4 = rand64();
        కీలకం[2].మాట_4 = rand64();
        దత్తాంశం.మాట_4   = rand64();
        av_des_init(&d, కీలకం[0].byte, 192, 0);
        av_des_crypt(&d, ct.byte, దత్తాంశం.byte, 1, ఖాళీ, 0);
        av_des_init(&d, కీలకం[0].byte, 192, 1);
        av_des_crypt(&d, ct.byte, ct.byte, 1, ఖాళీ, 1);
        ఒకవేళ (ct.మాట_4 != దత్తాంశం.మాట_4) {
            రాయి("Test 2 failed\n");
            తిరిగి 1;
        }
    }
#నిర్వచితమైతే GENTABLES
    రాయి("static const uint32_t S_boxes_P_shuffle[8][64] = {\n");
    కొరకు (i = 0; i < 8; i++) {
        పూర్ణాంకం j;
        రాయి("    {");
        కొరకు (j = 0; j < 64; j++) {
            uint32_t v = S_boxes[i][j >> 1];
            v   = j & 1 ? v >> 4 : v & 0xf;
            v <<= 28 - 4 * i;
            v   = shuffle(v, P_shuffle, పరిమాణం(P_shuffle));
            రాయి((j & 7) == 0 ? "\n    " : " ");
            రాయి("0x%08X,", v);
        }
        రాయి("\n    },\n");
    }
    రాయి("};\n");
#అయితే_ముగింపు
    తిరిగి 0;
}

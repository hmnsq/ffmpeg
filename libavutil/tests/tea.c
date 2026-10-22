/*
 * A 32-bit implementation of the TEA algorithm
 * Copyright (c) 2015 Vesselin Bontchev
 *
 * Loosely based on the implementation of David Wheeler and Roger Needham,
 * https://en.wikipedia.org/wiki/Tiny_Encryption_Algorithm#Reference_code
 *
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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/common.h"
#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/tea.h"

#నిర్వచించు TEA_అంకె_TESTS 4

// https://github.com/logandrews/TeaCrypt/blob/master/tea/tea_test.go
స్థిర స్థిరరాశి uint8_t tea_test_కీలకం[TEA_అంకె_TESTS][16] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    },
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    },
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
    },
    { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
      0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
    }
};

స్థిర స్థిరరాశి uint8_t tea_test_pt[TEA_అంకె_TESTS][8] = {
    { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },
    { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 },
    { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF }
};

స్థిర స్థిరరాశి uint8_t tea_test_ct[TEA_అంకె_TESTS][8] = {
    { 0x41, 0xEA, 0x3A, 0x0A, 0x94, 0xBA, 0xA9, 0x40 },
    { 0x6A, 0x2F, 0x9C, 0xF3, 0xFC, 0xCF, 0x3C, 0x55 },
    { 0xDE, 0xB1, 0xC0, 0xA2, 0x7E, 0x74, 0x5D, 0xB3 },
    { 0x12, 0x6C, 0x6B, 0x92, 0xC0, 0x65, 0x3A, 0x3E }
};

స్థిర శూన్య test_tea(నిర్మాణం AVTEA *ctx, uint8_t *dst, స్థిరరాశి uint8_t *src,
                     స్థిరరాశి uint8_t *ref, పూర్ణాంకం len, uint8_t *iv, పూర్ణాంకం dir,
                     స్థిరరాశి అక్షరం *test)
{
    av_tea_crypt(ctx, dst, src, len, iv, dir);
    ఒకవేళ (memcmp(dst, ref, 8*len)) {
        పూర్ణాంకం i;
        రాయి("%s failed\ngot      ", test);
        కొరకు (i = 0; i < 8*len; i++)
            రాయి("%02x ", dst[i]);
        రాయి("\nexpected ");
        కొరకు (i = 0; i < 8*len; i++)
            రాయి("%02x ", ref[i]);
        రాయి("\n");
        నిష్క్రమించు(1);
    }
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    నిర్మాణం AVTEA *ctx;
    uint8_t buf[8], iv[8];
    పూర్ణాంకం i;
    స్థిర స్థిరరాశి uint8_t src[32] = "HelloWorldHelloWorldHelloWorld";
    uint8_t ct[32];
    uint8_t pl[32];

    ctx = av_tea_alloc();
    ఒకవేళ (!ctx)
        తిరిగి 1;

    కొరకు (i = 0; i < TEA_అంకె_TESTS; i++) {
        av_tea_init(ctx, tea_test_కీలకం[i], 64);

        test_tea(ctx, buf, tea_test_pt[i], tea_test_ct[i], 1, ఖాళీ, 0, "encryption");
        test_tea(ctx, buf, tea_test_ct[i], tea_test_pt[i], 1, ఖాళీ, 1, "decryption");

        /* encrypt */
        జ్ఞాపకం_నకలు(iv, "HALLO123", 8);
        av_tea_crypt(ctx, ct, src, 4, iv, 0);

        /* decrypt into pl */
        జ్ఞాపకం_నకలు(iv, "HALLO123", 8);
        test_tea(ctx, pl, ct, src, 4, iv, 1, "CBC decryption");

        జ్ఞాపకం_నకలు(iv, "HALLO123", 8);
        test_tea(ctx, ct, ct, src, 4, iv, 1, "CBC inplace decryption");
    }

    రాయి("Test encryption/decryption success.\n");
    av_free(ctx);

    తిరిగి 0;
}

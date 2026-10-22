/*
 * An implementation of the CAST128 algorithm as mentioned in RFC2144
 * Copyright (c) 2014 Supraja Meedinti
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

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "libavutil/cast5.h"
#অন্তর্ভাব "libavutil/log.h"
#অন্তর্ভাব "libavutil/mem.h"

পূর্ণসংখ্যা প্রধান(পূর্ণসংখ্যা argc, অক্ষর** argv)
{

    স্থির ধ্রুবক uint8_t চাবি_2[3][16] = {
        {0x01, 0x23, 0x45, 0x67, 0x12, 0x34, 0x56, 0x78, 0x23, 0x45, 0x67, 0x89, 0x34, 0x56, 0x78, 0x9a},
        {0x01, 0x23, 0x45, 0x67, 0x12, 0x34, 0x56, 0x78, 0x23, 0x45},
        {0x01, 0x23, 0x45, 0x67, 0x12}
    };
    স্থির ধ্রুবক uint8_t rpt[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    স্থির ধ্রুবক uint8_t rct[3][8] = {
        {0x23, 0x8b, 0x4f, 0xe5, 0x84, 0x7e, 0x44, 0xb2},
        {0xeb, 0x6a, 0x71, 0x1a, 0x2c, 0x02, 0x27, 0x1b},
        {0x7a, 0xc8, 0x16, 0xd1, 0x6e, 0x9b, 0x30, 0x2e}
    };
    স্থির ধ্রুবক uint8_t rct2[2][16] = {
        {0xee, 0xa9, 0xd0, 0xa2, 0x49, 0xfd, 0x3b, 0xa6, 0xb3, 0x43, 0x6f, 0xb8, 0x9d, 0x6d, 0xca, 0x92},
        {0xb2, 0xc9, 0x5e, 0xb0, 0x0c, 0x31, 0xad, 0x71, 0x80, 0xac, 0x05, 0xb8, 0xe8, 0x3d, 0x69, 0x6e}
    };
    স্থির ধ্রুবক uint8_t iv[8] = {0xee, 0xa9, 0xd0, 0xa2, 0x49, 0xfd, 0x3b, 0xa6};
    স্থির uint8_t rpt2[2][16];
    পূর্ণসংখ্যা i, j, err = 0;
    স্থির ধ্রুবক পূর্ণসংখ্যা চাবি_bits[3] = {128, 80, 40};
    uint8_t অস্থায়ী[8];
    কাঠামো AVCAST5 *cs;
    cs = av_cast5_alloc();
    যদি (!cs)
        ফেরত 1;
    জন্য (j = 0; j < 3; j++){

        av_cast5_init(cs, চাবি_2[j], চাবি_bits[j]);
        av_cast5_crypt(cs, অস্থায়ী, rpt, 1, 0);
        জন্য (i = 0;i < 8; i++){
            যদি (rct[j][i] != অস্থায়ী[i]){
                av_log(ফাঁকা, AV_LOG_ERROR, "%d %02x %02x\n", i, rct[j][i], অস্থায়ী[i]);
                err = 1;
            }
        }

        av_cast5_crypt(cs, অস্থায়ী, rct[j], 1, 1);
        জন্য (i =0; i < 8; i++) {
            যদি (rpt[i] != অস্থায়ী[i]) {
                av_log(ফাঁকা, AV_LOG_ERROR, "%d %02x %02x\n", i, rpt[i], অস্থায়ী[i]);
                err = 1;
            }
        }
    }
    memcpy(rpt2[0], চাবি_2[0], 16);
    memcpy(rpt2[1], চাবি_2[0], 16);
    জন্য (i = 0; i < 1000000; i++){
        av_cast5_init(cs, rpt2[1], 128);
        av_cast5_crypt(cs, rpt2[0], rpt2[0], 2, 0);
        av_cast5_init(cs, rpt2[0], 128);
        av_cast5_crypt(cs, rpt2[1], rpt2[1], 2, 0);
    }
    জন্য (j = 0; j < 2; j++) {
        জন্য (i = 0; i < 16; i++) {
            যদি (rct2[j][i] != rpt2[j][i]) {
                av_log(ফাঁকা, AV_LOG_ERROR, "%d %02x %02x\n", i, rct2[j][i], rpt2[j][i]);
                err = 1;
            }
        }
    }
    জন্য (j = 0; j < 3; j++) {

        av_cast5_init(cs, চাবি_2[j], চাবি_bits[j]);
        memcpy(অস্থায়ী, iv, 8);
        av_cast5_crypt2(cs, rpt2[0], rct2[0], 2, অস্থায়ী, 0);
        memcpy(অস্থায়ী, iv, 8);
        av_cast5_crypt2(cs, rpt2[0], rpt2[0], 2, অস্থায়ী, 1);
        জন্য (i = 0; i < 16; i++) {
            যদি (rct2[0][i] != rpt2[0][i]) {
                av_log(ফাঁকা, AV_LOG_ERROR, "%d %02x %02x\n", i, rct2[0][i], rpt2[0][i]);
                err = 1;
            }
        }
    }
    av_free(cs);
    ফেরত err;
}

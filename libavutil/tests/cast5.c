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

#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/cast5.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/log.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/mem.h"

ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର** argv)
{

    ସ୍ଥିର ଅଚଳ uint8_t ଚାବି_2[3][16] = {
        {0x01, 0x23, 0x45, 0x67, 0x12, 0x34, 0x56, 0x78, 0x23, 0x45, 0x67, 0x89, 0x34, 0x56, 0x78, 0x9a},
        {0x01, 0x23, 0x45, 0x67, 0x12, 0x34, 0x56, 0x78, 0x23, 0x45},
        {0x01, 0x23, 0x45, 0x67, 0x12}
    };
    ସ୍ଥିର ଅଚଳ uint8_t rpt[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    ସ୍ଥିର ଅଚଳ uint8_t rct[3][8] = {
        {0x23, 0x8b, 0x4f, 0xe5, 0x84, 0x7e, 0x44, 0xb2},
        {0xeb, 0x6a, 0x71, 0x1a, 0x2c, 0x02, 0x27, 0x1b},
        {0x7a, 0xc8, 0x16, 0xd1, 0x6e, 0x9b, 0x30, 0x2e}
    };
    ସ୍ଥିର ଅଚଳ uint8_t rct2[2][16] = {
        {0xee, 0xa9, 0xd0, 0xa2, 0x49, 0xfd, 0x3b, 0xa6, 0xb3, 0x43, 0x6f, 0xb8, 0x9d, 0x6d, 0xca, 0x92},
        {0xb2, 0xc9, 0x5e, 0xb0, 0x0c, 0x31, 0xad, 0x71, 0x80, 0xac, 0x05, 0xb8, 0xe8, 0x3d, 0x69, 0x6e}
    };
    ସ୍ଥିର ଅଚଳ uint8_t iv[8] = {0xee, 0xa9, 0xd0, 0xa2, 0x49, 0xfd, 0x3b, 0xa6};
    ସ୍ଥିର uint8_t rpt2[2][16];
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j, err = 0;
    ସ୍ଥିର ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଚାବି_bits[3] = {128, 80, 40};
    uint8_t temp[8];
    ସଂରଚନା AVCAST5 *cs;
    cs = av_cast5_alloc();
    ଯଦି (!cs)
        ଫେରନ୍ତୁ 1;
    ପାଇଁ (j = 0; j < 3; j++){

        av_cast5_init(cs, ଚାବି_2[j], ଚାବି_bits[j]);
        av_cast5_crypt(cs, temp, rpt, 1, 0);
        ପାଇଁ (i = 0;i < 8; i++){
            ଯଦି (rct[j][i] != temp[i]){
                av_log(ଖାଲି, AV_LOG_ERROR, "%d %02x %02x\n", i, rct[j][i], temp[i]);
                err = 1;
            }
        }

        av_cast5_crypt(cs, temp, rct[j], 1, 1);
        ପାଇଁ (i =0; i < 8; i++) {
            ଯଦି (rpt[i] != temp[i]) {
                av_log(ଖାଲି, AV_LOG_ERROR, "%d %02x %02x\n", i, rpt[i], temp[i]);
                err = 1;
            }
        }
    }
    memcpy(rpt2[0], ଚାବି_2[0], 16);
    memcpy(rpt2[1], ଚାବି_2[0], 16);
    ପାଇଁ (i = 0; i < 1000000; i++){
        av_cast5_init(cs, rpt2[1], 128);
        av_cast5_crypt(cs, rpt2[0], rpt2[0], 2, 0);
        av_cast5_init(cs, rpt2[0], 128);
        av_cast5_crypt(cs, rpt2[1], rpt2[1], 2, 0);
    }
    ପାଇଁ (j = 0; j < 2; j++) {
        ପାଇଁ (i = 0; i < 16; i++) {
            ଯଦି (rct2[j][i] != rpt2[j][i]) {
                av_log(ଖାଲି, AV_LOG_ERROR, "%d %02x %02x\n", i, rct2[j][i], rpt2[j][i]);
                err = 1;
            }
        }
    }
    ପାଇଁ (j = 0; j < 3; j++) {

        av_cast5_init(cs, ଚାବି_2[j], ଚାବି_bits[j]);
        memcpy(temp, iv, 8);
        av_cast5_crypt2(cs, rpt2[0], rct2[0], 2, temp, 0);
        memcpy(temp, iv, 8);
        av_cast5_crypt2(cs, rpt2[0], rpt2[0], 2, temp, 1);
        ପାଇଁ (i = 0; i < 16; i++) {
            ଯଦି (rct2[0][i] != rpt2[0][i]) {
                av_log(ଖାଲି, AV_LOG_ERROR, "%d %02x %02x\n", i, rct2[0][i], rpt2[0][i]);
                err = 1;
            }
        }
    }
    av_free(cs);
    ଫେରନ୍ତୁ err;
}

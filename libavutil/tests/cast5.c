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

#समावेश <stddef.h>
#समावेश <string.h>

#समावेश "libavutil/cast5.h"
#समावेश "libavutil/log.h"
#समावेश "libavutil/mem.h"

पूर्णांक मुख्य(पूर्णांक argc, अक्षर** argv)
{

    अटल स्थिर uint8_t कुंजी_2[3][16] = {
        {0x01, 0x23, 0x45, 0x67, 0x12, 0x34, 0x56, 0x78, 0x23, 0x45, 0x67, 0x89, 0x34, 0x56, 0x78, 0x9a},
        {0x01, 0x23, 0x45, 0x67, 0x12, 0x34, 0x56, 0x78, 0x23, 0x45},
        {0x01, 0x23, 0x45, 0x67, 0x12}
    };
    अटल स्थिर uint8_t rpt[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    अटल स्थिर uint8_t rct[3][8] = {
        {0x23, 0x8b, 0x4f, 0xe5, 0x84, 0x7e, 0x44, 0xb2},
        {0xeb, 0x6a, 0x71, 0x1a, 0x2c, 0x02, 0x27, 0x1b},
        {0x7a, 0xc8, 0x16, 0xd1, 0x6e, 0x9b, 0x30, 0x2e}
    };
    अटल स्थिर uint8_t rct2[2][16] = {
        {0xee, 0xa9, 0xd0, 0xa2, 0x49, 0xfd, 0x3b, 0xa6, 0xb3, 0x43, 0x6f, 0xb8, 0x9d, 0x6d, 0xca, 0x92},
        {0xb2, 0xc9, 0x5e, 0xb0, 0x0c, 0x31, 0xad, 0x71, 0x80, 0xac, 0x05, 0xb8, 0xe8, 0x3d, 0x69, 0x6e}
    };
    अटल स्थिर uint8_t iv[8] = {0xee, 0xa9, 0xd0, 0xa2, 0x49, 0xfd, 0x3b, 0xa6};
    अटल uint8_t rpt2[2][16];
    पूर्णांक i, j, err = 0;
    अटल स्थिर पूर्णांक कुंजी_bits[3] = {128, 80, 40};
    uint8_t अस्थायी[8];
    काष्ठा AVCAST5 *cs;
    cs = av_cast5_alloc();
    अगर (!cs)
        वापस 1;
    क्रम (j = 0; j < 3; j++){

        av_cast5_init(cs, कुंजी_2[j], कुंजी_bits[j]);
        av_cast5_crypt(cs, अस्थायी, rpt, 1, 0);
        क्रम (i = 0;i < 8; i++){
            अगर (rct[j][i] != अस्थायी[i]){
                av_log(शून्य, AV_LOG_ERROR, "%d %02x %02x\n", i, rct[j][i], अस्थायी[i]);
                err = 1;
            }
        }

        av_cast5_crypt(cs, अस्थायी, rct[j], 1, 1);
        क्रम (i =0; i < 8; i++) {
            अगर (rpt[i] != अस्थायी[i]) {
                av_log(शून्य, AV_LOG_ERROR, "%d %02x %02x\n", i, rpt[i], अस्थायी[i]);
                err = 1;
            }
        }
    }
    स_नकल(rpt2[0], कुंजी_2[0], 16);
    स_नकल(rpt2[1], कुंजी_2[0], 16);
    क्रम (i = 0; i < 1000000; i++){
        av_cast5_init(cs, rpt2[1], 128);
        av_cast5_crypt(cs, rpt2[0], rpt2[0], 2, 0);
        av_cast5_init(cs, rpt2[0], 128);
        av_cast5_crypt(cs, rpt2[1], rpt2[1], 2, 0);
    }
    क्रम (j = 0; j < 2; j++) {
        क्रम (i = 0; i < 16; i++) {
            अगर (rct2[j][i] != rpt2[j][i]) {
                av_log(शून्य, AV_LOG_ERROR, "%d %02x %02x\n", i, rct2[j][i], rpt2[j][i]);
                err = 1;
            }
        }
    }
    क्रम (j = 0; j < 3; j++) {

        av_cast5_init(cs, कुंजी_2[j], कुंजी_bits[j]);
        स_नकल(अस्थायी, iv, 8);
        av_cast5_crypt2(cs, rpt2[0], rct2[0], 2, अस्थायी, 0);
        स_नकल(अस्थायी, iv, 8);
        av_cast5_crypt2(cs, rpt2[0], rpt2[0], 2, अस्थायी, 1);
        क्रम (i = 0; i < 16; i++) {
            अगर (rct2[0][i] != rpt2[0][i]) {
                av_log(शून्य, AV_LOG_ERROR, "%d %02x %02x\n", i, rct2[0][i], rpt2[0][i]);
                err = 1;
            }
        }
    }
    av_free(cs);
    वापस err;
}

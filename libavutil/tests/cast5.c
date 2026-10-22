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

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "libavutil/cast5.h"
#ಅನ್ತರ್ಭಾವ "libavutil/log.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ** argv)
{

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t ಕೀಲಿ_2[3][16] = {
        {0x01, 0x23, 0x45, 0x67, 0x12, 0x34, 0x56, 0x78, 0x23, 0x45, 0x67, 0x89, 0x34, 0x56, 0x78, 0x9a},
        {0x01, 0x23, 0x45, 0x67, 0x12, 0x34, 0x56, 0x78, 0x23, 0x45},
        {0x01, 0x23, 0x45, 0x67, 0x12}
    };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t rpt[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t rct[3][8] = {
        {0x23, 0x8b, 0x4f, 0xe5, 0x84, 0x7e, 0x44, 0xb2},
        {0xeb, 0x6a, 0x71, 0x1a, 0x2c, 0x02, 0x27, 0x1b},
        {0x7a, 0xc8, 0x16, 0xd1, 0x6e, 0x9b, 0x30, 0x2e}
    };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t rct2[2][16] = {
        {0xee, 0xa9, 0xd0, 0xa2, 0x49, 0xfd, 0x3b, 0xa6, 0xb3, 0x43, 0x6f, 0xb8, 0x9d, 0x6d, 0xca, 0x92},
        {0xb2, 0xc9, 0x5e, 0xb0, 0x0c, 0x31, 0xad, 0x71, 0x80, 0xac, 0x05, 0xb8, 0xe8, 0x3d, 0x69, 0x6e}
    };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ uint8_t iv[8] = {0xee, 0xa9, 0xd0, 0xa2, 0x49, 0xfd, 0x3b, 0xa6};
    ಸ್ಥಿರ uint8_t rpt2[2][16];
    ಪೂರ್ಣಾಂಕ i, j, err = 0;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಕೀಲಿ_ಬಿಟ್ಟುಗಳು[3] = {128, 80, 40};
    uint8_t ತಾತ್ಕಾಲಿಕ[8];
    ರಚನೆ AVCAST5 *cs;
    cs = av_cast5_alloc();
    ಆದರೆ (!cs)
        ಹಿಂತಿರುಗಿ 1;
    ಗಾಗಿ (j = 0; j < 3; j++){

        av_cast5_init(cs, ಕೀಲಿ_2[j], ಕೀಲಿ_ಬಿಟ್ಟುಗಳು[j]);
        av_cast5_crypt(cs, ತಾತ್ಕಾಲಿಕ, rpt, 1, 0);
        ಗಾಗಿ (i = 0;i < 8; i++){
            ಆದರೆ (rct[j][i] != ತಾತ್ಕಾಲಿಕ[i]){
                av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d %02x %02x\n", i, rct[j][i], ತಾತ್ಕಾಲಿಕ[i]);
                err = 1;
            }
        }

        av_cast5_crypt(cs, ತಾತ್ಕಾಲಿಕ, rct[j], 1, 1);
        ಗಾಗಿ (i =0; i < 8; i++) {
            ಆದರೆ (rpt[i] != ತಾತ್ಕಾಲಿಕ[i]) {
                av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d %02x %02x\n", i, rpt[i], ತಾತ್ಕಾಲಿಕ[i]);
                err = 1;
            }
        }
    }
    ಸ್ಮರಣೆ_ನಕಲು(rpt2[0], ಕೀಲಿ_2[0], 16);
    ಸ್ಮರಣೆ_ನಕಲು(rpt2[1], ಕೀಲಿ_2[0], 16);
    ಗಾಗಿ (i = 0; i < 1000000; i++){
        av_cast5_init(cs, rpt2[1], 128);
        av_cast5_crypt(cs, rpt2[0], rpt2[0], 2, 0);
        av_cast5_init(cs, rpt2[0], 128);
        av_cast5_crypt(cs, rpt2[1], rpt2[1], 2, 0);
    }
    ಗಾಗಿ (j = 0; j < 2; j++) {
        ಗಾಗಿ (i = 0; i < 16; i++) {
            ಆದರೆ (rct2[j][i] != rpt2[j][i]) {
                av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d %02x %02x\n", i, rct2[j][i], rpt2[j][i]);
                err = 1;
            }
        }
    }
    ಗಾಗಿ (j = 0; j < 3; j++) {

        av_cast5_init(cs, ಕೀಲಿ_2[j], ಕೀಲಿ_ಬಿಟ್ಟುಗಳು[j]);
        ಸ್ಮರಣೆ_ನಕಲು(ತಾತ್ಕಾಲಿಕ, iv, 8);
        av_cast5_crypt2(cs, rpt2[0], rct2[0], 2, ತಾತ್ಕಾಲಿಕ, 0);
        ಸ್ಮರಣೆ_ನಕಲು(ತಾತ್ಕಾಲಿಕ, iv, 8);
        av_cast5_crypt2(cs, rpt2[0], rpt2[0], 2, ತಾತ್ಕಾಲಿಕ, 1);
        ಗಾಗಿ (i = 0; i < 16; i++) {
            ಆದರೆ (rct2[0][i] != rpt2[0][i]) {
                av_log(ಖಾಲಿ, AV_LOG_ERROR, "%d %02x %02x\n", i, rct2[0][i], rpt2[0][i]);
                err = 1;
            }
        }
    }
    av_free(cs);
    ಹಿಂತಿರುಗಿ err;
}

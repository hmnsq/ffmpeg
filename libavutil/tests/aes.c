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

// LCOV_EXCL_START

#شامل "libavutil/timer.h"

#شامل <string.h>

#شامل "libavutil/aes.h"
#شامل "libavutil/lfg.h"
#شامل "libavutil/log.h"
#شامل "libavutil/mem.h"

صحیح مین(صحیح argc, حرف **argv)
{
    صحیح i, j;
    ساخت AVAES *b;
    ساکن ثابت uint8_t rkey[2][16] = {
        { 0 },
        { 0x10, 0xa5, 0x88, 0x69, 0xd7, 0x4b, 0xe5, 0xa3,
          0x74, 0xcf, 0x86, 0x7c, 0xfb, 0x47, 0x38, 0x59 }
    };
    ساکن ثابت uint8_t rpt[2][16] = {
        { 0x6a, 0x84, 0x86, 0x7c, 0xd7, 0x7e, 0x12, 0xad,
          0x07, 0xea, 0x1b, 0xe8, 0x95, 0xc5, 0x3f, 0xa3 },
        { 0 }
    };
    ساکن ثابت uint8_t rct[2][16] = {
        { 0x73, 0x22, 0x81, 0xc0, 0xa0, 0xaa, 0xb8, 0xf7,
          0xa5, 0x4a, 0x0c, 0x67, 0xa0, 0xc4, 0x5e, 0xcf },
        { 0x6d, 0x25, 0x1e, 0x69, 0x44, 0xb0, 0x51, 0xe0,
          0x4e, 0xaa, 0x6f, 0xb4, 0xdb, 0xf7, 0x84, 0x65 }
    };
    uint8_t pt[32];
    uint8_t عارضی[32];
    uint8_t iv[2][16];
    صحیح err = 0;

    b = av_aes_alloc();
    اگر (!b)
        واپس 1;

    av_log_سیٹ_level(AV_LOG_DEBUG);

    برائے (i = 0; i < 2; i++) {
        av_aes_init(b, rkey[i], 128, 1);
        av_aes_crypt(b, عارضی, rct[i], 1, تہی, 1);
        برائے (j = 0; j < 16; j++) {
            اگر (rpt[i][j] != عارضی[j]) {
                av_log(تہی, AV_LOG_ERROR, "%d %02X %02X\n",
                       j, rpt[i][j], عارضی[j]);
                err = 1;
            }
        }
    }
    av_free(b);

    اگر (argc > 1 && !strcmp(argv[1], "-t")) {
        ساخت AVAES *ae, *ad;
        AVLFG prng;

        ae = av_aes_alloc();
        ad = av_aes_alloc();

        اگر (!ae || !ad) {
            av_free(ae);
            av_free(ad);
            واپس 1;
        }

        av_aes_init(ae, (ثابت uint8_t*)"PI=3.141592654..", 128, 0);
        av_aes_init(ad, (ثابت uint8_t*)"PI=3.141592654..", 128, 1);
        av_lfg_init(&prng, 1);

        برائے (i = 0; i < 10000; i++) {
            برائے (j = 0; j < 32; j++)
                pt[j] = av_lfg_get(&prng);
            برائے (j = 0; j < 16; j++)
                iv[0][j] = iv[1][j] = av_lfg_get(&prng);
            {
                آغاز_TIMER;
                av_aes_crypt(ae, عارضی, pt, 2, iv[0], 0);
                اگر (!(i & (i - 1)))
                    av_log(تہی, AV_LOG_ERROR, "%02X %02X %02X %02X\n",
                           عارضی[0], عارضی[5], عارضی[10], عارضی[15]);
                av_aes_crypt(ad, عارضی, عارضی, 2, iv[1], 1);
                av_aes_crypt(ae, عارضی, pt, 2, تہی, 0);
                اگر (!(i & (i - 1)))
                    av_log(تہی, AV_LOG_ERROR, "%02X %02X %02X %02X\n",
                           عارضی[0], عارضی[5], عارضی[10], عارضی[15]);
                av_aes_crypt(ad, عارضی, عارضی, 2, تہی, 1);
                STOP_TIMER("aes");
            }
            برائے (j = 0; j < 16; j++) {
                اگر (pt[j] != عارضی[j]) {
                    av_log(تہی, AV_LOG_ERROR, "%d %d %02X %02X\n",
                           i, j, pt[j], عارضی[j]);
                }
            }
        }
        av_free(ae);
        av_free(ad);
    }
    واپس err;
}
// LCOV_EXCL_STOP

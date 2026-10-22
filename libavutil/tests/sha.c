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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/sha.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    పూర్ణాంకం i, j, k;
    నిర్మాణం AVSHA *ctx;
    గుర్తులేని అక్షరం digest[32];
    స్థిర స్థిరరాశి పూర్ణాంకం lengths[3] = { 160, 224, 256 };

    ctx = av_sha_alloc();
    ఒకవేళ (!ctx)
        తిరిగి 1;

    కొరకు (j = 0; j < 3; j++) {
        రాయి("Testing SHA-%d\n", lengths[j]);
        కొరకు (k = 0; k < 3; k++) {
            av_sha_init(ctx, lengths[j]);
            ఒకవేళ (k == 0)
                av_sha_update(ctx, "abc", 3);
            లేకపోతే ఒకవేళ (k == 1)
                av_sha_update(ctx, "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq", 56);
            లేకపోతే
                కొరకు (i = 0; i < 1000*1000; i++)
                    av_sha_update(ctx, "a", 1);
            av_sha_final(ctx, digest);
            కొరకు (i = 0; i < lengths[j] >> 3; i++)
                రాయి("%02X", digest[i]);
            అక్షరం_రాయి('\n');
        }
        ఎంపిక (j) {
        స్థితి 0:
            //test vectors (from FIPS PUB 180-1)
            రాయి("A9993E36 4706816A BA3E2571 7850C26C 9CD0D89D\n"
                   "84983E44 1C3BD26E BAAE4AA1 F95129E5 E54670F1\n"
                   "34AA973C D4C4DAA4 F61EEB2B DBAD2731 6534016F\n");
            ఆపు;
        స్థితి 1:
            //test vectors (from FIPS PUB 180-2 Appendix A)
            రాయి("23097d22 3405d822 8642a477 bda255b3 2aadbce4 bda0b3f7 e36c9da7\n"
                   "75388b16 512776cc 5dba5da1 fd890150 b0c6455c b4f58b19 52522525\n"
                   "20794655 980c91d8 bbb4c1ea 97618a4b f03f4258 1948b2ee 4ee7ad67\n");
            ఆపు;
        స్థితి 2:
            //test vectors (from FIPS PUB 180-2)
            రాయి("ba7816bf 8f01cfea 414140de 5dae2223 b00361a3 96177a9c b410ff61 f20015ad\n"
                   "248d6a61 d20638b8 e5c02693 0c3e6039 a33ce459 64ff2167 f6ecedd4 19db06c1\n"
                   "cdc76e5c 9914fb92 81a1c7e2 84d73e67 f1809a48 a497200e 046d39cc c7112cd0\n");
            ఆపు;
        }
    }
    av_free(ctx);

    తిరిగి 0;
}

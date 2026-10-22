/*
 * Copyright (C) 2007 Michael Niedermayer <michaelni@gmx.at>
 * Copyright (C) 2009 Konstantin Shishkov
 * Copyright (C) 2013 James Almer
 * based on BSD-licensed SHA-2 code by Aaron D. Gifford
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

#అన్తర్భావ "libavutil/mem.h"
#అన్తర్భావ "libavutil/sha512.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    పూర్ణాంకం i, j, k;
    నిర్మాణం AVSHA512 *ctx;
    గుర్తులేని అక్షరం digest[64];
    స్థిర స్థిరరాశి పూర్ణాంకం lengths[4] = { 224, 256, 384, 512 };

    ctx = av_sha512_alloc();
    ఒకవేళ (!ctx)
        తిరిగి 1;

    కొరకు (j = 0; j < 4; j++) {
        ఒకవేళ (j < 2) రాయి("Testing SHA-512/%d\n", lengths[j]);
        లేకపోతే       రాయి("Testing SHA-%d\n", lengths[j]);
        కొరకు (k = 0; k < 3; k++) {
            av_sha512_init(ctx, lengths[j]);
            ఒకవేళ (k == 0)
                av_sha512_update(ctx, "abc", 3);
            లేకపోతే ఒకవేళ (k == 1)
                av_sha512_update(ctx, "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
                                       "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu", 112);
            లేకపోతే
                కొరకు (i = 0; i < 1000*1000; i++)
                    av_sha512_update(ctx, "a", 1);
            av_sha512_final(ctx, digest);
            కొరకు (i = 0; i < lengths[j] >> 3; i++)
                రాయి("%02X", digest[i]);
            అక్షరం_రాయి('\n');
        }
        ఎంపిక (j) { //test vectors (from FIPS PUB 180-4 Appendix A)
        స్థితి 0:
            రాయి("4634270f 707b6a54 daae7530 460842e2 0e37ed26 5ceee9a4 3e8924aa\n"
                   "23fec5bb 94d60b23 30819264 0b0c4533 35d66473 4fe40e72 68674af9\n"
                   "37ab331d 76f0d36d e422bd0e deb22a28 accd487b 7a8453ae 965dd287\n");
            ఆపు;
        స్థితి 1:
            రాయి("53048e26 81941ef9 9b2e29b7 6b4c7dab e4c2d0c6 34fc6d46 e0e2f131 07e7af23\n"
                   "3928e184 fb8690f8 40da3988 121d31be 65cb9d3e f83ee614 6feac861 e19b563a\n"
                   "9a59a052 930187a9 7038cae6 92f30708 aa649192 3ef51943 94dc68d5 6c74fb21\n");
            ఆపు;
        స్థితి 2:
            రాయి("cb00753f 45a35e8b b5a03d69 9ac65007 272c32ab 0eded163 "
                   "1a8b605a 43ff5bed 8086072b a1e7cc23 58baeca1 34c825a7\n"
                   "09330c33 f71147e8 3d192fc7 82cd1b47 53111b17 3b3b05d2 "
                   "2fa08086 e3b0f712 fcc7c71a 557e2db9 66c3e9fa 91746039\n"
                   "9d0e1809 716474cb 086e834e 310a4a1c ed149e9c 00f24852 "
                   "7972cec5 704c2a5b 07b8b3dc 38ecc4eb ae97ddd8 7f3d8985\n");
            ఆపు;
        స్థితి 3:
            రాయి("ddaf35a1 93617aba cc417349 ae204131 12e6fa4e 89a97ea2 0a9eeee6 4b55d39a "
                   "2192992a 274fc1a8 36ba3c23 a3feebbd 454d4423 643ce80e 2a9ac94f a54ca49f\n"
                   "8e959b75 dae313da 8cf4f728 14fc143f 8f7779c6 eb9f7fa1 7299aead b6889018 "
                   "501d289e 4900f7e4 331b99de c4b5433a c7d329ee b6dd2654 5e96e55b 874be909\n"
                   "e718483d 0ce76964 4e2e42c7 bc15b463 8e1f98b1 3b204428 5632a803 afa973eb "
                   "de0ff244 877ea60a 4cb0432c e577c31b eb009c5c 2c49aa2e 4eadb217 ad8cc09b\n");
            ఆపు;
        }
    }
    av_free(ctx);

    తిరిగి 0;
}

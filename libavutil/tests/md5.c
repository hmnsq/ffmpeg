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

#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/md5.h"

స్థిర శూన్య print_md5(uint8_t *md5)
{
    పూర్ణాంకం i;
    కొరకు (i = 0; i < 16; i++)
        రాయి("%02x", md5[i]);
    రాయి("\n");
}

పూర్ణాంకం ప్రధాన(శూన్య)
{
    uint8_t md5val[16];
    పూర్ణాంకం i;

    uint8_t లోపల[1000];

    కొరకు (i = 0; i < 1000; i++)
        లోపల[i] = i * i;
    av_md5_కూడిక(md5val, లోపల, 1000);
    print_md5(md5val);
    av_md5_కూడిక(md5val, లోపల, 63);
    print_md5(md5val);
    av_md5_కూడిక(md5val, లోపల, 64);
    print_md5(md5val);
    av_md5_కూడిక(md5val, లోపల, 65);
    print_md5(md5val);
    కొరకు (i = 0; i < 1000; i++)
        లోపల[i] = i % 127;
    av_md5_కూడిక(md5val, లోపల, 999);
    print_md5(md5val);

    తిరిగి 0;
}

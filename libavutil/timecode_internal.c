/*
 * Copyright (c) 2006 Smartjog S.A.S, Baptiste Coudurier <baptiste.coudurier@gmail.com>
 * Copyright (c) 2011-2012 Smartjog S.A.S, Clément Bœsch <clement.boesch@smartjog.com>
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

#అన్తర్భావ "timecode_internal.h"

స్థిర గుర్తులేని bcd2uint(uint8_t bcd)
{
   గుర్తులేని దిగువ  = bcd & 0xf;
   గుర్తులేని ఎగువ = bcd >> 4;
   ఒకవేళ (దిగువ > 9 || ఎగువ > 9)
       తిరిగి 0;
   తిరిగి దిగువ + 10*ఎగువ;
}

శూన్య ff_timecode_సమితి_smpte(గుర్తులేని *drop, గుర్తులేని *hh, గుర్తులేని *mm, గుర్తులేని *ss, గుర్తులేని *ff,
                           AVRational రేటు, uint32_t tcsmpte, పూర్ణాంకం prevent_df, పూర్ణాంకం skip_క్షేత్రం)
{
    *hh   = bcd2uint(tcsmpte     & 0x3f);    // 6-bit hours
    *mm   = bcd2uint(tcsmpte>>8  & 0x7f);    // 7-bit minutes
    *ss   = bcd2uint(tcsmpte>>16 & 0x7f);    // 7-bit seconds
    *ff   = bcd2uint(tcsmpte>>24 & 0x3f);    // 6-bit frames
    *drop = tcsmpte & 1<<30 && !prevent_df;  // 1-bit drop if not arbitrary bit

    ఒకవేళ (av_cmp_q(రేటు, (AVRational) {30, 1}) == 1) {
        *ff <<= 1;
        ఒకవేళ (!skip_క్షేత్రం) {
            ఒకవేళ (av_cmp_q(రేటు, (AVRational) {50, 1}) == 0)
                *ff += !!(tcsmpte & 1 << 7);
            లేకపోతే
                *ff += !!(tcsmpte & 1 << 23);
        }
    }
}

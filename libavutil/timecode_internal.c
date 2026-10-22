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

#அந்தர்பாவ "timecode_internal.h"

நிலையான unsigned bcd2uint(uint8_t bcd)
{
   unsigned கீழ்  = bcd & 0xf;
   unsigned உயர்வு = bcd >> 4;
   எனில் (கீழ் > 9 || உயர்வு > 9)
       திரும்பு 0;
   திரும்பு கீழ் + 10*உயர்வு;
}

வெறுமை ff_timecode_set_smpte(unsigned *drop, unsigned *hh, unsigned *mm, unsigned *ss, unsigned *ff,
                           AVRational rate, uint32_t tcsmpte, முழு prevent_df, முழு skip_field)
{
    *hh   = bcd2uint(tcsmpte     & 0x3f);    // 6-bit hours
    *mm   = bcd2uint(tcsmpte>>8  & 0x7f);    // 7-bit minutes
    *ss   = bcd2uint(tcsmpte>>16 & 0x7f);    // 7-bit seconds
    *ff   = bcd2uint(tcsmpte>>24 & 0x3f);    // 6-bit frames
    *drop = tcsmpte & 1<<30 && !prevent_df;  // 1-bit drop if not arbitrary bit

    எனில் (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        *ff <<= 1;
        எனில் (!skip_field) {
            எனில் (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                *ff += !!(tcsmpte & 1 << 7);
            இல்லையெனில்
                *ff += !!(tcsmpte & 1 << 23);
        }
    }
}

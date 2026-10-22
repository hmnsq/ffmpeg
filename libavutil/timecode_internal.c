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

#अन्तर्भाव "timecode_internal.h"

स्थिर अचिन्हित bcd2uint(uint8_t bcd)
{
   अचिन्हित तल्लो  = bcd & 0xf;
   अचिन्हित माथिल्लो = bcd >> 4;
   यदि (तल्लो > 9 || माथिल्लो > 9)
       फर्काऊ 0;
   फर्काऊ तल्लो + 10*माथिल्लो;
}

शून्य ff_timecode_set_smpte(अचिन्हित *drop, अचिन्हित *hh, अचिन्हित *mm, अचिन्हित *ss, अचिन्हित *ff,
                           AVRational rate, uint32_t tcsmpte, पूर्णाङ्क prevent_df, पूर्णाङ्क skip_field)
{
    *hh   = bcd2uint(tcsmpte     & 0x3f);    // 6-bit hours
    *mm   = bcd2uint(tcsmpte>>8  & 0x7f);    // 7-bit minutes
    *ss   = bcd2uint(tcsmpte>>16 & 0x7f);    // 7-bit seconds
    *ff   = bcd2uint(tcsmpte>>24 & 0x3f);    // 6-bit frames
    *drop = tcsmpte & 1<<30 && !prevent_df;  // 1-bit drop if not arbitrary bit

    यदि (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        *ff <<= 1;
        यदि (!skip_field) {
            यदि (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                *ff += !!(tcsmpte & 1 << 7);
            अन्यथा
                *ff += !!(tcsmpte & 1 << 23);
        }
    }
}

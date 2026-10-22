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

#ಅನ್ತರ್ಭಾವ "timecode_internal.h"

ಸ್ಥಿರ unsigned bcd2uint(uint8_t bcd)
{
   unsigned ಕೆಳಗಿನ  = bcd & 0xf;
   unsigned ಮೇಲಿನ = bcd >> 4;
   ಯದಿ (ಕೆಳಗಿನ > 9 || ಮೇಲಿನ > 9)
       ಪ್ರತ್ಯಾಗಮ 0;
   ಪ್ರತ್ಯಾಗಮ ಕೆಳಗಿನ + 10*ಮೇಲಿನ;
}

ಶೂನ್ಯ ff_timecode_set_smpte(unsigned *drop, unsigned *hh, unsigned *mm, unsigned *ss, unsigned *ff,
                           AVRational rate, uint32_t tcsmpte, ಪೂರ್ಣಾಙ್ಕ prevent_df, ಪೂರ್ಣಾಙ್ಕ skip_field)
{
    *hh   = bcd2uint(tcsmpte     & 0x3f);    // 6-bit hours
    *mm   = bcd2uint(tcsmpte>>8  & 0x7f);    // 7-bit minutes
    *ss   = bcd2uint(tcsmpte>>16 & 0x7f);    // 7-bit seconds
    *ff   = bcd2uint(tcsmpte>>24 & 0x3f);    // 6-bit frames
    *drop = tcsmpte & 1<<30 && !prevent_df;  // 1-bit drop if not arbitrary bit

    ಯದಿ (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        *ff <<= 1;
        ಯದಿ (!skip_field) {
            ಯದಿ (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                *ff += !!(tcsmpte & 1 << 7);
            ಅನ್ಯಥಾ
                *ff += !!(tcsmpte & 1 << 23);
        }
    }
}

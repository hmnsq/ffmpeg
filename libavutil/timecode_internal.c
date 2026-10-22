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

ಸ್ಥಿರ ಚಿಹ್ನೆರಹಿತ bcd2uint(uint8_t bcd)
{
   ಚಿಹ್ನೆರಹಿತ ಕೆಳಗಿನ  = bcd & 0xf;
   ಚಿಹ್ನೆರಹಿತ ಮೇಲಿನ = bcd >> 4;
   ಆದರೆ (ಕೆಳಗಿನ > 9 || ಮೇಲಿನ > 9)
       ಹಿಂತಿರುಗಿ 0;
   ಹಿಂತಿರುಗಿ ಕೆಳಗಿನ + 10*ಮೇಲಿನ;
}

ಶೂನ್ಯ ff_timecode_ಗಣ_smpte(ಚಿಹ್ನೆರಹಿತ *drop, ಚಿಹ್ನೆರಹಿತ *hh, ಚಿಹ್ನೆರಹಿತ *mm, ಚಿಹ್ನೆರಹಿತ *ss, ಚಿಹ್ನೆರಹಿತ *ff,
                           AVRational ದರ, uint32_t tcsmpte, ಪೂರ್ಣಾಂಕ prevent_df, ಪೂರ್ಣಾಂಕ skip_ಕ್ಷೇತ್ರ)
{
    *hh   = bcd2uint(tcsmpte     & 0x3f);    // 6-bit hours
    *mm   = bcd2uint(tcsmpte>>8  & 0x7f);    // 7-bit minutes
    *ss   = bcd2uint(tcsmpte>>16 & 0x7f);    // 7-bit seconds
    *ff   = bcd2uint(tcsmpte>>24 & 0x3f);    // 6-bit frames
    *drop = tcsmpte & 1<<30 && !prevent_df;  // 1-bit drop if not arbitrary bit

    ಆದರೆ (av_cmp_q(ದರ, (AVRational) {30, 1}) == 1) {
        *ff <<= 1;
        ಆದರೆ (!skip_ಕ್ಷೇತ್ರ) {
            ಆದರೆ (av_cmp_q(ದರ, (AVRational) {50, 1}) == 0)
                *ff += !!(tcsmpte & 1 << 7);
            ಇಲ್ಲದಿದ್ದರೆ
                *ff += !!(tcsmpte & 1 << 23);
        }
    }
}

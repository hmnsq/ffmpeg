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

#അന്തര്ഭാവ "timecode_internal.h"

സ്ഥിതം unsigned bcd2uint(uint8_t bcd)
{
   unsigned താഴെയുള്ള  = bcd & 0xf;
   unsigned മുകളിലെ = bcd >> 4;
   എങ്കിൽ (താഴെയുള്ള > 9 || മുകളിലെ > 9)
       തിരികെ 0;
   തിരികെ താഴെയുള്ള + 10*മുകളിലെ;
}

ശൂന്യം ff_timecode_set_smpte(unsigned *drop, unsigned *hh, unsigned *mm, unsigned *ss, unsigned *ff,
                           AVRational rate, uint32_t tcsmpte, പൂർണ്ണസംഖ്യ prevent_df, പൂർണ്ണസംഖ്യ skip_field)
{
    *hh   = bcd2uint(tcsmpte     & 0x3f);    // 6-bit hours
    *mm   = bcd2uint(tcsmpte>>8  & 0x7f);    // 7-bit minutes
    *ss   = bcd2uint(tcsmpte>>16 & 0x7f);    // 7-bit seconds
    *ff   = bcd2uint(tcsmpte>>24 & 0x3f);    // 6-bit frames
    *drop = tcsmpte & 1<<30 && !prevent_df;  // 1-bit drop if not arbitrary bit

    എങ്കിൽ (av_cmp_q(rate, (AVRational) {30, 1}) == 1) {
        *ff <<= 1;
        എങ്കിൽ (!skip_field) {
            എങ്കിൽ (av_cmp_q(rate, (AVRational) {50, 1}) == 0)
                *ff += !!(tcsmpte & 1 << 7);
            അല്ലെങ്കിൽ
                *ff += !!(tcsmpte & 1 << 23);
        }
    }
}

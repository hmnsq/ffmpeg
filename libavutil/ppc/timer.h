/*
 * Copyright (c) 2005 Luca Barbato <lu_zero@gentoo.org>
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_PPC_TIMER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_PPC_TIMER_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_READ_ਸਮਾਂ read_ਸਮਾਂ

ਸਥਿਰ ਸਤਰਅੰਦਰ uint64_t read_ਸਮਾਂ(ਖਾਲੀ)
{
    uint32_t tbu, tbl, ਆਰਜ਼ੀ;

     /* from section 2.2.1 of the 32-bit PowerPC PEM */
     __asm__ ਅਸਥਿਰ(
         "mftbu  %2\n"
         "mftb   %0\n"
         "mftbu  %1\n"
         "cmpw   %2,%1\n"
         "bne    $-0x10\n"
     : "=r"(tbl), "=r"(tbu), "=r"(ਆਰਜ਼ੀ)
     :
     : "cc");

     ਵਾਪਸ (((uint64_t)tbu)<<32) | (uint64_t)tbl;
}

#ਜੇ_ਅੰਤ /* AVUTIL_PPC_TIMER_H */

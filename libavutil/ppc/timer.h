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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_PPC_TIMER_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_PPC_TIMER_H

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "config.h"

#ವ್ಯಾಖ್ಯಾನಿಸು AV_READ_ಸಮಯ read_ಸಮಯ

ಸ್ಥಿರ ಸಾಲೊಳಗೆ uint64_t read_ಸಮಯ(ಶೂನ್ಯ)
{
    uint32_t tbu, tbl, ತಾತ್ಕಾಲಿಕ;

     /* from section 2.2.1 of the 32-bit PowerPC PEM */
     __asm__ ಅಸ್ಥಿರ(
         "mftbu  %2\n"
         "mftb   %0\n"
         "mftbu  %1\n"
         "cmpw   %2,%1\n"
         "bne    $-0x10\n"
     : "=r"(tbl), "=r"(tbu), "=r"(ತಾತ್ಕಾಲಿಕ)
     :
     : "cc");

     ಹಿಂತಿರುಗಿ (((uint64_t)tbu)<<32) | (uint64_t)tbl;
}

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_PPC_TIMER_H */

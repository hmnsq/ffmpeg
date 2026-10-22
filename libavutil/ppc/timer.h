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

#अगर_अघोषित AVUTIL_PPC_TIMER_H
#घोषणा AVUTIL_PPC_TIMER_H

#समावेश <stdint.h>

#समावेश "config.h"

#घोषणा AV_READ_TIME read_time

अटल अंतरभूत uint64_t read_time(व्योम)
{
    uint32_t tbu, tbl, अस्थायी;

     /* from section 2.2.1 of the 32-bit PowerPC PEM */
     __asm__ अस्थिर(
         "mftbu  %2\n"
         "mftb   %0\n"
         "mftbu  %1\n"
         "cmpw   %2,%1\n"
         "bne    $-0x10\n"
     : "=r"(tbl), "=r"(tbu), "=r"(अस्थायी)
     :
     : "cc");

     वापस (((uint64_t)tbu)<<32) | (uint64_t)tbl;
}

#पूर्ण_अगर /* AVUTIL_PPC_TIMER_H */

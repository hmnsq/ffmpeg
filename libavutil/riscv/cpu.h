/*
 * Copyright © 2022 Rémi Denis-Courmont.
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

#अगर_अघोषित AVUTIL_RISCV_CPU_H
#घोषणा AVUTIL_RISCV_CPU_H

#समावेश "config.h"
#समावेश <stdbool.h>
#समावेश <stddef.h>
#समावेश "libavutil/attributes_internal.h"
#समावेश "libavutil/cpu.h"

#अगर_अघोषित __riscv_zbb
बाह्य attribute_visibility_hidden bool ff_rv_zbb_supported;
#पूर्ण_अगर

अटल अंतरभूत av_const bool ff_rv_zbb_support(व्योम)
{
#अगर_अघोषित __riscv_zbb
    वापस ff_rv_zbb_supported;
#अन्यथा
    वापस true;
#पूर्ण_अगर
}

#अगर HAVE_RVV
/**
 * Returns the vector size in bytes (always a power of two and at least 4).
 * This is undefined behaviour if vectors are not implemented.
 */
अटल अंतरभूत av_const माप_प्रकार ff_get_rv_vlenb(व्योम)
{
    माप_प्रकार vlenb;

    __asm__ (
        ".option push\n"
        ".option arch, +v\n"
        "    csrr %0, vlenb\n"
        ".option pop\n" : "=r" (vlenb));
    वापस vlenb;
}

/**
 * Checks that the vector bit-size is at least the given value.
 * This is potentially undefined behaviour if vectors are not implemented.
 */
अटल अंतरभूत av_const bool ff_rv_vlen_least(अचिन्हित पूर्णांक bits)
{
#अगर_घोषित __riscv_v_min_vlen
    अगर (bits <= __riscv_v_min_vlen)
        वापस true;
#अन्यथा
    /*
     * Vector lengths smaller than 128 bits are only possible in embedded cases
     * and cannot be run-time detected, so we can assume 128 bits at least.
     */
    अगर (bits <= 128)
        वापस true;
#पूर्ण_अगर
    वापस bits <= (8 * ff_get_rv_vlenb());
}
#पूर्ण_अगर
#पूर्ण_अगर /* HAVE_RVV */

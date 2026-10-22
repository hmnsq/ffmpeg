/*
 * Copyright (c) 2020 Loongson Technology Corporation Limited
 * Contributed by Shiyou Yin <yinshiyou-hf@loongson.cn>
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

#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ "cpu.h"
#അന്തര്ഭാവ <sys/auxv.h>

#define LA_HWCAP_LSX    (1<<4)
#define LA_HWCAP_LASX   (1<<5)
സ്ഥിതം പൂർണ്ണസംഖ്യ cpu_flags_getauxval(ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ flags = 0;
    പൂർണ്ണസംഖ്യ flag  = (പൂർണ്ണസംഖ്യ)ff_getauxval(AT_HWCAP);

    എങ്കിൽ (flag & LA_HWCAP_LSX)
        flags |= AV_CPU_FLAG_LSX;
    എങ്കിൽ (flag & LA_HWCAP_LASX)
        flags |= AV_CPU_FLAG_LASX;

    തിരികെ flags;
}

പൂർണ്ണസംഖ്യ ff_get_cpu_flags_loongarch(ശൂന്യം)
{
#എങ്കിൽ defined __linux__
    തിരികെ cpu_flags_getauxval();
#അല്ലെങ്കിൽ
    /* Assume no SIMD ASE supported */
    തിരികെ 0;
#endif
}

size_t ff_get_cpu_max_align_loongarch(ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ flags = av_get_cpu_flags();

    എങ്കിൽ (flags & AV_CPU_FLAG_LASX)
        തിരികെ 32;
    എങ്കിൽ (flags & AV_CPU_FLAG_LSX)
        തിരികെ 16;

    തിരികെ 8;
}

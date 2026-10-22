/*
 * Copyright © 2024 Rémi Denis-Courmont.
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

#అన్తర్భావ "libavutil/cpu.h"

#నిర్వచితం_కాకపోతే __riscv_zbb
గుర్తులేని అక్షరం ff_rv_zbb_supported = 0;

#నిర్వచితమైతే __ELF__
__attribute__((constructor))
స్థిర శూన్య probe_zbb(శూన్య)
{
    ff_rv_zbb_supported = (av_get_cpu_flags() & AV_CPU_FLAG_RVB_BASIC) != 0;
}
#అయితే_ముగింపు
#అయితే_ముగింపు

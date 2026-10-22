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

#अन्तर्भाव "libavutil/cpu.h"

#यदि_अपरिभाषितम् __riscv_zbb
अचिह्नित वर्ण ff_rv_zbb_supported = 0;

#यदि_परिभाषितम् __ELF__
__attribute__((constructor))
स्थिर शून्य probe_zbb(शून्य)
{
    ff_rv_zbb_supported = (av_get_cpu_flags() & AV_CPU_FLAG_RVB_BASIC) != 0;
}
#यदि_अन्तः
#यदि_अन्तः

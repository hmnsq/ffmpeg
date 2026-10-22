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

#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __riscv_zbb
ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ ff_rv_zbb_supported = 0;

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __ELF__
__attribute__((constructor))
ಸ್ಥಿರ ಶೂನ್ಯ probe_zbb(ಶೂನ್ಯ)
{
    ff_rv_zbb_supported = (av_get_cpu_flags() & AV_CPU_FLAG_RVB_BASIC) != 0;
}
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ

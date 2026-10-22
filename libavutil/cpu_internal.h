/*
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

#ifndef AVUTIL_CPU_INTERNAL_H
#define AVUTIL_CPU_INTERNAL_H

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ "cpu.h"

#define CPUEXT_SUFFIX(flags, suffix, cpuext)                            \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext))

#define CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     !((flags) & AV_CPU_FLAG_ ## slow_cpuext ## SLOW))

#define CPUEXT_SUFFIX_SLOW(flags, suffix, cpuext)                       \
    (HAVE_ ## cpuext ## suffix &&                                       \
     ((flags) & (AV_CPU_FLAG_ ## cpuext | AV_CPU_FLAG_ ## cpuext ## SLOW)))

#define CPUEXT_SUFFIX_SLOW2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     ((flags) & (AV_CPU_FLAG_ ## slow_cpuext | AV_CPU_FLAG_ ## slow_cpuext ## SLOW)))

#define CPUEXT_SUFFIX_FAST(flags, suffix, cpuext) CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, cpuext)

#define CPUEXT(flags, cpuext) CPUEXT_SUFFIX(flags, , cpuext)
#define CPUEXT_FAST(flags, cpuext) CPUEXT_SUFFIX_FAST(flags, , cpuext)
#define CPUEXT_SLOW(flags, cpuext) CPUEXT_SUFFIX_SLOW(flags, , cpuext)

ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_mips(ಶೂನ್ಯ);
ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_aarch64(ಶೂನ್ಯ);
ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_arm(ಶೂನ್ಯ);
ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_ppc(ಶೂನ್ಯ);
ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_riscv(ಶೂನ್ಯ);
ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_wasm(ಶೂನ್ಯ);
ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_x86(ಶೂನ್ಯ);
ಪೂರ್ಣಾಙ್ಕ ff_get_cpu_flags_loongarch(ಶೂನ್ಯ);

size_t ff_get_cpu_max_align_mips(ಶೂನ್ಯ);
size_t ff_get_cpu_max_align_aarch64(ಶೂನ್ಯ);
size_t ff_get_cpu_max_align_arm(ಶೂನ್ಯ);
size_t ff_get_cpu_max_align_ppc(ಶೂನ್ಯ);
size_t ff_get_cpu_max_align_wasm(ಶೂನ್ಯ);
size_t ff_get_cpu_max_align_x86(ಶೂನ್ಯ);
size_t ff_get_cpu_max_align_loongarch(ಶೂನ್ಯ);

unsigned long ff_getauxval(unsigned long type);

#endif /* AVUTIL_CPU_INTERNAL_H */

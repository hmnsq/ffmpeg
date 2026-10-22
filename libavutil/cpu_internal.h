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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_CPU_اندروني_H
#وصف_ڪريو AVUTIL_CPU_اندروني_H

#ضمن "config.h"

#ضمن "cpu.h"

#وصف_ڪريو CPUEXT_SUFFIX(flags, suffix, cpuext)                            \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext))

#وصف_ڪريو CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     !((flags) & AV_CPU_FLAG_ ## slow_cpuext ## SLOW))

#وصف_ڪريو CPUEXT_SUFFIX_SLOW(flags, suffix, cpuext)                       \
    (HAVE_ ## cpuext ## suffix &&                                       \
     ((flags) & (AV_CPU_FLAG_ ## cpuext | AV_CPU_FLAG_ ## cpuext ## SLOW)))

#وصف_ڪريو CPUEXT_SUFFIX_SLOW2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     ((flags) & (AV_CPU_FLAG_ ## slow_cpuext | AV_CPU_FLAG_ ## slow_cpuext ## SLOW)))

#وصف_ڪريو CPUEXT_SUFFIX_FAST(flags, suffix, cpuext) CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, cpuext)

#وصف_ڪريو CPUEXT(flags, cpuext) CPUEXT_SUFFIX(flags, , cpuext)
#وصف_ڪريو CPUEXT_FAST(flags, cpuext) CPUEXT_SUFFIX_FAST(flags, , cpuext)
#وصف_ڪريو CPUEXT_SLOW(flags, cpuext) CPUEXT_SUFFIX_SLOW(flags, , cpuext)

صحيح ff_get_cpu_flags_mips(فراغ);
صحيح ff_get_cpu_flags_aarch64(فراغ);
صحيح ff_get_cpu_flags_arm(فراغ);
صحيح ff_get_cpu_flags_ppc(فراغ);
صحيح ff_get_cpu_flags_riscv(فراغ);
صحيح ff_get_cpu_flags_wasm(فراغ);
صحيح ff_get_cpu_flags_x86(فراغ);
صحيح ff_get_cpu_flags_loongarch(فراغ);

size_t ff_get_cpu_max_align_mips(فراغ);
size_t ff_get_cpu_max_align_aarch64(فراغ);
size_t ff_get_cpu_max_align_arm(فراغ);
size_t ff_get_cpu_max_align_ppc(فراغ);
size_t ff_get_cpu_max_align_wasm(فراغ);
size_t ff_get_cpu_max_align_x86(فراغ);
size_t ff_get_cpu_max_align_loongarch(فراغ);

بنانشان ڊگهو ff_getauxval(بنانشان ڊگهو type);

#جيڪڏهن_پورو /* AVUTIL_CPU_INTERNAL_H */

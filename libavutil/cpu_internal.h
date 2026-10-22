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

#جے_بنا_تعریف AVUTIL_CPU_اندرونی_H
#تعریف_کرو AVUTIL_CPU_اندرونی_H

#ضمن "config.h"

#ضمن "cpu.h"

#تعریف_کرو CPUEXT_SUFFIX(flags, suffix, cpuext)                            \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext))

#تعریف_کرو CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     !((flags) & AV_CPU_FLAG_ ## slow_cpuext ## SLOW))

#تعریف_کرو CPUEXT_SUFFIX_SLOW(flags, suffix, cpuext)                       \
    (HAVE_ ## cpuext ## suffix &&                                       \
     ((flags) & (AV_CPU_FLAG_ ## cpuext | AV_CPU_FLAG_ ## cpuext ## SLOW)))

#تعریف_کرو CPUEXT_SUFFIX_SLOW2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     ((flags) & (AV_CPU_FLAG_ ## slow_cpuext | AV_CPU_FLAG_ ## slow_cpuext ## SLOW)))

#تعریف_کرو CPUEXT_SUFFIX_FAST(flags, suffix, cpuext) CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, cpuext)

#تعریف_کرو CPUEXT(flags, cpuext) CPUEXT_SUFFIX(flags, , cpuext)
#تعریف_کرو CPUEXT_FAST(flags, cpuext) CPUEXT_SUFFIX_FAST(flags, , cpuext)
#تعریف_کرو CPUEXT_SLOW(flags, cpuext) CPUEXT_SUFFIX_SLOW(flags, , cpuext)

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

بنانشانی لما ff_getauxval(بنانشانی لما type);

#جے_انت /* AVUTIL_CPU_INTERNAL_H */

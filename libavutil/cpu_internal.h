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

#اگر_غیر_تعریف_شدہ AVUTIL_CPU_اندرونی_H
#تعریف_کرو AVUTIL_CPU_اندرونی_H

#شامل "config.h"

#شامل "cpu.h"

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

صحیح ff_get_cpu_flags_mips(خالی);
صحیح ff_get_cpu_flags_aarch64(خالی);
صحیح ff_get_cpu_flags_arm(خالی);
صحیح ff_get_cpu_flags_ppc(خالی);
صحیح ff_get_cpu_flags_riscv(خالی);
صحیح ff_get_cpu_flags_wasm(خالی);
صحیح ff_get_cpu_flags_x86(خالی);
صحیح ff_get_cpu_flags_loongarch(خالی);

size_t ff_get_cpu_max_align_mips(خالی);
size_t ff_get_cpu_max_align_aarch64(خالی);
size_t ff_get_cpu_max_align_arm(خالی);
size_t ff_get_cpu_max_align_ppc(خالی);
size_t ff_get_cpu_max_align_wasm(خالی);
size_t ff_get_cpu_max_align_x86(خالی);
size_t ff_get_cpu_max_align_loongarch(خالی);

غیرعلامتی طویل ff_getauxval(غیرعلامتی طویل type);

#اگر_ختم /* AVUTIL_CPU_INTERNAL_H */

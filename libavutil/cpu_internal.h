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

#यदि_अपरिभाषितम् AVUTIL_CPU_आन्तरिकम्_H
#परिभाषय AVUTIL_CPU_आन्तरिकम्_H

#अन्तर्भाव "config.h"

#अन्तर्भाव "cpu.h"

#परिभाषय CPUEXT_SUFFIX(flags, suffix, cpuext)                            \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext))

#परिभाषय CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     !((flags) & AV_CPU_FLAG_ ## slow_cpuext ## SLOW))

#परिभाषय CPUEXT_SUFFIX_SLOW(flags, suffix, cpuext)                       \
    (HAVE_ ## cpuext ## suffix &&                                       \
     ((flags) & (AV_CPU_FLAG_ ## cpuext | AV_CPU_FLAG_ ## cpuext ## SLOW)))

#परिभाषय CPUEXT_SUFFIX_SLOW2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     ((flags) & (AV_CPU_FLAG_ ## slow_cpuext | AV_CPU_FLAG_ ## slow_cpuext ## SLOW)))

#परिभाषय CPUEXT_SUFFIX_FAST(flags, suffix, cpuext) CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, cpuext)

#परिभाषय CPUEXT(flags, cpuext) CPUEXT_SUFFIX(flags, , cpuext)
#परिभाषय CPUEXT_FAST(flags, cpuext) CPUEXT_SUFFIX_FAST(flags, , cpuext)
#परिभाषय CPUEXT_SLOW(flags, cpuext) CPUEXT_SUFFIX_SLOW(flags, , cpuext)

पूर्णाङ्क ff_get_cpu_flags_mips(शून्य);
पूर्णाङ्क ff_get_cpu_flags_aarch64(शून्य);
पूर्णाङ्क ff_get_cpu_flags_arm(शून्य);
पूर्णाङ्क ff_get_cpu_flags_ppc(शून्य);
पूर्णाङ्क ff_get_cpu_flags_riscv(शून्य);
पूर्णाङ्क ff_get_cpu_flags_wasm(शून्य);
पूर्णाङ्क ff_get_cpu_flags_x86(शून्य);
पूर्णाङ्क ff_get_cpu_flags_loongarch(शून्य);

size_t ff_get_cpu_max_align_mips(शून्य);
size_t ff_get_cpu_max_align_aarch64(शून्य);
size_t ff_get_cpu_max_align_arm(शून्य);
size_t ff_get_cpu_max_align_ppc(शून्य);
size_t ff_get_cpu_max_align_wasm(शून्य);
size_t ff_get_cpu_max_align_x86(शून्य);
size_t ff_get_cpu_max_align_loongarch(शून्य);

अचिह्नित दीर्घ ff_getauxval(अचिह्नित दीर्घ type);

#यदि_अन्तः /* AVUTIL_CPU_INTERNAL_H */

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

#अगर_अघोषित AVUTIL_CPU_INTERNAL_H
#घोषणा AVUTIL_CPU_INTERNAL_H

#समावेश "config.h"

#समावेश "cpu.h"

#घोषणा CPUEXT_SUFFIX(flags, suffix, cpuext)                            \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext))

#घोषणा CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     !((flags) & AV_CPU_FLAG_ ## slow_cpuext ## SLOW))

#घोषणा CPUEXT_SUFFIX_SLOW(flags, suffix, cpuext)                       \
    (HAVE_ ## cpuext ## suffix &&                                       \
     ((flags) & (AV_CPU_FLAG_ ## cpuext | AV_CPU_FLAG_ ## cpuext ## SLOW)))

#घोषणा CPUEXT_SUFFIX_SLOW2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     ((flags) & (AV_CPU_FLAG_ ## slow_cpuext | AV_CPU_FLAG_ ## slow_cpuext ## SLOW)))

#घोषणा CPUEXT_SUFFIX_FAST(flags, suffix, cpuext) CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, cpuext)

#घोषणा CPUEXT(flags, cpuext) CPUEXT_SUFFIX(flags, , cpuext)
#घोषणा CPUEXT_FAST(flags, cpuext) CPUEXT_SUFFIX_FAST(flags, , cpuext)
#घोषणा CPUEXT_SLOW(flags, cpuext) CPUEXT_SUFFIX_SLOW(flags, , cpuext)

पूर्णांक ff_get_cpu_flags_mips(व्योम);
पूर्णांक ff_get_cpu_flags_aarch64(व्योम);
पूर्णांक ff_get_cpu_flags_arm(व्योम);
पूर्णांक ff_get_cpu_flags_ppc(व्योम);
पूर्णांक ff_get_cpu_flags_riscv(व्योम);
पूर्णांक ff_get_cpu_flags_wasm(व्योम);
पूर्णांक ff_get_cpu_flags_x86(व्योम);
पूर्णांक ff_get_cpu_flags_loongarch(व्योम);

माप_प्रकार ff_get_cpu_max_align_mips(व्योम);
माप_प्रकार ff_get_cpu_max_align_aarch64(व्योम);
माप_प्रकार ff_get_cpu_max_align_arm(व्योम);
माप_प्रकार ff_get_cpu_max_align_ppc(व्योम);
माप_प्रकार ff_get_cpu_max_align_wasm(व्योम);
माप_प्रकार ff_get_cpu_max_align_x86(व्योम);
माप_प्रकार ff_get_cpu_max_align_loongarch(व्योम);

अचिन्हित दीर्घ ff_getauxval(अचिन्हित दीर्घ type);

#पूर्ण_अगर /* AVUTIL_CPU_INTERNAL_H */

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

#నిర్వచితం_కాకపోతే AVUTIL_CPU_అంతర్గత_H
#నిర్వచించు AVUTIL_CPU_అంతర్గత_H

#అన్తర్భావ "config.h"

#అన్తర్భావ "cpu.h"

#నిర్వచించు CPUEXT_SUFFIX(flags, suffix, cpuext)                            \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext))

#నిర్వచించు CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     !((flags) & AV_CPU_FLAG_ ## slow_cpuext ## SLOW))

#నిర్వచించు CPUEXT_SUFFIX_SLOW(flags, suffix, cpuext)                       \
    (HAVE_ ## cpuext ## suffix &&                                       \
     ((flags) & (AV_CPU_FLAG_ ## cpuext | AV_CPU_FLAG_ ## cpuext ## SLOW)))

#నిర్వచించు CPUEXT_SUFFIX_SLOW2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     ((flags) & (AV_CPU_FLAG_ ## slow_cpuext | AV_CPU_FLAG_ ## slow_cpuext ## SLOW)))

#నిర్వచించు CPUEXT_SUFFIX_FAST(flags, suffix, cpuext) CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, cpuext)

#నిర్వచించు CPUEXT(flags, cpuext) CPUEXT_SUFFIX(flags, , cpuext)
#నిర్వచించు CPUEXT_FAST(flags, cpuext) CPUEXT_SUFFIX_FAST(flags, , cpuext)
#నిర్వచించు CPUEXT_SLOW(flags, cpuext) CPUEXT_SUFFIX_SLOW(flags, , cpuext)

పూర్ణాంకం ff_get_cpu_flags_mips(శూన్య);
పూర్ణాంకం ff_get_cpu_flags_aarch64(శూన్య);
పూర్ణాంకం ff_get_cpu_flags_arm(శూన్య);
పూర్ణాంకం ff_get_cpu_flags_ppc(శూన్య);
పూర్ణాంకం ff_get_cpu_flags_riscv(శూన్య);
పూర్ణాంకం ff_get_cpu_flags_wasm(శూన్య);
పూర్ణాంకం ff_get_cpu_flags_x86(శూన్య);
పూర్ణాంకం ff_get_cpu_flags_loongarch(శూన్య);

size_t ff_get_cpu_max_align_mips(శూన్య);
size_t ff_get_cpu_max_align_aarch64(శూన్య);
size_t ff_get_cpu_max_align_arm(శూన్య);
size_t ff_get_cpu_max_align_ppc(శూన్య);
size_t ff_get_cpu_max_align_wasm(శూన్య);
size_t ff_get_cpu_max_align_x86(శూన్య);
size_t ff_get_cpu_max_align_loongarch(శూన్య);

గుర్తులేని దీర్ఘ ff_getauxval(గుర్తులేని దీర్ఘ type);

#అయితే_ముగింపు /* AVUTIL_CPU_INTERNAL_H */

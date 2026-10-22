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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_CPU_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_CPU_ਅੰਦਰੂਨੀ_H

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPUEXT_SUFFIX(flags, suffix, cpuext)                            \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     !((flags) & AV_CPU_FLAG_ ## slow_cpuext ## SLOW))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPUEXT_SUFFIX_SLOW(flags, suffix, cpuext)                       \
    (HAVE_ ## cpuext ## suffix &&                                       \
     ((flags) & (AV_CPU_FLAG_ ## cpuext | AV_CPU_FLAG_ ## cpuext ## SLOW)))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPUEXT_SUFFIX_SLOW2(flags, suffix, cpuext, slow_cpuext)         \
    (HAVE_ ## cpuext ## suffix && ((flags) & AV_CPU_FLAG_ ## cpuext) && \
     ((flags) & (AV_CPU_FLAG_ ## slow_cpuext | AV_CPU_FLAG_ ## slow_cpuext ## SLOW)))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPUEXT_SUFFIX_FAST(flags, suffix, cpuext) CPUEXT_SUFFIX_FAST2(flags, suffix, cpuext, cpuext)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPUEXT(flags, cpuext) CPUEXT_SUFFIX(flags, , cpuext)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPUEXT_FAST(flags, cpuext) CPUEXT_SUFFIX_FAST(flags, , cpuext)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPUEXT_SLOW(flags, cpuext) CPUEXT_SUFFIX_SLOW(flags, , cpuext)

ਪੂਰਨ ff_get_cpu_flags_mips(ਖਾਲੀ);
ਪੂਰਨ ff_get_cpu_flags_aarch64(ਖਾਲੀ);
ਪੂਰਨ ff_get_cpu_flags_arm(ਖਾਲੀ);
ਪੂਰਨ ff_get_cpu_flags_ppc(ਖਾਲੀ);
ਪੂਰਨ ff_get_cpu_flags_riscv(ਖਾਲੀ);
ਪੂਰਨ ff_get_cpu_flags_wasm(ਖਾਲੀ);
ਪੂਰਨ ff_get_cpu_flags_x86(ਖਾਲੀ);
ਪੂਰਨ ff_get_cpu_flags_loongarch(ਖਾਲੀ);

size_t ff_get_cpu_max_align_mips(ਖਾਲੀ);
size_t ff_get_cpu_max_align_aarch64(ਖਾਲੀ);
size_t ff_get_cpu_max_align_arm(ਖਾਲੀ);
size_t ff_get_cpu_max_align_ppc(ਖਾਲੀ);
size_t ff_get_cpu_max_align_wasm(ਖਾਲੀ);
size_t ff_get_cpu_max_align_x86(ਖਾਲੀ);
size_t ff_get_cpu_max_align_loongarch(ਖਾਲੀ);

ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ff_getauxval(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ type);

#ਜੇ_ਅੰਤ /* AVUTIL_CPU_INTERNAL_H */

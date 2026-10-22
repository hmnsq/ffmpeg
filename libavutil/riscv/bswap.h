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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_RISCV_BSWAP_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_RISCV_BSWAP_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "libavutil/attributes.h"
#ಅನ್ತರ್ಭಾವ "libavutil/riscv/cpu.h"

#ಆದರೆ defined (__GNUC__) || defined (__clang__)
#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap16 __builtin_bswap16

ಸ್ಥಿರ av_always_inline av_const uint32_t av_bswap32_rv(uint32_t x)
{
#ಆದರೆ HAVE_RV && !defined(__riscv_zbb)
    ಆದರೆ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), 1)) {
        uintptr_t y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "rev8    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ಹಿಂತಿರುಗಿ y >> (__riscv_xlen - 32);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ __builtin_bswap32(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap32 av_bswap32_rv

#ಆದರೆ __riscv_xlen >= 64
ಸ್ಥಿರ av_always_inline av_const uint64_t av_bswap64_rv(uint64_t x)
{
#ಆದರೆ HAVE_RV && !defined(__riscv_zbb)
    ಆದರೆ (!__builtin_constant_p(x) &&
        __builtin_expect(ff_rv_zbb_support(), 1)) {
        uintptr_t y;

        __asm__ (
            ".option push\n"
            ".option arch, +zbb\n"
            "rev8    %0, %1\n"
            ".option pop" : "=r" (y) : "r" (x));
        ಹಿಂತಿರುಗಿ y >> (__riscv_xlen - 64);
    }
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ __builtin_bswap64(x);
}
#ವ್ಯಾಖ್ಯಾನಿಸು av_bswap64 av_bswap64_rv
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_RISCV_BSWAP_H */

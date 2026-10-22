/*
 * Loongson SIMD utils
 *
 * Copyright (c) 2016 Loongson Technology Corporation Limited
 * Copyright (c) 2016 Zhou Xiaoyong <zhouxiaoyong@loongson.cn>
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_MIPS_MMIUTILS_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_MIPS_MMIUTILS_H

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ "libavutil/mem_internal.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mips/asmdefs.h"

#ಆದರೆ !HAVE_LOONGSON_MMI_MNEMONICS
/* GNU binutils lacks Loongson's names for these MMI instructions */
__asm__(".macro pxor  d, s, t\n\txor  \\d, \\s, \\t\n\t.endm\n"
        ".macro pand  d, s, t\n\tand  \\d, \\s, \\t\n\t.endm\n"
        ".macro por   d, s, t\n\tor   \\d, \\s, \\t\n\t.endm\n"
        ".macro pnor  d, s, t\n\tnor  \\d, \\s, \\t\n\t.endm\n"
        ".macro ssrld d, s, t\n\tdsrl \\d, \\s, \\t\n\t.endm\n"
        ".macro sslld d, s, t\n\tdsll \\d, \\s, \\t\n\t.endm\n");
#ಆದರೆ_ಅಂತ್ಯ

/*
 * These were used to define temporary registers for MMI marcos
 * however now we're using $at. They're theoretically unnecessary
 * but just leave them here to avoid mess.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು DECLARE_VAR_LOW32
#ವ್ಯಾಖ್ಯಾನಿಸು RESTRICT_ASM_LOW32
#ವ್ಯಾಖ್ಯಾನಿಸು DECLARE_VAR_ALL64
#ವ್ಯಾಖ್ಯಾನಿಸು RESTRICT_ASM_ALL64
#ವ್ಯಾಖ್ಯಾನಿಸು DECLARE_VAR_ADDRT
#ವ್ಯಾಖ್ಯಾನಿಸು RESTRICT_ASM_ADDRT

#ಆದರೆ HAVE_LOONGSON2

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LWX(reg, addr, stride, bias)                                    \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    "lw         "#reg",     "#bias"($at)                       \n\t"   \
    ".set at                                                   \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SWX(reg, addr, stride, bias)                                    \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    "sw         "#reg",     "#bias"($at)                       \n\t"   \
    ".set at                                                   \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LDX(reg, addr, stride, bias)                                    \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    "ld         "#reg",     "#bias"($at)                       \n\t"   \
    ".set at                                                   \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SDX(reg, addr, stride, bias)                                    \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    "sd         "#reg",     "#bias"($at)                       \n\t"   \
    ".set at                                                   \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LWC1(fp, addr, bias)                                            \
    "lwc1       "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_ULWC1(fp, addr, bias)                                           \
    ".set noat                                                      \n\t"   \
    "ulw        $at,   "#bias"("#addr")                             \n\t"   \
    "mtc1       $at,   "#fp"                                        \n\t"   \
    ".set at                                                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LWXC1(fp, addr, stride, bias)                                   \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    MMI_LWC1(fp, $at, bias)                                            \
    ".set at                                                   \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SWC1(fp, addr, bias)                                            \
    "swc1       "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_USWC1(fp, addr, bias)                                           \
    ".set noat                                                      \n\t"   \
    "mfc1       $at,   "#fp"                                        \n\t"   \
    "usw        $at,   "#bias"("#addr")                             \n\t"   \
    ".set at                                                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SWXC1(fp, addr, stride, bias)                                   \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    MMI_SWC1(fp, $at, bias)                                           \
    ".set at                                                   \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LDC1(fp, addr, bias)                                            \
    "ldc1       "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_ULDC1(fp, addr, bias)                                           \
    ".set noat                                                      \n\t"   \
    "uld        $at,   "#bias"("#addr")                             \n\t"   \
    "dmtc1      $at,   "#fp"                                        \n\t"   \
    ".set at                                                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LDXC1(fp, addr, stride, bias)                                   \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    MMI_LDC1(fp, $at, bias)                                           \
    ".set at                                                   \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SDC1(fp, addr, bias)                                            \
    "sdc1       "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_USDC1(fp, addr, bias)                                           \
    ".set noat                                                      \n\t"   \
    "dmfc1      $at,   "#fp"                                        \n\t"   \
    "usd        $at,   "#bias"("#addr")                             \n\t"   \
    ".set at                                                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SDXC1(fp, addr, stride, bias)                                   \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    MMI_SDC1(fp, $at, bias)                                            \
    ".set at                                                   \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LQ(reg1, reg2, addr, bias)                                      \
    "ld         "#reg1",    "#bias"("#addr")                        \n\t"   \
    "ld         "#reg2",  8+"#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SQ(reg1, reg2, addr, bias)                                      \
    "sd         "#reg1",    "#bias"("#addr")                        \n\t"   \
    "sd         "#reg2",  8+"#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LQC1(fp1, fp2, addr, bias)                                      \
    "ldc1       "#fp1",     "#bias"("#addr")                        \n\t"   \
    "ldc1       "#fp2",   8+"#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SQC1(fp1, fp2, addr, bias)                                      \
    "sdc1       "#fp1",     "#bias"("#addr")                        \n\t"   \
    "sdc1       "#fp2",   8+"#bias"("#addr")                        \n\t"

#ಅಥವಾಆದರೆ HAVE_LOONGSON3 /* !HAVE_LOONGSON2 */

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LWX(reg, addr, stride, bias)                                    \
    "gslwx      "#reg",     "#bias"("#addr", "#stride")             \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SWX(reg, addr, stride, bias)                                    \
    "gsswx      "#reg",     "#bias"("#addr", "#stride")             \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LDX(reg, addr, stride, bias)                                    \
    "gsldx      "#reg",     "#bias"("#addr", "#stride")             \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SDX(reg, addr, stride, bias)                                    \
    "gssdx      "#reg",     "#bias"("#addr", "#stride")             \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LWC1(fp, addr, bias)                                            \
    "lwc1       "#fp",      "#bias"("#addr")                        \n\t"

#ಆದರೆ _MIPS_SIM == _ABIO32 /* workaround for 3A2000 gslwlc1 bug */

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LWLRC1(fp, addr, bias, off)                                     \
    ".set noat                                                 \n\t"   \
    "lwl        $at,   "#bias"+"#off"("#addr")                 \n\t"   \
    "lwr        $at,   "#bias"("#addr")                        \n\t"   \
    "mtc1       $at,   "#fp"                                   \n\t"   \
    ".set at                                                   \n\t"

#ಇಲ್ಲದಿದ್ದರೆ /* _MIPS_SIM != _ABIO32 */

#ವ್ಯಾಖ್ಯಾನಿಸು DECLARE_VAR_LOW32
#ವ್ಯಾಖ್ಯಾನಿಸು RESTRICT_ASM_LOW32

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_ULWC1(fp, addr, bias)                                           \
    "gslwlc1    "#fp",    3+"#bias"("#addr")                        \n\t"   \
    "gslwrc1    "#fp",      "#bias"("#addr")                        \n\t"

#ಆದರೆ_ಅಂತ್ಯ /* _MIPS_SIM != _ABIO32 */

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LWXC1(fp, addr, stride, bias)                                   \
    "gslwxc1    "#fp",      "#bias"("#addr", "#stride")             \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SWC1(fp, addr, bias)                                            \
    "swc1       "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_USWC1(fp, addr, bias)                                           \
    "gsswlc1    "#fp",    3+"#bias"("#addr")                        \n\t"   \
    "gsswrc1    "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SWXC1(fp, addr, stride, bias)                                   \
    "gsswxc1    "#fp",      "#bias"("#addr", "#stride")             \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LDC1(fp, addr, bias)                                            \
    "ldc1       "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_ULDC1(fp, addr, bias)                                           \
    "gsldlc1    "#fp",    7+"#bias"("#addr")                        \n\t"   \
    "gsldrc1    "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LDXC1(fp, addr, stride, bias)                                   \
    "gsldxc1    "#fp",      "#bias"("#addr", "#stride")             \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SDC1(fp, addr, bias)                                            \
    "sdc1       "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_USDC1(fp, addr, bias)                                           \
    "gssdlc1    "#fp",    7+"#bias"("#addr")                        \n\t"   \
    "gssdrc1    "#fp",      "#bias"("#addr")                        \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SDXC1(fp, addr, stride, bias)                                   \
    "gssdxc1    "#fp",      "#bias"("#addr", "#stride")             \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LQ(reg1, reg2, addr, bias)                                      \
    "gslq       "#reg1",    "#reg2",     "#bias"("#addr")           \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SQ(reg1, reg2, addr, bias)                                      \
    "gssq       "#reg1",    "#reg2",     "#bias"("#addr")           \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_LQC1(fp1, fp2, addr, bias)                                      \
    "gslqc1     "#fp1",     "#fp2",     "#bias"("#addr")            \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು MMI_SQC1(fp1, fp2, addr, bias)                                      \
    "gssqc1     "#fp1",     "#fp2",     "#bias"("#addr")            \n\t"

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_LOONGSON2 */

/**
 * Backup saved registers
 * We're not using compiler's clobber list as it's not smart enough
 * to take advantage of quad word load/store.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು BACKUP_REG \
  LOCAL_ALIGNED_16(ದ್ವಿಗುಣ, ತಾತ್ಕಾಲಿಕ_backup_reg, [8]);               \
  ಆದರೆ (_MIPS_SIM == _ABI64)                                      \
    __asm__ ಅಸ್ಥಿರ (                                          \
      MMI_SQC1($f25, $f24, %[ತಾತ್ಕಾಲಿಕ], 0x00)                       \
      MMI_SQC1($f27, $f26, %[ತಾತ್ಕಾಲಿಕ], 0x10)                       \
      MMI_SQC1($f29, $f28, %[ತಾತ್ಕಾಲಿಕ], 0x20)                       \
      MMI_SQC1($f31, $f30, %[ತಾತ್ಕಾಲಿಕ], 0x30)                       \
      :                                                         \
      : [ತಾತ್ಕಾಲಿಕ]"r"(ತಾತ್ಕಾಲಿಕ_backup_reg)                              \
      : "memory"                                                \
    );                                                          \
  ಇಲ್ಲದಿದ್ದರೆ                                                          \
    __asm__ ಅಸ್ಥಿರ (                                          \
      MMI_SQC1($f22, $f20, %[ತಾತ್ಕಾಲಿಕ], 0x10)                       \
      MMI_SQC1($f26, $f24, %[ತಾತ್ಕಾಲಿಕ], 0x10)                       \
      MMI_SQC1($f30, $f28, %[ತಾತ್ಕಾಲಿಕ], 0x20)                       \
      :                                                         \
      : [ತಾತ್ಕಾಲಿಕ]"r"(ತಾತ್ಕಾಲಿಕ_backup_reg)                              \
      : "memory"                                                \
    );

/**
 * recover register
 */
#ವ್ಯಾಖ್ಯಾನಿಸು RECOVER_REG \
  ಆದರೆ (_MIPS_SIM == _ABI64)                                      \
    __asm__ ಅಸ್ಥಿರ (                                          \
      MMI_LQC1($f25, $f24, %[ತಾತ್ಕಾಲಿಕ], 0x00)                       \
      MMI_LQC1($f27, $f26, %[ತಾತ್ಕಾಲಿಕ], 0x10)                       \
      MMI_LQC1($f29, $f28, %[ತಾತ್ಕಾಲಿಕ], 0x20)                       \
      MMI_LQC1($f31, $f30, %[ತಾತ್ಕಾಲಿಕ], 0x30)                       \
      :                                                         \
      : [ತಾತ್ಕಾಲಿಕ]"r"(ತಾತ್ಕಾಲಿಕ_backup_reg)                              \
      : "memory"                                                \
    );                                                          \
  ಇಲ್ಲದಿದ್ದರೆ                                                          \
    __asm__ ಅಸ್ಥಿರ (                                          \
      MMI_LQC1($f22, $f20, %[ತಾತ್ಕಾಲಿಕ], 0x10)                       \
      MMI_LQC1($f26, $f24, %[ತಾತ್ಕಾಲಿಕ], 0x10)                       \
      MMI_LQC1($f30, $f28, %[ತಾತ್ಕಾಲಿಕ], 0x20)                       \
      :                                                         \
      : [ತಾತ್ಕಾಲಿಕ]"r"(ತಾತ್ಕಾಲಿಕ_backup_reg)                              \
      : "memory"                                                \
    );

/**
 * brief: Transpose 2X2 word packaged data.
 * fr_i0, fr_i1: src
 * fr_o0, fr_o1: dst
 */
#ವ್ಯಾಖ್ಯಾನಿಸು TRANSPOSE_2W(fr_i0, fr_i1, fr_o0, fr_o1)                          \
        "punpcklwd  "#fr_o0",   "#fr_i0",   "#fr_i1"                \n\t" \
        "punpckhwd  "#fr_o1",   "#fr_i0",   "#fr_i1"                \n\t"

/**
 * brief: Transpose 4X4 half word packaged data.
 * fr_i0, fr_i1, fr_i2, fr_i3: src & dst
 * fr_t0, fr_t1, fr_t2, fr_t3: temporary register
 */
#ವ್ಯಾಖ್ಯಾನಿಸು TRANSPOSE_4H(fr_i0, fr_i1, fr_i2, fr_i3,                          \
                     fr_t0, fr_t1, fr_t2, fr_t3)                          \
        "punpcklhw  "#fr_t0",   "#fr_i0",   "#fr_i1"                \n\t" \
        "punpckhhw  "#fr_t1",   "#fr_i0",   "#fr_i1"                \n\t" \
        "punpcklhw  "#fr_t2",   "#fr_i2",   "#fr_i3"                \n\t" \
        "punpckhhw  "#fr_t3",   "#fr_i2",   "#fr_i3"                \n\t" \
        "punpcklwd  "#fr_i0",   "#fr_t0",   "#fr_t2"                \n\t" \
        "punpckhwd  "#fr_i1",   "#fr_t0",   "#fr_t2"                \n\t" \
        "punpcklwd  "#fr_i2",   "#fr_t1",   "#fr_t3"                \n\t" \
        "punpckhwd  "#fr_i3",   "#fr_t1",   "#fr_t3"                \n\t"

/**
 * brief: Transpose 8x8 byte packaged data.
 * fr_i0~i7: src & dst
 * fr_t0~t3: temporary register
 */
#ವ್ಯಾಖ್ಯಾನಿಸು TRANSPOSE_8B(fr_i0, fr_i1, fr_i2, fr_i3, fr_i4, fr_i5,            \
                     fr_i6, fr_i7, fr_t0, fr_t1, fr_t2, fr_t3)            \
        "punpcklbh  "#fr_t0",   "#fr_i0",   "#fr_i1"                \n\t" \
        "punpckhbh  "#fr_t1",   "#fr_i0",   "#fr_i1"                \n\t" \
        "punpcklbh  "#fr_t2",   "#fr_i2",   "#fr_i3"                \n\t" \
        "punpckhbh  "#fr_t3",   "#fr_i2",   "#fr_i3"                \n\t" \
        "punpcklbh  "#fr_i0",   "#fr_i4",   "#fr_i5"                \n\t" \
        "punpckhbh  "#fr_i1",   "#fr_i4",   "#fr_i5"                \n\t" \
        "punpcklbh  "#fr_i2",   "#fr_i6",   "#fr_i7"                \n\t" \
        "punpckhbh  "#fr_i3",   "#fr_i6",   "#fr_i7"                \n\t" \
        "punpcklhw  "#fr_i4",   "#fr_t0",   "#fr_t2"                \n\t" \
        "punpckhhw  "#fr_i5",   "#fr_t0",   "#fr_t2"                \n\t" \
        "punpcklhw  "#fr_i6",   "#fr_t1",   "#fr_t3"                \n\t" \
        "punpckhhw  "#fr_i7",   "#fr_t1",   "#fr_t3"                \n\t" \
        "punpcklhw  "#fr_t0",   "#fr_i0",   "#fr_i2"                \n\t" \
        "punpckhhw  "#fr_t1",   "#fr_i0",   "#fr_i2"                \n\t" \
        "punpcklhw  "#fr_t2",   "#fr_i1",   "#fr_i3"                \n\t" \
        "punpckhhw  "#fr_t3",   "#fr_i1",   "#fr_i3"                \n\t" \
        "punpcklwd  "#fr_i0",   "#fr_i4",   "#fr_t0"                \n\t" \
        "punpckhwd  "#fr_i1",   "#fr_i4",   "#fr_t0"                \n\t" \
        "punpcklwd  "#fr_i2",   "#fr_i5",   "#fr_t1"                \n\t" \
        "punpckhwd  "#fr_i3",   "#fr_i5",   "#fr_t1"                \n\t" \
        "punpcklwd  "#fr_i4",   "#fr_i6",   "#fr_t2"                \n\t" \
        "punpckhwd  "#fr_i5",   "#fr_i6",   "#fr_t2"                \n\t" \
        "punpcklwd  "#fr_i6",   "#fr_i7",   "#fr_t3"                \n\t" \
        "punpckhwd  "#fr_i7",   "#fr_i7",   "#fr_t3"                \n\t"

/**
 * brief: Parallel SRA for 8 byte packaged data.
 * fr_i0: src
 * fr_i1: SRA number(SRAB number + 8)
 * fr_t0, fr_t1: temporary register
 * fr_d0: dst
 */
#ವ್ಯಾಖ್ಯಾನಿಸು PSRAB_MMI(fr_i0, fr_i1, fr_t0, fr_t1, fr_d0)                      \
        "punpcklbh    "#fr_t0",   "#fr_t0",   "#fr_i0"              \n\t" \
        "punpckhbh    "#fr_t1",   "#fr_t1",   "#fr_i0"              \n\t" \
        "psrah        "#fr_t0",   "#fr_t0",   "#fr_i1"              \n\t" \
        "psrah        "#fr_t1",   "#fr_t1",   "#fr_i1"              \n\t" \
        "packsshb     "#fr_d0",   "#fr_t0",   "#fr_t1"              \n\t"

/**
 * brief: Parallel SRL for 8 byte packaged data.
 * fr_i0: src
 * fr_i1: SRL number(SRLB number + 8)
 * fr_t0, fr_t1: temporary register
 * fr_d0: dst
 */
#ವ್ಯಾಖ್ಯಾನಿಸು PSRLB_MMI(fr_i0, fr_i1, fr_t0, fr_t1, fr_d0)                      \
        "punpcklbh    "#fr_t0",   "#fr_t0",   "#fr_i0"              \n\t" \
        "punpckhbh    "#fr_t1",   "#fr_t1",   "#fr_i0"              \n\t" \
        "psrlh        "#fr_t0",   "#fr_t0",   "#fr_i1"              \n\t" \
        "psrlh        "#fr_t1",   "#fr_t1",   "#fr_i1"              \n\t" \
        "packsshb     "#fr_d0",   "#fr_t0",   "#fr_t1"              \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು PSRAH_4_MMI(fp1, fp2, fp3, fp4, ಸರಿಸು)                            \
        "psrah      "#fp1",     "#fp1",     "#shift"                \n\t" \
        "psrah      "#fp2",     "#fp2",     "#shift"                \n\t" \
        "psrah      "#fp3",     "#fp3",     "#shift"                \n\t" \
        "psrah      "#fp4",     "#fp4",     "#shift"                \n\t"

#ವ್ಯಾಖ್ಯಾನಿಸು PSRAH_8_MMI(fp1, fp2, fp3, fp4, fp5, fp6, fp7, fp8, ಸರಿಸು)        \
        PSRAH_4_MMI(fp1, fp2, fp3, fp4, ಸರಿಸು)                            \
        PSRAH_4_MMI(fp5, fp6, fp7, fp8, ಸರಿಸು)

/**
 * brief: (((value) + (1 << ((n) - 1))) >> (n))
 * fr_i0: src & dst
 * fr_i1: Operand number
 * fr_t0, fr_t1: temporary FPR
 * gr_t0: temporary GPR
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಸುತ್ತು_POWER_ದ_TWO_MMI(fr_i0, fr_i1, fr_t0, fr_t1, gr_t0)         \
        "li         "#gr_t0",     0x01                              \n\t" \
        "dmtc1      "#gr_t0",     "#fr_t0"                          \n\t" \
        "punpcklwd  "#fr_t0",     "#fr_t0",    "#fr_t0"             \n\t" \
        "psubw      "#fr_t1",     "#fr_i1",    "#fr_t0"             \n\t" \
        "psllw      "#fr_t1",     "#fr_t0",    "#fr_t1"             \n\t" \
        "paddw      "#fr_i0",     "#fr_i0",    "#fr_t1"             \n\t" \
        "psraw      "#fr_i0",     "#fr_i0",    "#fr_i1"             \n\t"

#ಆದರೆ_ಅಂತ್ಯ /* AVUTILS_MIPS_MMIUTILS_H */

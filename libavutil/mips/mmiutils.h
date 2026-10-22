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

#నిర్వచితం_కాకపోతే AVUTIL_MIPS_MMIUTILS_H
#నిర్వచించు AVUTIL_MIPS_MMIUTILS_H

#అన్తర్భావ "config.h"

#అన్తర్భావ "libavutil/mem_internal.h"
#అన్తర్భావ "libavutil/mips/asmdefs.h"

#ఒకవేళ !HAVE_LOONGSON_MMI_MNEMONICS
/* GNU binutils lacks Loongson's names for these MMI instructions */
__asm__(".macro pxor  d, s, t\n\txor  \\d, \\s, \\t\n\t.endm\n"
        ".macro pand  d, s, t\n\tand  \\d, \\s, \\t\n\t.endm\n"
        ".macro por   d, s, t\n\tor   \\d, \\s, \\t\n\t.endm\n"
        ".macro pnor  d, s, t\n\tnor  \\d, \\s, \\t\n\t.endm\n"
        ".macro ssrld d, s, t\n\tdsrl \\d, \\s, \\t\n\t.endm\n"
        ".macro sslld d, s, t\n\tdsll \\d, \\s, \\t\n\t.endm\n");
#అయితే_ముగింపు

/*
 * These were used to define temporary registers for MMI marcos
 * however now we're using $at. They're theoretically unnecessary
 * but just leave them here to avoid mess.
 */
#నిర్వచించు DECLARE_VAR_LOW32
#నిర్వచించు RESTRICT_ASM_LOW32
#నిర్వచించు DECLARE_VAR_ALL64
#నిర్వచించు RESTRICT_ASM_ALL64
#నిర్వచించు DECLARE_VAR_ADDRT
#నిర్వచించు RESTRICT_ASM_ADDRT

#ఒకవేళ HAVE_LOONGSON2

#నిర్వచించు MMI_LWX(reg, addr, stride, bias)                                    \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    "lw         "#reg",     "#bias"($at)                       \n\t"   \
    ".set at                                                   \n\t"

#నిర్వచించు MMI_SWX(reg, addr, stride, bias)                                    \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    "sw         "#reg",     "#bias"($at)                       \n\t"   \
    ".set at                                                   \n\t"

#నిర్వచించు MMI_LDX(reg, addr, stride, bias)                                    \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    "ld         "#reg",     "#bias"($at)                       \n\t"   \
    ".set at                                                   \n\t"

#నిర్వచించు MMI_SDX(reg, addr, stride, bias)                                    \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    "sd         "#reg",     "#bias"($at)                       \n\t"   \
    ".set at                                                   \n\t"

#నిర్వచించు MMI_LWC1(fp, addr, bias)                                            \
    "lwc1       "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_ULWC1(fp, addr, bias)                                           \
    ".set noat                                                      \n\t"   \
    "ulw        $at,   "#bias"("#addr")                             \n\t"   \
    "mtc1       $at,   "#fp"                                        \n\t"   \
    ".set at                                                        \n\t"

#నిర్వచించు MMI_LWXC1(fp, addr, stride, bias)                                   \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    MMI_LWC1(fp, $at, bias)                                            \
    ".set at                                                   \n\t"

#నిర్వచించు MMI_SWC1(fp, addr, bias)                                            \
    "swc1       "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_USWC1(fp, addr, bias)                                           \
    ".set noat                                                      \n\t"   \
    "mfc1       $at,   "#fp"                                        \n\t"   \
    "usw        $at,   "#bias"("#addr")                             \n\t"   \
    ".set at                                                        \n\t"

#నిర్వచించు MMI_SWXC1(fp, addr, stride, bias)                                   \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    MMI_SWC1(fp, $at, bias)                                           \
    ".set at                                                   \n\t"

#నిర్వచించు MMI_LDC1(fp, addr, bias)                                            \
    "ldc1       "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_ULDC1(fp, addr, bias)                                           \
    ".set noat                                                      \n\t"   \
    "uld        $at,   "#bias"("#addr")                             \n\t"   \
    "dmtc1      $at,   "#fp"                                        \n\t"   \
    ".set at                                                        \n\t"

#నిర్వచించు MMI_LDXC1(fp, addr, stride, bias)                                   \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    MMI_LDC1(fp, $at, bias)                                           \
    ".set at                                                   \n\t"

#నిర్వచించు MMI_SDC1(fp, addr, bias)                                            \
    "sdc1       "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_USDC1(fp, addr, bias)                                           \
    ".set noat                                                      \n\t"   \
    "dmfc1      $at,   "#fp"                                        \n\t"   \
    "usd        $at,   "#bias"("#addr")                             \n\t"   \
    ".set at                                                        \n\t"

#నిర్వచించు MMI_SDXC1(fp, addr, stride, bias)                                   \
    ".set noat                                                 \n\t"   \
    PTR_ADDU    "$at,  "#addr",    "#stride"                   \n\t"   \
    MMI_SDC1(fp, $at, bias)                                            \
    ".set at                                                   \n\t"

#నిర్వచించు MMI_LQ(reg1, reg2, addr, bias)                                      \
    "ld         "#reg1",    "#bias"("#addr")                        \n\t"   \
    "ld         "#reg2",  8+"#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_SQ(reg1, reg2, addr, bias)                                      \
    "sd         "#reg1",    "#bias"("#addr")                        \n\t"   \
    "sd         "#reg2",  8+"#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_LQC1(fp1, fp2, addr, bias)                                      \
    "ldc1       "#fp1",     "#bias"("#addr")                        \n\t"   \
    "ldc1       "#fp2",   8+"#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_SQC1(fp1, fp2, addr, bias)                                      \
    "sdc1       "#fp1",     "#bias"("#addr")                        \n\t"   \
    "sdc1       "#fp2",   8+"#bias"("#addr")                        \n\t"

#లేదావేళ HAVE_LOONGSON3 /* !HAVE_LOONGSON2 */

#నిర్వచించు MMI_LWX(reg, addr, stride, bias)                                    \
    "gslwx      "#reg",     "#bias"("#addr", "#stride")             \n\t"

#నిర్వచించు MMI_SWX(reg, addr, stride, bias)                                    \
    "gsswx      "#reg",     "#bias"("#addr", "#stride")             \n\t"

#నిర్వచించు MMI_LDX(reg, addr, stride, bias)                                    \
    "gsldx      "#reg",     "#bias"("#addr", "#stride")             \n\t"

#నిర్వచించు MMI_SDX(reg, addr, stride, bias)                                    \
    "gssdx      "#reg",     "#bias"("#addr", "#stride")             \n\t"

#నిర్వచించు MMI_LWC1(fp, addr, bias)                                            \
    "lwc1       "#fp",      "#bias"("#addr")                        \n\t"

#ఒకవేళ _MIPS_SIM == _ABIO32 /* workaround for 3A2000 gslwlc1 bug */

#నిర్వచించు MMI_LWLRC1(fp, addr, bias, off)                                     \
    ".set noat                                                 \n\t"   \
    "lwl        $at,   "#bias"+"#off"("#addr")                 \n\t"   \
    "lwr        $at,   "#bias"("#addr")                        \n\t"   \
    "mtc1       $at,   "#fp"                                   \n\t"   \
    ".set at                                                   \n\t"

#లేకపోతే /* _MIPS_SIM != _ABIO32 */

#నిర్వచించు DECLARE_VAR_LOW32
#నిర్వచించు RESTRICT_ASM_LOW32

#నిర్వచించు MMI_ULWC1(fp, addr, bias)                                           \
    "gslwlc1    "#fp",    3+"#bias"("#addr")                        \n\t"   \
    "gslwrc1    "#fp",      "#bias"("#addr")                        \n\t"

#అయితే_ముగింపు /* _MIPS_SIM != _ABIO32 */

#నిర్వచించు MMI_LWXC1(fp, addr, stride, bias)                                   \
    "gslwxc1    "#fp",      "#bias"("#addr", "#stride")             \n\t"

#నిర్వచించు MMI_SWC1(fp, addr, bias)                                            \
    "swc1       "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_USWC1(fp, addr, bias)                                           \
    "gsswlc1    "#fp",    3+"#bias"("#addr")                        \n\t"   \
    "gsswrc1    "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_SWXC1(fp, addr, stride, bias)                                   \
    "gsswxc1    "#fp",      "#bias"("#addr", "#stride")             \n\t"

#నిర్వచించు MMI_LDC1(fp, addr, bias)                                            \
    "ldc1       "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_ULDC1(fp, addr, bias)                                           \
    "gsldlc1    "#fp",    7+"#bias"("#addr")                        \n\t"   \
    "gsldrc1    "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_LDXC1(fp, addr, stride, bias)                                   \
    "gsldxc1    "#fp",      "#bias"("#addr", "#stride")             \n\t"

#నిర్వచించు MMI_SDC1(fp, addr, bias)                                            \
    "sdc1       "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_USDC1(fp, addr, bias)                                           \
    "gssdlc1    "#fp",    7+"#bias"("#addr")                        \n\t"   \
    "gssdrc1    "#fp",      "#bias"("#addr")                        \n\t"

#నిర్వచించు MMI_SDXC1(fp, addr, stride, bias)                                   \
    "gssdxc1    "#fp",      "#bias"("#addr", "#stride")             \n\t"

#నిర్వచించు MMI_LQ(reg1, reg2, addr, bias)                                      \
    "gslq       "#reg1",    "#reg2",     "#bias"("#addr")           \n\t"

#నిర్వచించు MMI_SQ(reg1, reg2, addr, bias)                                      \
    "gssq       "#reg1",    "#reg2",     "#bias"("#addr")           \n\t"

#నిర్వచించు MMI_LQC1(fp1, fp2, addr, bias)                                      \
    "gslqc1     "#fp1",     "#fp2",     "#bias"("#addr")            \n\t"

#నిర్వచించు MMI_SQC1(fp1, fp2, addr, bias)                                      \
    "gssqc1     "#fp1",     "#fp2",     "#bias"("#addr")            \n\t"

#అయితే_ముగింపు /* HAVE_LOONGSON2 */

/**
 * Backup saved registers
 * We're not using compiler's clobber list as it's not smart enough
 * to take advantage of quad word load/store.
 */
#నిర్వచించు BACKUP_REG \
  LOCAL_ALIGNED_16(ద్విగుణ, తాత్కాలిక_backup_reg, [8]);               \
  ఒకవేళ (_MIPS_SIM == _ABI64)                                      \
    __asm__ అస్థిర (                                          \
      MMI_SQC1($f25, $f24, %[తాత్కాలిక], 0x00)                       \
      MMI_SQC1($f27, $f26, %[తాత్కాలిక], 0x10)                       \
      MMI_SQC1($f29, $f28, %[తాత్కాలిక], 0x20)                       \
      MMI_SQC1($f31, $f30, %[తాత్కాలిక], 0x30)                       \
      :                                                         \
      : [తాత్కాలిక]"r"(తాత్కాలిక_backup_reg)                              \
      : "memory"                                                \
    );                                                          \
  లేకపోతే                                                          \
    __asm__ అస్థిర (                                          \
      MMI_SQC1($f22, $f20, %[తాత్కాలిక], 0x10)                       \
      MMI_SQC1($f26, $f24, %[తాత్కాలిక], 0x10)                       \
      MMI_SQC1($f30, $f28, %[తాత్కాలిక], 0x20)                       \
      :                                                         \
      : [తాత్కాలిక]"r"(తాత్కాలిక_backup_reg)                              \
      : "memory"                                                \
    );

/**
 * recover register
 */
#నిర్వచించు RECOVER_REG \
  ఒకవేళ (_MIPS_SIM == _ABI64)                                      \
    __asm__ అస్థిర (                                          \
      MMI_LQC1($f25, $f24, %[తాత్కాలిక], 0x00)                       \
      MMI_LQC1($f27, $f26, %[తాత్కాలిక], 0x10)                       \
      MMI_LQC1($f29, $f28, %[తాత్కాలిక], 0x20)                       \
      MMI_LQC1($f31, $f30, %[తాత్కాలిక], 0x30)                       \
      :                                                         \
      : [తాత్కాలిక]"r"(తాత్కాలిక_backup_reg)                              \
      : "memory"                                                \
    );                                                          \
  లేకపోతే                                                          \
    __asm__ అస్థిర (                                          \
      MMI_LQC1($f22, $f20, %[తాత్కాలిక], 0x10)                       \
      MMI_LQC1($f26, $f24, %[తాత్కాలిక], 0x10)                       \
      MMI_LQC1($f30, $f28, %[తాత్కాలిక], 0x20)                       \
      :                                                         \
      : [తాత్కాలిక]"r"(తాత్కాలిక_backup_reg)                              \
      : "memory"                                                \
    );

/**
 * brief: Transpose 2X2 word packaged data.
 * fr_i0, fr_i1: src
 * fr_o0, fr_o1: dst
 */
#నిర్వచించు TRANSPOSE_2W(fr_i0, fr_i1, fr_o0, fr_o1)                          \
        "punpcklwd  "#fr_o0",   "#fr_i0",   "#fr_i1"                \n\t" \
        "punpckhwd  "#fr_o1",   "#fr_i0",   "#fr_i1"                \n\t"

/**
 * brief: Transpose 4X4 half word packaged data.
 * fr_i0, fr_i1, fr_i2, fr_i3: src & dst
 * fr_t0, fr_t1, fr_t2, fr_t3: temporary register
 */
#నిర్వచించు TRANSPOSE_4H(fr_i0, fr_i1, fr_i2, fr_i3,                          \
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
#నిర్వచించు TRANSPOSE_8B(fr_i0, fr_i1, fr_i2, fr_i3, fr_i4, fr_i5,            \
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
#నిర్వచించు PSRAB_MMI(fr_i0, fr_i1, fr_t0, fr_t1, fr_d0)                      \
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
#నిర్వచించు PSRLB_MMI(fr_i0, fr_i1, fr_t0, fr_t1, fr_d0)                      \
        "punpcklbh    "#fr_t0",   "#fr_t0",   "#fr_i0"              \n\t" \
        "punpckhbh    "#fr_t1",   "#fr_t1",   "#fr_i0"              \n\t" \
        "psrlh        "#fr_t0",   "#fr_t0",   "#fr_i1"              \n\t" \
        "psrlh        "#fr_t1",   "#fr_t1",   "#fr_i1"              \n\t" \
        "packsshb     "#fr_d0",   "#fr_t0",   "#fr_t1"              \n\t"

#నిర్వచించు PSRAH_4_MMI(fp1, fp2, fp3, fp4, జరుపు)                            \
        "psrah      "#fp1",     "#fp1",     "#shift"                \n\t" \
        "psrah      "#fp2",     "#fp2",     "#shift"                \n\t" \
        "psrah      "#fp3",     "#fp3",     "#shift"                \n\t" \
        "psrah      "#fp4",     "#fp4",     "#shift"                \n\t"

#నిర్వచించు PSRAH_8_MMI(fp1, fp2, fp3, fp4, fp5, fp6, fp7, fp8, జరుపు)        \
        PSRAH_4_MMI(fp1, fp2, fp3, fp4, జరుపు)                            \
        PSRAH_4_MMI(fp5, fp6, fp7, fp8, జరుపు)

/**
 * brief: (((value) + (1 << ((n) - 1))) >> (n))
 * fr_i0: src & dst
 * fr_i1: Operand number
 * fr_t0, fr_t1: temporary FPR
 * gr_t0: temporary GPR
 */
#నిర్వచించు విడత_POWER_యొక్క_TWO_MMI(fr_i0, fr_i1, fr_t0, fr_t1, gr_t0)         \
        "li         "#gr_t0",     0x01                              \n\t" \
        "dmtc1      "#gr_t0",     "#fr_t0"                          \n\t" \
        "punpcklwd  "#fr_t0",     "#fr_t0",    "#fr_t0"             \n\t" \
        "psubw      "#fr_t1",     "#fr_i1",    "#fr_t0"             \n\t" \
        "psllw      "#fr_t1",     "#fr_t0",    "#fr_t1"             \n\t" \
        "paddw      "#fr_i0",     "#fr_i0",    "#fr_t1"             \n\t" \
        "psraw      "#fr_i0",     "#fr_i0",    "#fr_i1"             \n\t"

#అయితే_ముగింపు /* AVUTILS_MIPS_MMIUTILS_H */

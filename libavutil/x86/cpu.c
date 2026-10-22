/*
 * CPU detection code, extracted from mmx.h
 * (c)1997-99 by H. Dietz and R. Fisher
 * Converted to C and improved by Fabrice Bellard.
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

#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "libavutil/x86/asm.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/x86/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/cpu_internal.h"

#ଯଦି HAVE_X86ASM

#define cpuid(index, eax, ebx, ecx, edx)        \
    ff_cpu_cpuid(index, &eax, &ebx, &ecx, &edx)

#define xgetbv(index, eax, edx)                 \
    ff_cpu_xgetbv(index, &eax, &edx)

#ନଚେତଯଦି HAVE_INLINE_ASM

/* ebx saving is necessary for PIC. gcc seems unable to see it alone */
#define cpuid(index, eax, ebx, ecx, edx)                        \
    __asm__ ଅସ୍ଥିର (                                          \
        "mov    %%"FF_REG_b", %%"FF_REG_S" \n\t"                \
        "cpuid                       \n\t"                      \
        "xchg   %%"FF_REG_b", %%"FF_REG_S                       \
        : "=a" (eax), "=S" (ebx), "=c" (ecx), "=d" (edx)        \
        : "0" (index), "2"(0))

#define xgetbv(index, eax, edx)                                 \
    __asm__ (".byte 0x0f, 0x01, 0xd0" : "=a"(eax), "=d"(edx) : "c" (index))

#define get_eflags(x)                           \
    __asm__ ଅସ୍ଥିର ("pushfl     \n"           \
                      "pop    %0  \n"           \
                      : "=r"(x))

#define set_eflags(x)                           \
    __asm__ ଅସ୍ଥିର ("push    %0 \n"           \
                      "popfl      \n"           \
                      :: "r"(x))

#endif /* HAVE_INLINE_ASM */

#ଯଦି ARCH_X86_64

#define cpuid_test() 1

#ନଚେତଯଦି HAVE_X86ASM

#define cpuid_test ff_cpu_cpuid_test

#ନଚେତଯଦି HAVE_INLINE_ASM

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpuid_test(ଶୂନ୍ୟ)
{
    x86_reg a, c;

    /* Check if CPUID is supported by attempting to toggle the ID bit in
     * the EFLAGS register. */
    get_eflags(a);
    set_eflags(a ^ 0x200000);
    get_eflags(c);

    ଫେରନ୍ତୁ a != c;
}
#endif

/* Function to test if multimedia instructions are supported...  */
ପୂର୍ଣ୍ଣସଂଖ୍ୟା ff_get_cpu_flags_x86(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା rval = 0;

#ifdef cpuid

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା eax, ebx, ecx, edx;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା max_std_level, max_ext_level, std_caps = 0, ext_caps = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା family = 0, model = 0;
    ସଂଘ { ପୂର୍ଣ୍ଣସଂଖ୍ୟା i[3]; ଅକ୍ଷର c[12]; } vendor;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା xcr0_lo = 0, xcr0_hi = 0;

    ଯଦି (!cpuid_test())
        ଫେରନ୍ତୁ 0; /* CPUID not supported */

    cpuid(0, max_std_level, vendor.i[0], vendor.i[2], vendor.i[1]);

    ଯଦି (max_std_level >= 1) {
        cpuid(1, eax, ebx, ecx, std_caps);
        family = ((eax >> 8) & 0xf) + ((eax >> 20) & 0xff);
        model  = ((eax >> 4) & 0xf) + ((eax >> 12) & 0xf0);
        ଯଦି (std_caps & (1 << 15))
            rval |= AV_CPU_FLAG_CMOV;
        ଯଦି (std_caps & (1 << 23))
            rval |= AV_CPU_FLAG_MMX;
        ଯଦି (std_caps & (1 << 25))
            rval |= AV_CPU_FLAG_MMXEXT;
#ଯଦି HAVE_SSE
        ଯଦି (std_caps & (1 << 25))
            rval |= AV_CPU_FLAG_SSE;
        ଯଦି (std_caps & (1 << 26))
            rval |= AV_CPU_FLAG_SSE2;
        ଯଦି (ecx & 1)
            rval |= AV_CPU_FLAG_SSE3;
        ଯଦି (ecx & 0x2)
            rval |= AV_CPU_FLAG_CLMUL;
        ଯଦି (ecx & 0x00000200 )
            rval |= AV_CPU_FLAG_SSSE3;
        ଯଦି (ecx & 0x00080000 )
            rval |= AV_CPU_FLAG_SSE4;
        ଯଦି (ecx & 0x00100000 )
            rval |= AV_CPU_FLAG_SSE42;
        ଯଦି (ecx & 0x02000000 )
            rval |= AV_CPU_FLAG_AESNI;
#ଯଦି HAVE_AVX
        /* Check OXSAVE and AVX bits */
        ଯଦି ((ecx & 0x18000000) == 0x18000000) {
            /* Check for OS support */
            xgetbv(0, xcr0_lo, xcr0_hi);
            ଯଦି ((xcr0_lo & 0x6) == 0x6) {
                rval |= AV_CPU_FLAG_AVX;
                ଯଦି (ecx & 0x00001000)
                    rval |= AV_CPU_FLAG_FMA3;
            }
        }
#endif /* HAVE_AVX */
#endif /* HAVE_SSE */
    }
    ଯଦି (max_std_level >= 7) {
        cpuid(7, eax, ebx, ecx, edx);
#ଯଦି HAVE_AVX2
        ଯଦି ((rval & AV_CPU_FLAG_AVX) && (ebx & 0x00000020))
            rval |= AV_CPU_FLAG_AVX2;
#ଯଦି HAVE_AVX512 /* F, CD, BW, DQ, VL */
        ଯଦି ((xcr0_lo & 0xe0) == 0xe0) { /* OPMASK/ZMM state */
            ଯଦି ((rval & AV_CPU_FLAG_AVX2) && (ebx & 0xd0030000) == 0xd0030000) {
                rval |= AV_CPU_FLAG_AVX512;
#ଯଦି HAVE_AVX512ICL
                ଯଦି ((ebx & 0xd0200000) == 0xd0200000 && (ecx & 0x5f42) == 0x5f42)
                    rval |= AV_CPU_FLAG_AVX512ICL;
#endif /* HAVE_AVX512ICL */
            }
        }
#endif /* HAVE_AVX512 */
#endif /* HAVE_AVX2 */
        /* BMI1/2 don't need OS support */
        ଯଦି (ebx & 0x00000008) {
            rval |= AV_CPU_FLAG_BMI1;
            ଯଦି (ebx & 0x00000100)
                rval |= AV_CPU_FLAG_BMI2;
        }
    }

    cpuid(0x80000000, max_ext_level, ebx, ecx, edx);

    ଯଦି (max_ext_level >= 0x80000001) {
        cpuid(0x80000001, eax, ebx, ecx, ext_caps);
        ଯଦି (ext_caps & (1U << 31))
            rval |= AV_CPU_FLAG_3DNOW;
        ଯଦି (ext_caps & (1 << 30))
            rval |= AV_CPU_FLAG_3DNOWEXT;
        ଯଦି (ext_caps & (1 << 23))
            rval |= AV_CPU_FLAG_MMX;
        ଯଦି (ext_caps & (1 << 22))
            rval |= AV_CPU_FLAG_MMXEXT;

        ଯଦି (!strncmp(vendor.c, "AuthenticAMD", 12)) {
        /* Allow for selectively disabling SSE2 functions on AMD processors
           with SSE2 support but not SSE4a. This includes Athlon64, some
           Opteron, and some Sempron processors. MMX, SSE, or 3DNow! are faster
           than SSE2 often enough to utilize this special-case flag.
           AV_CPU_FLAG_SSE2 and AV_CPU_FLAG_SSE2SLOW are both set in this case
           so that SSE2 is used unless explicitly disabled by checking
           AV_CPU_FLAG_SSE2SLOW. */
            ଯଦି (rval & AV_CPU_FLAG_SSE2 && !(ecx & 0x00000040))
                rval |= AV_CPU_FLAG_SSE2SLOW;

        /* Similar to the above but for AVX functions on AMD processors.
           This is necessary only for functions using YMM registers on Bulldozer
           and Jaguar based CPUs as they lack 256-bit execution units. SSE/AVX
           functions using XMM registers are always faster on them.
           AV_CPU_FLAG_AVX and AV_CPU_FLAG_AVXSLOW are both set so that AVX is
           used unless explicitly disabled by checking AV_CPU_FLAG_AVXSLOW. */
            ଯଦି ((family == 0x15 || family == 0x16) && (rval & AV_CPU_FLAG_AVX))
                rval |= AV_CPU_FLAG_AVXSLOW;

        /* Zen 3 and earlier have slow gather */
            ଯଦି ((family <= 0x19) && (rval & AV_CPU_FLAG_AVX2))
                rval |= AV_CPU_FLAG_SLOW_GATHER;
        }

        /* XOP and FMA4 use the AVX instruction coding scheme, so they can't be
         * used unless the OS has AVX support. */
        ଯଦି (rval & AV_CPU_FLAG_AVX) {
            ଯଦି (ecx & 0x00000800)
                rval |= AV_CPU_FLAG_XOP;
            ଯଦି (ecx & 0x00010000)
                rval |= AV_CPU_FLAG_FMA4;
        }
    }

    ଯଦି (!strncmp(vendor.c, "GenuineIntel", 12)) {
        ଯଦି (family == 6 && (model == 9 || model == 13 || model == 14)) {
            /* 6/9 (pentium-m "banias"), 6/13 (pentium-m "dothan"), and
             * 6/14 (core1 "yonah") theoretically support sse2, but it's
             * usually slower than mmx, so let's just pretend they don't.
             * AV_CPU_FLAG_SSE2 is disabled and AV_CPU_FLAG_SSE2SLOW is
             * enabled so that SSE2 is not used unless explicitly enabled
             * by checking AV_CPU_FLAG_SSE2SLOW. The same situation
             * applies for AV_CPU_FLAG_SSE3 and AV_CPU_FLAG_SSE3SLOW. */
            ଯଦି (rval & AV_CPU_FLAG_SSE2)
                rval ^= AV_CPU_FLAG_SSE2SLOW | AV_CPU_FLAG_SSE2;
            ଯଦି (rval & AV_CPU_FLAG_SSE3)
                rval ^= AV_CPU_FLAG_SSE3SLOW | AV_CPU_FLAG_SSE3;
        }
        /* The Atom processor has SSSE3 support, which is useful in many cases,
         * but sometimes the SSSE3 version is slower than the SSE2 equivalent
         * on the Atom, but is generally faster on other processors supporting
         * SSSE3. This flag allows for selectively disabling certain SSSE3
         * functions on the Atom. */
        ଯଦି (family == 6 && model == 28)
            rval |= AV_CPU_FLAG_ATOM;

        /* Conroe has a slow shuffle unit. Check the model number to ensure not
         * to include crippled low-end Penryns and Nehalems that lack SSE4. */
        ଯଦି ((rval & AV_CPU_FLAG_SSSE3) && !(rval & AV_CPU_FLAG_SSE4) &&
            family == 6 && model < 23)
            rval |= AV_CPU_FLAG_SSSE3SLOW;

        /* Ice Lake and below have slow gather due to Gather Data Sampling
         * mitigation. */
        ଯଦି ((rval & AV_CPU_FLAG_AVX2) && family == 6 && model < 143)
            rval |= AV_CPU_FLAG_SLOW_GATHER;
    }

#endif /* cpuid */

    ଫେରନ୍ତୁ rval;
}

size_t ff_get_cpu_max_align_x86(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = av_get_cpu_flags();

    ଯଦି (flags & AV_CPU_FLAG_AVX512)
        ଫେରନ୍ତୁ 64;
    ଯଦି (flags & (AV_CPU_FLAG_AVX2      |
                 AV_CPU_FLAG_AVX       |
                 AV_CPU_FLAG_XOP       |
                 AV_CPU_FLAG_FMA4      |
                 AV_CPU_FLAG_FMA3      |
                 AV_CPU_FLAG_AVXSLOW))
        ଫେରନ୍ତୁ 32;
    ଯଦି (flags & (AV_CPU_FLAG_AESNI     |
                 AV_CPU_FLAG_SSE42     |
                 AV_CPU_FLAG_SSE4      |
                 AV_CPU_FLAG_SSSE3     |
                 AV_CPU_FLAG_SSE3      |
                 AV_CPU_FLAG_SSE2      |
                 AV_CPU_FLAG_SSE       |
                 AV_CPU_FLAG_ATOM      |
                 AV_CPU_FLAG_SSSE3SLOW |
                 AV_CPU_FLAG_SSE3SLOW  |
                 AV_CPU_FLAG_SSE2SLOW))
        ଫେରନ୍ତୁ 16;

    ଫେରନ୍ତୁ 8;
}

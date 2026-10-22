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

#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ HAVE_SCHED_GETAFFINITY
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ GNU_ಮೂಲ
# define GNU_ಮೂಲ
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <sched.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdatomic.h>

#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ "cpu_internal.h"
#ಅನ್ತರ್ಭಾವ "opt.h"
#ಅನ್ತರ್ಭಾವ "common.h"

#ಆದರೆ HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#ಅನ್ತರ್ಭಾವ <windows.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_SYSCTL
#ಆದರೆ HAVE_SYS_PARAM_H
#ಅನ್ತರ್ಭಾವ <sys/param.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಅನ್ತರ್ಭಾವ <sys/types.h>
#ಅನ್ತರ್ಭಾವ <sys/sysctl.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ atomic_int cpu_flags = -1;
ಸ್ಥಿರ atomic_int cpu_ಎಣಿಕೆ = -1;

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ get_cpu_flags(ಶೂನ್ಯ)
{
#ಆದರೆ ARCH_MIPS
    ಹಿಂತಿರುಗಿ ff_get_cpu_flags_mips();
#ಅಥವಾಆದರೆ ARCH_AARCH64
    ಹಿಂತಿರುಗಿ ff_get_cpu_flags_aarch64();
#ಅಥವಾಆದರೆ ARCH_ARM
    ಹಿಂತಿರುಗಿ ff_get_cpu_flags_arm();
#ಅಥವಾಆದರೆ ARCH_PPC
    ಹಿಂತಿರುಗಿ ff_get_cpu_flags_ppc();
#ಅಥವಾಆದರೆ ARCH_RISCV
    ಹಿಂತಿರುಗಿ ff_get_cpu_flags_riscv();
#ಅಥವಾಆದರೆ ARCH_WASM
    ಹಿಂತಿರುಗಿ ff_get_cpu_flags_wasm();
#ಅಥವಾಆದರೆ ARCH_X86
    ಹಿಂತಿರುಗಿ ff_get_cpu_flags_x86();
#ಅಥವಾಆದರೆ ARCH_LOONGARCH
    ಹಿಂತಿರುಗಿ ff_get_cpu_flags_loongarch();
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_force_cpu_flags(ಪೂರ್ಣಾಂಕ arg){
    ಆದರೆ (ARCH_X86 &&
           (arg & ( AV_CPU_FLAG_3DNOW    |
                    AV_CPU_FLAG_3DNOWEXT |
                    AV_CPU_FLAG_MMXEXT   |
                    AV_CPU_FLAG_SSE      |
                    AV_CPU_FLAG_SSE2     |
                    AV_CPU_FLAG_SSE2SLOW |
                    AV_CPU_FLAG_SSE3     |
                    AV_CPU_FLAG_SSE3SLOW |
                    AV_CPU_FLAG_SSSE3    |
                    AV_CPU_FLAG_SSE4     |
                    AV_CPU_FLAG_SSE42    |
                    AV_CPU_FLAG_AVX      |
                    AV_CPU_FLAG_AVXSLOW  |
                    AV_CPU_FLAG_XOP      |
                    AV_CPU_FLAG_FMA3     |
                    AV_CPU_FLAG_FMA4     |
                    AV_CPU_FLAG_AVX2     |
                    AV_CPU_FLAG_AVX512   ))
        && !(arg & AV_CPU_FLAG_MMX)) {
        av_log(ಖಾಲಿ, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

ಪೂರ್ಣಾಂಕ av_get_cpu_flags(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಂಕ flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    ಆದರೆ (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    ಹಿಂತಿರುಗಿ flags;
}

ಪೂರ್ಣಾಂಕ av_parse_cpu_caps(ಚಿಹ್ನೆರಹಿತ *flags, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s)
{
        ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVOption cpuflags_opts[] = {
        { "flags"   , ಖಾಲಿ, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#ಆದರೆ   ARCH_PPC
        { "altivec" , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#ಅಥವಾಆದರೆ ARCH_X86
        { "mmx"     , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#ವ್ಯಾಖ್ಯಾನಿಸು CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#ವ್ಯಾಖ್ಯಾನಿಸು CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#ವ್ಯಾಖ್ಯಾನಿಸು CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#ವ್ಯಾಖ್ಯಾನಿಸು CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#ವ್ಯಾಖ್ಯಾನಿಸು CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#ವ್ಯಾಖ್ಯಾನಿಸು CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#ವ್ಯಾಖ್ಯಾನಿಸು CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#ಅಥವಾಆದರೆ ARCH_ARM
        { "armv5te",  ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#ಅಥವಾಆದರೆ ARCH_AARCH64
        { "armv8",    ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ  },    .unit = "flags" },
        { "sme_i16i64", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#ಅಥವಾಆದರೆ ARCH_MIPS
        { "mmi",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#ಅಥವಾಆದರೆ ARCH_LOONGARCH
        { "lsx",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#ಅಥವಾಆದರೆ ARCH_RISCV
        { "rvi",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#ಅಥವಾಆದರೆ ARCH_WASM
        { "simd128",  ಖಾಲಿ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#ಆದರೆ_ಅಂತ್ಯ
        { ಖಾಲಿ },
    };
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass class = {
        .class_name = "cpuflags",
        .ಅಂಶ_name  = av_default_ಅಂಶ_name,
        .option     = cpuflags_opts,
        .ಆವೃತ್ತಿ    = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    };
    ಸ್ಥಿರಾಂಕ AVClass *pclass = &class;

    ಹಿಂತಿರುಗಿ av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

ಪೂರ್ಣಾಂಕ av_cpu_ಎಣಿಕೆ(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ atomic_int printed = 0;

    ಪೂರ್ಣಾಂಕ nb_cpus = 1;
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2   = 0;
#ಆದರೆ HAVE_WINRT
    SYSTEM_INFO sysinfo;
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_SCHED_GETAFFINITY && defined(CPU_ಎಣಿಕೆ)
    cpu_ಗಣ_t cpuset;

    CPU_ZERO(&cpuset);

    ಆದರೆ (!sched_getaffinity(0, ಗಾತ್ರ(cpuset), &cpuset))
        nb_cpus = CPU_ಎಣಿಕೆ(&cpuset);
#ಅಥವಾಆದರೆ HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    ಆದರೆ (Get_Process_Affinity_ಮುಖವಾಡ(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#ಅಥವಾಆದರೆ HAVE_SYSCTL && defined(HW_NCPUONLINE)
    ಪೂರ್ಣಾಂಕ mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = ಗಾತ್ರ(nb_cpus);

    ಆದರೆ (sysctl(mib, 2, &nb_cpus, &len, ಖಾಲಿ, 0) == -1)
        nb_cpus = 0;
#ಅಥವಾಆದರೆ HAVE_SYSCTL && defined(HW_NCPU)
    ಪೂರ್ಣಾಂಕ mib[2] = { CTL_HW, HW_NCPU };
    size_t len = ಗಾತ್ರ(nb_cpus);

    ಆದರೆ (sysctl(mib, 2, &nb_cpus, &len, ಖಾಲಿ, 0) == -1)
        nb_cpus = 0;
#ಅಥವಾಆದರೆ HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#ಅಥವಾಆದರೆ HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#ಅಥವಾಆದರೆ HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_ಸಂಖ್ಯೆ_ದ_Processors;
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(ಖಾಲಿ, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    ಎಣಿಕೆ_2 = atomic_load_explicit(&cpu_ಎಣಿಕೆ, memory_order_relaxed);

    ಆದರೆ (ಎಣಿಕೆ_2 > 0) {
        nb_cpus = ಎಣಿಕೆ_2;
        av_log(ಖಾಲಿ, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    ಹಿಂತಿರುಗಿ nb_cpus;
}

ಶೂನ್ಯ av_cpu_force_ಎಣಿಕೆ(ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2)
{
    atomic_store_explicit(&cpu_ಎಣಿಕೆ, ಎಣಿಕೆ_2, memory_order_relaxed);
}

size_t av_cpu_max_align(ಶೂನ್ಯ)
{
#ಆದರೆ ARCH_MIPS
    ಹಿಂತಿರುಗಿ ff_get_cpu_max_align_mips();
#ಅಥವಾಆದರೆ ARCH_AARCH64
    ಹಿಂತಿರುಗಿ ff_get_cpu_max_align_aarch64();
#ಅಥವಾಆದರೆ ARCH_ARM
    ಹಿಂತಿರುಗಿ ff_get_cpu_max_align_arm();
#ಅಥವಾಆದರೆ ARCH_PPC
    ಹಿಂತಿರುಗಿ ff_get_cpu_max_align_ppc();
#ಅಥವಾಆದರೆ ARCH_WASM
    ಹಿಂತಿರುಗಿ ff_get_cpu_max_align_wasm();
#ಅಥವಾಆದರೆ ARCH_X86
    ಹಿಂತಿರುಗಿ ff_get_cpu_max_align_x86();
#ಅಥವಾಆದರೆ ARCH_LOONGARCH
    ಹಿಂತಿರುಗಿ ff_get_cpu_max_align_loongarch();
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ 8;
}

#ಆದರೆ !ARCH_X86
ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ff_getauxval(ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ type)
{
#ಆದರೆ HAVE_GETAUXVAL
    ಹಿಂತಿರುಗಿ getauxval(type);
#ಅಥವಾಆದರೆ HAVE_ELF_AUX_INFO
    ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ aux = 0;
    ಪೂರ್ಣಾಂಕ ret = elf_aux_info(type, &aux, ಗಾತ್ರ(aux));
    ಆದರೆ (ret != 0) {
        errno = ret;
    }
    ಹಿಂತಿರುಗಿ aux;
#ಇಲ್ಲದಿದ್ದರೆ
    errno = ENOSYS;
    ಹಿಂತಿರುಗಿ 0;
#ಆದರೆ_ಅಂತ್ಯ
}
#ಆದರೆ_ಅಂತ್ಯ

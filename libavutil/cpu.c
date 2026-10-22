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

#ಯದಿ HAVE_SCHED_GETAFFINITY
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#ಅನ್ತರ್ಭಾವ <sched.h>
#endif

#ಅನ್ತರ್ಭಾವ <stddef.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdatomic.h>

#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "cpu.h"
#ಅನ್ತರ್ಭಾವ "cpu_internal.h"
#ಅನ್ತರ್ಭಾವ "opt.h"
#ಅನ್ತರ್ಭಾವ "common.h"

#ಯದಿ HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#ಅನ್ತರ್ಭಾವ <windows.h>
#endif
#ಯದಿ HAVE_SYSCTL
#ಯದಿ HAVE_SYS_PARAM_H
#ಅನ್ತರ್ಭಾವ <sys/param.h>
#endif
#ಅನ್ತರ್ಭಾವ <sys/types.h>
#ಅನ್ತರ್ಭಾವ <sys/sysctl.h>
#endif
#ಯದಿ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#endif

#ಯದಿ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ಅನ್ತರ್ಭಾವ <sys/auxv.h>
#endif

ಸ್ಥಿರ atomic_int cpu_flags = -1;
ಸ್ಥಿರ atomic_int cpu_ಎಣಿಕೆ = -1;

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ get_cpu_flags(ಶೂನ್ಯ)
{
#ಯದಿ ARCH_MIPS
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_flags_mips();
#ನೋಚೇದ್ಯದಿ ARCH_AARCH64
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_flags_aarch64();
#ನೋಚೇದ್ಯದಿ ARCH_ARM
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_flags_arm();
#ನೋಚೇದ್ಯದಿ ARCH_PPC
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_flags_ppc();
#ನೋಚೇದ್ಯದಿ ARCH_RISCV
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_flags_riscv();
#ನೋಚೇದ್ಯದಿ ARCH_WASM
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_flags_wasm();
#ನೋಚೇದ್ಯದಿ ARCH_X86
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_flags_x86();
#ನೋಚೇದ್ಯದಿ ARCH_LOONGARCH
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_flags_loongarch();
#endif
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_force_cpu_flags(ಪೂರ್ಣಾಙ್ಕ arg){
    ಯದಿ (ARCH_X86 &&
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
        av_log(ರಿಕ್ತ, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

ಪೂರ್ಣಾಙ್ಕ av_get_cpu_flags(ಶೂನ್ಯ)
{
    ಪೂರ್ಣಾಙ್ಕ flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    ಯದಿ (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    ಪ್ರತ್ಯಾಗಮ flags;
}

ಪೂರ್ಣಾಙ್ಕ av_parse_cpu_caps(unsigned *flags, ಧ್ರುವ ವರ್ಣ *s)
{
        ಸ್ಥಿರ ಧ್ರುವ AVOption cpuflags_opts[] = {
        { "flags"   , ರಿಕ್ತ, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#ಯದಿ   ARCH_PPC
        { "altivec" , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#ನೋಚೇದ್ಯದಿ ARCH_X86
        { "mmx"     , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#define CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#define CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#define CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#define CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#define CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#define CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#define CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#ನೋಚೇದ್ಯದಿ ARCH_ARM
        { "armv5te",  ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#ನೋಚೇದ್ಯದಿ ARCH_AARCH64
        { "armv8",    ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#ನೋಚೇದ್ಯದಿ ARCH_MIPS
        { "mmi",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#ನೋಚೇದ್ಯದಿ ARCH_LOONGARCH
        { "lsx",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#ನೋಚೇದ್ಯದಿ ARCH_RISCV
        { "rvi",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#ನೋಚೇದ್ಯದಿ ARCH_WASM
        { "simd128",  ರಿಕ್ತ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { ರಿಕ್ತ },
    };
    ಸ್ಥಿರ ಧ್ರುವ AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    ಧ್ರುವ AVClass *pclass = &class;

    ಪ್ರತ್ಯಾಗಮ av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

ಪೂರ್ಣಾಙ್ಕ av_cpu_ಎಣಿಕೆ(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ atomic_int printed = 0;

    ಪೂರ್ಣಾಙ್ಕ nb_cpus = 1;
    ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ   = 0;
#ಯದಿ HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#ಯದಿ HAVE_SCHED_GETAFFINITY && defined(CPU_ಎಣಿಕೆ)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    ಯದಿ (!sched_getaffinity(0, ಪರಿಮಾಣ(cpuset), &cpuset))
        nb_cpus = CPU_ಎಣಿಕೆ(&cpuset);
#ನೋಚೇದ್ಯದಿ HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    ಯದಿ (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#ನೋಚೇದ್ಯದಿ HAVE_SYSCTL && defined(HW_NCPUONLINE)
    ಪೂರ್ಣಾಙ್ಕ mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = ಪರಿಮಾಣ(nb_cpus);

    ಯದಿ (sysctl(mib, 2, &nb_cpus, &len, ರಿಕ್ತ, 0) == -1)
        nb_cpus = 0;
#ನೋಚೇದ್ಯದಿ HAVE_SYSCTL && defined(HW_NCPU)
    ಪೂರ್ಣಾಙ್ಕ mib[2] = { CTL_HW, HW_NCPU };
    size_t len = ಪರಿಮಾಣ(nb_cpus);

    ಯದಿ (sysctl(mib, 2, &nb_cpus, &len, ರಿಕ್ತ, 0) == -1)
        nb_cpus = 0;
#ನೋಚೇದ್ಯದಿ HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#ನೋಚೇದ್ಯದಿ HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#ನೋಚೇದ್ಯದಿ HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_ಸಂಖ್ಯೆ_Of_Processors;
#endif

    ಯದಿ (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(ರಿಕ್ತ, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    ಎಣಿಕೆ = atomic_load_explicit(&cpu_ಎಣಿಕೆ, memory_order_relaxed);

    ಯದಿ (ಎಣಿಕೆ > 0) {
        nb_cpus = ಎಣಿಕೆ;
        av_log(ರಿಕ್ತ, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    ಪ್ರತ್ಯಾಗಮ nb_cpus;
}

ಶೂನ್ಯ av_cpu_force_ಎಣಿಕೆ(ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ)
{
    atomic_store_explicit(&cpu_ಎಣಿಕೆ, ಎಣಿಕೆ, memory_order_relaxed);
}

size_t av_cpu_max_align(ಶೂನ್ಯ)
{
#ಯದಿ ARCH_MIPS
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_max_align_mips();
#ನೋಚೇದ್ಯದಿ ARCH_AARCH64
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_max_align_aarch64();
#ನೋಚೇದ್ಯದಿ ARCH_ARM
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_max_align_arm();
#ನೋಚೇದ್ಯದಿ ARCH_PPC
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_max_align_ppc();
#ನೋಚೇದ್ಯದಿ ARCH_WASM
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_max_align_wasm();
#ನೋಚೇದ್ಯದಿ ARCH_X86
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_max_align_x86();
#ನೋಚೇದ್ಯದಿ ARCH_LOONGARCH
    ಪ್ರತ್ಯಾಗಮ ff_get_cpu_max_align_loongarch();
#endif

    ಪ್ರತ್ಯಾಗಮ 8;
}

#ಯದಿ !ARCH_X86
unsigned long ff_getauxval(unsigned long type)
{
#ಯದಿ HAVE_GETAUXVAL
    ಪ್ರತ್ಯಾಗಮ getauxval(type);
#ನೋಚೇದ್ಯದಿ HAVE_ELF_AUX_INFO
    unsigned long aux = 0;
    ಪೂರ್ಣಾಙ್ಕ ret = elf_aux_info(type, &aux, ಪರಿಮಾಣ(aux));
    ಯದಿ (ret != 0) {
        errno = ret;
    }
    ಪ್ರತ್ಯಾಗಮ aux;
#ಅನ್ಯಥಾ
    errno = ENOSYS;
    ಪ್ರತ್ಯಾಗಮ 0;
#endif
}
#endif

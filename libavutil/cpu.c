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

#അന്തര്ഭാവ "config.h"

#എങ്കിൽ HAVE_SCHED_GETAFFINITY
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#അന്തര്ഭാവ <sched.h>
#endif

#അന്തര്ഭാവ <stddef.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdatomic.h>

#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "cpu.h"
#അന്തര്ഭാവ "cpu_internal.h"
#അന്തര്ഭാവ "opt.h"
#അന്തര്ഭാവ "common.h"

#എങ്കിൽ HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#അന്തര്ഭാവ <windows.h>
#endif
#എങ്കിൽ HAVE_SYSCTL
#എങ്കിൽ HAVE_SYS_PARAM_H
#അന്തര്ഭാവ <sys/param.h>
#endif
#അന്തര്ഭാവ <sys/types.h>
#അന്തര്ഭാവ <sys/sysctl.h>
#endif
#എങ്കിൽ HAVE_UNISTD_H
#അന്തര്ഭാവ <unistd.h>
#endif

#എങ്കിൽ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#അന്തര്ഭാവ <sys/auxv.h>
#endif

സ്ഥിതം atomic_int cpu_flags = -1;
സ്ഥിതം atomic_int cpu_എണ്ണം = -1;

സ്ഥിതം പൂർണ്ണസംഖ്യ get_cpu_flags(ശൂന്യം)
{
#എങ്കിൽ ARCH_MIPS
    തിരികെ ff_get_cpu_flags_mips();
#അല്ലെങ്കിലെങ്കിൽ ARCH_AARCH64
    തിരികെ ff_get_cpu_flags_aarch64();
#അല്ലെങ്കിലെങ്കിൽ ARCH_ARM
    തിരികെ ff_get_cpu_flags_arm();
#അല്ലെങ്കിലെങ്കിൽ ARCH_PPC
    തിരികെ ff_get_cpu_flags_ppc();
#അല്ലെങ്കിലെങ്കിൽ ARCH_RISCV
    തിരികെ ff_get_cpu_flags_riscv();
#അല്ലെങ്കിലെങ്കിൽ ARCH_WASM
    തിരികെ ff_get_cpu_flags_wasm();
#അല്ലെങ്കിലെങ്കിൽ ARCH_X86
    തിരികെ ff_get_cpu_flags_x86();
#അല്ലെങ്കിലെങ്കിൽ ARCH_LOONGARCH
    തിരികെ ff_get_cpu_flags_loongarch();
#endif
    തിരികെ 0;
}

ശൂന്യം av_force_cpu_flags(പൂർണ്ണസംഖ്യ arg){
    എങ്കിൽ (ARCH_X86 &&
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
        av_log(ശൂന്യ, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

പൂർണ്ണസംഖ്യ av_get_cpu_flags(ശൂന്യം)
{
    പൂർണ്ണസംഖ്യ flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    എങ്കിൽ (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    തിരികെ flags;
}

പൂർണ്ണസംഖ്യ av_parse_cpu_caps(unsigned *flags, സ്ഥിരം അക്ഷരം *s)
{
        സ്ഥിതം സ്ഥിരം AVOption cpuflags_opts[] = {
        { "flags"   , ശൂന്യ, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#എങ്കിൽ   ARCH_PPC
        { "altivec" , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#അല്ലെങ്കിലെങ്കിൽ ARCH_X86
        { "mmx"     , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#define CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#define CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#define CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#define CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#define CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#define CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#define CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#അല്ലെങ്കിലെങ്കിൽ ARCH_ARM
        { "armv5te",  ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#അല്ലെങ്കിലെങ്കിൽ ARCH_AARCH64
        { "armv8",    ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#അല്ലെങ്കിലെങ്കിൽ ARCH_MIPS
        { "mmi",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#അല്ലെങ്കിലെങ്കിൽ ARCH_LOONGARCH
        { "lsx",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#അല്ലെങ്കിലെങ്കിൽ ARCH_RISCV
        { "rvi",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#അല്ലെങ്കിലെങ്കിൽ ARCH_WASM
        { "simd128",  ശൂന്യ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { ശൂന്യ },
    };
    സ്ഥിതം സ്ഥിരം AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    സ്ഥിരം AVClass *pclass = &class;

    തിരികെ av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

പൂർണ്ണസംഖ്യ av_cpu_എണ്ണം(ശൂന്യം)
{
    സ്ഥിതം atomic_int printed = 0;

    പൂർണ്ണസംഖ്യ nb_cpus = 1;
    പൂർണ്ണസംഖ്യ എണ്ണം   = 0;
#എങ്കിൽ HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#എങ്കിൽ HAVE_SCHED_GETAFFINITY && defined(CPU_എണ്ണം)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    എങ്കിൽ (!sched_getaffinity(0, വലുപ്പം(cpuset), &cpuset))
        nb_cpus = CPU_എണ്ണം(&cpuset);
#അല്ലെങ്കിലെങ്കിൽ HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    എങ്കിൽ (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#അല്ലെങ്കിലെങ്കിൽ HAVE_SYSCTL && defined(HW_NCPUONLINE)
    പൂർണ്ണസംഖ്യ mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = വലുപ്പം(nb_cpus);

    എങ്കിൽ (sysctl(mib, 2, &nb_cpus, &len, ശൂന്യ, 0) == -1)
        nb_cpus = 0;
#അല്ലെങ്കിലെങ്കിൽ HAVE_SYSCTL && defined(HW_NCPU)
    പൂർണ്ണസംഖ്യ mib[2] = { CTL_HW, HW_NCPU };
    size_t len = വലുപ്പം(nb_cpus);

    എങ്കിൽ (sysctl(mib, 2, &nb_cpus, &len, ശൂന്യ, 0) == -1)
        nb_cpus = 0;
#അല്ലെങ്കിലെങ്കിൽ HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#അല്ലെങ്കിലെങ്കിൽ HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#അല്ലെങ്കിലെങ്കിൽ HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_സംഖ്യ_Of_Processors;
#endif

    എങ്കിൽ (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(ശൂന്യ, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    എണ്ണം = atomic_load_explicit(&cpu_എണ്ണം, memory_order_relaxed);

    എങ്കിൽ (എണ്ണം > 0) {
        nb_cpus = എണ്ണം;
        av_log(ശൂന്യ, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    തിരികെ nb_cpus;
}

ശൂന്യം av_cpu_force_എണ്ണം(പൂർണ്ണസംഖ്യ എണ്ണം)
{
    atomic_store_explicit(&cpu_എണ്ണം, എണ്ണം, memory_order_relaxed);
}

size_t av_cpu_max_align(ശൂന്യം)
{
#എങ്കിൽ ARCH_MIPS
    തിരികെ ff_get_cpu_max_align_mips();
#അല്ലെങ്കിലെങ്കിൽ ARCH_AARCH64
    തിരികെ ff_get_cpu_max_align_aarch64();
#അല്ലെങ്കിലെങ്കിൽ ARCH_ARM
    തിരികെ ff_get_cpu_max_align_arm();
#അല്ലെങ്കിലെങ്കിൽ ARCH_PPC
    തിരികെ ff_get_cpu_max_align_ppc();
#അല്ലെങ്കിലെങ്കിൽ ARCH_WASM
    തിരികെ ff_get_cpu_max_align_wasm();
#അല്ലെങ്കിലെങ്കിൽ ARCH_X86
    തിരികെ ff_get_cpu_max_align_x86();
#അല്ലെങ്കിലെങ്കിൽ ARCH_LOONGARCH
    തിരികെ ff_get_cpu_max_align_loongarch();
#endif

    തിരികെ 8;
}

#എങ്കിൽ !ARCH_X86
unsigned long ff_getauxval(unsigned long type)
{
#എങ്കിൽ HAVE_GETAUXVAL
    തിരികെ getauxval(type);
#അല്ലെങ്കിലെങ്കിൽ HAVE_ELF_AUX_INFO
    unsigned long aux = 0;
    പൂർണ്ണസംഖ്യ ret = elf_aux_info(type, &aux, വലുപ്പം(aux));
    എങ്കിൽ (ret != 0) {
        errno = ret;
    }
    തിരികെ aux;
#അല്ലെങ്കിൽ
    errno = ENOSYS;
    തിരികെ 0;
#endif
}
#endif

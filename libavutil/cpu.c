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

#অন্তর্ভাব "config.h"

#যদি HAVE_SCHED_GETAFFINITY
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#অন্তর্ভাব <sched.h>
#endif

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdatomic.h>

#অন্তর্ভাব "attributes.h"
#অন্তর্ভাব "cpu.h"
#অন্তর্ভাব "cpu_internal.h"
#অন্তর্ভাব "opt.h"
#অন্তর্ভাব "common.h"

#যদি HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#অন্তর্ভাব <windows.h>
#endif
#যদি HAVE_SYSCTL
#যদি HAVE_SYS_PARAM_H
#অন্তর্ভাব <sys/param.h>
#endif
#অন্তর্ভাব <sys/types.h>
#অন্তর্ভাব <sys/sysctl.h>
#endif
#যদি HAVE_UNISTD_H
#অন্তর্ভাব <unistd.h>
#endif

#যদি HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#অন্তর্ভাব <sys/auxv.h>
#endif

স্থির atomic_int cpu_flags = -1;
স্থির atomic_int cpu_গুনতি = -1;

স্থির পূর্ণাঙ্ক get_cpu_flags(শূন্য)
{
#যদি ARCH_MIPS
    প্রত্যাগম ff_get_cpu_flags_mips();
#নোচেদ্যদি ARCH_AARCH64
    প্রত্যাগম ff_get_cpu_flags_aarch64();
#নোচেদ্যদি ARCH_ARM
    প্রত্যাগম ff_get_cpu_flags_arm();
#নোচেদ্যদি ARCH_PPC
    প্রত্যাগম ff_get_cpu_flags_ppc();
#নোচেদ্যদি ARCH_RISCV
    প্রত্যাগম ff_get_cpu_flags_riscv();
#নোচেদ্যদি ARCH_WASM
    প্রত্যাগম ff_get_cpu_flags_wasm();
#নোচেদ্যদি ARCH_X86
    প্রত্যাগম ff_get_cpu_flags_x86();
#নোচেদ্যদি ARCH_LOONGARCH
    প্রত্যাগম ff_get_cpu_flags_loongarch();
#endif
    প্রত্যাগম 0;
}

শূন্য av_force_cpu_flags(পূর্ণাঙ্ক arg){
    যদি (ARCH_X86 &&
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
        av_log(রিক্ত, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

পূর্ণাঙ্ক av_get_cpu_flags(শূন্য)
{
    পূর্ণাঙ্ক flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    যদি (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    প্রত্যাগম flags;
}

পূর্ণাঙ্ক av_parse_cpu_caps(unsigned *flags, ধ্রুব বর্ণ *s)
{
        স্থির ধ্রুব AVOption cpuflags_opts[] = {
        { "flags"   , রিক্ত, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#যদি   ARCH_PPC
        { "altivec" , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#নোচেদ্যদি ARCH_X86
        { "mmx"     , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#define CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#define CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#define CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#define CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#define CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#define CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#define CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#নোচেদ্যদি ARCH_ARM
        { "armv5te",  রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#নোচেদ্যদি ARCH_AARCH64
        { "armv8",    রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#নোচেদ্যদি ARCH_MIPS
        { "mmi",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#নোচেদ্যদি ARCH_LOONGARCH
        { "lsx",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#নোচেদ্যদি ARCH_RISCV
        { "rvi",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#নোচেদ্যদি ARCH_WASM
        { "simd128",  রিক্ত, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { রিক্ত },
    };
    স্থির ধ্রুব AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    ধ্রুব AVClass *pclass = &class;

    প্রত্যাগম av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

পূর্ণাঙ্ক av_cpu_গুনতি(শূন্য)
{
    স্থির atomic_int printed = 0;

    পূর্ণাঙ্ক nb_cpus = 1;
    পূর্ণাঙ্ক গুনতি   = 0;
#যদি HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#যদি HAVE_SCHED_GETAFFINITY && defined(CPU_গুনতি)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    যদি (!sched_getaffinity(0, পরিমাণ(cpuset), &cpuset))
        nb_cpus = CPU_গুনতি(&cpuset);
#নোচেদ্যদি HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    যদি (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#নোচেদ্যদি HAVE_SYSCTL && defined(HW_NCPUONLINE)
    পূর্ণাঙ্ক mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = পরিমাণ(nb_cpus);

    যদি (sysctl(mib, 2, &nb_cpus, &len, রিক্ত, 0) == -1)
        nb_cpus = 0;
#নোচেদ্যদি HAVE_SYSCTL && defined(HW_NCPU)
    পূর্ণাঙ্ক mib[2] = { CTL_HW, HW_NCPU };
    size_t len = পরিমাণ(nb_cpus);

    যদি (sysctl(mib, 2, &nb_cpus, &len, রিক্ত, 0) == -1)
        nb_cpus = 0;
#নোচেদ্যদি HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#নোচেদ্যদি HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#নোচেদ্যদি HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_সংখ্যা_Of_Processors;
#endif

    যদি (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(রিক্ত, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    গুনতি = atomic_load_explicit(&cpu_গুনতি, memory_order_relaxed);

    যদি (গুনতি > 0) {
        nb_cpus = গুনতি;
        av_log(রিক্ত, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    প্রত্যাগম nb_cpus;
}

শূন্য av_cpu_force_গুনতি(পূর্ণাঙ্ক গুনতি)
{
    atomic_store_explicit(&cpu_গুনতি, গুনতি, memory_order_relaxed);
}

size_t av_cpu_max_align(শূন্য)
{
#যদি ARCH_MIPS
    প্রত্যাগম ff_get_cpu_max_align_mips();
#নোচেদ্যদি ARCH_AARCH64
    প্রত্যাগম ff_get_cpu_max_align_aarch64();
#নোচেদ্যদি ARCH_ARM
    প্রত্যাগম ff_get_cpu_max_align_arm();
#নোচেদ্যদি ARCH_PPC
    প্রত্যাগম ff_get_cpu_max_align_ppc();
#নোচেদ্যদি ARCH_WASM
    প্রত্যাগম ff_get_cpu_max_align_wasm();
#নোচেদ্যদি ARCH_X86
    প্রত্যাগম ff_get_cpu_max_align_x86();
#নোচেদ্যদি ARCH_LOONGARCH
    প্রত্যাগম ff_get_cpu_max_align_loongarch();
#endif

    প্রত্যাগম 8;
}

#যদি !ARCH_X86
unsigned long ff_getauxval(unsigned long type)
{
#যদি HAVE_GETAUXVAL
    প্রত্যাগম getauxval(type);
#নোচেদ্যদি HAVE_ELF_AUX_INFO
    unsigned long aux = 0;
    পূর্ণাঙ্ক ret = elf_aux_info(type, &aux, পরিমাণ(aux));
    যদি (ret != 0) {
        errno = ret;
    }
    প্রত্যাগম aux;
#অন্যথা
    errno = ENOSYS;
    প্রত্যাগম 0;
#endif
}
#endif

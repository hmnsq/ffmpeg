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

স্থির পূর্ণসংখ্যা get_cpu_flags(শূন্য)
{
#যদি ARCH_MIPS
    ফেরত ff_get_cpu_flags_mips();
#নতুবা_যদি ARCH_AARCH64
    ফেরত ff_get_cpu_flags_aarch64();
#নতুবা_যদি ARCH_ARM
    ফেরত ff_get_cpu_flags_arm();
#নতুবা_যদি ARCH_PPC
    ফেরত ff_get_cpu_flags_ppc();
#নতুবা_যদি ARCH_RISCV
    ফেরত ff_get_cpu_flags_riscv();
#নতুবা_যদি ARCH_WASM
    ফেরত ff_get_cpu_flags_wasm();
#নতুবা_যদি ARCH_X86
    ফেরত ff_get_cpu_flags_x86();
#নতুবা_যদি ARCH_LOONGARCH
    ফেরত ff_get_cpu_flags_loongarch();
#endif
    ফেরত 0;
}

শূন্য av_force_cpu_flags(পূর্ণসংখ্যা arg){
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
        av_log(ফাঁকা, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

পূর্ণসংখ্যা av_get_cpu_flags(শূন্য)
{
    পূর্ণসংখ্যা flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    যদি (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    ফেরত flags;
}

পূর্ণসংখ্যা av_parse_cpu_caps(unsigned *flags, ধ্রুবক অক্ষর *s)
{
        স্থির ধ্রুবক AVOption cpuflags_opts[] = {
        { "flags"   , ফাঁকা, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#যদি   ARCH_PPC
        { "altivec" , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#নতুবা_যদি ARCH_X86
        { "mmx"     , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#define CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#define CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#define CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#define CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#define CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#define CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#define CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#নতুবা_যদি ARCH_ARM
        { "armv5te",  ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#নতুবা_যদি ARCH_AARCH64
        { "armv8",    ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#নতুবা_যদি ARCH_MIPS
        { "mmi",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#নতুবা_যদি ARCH_LOONGARCH
        { "lsx",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#নতুবা_যদি ARCH_RISCV
        { "rvi",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#নতুবা_যদি ARCH_WASM
        { "simd128",  ফাঁকা, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { ফাঁকা },
    };
    স্থির ধ্রুবক AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    ধ্রুবক AVClass *pclass = &class;

    ফেরত av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

পূর্ণসংখ্যা av_cpu_গুনতি(শূন্য)
{
    স্থির atomic_int printed = 0;

    পূর্ণসংখ্যা nb_cpus = 1;
    পূর্ণসংখ্যা গুনতি   = 0;
#যদি HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#যদি HAVE_SCHED_GETAFFINITY && defined(CPU_গুনতি)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    যদি (!sched_getaffinity(0, আকার(cpuset), &cpuset))
        nb_cpus = CPU_গুনতি(&cpuset);
#নতুবা_যদি HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    যদি (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#নতুবা_যদি HAVE_SYSCTL && defined(HW_NCPUONLINE)
    পূর্ণসংখ্যা mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = আকার(nb_cpus);

    যদি (sysctl(mib, 2, &nb_cpus, &len, ফাঁকা, 0) == -1)
        nb_cpus = 0;
#নতুবা_যদি HAVE_SYSCTL && defined(HW_NCPU)
    পূর্ণসংখ্যা mib[2] = { CTL_HW, HW_NCPU };
    size_t len = আকার(nb_cpus);

    যদি (sysctl(mib, 2, &nb_cpus, &len, ফাঁকা, 0) == -1)
        nb_cpus = 0;
#নতুবা_যদি HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#নতুবা_যদি HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#নতুবা_যদি HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_সংখ্যা_Of_Processors;
#endif

    যদি (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(ফাঁকা, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    গুনতি = atomic_load_explicit(&cpu_গুনতি, memory_order_relaxed);

    যদি (গুনতি > 0) {
        nb_cpus = গুনতি;
        av_log(ফাঁকা, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    ফেরত nb_cpus;
}

শূন্য av_cpu_force_গুনতি(পূর্ণসংখ্যা গুনতি)
{
    atomic_store_explicit(&cpu_গুনতি, গুনতি, memory_order_relaxed);
}

size_t av_cpu_max_align(শূন্য)
{
#যদি ARCH_MIPS
    ফেরত ff_get_cpu_max_align_mips();
#নতুবা_যদি ARCH_AARCH64
    ফেরত ff_get_cpu_max_align_aarch64();
#নতুবা_যদি ARCH_ARM
    ফেরত ff_get_cpu_max_align_arm();
#নতুবা_যদি ARCH_PPC
    ফেরত ff_get_cpu_max_align_ppc();
#নতুবা_যদি ARCH_WASM
    ফেরত ff_get_cpu_max_align_wasm();
#নতুবা_যদি ARCH_X86
    ফেরত ff_get_cpu_max_align_x86();
#নতুবা_যদি ARCH_LOONGARCH
    ফেরত ff_get_cpu_max_align_loongarch();
#endif

    ফেরত 8;
}

#যদি !ARCH_X86
unsigned long ff_getauxval(unsigned long type)
{
#যদি HAVE_GETAUXVAL
    ফেরত getauxval(type);
#নতুবা_যদি HAVE_ELF_AUX_INFO
    unsigned long aux = 0;
    পূর্ণসংখ্যা ret = elf_aux_info(type, &aux, আকার(aux));
    যদি (ret != 0) {
        errno = ret;
    }
    ফেরত aux;
#অন্যথা
    errno = ENOSYS;
    ফেরত 0;
#endif
}
#endif

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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଯଦି HAVE_SCHED_GETAFFINITY
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#ଅନ୍ତର୍ଭାଵ <sched.h>
#endif

#ଅନ୍ତର୍ଭାଵ <stddef.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdatomic.h>

#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "cpu.h"
#ଅନ୍ତର୍ଭାଵ "cpu_internal.h"
#ଅନ୍ତର୍ଭାଵ "opt.h"
#ଅନ୍ତର୍ଭାଵ "common.h"

#ଯଦି HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#ଅନ୍ତର୍ଭାଵ <windows.h>
#endif
#ଯଦି HAVE_SYSCTL
#ଯଦି HAVE_SYS_PARAM_H
#ଅନ୍ତର୍ଭାଵ <sys/param.h>
#endif
#ଅନ୍ତର୍ଭାଵ <sys/types.h>
#ଅନ୍ତର୍ଭାଵ <sys/sysctl.h>
#endif
#ଯଦି HAVE_UNISTD_H
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#endif

#ଯଦି HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ଅନ୍ତର୍ଭାଵ <sys/auxv.h>
#endif

ସ୍ଥିର atomic_int cpu_flags = -1;
ସ୍ଥିର atomic_int cpu_ଗଣନା = -1;

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା get_cpu_flags(ଶୂନ୍ୟ)
{
#ଯଦି ARCH_MIPS
    ଫେରନ୍ତୁ ff_get_cpu_flags_mips();
#ନଚେତଯଦି ARCH_AARCH64
    ଫେରନ୍ତୁ ff_get_cpu_flags_aarch64();
#ନଚେତଯଦି ARCH_ARM
    ଫେରନ୍ତୁ ff_get_cpu_flags_arm();
#ନଚେତଯଦି ARCH_PPC
    ଫେରନ୍ତୁ ff_get_cpu_flags_ppc();
#ନଚେତଯଦି ARCH_RISCV
    ଫେରନ୍ତୁ ff_get_cpu_flags_riscv();
#ନଚେତଯଦି ARCH_WASM
    ଫେରନ୍ତୁ ff_get_cpu_flags_wasm();
#ନଚେତଯଦି ARCH_X86
    ଫେରନ୍ତୁ ff_get_cpu_flags_x86();
#ନଚେତଯଦି ARCH_LOONGARCH
    ଫେରନ୍ତୁ ff_get_cpu_flags_loongarch();
#endif
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_force_cpu_flags(ପୂର୍ଣ୍ଣସଂଖ୍ୟା arg){
    ଯଦି (ARCH_X86 &&
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
        av_log(ଖାଲି, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_get_cpu_flags(ଶୂନ୍ୟ)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    ଯଦି (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    ଫେରନ୍ତୁ flags;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_parse_cpu_caps(unsigned *flags, ଅଚଳ ଅକ୍ଷର *s)
{
        ସ୍ଥିର ଅଚଳ AVOption cpuflags_opts[] = {
        { "flags"   , ଖାଲି, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#ଯଦି   ARCH_PPC
        { "altivec" , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#ନଚେତଯଦି ARCH_X86
        { "mmx"     , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#define CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#define CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#define CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#define CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#define CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#define CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#define CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#ନଚେତଯଦି ARCH_ARM
        { "armv5te",  ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#ନଚେତଯଦି ARCH_AARCH64
        { "armv8",    ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#ନଚେତଯଦି ARCH_MIPS
        { "mmi",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#ନଚେତଯଦି ARCH_LOONGARCH
        { "lsx",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#ନଚେତଯଦି ARCH_RISCV
        { "rvi",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#ନଚେତଯଦି ARCH_WASM
        { "simd128",  ଖାଲି, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { ଖାଲି },
    };
    ସ୍ଥିର ଅଚଳ AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    ଅଚଳ AVClass *pclass = &class;

    ଫେରନ୍ତୁ av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_cpu_ଗଣନା(ଶୂନ୍ୟ)
{
    ସ୍ଥିର atomic_int printed = 0;

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା nb_cpus = 1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2   = 0;
#ଯଦି HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#ଯଦି HAVE_SCHED_GETAFFINITY && defined(CPU_ଗଣନା)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    ଯଦି (!sched_getaffinity(0, ଆକାର(cpuset), &cpuset))
        nb_cpus = CPU_ଗଣନା(&cpuset);
#ନଚେତଯଦି HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    ଯଦି (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#ନଚେତଯଦି HAVE_SYSCTL && defined(HW_NCPUONLINE)
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = ଆକାର(nb_cpus);

    ଯଦି (sysctl(mib, 2, &nb_cpus, &len, ଖାଲି, 0) == -1)
        nb_cpus = 0;
#ନଚେତଯଦି HAVE_SYSCTL && defined(HW_NCPU)
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା mib[2] = { CTL_HW, HW_NCPU };
    size_t len = ଆକାର(nb_cpus);

    ଯଦି (sysctl(mib, 2, &nb_cpus, &len, ଖାଲି, 0) == -1)
        nb_cpus = 0;
#ନଚେତଯଦି HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#ନଚେତଯଦି HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#ନଚେତଯଦି HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_ସଂଖ୍ୟା_Of_Processors;
#endif

    ଯଦି (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(ଖାଲି, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    ଗଣନା_2 = atomic_load_explicit(&cpu_ଗଣନା, memory_order_relaxed);

    ଯଦି (ଗଣନା_2 > 0) {
        nb_cpus = ଗଣନା_2;
        av_log(ଖାଲି, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    ଫେରନ୍ତୁ nb_cpus;
}

ଶୂନ୍ୟ av_cpu_force_ଗଣନା(ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2)
{
    atomic_store_explicit(&cpu_ଗଣନା, ଗଣନା_2, memory_order_relaxed);
}

size_t av_cpu_max_align(ଶୂନ୍ୟ)
{
#ଯଦି ARCH_MIPS
    ଫେରନ୍ତୁ ff_get_cpu_max_align_mips();
#ନଚେତଯଦି ARCH_AARCH64
    ଫେରନ୍ତୁ ff_get_cpu_max_align_aarch64();
#ନଚେତଯଦି ARCH_ARM
    ଫେରନ୍ତୁ ff_get_cpu_max_align_arm();
#ନଚେତଯଦି ARCH_PPC
    ଫେରନ୍ତୁ ff_get_cpu_max_align_ppc();
#ନଚେତଯଦି ARCH_WASM
    ଫେରନ୍ତୁ ff_get_cpu_max_align_wasm();
#ନଚେତଯଦି ARCH_X86
    ଫେରନ୍ତୁ ff_get_cpu_max_align_x86();
#ନଚେତଯଦି ARCH_LOONGARCH
    ଫେରନ୍ତୁ ff_get_cpu_max_align_loongarch();
#endif

    ଫେରନ୍ତୁ 8;
}

#ଯଦି !ARCH_X86
unsigned long ff_getauxval(unsigned long type)
{
#ଯଦି HAVE_GETAUXVAL
    ଫେରନ୍ତୁ getauxval(type);
#ନଚେତଯଦି HAVE_ELF_AUX_INFO
    unsigned long aux = 0;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = elf_aux_info(type, &aux, ଆକାର(aux));
    ଯଦି (ret != 0) {
        errno = ret;
    }
    ଫେରନ୍ତୁ aux;
#ଅନ୍ୟଥା
    errno = ENOSYS;
    ଫେରନ୍ତୁ 0;
#endif
}
#endif

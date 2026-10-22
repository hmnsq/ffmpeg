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

#అన్తర్భావ "config.h"

#ఒకవేళ HAVE_SCHED_GETAFFINITY
#నిర్వచితం_కాకపోతే GNU_ఆధారం
# define GNU_ఆధారం
#అయితే_ముగింపు
#అన్తర్భావ <sched.h>
#అయితే_ముగింపు

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdatomic.h>

#అన్తర్భావ "attributes.h"
#అన్తర్భావ "cpu.h"
#అన్తర్భావ "cpu_internal.h"
#అన్తర్భావ "opt.h"
#అన్తర్భావ "common.h"

#ఒకవేళ HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#అన్తర్భావ <windows.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_SYSCTL
#ఒకవేళ HAVE_SYS_PARAM_H
#అన్తర్భావ <sys/param.h>
#అయితే_ముగింపు
#అన్తర్భావ <sys/types.h>
#అన్తర్భావ <sys/sysctl.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_UNISTD_H
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు

#ఒకవేళ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#అన్తర్భావ <sys/auxv.h>
#అయితే_ముగింపు

స్థిర atomic_int cpu_flags = -1;
స్థిర atomic_int cpu_లెక్క = -1;

స్థిర పూర్ణాంకం get_cpu_flags(శూన్య)
{
#ఒకవేళ ARCH_MIPS
    తిరిగి ff_get_cpu_flags_mips();
#లేదావేళ ARCH_AARCH64
    తిరిగి ff_get_cpu_flags_aarch64();
#లేదావేళ ARCH_ARM
    తిరిగి ff_get_cpu_flags_arm();
#లేదావేళ ARCH_PPC
    తిరిగి ff_get_cpu_flags_ppc();
#లేదావేళ ARCH_RISCV
    తిరిగి ff_get_cpu_flags_riscv();
#లేదావేళ ARCH_WASM
    తిరిగి ff_get_cpu_flags_wasm();
#లేదావేళ ARCH_X86
    తిరిగి ff_get_cpu_flags_x86();
#లేదావేళ ARCH_LOONGARCH
    తిరిగి ff_get_cpu_flags_loongarch();
#అయితే_ముగింపు
    తిరిగి 0;
}

శూన్య av_force_cpu_flags(పూర్ణాంకం arg){
    ఒకవేళ (ARCH_X86 &&
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
        av_log(ఖాళీ, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

పూర్ణాంకం av_get_cpu_flags(శూన్య)
{
    పూర్ణాంకం flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    ఒకవేళ (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    తిరిగి flags;
}

పూర్ణాంకం av_parse_cpu_caps(గుర్తులేని *flags, స్థిరరాశి అక్షరం *s)
{
        స్థిర స్థిరరాశి AVOption cpuflags_opts[] = {
        { "flags"   , ఖాళీ, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#ఒకవేళ   ARCH_PPC
        { "altivec" , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#లేదావేళ ARCH_X86
        { "mmx"     , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#నిర్వచించు CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#నిర్వచించు CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#నిర్వచించు CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#నిర్వచించు CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#నిర్వచించు CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#నిర్వచించు CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#నిర్వచించు CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#లేదావేళ ARCH_ARM
        { "armv5te",  ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#లేదావేళ ARCH_AARCH64
        { "armv8",    ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_చక్రీయ_తనిఖీ  },    .unit = "flags" },
        { "sme_i16i64", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#లేదావేళ ARCH_MIPS
        { "mmi",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#లేదావేళ ARCH_LOONGARCH
        { "lsx",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#లేదావేళ ARCH_RISCV
        { "rvi",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#లేదావేళ ARCH_WASM
        { "simd128",  ఖాళీ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#అయితే_ముగింపు
        { ఖాళీ },
    };
    స్థిర స్థిరరాశి AVClass class = {
        .class_name = "cpuflags",
        .అంశం_name  = av_default_అంశం_name,
        .option     = cpuflags_opts,
        .సంస్కరణ    = LIBAVUTIL_సంస్కరణ_INT,
    };
    స్థిరరాశి AVClass *pclass = &class;

    తిరిగి av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

పూర్ణాంకం av_cpu_లెక్క(శూన్య)
{
    స్థిర atomic_int printed = 0;

    పూర్ణాంకం nb_cpus = 1;
    పూర్ణాంకం లెక్క   = 0;
#ఒకవేళ HAVE_WINRT
    SYSTEM_INFO sysinfo;
#అయితే_ముగింపు
#ఒకవేళ HAVE_SCHED_GETAFFINITY && defined(CPU_లెక్క)
    cpu_సమితి_t cpuset;

    CPU_ZERO(&cpuset);

    ఒకవేళ (!sched_getaffinity(0, పరిమాణం(cpuset), &cpuset))
        nb_cpus = CPU_లెక్క(&cpuset);
#లేదావేళ HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    ఒకవేళ (Get_Process_Affinity_ముసుగు(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#లేదావేళ HAVE_SYSCTL && defined(HW_NCPUONLINE)
    పూర్ణాంకం mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = పరిమాణం(nb_cpus);

    ఒకవేళ (sysctl(mib, 2, &nb_cpus, &len, ఖాళీ, 0) == -1)
        nb_cpus = 0;
#లేదావేళ HAVE_SYSCTL && defined(HW_NCPU)
    పూర్ణాంకం mib[2] = { CTL_HW, HW_NCPU };
    size_t len = పరిమాణం(nb_cpus);

    ఒకవేళ (sysctl(mib, 2, &nb_cpus, &len, ఖాళీ, 0) == -1)
        nb_cpus = 0;
#లేదావేళ HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#లేదావేళ HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#లేదావేళ HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_సంఖ్య_యొక్క_Processors;
#అయితే_ముగింపు

    ఒకవేళ (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(ఖాళీ, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    లెక్క = atomic_load_explicit(&cpu_లెక్క, memory_order_relaxed);

    ఒకవేళ (లెక్క > 0) {
        nb_cpus = లెక్క;
        av_log(ఖాళీ, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    తిరిగి nb_cpus;
}

శూన్య av_cpu_force_లెక్క(పూర్ణాంకం లెక్క)
{
    atomic_store_explicit(&cpu_లెక్క, లెక్క, memory_order_relaxed);
}

size_t av_cpu_max_align(శూన్య)
{
#ఒకవేళ ARCH_MIPS
    తిరిగి ff_get_cpu_max_align_mips();
#లేదావేళ ARCH_AARCH64
    తిరిగి ff_get_cpu_max_align_aarch64();
#లేదావేళ ARCH_ARM
    తిరిగి ff_get_cpu_max_align_arm();
#లేదావేళ ARCH_PPC
    తిరిగి ff_get_cpu_max_align_ppc();
#లేదావేళ ARCH_WASM
    తిరిగి ff_get_cpu_max_align_wasm();
#లేదావేళ ARCH_X86
    తిరిగి ff_get_cpu_max_align_x86();
#లేదావేళ ARCH_LOONGARCH
    తిరిగి ff_get_cpu_max_align_loongarch();
#అయితే_ముగింపు

    తిరిగి 8;
}

#ఒకవేళ !ARCH_X86
గుర్తులేని దీర్ఘ ff_getauxval(గుర్తులేని దీర్ఘ type)
{
#ఒకవేళ HAVE_GETAUXVAL
    తిరిగి getauxval(type);
#లేదావేళ HAVE_ELF_AUX_INFO
    గుర్తులేని దీర్ఘ aux = 0;
    పూర్ణాంకం ret = elf_aux_info(type, &aux, పరిమాణం(aux));
    ఒకవేళ (ret != 0) {
        errno = ret;
    }
    తిరిగి aux;
#లేకపోతే
    errno = ENOSYS;
    తిరిగి 0;
#అయితే_ముగింపు
}
#అయితే_ముగింపు

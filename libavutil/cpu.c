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

#અન્તર્ભાવ "config.h"

#જો HAVE_SCHED_GETAFFINITY
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#અન્તર્ભાવ <sched.h>
#endif

#અન્તર્ભાવ <stddef.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdatomic.h>

#અન્તર્ભાવ "attributes.h"
#અન્તર્ભાવ "cpu.h"
#અન્તર્ભાવ "cpu_internal.h"
#અન્તર્ભાવ "opt.h"
#અન્તર્ભાવ "common.h"

#જો HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#અન્તર્ભાવ <windows.h>
#endif
#જો HAVE_SYSCTL
#જો HAVE_SYS_PARAM_H
#અન્તર્ભાવ <sys/param.h>
#endif
#અન્તર્ભાવ <sys/types.h>
#અન્તર્ભાવ <sys/sysctl.h>
#endif
#જો HAVE_UNISTD_H
#અન્તર્ભાવ <unistd.h>
#endif

#જો HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#અન્તર્ભાવ <sys/auxv.h>
#endif

સ્થિર atomic_int cpu_flags = -1;
સ્થિર atomic_int cpu_ગણતરી = -1;

સ્થિર પૂર્ણાંક get_cpu_flags(શૂન્ય)
{
#જો ARCH_MIPS
    પાછા ff_get_cpu_flags_mips();
#અથવાજો ARCH_AARCH64
    પાછા ff_get_cpu_flags_aarch64();
#અથવાજો ARCH_ARM
    પાછા ff_get_cpu_flags_arm();
#અથવાજો ARCH_PPC
    પાછા ff_get_cpu_flags_ppc();
#અથવાજો ARCH_RISCV
    પાછા ff_get_cpu_flags_riscv();
#અથવાજો ARCH_WASM
    પાછા ff_get_cpu_flags_wasm();
#અથવાજો ARCH_X86
    પાછા ff_get_cpu_flags_x86();
#અથવાજો ARCH_LOONGARCH
    પાછા ff_get_cpu_flags_loongarch();
#endif
    પાછા 0;
}

શૂન્ય av_force_cpu_flags(પૂર્ણાંક arg){
    જો (ARCH_X86 &&
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
        av_log(ખાલી, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

પૂર્ણાંક av_get_cpu_flags(શૂન્ય)
{
    પૂર્ણાંક flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    જો (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    પાછા flags;
}

પૂર્ણાંક av_parse_cpu_caps(unsigned *flags, અચલ અક્ષર *s)
{
        સ્થિર અચલ AVOption cpuflags_opts[] = {
        { "flags"   , ખાલી, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#જો   ARCH_PPC
        { "altivec" , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#અથવાજો ARCH_X86
        { "mmx"     , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#define CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#define CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#define CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#define CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#define CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#define CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#define CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#અથવાજો ARCH_ARM
        { "armv5te",  ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#અથવાજો ARCH_AARCH64
        { "armv8",    ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#અથવાજો ARCH_MIPS
        { "mmi",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#અથવાજો ARCH_LOONGARCH
        { "lsx",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#અથવાજો ARCH_RISCV
        { "rvi",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#અથવાજો ARCH_WASM
        { "simd128",  ખાલી, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { ખાલી },
    };
    સ્થિર અચલ AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    અચલ AVClass *pclass = &class;

    પાછા av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

પૂર્ણાંક av_cpu_ગણતરી(શૂન્ય)
{
    સ્થિર atomic_int printed = 0;

    પૂર્ણાંક nb_cpus = 1;
    પૂર્ણાંક ગણતરી   = 0;
#જો HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#જો HAVE_SCHED_GETAFFINITY && defined(CPU_ગણતરી)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    જો (!sched_getaffinity(0, કદ(cpuset), &cpuset))
        nb_cpus = CPU_ગણતરી(&cpuset);
#અથવાજો HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    જો (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#અથવાજો HAVE_SYSCTL && defined(HW_NCPUONLINE)
    પૂર્ણાંક mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = કદ(nb_cpus);

    જો (sysctl(mib, 2, &nb_cpus, &len, ખાલી, 0) == -1)
        nb_cpus = 0;
#અથવાજો HAVE_SYSCTL && defined(HW_NCPU)
    પૂર્ણાંક mib[2] = { CTL_HW, HW_NCPU };
    size_t len = કદ(nb_cpus);

    જો (sysctl(mib, 2, &nb_cpus, &len, ખાલી, 0) == -1)
        nb_cpus = 0;
#અથવાજો HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#અથવાજો HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#અથવાજો HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_સંખ્યા_Of_Processors;
#endif

    જો (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(ખાલી, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    ગણતરી = atomic_load_explicit(&cpu_ગણતરી, memory_order_relaxed);

    જો (ગણતરી > 0) {
        nb_cpus = ગણતરી;
        av_log(ખાલી, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    પાછા nb_cpus;
}

શૂન્ય av_cpu_force_ગણતરી(પૂર્ણાંક ગણતરી)
{
    atomic_store_explicit(&cpu_ગણતરી, ગણતરી, memory_order_relaxed);
}

size_t av_cpu_max_align(શૂન્ય)
{
#જો ARCH_MIPS
    પાછા ff_get_cpu_max_align_mips();
#અથવાજો ARCH_AARCH64
    પાછા ff_get_cpu_max_align_aarch64();
#અથવાજો ARCH_ARM
    પાછા ff_get_cpu_max_align_arm();
#અથવાજો ARCH_PPC
    પાછા ff_get_cpu_max_align_ppc();
#અથવાજો ARCH_WASM
    પાછા ff_get_cpu_max_align_wasm();
#અથવાજો ARCH_X86
    પાછા ff_get_cpu_max_align_x86();
#અથવાજો ARCH_LOONGARCH
    પાછા ff_get_cpu_max_align_loongarch();
#endif

    પાછા 8;
}

#જો !ARCH_X86
unsigned long ff_getauxval(unsigned long type)
{
#જો HAVE_GETAUXVAL
    પાછા getauxval(type);
#અથવાજો HAVE_ELF_AUX_INFO
    unsigned long aux = 0;
    પૂર્ણાંક ret = elf_aux_info(type, &aux, કદ(aux));
    જો (ret != 0) {
        errno = ret;
    }
    પાછા aux;
#નહીંતર
    errno = ENOSYS;
    પાછા 0;
#endif
}
#endif

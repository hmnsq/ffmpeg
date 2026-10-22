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

#अन्तर्भाव "config.h"

#जइ HAVE_SCHED_GETAFFINITY
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#अन्तर्भाव <sched.h>
#endif

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdatomic.h>

#अन्तर्भाव "attributes.h"
#अन्तर्भाव "cpu.h"
#अन्तर्भाव "cpu_internal.h"
#अन्तर्भाव "opt.h"
#अन्तर्भाव "common.h"

#जइ HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#अन्तर्भाव <windows.h>
#endif
#जइ HAVE_SYSCTL
#जइ HAVE_SYS_PARAM_H
#अन्तर्भाव <sys/param.h>
#endif
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/sysctl.h>
#endif
#जइ HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif

#जइ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#अन्तर्भाव <sys/auxv.h>
#endif

स्थिर atomic_int cpu_flags = -1;
स्थिर atomic_int cpu_गणनम् = -1;

स्थिर पूर्णाङ्क get_cpu_flags(शून्य)
{
#जइ ARCH_MIPS
    प्रत्यागम ff_get_cpu_flags_mips();
#नोचेद्यदि ARCH_AARCH64
    प्रत्यागम ff_get_cpu_flags_aarch64();
#नोचेद्यदि ARCH_ARM
    प्रत्यागम ff_get_cpu_flags_arm();
#नोचेद्यदि ARCH_PPC
    प्रत्यागम ff_get_cpu_flags_ppc();
#नोचेद्यदि ARCH_RISCV
    प्रत्यागम ff_get_cpu_flags_riscv();
#नोचेद्यदि ARCH_WASM
    प्रत्यागम ff_get_cpu_flags_wasm();
#नोचेद्यदि ARCH_X86
    प्रत्यागम ff_get_cpu_flags_x86();
#नोचेद्यदि ARCH_LOONGARCH
    प्रत्यागम ff_get_cpu_flags_loongarch();
#endif
    प्रत्यागम 0;
}

शून्य av_force_cpu_flags(पूर्णाङ्क arg){
    जइ (ARCH_X86 &&
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
        av_log(रिक्त, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

पूर्णाङ्क av_get_cpu_flags(शून्य)
{
    पूर्णाङ्क flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    जइ (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    प्रत्यागम flags;
}

पूर्णाङ्क av_parse_cpu_caps(unsigned *flags, ध्रुव वर्ण *s)
{
        स्थिर ध्रुव AVOption cpuflags_opts[] = {
        { "flags"   , रिक्त, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#जइ   ARCH_PPC
        { "altivec" , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#नोचेद्यदि ARCH_X86
        { "mmx"     , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#define CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#define CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#define CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#define CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#define CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#define CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#define CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#नोचेद्यदि ARCH_ARM
        { "armv5te",  रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#नोचेद्यदि ARCH_AARCH64
        { "armv8",    रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#नोचेद्यदि ARCH_MIPS
        { "mmi",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#नोचेद्यदि ARCH_LOONGARCH
        { "lsx",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#नोचेद्यदि ARCH_RISCV
        { "rvi",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#नोचेद्यदि ARCH_WASM
        { "simd128",  रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { रिक्त },
    };
    स्थिर ध्रुव AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    ध्रुव AVClass *pclass = &class;

    प्रत्यागम av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

पूर्णाङ्क av_cpu_गणनम्(शून्य)
{
    स्थिर atomic_int printed = 0;

    पूर्णाङ्क nb_cpus = 1;
    पूर्णाङ्क गणनम्   = 0;
#जइ HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#जइ HAVE_SCHED_GETAFFINITY && defined(CPU_गणनम्)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    जइ (!sched_getaffinity(0, परिमाण(cpuset), &cpuset))
        nb_cpus = CPU_गणनम्(&cpuset);
#नोचेद्यदि HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    जइ (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#नोचेद्यदि HAVE_SYSCTL && defined(HW_NCPUONLINE)
    पूर्णाङ्क mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = परिमाण(nb_cpus);

    जइ (sysctl(mib, 2, &nb_cpus, &len, रिक्त, 0) == -1)
        nb_cpus = 0;
#नोचेद्यदि HAVE_SYSCTL && defined(HW_NCPU)
    पूर्णाङ्क mib[2] = { CTL_HW, HW_NCPU };
    size_t len = परिमाण(nb_cpus);

    जइ (sysctl(mib, 2, &nb_cpus, &len, रिक्त, 0) == -1)
        nb_cpus = 0;
#नोचेद्यदि HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#नोचेद्यदि HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#नोचेद्यदि HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_सङ्ख्या_Of_Processors;
#endif

    जइ (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(रिक्त, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    गणनम् = atomic_load_explicit(&cpu_गणनम्, memory_order_relaxed);

    जइ (गणनम् > 0) {
        nb_cpus = गणनम्;
        av_log(रिक्त, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    प्रत्यागम nb_cpus;
}

शून्य av_cpu_force_गणनम्(पूर्णाङ्क गणनम्)
{
    atomic_store_explicit(&cpu_गणनम्, गणनम्, memory_order_relaxed);
}

size_t av_cpu_max_align(शून्य)
{
#जइ ARCH_MIPS
    प्रत्यागम ff_get_cpu_max_align_mips();
#नोचेद्यदि ARCH_AARCH64
    प्रत्यागम ff_get_cpu_max_align_aarch64();
#नोचेद्यदि ARCH_ARM
    प्रत्यागम ff_get_cpu_max_align_arm();
#नोचेद्यदि ARCH_PPC
    प्रत्यागम ff_get_cpu_max_align_ppc();
#नोचेद्यदि ARCH_WASM
    प्रत्यागम ff_get_cpu_max_align_wasm();
#नोचेद्यदि ARCH_X86
    प्रत्यागम ff_get_cpu_max_align_x86();
#नोचेद्यदि ARCH_LOONGARCH
    प्रत्यागम ff_get_cpu_max_align_loongarch();
#endif

    प्रत्यागम 8;
}

#जइ !ARCH_X86
unsigned long ff_getauxval(unsigned long type)
{
#जइ HAVE_GETAUXVAL
    प्रत्यागम getauxval(type);
#नोचेद्यदि HAVE_ELF_AUX_INFO
    unsigned long aux = 0;
    पूर्णाङ्क ret = elf_aux_info(type, &aux, परिमाण(aux));
    जइ (ret != 0) {
        errno = ret;
    }
    प्रत्यागम aux;
#अण्णहा
    errno = ENOSYS;
    प्रत्यागम 0;
#endif
}
#endif

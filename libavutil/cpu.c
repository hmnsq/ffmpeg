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

#जर HAVE_SCHED_GETAFFINITY
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

#जर HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#अन्तर्भाव <windows.h>
#endif
#जर HAVE_SYSCTL
#जर HAVE_SYS_PARAM_H
#अन्तर्भाव <sys/param.h>
#endif
#अन्तर्भाव <sys/types.h>
#अन्तर्भाव <sys/sysctl.h>
#endif
#जर HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif

#जर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#अन्तर्भाव <sys/auxv.h>
#endif

स्थिर atomic_int cpu_flags = -1;
स्थिर atomic_int cpu_मोजणी = -1;

स्थिर पूर्णांक get_cpu_flags(शून्य)
{
#जर ARCH_MIPS
    परत ff_get_cpu_flags_mips();
#किंवाजर ARCH_AARCH64
    परत ff_get_cpu_flags_aarch64();
#किंवाजर ARCH_ARM
    परत ff_get_cpu_flags_arm();
#किंवाजर ARCH_PPC
    परत ff_get_cpu_flags_ppc();
#किंवाजर ARCH_RISCV
    परत ff_get_cpu_flags_riscv();
#किंवाजर ARCH_WASM
    परत ff_get_cpu_flags_wasm();
#किंवाजर ARCH_X86
    परत ff_get_cpu_flags_x86();
#किंवाजर ARCH_LOONGARCH
    परत ff_get_cpu_flags_loongarch();
#endif
    परत 0;
}

शून्य av_force_cpu_flags(पूर्णांक arg){
    जर (ARCH_X86 &&
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

पूर्णांक av_get_cpu_flags(शून्य)
{
    पूर्णांक flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    जर (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    परत flags;
}

पूर्णांक av_parse_cpu_caps(अचिन्हित *flags, स्थिरांक अक्षर *s)
{
        स्थिर स्थिरांक AVOption cpuflags_opts[] = {
        { "flags"   , रिक्त, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#जर   ARCH_PPC
        { "altivec" , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#किंवाजर ARCH_X86
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
#किंवाजर ARCH_ARM
        { "armv5te",  रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#किंवाजर ARCH_AARCH64
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
#किंवाजर ARCH_MIPS
        { "mmi",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#किंवाजर ARCH_LOONGARCH
        { "lsx",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#किंवाजर ARCH_RISCV
        { "rvi",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#किंवाजर ARCH_WASM
        { "simd128",  रिक्त, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { रिक्त },
    };
    स्थिर स्थिरांक AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    स्थिरांक AVClass *pclass = &class;

    परत av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

पूर्णांक av_cpu_मोजणी(शून्य)
{
    स्थिर atomic_int printed = 0;

    पूर्णांक nb_cpus = 1;
    पूर्णांक मोजणी   = 0;
#जर HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#जर HAVE_SCHED_GETAFFINITY && defined(CPU_मोजणी)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    जर (!sched_getaffinity(0, आकार(cpuset), &cpuset))
        nb_cpus = CPU_मोजणी(&cpuset);
#किंवाजर HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    जर (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#किंवाजर HAVE_SYSCTL && defined(HW_NCPUONLINE)
    पूर्णांक mib[2] = { CTL_HW, HW_NCPUONLINE };
    माप_प्रकार len = आकार(nb_cpus);

    जर (sysctl(mib, 2, &nb_cpus, &len, रिक्त, 0) == -1)
        nb_cpus = 0;
#किंवाजर HAVE_SYSCTL && defined(HW_NCPU)
    पूर्णांक mib[2] = { CTL_HW, HW_NCPU };
    माप_प्रकार len = आकार(nb_cpus);

    जर (sysctl(mib, 2, &nb_cpus, &len, रिक्त, 0) == -1)
        nb_cpus = 0;
#किंवाजर HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#किंवाजर HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#किंवाजर HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_संख्या_Of_Processors;
#endif

    जर (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(रिक्त, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    मोजणी = atomic_load_explicit(&cpu_मोजणी, memory_order_relaxed);

    जर (मोजणी > 0) {
        nb_cpus = मोजणी;
        av_log(रिक्त, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    परत nb_cpus;
}

शून्य av_cpu_force_मोजणी(पूर्णांक मोजणी)
{
    atomic_store_explicit(&cpu_मोजणी, मोजणी, memory_order_relaxed);
}

माप_प्रकार av_cpu_max_align(शून्य)
{
#जर ARCH_MIPS
    परत ff_get_cpu_max_align_mips();
#किंवाजर ARCH_AARCH64
    परत ff_get_cpu_max_align_aarch64();
#किंवाजर ARCH_ARM
    परत ff_get_cpu_max_align_arm();
#किंवाजर ARCH_PPC
    परत ff_get_cpu_max_align_ppc();
#किंवाजर ARCH_WASM
    परत ff_get_cpu_max_align_wasm();
#किंवाजर ARCH_X86
    परत ff_get_cpu_max_align_x86();
#किंवाजर ARCH_LOONGARCH
    परत ff_get_cpu_max_align_loongarch();
#endif

    परत 8;
}

#जर !ARCH_X86
अचिन्हित दीर्घ ff_getauxval(अचिन्हित दीर्घ type)
{
#जर HAVE_GETAUXVAL
    परत getauxval(type);
#किंवाजर HAVE_ELF_AUX_INFO
    अचिन्हित दीर्घ aux = 0;
    पूर्णांक ret = elf_aux_info(type, &aux, आकार(aux));
    जर (ret != 0) {
        त्रुटि_सं = ret;
    }
    परत aux;
#अन्यथा
    त्रुटि_सं = ENOSYS;
    परत 0;
#endif
}
#endif

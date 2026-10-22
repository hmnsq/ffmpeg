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

#समावेश "config.h"

#अगर HAVE_SCHED_GETAFFINITY
#अगर_अघोषित _GNU_SOURCE
# define _GNU_SOURCE
#पूर्ण_अगर
#समावेश <sched.h>
#पूर्ण_अगर

#समावेश <stddef.h>
#समावेश <stdint.h>
#समावेश <stdatomic.h>

#समावेश "attributes.h"
#समावेश "cpu.h"
#समावेश "cpu_internal.h"
#समावेश "opt.h"
#समावेश "common.h"

#अगर HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#समावेश <windows.h>
#पूर्ण_अगर
#अगर HAVE_SYSCTL
#अगर HAVE_SYS_PARAM_H
#समावेश <sys/param.h>
#पूर्ण_अगर
#समावेश <sys/types.h>
#समावेश <sys/sysctl.h>
#पूर्ण_अगर
#अगर HAVE_UNISTD_H
#समावेश <unistd.h>
#पूर्ण_अगर

#अगर HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#समावेश <sys/auxv.h>
#पूर्ण_अगर

अटल atomic_int cpu_flags = -1;
अटल atomic_int cpu_गिनती = -1;

अटल पूर्णांक get_cpu_flags(व्योम)
{
#अगर ARCH_MIPS
    वापस ff_get_cpu_flags_mips();
#या_अगर ARCH_AARCH64
    वापस ff_get_cpu_flags_aarch64();
#या_अगर ARCH_ARM
    वापस ff_get_cpu_flags_arm();
#या_अगर ARCH_PPC
    वापस ff_get_cpu_flags_ppc();
#या_अगर ARCH_RISCV
    वापस ff_get_cpu_flags_riscv();
#या_अगर ARCH_WASM
    वापस ff_get_cpu_flags_wasm();
#या_अगर ARCH_X86
    वापस ff_get_cpu_flags_x86();
#या_अगर ARCH_LOONGARCH
    वापस ff_get_cpu_flags_loongarch();
#पूर्ण_अगर
    वापस 0;
}

व्योम av_force_cpu_flags(पूर्णांक arg){
    अगर (ARCH_X86 &&
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
        av_log(शून्य, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

पूर्णांक av_get_cpu_flags(व्योम)
{
    पूर्णांक flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    अगर (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    वापस flags;
}

पूर्णांक av_parse_cpu_caps(अचिन्हित *flags, स्थिर अक्षर *s)
{
        अटल स्थिर AVOption cpuflags_opts[] = {
        { "flags"   , शून्य, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#अगर   ARCH_PPC
        { "altivec" , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#या_अगर ARCH_X86
        { "mmx"     , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#घोषणा CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#घोषणा CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#घोषणा CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#घोषणा CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#घोषणा CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#घोषणा CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#घोषणा CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#या_अगर ARCH_ARM
        { "armv5te",  शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#या_अगर ARCH_AARCH64
        { "armv8",    शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#या_अगर ARCH_MIPS
        { "mmi",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#या_अगर ARCH_LOONGARCH
        { "lsx",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#या_अगर ARCH_RISCV
        { "rvi",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#या_अगर ARCH_WASM
        { "simd128",  शून्य, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#पूर्ण_अगर
        { शून्य },
    };
    अटल स्थिर AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    स्थिर AVClass *pclass = &class;

    वापस av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

पूर्णांक av_cpu_गिनती(व्योम)
{
    अटल atomic_int printed = 0;

    पूर्णांक nb_cpus = 1;
    पूर्णांक गिनती   = 0;
#अगर HAVE_WINRT
    SYSTEM_INFO sysinfo;
#पूर्ण_अगर
#अगर HAVE_SCHED_GETAFFINITY && defined(CPU_गिनती)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    अगर (!sched_getaffinity(0, माप(cpuset), &cpuset))
        nb_cpus = CPU_गिनती(&cpuset);
#या_अगर HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    अगर (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#या_अगर HAVE_SYSCTL && defined(HW_NCPUONLINE)
    पूर्णांक mib[2] = { CTL_HW, HW_NCPUONLINE };
    माप_प्रकार len = माप(nb_cpus);

    अगर (sysctl(mib, 2, &nb_cpus, &len, शून्य, 0) == -1)
        nb_cpus = 0;
#या_अगर HAVE_SYSCTL && defined(HW_NCPU)
    पूर्णांक mib[2] = { CTL_HW, HW_NCPU };
    माप_प्रकार len = माप(nb_cpus);

    अगर (sysctl(mib, 2, &nb_cpus, &len, शून्य, 0) == -1)
        nb_cpus = 0;
#या_अगर HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#या_अगर HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#या_अगर HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_संख्या_Of_Processors;
#पूर्ण_अगर

    अगर (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(शून्य, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    गिनती = atomic_load_explicit(&cpu_गिनती, memory_order_relaxed);

    अगर (गिनती > 0) {
        nb_cpus = गिनती;
        av_log(शून्य, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    वापस nb_cpus;
}

व्योम av_cpu_force_गिनती(पूर्णांक गिनती)
{
    atomic_store_explicit(&cpu_गिनती, गिनती, memory_order_relaxed);
}

माप_प्रकार av_cpu_max_align(व्योम)
{
#अगर ARCH_MIPS
    वापस ff_get_cpu_max_align_mips();
#या_अगर ARCH_AARCH64
    वापस ff_get_cpu_max_align_aarch64();
#या_अगर ARCH_ARM
    वापस ff_get_cpu_max_align_arm();
#या_अगर ARCH_PPC
    वापस ff_get_cpu_max_align_ppc();
#या_अगर ARCH_WASM
    वापस ff_get_cpu_max_align_wasm();
#या_अगर ARCH_X86
    वापस ff_get_cpu_max_align_x86();
#या_अगर ARCH_LOONGARCH
    वापस ff_get_cpu_max_align_loongarch();
#पूर्ण_अगर

    वापस 8;
}

#अगर !ARCH_X86
अचिन्हित दीर्घ ff_getauxval(अचिन्हित दीर्घ type)
{
#अगर HAVE_GETAUXVAL
    वापस getauxval(type);
#या_अगर HAVE_ELF_AUX_INFO
    अचिन्हित दीर्घ aux = 0;
    पूर्णांक ret = elf_aux_info(type, &aux, माप(aux));
    अगर (ret != 0) {
        त्रुटि_सं = ret;
    }
    वापस aux;
#अन्यथा
    त्रुटि_सं = ENOSYS;
    वापस 0;
#पूर्ण_अगर
}
#पूर्ण_अगर

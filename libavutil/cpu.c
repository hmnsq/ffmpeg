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

#ضمن "config.h"

#إذا HAVE_SCHED_GETAFFINITY
#که_نه_تعریف_شوی GNU_سرچینه
# define GNU_سرچینه
#د_که_پای
#ضمن <sched.h>
#د_که_پای

#ضمن <stddef.h>
#ضمن <stdint.h>
#ضمن <stdatomic.h>

#ضمن "attributes.h"
#ضمن "cpu.h"
#ضمن "cpu_internal.h"
#ضمن "opt.h"
#ضمن "common.h"

#إذا HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#ضمن <windows.h>
#د_که_پای
#إذا HAVE_SYSCTL
#إذا HAVE_SYS_PARAM_H
#ضمن <sys/param.h>
#د_که_پای
#ضمن <sys/types.h>
#ضمن <sys/sysctl.h>
#د_که_پای
#إذا HAVE_UNISTD_H
#ضمن <unistd.h>
#د_که_پای

#إذا HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ضمن <sys/auxv.h>
#د_که_پای

ساكن atomic_int cpu_flags = -1;
ساكن atomic_int cpu_شمېر = -1;

ساكن صحيح get_cpu_flags(فراغ)
{
#إذا ARCH_MIPS
    أرجع ff_get_cpu_flags_mips();
#وإلاإذا ARCH_AARCH64
    أرجع ff_get_cpu_flags_aarch64();
#وإلاإذا ARCH_ARM
    أرجع ff_get_cpu_flags_arm();
#وإلاإذا ARCH_PPC
    أرجع ff_get_cpu_flags_ppc();
#وإلاإذا ARCH_RISCV
    أرجع ff_get_cpu_flags_riscv();
#وإلاإذا ARCH_WASM
    أرجع ff_get_cpu_flags_wasm();
#وإلاإذا ARCH_X86
    أرجع ff_get_cpu_flags_x86();
#وإلاإذا ARCH_LOONGARCH
    أرجع ff_get_cpu_flags_loongarch();
#د_که_پای
    أرجع 0;
}

فراغ av_force_cpu_flags(صحيح arg){
    إذا (ARCH_X86 &&
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
        av_log(عدم, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

صحيح av_get_cpu_flags(فراغ)
{
    صحيح flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    إذا (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    أرجع flags;
}

صحيح av_parse_cpu_caps(بینښه *flags, ثابت حرف *s)
{
        ساكن ثابت AVOption cpuflags_opts[] = {
        { "flags"   , عدم, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#إذا   ARCH_PPC
        { "altivec" , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#وإلاإذا ARCH_X86
        { "mmx"     , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#تعریف_کړه CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#تعریف_کړه CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#تعریف_کړه CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#تعریف_کړه CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#تعریف_کړه CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#تعریف_کړه CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#تعریف_کړه CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   عدم, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       عدم, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#وإلاإذا ARCH_ARM
        { "armv5te",  عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#وإلاإذا ARCH_AARCH64
        { "armv8",    عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_دوراني_ازموینه  },    .unit = "flags" },
        { "sme_i16i64", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#وإلاإذا ARCH_MIPS
        { "mmi",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#وإلاإذا ARCH_LOONGARCH
        { "lsx",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#وإلاإذا ARCH_RISCV
        { "rvi",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#وإلاإذا ARCH_WASM
        { "simd128",  عدم, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#د_که_پای
        { عدم },
    };
    ساكن ثابت AVClass class = {
        .class_name = "cpuflags",
        .توکی_name  = av_default_توکی_name,
        .option     = cpuflags_opts,
        .نسخه    = LIBAVUTIL_نسخه_INT,
    };
    ثابت AVClass *pclass = &class;

    أرجع av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

صحيح av_cpu_شمېر(فراغ)
{
    ساكن atomic_int printed = 0;

    صحيح nb_cpus = 1;
    صحيح شمېر   = 0;
#إذا HAVE_WINRT
    SYSTEM_INFO sysinfo;
#د_که_پای
#إذا HAVE_SCHED_GETAFFINITY && defined(CPU_شمېر)
    cpu_سېټ_t cpuset;

    CPU_ZERO(&cpuset);

    إذا (!sched_getaffinity(0, حجم(cpuset), &cpuset))
        nb_cpus = CPU_شمېر(&cpuset);
#وإلاإذا HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    إذا (Get_Process_Affinity_ماسک(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#وإلاإذا HAVE_SYSCTL && defined(HW_NCPUONLINE)
    صحيح mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = حجم(nb_cpus);

    إذا (sysctl(mib, 2, &nb_cpus, &len, عدم, 0) == -1)
        nb_cpus = 0;
#وإلاإذا HAVE_SYSCTL && defined(HW_NCPU)
    صحيح mib[2] = { CTL_HW, HW_NCPU };
    size_t len = حجم(nb_cpus);

    إذا (sysctl(mib, 2, &nb_cpus, &len, عدم, 0) == -1)
        nb_cpus = 0;
#وإلاإذا HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#وإلاإذا HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#وإلاإذا HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_شمېره_د_Processors;
#د_که_پای

    إذا (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(عدم, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    شمېر = atomic_load_explicit(&cpu_شمېر, memory_order_relaxed);

    إذا (شمېر > 0) {
        nb_cpus = شمېر;
        av_log(عدم, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    أرجع nb_cpus;
}

فراغ av_cpu_force_شمېر(صحيح شمېر)
{
    atomic_store_explicit(&cpu_شمېر, شمېر, memory_order_relaxed);
}

size_t av_cpu_max_align(فراغ)
{
#إذا ARCH_MIPS
    أرجع ff_get_cpu_max_align_mips();
#وإلاإذا ARCH_AARCH64
    أرجع ff_get_cpu_max_align_aarch64();
#وإلاإذا ARCH_ARM
    أرجع ff_get_cpu_max_align_arm();
#وإلاإذا ARCH_PPC
    أرجع ff_get_cpu_max_align_ppc();
#وإلاإذا ARCH_WASM
    أرجع ff_get_cpu_max_align_wasm();
#وإلاإذا ARCH_X86
    أرجع ff_get_cpu_max_align_x86();
#وإلاإذا ARCH_LOONGARCH
    أرجع ff_get_cpu_max_align_loongarch();
#د_که_پای

    أرجع 8;
}

#إذا !ARCH_X86
بینښه اوږد ff_getauxval(بینښه اوږد type)
{
#إذا HAVE_GETAUXVAL
    أرجع getauxval(type);
#وإلاإذا HAVE_ELF_AUX_INFO
    بینښه اوږد aux = 0;
    صحيح ret = elf_aux_info(type, &aux, حجم(aux));
    إذا (ret != 0) {
        errno = ret;
    }
    أرجع aux;
#وإلا
    errno = ENOSYS;
    أرجع 0;
#د_که_پای
}
#د_که_پای

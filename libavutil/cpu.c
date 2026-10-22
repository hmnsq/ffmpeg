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

#شامل "config.h"

#اگر HAVE_SCHED_GETAFFINITY
#اگر_غیر_تعریف_شدہ GNU_ماخذ
# define GNU_ماخذ
#اگر_ختم
#شامل <sched.h>
#اگر_ختم

#شامل <stddef.h>
#شامل <stdint.h>
#شامل <stdatomic.h>

#شامل "attributes.h"
#شامل "cpu.h"
#شامل "cpu_internal.h"
#شامل "opt.h"
#شامل "common.h"

#اگر HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#شامل <windows.h>
#اگر_ختم
#اگر HAVE_SYSCTL
#اگر HAVE_SYS_PARAM_H
#شامل <sys/param.h>
#اگر_ختم
#شامل <sys/types.h>
#شامل <sys/sysctl.h>
#اگر_ختم
#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#اگر_ختم

#اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#شامل <sys/auxv.h>
#اگر_ختم

ساکن atomic_int cpu_flags = -1;
ساکن atomic_int cpu_گنتی = -1;

ساکن صحیح get_cpu_flags(خالی)
{
#اگر ARCH_MIPS
    واپس ff_get_cpu_flags_mips();
#وگرنہ_اگر ARCH_AARCH64
    واپس ff_get_cpu_flags_aarch64();
#وگرنہ_اگر ARCH_ARM
    واپس ff_get_cpu_flags_arm();
#وگرنہ_اگر ARCH_PPC
    واپس ff_get_cpu_flags_ppc();
#وگرنہ_اگر ARCH_RISCV
    واپس ff_get_cpu_flags_riscv();
#وگرنہ_اگر ARCH_WASM
    واپس ff_get_cpu_flags_wasm();
#وگرنہ_اگر ARCH_X86
    واپس ff_get_cpu_flags_x86();
#وگرنہ_اگر ARCH_LOONGARCH
    واپس ff_get_cpu_flags_loongarch();
#اگر_ختم
    واپس 0;
}

خالی av_force_cpu_flags(صحیح arg){
    اگر (ARCH_X86 &&
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
        av_log(تہی, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

صحیح av_get_cpu_flags(خالی)
{
    صحیح flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    اگر (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    واپس flags;
}

صحیح av_parse_cpu_caps(غیرعلامتی *flags, ثابت حرف *s)
{
        ساکن ثابت AVOption cpuflags_opts[] = {
        { "flags"   , تہی, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#اگر   ARCH_PPC
        { "altivec" , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#وگرنہ_اگر ARCH_X86
        { "mmx"     , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#تعریف_کرو CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#تعریف_کرو CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#تعریف_کرو CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#تعریف_کرو CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#تعریف_کرو CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#تعریف_کرو CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#تعریف_کرو CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   تہی, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       تہی, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#وگرنہ_اگر ARCH_ARM
        { "armv5te",  تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#وگرنہ_اگر ARCH_AARCH64
        { "armv8",    تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_چکری_جانچ  },    .unit = "flags" },
        { "sme_i16i64", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#وگرنہ_اگر ARCH_MIPS
        { "mmi",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#وگرنہ_اگر ARCH_LOONGARCH
        { "lsx",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#وگرنہ_اگر ARCH_RISCV
        { "rvi",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#وگرنہ_اگر ARCH_WASM
        { "simd128",  تہی, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#اگر_ختم
        { تہی },
    };
    ساکن ثابت AVClass class = {
        .class_name = "cpuflags",
        .شے_name  = av_default_شے_name,
        .option     = cpuflags_opts,
        .نسخہ    = LIBAVUTIL_نسخہ_INT,
    };
    ثابت AVClass *pclass = &class;

    واپس av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

صحیح av_cpu_گنتی(خالی)
{
    ساکن atomic_int printed = 0;

    صحیح nb_cpus = 1;
    صحیح گنتی   = 0;
#اگر HAVE_WINRT
    SYSTEM_INFO sysinfo;
#اگر_ختم
#اگر HAVE_SCHED_GETAFFINITY && defined(CPU_گنتی)
    cpu_سیٹ_t cpuset;

    CPU_ZERO(&cpuset);

    اگر (!sched_getaffinity(0, حجم(cpuset), &cpuset))
        nb_cpus = CPU_گنتی(&cpuset);
#وگرنہ_اگر HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    اگر (Get_Process_Affinity_نقاب(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#وگرنہ_اگر HAVE_SYSCTL && defined(HW_NCPUONLINE)
    صحیح mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = حجم(nb_cpus);

    اگر (sysctl(mib, 2, &nb_cpus, &len, تہی, 0) == -1)
        nb_cpus = 0;
#وگرنہ_اگر HAVE_SYSCTL && defined(HW_NCPU)
    صحیح mib[2] = { CTL_HW, HW_NCPU };
    size_t len = حجم(nb_cpus);

    اگر (sysctl(mib, 2, &nb_cpus, &len, تہی, 0) == -1)
        nb_cpus = 0;
#وگرنہ_اگر HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#وگرنہ_اگر HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#وگرنہ_اگر HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_نمبر_کا_Processors;
#اگر_ختم

    اگر (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(تہی, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    گنتی = atomic_load_explicit(&cpu_گنتی, memory_order_relaxed);

    اگر (گنتی > 0) {
        nb_cpus = گنتی;
        av_log(تہی, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    واپس nb_cpus;
}

خالی av_cpu_force_گنتی(صحیح گنتی)
{
    atomic_store_explicit(&cpu_گنتی, گنتی, memory_order_relaxed);
}

size_t av_cpu_max_align(خالی)
{
#اگر ARCH_MIPS
    واپس ff_get_cpu_max_align_mips();
#وگرنہ_اگر ARCH_AARCH64
    واپس ff_get_cpu_max_align_aarch64();
#وگرنہ_اگر ARCH_ARM
    واپس ff_get_cpu_max_align_arm();
#وگرنہ_اگر ARCH_PPC
    واپس ff_get_cpu_max_align_ppc();
#وگرنہ_اگر ARCH_WASM
    واپس ff_get_cpu_max_align_wasm();
#وگرنہ_اگر ARCH_X86
    واپس ff_get_cpu_max_align_x86();
#وگرنہ_اگر ARCH_LOONGARCH
    واپس ff_get_cpu_max_align_loongarch();
#اگر_ختم

    واپس 8;
}

#اگر !ARCH_X86
غیرعلامتی طویل ff_getauxval(غیرعلامتی طویل type)
{
#اگر HAVE_GETAUXVAL
    واپس getauxval(type);
#وگرنہ_اگر HAVE_ELF_AUX_INFO
    غیرعلامتی طویل aux = 0;
    صحیح ret = elf_aux_info(type, &aux, حجم(aux));
    اگر (ret != 0) {
        errno = ret;
    }
    واپس aux;
#ورنہ
    errno = ENOSYS;
    واپس 0;
#اگر_ختم
}
#اگر_ختم

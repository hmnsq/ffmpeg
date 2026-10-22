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
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#شامل <sched.h>
#endif

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
#endif
#اگر HAVE_SYSCTL
#اگر HAVE_SYS_PARAM_H
#شامل <sys/param.h>
#endif
#شامل <sys/types.h>
#شامل <sys/sysctl.h>
#endif
#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#endif

#اگر HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#شامل <sys/auxv.h>
#endif

ایستا atomic_int cpu_flags = -1;
ایستا atomic_int cpu_شمار = -1;

ایستا صحیح get_cpu_flags(تهی)
{
#اگر ARCH_MIPS
    بازگشت ff_get_cpu_flags_mips();
#وگرنهاگر ARCH_AARCH64
    بازگشت ff_get_cpu_flags_aarch64();
#وگرنهاگر ARCH_ARM
    بازگشت ff_get_cpu_flags_arm();
#وگرنهاگر ARCH_PPC
    بازگشت ff_get_cpu_flags_ppc();
#وگرنهاگر ARCH_RISCV
    بازگشت ff_get_cpu_flags_riscv();
#وگرنهاگر ARCH_WASM
    بازگشت ff_get_cpu_flags_wasm();
#وگرنهاگر ARCH_X86
    بازگشت ff_get_cpu_flags_x86();
#وگرنهاگر ARCH_LOONGARCH
    بازگشت ff_get_cpu_flags_loongarch();
#endif
    بازگشت 0;
}

تهی av_force_cpu_flags(صحیح arg){
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
        av_log(پوچ, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

صحیح av_get_cpu_flags(تهی)
{
    صحیح flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    اگر (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    بازگشت flags;
}

صحیح av_parse_cpu_caps(unsigned *flags, ثابت نویسه *s)
{
        ایستا ثابت AVOption cpuflags_opts[] = {
        { "flags"   , پوچ, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#اگر   ARCH_PPC
        { "altivec" , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#وگرنهاگر ARCH_X86
        { "mmx"     , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#define CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#define CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#define CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#define CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#define CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#define CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#define CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#وگرنهاگر ARCH_ARM
        { "armv5te",  پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#وگرنهاگر ARCH_AARCH64
        { "armv8",    پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#وگرنهاگر ARCH_MIPS
        { "mmi",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#وگرنهاگر ARCH_LOONGARCH
        { "lsx",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#وگرنهاگر ARCH_RISCV
        { "rvi",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#وگرنهاگر ARCH_WASM
        { "simd128",  پوچ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { پوچ },
    };
    ایستا ثابت AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    ثابت AVClass *pclass = &class;

    بازگشت av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

صحیح av_cpu_شمار(تهی)
{
    ایستا atomic_int printed = 0;

    صحیح nb_cpus = 1;
    صحیح شمار   = 0;
#اگر HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#اگر HAVE_SCHED_GETAFFINITY && defined(CPU_شمار)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    اگر (!sched_getaffinity(0, اندازه(cpuset), &cpuset))
        nb_cpus = CPU_شمار(&cpuset);
#وگرنهاگر HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    اگر (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#وگرنهاگر HAVE_SYSCTL && defined(HW_NCPUONLINE)
    صحیح mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = اندازه(nb_cpus);

    اگر (sysctl(mib, 2, &nb_cpus, &len, پوچ, 0) == -1)
        nb_cpus = 0;
#وگرنهاگر HAVE_SYSCTL && defined(HW_NCPU)
    صحیح mib[2] = { CTL_HW, HW_NCPU };
    size_t len = اندازه(nb_cpus);

    اگر (sysctl(mib, 2, &nb_cpus, &len, پوچ, 0) == -1)
        nb_cpus = 0;
#وگرنهاگر HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#وگرنهاگر HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#وگرنهاگر HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_عدد_Of_Processors;
#endif

    اگر (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(پوچ, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    شمار = atomic_load_explicit(&cpu_شمار, memory_order_relaxed);

    اگر (شمار > 0) {
        nb_cpus = شمار;
        av_log(پوچ, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    بازگشت nb_cpus;
}

تهی av_cpu_force_شمار(صحیح شمار)
{
    atomic_store_explicit(&cpu_شمار, شمار, memory_order_relaxed);
}

size_t av_cpu_max_align(تهی)
{
#اگر ARCH_MIPS
    بازگشت ff_get_cpu_max_align_mips();
#وگرنهاگر ARCH_AARCH64
    بازگشت ff_get_cpu_max_align_aarch64();
#وگرنهاگر ARCH_ARM
    بازگشت ff_get_cpu_max_align_arm();
#وگرنهاگر ARCH_PPC
    بازگشت ff_get_cpu_max_align_ppc();
#وگرنهاگر ARCH_WASM
    بازگشت ff_get_cpu_max_align_wasm();
#وگرنهاگر ARCH_X86
    بازگشت ff_get_cpu_max_align_x86();
#وگرنهاگر ARCH_LOONGARCH
    بازگشت ff_get_cpu_max_align_loongarch();
#endif

    بازگشت 8;
}

#اگر !ARCH_X86
unsigned long ff_getauxval(unsigned long type)
{
#اگر HAVE_GETAUXVAL
    بازگشت getauxval(type);
#وگرنهاگر HAVE_ELF_AUX_INFO
    unsigned long aux = 0;
    صحیح ret = elf_aux_info(type, &aux, اندازه(aux));
    اگر (ret != 0) {
        errno = ret;
    }
    بازگشت aux;
#وگرنه
    errno = ENOSYS;
    بازگشت 0;
#endif
}
#endif

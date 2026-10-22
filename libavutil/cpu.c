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

#அந்தர்பாவ "config.h"

#எனில் HAVE_SCHED_GETAFFINITY
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#அந்தர்பாவ <sched.h>
#endif

#அந்தர்பாவ <stddef.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdatomic.h>

#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "cpu.h"
#அந்தர்பாவ "cpu_internal.h"
#அந்தர்பாவ "opt.h"
#அந்தர்பாவ "common.h"

#எனில் HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#அந்தர்பாவ <windows.h>
#endif
#எனில் HAVE_SYSCTL
#எனில் HAVE_SYS_PARAM_H
#அந்தர்பாவ <sys/param.h>
#endif
#அந்தர்பாவ <sys/types.h>
#அந்தர்பாவ <sys/sysctl.h>
#endif
#எனில் HAVE_UNISTD_H
#அந்தர்பாவ <unistd.h>
#endif

#எனில் HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#அந்தர்பாவ <sys/auxv.h>
#endif

நிலையான atomic_int cpu_flags = -1;
நிலையான atomic_int cpu_மொத்தம் = -1;

நிலையான முழு get_cpu_flags(வெறுமை)
{
#எனில் ARCH_MIPS
    திரும்பு ff_get_cpu_flags_mips();
#அல்லதெனில் ARCH_AARCH64
    திரும்பு ff_get_cpu_flags_aarch64();
#அல்லதெனில் ARCH_ARM
    திரும்பு ff_get_cpu_flags_arm();
#அல்லதெனில் ARCH_PPC
    திரும்பு ff_get_cpu_flags_ppc();
#அல்லதெனில் ARCH_RISCV
    திரும்பு ff_get_cpu_flags_riscv();
#அல்லதெனில் ARCH_WASM
    திரும்பு ff_get_cpu_flags_wasm();
#அல்லதெனில் ARCH_X86
    திரும்பு ff_get_cpu_flags_x86();
#அல்லதெனில் ARCH_LOONGARCH
    திரும்பு ff_get_cpu_flags_loongarch();
#endif
    திரும்பு 0;
}

வெறுமை av_force_cpu_flags(முழு arg){
    எனில் (ARCH_X86 &&
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
        av_log(வெற்று, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

முழு av_get_cpu_flags(வெறுமை)
{
    முழு flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    எனில் (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    திரும்பு flags;
}

முழு av_parse_cpu_caps(unsigned *flags, மாறிலி எழுத்து *s)
{
        நிலையான மாறிலி AVOption cpuflags_opts[] = {
        { "flags"   , வெற்று, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#எனில்   ARCH_PPC
        { "altivec" , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#அல்லதெனில் ARCH_X86
        { "mmx"     , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#define CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#define CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#define CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#define CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#define CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#define CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#define CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#அல்லதெனில் ARCH_ARM
        { "armv5te",  வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#அல்லதெனில் ARCH_AARCH64
        { "armv8",    வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_CRC  },    .unit = "flags" },
        { "sme_i16i64", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#அல்லதெனில் ARCH_MIPS
        { "mmi",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#அல்லதெனில் ARCH_LOONGARCH
        { "lsx",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#அல்லதெனில் ARCH_RISCV
        { "rvi",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#அல்லதெனில் ARCH_WASM
        { "simd128",  வெற்று, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#endif
        { வெற்று },
    };
    நிலையான மாறிலி AVClass class = {
        .class_name = "cpuflags",
        .item_name  = av_default_item_name,
        .option     = cpuflags_opts,
        .version    = LIBAVUTIL_VERSION_INT,
    };
    மாறிலி AVClass *pclass = &class;

    திரும்பு av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

முழு av_cpu_மொத்தம்(வெறுமை)
{
    நிலையான atomic_int printed = 0;

    முழு nb_cpus = 1;
    முழு மொத்தம்   = 0;
#எனில் HAVE_WINRT
    SYSTEM_INFO sysinfo;
#endif
#எனில் HAVE_SCHED_GETAFFINITY && defined(CPU_மொத்தம்)
    cpu_set_t cpuset;

    CPU_ZERO(&cpuset);

    எனில் (!sched_getaffinity(0, அளவு(cpuset), &cpuset))
        nb_cpus = CPU_மொத்தம்(&cpuset);
#அல்லதெனில் HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    எனில் (GetProcessAffinityMask(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#அல்லதெனில் HAVE_SYSCTL && defined(HW_NCPUONLINE)
    முழு mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = அளவு(nb_cpus);

    எனில் (sysctl(mib, 2, &nb_cpus, &len, வெற்று, 0) == -1)
        nb_cpus = 0;
#அல்லதெனில் HAVE_SYSCTL && defined(HW_NCPU)
    முழு mib[2] = { CTL_HW, HW_NCPU };
    size_t len = அளவு(nb_cpus);

    எனில் (sysctl(mib, 2, &nb_cpus, &len, வெற்று, 0) == -1)
        nb_cpus = 0;
#அல்லதெனில் HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#அல்லதெனில் HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#அல்லதெனில் HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_எண்_Of_Processors;
#endif

    எனில் (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(வெற்று, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    மொத்தம் = atomic_load_explicit(&cpu_மொத்தம், memory_order_relaxed);

    எனில் (மொத்தம் > 0) {
        nb_cpus = மொத்தம்;
        av_log(வெற்று, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    திரும்பு nb_cpus;
}

வெறுமை av_cpu_force_மொத்தம்(முழு மொத்தம்)
{
    atomic_store_explicit(&cpu_மொத்தம், மொத்தம், memory_order_relaxed);
}

size_t av_cpu_max_align(வெறுமை)
{
#எனில் ARCH_MIPS
    திரும்பு ff_get_cpu_max_align_mips();
#அல்லதெனில் ARCH_AARCH64
    திரும்பு ff_get_cpu_max_align_aarch64();
#அல்லதெனில் ARCH_ARM
    திரும்பு ff_get_cpu_max_align_arm();
#அல்லதெனில் ARCH_PPC
    திரும்பு ff_get_cpu_max_align_ppc();
#அல்லதெனில் ARCH_WASM
    திரும்பு ff_get_cpu_max_align_wasm();
#அல்லதெனில் ARCH_X86
    திரும்பு ff_get_cpu_max_align_x86();
#அல்லதெனில் ARCH_LOONGARCH
    திரும்பு ff_get_cpu_max_align_loongarch();
#endif

    திரும்பு 8;
}

#எனில் !ARCH_X86
unsigned long ff_getauxval(unsigned long type)
{
#எனில் HAVE_GETAUXVAL
    திரும்பு getauxval(type);
#அல்லதெனில் HAVE_ELF_AUX_INFO
    unsigned long aux = 0;
    முழு ret = elf_aux_info(type, &aux, அளவு(aux));
    எனில் (ret != 0) {
        errno = ret;
    }
    திரும்பு aux;
#இல்லையெனில்
    errno = ENOSYS;
    திரும்பு 0;
#endif
}
#endif

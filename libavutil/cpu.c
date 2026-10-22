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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ HAVE_SCHED_GETAFFINITY
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ GNU_ਸਰੋਤ
# define GNU_ਸਰੋਤ
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <sched.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cpu_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "opt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"

#ਜੇ HAVE_GETPROCESSAFFINITYMASK || HAVE_WINRT
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_SYSCTL
#ਜੇ HAVE_SYS_PARAM_H
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/param.h>
#ਜੇ_ਅੰਤ
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/types.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/sysctl.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_UNISTD_H
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_GETAUXVAL || HAVE_ELF_AUX_INFO
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/auxv.h>
#ਜੇ_ਅੰਤ

ਸਥਿਰ atomic_int cpu_flags = -1;
ਸਥਿਰ atomic_int cpu_ਗਿਣਤੀ = -1;

ਸਥਿਰ ਪੂਰਨ get_cpu_flags(ਖਾਲੀ)
{
#ਜੇ ARCH_MIPS
    ਵਾਪਸ ff_get_cpu_flags_mips();
#ਜਾਂਜੇ ARCH_AARCH64
    ਵਾਪਸ ff_get_cpu_flags_aarch64();
#ਜਾਂਜੇ ARCH_ARM
    ਵਾਪਸ ff_get_cpu_flags_arm();
#ਜਾਂਜੇ ARCH_PPC
    ਵਾਪਸ ff_get_cpu_flags_ppc();
#ਜਾਂਜੇ ARCH_RISCV
    ਵਾਪਸ ff_get_cpu_flags_riscv();
#ਜਾਂਜੇ ARCH_WASM
    ਵਾਪਸ ff_get_cpu_flags_wasm();
#ਜਾਂਜੇ ARCH_X86
    ਵਾਪਸ ff_get_cpu_flags_x86();
#ਜਾਂਜੇ ARCH_LOONGARCH
    ਵਾਪਸ ff_get_cpu_flags_loongarch();
#ਜੇ_ਅੰਤ
    ਵਾਪਸ 0;
}

ਖਾਲੀ av_force_cpu_flags(ਪੂਰਨ arg){
    ਜੇ (ARCH_X86 &&
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
        av_log(ਨਿਰਾ, AV_LOG_WARNING, "MMX implied by specified flags\n");
        arg |= AV_CPU_FLAG_MMX;
    }

    atomic_store_explicit(&cpu_flags, arg, memory_order_relaxed);
}

ਪੂਰਨ av_get_cpu_flags(ਖਾਲੀ)
{
    ਪੂਰਨ flags = atomic_load_explicit(&cpu_flags, memory_order_relaxed);
    ਜੇ (flags == -1) {
        flags = get_cpu_flags();
        atomic_store_explicit(&cpu_flags, flags, memory_order_relaxed);
    }
    ਵਾਪਸ flags;
}

ਪੂਰਨ av_parse_cpu_caps(ਬਿਨਾਨਿਸ਼ਾਨੀ *flags, ਅਚਲ ਅੱਖਰ *s)
{
        ਸਥਿਰ ਅਚਲ AVOption cpuflags_opts[] = {
        { "flags"   , ਨਿਰਾ, 0, AV_OPT_TYPE_FLAGS, { .i64 = 0 }, INT64_MIN, INT64_MAX, .unit = "flags" },
#ਜੇ   ARCH_PPC
        { "altivec" , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ALTIVEC  },    .unit = "flags" },
        { "vsx"     , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VSX      },    .unit = "flags" },
        { "power8"  , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_POWER8   },    .unit = "flags" },
#ਜਾਂਜੇ ARCH_X86
        { "mmx"     , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "mmx2"    , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "mmxext"  , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX2     },    .unit = "flags" },
        { "sse"     , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE      },    .unit = "flags" },
        { "sse2"    , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2     },    .unit = "flags" },
        { "sse2slow", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE2SLOW },    .unit = "flags" },
        { "sse3"    , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3     },    .unit = "flags" },
        { "sse3slow", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE3SLOW },    .unit = "flags" },
        { "ssse3"   , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSSE3    },    .unit = "flags" },
        { "atom"    , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ATOM     },    .unit = "flags" },
        { "sse4.1"  , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE4     },    .unit = "flags" },
        { "sse4.2"  , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SSE42    },    .unit = "flags" },
        { "avx"     , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX      },    .unit = "flags" },
        { "avxslow" , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVXSLOW  },    .unit = "flags" },
        { "xop"     , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_XOP      },    .unit = "flags" },
        { "fma3"    , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA3     },    .unit = "flags" },
        { "fma4"    , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_FMA4     },    .unit = "flags" },
        { "avx2"    , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX2     },    .unit = "flags" },
        { "bmi1"    , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI1     },    .unit = "flags" },
        { "bmi2"    , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_BMI2     },    .unit = "flags" },
        { "3dnow"   , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOW    },    .unit = "flags" },
        { "3dnowext", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_3DNOWEXT },    .unit = "flags" },
        { "cmov",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CMOV     },    .unit = "flags" },
        { "aesni",    ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AESNI    },    .unit = "flags" },
        { "clmul",    ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_CLMUL    },    .unit = "flags" },
        { "avx512"  , ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512   },    .unit = "flags" },
        { "avx512icl",  ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_AVX512ICL   }, .unit = "flags" },
        { "slowgather", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SLOW_GATHER }, .unit = "flags" },

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPU_FLAG_P2 AV_CPU_FLAG_CMOV | AV_CPU_FLAG_MMX
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPU_FLAG_P3 CPU_FLAG_P2 | AV_CPU_FLAG_MMX2 | AV_CPU_FLAG_SSE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPU_FLAG_P4 CPU_FLAG_P3| AV_CPU_FLAG_SSE2
        { "pentium2", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P2          },    .unit = "flags" },
        { "pentium3", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P3          },    .unit = "flags" },
        { "pentium4", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_P4          },    .unit = "flags" },

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPU_FLAG_K62 AV_CPU_FLAG_MMX | AV_CPU_FLAG_3DNOW
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPU_FLAG_ATHLON   CPU_FLAG_K62 | AV_CPU_FLAG_CMOV | AV_CPU_FLAG_3DNOWEXT | AV_CPU_FLAG_MMX2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPU_FLAG_ATHLONXP CPU_FLAG_ATHLON | AV_CPU_FLAG_SSE
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CPU_FLAG_K8  CPU_FLAG_ATHLONXP | AV_CPU_FLAG_SSE2
        { "k6",       ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMX      },    .unit = "flags" },
        { "k62",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K62         },    .unit = "flags" },
        { "athlon",   ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLON      },    .unit = "flags" },
        { "athlonxp", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_ATHLONXP    },    .unit = "flags" },
        { "k8",       ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = CPU_FLAG_K8          },    .unit = "flags" },
#ਜਾਂਜੇ ARCH_ARM
        { "armv5te",  ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV5TE  },    .unit = "flags" },
        { "armv6",    ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6    },    .unit = "flags" },
        { "armv6t2",  ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV6T2  },    .unit = "flags" },
        { "vfp",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "vfp_vm",   ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP_VM   },    .unit = "flags" },
        { "vfpv3",    ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFPV3    },    .unit = "flags" },
        { "neon",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "setend",   ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SETEND   },    .unit = "flags" },
#ਜਾਂਜੇ ARCH_AARCH64
        { "armv8",    ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARMV8    },    .unit = "flags" },
        { "neon",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_NEON     },    .unit = "flags" },
        { "vfp",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_VFP      },    .unit = "flags" },
        { "dotprod",  ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_DOTPROD  },    .unit = "flags" },
        { "i8mm",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_I8MM     },    .unit = "flags" },
        { "sve",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE      },    .unit = "flags" },
        { "sve2",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SVE2     },    .unit = "flags" },
        { "sme",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME      },    .unit = "flags" },
        { "crc",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_ਚੱਕਰੀ_ਜਾਂਚ  },    .unit = "flags" },
        { "sme_i16i64", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME_I16I64 },    .unit = "flags" },
        { "sme2",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SME2     },    .unit = "flags" },
        { "pmull",    ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_PMULL    },    .unit = "flags" },
        { "eor3",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_EOR3     },    .unit = "flags" },
        { "aes",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_ARM_AES  },    .unit = "flags" },
#ਜਾਂਜੇ ARCH_MIPS
        { "mmi",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MMI      },    .unit = "flags" },
        { "msa",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_MSA      },    .unit = "flags" },
#ਜਾਂਜੇ ARCH_LOONGARCH
        { "lsx",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LSX      },    .unit = "flags" },
        { "lasx",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_LASX     },    .unit = "flags" },
#ਜਾਂਜੇ ARCH_RISCV
        { "rvi",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVI      },    .unit = "flags" },
        { "rvb",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB      },    .unit = "flags" },
        { "zve32x",   ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I32  },    .unit = "flags" },
        { "zve32f",   ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F32  },    .unit = "flags" },
        { "zve64x",   ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_I64  },    .unit = "flags" },
        { "zve64d",   ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVV_F64  },    .unit = "flags" },
        { "zbb",      ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RVB_BASIC },   .unit = "flags" },
        { "zvbb",     ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_ZVBB },   .unit = "flags" },
        { "misaligned", ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_RV_MISALIGNED },   .unit = "flags" },
#ਜਾਂਜੇ ARCH_WASM
        { "simd128",  ਨਿਰਾ, 0, AV_OPT_TYPE_CONST, { .i64 = AV_CPU_FLAG_SIMD128  },    .unit = "flags" },
#ਜੇ_ਅੰਤ
        { ਨਿਰਾ },
    };
    ਸਥਿਰ ਅਚਲ AVClass class = {
        .class_name = "cpuflags",
        .ਵਸਤੂ_name  = av_default_ਵਸਤੂ_name,
        .option     = cpuflags_opts,
        .ਸੰਸਕਰਣ    = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    };
    ਅਚਲ AVClass *pclass = &class;

    ਵਾਪਸ av_opt_eval_flags(&pclass, &cpuflags_opts[0], s, flags);
}

ਪੂਰਨ av_cpu_ਗਿਣਤੀ(ਖਾਲੀ)
{
    ਸਥਿਰ atomic_int printed = 0;

    ਪੂਰਨ nb_cpus = 1;
    ਪੂਰਨ ਗਿਣਤੀ_2   = 0;
#ਜੇ HAVE_WINRT
    SYSTEM_INFO sysinfo;
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_SCHED_GETAFFINITY && defined(CPU_ਗਿਣਤੀ)
    cpu_ਸੈੱਟ_t cpuset;

    CPU_ZERO(&cpuset);

    ਜੇ (!sched_getaffinity(0, ਆਕਾਰ(cpuset), &cpuset))
        nb_cpus = CPU_ਗਿਣਤੀ(&cpuset);
#ਜਾਂਜੇ HAVE_GETPROCESSAFFINITYMASK
    DWORD_PTR proc_aff, sys_aff;
    ਜੇ (Get_Process_Affinity_ਨਕਾਬ(GetCurrentProcess(), &proc_aff, &sys_aff))
        nb_cpus = av_popcount64(proc_aff);
#ਜਾਂਜੇ HAVE_SYSCTL && defined(HW_NCPUONLINE)
    ਪੂਰਨ mib[2] = { CTL_HW, HW_NCPUONLINE };
    size_t len = ਆਕਾਰ(nb_cpus);

    ਜੇ (sysctl(mib, 2, &nb_cpus, &len, ਨਿਰਾ, 0) == -1)
        nb_cpus = 0;
#ਜਾਂਜੇ HAVE_SYSCTL && defined(HW_NCPU)
    ਪੂਰਨ mib[2] = { CTL_HW, HW_NCPU };
    size_t len = ਆਕਾਰ(nb_cpus);

    ਜੇ (sysctl(mib, 2, &nb_cpus, &len, ਨਿਰਾ, 0) == -1)
        nb_cpus = 0;
#ਜਾਂਜੇ HAVE_SYSCONF && defined(_SC_NPROC_ONLN)
    nb_cpus = sysconf(_SC_NPROC_ONLN);
#ਜਾਂਜੇ HAVE_SYSCONF && defined(_SC_NPROCESSORS_ONLN)
    nb_cpus = sysconf(_SC_NPROCESSORS_ONLN);
#ਜਾਂਜੇ HAVE_WINRT
    GetNativeSystemInfo(&sysinfo);
    nb_cpus = sysinfo.dw_ਸੰਖਿਆ_ਦਾ_Processors;
#ਜੇ_ਅੰਤ

    ਜੇ (!atomic_exchange_explicit(&printed, 1, memory_order_relaxed))
        av_log(ਨਿਰਾ, AV_LOG_DEBUG, "detected %d logical cores\n", nb_cpus);

    ਗਿਣਤੀ_2 = atomic_load_explicit(&cpu_ਗਿਣਤੀ, memory_order_relaxed);

    ਜੇ (ਗਿਣਤੀ_2 > 0) {
        nb_cpus = ਗਿਣਤੀ_2;
        av_log(ਨਿਰਾ, AV_LOG_DEBUG, "overriding to %d logical cores\n", nb_cpus);
    }

    ਵਾਪਸ nb_cpus;
}

ਖਾਲੀ av_cpu_force_ਗਿਣਤੀ(ਪੂਰਨ ਗਿਣਤੀ_2)
{
    atomic_store_explicit(&cpu_ਗਿਣਤੀ, ਗਿਣਤੀ_2, memory_order_relaxed);
}

size_t av_cpu_max_align(ਖਾਲੀ)
{
#ਜੇ ARCH_MIPS
    ਵਾਪਸ ff_get_cpu_max_align_mips();
#ਜਾਂਜੇ ARCH_AARCH64
    ਵਾਪਸ ff_get_cpu_max_align_aarch64();
#ਜਾਂਜੇ ARCH_ARM
    ਵਾਪਸ ff_get_cpu_max_align_arm();
#ਜਾਂਜੇ ARCH_PPC
    ਵਾਪਸ ff_get_cpu_max_align_ppc();
#ਜਾਂਜੇ ARCH_WASM
    ਵਾਪਸ ff_get_cpu_max_align_wasm();
#ਜਾਂਜੇ ARCH_X86
    ਵਾਪਸ ff_get_cpu_max_align_x86();
#ਜਾਂਜੇ ARCH_LOONGARCH
    ਵਾਪਸ ff_get_cpu_max_align_loongarch();
#ਜੇ_ਅੰਤ

    ਵਾਪਸ 8;
}

#ਜੇ !ARCH_X86
ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ff_getauxval(ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ type)
{
#ਜੇ HAVE_GETAUXVAL
    ਵਾਪਸ getauxval(type);
#ਜਾਂਜੇ HAVE_ELF_AUX_INFO
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ aux = 0;
    ਪੂਰਨ ret = elf_aux_info(type, &aux, ਆਕਾਰ(aux));
    ਜੇ (ret != 0) {
        errno = ret;
    }
    ਵਾਪਸ aux;
#ਨਹੀਂਤਾਂ
    errno = ENOSYS;
    ਵਾਪਸ 0;
#ਜੇ_ਅੰਤ
}
#ਜੇ_ਅੰਤ

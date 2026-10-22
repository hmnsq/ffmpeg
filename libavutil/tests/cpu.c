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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/cpu.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/avstring.h"

#ਜੇ ARCH_AARCH64
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/aarch64/cpu.h"
#ਜਾਂਜੇ ARCH_RISCV
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/riscv/cpu.h"
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_UNISTD_H
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ
#ਜੇ !HAVE_GETOPT
#ਅਨ੍ਤਰ੍ਭਾਵ "compat/getopt.c"
#ਜੇ_ਅੰਤ

ਸਥਿਰ ਅਚਲ ਬਣਤਰ {
    ਪੂਰਨ flag;
    ਅਚਲ ਅੱਖਰ *name;
} cpu_flag_tab[] = {
#ਜੇ   ARCH_AARCH64
    { AV_CPU_FLAG_ARMV8,     "armv8"      },
    { AV_CPU_FLAG_NEON,      "neon"       },
    { AV_CPU_FLAG_VFP,       "vfp"        },
    { AV_CPU_FLAG_DOTPROD,   "dotprod"    },
    { AV_CPU_FLAG_I8MM,      "i8mm"       },
    { AV_CPU_FLAG_SVE,       "sve"        },
    { AV_CPU_FLAG_SVE2,      "sve2"       },
    { AV_CPU_FLAG_SME,       "sme"        },
    { AV_CPU_FLAG_SME_I16I64, "sme_i16i64" },
    { AV_CPU_FLAG_ARM_ਚੱਕਰੀ_ਜਾਂਚ,   "crc"        },
    { AV_CPU_FLAG_SME2,      "sme2"       },
    { AV_CPU_FLAG_PMULL,     "pmull"      },
    { AV_CPU_FLAG_EOR3,      "eor3"       },
    { AV_CPU_FLAG_ARM_AES,   "aes"        },
#ਜਾਂਜੇ ARCH_ARM
    { AV_CPU_FLAG_ARMV5TE,   "armv5te"    },
    { AV_CPU_FLAG_ARMV6,     "armv6"      },
    { AV_CPU_FLAG_ARMV6T2,   "armv6t2"    },
    { AV_CPU_FLAG_VFP,       "vfp"        },
    { AV_CPU_FLAG_VFP_VM,    "vfp_vm"     },
    { AV_CPU_FLAG_VFPV3,     "vfpv3"      },
    { AV_CPU_FLAG_NEON,      "neon"       },
    { AV_CPU_FLAG_SETEND,    "setend"     },
#ਜਾਂਜੇ ARCH_PPC
    { AV_CPU_FLAG_ALTIVEC,   "altivec"    },
    { AV_CPU_FLAG_VSX,       "vsx"        },
    { AV_CPU_FLAG_POWER8,    "power8"     },
#ਜਾਂਜੇ ARCH_MIPS
    { AV_CPU_FLAG_MMI,       "mmi"        },
    { AV_CPU_FLAG_MSA,       "msa"        },
#ਜਾਂਜੇ ARCH_X86
    { AV_CPU_FLAG_MMX,       "mmx"        },
    { AV_CPU_FLAG_MMXEXT,    "mmxext"     },
    { AV_CPU_FLAG_SSE,       "sse"        },
    { AV_CPU_FLAG_SSE2,      "sse2"       },
    { AV_CPU_FLAG_SSE2SLOW,  "sse2slow"   },
    { AV_CPU_FLAG_SSE3,      "sse3"       },
    { AV_CPU_FLAG_SSE3SLOW,  "sse3slow"   },
    { AV_CPU_FLAG_SSSE3,     "ssse3"      },
    { AV_CPU_FLAG_ATOM,      "atom"       },
    { AV_CPU_FLAG_SSE4,      "sse4.1"     },
    { AV_CPU_FLAG_SSE42,     "sse4.2"     },
    { AV_CPU_FLAG_AVX,       "avx"        },
    { AV_CPU_FLAG_AVXSLOW,   "avxslow"    },
    { AV_CPU_FLAG_XOP,       "xop"        },
    { AV_CPU_FLAG_FMA3,      "fma3"       },
    { AV_CPU_FLAG_FMA4,      "fma4"       },
    { AV_CPU_FLAG_3DNOW,     "3dnow"      },
    { AV_CPU_FLAG_3DNOWEXT,  "3dnowext"   },
    { AV_CPU_FLAG_CMOV,      "cmov"       },
    { AV_CPU_FLAG_AVX2,      "avx2"       },
    { AV_CPU_FLAG_BMI1,      "bmi1"       },
    { AV_CPU_FLAG_BMI2,      "bmi2"       },
    { AV_CPU_FLAG_AESNI,     "aesni"      },
    { AV_CPU_FLAG_CLMUL,     "clmul"      },
    { AV_CPU_FLAG_AVX512,    "avx512"     },
    { AV_CPU_FLAG_AVX512ICL, "avx512icl"  },
    { AV_CPU_FLAG_SLOW_GATHER, "slowgather" },
#ਜਾਂਜੇ ARCH_LOONGARCH
    { AV_CPU_FLAG_LSX,       "lsx"        },
    { AV_CPU_FLAG_LASX,      "lasx"       },
#ਜਾਂਜੇ ARCH_RISCV
    { AV_CPU_FLAG_RVI,       "rvi"        },
    { AV_CPU_FLAG_RVB_BASIC, "zbb"        },
    { AV_CPU_FLAG_RVB,       "rvb"        },
    { AV_CPU_FLAG_RVV_I32,   "zve32x"     },
    { AV_CPU_FLAG_RVV_F32,   "zve32f"     },
    { AV_CPU_FLAG_RVV_I64,   "zve64x"     },
    { AV_CPU_FLAG_RVV_F64,   "zve64d"     },
    { AV_CPU_FLAG_RV_ZVBB,   "zvbb"       },
    { AV_CPU_FLAG_RV_MISALIGNED, "misaligned" },
#ਜਾਂਜੇ ARCH_WASM
    { AV_CPU_FLAG_SIMD128,   "simd128"    },
#ਜੇ_ਅੰਤ
    { 0 }
};

ਸਥਿਰ ਖਾਲੀ print_cpu_flags(ਪੂਰਨ cpu_flags, ਅਚਲ ਅੱਖਰ *type)
{
    ਪੂਰਨ i;

    ਲਿਖੋ("cpu_flags(%s) = 0x%08X\n", type, cpu_flags);
    ਲਿਖੋ("cpu_flags_str(%s) =", type);
    ਲਈ (i = 0; cpu_flag_tab[i].flag; i++)
        ਜੇ (cpu_flags & cpu_flag_tab[i].flag)
            ਲਿਖੋ(" %s", cpu_flag_tab[i].name);
    ਲਿਖੋ("\n");
}


ਪੂਰਨ ਮੁੱਖ(ਪੂਰਨ argc, ਅੱਖਰ **argv)
{
    ਪੂਰਨ cpu_flags_raw = av_get_cpu_flags();
    ਪੂਰਨ cpu_flags_eff;
    ਪੂਰਨ cpu_ਗਿਣਤੀ = av_cpu_ਗਿਣਤੀ();
    ਅਚਲ ਅੱਖਰ *ਧਾਗੇ = "auto";
    ਪੂਰਨ i;

    ਲਈ(i = 0; cpu_flag_tab[i].flag; i++) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ tmp = 0;
        ਜੇ (av_parse_cpu_caps(&tmp, cpu_flag_tab[i].name) < 0) {
            fprintf(stderr, "Table missing %s\n", cpu_flag_tab[i].name);
            ਵਾਪਸ 4;
        }
    }

    ਜੇ (cpu_flags_raw < 0)
        ਵਾਪਸ 1;

    ਲਈ (;;) {
        ਪੂਰਨ c = getopt(argc, argv, "c:t:");
        ਜੇ (c == -1)
            ਰੋਕੋ;
        ਚੋਣ (c) {
        ਹਾਲਤ 'c':
        {
            ਬਿਨਾਨਿਸ਼ਾਨੀ flags = av_get_cpu_flags();
            ਜੇ (av_parse_cpu_caps(&flags, optarg) < 0)
                ਵਾਪਸ 2;

            av_force_cpu_flags(flags);
            ਰੋਕੋ;
        }
        ਹਾਲਤ 't':
        {
            ਧਾਗੇ = optarg;
        }
        }
    }

    cpu_flags_eff = av_get_cpu_flags();

    ਜੇ (cpu_flags_eff < 0)
        ਵਾਪਸ 3;

    print_cpu_flags(cpu_flags_raw, "raw");
    print_cpu_flags(cpu_flags_eff, "effective");
    ਲਿਖੋ("threads = %s (cpu_count = %d)\n", ਧਾਗੇ, cpu_ਗਿਣਤੀ);
#ਜੇ ARCH_AARCH64 && HAVE_SVE
    ਜੇ (cpu_flags_raw & AV_CPU_FLAG_SVE)
        ਲਿਖੋ("sve_vector_length = %d\n", 8 * ff_aarch64_sve_ਲੰਮਾਈ());
#ਜੇ_ਅੰਤ
#ਜੇ ARCH_AARCH64 && HAVE_SME
    ਜੇ (cpu_flags_raw & AV_CPU_FLAG_SME)
        ਲਿਖੋ("sme_vector_length = %d\n", 8 * ff_aarch64_sme_ਲੰਮਾਈ());
#ਜੇ_ਅੰਤ
#ਜੇ ARCH_RISCV && HAVE_RVV
    ਜੇ (cpu_flags_raw & AV_CPU_FLAG_RVV_I32) {
        size_t ਬਾਈਟਾਂ = ff_get_rv_vlenb();

        ਲਿਖੋ("rv_vlenb = %zu (%zu bits)\n", ਬਾਈਟਾਂ, 8 * ਬਾਈਟਾਂ);
    }
#ਜੇ_ਅੰਤ

    ਵਾਪਸ 0;
}

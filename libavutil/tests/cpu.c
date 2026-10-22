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

#అన్తర్భావ <stdio.h>

#అన్తర్భావ "config.h"

#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/avstring.h"

#ఒకవేళ ARCH_AARCH64
#అన్తర్భావ "libavutil/aarch64/cpu.h"
#లేదావేళ ARCH_RISCV
#అన్తర్భావ "libavutil/riscv/cpu.h"
#అయితే_ముగింపు

#ఒకవేళ HAVE_UNISTD_H
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు
#ఒకవేళ !HAVE_GETOPT
#అన్తర్భావ "compat/getopt.c"
#అయితే_ముగింపు

స్థిర స్థిరరాశి నిర్మాణం {
    పూర్ణాంకం flag;
    స్థిరరాశి అక్షరం *name;
} cpu_flag_tab[] = {
#ఒకవేళ   ARCH_AARCH64
    { AV_CPU_FLAG_ARMV8,     "armv8"      },
    { AV_CPU_FLAG_NEON,      "neon"       },
    { AV_CPU_FLAG_VFP,       "vfp"        },
    { AV_CPU_FLAG_DOTPROD,   "dotprod"    },
    { AV_CPU_FLAG_I8MM,      "i8mm"       },
    { AV_CPU_FLAG_SVE,       "sve"        },
    { AV_CPU_FLAG_SVE2,      "sve2"       },
    { AV_CPU_FLAG_SME,       "sme"        },
    { AV_CPU_FLAG_SME_I16I64, "sme_i16i64" },
    { AV_CPU_FLAG_ARM_చక్రీయ_తనిఖీ,   "crc"        },
    { AV_CPU_FLAG_SME2,      "sme2"       },
    { AV_CPU_FLAG_PMULL,     "pmull"      },
    { AV_CPU_FLAG_EOR3,      "eor3"       },
    { AV_CPU_FLAG_ARM_AES,   "aes"        },
#లేదావేళ ARCH_ARM
    { AV_CPU_FLAG_ARMV5TE,   "armv5te"    },
    { AV_CPU_FLAG_ARMV6,     "armv6"      },
    { AV_CPU_FLAG_ARMV6T2,   "armv6t2"    },
    { AV_CPU_FLAG_VFP,       "vfp"        },
    { AV_CPU_FLAG_VFP_VM,    "vfp_vm"     },
    { AV_CPU_FLAG_VFPV3,     "vfpv3"      },
    { AV_CPU_FLAG_NEON,      "neon"       },
    { AV_CPU_FLAG_SETEND,    "setend"     },
#లేదావేళ ARCH_PPC
    { AV_CPU_FLAG_ALTIVEC,   "altivec"    },
    { AV_CPU_FLAG_VSX,       "vsx"        },
    { AV_CPU_FLAG_POWER8,    "power8"     },
#లేదావేళ ARCH_MIPS
    { AV_CPU_FLAG_MMI,       "mmi"        },
    { AV_CPU_FLAG_MSA,       "msa"        },
#లేదావేళ ARCH_X86
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
#లేదావేళ ARCH_LOONGARCH
    { AV_CPU_FLAG_LSX,       "lsx"        },
    { AV_CPU_FLAG_LASX,      "lasx"       },
#లేదావేళ ARCH_RISCV
    { AV_CPU_FLAG_RVI,       "rvi"        },
    { AV_CPU_FLAG_RVB_BASIC, "zbb"        },
    { AV_CPU_FLAG_RVB,       "rvb"        },
    { AV_CPU_FLAG_RVV_I32,   "zve32x"     },
    { AV_CPU_FLAG_RVV_F32,   "zve32f"     },
    { AV_CPU_FLAG_RVV_I64,   "zve64x"     },
    { AV_CPU_FLAG_RVV_F64,   "zve64d"     },
    { AV_CPU_FLAG_RV_ZVBB,   "zvbb"       },
    { AV_CPU_FLAG_RV_MISALIGNED, "misaligned" },
#లేదావేళ ARCH_WASM
    { AV_CPU_FLAG_SIMD128,   "simd128"    },
#అయితే_ముగింపు
    { 0 }
};

స్థిర శూన్య print_cpu_flags(పూర్ణాంకం cpu_flags, స్థిరరాశి అక్షరం *type)
{
    పూర్ణాంకం i;

    రాయి("cpu_flags(%s) = 0x%08X\n", type, cpu_flags);
    రాయి("cpu_flags_str(%s) =", type);
    కొరకు (i = 0; cpu_flag_tab[i].flag; i++)
        ఒకవేళ (cpu_flags & cpu_flag_tab[i].flag)
            రాయి(" %s", cpu_flag_tab[i].name);
    రాయి("\n");
}


పూర్ణాంకం ప్రధాన(పూర్ణాంకం argc, అక్షరం **argv)
{
    పూర్ణాంకం cpu_flags_raw = av_get_cpu_flags();
    పూర్ణాంకం cpu_flags_eff;
    పూర్ణాంకం cpu_లెక్క = av_cpu_లెక్క();
    స్థిరరాశి అక్షరం *దారాలు = "auto";
    పూర్ణాంకం i;

    కొరకు(i = 0; cpu_flag_tab[i].flag; i++) {
        గుర్తులేని tmp = 0;
        ఒకవేళ (av_parse_cpu_caps(&tmp, cpu_flag_tab[i].name) < 0) {
            fprintf(stderr, "Table missing %s\n", cpu_flag_tab[i].name);
            తిరిగి 4;
        }
    }

    ఒకవేళ (cpu_flags_raw < 0)
        తిరిగి 1;

    కొరకు (;;) {
        పూర్ణాంకం c = getopt(argc, argv, "c:t:");
        ఒకవేళ (c == -1)
            ఆపు;
        ఎంపిక (c) {
        స్థితి 'c':
        {
            గుర్తులేని flags = av_get_cpu_flags();
            ఒకవేళ (av_parse_cpu_caps(&flags, optarg) < 0)
                తిరిగి 2;

            av_force_cpu_flags(flags);
            ఆపు;
        }
        స్థితి 't':
        {
            దారాలు = optarg;
        }
        }
    }

    cpu_flags_eff = av_get_cpu_flags();

    ఒకవేళ (cpu_flags_eff < 0)
        తిరిగి 3;

    print_cpu_flags(cpu_flags_raw, "raw");
    print_cpu_flags(cpu_flags_eff, "effective");
    రాయి("threads = %s (cpu_count = %d)\n", దారాలు, cpu_లెక్క);
#ఒకవేళ ARCH_AARCH64 && HAVE_SVE
    ఒకవేళ (cpu_flags_raw & AV_CPU_FLAG_SVE)
        రాయి("sve_vector_length = %d\n", 8 * ff_aarch64_sve_నిడివి());
#అయితే_ముగింపు
#ఒకవేళ ARCH_AARCH64 && HAVE_SME
    ఒకవేళ (cpu_flags_raw & AV_CPU_FLAG_SME)
        రాయి("sme_vector_length = %d\n", 8 * ff_aarch64_sme_నిడివి());
#అయితే_ముగింపు
#ఒకవేళ ARCH_RISCV && HAVE_RVV
    ఒకవేళ (cpu_flags_raw & AV_CPU_FLAG_RVV_I32) {
        size_t బైట్లు = ff_get_rv_vlenb();

        రాయి("rv_vlenb = %zu (%zu bits)\n", బైట్లు, 8 * బైట్లు);
    }
#అయితే_ముగింపు

    తిరిగి 0;
}

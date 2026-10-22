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

#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ "libavutil/cpu.h"
#ಅನ್ತರ್ಭಾವ "libavutil/avstring.h"

#ಯದಿ ARCH_AARCH64
#ಅನ್ತರ್ಭಾವ "libavutil/aarch64/cpu.h"
#ನೋಚೇದ್ಯದಿ ARCH_RISCV
#ಅನ್ತರ್ಭಾವ "libavutil/riscv/cpu.h"
#endif

#ಯದಿ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#endif
#ಯದಿ !HAVE_GETOPT
#ಅನ್ತರ್ಭಾವ "compat/getopt.c"
#endif

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ {
    ಪೂರ್ಣಾಙ್ಕ flag;
    ಧ್ರುವ ವರ್ಣ *name;
} cpu_flag_tab[] = {
#ಯದಿ   ARCH_AARCH64
    { AV_CPU_FLAG_ARMV8,     "armv8"      },
    { AV_CPU_FLAG_NEON,      "neon"       },
    { AV_CPU_FLAG_VFP,       "vfp"        },
    { AV_CPU_FLAG_DOTPROD,   "dotprod"    },
    { AV_CPU_FLAG_I8MM,      "i8mm"       },
    { AV_CPU_FLAG_SVE,       "sve"        },
    { AV_CPU_FLAG_SVE2,      "sve2"       },
    { AV_CPU_FLAG_SME,       "sme"        },
    { AV_CPU_FLAG_SME_I16I64, "sme_i16i64" },
    { AV_CPU_FLAG_ARM_CRC,   "crc"        },
    { AV_CPU_FLAG_SME2,      "sme2"       },
    { AV_CPU_FLAG_PMULL,     "pmull"      },
    { AV_CPU_FLAG_EOR3,      "eor3"       },
    { AV_CPU_FLAG_ARM_AES,   "aes"        },
#ನೋಚೇದ್ಯದಿ ARCH_ARM
    { AV_CPU_FLAG_ARMV5TE,   "armv5te"    },
    { AV_CPU_FLAG_ARMV6,     "armv6"      },
    { AV_CPU_FLAG_ARMV6T2,   "armv6t2"    },
    { AV_CPU_FLAG_VFP,       "vfp"        },
    { AV_CPU_FLAG_VFP_VM,    "vfp_vm"     },
    { AV_CPU_FLAG_VFPV3,     "vfpv3"      },
    { AV_CPU_FLAG_NEON,      "neon"       },
    { AV_CPU_FLAG_SETEND,    "setend"     },
#ನೋಚೇದ್ಯದಿ ARCH_PPC
    { AV_CPU_FLAG_ALTIVEC,   "altivec"    },
    { AV_CPU_FLAG_VSX,       "vsx"        },
    { AV_CPU_FLAG_POWER8,    "power8"     },
#ನೋಚೇದ್ಯದಿ ARCH_MIPS
    { AV_CPU_FLAG_MMI,       "mmi"        },
    { AV_CPU_FLAG_MSA,       "msa"        },
#ನೋಚೇದ್ಯದಿ ARCH_X86
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
#ನೋಚೇದ್ಯದಿ ARCH_LOONGARCH
    { AV_CPU_FLAG_LSX,       "lsx"        },
    { AV_CPU_FLAG_LASX,      "lasx"       },
#ನೋಚೇದ್ಯದಿ ARCH_RISCV
    { AV_CPU_FLAG_RVI,       "rvi"        },
    { AV_CPU_FLAG_RVB_BASIC, "zbb"        },
    { AV_CPU_FLAG_RVB,       "rvb"        },
    { AV_CPU_FLAG_RVV_I32,   "zve32x"     },
    { AV_CPU_FLAG_RVV_F32,   "zve32f"     },
    { AV_CPU_FLAG_RVV_I64,   "zve64x"     },
    { AV_CPU_FLAG_RVV_F64,   "zve64d"     },
    { AV_CPU_FLAG_RV_ZVBB,   "zvbb"       },
    { AV_CPU_FLAG_RV_MISALIGNED, "misaligned" },
#ನೋಚೇದ್ಯದಿ ARCH_WASM
    { AV_CPU_FLAG_SIMD128,   "simd128"    },
#endif
    { 0 }
};

ಸ್ಥಿರ ಶೂನ್ಯ print_cpu_flags(ಪೂರ್ಣಾಙ್ಕ cpu_flags, ಧ್ರುವ ವರ್ಣ *type)
{
    ಪೂರ್ಣಾಙ್ಕ i;

    printf("cpu_flags(%s) = 0x%08X\n", type, cpu_flags);
    printf("cpu_flags_str(%s) =", type);
    ಪ್ರತಿ (i = 0; cpu_flag_tab[i].flag; i++)
        ಯದಿ (cpu_flags & cpu_flag_tab[i].flag)
            printf(" %s", cpu_flag_tab[i].name);
    printf("\n");
}


ಪೂರ್ಣಾಙ್ಕ main(ಪೂರ್ಣಾಙ್ಕ argc, ವರ್ಣ **argv)
{
    ಪೂರ್ಣಾಙ್ಕ cpu_flags_raw = av_get_cpu_flags();
    ಪೂರ್ಣಾಙ್ಕ cpu_flags_eff;
    ಪೂರ್ಣಾಙ್ಕ cpu_ಎಣಿಕೆ = av_cpu_ಎಣಿಕೆ();
    ಧ್ರುವ ವರ್ಣ *threads = "auto";
    ಪೂರ್ಣಾಙ್ಕ i;

    ಪ್ರತಿ(i = 0; cpu_flag_tab[i].flag; i++) {
        unsigned tmp = 0;
        ಯದಿ (av_parse_cpu_caps(&tmp, cpu_flag_tab[i].name) < 0) {
            fprintf(stderr, "Table missing %s\n", cpu_flag_tab[i].name);
            ಪ್ರತ್ಯಾಗಮ 4;
        }
    }

    ಯದಿ (cpu_flags_raw < 0)
        ಪ್ರತ್ಯಾಗಮ 1;

    ಪ್ರತಿ (;;) {
        ಪೂರ್ಣಾಙ್ಕ c = getopt(argc, argv, "c:t:");
        ಯದಿ (c == -1)
            ಭಙ್ಗ;
        ವಿಕಲ್ಪ (c) {
        ಪಕ್ಷ 'c':
        {
            unsigned flags = av_get_cpu_flags();
            ಯದಿ (av_parse_cpu_caps(&flags, optarg) < 0)
                ಪ್ರತ್ಯಾಗಮ 2;

            av_force_cpu_flags(flags);
            ಭಙ್ಗ;
        }
        ಪಕ್ಷ 't':
        {
            threads = optarg;
        }
        }
    }

    cpu_flags_eff = av_get_cpu_flags();

    ಯದಿ (cpu_flags_eff < 0)
        ಪ್ರತ್ಯಾಗಮ 3;

    print_cpu_flags(cpu_flags_raw, "raw");
    print_cpu_flags(cpu_flags_eff, "effective");
    printf("threads = %s (cpu_count = %d)\n", threads, cpu_ಎಣಿಕೆ);
#ಯದಿ ARCH_AARCH64 && HAVE_SVE
    ಯದಿ (cpu_flags_raw & AV_CPU_FLAG_SVE)
        printf("sve_vector_length = %d\n", 8 * ff_aarch64_sve_length());
#endif
#ಯದಿ ARCH_AARCH64 && HAVE_SME
    ಯದಿ (cpu_flags_raw & AV_CPU_FLAG_SME)
        printf("sme_vector_length = %d\n", 8 * ff_aarch64_sme_length());
#endif
#ಯದಿ ARCH_RISCV && HAVE_RVV
    ಯದಿ (cpu_flags_raw & AV_CPU_FLAG_RVV_I32) {
        size_t bytes = ff_get_rv_vlenb();

        printf("rv_vlenb = %zu (%zu bits)\n", bytes, 8 * bytes);
    }
#endif

    ಪ್ರತ್ಯಾಗಮ 0;
}

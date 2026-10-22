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

#ଅନ୍ତର୍ଭାଵ <stdio.h>

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ "libavutil/cpu.h"
#ଅନ୍ତର୍ଭାଵ "libavutil/avstring.h"

#ଯଦି ARCH_AARCH64
#ଅନ୍ତର୍ଭାଵ "libavutil/aarch64/cpu.h"
#ନଚେତଯଦି ARCH_RISCV
#ଅନ୍ତର୍ଭାଵ "libavutil/riscv/cpu.h"
#endif

#ଯଦି HAVE_UNISTD_H
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#endif
#ଯଦି !HAVE_GETOPT
#ଅନ୍ତର୍ଭାଵ "compat/getopt.c"
#endif

ସ୍ଥିର ଅଚଳ ସଂରଚନା {
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flag;
    ଅଚଳ ଅକ୍ଷର *name;
} cpu_flag_tab[] = {
#ଯଦି   ARCH_AARCH64
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
#ନଚେତଯଦି ARCH_ARM
    { AV_CPU_FLAG_ARMV5TE,   "armv5te"    },
    { AV_CPU_FLAG_ARMV6,     "armv6"      },
    { AV_CPU_FLAG_ARMV6T2,   "armv6t2"    },
    { AV_CPU_FLAG_VFP,       "vfp"        },
    { AV_CPU_FLAG_VFP_VM,    "vfp_vm"     },
    { AV_CPU_FLAG_VFPV3,     "vfpv3"      },
    { AV_CPU_FLAG_NEON,      "neon"       },
    { AV_CPU_FLAG_SETEND,    "setend"     },
#ନଚେତଯଦି ARCH_PPC
    { AV_CPU_FLAG_ALTIVEC,   "altivec"    },
    { AV_CPU_FLAG_VSX,       "vsx"        },
    { AV_CPU_FLAG_POWER8,    "power8"     },
#ନଚେତଯଦି ARCH_MIPS
    { AV_CPU_FLAG_MMI,       "mmi"        },
    { AV_CPU_FLAG_MSA,       "msa"        },
#ନଚେତଯଦି ARCH_X86
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
#ନଚେତଯଦି ARCH_LOONGARCH
    { AV_CPU_FLAG_LSX,       "lsx"        },
    { AV_CPU_FLAG_LASX,      "lasx"       },
#ନଚେତଯଦି ARCH_RISCV
    { AV_CPU_FLAG_RVI,       "rvi"        },
    { AV_CPU_FLAG_RVB_BASIC, "zbb"        },
    { AV_CPU_FLAG_RVB,       "rvb"        },
    { AV_CPU_FLAG_RVV_I32,   "zve32x"     },
    { AV_CPU_FLAG_RVV_F32,   "zve32f"     },
    { AV_CPU_FLAG_RVV_I64,   "zve64x"     },
    { AV_CPU_FLAG_RVV_F64,   "zve64d"     },
    { AV_CPU_FLAG_RV_ZVBB,   "zvbb"       },
    { AV_CPU_FLAG_RV_MISALIGNED, "misaligned" },
#ନଚେତଯଦି ARCH_WASM
    { AV_CPU_FLAG_SIMD128,   "simd128"    },
#endif
    { 0 }
};

ସ୍ଥିର ଶୂନ୍ୟ print_cpu_flags(ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags, ଅଚଳ ଅକ୍ଷର *type)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    printf("cpu_flags(%s) = 0x%08X\n", type, cpu_flags);
    printf("cpu_flags_str(%s) =", type);
    ପାଇଁ (i = 0; cpu_flag_tab[i].flag; i++)
        ଯଦି (cpu_flags & cpu_flag_tab[i].flag)
            printf(" %s", cpu_flag_tab[i].name);
    printf("\n");
}


ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୁଖ୍ୟ(ପୂର୍ଣ୍ଣସଂଖ୍ୟା argc, ଅକ୍ଷର **argv)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags_raw = av_get_cpu_flags();
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_flags_eff;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା cpu_ଗଣନା = av_cpu_ଗଣନା();
    ଅଚଳ ଅକ୍ଷର *threads = "auto";
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;

    ପାଇଁ(i = 0; cpu_flag_tab[i].flag; i++) {
        unsigned tmp = 0;
        ଯଦି (av_parse_cpu_caps(&tmp, cpu_flag_tab[i].name) < 0) {
            fprintf(stderr, "Table missing %s\n", cpu_flag_tab[i].name);
            ଫେରନ୍ତୁ 4;
        }
    }

    ଯଦି (cpu_flags_raw < 0)
        ଫେରନ୍ତୁ 1;

    ପାଇଁ (;;) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା c = getopt(argc, argv, "c:t:");
        ଯଦି (c == -1)
            ଭାଙ୍ଗ;
        ବାଛ (c) {
        ସ୍ଥିତି 'c':
        {
            unsigned flags = av_get_cpu_flags();
            ଯଦି (av_parse_cpu_caps(&flags, optarg) < 0)
                ଫେରନ୍ତୁ 2;

            av_force_cpu_flags(flags);
            ଭାଙ୍ଗ;
        }
        ସ୍ଥିତି 't':
        {
            threads = optarg;
        }
        }
    }

    cpu_flags_eff = av_get_cpu_flags();

    ଯଦି (cpu_flags_eff < 0)
        ଫେରନ୍ତୁ 3;

    print_cpu_flags(cpu_flags_raw, "raw");
    print_cpu_flags(cpu_flags_eff, "effective");
    printf("threads = %s (cpu_count = %d)\n", threads, cpu_ଗଣନା);
#ଯଦି ARCH_AARCH64 && HAVE_SVE
    ଯଦି (cpu_flags_raw & AV_CPU_FLAG_SVE)
        printf("sve_vector_length = %d\n", 8 * ff_aarch64_sve_length());
#endif
#ଯଦି ARCH_AARCH64 && HAVE_SME
    ଯଦି (cpu_flags_raw & AV_CPU_FLAG_SME)
        printf("sme_vector_length = %d\n", 8 * ff_aarch64_sme_length());
#endif
#ଯଦି ARCH_RISCV && HAVE_RVV
    ଯଦି (cpu_flags_raw & AV_CPU_FLAG_RVV_I32) {
        size_t bytes = ff_get_rv_vlenb();

        printf("rv_vlenb = %zu (%zu bits)\n", bytes, 8 * bytes);
    }
#endif

    ଫେରନ୍ତୁ 0;
}

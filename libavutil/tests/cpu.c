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

#अन्तर्भाव <stdio.h>

#अन्तर्भाव "config.h"

#अन्तर्भाव "libavutil/cpu.h"
#अन्तर्भाव "libavutil/avstring.h"

#जइ ARCH_AARCH64
#अन्तर्भाव "libavutil/aarch64/cpu.h"
#नोचेद्यदि ARCH_RISCV
#अन्तर्भाव "libavutil/riscv/cpu.h"
#endif

#जइ HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#जइ !HAVE_GETOPT
#अन्तर्भाव "compat/getopt.c"
#endif

स्थिर ध्रुव संरचना {
    पूर्णाङ्क flag;
    ध्रुव वर्ण *name;
} cpu_flag_tab[] = {
#जइ   ARCH_AARCH64
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
#नोचेद्यदि ARCH_ARM
    { AV_CPU_FLAG_ARMV5TE,   "armv5te"    },
    { AV_CPU_FLAG_ARMV6,     "armv6"      },
    { AV_CPU_FLAG_ARMV6T2,   "armv6t2"    },
    { AV_CPU_FLAG_VFP,       "vfp"        },
    { AV_CPU_FLAG_VFP_VM,    "vfp_vm"     },
    { AV_CPU_FLAG_VFPV3,     "vfpv3"      },
    { AV_CPU_FLAG_NEON,      "neon"       },
    { AV_CPU_FLAG_SETEND,    "setend"     },
#नोचेद्यदि ARCH_PPC
    { AV_CPU_FLAG_ALTIVEC,   "altivec"    },
    { AV_CPU_FLAG_VSX,       "vsx"        },
    { AV_CPU_FLAG_POWER8,    "power8"     },
#नोचेद्यदि ARCH_MIPS
    { AV_CPU_FLAG_MMI,       "mmi"        },
    { AV_CPU_FLAG_MSA,       "msa"        },
#नोचेद्यदि ARCH_X86
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
#नोचेद्यदि ARCH_LOONGARCH
    { AV_CPU_FLAG_LSX,       "lsx"        },
    { AV_CPU_FLAG_LASX,      "lasx"       },
#नोचेद्यदि ARCH_RISCV
    { AV_CPU_FLAG_RVI,       "rvi"        },
    { AV_CPU_FLAG_RVB_BASIC, "zbb"        },
    { AV_CPU_FLAG_RVB,       "rvb"        },
    { AV_CPU_FLAG_RVV_I32,   "zve32x"     },
    { AV_CPU_FLAG_RVV_F32,   "zve32f"     },
    { AV_CPU_FLAG_RVV_I64,   "zve64x"     },
    { AV_CPU_FLAG_RVV_F64,   "zve64d"     },
    { AV_CPU_FLAG_RV_ZVBB,   "zvbb"       },
    { AV_CPU_FLAG_RV_MISALIGNED, "misaligned" },
#नोचेद्यदि ARCH_WASM
    { AV_CPU_FLAG_SIMD128,   "simd128"    },
#endif
    { 0 }
};

स्थिर शून्य print_cpu_flags(पूर्णाङ्क cpu_flags, ध्रुव वर्ण *type)
{
    पूर्णाङ्क i;

    printf("cpu_flags(%s) = 0x%08X\n", type, cpu_flags);
    printf("cpu_flags_str(%s) =", type);
    प्रति (i = 0; cpu_flag_tab[i].flag; i++)
        जइ (cpu_flags & cpu_flag_tab[i].flag)
            printf(" %s", cpu_flag_tab[i].name);
    printf("\n");
}


पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण **argv)
{
    पूर्णाङ्क cpu_flags_raw = av_get_cpu_flags();
    पूर्णाङ्क cpu_flags_eff;
    पूर्णाङ्क cpu_गणनम् = av_cpu_गणनम्();
    ध्रुव वर्ण *threads = "auto";
    पूर्णाङ्क i;

    प्रति(i = 0; cpu_flag_tab[i].flag; i++) {
        unsigned tmp = 0;
        जइ (av_parse_cpu_caps(&tmp, cpu_flag_tab[i].name) < 0) {
            fprintf(stderr, "Table missing %s\n", cpu_flag_tab[i].name);
            प्रत्यागम 4;
        }
    }

    जइ (cpu_flags_raw < 0)
        प्रत्यागम 1;

    प्रति (;;) {
        पूर्णाङ्क c = getopt(argc, argv, "c:t:");
        जइ (c == -1)
            भङ्ग;
        विकल्प (c) {
        पक्ष 'c':
        {
            unsigned flags = av_get_cpu_flags();
            जइ (av_parse_cpu_caps(&flags, optarg) < 0)
                प्रत्यागम 2;

            av_force_cpu_flags(flags);
            भङ्ग;
        }
        पक्ष 't':
        {
            threads = optarg;
        }
        }
    }

    cpu_flags_eff = av_get_cpu_flags();

    जइ (cpu_flags_eff < 0)
        प्रत्यागम 3;

    print_cpu_flags(cpu_flags_raw, "raw");
    print_cpu_flags(cpu_flags_eff, "effective");
    printf("threads = %s (cpu_count = %d)\n", threads, cpu_गणनम्);
#जइ ARCH_AARCH64 && HAVE_SVE
    जइ (cpu_flags_raw & AV_CPU_FLAG_SVE)
        printf("sve_vector_length = %d\n", 8 * ff_aarch64_sve_length());
#endif
#जइ ARCH_AARCH64 && HAVE_SME
    जइ (cpu_flags_raw & AV_CPU_FLAG_SME)
        printf("sme_vector_length = %d\n", 8 * ff_aarch64_sme_length());
#endif
#जइ ARCH_RISCV && HAVE_RVV
    जइ (cpu_flags_raw & AV_CPU_FLAG_RVV_I32) {
        size_t bytes = ff_get_rv_vlenb();

        printf("rv_vlenb = %zu (%zu bits)\n", bytes, 8 * bytes);
    }
#endif

    प्रत्यागम 0;
}

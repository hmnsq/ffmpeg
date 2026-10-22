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

#समावेश <stdio.h>

#समावेश "config.h"

#समावेश "libavutil/cpu.h"
#समावेश "libavutil/avstring.h"

#अगर ARCH_AARCH64
#समावेश "libavutil/aarch64/cpu.h"
#या_अगर ARCH_RISCV
#समावेश "libavutil/riscv/cpu.h"
#पूर्ण_अगर

#अगर HAVE_UNISTD_H
#समावेश <unistd.h>
#पूर्ण_अगर
#अगर !HAVE_GETOPT
#समावेश "compat/getopt.c"
#पूर्ण_अगर

अटल स्थिर काष्ठा {
    पूर्णांक flag;
    स्थिर अक्षर *name;
} cpu_flag_tab[] = {
#अगर   ARCH_AARCH64
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
#या_अगर ARCH_ARM
    { AV_CPU_FLAG_ARMV5TE,   "armv5te"    },
    { AV_CPU_FLAG_ARMV6,     "armv6"      },
    { AV_CPU_FLAG_ARMV6T2,   "armv6t2"    },
    { AV_CPU_FLAG_VFP,       "vfp"        },
    { AV_CPU_FLAG_VFP_VM,    "vfp_vm"     },
    { AV_CPU_FLAG_VFPV3,     "vfpv3"      },
    { AV_CPU_FLAG_NEON,      "neon"       },
    { AV_CPU_FLAG_SETEND,    "setend"     },
#या_अगर ARCH_PPC
    { AV_CPU_FLAG_ALTIVEC,   "altivec"    },
    { AV_CPU_FLAG_VSX,       "vsx"        },
    { AV_CPU_FLAG_POWER8,    "power8"     },
#या_अगर ARCH_MIPS
    { AV_CPU_FLAG_MMI,       "mmi"        },
    { AV_CPU_FLAG_MSA,       "msa"        },
#या_अगर ARCH_X86
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
#या_अगर ARCH_LOONGARCH
    { AV_CPU_FLAG_LSX,       "lsx"        },
    { AV_CPU_FLAG_LASX,      "lasx"       },
#या_अगर ARCH_RISCV
    { AV_CPU_FLAG_RVI,       "rvi"        },
    { AV_CPU_FLAG_RVB_BASIC, "zbb"        },
    { AV_CPU_FLAG_RVB,       "rvb"        },
    { AV_CPU_FLAG_RVV_I32,   "zve32x"     },
    { AV_CPU_FLAG_RVV_F32,   "zve32f"     },
    { AV_CPU_FLAG_RVV_I64,   "zve64x"     },
    { AV_CPU_FLAG_RVV_F64,   "zve64d"     },
    { AV_CPU_FLAG_RV_ZVBB,   "zvbb"       },
    { AV_CPU_FLAG_RV_MISALIGNED, "misaligned" },
#या_अगर ARCH_WASM
    { AV_CPU_FLAG_SIMD128,   "simd128"    },
#पूर्ण_अगर
    { 0 }
};

अटल व्योम print_cpu_flags(पूर्णांक cpu_flags, स्थिर अक्षर *type)
{
    पूर्णांक i;

    म_लिखो("cpu_flags(%s) = 0x%08X\n", type, cpu_flags);
    म_लिखो("cpu_flags_str(%s) =", type);
    क्रम (i = 0; cpu_flag_tab[i].flag; i++)
        अगर (cpu_flags & cpu_flag_tab[i].flag)
            म_लिखो(" %s", cpu_flag_tab[i].name);
    म_लिखो("\n");
}


पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
{
    पूर्णांक cpu_flags_raw = av_get_cpu_flags();
    पूर्णांक cpu_flags_eff;
    पूर्णांक cpu_गिनती = av_cpu_गिनती();
    स्थिर अक्षर *threads = "auto";
    पूर्णांक i;

    क्रम(i = 0; cpu_flag_tab[i].flag; i++) {
        अचिन्हित tmp = 0;
        अगर (av_parse_cpu_caps(&tmp, cpu_flag_tab[i].name) < 0) {
            ख_लिखो(मानक_त्रुटि, "Table missing %s\n", cpu_flag_tab[i].name);
            वापस 4;
        }
    }

    अगर (cpu_flags_raw < 0)
        वापस 1;

    क्रम (;;) {
        पूर्णांक c = getopt(argc, argv, "c:t:");
        अगर (c == -1)
            अवरोध;
        चयन (c) {
        हाल 'c':
        {
            अचिन्हित flags = av_get_cpu_flags();
            अगर (av_parse_cpu_caps(&flags, optarg) < 0)
                वापस 2;

            av_force_cpu_flags(flags);
            अवरोध;
        }
        हाल 't':
        {
            threads = optarg;
        }
        }
    }

    cpu_flags_eff = av_get_cpu_flags();

    अगर (cpu_flags_eff < 0)
        वापस 3;

    print_cpu_flags(cpu_flags_raw, "raw");
    print_cpu_flags(cpu_flags_eff, "effective");
    म_लिखो("threads = %s (cpu_count = %d)\n", threads, cpu_गिनती);
#अगर ARCH_AARCH64 && HAVE_SVE
    अगर (cpu_flags_raw & AV_CPU_FLAG_SVE)
        म_लिखो("sve_vector_length = %d\n", 8 * ff_aarch64_sve_लंबाई());
#पूर्ण_अगर
#अगर ARCH_AARCH64 && HAVE_SME
    अगर (cpu_flags_raw & AV_CPU_FLAG_SME)
        म_लिखो("sme_vector_length = %d\n", 8 * ff_aarch64_sme_लंबाई());
#पूर्ण_अगर
#अगर ARCH_RISCV && HAVE_RVV
    अगर (cpu_flags_raw & AV_CPU_FLAG_RVV_I32) {
        माप_प्रकार bytes = ff_get_rv_vlenb();

        म_लिखो("rv_vlenb = %zu (%zu bits)\n", bytes, 8 * bytes);
    }
#पूर्ण_अगर

    वापस 0;
}

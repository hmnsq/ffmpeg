/*
 * Copyright (c) 2015 Manojkumar Bhosale (Manojkumar.Bhosale@imgtec.com)
 *
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_MIPS_GENERIC_MACROS_MSA_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_MIPS_GENERIC_MACROS_MSA_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <msa.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <config.h>

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGNMENT           16
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALLOC_ALIGNED(align) __attribute__ ((aligned((align) << 1)))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_V(RTYPE, psrc) *((RTYPE *)(psrc))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UB(...) LD_V(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SB(...) LD_V(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UH(...) LD_V(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SH(...) LD_V(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UW(...) LD_V(v4u32, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SW(...) LD_V(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_V(RTYPE, ਵਿੱਚ_2, pdst) *((RTYPE *)(pdst)) = (ਵਿੱਚ_2)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_UB(...) ST_V(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SB(...) ST_V(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_UH(...) ST_V(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SH(...) ST_V(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_UW(...) ST_V(v4u32, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SW(...) ST_V(v4i32, __VA_ARGS__)

#ਜੇ HAVE_MIPS32R6 || HAVE_MIPS64R6
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LH(psrc)                              \
    ( {                                           \
        uint16_t val_lh_m = *(uint16_t *)(psrc);  \
        val_lh_m;                                 \
    } )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LW(psrc)                              \
    ( {                                           \
        uint32_t val_lw_m = *(uint32_t *)(psrc);  \
        val_lw_m;                                 \
    } )

    #ਜੇ (__mips == 64)
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD(psrc)                               \
        ( {                                            \
            uint64_t val_ld_m =  *(uint64_t *)(psrc);  \
            val_ld_m;                                  \
        } )
    #ਨਹੀਂਤਾਂ  // !(__mips == 64)
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD(psrc)                                                    \
        ( {                                                                 \
            uint8_t *psrc_ld_m = (uint8_t *) (psrc);                        \
            uint32_t val0_ld_m, val1_ld_m;                                  \
            uint64_t val_ld_m = 0;                                          \
                                                                            \
            val0_ld_m = LW(psrc_ld_m);                                      \
            val1_ld_m = LW(psrc_ld_m + 4);                                  \
                                                                            \
            val_ld_m = (uint64_t) (val1_ld_m);                              \
            val_ld_m = (uint64_t) ((val_ld_m << 32) & 0xFFFFFFFF00000000);  \
            val_ld_m = (uint64_t) (val_ld_m | (uint64_t) val0_ld_m);        \
                                                                            \
            val_ld_m;                                                       \
        } )
    #ਜੇ_ਅੰਤ  // (__mips == 64)

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SH(val, pdst)  *(uint16_t *)(pdst) = (val);
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SW(val, pdst)  *(uint32_t *)(pdst) = (val);
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SD(val, pdst)  *(uint64_t *)(pdst) = (val);

#ਨਹੀਂਤਾਂ  // !HAVE_MIPS32R6 && !HAVE_MIPS64R6
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LH(psrc)                                 \
    ( {                                              \
        uint8_t *psrc_lh_m = (uint8_t *) (psrc);     \
        uint16_t val_lh_m;                           \
                                                     \
        __asm__ ਅਸਥਿਰ (                           \
            "ulh  %[val_lh_m],  %[psrc_lh_m]  \n\t"  \
                                                     \
            : [val_lh_m] "=r" (val_lh_m)             \
            : [psrc_lh_m] "m" (*psrc_lh_m)           \
        );                                           \
                                                     \
        val_lh_m;                                    \
    } )

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LW(psrc)                                 \
    ( {                                              \
        uint8_t *psrc_lw_m = (uint8_t *) (psrc);     \
        uint32_t val_lw_m;                           \
                                                     \
        __asm__ ਅਸਥਿਰ (                           \
            "lwr %[val_lw_m], 0(%[psrc_lw_m]) \n\t"  \
            "lwl %[val_lw_m], 3(%[psrc_lw_m]) \n\t"  \
                                                     \
            : [val_lw_m] "=&r"(val_lw_m)             \
            : [psrc_lw_m] "r"(psrc_lw_m)             \
        );                                           \
                                                     \
        val_lw_m;                                    \
    } )

    #ਜੇ (__mips == 64)
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD(psrc)                                 \
        ( {                                              \
            uint8_t *psrc_ld_m = (uint8_t *) (psrc);     \
            uint64_t val_ld_m = 0;                       \
                                                         \
            __asm__ ਅਸਥਿਰ (                           \
                "ldr %[val_ld_m], 0(%[psrc_ld_m]) \n\t"  \
                "ldl %[val_ld_m], 7(%[psrc_ld_m]) \n\t"  \
                                                         \
                : [val_ld_m] "=&r" (val_ld_m)            \
                : [psrc_ld_m] "r" (psrc_ld_m)            \
            );                                           \
                                                         \
            val_ld_m;                                    \
        } )
    #ਨਹੀਂਤਾਂ  // !(__mips == 64)
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD(psrc)                                                    \
        ( {                                                                 \
            uint8_t *psrc_ld_m = (uint8_t *) (psrc);                        \
            uint32_t val0_ld_m, val1_ld_m;                                  \
            uint64_t val_ld_m = 0;                                          \
                                                                            \
            val0_ld_m = LW(psrc_ld_m);                                      \
            val1_ld_m = LW(psrc_ld_m + 4);                                  \
                                                                            \
            val_ld_m = (uint64_t) (val1_ld_m);                              \
            val_ld_m = (uint64_t) ((val_ld_m << 32) & 0xFFFFFFFF00000000);  \
            val_ld_m = (uint64_t) (val_ld_m | (uint64_t) val0_ld_m);        \
                                                                            \
            val_ld_m;                                                       \
        } )
    #ਜੇ_ਅੰਤ  // (__mips == 64)

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SH(val, pdst)                            \
    {                                                \
        uint8_t *pdst_sh_m = (uint8_t *) (pdst);     \
        uint16_t val_sh_m = (val);                   \
                                                     \
        __asm__ ਅਸਥਿਰ (                           \
            "ush  %[val_sh_m],  %[pdst_sh_m]  \n\t"  \
                                                     \
            : [pdst_sh_m] "=m" (*pdst_sh_m)          \
            : [val_sh_m] "r" (val_sh_m)              \
        );                                           \
    }

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SW(val, pdst)                            \
    {                                                \
        uint8_t *pdst_sw_m = (uint8_t *) (pdst);     \
        uint32_t val_sw_m = (val);                   \
                                                     \
        __asm__ ਅਸਥਿਰ (                           \
            "usw  %[val_sw_m],  %[pdst_sw_m]  \n\t"  \
                                                     \
            : [pdst_sw_m] "=m" (*pdst_sw_m)          \
            : [val_sw_m] "r" (val_sw_m)              \
        );                                           \
    }

    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SD(val, pdst)                                             \
    {                                                                 \
        uint8_t *pdst_sd_m = (uint8_t *) (pdst);                      \
        uint32_t val0_sd_m, val1_sd_m;                                \
                                                                      \
        val0_sd_m = (uint32_t) ((val) & 0x00000000FFFFFFFF);          \
        val1_sd_m = (uint32_t) (((val) >> 32) & 0x00000000FFFFFFFF);  \
                                                                      \
        SW(val0_sd_m, pdst_sd_m);                                     \
        SW(val1_sd_m, pdst_sd_m + 4);                                 \
    }
#ਜੇ_ਅੰਤ // HAVE_MIPS32R6 || HAVE_MIPS64R6

/* Description : Load 4 words with stride
   Arguments   : Inputs  - psrc    (source pointer to load from)
                         - stride
                 Outputs - out0, out1, out2, out3
   Details     : Loads word in 'out0' from (psrc)
                 Loads word in 'out1' from (psrc + stride)
                 Loads word in 'out2' from (psrc + 2 * stride)
                 Loads word in 'out3' from (psrc + 3 * stride)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LW4(psrc, stride, out0, out1, out2, out3)  \
{                                                  \
    out0 = LW((psrc));                             \
    out1 = LW((psrc) + stride);                    \
    out2 = LW((psrc) + 2 * stride);                \
    out3 = LW((psrc) + 3 * stride);                \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LW2(psrc, stride, out0, out1)  \
{                                      \
    out0 = LW((psrc));                 \
    out1 = LW((psrc) + stride);        \
}

/* Description : Load double words with stride
   Arguments   : Inputs  - psrc    (source pointer to load from)
                         - stride
                 Outputs - out0, out1
   Details     : Loads double word in 'out0' from (psrc)
                 Loads double word in 'out1' from (psrc + stride)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD2(psrc, stride, out0, out1)  \
{                                      \
    out0 = LD((psrc));                 \
    out1 = LD((psrc) + stride);        \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD4(psrc, stride, out0, out1, out2, out3)  \
{                                                  \
    LD2((psrc), stride, out0, out1);               \
    LD2((psrc) + 2 * stride, stride, out2, out3);  \
}

/* Description : Store 4 words with stride
   Arguments   : Inputs  - in0, in1, in2, in3, pdst, stride
   Details     : Stores word from 'in0' to (pdst)
                 Stores word from 'in1' to (pdst + stride)
                 Stores word from 'in2' to (pdst + 2 * stride)
                 Stores word from 'in3' to (pdst + 3 * stride)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SW4(in0, in1, in2, in3, pdst, stride)  \
{                                              \
    SW(in0, (pdst))                            \
    SW(in1, (pdst) + stride);                  \
    SW(in2, (pdst) + 2 * stride);              \
    SW(in3, (pdst) + 3 * stride);              \
}

/* Description : Store 4 double words with stride
   Arguments   : Inputs  - in0, in1, in2, in3, pdst, stride
   Details     : Stores double word from 'in0' to (pdst)
                 Stores double word from 'in1' to (pdst + stride)
                 Stores double word from 'in2' to (pdst + 2 * stride)
                 Stores double word from 'in3' to (pdst + 3 * stride)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SD4(in0, in1, in2, in3, pdst, stride)  \
{                                              \
    SD(in0, (pdst))                            \
    SD(in1, (pdst) + stride);                  \
    SD(in2, (pdst) + 2 * stride);              \
    SD(in3, (pdst) + 3 * stride);              \
}

/* Description : Load vector elements with stride
   Arguments   : Inputs  - psrc    (source pointer to load from)
                         - stride
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Loads elements in 'out0' from (psrc)
                 Loads elements in 'out1' from (psrc + stride)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_V2(RTYPE, psrc, stride, out0, out1)  \
{                                               \
    out0 = LD_V(RTYPE, (psrc));                 \
    out1 = LD_V(RTYPE, (psrc) + stride);        \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UB2(...) LD_V2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SB2(...) LD_V2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UH2(...) LD_V2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SH2(...) LD_V2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SW2(...) LD_V2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_V3(RTYPE, psrc, stride, out0, out1, out2)  \
{                                                     \
    LD_V2(RTYPE, (psrc), stride, out0, out1);         \
    out2 = LD_V(RTYPE, (psrc) + 2 * stride);          \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UB3(...) LD_V3(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SB3(...) LD_V3(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_V4(RTYPE, psrc, stride, out0, out1, out2, out3)   \
{                                                            \
    LD_V2(RTYPE, (psrc), stride, out0, out1);                \
    LD_V2(RTYPE, (psrc) + 2 * stride , stride, out2, out3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UB4(...) LD_V4(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SB4(...) LD_V4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UH4(...) LD_V4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SH4(...) LD_V4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SW4(...) LD_V4(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_V5(RTYPE, psrc, stride, out0, out1, out2, out3, out4)  \
{                                                                 \
    LD_V4(RTYPE, (psrc), stride, out0, out1, out2, out3);         \
    out4 = LD_V(RTYPE, (psrc) + 4 * stride);                      \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UB5(...) LD_V5(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SB5(...) LD_V5(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_V6(RTYPE, psrc, stride, out0, out1, out2, out3, out4, out5)  \
{                                                                       \
    LD_V4(RTYPE, (psrc), stride, out0, out1, out2, out3);               \
    LD_V2(RTYPE, (psrc) + 4 * stride, stride, out4, out5);              \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UB6(...) LD_V6(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SB6(...) LD_V6(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UH6(...) LD_V6(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SH6(...) LD_V6(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_V7(RTYPE, psrc, stride,                               \
              out0, out1, out2, out3, out4, out5, out6)          \
{                                                                \
    LD_V5(RTYPE, (psrc), stride, out0, out1, out2, out3, out4);  \
    LD_V2(RTYPE, (psrc) + 5 * stride, stride, out5, out6);       \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UB7(...) LD_V7(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SB7(...) LD_V7(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_V8(RTYPE, psrc, stride,                                      \
              out0, out1, out2, out3, out4, out5, out6, out7)           \
{                                                                       \
    LD_V4(RTYPE, (psrc), stride, out0, out1, out2, out3);               \
    LD_V4(RTYPE, (psrc) + 4 * stride, stride, out4, out5, out6, out7);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UB8(...) LD_V8(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SB8(...) LD_V8(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_UH8(...) LD_V8(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SH8(...) LD_V8(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SW8(...) LD_V8(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_V16(RTYPE, psrc, stride,                                   \
               out0, out1, out2, out3, out4, out5, out6, out7,        \
               out8, out9, out10, out11, out12, out13, out14, out15)  \
{                                                                     \
    LD_V8(RTYPE, (psrc), stride,                                      \
          out0, out1, out2, out3, out4, out5, out6, out7);            \
    LD_V8(RTYPE, (psrc) + 8 * stride, stride,                         \
          out8, out9, out10, out11, out12, out13, out14, out15);      \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LD_SH16(...) LD_V16(v8i16, __VA_ARGS__)

/* Description : Store vectors with stride
   Arguments   : Inputs  - in0, in1, stride
                 Outputs - pdst    (destination pointer to store to)
   Details     : Stores elements from 'in0' to (pdst)
                 Stores elements from 'in1' to (pdst + stride)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_V2(RTYPE, in0, in1, pdst, stride)  \
{                                             \
    ST_V(RTYPE, in0, (pdst));                 \
    ST_V(RTYPE, in1, (pdst) + stride);        \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_UB2(...) ST_V2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SB2(...) ST_V2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_UH2(...) ST_V2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SH2(...) ST_V2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SW2(...) ST_V2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_V4(RTYPE, in0, in1, in2, in3, pdst, stride)    \
{                                                         \
    ST_V2(RTYPE, in0, in1, (pdst), stride);               \
    ST_V2(RTYPE, in2, in3, (pdst) + 2 * stride, stride);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_UB4(...) ST_V4(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SB4(...) ST_V4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SH4(...) ST_V4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SW4(...) ST_V4(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_V6(RTYPE, in0, in1, in2, in3, in4, in5, pdst, stride)  \
{                                                                 \
    ST_V4(RTYPE, in0, in1, in2, in3, (pdst), stride);             \
    ST_V2(RTYPE, in4, in5, (pdst) + 4 * stride, stride);          \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SH6(...) ST_V6(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_V8(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride)  \
{                                                                           \
    ST_V4(RTYPE, in0, in1, in2, in3, (pdst), stride);                       \
    ST_V4(RTYPE, in4, in5, in6, in7, (pdst) + 4 * stride, stride);          \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_UB8(...) ST_V8(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SH8(...) ST_V8(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_SW8(...) ST_V8(v4i32, __VA_ARGS__)

/* Description : Store half word elements of vector with stride
 * Arguments   : Inputs  - in   source vector
 *                       - pdst    (destination pointer to store to)
 *                       - stride
 * Details     : Stores half word 'idx0' from 'in' to (pdst)
 *               Stores half word 'idx1' from 'in' to (pdst + stride)
 *               Similar for other elements
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_H1(ਵਿੱਚ_2, idx, pdst)                             \
{                                                        \
    uint16_t out0_m;                                     \
    out0_m = __msa_copy_u_h((v8i16) ਵਿੱਚ_2, idx);            \
    SH(out0_m, (pdst));                                  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_H2(ਵਿੱਚ_2, idx0, idx1, pdst, stride)              \
{                                                        \
    uint16_t out0_m, out1_m;                             \
    out0_m = __msa_copy_u_h((v8i16) ਵਿੱਚ_2, idx0);           \
    out1_m = __msa_copy_u_h((v8i16) ਵਿੱਚ_2, idx1);           \
    SH(out0_m, (pdst));                                  \
    SH(out1_m, (pdst) + stride);                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_H4(ਵਿੱਚ_2, idx0, idx1, idx2, idx3, pdst, stride)  \
{                                                        \
    uint16_t out0_m, out1_m, out2_m, out3_m;             \
    out0_m = __msa_copy_u_h((v8i16) ਵਿੱਚ_2, idx0);           \
    out1_m = __msa_copy_u_h((v8i16) ਵਿੱਚ_2, idx1);           \
    out2_m = __msa_copy_u_h((v8i16) ਵਿੱਚ_2, idx2);           \
    out3_m = __msa_copy_u_h((v8i16) ਵਿੱਚ_2, idx3);           \
    SH(out0_m, (pdst));                                  \
    SH(out1_m, (pdst) + stride);                         \
    SH(out2_m, (pdst) + 2 * stride);                     \
    SH(out3_m, (pdst) + 3 * stride);                     \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_H8(ਵਿੱਚ_2, idx0, idx1, idx2, idx3, idx4, idx5,            \
              idx6, idx7, pdst, stride)                          \
{                                                                \
    ST_H4(ਵਿੱਚ_2, idx0, idx1, idx2, idx3, pdst, stride)              \
    ST_H4(ਵਿੱਚ_2, idx4, idx5, idx6, idx7, (pdst) + 4*stride, stride) \
}

/* Description : Store word elements of vector with stride
 * Arguments   : Inputs  - in   source vector
 *                       - pdst    (destination pointer to store to)
 *                       - stride
 * Details     : Stores word 'idx0' from 'in' to (pdst)
 *               Stores word 'idx1' from 'in' to (pdst + stride)
 *               Similar for other elements
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_W1(ਵਿੱਚ_2, idx, pdst)                             \
{                                                        \
    uint32_t out0_m;                                     \
    out0_m = __msa_copy_u_w((v4i32) ਵਿੱਚ_2, idx);            \
    SW(out0_m, (pdst));                                  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_W2(ਵਿੱਚ_2, idx0, idx1, pdst, stride)              \
{                                                        \
    uint32_t out0_m, out1_m;                             \
    out0_m = __msa_copy_u_w((v4i32) ਵਿੱਚ_2, idx0);           \
    out1_m = __msa_copy_u_w((v4i32) ਵਿੱਚ_2, idx1);           \
    SW(out0_m, (pdst));                                  \
    SW(out1_m, (pdst) + stride);                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_W4(ਵਿੱਚ_2, idx0, idx1, idx2, idx3, pdst, stride)  \
{                                                        \
    uint32_t out0_m, out1_m, out2_m, out3_m;             \
    out0_m = __msa_copy_u_w((v4i32) ਵਿੱਚ_2, idx0);           \
    out1_m = __msa_copy_u_w((v4i32) ਵਿੱਚ_2, idx1);           \
    out2_m = __msa_copy_u_w((v4i32) ਵਿੱਚ_2, idx2);           \
    out3_m = __msa_copy_u_w((v4i32) ਵਿੱਚ_2, idx3);           \
    SW(out0_m, (pdst));                                  \
    SW(out1_m, (pdst) + stride);                         \
    SW(out2_m, (pdst) + 2*stride);                       \
    SW(out3_m, (pdst) + 3*stride);                       \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_W8(in0, in1, idx0, idx1, idx2, idx3,                 \
              idx4, idx5, idx6, idx7, pdst, stride)             \
{                                                               \
    ST_W4(in0, idx0, idx1, idx2, idx3, pdst, stride)            \
    ST_W4(in1, idx4, idx5, idx6, idx7, pdst + 4*stride, stride) \
}

/* Description : Store double word elements of vector with stride
 * Arguments   : Inputs  - in   source vector
 *                       - pdst    (destination pointer to store to)
 *                       - stride
 * Details     : Stores double word 'idx0' from 'in' to (pdst)
 *               Stores double word 'idx1' from 'in' to (pdst + stride)
 *               Similar for other elements
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_D1(ਵਿੱਚ_2, idx, pdst)                   \
{                                              \
    uint64_t out0_m;                           \
    out0_m = __msa_copy_u_d((v2i64) ਵਿੱਚ_2, idx);  \
    SD(out0_m, (pdst));                        \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_D2(ਵਿੱਚ_2, idx0, idx1, pdst, stride)    \
{                                              \
    uint64_t out0_m, out1_m;                   \
    out0_m = __msa_copy_u_d((v2i64) ਵਿੱਚ_2, idx0); \
    out1_m = __msa_copy_u_d((v2i64) ਵਿੱਚ_2, idx1); \
    SD(out0_m, (pdst));                        \
    SD(out1_m, (pdst) + stride);               \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_D4(in0, in1, idx0, idx1, idx2, idx3, pdst, stride) \
{                                                             \
    uint64_t out0_m, out1_m, out2_m, out3_m;                  \
    out0_m = __msa_copy_u_d((v2i64) in0, idx0);               \
    out1_m = __msa_copy_u_d((v2i64) in0, idx1);               \
    out2_m = __msa_copy_u_d((v2i64) in1, idx2);               \
    out3_m = __msa_copy_u_d((v2i64) in1, idx3);               \
    SD(out0_m, (pdst));                                       \
    SD(out1_m, (pdst) + stride);                              \
    SD(out2_m, (pdst) + 2 * stride);                          \
    SD(out3_m, (pdst) + 3 * stride);                          \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST_D8(in0, in1, in2, in3, idx0, idx1, idx2, idx3,              \
              idx4, idx5, idx6, idx7, pdst, stride)                    \
{                                                                      \
    ST_D4(in0, in1, idx0, idx1, idx2, idx3, pdst, stride)              \
    ST_D4(in2, in3, idx4, idx5, idx6, idx7, pdst + 4 * stride, stride) \
}

/* Description : Store as 12x8 byte block to destination memory from
                 input vectors
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride
   Details     : Index 0 double word element from input vector 'in0' is copied
                 and stored to destination memory at (pblk_12x8_m) followed by
                 index 2 word element from same input vector 'in0' at
                 (pblk_12x8_m + 8)
                 Similar to remaining lines
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ST12x8_UB(in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride)  \
{                                                                        \
    uint64_t out0_m, out1_m, out2_m, out3_m;                             \
    uint64_t out4_m, out5_m, out6_m, out7_m;                             \
    uint32_t out8_m, out9_m, out10_m, out11_m;                           \
    uint32_t out12_m, out13_m, out14_m, out15_m;                         \
    uint8_t *pblk_12x8_m = (uint8_t *) (pdst);                           \
                                                                         \
    out0_m = __msa_copy_u_d((v2i64) in0, 0);                             \
    out1_m = __msa_copy_u_d((v2i64) in1, 0);                             \
    out2_m = __msa_copy_u_d((v2i64) in2, 0);                             \
    out3_m = __msa_copy_u_d((v2i64) in3, 0);                             \
    out4_m = __msa_copy_u_d((v2i64) in4, 0);                             \
    out5_m = __msa_copy_u_d((v2i64) in5, 0);                             \
    out6_m = __msa_copy_u_d((v2i64) in6, 0);                             \
    out7_m = __msa_copy_u_d((v2i64) in7, 0);                             \
                                                                         \
    out8_m =  __msa_copy_u_w((v4i32) in0, 2);                            \
    out9_m =  __msa_copy_u_w((v4i32) in1, 2);                            \
    out10_m = __msa_copy_u_w((v4i32) in2, 2);                            \
    out11_m = __msa_copy_u_w((v4i32) in3, 2);                            \
    out12_m = __msa_copy_u_w((v4i32) in4, 2);                            \
    out13_m = __msa_copy_u_w((v4i32) in5, 2);                            \
    out14_m = __msa_copy_u_w((v4i32) in6, 2);                            \
    out15_m = __msa_copy_u_w((v4i32) in7, 2);                            \
                                                                         \
    SD(out0_m, pblk_12x8_m);                                             \
    SW(out8_m, pblk_12x8_m + 8);                                         \
    pblk_12x8_m += stride;                                               \
    SD(out1_m, pblk_12x8_m);                                             \
    SW(out9_m, pblk_12x8_m + 8);                                         \
    pblk_12x8_m += stride;                                               \
    SD(out2_m, pblk_12x8_m);                                             \
    SW(out10_m, pblk_12x8_m + 8);                                        \
    pblk_12x8_m += stride;                                               \
    SD(out3_m, pblk_12x8_m);                                             \
    SW(out11_m, pblk_12x8_m + 8);                                        \
    pblk_12x8_m += stride;                                               \
    SD(out4_m, pblk_12x8_m);                                             \
    SW(out12_m, pblk_12x8_m + 8);                                        \
    pblk_12x8_m += stride;                                               \
    SD(out5_m, pblk_12x8_m);                                             \
    SW(out13_m, pblk_12x8_m + 8);                                        \
    pblk_12x8_m += stride;                                               \
    SD(out6_m, pblk_12x8_m);                                             \
    SW(out14_m, pblk_12x8_m + 8);                                        \
    pblk_12x8_m += stride;                                               \
    SD(out7_m, pblk_12x8_m);                                             \
    SW(out15_m, pblk_12x8_m + 8);                                        \
}

/* Description : average with rounding (in0 + in1 + 1) / 2.
   Arguments   : Inputs  - in0, in1, in2, in3,
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Each byte element from 'in0' vector is added with each byte
                 element from 'in1' vector. The addition of the elements plus 1
                (for rounding) is done unsigned with full precision,
                i.e. the result has one extra bit. Unsigned division by 2
                (or logical shift right by one bit) is performed before writing
                the result to vector 'out0'
                Similar for the pair of 'in2' and 'in3'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVER_UB2(RTYPE, in0, in1, in2, in3, out0, out1)       \
{                                                             \
    out0 = (RTYPE) __msa_aver_u_b((v16u8) in0, (v16u8) in1);  \
    out1 = (RTYPE) __msa_aver_u_b((v16u8) in2, (v16u8) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVER_UB2_UB(...) AVER_UB2(v16u8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVER_UB4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7, \
                 out0, out1, out2, out3)                        \
{                                                               \
    AVER_UB2(RTYPE, in0, in1, in2, in3, out0, out1)             \
    AVER_UB2(RTYPE, in4, in5, in6, in7, out2, out3)             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVER_UB4_UB(...) AVER_UB4(v16u8, __VA_ARGS__)

/* Description : Immediate number of columns to slide
   Arguments   : Inputs  - s, d, slide_val
                 Outputs - out
                 Return Type - as per RTYPE
   Details     : Byte elements from 'd' vector are slide into 's' by
                 number of elements specified by 'slide_val'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B(RTYPE, d, s, slide_val, ਬਾਹਰਲਾ)                       \
{                                                                 \
    ਬਾਹਰਲਾ = (RTYPE) __msa_sldi_b((v16i8) d, (v16i8) s, slide_val);  \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B2(RTYPE, d0, s0, d1, s1, slide_val, out0, out1)  \
{                                                              \
    SLDI_B(RTYPE, d0, s0, slide_val, out0)                     \
    SLDI_B(RTYPE, d1, s1, slide_val, out1)                     \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B2_UB(...) SLDI_B2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B2_SB(...) SLDI_B2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B2_SH(...) SLDI_B2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B2_SW(...) SLDI_B2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B3(RTYPE, d0, s0, d1, s1, d2, s2, slide_val,  \
                out0, out1, out2)                          \
{                                                          \
    SLDI_B2(RTYPE, d0, s0, d1, s1, slide_val, out0, out1)  \
    SLDI_B(RTYPE, d2, s2, slide_val, out2)                 \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B3_UB(...) SLDI_B3(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B3_SB(...) SLDI_B3(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B3_UH(...) SLDI_B3(v8u16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B4(RTYPE, d0, s0, d1, s1, d2, s2, d3, s3,     \
                slide_val, out0, out1, out2, out3)         \
{                                                          \
    SLDI_B2(RTYPE, d0, s0, d1, s1, slide_val, out0, out1)  \
    SLDI_B2(RTYPE, d2, s2, d3, s3, slide_val, out2, out3)  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B4_UB(...) SLDI_B4(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B4_SB(...) SLDI_B4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLDI_B4_SH(...) SLDI_B4(v8i16, __VA_ARGS__)

/* Description : Shuffle byte vector elements as per mask vector
   Arguments   : Inputs  - in0, in1, in2, in3, mask0, mask1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Selective byte elements from in0 & in1 are copied to out0 as
                 per control vector mask0
                 Selective byte elements from in2 & in3 are copied to out1 as
                 per control vector mask1
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B2(RTYPE, in0, in1, in2, in3, mask0, mask1, out0, out1)       \
{                                                                          \
    out0 = (RTYPE) __msa_vshf_b((v16i8) mask0, (v16i8) in1, (v16i8) in0);  \
    out1 = (RTYPE) __msa_vshf_b((v16i8) mask1, (v16i8) in3, (v16i8) in2);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B2_UB(...) VSHF_B2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B2_SB(...) VSHF_B2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B2_UH(...) VSHF_B2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B2_SH(...) VSHF_B2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B3(RTYPE, in0, in1, in2, in3, in4, in5, mask0, mask1, mask2,  \
                out0, out1, out2)                                          \
{                                                                          \
    VSHF_B2(RTYPE, in0, in1, in2, in3, mask0, mask1, out0, out1);          \
    out2 = (RTYPE) __msa_vshf_b((v16i8) mask2, (v16i8) in5, (v16i8) in4);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B3_SB(...) VSHF_B3(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B4(RTYPE, in0, in1, mask0, mask1, mask2, mask3,       \
                out0, out1, out2, out3)                            \
{                                                                  \
    VSHF_B2(RTYPE, in0, in1, in0, in1, mask0, mask1, out0, out1);  \
    VSHF_B2(RTYPE, in0, in1, in0, in1, mask2, mask3, out2, out3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B4_SB(...) VSHF_B4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_B4_SH(...) VSHF_B4(v8i16, __VA_ARGS__)

/* Description : Shuffle halfword vector elements as per mask vector
   Arguments   : Inputs  - in0, in1, in2, in3, mask0, mask1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Selective halfword elements from in0 & in1 are copied to out0
                 as per control vector mask0
                 Selective halfword elements from in2 & in3 are copied to out1
                 as per control vector mask1
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_H2(RTYPE, in0, in1, in2, in3, mask0, mask1, out0, out1)       \
{                                                                          \
    out0 = (RTYPE) __msa_vshf_h((v8i16) mask0, (v8i16) in1, (v8i16) in0);  \
    out1 = (RTYPE) __msa_vshf_h((v8i16) mask1, (v8i16) in3, (v8i16) in2);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_H2_SH(...) VSHF_H2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_H3(RTYPE, in0, in1, in2, in3, in4, in5, mask0, mask1, mask2,  \
                out0, out1, out2)                                          \
{                                                                          \
    VSHF_H2(RTYPE, in0, in1, in2, in3, mask0, mask1, out0, out1);          \
    out2 = (RTYPE) __msa_vshf_h((v8i16) mask2, (v8i16) in5, (v8i16) in4);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_H3_SH(...) VSHF_H3(v8i16, __VA_ARGS__)

/* Description : Shuffle byte vector elements as per mask vector
   Arguments   : Inputs  - in0, in1, in2, in3, mask0, mask1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Selective byte elements from in0 & in1 are copied to out0 as
                 per control vector mask0
                 Selective byte elements from in2 & in3 are copied to out1 as
                 per control vector mask1
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_W2(RTYPE, in0, in1, in2, in3, mask0, mask1, out0, out1)      \
{                                                                         \
    out0 = (RTYPE) __msa_vshf_w((v4i32) mask0, (v4i32) in1, (v4i32) in0); \
    out1 = (RTYPE) __msa_vshf_w((v4i32) mask1, (v4i32) in3, (v4i32) in2); \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VSHF_W2_SB(...) VSHF_W2(v16i8, __VA_ARGS__)

/* Description : Dot product of byte vector elements
   Arguments   : Inputs  - mult0, mult1
                           cnst0, cnst1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Unsigned byte elements from mult0 are multiplied with
                 unsigned byte elements from cnst0 producing a result
                 twice the size of input i.e. unsigned halfword.
                 Then this multiplication results of adjacent odd-even elements
                 are added together and stored to the out vector
                 (2 unsigned halfword results)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_UB2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1)   \
{                                                                 \
    out0 = (RTYPE) __msa_dotp_u_h((v16u8) mult0, (v16u8) cnst0);  \
    out1 = (RTYPE) __msa_dotp_u_h((v16u8) mult1, (v16u8) cnst1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_UB2_UH(...) DOTP_UB2(v8u16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_UB4(RTYPE, mult0, mult1, mult2, mult3,           \
                 cnst0, cnst1, cnst2, cnst3,                  \
                 out0, out1, out2, out3)                      \
{                                                             \
    DOTP_UB2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1);  \
    DOTP_UB2(RTYPE, mult2, mult3, cnst2, cnst3, out2, out3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_UB4_UH(...) DOTP_UB4(v8u16, __VA_ARGS__)

/* Description : Dot product of byte vector elements
   Arguments   : Inputs  - mult0, mult1
                           cnst0, cnst1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Signed byte elements from mult0 are multiplied with
                 signed byte elements from cnst0 producing a result
                 twice the size of input i.e. signed halfword.
                 Then this multiplication results of adjacent odd-even elements
                 are added together and stored to the out vector
                 (2 signed halfword results)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SB2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1)   \
{                                                                 \
    out0 = (RTYPE) __msa_dotp_s_h((v16i8) mult0, (v16i8) cnst0);  \
    out1 = (RTYPE) __msa_dotp_s_h((v16i8) mult1, (v16i8) cnst1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SB2_SH(...) DOTP_SB2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SB3(RTYPE, mult0, mult1, mult2, cnst0, cnst1, cnst2,  \
                 out0, out1, out2)                                 \
{                                                                  \
    DOTP_SB2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1);       \
    out2 = (RTYPE) __msa_dotp_s_h((v16i8) mult2, (v16i8) cnst2);   \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SB3_SH(...) DOTP_SB3(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SB4(RTYPE, mult0, mult1, mult2, mult3,                   \
                 cnst0, cnst1, cnst2, cnst3, out0, out1, out2, out3)  \
{                                                                     \
    DOTP_SB2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1);          \
    DOTP_SB2(RTYPE, mult2, mult3, cnst2, cnst3, out2, out3);          \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SB4_SH(...) DOTP_SB4(v8i16, __VA_ARGS__)

/* Description : Dot product of halfword vector elements
   Arguments   : Inputs  - mult0, mult1
                           cnst0, cnst1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Signed halfword elements from mult0 are multiplied with
                 signed halfword elements from cnst0 producing a result
                 twice the size of input i.e. signed word.
                 Then this multiplication results of adjacent odd-even elements
                 are added together and stored to the out vector
                 (2 signed word results)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SH2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1)   \
{                                                                 \
    out0 = (RTYPE) __msa_dotp_s_w((v8i16) mult0, (v8i16) cnst0);  \
    out1 = (RTYPE) __msa_dotp_s_w((v8i16) mult1, (v8i16) cnst1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SH2_SW(...) DOTP_SH2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SH4(RTYPE, mult0, mult1, mult2, mult3,           \
                 cnst0, cnst1, cnst2, cnst3,                  \
                 out0, out1, out2, out3)                      \
{                                                             \
    DOTP_SH2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1);  \
    DOTP_SH2(RTYPE, mult2, mult3, cnst2, cnst3, out2, out3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DOTP_SH4_SW(...) DOTP_SH4(v4i32, __VA_ARGS__)

/* Description : Dot product & addition of byte vector elements
   Arguments   : Inputs  - mult0, mult1
                           cnst0, cnst1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Signed byte elements from mult0 are multiplied with
                 signed byte elements from cnst0 producing a result
                 twice the size of input i.e. signed halfword.
                 Then this multiplication results of adjacent odd-even elements
                 are added to the out vector
                 (2 signed halfword results)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_SB2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1)   \
{                                                                  \
    out0 = (RTYPE) __msa_dpadd_s_h((v8i16) out0,                   \
                                   (v16i8) mult0, (v16i8) cnst0);  \
    out1 = (RTYPE) __msa_dpadd_s_h((v8i16) out1,                   \
                                   (v16i8) mult1, (v16i8) cnst1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_SB2_SH(...) DPADD_SB2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_SB4(RTYPE, mult0, mult1, mult2, mult3,                   \
                  cnst0, cnst1, cnst2, cnst3, out0, out1, out2, out3)  \
{                                                                      \
    DPADD_SB2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1);          \
    DPADD_SB2(RTYPE, mult2, mult3, cnst2, cnst3, out2, out3);          \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_SB4_SH(...) DPADD_SB4(v8i16, __VA_ARGS__)

/* Description : Dot product & addition of byte vector elements
   Arguments   : Inputs  - mult0, mult1
                           cnst0, cnst1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Unsigned byte elements from mult0 are multiplied with
                 unsigned byte elements from cnst0 producing a result
                 twice the size of input i.e. unsigned halfword.
                 Then this multiplication results of adjacent odd-even elements
                 are added to the out vector
                 (2 unsigned halfword results)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_UB2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1)   \
{                                                                  \
    out0 = (RTYPE) __msa_dpadd_u_h((v8u16) out0,                   \
                                   (v16u8) mult0, (v16u8) cnst0);  \
    out1 = (RTYPE) __msa_dpadd_u_h((v8u16) out1,                   \
                                   (v16u8) mult1, (v16u8) cnst1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_UB2_UH(...) DPADD_UB2(v8u16, __VA_ARGS__)

/* Description : Dot product & addition of halfword vector elements
   Arguments   : Inputs  - mult0, mult1
                           cnst0, cnst1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Signed halfword elements from mult0 are multiplied with
                 signed halfword elements from cnst0 producing a result
                 twice the size of input i.e. signed word.
                 Then this multiplication results of adjacent odd-even elements
                 are added to the out vector
                 (2 signed word results)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_SH2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1)   \
{                                                                  \
    out0 = (RTYPE) __msa_dpadd_s_w((v4i32) out0,                   \
                                   (v8i16) mult0, (v8i16) cnst0);  \
    out1 = (RTYPE) __msa_dpadd_s_w((v4i32) out1,                   \
                                   (v8i16) mult1, (v8i16) cnst1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_SH2_SW(...) DPADD_SH2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_SH4(RTYPE, mult0, mult1, mult2, mult3,                   \
                  cnst0, cnst1, cnst2, cnst3, out0, out1, out2, out3)  \
{                                                                      \
    DPADD_SH2(RTYPE, mult0, mult1, cnst0, cnst1, out0, out1);          \
    DPADD_SH2(RTYPE, mult2, mult3, cnst2, cnst3, out2, out3);          \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_SH4_SW(...) DPADD_SH4(v4i32, __VA_ARGS__)

/* Description : Minimum values between unsigned elements of
                 either vector are copied to the output vector
   Arguments   : Inputs  - in0, in1, min_vec
                 Outputs - in0, in1, (in place)
                 Return Type - as per RTYPE
   Details     : Minimum of unsigned halfword element values from 'in0' and
                 'min_value' are written to output vector 'in0'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_UH2(RTYPE, in0, in1, min_vec)               \
{                                                       \
    in0 = (RTYPE) __msa_min_u_h((v8u16) in0, min_vec);  \
    in1 = (RTYPE) __msa_min_u_h((v8u16) in1, min_vec);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_UH2_UH(...) MIN_UH2(v8u16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_UH4(RTYPE, in0, in1, in2, in3, min_vec)  \
{                                                    \
    MIN_UH2(RTYPE, in0, in1, min_vec);               \
    MIN_UH2(RTYPE, in2, in3, min_vec);               \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MIN_UH4_UH(...) MIN_UH4(v8u16, __VA_ARGS__)

/* Description : Clips all halfword elements of input vector between min & max
                 out = ((in) < (min)) ? (min) : (((in) > (max)) ? (max) : (in))
   Arguments   : Inputs  - in    (input vector)
                         - min   (min threshold)
                         - max   (max threshold)
                 Outputs - in    (output vector with clipped elements)
                 Return Type - signed halfword
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIP_SH(ਵਿੱਚ_2, min, max)                     \
{                                                 \
    ਵਿੱਚ_2 = __msa_max_s_h((v8i16) min, (v8i16) ਵਿੱਚ_2);  \
    ਵਿੱਚ_2 = __msa_min_s_h((v8i16) max, (v8i16) ਵਿੱਚ_2);  \
}

/* Description : Clips all signed halfword elements of input vector
                 between 0 & 255
   Arguments   : Inputs  - in    (input vector)
                 Outputs - in    (output vector with clipped elements)
                 Return Type - signed halfwords
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIP_SH_0_255(ਵਿੱਚ_2)                       \
{                                               \
    ਵਿੱਚ_2 = __msa_maxi_s_h((v8i16) ਵਿੱਚ_2, 0);         \
    ਵਿੱਚ_2 = (v8i16) __msa_sat_u_h((v8u16) ਵਿੱਚ_2, 7);  \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIP_SH2_0_255(in0, in1)  \
{                                 \
    CLIP_SH_0_255(in0);           \
    CLIP_SH_0_255(in1);           \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIP_SH4_0_255(in0, in1, in2, in3)  \
{                                           \
    CLIP_SH2_0_255(in0, in1);               \
    CLIP_SH2_0_255(in2, in3);               \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIP_SH8_0_255(in0, in1, in2, in3,  \
                       in4, in5, in6, in7)  \
{                                           \
    CLIP_SH4_0_255(in0, in1, in2, in3);     \
    CLIP_SH4_0_255(in4, in5, in6, in7);     \
}

/* Description : Clips all signed word elements of input vector
                 between 0 & 255
   Arguments   : Inputs  - in    (input vector)
                 Outputs - in    (output vector with clipped elements)
                 Return Type - signed word
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIP_SW_0_255(ਵਿੱਚ_2)                       \
{                                               \
    ਵਿੱਚ_2 = __msa_maxi_s_w((v4i32) ਵਿੱਚ_2, 0);         \
    ਵਿੱਚ_2 = (v4i32) __msa_sat_u_w((v4u32) ਵਿੱਚ_2, 7);  \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIP_SW2_0_255(in0, in1)  \
{                                 \
    CLIP_SW_0_255(in0);           \
    CLIP_SW_0_255(in1);           \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIP_SW4_0_255(in0, in1, in2, in3)  \
{                                           \
    CLIP_SW2_0_255(in0, in1);               \
    CLIP_SW2_0_255(in2, in3);               \
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CLIP_SW8_0_255(in0, in1, in2, in3,  \
                       in4, in5, in6, in7)  \
{                                           \
    CLIP_SW4_0_255(in0, in1, in2, in3);     \
    CLIP_SW4_0_255(in4, in5, in6, in7);     \
}

/* Description : Addition of 4 signed word elements
                 4 signed word elements of input vector are added together and
                 resulted integer sum is returned
   Arguments   : Inputs  - in       (signed word vector)
                 Outputs - sum_m    (i32 sum)
                 Return Type - signed word
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_SW_S32(ਵਿੱਚ_2)                               \
( {                                                   \
    v2i64 res0_m, res1_m;                             \
    int32_t ਜੋੜ_m;                                    \
                                                      \
    res0_m = __msa_hadd_s_d((v4i32) ਵਿੱਚ_2, (v4i32) ਵਿੱਚ_2);  \
    res1_m = __msa_splati_d(res0_m, 1);               \
    res0_m += res1_m;                                 \
    ਜੋੜ_m = __msa_copy_s_w((v4i32) res0_m, 0);        \
    ਜੋੜ_m;                                            \
} )

/* Description : Addition of 8 unsigned halfword elements
                 8 unsigned halfword elements of input vector are added
                 together and resulted integer sum is returned
   Arguments   : Inputs  - in       (unsigned halfword vector)
                 Outputs - sum_m    (u32 sum)
                 Return Type - unsigned word
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_UH_U32(ਵਿੱਚ_2)                                  \
( {                                                      \
    v4u32 res_m;                                         \
    v2u64 res0_m, res1_m;                                \
    uint32_t ਜੋੜ_m;                                      \
                                                         \
    res_m = __msa_hadd_u_w((v8u16) ਵਿੱਚ_2, (v8u16) ਵਿੱਚ_2);      \
    res0_m = __msa_hadd_u_d(res_m, res_m);               \
    res1_m = (v2u64) __msa_splati_d((v2i64) res0_m, 1);  \
    res0_m += res1_m;                                    \
    ਜੋੜ_m = __msa_copy_u_w((v4i32) res0_m, 0);           \
    ਜੋੜ_m;                                               \
} )

/* Description : Horizontal addition of signed byte vector elements
   Arguments   : Inputs  - in0, in1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Each signed odd byte element from 'in0' is added to
                 even signed byte element from 'in0' (pairwise) and the
                 halfword result is stored in 'out0'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_SB2(RTYPE, in0, in1, out0, out1)                 \
{                                                             \
    out0 = (RTYPE) __msa_hadd_s_h((v16i8) in0, (v16i8) in0);  \
    out1 = (RTYPE) __msa_hadd_s_h((v16i8) in1, (v16i8) in1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_SB2_SH(...) HADD_SB2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_SB4(RTYPE, in0, in1, in2, in3, out0, out1, out2, out3)  \
{                                                                    \
    HADD_SB2(RTYPE, in0, in1, out0, out1);                           \
    HADD_SB2(RTYPE, in2, in3, out2, out3);                           \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_SB4_UH(...) HADD_SB4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_SB4_SH(...) HADD_SB4(v8i16, __VA_ARGS__)

/* Description : Horizontal addition of unsigned byte vector elements
   Arguments   : Inputs  - in0, in1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Each unsigned odd byte element from 'in0' is added to
                 even unsigned byte element from 'in0' (pairwise) and the
                 halfword result is stored in 'out0'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_UB2(RTYPE, in0, in1, out0, out1)                 \
{                                                             \
    out0 = (RTYPE) __msa_hadd_u_h((v16u8) in0, (v16u8) in0);  \
    out1 = (RTYPE) __msa_hadd_u_h((v16u8) in1, (v16u8) in1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_UB2_UH(...) HADD_UB2(v8u16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_UB3(RTYPE, in0, in1, in2, out0, out1, out2)      \
{                                                             \
    HADD_UB2(RTYPE, in0, in1, out0, out1);                    \
    out2 = (RTYPE) __msa_hadd_u_h((v16u8) in2, (v16u8) in2);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_UB3_UH(...) HADD_UB3(v8u16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_UB4(RTYPE, in0, in1, in2, in3, out0, out1, out2, out3)  \
{                                                                    \
    HADD_UB2(RTYPE, in0, in1, out0, out1);                           \
    HADD_UB2(RTYPE, in2, in3, out2, out3);                           \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_UB4_UB(...) HADD_UB4(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_UB4_UH(...) HADD_UB4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HADD_UB4_SH(...) HADD_UB4(v8i16, __VA_ARGS__)

/* Description : Horizontal subtraction of unsigned byte vector elements
   Arguments   : Inputs  - in0, in1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Each unsigned odd byte element from 'in0' is subtracted from
                 even unsigned byte element from 'in0' (pairwise) and the
                 halfword result is stored in 'out0'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HSUB_UB2(RTYPE, in0, in1, out0, out1)                 \
{                                                             \
    out0 = (RTYPE) __msa_hsub_u_h((v16u8) in0, (v16u8) in0);  \
    out1 = (RTYPE) __msa_hsub_u_h((v16u8) in1, (v16u8) in1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HSUB_UB2_UH(...) HSUB_UB2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HSUB_UB2_SH(...) HSUB_UB2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HSUB_UB4(RTYPE, in0, in1, in2, in3, out0, out1, out2, out3)  \
{                                                                    \
    HSUB_UB2(RTYPE, in0, in1, out0, out1);                           \
    HSUB_UB2(RTYPE, in2, in3, out2, out3);                           \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HSUB_UB4_UH(...) HSUB_UB4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HSUB_UB4_SH(...) HSUB_UB4(v8i16, __VA_ARGS__)

/* Description : SAD (Sum of Absolute Difference)
   Arguments   : Inputs  - in0, in1, ref0, ref1  (unsigned byte src & ref)
                 Outputs - sad_m                 (halfword vector with sad)
                 Return Type - unsigned halfword
   Details     : Absolute difference of all the byte elements from 'in0' with
                 'ref0' is calculated and preserved in 'diff0'. From the 16
                 unsigned absolute diff values, even-odd pairs are added
                 together to generate 8 halfword results.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAD_UB2_UH(in0, in1, ref0, ref1)                        \
( {                                                             \
    v16u8 diff0_m, diff1_m;                                     \
    v8u16 sad_m = { 0 };                                        \
                                                                \
    diff0_m = __msa_asub_u_b((v16u8) in0, (v16u8) ref0);        \
    diff1_m = __msa_asub_u_b((v16u8) in1, (v16u8) ref1);        \
                                                                \
    sad_m += __msa_hadd_u_h((v16u8) diff0_m, (v16u8) diff0_m);  \
    sad_m += __msa_hadd_u_h((v16u8) diff1_m, (v16u8) diff1_m);  \
                                                                \
    sad_m;                                                      \
} )

/* Description : Insert specified word elements from input vectors to 1
                 destination vector
   Arguments   : Inputs  - in0, in1, in2, in3 (4 input vectors)
                 Outputs - out                (output vector)
                 Return Type - as per RTYPE
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_W2(RTYPE, in0, in1, ਬਾਹਰਲਾ)                 \
{                                                       \
    ਬਾਹਰਲਾ = (RTYPE) __msa_insert_w((v4i32) ਬਾਹਰਲਾ, 0, in0);  \
    ਬਾਹਰਲਾ = (RTYPE) __msa_insert_w((v4i32) ਬਾਹਰਲਾ, 1, in1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_W2_UB(...) ਪਾਓ_W2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_W2_SB(...) ਪਾਓ_W2(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_W4(RTYPE, in0, in1, in2, in3, ਬਾਹਰਲਾ)       \
{                                                       \
    ਬਾਹਰਲਾ = (RTYPE) __msa_insert_w((v4i32) ਬਾਹਰਲਾ, 0, in0);  \
    ਬਾਹਰਲਾ = (RTYPE) __msa_insert_w((v4i32) ਬਾਹਰਲਾ, 1, in1);  \
    ਬਾਹਰਲਾ = (RTYPE) __msa_insert_w((v4i32) ਬਾਹਰਲਾ, 2, in2);  \
    ਬਾਹਰਲਾ = (RTYPE) __msa_insert_w((v4i32) ਬਾਹਰਲਾ, 3, in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_W4_UB(...) ਪਾਓ_W4(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_W4_SB(...) ਪਾਓ_W4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_W4_SH(...) ਪਾਓ_W4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_W4_SW(...) ਪਾਓ_W4(v4i32, __VA_ARGS__)

/* Description : Insert specified double word elements from input vectors to 1
                 destination vector
   Arguments   : Inputs  - in0, in1      (2 input vectors)
                 Outputs - out           (output vector)
                 Return Type - as per RTYPE
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_D2(RTYPE, in0, in1, ਬਾਹਰਲਾ)                 \
{                                                       \
    ਬਾਹਰਲਾ = (RTYPE) __msa_insert_d((v2i64) ਬਾਹਰਲਾ, 0, in0);  \
    ਬਾਹਰਲਾ = (RTYPE) __msa_insert_d((v2i64) ਬਾਹਰਲਾ, 1, in1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_D2_UB(...) ਪਾਓ_D2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_D2_SB(...) ਪਾਓ_D2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_D2_SH(...) ਪਾਓ_D2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਪਾਓ_D2_SD(...) ਪਾਓ_D2(v2i64, __VA_ARGS__)

/* Description : Interleave even byte elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Even byte elements of 'in0' and even byte
                 elements of 'in1' are interleaved and copied to 'out0'
                 Even byte elements of 'in2' and even byte
                 elements of 'in3' are interleaved and copied to 'out1'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_B2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                            \
    out0 = (RTYPE) __msa_ilvev_b((v16i8) in1, (v16i8) in0);  \
    out1 = (RTYPE) __msa_ilvev_b((v16i8) in3, (v16i8) in2);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_B2_UB(...) ILVEV_B2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_B2_SB(...) ILVEV_B2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_B2_SH(...) ILVEV_B2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_B2_SD(...) ILVEV_B2(v2i64, __VA_ARGS__)

/* Description : Interleave even halfword elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Even halfword elements of 'in0' and even halfword
                 elements of 'in1' are interleaved and copied to 'out0'
                 Even halfword elements of 'in2' and even halfword
                 elements of 'in3' are interleaved and copied to 'out1'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_H2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                            \
    out0 = (RTYPE) __msa_ilvev_h((v8i16) in1, (v8i16) in0);  \
    out1 = (RTYPE) __msa_ilvev_h((v8i16) in3, (v8i16) in2);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_H2_UB(...) ILVEV_H2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_H2_SH(...) ILVEV_H2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_H2_SW(...) ILVEV_H2(v4i32, __VA_ARGS__)

/* Description : Interleave even word elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Even word elements of 'in0' and even word
                 elements of 'in1' are interleaved and copied to 'out0'
                 Even word elements of 'in2' and even word
                 elements of 'in3' are interleaved and copied to 'out1'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_W2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                            \
    out0 = (RTYPE) __msa_ilvev_w((v4i32) in1, (v4i32) in0);  \
    out1 = (RTYPE) __msa_ilvev_w((v4i32) in3, (v4i32) in2);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_W2_UB(...) ILVEV_W2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_W2_SB(...) ILVEV_W2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_W2_UH(...) ILVEV_W2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_W2_SD(...) ILVEV_W2(v2i64, __VA_ARGS__)

/* Description : Interleave even double word elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Even double word elements of 'in0' and even double word
                 elements of 'in1' are interleaved and copied to 'out0'
                 Even double word elements of 'in2' and even double word
                 elements of 'in3' are interleaved and copied to 'out1'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_D2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                            \
    out0 = (RTYPE) __msa_ilvev_d((v2i64) in1, (v2i64) in0);  \
    out1 = (RTYPE) __msa_ilvev_d((v2i64) in3, (v2i64) in2);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_D2_UB(...) ILVEV_D2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_D2_SB(...) ILVEV_D2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVEV_D2_SW(...) ILVEV_D2(v4i32, __VA_ARGS__)

/* Description : Interleave left half of byte elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Left half of byte elements of in0 and left half of byte
                 elements of in1 are interleaved and copied to out0.
                 Left half of byte elements of in2 and left half of byte
                 elements of in3 are interleaved and copied to out1.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                           \
    out0 = (RTYPE) __msa_ilvl_b((v16i8) in0, (v16i8) in1);  \
    out1 = (RTYPE) __msa_ilvl_b((v16i8) in2, (v16i8) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B2_UB(...) ILVL_B2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B2_SB(...) ILVL_B2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B2_UH(...) ILVL_B2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B2_SH(...) ILVL_B2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                out0, out1, out2, out3)                         \
{                                                               \
    ILVL_B2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    ILVL_B2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B4_UB(...) ILVL_B4(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B4_SB(...) ILVL_B4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B4_UH(...) ILVL_B4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_B4_SH(...) ILVL_B4(v8i16, __VA_ARGS__)

/* Description : Interleave left half of halfword elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Left half of halfword elements of in0 and left half of halfword
                 elements of in1 are interleaved and copied to out0.
                 Left half of halfword elements of in2 and left half of halfword
                 elements of in3 are interleaved and copied to out1.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_H2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                           \
    out0 = (RTYPE) __msa_ilvl_h((v8i16) in0, (v8i16) in1);  \
    out1 = (RTYPE) __msa_ilvl_h((v8i16) in2, (v8i16) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_H2_SH(...) ILVL_H2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_H2_SW(...) ILVL_H2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_H4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                out0, out1, out2, out3)                         \
{                                                               \
    ILVL_H2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    ILVL_H2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_H4_SH(...) ILVL_H4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_H4_SW(...) ILVL_H4(v4i32, __VA_ARGS__)

/* Description : Interleave left half of word elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Left half of word elements of in0 and left half of word
                 elements of in1 are interleaved and copied to out0.
                 Left half of word elements of in2 and left half of word
                 elements of in3 are interleaved and copied to out1.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_W2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                           \
    out0 = (RTYPE) __msa_ilvl_w((v4i32) in0, (v4i32) in1);  \
    out1 = (RTYPE) __msa_ilvl_w((v4i32) in2, (v4i32) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_W2_UB(...) ILVL_W2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_W2_SB(...) ILVL_W2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_W2_SH(...) ILVL_W2(v8i16, __VA_ARGS__)

/* Description : Interleave right half of byte elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7
                 Outputs - out0, out1, out2, out3
                 Return Type - as per RTYPE
   Details     : Right half of byte elements of in0 and right half of byte
                 elements of in1 are interleaved and copied to out0.
                 Right half of byte elements of in2 and right half of byte
                 elements of in3 are interleaved and copied to out1.
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                           \
    out0 = (RTYPE) __msa_ilvr_b((v16i8) in0, (v16i8) in1);  \
    out1 = (RTYPE) __msa_ilvr_b((v16i8) in2, (v16i8) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B2_UB(...) ILVR_B2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B2_SB(...) ILVR_B2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B2_UH(...) ILVR_B2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B2_SH(...) ILVR_B2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B2_SW(...) ILVR_B2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B3(RTYPE, in0, in1, in2, in3, in4, in5, out0, out1, out2)  \
{                                                                       \
    ILVR_B2(RTYPE, in0, in1, in2, in3, out0, out1);                     \
    out2 = (RTYPE) __msa_ilvr_b((v16i8) in4, (v16i8) in5);              \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B3_UB(...) ILVR_B3(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B3_SB(...) ILVR_B3(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B3_UH(...) ILVR_B3(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B3_SH(...) ILVR_B3(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                out0, out1, out2, out3)                         \
{                                                               \
    ILVR_B2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    ILVR_B2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B4_UB(...) ILVR_B4(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B4_SB(...) ILVR_B4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B4_UH(...) ILVR_B4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B4_SH(...) ILVR_B4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B4_SW(...) ILVR_B4(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B8(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,    \
                in8, in9, in10, in11, in12, in13, in14, in15,     \
                out0, out1, out2, out3, out4, out5, out6, out7)   \
{                                                                 \
    ILVR_B4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,        \
            out0, out1, out2, out3);                              \
    ILVR_B4(RTYPE, in8, in9, in10, in11, in12, in13, in14, in15,  \
            out4, out5, out6, out7);                              \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B8_UH(...) ILVR_B8(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_B8_SW(...) ILVR_B8(v4i32, __VA_ARGS__)

/* Description : Interleave right half of halfword elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7
                 Outputs - out0, out1, out2, out3
                 Return Type - as per RTYPE
   Details     : Right half of halfword elements of in0 and right half of
                 halfword elements of in1 are interleaved and copied to out0.
                 Right half of halfword elements of in2 and right half of
                 halfword elements of in3 are interleaved and copied to out1.
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_H2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                           \
    out0 = (RTYPE) __msa_ilvr_h((v8i16) in0, (v8i16) in1);  \
    out1 = (RTYPE) __msa_ilvr_h((v8i16) in2, (v8i16) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_H2_SH(...) ILVR_H2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_H2_SW(...) ILVR_H2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_H3(RTYPE, in0, in1, in2, in3, in4, in5, out0, out1, out2)  \
{                                                                       \
    ILVR_H2(RTYPE, in0, in1, in2, in3, out0, out1);                     \
    out2 = (RTYPE) __msa_ilvr_h((v8i16) in4, (v8i16) in5);              \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_H3_SH(...) ILVR_H3(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_H4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                out0, out1, out2, out3)                         \
{                                                               \
    ILVR_H2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    ILVR_H2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_H4_SH(...) ILVR_H4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_H4_SW(...) ILVR_H4(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_W2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                           \
    out0 = (RTYPE) __msa_ilvr_w((v4i32) in0, (v4i32) in1);  \
    out1 = (RTYPE) __msa_ilvr_w((v4i32) in2, (v4i32) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_W2_UB(...) ILVR_W2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_W2_SB(...) ILVR_W2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_W2_SH(...) ILVR_W2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_W4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                out0, out1, out2, out3)                         \
{                                                               \
    ILVR_W2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    ILVR_W2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_W4_SB(...) ILVR_W4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_W4_UB(...) ILVR_W4(v16u8, __VA_ARGS__)

/* Description : Interleave right half of double word elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7
                 Outputs - out0, out1, out2, out3
                 Return Type - as per RTYPE
   Details     : Right half of double word elements of in0 and right half of
                 double word elements of in1 are interleaved and copied to out0.
                 Right half of double word elements of in2 and right half of
                 double word elements of in3 are interleaved and copied to out1.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_D2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                           \
    out0 = (RTYPE) __msa_ilvr_d((v2i64) in0, (v2i64) in1);  \
    out1 = (RTYPE) __msa_ilvr_d((v2i64) in2, (v2i64) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_D2_UB(...) ILVR_D2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_D2_SB(...) ILVR_D2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_D2_SH(...) ILVR_D2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_D3(RTYPE, in0, in1, in2, in3, in4, in5, out0, out1, out2)  \
{                                                                       \
    ILVR_D2(RTYPE, in0, in1, in2, in3, out0, out1);                     \
    out2 = (RTYPE) __msa_ilvr_d((v2i64) in4, (v2i64) in5);              \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_D3_SB(...) ILVR_D3(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_D4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                out0, out1, out2, out3)                         \
{                                                               \
    ILVR_D2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    ILVR_D2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_D4_SB(...) ILVR_D4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVR_D4_UB(...) ILVR_D4(v16u8, __VA_ARGS__)

/* Description : Interleave left half of double word elements from vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Left half of double word elements of in0 and left half of
                 double word elements of in1 are interleaved and copied to out0.
                 Left half of double word elements of in2 and left half of
                 double word elements of in3 are interleaved and copied to out1.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_D2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                           \
    out0 = (RTYPE) __msa_ilvl_d((v2i64) in0, (v2i64) in1);  \
    out1 = (RTYPE) __msa_ilvl_d((v2i64) in2, (v2i64) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_D2_UB(...) ILVL_D2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_D2_SB(...) ILVL_D2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVL_D2_SH(...) ILVL_D2(v8i16, __VA_ARGS__)

/* Description : Interleave both left and right half of input vectors
   Arguments   : Inputs  - in0, in1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Right half of byte elements from 'in0' and 'in1' are
                 interleaved and stored to 'out0'
                 Left half of byte elements from 'in0' and 'in1' are
                 interleaved and stored to 'out1'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_B2(RTYPE, in0, in1, out0, out1)               \
{                                                           \
    out0 = (RTYPE) __msa_ilvr_b((v16i8) in0, (v16i8) in1);  \
    out1 = (RTYPE) __msa_ilvl_b((v16i8) in0, (v16i8) in1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_B2_UB(...) ILVRL_B2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_B2_SB(...) ILVRL_B2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_B2_UH(...) ILVRL_B2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_B2_SH(...) ILVRL_B2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_B2_SW(...) ILVRL_B2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_H2(RTYPE, in0, in1, out0, out1)               \
{                                                           \
    out0 = (RTYPE) __msa_ilvr_h((v8i16) in0, (v8i16) in1);  \
    out1 = (RTYPE) __msa_ilvl_h((v8i16) in0, (v8i16) in1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_H2_UB(...) ILVRL_H2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_H2_SB(...) ILVRL_H2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_H2_SH(...) ILVRL_H2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_H2_SW(...) ILVRL_H2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_W2(RTYPE, in0, in1, out0, out1)               \
{                                                           \
    out0 = (RTYPE) __msa_ilvr_w((v4i32) in0, (v4i32) in1);  \
    out1 = (RTYPE) __msa_ilvl_w((v4i32) in0, (v4i32) in1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_W2_UB(...) ILVRL_W2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_W2_SH(...) ILVRL_W2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ILVRL_W2_SW(...) ILVRL_W2(v4i32, __VA_ARGS__)

/* Description : Maximum values between signed elements of vector and
                 5-bit signed immediate value are copied to the output vector
   Arguments   : Inputs  - in0, in1, in2, in3, max_val
                 Outputs - in0, in1, in2, in3 (in place)
                 Return Type - as per RTYPE
   Details     : Maximum of signed halfword element values from 'in0' and
                 'max_val' are written to output vector 'in0'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXI_SH2(RTYPE, in0, in1, max_val)               \
{                                                        \
    in0 = (RTYPE) __msa_maxi_s_h((v8i16) in0, max_val);  \
    in1 = (RTYPE) __msa_maxi_s_h((v8i16) in1, max_val);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXI_SH2_UH(...) MAXI_SH2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXI_SH2_SH(...) MAXI_SH2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXI_SH4(RTYPE, in0, in1, in2, in3, max_val)  \
{                                                     \
    MAXI_SH2(RTYPE, in0, in1, max_val);               \
    MAXI_SH2(RTYPE, in2, in3, max_val);               \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXI_SH4_UH(...) MAXI_SH4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXI_SH4_SH(...) MAXI_SH4(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXI_SH8(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7, max_val)  \
{                                                                         \
    MAXI_SH4(RTYPE, in0, in1, in2, in3, max_val);                         \
    MAXI_SH4(RTYPE, in4, in5, in6, in7, max_val);                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXI_SH8_UH(...) MAXI_SH8(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAXI_SH8_SH(...) MAXI_SH8(v8i16, __VA_ARGS__)

/* Description : Saturate the halfword element values to the max
                 unsigned value of (sat_val+1 bits)
                 The element data width remains unchanged
   Arguments   : Inputs  - in0, in1, in2, in3, sat_val
                 Outputs - in0, in1, in2, in3 (in place)
                 Return Type - as per RTYPE
   Details     : Each unsigned halfword element from 'in0' is saturated to the
                 value generated with (sat_val+1) bit range
                 Results are in placed to original vectors
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_UH2(RTYPE, in0, in1, sat_val)               \
{                                                       \
    in0 = (RTYPE) __msa_sat_u_h((v8u16) in0, sat_val);  \
    in1 = (RTYPE) __msa_sat_u_h((v8u16) in1, sat_val);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_UH2_UH(...) SAT_UH2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_UH2_SH(...) SAT_UH2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_UH4(RTYPE, in0, in1, in2, in3, sat_val)  \
{                                                    \
    SAT_UH2(RTYPE, in0, in1, sat_val);               \
    SAT_UH2(RTYPE, in2, in3, sat_val);               \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_UH4_UH(...) SAT_UH4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_UH4_SH(...) SAT_UH4(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_UH8(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7, sat_val)  \
{                                                                        \
    SAT_UH4(RTYPE, in0, in1, in2, in3, sat_val);                         \
    SAT_UH4(RTYPE, in4, in5, in6, in7, sat_val);                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_UH8_UH(...) SAT_UH8(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_UH8_SH(...) SAT_UH8(v8i16, __VA_ARGS__)

/* Description : Saturate the halfword element values to the max
                 unsigned value of (sat_val+1 bits)
                 The element data width remains unchanged
   Arguments   : Inputs  - in0, in1, in2, in3, sat_val
                 Outputs - in0, in1, in2, in3 (in place)
                 Return Type - as per RTYPE
   Details     : Each unsigned halfword element from 'in0' is saturated to the
                 value generated with (sat_val+1) bit range
                 Results are in placed to original vectors
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SH2(RTYPE, in0, in1, sat_val)               \
{                                                       \
    in0 = (RTYPE) __msa_sat_s_h((v8i16) in0, sat_val);  \
    in1 = (RTYPE) __msa_sat_s_h((v8i16) in1, sat_val);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SH2_SH(...) SAT_SH2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SH3(RTYPE, in0, in1, in2, sat_val)          \
{                                                       \
    SAT_SH2(RTYPE, in0, in1, sat_val);                  \
    in2 = (RTYPE) __msa_sat_s_h((v8i16) in2, sat_val);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SH3_SH(...) SAT_SH3(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SH4(RTYPE, in0, in1, in2, in3, sat_val)  \
{                                                    \
    SAT_SH2(RTYPE, in0, in1, sat_val);               \
    SAT_SH2(RTYPE, in2, in3, sat_val);               \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SH4_SH(...) SAT_SH4(v8i16, __VA_ARGS__)

/* Description : Saturate the word element values to the max
                 unsigned value of (sat_val+1 bits)
                 The element data width remains unchanged
   Arguments   : Inputs  - in0, in1, in2, in3, sat_val
                 Outputs - in0, in1, in2, in3 (in place)
                 Return Type - as per RTYPE
   Details     : Each unsigned word element from 'in0' is saturated to the
                 value generated with (sat_val+1) bit range
                 Results are in placed to original vectors
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SW2(RTYPE, in0, in1, sat_val)               \
{                                                       \
    in0 = (RTYPE) __msa_sat_s_w((v4i32) in0, sat_val);  \
    in1 = (RTYPE) __msa_sat_s_w((v4i32) in1, sat_val);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SW2_SW(...) SAT_SW2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SW4(RTYPE, in0, in1, in2, in3, sat_val)  \
{                                                    \
    SAT_SW2(RTYPE, in0, in1, sat_val);               \
    SAT_SW2(RTYPE, in2, in3, sat_val);               \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SAT_SW4_SW(...) SAT_SW4(v4i32, __VA_ARGS__)

/* Description : Indexed halfword element values are replicated to all
                 elements in output vector
   Arguments   : Inputs  - in, idx0, idx1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : 'idx0' element value from 'in' vector is replicated to all
                  elements in 'out0' vector
                  Valid index range for halfword operation is 0-7
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_H2(RTYPE, ਵਿੱਚ_2, idx0, idx1, out0, out1)  \
{                                                     \
    out0 = (RTYPE) __msa_splati_h((v8i16) ਵਿੱਚ_2, idx0);  \
    out1 = (RTYPE) __msa_splati_h((v8i16) ਵਿੱਚ_2, idx1);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_H2_SB(...) SPLATI_H2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_H2_SH(...) SPLATI_H2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_H3(RTYPE, ਵਿੱਚ_2, idx0, idx1, idx2,        \
                  out0, out1, out2)                   \
{                                                     \
    SPLATI_H2(RTYPE, ਵਿੱਚ_2, idx0, idx1, out0, out1);     \
    out2 = (RTYPE) __msa_splati_h((v8i16) ਵਿੱਚ_2, idx2);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_H3_SB(...) SPLATI_H3(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_H3_SH(...) SPLATI_H3(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_H4(RTYPE, ਵਿੱਚ_2, idx0, idx1, idx2, idx3,  \
                  out0, out1, out2, out3)             \
{                                                     \
    SPLATI_H2(RTYPE, ਵਿੱਚ_2, idx0, idx1, out0, out1);     \
    SPLATI_H2(RTYPE, ਵਿੱਚ_2, idx2, idx3, out2, out3);     \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_H4_SB(...) SPLATI_H4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_H4_SH(...) SPLATI_H4(v8i16, __VA_ARGS__)

/* Description : Indexed word element values are replicated to all
                 elements in output vector
   Arguments   : Inputs  - in, stidx
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : 'stidx' element value from 'in' vector is replicated to all
                  elements in 'out0' vector
                 'stidx + 1' element value from 'in' vector is replicated to all
                  elements in 'out1' vector
                  Valid index range for halfword operation is 0-3
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_W2(RTYPE, ਵਿੱਚ_2, stidx, out0, out1)            \
{                                                          \
    out0 = (RTYPE) __msa_splati_w((v4i32) ਵਿੱਚ_2, stidx);      \
    out1 = (RTYPE) __msa_splati_w((v4i32) ਵਿੱਚ_2, (stidx+1));  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_W2_SH(...) SPLATI_W2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_W2_SW(...) SPLATI_W2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_W4(RTYPE, ਵਿੱਚ_2, out0, out1, out2, out3)  \
{                                                     \
    SPLATI_W2(RTYPE, ਵਿੱਚ_2, 0, out0, out1);              \
    SPLATI_W2(RTYPE, ਵਿੱਚ_2, 2, out2, out3);              \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_W4_SH(...) SPLATI_W4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SPLATI_W4_SW(...) SPLATI_W4(v4i32, __VA_ARGS__)

/* Description : Pack even byte elements of vector pairs
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Even byte elements of in0 are copied to the left half of
                 out0 & even byte elements of in1 are copied to the right
                 half of out0.
                 Even byte elements of in2 are copied to the left half of
                 out1 & even byte elements of in3 are copied to the right
                 half of out1.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                            \
    out0 = (RTYPE) __msa_pckev_b((v16i8) in0, (v16i8) in1);  \
    out1 = (RTYPE) __msa_pckev_b((v16i8) in2, (v16i8) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B2_SB(...) PCKEV_B2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B2_UB(...) PCKEV_B2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B2_SH(...) PCKEV_B2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B2_SW(...) PCKEV_B2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B3(RTYPE, in0, in1, in2, in3, in4, in5, out0, out1, out2)  \
{                                                                        \
    PCKEV_B2(RTYPE, in0, in1, in2, in3, out0, out1);                     \
    out2 = (RTYPE) __msa_pckev_b((v16i8) in4, (v16i8) in5);              \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B3_UB(...) PCKEV_B3(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B3_SB(...) PCKEV_B3(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                 out0, out1, out2, out3)                         \
{                                                                \
    PCKEV_B2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    PCKEV_B2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B4_SB(...) PCKEV_B4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B4_UB(...) PCKEV_B4(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B4_SH(...) PCKEV_B4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_B4_SW(...) PCKEV_B4(v4i32, __VA_ARGS__)

/* Description : Pack even halfword elements of vector pairs
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Even halfword elements of in0 are copied to the left half of
                 out0 & even halfword elements of in1 are copied to the right
                 half of out0.
                 Even halfword elements of in2 are copied to the left half of
                 out1 & even halfword elements of in3 are copied to the right
                 half of out1.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_H2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                            \
    out0 = (RTYPE) __msa_pckev_h((v8i16) in0, (v8i16) in1);  \
    out1 = (RTYPE) __msa_pckev_h((v8i16) in2, (v8i16) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_H2_SB(...) PCKEV_H2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_H2_SH(...) PCKEV_H2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_H2_SW(...) PCKEV_H2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_H4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                 out0, out1, out2, out3)                         \
{                                                                \
    PCKEV_H2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    PCKEV_H2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_H4_SB(...) PCKEV_H4(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_H4_SH(...) PCKEV_H4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_H4_SW(...) PCKEV_H4(v4i32, __VA_ARGS__)

/* Description : Pack even double word elements of vector pairs
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Even double elements of in0 are copied to the left half of
                 out0 & even double elements of in1 are copied to the right
                 half of out0.
                 Even double elements of in2 are copied to the left half of
                 out1 & even double elements of in3 are copied to the right
                 half of out1.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_D2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                            \
    out0 = (RTYPE) __msa_pckev_d((v2i64) in0, (v2i64) in1);  \
    out1 = (RTYPE) __msa_pckev_d((v2i64) in2, (v2i64) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_D2_UB(...) PCKEV_D2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_D2_SB(...) PCKEV_D2(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_D2_SH(...) PCKEV_D2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_D4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                 out0, out1, out2, out3)                         \
{                                                                \
    PCKEV_D2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    PCKEV_D2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_D4_UB(...) PCKEV_D4(v16u8, __VA_ARGS__)

/* Description : Pack odd double word elements of vector pairs
   Arguments   : Inputs  - in0, in1
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : As operation is on same input 'in0' vector, index 1 double word
                 element is overwritten to index 0 and result is written to out0
                 As operation is on same input 'in1' vector, index 1 double word
                 element is overwritten to index 0 and result is written to out1
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKOD_D2(RTYPE, in0, in1, in2, in3, out0, out1)      \
{                                                            \
    out0 = (RTYPE) __msa_pckod_d((v2i64) in0, (v2i64) in1);  \
    out1 = (RTYPE) __msa_pckod_d((v2i64) in2, (v2i64) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKOD_D2_UB(...) PCKOD_D2(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKOD_D2_SH(...) PCKOD_D2(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKOD_D2_SD(...) PCKOD_D2(v2i64, __VA_ARGS__)

/* Description : Each byte element is logically xor'ed with immediate 128
   Arguments   : Inputs  - in0, in1
                 Outputs - in0, in1 (in-place)
                 Return Type - as per RTYPE
   Details     : Each unsigned byte element from input vector 'in0' is
                 logically xor'ed with 128 and result is in-place stored in
                 'in0' vector
                 Each unsigned byte element from input vector 'in1' is
                 logically xor'ed with 128 and result is in-place stored in
                 'in1' vector
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B2_128(RTYPE, in0, in1)               \
{                                                  \
    in0 = (RTYPE) __msa_xori_b((v16u8) in0, 128);  \
    in1 = (RTYPE) __msa_xori_b((v16u8) in1, 128);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B2_128_UB(...) XORI_B2_128(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B2_128_SB(...) XORI_B2_128(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B2_128_SH(...) XORI_B2_128(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B3_128(RTYPE, in0, in1, in2)          \
{                                                  \
    XORI_B2_128(RTYPE, in0, in1);                  \
    in2 = (RTYPE) __msa_xori_b((v16u8) in2, 128);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B3_128_SB(...) XORI_B3_128(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B4_128(RTYPE, in0, in1, in2, in3)  \
{                                               \
    XORI_B2_128(RTYPE, in0, in1);               \
    XORI_B2_128(RTYPE, in2, in3);               \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B4_128_UB(...) XORI_B4_128(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B4_128_SB(...) XORI_B4_128(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B4_128_SH(...) XORI_B4_128(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B5_128(RTYPE, in0, in1, in2, in3, in4)  \
{                                                    \
    XORI_B3_128(RTYPE, in0, in1, in2);               \
    XORI_B2_128(RTYPE, in3, in4);                    \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B5_128_SB(...) XORI_B5_128(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B6_128(RTYPE, in0, in1, in2, in3, in4, in5)  \
{                                                         \
    XORI_B4_128(RTYPE, in0, in1, in2, in3);               \
    XORI_B2_128(RTYPE, in4, in5);                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B6_128_SB(...) XORI_B6_128(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B7_128(RTYPE, in0, in1, in2, in3, in4, in5, in6)  \
{                                                              \
    XORI_B4_128(RTYPE, in0, in1, in2, in3);                    \
    XORI_B3_128(RTYPE, in4, in5, in6);                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B7_128_SB(...) XORI_B7_128(v16i8, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B8_128(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7)  \
{                                                                   \
    XORI_B4_128(RTYPE, in0, in1, in2, in3);                         \
    XORI_B4_128(RTYPE, in4, in5, in6, in7);                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B8_128_SB(...) XORI_B8_128(v16i8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XORI_B8_128_UB(...) XORI_B8_128(v16u8, __VA_ARGS__)

/* Description : Addition of signed halfword elements and signed saturation
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
                 Return Type - as per RTYPE
   Details     : Signed halfword elements from 'in0' are added to signed
                 halfword elements of 'in1'. The result is then signed saturated
                 between -32768 to +32767 (as per halfword data type)
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ADDS_SH2(RTYPE, in0, in1, in2, in3, out0, out1)       \
{                                                             \
    out0 = (RTYPE) __msa_adds_s_h((v8i16) in0, (v8i16) in1);  \
    out1 = (RTYPE) __msa_adds_s_h((v8i16) in2, (v8i16) in3);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ADDS_SH2_SH(...) ADDS_SH2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ADDS_SH4(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                 out0, out1, out2, out3)                         \
{                                                                \
    ADDS_SH2(RTYPE, in0, in1, in2, in3, out0, out1);             \
    ADDS_SH2(RTYPE, in4, in5, in6, in7, out2, out3);             \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ADDS_SH4_UH(...) ADDS_SH4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ADDS_SH4_SH(...) ADDS_SH4(v8i16, __VA_ARGS__)

/* Description : Shift left all elements of vector (generic for all data types)
   Arguments   : Inputs  - in0, in1, in2, in3, shift
                 Outputs - in0, in1, in2, in3 (in place)
                 Return Type - as per input vector RTYPE
   Details     : Each element of vector 'in0' is left shifted by 'shift' and
                 result is in place written to 'in0'
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLLI_2V(in0, in1, ਖਿਸਕਾਓ)  \
{                                 \
    in0 = in0 << ਖਿਸਕਾਓ;           \
    in1 = in1 << ਖਿਸਕਾਓ;           \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SLLI_4V(in0, in1, in2, in3, ਖਿਸਕਾਓ)  \
{                                           \
    in0 = in0 << ਖਿਸਕਾਓ;                     \
    in1 = in1 << ਖਿਸਕਾਓ;                     \
    in2 = in2 << ਖਿਸਕਾਓ;                     \
    in3 = in3 << ਖਿਸਕਾਓ;                     \
}

/* Description : Arithmetic shift right all elements of vector
                 (generic for all data types)
   Arguments   : Inputs  - in0, in1, in2, in3, shift
                 Outputs - in0, in1, in2, in3 (in place)
                 Return Type - as per input vector RTYPE
   Details     : Each element of vector 'in0' is right shifted by 'shift' and
                 result is in place written to 'in0'
                 Here, 'shift' is GP variable passed in
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRA_4V(in0, in1, in2, in3, ਖਿਸਕਾਓ)  \
{                                          \
    in0 = in0 >> ਖਿਸਕਾਓ;                    \
    in1 = in1 >> ਖਿਸਕਾਓ;                    \
    in2 = in2 >> ਖਿਸਕਾਓ;                    \
    in3 = in3 >> ਖਿਸਕਾਓ;                    \
}

/* Description : Shift right logical all halfword elements of vector
   Arguments   : Inputs  - in0, in1, in2, in3, shift
                 Outputs - in0, in1, in2, in3 (in place)
                 Return Type - as per RTYPE
   Details     : Each element of vector 'in0' is shifted right logical by
                 number of bits respective element holds in vector 'shift' and
                 result is in place written to 'in0'
                 Here, 'shift' is a vector passed in
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRL_H4(RTYPE, in0, in1, in2, in3, ਖਿਸਕਾਓ)            \
{                                                           \
    in0 = (RTYPE) __msa_srl_h((v8i16) in0, (v8i16) ਖਿਸਕਾਓ);  \
    in1 = (RTYPE) __msa_srl_h((v8i16) in1, (v8i16) ਖਿਸਕਾਓ);  \
    in2 = (RTYPE) __msa_srl_h((v8i16) in2, (v8i16) ਖਿਸਕਾਓ);  \
    in3 = (RTYPE) __msa_srl_h((v8i16) in3, (v8i16) ਖਿਸਕਾਓ);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRL_H4_UH(...) SRL_H4(v8u16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRLR_H4(RTYPE, in0, in1, in2, in3, ਖਿਸਕਾਓ)            \
{                                                            \
    in0 = (RTYPE) __msa_srlr_h((v8i16) in0, (v8i16) ਖਿਸਕਾਓ);  \
    in1 = (RTYPE) __msa_srlr_h((v8i16) in1, (v8i16) ਖਿਸਕਾਓ);  \
    in2 = (RTYPE) __msa_srlr_h((v8i16) in2, (v8i16) ਖਿਸਕਾਓ);  \
    in3 = (RTYPE) __msa_srlr_h((v8i16) in3, (v8i16) ਖਿਸਕਾਓ);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRLR_H4_UH(...) SRLR_H4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRLR_H4_SH(...) SRLR_H4(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRLR_H8(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7, ਖਿਸਕਾਓ)  \
{                                                                      \
    SRLR_H4(RTYPE, in0, in1, in2, in3, ਖਿਸਕਾਓ);                         \
    SRLR_H4(RTYPE, in4, in5, in6, in7, ਖਿਸਕਾਓ);                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRLR_H8_UH(...) SRLR_H8(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRLR_H8_SH(...) SRLR_H8(v8i16, __VA_ARGS__)

/* Description : Shift right arithmetic rounded halfwords
   Arguments   : Inputs  - in0, in1, shift
                 Outputs - in0, in1, (in place)
                 Return Type - as per RTYPE
   Details     : Each element of vector 'in0' is shifted right arithmetic by
                 number of bits respective element holds in vector 'shift'.
                 The last discarded bit is added to shifted value for rounding
                 and the result is in place written to 'in0'
                 Here, 'shift' is a vector passed in
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_H2(RTYPE, in0, in1, ਖਿਸਕਾਓ)                      \
{                                                            \
    in0 = (RTYPE) __msa_srar_h((v8i16) in0, (v8i16) ਖਿਸਕਾਓ);  \
    in1 = (RTYPE) __msa_srar_h((v8i16) in1, (v8i16) ਖਿਸਕਾਓ);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_H2_UH(...) SRAR_H2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_H2_SH(...) SRAR_H2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_H3(RTYPE, in0, in1, in2, ਖਿਸਕਾਓ)                 \
{                                                            \
    SRAR_H2(RTYPE, in0, in1, ਖਿਸਕਾਓ)                          \
    in2 = (RTYPE) __msa_srar_h((v8i16) in2, (v8i16) ਖਿਸਕਾਓ);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_H3_SH(...) SRAR_H3(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_H4(RTYPE, in0, in1, in2, in3, ਖਿਸਕਾਓ)  \
{                                                  \
    SRAR_H2(RTYPE, in0, in1, ਖਿਸਕਾਓ)                \
    SRAR_H2(RTYPE, in2, in3, ਖਿਸਕਾਓ)                \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_H4_UH(...) SRAR_H4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_H4_SH(...) SRAR_H4(v8i16, __VA_ARGS__)

/* Description : Shift right arithmetic rounded words
   Arguments   : Inputs  - in0, in1, shift
                 Outputs - in0, in1, (in place)
                 Return Type - as per RTYPE
   Details     : Each element of vector 'in0' is shifted right arithmetic by
                 number of bits respective element holds in vector 'shift'.
                 The last discarded bit is added to shifted value for rounding
                 and the result is in place written to 'in0'
                 Here, 'shift' is a vector passed in
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_W2(RTYPE, in0, in1, ਖਿਸਕਾਓ)                      \
{                                                            \
    in0 = (RTYPE) __msa_srar_w((v4i32) in0, (v4i32) ਖਿਸਕਾਓ);  \
    in1 = (RTYPE) __msa_srar_w((v4i32) in1, (v4i32) ਖਿਸਕਾਓ);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_W2_SW(...) SRAR_W2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_W4(RTYPE, in0, in1, in2, in3, ਖਿਸਕਾਓ)  \
{                                                  \
    SRAR_W2(RTYPE, in0, in1, ਖਿਸਕਾਓ)                \
    SRAR_W2(RTYPE, in2, in3, ਖਿਸਕਾਓ)                \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRAR_W4_SW(...) SRAR_W4(v4i32, __VA_ARGS__)

/* Description : Shift right arithmetic rounded (immediate)
   Arguments   : Inputs  - in0, in1, in2, in3, shift
                 Outputs - in0, in1, in2, in3 (in place)
                 Return Type - as per RTYPE
   Details     : Each element of vector 'in0' is shifted right arithmetic by
                 value in 'shift'.
                 The last discarded bit is added to shifted value for rounding
                 and the result is in place written to 'in0'
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_H2(RTYPE, in0, in1, ਖਿਸਕਾਓ)              \
{                                                     \
    in0 = (RTYPE) __msa_srari_h((v8i16) in0, ਖਿਸਕਾਓ);  \
    in1 = (RTYPE) __msa_srari_h((v8i16) in1, ਖਿਸਕਾਓ);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_H2_UH(...) SRARI_H2(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_H2_SH(...) SRARI_H2(v8i16, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_H4(RTYPE, in0, in1, in2, in3, ਖਿਸਕਾਓ)    \
{                                                     \
    SRARI_H2(RTYPE, in0, in1, ਖਿਸਕਾਓ);                 \
    SRARI_H2(RTYPE, in2, in3, ਖਿਸਕਾਓ);                 \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_H4_UH(...) SRARI_H4(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_H4_SH(...) SRARI_H4(v8i16, __VA_ARGS__)

/* Description : Shift right arithmetic rounded (immediate)
   Arguments   : Inputs  - in0, in1, shift
                 Outputs - in0, in1     (in place)
                 Return Type - as per RTYPE
   Details     : Each element of vector 'in0' is shifted right arithmetic by
                 value in 'shift'.
                 The last discarded bit is added to shifted value for rounding
                 and the result is in place written to 'in0'
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_W2(RTYPE, in0, in1, ਖਿਸਕਾਓ)              \
{                                                     \
    in0 = (RTYPE) __msa_srari_w((v4i32) in0, ਖਿਸਕਾਓ);  \
    in1 = (RTYPE) __msa_srari_w((v4i32) in1, ਖਿਸਕਾਓ);  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_W2_SW(...) SRARI_W2(v4i32, __VA_ARGS__)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_W4(RTYPE, in0, in1, in2, in3, ਖਿਸਕਾਓ)  \
{                                                   \
    SRARI_W2(RTYPE, in0, in1, ਖਿਸਕਾਓ);               \
    SRARI_W2(RTYPE, in2, in3, ਖਿਸਕਾਓ);               \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_W4_SH(...) SRARI_W4(v8i16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SRARI_W4_SW(...) SRARI_W4(v4i32, __VA_ARGS__)

/* Description : Multiplication of pairs of vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
   Details     : Each element from 'in0' is multiplied with elements from 'in1'
                 and result is written to 'out0'
                 Similar for other pairs
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MUL2(in0, in1, in2, in3, out0, out1)  \
{                                             \
    out0 = in0 * in1;                         \
    out1 = in2 * in3;                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MUL4(in0, in1, in2, in3, in4, in5, in6, in7, out0, out1, out2, out3)  \
{                                                                             \
    MUL2(in0, in1, in2, in3, out0, out1);                                     \
    MUL2(in4, in5, in6, in7, out2, out3);                                     \
}

/* Description : Addition of 2 pairs of vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
   Details     : Each element from 2 pairs vectors is added and 2 results are
                 produced
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ADD2(in0, in1, in2, in3, out0, out1)  \
{                                             \
    out0 = in0 + in1;                         \
    out1 = in2 + in3;                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ADD4(in0, in1, in2, in3, in4, in5, in6, in7, out0, out1, out2, out3)  \
{                                                                             \
    ADD2(in0, in1, in2, in3, out0, out1);                                     \
    ADD2(in4, in5, in6, in7, out2, out3);                                     \
}

/* Description : Subtraction of 2 pairs of vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1
   Details     : Each element from 2 pairs vectors is subtracted and 2 results
                 are produced
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUB2(in0, in1, in2, in3, out0, out1)  \
{                                             \
    out0 = in0 - in1;                         \
    out1 = in2 - in3;                         \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SUB4(in0, in1, in2, in3, in4, in5, in6, in7, out0, out1, out2, out3)  \
{                                                                             \
    out0 = in0 - in1;                                                         \
    out1 = in2 - in3;                                                         \
    out2 = in4 - in5;                                                         \
    out3 = in6 - in7;                                                         \
}

/* Description : Sign extend byte elements from right half of the vector
   Arguments   : Input  - in    (byte vector)
                 Output - out   (sign extended halfword vector)
                 Return Type - signed halfword
   Details     : Sign bit of byte elements from input vector 'in' is
                 extracted and interleaved with same vector 'in' to generate
                 8 halfword elements keeping sign intact
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UNPCK_R_SB_SH(ਵਿੱਚ_2, ਬਾਹਰਲਾ)                       \
{                                                    \
    v16i8 sign_m;                                    \
                                                     \
    sign_m = __msa_clti_s_b((v16i8) ਵਿੱਚ_2, 0);          \
    ਬਾਹਰਲਾ = (v8i16) __msa_ilvr_b(sign_m, (v16i8) ਵਿੱਚ_2);  \
}

/* Description : Sign extend halfword elements from right half of the vector
   Arguments   : Inputs  - in    (input halfword vector)
                 Outputs - out   (sign extended word vectors)
                 Return Type - signed word
   Details     : Sign bit of halfword elements from input vector 'in' is
                 extracted and interleaved with same vector 'in0' to generate
                 4 word elements keeping sign intact
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UNPCK_R_SH_SW(ਵਿੱਚ_2, ਬਾਹਰਲਾ)                       \
{                                                    \
    v8i16 sign_m;                                    \
                                                     \
    sign_m = __msa_clti_s_h((v8i16) ਵਿੱਚ_2, 0);          \
    ਬਾਹਰਲਾ = (v4i32) __msa_ilvr_h(sign_m, (v8i16) ਵਿੱਚ_2);  \
}

/* Description : Sign extend byte elements from input vector and return
                 halfword results in pair of vectors
   Arguments   : Inputs  - in           (1 input byte vector)
                 Outputs - out0, out1   (sign extended 2 halfword vectors)
                 Return Type - signed halfword
   Details     : Sign bit of byte elements from input vector 'in' is
                 extracted and interleaved right with same vector 'in0' to
                 generate 8 signed halfword elements in 'out0'
                 Then interleaved left with same vector 'in0' to
                 generate 8 signed halfword elements in 'out1'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UNPCK_SB_SH(ਵਿੱਚ_2, out0, out1)                  \
{                                                    \
    v16i8 tmp_m;                                     \
                                                     \
    tmp_m = __msa_clti_s_b((v16i8) ਵਿੱਚ_2, 0);           \
    ILVRL_B2_SH(tmp_m, ਵਿੱਚ_2, out0, out1);              \
}

/* Description : Zero extend unsigned byte elements to halfword elements
   Arguments   : Inputs  - in           (1 input unsigned byte vector)
                 Outputs - out0, out1   (unsigned 2 halfword vectors)
                 Return Type - signed halfword
   Details     : Zero extended right half of vector is returned in 'out0'
                 Zero extended left half of vector is returned in 'out1'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UNPCK_UB_SH(ਵਿੱਚ_2, out0, out1)                   \
{                                                     \
    v16i8 zero_m = { 0 };                             \
                                                      \
    ILVRL_B2_SH(zero_m, ਵਿੱਚ_2, out0, out1);              \
}

/* Description : Sign extend halfword elements from input vector and return
                 result in pair of vectors
   Arguments   : Inputs  - in           (1 input halfword vector)
                 Outputs - out0, out1   (sign extended 2 word vectors)
                 Return Type - signed word
   Details     : Sign bit of halfword elements from input vector 'in' is
                 extracted and interleaved right with same vector 'in0' to
                 generate 4 signed word elements in 'out0'
                 Then interleaved left with same vector 'in0' to
                 generate 4 signed word elements in 'out1'
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ UNPCK_SH_SW(ਵਿੱਚ_2, out0, out1)                  \
{                                                    \
    v8i16 tmp_m;                                     \
                                                     \
    tmp_m = __msa_clti_s_h((v8i16) ਵਿੱਚ_2, 0);           \
    ILVRL_H2_SW(tmp_m, ਵਿੱਚ_2, out0, out1);              \
}

/* Description : Swap two variables
   Arguments   : Inputs  - in0, in1
                 Outputs - in0, in1 (in-place)
   Details     : Swapping of two input variables using xor
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਅਦਲਾ_ਬਦਲੀ(in0, in1)  \
{                       \
    in0 = in0 ^ in1;    \
    in1 = in0 ^ in1;    \
    in0 = in0 ^ in1;    \
}

/* Description : Butterfly of 4 input vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1, out2, out3
   Details     : Butterfly operation
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTERFLY_4(in0, in1, in2, in3, out0, out1, out2, out3)  \
{                                                                \
    out0 = in0 + in3;                                            \
    out1 = in1 + in2;                                            \
                                                                 \
    out2 = in1 - in2;                                            \
    out3 = in0 - in3;                                            \
}

/* Description : Butterfly of 8 input vectors
   Arguments   : Inputs  - in0 ...  in7
                 Outputs - out0 .. out7
   Details     : Butterfly operation
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTERFLY_8(in0, in1, in2, in3, in4, in5, in6, in7,          \
                    out0, out1, out2, out3, out4, out5, out6, out7)  \
{                                                                    \
    out0 = in0 + in7;                                                \
    out1 = in1 + in6;                                                \
    out2 = in2 + in5;                                                \
    out3 = in3 + in4;                                                \
                                                                     \
    out4 = in3 - in4;                                                \
    out5 = in2 - in5;                                                \
    out6 = in1 - in6;                                                \
    out7 = in0 - in7;                                                \
}

/* Description : Butterfly of 16 input vectors
   Arguments   : Inputs  - in0 ...  in15
                 Outputs - out0 .. out15
   Details     : Butterfly operation
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTERFLY_16(in0, in1, in2, in3, in4, in5, in6, in7,                \
                     in8, in9,  in10, in11, in12, in13, in14, in15,         \
                     out0, out1, out2, out3, out4, out5, out6, out7,        \
                     out8, out9, out10, out11, out12, out13, out14, out15)  \
{                                                                           \
    out0 = in0 + in15;                                                      \
    out1 = in1 + in14;                                                      \
    out2 = in2 + in13;                                                      \
    out3 = in3 + in12;                                                      \
    out4 = in4 + in11;                                                      \
    out5 = in5 + in10;                                                      \
    out6 = in6 + in9;                                                       \
    out7 = in7 + in8;                                                       \
                                                                            \
    out8 = in7 - in8;                                                       \
    out9 = in6 - in9;                                                       \
    out10 = in5 - in10;                                                     \
    out11 = in4 - in11;                                                     \
    out12 = in3 - in12;                                                     \
    out13 = in2 - in13;                                                     \
    out14 = in1 - in14;                                                     \
    out15 = in0 - in15;                                                     \
}

/* Description : Transposes input 4x4 byte block
   Arguments   : Inputs  - in0, in1, in2, in3      (input 4x4 byte block)
                 Outputs - out0, out1, out2, out3  (output 4x4 byte block)
                 Return Type - unsigned byte
   Details     :
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE4x4_UB_UB(in0, in1, in2, in3, out0, out1, out2, out3)  \
{                                                                       \
    v16i8 zero_m = { 0 };                                               \
    v16i8 s0_m, s1_m, s2_m, s3_m;                                       \
                                                                        \
    ILVR_D2_SB(in1, in0, in3, in2, s0_m, s1_m);                         \
    ILVRL_B2_SB(s1_m, s0_m, s2_m, s3_m);                                \
                                                                        \
    out0 = (v16u8) __msa_ilvr_b(s3_m, s2_m);                            \
    out1 = (v16u8) __msa_sldi_b(zero_m, (v16i8) out0, 4);               \
    out2 = (v16u8) __msa_sldi_b(zero_m, (v16i8) out1, 4);               \
    out3 = (v16u8) __msa_sldi_b(zero_m, (v16i8) out2, 4);               \
}

/* Description : Transposes input 8x4 byte block into 4x8
   Arguments   : Inputs  - in0, in1, in2, in3      (input 8x4 byte block)
                 Outputs - out0, out1, out2, out3  (output 4x8 byte block)
                 Return Type - as per RTYPE
   Details     :
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8x4_UB(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,  \
                        out0, out1, out2, out3)                         \
{                                                                       \
    v16i8 tmp0_m, tmp1_m, tmp2_m, tmp3_m;                               \
                                                                        \
    ILVEV_W2_SB(in0, in4, in1, in5, tmp0_m, tmp1_m);                    \
    tmp2_m = __msa_ilvr_b(tmp1_m, tmp0_m);                              \
    ILVEV_W2_SB(in2, in6, in3, in7, tmp0_m, tmp1_m);                    \
                                                                        \
    tmp3_m = __msa_ilvr_b(tmp1_m, tmp0_m);                              \
    ILVRL_H2_SB(tmp3_m, tmp2_m, tmp0_m, tmp1_m);                        \
                                                                        \
    ILVRL_W2(RTYPE, tmp1_m, tmp0_m, out0, out2);                        \
    out1 = (RTYPE) __msa_ilvl_d((v2i64) out2, (v2i64) out0);            \
    out3 = (RTYPE) __msa_ilvl_d((v2i64) out0, (v2i64) out2);            \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8x4_UB_UB(...) TRANSPOSE8x4_UB(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8x4_UB_UH(...) TRANSPOSE8x4_UB(v8u16, __VA_ARGS__)

/* Description : Transposes input 8x8 byte block
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7
                           (input 8x8 byte block)
                 Outputs - out0, out1, out2, out3, out4, out5, out6, out7
                           (output 8x8 byte block)
                 Return Type - as per RTYPE
   Details     :
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8x8_UB(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,   \
                        out0, out1, out2, out3, out4, out5, out6, out7)  \
{                                                                        \
    v16i8 tmp0_m, tmp1_m, tmp2_m, tmp3_m;                                \
    v16i8 tmp4_m, tmp5_m, tmp6_m, tmp7_m;                                \
    v16i8 zeros = { 0 };                                                 \
                                                                         \
    ILVR_B4_SB(in2, in0, in3, in1, in6, in4, in7, in5,                   \
               tmp0_m, tmp1_m, tmp2_m, tmp3_m);                          \
    ILVRL_B2_SB(tmp1_m, tmp0_m, tmp4_m, tmp5_m);                         \
    ILVRL_B2_SB(tmp3_m, tmp2_m, tmp6_m, tmp7_m);                         \
    ILVRL_W2(RTYPE, tmp6_m, tmp4_m, out0, out2);                         \
    ILVRL_W2(RTYPE, tmp7_m, tmp5_m, out4, out6);                         \
    SLDI_B4(RTYPE, zeros, out0, zeros, out2, zeros, out4, zeros, out6,   \
            8, out1, out3, out5, out7);                                  \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8x8_UB_UB(...) TRANSPOSE8x8_UB(v16u8, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8x8_UB_UH(...) TRANSPOSE8x8_UB(v8u16, __VA_ARGS__)

/* Description : Transposes 16x4 block into 4x16 with byte elements in vectors
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7,
                           in8, in9, in10, in11, in12, in13, in14, in15
                 Outputs - out0, out1, out2, out3
                 Return Type - unsigned byte
   Details     :
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE16x4_UB_UB(in0, in1, in2, in3, in4, in5, in6, in7,        \
                            in8, in9, in10, in11, in12, in13, in14, in15,  \
                            out0, out1, out2, out3)                        \
{                                                                          \
    v2i64 tmp0_m, tmp1_m, tmp2_m, tmp3_m;                                  \
                                                                           \
    ILVEV_W2_SD(in0, in4, in8, in12, tmp0_m, tmp1_m);                      \
    out1 = (v16u8) __msa_ilvev_d(tmp1_m, tmp0_m);                          \
                                                                           \
    ILVEV_W2_SD(in1, in5, in9, in13, tmp0_m, tmp1_m);                      \
    out3 = (v16u8) __msa_ilvev_d(tmp1_m, tmp0_m);                          \
                                                                           \
    ILVEV_W2_SD(in2, in6, in10, in14, tmp0_m, tmp1_m);                     \
                                                                           \
    tmp2_m = __msa_ilvev_d(tmp1_m, tmp0_m);                                \
    ILVEV_W2_SD(in3, in7, in11, in15, tmp0_m, tmp1_m);                     \
                                                                           \
    tmp3_m = __msa_ilvev_d(tmp1_m, tmp0_m);                                \
    ILVEV_B2_SD(out1, out3, tmp2_m, tmp3_m, tmp0_m, tmp1_m);               \
    out0 = (v16u8) __msa_ilvev_h((v8i16) tmp1_m, (v8i16) tmp0_m);          \
    out2 = (v16u8) __msa_ilvod_h((v8i16) tmp1_m, (v8i16) tmp0_m);          \
                                                                           \
    tmp0_m = (v2i64) __msa_ilvod_b((v16i8) out3, (v16i8) out1);            \
    tmp1_m = (v2i64) __msa_ilvod_b((v16i8) tmp3_m, (v16i8) tmp2_m);        \
    out1 = (v16u8) __msa_ilvev_h((v8i16) tmp1_m, (v8i16) tmp0_m);          \
    out3 = (v16u8) __msa_ilvod_h((v8i16) tmp1_m, (v8i16) tmp0_m);          \
}

/* Description : Transposes 16x8 block into 8x16 with byte elements in vectors
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7,
                           in8, in9, in10, in11, in12, in13, in14, in15
                 Outputs - out0, out1, out2, out3, out4, out5, out6, out7
                 Return Type - unsigned byte
   Details     :
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE16x8_UB_UB(in0, in1, in2, in3, in4, in5, in6, in7,          \
                            in8, in9, in10, in11, in12, in13, in14, in15,    \
                            out0, out1, out2, out3, out4, out5, out6, out7)  \
{                                                                            \
    v16u8 tmp0_m, tmp1_m, tmp2_m, tmp3_m;                                    \
    v16u8 tmp4_m, tmp5_m, tmp6_m, tmp7_m;                                    \
                                                                             \
    ILVEV_D2_UB(in0, in8, in1, in9, out7, out6);                             \
    ILVEV_D2_UB(in2, in10, in3, in11, out5, out4);                           \
    ILVEV_D2_UB(in4, in12, in5, in13, out3, out2);                           \
    ILVEV_D2_UB(in6, in14, in7, in15, out1, out0);                           \
                                                                             \
    tmp0_m = (v16u8) __msa_ilvev_b((v16i8) out6, (v16i8) out7);              \
    tmp4_m = (v16u8) __msa_ilvod_b((v16i8) out6, (v16i8) out7);              \
    tmp1_m = (v16u8) __msa_ilvev_b((v16i8) out4, (v16i8) out5);              \
    tmp5_m = (v16u8) __msa_ilvod_b((v16i8) out4, (v16i8) out5);              \
    out5 = (v16u8) __msa_ilvev_b((v16i8) out2, (v16i8) out3);                \
    tmp6_m = (v16u8) __msa_ilvod_b((v16i8) out2, (v16i8) out3);              \
    out7 = (v16u8) __msa_ilvev_b((v16i8) out0, (v16i8) out1);                \
    tmp7_m = (v16u8) __msa_ilvod_b((v16i8) out0, (v16i8) out1);              \
                                                                             \
    ILVEV_H2_UB(tmp0_m, tmp1_m, out5, out7, tmp2_m, tmp3_m);                 \
    out0 = (v16u8) __msa_ilvev_w((v4i32) tmp3_m, (v4i32) tmp2_m);            \
    out4 = (v16u8) __msa_ilvod_w((v4i32) tmp3_m, (v4i32) tmp2_m);            \
                                                                             \
    tmp2_m = (v16u8) __msa_ilvod_h((v8i16) tmp1_m, (v8i16) tmp0_m);          \
    tmp3_m = (v16u8) __msa_ilvod_h((v8i16) out7, (v8i16) out5);              \
    out2 = (v16u8) __msa_ilvev_w((v4i32) tmp3_m, (v4i32) tmp2_m);            \
    out6 = (v16u8) __msa_ilvod_w((v4i32) tmp3_m, (v4i32) tmp2_m);            \
                                                                             \
    ILVEV_H2_UB(tmp4_m, tmp5_m, tmp6_m, tmp7_m, tmp2_m, tmp3_m);             \
    out1 = (v16u8) __msa_ilvev_w((v4i32) tmp3_m, (v4i32) tmp2_m);            \
    out5 = (v16u8) __msa_ilvod_w((v4i32) tmp3_m, (v4i32) tmp2_m);            \
                                                                             \
    tmp2_m = (v16u8) __msa_ilvod_h((v8i16) tmp5_m, (v8i16) tmp4_m);          \
    tmp3_m = (v16u8) __msa_ilvod_h((v8i16) tmp7_m, (v8i16) tmp6_m);          \
    out3 = (v16u8) __msa_ilvev_w((v4i32) tmp3_m, (v4i32) tmp2_m);            \
    out7 = (v16u8) __msa_ilvod_w((v4i32) tmp3_m, (v4i32) tmp2_m);            \
}

/* Description : Transposes 4x4 block with half word elements in vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1, out2, out3
                 Return Type - signed halfword
   Details     :
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE4x4_SH_SH(in0, in1, in2, in3, out0, out1, out2, out3)  \
{                                                                       \
    v8i16 s0_m, s1_m;                                                   \
                                                                        \
    ILVR_H2_SH(in1, in0, in3, in2, s0_m, s1_m);                         \
    ILVRL_W2_SH(s1_m, s0_m, out0, out2);                                \
    out1 = (v8i16) __msa_ilvl_d((v2i64) out0, (v2i64) out0);            \
    out3 = (v8i16) __msa_ilvl_d((v2i64) out0, (v2i64) out2);            \
}

/* Description : Transposes 8x8 block with half word elements in vectors
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7
                 Outputs - out0, out1, out2, out3, out4, out5, out6, out7
                 Return Type - as per RTYPE
   Details     :
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8x8_H(RTYPE, in0, in1, in2, in3, in4, in5, in6, in7,   \
                       out0, out1, out2, out3, out4, out5, out6, out7)  \
{                                                                       \
    v8i16 s0_m, s1_m;                                                   \
    v8i16 tmp0_m, tmp1_m, tmp2_m, tmp3_m;                               \
    v8i16 tmp4_m, tmp5_m, tmp6_m, tmp7_m;                               \
                                                                        \
    ILVR_H2_SH(in6, in4, in7, in5, s0_m, s1_m);                         \
    ILVRL_H2_SH(s1_m, s0_m, tmp0_m, tmp1_m);                            \
    ILVL_H2_SH(in6, in4, in7, in5, s0_m, s1_m);                         \
    ILVRL_H2_SH(s1_m, s0_m, tmp2_m, tmp3_m);                            \
    ILVR_H2_SH(in2, in0, in3, in1, s0_m, s1_m);                         \
    ILVRL_H2_SH(s1_m, s0_m, tmp4_m, tmp5_m);                            \
    ILVL_H2_SH(in2, in0, in3, in1, s0_m, s1_m);                         \
    ILVRL_H2_SH(s1_m, s0_m, tmp6_m, tmp7_m);                            \
    PCKEV_D4(RTYPE, tmp0_m, tmp4_m, tmp1_m, tmp5_m, tmp2_m, tmp6_m,     \
             tmp3_m, tmp7_m, out0, out2, out4, out6);                   \
    out1 = (RTYPE) __msa_pckod_d((v2i64) tmp0_m, (v2i64) tmp4_m);       \
    out3 = (RTYPE) __msa_pckod_d((v2i64) tmp1_m, (v2i64) tmp5_m);       \
    out5 = (RTYPE) __msa_pckod_d((v2i64) tmp2_m, (v2i64) tmp6_m);       \
    out7 = (RTYPE) __msa_pckod_d((v2i64) tmp3_m, (v2i64) tmp7_m);       \
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8x8_UH_UH(...) TRANSPOSE8x8_H(v8u16, __VA_ARGS__)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8x8_SH_SH(...) TRANSPOSE8x8_H(v8i16, __VA_ARGS__)

/* Description : Transposes 4x4 block with word elements in vectors
   Arguments   : Inputs  - in0, in1, in2, in3
                 Outputs - out0, out1, out2, out3
                 Return Type - signed word
   Details     :
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE4x4_SW_SW(in0, in1, in2, in3, out0, out1, out2, out3)  \
{                                                                       \
    v4i32 s0_m, s1_m, s2_m, s3_m;                                       \
                                                                        \
    ILVRL_W2_SW(in1, in0, s0_m, s1_m);                                  \
    ILVRL_W2_SW(in3, in2, s2_m, s3_m);                                  \
                                                                        \
    out0 = (v4i32) __msa_ilvr_d((v2i64) s2_m, (v2i64) s0_m);            \
    out1 = (v4i32) __msa_ilvl_d((v2i64) s2_m, (v2i64) s0_m);            \
    out2 = (v4i32) __msa_ilvr_d((v2i64) s3_m, (v2i64) s1_m);            \
    out3 = (v4i32) __msa_ilvl_d((v2i64) s3_m, (v2i64) s1_m);            \
}

/* Description : Average byte elements from pair of vectors and store 8x4 byte
                 block in destination memory
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride
   Details     : Each byte element from input vector pair 'in0' and 'in1' are
                 averaged (a + b)/2 and stored in 'tmp0_m'
                 Each byte element from input vector pair 'in2' and 'in3' are
                 averaged (a + b)/2 and stored in 'tmp1_m'
                 Each byte element from input vector pair 'in4' and 'in5' are
                 averaged (a + b)/2 and stored in 'tmp2_m'
                 Each byte element from input vector pair 'in6' and 'in7' are
                 averaged (a + b)/2 and stored in 'tmp3_m'
                 The half vector results from all 4 vectors are stored in
                 destination memory as 8x4 byte block
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVE_ST8x4_UB(in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride)  \
{                                                                           \
    uint64_t out0_m, out1_m, out2_m, out3_m;                                \
    v16u8 tmp0_m, tmp1_m, tmp2_m, tmp3_m;                                   \
                                                                            \
    tmp0_m = __msa_ave_u_b((v16u8) in0, (v16u8) in1);                       \
    tmp1_m = __msa_ave_u_b((v16u8) in2, (v16u8) in3);                       \
    tmp2_m = __msa_ave_u_b((v16u8) in4, (v16u8) in5);                       \
    tmp3_m = __msa_ave_u_b((v16u8) in6, (v16u8) in7);                       \
                                                                            \
    out0_m = __msa_copy_u_d((v2i64) tmp0_m, 0);                             \
    out1_m = __msa_copy_u_d((v2i64) tmp1_m, 0);                             \
    out2_m = __msa_copy_u_d((v2i64) tmp2_m, 0);                             \
    out3_m = __msa_copy_u_d((v2i64) tmp3_m, 0);                             \
    SD4(out0_m, out1_m, out2_m, out3_m, pdst, stride);                      \
}

/* Description : Average byte elements from pair of vectors and store 16x4 byte
                 block in destination memory
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride
   Details     : Each byte element from input vector pair 'in0' and 'in1' are
                 averaged (a + b)/2 and stored in 'tmp0_m'
                 Each byte element from input vector pair 'in2' and 'in3' are
                 averaged (a + b)/2 and stored in 'tmp1_m'
                 Each byte element from input vector pair 'in4' and 'in5' are
                 averaged (a + b)/2 and stored in 'tmp2_m'
                 Each byte element from input vector pair 'in6' and 'in7' are
                 averaged (a + b)/2 and stored in 'tmp3_m'
                 The results from all 4 vectors are stored in destination
                 memory as 16x4 byte block
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVE_ST16x4_UB(in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride)  \
{                                                                            \
    v16u8 tmp0_m, tmp1_m, tmp2_m, tmp3_m;                                    \
                                                                             \
    tmp0_m = __msa_ave_u_b((v16u8) in0, (v16u8) in1);                        \
    tmp1_m = __msa_ave_u_b((v16u8) in2, (v16u8) in3);                        \
    tmp2_m = __msa_ave_u_b((v16u8) in4, (v16u8) in5);                        \
    tmp3_m = __msa_ave_u_b((v16u8) in6, (v16u8) in7);                        \
                                                                             \
    ST_UB4(tmp0_m, tmp1_m, tmp2_m, tmp3_m, pdst, stride);                    \
}

/* Description : Average rounded byte elements from pair of vectors and store
                 8x4 byte block in destination memory
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride
   Details     : Each byte element from input vector pair 'in0' and 'in1' are
                 average rounded (a + b + 1)/2 and stored in 'tmp0_m'
                 Each byte element from input vector pair 'in2' and 'in3' are
                 average rounded (a + b + 1)/2 and stored in 'tmp1_m'
                 Each byte element from input vector pair 'in4' and 'in5' are
                 average rounded (a + b + 1)/2 and stored in 'tmp2_m'
                 Each byte element from input vector pair 'in6' and 'in7' are
                 average rounded (a + b + 1)/2 and stored in 'tmp3_m'
                 The half vector results from all 4 vectors are stored in
                 destination memory as 8x4 byte block
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVER_ST8x4_UB(in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride)  \
{                                                                            \
    uint64_t out0_m, out1_m, out2_m, out3_m;                                 \
    v16u8 tp0_m, tp1_m, tp2_m, tp3_m;                                        \
                                                                             \
    AVER_UB4_UB(in0, in1, in2, in3, in4, in5, in6, in7,                      \
                tp0_m, tp1_m, tp2_m, tp3_m);                                 \
                                                                             \
    out0_m = __msa_copy_u_d((v2i64) tp0_m, 0);                               \
    out1_m = __msa_copy_u_d((v2i64) tp1_m, 0);                               \
    out2_m = __msa_copy_u_d((v2i64) tp2_m, 0);                               \
    out3_m = __msa_copy_u_d((v2i64) tp3_m, 0);                               \
    SD4(out0_m, out1_m, out2_m, out3_m, pdst, stride);                       \
}

/* Description : Average rounded byte elements from pair of vectors and store
                 16x4 byte block in destination memory
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride
   Details     : Each byte element from input vector pair 'in0' and 'in1' are
                 average rounded (a + b + 1)/2 and stored in 'tmp0_m'
                 Each byte element from input vector pair 'in2' and 'in3' are
                 average rounded (a + b + 1)/2 and stored in 'tmp1_m'
                 Each byte element from input vector pair 'in4' and 'in5' are
                 average rounded (a + b + 1)/2 and stored in 'tmp2_m'
                 Each byte element from input vector pair 'in6' and 'in7' are
                 average rounded (a + b + 1)/2 and stored in 'tmp3_m'
                 The vector results from all 4 vectors are stored in
                 destination memory as 16x4 byte block
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVER_ST16x4_UB(in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride)  \
{                                                                             \
    v16u8 t0_m, t1_m, t2_m, t3_m;                                             \
                                                                              \
    AVER_UB4_UB(in0, in1, in2, in3, in4, in5, in6, in7,                       \
                t0_m, t1_m, t2_m, t3_m);                                      \
    ST_UB4(t0_m, t1_m, t2_m, t3_m, pdst, stride);                             \
}

/* Description : Average rounded byte elements from pair of vectors,
                 average rounded with destination and store 8x4 byte block
                 in destination memory
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride
   Details     : Each byte element from input vector pair 'in0' and 'in1' are
                 average rounded (a + b + 1)/2 and stored in 'tmp0_m'
                 Each byte element from input vector pair 'in2' and 'in3' are
                 average rounded (a + b + 1)/2 and stored in 'tmp1_m'
                 Each byte element from input vector pair 'in4' and 'in5' are
                 average rounded (a + b + 1)/2 and stored in 'tmp2_m'
                 Each byte element from input vector pair 'in6' and 'in7' are
                 average rounded (a + b + 1)/2 and stored in 'tmp3_m'
                 The half vector results from all 4 vectors are stored in
                 destination memory as 8x4 byte block
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVER_DST_ST8x4_UB(in0, in1, in2, in3, in4, in5, in6, in7,  \
                          pdst, stride)                            \
{                                                                  \
    v16u8 tmp0_m, tmp1_m, tmp2_m, tmp3_m;                          \
    v16u8 dst0_m, dst1_m, dst2_m, dst3_m;                          \
                                                                   \
    LD_UB4(pdst, stride, dst0_m, dst1_m, dst2_m, dst3_m);          \
    AVER_UB4_UB(in0, in1, in2, in3, in4, in5, in6, in7,            \
                tmp0_m, tmp1_m, tmp2_m, tmp3_m);                   \
    AVER_ST8x4_UB(dst0_m, tmp0_m, dst1_m, tmp1_m,                  \
                  dst2_m, tmp2_m, dst3_m, tmp3_m, pdst, stride);   \
}

/* Description : Average rounded byte elements from pair of vectors,
                 average rounded with destination and store 16x4 byte block
                 in destination memory
   Arguments   : Inputs  - in0, in1, in2, in3, in4, in5, in6, in7, pdst, stride
   Details     : Each byte element from input vector pair 'in0' and 'in1' are
                 average rounded (a + b + 1)/2 and stored in 'tmp0_m'
                 Each byte element from input vector pair 'in2' and 'in3' are
                 average rounded (a + b + 1)/2 and stored in 'tmp1_m'
                 Each byte element from input vector pair 'in4' and 'in5' are
                 average rounded (a + b + 1)/2 and stored in 'tmp2_m'
                 Each byte element from input vector pair 'in6' and 'in7' are
                 average rounded (a + b + 1)/2 and stored in 'tmp3_m'
                 The vector results from all 4 vectors are stored in
                 destination memory as 16x4 byte block
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVER_DST_ST16x4_UB(in0, in1, in2, in3, in4, in5, in6, in7,  \
                           pdst, stride)                            \
{                                                                   \
    v16u8 tmp0_m, tmp1_m, tmp2_m, tmp3_m;                           \
    v16u8 dst0_m, dst1_m, dst2_m, dst3_m;                           \
                                                                    \
    LD_UB4(pdst, stride, dst0_m, dst1_m, dst2_m, dst3_m);           \
    AVER_UB4_UB(in0, in1, in2, in3, in4, in5, in6, in7,             \
                tmp0_m, tmp1_m, tmp2_m, tmp3_m);                    \
    AVER_ST16x4_UB(dst0_m, tmp0_m, dst1_m, tmp1_m,                  \
                   dst2_m, tmp2_m, dst3_m, tmp3_m, pdst, stride);   \
}

/* Description : Add block 4x4
   Arguments   : Inputs  - in0, in1, in2, in3, pdst, stride
   Details     : Least significant 4 bytes from each input vector are added to
                 the destination bytes, clipped between 0-255 and then stored.
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ADDBLK_ST4x4_UB(in0, in1, in2, in3, pdst, stride)         \
{                                                                 \
    uint32_t src0_m, src1_m, src2_m, src3_m;                      \
    uint32_t out0_m, out1_m, out2_m, out3_m;                      \
    v8i16 inp0_m, inp1_m, res0_m, res1_m;                         \
    v16i8 dst0_m = { 0 };                                         \
    v16i8 dst1_m = { 0 };                                         \
    v16i8 zero_m = { 0 };                                         \
                                                                  \
    ILVR_D2_SH(in1, in0, in3, in2, inp0_m, inp1_m)                \
    LW4(pdst, stride,  src0_m, src1_m, src2_m, src3_m);           \
    ਪਾਓ_W2_SB(src0_m, src1_m, dst0_m);                         \
    ਪਾਓ_W2_SB(src2_m, src3_m, dst1_m);                         \
    ILVR_B2_SH(zero_m, dst0_m, zero_m, dst1_m, res0_m, res1_m);   \
    ADD2(res0_m, inp0_m, res1_m, inp1_m, res0_m, res1_m);         \
    CLIP_SH2_0_255(res0_m, res1_m);                               \
    PCKEV_B2_SB(res0_m, res0_m, res1_m, res1_m, dst0_m, dst1_m);  \
                                                                  \
    out0_m = __msa_copy_u_w((v4i32) dst0_m, 0);                   \
    out1_m = __msa_copy_u_w((v4i32) dst0_m, 1);                   \
    out2_m = __msa_copy_u_w((v4i32) dst1_m, 0);                   \
    out3_m = __msa_copy_u_w((v4i32) dst1_m, 1);                   \
    SW4(out0_m, out1_m, out2_m, out3_m, pdst, stride);            \
}

/* Description : Dot product and addition of 3 signed halfword input vectors
   Arguments   : Inputs  - in0, in1, in2, coeff0, coeff1, coeff2
                 Outputs - out0_m
                 Return Type - signed halfword
   Details     : Dot product of 'in0' with 'coeff0'
                 Dot product of 'in1' with 'coeff1'
                 Dot product of 'in2' with 'coeff2'
                 Addition of all the 3 vector results

                 out0_m = (in0 * coeff0) + (in1 * coeff1) + (in2 * coeff2)
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ DPADD_SH3_SH(in0, in1, in2, coeff0, coeff1, coeff2)         \
( {                                                                 \
    v8i16 out0_m;                                                   \
                                                                    \
    out0_m = __msa_dotp_s_h((v16i8) in0, (v16i8) coeff0);           \
    out0_m = __msa_dpadd_s_h(out0_m, (v16i8) in1, (v16i8) coeff1);  \
    out0_m = __msa_dpadd_s_h(out0_m, (v16i8) in2, (v16i8) coeff2);  \
                                                                    \
    out0_m;                                                         \
} )

/* Description : Pack even elements of input vectors & xor with 128
   Arguments   : Inputs  - in0, in1
                 Outputs - out_m
                 Return Type - unsigned byte
   Details     : Signed byte even elements from 'in0' and 'in1' are packed
                 together in one vector and the resulted vector is xor'ed with
                 128 to shift the range from signed to unsigned byte
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_XORI128_UB(in0, in1)                            \
( {                                                           \
    v16u8 ਬਾਹਰਲਾ_m;                                              \
    ਬਾਹਰਲਾ_m = (v16u8) __msa_pckev_b((v16i8) in1, (v16i8) in0);  \
    ਬਾਹਰਲਾ_m = (v16u8) __msa_xori_b((v16u8) ਬਾਹਰਲਾ_m, 128);         \
    ਬਾਹਰਲਾ_m;                                                    \
} )

/* Description : Converts inputs to unsigned bytes, interleave, average & store
                 as 8x4 unsigned byte block
   Arguments   : Inputs  - in0, in1, in2, in3, dst0, dst1, pdst, stride
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CONVERT_UB_AVG_ST8x4_UB(in0, in1, in2, in3,           \
                                dst0, dst1, pdst, stride)     \
{                                                             \
    v16u8 tmp0_m, tmp1_m;                                     \
    uint8_t *pdst_m = (uint8_t *) (pdst);                     \
                                                              \
    tmp0_m = PCKEV_XORI128_UB(in0, in1);                      \
    tmp1_m = PCKEV_XORI128_UB(in2, in3);                      \
    AVER_UB2_UB(tmp0_m, dst0, tmp1_m, dst1, tmp0_m, tmp1_m);  \
    ST_D4(tmp0_m, tmp1_m, 0, 1, 0, 1, pdst_m, stride);        \
}

/* Description : Pack even byte elements, extract 0 & 2 index words from pair
                 of results and store 4 words in destination memory as per
                 stride
   Arguments   : Inputs  - in0, in1, in2, in3, pdst, stride
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_ST4x4_UB(in0, in1, in2, in3, pdst, stride)  \
{                                                         \
    uint32_t out0_m, out1_m, out2_m, out3_m;              \
    v16i8 tmp0_m, tmp1_m;                                 \
                                                          \
    PCKEV_B2_SB(in1, in0, in3, in2, tmp0_m, tmp1_m);      \
                                                          \
    out0_m = __msa_copy_u_w((v4i32) tmp0_m, 0);           \
    out1_m = __msa_copy_u_w((v4i32) tmp0_m, 2);           \
    out2_m = __msa_copy_u_w((v4i32) tmp1_m, 0);           \
    out3_m = __msa_copy_u_w((v4i32) tmp1_m, 2);           \
                                                          \
    SW4(out0_m, out1_m, out2_m, out3_m, pdst, stride);    \
}

/* Description : Pack even byte elements and store byte vector in destination
ਸਮ੍ਰਿਤੀ
   Arguments   : Inputs  - in0, in1, pdst
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PCKEV_ST_SB(in0, in1, pdst)                   \
{                                                     \
    v16i8 tmp_m;                                      \
    tmp_m = __msa_pckev_b((v16i8) in1, (v16i8) in0);  \
    ST_SB(tmp_m, (pdst));                             \
}

/* Description : Horizontal 2 tap filter kernel code
   Arguments   : Inputs  - in0, in1, mask, coeff, shift
*/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HORIZ_2TAP_FILT_UH(in0, in1, ਨਕਾਬ_2, coeff, ਖਿਸਕਾਓ)            \
( {                                                                 \
    v16i8 tmp0_m;                                                   \
    v8u16 tmp1_m;                                                   \
                                                                    \
    tmp0_m = __msa_vshf_b((v16i8) ਨਕਾਬ_2, (v16i8) in1, (v16i8) in0);  \
    tmp1_m = __msa_dotp_u_h((v16u8) tmp0_m, (v16u8) coeff);         \
    tmp1_m = (v8u16) __msa_srari_h((v8i16) tmp1_m, ਖਿਸਕਾਓ);          \
    tmp1_m = __msa_sat_u_h(tmp1_m, ਖਿਸਕਾਓ);                          \
                                                                    \
    tmp1_m;                                                         \
} )
#ਜੇ_ਅੰਤ  /* AVUTIL_MIPS_GENERIC_MACROS_MSA_H */

/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_X86_ASM_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_X86_ASM_H

#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ "config.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ xmm_reg { uint64_t a, b; } xmm_reg;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ymm_reg { uint64_t a, b, c, d; } ymm_reg;

#ಆದರೆ ARCH_X86_64
#    define FF_OPSIZE "q"
#    define FF_REG_a "rax"
#    define FF_REG_b "rbx"
#    define FF_REG_c "rcx"
#    define FF_REG_d "rdx"
#    define FF_REG_D "rdi"
#    define FF_REG_S "rsi"
#    define FF_PTR_ಗಾತ್ರ "8"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int64_t x86_reg;

#    define FF_REG_SP "rsp"
#    define FF_REG_BP "rbp"
#    define FF_REGBP   rbp
#    define FF_REGa    rax
#    define FF_REGb    rbx
#    define FF_REGc    rcx
#    define FF_REGd    rdx
#    define FF_REGSP   rsp

#ಅಥವಾಆದರೆ ARCH_X86_32

#    define FF_OPSIZE "l"
#    define FF_REG_a "eax"
#    define FF_REG_b "ebx"
#    define FF_REG_c "ecx"
#    define FF_REG_d "edx"
#    define FF_REG_D "edi"
#    define FF_REG_S "esi"
#    define FF_PTR_ಗಾತ್ರ "4"
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ int32_t x86_reg;

#    define FF_REG_SP "esp"
#    define FF_REG_BP "ebp"
#    define FF_REGBP   ebp
#    define FF_REGa    eax
#    define FF_REGb    ebx
#    define FF_REGc    ecx
#    define FF_REGd    edx
#    define FF_REGSP   esp
#ಇಲ್ಲದಿದ್ದರೆ
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ x86_reg;
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ ARCH_X86_64 && defined(PIC)
#    define BROKEN_RELOCATIONS 1
#ಆದರೆ_ಅಂತ್ಯ

/*
 * If gcc is not set to support sse (-msse) it will not accept xmm registers
 * in the clobber list for inline asm. XMM_CLOBBERS takes a list of xmm
 * registers to be marked as clobbered and evaluates to nothing if they are
 * not supported, or to the list itself if they are supported. Since a clobber
 * list may not be empty, XMM_CLOBBERS_ONLY should be used if the xmm
 * registers are the only in the clobber list.
 * For example a list with "eax" and "xmm0" as clobbers should become:
 * : XMM_CLOBBERS("xmm0",) "eax"
 * and a list with only "xmm0" should become:
 * XMM_CLOBBERS_ONLY("xmm0")
 */
#ಆದರೆ HAVE_XMM_CLOBBERS
#    define XMM_CLOBBERS(...)        __VA_ARGS__
#    define XMM_CLOBBERS_ONLY(...) : __VA_ARGS__
#ಇಲ್ಲದಿದ್ದರೆ
#    define XMM_CLOBBERS(...)
#    define XMM_CLOBBERS_ONLY(...)
#ಆದರೆ_ಅಂತ್ಯ

/* Use to export labels from asm. */
#ವ್ಯಾಖ್ಯಾನಿಸು LABEL_MANGLE(a) EXTERN_ಪೂರ್ವಪ್ರತ್ಯಯ #a

// Use rip-relative addressing if compiling PIC code on x86-64.
#ಆದರೆ ARCH_X86_64 && defined(PIC)
#    define LOCAL_MANGLE(a) #a "(%%rip)"
#ಇಲ್ಲದಿದ್ದರೆ
#    define LOCAL_MANGLE(a) #a
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_INLINE_ASM_ನೇರ_ಚಿಹ್ನೆ_REFS
#   define MANGLE(a) EXTERN_ಪೂರ್ವಪ್ರತ್ಯಯ LOCAL_MANGLE(a)
#   define NAMED_CONSTRAINTS_ಕೂಡಿಸು(...)
#   define NAMED_CONSTRAINTS(...)
#   define NAMED_CONSTRAINTS_ARRAY_ಕೂಡಿಸು(...)
#   define NAMED_CONSTRAINTS_ARRAY(...)
#ಇಲ್ಲದಿದ್ದರೆ
    /* When direct symbol references are used in code passed to a compiler that does not support them
     *  then these references need to be converted to named asm constraints instead.
     * Instead of returning a direct symbol MANGLE now returns a named constraint for that specific symbol.
     * In order for this to work there must also be a corresponding entry in the asm-interface. To add this
     *  entry use the macro NAMED_CONSTRAINTS() and pass in a list of each symbol reference used in the
     *  corresponding block of code. (e.g. NAMED_CONSTRAINTS(var1,var2,var3) where var1 is the first symbol etc. ).
     * If there are already existing constraints then use NAMED_CONSTRAINTS_ADD to add to the existing constraint list.
     */
#   define MANGLE(a) "%["#a"]"
    // Intel/MSVC does not correctly expand va-args so we need a rather ugly hack in order to get it to work
#   define FE_0(P,X) P(X)
#   define FE_1(P,X,X1) P(X), FE_0(P,X1)
#   define FE_2(P,X,X1,X2) P(X), FE_1(P,X1,X2)
#   define FE_3(P,X,X1,X2,X3) P(X), FE_2(P,X1,X2,X3)
#   define FE_4(P,X,X1,X2,X3,X4) P(X), FE_3(P,X1,X2,X3,X4)
#   define FE_5(P,X,X1,X2,X3,X4,X5) P(X), FE_4(P,X1,X2,X3,X4,X5)
#   define FE_6(P,X,X1,X2,X3,X4,X5,X6) P(X), FE_5(P,X1,X2,X3,X4,X5,X6)
#   define FE_7(P,X,X1,X2,X3,X4,X5,X6,X7) P(X), FE_6(P,X1,X2,X3,X4,X5,X6,X7)
#   define FE_8(P,X,X1,X2,X3,X4,X5,X6,X7,X8) P(X), FE_7(P,X1,X2,X3,X4,X5,X6,X7,X8)
#   define FE_9(P,X,X1,X2,X3,X4,X5,X6,X7,X8,X9) P(X), FE_8(P,X1,X2,X3,X4,X5,X6,X7,X8,X9)
#   define GET_FE_IMPL(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,NAME,...) NAME
#   define GET_FE(A) GET_FE_IMPL A
#   define GET_FE_GLUE(x, y) x y
#   define FOR_EACH_VA(P,...) GET_FE_GLUE(GET_FE((__VA_ARGS__,FE_9,FE_8,FE_7,FE_6,FE_5,FE_4,FE_3,FE_2,FE_1,FE_0)), (P,__VA_ARGS__))
#   define NAME_CONSTRAINT(x) [x] "m"(x)
    // Parameters are a list of each symbol reference required
#   define NAMED_CONSTRAINTS_ಕೂಡಿಸು(...) , FOR_EACH_VA(NAME_CONSTRAINT,__VA_ARGS__)
    // Same but without comma for when there are no previously defined constraints
#   define NAMED_CONSTRAINTS(...) FOR_EACH_VA(NAME_CONSTRAINT,__VA_ARGS__)
    // Same as above NAMED_CONSTRAINTS except used for passing arrays/pointers instead of normal variables
#   define NAME_CONSTRAINT_ARRAY(x) [x] "m"(*x)
#   define NAMED_CONSTRAINTS_ARRAY_ಕೂಡಿಸು(...) , FOR_EACH_VA(NAME_CONSTRAINT_ARRAY,__VA_ARGS__)
#   define NAMED_CONSTRAINTS_ARRAY(...) FOR_EACH_VA(NAME_CONSTRAINT_ARRAY,__VA_ARGS__)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_X86_ASM_H */

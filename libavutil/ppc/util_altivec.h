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

/**
 * @file
 * Contains misc utility macros and inline functions
 */

#अगर_अघोषित AVUTIL_PPC_UTIL_ALTIVEC_H
#घोषणा AVUTIL_PPC_UTIL_ALTIVEC_H

#समावेश <stdint.h>

#समावेश "config.h"

/***********************************************************************
 * Vector types
 **********************************************************************/
#घोषणा vec_u8  vector अचिन्हित अक्षर
#घोषणा vec_s8  vector चिन्हित अक्षर
#घोषणा vec_u16 vector अचिन्हित लघु
#घोषणा vec_s16 vector चिन्हित लघु
#घोषणा vec_u32 vector अचिन्हित पूर्णांक
#घोषणा vec_s32 vector चिन्हित पूर्णांक
#घोषणा vec_f   vector भग्न

/***********************************************************************
 * Null vector
 **********************************************************************/
#घोषणा LOAD_ZERO स्थिर vec_u8 zerov = vec_splat_u8( 0 )

#घोषणा zero_u8v  (vec_u8)  zerov
#घोषणा zero_s8v  (vec_s8)  zerov
#घोषणा zero_u16v (vec_u16) zerov
#घोषणा zero_s16v (vec_s16) zerov
#घोषणा zero_u32v (vec_u32) zerov
#घोषणा zero_s32v (vec_s32) zerov

#अगर HAVE_ALTIVEC
#समावेश <altivec.h>

// used to build registers permutation vectors (vcprm)
// the 's' are for words in the _s_econd vector
#घोषणा WORD_0 0x00,0x01,0x02,0x03
#घोषणा WORD_1 0x04,0x05,0x06,0x07
#घोषणा WORD_2 0x08,0x09,0x0a,0x0b
#घोषणा WORD_3 0x0c,0x0d,0x0e,0x0f
#घोषणा WORD_s0 0x10,0x11,0x12,0x13
#घोषणा WORD_s1 0x14,0x15,0x16,0x17
#घोषणा WORD_s2 0x18,0x19,0x1a,0x1b
#घोषणा WORD_s3 0x1c,0x1d,0x1e,0x1f
#घोषणा vcprm(a,b,c,d) (स्थिर vec_u8){WORD_ ## a, WORD_ ## b, WORD_ ## c, WORD_ ## d}

#घोषणा SWP_W2S0 0x02,0x03,0x00,0x01
#घोषणा SWP_W2S1 0x06,0x07,0x04,0x05
#घोषणा SWP_W2S2 0x0a,0x0b,0x08,0x09
#घोषणा SWP_W2S3 0x0e,0x0f,0x0c,0x0d
#घोषणा SWP_W2Ss0 0x12,0x13,0x10,0x11
#घोषणा SWP_W2Ss1 0x16,0x17,0x14,0x15
#घोषणा SWP_W2Ss2 0x1a,0x1b,0x18,0x19
#घोषणा SWP_W2Ss3 0x1e,0x1f,0x1c,0x1d
#घोषणा vcswapi2s(a,b,c,d) (स्थिर vector अचिन्हित अक्षर){SWP_W2S ## a, SWP_W2S ## b, SWP_W2S ## c, SWP_W2S ## d}

#घोषणा vcswapc() \
  (स्थिर vector अचिन्हित अक्षर){0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}


// Transpose 8x8 matrix of 16-bit elements (in-place)
#घोषणा TRANSPOSE8(a,b,c,d,e,f,g,h) \
करो { \
    vec_s16 A1, B1, C1, D1, E1, F1, G1, H1; \
    vec_s16 A2, B2, C2, D2, E2, F2, G2, H2; \
 \
    A1 = vec_mergeh (a, e); \
    B1 = vec_mergel (a, e); \
    C1 = vec_mergeh (b, f); \
    D1 = vec_mergel (b, f); \
    E1 = vec_mergeh (c, g); \
    F1 = vec_mergel (c, g); \
    G1 = vec_mergeh (d, h); \
    H1 = vec_mergel (d, h); \
 \
    A2 = vec_mergeh (A1, E1); \
    B2 = vec_mergel (A1, E1); \
    C2 = vec_mergeh (B1, F1); \
    D2 = vec_mergel (B1, F1); \
    E2 = vec_mergeh (C1, G1); \
    F2 = vec_mergel (C1, G1); \
    G2 = vec_mergeh (D1, H1); \
    H2 = vec_mergel (D1, H1); \
 \
    a = vec_mergeh (A2, E2); \
    b = vec_mergel (A2, E2); \
    c = vec_mergeh (B2, F2); \
    d = vec_mergel (B2, F2); \
    e = vec_mergeh (C2, G2); \
    f = vec_mergel (C2, G2); \
    g = vec_mergeh (D2, H2); \
    h = vec_mergel (D2, H2); \
} जबतक (0)


#अगर HAVE_BIGENDIAN
#घोषणा VEC_LD(offset,b)                                   \
    vec_perm(vec_ld(offset, b), vec_ld((offset)+15, b), vec_lvsl(offset, b))
#अन्यथा
#घोषणा VEC_LD(offset,b)                                   \
    vec_vsx_ld(offset, b)
#पूर्ण_अगर

/** @brief loads unaligned vector @a *src with offset @a offset
    and returns it */
#अगर HAVE_BIGENDIAN
अटल अंतरभूत vec_u8 unaligned_load(पूर्णांक offset, स्थिर uint8_t *src)
{
    रेजिस्टर vec_u8 first = vec_ld(offset, src);
    रेजिस्टर vec_u8 second = vec_ld(offset + 15, src);
    रेजिस्टर vec_u8 mask = vec_lvsl(offset, src);
    वापस vec_perm(first, second, mask);
}
अटल अंतरभूत vec_u8 load_with_perm_vec(पूर्णांक offset, स्थिर uint8_t *src, vec_u8 perm_vec)
{
    vec_u8 a = vec_ld(offset, src);
    vec_u8 b = vec_ld(offset + 15, src);
    वापस vec_perm(a, b, perm_vec);
}
#अन्यथा
#घोषणा unaligned_load(a,b) VEC_LD(a,b)
#घोषणा load_with_perm_vec(a,b,c) VEC_LD(a,b)
#पूर्ण_अगर

#अगर HAVE_BIGENDIAN
अटल अंतरभूत व्योम unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_u8 lo    = vec_ld(0, dst);
    vec_u8 hi    = vec_ld(15, dst);
    vec_u8 edges = vec_perm(hi, lo, vec_lvsl(0, dst));
    vec_u8 align = vec_lvsr(0, dst);

    vec_st(vec_perm(v, edges, align), 15, dst);
    vec_st(vec_perm(edges, v, align), 0, dst);
}
#अन्यथा
अटल अंतरभूत व्योम unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_vsx_st(v, 0, dst);
}
#पूर्ण_अगर


/**
 * loads vector known misalignment
 * @param perm_vec the align permute vector to combine the two loads from lvsl
 */

#घोषणा vec_unaligned_load(b)  VEC_LD(0, b)

#अगर HAVE_BIGENDIAN
#घोषणा VEC_MERGEH(a, b) vec_mergeh(a, b)
#घोषणा VEC_MERGEL(a, b) vec_mergel(a, b)
#अन्यथा
#घोषणा VEC_MERGEH(a, b) vec_mergeh(b, a)
#घोषणा VEC_MERGEL(a, b) vec_mergel(b, a)
#पूर्ण_अगर

#अगर HAVE_BIGENDIAN
#घोषणा VEC_ST(a,b,c) vec_st(a,b,c)
#अन्यथा
#घोषणा VEC_ST(a,b,c) vec_vsx_st(a,b,c)
#पूर्ण_अगर

#अगर HAVE_BIGENDIAN
#घोषणा VEC_SPLAT16(a,b) vec_splat((vec_s16)(a), b)
#अन्यथा
#घोषणा VEC_SPLAT16(a,b) vec_splat((vec_s16)(vec_perm(a, a, vcswapi2s(0,1,2,3))), b)
#पूर्ण_अगर

#अगर HAVE_BIGENDIAN
#घोषणा VEC_SLD16(a,b,c) vec_sld(a, b, c)
#अन्यथा
#घोषणा VEC_SLD16(a,b,c) vec_sld(b, a, c)
#पूर्ण_अगर

#पूर्ण_अगर /* HAVE_ALTIVEC */

#अगर HAVE_VSX
#अगर HAVE_BIGENDIAN
#घोषणा vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_splat_u8(0),           \
                         (vec_u8)vec_vsx_ld((off), (p))))
#अन्यथा
#घोषणा vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_vsx_ld((off), (p)),    \
                         (vec_u8)vec_splat_u8(0)))
#पूर्ण_अगर /* HAVE_BIGENDIAN */
#पूर्ण_अगर /* HAVE_VSX */

#पूर्ण_अगर /* AVUTIL_PPC_UTIL_ALTIVEC_H */

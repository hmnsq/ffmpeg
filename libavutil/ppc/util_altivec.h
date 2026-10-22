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

#यदि_अपरिभाषितम् AVUTIL_PPC_UTIL_ALTIVEC_H
#परिभाषय AVUTIL_PPC_UTIL_ALTIVEC_H

#अन्तर्भाव <stdint.h>

#अन्तर्भाव "config.h"

/***********************************************************************
 * Vector types
 **********************************************************************/
#परिभाषय vec_u8  सदिशम् अचिह्नित वर्ण
#परिभाषय vec_s8  सदिशम् चिह्नित वर्ण
#परिभाषय vec_u16 सदिशम् अचिह्नित ह्रस्व
#परिभाषय vec_s16 सदिशम् चिह्नित ह्रस्व
#परिभाषय vec_u32 सदिशम् अचिह्नित पूर्णाङ्क
#परिभाषय vec_s32 सदिशम् चिह्नित पूर्णाङ्क
#परिभाषय vec_f   सदिशम् भिन्न

/***********************************************************************
 * Null vector
 **********************************************************************/
#परिभाषय आरोपय_ZERO ध्रुव vec_u8 zerov = vec_splat_u8( 0 )

#परिभाषय zero_u8v  (vec_u8)  zerov
#परिभाषय zero_s8v  (vec_s8)  zerov
#परिभाषय zero_u16v (vec_u16) zerov
#परिभाषय zero_s16v (vec_s16) zerov
#परिभाषय zero_u32v (vec_u32) zerov
#परिभाषय zero_s32v (vec_s32) zerov

#यदि HAVE_ALTIVEC
#अन्तर्भाव <altivec.h>

// used to build registers permutation vectors (vcprm)
// the 's' are for words in the _s_econd vector
#परिभाषय WORD_0 0x00,0x01,0x02,0x03
#परिभाषय WORD_1 0x04,0x05,0x06,0x07
#परिभाषय WORD_2 0x08,0x09,0x0a,0x0b
#परिभाषय WORD_3 0x0c,0x0d,0x0e,0x0f
#परिभाषय WORD_s0 0x10,0x11,0x12,0x13
#परिभाषय WORD_s1 0x14,0x15,0x16,0x17
#परिभाषय WORD_s2 0x18,0x19,0x1a,0x1b
#परिभाषय WORD_s3 0x1c,0x1d,0x1e,0x1f
#परिभाषय vcprm(a,b,c,d) (ध्रुव vec_u8){WORD_ ## a, WORD_ ## b, WORD_ ## c, WORD_ ## d}

#परिभाषय SWP_W2S0 0x02,0x03,0x00,0x01
#परिभाषय SWP_W2S1 0x06,0x07,0x04,0x05
#परिभाषय SWP_W2S2 0x0a,0x0b,0x08,0x09
#परिभाषय SWP_W2S3 0x0e,0x0f,0x0c,0x0d
#परिभाषय SWP_W2Ss0 0x12,0x13,0x10,0x11
#परिभाषय SWP_W2Ss1 0x16,0x17,0x14,0x15
#परिभाषय SWP_W2Ss2 0x1a,0x1b,0x18,0x19
#परिभाषय SWP_W2Ss3 0x1e,0x1f,0x1c,0x1d
#परिभाषय vcswapi2s(a,b,c,d) (ध्रुव सदिशम् अचिह्नित वर्ण){SWP_W2S ## a, SWP_W2S ## b, SWP_W2S ## c, SWP_W2S ## d}

#परिभाषय vcswapc() \
  (ध्रुव सदिशम् अचिह्नित वर्ण){0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}


// Transpose 8x8 matrix of 16-bit elements (in-place)
#परिभाषय TRANSPOSE8(a,b,c,d,e,f,g,h) \
कुरु { \
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
} यावत् (0)


#यदि HAVE_BIGENDIAN
#परिभाषय VEC_LD(विस्थापनम्,b)                                   \
    vec_perm(vec_ld(विस्थापनम्, b), vec_ld((विस्थापनम्)+15, b), vec_lvsl(विस्थापनम्, b))
#अन्यथा
#परिभाषय VEC_LD(विस्थापनम्,b)                                   \
    vec_vsx_ld(विस्थापनम्, b)
#यदि_अन्तः

/** @brief loads unaligned vector @a *src with offset @a offset
    and returns it */
#यदि HAVE_BIGENDIAN
स्थिर अन्तःस्थ vec_u8 unaligned_आरोपय(पूर्णाङ्क विस्थापनम्, ध्रुव uint8_t *src)
{
    पञ्जिका vec_u8 first = vec_ld(विस्थापनम्, src);
    पञ्जिका vec_u8 second = vec_ld(विस्थापनम् + 15, src);
    पञ्जिका vec_u8 आवरणम्_2 = vec_lvsl(विस्थापनम्, src);
    प्रत्यागम vec_perm(first, second, आवरणम्_2);
}
स्थिर अन्तःस्थ vec_u8 आरोपय_with_perm_vec(पूर्णाङ्क विस्थापनम्, ध्रुव uint8_t *src, vec_u8 perm_vec)
{
    vec_u8 a = vec_ld(विस्थापनम्, src);
    vec_u8 b = vec_ld(विस्थापनम् + 15, src);
    प्रत्यागम vec_perm(a, b, perm_vec);
}
#अन्यथा
#परिभाषय unaligned_आरोपय(a,b) VEC_LD(a,b)
#परिभाषय आरोपय_with_perm_vec(a,b,c) VEC_LD(a,b)
#यदि_अन्तः

#यदि HAVE_BIGENDIAN
स्थिर अन्तःस्थ शून्य unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_u8 lo    = vec_ld(0, dst);
    vec_u8 hi    = vec_ld(15, dst);
    vec_u8 धाराः = vec_perm(hi, lo, vec_lvsl(0, dst));
    vec_u8 align = vec_lvsr(0, dst);

    vec_st(vec_perm(v, धाराः, align), 15, dst);
    vec_st(vec_perm(धाराः, v, align), 0, dst);
}
#अन्यथा
स्थिर अन्तःस्थ शून्य unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_vsx_st(v, 0, dst);
}
#यदि_अन्तः


/**
 * loads vector known misalignment
 * @param perm_vec the align permute vector to combine the two loads from lvsl
 */

#परिभाषय vec_unaligned_आरोपय(b)  VEC_LD(0, b)

#यदि HAVE_BIGENDIAN
#परिभाषय VEC_MERGEH(a, b) vec_mergeh(a, b)
#परिभाषय VEC_MERGEL(a, b) vec_mergel(a, b)
#अन्यथा
#परिभाषय VEC_MERGEH(a, b) vec_mergeh(b, a)
#परिभाषय VEC_MERGEL(a, b) vec_mergel(b, a)
#यदि_अन्तः

#यदि HAVE_BIGENDIAN
#परिभाषय VEC_ST(a,b,c) vec_st(a,b,c)
#अन्यथा
#परिभाषय VEC_ST(a,b,c) vec_vsx_st(a,b,c)
#यदि_अन्तः

#यदि HAVE_BIGENDIAN
#परिभाषय VEC_SPLAT16(a,b) vec_splat((vec_s16)(a), b)
#अन्यथा
#परिभाषय VEC_SPLAT16(a,b) vec_splat((vec_s16)(vec_perm(a, a, vcswapi2s(0,1,2,3))), b)
#यदि_अन्तः

#यदि HAVE_BIGENDIAN
#परिभाषय VEC_SLD16(a,b,c) vec_sld(a, b, c)
#अन्यथा
#परिभाषय VEC_SLD16(a,b,c) vec_sld(b, a, c)
#यदि_अन्तः

#यदि_अन्तः /* HAVE_ALTIVEC */

#यदि HAVE_VSX
#यदि HAVE_BIGENDIAN
#परिभाषय vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_splat_u8(0),           \
                         (vec_u8)vec_vsx_ld((off), (p))))
#अन्यथा
#परिभाषय vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_vsx_ld((off), (p)),    \
                         (vec_u8)vec_splat_u8(0)))
#यदि_अन्तः /* HAVE_BIGENDIAN */
#यदि_अन्तः /* HAVE_VSX */

#यदि_अन्तः /* AVUTIL_PPC_UTIL_ALTIVEC_H */

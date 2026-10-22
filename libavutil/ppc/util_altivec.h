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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_PPC_UTIL_ALTIVEC_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_PPC_UTIL_ALTIVEC_H

#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "config.h"

/***********************************************************************
 * Vector types
 **********************************************************************/
#ವ್ಯಾಖ್ಯಾನಿಸು vec_u8  ಸದಿಶ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು vec_s8  ಸದಿಶ ಚಿಹ್ನೆಯುಳ್ಳ ಅಕ್ಷರ
#ವ್ಯಾಖ್ಯಾನಿಸು vec_u16 ಸದಿಶ ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು vec_s16 ಸದಿಶ ಚಿಹ್ನೆಯುಳ್ಳ ಗಿಡ್ಡ
#ವ್ಯಾಖ್ಯಾನಿಸು vec_u32 ಸದಿಶ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ
#ವ್ಯಾಖ್ಯಾನಿಸು vec_s32 ಸದಿಶ ಚಿಹ್ನೆಯುಳ್ಳ ಪೂರ್ಣಾಂಕ
#ವ್ಯಾಖ್ಯಾನಿಸು vec_f   ಸದಿಶ ದಶಮಾಂಶ

/***********************************************************************
 * Null vector
 **********************************************************************/
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_ZERO ಸ್ಥಿರಾಂಕ vec_u8 zerov = vec_splat_u8( 0 )

#ವ್ಯಾಖ್ಯಾನಿಸು zero_u8v  (vec_u8)  zerov
#ವ್ಯಾಖ್ಯಾನಿಸು zero_s8v  (vec_s8)  zerov
#ವ್ಯಾಖ್ಯಾನಿಸು zero_u16v (vec_u16) zerov
#ವ್ಯಾಖ್ಯಾನಿಸು zero_s16v (vec_s16) zerov
#ವ್ಯಾಖ್ಯಾನಿಸು zero_u32v (vec_u32) zerov
#ವ್ಯಾಖ್ಯಾನಿಸು zero_s32v (vec_s32) zerov

#ಆದರೆ HAVE_ALTIVEC
#ಅನ್ತರ್ಭಾವ <altivec.h>

// used to build registers permutation vectors (vcprm)
// the 's' are for words in the _s_econd vector
#ವ್ಯಾಖ್ಯಾನಿಸು ಶಬ್ದ_0 0x00,0x01,0x02,0x03
#ವ್ಯಾಖ್ಯಾನಿಸು ಶಬ್ದ_1 0x04,0x05,0x06,0x07
#ವ್ಯಾಖ್ಯಾನಿಸು ಶಬ್ದ_2 0x08,0x09,0x0a,0x0b
#ವ್ಯಾಖ್ಯಾನಿಸು ಶಬ್ದ_3 0x0c,0x0d,0x0e,0x0f
#ವ್ಯಾಖ್ಯಾನಿಸು ಶಬ್ದ_s0 0x10,0x11,0x12,0x13
#ವ್ಯಾಖ್ಯಾನಿಸು ಶಬ್ದ_s1 0x14,0x15,0x16,0x17
#ವ್ಯಾಖ್ಯಾನಿಸು ಶಬ್ದ_s2 0x18,0x19,0x1a,0x1b
#ವ್ಯಾಖ್ಯಾನಿಸು ಶಬ್ದ_s3 0x1c,0x1d,0x1e,0x1f
#ವ್ಯಾಖ್ಯಾನಿಸು vcprm(a,b,c,d) (ಸ್ಥಿರಾಂಕ vec_u8){ಶಬ್ದ ## a, ಶಬ್ದ ## b, ಶಬ್ದ ## c, ಶಬ್ದ ## d}

#ವ್ಯಾಖ್ಯಾನಿಸು SWP_W2S0 0x02,0x03,0x00,0x01
#ವ್ಯಾಖ್ಯಾನಿಸು SWP_W2S1 0x06,0x07,0x04,0x05
#ವ್ಯಾಖ್ಯಾನಿಸು SWP_W2S2 0x0a,0x0b,0x08,0x09
#ವ್ಯಾಖ್ಯಾನಿಸು SWP_W2S3 0x0e,0x0f,0x0c,0x0d
#ವ್ಯಾಖ್ಯಾನಿಸು SWP_W2Ss0 0x12,0x13,0x10,0x11
#ವ್ಯಾಖ್ಯಾನಿಸು SWP_W2Ss1 0x16,0x17,0x14,0x15
#ವ್ಯಾಖ್ಯಾನಿಸು SWP_W2Ss2 0x1a,0x1b,0x18,0x19
#ವ್ಯಾಖ್ಯಾನಿಸು SWP_W2Ss3 0x1e,0x1f,0x1c,0x1d
#ವ್ಯಾಖ್ಯಾನಿಸು vcswapi2s(a,b,c,d) (ಸ್ಥಿರಾಂಕ ಸದಿಶ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ){SWP_W2S ## a, SWP_W2S ## b, SWP_W2S ## c, SWP_W2S ## d}

#ವ್ಯಾಖ್ಯಾನಿಸು vcswapc() \
  (ಸ್ಥಿರಾಂಕ ಸದಿಶ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ){0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}


// Transpose 8x8 matrix of 16-bit elements (in-place)
#ವ್ಯಾಖ್ಯಾನಿಸು TRANSPOSE8(a,b,c,d,e,f,g,h) \
ಮಾಡು { \
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
} ಆಗ (0)


#ಆದರೆ HAVE_BIGENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_LD(ಸ್ಥಾನಾಂತರ,b)                                   \
    vec_perm(vec_ld(ಸ್ಥಾನಾಂತರ, b), vec_ld((ಸ್ಥಾನಾಂತರ)+15, b), vec_lvsl(ಸ್ಥಾನಾಂತರ, b))
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_LD(ಸ್ಥಾನಾಂತರ,b)                                   \
    vec_vsx_ld(ಸ್ಥಾನಾಂತರ, b)
#ಆದರೆ_ಅಂತ್ಯ

/** @brief loads unaligned vector @a *src with offset @a offset
    and returns it */
#ಆದರೆ HAVE_BIGENDIAN
ಸ್ಥಿರ ಸಾಲೊಳಗೆ vec_u8 unaligned_ತುಂಬು(ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ, ಸ್ಥಿರಾಂಕ uint8_t *src)
{
    ನೋಂದಣಿ vec_u8 ಮೊದಲ = vec_ld(ಸ್ಥಾನಾಂತರ, src);
    ನೋಂದಣಿ vec_u8 ಎರಡನೇ = vec_ld(ಸ್ಥಾನಾಂತರ + 15, src);
    ನೋಂದಣಿ vec_u8 ಮುಖವಾಡ_2 = vec_lvsl(ಸ್ಥಾನಾಂತರ, src);
    ಹಿಂತಿರುಗಿ vec_perm(ಮೊದಲ, ಎರಡನೇ, ಮುಖವಾಡ_2);
}
ಸ್ಥಿರ ಸಾಲೊಳಗೆ vec_u8 ತುಂಬು_with_perm_vec(ಪೂರ್ಣಾಂಕ ಸ್ಥಾನಾಂತರ, ಸ್ಥಿರಾಂಕ uint8_t *src, vec_u8 perm_vec)
{
    vec_u8 a = vec_ld(ಸ್ಥಾನಾಂತರ, src);
    vec_u8 b = vec_ld(ಸ್ಥಾನಾಂತರ + 15, src);
    ಹಿಂತಿರುಗಿ vec_perm(a, b, perm_vec);
}
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು unaligned_ತುಂಬು(a,b) VEC_LD(a,b)
#ವ್ಯಾಖ್ಯಾನಿಸು ತುಂಬು_with_perm_vec(a,b,c) VEC_LD(a,b)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_BIGENDIAN
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_u8 lo    = vec_ld(0, dst);
    vec_u8 hi    = vec_ld(15, dst);
    vec_u8 ಅಂಚುಗಳು = vec_perm(hi, lo, vec_lvsl(0, dst));
    vec_u8 align = vec_lvsr(0, dst);

    vec_st(vec_perm(v, ಅಂಚುಗಳು, align), 15, dst);
    vec_st(vec_perm(ಅಂಚುಗಳು, v, align), 0, dst);
}
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_vsx_st(v, 0, dst);
}
#ಆದರೆ_ಅಂತ್ಯ


/**
 * loads vector known misalignment
 * @param perm_vec the align permute vector to combine the two loads from lvsl
 */

#ವ್ಯಾಖ್ಯಾನಿಸು vec_unaligned_ತುಂಬು(b)  VEC_LD(0, b)

#ಆದರೆ HAVE_BIGENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_MERGEH(a, b) vec_mergeh(a, b)
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_MERGEL(a, b) vec_mergel(a, b)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_MERGEH(a, b) vec_mergeh(b, a)
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_MERGEL(a, b) vec_mergel(b, a)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_BIGENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_ST(a,b,c) vec_st(a,b,c)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_ST(a,b,c) vec_vsx_st(a,b,c)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_BIGENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_SPLAT16(a,b) vec_splat((vec_s16)(a), b)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_SPLAT16(a,b) vec_splat((vec_s16)(vec_perm(a, a, vcswapi2s(0,1,2,3))), b)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ HAVE_BIGENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_SLD16(a,b,c) vec_sld(a, b, c)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು VEC_SLD16(a,b,c) vec_sld(b, a, c)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* HAVE_ALTIVEC */

#ಆದರೆ HAVE_VSX
#ಆದರೆ HAVE_BIGENDIAN
#ವ್ಯಾಖ್ಯಾನಿಸು vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_splat_u8(0),           \
                         (vec_u8)vec_vsx_ld((off), (p))))
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_vsx_ld((off), (p)),    \
                         (vec_u8)vec_splat_u8(0)))
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_BIGENDIAN */
#ಆದರೆ_ಅಂತ್ಯ /* HAVE_VSX */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_PPC_UTIL_ALTIVEC_H */

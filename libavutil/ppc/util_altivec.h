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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_PPC_UTIL_ALTIVEC_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_PPC_UTIL_ALTIVEC_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

/***********************************************************************
 * Vector types
 **********************************************************************/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vec_u8  ਸਦਿਸ਼ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vec_s8  ਸਦਿਸ਼ ਨਿਸ਼ਾਨੀਵਾਲਾ ਅੱਖਰ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vec_u16 ਸਦਿਸ਼ ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vec_s16 ਸਦਿਸ਼ ਨਿਸ਼ਾਨੀਵਾਲਾ ਛੋਟਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vec_u32 ਸਦਿਸ਼ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vec_s32 ਸਦਿਸ਼ ਨਿਸ਼ਾਨੀਵਾਲਾ ਪੂਰਨ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vec_f   ਸਦਿਸ਼ ਦਸ਼ਮਲਵ

/***********************************************************************
 * Null vector
 **********************************************************************/
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_ZERO ਅਚਲ vec_u8 zerov = vec_splat_u8( 0 )

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ zero_u8v  (vec_u8)  zerov
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ zero_s8v  (vec_s8)  zerov
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ zero_u16v (vec_u16) zerov
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ zero_s16v (vec_s16) zerov
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ zero_u32v (vec_u32) zerov
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ zero_s32v (vec_s32) zerov

#ਜੇ HAVE_ALTIVEC
#ਅਨ੍ਤਰ੍ਭਾਵ <altivec.h>

// used to build registers permutation vectors (vcprm)
// the 's' are for words in the _s_econd vector
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ਬਦ_0 0x00,0x01,0x02,0x03
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ਬਦ_1 0x04,0x05,0x06,0x07
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ਬਦ_2 0x08,0x09,0x0a,0x0b
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ਬਦ_3 0x0c,0x0d,0x0e,0x0f
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ਬਦ_s0 0x10,0x11,0x12,0x13
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ਬਦ_s1 0x14,0x15,0x16,0x17
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ਬਦ_s2 0x18,0x19,0x1a,0x1b
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸ਼ਬਦ_s3 0x1c,0x1d,0x1e,0x1f
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vcprm(a,b,c,d) (ਅਚਲ vec_u8){ਸ਼ਬਦ ## a, ਸ਼ਬਦ ## b, ਸ਼ਬਦ ## c, ਸ਼ਬਦ ## d}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWP_W2S0 0x02,0x03,0x00,0x01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWP_W2S1 0x06,0x07,0x04,0x05
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWP_W2S2 0x0a,0x0b,0x08,0x09
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWP_W2S3 0x0e,0x0f,0x0c,0x0d
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWP_W2Ss0 0x12,0x13,0x10,0x11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWP_W2Ss1 0x16,0x17,0x14,0x15
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWP_W2Ss2 0x1a,0x1b,0x18,0x19
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SWP_W2Ss3 0x1e,0x1f,0x1c,0x1d
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vcswapi2s(a,b,c,d) (ਅਚਲ ਸਦਿਸ਼ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ){SWP_W2S ## a, SWP_W2S ## b, SWP_W2S ## c, SWP_W2S ## d}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vcswapc() \
  (ਅਚਲ ਸਦਿਸ਼ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ){0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}


// Transpose 8x8 matrix of 16-bit elements (in-place)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TRANSPOSE8(a,b,c,d,e,f,g,h) \
ਕਰੋ { \
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
} ਜਦੋਂ (0)


#ਜੇ HAVE_BIGENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_LD(ਵਿੱਥ,b)                                   \
    vec_perm(vec_ld(ਵਿੱਥ, b), vec_ld((ਵਿੱਥ)+15, b), vec_lvsl(ਵਿੱਥ, b))
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_LD(ਵਿੱਥ,b)                                   \
    vec_vsx_ld(ਵਿੱਥ, b)
#ਜੇ_ਅੰਤ

/** @brief loads unaligned vector @a *src with offset @a offset
    and returns it */
#ਜੇ HAVE_BIGENDIAN
ਸਥਿਰ ਸਤਰਅੰਦਰ vec_u8 unaligned_ਲੱਦੋ(ਪੂਰਨ ਵਿੱਥ, ਅਚਲ uint8_t *src)
{
    ਰਜਿਸਟਰ vec_u8 ਪਹਿਲਾ = vec_ld(ਵਿੱਥ, src);
    ਰਜਿਸਟਰ vec_u8 ਦੂਜਾ = vec_ld(ਵਿੱਥ + 15, src);
    ਰਜਿਸਟਰ vec_u8 ਨਕਾਬ_2 = vec_lvsl(ਵਿੱਥ, src);
    ਵਾਪਸ vec_perm(ਪਹਿਲਾ, ਦੂਜਾ, ਨਕਾਬ_2);
}
ਸਥਿਰ ਸਤਰਅੰਦਰ vec_u8 ਲੱਦੋ_with_perm_vec(ਪੂਰਨ ਵਿੱਥ, ਅਚਲ uint8_t *src, vec_u8 perm_vec)
{
    vec_u8 a = vec_ld(ਵਿੱਥ, src);
    vec_u8 b = vec_ld(ਵਿੱਥ + 15, src);
    ਵਾਪਸ vec_perm(a, b, perm_vec);
}
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ unaligned_ਲੱਦੋ(a,b) VEC_LD(a,b)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਲੱਦੋ_with_perm_vec(a,b,c) VEC_LD(a,b)
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_BIGENDIAN
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_u8 lo    = vec_ld(0, dst);
    vec_u8 hi    = vec_ld(15, dst);
    vec_u8 ਕਿਨਾਰੇ = vec_perm(hi, lo, vec_lvsl(0, dst));
    vec_u8 align = vec_lvsr(0, dst);

    vec_st(vec_perm(v, ਕਿਨਾਰੇ, align), 15, dst);
    vec_st(vec_perm(ਕਿਨਾਰੇ, v, align), 0, dst);
}
#ਨਹੀਂਤਾਂ
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_vsx_st(v, 0, dst);
}
#ਜੇ_ਅੰਤ


/**
 * loads vector known misalignment
 * @param perm_vec the align permute vector to combine the two loads from lvsl
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vec_unaligned_ਲੱਦੋ(b)  VEC_LD(0, b)

#ਜੇ HAVE_BIGENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_MERGEH(a, b) vec_mergeh(a, b)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_MERGEL(a, b) vec_mergel(a, b)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_MERGEH(a, b) vec_mergeh(b, a)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_MERGEL(a, b) vec_mergel(b, a)
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_BIGENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_ST(a,b,c) vec_st(a,b,c)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_ST(a,b,c) vec_vsx_st(a,b,c)
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_BIGENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_SPLAT16(a,b) vec_splat((vec_s16)(a), b)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_SPLAT16(a,b) vec_splat((vec_s16)(vec_perm(a, a, vcswapi2s(0,1,2,3))), b)
#ਜੇ_ਅੰਤ

#ਜੇ HAVE_BIGENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_SLD16(a,b,c) vec_sld(a, b, c)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ VEC_SLD16(a,b,c) vec_sld(b, a, c)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* HAVE_ALTIVEC */

#ਜੇ HAVE_VSX
#ਜੇ HAVE_BIGENDIAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_splat_u8(0),           \
                         (vec_u8)vec_vsx_ld((off), (p))))
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_vsx_ld((off), (p)),    \
                         (vec_u8)vec_splat_u8(0)))
#ਜੇ_ਅੰਤ /* HAVE_BIGENDIAN */
#ਜੇ_ਅੰਤ /* HAVE_VSX */

#ਜੇ_ਅੰਤ /* AVUTIL_PPC_UTIL_ALTIVEC_H */

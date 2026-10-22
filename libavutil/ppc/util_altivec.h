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

#నిర్వచితం_కాకపోతే AVUTIL_PPC_UTIL_ALTIVEC_H
#నిర్వచించు AVUTIL_PPC_UTIL_ALTIVEC_H

#అన్తర్భావ <stdint.h>

#అన్తర్భావ "config.h"

/***********************************************************************
 * Vector types
 **********************************************************************/
#నిర్వచించు vec_u8  సదిశ గుర్తులేని అక్షరం
#నిర్వచించు vec_s8  సదిశ గుర్తుగల అక్షరం
#నిర్వచించు vec_u16 సదిశ గుర్తులేని పొట్టి
#నిర్వచించు vec_s16 సదిశ గుర్తుగల పొట్టి
#నిర్వచించు vec_u32 సదిశ గుర్తులేని పూర్ణాంకం
#నిర్వచించు vec_s32 సదిశ గుర్తుగల పూర్ణాంకం
#నిర్వచించు vec_f   సదిశ దశాంశం

/***********************************************************************
 * Null vector
 **********************************************************************/
#నిర్వచించు ఎక్కించు_ZERO స్థిరరాశి vec_u8 zerov = vec_splat_u8( 0 )

#నిర్వచించు zero_u8v  (vec_u8)  zerov
#నిర్వచించు zero_s8v  (vec_s8)  zerov
#నిర్వచించు zero_u16v (vec_u16) zerov
#నిర్వచించు zero_s16v (vec_s16) zerov
#నిర్వచించు zero_u32v (vec_u32) zerov
#నిర్వచించు zero_s32v (vec_s32) zerov

#ఒకవేళ HAVE_ALTIVEC
#అన్తర్భావ <altivec.h>

// used to build registers permutation vectors (vcprm)
// the 's' are for words in the _s_econd vector
#నిర్వచించు మాట_0 0x00,0x01,0x02,0x03
#నిర్వచించు మాట_1 0x04,0x05,0x06,0x07
#నిర్వచించు మాట_2 0x08,0x09,0x0a,0x0b
#నిర్వచించు మాట_3 0x0c,0x0d,0x0e,0x0f
#నిర్వచించు మాట_s0 0x10,0x11,0x12,0x13
#నిర్వచించు మాట_s1 0x14,0x15,0x16,0x17
#నిర్వచించు మాట_s2 0x18,0x19,0x1a,0x1b
#నిర్వచించు మాట_s3 0x1c,0x1d,0x1e,0x1f
#నిర్వచించు vcprm(a,b,c,d) (స్థిరరాశి vec_u8){మాట ## a, మాట ## b, మాట ## c, మాట ## d}

#నిర్వచించు SWP_W2S0 0x02,0x03,0x00,0x01
#నిర్వచించు SWP_W2S1 0x06,0x07,0x04,0x05
#నిర్వచించు SWP_W2S2 0x0a,0x0b,0x08,0x09
#నిర్వచించు SWP_W2S3 0x0e,0x0f,0x0c,0x0d
#నిర్వచించు SWP_W2Ss0 0x12,0x13,0x10,0x11
#నిర్వచించు SWP_W2Ss1 0x16,0x17,0x14,0x15
#నిర్వచించు SWP_W2Ss2 0x1a,0x1b,0x18,0x19
#నిర్వచించు SWP_W2Ss3 0x1e,0x1f,0x1c,0x1d
#నిర్వచించు vcswapi2s(a,b,c,d) (స్థిరరాశి సదిశ గుర్తులేని అక్షరం){SWP_W2S ## a, SWP_W2S ## b, SWP_W2S ## c, SWP_W2S ## d}

#నిర్వచించు vcswapc() \
  (స్థిరరాశి సదిశ గుర్తులేని అక్షరం){0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}


// Transpose 8x8 matrix of 16-bit elements (in-place)
#నిర్వచించు TRANSPOSE8(a,b,c,d,e,f,g,h) \
చేయి { \
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
} అయితే (0)


#ఒకవేళ HAVE_BIGENDIAN
#నిర్వచించు VEC_LD(స్థానభ్రంశం,b)                                   \
    vec_perm(vec_ld(స్థానభ్రంశం, b), vec_ld((స్థానభ్రంశం)+15, b), vec_lvsl(స్థానభ్రంశం, b))
#లేకపోతే
#నిర్వచించు VEC_LD(స్థానభ్రంశం,b)                                   \
    vec_vsx_ld(స్థానభ్రంశం, b)
#అయితే_ముగింపు

/** @brief loads unaligned vector @a *src with offset @a offset
    and returns it */
#ఒకవేళ HAVE_BIGENDIAN
స్థిర అంతఃవరుస vec_u8 unaligned_ఎక్కించు(పూర్ణాంకం స్థానభ్రంశం, స్థిరరాశి uint8_t *src)
{
    నమోదు vec_u8 మొదటి = vec_ld(స్థానభ్రంశం, src);
    నమోదు vec_u8 రెండవ = vec_ld(స్థానభ్రంశం + 15, src);
    నమోదు vec_u8 ముసుగు_2 = vec_lvsl(స్థానభ్రంశం, src);
    తిరిగి vec_perm(మొదటి, రెండవ, ముసుగు_2);
}
స్థిర అంతఃవరుస vec_u8 ఎక్కించు_with_perm_vec(పూర్ణాంకం స్థానభ్రంశం, స్థిరరాశి uint8_t *src, vec_u8 perm_vec)
{
    vec_u8 a = vec_ld(స్థానభ్రంశం, src);
    vec_u8 b = vec_ld(స్థానభ్రంశం + 15, src);
    తిరిగి vec_perm(a, b, perm_vec);
}
#లేకపోతే
#నిర్వచించు unaligned_ఎక్కించు(a,b) VEC_LD(a,b)
#నిర్వచించు ఎక్కించు_with_perm_vec(a,b,c) VEC_LD(a,b)
#అయితే_ముగింపు

#ఒకవేళ HAVE_BIGENDIAN
స్థిర అంతఃవరుస శూన్య unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_u8 lo    = vec_ld(0, dst);
    vec_u8 hi    = vec_ld(15, dst);
    vec_u8 అంచులు = vec_perm(hi, lo, vec_lvsl(0, dst));
    vec_u8 align = vec_lvsr(0, dst);

    vec_st(vec_perm(v, అంచులు, align), 15, dst);
    vec_st(vec_perm(అంచులు, v, align), 0, dst);
}
#లేకపోతే
స్థిర అంతఃవరుస శూన్య unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_vsx_st(v, 0, dst);
}
#అయితే_ముగింపు


/**
 * loads vector known misalignment
 * @param perm_vec the align permute vector to combine the two loads from lvsl
 */

#నిర్వచించు vec_unaligned_ఎక్కించు(b)  VEC_LD(0, b)

#ఒకవేళ HAVE_BIGENDIAN
#నిర్వచించు VEC_MERGEH(a, b) vec_mergeh(a, b)
#నిర్వచించు VEC_MERGEL(a, b) vec_mergel(a, b)
#లేకపోతే
#నిర్వచించు VEC_MERGEH(a, b) vec_mergeh(b, a)
#నిర్వచించు VEC_MERGEL(a, b) vec_mergel(b, a)
#అయితే_ముగింపు

#ఒకవేళ HAVE_BIGENDIAN
#నిర్వచించు VEC_ST(a,b,c) vec_st(a,b,c)
#లేకపోతే
#నిర్వచించు VEC_ST(a,b,c) vec_vsx_st(a,b,c)
#అయితే_ముగింపు

#ఒకవేళ HAVE_BIGENDIAN
#నిర్వచించు VEC_SPLAT16(a,b) vec_splat((vec_s16)(a), b)
#లేకపోతే
#నిర్వచించు VEC_SPLAT16(a,b) vec_splat((vec_s16)(vec_perm(a, a, vcswapi2s(0,1,2,3))), b)
#అయితే_ముగింపు

#ఒకవేళ HAVE_BIGENDIAN
#నిర్వచించు VEC_SLD16(a,b,c) vec_sld(a, b, c)
#లేకపోతే
#నిర్వచించు VEC_SLD16(a,b,c) vec_sld(b, a, c)
#అయితే_ముగింపు

#అయితే_ముగింపు /* HAVE_ALTIVEC */

#ఒకవేళ HAVE_VSX
#ఒకవేళ HAVE_BIGENDIAN
#నిర్వచించు vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_splat_u8(0),           \
                         (vec_u8)vec_vsx_ld((off), (p))))
#లేకపోతే
#నిర్వచించు vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_vsx_ld((off), (p)),    \
                         (vec_u8)vec_splat_u8(0)))
#అయితే_ముగింపు /* HAVE_BIGENDIAN */
#అయితే_ముగింపు /* HAVE_VSX */

#అయితే_ముగింపు /* AVUTIL_PPC_UTIL_ALTIVEC_H */

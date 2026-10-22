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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_PPC_UTIL_ALTIVEC_H
#وصف_ڪريو AVUTIL_PPC_UTIL_ALTIVEC_H

#ضمن <stdint.h>

#ضمن "config.h"

/***********************************************************************
 * Vector types
 **********************************************************************/
#وصف_ڪريو vec_u8  ويڪٽر بنانشان حرف
#وصف_ڪريو vec_s8  ويڪٽر نشانوارو حرف
#وصف_ڪريو vec_u16 ويڪٽر بنانشان ننڍو
#وصف_ڪريو vec_s16 ويڪٽر نشانوارو ننڍو
#وصف_ڪريو vec_u32 ويڪٽر بنانشان صحيح
#وصف_ڪريو vec_s32 ويڪٽر نشانوارو صحيح
#وصف_ڪريو vec_f   ويڪٽر عائم

/***********************************************************************
 * Null vector
 **********************************************************************/
#وصف_ڪريو ڀريو_ZERO ثابت vec_u8 zerov = vec_splat_u8( 0 )

#وصف_ڪريو zero_u8v  (vec_u8)  zerov
#وصف_ڪريو zero_s8v  (vec_s8)  zerov
#وصف_ڪريو zero_u16v (vec_u16) zerov
#وصف_ڪريو zero_s16v (vec_s16) zerov
#وصف_ڪريو zero_u32v (vec_u32) zerov
#وصف_ڪريو zero_s32v (vec_s32) zerov

#إذا HAVE_ALTIVEC
#ضمن <altivec.h>

// used to build registers permutation vectors (vcprm)
// the 's' are for words in the _s_econd vector
#وصف_ڪريو لفظ_0 0x00,0x01,0x02,0x03
#وصف_ڪريو لفظ_1 0x04,0x05,0x06,0x07
#وصف_ڪريو لفظ_2 0x08,0x09,0x0a,0x0b
#وصف_ڪريو لفظ_3 0x0c,0x0d,0x0e,0x0f
#وصف_ڪريو لفظ_s0 0x10,0x11,0x12,0x13
#وصف_ڪريو لفظ_s1 0x14,0x15,0x16,0x17
#وصف_ڪريو لفظ_s2 0x18,0x19,0x1a,0x1b
#وصف_ڪريو لفظ_s3 0x1c,0x1d,0x1e,0x1f
#وصف_ڪريو vcprm(a,b,c,d) (ثابت vec_u8){لفظ ## a, لفظ ## b, لفظ ## c, لفظ ## d}

#وصف_ڪريو SWP_W2S0 0x02,0x03,0x00,0x01
#وصف_ڪريو SWP_W2S1 0x06,0x07,0x04,0x05
#وصف_ڪريو SWP_W2S2 0x0a,0x0b,0x08,0x09
#وصف_ڪريو SWP_W2S3 0x0e,0x0f,0x0c,0x0d
#وصف_ڪريو SWP_W2Ss0 0x12,0x13,0x10,0x11
#وصف_ڪريو SWP_W2Ss1 0x16,0x17,0x14,0x15
#وصف_ڪريو SWP_W2Ss2 0x1a,0x1b,0x18,0x19
#وصف_ڪريو SWP_W2Ss3 0x1e,0x1f,0x1c,0x1d
#وصف_ڪريو vcswapi2s(a,b,c,d) (ثابت ويڪٽر بنانشان حرف){SWP_W2S ## a, SWP_W2S ## b, SWP_W2S ## c, SWP_W2S ## d}

#وصف_ڪريو vcswapc() \
  (ثابت ويڪٽر بنانشان حرف){0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00}


// Transpose 8x8 matrix of 16-bit elements (in-place)
#وصف_ڪريو TRANSPOSE8(a,b,c,d,e,f,g,h) \
افعل { \
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
} طالما (0)


#إذا HAVE_BIGENDIAN
#وصف_ڪريو VEC_LD(وٿي,b)                                   \
    vec_perm(vec_ld(وٿي, b), vec_ld((وٿي)+15, b), vec_lvsl(وٿي, b))
#وإلا
#وصف_ڪريو VEC_LD(وٿي,b)                                   \
    vec_vsx_ld(وٿي, b)
#جيڪڏهن_پورو

/** @brief loads unaligned vector @a *src with offset @a offset
    and returns it */
#إذا HAVE_BIGENDIAN
ساكن مضمن vec_u8 unaligned_ڀريو(صحيح وٿي, ثابت uint8_t *src)
{
    سجل vec_u8 پهريون = vec_ld(وٿي, src);
    سجل vec_u8 ٻيو = vec_ld(وٿي + 15, src);
    سجل vec_u8 نقاب_2 = vec_lvsl(وٿي, src);
    أرجع vec_perm(پهريون, ٻيو, نقاب_2);
}
ساكن مضمن vec_u8 ڀريو_with_perm_vec(صحيح وٿي, ثابت uint8_t *src, vec_u8 perm_vec)
{
    vec_u8 a = vec_ld(وٿي, src);
    vec_u8 b = vec_ld(وٿي + 15, src);
    أرجع vec_perm(a, b, perm_vec);
}
#وإلا
#وصف_ڪريو unaligned_ڀريو(a,b) VEC_LD(a,b)
#وصف_ڪريو ڀريو_with_perm_vec(a,b,c) VEC_LD(a,b)
#جيڪڏهن_پورو

#إذا HAVE_BIGENDIAN
ساكن مضمن فراغ unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_u8 lo    = vec_ld(0, dst);
    vec_u8 hi    = vec_ld(15, dst);
    vec_u8 ڪنارا = vec_perm(hi, lo, vec_lvsl(0, dst));
    vec_u8 align = vec_lvsr(0, dst);

    vec_st(vec_perm(v, ڪنارا, align), 15, dst);
    vec_st(vec_perm(ڪنارا, v, align), 0, dst);
}
#وإلا
ساكن مضمن فراغ unaligned_store(vec_u8 v, uint8_t *dst)
{
    vec_vsx_st(v, 0, dst);
}
#جيڪڏهن_پورو


/**
 * loads vector known misalignment
 * @param perm_vec the align permute vector to combine the two loads from lvsl
 */

#وصف_ڪريو vec_unaligned_ڀريو(b)  VEC_LD(0, b)

#إذا HAVE_BIGENDIAN
#وصف_ڪريو VEC_MERGEH(a, b) vec_mergeh(a, b)
#وصف_ڪريو VEC_MERGEL(a, b) vec_mergel(a, b)
#وإلا
#وصف_ڪريو VEC_MERGEH(a, b) vec_mergeh(b, a)
#وصف_ڪريو VEC_MERGEL(a, b) vec_mergel(b, a)
#جيڪڏهن_پورو

#إذا HAVE_BIGENDIAN
#وصف_ڪريو VEC_ST(a,b,c) vec_st(a,b,c)
#وإلا
#وصف_ڪريو VEC_ST(a,b,c) vec_vsx_st(a,b,c)
#جيڪڏهن_پورو

#إذا HAVE_BIGENDIAN
#وصف_ڪريو VEC_SPLAT16(a,b) vec_splat((vec_s16)(a), b)
#وإلا
#وصف_ڪريو VEC_SPLAT16(a,b) vec_splat((vec_s16)(vec_perm(a, a, vcswapi2s(0,1,2,3))), b)
#جيڪڏهن_پورو

#إذا HAVE_BIGENDIAN
#وصف_ڪريو VEC_SLD16(a,b,c) vec_sld(a, b, c)
#وإلا
#وصف_ڪريو VEC_SLD16(a,b,c) vec_sld(b, a, c)
#جيڪڏهن_پورو

#جيڪڏهن_پورو /* HAVE_ALTIVEC */

#إذا HAVE_VSX
#إذا HAVE_BIGENDIAN
#وصف_ڪريو vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_splat_u8(0),           \
                         (vec_u8)vec_vsx_ld((off), (p))))
#وإلا
#وصف_ڪريو vsx_ld_u8_s16(off, p)                               \
    ((vec_s16)vec_mergeh((vec_u8)vec_vsx_ld((off), (p)),    \
                         (vec_u8)vec_splat_u8(0)))
#جيڪڏهن_پورو /* HAVE_BIGENDIAN */
#جيڪڏهن_پورو /* HAVE_VSX */

#جيڪڏهن_پورو /* AVUTIL_PPC_UTIL_ALTIVEC_H */

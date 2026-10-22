/*
 * Copyright (c) 2010 Mans Rullgard <mans@mansr.com>
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ARM_INTMATH_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ARM_INTMATH_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/attributes.h"

#ਜੇ HAVE_INLINE_ASM

#ਜੇ HAVE_ARMV6_INLINE

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clip_uint8 av_clip_uint8_arm
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_clip_uint8_arm(ਪੂਰਨ a)
{
    ਪੂਰਨ x;
    __asm__ ("usat %0, #8,  %1" : "=r"(x) : "r"(a));
    ਵਾਪਸ x;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clip_int8 av_clip_int8_arm
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_clip_int8_arm(ਪੂਰਨ a)
{
    ਪੂਰਨ x;
    __asm__ ("ssat %0, #8,  %1" : "=r"(x) : "r"(a));
    ਵਾਪਸ x;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clip_uint16 av_clip_uint16_arm
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_clip_uint16_arm(ਪੂਰਨ a)
{
    ਪੂਰਨ x;
    __asm__ ("usat %0, #16, %1" : "=r"(x) : "r"(a));
    ਵਾਪਸ x;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clip_int16 av_clip_int16_arm
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_clip_int16_arm(ਪੂਰਨ a)
{
    ਪੂਰਨ x;
    __asm__ ("ssat %0, #16, %1" : "=r"(x) : "r"(a));
    ਵਾਪਸ x;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clip_intp2 av_clip_intp2_arm
ਸਥਿਰ av_always_inline av_const ਪੂਰਨ av_clip_intp2_arm(ਪੂਰਨ a, ਪੂਰਨ p)
{
    ਜੇ (av_builtin_constant_p(p)) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ x;
        __asm__ ("ssat %0, %2, %1" : "=r"(x) : "r"(a), "i"(p+1));
        ਵਾਪਸ x;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (((ਬਿਨਾਨਿਸ਼ਾਨੀ)a + (1 << p)) & ~((2 << p) - 1))
            ਵਾਪਸ (a >> 31) ^ ((1 << p) - 1);
        ਨਹੀਂਤਾਂ
            ਵਾਪਸ a;
    }
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clip_uintp2 av_clip_uintp2_arm
ਸਥਿਰ av_always_inline av_const ਬਿਨਾਨਿਸ਼ਾਨੀ av_clip_uintp2_arm(ਪੂਰਨ a, ਪੂਰਨ p)
{
    ਜੇ (av_builtin_constant_p(p)) {
        ਬਿਨਾਨਿਸ਼ਾਨੀ x;
        __asm__ ("usat %0, %2, %1" : "=r"(x) : "r"(a), "i"(p));
        ਵਾਪਸ x;
    } ਨਹੀਂਤਾਂ {
        ਜੇ (a & ~((1<<p) - 1)) ਵਾਪਸ (~a) >> 31 & ((1<<p) - 1);
        ਨਹੀਂਤਾਂ                   ਵਾਪਸ  a;
    }
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_sat_add32 av_sat_add32_arm
ਸਥਿਰ av_always_inline ਪੂਰਨ av_sat_add32_arm(ਪੂਰਨ a, ਪੂਰਨ b)
{
    ਪੂਰਨ r;
    __asm__ ("qadd %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    ਵਾਪਸ r;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_sat_dadd32 av_sat_dadd32_arm
ਸਥਿਰ av_always_inline ਪੂਰਨ av_sat_dadd32_arm(ਪੂਰਨ a, ਪੂਰਨ b)
{
    ਪੂਰਨ r;
    __asm__ ("qdadd %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    ਵਾਪਸ r;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_sat_sub32 av_sat_sub32_arm
ਸਥਿਰ av_always_inline ਪੂਰਨ av_sat_sub32_arm(ਪੂਰਨ a, ਪੂਰਨ b)
{
    ਪੂਰਨ r;
    __asm__ ("qsub %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    ਵਾਪਸ r;
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_sat_dsub32 av_sat_dsub32_arm
ਸਥਿਰ av_always_inline ਪੂਰਨ av_sat_dsub32_arm(ਪੂਰਨ a, ਪੂਰਨ b)
{
    ਪੂਰਨ r;
    __asm__ ("qdsub %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    ਵਾਪਸ r;
}

#ਜੇ_ਅੰਤ /* HAVE_ARMV6_INLINE */

#ਜੇ HAVE_ASM_MOD_Q

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_clipl_int32 av_clipl_int32_arm
ਸਥਿਰ av_always_inline av_const int32_t av_clipl_int32_arm(int64_t a)
{
    ਪੂਰਨ x, y;
    __asm__ ("adds   %1, %R2, %Q2, lsr #31  \n\t"
             "itet   ne                     \n\t"
             "mvnne  %1, #1<<31             \n\t"
             "moveq  %0, %Q2                \n\t"
             "eorne  %0, %1,  %R2, asr #31  \n\t"
             : "=r"(x), "=&r"(y) : "r"(a) : "cc");
    ਵਾਪਸ x;
}

#ਜੇ_ਅੰਤ /* HAVE_ASM_MOD_Q */

#ਜੇ_ਅੰਤ /* HAVE_INLINE_ASM */

#ਜੇ_ਅੰਤ /* AVUTIL_ARM_INTMATH_H */

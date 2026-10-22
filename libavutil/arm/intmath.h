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

#ifndef AVUTIL_ARM_INTMATH_H
#define AVUTIL_ARM_INTMATH_H

#include <stdint.h>

#include "config.h"
#include "libavutil/attributes.h"

#ប្រសិនបើ HAVE_INLINE_ASM

#ប្រសិនបើ HAVE_ARMV6_INLINE

#define av_clip_uint8 av_clip_uint8_arm
static av_always_inline av_const ចំនួនគត់ av_clip_uint8_arm(ចំនួនគត់ a)
{
    ចំនួនគត់ x;
    __asm__ ("usat %0, #8,  %1" : "=r"(x) : "r"(a));
    ត្រឡប់ x;
}

#define av_clip_int8 av_clip_int8_arm
static av_always_inline av_const ចំនួនគត់ av_clip_int8_arm(ចំនួនគត់ a)
{
    ចំនួនគត់ x;
    __asm__ ("ssat %0, #8,  %1" : "=r"(x) : "r"(a));
    ត្រឡប់ x;
}

#define av_clip_uint16 av_clip_uint16_arm
static av_always_inline av_const ចំនួនគត់ av_clip_uint16_arm(ចំនួនគត់ a)
{
    ចំនួនគត់ x;
    __asm__ ("usat %0, #16, %1" : "=r"(x) : "r"(a));
    ត្រឡប់ x;
}

#define av_clip_int16 av_clip_int16_arm
static av_always_inline av_const ចំនួនគត់ av_clip_int16_arm(ចំនួនគត់ a)
{
    ចំនួនគត់ x;
    __asm__ ("ssat %0, #16, %1" : "=r"(x) : "r"(a));
    ត្រឡប់ x;
}

#define av_clip_intp2 av_clip_intp2_arm
static av_always_inline av_const ចំនួនគត់ av_clip_intp2_arm(ចំនួនគត់ a, ចំនួនគត់ p)
{
    ប្រសិនបើ (av_builtin_constant_p(p)) {
        unsigned x;
        __asm__ ("ssat %0, %2, %1" : "=r"(x) : "r"(a), "i"(p+1));
        ត្រឡប់ x;
    } បើមិនដូច្នេះ {
        ប្រសិនបើ (((unsigned)a + (1 << p)) & ~((2 << p) - 1))
            ត្រឡប់ (a >> 31) ^ ((1 << p) - 1);
        បើមិនដូច្នេះ
            ត្រឡប់ a;
    }
}

#define av_clip_uintp2 av_clip_uintp2_arm
static av_always_inline av_const unsigned av_clip_uintp2_arm(ចំនួនគត់ a, ចំនួនគត់ p)
{
    ប្រសិនបើ (av_builtin_constant_p(p)) {
        unsigned x;
        __asm__ ("usat %0, %2, %1" : "=r"(x) : "r"(a), "i"(p));
        ត្រឡប់ x;
    } បើមិនដូច្នេះ {
        ប្រសិនបើ (a & ~((1<<p) - 1)) ត្រឡប់ (~a) >> 31 & ((1<<p) - 1);
        បើមិនដូច្នេះ                   ត្រឡប់  a;
    }
}

#define av_sat_add32 av_sat_add32_arm
static av_always_inline ចំនួនគត់ av_sat_add32_arm(ចំនួនគត់ a, ចំនួនគត់ b)
{
    ចំនួនគត់ r;
    __asm__ ("qadd %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    ត្រឡប់ r;
}

#define av_sat_dadd32 av_sat_dadd32_arm
static av_always_inline ចំនួនគត់ av_sat_dadd32_arm(ចំនួនគត់ a, ចំនួនគត់ b)
{
    ចំនួនគត់ r;
    __asm__ ("qdadd %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    ត្រឡប់ r;
}

#define av_sat_sub32 av_sat_sub32_arm
static av_always_inline ចំនួនគត់ av_sat_sub32_arm(ចំនួនគត់ a, ចំនួនគត់ b)
{
    ចំនួនគត់ r;
    __asm__ ("qsub %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    ត្រឡប់ r;
}

#define av_sat_dsub32 av_sat_dsub32_arm
static av_always_inline ចំនួនគត់ av_sat_dsub32_arm(ចំនួនគត់ a, ចំនួនគត់ b)
{
    ចំនួនគត់ r;
    __asm__ ("qdsub %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    ត្រឡប់ r;
}

#endif /* HAVE_ARMV6_INLINE */

#ប្រសិនបើ HAVE_ASM_MOD_Q

#define av_clipl_int32 av_clipl_int32_arm
static av_always_inline av_const int32_t av_clipl_int32_arm(int64_t a)
{
    ចំនួនគត់ x, y;
    __asm__ ("adds   %1, %R2, %Q2, lsr #31  \n\t"
             "itet   ne                     \n\t"
             "mvnne  %1, #1<<31             \n\t"
             "moveq  %0, %Q2                \n\t"
             "eorne  %0, %1,  %R2, asr #31  \n\t"
             : "=r"(x), "=&r"(y) : "r"(a) : "cc");
    ត្រឡប់ x;
}

#endif /* HAVE_ASM_MOD_Q */

#endif /* HAVE_INLINE_ASM */

#endif /* AVUTIL_ARM_INTMATH_H */

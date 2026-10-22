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

#اگر_غیر_تعریف_شدہ AVUTIL_ARM_INTMATH_H
#تعریف_کرو AVUTIL_ARM_INTMATH_H

#شامل <stdint.h>

#شامل "config.h"
#شامل "libavutil/attributes.h"

#اگر HAVE_INLINE_ASM

#اگر HAVE_ARMV6_INLINE

#تعریف_کرو av_clip_uint8 av_clip_uint8_arm
ساکن av_always_inline av_const صحیح av_clip_uint8_arm(صحیح a)
{
    صحیح x;
    __asm__ ("usat %0, #8,  %1" : "=r"(x) : "r"(a));
    واپس x;
}

#تعریف_کرو av_clip_int8 av_clip_int8_arm
ساکن av_always_inline av_const صحیح av_clip_int8_arm(صحیح a)
{
    صحیح x;
    __asm__ ("ssat %0, #8,  %1" : "=r"(x) : "r"(a));
    واپس x;
}

#تعریف_کرو av_clip_uint16 av_clip_uint16_arm
ساکن av_always_inline av_const صحیح av_clip_uint16_arm(صحیح a)
{
    صحیح x;
    __asm__ ("usat %0, #16, %1" : "=r"(x) : "r"(a));
    واپس x;
}

#تعریف_کرو av_clip_int16 av_clip_int16_arm
ساکن av_always_inline av_const صحیح av_clip_int16_arm(صحیح a)
{
    صحیح x;
    __asm__ ("ssat %0, #16, %1" : "=r"(x) : "r"(a));
    واپس x;
}

#تعریف_کرو av_clip_intp2 av_clip_intp2_arm
ساکن av_always_inline av_const صحیح av_clip_intp2_arm(صحیح a, صحیح p)
{
    اگر (av_builtin_constant_p(p)) {
        غیرعلامتی x;
        __asm__ ("ssat %0, %2, %1" : "=r"(x) : "r"(a), "i"(p+1));
        واپس x;
    } ورنہ {
        اگر (((غیرعلامتی)a + (1 << p)) & ~((2 << p) - 1))
            واپس (a >> 31) ^ ((1 << p) - 1);
        ورنہ
            واپس a;
    }
}

#تعریف_کرو av_clip_uintp2 av_clip_uintp2_arm
ساکن av_always_inline av_const غیرعلامتی av_clip_uintp2_arm(صحیح a, صحیح p)
{
    اگر (av_builtin_constant_p(p)) {
        غیرعلامتی x;
        __asm__ ("usat %0, %2, %1" : "=r"(x) : "r"(a), "i"(p));
        واپس x;
    } ورنہ {
        اگر (a & ~((1<<p) - 1)) واپس (~a) >> 31 & ((1<<p) - 1);
        ورنہ                   واپس  a;
    }
}

#تعریف_کرو av_sat_add32 av_sat_add32_arm
ساکن av_always_inline صحیح av_sat_add32_arm(صحیح a, صحیح b)
{
    صحیح r;
    __asm__ ("qadd %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    واپس r;
}

#تعریف_کرو av_sat_dadd32 av_sat_dadd32_arm
ساکن av_always_inline صحیح av_sat_dadd32_arm(صحیح a, صحیح b)
{
    صحیح r;
    __asm__ ("qdadd %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    واپس r;
}

#تعریف_کرو av_sat_sub32 av_sat_sub32_arm
ساکن av_always_inline صحیح av_sat_sub32_arm(صحیح a, صحیح b)
{
    صحیح r;
    __asm__ ("qsub %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    واپس r;
}

#تعریف_کرو av_sat_dsub32 av_sat_dsub32_arm
ساکن av_always_inline صحیح av_sat_dsub32_arm(صحیح a, صحیح b)
{
    صحیح r;
    __asm__ ("qdsub %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    واپس r;
}

#اگر_ختم /* HAVE_ARMV6_INLINE */

#اگر HAVE_ASM_MOD_Q

#تعریف_کرو av_clipl_int32 av_clipl_int32_arm
ساکن av_always_inline av_const int32_t av_clipl_int32_arm(int64_t a)
{
    صحیح x, y;
    __asm__ ("adds   %1, %R2, %Q2, lsr #31  \n\t"
             "itet   ne                     \n\t"
             "mvnne  %1, #1<<31             \n\t"
             "moveq  %0, %Q2                \n\t"
             "eorne  %0, %1,  %R2, asr #31  \n\t"
             : "=r"(x), "=&r"(y) : "r"(a) : "cc");
    واپس x;
}

#اگر_ختم /* HAVE_ASM_MOD_Q */

#اگر_ختم /* HAVE_INLINE_ASM */

#اگر_ختم /* AVUTIL_ARM_INTMATH_H */

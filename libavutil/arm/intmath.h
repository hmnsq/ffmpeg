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

#నిర్వచితం_కాకపోతే AVUTIL_ARM_INTMATH_H
#నిర్వచించు AVUTIL_ARM_INTMATH_H

#అన్తర్భావ <stdint.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "libavutil/attributes.h"

#ఒకవేళ HAVE_INLINE_ASM

#ఒకవేళ HAVE_ARMV6_INLINE

#నిర్వచించు av_clip_uint8 av_clip_uint8_arm
స్థిర av_always_inline av_const పూర్ణాంకం av_clip_uint8_arm(పూర్ణాంకం a)
{
    పూర్ణాంకం x;
    __asm__ ("usat %0, #8,  %1" : "=r"(x) : "r"(a));
    తిరిగి x;
}

#నిర్వచించు av_clip_int8 av_clip_int8_arm
స్థిర av_always_inline av_const పూర్ణాంకం av_clip_int8_arm(పూర్ణాంకం a)
{
    పూర్ణాంకం x;
    __asm__ ("ssat %0, #8,  %1" : "=r"(x) : "r"(a));
    తిరిగి x;
}

#నిర్వచించు av_clip_uint16 av_clip_uint16_arm
స్థిర av_always_inline av_const పూర్ణాంకం av_clip_uint16_arm(పూర్ణాంకం a)
{
    పూర్ణాంకం x;
    __asm__ ("usat %0, #16, %1" : "=r"(x) : "r"(a));
    తిరిగి x;
}

#నిర్వచించు av_clip_int16 av_clip_int16_arm
స్థిర av_always_inline av_const పూర్ణాంకం av_clip_int16_arm(పూర్ణాంకం a)
{
    పూర్ణాంకం x;
    __asm__ ("ssat %0, #16, %1" : "=r"(x) : "r"(a));
    తిరిగి x;
}

#నిర్వచించు av_clip_intp2 av_clip_intp2_arm
స్థిర av_always_inline av_const పూర్ణాంకం av_clip_intp2_arm(పూర్ణాంకం a, పూర్ణాంకం p)
{
    ఒకవేళ (av_builtin_constant_p(p)) {
        గుర్తులేని x;
        __asm__ ("ssat %0, %2, %1" : "=r"(x) : "r"(a), "i"(p+1));
        తిరిగి x;
    } లేకపోతే {
        ఒకవేళ (((గుర్తులేని)a + (1 << p)) & ~((2 << p) - 1))
            తిరిగి (a >> 31) ^ ((1 << p) - 1);
        లేకపోతే
            తిరిగి a;
    }
}

#నిర్వచించు av_clip_uintp2 av_clip_uintp2_arm
స్థిర av_always_inline av_const గుర్తులేని av_clip_uintp2_arm(పూర్ణాంకం a, పూర్ణాంకం p)
{
    ఒకవేళ (av_builtin_constant_p(p)) {
        గుర్తులేని x;
        __asm__ ("usat %0, %2, %1" : "=r"(x) : "r"(a), "i"(p));
        తిరిగి x;
    } లేకపోతే {
        ఒకవేళ (a & ~((1<<p) - 1)) తిరిగి (~a) >> 31 & ((1<<p) - 1);
        లేకపోతే                   తిరిగి  a;
    }
}

#నిర్వచించు av_sat_add32 av_sat_add32_arm
స్థిర av_always_inline పూర్ణాంకం av_sat_add32_arm(పూర్ణాంకం a, పూర్ణాంకం b)
{
    పూర్ణాంకం r;
    __asm__ ("qadd %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    తిరిగి r;
}

#నిర్వచించు av_sat_dadd32 av_sat_dadd32_arm
స్థిర av_always_inline పూర్ణాంకం av_sat_dadd32_arm(పూర్ణాంకం a, పూర్ణాంకం b)
{
    పూర్ణాంకం r;
    __asm__ ("qdadd %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    తిరిగి r;
}

#నిర్వచించు av_sat_sub32 av_sat_sub32_arm
స్థిర av_always_inline పూర్ణాంకం av_sat_sub32_arm(పూర్ణాంకం a, పూర్ణాంకం b)
{
    పూర్ణాంకం r;
    __asm__ ("qsub %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    తిరిగి r;
}

#నిర్వచించు av_sat_dsub32 av_sat_dsub32_arm
స్థిర av_always_inline పూర్ణాంకం av_sat_dsub32_arm(పూర్ణాంకం a, పూర్ణాంకం b)
{
    పూర్ణాంకం r;
    __asm__ ("qdsub %0, %1, %2" : "=r"(r) : "r"(a), "r"(b));
    తిరిగి r;
}

#అయితే_ముగింపు /* HAVE_ARMV6_INLINE */

#ఒకవేళ HAVE_ASM_MOD_Q

#నిర్వచించు av_clipl_int32 av_clipl_int32_arm
స్థిర av_always_inline av_const int32_t av_clipl_int32_arm(int64_t a)
{
    పూర్ణాంకం x, y;
    __asm__ ("adds   %1, %R2, %Q2, lsr #31  \n\t"
             "itet   ne                     \n\t"
             "mvnne  %1, #1<<31             \n\t"
             "moveq  %0, %Q2                \n\t"
             "eorne  %0, %1,  %R2, asr #31  \n\t"
             : "=r"(x), "=&r"(y) : "r"(a) : "cc");
    తిరిగి x;
}

#అయితే_ముగింపు /* HAVE_ASM_MOD_Q */

#అయితే_ముగింపు /* HAVE_INLINE_ASM */

#అయితే_ముగింపు /* AVUTIL_ARM_INTMATH_H */

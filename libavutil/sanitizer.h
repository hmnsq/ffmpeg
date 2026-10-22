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

#నిర్వచితం_కాకపోతే AVUTIL_SANITIZER_H
#నిర్వచించు AVUTIL_SANITIZER_H

#అన్తర్భావ "config.h"

#ఒకవేళ defined(__has_feature)
#ఒకవేళ __has_feature(చిరునామా_sanitizer)
#నిర్వచించు HAVE_ASAN 1
#అయితే_ముగింపు
#ఒకవేళ __has_feature(జ్ఞాపకం_sanitizer)
#నిర్వచించు HAVE_MSAN 1
#అయితే_ముగింపు
#ఒకవేళ __has_feature(undefined_behavior_sanitizer)
#నిర్వచించు HAVE_UBSAN 1
#అయితే_ముగింపు
#అయితే_ముగింపు
#ఒకవేళ defined(__SANITIZE_ADDRESS__)
#నిర్వచనం_రద్దు  HAVE_ASAN
#నిర్వచించు HAVE_ASAN 1
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే HAVE_ASAN
#నిర్వచించు HAVE_ASAN 0
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే HAVE_MSAN
#నిర్వచించు HAVE_MSAN 0
#అయితే_ముగింపు
#నిర్వచితం_కాకపోతే HAVE_UBSAN
#నిర్వచించు HAVE_UBSAN 0
#అయితే_ముగింపు

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#ఒకవేళ HAVE_ASAN
#అన్తర్భావ <sanitizer/asan_interface.h>
#నిర్వచించు FF_ASAN_POISON(ptr, కొలత)   __asan_poison_memory_region(ptr, కొలత)
#నిర్వచించు FF_ASAN_UNPOISON(ptr, కొలత) __asan_unpoison_memory_region(ptr, కొలత)
#లేకపోతే
#నిర్వచించు FF_ASAN_POISON(ptr, కొలత)   ((శూన్య)(ptr), (శూన్య)(కొలత))
#నిర్వచించు FF_ASAN_UNPOISON(ptr, కొలత) ((శూన్య)(ptr), (శూన్య)(కొలత))
#అయితే_ముగింపు

/* Mark memory as uninitialized. */
#ఒకవేళ HAVE_MSAN
#అన్తర్భావ <sanitizer/msan_interface.h>
#నిర్వచించు FF_MEM_UNDEFINED(ptr, కొలత) __msan_allocated_memory(ptr, కొలత)
#లేదావేళ CONFIG_జ్ఞాపకం_POISONING && HAVE_VALGRIND_MEMCHECK_H
#అన్తర్భావ <valgrind/memcheck.h>
#నిర్వచించు FF_MEM_UNDEFINED(ptr, కొలత) VALGRIND_MAKE_MEM_UNDEFINED(ptr, కొలత)
#లేకపోతే
#నిర్వచించు FF_MEM_UNDEFINED(ptr, కొలత) ((శూన్య)(ptr), (శూన్య)(కొలత))
#అయితే_ముగింపు

#అయితే_ముగింపు /* AVUTIL_SANITIZER_H */

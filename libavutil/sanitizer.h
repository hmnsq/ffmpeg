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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_SANITIZER_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_SANITIZER_H

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਜੇ defined(__has_feature)
#ਜੇ __has_feature(ਪਤਾ_sanitizer)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HAVE_ASAN 1
#ਜੇ_ਅੰਤ
#ਜੇ __has_feature(ਸਮ੍ਰਿਤੀ_sanitizer)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HAVE_MSAN 1
#ਜੇ_ਅੰਤ
#ਜੇ __has_feature(undefined_behavior_sanitizer)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HAVE_UBSAN 1
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
#ਜੇ defined(__SANITIZE_ADDRESS__)
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ  HAVE_ASAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HAVE_ASAN 1
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HAVE_ASAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HAVE_ASAN 0
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HAVE_MSAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HAVE_MSAN 0
#ਜੇ_ਅੰਤ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ HAVE_UBSAN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ HAVE_UBSAN 0
#ਜੇ_ਅੰਤ

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#ਜੇ HAVE_ASAN
#ਅਨ੍ਤਰ੍ਭਾਵ <sanitizer/asan_interface.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ASAN_POISON(ptr, ਮਾਪ)   __asan_poison_memory_region(ptr, ਮਾਪ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ASAN_UNPOISON(ptr, ਮਾਪ) __asan_unpoison_memory_region(ptr, ਮਾਪ)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ASAN_POISON(ptr, ਮਾਪ)   ((ਖਾਲੀ)(ptr), (ਖਾਲੀ)(ਮਾਪ))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ASAN_UNPOISON(ptr, ਮਾਪ) ((ਖਾਲੀ)(ptr), (ਖਾਲੀ)(ਮਾਪ))
#ਜੇ_ਅੰਤ

/* Mark memory as uninitialized. */
#ਜੇ HAVE_MSAN
#ਅਨ੍ਤਰ੍ਭਾਵ <sanitizer/msan_interface.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_MEM_UNDEFINED(ptr, ਮਾਪ) __msan_allocated_memory(ptr, ਮਾਪ)
#ਜਾਂਜੇ CONFIG_ਸਮ੍ਰਿਤੀ_POISONING && HAVE_VALGRIND_MEMCHECK_H
#ਅਨ੍ਤਰ੍ਭਾਵ <valgrind/memcheck.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_MEM_UNDEFINED(ptr, ਮਾਪ) VALGRIND_MAKE_MEM_UNDEFINED(ptr, ਮਾਪ)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_MEM_UNDEFINED(ptr, ਮਾਪ) ((ਖਾਲੀ)(ptr), (ਖਾਲੀ)(ਮਾਪ))
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ /* AVUTIL_SANITIZER_H */

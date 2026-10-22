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

#اگر_غیر_تعریف_شدہ AVUTIL_SANITIZER_H
#تعریف_کرو AVUTIL_SANITIZER_H

#شامل "config.h"

#اگر defined(__has_feature)
#اگر __has_feature(پتہ_sanitizer)
#تعریف_کرو HAVE_ASAN 1
#اگر_ختم
#اگر __has_feature(حافظہ_sanitizer)
#تعریف_کرو HAVE_MSAN 1
#اگر_ختم
#اگر __has_feature(undefined_behavior_sanitizer)
#تعریف_کرو HAVE_UBSAN 1
#اگر_ختم
#اگر_ختم
#اگر defined(__SANITIZE_ADDRESS__)
#تعریف_منسوخ  HAVE_ASAN
#تعریف_کرو HAVE_ASAN 1
#اگر_ختم
#اگر_غیر_تعریف_شدہ HAVE_ASAN
#تعریف_کرو HAVE_ASAN 0
#اگر_ختم
#اگر_غیر_تعریف_شدہ HAVE_MSAN
#تعریف_کرو HAVE_MSAN 0
#اگر_ختم
#اگر_غیر_تعریف_شدہ HAVE_UBSAN
#تعریف_کرو HAVE_UBSAN 0
#اگر_ختم

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#اگر HAVE_ASAN
#شامل <sanitizer/asan_interface.h>
#تعریف_کرو FF_ASAN_POISON(ptr, سائز)   __asan_poison_memory_region(ptr, سائز)
#تعریف_کرو FF_ASAN_UNPOISON(ptr, سائز) __asan_unpoison_memory_region(ptr, سائز)
#ورنہ
#تعریف_کرو FF_ASAN_POISON(ptr, سائز)   ((خالی)(ptr), (خالی)(سائز))
#تعریف_کرو FF_ASAN_UNPOISON(ptr, سائز) ((خالی)(ptr), (خالی)(سائز))
#اگر_ختم

/* Mark memory as uninitialized. */
#اگر HAVE_MSAN
#شامل <sanitizer/msan_interface.h>
#تعریف_کرو FF_MEM_UNDEFINED(ptr, سائز) __msan_allocated_memory(ptr, سائز)
#وگرنہ_اگر CONFIG_حافظہ_POISONING && HAVE_VALGRIND_MEMCHECK_H
#شامل <valgrind/memcheck.h>
#تعریف_کرو FF_MEM_UNDEFINED(ptr, سائز) VALGRIND_MAKE_MEM_UNDEFINED(ptr, سائز)
#ورنہ
#تعریف_کرو FF_MEM_UNDEFINED(ptr, سائز) ((خالی)(ptr), (خالی)(سائز))
#اگر_ختم

#اگر_ختم /* AVUTIL_SANITIZER_H */

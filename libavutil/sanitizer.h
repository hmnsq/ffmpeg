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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_SANITIZER_H
#وصف_ڪريو AVUTIL_SANITIZER_H

#ضمن "config.h"

#إذا defined(__has_feature)
#إذا __has_feature(پتو_sanitizer)
#وصف_ڪريو HAVE_ASAN 1
#جيڪڏهن_پورو
#إذا __has_feature(يادگيري_sanitizer)
#وصف_ڪريو HAVE_MSAN 1
#جيڪڏهن_پورو
#إذا __has_feature(undefined_behavior_sanitizer)
#وصف_ڪريو HAVE_UBSAN 1
#جيڪڏهن_پورو
#جيڪڏهن_پورو
#إذا defined(__SANITIZE_ADDRESS__)
#وصف_رد  HAVE_ASAN
#وصف_ڪريو HAVE_ASAN 1
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل HAVE_ASAN
#وصف_ڪريو HAVE_ASAN 0
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل HAVE_MSAN
#وصف_ڪريو HAVE_MSAN 0
#جيڪڏهن_پورو
#جيڪڏهن_وصف_نه_ٿيل HAVE_UBSAN
#وصف_ڪريو HAVE_UBSAN 0
#جيڪڏهن_پورو

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#إذا HAVE_ASAN
#ضمن <sanitizer/asan_interface.h>
#وصف_ڪريو FF_ASAN_POISON(ptr, سائيز)   __asan_poison_memory_region(ptr, سائيز)
#وصف_ڪريو FF_ASAN_UNPOISON(ptr, سائيز) __asan_unpoison_memory_region(ptr, سائيز)
#وإلا
#وصف_ڪريو FF_ASAN_POISON(ptr, سائيز)   ((فراغ)(ptr), (فراغ)(سائيز))
#وصف_ڪريو FF_ASAN_UNPOISON(ptr, سائيز) ((فراغ)(ptr), (فراغ)(سائيز))
#جيڪڏهن_پورو

/* Mark memory as uninitialized. */
#إذا HAVE_MSAN
#ضمن <sanitizer/msan_interface.h>
#وصف_ڪريو FF_MEM_UNDEFINED(ptr, سائيز) __msan_allocated_memory(ptr, سائيز)
#وإلاإذا CONFIG_يادگيري_POISONING && HAVE_VALGRIND_MEMCHECK_H
#ضمن <valgrind/memcheck.h>
#وصف_ڪريو FF_MEM_UNDEFINED(ptr, سائيز) VALGRIND_MAKE_MEM_UNDEFINED(ptr, سائيز)
#وإلا
#وصف_ڪريو FF_MEM_UNDEFINED(ptr, سائيز) ((فراغ)(ptr), (فراغ)(سائيز))
#جيڪڏهن_پورو

#جيڪڏهن_پورو /* AVUTIL_SANITIZER_H */

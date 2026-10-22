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

#اگر_تعریف_نشده AVUTIL_SANITIZER_H
#تعریف_کن AVUTIL_SANITIZER_H

#ضمن "config.h"

#إذا defined(__has_feature)
#إذا __has_feature(آدرس_sanitizer)
#تعریف_کن HAVE_ASAN 1
#پایان_اگر
#إذا __has_feature(حافظه_sanitizer)
#تعریف_کن HAVE_MSAN 1
#پایان_اگر
#إذا __has_feature(undefined_behavior_sanitizer)
#تعریف_کن HAVE_UBSAN 1
#پایان_اگر
#پایان_اگر
#إذا defined(__SANITIZE_ADDRESS__)
#لغو_تعریف  HAVE_ASAN
#تعریف_کن HAVE_ASAN 1
#پایان_اگر
#اگر_تعریف_نشده HAVE_ASAN
#تعریف_کن HAVE_ASAN 0
#پایان_اگر
#اگر_تعریف_نشده HAVE_MSAN
#تعریف_کن HAVE_MSAN 0
#پایان_اگر
#اگر_تعریف_نشده HAVE_UBSAN
#تعریف_کن HAVE_UBSAN 0
#پایان_اگر

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#إذا HAVE_ASAN
#ضمن <sanitizer/asan_interface.h>
#تعریف_کن FF_ASAN_POISON(ptr, اندازه)   __asan_poison_memory_region(ptr, اندازه)
#تعریف_کن FF_ASAN_UNPOISON(ptr, اندازه) __asan_unpoison_memory_region(ptr, اندازه)
#وإلا
#تعریف_کن FF_ASAN_POISON(ptr, اندازه)   ((فراغ)(ptr), (فراغ)(اندازه))
#تعریف_کن FF_ASAN_UNPOISON(ptr, اندازه) ((فراغ)(ptr), (فراغ)(اندازه))
#پایان_اگر

/* Mark memory as uninitialized. */
#إذا HAVE_MSAN
#ضمن <sanitizer/msan_interface.h>
#تعریف_کن FF_MEM_UNDEFINED(ptr, اندازه) __msan_allocated_memory(ptr, اندازه)
#وإلاإذا CONFIG_حافظه_POISONING && HAVE_VALGRIND_MEMCHECK_H
#ضمن <valgrind/memcheck.h>
#تعریف_کن FF_MEM_UNDEFINED(ptr, اندازه) VALGRIND_MAKE_MEM_UNDEFINED(ptr, اندازه)
#وإلا
#تعریف_کن FF_MEM_UNDEFINED(ptr, اندازه) ((فراغ)(ptr), (فراغ)(اندازه))
#پایان_اگر

#پایان_اگر /* AVUTIL_SANITIZER_H */

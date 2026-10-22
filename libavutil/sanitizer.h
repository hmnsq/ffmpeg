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

#که_نه_تعریف_شوی AVUTIL_SANITIZER_H
#تعریف_کړه AVUTIL_SANITIZER_H

#ضمن "config.h"

#إذا defined(__has_feature)
#إذا __has_feature(پته_sanitizer)
#تعریف_کړه HAVE_ASAN 1
#د_که_پای
#إذا __has_feature(حافظه_sanitizer)
#تعریف_کړه HAVE_MSAN 1
#د_که_پای
#إذا __has_feature(undefined_behavior_sanitizer)
#تعریف_کړه HAVE_UBSAN 1
#د_که_پای
#د_که_پای
#إذا defined(__SANITIZE_ADDRESS__)
#تعریف_لغوه  HAVE_ASAN
#تعریف_کړه HAVE_ASAN 1
#د_که_پای
#که_نه_تعریف_شوی HAVE_ASAN
#تعریف_کړه HAVE_ASAN 0
#د_که_پای
#که_نه_تعریف_شوی HAVE_MSAN
#تعریف_کړه HAVE_MSAN 0
#د_که_پای
#که_نه_تعریف_شوی HAVE_UBSAN
#تعریف_کړه HAVE_UBSAN 0
#د_که_پای

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#إذا HAVE_ASAN
#ضمن <sanitizer/asan_interface.h>
#تعریف_کړه FF_ASAN_POISON(ptr, اندازه)   __asan_poison_memory_region(ptr, اندازه)
#تعریف_کړه FF_ASAN_UNPOISON(ptr, اندازه) __asan_unpoison_memory_region(ptr, اندازه)
#وإلا
#تعریف_کړه FF_ASAN_POISON(ptr, اندازه)   ((فراغ)(ptr), (فراغ)(اندازه))
#تعریف_کړه FF_ASAN_UNPOISON(ptr, اندازه) ((فراغ)(ptr), (فراغ)(اندازه))
#د_که_پای

/* Mark memory as uninitialized. */
#إذا HAVE_MSAN
#ضمن <sanitizer/msan_interface.h>
#تعریف_کړه FF_MEM_UNDEFINED(ptr, اندازه) __msan_allocated_memory(ptr, اندازه)
#وإلاإذا CONFIG_حافظه_POISONING && HAVE_VALGRIND_MEMCHECK_H
#ضمن <valgrind/memcheck.h>
#تعریف_کړه FF_MEM_UNDEFINED(ptr, اندازه) VALGRIND_MAKE_MEM_UNDEFINED(ptr, اندازه)
#وإلا
#تعریف_کړه FF_MEM_UNDEFINED(ptr, اندازه) ((فراغ)(ptr), (فراغ)(اندازه))
#د_که_پای

#د_که_پای /* AVUTIL_SANITIZER_H */

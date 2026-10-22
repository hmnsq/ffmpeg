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

#جے_بنا_تعریف AVUTIL_SANITIZER_H
#تعریف_کرو AVUTIL_SANITIZER_H

#ضمن "config.h"

#إذا defined(__has_feature)
#إذا __has_feature(پتہ_sanitizer)
#تعریف_کرو HAVE_ASAN 1
#جے_انت
#إذا __has_feature(حافظہ_sanitizer)
#تعریف_کرو HAVE_MSAN 1
#جے_انت
#إذا __has_feature(undefined_behavior_sanitizer)
#تعریف_کرو HAVE_UBSAN 1
#جے_انت
#جے_انت
#إذا defined(__SANITIZE_ADDRESS__)
#تعریف_رد  HAVE_ASAN
#تعریف_کرو HAVE_ASAN 1
#جے_انت
#جے_بنا_تعریف HAVE_ASAN
#تعریف_کرو HAVE_ASAN 0
#جے_انت
#جے_بنا_تعریف HAVE_MSAN
#تعریف_کرو HAVE_MSAN 0
#جے_انت
#جے_بنا_تعریف HAVE_UBSAN
#تعریف_کرو HAVE_UBSAN 0
#جے_انت

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#إذا HAVE_ASAN
#ضمن <sanitizer/asan_interface.h>
#تعریف_کرو FF_ASAN_POISON(ptr, ناپ)   __asan_poison_memory_region(ptr, ناپ)
#تعریف_کرو FF_ASAN_UNPOISON(ptr, ناپ) __asan_unpoison_memory_region(ptr, ناپ)
#وإلا
#تعریف_کرو FF_ASAN_POISON(ptr, ناپ)   ((فراغ)(ptr), (فراغ)(ناپ))
#تعریف_کرو FF_ASAN_UNPOISON(ptr, ناپ) ((فراغ)(ptr), (فراغ)(ناپ))
#جے_انت

/* Mark memory as uninitialized. */
#إذا HAVE_MSAN
#ضمن <sanitizer/msan_interface.h>
#تعریف_کرو FF_MEM_UNDEFINED(ptr, ناپ) __msan_allocated_memory(ptr, ناپ)
#وإلاإذا CONFIG_حافظہ_POISONING && HAVE_VALGRIND_MEMCHECK_H
#ضمن <valgrind/memcheck.h>
#تعریف_کرو FF_MEM_UNDEFINED(ptr, ناپ) VALGRIND_MAKE_MEM_UNDEFINED(ptr, ناپ)
#وإلا
#تعریف_کرو FF_MEM_UNDEFINED(ptr, ناپ) ((فراغ)(ptr), (فراغ)(ناپ))
#جے_انت

#جے_انت /* AVUTIL_SANITIZER_H */

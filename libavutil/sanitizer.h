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

#यदि_अपरिभाषितम् AVUTIL_SANITIZER_H
#परिभाषय AVUTIL_SANITIZER_H

#अन्तर्भाव "config.h"

#यदि defined(__has_feature)
#यदि __has_feature(स्थानाङ्कः_sanitizer)
#परिभाषय HAVE_ASAN 1
#यदि_अन्तः
#यदि __has_feature(स्मृतिः_sanitizer)
#परिभाषय HAVE_MSAN 1
#यदि_अन्तः
#यदि __has_feature(undefined_behavior_sanitizer)
#परिभाषय HAVE_UBSAN 1
#यदि_अन्तः
#यदि_अन्तः
#यदि defined(__SANITIZE_ADDRESS__)
#अपरिभाषय  HAVE_ASAN
#परिभाषय HAVE_ASAN 1
#यदि_अन्तः
#यदि_अपरिभाषितम् HAVE_ASAN
#परिभाषय HAVE_ASAN 0
#यदि_अन्तः
#यदि_अपरिभाषितम् HAVE_MSAN
#परिभाषय HAVE_MSAN 0
#यदि_अन्तः
#यदि_अपरिभाषितम् HAVE_UBSAN
#परिभाषय HAVE_UBSAN 0
#यदि_अन्तः

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#यदि HAVE_ASAN
#अन्तर्भाव <sanitizer/asan_interface.h>
#परिभाषय FF_ASAN_POISON(ptr, आकार)   __asan_poison_memory_region(ptr, आकार)
#परिभाषय FF_ASAN_UNPOISON(ptr, आकार) __asan_unpoison_memory_region(ptr, आकार)
#अन्यथा
#परिभाषय FF_ASAN_POISON(ptr, आकार)   ((शून्य)(ptr), (शून्य)(आकार))
#परिभाषय FF_ASAN_UNPOISON(ptr, आकार) ((शून्य)(ptr), (शून्य)(आकार))
#यदि_अन्तः

/* Mark memory as uninitialized. */
#यदि HAVE_MSAN
#अन्तर्भाव <sanitizer/msan_interface.h>
#परिभाषय FF_MEM_UNDEFINED(ptr, आकार) __msan_allocated_memory(ptr, आकार)
#नोचेद्यदि CONFIG_स्मृतिः_POISONING && HAVE_VALGRIND_MEMCHECK_H
#अन्तर्भाव <valgrind/memcheck.h>
#परिभाषय FF_MEM_UNDEFINED(ptr, आकार) VALGRIND_MAKE_MEM_UNDEFINED(ptr, आकार)
#अन्यथा
#परिभाषय FF_MEM_UNDEFINED(ptr, आकार) ((शून्य)(ptr), (शून्य)(आकार))
#यदि_अन्तः

#यदि_अन्तः /* AVUTIL_SANITIZER_H */

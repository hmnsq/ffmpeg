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

#ifndef AVUTIL_SANITIZER_H
#define AVUTIL_SANITIZER_H

#ضمن "config.h"

#ܐܢ defined(__has_feature)
#ܐܢ __has_feature(address_sanitizer)
#define HAVE_ASAN 1
#endif
#ܐܢ __has_feature(memory_sanitizer)
#define HAVE_MSAN 1
#endif
#ܐܢ __has_feature(undefined_behavior_sanitizer)
#define HAVE_UBSAN 1
#endif
#endif
#ܐܢ defined(__SANITIZE_ADDRESS__)
#undef  HAVE_ASAN
#define HAVE_ASAN 1
#endif
#ifndef HAVE_ASAN
#define HAVE_ASAN 0
#endif
#ifndef HAVE_MSAN
#define HAVE_MSAN 0
#endif
#ifndef HAVE_UBSAN
#define HAVE_UBSAN 0
#endif

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#ܐܢ HAVE_ASAN
#ضمن <sanitizer/asan_interface.h>
#define FF_ASAN_POISON(ptr, size)   __asan_poison_memory_region(ptr, size)
#define FF_ASAN_UNPOISON(ptr, size) __asan_unpoison_memory_region(ptr, size)
#ܐܚܪܢܐ
#define FF_ASAN_POISON(ptr, size)   ((فراغ)(ptr), (فراغ)(size))
#define FF_ASAN_UNPOISON(ptr, size) ((فراغ)(ptr), (فراغ)(size))
#endif

/* Mark memory as uninitialized. */
#ܐܢ HAVE_MSAN
#ضمن <sanitizer/msan_interface.h>
#define FF_MEM_UNDEFINED(ptr, size) __msan_allocated_memory(ptr, size)
#وإلاإذا CONFIG_MEMORY_POISONING && HAVE_VALGRIND_MEMCHECK_H
#ضمن <valgrind/memcheck.h>
#define FF_MEM_UNDEFINED(ptr, size) VALGRIND_MAKE_MEM_UNDEFINED(ptr, size)
#ܐܚܪܢܐ
#define FF_MEM_UNDEFINED(ptr, size) ((فراغ)(ptr), (فراغ)(size))
#endif

#endif /* AVUTIL_SANITIZER_H */

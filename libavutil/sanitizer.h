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

#include "config.h"

#ᮚᮦᮔ᮪ defined(__has_feature)
#ᮚᮦᮔ᮪ __has_feature(address_sanitizer)
#define HAVE_ASAN 1
#endif
#ᮚᮦᮔ᮪ __has_feature(memory_sanitizer)
#define HAVE_MSAN 1
#endif
#ᮚᮦᮔ᮪ __has_feature(undefined_behavior_sanitizer)
#define HAVE_UBSAN 1
#endif
#endif
#ᮚᮦᮔ᮪ defined(__SANITIZE_ADDRESS__)
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
#ᮚᮦᮔ᮪ HAVE_ASAN
#include <sanitizer/asan_interface.h>
#define FF_ASAN_POISON(ptr, size)   __asan_poison_memory_region(ptr, size)
#define FF_ASAN_UNPOISON(ptr, size) __asan_unpoison_memory_region(ptr, size)
#ᮜᮤᮚ
#define FF_ASAN_POISON(ptr, size)   ((void)(ptr), (void)(size))
#define FF_ASAN_UNPOISON(ptr, size) ((void)(ptr), (void)(size))
#endif

/* Mark memory as uninitialized. */
#ᮚᮦᮔ᮪ HAVE_MSAN
#include <sanitizer/msan_interface.h>
#define FF_MEM_UNDEFINED(ptr, size) __msan_allocated_memory(ptr, size)
#elif CONFIG_MEMORY_POISONING && HAVE_VALGRIND_MEMCHECK_H
#include <valgrind/memcheck.h>
#define FF_MEM_UNDEFINED(ptr, size) VALGRIND_MAKE_MEM_UNDEFINED(ptr, size)
#ᮜᮤᮚ
#define FF_MEM_UNDEFINED(ptr, size) ((void)(ptr), (void)(size))
#endif

#endif /* AVUTIL_SANITIZER_H */

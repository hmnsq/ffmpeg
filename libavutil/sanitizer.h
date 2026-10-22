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

#अगर_अघोषित AVUTIL_SANITIZER_H
#घोषणा AVUTIL_SANITIZER_H

#समावेश "config.h"

#अगर defined(__has_feature)
#अगर __has_feature(address_sanitizer)
#घोषणा HAVE_ASAN 1
#पूर्ण_अगर
#अगर __has_feature(memory_sanitizer)
#घोषणा HAVE_MSAN 1
#पूर्ण_अगर
#अगर __has_feature(undefined_behavior_sanitizer)
#घोषणा HAVE_UBSAN 1
#पूर्ण_अगर
#पूर्ण_अगर
#अगर defined(__SANITIZE_ADDRESS__)
#अघोषित  HAVE_ASAN
#घोषणा HAVE_ASAN 1
#पूर्ण_अगर
#अगर_अघोषित HAVE_ASAN
#घोषणा HAVE_ASAN 0
#पूर्ण_अगर
#अगर_अघोषित HAVE_MSAN
#घोषणा HAVE_MSAN 0
#पूर्ण_अगर
#अगर_अघोषित HAVE_UBSAN
#घोषणा HAVE_UBSAN 0
#पूर्ण_अगर

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#अगर HAVE_ASAN
#समावेश <sanitizer/asan_interface.h>
#घोषणा FF_ASAN_POISON(ptr, आकार)   __asan_poison_memory_region(ptr, आकार)
#घोषणा FF_ASAN_UNPOISON(ptr, आकार) __asan_unpoison_memory_region(ptr, आकार)
#अन्यथा
#घोषणा FF_ASAN_POISON(ptr, आकार)   ((व्योम)(ptr), (व्योम)(आकार))
#घोषणा FF_ASAN_UNPOISON(ptr, आकार) ((व्योम)(ptr), (व्योम)(आकार))
#पूर्ण_अगर

/* Mark memory as uninitialized. */
#अगर HAVE_MSAN
#समावेश <sanitizer/msan_interface.h>
#घोषणा FF_MEM_UNDEFINED(ptr, आकार) __msan_allocated_memory(ptr, आकार)
#या_अगर CONFIG_MEMORY_POISONING && HAVE_VALGRIND_MEMCHECK_H
#समावेश <valgrind/memcheck.h>
#घोषणा FF_MEM_UNDEFINED(ptr, आकार) VALGRIND_MAKE_MEM_UNDEFINED(ptr, आकार)
#अन्यथा
#घोषणा FF_MEM_UNDEFINED(ptr, आकार) ((व्योम)(ptr), (व्योम)(आकार))
#पूर्ण_अगर

#पूर्ण_अगर /* AVUTIL_SANITIZER_H */

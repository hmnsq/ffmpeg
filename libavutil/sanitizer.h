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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_SANITIZER_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_SANITIZER_H

#ಅನ್ತರ್ಭಾವ "config.h"

#ಆದರೆ defined(__has_feature)
#ಆದರೆ __has_feature(ವಿಳಾಸ_sanitizer)
#ವ್ಯಾಖ್ಯಾನಿಸು HAVE_ASAN 1
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ __has_feature(ಸ್ಮರಣೆ_sanitizer)
#ವ್ಯಾಖ್ಯಾನಿಸು HAVE_MSAN 1
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ __has_feature(undefined_behavior_sanitizer)
#ವ್ಯಾಖ್ಯಾನಿಸು HAVE_UBSAN 1
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ defined(__SANITIZE_ADDRESS__)
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು  HAVE_ASAN
#ವ್ಯಾಖ್ಯಾನಿಸು HAVE_ASAN 1
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HAVE_ASAN
#ವ್ಯಾಖ್ಯಾನಿಸು HAVE_ASAN 0
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HAVE_MSAN
#ವ್ಯಾಖ್ಯಾನಿಸು HAVE_MSAN 0
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ HAVE_UBSAN
#ವ್ಯಾಖ್ಯಾನಿಸು HAVE_UBSAN 0
#ಆದರೆ_ಅಂತ್ಯ

/* Mark allocated memory that nothing may touch until it is unpoisoned. */
#ಆದರೆ HAVE_ASAN
#ಅನ್ತರ್ಭಾವ <sanitizer/asan_interface.h>
#ವ್ಯಾಖ್ಯಾನಿಸು FF_ASAN_POISON(ptr, ಗಾತ್ರ_2)   __asan_poison_memory_region(ptr, ಗಾತ್ರ_2)
#ವ್ಯಾಖ್ಯಾನಿಸು FF_ASAN_UNPOISON(ptr, ಗಾತ್ರ_2) __asan_unpoison_memory_region(ptr, ಗಾತ್ರ_2)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು FF_ASAN_POISON(ptr, ಗಾತ್ರ_2)   ((ಶೂನ್ಯ)(ptr), (ಶೂನ್ಯ)(ಗಾತ್ರ_2))
#ವ್ಯಾಖ್ಯಾನಿಸು FF_ASAN_UNPOISON(ptr, ಗಾತ್ರ_2) ((ಶೂನ್ಯ)(ptr), (ಶೂನ್ಯ)(ಗಾತ್ರ_2))
#ಆದರೆ_ಅಂತ್ಯ

/* Mark memory as uninitialized. */
#ಆದರೆ HAVE_MSAN
#ಅನ್ತರ್ಭಾವ <sanitizer/msan_interface.h>
#ವ್ಯಾಖ್ಯಾನಿಸು FF_MEM_UNDEFINED(ptr, ಗಾತ್ರ_2) __msan_allocated_memory(ptr, ಗಾತ್ರ_2)
#ಅಥವಾಆದರೆ CONFIG_ಸ್ಮರಣೆ_POISONING && HAVE_VALGRIND_MEMCHECK_H
#ಅನ್ತರ್ಭಾವ <valgrind/memcheck.h>
#ವ್ಯಾಖ್ಯಾನಿಸು FF_MEM_UNDEFINED(ptr, ಗಾತ್ರ_2) VALGRIND_MAKE_MEM_UNDEFINED(ptr, ಗಾತ್ರ_2)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು FF_MEM_UNDEFINED(ptr, ಗಾತ್ರ_2) ((ಶೂನ್ಯ)(ptr), (ಶೂನ್ಯ)(ಗಾತ್ರ_2))
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_SANITIZER_H */

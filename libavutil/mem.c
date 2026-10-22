/*
 * default memory allocator for libavutil
 * Copyright (c) 2002 Fabrice Bellard
 *
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

/**
 * @file
 * default memory allocator for libavutil
 */

#ವ್ಯಾಖ್ಯಾನಿಸು XOPEN_ಮೂಲ 600

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdatomic.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಆದರೆ HAVE_MALLOC_H
#ಅನ್ತರ್ಭಾವ <malloc.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "dynarray.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "internal.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "sanitizer.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MALLOC_ಪೂರ್ವಪ್ರತ್ಯಯ

#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಮರಣೆ_ಕೊಡು         AV_JOIN(MALLOC_ಪೂರ್ವಪ್ರತ್ಯಯ, ಸ್ಮರಣೆ_ಕೊಡು)
#ವ್ಯಾಖ್ಯಾನಿಸು memalign       AV_JOIN(MALLOC_ಪೂರ್ವಪ್ರತ್ಯಯ, memalign)
#ವ್ಯಾಖ್ಯಾನಿಸು posix_memalign AV_JOIN(MALLOC_ಪೂರ್ವಪ್ರತ್ಯಯ, posix_memalign)
#ವ್ಯಾಖ್ಯಾನಿಸು realloc        AV_JOIN(MALLOC_ಪೂರ್ವಪ್ರತ್ಯಯ, realloc)
#ವ್ಯಾಖ್ಯಾನಿಸು ಬಿಡುಗಡೆ           AV_JOIN(MALLOC_ಪೂರ್ವಪ್ರತ್ಯಯ, ಬಿಡುಗಡೆ)

ಶೂನ್ಯ *ಸ್ಮರಣೆ_ಕೊಡು(size_t ಗಾತ್ರ_2);
ಶೂನ್ಯ *memalign(size_t align, size_t ಗಾತ್ರ_2);
ಪೂರ್ಣಾಂಕ   posix_memalign(ಶೂನ್ಯ **ptr, size_t align, size_t ಗಾತ್ರ_2);
ಶೂನ್ಯ *realloc(ಶೂನ್ಯ *ptr, size_t ಗಾತ್ರ_2);
ಶೂನ್ಯ  ಬಿಡುಗಡೆ(ಶೂನ್ಯ *ptr);

#ಆದರೆ_ಅಂತ್ಯ /* MALLOC_PREFIX */

#ವ್ಯಾಖ್ಯಾನಿಸು ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#ವ್ಯಾಖ್ಯಾನಿಸು FF_ಸ್ಮರಣೆ_POISON 0x2a

ಸ್ಥಿರ ಶೂನ್ಯ poison_ಸ್ಮರಣೆ(ಶೂನ್ಯ *ptr, size_t ಗಾತ್ರ_2)
{
#ಆದರೆ CONFIG_ಸ್ಮರಣೆ_POISONING
    memset(ptr, FF_ಸ್ಮರಣೆ_POISON, ಗಾತ್ರ_2);
#ಆದರೆ_ಅಂತ್ಯ
    FF_MEM_UNDEFINED(ptr, ಗಾತ್ರ_2);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#ಆದರೆ HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#ವ್ಯಾಖ್ಯಾನಿಸು ASAN_ALIGNED_ALLOC 1

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ asan_aligned_alloc_needed(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ atomic_int needed = -1;
    ಪೂರ್ಣಾಂಕ ret = atomic_load_explicit(&needed, memory_order_relaxed);

    ಆದರೆ (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        ಪೂರ್ಣಾಂಕ probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        ಆದರೆ (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    ಹಿಂತಿರುಗಿ ret;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Asan_Aligned_ಶೀರ್ಷಿಕೆ {
    ಶೂನ್ಯ  *ತಳ_2;
    size_t ಗಾತ್ರ_2;
} Asan_Aligned_ಶೀರ್ಷಿಕೆ;

ಸ್ಥಿರ ಶೂನ್ಯ *asan_aligned_malloc(size_t ಗಾತ್ರ_2)
{
    Asan_Aligned_ಶೀರ್ಷಿಕೆ *hdr;
    uint8_t *ತಳ_2, *ptr;
    size_t ಒಟ್ಟು;

    ಆದರೆ (ಗಾತ್ರ_2 > SIZE_MAX - ALIGN - ಗಾತ್ರ(*hdr))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಒಟ್ಟು = ಗಾತ್ರ_2 + ALIGN + ಗಾತ್ರ(*hdr);
    ತಳ_2  = ಸ್ಮರಣೆ_ಕೊಡು(ಒಟ್ಟು);
    ಆದರೆ (!ತಳ_2)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ptr = (uint8_t *)FFALIGN((uintptr_t)ತಳ_2 + ಗಾತ್ರ(*hdr), ALIGN);
    hdr = (Asan_Aligned_ಶೀರ್ಷಿಕೆ *)ptr - 1;
    hdr->ತಳ_2 = ತಳ_2;
    hdr->ಗಾತ್ರ_2 = ಗಾತ್ರ_2;
    FF_ASAN_POISON(ತಳ_2, ptr - ತಳ_2);
    FF_ASAN_POISON(ptr + ಗಾತ್ರ_2, ತಳ_2 + ಒಟ್ಟು - (ptr + ಗಾತ್ರ_2));
    ಹಿಂತಿರುಗಿ ptr;
}

ಸ್ಥಿರ Asan_Aligned_ಶೀರ್ಷಿಕೆ *asan_aligned_ಶೀರ್ಷಿಕೆ(ಶೂನ್ಯ *ptr)
{
    Asan_Aligned_ಶೀರ್ಷಿಕೆ *hdr = (Asan_Aligned_ಶೀರ್ಷಿಕೆ *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, ಗಾತ್ರ(*hdr));
    ಹಿಂತಿರುಗಿ hdr;
}

ಸ್ಥಿರ ಶೂನ್ಯ asan_aligned_free(ಶೂನ್ಯ *ptr)
{
    ಆದರೆ (ptr)
        ಬಿಡುಗಡೆ(asan_aligned_ಶೀರ್ಷಿಕೆ(ptr)->ತಳ_2);
}

ಸ್ಥಿರ ಶೂನ್ಯ *asan_aligned_realloc(ಶೂನ್ಯ *ptr, size_t ಗಾತ್ರ_2)
{
    Asan_Aligned_ಶೀರ್ಷಿಕೆ *hdr;
    ಶೂನ್ಯ *ret;

    ಆದರೆ (!ptr)
        ಹಿಂತಿರುಗಿ asan_aligned_malloc(ಗಾತ್ರ_2);
    ret = asan_aligned_malloc(ಗಾತ್ರ_2);
    ಆದರೆ (!ret)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    hdr = asan_aligned_ಶೀರ್ಷಿಕೆ(ptr);
    ಸ್ಮರಣೆ_ನಕಲು(ret, ptr, FFMIN(ಗಾತ್ರ_2, hdr->ಗಾತ್ರ_2));
    ಬಿಡುಗಡೆ(hdr->ತಳ_2);
    ಹಿಂತಿರುಗಿ ret;
}
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು ASAN_ALIGNED_ALLOC 0
#ಆದರೆ_ಅಂತ್ಯ

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

ಸ್ಥಿರ atomic_size_t max_alloc_ಗಾತ್ರ = ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ;

ಶೂನ್ಯ av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_ಗಾತ್ರ, max, memory_order_relaxed);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#ಆದರೆ (!defined(__INTEL_COMPILER) && AV_GCC_ಆವೃತ್ತಿ_AT_ಕನಿಷ್ಠ(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    ಆದರೆ (__builtin_mul_overflow(a, b, &t))
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
#ಇಲ್ಲದಿದ್ದರೆ
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    ಆದರೆ ((a | b) >= ((size_t)1 << (ಗಾತ್ರ(size_t) * 4)) && a && t / a != b)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
#ಆದರೆ_ಅಂತ್ಯ
    *r = t;
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ *av_malloc(size_t ಗಾತ್ರ_2)
{
    ಶೂನ್ಯ *ptr = ಖಾಲಿ;

    ಆದರೆ (ಗಾತ್ರ_2 > atomic_load_explicit(&max_alloc_ಗಾತ್ರ, memory_order_relaxed))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

#ಆದರೆ ASAN_ALIGNED_ALLOC
    ಆದರೆ (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(ಗಾತ್ರ_2);
    ಇಲ್ಲದಿದ್ದರೆ
        ptr = _aligned_malloc(ಗಾತ್ರ_2, ALIGN);
#ಅಥವಾಆದರೆ HAVE_POSIX_MEMALIGN
    ಆದರೆ (ಗಾತ್ರ_2) //OS X on SDK 10.6 has a broken posix_memalign implementation
    ಆದರೆ (posix_memalign(&ptr, ALIGN, ಗಾತ್ರ_2))
        ptr = ಖಾಲಿ;
#ಅಥವಾಆದರೆ HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(ಗಾತ್ರ_2, ALIGN);
#ಅಥವಾಆದರೆ HAVE_MEMALIGN
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ __DJGPP__
    ptr = memalign(ALIGN, ಗಾತ್ರ_2);
#ಇಲ್ಲದಿದ್ದರೆ
    ptr = memalign(ಗಾತ್ರ_2, ALIGN);
#ಆದರೆ_ಅಂತ್ಯ
    /* Why 64?
     * Indeed, we should align it:
     *   on  4 for 386
     *   on 16 for 486
     *   on 32 for 586, PPro - K6-III
     *   on 64 for K7 (maybe for P3 too).
     * Because L1 and L2 caches are aligned on those values.
     * But I don't want to code such logic here!
     */
    /* Why 32?
     * For AVX ASM. SSE / NEON needs only 16.
     * Why not larger? Because I did not see a difference in benchmarks ...
     */
    /* benchmarks with P3
     * memalign(64) + 1          3071, 3051, 3032
     * memalign(64) + 2          3051, 3032, 3041
     * memalign(64) + 4          2911, 2896, 2915
     * memalign(64) + 8          2545, 2554, 2550
     * memalign(64) + 16         2543, 2572, 2563
     * memalign(64) + 32         2546, 2545, 2571
     * memalign(64) + 64         2570, 2533, 2558
     *
     * BTW, malloc seems to do 8-byte alignment by default here.
     */
#ಇಲ್ಲದಿದ್ದರೆ
    ptr = ಸ್ಮರಣೆ_ಕೊಡು(ಗಾತ್ರ_2);
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ(!ptr && !ಗಾತ್ರ_2) {
        ಗಾತ್ರ_2 = 1;
        ptr= av_malloc(1);
    }
    ಆದರೆ (ptr)
        poison_ಸ್ಮರಣೆ(ptr, ಗಾತ್ರ_2);
    ಹಿಂತಿರುಗಿ ptr;
}

ಶೂನ್ಯ *av_realloc(ಶೂನ್ಯ *ptr, size_t ಗಾತ್ರ_2)
{
    ಶೂನ್ಯ *ret;
    ಆದರೆ (ಗಾತ್ರ_2 > atomic_load_explicit(&max_alloc_ಗಾತ್ರ, memory_order_relaxed))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

#ಆದರೆ ASAN_ALIGNED_ALLOC
    ಆದರೆ (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, ಗಾತ್ರ_2 + !ಗಾತ್ರ_2);
    ಇಲ್ಲದಿದ್ದರೆ
        ret = _aligned_realloc(ptr, ಗಾತ್ರ_2 + !ಗಾತ್ರ_2, ALIGN);
#ಅಥವಾಆದರೆ HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, ಗಾತ್ರ_2 + !ಗಾತ್ರ_2, ALIGN);
#ಇಲ್ಲದಿದ್ದರೆ
    ret = realloc(ptr, ಗಾತ್ರ_2 + !ಗಾತ್ರ_2);
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (ret && !ptr)
        poison_ಸ್ಮರಣೆ(ret, ಗಾತ್ರ_2);
    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ *av_realloc_f(ಶೂನ್ಯ *ptr, size_t nelem, size_t elsize)
{
    size_t ಗಾತ್ರ_2;
    ಶೂನ್ಯ *r;

    ಆದರೆ (ಗಾತ್ರ_mult(elsize, nelem, &ಗಾತ್ರ_2)) {
        av_free(ptr);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    r = av_realloc(ptr, ಗಾತ್ರ_2);
    ಆದರೆ (!r)
        av_free(ptr);
    ಹಿಂತಿರುಗಿ r;
}

ಪೂರ್ಣಾಂಕ av_reallocp(ಶೂನ್ಯ *ptr, size_t ಗಾತ್ರ_2)
{
    ಶೂನ್ಯ *val;

    ಆದರೆ (!ಗಾತ್ರ_2) {
        av_freep(ptr);
        ಹಿಂತಿರುಗಿ 0;
    }

    ಸ್ಮರಣೆ_ನಕಲು(&val, ptr, ಗಾತ್ರ(val));
    val = av_realloc(val, ಗಾತ್ರ_2);

    ಆದರೆ (!val) {
        av_freep(ptr);
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }

    ಸ್ಮರಣೆ_ನಕಲು(ptr, &val, ಗಾತ್ರ(val));
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ *av_malloc_array(size_t nmemb, size_t ಗಾತ್ರ_2)
{
    size_t ಫಲಿತಾಂಶ;
    ಆದರೆ (ಗಾತ್ರ_mult(nmemb, ಗಾತ್ರ_2, &ಫಲಿತಾಂಶ) < 0)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ av_malloc(ಫಲಿತಾಂಶ);
}

ಶೂನ್ಯ *av_realloc_array(ಶೂನ್ಯ *ptr, size_t nmemb, size_t ಗಾತ್ರ_2)
{
    size_t ಫಲಿತಾಂಶ;
    ಆದರೆ (ಗಾತ್ರ_mult(nmemb, ಗಾತ್ರ_2, &ಫಲಿತಾಂಶ) < 0)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ av_realloc(ptr, ಫಲಿತಾಂಶ);
}

ಪೂರ್ಣಾಂಕ av_reallocp_array(ಶೂನ್ಯ *ptr, size_t nmemb, size_t ಗಾತ್ರ_2)
{
    ಶೂನ್ಯ *val;

    ಸ್ಮರಣೆ_ನಕಲು(&val, ptr, ಗಾತ್ರ(val));
    val = av_realloc_f(val, nmemb, ಗಾತ್ರ_2);
    ಸ್ಮರಣೆ_ನಕಲು(ptr, &val, ಗಾತ್ರ(val));
    ಆದರೆ (!val && nmemb && ಗಾತ್ರ_2)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_free(ಶೂನ್ಯ *ptr)
{
#ಆದರೆ ASAN_ALIGNED_ALLOC
    ಆದರೆ (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    ಇಲ್ಲದಿದ್ದರೆ
        _aligned_free(ptr);
#ಅಥವಾಆದರೆ HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#ಇಲ್ಲದಿದ್ದರೆ
    ಬಿಡುಗಡೆ(ptr);
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ av_freep(ಶೂನ್ಯ *arg)
{
    ಶೂನ್ಯ *val;

    ಸ್ಮರಣೆ_ನಕಲು(&val, arg, ಗಾತ್ರ(val));
    ಸ್ಮರಣೆ_ನಕಲು(arg, &(ಶೂನ್ಯ *){ ಖಾಲಿ }, ಗಾತ್ರ(val));
    av_free(val);
}

ಶೂನ್ಯ *av_mallocz(size_t ಗಾತ್ರ_2)
{
    ಶೂನ್ಯ *ptr = av_malloc(ಗಾತ್ರ_2);
    ಆದರೆ (ptr)
        memset(ptr, 0, ಗಾತ್ರ_2);
    ಹಿಂತಿರುಗಿ ptr;
}

ಶೂನ್ಯ *av_calloc(size_t nmemb, size_t ಗಾತ್ರ_2)
{
    size_t ಫಲಿತಾಂಶ;
    ಆದರೆ (ಗಾತ್ರ_mult(nmemb, ಗಾತ್ರ_2, &ಫಲಿತಾಂಶ) < 0)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ av_mallocz(ಫಲಿತಾಂಶ);
}

ಅಕ್ಷರ *av_strdup(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s)
{
    ಅಕ್ಷರ *ptr = ಖಾಲಿ;
    ಆದರೆ (s) {
        size_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(s) + 1;
        ptr = av_realloc(ಖಾಲಿ, len);
        ಆದರೆ (ptr)
            ಸ್ಮರಣೆ_ನಕಲು(ptr, s, len);
    }
    ಹಿಂತಿರುಗಿ ptr;
}

ಅಕ್ಷರ *av_strndup(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *s, size_t len)
{
    ಆದರೆ (!s)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಕೊನೆ = memchr(s, 0, len);
    ಆದರೆ (ಕೊನೆ)
        len = ಕೊನೆ - s;

    ಅಕ್ಷರ *ret = av_realloc(ಖಾಲಿ, len + 1);
    ಆದರೆ (!ret)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಸ್ಮರಣೆ_ನಕಲು(ret, s, len);
    ret[len] = 0;
    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ *av_memdup(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p, size_t ಗಾತ್ರ_2)
{
    ಶೂನ್ಯ *ptr = ಖಾಲಿ;
    ಆದರೆ (p) {
        ptr = av_malloc(ಗಾತ್ರ_2);
        ಆದರೆ (ptr)
            ಸ್ಮರಣೆ_ನಕಲು(ptr, p, ಗಾತ್ರ_2);
    }
    ಹಿಂತಿರುಗಿ ptr;
}

ಪೂರ್ಣಾಂಕ av_dynarray_ಕೂಡಿಸು_nofree(ಶೂನ್ಯ *tab_ptr, ಪೂರ್ಣಾಂಕ *nb_ptr, ಶೂನ್ಯ *elem)
{
    ಶೂನ್ಯ **tab;
    ಸ್ಮರಣೆ_ನಕಲು(&tab, tab_ptr, ಗಾತ್ರ(tab));

    FF_DYNARRAY_ಕೂಡಿಸು(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, ಗಾತ್ರ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        ಸ್ಮರಣೆ_ನಕಲು(tab_ptr, &tab, ಗಾತ್ರ(tab));
    }, {
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    });
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_dynarray_ಕೂಡಿಸು(ಶೂನ್ಯ *tab_ptr, ಪೂರ್ಣಾಂಕ *nb_ptr, ಶೂನ್ಯ *elem)
{
    ಶೂನ್ಯ **tab;
    ಸ್ಮರಣೆ_ನಕಲು(&tab, tab_ptr, ಗಾತ್ರ(tab));

    FF_DYNARRAY_ಕೂಡಿಸು(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, ಗಾತ್ರ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        ಸ್ಮರಣೆ_ನಕಲು(tab_ptr, &tab, ಗಾತ್ರ(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

ಶೂನ್ಯ *av_dynarray2_ಕೂಡಿಸು(ಶೂನ್ಯ **tab_ptr, ಪೂರ್ಣಾಂಕ *nb_ptr, size_t elem_ಗಾತ್ರ,
                       ಸ್ಥಿರಾಂಕ uint8_t *elem_ದತ್ತಾಂಶ)
{
    uint8_t *tab_elem_ದತ್ತಾಂಶ = ಖಾಲಿ;

    FF_DYNARRAY_ಕೂಡಿಸು(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ, elem_ಗಾತ್ರ, *tab_ptr, *nb_ptr, {
        tab_elem_ದತ್ತಾಂಶ = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_ಗಾತ್ರ;
        ಆದರೆ (elem_ದತ್ತಾಂಶ)
            ಸ್ಮರಣೆ_ನಕಲು(tab_elem_ದತ್ತಾಂಶ, elem_ದತ್ತಾಂಶ, elem_ಗಾತ್ರ);
        ಇಲ್ಲದಿದ್ದರೆ
            poison_ಸ್ಮರಣೆ(tab_elem_ದತ್ತಾಂಶ, elem_ಗಾತ್ರ);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    ಹಿಂತಿರುಗಿ tab_elem_ದತ್ತಾಂಶ;
}

ಸ್ಥಿರ ಶೂನ್ಯ fill16(uint8_t *dst, ಪೂರ್ಣಾಂಕ len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    ಆಗ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ಆಗ (len--) {
        *dst = dst[-2];
        dst++;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ fill24(uint8_t *dst, ಪೂರ್ಣಾಂಕ len)
{
#ಆದರೆ HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#ಇಲ್ಲದಿದ್ದರೆ
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#ಆದರೆ_ಅಂತ್ಯ

    ಆಗ (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    ಆದರೆ (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    ಆದರೆ (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    ಆಗ (len--) {
        *dst = dst[-3];
        dst++;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ fill32(uint8_t *dst, ಪೂರ್ಣಾಂಕ len)
{
    uint32_t v = AV_RN32(dst - 4);

#ಆದರೆ HAVE_FAST_64_ಬಿಟ್
    uint64_t v2= v + ((uint64_t)v<<32);
    ಆಗ (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆಗ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ಆಗ (len--) {
        *dst = dst[-4];
        dst++;
    }
}

ಶೂನ್ಯ av_memcpy_backptr(uint8_t *dst, ಪೂರ್ಣಾಂಕ ಹಿಂಭಾಗ, ಪೂರ್ಣಾಂಕ cnt)
{
    ಸ್ಥಿರಾಂಕ uint8_t *src = &dst[-ಹಿಂಭಾಗ];
    ಆದರೆ (!ಹಿಂಭಾಗ)
        ಹಿಂತಿರುಗಿ;

    ಆದರೆ (ಹಿಂಭಾಗ == 1) {
        memset(dst, *src, cnt);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹಿಂಭಾಗ == 2) {
        fill16(dst, cnt);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹಿಂಭಾಗ == 3) {
        fill24(dst, cnt);
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಹಿಂಭಾಗ == 4) {
        fill32(dst, cnt);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (cnt >= 16) {
            ಪೂರ್ಣಾಂಕ blocklen = ಹಿಂಭಾಗ;
            ಆಗ (cnt > blocklen) {
                ಸ್ಮರಣೆ_ನಕಲು(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            ಸ್ಮರಣೆ_ನಕಲು(dst, src, cnt);
            ಹಿಂತಿರುಗಿ;
        }
        ಆದರೆ (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        ಆದರೆ (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        ಆದರೆ (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        ಆದರೆ (cnt)
            *dst = *src;
    }
}

ಶೂನ್ಯ *av_fast_realloc(ಶೂನ್ಯ *ptr, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *ಗಾತ್ರ_2, size_t min_ಗಾತ್ರ)
{
    size_t max_ಗಾತ್ರ;

    ಆದರೆ (min_ಗಾತ್ರ <= *ಗಾತ್ರ_2)
        ಹಿಂತಿರುಗಿ ptr;

    max_ಗಾತ್ರ = atomic_load_explicit(&max_alloc_ಗಾತ್ರ, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_ಗಾತ್ರ = FFMIN(max_ಗಾತ್ರ, UINT_MAX);

    ಆದರೆ (min_ಗಾತ್ರ > max_ಗಾತ್ರ) {
        *ಗಾತ್ರ_2 = 0;
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    min_ಗಾತ್ರ = FFMIN(max_ಗಾತ್ರ, FFMAX(min_ಗಾತ್ರ + min_ಗಾತ್ರ / 16 + 32, min_ಗಾತ್ರ));

    ptr = av_realloc(ptr, min_ಗಾತ್ರ);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    ಆದರೆ (!ptr)
        min_ಗಾತ್ರ = 0;

    *ಗಾತ್ರ_2 = min_ಗಾತ್ರ;

    ಹಿಂತಿರುಗಿ ptr;
}

ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಶೂನ್ಯ fast_malloc(ಶೂನ್ಯ *ptr, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *ಗಾತ್ರ_2, size_t min_ಗಾತ್ರ, ಪೂರ್ಣಾಂಕ zero_realloc)
{
    size_t max_ಗಾತ್ರ;
    ಶೂನ್ಯ *val;

    ಸ್ಮರಣೆ_ನಕಲು(&val, ptr, ಗಾತ್ರ(val));
    ಆದರೆ (min_ಗಾತ್ರ <= *ಗಾತ್ರ_2) {
        av_assert0(val || !min_ಗಾತ್ರ);
        ಹಿಂತಿರುಗಿ;
    }

    max_ಗಾತ್ರ = atomic_load_explicit(&max_alloc_ಗಾತ್ರ, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_ಗಾತ್ರ = FFMIN(max_ಗಾತ್ರ, UINT_MAX);

    ಆದರೆ (min_ಗಾತ್ರ > max_ಗಾತ್ರ) {
        av_freep(ptr);
        *ಗಾತ್ರ_2 = 0;
        ಹಿಂತಿರುಗಿ;
    }
    min_ಗಾತ್ರ = FFMIN(max_ಗಾತ್ರ, FFMAX(min_ಗಾತ್ರ + min_ಗಾತ್ರ / 16 + 32, min_ಗಾತ್ರ));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_ಗಾತ್ರ) : av_malloc(min_ಗಾತ್ರ);
    ಸ್ಮರಣೆ_ನಕಲು(ptr, &val, ಗಾತ್ರ(val));
    ಆದರೆ (!val)
        min_ಗಾತ್ರ = 0;
    *ಗಾತ್ರ_2 = min_ಗಾತ್ರ;
    ಹಿಂತಿರುಗಿ;
}

ಶೂನ್ಯ av_fast_malloc(ಶೂನ್ಯ *ptr, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *ಗಾತ್ರ_2, size_t min_ಗಾತ್ರ)
{
    fast_malloc(ptr, ಗಾತ್ರ_2, min_ಗಾತ್ರ, 0);
}

ಶೂನ್ಯ av_fast_mallocz(ಶೂನ್ಯ *ptr, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ *ಗಾತ್ರ_2, size_t min_ಗಾತ್ರ)
{
    fast_malloc(ptr, ಗಾತ್ರ_2, min_ಗಾತ್ರ, 1);
}

ಪೂರ್ಣಾಂಕ av_ಗಾತ್ರ_mult(size_t a, size_t b, size_t *r)
{
    ಹಿಂತಿರುಗಿ ಗಾತ್ರ_mult(a, b, r);
}

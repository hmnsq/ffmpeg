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

#define _XOPEN_SOURCE 600

#ಅನ್ತರ್ಭಾವ "config.h"

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <stdlib.h>
#ಅನ್ತರ್ಭಾವ <stdatomic.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಯದಿ HAVE_MALLOC_H
#ಅನ್ತರ್ಭಾವ <malloc.h>
#endif

#ಅನ್ತರ್ಭಾವ "attributes.h"
#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "dynarray.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "internal.h"
#ಅನ್ತರ್ಭಾವ "intreadwrite.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define ಮುಕ್ತ           AV_JOIN(MALLOC_PREFIX, ಮುಕ್ತ)

ಶೂನ್ಯ *malloc(size_t size);
ಶೂನ್ಯ *memalign(size_t align, size_t size);
ಪೂರ್ಣಾಙ್ಕ   posix_memalign(ಶೂನ್ಯ **ptr, size_t align, size_t size);
ಶೂನ್ಯ *realloc(ಶೂನ್ಯ *ptr, size_t size);
ಶೂನ್ಯ  ಮುಕ್ತ(ಶೂನ್ಯ *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

ಸ್ಥಿರ ಶೂನ್ಯ poison_memory(ಶೂನ್ಯ *ptr, size_t size)
{
#ಯದಿ CONFIG_MEMORY_POISONING
    memset(ptr, FF_MEMORY_POISON, size);
#endif
    FF_MEM_UNDEFINED(ptr, size);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#ಯದಿ HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ asan_aligned_alloc_needed(ಶೂನ್ಯ)
{
    ಸ್ಥಿರ atomic_int needed = -1;
    ಪೂರ್ಣಾಙ್ಕ ret = atomic_load_explicit(&needed, memory_order_relaxed);

    ಯದಿ (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        ಪೂರ್ಣಾಙ್ಕ probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        ಯದಿ (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ AsanAlignedHeader {
    ಶೂನ್ಯ  *base;
    size_t size;
} AsanAlignedHeader;

ಸ್ಥಿರ ಶೂನ್ಯ *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    ಯದಿ (size > SIZE_MAX - ALIGN - ಪರಿಮಾಣ(*hdr))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    total = size + ALIGN + ಪರಿಮಾಣ(*hdr);
    base  = malloc(total);
    ಯದಿ (!base)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + ಪರಿಮಾಣ(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    ಪ್ರತ್ಯಾಗಮ ptr;
}

ಸ್ಥಿರ AsanAlignedHeader *asan_aligned_header(ಶೂನ್ಯ *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, ಪರಿಮಾಣ(*hdr));
    ಪ್ರತ್ಯಾಗಮ hdr;
}

ಸ್ಥಿರ ಶೂನ್ಯ asan_aligned_free(ಶೂನ್ಯ *ptr)
{
    ಯದಿ (ptr)
        ಮುಕ್ತ(asan_aligned_header(ptr)->base);
}

ಸ್ಥಿರ ಶೂನ್ಯ *asan_aligned_realloc(ಶೂನ್ಯ *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    ಶೂನ್ಯ *ret;

    ಯದಿ (!ptr)
        ಪ್ರತ್ಯಾಗಮ asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    ಯದಿ (!ret)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    ಮುಕ್ತ(hdr->base);
    ಪ್ರತ್ಯಾಗಮ ret;
}
#ಅನ್ಯಥಾ
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

ಸ್ಥಿರ atomic_size_t max_alloc_size = INT_MAX;

ಶೂನ್ಯ av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#ಯದಿ (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    ಯದಿ (__builtin_mul_overflow(a, b, &t))
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
#ಅನ್ಯಥಾ
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    ಯದಿ ((a | b) >= ((size_t)1 << (ಪರಿಮಾಣ(size_t) * 4)) && a && t / a != b)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
#endif
    *r = t;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ *av_malloc(size_t size)
{
    ಶೂನ್ಯ *ptr = ರಿಕ್ತ;

    ಯದಿ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

#ಯದಿ ASAN_ALIGNED_ALLOC
    ಯದಿ (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    ಅನ್ಯಥಾ
        ptr = _aligned_malloc(size, ALIGN);
#ನೋಚೇದ್ಯದಿ HAVE_POSIX_MEMALIGN
    ಯದಿ (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    ಯದಿ (posix_memalign(&ptr, ALIGN, size))
        ptr = ರಿಕ್ತ;
#ನೋಚೇದ್ಯದಿ HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#ನೋಚೇದ್ಯದಿ HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#ಅನ್ಯಥಾ
    ptr = memalign(size, ALIGN);
#endif
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
#ಅನ್ಯಥಾ
    ptr = malloc(size);
#endif
    ಯದಿ(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    ಯದಿ (ptr)
        poison_memory(ptr, size);
    ಪ್ರತ್ಯಾಗಮ ptr;
}

ಶೂನ್ಯ *av_realloc(ಶೂನ್ಯ *ptr, size_t size)
{
    ಶೂನ್ಯ *ret;
    ಯದಿ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

#ಯದಿ ASAN_ALIGNED_ALLOC
    ಯದಿ (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    ಅನ್ಯಥಾ
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#ನೋಚೇದ್ಯದಿ HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#ಅನ್ಯಥಾ
    ret = realloc(ptr, size + !size);
#endif
    ಯದಿ (ret && !ptr)
        poison_memory(ret, size);
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ *av_realloc_f(ಶೂನ್ಯ *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    ಶೂನ್ಯ *r;

    ಯದಿ (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    r = av_realloc(ptr, size);
    ಯದಿ (!r)
        av_free(ptr);
    ಪ್ರತ್ಯಾಗಮ r;
}

ಪೂರ್ಣಾಙ್ಕ av_reallocp(ಶೂನ್ಯ *ptr, size_t size)
{
    ಶೂನ್ಯ *val;

    ಯದಿ (!size) {
        av_freep(ptr);
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    memcpy(&val, ptr, ಪರಿಮಾಣ(val));
    val = av_realloc(val, size);

    ಯದಿ (!val) {
        av_freep(ptr);
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, ಪರಿಮಾಣ(val));
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    ಯದಿ (size_mult(nmemb, size, &result) < 0)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ av_malloc(result);
}

ಶೂನ್ಯ *av_realloc_array(ಶೂನ್ಯ *ptr, size_t nmemb, size_t size)
{
    size_t result;
    ಯದಿ (size_mult(nmemb, size, &result) < 0)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ av_realloc(ptr, result);
}

ಪೂರ್ಣಾಙ್ಕ av_reallocp_array(ಶೂನ್ಯ *ptr, size_t nmemb, size_t size)
{
    ಶೂನ್ಯ *val;

    memcpy(&val, ptr, ಪರಿಮಾಣ(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, ಪರಿಮಾಣ(val));
    ಯದಿ (!val && nmemb && size)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_free(ಶೂನ್ಯ *ptr)
{
#ಯದಿ ASAN_ALIGNED_ALLOC
    ಯದಿ (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    ಅನ್ಯಥಾ
        _aligned_free(ptr);
#ನೋಚೇದ್ಯದಿ HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#ಅನ್ಯಥಾ
    ಮುಕ್ತ(ptr);
#endif
}

ಶೂನ್ಯ av_freep(ಶೂನ್ಯ *arg)
{
    ಶೂನ್ಯ *val;

    memcpy(&val, arg, ಪರಿಮಾಣ(val));
    memcpy(arg, &(ಶೂನ್ಯ *){ ರಿಕ್ತ }, ಪರಿಮಾಣ(val));
    av_free(val);
}

ಶೂನ್ಯ *av_mallocz(size_t size)
{
    ಶೂನ್ಯ *ptr = av_malloc(size);
    ಯದಿ (ptr)
        memset(ptr, 0, size);
    ಪ್ರತ್ಯಾಗಮ ptr;
}

ಶೂನ್ಯ *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    ಯದಿ (size_mult(nmemb, size, &result) < 0)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ av_mallocz(result);
}

ವರ್ಣ *av_strdup(ಧ್ರುವ ವರ್ಣ *s)
{
    ವರ್ಣ *ptr = ರಿಕ್ತ;
    ಯದಿ (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(ರಿಕ್ತ, len);
        ಯದಿ (ptr)
            memcpy(ptr, s, len);
    }
    ಪ್ರತ್ಯಾಗಮ ptr;
}

ವರ್ಣ *av_strndup(ಧ್ರುವ ವರ್ಣ *s, size_t len)
{
    ಯದಿ (!s)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಧ್ರುವ ವರ್ಣ *end = memchr(s, 0, len);
    ಯದಿ (end)
        len = end - s;

    ವರ್ಣ *ret = av_realloc(ರಿಕ್ತ, len + 1);
    ಯದಿ (!ret)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    memcpy(ret, s, len);
    ret[len] = 0;
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ *av_memdup(ಧ್ರುವ ಶೂನ್ಯ *p, size_t size)
{
    ಶೂನ್ಯ *ptr = ರಿಕ್ತ;
    ಯದಿ (p) {
        ptr = av_malloc(size);
        ಯದಿ (ptr)
            memcpy(ptr, p, size);
    }
    ಪ್ರತ್ಯಾಗಮ ptr;
}

ಪೂರ್ಣಾಙ್ಕ av_dynarray_add_nofree(ಶೂನ್ಯ *tab_ptr, ಪೂರ್ಣಾಙ್ಕ *nb_ptr, ಶೂನ್ಯ *elem)
{
    ಶೂನ್ಯ **tab;
    memcpy(&tab, tab_ptr, ಪರಿಮಾಣ(tab));

    FF_DYNARRAY_ADD(INT_MAX, ಪರಿಮಾಣ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, ಪರಿಮಾಣ(tab));
    }, {
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    });
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_dynarray_add(ಶೂನ್ಯ *tab_ptr, ಪೂರ್ಣಾಙ್ಕ *nb_ptr, ಶೂನ್ಯ *elem)
{
    ಶೂನ್ಯ **tab;
    memcpy(&tab, tab_ptr, ಪರಿಮಾಣ(tab));

    FF_DYNARRAY_ADD(INT_MAX, ಪರಿಮಾಣ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, ಪರಿಮಾಣ(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

ಶೂನ್ಯ *av_dynarray2_add(ಶೂನ್ಯ **tab_ptr, ಪೂರ್ಣಾಙ್ಕ *nb_ptr, size_t elem_size,
                       ಧ್ರುವ uint8_t *elem_data)
{
    uint8_t *tab_elem_data = ರಿಕ್ತ;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        ಯದಿ (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        ಅನ್ಯಥಾ
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    ಪ್ರತ್ಯಾಗಮ tab_elem_data;
}

ಸ್ಥಿರ ಶೂನ್ಯ fill16(uint8_t *dst, ಪೂರ್ಣಾಙ್ಕ len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    ಯಾವತ್ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ಯಾವತ್ (len--) {
        *dst = dst[-2];
        dst++;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ fill24(uint8_t *dst, ಪೂರ್ಣಾಙ್ಕ len)
{
#ಯದಿ HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#ಅನ್ಯಥಾ
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    ಯಾವತ್ (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    ಯದಿ (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    ಯದಿ (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    ಯಾವತ್ (len--) {
        *dst = dst[-3];
        dst++;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ fill32(uint8_t *dst, ಪೂರ್ಣಾಙ್ಕ len)
{
    uint32_t v = AV_RN32(dst - 4);

#ಯದಿ HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    ಯಾವತ್ (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    ಯಾವತ್ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ಯಾವತ್ (len--) {
        *dst = dst[-4];
        dst++;
    }
}

ಶೂನ್ಯ av_memcpy_backptr(uint8_t *dst, ಪೂರ್ಣಾಙ್ಕ back, ಪೂರ್ಣಾಙ್ಕ cnt)
{
    ಧ್ರುವ uint8_t *src = &dst[-back];
    ಯದಿ (!back)
        ಪ್ರತ್ಯಾಗಮ;

    ಯದಿ (back == 1) {
        memset(dst, *src, cnt);
    } ಅನ್ಯಥಾ ಯದಿ (back == 2) {
        fill16(dst, cnt);
    } ಅನ್ಯಥಾ ಯದಿ (back == 3) {
        fill24(dst, cnt);
    } ಅನ್ಯಥಾ ಯದಿ (back == 4) {
        fill32(dst, cnt);
    } ಅನ್ಯಥಾ {
        ಯದಿ (cnt >= 16) {
            ಪೂರ್ಣಾಙ್ಕ blocklen = back;
            ಯಾವತ್ (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            ಪ್ರತ್ಯಾಗಮ;
        }
        ಯದಿ (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        ಯದಿ (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        ಯದಿ (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        ಯದಿ (cnt)
            *dst = *src;
    }
}

ಶೂನ್ಯ *av_fast_realloc(ಶೂನ್ಯ *ptr, unsigned ಪೂರ್ಣಾಙ್ಕ *size, size_t min_size)
{
    size_t max_size;

    ಯದಿ (min_size <= *size)
        ಪ್ರತ್ಯಾಗಮ ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    ಯದಿ (min_size > max_size) {
        *size = 0;
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    ಯದಿ (!ptr)
        min_size = 0;

    *size = min_size;

    ಪ್ರತ್ಯಾಗಮ ptr;
}

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ಶೂನ್ಯ fast_malloc(ಶೂನ್ಯ *ptr, unsigned ಪೂರ್ಣಾಙ್ಕ *size, size_t min_size, ಪೂರ್ಣಾಙ್ಕ zero_realloc)
{
    size_t max_size;
    ಶೂನ್ಯ *val;

    memcpy(&val, ptr, ಪರಿಮಾಣ(val));
    ಯದಿ (min_size <= *size) {
        av_assert0(val || !min_size);
        ಪ್ರತ್ಯಾಗಮ;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    ಯದಿ (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        ಪ್ರತ್ಯಾಗಮ;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, ಪರಿಮಾಣ(val));
    ಯದಿ (!val)
        min_size = 0;
    *size = min_size;
    ಪ್ರತ್ಯಾಗಮ;
}

ಶೂನ್ಯ av_fast_malloc(ಶೂನ್ಯ *ptr, unsigned ಪೂರ್ಣಾಙ್ಕ *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

ಶೂನ್ಯ av_fast_mallocz(ಶೂನ್ಯ *ptr, unsigned ಪೂರ್ಣಾಙ್ಕ *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

ಪೂರ್ಣಾಙ್ಕ av_size_mult(size_t a, size_t b, size_t *r)
{
    ಪ್ರತ್ಯಾಗಮ size_mult(a, b, r);
}

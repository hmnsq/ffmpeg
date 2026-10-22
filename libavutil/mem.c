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

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XOPEN_ਸਰੋਤ 600

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdlib.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਜੇ HAVE_MALLOC_H
#ਅਨ੍ਤਰ੍ਭਾਵ <malloc.h>
#ਜੇ_ਅੰਤ

#ਅਨ੍ਤਰ੍ਭਾਵ "attributes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "dynarray.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intreadwrite.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sanitizer.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MALLOC_ਅਗੇਤਰ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਸਮ੍ਰਿਤੀ_ਦਿਓ         AV_JOIN(MALLOC_ਅਗੇਤਰ, ਸਮ੍ਰਿਤੀ_ਦਿਓ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ memalign       AV_JOIN(MALLOC_ਅਗੇਤਰ, memalign)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ posix_memalign AV_JOIN(MALLOC_ਅਗੇਤਰ, posix_memalign)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ realloc        AV_JOIN(MALLOC_ਅਗੇਤਰ, realloc)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਮੁਕਤ           AV_JOIN(MALLOC_ਅਗੇਤਰ, ਮੁਕਤ)

ਖਾਲੀ *ਸਮ੍ਰਿਤੀ_ਦਿਓ(size_t ਮਾਪ);
ਖਾਲੀ *memalign(size_t align, size_t ਮਾਪ);
ਪੂਰਨ   posix_memalign(ਖਾਲੀ **ptr, size_t align, size_t ਮਾਪ);
ਖਾਲੀ *realloc(ਖਾਲੀ *ptr, size_t ਮਾਪ);
ਖਾਲੀ  ਮੁਕਤ(ਖਾਲੀ *ptr);

#ਜੇ_ਅੰਤ /* MALLOC_PREFIX */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_ਸਮ੍ਰਿਤੀ_POISON 0x2a

ਸਥਿਰ ਖਾਲੀ poison_ਸਮ੍ਰਿਤੀ(ਖਾਲੀ *ptr, size_t ਮਾਪ)
{
#ਜੇ CONFIG_ਸਮ੍ਰਿਤੀ_POISONING
    memset(ptr, FF_ਸਮ੍ਰਿਤੀ_POISON, ਮਾਪ);
#ਜੇ_ਅੰਤ
    FF_MEM_UNDEFINED(ptr, ਮਾਪ);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#ਜੇ HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASAN_ALIGNED_ALLOC 1

ਸਥਿਰ ਪੂਰਨ asan_aligned_alloc_needed(ਖਾਲੀ)
{
    ਸਥਿਰ atomic_int needed = -1;
    ਪੂਰਨ ret = atomic_load_explicit(&needed, memory_order_relaxed);

    ਜੇ (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        ਪੂਰਨ probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        ਜੇ (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    ਵਾਪਸ ret;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Asan_Aligned_ਸਿਰਲੇਖ {
    ਖਾਲੀ  *ਅਧਾਰ_2;
    size_t ਮਾਪ;
} Asan_Aligned_ਸਿਰਲੇਖ;

ਸਥਿਰ ਖਾਲੀ *asan_aligned_malloc(size_t ਮਾਪ)
{
    Asan_Aligned_ਸਿਰਲੇਖ *hdr;
    uint8_t *ਅਧਾਰ_2, *ptr;
    size_t ਕੁੱਲ;

    ਜੇ (ਮਾਪ > SIZE_MAX - ALIGN - ਆਕਾਰ(*hdr))
        ਵਾਪਸ ਨਿਰਾ;
    ਕੁੱਲ = ਮਾਪ + ALIGN + ਆਕਾਰ(*hdr);
    ਅਧਾਰ_2  = ਸਮ੍ਰਿਤੀ_ਦਿਓ(ਕੁੱਲ);
    ਜੇ (!ਅਧਾਰ_2)
        ਵਾਪਸ ਨਿਰਾ;
    ptr = (uint8_t *)FFALIGN((uintptr_t)ਅਧਾਰ_2 + ਆਕਾਰ(*hdr), ALIGN);
    hdr = (Asan_Aligned_ਸਿਰਲੇਖ *)ptr - 1;
    hdr->ਅਧਾਰ_2 = ਅਧਾਰ_2;
    hdr->ਮਾਪ = ਮਾਪ;
    FF_ASAN_POISON(ਅਧਾਰ_2, ptr - ਅਧਾਰ_2);
    FF_ASAN_POISON(ptr + ਮਾਪ, ਅਧਾਰ_2 + ਕੁੱਲ - (ptr + ਮਾਪ));
    ਵਾਪਸ ptr;
}

ਸਥਿਰ Asan_Aligned_ਸਿਰਲੇਖ *asan_aligned_ਸਿਰਲੇਖ(ਖਾਲੀ *ptr)
{
    Asan_Aligned_ਸਿਰਲੇਖ *hdr = (Asan_Aligned_ਸਿਰਲੇਖ *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, ਆਕਾਰ(*hdr));
    ਵਾਪਸ hdr;
}

ਸਥਿਰ ਖਾਲੀ asan_aligned_free(ਖਾਲੀ *ptr)
{
    ਜੇ (ptr)
        ਮੁਕਤ(asan_aligned_ਸਿਰਲੇਖ(ptr)->ਅਧਾਰ_2);
}

ਸਥਿਰ ਖਾਲੀ *asan_aligned_realloc(ਖਾਲੀ *ptr, size_t ਮਾਪ)
{
    Asan_Aligned_ਸਿਰਲੇਖ *hdr;
    ਖਾਲੀ *ret;

    ਜੇ (!ptr)
        ਵਾਪਸ asan_aligned_malloc(ਮਾਪ);
    ret = asan_aligned_malloc(ਮਾਪ);
    ਜੇ (!ret)
        ਵਾਪਸ ਨਿਰਾ;
    hdr = asan_aligned_ਸਿਰਲੇਖ(ptr);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(ret, ptr, FFMIN(ਮਾਪ, hdr->ਮਾਪ));
    ਮੁਕਤ(hdr->ਅਧਾਰ_2);
    ਵਾਪਸ ret;
}
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASAN_ALIGNED_ALLOC 0
#ਜੇ_ਅੰਤ

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

ਸਥਿਰ atomic_size_t max_alloc_ਮਾਪ = ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ;

ਖਾਲੀ av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_ਮਾਪ, max, memory_order_relaxed);
}

ਸਥਿਰ ਪੂਰਨ ਮਾਪ_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#ਜੇ (!defined(__INTEL_COMPILER) && AV_GCC_ਸੰਸਕਰਣ_AT_ਘੱਟ_ਤੋਂ_ਘੱਟ(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    ਜੇ (__builtin_mul_overflow(a, b, &t))
        ਵਾਪਸ AVERROR(EINVAL);
#ਨਹੀਂਤਾਂ
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    ਜੇ ((a | b) >= ((size_t)1 << (ਆਕਾਰ(size_t) * 4)) && a && t / a != b)
        ਵਾਪਸ AVERROR(EINVAL);
#ਜੇ_ਅੰਤ
    *r = t;
    ਵਾਪਸ 0;
}

ਖਾਲੀ *av_malloc(size_t ਮਾਪ)
{
    ਖਾਲੀ *ptr = ਨਿਰਾ;

    ਜੇ (ਮਾਪ > atomic_load_explicit(&max_alloc_ਮਾਪ, memory_order_relaxed))
        ਵਾਪਸ ਨਿਰਾ;

#ਜੇ ASAN_ALIGNED_ALLOC
    ਜੇ (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(ਮਾਪ);
    ਨਹੀਂਤਾਂ
        ptr = _aligned_malloc(ਮਾਪ, ALIGN);
#ਜਾਂਜੇ HAVE_POSIX_MEMALIGN
    ਜੇ (ਮਾਪ) //OS X on SDK 10.6 has a broken posix_memalign implementation
    ਜੇ (posix_memalign(&ptr, ALIGN, ਮਾਪ))
        ptr = ਨਿਰਾ;
#ਜਾਂਜੇ HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(ਮਾਪ, ALIGN);
#ਜਾਂਜੇ HAVE_MEMALIGN
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ __DJGPP__
    ptr = memalign(ALIGN, ਮਾਪ);
#ਨਹੀਂਤਾਂ
    ptr = memalign(ਮਾਪ, ALIGN);
#ਜੇ_ਅੰਤ
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
#ਨਹੀਂਤਾਂ
    ptr = ਸਮ੍ਰਿਤੀ_ਦਿਓ(ਮਾਪ);
#ਜੇ_ਅੰਤ
    ਜੇ(!ptr && !ਮਾਪ) {
        ਮਾਪ = 1;
        ptr= av_malloc(1);
    }
    ਜੇ (ptr)
        poison_ਸਮ੍ਰਿਤੀ(ptr, ਮਾਪ);
    ਵਾਪਸ ptr;
}

ਖਾਲੀ *av_realloc(ਖਾਲੀ *ptr, size_t ਮਾਪ)
{
    ਖਾਲੀ *ret;
    ਜੇ (ਮਾਪ > atomic_load_explicit(&max_alloc_ਮਾਪ, memory_order_relaxed))
        ਵਾਪਸ ਨਿਰਾ;

#ਜੇ ASAN_ALIGNED_ALLOC
    ਜੇ (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, ਮਾਪ + !ਮਾਪ);
    ਨਹੀਂਤਾਂ
        ret = _aligned_realloc(ptr, ਮਾਪ + !ਮਾਪ, ALIGN);
#ਜਾਂਜੇ HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, ਮਾਪ + !ਮਾਪ, ALIGN);
#ਨਹੀਂਤਾਂ
    ret = realloc(ptr, ਮਾਪ + !ਮਾਪ);
#ਜੇ_ਅੰਤ
    ਜੇ (ret && !ptr)
        poison_ਸਮ੍ਰਿਤੀ(ret, ਮਾਪ);
    ਵਾਪਸ ret;
}

ਖਾਲੀ *av_realloc_f(ਖਾਲੀ *ptr, size_t nelem, size_t elsize)
{
    size_t ਮਾਪ;
    ਖਾਲੀ *r;

    ਜੇ (ਮਾਪ_mult(elsize, nelem, &ਮਾਪ)) {
        av_free(ptr);
        ਵਾਪਸ ਨਿਰਾ;
    }
    r = av_realloc(ptr, ਮਾਪ);
    ਜੇ (!r)
        av_free(ptr);
    ਵਾਪਸ r;
}

ਪੂਰਨ av_reallocp(ਖਾਲੀ *ptr, size_t ਮਾਪ)
{
    ਖਾਲੀ *val;

    ਜੇ (!ਮਾਪ) {
        av_freep(ptr);
        ਵਾਪਸ 0;
    }

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(&val, ptr, ਆਕਾਰ(val));
    val = av_realloc(val, ਮਾਪ);

    ਜੇ (!val) {
        av_freep(ptr);
        ਵਾਪਸ AVERROR(ENOMEM);
    }

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(ptr, &val, ਆਕਾਰ(val));
    ਵਾਪਸ 0;
}

ਖਾਲੀ *av_malloc_array(size_t nmemb, size_t ਮਾਪ)
{
    size_t ਨਤੀਜਾ;
    ਜੇ (ਮਾਪ_mult(nmemb, ਮਾਪ, &ਨਤੀਜਾ) < 0)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ av_malloc(ਨਤੀਜਾ);
}

ਖਾਲੀ *av_realloc_array(ਖਾਲੀ *ptr, size_t nmemb, size_t ਮਾਪ)
{
    size_t ਨਤੀਜਾ;
    ਜੇ (ਮਾਪ_mult(nmemb, ਮਾਪ, &ਨਤੀਜਾ) < 0)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ av_realloc(ptr, ਨਤੀਜਾ);
}

ਪੂਰਨ av_reallocp_array(ਖਾਲੀ *ptr, size_t nmemb, size_t ਮਾਪ)
{
    ਖਾਲੀ *val;

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(&val, ptr, ਆਕਾਰ(val));
    val = av_realloc_f(val, nmemb, ਮਾਪ);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(ptr, &val, ਆਕਾਰ(val));
    ਜੇ (!val && nmemb && ਮਾਪ)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਵਾਪਸ 0;
}

ਖਾਲੀ av_free(ਖਾਲੀ *ptr)
{
#ਜੇ ASAN_ALIGNED_ALLOC
    ਜੇ (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    ਨਹੀਂਤਾਂ
        _aligned_free(ptr);
#ਜਾਂਜੇ HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#ਨਹੀਂਤਾਂ
    ਮੁਕਤ(ptr);
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ av_freep(ਖਾਲੀ *arg)
{
    ਖਾਲੀ *val;

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(&val, arg, ਆਕਾਰ(val));
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(arg, &(ਖਾਲੀ *){ ਨਿਰਾ }, ਆਕਾਰ(val));
    av_free(val);
}

ਖਾਲੀ *av_mallocz(size_t ਮਾਪ)
{
    ਖਾਲੀ *ptr = av_malloc(ਮਾਪ);
    ਜੇ (ptr)
        memset(ptr, 0, ਮਾਪ);
    ਵਾਪਸ ptr;
}

ਖਾਲੀ *av_calloc(size_t nmemb, size_t ਮਾਪ)
{
    size_t ਨਤੀਜਾ;
    ਜੇ (ਮਾਪ_mult(nmemb, ਮਾਪ, &ਨਤੀਜਾ) < 0)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ av_mallocz(ਨਤੀਜਾ);
}

ਅੱਖਰ *av_strdup(ਅਚਲ ਅੱਖਰ *s)
{
    ਅੱਖਰ *ptr = ਨਿਰਾ;
    ਜੇ (s) {
        size_t len = ਲੜੀ_ਲੰਬਾਈ(s) + 1;
        ptr = av_realloc(ਨਿਰਾ, len);
        ਜੇ (ptr)
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(ptr, s, len);
    }
    ਵਾਪਸ ptr;
}

ਅੱਖਰ *av_strndup(ਅਚਲ ਅੱਖਰ *s, size_t len)
{
    ਜੇ (!s)
        ਵਾਪਸ ਨਿਰਾ;

    ਅਚਲ ਅੱਖਰ *ਸਿਰਾ = memchr(s, 0, len);
    ਜੇ (ਸਿਰਾ)
        len = ਸਿਰਾ - s;

    ਅੱਖਰ *ret = av_realloc(ਨਿਰਾ, len + 1);
    ਜੇ (!ret)
        ਵਾਪਸ ਨਿਰਾ;

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(ret, s, len);
    ret[len] = 0;
    ਵਾਪਸ ret;
}

ਖਾਲੀ *av_memdup(ਅਚਲ ਖਾਲੀ *p, size_t ਮਾਪ)
{
    ਖਾਲੀ *ptr = ਨਿਰਾ;
    ਜੇ (p) {
        ptr = av_malloc(ਮਾਪ);
        ਜੇ (ptr)
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(ptr, p, ਮਾਪ);
    }
    ਵਾਪਸ ptr;
}

ਪੂਰਨ av_dynarray_ਜੋੜੋ_nofree(ਖਾਲੀ *tab_ptr, ਪੂਰਨ *nb_ptr, ਖਾਲੀ *elem)
{
    ਖਾਲੀ **tab;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(&tab, tab_ptr, ਆਕਾਰ(tab));

    FF_DYNARRAY_ਜੋੜੋ(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, ਆਕਾਰ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(tab_ptr, &tab, ਆਕਾਰ(tab));
    }, {
        ਵਾਪਸ AVERROR(ENOMEM);
    });
    ਵਾਪਸ 0;
}

ਖਾਲੀ av_dynarray_ਜੋੜੋ(ਖਾਲੀ *tab_ptr, ਪੂਰਨ *nb_ptr, ਖਾਲੀ *elem)
{
    ਖਾਲੀ **tab;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(&tab, tab_ptr, ਆਕਾਰ(tab));

    FF_DYNARRAY_ਜੋੜੋ(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, ਆਕਾਰ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(tab_ptr, &tab, ਆਕਾਰ(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

ਖਾਲੀ *av_dynarray2_ਜੋੜੋ(ਖਾਲੀ **tab_ptr, ਪੂਰਨ *nb_ptr, size_t elem_ਮਾਪ,
                       ਅਚਲ uint8_t *elem_ਅੰਕੜੇ)
{
    uint8_t *tab_elem_ਅੰਕੜੇ = ਨਿਰਾ;

    FF_DYNARRAY_ਜੋੜੋ(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ, elem_ਮਾਪ, *tab_ptr, *nb_ptr, {
        tab_elem_ਅੰਕੜੇ = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_ਮਾਪ;
        ਜੇ (elem_ਅੰਕੜੇ)
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(tab_elem_ਅੰਕੜੇ, elem_ਅੰਕੜੇ, elem_ਮਾਪ);
        ਨਹੀਂਤਾਂ
            poison_ਸਮ੍ਰਿਤੀ(tab_elem_ਅੰਕੜੇ, elem_ਮਾਪ);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    ਵਾਪਸ tab_elem_ਅੰਕੜੇ;
}

ਸਥਿਰ ਖਾਲੀ fill16(uint8_t *dst, ਪੂਰਨ len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    ਜਦੋਂ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ਜਦੋਂ (len--) {
        *dst = dst[-2];
        dst++;
    }
}

ਸਥਿਰ ਖਾਲੀ fill24(uint8_t *dst, ਪੂਰਨ len)
{
#ਜੇ HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#ਨਹੀਂਤਾਂ
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#ਜੇ_ਅੰਤ

    ਜਦੋਂ (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    ਜੇ (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    ਜੇ (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    ਜਦੋਂ (len--) {
        *dst = dst[-3];
        dst++;
    }
}

ਸਥਿਰ ਖਾਲੀ fill32(uint8_t *dst, ਪੂਰਨ len)
{
    uint32_t v = AV_RN32(dst - 4);

#ਜੇ HAVE_FAST_64_ਦੋਆਧਾਰੀ_ਅੰਕ
    uint64_t v2= v + ((uint64_t)v<<32);
    ਜਦੋਂ (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#ਜੇ_ਅੰਤ

    ਜਦੋਂ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ਜਦੋਂ (len--) {
        *dst = dst[-4];
        dst++;
    }
}

ਖਾਲੀ av_memcpy_backptr(uint8_t *dst, ਪੂਰਨ ਪਿੱਠ, ਪੂਰਨ cnt)
{
    ਅਚਲ uint8_t *src = &dst[-ਪਿੱਠ];
    ਜੇ (!ਪਿੱਠ)
        ਵਾਪਸ;

    ਜੇ (ਪਿੱਠ == 1) {
        memset(dst, *src, cnt);
    } ਨਹੀਂਤਾਂ ਜੇ (ਪਿੱਠ == 2) {
        fill16(dst, cnt);
    } ਨਹੀਂਤਾਂ ਜੇ (ਪਿੱਠ == 3) {
        fill24(dst, cnt);
    } ਨਹੀਂਤਾਂ ਜੇ (ਪਿੱਠ == 4) {
        fill32(dst, cnt);
    } ਨਹੀਂਤਾਂ {
        ਜੇ (cnt >= 16) {
            ਪੂਰਨ blocklen = ਪਿੱਠ;
            ਜਦੋਂ (cnt > blocklen) {
                ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            ਸਮ੍ਰਿਤੀ_ਨਕਲ(dst, src, cnt);
            ਵਾਪਸ;
        }
        ਜੇ (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        ਜੇ (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        ਜੇ (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        ਜੇ (cnt)
            *dst = *src;
    }
}

ਖਾਲੀ *av_fast_realloc(ਖਾਲੀ *ptr, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *ਮਾਪ, size_t min_ਮਾਪ)
{
    size_t max_ਮਾਪ;

    ਜੇ (min_ਮਾਪ <= *ਮਾਪ)
        ਵਾਪਸ ptr;

    max_ਮਾਪ = atomic_load_explicit(&max_alloc_ਮਾਪ, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_ਮਾਪ = FFMIN(max_ਮਾਪ, UINT_MAX);

    ਜੇ (min_ਮਾਪ > max_ਮਾਪ) {
        *ਮਾਪ = 0;
        ਵਾਪਸ ਨਿਰਾ;
    }

    min_ਮਾਪ = FFMIN(max_ਮਾਪ, FFMAX(min_ਮਾਪ + min_ਮਾਪ / 16 + 32, min_ਮਾਪ));

    ptr = av_realloc(ptr, min_ਮਾਪ);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    ਜੇ (!ptr)
        min_ਮਾਪ = 0;

    *ਮਾਪ = min_ਮਾਪ;

    ਵਾਪਸ ptr;
}

ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ fast_malloc(ਖਾਲੀ *ptr, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *ਮਾਪ, size_t min_ਮਾਪ, ਪੂਰਨ zero_realloc)
{
    size_t max_ਮਾਪ;
    ਖਾਲੀ *val;

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(&val, ptr, ਆਕਾਰ(val));
    ਜੇ (min_ਮਾਪ <= *ਮਾਪ) {
        av_assert0(val || !min_ਮਾਪ);
        ਵਾਪਸ;
    }

    max_ਮਾਪ = atomic_load_explicit(&max_alloc_ਮਾਪ, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_ਮਾਪ = FFMIN(max_ਮਾਪ, UINT_MAX);

    ਜੇ (min_ਮਾਪ > max_ਮਾਪ) {
        av_freep(ptr);
        *ਮਾਪ = 0;
        ਵਾਪਸ;
    }
    min_ਮਾਪ = FFMIN(max_ਮਾਪ, FFMAX(min_ਮਾਪ + min_ਮਾਪ / 16 + 32, min_ਮਾਪ));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_ਮਾਪ) : av_malloc(min_ਮਾਪ);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(ptr, &val, ਆਕਾਰ(val));
    ਜੇ (!val)
        min_ਮਾਪ = 0;
    *ਮਾਪ = min_ਮਾਪ;
    ਵਾਪਸ;
}

ਖਾਲੀ av_fast_malloc(ਖਾਲੀ *ptr, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *ਮਾਪ, size_t min_ਮਾਪ)
{
    fast_malloc(ptr, ਮਾਪ, min_ਮਾਪ, 0);
}

ਖਾਲੀ av_fast_mallocz(ਖਾਲੀ *ptr, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ *ਮਾਪ, size_t min_ਮਾਪ)
{
    fast_malloc(ptr, ਮਾਪ, min_ਮਾਪ, 1);
}

ਪੂਰਨ av_ਮਾਪ_mult(size_t a, size_t b, size_t *r)
{
    ਵਾਪਸ ਮਾਪ_mult(a, b, r);
}

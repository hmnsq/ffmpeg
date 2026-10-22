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

#অন্তর্ভাব "config.h"

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <stdlib.h>
#অন্তর্ভাব <stdatomic.h>
#অন্তর্ভাব <string.h>
#যদি HAVE_MALLOC_H
#অন্তর্ভাব <malloc.h>
#endif

#অন্তর্ভাব "attributes.h"
#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "dynarray.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "internal.h"
#অন্তর্ভাব "intreadwrite.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define মুক্ত           AV_JOIN(MALLOC_PREFIX, মুক্ত)

শূন্য *malloc(size_t আকার_2);
শূন্য *memalign(size_t align, size_t আকার_2);
পূর্ণসংখ্যা   posix_memalign(শূন্য **ptr, size_t align, size_t আকার_2);
শূন্য *realloc(শূন্য *ptr, size_t আকার_2);
শূন্য  মুক্ত(শূন্য *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

স্থির শূন্য poison_memory(শূন্য *ptr, size_t আকার_2)
{
#যদি CONFIG_MEMORY_POISONING
    memset(ptr, FF_MEMORY_POISON, আকার_2);
#endif
    FF_MEM_UNDEFINED(ptr, আকার_2);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#যদি HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

স্থির পূর্ণসংখ্যা asan_aligned_alloc_needed(শূন্য)
{
    স্থির atomic_int needed = -1;
    পূর্ণসংখ্যা ret = atomic_load_explicit(&needed, memory_order_relaxed);

    যদি (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        পূর্ণসংখ্যা probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        যদি (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    ফেরত ret;
}

প্রকারলেখ কাঠামো AsanAlignedHeader {
    শূন্য  *base;
    size_t আকার_2;
} AsanAlignedHeader;

স্থির শূন্য *asan_aligned_malloc(size_t আকার_2)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t যোগ_2;

    যদি (আকার_2 > SIZE_MAX - ALIGN - আকার(*hdr))
        ফেরত ফাঁকা;
    যোগ_2 = আকার_2 + ALIGN + আকার(*hdr);
    base  = malloc(যোগ_2);
    যদি (!base)
        ফেরত ফাঁকা;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + আকার(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->আকার_2 = আকার_2;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + আকার_2, base + যোগ_2 - (ptr + আকার_2));
    ফেরত ptr;
}

স্থির AsanAlignedHeader *asan_aligned_header(শূন্য *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, আকার(*hdr));
    ফেরত hdr;
}

স্থির শূন্য asan_aligned_free(শূন্য *ptr)
{
    যদি (ptr)
        মুক্ত(asan_aligned_header(ptr)->base);
}

স্থির শূন্য *asan_aligned_realloc(শূন্য *ptr, size_t আকার_2)
{
    AsanAlignedHeader *hdr;
    শূন্য *ret;

    যদি (!ptr)
        ফেরত asan_aligned_malloc(আকার_2);
    ret = asan_aligned_malloc(আকার_2);
    যদি (!ret)
        ফেরত ফাঁকা;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(আকার_2, hdr->আকার_2));
    মুক্ত(hdr->base);
    ফেরত ret;
}
#অন্যথা
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

স্থির atomic_size_t max_alloc_আকার = INT_MAX;

শূন্য av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_আকার, max, memory_order_relaxed);
}

স্থির পূর্ণসংখ্যা আকার_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#যদি (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    যদি (__builtin_mul_overflow(a, b, &t))
        ফেরত AVERROR(EINVAL);
#অন্যথা
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    যদি ((a | b) >= ((size_t)1 << (আকার(size_t) * 4)) && a && t / a != b)
        ফেরত AVERROR(EINVAL);
#endif
    *r = t;
    ফেরত 0;
}

শূন্য *av_malloc(size_t আকার_2)
{
    শূন্য *ptr = ফাঁকা;

    যদি (আকার_2 > atomic_load_explicit(&max_alloc_আকার, memory_order_relaxed))
        ফেরত ফাঁকা;

#যদি ASAN_ALIGNED_ALLOC
    যদি (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(আকার_2);
    অন্যথা
        ptr = _aligned_malloc(আকার_2, ALIGN);
#নতুবা_যদি HAVE_POSIX_MEMALIGN
    যদি (আকার_2) //OS X on SDK 10.6 has a broken posix_memalign implementation
    যদি (posix_memalign(&ptr, ALIGN, আকার_2))
        ptr = ফাঁকা;
#নতুবা_যদি HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(আকার_2, ALIGN);
#নতুবা_যদি HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, আকার_2);
#অন্যথা
    ptr = memalign(আকার_2, ALIGN);
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
#অন্যথা
    ptr = malloc(আকার_2);
#endif
    যদি(!ptr && !আকার_2) {
        আকার_2 = 1;
        ptr= av_malloc(1);
    }
    যদি (ptr)
        poison_memory(ptr, আকার_2);
    ফেরত ptr;
}

শূন্য *av_realloc(শূন্য *ptr, size_t আকার_2)
{
    শূন্য *ret;
    যদি (আকার_2 > atomic_load_explicit(&max_alloc_আকার, memory_order_relaxed))
        ফেরত ফাঁকা;

#যদি ASAN_ALIGNED_ALLOC
    যদি (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, আকার_2 + !আকার_2);
    অন্যথা
        ret = _aligned_realloc(ptr, আকার_2 + !আকার_2, ALIGN);
#নতুবা_যদি HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, আকার_2 + !আকার_2, ALIGN);
#অন্যথা
    ret = realloc(ptr, আকার_2 + !আকার_2);
#endif
    যদি (ret && !ptr)
        poison_memory(ret, আকার_2);
    ফেরত ret;
}

শূন্য *av_realloc_f(শূন্য *ptr, size_t nelem, size_t elsize)
{
    size_t আকার_2;
    শূন্য *r;

    যদি (আকার_mult(elsize, nelem, &আকার_2)) {
        av_free(ptr);
        ফেরত ফাঁকা;
    }
    r = av_realloc(ptr, আকার_2);
    যদি (!r)
        av_free(ptr);
    ফেরত r;
}

পূর্ণসংখ্যা av_reallocp(শূন্য *ptr, size_t আকার_2)
{
    শূন্য *val;

    যদি (!আকার_2) {
        av_freep(ptr);
        ফেরত 0;
    }

    memcpy(&val, ptr, আকার(val));
    val = av_realloc(val, আকার_2);

    যদি (!val) {
        av_freep(ptr);
        ফেরত AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, আকার(val));
    ফেরত 0;
}

শূন্য *av_malloc_array(size_t nmemb, size_t আকার_2)
{
    size_t ফলাফল;
    যদি (আকার_mult(nmemb, আকার_2, &ফলাফল) < 0)
        ফেরত ফাঁকা;
    ফেরত av_malloc(ফলাফল);
}

শূন্য *av_realloc_array(শূন্য *ptr, size_t nmemb, size_t আকার_2)
{
    size_t ফলাফল;
    যদি (আকার_mult(nmemb, আকার_2, &ফলাফল) < 0)
        ফেরত ফাঁকা;
    ফেরত av_realloc(ptr, ফলাফল);
}

পূর্ণসংখ্যা av_reallocp_array(শূন্য *ptr, size_t nmemb, size_t আকার_2)
{
    শূন্য *val;

    memcpy(&val, ptr, আকার(val));
    val = av_realloc_f(val, nmemb, আকার_2);
    memcpy(ptr, &val, আকার(val));
    যদি (!val && nmemb && আকার_2)
        ফেরত AVERROR(ENOMEM);

    ফেরত 0;
}

শূন্য av_free(শূন্য *ptr)
{
#যদি ASAN_ALIGNED_ALLOC
    যদি (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    অন্যথা
        _aligned_free(ptr);
#নতুবা_যদি HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#অন্যথা
    মুক্ত(ptr);
#endif
}

শূন্য av_freep(শূন্য *arg)
{
    শূন্য *val;

    memcpy(&val, arg, আকার(val));
    memcpy(arg, &(শূন্য *){ ফাঁকা }, আকার(val));
    av_free(val);
}

শূন্য *av_mallocz(size_t আকার_2)
{
    শূন্য *ptr = av_malloc(আকার_2);
    যদি (ptr)
        memset(ptr, 0, আকার_2);
    ফেরত ptr;
}

শূন্য *av_calloc(size_t nmemb, size_t আকার_2)
{
    size_t ফলাফল;
    যদি (আকার_mult(nmemb, আকার_2, &ফলাফল) < 0)
        ফেরত ফাঁকা;
    ফেরত av_mallocz(ফলাফল);
}

অক্ষর *av_strdup(ধ্রুবক অক্ষর *s)
{
    অক্ষর *ptr = ফাঁকা;
    যদি (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(ফাঁকা, len);
        যদি (ptr)
            memcpy(ptr, s, len);
    }
    ফেরত ptr;
}

অক্ষর *av_strndup(ধ্রুবক অক্ষর *s, size_t len)
{
    যদি (!s)
        ফেরত ফাঁকা;

    ধ্রুবক অক্ষর *end = memchr(s, 0, len);
    যদি (end)
        len = end - s;

    অক্ষর *ret = av_realloc(ফাঁকা, len + 1);
    যদি (!ret)
        ফেরত ফাঁকা;

    memcpy(ret, s, len);
    ret[len] = 0;
    ফেরত ret;
}

শূন্য *av_memdup(ধ্রুবক শূন্য *p, size_t আকার_2)
{
    শূন্য *ptr = ফাঁকা;
    যদি (p) {
        ptr = av_malloc(আকার_2);
        যদি (ptr)
            memcpy(ptr, p, আকার_2);
    }
    ফেরত ptr;
}

পূর্ণসংখ্যা av_dynarray_add_nofree(শূন্য *tab_ptr, পূর্ণসংখ্যা *nb_ptr, শূন্য *elem)
{
    শূন্য **tab;
    memcpy(&tab, tab_ptr, আকার(tab));

    FF_DYNARRAY_ADD(INT_MAX, আকার(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, আকার(tab));
    }, {
        ফেরত AVERROR(ENOMEM);
    });
    ফেরত 0;
}

শূন্য av_dynarray_add(শূন্য *tab_ptr, পূর্ণসংখ্যা *nb_ptr, শূন্য *elem)
{
    শূন্য **tab;
    memcpy(&tab, tab_ptr, আকার(tab));

    FF_DYNARRAY_ADD(INT_MAX, আকার(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, আকার(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

শূন্য *av_dynarray2_add(শূন্য **tab_ptr, পূর্ণসংখ্যা *nb_ptr, size_t elem_আকার,
                       ধ্রুবক uint8_t *elem_তথ্য)
{
    uint8_t *tab_elem_তথ্য = ফাঁকা;

    FF_DYNARRAY_ADD(INT_MAX, elem_আকার, *tab_ptr, *nb_ptr, {
        tab_elem_তথ্য = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_আকার;
        যদি (elem_তথ্য)
            memcpy(tab_elem_তথ্য, elem_তথ্য, elem_আকার);
        অন্যথা
            poison_memory(tab_elem_তথ্য, elem_আকার);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    ফেরত tab_elem_তথ্য;
}

স্থির শূন্য fill16(uint8_t *dst, পূর্ণসংখ্যা len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    যখন (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    যখন (len--) {
        *dst = dst[-2];
        dst++;
    }
}

স্থির শূন্য fill24(uint8_t *dst, পূর্ণসংখ্যা len)
{
#যদি HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#অন্যথা
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    যখন (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    যদি (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    যদি (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    যখন (len--) {
        *dst = dst[-3];
        dst++;
    }
}

স্থির শূন্য fill32(uint8_t *dst, পূর্ণসংখ্যা len)
{
    uint32_t v = AV_RN32(dst - 4);

#যদি HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    যখন (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    যখন (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    যখন (len--) {
        *dst = dst[-4];
        dst++;
    }
}

শূন্য av_memcpy_backptr(uint8_t *dst, পূর্ণসংখ্যা back, পূর্ণসংখ্যা cnt)
{
    ধ্রুবক uint8_t *src = &dst[-back];
    যদি (!back)
        ফেরত;

    যদি (back == 1) {
        memset(dst, *src, cnt);
    } অন্যথা যদি (back == 2) {
        fill16(dst, cnt);
    } অন্যথা যদি (back == 3) {
        fill24(dst, cnt);
    } অন্যথা যদি (back == 4) {
        fill32(dst, cnt);
    } অন্যথা {
        যদি (cnt >= 16) {
            পূর্ণসংখ্যা blocklen = back;
            যখন (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            ফেরত;
        }
        যদি (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        যদি (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        যদি (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        যদি (cnt)
            *dst = *src;
    }
}

শূন্য *av_fast_realloc(শূন্য *ptr, unsigned পূর্ণসংখ্যা *আকার_2, size_t min_আকার)
{
    size_t max_আকার;

    যদি (min_আকার <= *আকার_2)
        ফেরত ptr;

    max_আকার = atomic_load_explicit(&max_alloc_আকার, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_আকার = FFMIN(max_আকার, UINT_MAX);

    যদি (min_আকার > max_আকার) {
        *আকার_2 = 0;
        ফেরত ফাঁকা;
    }

    min_আকার = FFMIN(max_আকার, FFMAX(min_আকার + min_আকার / 16 + 32, min_আকার));

    ptr = av_realloc(ptr, min_আকার);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    যদি (!ptr)
        min_আকার = 0;

    *আকার_2 = min_আকার;

    ফেরত ptr;
}

স্থির অন্তঃরেখ শূন্য fast_malloc(শূন্য *ptr, unsigned পূর্ণসংখ্যা *আকার_2, size_t min_আকার, পূর্ণসংখ্যা zero_realloc)
{
    size_t max_আকার;
    শূন্য *val;

    memcpy(&val, ptr, আকার(val));
    যদি (min_আকার <= *আকার_2) {
        av_assert0(val || !min_আকার);
        ফেরত;
    }

    max_আকার = atomic_load_explicit(&max_alloc_আকার, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_আকার = FFMIN(max_আকার, UINT_MAX);

    যদি (min_আকার > max_আকার) {
        av_freep(ptr);
        *আকার_2 = 0;
        ফেরত;
    }
    min_আকার = FFMIN(max_আকার, FFMAX(min_আকার + min_আকার / 16 + 32, min_আকার));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_আকার) : av_malloc(min_আকার);
    memcpy(ptr, &val, আকার(val));
    যদি (!val)
        min_আকার = 0;
    *আকার_2 = min_আকার;
    ফেরত;
}

শূন্য av_fast_malloc(শূন্য *ptr, unsigned পূর্ণসংখ্যা *আকার_2, size_t min_আকার)
{
    fast_malloc(ptr, আকার_2, min_আকার, 0);
}

শূন্য av_fast_mallocz(শূন্য *ptr, unsigned পূর্ণসংখ্যা *আকার_2, size_t min_আকার)
{
    fast_malloc(ptr, আকার_2, min_আকার, 1);
}

পূর্ণসংখ্যা av_আকার_mult(size_t a, size_t b, size_t *r)
{
    ফেরত আকার_mult(a, b, r);
}

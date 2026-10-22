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

#شامل "config.h"

#شامل <limits.h>
#شامل <stdint.h>
#شامل <stdlib.h>
#شامل <stdatomic.h>
#شامل <string.h>
#اگر HAVE_MALLOC_H
#شامل <malloc.h>
#endif

#شامل "attributes.h"
#شامل "avassert.h"
#شامل "dynarray.h"
#شامل "error.h"
#شامل "internal.h"
#شامل "intreadwrite.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define آزاد           AV_JOIN(MALLOC_PREFIX, آزاد)

تهی *malloc(size_t size);
تهی *memalign(size_t align, size_t size);
صحیح   posix_memalign(تهی **ptr, size_t align, size_t size);
تهی *realloc(تهی *ptr, size_t size);
تهی  آزاد(تهی *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

ایستا تهی poison_memory(تهی *ptr, size_t size)
{
#اگر CONFIG_MEMORY_POISONING
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
#اگر HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

ایستا صحیح asan_aligned_alloc_needed(تهی)
{
    ایستا atomic_int needed = -1;
    صحیح ret = atomic_load_explicit(&needed, memory_order_relaxed);

    اگر (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        صحیح probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        اگر (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    بازگشت ret;
}

تعریفنوع ساختار AsanAlignedHeader {
    تهی  *base;
    size_t size;
} AsanAlignedHeader;

ایستا تهی *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    اگر (size > SIZE_MAX - ALIGN - اندازه(*hdr))
        بازگشت پوچ;
    total = size + ALIGN + اندازه(*hdr);
    base  = malloc(total);
    اگر (!base)
        بازگشت پوچ;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + اندازه(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    بازگشت ptr;
}

ایستا AsanAlignedHeader *asan_aligned_header(تهی *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, اندازه(*hdr));
    بازگشت hdr;
}

ایستا تهی asan_aligned_free(تهی *ptr)
{
    اگر (ptr)
        آزاد(asan_aligned_header(ptr)->base);
}

ایستا تهی *asan_aligned_realloc(تهی *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    تهی *ret;

    اگر (!ptr)
        بازگشت asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    اگر (!ret)
        بازگشت پوچ;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    آزاد(hdr->base);
    بازگشت ret;
}
#وگرنه
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

ایستا atomic_size_t max_alloc_size = INT_MAX;

تهی av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

ایستا صحیح size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#اگر (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    اگر (__builtin_mul_overflow(a, b, &t))
        بازگشت AVERROR(EINVAL);
#وگرنه
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    اگر ((a | b) >= ((size_t)1 << (اندازه(size_t) * 4)) && a && t / a != b)
        بازگشت AVERROR(EINVAL);
#endif
    *r = t;
    بازگشت 0;
}

تهی *av_malloc(size_t size)
{
    تهی *ptr = پوچ;

    اگر (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        بازگشت پوچ;

#اگر ASAN_ALIGNED_ALLOC
    اگر (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    وگرنه
        ptr = _aligned_malloc(size, ALIGN);
#وگرنهاگر HAVE_POSIX_MEMALIGN
    اگر (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    اگر (posix_memalign(&ptr, ALIGN, size))
        ptr = پوچ;
#وگرنهاگر HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#وگرنهاگر HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#وگرنه
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
#وگرنه
    ptr = malloc(size);
#endif
    اگر(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    اگر (ptr)
        poison_memory(ptr, size);
    بازگشت ptr;
}

تهی *av_realloc(تهی *ptr, size_t size)
{
    تهی *ret;
    اگر (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        بازگشت پوچ;

#اگر ASAN_ALIGNED_ALLOC
    اگر (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    وگرنه
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#وگرنهاگر HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#وگرنه
    ret = realloc(ptr, size + !size);
#endif
    اگر (ret && !ptr)
        poison_memory(ret, size);
    بازگشت ret;
}

تهی *av_realloc_f(تهی *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    تهی *r;

    اگر (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        بازگشت پوچ;
    }
    r = av_realloc(ptr, size);
    اگر (!r)
        av_free(ptr);
    بازگشت r;
}

صحیح av_reallocp(تهی *ptr, size_t size)
{
    تهی *val;

    اگر (!size) {
        av_freep(ptr);
        بازگشت 0;
    }

    memcpy(&val, ptr, اندازه(val));
    val = av_realloc(val, size);

    اگر (!val) {
        av_freep(ptr);
        بازگشت AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, اندازه(val));
    بازگشت 0;
}

تهی *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    اگر (size_mult(nmemb, size, &result) < 0)
        بازگشت پوچ;
    بازگشت av_malloc(result);
}

تهی *av_realloc_array(تهی *ptr, size_t nmemb, size_t size)
{
    size_t result;
    اگر (size_mult(nmemb, size, &result) < 0)
        بازگشت پوچ;
    بازگشت av_realloc(ptr, result);
}

صحیح av_reallocp_array(تهی *ptr, size_t nmemb, size_t size)
{
    تهی *val;

    memcpy(&val, ptr, اندازه(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, اندازه(val));
    اگر (!val && nmemb && size)
        بازگشت AVERROR(ENOMEM);

    بازگشت 0;
}

تهی av_free(تهی *ptr)
{
#اگر ASAN_ALIGNED_ALLOC
    اگر (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    وگرنه
        _aligned_free(ptr);
#وگرنهاگر HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#وگرنه
    آزاد(ptr);
#endif
}

تهی av_freep(تهی *arg)
{
    تهی *val;

    memcpy(&val, arg, اندازه(val));
    memcpy(arg, &(تهی *){ پوچ }, اندازه(val));
    av_free(val);
}

تهی *av_mallocz(size_t size)
{
    تهی *ptr = av_malloc(size);
    اگر (ptr)
        memset(ptr, 0, size);
    بازگشت ptr;
}

تهی *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    اگر (size_mult(nmemb, size, &result) < 0)
        بازگشت پوچ;
    بازگشت av_mallocz(result);
}

نویسه *av_strdup(ثابت نویسه *s)
{
    نویسه *ptr = پوچ;
    اگر (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(پوچ, len);
        اگر (ptr)
            memcpy(ptr, s, len);
    }
    بازگشت ptr;
}

نویسه *av_strndup(ثابت نویسه *s, size_t len)
{
    اگر (!s)
        بازگشت پوچ;

    ثابت نویسه *end = memchr(s, 0, len);
    اگر (end)
        len = end - s;

    نویسه *ret = av_realloc(پوچ, len + 1);
    اگر (!ret)
        بازگشت پوچ;

    memcpy(ret, s, len);
    ret[len] = 0;
    بازگشت ret;
}

تهی *av_memdup(ثابت تهی *p, size_t size)
{
    تهی *ptr = پوچ;
    اگر (p) {
        ptr = av_malloc(size);
        اگر (ptr)
            memcpy(ptr, p, size);
    }
    بازگشت ptr;
}

صحیح av_dynarray_add_nofree(تهی *tab_ptr, صحیح *nb_ptr, تهی *elem)
{
    تهی **tab;
    memcpy(&tab, tab_ptr, اندازه(tab));

    FF_DYNARRAY_ADD(INT_MAX, اندازه(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, اندازه(tab));
    }, {
        بازگشت AVERROR(ENOMEM);
    });
    بازگشت 0;
}

تهی av_dynarray_add(تهی *tab_ptr, صحیح *nb_ptr, تهی *elem)
{
    تهی **tab;
    memcpy(&tab, tab_ptr, اندازه(tab));

    FF_DYNARRAY_ADD(INT_MAX, اندازه(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, اندازه(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

تهی *av_dynarray2_add(تهی **tab_ptr, صحیح *nb_ptr, size_t elem_size,
                       ثابت uint8_t *elem_data)
{
    uint8_t *tab_elem_data = پوچ;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        اگر (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        وگرنه
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    بازگشت tab_elem_data;
}

ایستا تهی fill16(uint8_t *dst, صحیح len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    وقتی (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    وقتی (len--) {
        *dst = dst[-2];
        dst++;
    }
}

ایستا تهی fill24(uint8_t *dst, صحیح len)
{
#اگر HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#وگرنه
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    وقتی (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    اگر (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    اگر (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    وقتی (len--) {
        *dst = dst[-3];
        dst++;
    }
}

ایستا تهی fill32(uint8_t *dst, صحیح len)
{
    uint32_t v = AV_RN32(dst - 4);

#اگر HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    وقتی (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    وقتی (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    وقتی (len--) {
        *dst = dst[-4];
        dst++;
    }
}

تهی av_memcpy_backptr(uint8_t *dst, صحیح back, صحیح cnt)
{
    ثابت uint8_t *src = &dst[-back];
    اگر (!back)
        بازگشت;

    اگر (back == 1) {
        memset(dst, *src, cnt);
    } وگرنه اگر (back == 2) {
        fill16(dst, cnt);
    } وگرنه اگر (back == 3) {
        fill24(dst, cnt);
    } وگرنه اگر (back == 4) {
        fill32(dst, cnt);
    } وگرنه {
        اگر (cnt >= 16) {
            صحیح blocklen = back;
            وقتی (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            بازگشت;
        }
        اگر (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        اگر (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        اگر (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        اگر (cnt)
            *dst = *src;
    }
}

تهی *av_fast_realloc(تهی *ptr, unsigned صحیح *size, size_t min_size)
{
    size_t max_size;

    اگر (min_size <= *size)
        بازگشت ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    اگر (min_size > max_size) {
        *size = 0;
        بازگشت پوچ;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    اگر (!ptr)
        min_size = 0;

    *size = min_size;

    بازگشت ptr;
}

ایستا درونخطی تهی fast_malloc(تهی *ptr, unsigned صحیح *size, size_t min_size, صحیح zero_realloc)
{
    size_t max_size;
    تهی *val;

    memcpy(&val, ptr, اندازه(val));
    اگر (min_size <= *size) {
        av_assert0(val || !min_size);
        بازگشت;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    اگر (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        بازگشت;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, اندازه(val));
    اگر (!val)
        min_size = 0;
    *size = min_size;
    بازگشت;
}

تهی av_fast_malloc(تهی *ptr, unsigned صحیح *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

تهی av_fast_mallocz(تهی *ptr, unsigned صحیح *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

صحیح av_size_mult(size_t a, size_t b, size_t *r)
{
    بازگشت size_mult(a, b, r);
}

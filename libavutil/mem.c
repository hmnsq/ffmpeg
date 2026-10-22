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

#ضمن "config.h"

#ضمن <limits.h>
#ضمن <stdint.h>
#ضمن <stdlib.h>
#ضمن <stdatomic.h>
#ضمن <string.h>
#إذا HAVE_MALLOC_H
#ضمن <malloc.h>
#endif

#ضمن "attributes.h"
#ضمن "avassert.h"
#ضمن "dynarray.h"
#ضمن "error.h"
#ضمن "internal.h"
#ضمن "intreadwrite.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define حرر           AV_JOIN(MALLOC_PREFIX, حرر)

فراغ *malloc(size_t size);
فراغ *memalign(size_t align, size_t size);
صحيح   posix_memalign(فراغ **ptr, size_t align, size_t size);
فراغ *realloc(فراغ *ptr, size_t size);
فراغ  حرر(فراغ *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

ساكن فراغ poison_memory(فراغ *ptr, size_t size)
{
#إذا CONFIG_MEMORY_POISONING
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
#إذا HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

ساكن صحيح asan_aligned_alloc_needed(فراغ)
{
    ساكن atomic_int needed = -1;
    صحيح ret = atomic_load_explicit(&needed, memory_order_relaxed);

    إذا (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        صحيح probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        إذا (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    إرجاع ret;
}

تعريفنوع بنية AsanAlignedHeader {
    فراغ  *base;
    size_t size;
} AsanAlignedHeader;

ساكن فراغ *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    إذا (size > SIZE_MAX - ALIGN - حجم(*hdr))
        إرجاع عدم;
    total = size + ALIGN + حجم(*hdr);
    base  = malloc(total);
    إذا (!base)
        إرجاع عدم;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + حجم(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    إرجاع ptr;
}

ساكن AsanAlignedHeader *asan_aligned_header(فراغ *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, حجم(*hdr));
    إرجاع hdr;
}

ساكن فراغ asan_aligned_free(فراغ *ptr)
{
    إذا (ptr)
        حرر(asan_aligned_header(ptr)->base);
}

ساكن فراغ *asan_aligned_realloc(فراغ *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    فراغ *ret;

    إذا (!ptr)
        إرجاع asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    إذا (!ret)
        إرجاع عدم;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    حرر(hdr->base);
    إرجاع ret;
}
#وإلا
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

ساكن atomic_size_t max_alloc_size = INT_MAX;

فراغ av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

ساكن صحيح size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#إذا (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    إذا (__builtin_mul_overflow(a, b, &t))
        إرجاع AVERROR(EINVAL);
#وإلا
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    إذا ((a | b) >= ((size_t)1 << (حجم(size_t) * 4)) && a && t / a != b)
        إرجاع AVERROR(EINVAL);
#endif
    *r = t;
    إرجاع 0;
}

فراغ *av_malloc(size_t size)
{
    فراغ *ptr = عدم;

    إذا (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        إرجاع عدم;

#إذا ASAN_ALIGNED_ALLOC
    إذا (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    وإلا
        ptr = _aligned_malloc(size, ALIGN);
#وإلاإذا HAVE_POSIX_MEMALIGN
    إذا (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    إذا (posix_memalign(&ptr, ALIGN, size))
        ptr = عدم;
#وإلاإذا HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#وإلاإذا HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#وإلا
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
#وإلا
    ptr = malloc(size);
#endif
    إذا(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    إذا (ptr)
        poison_memory(ptr, size);
    إرجاع ptr;
}

فراغ *av_realloc(فراغ *ptr, size_t size)
{
    فراغ *ret;
    إذا (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        إرجاع عدم;

#إذا ASAN_ALIGNED_ALLOC
    إذا (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    وإلا
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#وإلاإذا HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#وإلا
    ret = realloc(ptr, size + !size);
#endif
    إذا (ret && !ptr)
        poison_memory(ret, size);
    إرجاع ret;
}

فراغ *av_realloc_f(فراغ *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    فراغ *r;

    إذا (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        إرجاع عدم;
    }
    r = av_realloc(ptr, size);
    إذا (!r)
        av_free(ptr);
    إرجاع r;
}

صحيح av_reallocp(فراغ *ptr, size_t size)
{
    فراغ *val;

    إذا (!size) {
        av_freep(ptr);
        إرجاع 0;
    }

    memcpy(&val, ptr, حجم(val));
    val = av_realloc(val, size);

    إذا (!val) {
        av_freep(ptr);
        إرجاع AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, حجم(val));
    إرجاع 0;
}

فراغ *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    إذا (size_mult(nmemb, size, &result) < 0)
        إرجاع عدم;
    إرجاع av_malloc(result);
}

فراغ *av_realloc_array(فراغ *ptr, size_t nmemb, size_t size)
{
    size_t result;
    إذا (size_mult(nmemb, size, &result) < 0)
        إرجاع عدم;
    إرجاع av_realloc(ptr, result);
}

صحيح av_reallocp_array(فراغ *ptr, size_t nmemb, size_t size)
{
    فراغ *val;

    memcpy(&val, ptr, حجم(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, حجم(val));
    إذا (!val && nmemb && size)
        إرجاع AVERROR(ENOMEM);

    إرجاع 0;
}

فراغ av_free(فراغ *ptr)
{
#إذا ASAN_ALIGNED_ALLOC
    إذا (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    وإلا
        _aligned_free(ptr);
#وإلاإذا HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#وإلا
    حرر(ptr);
#endif
}

فراغ av_freep(فراغ *arg)
{
    فراغ *val;

    memcpy(&val, arg, حجم(val));
    memcpy(arg, &(فراغ *){ عدم }, حجم(val));
    av_free(val);
}

فراغ *av_mallocz(size_t size)
{
    فراغ *ptr = av_malloc(size);
    إذا (ptr)
        memset(ptr, 0, size);
    إرجاع ptr;
}

فراغ *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    إذا (size_mult(nmemb, size, &result) < 0)
        إرجاع عدم;
    إرجاع av_mallocz(result);
}

حرف *av_strdup(ثابت حرف *s)
{
    حرف *ptr = عدم;
    إذا (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(عدم, len);
        إذا (ptr)
            memcpy(ptr, s, len);
    }
    إرجاع ptr;
}

حرف *av_strndup(ثابت حرف *s, size_t len)
{
    إذا (!s)
        إرجاع عدم;

    ثابت حرف *end = memchr(s, 0, len);
    إذا (end)
        len = end - s;

    حرف *ret = av_realloc(عدم, len + 1);
    إذا (!ret)
        إرجاع عدم;

    memcpy(ret, s, len);
    ret[len] = 0;
    إرجاع ret;
}

فراغ *av_memdup(ثابت فراغ *p, size_t size)
{
    فراغ *ptr = عدم;
    إذا (p) {
        ptr = av_malloc(size);
        إذا (ptr)
            memcpy(ptr, p, size);
    }
    إرجاع ptr;
}

صحيح av_dynarray_add_nofree(فراغ *tab_ptr, صحيح *nb_ptr, فراغ *elem)
{
    فراغ **tab;
    memcpy(&tab, tab_ptr, حجم(tab));

    FF_DYNARRAY_ADD(INT_MAX, حجم(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, حجم(tab));
    }, {
        إرجاع AVERROR(ENOMEM);
    });
    إرجاع 0;
}

فراغ av_dynarray_add(فراغ *tab_ptr, صحيح *nb_ptr, فراغ *elem)
{
    فراغ **tab;
    memcpy(&tab, tab_ptr, حجم(tab));

    FF_DYNARRAY_ADD(INT_MAX, حجم(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, حجم(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

فراغ *av_dynarray2_add(فراغ **tab_ptr, صحيح *nb_ptr, size_t elem_size,
                       ثابت uint8_t *elem_data)
{
    uint8_t *tab_elem_data = عدم;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        إذا (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        وإلا
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    إرجاع tab_elem_data;
}

ساكن فراغ fill16(uint8_t *dst, صحيح len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    بينما (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    بينما (len--) {
        *dst = dst[-2];
        dst++;
    }
}

ساكن فراغ fill24(uint8_t *dst, صحيح len)
{
#إذا HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#وإلا
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    بينما (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    إذا (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    إذا (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    بينما (len--) {
        *dst = dst[-3];
        dst++;
    }
}

ساكن فراغ fill32(uint8_t *dst, صحيح len)
{
    uint32_t v = AV_RN32(dst - 4);

#إذا HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    بينما (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    بينما (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    بينما (len--) {
        *dst = dst[-4];
        dst++;
    }
}

فراغ av_memcpy_backptr(uint8_t *dst, صحيح back, صحيح cnt)
{
    ثابت uint8_t *src = &dst[-back];
    إذا (!back)
        إرجاع;

    إذا (back == 1) {
        memset(dst, *src, cnt);
    } وإلا إذا (back == 2) {
        fill16(dst, cnt);
    } وإلا إذا (back == 3) {
        fill24(dst, cnt);
    } وإلا إذا (back == 4) {
        fill32(dst, cnt);
    } وإلا {
        إذا (cnt >= 16) {
            صحيح blocklen = back;
            بينما (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            إرجاع;
        }
        إذا (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        إذا (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        إذا (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        إذا (cnt)
            *dst = *src;
    }
}

فراغ *av_fast_realloc(فراغ *ptr, unsigned صحيح *size, size_t min_size)
{
    size_t max_size;

    إذا (min_size <= *size)
        إرجاع ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    إذا (min_size > max_size) {
        *size = 0;
        إرجاع عدم;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    إذا (!ptr)
        min_size = 0;

    *size = min_size;

    إرجاع ptr;
}

ساكن مضمن فراغ fast_malloc(فراغ *ptr, unsigned صحيح *size, size_t min_size, صحيح zero_realloc)
{
    size_t max_size;
    فراغ *val;

    memcpy(&val, ptr, حجم(val));
    إذا (min_size <= *size) {
        av_assert0(val || !min_size);
        إرجاع;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    إذا (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        إرجاع;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, حجم(val));
    إذا (!val)
        min_size = 0;
    *size = min_size;
    إرجاع;
}

فراغ av_fast_malloc(فراغ *ptr, unsigned صحيح *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

فراغ av_fast_mallocz(فراغ *ptr, unsigned صحيح *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

صحيح av_size_mult(size_t a, size_t b, size_t *r)
{
    إرجاع size_mult(a, b, r);
}

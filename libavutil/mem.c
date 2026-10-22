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
#𐡄𐡍 HAVE_MALLOC_H
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
#𐡄𐡍 CONFIG_MEMORY_POISONING
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
#𐡄𐡍 HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

ساكن صحيح asan_aligned_alloc_needed(فراغ)
{
    ساكن atomic_int needed = -1;
    صحيح ret = atomic_load_explicit(&needed, memory_order_relaxed);

    𐡄𐡍 (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        صحيح probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        𐡄𐡍 (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    أرجع ret;
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

    𐡄𐡍 (size > SIZE_MAX - ALIGN - حجم(*hdr))
        أرجع عدم;
    total = size + ALIGN + حجم(*hdr);
    base  = malloc(total);
    𐡄𐡍 (!base)
        أرجع عدم;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + حجم(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    أرجع ptr;
}

ساكن AsanAlignedHeader *asan_aligned_header(فراغ *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, حجم(*hdr));
    أرجع hdr;
}

ساكن فراغ asan_aligned_free(فراغ *ptr)
{
    𐡄𐡍 (ptr)
        حرر(asan_aligned_header(ptr)->base);
}

ساكن فراغ *asan_aligned_realloc(فراغ *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    فراغ *ret;

    𐡄𐡍 (!ptr)
        أرجع asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    𐡄𐡍 (!ret)
        أرجع عدم;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    حرر(hdr->base);
    أرجع ret;
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

#𐡄𐡍 (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    𐡄𐡍 (__builtin_mul_overflow(a, b, &t))
        أرجع AVERROR(EINVAL);
#وإلا
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    𐡄𐡍 ((a | b) >= ((size_t)1 << (حجم(size_t) * 4)) && a && t / a != b)
        أرجع AVERROR(EINVAL);
#endif
    *r = t;
    أرجع 0;
}

فراغ *av_malloc(size_t size)
{
    فراغ *ptr = عدم;

    𐡄𐡍 (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        أرجع عدم;

#𐡄𐡍 ASAN_ALIGNED_ALLOC
    𐡄𐡍 (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    وإلا
        ptr = _aligned_malloc(size, ALIGN);
#وإلاإذا HAVE_POSIX_MEMALIGN
    𐡄𐡍 (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    𐡄𐡍 (posix_memalign(&ptr, ALIGN, size))
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
    𐡄𐡍(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    𐡄𐡍 (ptr)
        poison_memory(ptr, size);
    أرجع ptr;
}

فراغ *av_realloc(فراغ *ptr, size_t size)
{
    فراغ *ret;
    𐡄𐡍 (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        أرجع عدم;

#𐡄𐡍 ASAN_ALIGNED_ALLOC
    𐡄𐡍 (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    وإلا
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#وإلاإذا HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#وإلا
    ret = realloc(ptr, size + !size);
#endif
    𐡄𐡍 (ret && !ptr)
        poison_memory(ret, size);
    أرجع ret;
}

فراغ *av_realloc_f(فراغ *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    فراغ *r;

    𐡄𐡍 (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        أرجع عدم;
    }
    r = av_realloc(ptr, size);
    𐡄𐡍 (!r)
        av_free(ptr);
    أرجع r;
}

صحيح av_reallocp(فراغ *ptr, size_t size)
{
    فراغ *val;

    𐡄𐡍 (!size) {
        av_freep(ptr);
        أرجع 0;
    }

    memcpy(&val, ptr, حجم(val));
    val = av_realloc(val, size);

    𐡄𐡍 (!val) {
        av_freep(ptr);
        أرجع AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, حجم(val));
    أرجع 0;
}

فراغ *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    𐡄𐡍 (size_mult(nmemb, size, &result) < 0)
        أرجع عدم;
    أرجع av_malloc(result);
}

فراغ *av_realloc_array(فراغ *ptr, size_t nmemb, size_t size)
{
    size_t result;
    𐡄𐡍 (size_mult(nmemb, size, &result) < 0)
        أرجع عدم;
    أرجع av_realloc(ptr, result);
}

صحيح av_reallocp_array(فراغ *ptr, size_t nmemb, size_t size)
{
    فراغ *val;

    memcpy(&val, ptr, حجم(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, حجم(val));
    𐡄𐡍 (!val && nmemb && size)
        أرجع AVERROR(ENOMEM);

    أرجع 0;
}

فراغ av_free(فراغ *ptr)
{
#𐡄𐡍 ASAN_ALIGNED_ALLOC
    𐡄𐡍 (asan_aligned_alloc_needed())
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
    𐡄𐡍 (ptr)
        memset(ptr, 0, size);
    أرجع ptr;
}

فراغ *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    𐡄𐡍 (size_mult(nmemb, size, &result) < 0)
        أرجع عدم;
    أرجع av_mallocz(result);
}

حرف *av_strdup(ثابت حرف *s)
{
    حرف *ptr = عدم;
    𐡄𐡍 (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(عدم, len);
        𐡄𐡍 (ptr)
            memcpy(ptr, s, len);
    }
    أرجع ptr;
}

حرف *av_strndup(ثابت حرف *s, size_t len)
{
    𐡄𐡍 (!s)
        أرجع عدم;

    ثابت حرف *end = memchr(s, 0, len);
    𐡄𐡍 (end)
        len = end - s;

    حرف *ret = av_realloc(عدم, len + 1);
    𐡄𐡍 (!ret)
        أرجع عدم;

    memcpy(ret, s, len);
    ret[len] = 0;
    أرجع ret;
}

فراغ *av_memdup(ثابت فراغ *p, size_t size)
{
    فراغ *ptr = عدم;
    𐡄𐡍 (p) {
        ptr = av_malloc(size);
        𐡄𐡍 (ptr)
            memcpy(ptr, p, size);
    }
    أرجع ptr;
}

صحيح av_dynarray_add_nofree(فراغ *tab_ptr, صحيح *nb_ptr, فراغ *elem)
{
    فراغ **tab;
    memcpy(&tab, tab_ptr, حجم(tab));

    FF_DYNARRAY_ADD(INT_MAX, حجم(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, حجم(tab));
    }, {
        أرجع AVERROR(ENOMEM);
    });
    أرجع 0;
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
        𐡄𐡍 (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        وإلا
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    أرجع tab_elem_data;
}

ساكن فراغ fill16(uint8_t *dst, صحيح len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    طالما (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    طالما (len--) {
        *dst = dst[-2];
        dst++;
    }
}

ساكن فراغ fill24(uint8_t *dst, صحيح len)
{
#𐡄𐡍 HAVE_BIGENDIAN
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

    طالما (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    𐡄𐡍 (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    𐡄𐡍 (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    طالما (len--) {
        *dst = dst[-3];
        dst++;
    }
}

ساكن فراغ fill32(uint8_t *dst, صحيح len)
{
    uint32_t v = AV_RN32(dst - 4);

#𐡄𐡍 HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    طالما (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    طالما (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    طالما (len--) {
        *dst = dst[-4];
        dst++;
    }
}

فراغ av_memcpy_backptr(uint8_t *dst, صحيح back, صحيح cnt)
{
    ثابت uint8_t *src = &dst[-back];
    𐡄𐡍 (!back)
        أرجع;

    𐡄𐡍 (back == 1) {
        memset(dst, *src, cnt);
    } وإلا 𐡄𐡍 (back == 2) {
        fill16(dst, cnt);
    } وإلا 𐡄𐡍 (back == 3) {
        fill24(dst, cnt);
    } وإلا 𐡄𐡍 (back == 4) {
        fill32(dst, cnt);
    } وإلا {
        𐡄𐡍 (cnt >= 16) {
            صحيح blocklen = back;
            طالما (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            أرجع;
        }
        𐡄𐡍 (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        𐡄𐡍 (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        𐡄𐡍 (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        𐡄𐡍 (cnt)
            *dst = *src;
    }
}

فراغ *av_fast_realloc(فراغ *ptr, unsigned صحيح *size, size_t min_size)
{
    size_t max_size;

    𐡄𐡍 (min_size <= *size)
        أرجع ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    𐡄𐡍 (min_size > max_size) {
        *size = 0;
        أرجع عدم;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    𐡄𐡍 (!ptr)
        min_size = 0;

    *size = min_size;

    أرجع ptr;
}

ساكن مضمن فراغ fast_malloc(فراغ *ptr, unsigned صحيح *size, size_t min_size, صحيح zero_realloc)
{
    size_t max_size;
    فراغ *val;

    memcpy(&val, ptr, حجم(val));
    𐡄𐡍 (min_size <= *size) {
        av_assert0(val || !min_size);
        أرجع;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    𐡄𐡍 (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        أرجع;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, حجم(val));
    𐡄𐡍 (!val)
        min_size = 0;
    *size = min_size;
    أرجع;
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
    أرجع size_mult(a, b, r);
}

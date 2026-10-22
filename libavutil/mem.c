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

#அந்தர்பாவ "config.h"

#அந்தர்பாவ <limits.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <stdlib.h>
#அந்தர்பாவ <stdatomic.h>
#அந்தர்பாவ <string.h>
#எனில் HAVE_MALLOC_H
#அந்தர்பாவ <malloc.h>
#endif

#அந்தர்பாவ "attributes.h"
#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "dynarray.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "internal.h"
#அந்தர்பாவ "intreadwrite.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define விடுவி           AV_JOIN(MALLOC_PREFIX, விடுவி)

வெறுமை *malloc(size_t size);
வெறுமை *memalign(size_t align, size_t size);
முழு   posix_memalign(வெறுமை **ptr, size_t align, size_t size);
வெறுமை *realloc(வெறுமை *ptr, size_t size);
வெறுமை  விடுவி(வெறுமை *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

நிலையான வெறுமை poison_memory(வெறுமை *ptr, size_t size)
{
#எனில் CONFIG_MEMORY_POISONING
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
#எனில் HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

நிலையான முழு asan_aligned_alloc_needed(வெறுமை)
{
    நிலையான atomic_int needed = -1;
    முழு ret = atomic_load_explicit(&needed, memory_order_relaxed);

    எனில் (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        முழு probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        எனில் (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    திரும்பு ret;
}

வகைவரை கட்டமைப்பு AsanAlignedHeader {
    வெறுமை  *base;
    size_t size;
} AsanAlignedHeader;

நிலையான வெறுமை *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    எனில் (size > SIZE_MAX - ALIGN - அளவு(*hdr))
        திரும்பு வெற்று;
    total = size + ALIGN + அளவு(*hdr);
    base  = malloc(total);
    எனில் (!base)
        திரும்பு வெற்று;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + அளவு(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    திரும்பு ptr;
}

நிலையான AsanAlignedHeader *asan_aligned_header(வெறுமை *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, அளவு(*hdr));
    திரும்பு hdr;
}

நிலையான வெறுமை asan_aligned_free(வெறுமை *ptr)
{
    எனில் (ptr)
        விடுவி(asan_aligned_header(ptr)->base);
}

நிலையான வெறுமை *asan_aligned_realloc(வெறுமை *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    வெறுமை *ret;

    எனில் (!ptr)
        திரும்பு asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    எனில் (!ret)
        திரும்பு வெற்று;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    விடுவி(hdr->base);
    திரும்பு ret;
}
#இல்லையெனில்
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

நிலையான atomic_size_t max_alloc_size = INT_MAX;

வெறுமை av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

நிலையான முழு size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#எனில் (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    எனில் (__builtin_mul_overflow(a, b, &t))
        திரும்பு AVERROR(EINVAL);
#இல்லையெனில்
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    எனில் ((a | b) >= ((size_t)1 << (அளவு(size_t) * 4)) && a && t / a != b)
        திரும்பு AVERROR(EINVAL);
#endif
    *r = t;
    திரும்பு 0;
}

வெறுமை *av_malloc(size_t size)
{
    வெறுமை *ptr = வெற்று;

    எனில் (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        திரும்பு வெற்று;

#எனில் ASAN_ALIGNED_ALLOC
    எனில் (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    இல்லையெனில்
        ptr = _aligned_malloc(size, ALIGN);
#அல்லதெனில் HAVE_POSIX_MEMALIGN
    எனில் (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    எனில் (posix_memalign(&ptr, ALIGN, size))
        ptr = வெற்று;
#அல்லதெனில் HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#அல்லதெனில் HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#இல்லையெனில்
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
#இல்லையெனில்
    ptr = malloc(size);
#endif
    எனில்(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    எனில் (ptr)
        poison_memory(ptr, size);
    திரும்பு ptr;
}

வெறுமை *av_realloc(வெறுமை *ptr, size_t size)
{
    வெறுமை *ret;
    எனில் (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        திரும்பு வெற்று;

#எனில் ASAN_ALIGNED_ALLOC
    எனில் (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    இல்லையெனில்
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#அல்லதெனில் HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#இல்லையெனில்
    ret = realloc(ptr, size + !size);
#endif
    எனில் (ret && !ptr)
        poison_memory(ret, size);
    திரும்பு ret;
}

வெறுமை *av_realloc_f(வெறுமை *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    வெறுமை *r;

    எனில் (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        திரும்பு வெற்று;
    }
    r = av_realloc(ptr, size);
    எனில் (!r)
        av_free(ptr);
    திரும்பு r;
}

முழு av_reallocp(வெறுமை *ptr, size_t size)
{
    வெறுமை *val;

    எனில் (!size) {
        av_freep(ptr);
        திரும்பு 0;
    }

    memcpy(&val, ptr, அளவு(val));
    val = av_realloc(val, size);

    எனில் (!val) {
        av_freep(ptr);
        திரும்பு AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, அளவு(val));
    திரும்பு 0;
}

வெறுமை *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    எனில் (size_mult(nmemb, size, &result) < 0)
        திரும்பு வெற்று;
    திரும்பு av_malloc(result);
}

வெறுமை *av_realloc_array(வெறுமை *ptr, size_t nmemb, size_t size)
{
    size_t result;
    எனில் (size_mult(nmemb, size, &result) < 0)
        திரும்பு வெற்று;
    திரும்பு av_realloc(ptr, result);
}

முழு av_reallocp_array(வெறுமை *ptr, size_t nmemb, size_t size)
{
    வெறுமை *val;

    memcpy(&val, ptr, அளவு(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, அளவு(val));
    எனில் (!val && nmemb && size)
        திரும்பு AVERROR(ENOMEM);

    திரும்பு 0;
}

வெறுமை av_free(வெறுமை *ptr)
{
#எனில் ASAN_ALIGNED_ALLOC
    எனில் (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    இல்லையெனில்
        _aligned_free(ptr);
#அல்லதெனில் HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#இல்லையெனில்
    விடுவி(ptr);
#endif
}

வெறுமை av_freep(வெறுமை *arg)
{
    வெறுமை *val;

    memcpy(&val, arg, அளவு(val));
    memcpy(arg, &(வெறுமை *){ வெற்று }, அளவு(val));
    av_free(val);
}

வெறுமை *av_mallocz(size_t size)
{
    வெறுமை *ptr = av_malloc(size);
    எனில் (ptr)
        memset(ptr, 0, size);
    திரும்பு ptr;
}

வெறுமை *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    எனில் (size_mult(nmemb, size, &result) < 0)
        திரும்பு வெற்று;
    திரும்பு av_mallocz(result);
}

எழுத்து *av_strdup(மாறிலி எழுத்து *s)
{
    எழுத்து *ptr = வெற்று;
    எனில் (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(வெற்று, len);
        எனில் (ptr)
            memcpy(ptr, s, len);
    }
    திரும்பு ptr;
}

எழுத்து *av_strndup(மாறிலி எழுத்து *s, size_t len)
{
    எனில் (!s)
        திரும்பு வெற்று;

    மாறிலி எழுத்து *end = memchr(s, 0, len);
    எனில் (end)
        len = end - s;

    எழுத்து *ret = av_realloc(வெற்று, len + 1);
    எனில் (!ret)
        திரும்பு வெற்று;

    memcpy(ret, s, len);
    ret[len] = 0;
    திரும்பு ret;
}

வெறுமை *av_memdup(மாறிலி வெறுமை *p, size_t size)
{
    வெறுமை *ptr = வெற்று;
    எனில் (p) {
        ptr = av_malloc(size);
        எனில் (ptr)
            memcpy(ptr, p, size);
    }
    திரும்பு ptr;
}

முழு av_dynarray_add_nofree(வெறுமை *tab_ptr, முழு *nb_ptr, வெறுமை *elem)
{
    வெறுமை **tab;
    memcpy(&tab, tab_ptr, அளவு(tab));

    FF_DYNARRAY_ADD(INT_MAX, அளவு(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, அளவு(tab));
    }, {
        திரும்பு AVERROR(ENOMEM);
    });
    திரும்பு 0;
}

வெறுமை av_dynarray_add(வெறுமை *tab_ptr, முழு *nb_ptr, வெறுமை *elem)
{
    வெறுமை **tab;
    memcpy(&tab, tab_ptr, அளவு(tab));

    FF_DYNARRAY_ADD(INT_MAX, அளவு(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, அளவு(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

வெறுமை *av_dynarray2_add(வெறுமை **tab_ptr, முழு *nb_ptr, size_t elem_size,
                       மாறிலி uint8_t *elem_data)
{
    uint8_t *tab_elem_data = வெற்று;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        எனில் (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        இல்லையெனில்
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    திரும்பு tab_elem_data;
}

நிலையான வெறுமை fill16(uint8_t *dst, முழு len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    போது (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    போது (len--) {
        *dst = dst[-2];
        dst++;
    }
}

நிலையான வெறுமை fill24(uint8_t *dst, முழு len)
{
#எனில் HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#இல்லையெனில்
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    போது (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    எனில் (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    எனில் (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    போது (len--) {
        *dst = dst[-3];
        dst++;
    }
}

நிலையான வெறுமை fill32(uint8_t *dst, முழு len)
{
    uint32_t v = AV_RN32(dst - 4);

#எனில் HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    போது (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    போது (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    போது (len--) {
        *dst = dst[-4];
        dst++;
    }
}

வெறுமை av_memcpy_backptr(uint8_t *dst, முழு back, முழு cnt)
{
    மாறிலி uint8_t *src = &dst[-back];
    எனில் (!back)
        திரும்பு;

    எனில் (back == 1) {
        memset(dst, *src, cnt);
    } இல்லையெனில் எனில் (back == 2) {
        fill16(dst, cnt);
    } இல்லையெனில் எனில் (back == 3) {
        fill24(dst, cnt);
    } இல்லையெனில் எனில் (back == 4) {
        fill32(dst, cnt);
    } இல்லையெனில் {
        எனில் (cnt >= 16) {
            முழு blocklen = back;
            போது (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            திரும்பு;
        }
        எனில் (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        எனில் (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        எனில் (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        எனில் (cnt)
            *dst = *src;
    }
}

வெறுமை *av_fast_realloc(வெறுமை *ptr, unsigned முழு *size, size_t min_size)
{
    size_t max_size;

    எனில் (min_size <= *size)
        திரும்பு ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    எனில் (min_size > max_size) {
        *size = 0;
        திரும்பு வெற்று;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    எனில் (!ptr)
        min_size = 0;

    *size = min_size;

    திரும்பு ptr;
}

நிலையான உள்வரி வெறுமை fast_malloc(வெறுமை *ptr, unsigned முழு *size, size_t min_size, முழு zero_realloc)
{
    size_t max_size;
    வெறுமை *val;

    memcpy(&val, ptr, அளவு(val));
    எனில் (min_size <= *size) {
        av_assert0(val || !min_size);
        திரும்பு;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    எனில் (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        திரும்பு;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, அளவு(val));
    எனில் (!val)
        min_size = 0;
    *size = min_size;
    திரும்பு;
}

வெறுமை av_fast_malloc(வெறுமை *ptr, unsigned முழு *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

வெறுமை av_fast_mallocz(வெறுமை *ptr, unsigned முழு *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

முழு av_size_mult(size_t a, size_t b, size_t *r)
{
    திரும்பு size_mult(a, b, r);
}

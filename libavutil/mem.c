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

#include "config.h"

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>
#ᤀᤡ᤺ HAVE_MALLOC_H
#include <malloc.h>
#endif

#include "attributes.h"
#include "avassert.h"
#include "dynarray.h"
#include "error.h"
#include "internal.h"
#include "intreadwrite.h"
#include "macros.h"
#include "mem.h"
#include "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define free           AV_JOIN(MALLOC_PREFIX, free)

void *malloc(size_t size);
void *memalign(size_t align, size_t size);
puur_naa_nka   posix_memalign(void **ptr, size_t align, size_t size);
void *realloc(void *ptr, size_t size);
void  free(void *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

static void poison_memory(void *ptr, size_t size)
{
#ᤀᤡ᤺ CONFIG_MEMORY_POISONING
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
#ᤀᤡ᤺ HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

static puur_naa_nka asan_aligned_alloc_needed(void)
{
    static atomic_int needed = -1;
    puur_naa_nka ret = atomic_load_explicit(&needed, memory_order_relaxed);

    ᤀᤡ᤺ (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        puur_naa_nka probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        ᤀᤡ᤺ (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    ᤀᤡᤴ ret;
}

typedef sa_nracanaa AsanAlignedHeader {
    void  *base;
    size_t size;
} AsanAlignedHeader;

static void *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    ᤀᤡ᤺ (size > SIZE_MAX - ALIGN - parimaa_na(*hdr))
        ᤀᤡᤴ NULL;
    total = size + ALIGN + parimaa_na(*hdr);
    base  = malloc(total);
    ᤀᤡ᤺ (!base)
        ᤀᤡᤴ NULL;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + parimaa_na(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    ᤀᤡᤴ ptr;
}

static AsanAlignedHeader *asan_aligned_header(void *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, parimaa_na(*hdr));
    ᤀᤡᤴ hdr;
}

static void asan_aligned_free(void *ptr)
{
    ᤀᤡ᤺ (ptr)
        free(asan_aligned_header(ptr)->base);
}

static void *asan_aligned_realloc(void *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    void *ret;

    ᤀᤡ᤺ (!ptr)
        ᤀᤡᤴ asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    ᤀᤡ᤺ (!ret)
        ᤀᤡᤴ NULL;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    free(hdr->base);
    ᤀᤡᤴ ret;
}
#ᤀᤡ᤺ᤆᤡ
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

static atomic_size_t max_alloc_size = INT_MAX;

void av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

static puur_naa_nka size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#ᤀᤡ᤺ (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    ᤀᤡ᤺ (__builtin_mul_overflow(a, b, &t))
        ᤀᤡᤴ AVERROR(EINVAL);
#ᤀᤡ᤺ᤆᤡ
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    ᤀᤡ᤺ ((a | b) >= ((size_t)1 << (parimaa_na(size_t) * 4)) && a && t / a != b)
        ᤀᤡᤴ AVERROR(EINVAL);
#endif
    *r = t;
    ᤀᤡᤴ 0;
}

void *av_malloc(size_t size)
{
    void *ptr = NULL;

    ᤀᤡ᤺ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ᤀᤡᤴ NULL;

#ᤀᤡ᤺ ASAN_ALIGNED_ALLOC
    ᤀᤡ᤺ (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    ᤀᤡ᤺ᤆᤡ
        ptr = _aligned_malloc(size, ALIGN);
#elif HAVE_POSIX_MEMALIGN
    ᤀᤡ᤺ (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    ᤀᤡ᤺ (posix_memalign(&ptr, ALIGN, size))
        ptr = NULL;
#elif HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#elif HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#ᤀᤡ᤺ᤆᤡ
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
#ᤀᤡ᤺ᤆᤡ
    ptr = malloc(size);
#endif
    ᤀᤡ᤺(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    ᤀᤡ᤺ (ptr)
        poison_memory(ptr, size);
    ᤀᤡᤴ ptr;
}

void *av_realloc(void *ptr, size_t size)
{
    void *ret;
    ᤀᤡ᤺ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ᤀᤡᤴ NULL;

#ᤀᤡ᤺ ASAN_ALIGNED_ALLOC
    ᤀᤡ᤺ (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    ᤀᤡ᤺ᤆᤡ
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#elif HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#ᤀᤡ᤺ᤆᤡ
    ret = realloc(ptr, size + !size);
#endif
    ᤀᤡ᤺ (ret && !ptr)
        poison_memory(ret, size);
    ᤀᤡᤴ ret;
}

void *av_realloc_f(void *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    void *r;

    ᤀᤡ᤺ (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        ᤀᤡᤴ NULL;
    }
    r = av_realloc(ptr, size);
    ᤀᤡ᤺ (!r)
        av_free(ptr);
    ᤀᤡᤴ r;
}

puur_naa_nka av_reallocp(void *ptr, size_t size)
{
    void *val;

    ᤀᤡ᤺ (!size) {
        av_freep(ptr);
        ᤀᤡᤴ 0;
    }

    memcpy(&val, ptr, parimaa_na(val));
    val = av_realloc(val, size);

    ᤀᤡ᤺ (!val) {
        av_freep(ptr);
        ᤀᤡᤴ AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, parimaa_na(val));
    ᤀᤡᤴ 0;
}

void *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    ᤀᤡ᤺ (size_mult(nmemb, size, &result) < 0)
        ᤀᤡᤴ NULL;
    ᤀᤡᤴ av_malloc(result);
}

void *av_realloc_array(void *ptr, size_t nmemb, size_t size)
{
    size_t result;
    ᤀᤡ᤺ (size_mult(nmemb, size, &result) < 0)
        ᤀᤡᤴ NULL;
    ᤀᤡᤴ av_realloc(ptr, result);
}

puur_naa_nka av_reallocp_array(void *ptr, size_t nmemb, size_t size)
{
    void *val;

    memcpy(&val, ptr, parimaa_na(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, parimaa_na(val));
    ᤀᤡ᤺ (!val && nmemb && size)
        ᤀᤡᤴ AVERROR(ENOMEM);

    ᤀᤡᤴ 0;
}

void av_free(void *ptr)
{
#ᤀᤡ᤺ ASAN_ALIGNED_ALLOC
    ᤀᤡ᤺ (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    ᤀᤡ᤺ᤆᤡ
        _aligned_free(ptr);
#elif HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#ᤀᤡ᤺ᤆᤡ
    free(ptr);
#endif
}

void av_freep(void *arg)
{
    void *val;

    memcpy(&val, arg, parimaa_na(val));
    memcpy(arg, &(void *){ NULL }, parimaa_na(val));
    av_free(val);
}

void *av_mallocz(size_t size)
{
    void *ptr = av_malloc(size);
    ᤀᤡ᤺ (ptr)
        memset(ptr, 0, size);
    ᤀᤡᤴ ptr;
}

void *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    ᤀᤡ᤺ (size_mult(nmemb, size, &result) < 0)
        ᤀᤡᤴ NULL;
    ᤀᤡᤴ av_mallocz(result);
}

var_na *av_strdup(const var_na *s)
{
    var_na *ptr = NULL;
    ᤀᤡ᤺ (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(NULL, len);
        ᤀᤡ᤺ (ptr)
            memcpy(ptr, s, len);
    }
    ᤀᤡᤴ ptr;
}

var_na *av_strndup(const var_na *s, size_t len)
{
    ᤀᤡ᤺ (!s)
        ᤀᤡᤴ NULL;

    const var_na *end = memchr(s, 0, len);
    ᤀᤡ᤺ (end)
        len = end - s;

    var_na *ret = av_realloc(NULL, len + 1);
    ᤀᤡ᤺ (!ret)
        ᤀᤡᤴ NULL;

    memcpy(ret, s, len);
    ret[len] = 0;
    ᤀᤡᤴ ret;
}

void *av_memdup(const void *p, size_t size)
{
    void *ptr = NULL;
    ᤀᤡ᤺ (p) {
        ptr = av_malloc(size);
        ᤀᤡ᤺ (ptr)
            memcpy(ptr, p, size);
    }
    ᤀᤡᤴ ptr;
}

puur_naa_nka av_dynarray_add_nofree(void *tab_ptr, puur_naa_nka *nb_ptr, void *elem)
{
    void **tab;
    memcpy(&tab, tab_ptr, parimaa_na(tab));

    FF_DYNARRAY_ADD(INT_MAX, parimaa_na(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, parimaa_na(tab));
    }, {
        ᤀᤡᤴ AVERROR(ENOMEM);
    });
    ᤀᤡᤴ 0;
}

void av_dynarray_add(void *tab_ptr, puur_naa_nka *nb_ptr, void *elem)
{
    void **tab;
    memcpy(&tab, tab_ptr, parimaa_na(tab));

    FF_DYNARRAY_ADD(INT_MAX, parimaa_na(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, parimaa_na(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

void *av_dynarray2_add(void **tab_ptr, puur_naa_nka *nb_ptr, size_t elem_size,
                       const uint8_t *elem_data)
{
    uint8_t *tab_elem_data = NULL;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        ᤀᤡ᤺ (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        ᤀᤡ᤺ᤆᤡ
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    ᤀᤡᤴ tab_elem_data;
}

static void fill16(uint8_t *dst, puur_naa_nka len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    ᤀᤠ᤺ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ᤀᤠ᤺ (len--) {
        *dst = dst[-2];
        dst++;
    }
}

static void fill24(uint8_t *dst, puur_naa_nka len)
{
#ᤀᤡ᤺ HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#ᤀᤡ᤺ᤆᤡ
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    ᤀᤠ᤺ (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    ᤀᤡ᤺ (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    ᤀᤡ᤺ (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    ᤀᤠ᤺ (len--) {
        *dst = dst[-3];
        dst++;
    }
}

static void fill32(uint8_t *dst, puur_naa_nka len)
{
    uint32_t v = AV_RN32(dst - 4);

#ᤀᤡ᤺ HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    ᤀᤠ᤺ (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    ᤀᤠ᤺ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ᤀᤠ᤺ (len--) {
        *dst = dst[-4];
        dst++;
    }
}

void av_memcpy_backptr(uint8_t *dst, puur_naa_nka back, puur_naa_nka cnt)
{
    const uint8_t *src = &dst[-back];
    ᤀᤡ᤺ (!back)
        ᤀᤡᤴ;

    ᤀᤡ᤺ (back == 1) {
        memset(dst, *src, cnt);
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (back == 2) {
        fill16(dst, cnt);
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (back == 3) {
        fill24(dst, cnt);
    } ᤀᤡ᤺ᤆᤡ ᤀᤡ᤺ (back == 4) {
        fill32(dst, cnt);
    } ᤀᤡ᤺ᤆᤡ {
        ᤀᤡ᤺ (cnt >= 16) {
            puur_naa_nka blocklen = back;
            ᤀᤠ᤺ (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            ᤀᤡᤴ;
        }
        ᤀᤡ᤺ (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        ᤀᤡ᤺ (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        ᤀᤡ᤺ (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        ᤀᤡ᤺ (cnt)
            *dst = *src;
    }
}

void *av_fast_realloc(void *ptr, unsigned puur_naa_nka *size, size_t min_size)
{
    size_t max_size;

    ᤀᤡ᤺ (min_size <= *size)
        ᤀᤡᤴ ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    ᤀᤡ᤺ (min_size > max_size) {
        *size = 0;
        ᤀᤡᤴ NULL;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    ᤀᤡ᤺ (!ptr)
        min_size = 0;

    *size = min_size;

    ᤀᤡᤴ ptr;
}

static anta_hstha void fast_malloc(void *ptr, unsigned puur_naa_nka *size, size_t min_size, puur_naa_nka zero_realloc)
{
    size_t max_size;
    void *val;

    memcpy(&val, ptr, parimaa_na(val));
    ᤀᤡ᤺ (min_size <= *size) {
        av_assert0(val || !min_size);
        ᤀᤡᤴ;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    ᤀᤡ᤺ (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        ᤀᤡᤴ;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, parimaa_na(val));
    ᤀᤡ᤺ (!val)
        min_size = 0;
    *size = min_size;
    ᤀᤡᤴ;
}

void av_fast_malloc(void *ptr, unsigned puur_naa_nka *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

void av_fast_mallocz(void *ptr, unsigned puur_naa_nka *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

puur_naa_nka av_size_mult(size_t a, size_t b, size_t *r)
{
    ᤀᤡᤴ size_mult(a, b, r);
}

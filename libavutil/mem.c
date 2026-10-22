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
#如果 HAVE_MALLOC_H
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
整数   posix_memalign(void **ptr, size_t align, size_t size);
void *realloc(void *ptr, size_t size);
void  free(void *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

static void poison_memory(void *ptr, size_t size)
{
#如果 CONFIG_MEMORY_POISONING
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
#如果 HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

static 整数 asan_aligned_alloc_needed(void)
{
    static atomic_int needed = -1;
    整数 ret = atomic_load_explicit(&needed, memory_order_relaxed);

    如果 (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        整数 probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        如果 (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    返回 ret;
}

typedef struct AsanAlignedHeader {
    void  *base;
    size_t size;
} AsanAlignedHeader;

static void *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    如果 (size > SIZE_MAX - ALIGN - sizeof(*hdr))
        返回 NULL;
    total = size + ALIGN + sizeof(*hdr);
    base  = malloc(total);
    如果 (!base)
        返回 NULL;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + sizeof(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    返回 ptr;
}

static AsanAlignedHeader *asan_aligned_header(void *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, sizeof(*hdr));
    返回 hdr;
}

static void asan_aligned_free(void *ptr)
{
    如果 (ptr)
        free(asan_aligned_header(ptr)->base);
}

static void *asan_aligned_realloc(void *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    void *ret;

    如果 (!ptr)
        返回 asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    如果 (!ret)
        返回 NULL;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    free(hdr->base);
    返回 ret;
}
#否则
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

static 整数 size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#如果 (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    如果 (__builtin_mul_overflow(a, b, &t))
        返回 AVERROR(EINVAL);
#否则
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    如果 ((a | b) >= ((size_t)1 << (sizeof(size_t) * 4)) && a && t / a != b)
        返回 AVERROR(EINVAL);
#endif
    *r = t;
    返回 0;
}

void *av_malloc(size_t size)
{
    void *ptr = NULL;

    如果 (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        返回 NULL;

#如果 ASAN_ALIGNED_ALLOC
    如果 (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    否则
        ptr = _aligned_malloc(size, ALIGN);
#elif HAVE_POSIX_MEMALIGN
    如果 (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    如果 (posix_memalign(&ptr, ALIGN, size))
        ptr = NULL;
#elif HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#elif HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#否则
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
#否则
    ptr = malloc(size);
#endif
    如果(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    如果 (ptr)
        poison_memory(ptr, size);
    返回 ptr;
}

void *av_realloc(void *ptr, size_t size)
{
    void *ret;
    如果 (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        返回 NULL;

#如果 ASAN_ALIGNED_ALLOC
    如果 (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    否则
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#elif HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#否则
    ret = realloc(ptr, size + !size);
#endif
    如果 (ret && !ptr)
        poison_memory(ret, size);
    返回 ret;
}

void *av_realloc_f(void *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    void *r;

    如果 (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        返回 NULL;
    }
    r = av_realloc(ptr, size);
    如果 (!r)
        av_free(ptr);
    返回 r;
}

整数 av_reallocp(void *ptr, size_t size)
{
    void *val;

    如果 (!size) {
        av_freep(ptr);
        返回 0;
    }

    memcpy(&val, ptr, sizeof(val));
    val = av_realloc(val, size);

    如果 (!val) {
        av_freep(ptr);
        返回 AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, sizeof(val));
    返回 0;
}

void *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    如果 (size_mult(nmemb, size, &result) < 0)
        返回 NULL;
    返回 av_malloc(result);
}

void *av_realloc_array(void *ptr, size_t nmemb, size_t size)
{
    size_t result;
    如果 (size_mult(nmemb, size, &result) < 0)
        返回 NULL;
    返回 av_realloc(ptr, result);
}

整数 av_reallocp_array(void *ptr, size_t nmemb, size_t size)
{
    void *val;

    memcpy(&val, ptr, sizeof(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, sizeof(val));
    如果 (!val && nmemb && size)
        返回 AVERROR(ENOMEM);

    返回 0;
}

void av_free(void *ptr)
{
#如果 ASAN_ALIGNED_ALLOC
    如果 (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    否则
        _aligned_free(ptr);
#elif HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#否则
    free(ptr);
#endif
}

void av_freep(void *arg)
{
    void *val;

    memcpy(&val, arg, sizeof(val));
    memcpy(arg, &(void *){ NULL }, sizeof(val));
    av_free(val);
}

void *av_mallocz(size_t size)
{
    void *ptr = av_malloc(size);
    如果 (ptr)
        memset(ptr, 0, size);
    返回 ptr;
}

void *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    如果 (size_mult(nmemb, size, &result) < 0)
        返回 NULL;
    返回 av_mallocz(result);
}

char *av_strdup(const char *s)
{
    char *ptr = NULL;
    如果 (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(NULL, len);
        如果 (ptr)
            memcpy(ptr, s, len);
    }
    返回 ptr;
}

char *av_strndup(const char *s, size_t len)
{
    如果 (!s)
        返回 NULL;

    const char *end = memchr(s, 0, len);
    如果 (end)
        len = end - s;

    char *ret = av_realloc(NULL, len + 1);
    如果 (!ret)
        返回 NULL;

    memcpy(ret, s, len);
    ret[len] = 0;
    返回 ret;
}

void *av_memdup(const void *p, size_t size)
{
    void *ptr = NULL;
    如果 (p) {
        ptr = av_malloc(size);
        如果 (ptr)
            memcpy(ptr, p, size);
    }
    返回 ptr;
}

整数 av_dynarray_add_nofree(void *tab_ptr, 整数 *nb_ptr, void *elem)
{
    void **tab;
    memcpy(&tab, tab_ptr, sizeof(tab));

    FF_DYNARRAY_ADD(INT_MAX, sizeof(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, sizeof(tab));
    }, {
        返回 AVERROR(ENOMEM);
    });
    返回 0;
}

void av_dynarray_add(void *tab_ptr, 整数 *nb_ptr, void *elem)
{
    void **tab;
    memcpy(&tab, tab_ptr, sizeof(tab));

    FF_DYNARRAY_ADD(INT_MAX, sizeof(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, sizeof(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

void *av_dynarray2_add(void **tab_ptr, 整数 *nb_ptr, size_t elem_size,
                       const uint8_t *elem_data)
{
    uint8_t *tab_elem_data = NULL;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        如果 (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        否则
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    返回 tab_elem_data;
}

static void fill16(uint8_t *dst, 整数 len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    当 (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    当 (len--) {
        *dst = dst[-2];
        dst++;
    }
}

static void fill24(uint8_t *dst, 整数 len)
{
#如果 HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#否则
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    当 (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    如果 (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    如果 (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    当 (len--) {
        *dst = dst[-3];
        dst++;
    }
}

static void fill32(uint8_t *dst, 整数 len)
{
    uint32_t v = AV_RN32(dst - 4);

#如果 HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    当 (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    当 (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    当 (len--) {
        *dst = dst[-4];
        dst++;
    }
}

void av_memcpy_backptr(uint8_t *dst, 整数 back, 整数 cnt)
{
    const uint8_t *src = &dst[-back];
    如果 (!back)
        返回;

    如果 (back == 1) {
        memset(dst, *src, cnt);
    } 否则 如果 (back == 2) {
        fill16(dst, cnt);
    } 否则 如果 (back == 3) {
        fill24(dst, cnt);
    } 否则 如果 (back == 4) {
        fill32(dst, cnt);
    } 否则 {
        如果 (cnt >= 16) {
            整数 blocklen = back;
            当 (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            返回;
        }
        如果 (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        如果 (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        如果 (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        如果 (cnt)
            *dst = *src;
    }
}

void *av_fast_realloc(void *ptr, unsigned 整数 *size, size_t min_size)
{
    size_t max_size;

    如果 (min_size <= *size)
        返回 ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    如果 (min_size > max_size) {
        *size = 0;
        返回 NULL;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    如果 (!ptr)
        min_size = 0;

    *size = min_size;

    返回 ptr;
}

static inline void fast_malloc(void *ptr, unsigned 整数 *size, size_t min_size, 整数 zero_realloc)
{
    size_t max_size;
    void *val;

    memcpy(&val, ptr, sizeof(val));
    如果 (min_size <= *size) {
        av_assert0(val || !min_size);
        返回;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    如果 (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        返回;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, sizeof(val));
    如果 (!val)
        min_size = 0;
    *size = min_size;
    返回;
}

void av_fast_malloc(void *ptr, unsigned 整数 *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

void av_fast_mallocz(void *ptr, unsigned 整数 *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

整数 av_size_mult(size_t a, size_t b, size_t *r)
{
    返回 size_mult(a, b, r);
}

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
#නම් HAVE_MALLOC_H
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
පූර්ණ_සංඛ්‍යා   posix_memalign(void **ptr, size_t align, size_t size);
void *realloc(void *ptr, size_t size);
void  free(void *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

static void poison_memory(void *ptr, size_t size)
{
#නම් CONFIG_MEMORY_POISONING
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
#නම් HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

static පූර්ණ_සංඛ්‍යා asan_aligned_alloc_needed(void)
{
    static atomic_int needed = -1;
    පූර්ණ_සංඛ්‍යා ret = atomic_load_explicit(&needed, memory_order_relaxed);

    නම් (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        පූර්ණ_සංඛ්‍යා probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        නම් (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    ආපසු ret;
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

    නම් (size > SIZE_MAX - ALIGN - parimaa_na(*hdr))
        ආපසු NULL;
    total = size + ALIGN + parimaa_na(*hdr);
    base  = malloc(total);
    නම් (!base)
        ආපසු NULL;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + parimaa_na(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    ආපසු ptr;
}

static AsanAlignedHeader *asan_aligned_header(void *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, parimaa_na(*hdr));
    ආපසු hdr;
}

static void asan_aligned_free(void *ptr)
{
    නම් (ptr)
        free(asan_aligned_header(ptr)->base);
}

static void *asan_aligned_realloc(void *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    void *ret;

    නම් (!ptr)
        ආපසු asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    නම් (!ret)
        ආපසු NULL;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    free(hdr->base);
    ආපසු ret;
}
#නැතහොත්
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

static පූර්ණ_සංඛ්‍යා size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#නම් (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    නම් (__builtin_mul_overflow(a, b, &t))
        ආපසු AVERROR(EINVAL);
#නැතහොත්
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    නම් ((a | b) >= ((size_t)1 << (parimaa_na(size_t) * 4)) && a && t / a != b)
        ආපසු AVERROR(EINVAL);
#endif
    *r = t;
    ආපසු 0;
}

void *av_malloc(size_t size)
{
    void *ptr = NULL;

    නම් (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ආපසු NULL;

#නම් ASAN_ALIGNED_ALLOC
    නම් (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    නැතහොත්
        ptr = _aligned_malloc(size, ALIGN);
#elif HAVE_POSIX_MEMALIGN
    නම් (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    නම් (posix_memalign(&ptr, ALIGN, size))
        ptr = NULL;
#elif HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#elif HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#නැතහොත්
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
#නැතහොත්
    ptr = malloc(size);
#endif
    නම්(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    නම් (ptr)
        poison_memory(ptr, size);
    ආපසු ptr;
}

void *av_realloc(void *ptr, size_t size)
{
    void *ret;
    නම් (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ආපසු NULL;

#නම් ASAN_ALIGNED_ALLOC
    නම් (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    නැතහොත්
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#elif HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#නැතහොත්
    ret = realloc(ptr, size + !size);
#endif
    නම් (ret && !ptr)
        poison_memory(ret, size);
    ආපසු ret;
}

void *av_realloc_f(void *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    void *r;

    නම් (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        ආපසු NULL;
    }
    r = av_realloc(ptr, size);
    නම් (!r)
        av_free(ptr);
    ආපසු r;
}

පූර්ණ_සංඛ්‍යා av_reallocp(void *ptr, size_t size)
{
    void *val;

    නම් (!size) {
        av_freep(ptr);
        ආපසු 0;
    }

    memcpy(&val, ptr, parimaa_na(val));
    val = av_realloc(val, size);

    නම් (!val) {
        av_freep(ptr);
        ආපසු AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, parimaa_na(val));
    ආපසු 0;
}

void *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    නම් (size_mult(nmemb, size, &result) < 0)
        ආපසු NULL;
    ආපසු av_malloc(result);
}

void *av_realloc_array(void *ptr, size_t nmemb, size_t size)
{
    size_t result;
    නම් (size_mult(nmemb, size, &result) < 0)
        ආපසු NULL;
    ආපසු av_realloc(ptr, result);
}

පූර්ණ_සංඛ්‍යා av_reallocp_array(void *ptr, size_t nmemb, size_t size)
{
    void *val;

    memcpy(&val, ptr, parimaa_na(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, parimaa_na(val));
    නම් (!val && nmemb && size)
        ආපසු AVERROR(ENOMEM);

    ආපසු 0;
}

void av_free(void *ptr)
{
#නම් ASAN_ALIGNED_ALLOC
    නම් (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    නැතහොත්
        _aligned_free(ptr);
#elif HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#නැතහොත්
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
    නම් (ptr)
        memset(ptr, 0, size);
    ආපසු ptr;
}

void *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    නම් (size_mult(nmemb, size, &result) < 0)
        ආපසු NULL;
    ආපසු av_mallocz(result);
}

var_na *av_strdup(const var_na *s)
{
    var_na *ptr = NULL;
    නම් (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(NULL, len);
        නම් (ptr)
            memcpy(ptr, s, len);
    }
    ආපසු ptr;
}

var_na *av_strndup(const var_na *s, size_t len)
{
    නම් (!s)
        ආපසු NULL;

    const var_na *end = memchr(s, 0, len);
    නම් (end)
        len = end - s;

    var_na *ret = av_realloc(NULL, len + 1);
    නම් (!ret)
        ආපසු NULL;

    memcpy(ret, s, len);
    ret[len] = 0;
    ආපසු ret;
}

void *av_memdup(const void *p, size_t size)
{
    void *ptr = NULL;
    නම් (p) {
        ptr = av_malloc(size);
        නම් (ptr)
            memcpy(ptr, p, size);
    }
    ආපසු ptr;
}

පූර්ණ_සංඛ්‍යා av_dynarray_add_nofree(void *tab_ptr, පූර්ණ_සංඛ්‍යා *nb_ptr, void *elem)
{
    void **tab;
    memcpy(&tab, tab_ptr, parimaa_na(tab));

    FF_DYNARRAY_ADD(INT_MAX, parimaa_na(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, parimaa_na(tab));
    }, {
        ආපසු AVERROR(ENOMEM);
    });
    ආපසු 0;
}

void av_dynarray_add(void *tab_ptr, පූර්ණ_සංඛ්‍යා *nb_ptr, void *elem)
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

void *av_dynarray2_add(void **tab_ptr, පූර්ණ_සංඛ්‍යා *nb_ptr, size_t elem_size,
                       const uint8_t *elem_data)
{
    uint8_t *tab_elem_data = NULL;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        නම් (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        නැතහොත්
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    ආපසු tab_elem_data;
}

static void fill16(uint8_t *dst, පූර්ණ_සංඛ්‍යා len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    අතරතුර (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    අතරතුර (len--) {
        *dst = dst[-2];
        dst++;
    }
}

static void fill24(uint8_t *dst, පූර්ණ_සංඛ්‍යා len)
{
#නම් HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#නැතහොත්
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    අතරතුර (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    නම් (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    නම් (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    අතරතුර (len--) {
        *dst = dst[-3];
        dst++;
    }
}

static void fill32(uint8_t *dst, පූර්ණ_සංඛ්‍යා len)
{
    uint32_t v = AV_RN32(dst - 4);

#නම් HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    අතරතුර (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    අතරතුර (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    අතරතුර (len--) {
        *dst = dst[-4];
        dst++;
    }
}

void av_memcpy_backptr(uint8_t *dst, පූර්ණ_සංඛ්‍යා back, පූර්ණ_සංඛ්‍යා cnt)
{
    const uint8_t *src = &dst[-back];
    නම් (!back)
        ආපසු;

    නම් (back == 1) {
        memset(dst, *src, cnt);
    } නැතහොත් නම් (back == 2) {
        fill16(dst, cnt);
    } නැතහොත් නම් (back == 3) {
        fill24(dst, cnt);
    } නැතහොත් නම් (back == 4) {
        fill32(dst, cnt);
    } නැතහොත් {
        නම් (cnt >= 16) {
            පූර්ණ_සංඛ්‍යා blocklen = back;
            අතරතුර (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            ආපසු;
        }
        නම් (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        නම් (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        නම් (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        නම් (cnt)
            *dst = *src;
    }
}

void *av_fast_realloc(void *ptr, unsigned පූර්ණ_සංඛ්‍යා *size, size_t min_size)
{
    size_t max_size;

    නම් (min_size <= *size)
        ආපසු ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    නම් (min_size > max_size) {
        *size = 0;
        ආපසු NULL;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    නම් (!ptr)
        min_size = 0;

    *size = min_size;

    ආපසු ptr;
}

static anta_hstha void fast_malloc(void *ptr, unsigned පූර්ණ_සංඛ්‍යා *size, size_t min_size, පූර්ණ_සංඛ්‍යා zero_realloc)
{
    size_t max_size;
    void *val;

    memcpy(&val, ptr, parimaa_na(val));
    නම් (min_size <= *size) {
        av_assert0(val || !min_size);
        ආපසු;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    නම් (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        ආපසු;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, parimaa_na(val));
    නම් (!val)
        min_size = 0;
    *size = min_size;
    ආපසු;
}

void av_fast_malloc(void *ptr, unsigned පූර්ණ_සංඛ්‍යා *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

void av_fast_mallocz(void *ptr, unsigned පූර්ණ_සංඛ්‍යා *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

පූර්ණ_සංඛ්‍යා av_size_mult(size_t a, size_t b, size_t *r)
{
    ආපසු size_mult(a, b, r);
}

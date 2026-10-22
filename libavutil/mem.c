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
#အကယ်၍ HAVE_MALLOC_H
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
ကိန်းပြည့်   posix_memalign(void **ptr, size_t align, size_t size);
void *realloc(void *ptr, size_t size);
void  free(void *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

static void poison_memory(void *ptr, size_t size)
{
#အကယ်၍ CONFIG_MEMORY_POISONING
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
#အကယ်၍ HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

static ကိန်းပြည့် asan_aligned_alloc_needed(void)
{
    static atomic_int needed = -1;
    ကိန်းပြည့် ret = atomic_load_explicit(&needed, memory_order_relaxed);

    အကယ်၍ (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        ကိန်းပြည့် probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        အကယ်၍ (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    ပြန်ပေး ret;
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

    အကယ်၍ (size > SIZE_MAX - ALIGN - parimaa_na(*hdr))
        ပြန်ပေး NULL;
    total = size + ALIGN + parimaa_na(*hdr);
    base  = malloc(total);
    အကယ်၍ (!base)
        ပြန်ပေး NULL;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + parimaa_na(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    ပြန်ပေး ptr;
}

static AsanAlignedHeader *asan_aligned_header(void *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, parimaa_na(*hdr));
    ပြန်ပေး hdr;
}

static void asan_aligned_free(void *ptr)
{
    အကယ်၍ (ptr)
        free(asan_aligned_header(ptr)->base);
}

static void *asan_aligned_realloc(void *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    void *ret;

    အကယ်၍ (!ptr)
        ပြန်ပေး asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    အကယ်၍ (!ret)
        ပြန်ပေး NULL;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    free(hdr->base);
    ပြန်ပေး ret;
}
#မဟုတ်ပါက
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

static ကိန်းပြည့် size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#အကယ်၍ (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    အကယ်၍ (__builtin_mul_overflow(a, b, &t))
        ပြန်ပေး AVERROR(EINVAL);
#မဟုတ်ပါက
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    အကယ်၍ ((a | b) >= ((size_t)1 << (parimaa_na(size_t) * 4)) && a && t / a != b)
        ပြန်ပေး AVERROR(EINVAL);
#endif
    *r = t;
    ပြန်ပေး 0;
}

void *av_malloc(size_t size)
{
    void *ptr = NULL;

    အကယ်၍ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ပြန်ပေး NULL;

#အကယ်၍ ASAN_ALIGNED_ALLOC
    အကယ်၍ (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    မဟုတ်ပါက
        ptr = _aligned_malloc(size, ALIGN);
#elif HAVE_POSIX_MEMALIGN
    အကယ်၍ (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    အကယ်၍ (posix_memalign(&ptr, ALIGN, size))
        ptr = NULL;
#elif HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#elif HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#မဟုတ်ပါက
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
#မဟုတ်ပါက
    ptr = malloc(size);
#endif
    အကယ်၍(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    အကယ်၍ (ptr)
        poison_memory(ptr, size);
    ပြန်ပေး ptr;
}

void *av_realloc(void *ptr, size_t size)
{
    void *ret;
    အကယ်၍ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ပြန်ပေး NULL;

#အကယ်၍ ASAN_ALIGNED_ALLOC
    အကယ်၍ (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    မဟုတ်ပါက
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#elif HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#မဟုတ်ပါက
    ret = realloc(ptr, size + !size);
#endif
    အကယ်၍ (ret && !ptr)
        poison_memory(ret, size);
    ပြန်ပေး ret;
}

void *av_realloc_f(void *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    void *r;

    အကယ်၍ (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        ပြန်ပေး NULL;
    }
    r = av_realloc(ptr, size);
    အကယ်၍ (!r)
        av_free(ptr);
    ပြန်ပေး r;
}

ကိန်းပြည့် av_reallocp(void *ptr, size_t size)
{
    void *val;

    အကယ်၍ (!size) {
        av_freep(ptr);
        ပြန်ပေး 0;
    }

    memcpy(&val, ptr, parimaa_na(val));
    val = av_realloc(val, size);

    အကယ်၍ (!val) {
        av_freep(ptr);
        ပြန်ပေး AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, parimaa_na(val));
    ပြန်ပေး 0;
}

void *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    အကယ်၍ (size_mult(nmemb, size, &result) < 0)
        ပြန်ပေး NULL;
    ပြန်ပေး av_malloc(result);
}

void *av_realloc_array(void *ptr, size_t nmemb, size_t size)
{
    size_t result;
    အကယ်၍ (size_mult(nmemb, size, &result) < 0)
        ပြန်ပေး NULL;
    ပြန်ပေး av_realloc(ptr, result);
}

ကိန်းပြည့် av_reallocp_array(void *ptr, size_t nmemb, size_t size)
{
    void *val;

    memcpy(&val, ptr, parimaa_na(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, parimaa_na(val));
    အကယ်၍ (!val && nmemb && size)
        ပြန်ပေး AVERROR(ENOMEM);

    ပြန်ပေး 0;
}

void av_free(void *ptr)
{
#အကယ်၍ ASAN_ALIGNED_ALLOC
    အကယ်၍ (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    မဟုတ်ပါက
        _aligned_free(ptr);
#elif HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#မဟုတ်ပါက
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
    အကယ်၍ (ptr)
        memset(ptr, 0, size);
    ပြန်ပေး ptr;
}

void *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    အကယ်၍ (size_mult(nmemb, size, &result) < 0)
        ပြန်ပေး NULL;
    ပြန်ပေး av_mallocz(result);
}

var_na *av_strdup(const var_na *s)
{
    var_na *ptr = NULL;
    အကယ်၍ (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(NULL, len);
        အကယ်၍ (ptr)
            memcpy(ptr, s, len);
    }
    ပြန်ပေး ptr;
}

var_na *av_strndup(const var_na *s, size_t len)
{
    အကယ်၍ (!s)
        ပြန်ပေး NULL;

    const var_na *end = memchr(s, 0, len);
    အကယ်၍ (end)
        len = end - s;

    var_na *ret = av_realloc(NULL, len + 1);
    အကယ်၍ (!ret)
        ပြန်ပေး NULL;

    memcpy(ret, s, len);
    ret[len] = 0;
    ပြန်ပေး ret;
}

void *av_memdup(const void *p, size_t size)
{
    void *ptr = NULL;
    အကယ်၍ (p) {
        ptr = av_malloc(size);
        အကယ်၍ (ptr)
            memcpy(ptr, p, size);
    }
    ပြန်ပေး ptr;
}

ကိန်းပြည့် av_dynarray_add_nofree(void *tab_ptr, ကိန်းပြည့် *nb_ptr, void *elem)
{
    void **tab;
    memcpy(&tab, tab_ptr, parimaa_na(tab));

    FF_DYNARRAY_ADD(INT_MAX, parimaa_na(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, parimaa_na(tab));
    }, {
        ပြန်ပေး AVERROR(ENOMEM);
    });
    ပြန်ပေး 0;
}

void av_dynarray_add(void *tab_ptr, ကိန်းပြည့် *nb_ptr, void *elem)
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

void *av_dynarray2_add(void **tab_ptr, ကိန်းပြည့် *nb_ptr, size_t elem_size,
                       const uint8_t *elem_data)
{
    uint8_t *tab_elem_data = NULL;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        အကယ်၍ (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        မဟုတ်ပါက
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    ပြန်ပေး tab_elem_data;
}

static void fill16(uint8_t *dst, ကိန်းပြည့် len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    နေစဉ် (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    နေစဉ် (len--) {
        *dst = dst[-2];
        dst++;
    }
}

static void fill24(uint8_t *dst, ကိန်းပြည့် len)
{
#အကယ်၍ HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#မဟုတ်ပါက
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    နေစဉ် (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    အကယ်၍ (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    အကယ်၍ (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    နေစဉ် (len--) {
        *dst = dst[-3];
        dst++;
    }
}

static void fill32(uint8_t *dst, ကိန်းပြည့် len)
{
    uint32_t v = AV_RN32(dst - 4);

#အကယ်၍ HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    နေစဉ် (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    နေစဉ် (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    နေစဉ် (len--) {
        *dst = dst[-4];
        dst++;
    }
}

void av_memcpy_backptr(uint8_t *dst, ကိန်းပြည့် back, ကိန်းပြည့် cnt)
{
    const uint8_t *src = &dst[-back];
    အကယ်၍ (!back)
        ပြန်ပေး;

    အကယ်၍ (back == 1) {
        memset(dst, *src, cnt);
    } မဟုတ်ပါက အကယ်၍ (back == 2) {
        fill16(dst, cnt);
    } မဟုတ်ပါက အကယ်၍ (back == 3) {
        fill24(dst, cnt);
    } မဟုတ်ပါက အကယ်၍ (back == 4) {
        fill32(dst, cnt);
    } မဟုတ်ပါက {
        အကယ်၍ (cnt >= 16) {
            ကိန်းပြည့် blocklen = back;
            နေစဉ် (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            ပြန်ပေး;
        }
        အကယ်၍ (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        အကယ်၍ (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        အကယ်၍ (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        အကယ်၍ (cnt)
            *dst = *src;
    }
}

void *av_fast_realloc(void *ptr, unsigned ကိန်းပြည့် *size, size_t min_size)
{
    size_t max_size;

    အကယ်၍ (min_size <= *size)
        ပြန်ပေး ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    အကယ်၍ (min_size > max_size) {
        *size = 0;
        ပြန်ပေး NULL;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    အကယ်၍ (!ptr)
        min_size = 0;

    *size = min_size;

    ပြန်ပေး ptr;
}

static anta_hstha void fast_malloc(void *ptr, unsigned ကိန်းပြည့် *size, size_t min_size, ကိန်းပြည့် zero_realloc)
{
    size_t max_size;
    void *val;

    memcpy(&val, ptr, parimaa_na(val));
    အကယ်၍ (min_size <= *size) {
        av_assert0(val || !min_size);
        ပြန်ပေး;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    အကယ်၍ (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        ပြန်ပေး;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, parimaa_na(val));
    အကယ်၍ (!val)
        min_size = 0;
    *size = min_size;
    ပြန်ပေး;
}

void av_fast_malloc(void *ptr, unsigned ကိန်းပြည့် *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

void av_fast_mallocz(void *ptr, unsigned ကိန်းပြည့် *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

ကိန်းပြည့် av_size_mult(size_t a, size_t b, size_t *r)
{
    ပြန်ပေး size_mult(a, b, r);
}

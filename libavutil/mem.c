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

#ଅନ୍ତର୍ଭାଵ "config.h"

#ଅନ୍ତର୍ଭାଵ <limits.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <stdlib.h>
#ଅନ୍ତର୍ଭାଵ <stdatomic.h>
#ଅନ୍ତର୍ଭାଵ <string.h>
#ଯଦି HAVE_MALLOC_H
#ଅନ୍ତର୍ଭାଵ <malloc.h>
#endif

#ଅନ୍ତର୍ଭାଵ "attributes.h"
#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "dynarray.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "internal.h"
#ଅନ୍ତର୍ଭାଵ "intreadwrite.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define ମୁକ୍ତ           AV_JOIN(MALLOC_PREFIX, ମୁକ୍ତ)

ଶୂନ୍ୟ *malloc(size_t size);
ଶୂନ୍ୟ *memalign(size_t align, size_t size);
ପୂର୍ଣ୍ଣସଂଖ୍ୟା   posix_memalign(ଶୂନ୍ୟ **ptr, size_t align, size_t size);
ଶୂନ୍ୟ *realloc(ଶୂନ୍ୟ *ptr, size_t size);
ଶୂନ୍ୟ  ମୁକ୍ତ(ଶୂନ୍ୟ *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

ସ୍ଥିର ଶୂନ୍ୟ poison_memory(ଶୂନ୍ୟ *ptr, size_t size)
{
#ଯଦି CONFIG_MEMORY_POISONING
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
#ଯଦି HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା asan_aligned_alloc_needed(ଶୂନ୍ୟ)
{
    ସ୍ଥିର atomic_int needed = -1;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = atomic_load_explicit(&needed, memory_order_relaxed);

    ଯଦି (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        ଯଦି (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    ଫେରନ୍ତୁ ret;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା AsanAlignedHeader {
    ଶୂନ୍ୟ  *base;
    size_t size;
} AsanAlignedHeader;

ସ୍ଥିର ଶୂନ୍ୟ *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    ଯଦି (size > SIZE_MAX - ALIGN - ଆକାର(*hdr))
        ଫେରନ୍ତୁ ଖାଲି;
    total = size + ALIGN + ଆକାର(*hdr);
    base  = malloc(total);
    ଯଦି (!base)
        ଫେରନ୍ତୁ ଖାଲି;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + ଆକାର(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    ଫେରନ୍ତୁ ptr;
}

ସ୍ଥିର AsanAlignedHeader *asan_aligned_header(ଶୂନ୍ୟ *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, ଆକାର(*hdr));
    ଫେରନ୍ତୁ hdr;
}

ସ୍ଥିର ଶୂନ୍ୟ asan_aligned_free(ଶୂନ୍ୟ *ptr)
{
    ଯଦି (ptr)
        ମୁକ୍ତ(asan_aligned_header(ptr)->base);
}

ସ୍ଥିର ଶୂନ୍ୟ *asan_aligned_realloc(ଶୂନ୍ୟ *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    ଶୂନ୍ୟ *ret;

    ଯଦି (!ptr)
        ଫେରନ୍ତୁ asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    ଯଦି (!ret)
        ଫେରନ୍ତୁ ଖାଲି;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    ମୁକ୍ତ(hdr->base);
    ଫେରନ୍ତୁ ret;
}
#ଅନ୍ୟଥା
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

ସ୍ଥିର atomic_size_t max_alloc_size = INT_MAX;

ଶୂନ୍ୟ av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#ଯଦି (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    ଯଦି (__builtin_mul_overflow(a, b, &t))
        ଫେରନ୍ତୁ AVERROR(EINVAL);
#ଅନ୍ୟଥା
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    ଯଦି ((a | b) >= ((size_t)1 << (ଆକାର(size_t) * 4)) && a && t / a != b)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
#endif
    *r = t;
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ *av_malloc(size_t size)
{
    ଶୂନ୍ୟ *ptr = ଖାଲି;

    ଯଦି (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ଫେରନ୍ତୁ ଖାଲି;

#ଯଦି ASAN_ALIGNED_ALLOC
    ଯଦି (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    ଅନ୍ୟଥା
        ptr = _aligned_malloc(size, ALIGN);
#ନଚେତଯଦି HAVE_POSIX_MEMALIGN
    ଯଦି (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    ଯଦି (posix_memalign(&ptr, ALIGN, size))
        ptr = ଖାଲି;
#ନଚେତଯଦି HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#ନଚେତଯଦି HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#ଅନ୍ୟଥା
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
#ଅନ୍ୟଥା
    ptr = malloc(size);
#endif
    ଯଦି(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    ଯଦି (ptr)
        poison_memory(ptr, size);
    ଫେରନ୍ତୁ ptr;
}

ଶୂନ୍ୟ *av_realloc(ଶୂନ୍ୟ *ptr, size_t size)
{
    ଶୂନ୍ୟ *ret;
    ଯଦି (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ଫେରନ୍ତୁ ଖାଲି;

#ଯଦି ASAN_ALIGNED_ALLOC
    ଯଦି (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    ଅନ୍ୟଥା
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#ନଚେତଯଦି HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#ଅନ୍ୟଥା
    ret = realloc(ptr, size + !size);
#endif
    ଯଦି (ret && !ptr)
        poison_memory(ret, size);
    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ *av_realloc_f(ଶୂନ୍ୟ *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    ଶୂନ୍ୟ *r;

    ଯଦି (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    r = av_realloc(ptr, size);
    ଯଦି (!r)
        av_free(ptr);
    ଫେରନ୍ତୁ r;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_reallocp(ଶୂନ୍ୟ *ptr, size_t size)
{
    ଶୂନ୍ୟ *val;

    ଯଦି (!size) {
        av_freep(ptr);
        ଫେରନ୍ତୁ 0;
    }

    memcpy(&val, ptr, ଆକାର(val));
    val = av_realloc(val, size);

    ଯଦି (!val) {
        av_freep(ptr);
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, ଆକାର(val));
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    ଯଦି (size_mult(nmemb, size, &result) < 0)
        ଫେରନ୍ତୁ ଖାଲି;
    ଫେରନ୍ତୁ av_malloc(result);
}

ଶୂନ୍ୟ *av_realloc_array(ଶୂନ୍ୟ *ptr, size_t nmemb, size_t size)
{
    size_t result;
    ଯଦି (size_mult(nmemb, size, &result) < 0)
        ଫେରନ୍ତୁ ଖାଲି;
    ଫେରନ୍ତୁ av_realloc(ptr, result);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_reallocp_array(ଶୂନ୍ୟ *ptr, size_t nmemb, size_t size)
{
    ଶୂନ୍ୟ *val;

    memcpy(&val, ptr, ଆକାର(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, ଆକାର(val));
    ଯଦି (!val && nmemb && size)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_free(ଶୂନ୍ୟ *ptr)
{
#ଯଦି ASAN_ALIGNED_ALLOC
    ଯଦି (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    ଅନ୍ୟଥା
        _aligned_free(ptr);
#ନଚେତଯଦି HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#ଅନ୍ୟଥା
    ମୁକ୍ତ(ptr);
#endif
}

ଶୂନ୍ୟ av_freep(ଶୂନ୍ୟ *arg)
{
    ଶୂନ୍ୟ *val;

    memcpy(&val, arg, ଆକାର(val));
    memcpy(arg, &(ଶୂନ୍ୟ *){ ଖାଲି }, ଆକାର(val));
    av_free(val);
}

ଶୂନ୍ୟ *av_mallocz(size_t size)
{
    ଶୂନ୍ୟ *ptr = av_malloc(size);
    ଯଦି (ptr)
        memset(ptr, 0, size);
    ଫେରନ୍ତୁ ptr;
}

ଶୂନ୍ୟ *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    ଯଦି (size_mult(nmemb, size, &result) < 0)
        ଫେରନ୍ତୁ ଖାଲି;
    ଫେରନ୍ତୁ av_mallocz(result);
}

ଅକ୍ଷର *av_strdup(ଅଚଳ ଅକ୍ଷର *s)
{
    ଅକ୍ଷର *ptr = ଖାଲି;
    ଯଦି (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(ଖାଲି, len);
        ଯଦି (ptr)
            memcpy(ptr, s, len);
    }
    ଫେରନ୍ତୁ ptr;
}

ଅକ୍ଷର *av_strndup(ଅଚଳ ଅକ୍ଷର *s, size_t len)
{
    ଯଦି (!s)
        ଫେରନ୍ତୁ ଖାଲି;

    ଅଚଳ ଅକ୍ଷର *end = memchr(s, 0, len);
    ଯଦି (end)
        len = end - s;

    ଅକ୍ଷର *ret = av_realloc(ଖାଲି, len + 1);
    ଯଦି (!ret)
        ଫେରନ୍ତୁ ଖାଲି;

    memcpy(ret, s, len);
    ret[len] = 0;
    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ *av_memdup(ଅଚଳ ଶୂନ୍ୟ *p, size_t size)
{
    ଶୂନ୍ୟ *ptr = ଖାଲି;
    ଯଦି (p) {
        ptr = av_malloc(size);
        ଯଦି (ptr)
            memcpy(ptr, p, size);
    }
    ଫେରନ୍ତୁ ptr;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_dynarray_add_nofree(ଶୂନ୍ୟ *tab_ptr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_ptr, ଶୂନ୍ୟ *elem)
{
    ଶୂନ୍ୟ **tab;
    memcpy(&tab, tab_ptr, ଆକାର(tab));

    FF_DYNARRAY_ADD(INT_MAX, ଆକାର(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, ଆକାର(tab));
    }, {
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    });
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_dynarray_add(ଶୂନ୍ୟ *tab_ptr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_ptr, ଶୂନ୍ୟ *elem)
{
    ଶୂନ୍ୟ **tab;
    memcpy(&tab, tab_ptr, ଆକାର(tab));

    FF_DYNARRAY_ADD(INT_MAX, ଆକାର(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, ଆକାର(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

ଶୂନ୍ୟ *av_dynarray2_add(ଶୂନ୍ୟ **tab_ptr, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *nb_ptr, size_t elem_size,
                       ଅଚଳ uint8_t *elem_data)
{
    uint8_t *tab_elem_data = ଖାଲି;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        ଯଦି (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        ଅନ୍ୟଥା
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    ଫେରନ୍ତୁ tab_elem_data;
}

ସ୍ଥିର ଶୂନ୍ୟ fill16(uint8_t *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    ଯେତେବେଳେ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ଯେତେବେଳେ (len--) {
        *dst = dst[-2];
        dst++;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ fill24(uint8_t *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
#ଯଦି HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#ଅନ୍ୟଥା
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    ଯେତେବେଳେ (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    ଯଦି (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    ଯଦି (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    ଯେତେବେଳେ (len--) {
        *dst = dst[-3];
        dst++;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ fill32(uint8_t *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା len)
{
    uint32_t v = AV_RN32(dst - 4);

#ଯଦି HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    ଯେତେବେଳେ (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    ଯେତେବେଳେ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ଯେତେବେଳେ (len--) {
        *dst = dst[-4];
        dst++;
    }
}

ଶୂନ୍ୟ av_memcpy_backptr(uint8_t *dst, ପୂର୍ଣ୍ଣସଂଖ୍ୟା back, ପୂର୍ଣ୍ଣସଂଖ୍ୟା cnt)
{
    ଅଚଳ uint8_t *src = &dst[-back];
    ଯଦି (!back)
        ଫେରନ୍ତୁ;

    ଯଦି (back == 1) {
        memset(dst, *src, cnt);
    } ଅନ୍ୟଥା ଯଦି (back == 2) {
        fill16(dst, cnt);
    } ଅନ୍ୟଥା ଯଦି (back == 3) {
        fill24(dst, cnt);
    } ଅନ୍ୟଥା ଯଦି (back == 4) {
        fill32(dst, cnt);
    } ଅନ୍ୟଥା {
        ଯଦି (cnt >= 16) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା blocklen = back;
            ଯେତେବେଳେ (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            ଫେରନ୍ତୁ;
        }
        ଯଦି (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        ଯଦି (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        ଯଦି (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        ଯଦି (cnt)
            *dst = *src;
    }
}

ଶୂନ୍ୟ *av_fast_realloc(ଶୂନ୍ୟ *ptr, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *size, size_t min_size)
{
    size_t max_size;

    ଯଦି (min_size <= *size)
        ଫେରନ୍ତୁ ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    ଯଦି (min_size > max_size) {
        *size = 0;
        ଫେରନ୍ତୁ ଖାଲି;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    ଯଦି (!ptr)
        min_size = 0;

    *size = min_size;

    ଫେରନ୍ତୁ ptr;
}

ସ୍ଥିର ଧାଡ଼ିଭିତରେ ଶୂନ୍ୟ fast_malloc(ଶୂନ୍ୟ *ptr, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *size, size_t min_size, ପୂର୍ଣ୍ଣସଂଖ୍ୟା zero_realloc)
{
    size_t max_size;
    ଶୂନ୍ୟ *val;

    memcpy(&val, ptr, ଆକାର(val));
    ଯଦି (min_size <= *size) {
        av_assert0(val || !min_size);
        ଫେରନ୍ତୁ;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    ଯଦି (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        ଫେରନ୍ତୁ;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, ଆକାର(val));
    ଯଦି (!val)
        min_size = 0;
    *size = min_size;
    ଫେରନ୍ତୁ;
}

ଶୂନ୍ୟ av_fast_malloc(ଶୂନ୍ୟ *ptr, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

ଶୂନ୍ୟ av_fast_mallocz(ଶୂନ୍ୟ *ptr, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_size_mult(size_t a, size_t b, size_t *r)
{
    ଫେରନ୍ତୁ size_mult(a, b, r);
}

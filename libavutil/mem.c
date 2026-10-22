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

#અન્તર્ભાવ "config.h"

#અન્તર્ભાવ <limits.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <stdlib.h>
#અન્તર્ભાવ <stdatomic.h>
#અન્તર્ભાવ <string.h>
#જો HAVE_MALLOC_H
#અન્તર્ભાવ <malloc.h>
#endif

#અન્તર્ભાવ "attributes.h"
#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "dynarray.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "internal.h"
#અન્તર્ભાવ "intreadwrite.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define મુક્ત           AV_JOIN(MALLOC_PREFIX, મુક્ત)

શૂન્ય *malloc(size_t size);
શૂન્ય *memalign(size_t align, size_t size);
પૂર્ણાંક   posix_memalign(શૂન્ય **ptr, size_t align, size_t size);
શૂન્ય *realloc(શૂન્ય *ptr, size_t size);
શૂન્ય  મુક્ત(શૂન્ય *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

સ્થિર શૂન્ય poison_memory(શૂન્ય *ptr, size_t size)
{
#જો CONFIG_MEMORY_POISONING
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
#જો HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

સ્થિર પૂર્ણાંક asan_aligned_alloc_needed(શૂન્ય)
{
    સ્થિર atomic_int needed = -1;
    પૂર્ણાંક ret = atomic_load_explicit(&needed, memory_order_relaxed);

    જો (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        પૂર્ણાંક probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        જો (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    પાછા ret;
}

પ્રકારવ્યાખ્યા સંરચના AsanAlignedHeader {
    શૂન્ય  *base;
    size_t size;
} AsanAlignedHeader;

સ્થિર શૂન્ય *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    જો (size > SIZE_MAX - ALIGN - કદ(*hdr))
        પાછા ખાલી;
    total = size + ALIGN + કદ(*hdr);
    base  = malloc(total);
    જો (!base)
        પાછા ખાલી;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + કદ(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    પાછા ptr;
}

સ્થિર AsanAlignedHeader *asan_aligned_header(શૂન્ય *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, કદ(*hdr));
    પાછા hdr;
}

સ્થિર શૂન્ય asan_aligned_free(શૂન્ય *ptr)
{
    જો (ptr)
        મુક્ત(asan_aligned_header(ptr)->base);
}

સ્થિર શૂન્ય *asan_aligned_realloc(શૂન્ય *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    શૂન્ય *ret;

    જો (!ptr)
        પાછા asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    જો (!ret)
        પાછા ખાલી;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    મુક્ત(hdr->base);
    પાછા ret;
}
#નહીંતર
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

સ્થિર atomic_size_t max_alloc_size = INT_MAX;

શૂન્ય av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

સ્થિર પૂર્ણાંક size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#જો (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    જો (__builtin_mul_overflow(a, b, &t))
        પાછા AVERROR(EINVAL);
#નહીંતર
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    જો ((a | b) >= ((size_t)1 << (કદ(size_t) * 4)) && a && t / a != b)
        પાછા AVERROR(EINVAL);
#endif
    *r = t;
    પાછા 0;
}

શૂન્ય *av_malloc(size_t size)
{
    શૂન્ય *ptr = ખાલી;

    જો (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        પાછા ખાલી;

#જો ASAN_ALIGNED_ALLOC
    જો (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    નહીંતર
        ptr = _aligned_malloc(size, ALIGN);
#અથવાજો HAVE_POSIX_MEMALIGN
    જો (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    જો (posix_memalign(&ptr, ALIGN, size))
        ptr = ખાલી;
#અથવાજો HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#અથવાજો HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#નહીંતર
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
#નહીંતર
    ptr = malloc(size);
#endif
    જો(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    જો (ptr)
        poison_memory(ptr, size);
    પાછા ptr;
}

શૂન્ય *av_realloc(શૂન્ય *ptr, size_t size)
{
    શૂન્ય *ret;
    જો (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        પાછા ખાલી;

#જો ASAN_ALIGNED_ALLOC
    જો (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    નહીંતર
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#અથવાજો HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#નહીંતર
    ret = realloc(ptr, size + !size);
#endif
    જો (ret && !ptr)
        poison_memory(ret, size);
    પાછા ret;
}

શૂન્ય *av_realloc_f(શૂન્ય *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    શૂન્ય *r;

    જો (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        પાછા ખાલી;
    }
    r = av_realloc(ptr, size);
    જો (!r)
        av_free(ptr);
    પાછા r;
}

પૂર્ણાંક av_reallocp(શૂન્ય *ptr, size_t size)
{
    શૂન્ય *val;

    જો (!size) {
        av_freep(ptr);
        પાછા 0;
    }

    memcpy(&val, ptr, કદ(val));
    val = av_realloc(val, size);

    જો (!val) {
        av_freep(ptr);
        પાછા AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, કદ(val));
    પાછા 0;
}

શૂન્ય *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    જો (size_mult(nmemb, size, &result) < 0)
        પાછા ખાલી;
    પાછા av_malloc(result);
}

શૂન્ય *av_realloc_array(શૂન્ય *ptr, size_t nmemb, size_t size)
{
    size_t result;
    જો (size_mult(nmemb, size, &result) < 0)
        પાછા ખાલી;
    પાછા av_realloc(ptr, result);
}

પૂર્ણાંક av_reallocp_array(શૂન્ય *ptr, size_t nmemb, size_t size)
{
    શૂન્ય *val;

    memcpy(&val, ptr, કદ(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, કદ(val));
    જો (!val && nmemb && size)
        પાછા AVERROR(ENOMEM);

    પાછા 0;
}

શૂન્ય av_free(શૂન્ય *ptr)
{
#જો ASAN_ALIGNED_ALLOC
    જો (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    નહીંતર
        _aligned_free(ptr);
#અથવાજો HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#નહીંતર
    મુક્ત(ptr);
#endif
}

શૂન્ય av_freep(શૂન્ય *arg)
{
    શૂન્ય *val;

    memcpy(&val, arg, કદ(val));
    memcpy(arg, &(શૂન્ય *){ ખાલી }, કદ(val));
    av_free(val);
}

શૂન્ય *av_mallocz(size_t size)
{
    શૂન્ય *ptr = av_malloc(size);
    જો (ptr)
        memset(ptr, 0, size);
    પાછા ptr;
}

શૂન્ય *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    જો (size_mult(nmemb, size, &result) < 0)
        પાછા ખાલી;
    પાછા av_mallocz(result);
}

અક્ષર *av_strdup(અચલ અક્ષર *s)
{
    અક્ષર *ptr = ખાલી;
    જો (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(ખાલી, len);
        જો (ptr)
            memcpy(ptr, s, len);
    }
    પાછા ptr;
}

અક્ષર *av_strndup(અચલ અક્ષર *s, size_t len)
{
    જો (!s)
        પાછા ખાલી;

    અચલ અક્ષર *end = memchr(s, 0, len);
    જો (end)
        len = end - s;

    અક્ષર *ret = av_realloc(ખાલી, len + 1);
    જો (!ret)
        પાછા ખાલી;

    memcpy(ret, s, len);
    ret[len] = 0;
    પાછા ret;
}

શૂન્ય *av_memdup(અચલ શૂન્ય *p, size_t size)
{
    શૂન્ય *ptr = ખાલી;
    જો (p) {
        ptr = av_malloc(size);
        જો (ptr)
            memcpy(ptr, p, size);
    }
    પાછા ptr;
}

પૂર્ણાંક av_dynarray_add_nofree(શૂન્ય *tab_ptr, પૂર્ણાંક *nb_ptr, શૂન્ય *elem)
{
    શૂન્ય **tab;
    memcpy(&tab, tab_ptr, કદ(tab));

    FF_DYNARRAY_ADD(INT_MAX, કદ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, કદ(tab));
    }, {
        પાછા AVERROR(ENOMEM);
    });
    પાછા 0;
}

શૂન્ય av_dynarray_add(શૂન્ય *tab_ptr, પૂર્ણાંક *nb_ptr, શૂન્ય *elem)
{
    શૂન્ય **tab;
    memcpy(&tab, tab_ptr, કદ(tab));

    FF_DYNARRAY_ADD(INT_MAX, કદ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, કદ(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

શૂન્ય *av_dynarray2_add(શૂન્ય **tab_ptr, પૂર્ણાંક *nb_ptr, size_t elem_size,
                       અચલ uint8_t *elem_data)
{
    uint8_t *tab_elem_data = ખાલી;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        જો (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        નહીંતર
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    પાછા tab_elem_data;
}

સ્થિર શૂન્ય fill16(uint8_t *dst, પૂર્ણાંક len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    જ્યારે (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    જ્યારે (len--) {
        *dst = dst[-2];
        dst++;
    }
}

સ્થિર શૂન્ય fill24(uint8_t *dst, પૂર્ણાંક len)
{
#જો HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#નહીંતર
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    જ્યારે (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    જો (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    જો (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    જ્યારે (len--) {
        *dst = dst[-3];
        dst++;
    }
}

સ્થિર શૂન્ય fill32(uint8_t *dst, પૂર્ણાંક len)
{
    uint32_t v = AV_RN32(dst - 4);

#જો HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    જ્યારે (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    જ્યારે (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    જ્યારે (len--) {
        *dst = dst[-4];
        dst++;
    }
}

શૂન્ય av_memcpy_backptr(uint8_t *dst, પૂર્ણાંક back, પૂર્ણાંક cnt)
{
    અચલ uint8_t *src = &dst[-back];
    જો (!back)
        પાછા;

    જો (back == 1) {
        memset(dst, *src, cnt);
    } નહીંતર જો (back == 2) {
        fill16(dst, cnt);
    } નહીંતર જો (back == 3) {
        fill24(dst, cnt);
    } નહીંતર જો (back == 4) {
        fill32(dst, cnt);
    } નહીંતર {
        જો (cnt >= 16) {
            પૂર્ણાંક blocklen = back;
            જ્યારે (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            પાછા;
        }
        જો (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        જો (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        જો (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        જો (cnt)
            *dst = *src;
    }
}

શૂન્ય *av_fast_realloc(શૂન્ય *ptr, unsigned પૂર્ણાંક *size, size_t min_size)
{
    size_t max_size;

    જો (min_size <= *size)
        પાછા ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    જો (min_size > max_size) {
        *size = 0;
        પાછા ખાલી;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    જો (!ptr)
        min_size = 0;

    *size = min_size;

    પાછા ptr;
}

સ્થિર અંતઃરેખ શૂન્ય fast_malloc(શૂન્ય *ptr, unsigned પૂર્ણાંક *size, size_t min_size, પૂર્ણાંક zero_realloc)
{
    size_t max_size;
    શૂન્ય *val;

    memcpy(&val, ptr, કદ(val));
    જો (min_size <= *size) {
        av_assert0(val || !min_size);
        પાછા;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    જો (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        પાછા;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, કદ(val));
    જો (!val)
        min_size = 0;
    *size = min_size;
    પાછા;
}

શૂન્ય av_fast_malloc(શૂન્ય *ptr, unsigned પૂર્ણાંક *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

શૂન્ય av_fast_mallocz(શૂન્ય *ptr, unsigned પૂર્ણાંક *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

પૂર્ણાંક av_size_mult(size_t a, size_t b, size_t *r)
{
    પાછા size_mult(a, b, r);
}

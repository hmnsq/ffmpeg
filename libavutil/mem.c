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

#অন্তর্ভাৱ "config.h"

#অন্তর্ভাৱ <limits.h>
#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <stdlib.h>
#অন্তর্ভাৱ <stdatomic.h>
#অন্তর্ভাৱ <string.h>
#যদি HAVE_MALLOC_H
#অন্তর্ভাৱ <malloc.h>
#endif

#অন্তর্ভাৱ "attributes.h"
#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "dynarray.h"
#অন্তর্ভাৱ "error.h"
#অন্তর্ভাৱ "internal.h"
#অন্তর্ভাৱ "intreadwrite.h"
#অন্তর্ভাৱ "macros.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define মুক্ত           AV_JOIN(MALLOC_PREFIX, মুক্ত)

শূন্য *malloc(size_t size);
শূন্য *memalign(size_t align, size_t size);
পূর্ণাঙ্ক   posix_memalign(শূন্য **ptr, size_t align, size_t size);
শূন্য *realloc(শূন্য *ptr, size_t size);
শূন্য  মুক্ত(শূন্য *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

স্থির শূন্য poison_memory(শূন্য *ptr, size_t size)
{
#যদি CONFIG_MEMORY_POISONING
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
#যদি HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

স্থির পূর্ণাঙ্ক asan_aligned_alloc_needed(শূন্য)
{
    স্থির atomic_int needed = -1;
    পূর্ণাঙ্ক ret = atomic_load_explicit(&needed, memory_order_relaxed);

    যদি (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        পূর্ণাঙ্ক probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        যদি (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    ঘূৰাই ret;
}

প্রকারনির্দেশ সংরচনা AsanAlignedHeader {
    শূন্য  *base;
    size_t size;
} AsanAlignedHeader;

স্থির শূন্য *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    যদি (size > SIZE_MAX - ALIGN - পরিমাণ(*hdr))
        ঘূৰাই রিক্ত;
    total = size + ALIGN + পরিমাণ(*hdr);
    base  = malloc(total);
    যদি (!base)
        ঘূৰাই রিক্ত;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + পরিমাণ(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    ঘূৰাই ptr;
}

স্থির AsanAlignedHeader *asan_aligned_header(শূন্য *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, পরিমাণ(*hdr));
    ঘূৰাই hdr;
}

স্থির শূন্য asan_aligned_free(শূন্য *ptr)
{
    যদি (ptr)
        মুক্ত(asan_aligned_header(ptr)->base);
}

স্থির শূন্য *asan_aligned_realloc(শূন্য *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    শূন্য *ret;

    যদি (!ptr)
        ঘূৰাই asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    যদি (!ret)
        ঘূৰাই রিক্ত;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    মুক্ত(hdr->base);
    ঘূৰাই ret;
}
#অন্যথা
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

স্থির atomic_size_t max_alloc_size = INT_MAX;

শূন্য av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

স্থির পূর্ণাঙ্ক size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#যদি (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    যদি (__builtin_mul_overflow(a, b, &t))
        ঘূৰাই AVERROR(EINVAL);
#অন্যথা
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    যদি ((a | b) >= ((size_t)1 << (পরিমাণ(size_t) * 4)) && a && t / a != b)
        ঘূৰাই AVERROR(EINVAL);
#endif
    *r = t;
    ঘূৰাই 0;
}

শূন্য *av_malloc(size_t size)
{
    শূন্য *ptr = রিক্ত;

    যদি (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ঘূৰাই রিক্ত;

#যদি ASAN_ALIGNED_ALLOC
    যদি (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    অন্যথা
        ptr = _aligned_malloc(size, ALIGN);
#নোচেদ্যদি HAVE_POSIX_MEMALIGN
    যদি (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    যদি (posix_memalign(&ptr, ALIGN, size))
        ptr = রিক্ত;
#নোচেদ্যদি HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#নোচেদ্যদি HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#অন্যথা
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
#অন্যথা
    ptr = malloc(size);
#endif
    যদি(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    যদি (ptr)
        poison_memory(ptr, size);
    ঘূৰাই ptr;
}

শূন্য *av_realloc(শূন্য *ptr, size_t size)
{
    শূন্য *ret;
    যদি (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        ঘূৰাই রিক্ত;

#যদি ASAN_ALIGNED_ALLOC
    যদি (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    অন্যথা
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#নোচেদ্যদি HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#অন্যথা
    ret = realloc(ptr, size + !size);
#endif
    যদি (ret && !ptr)
        poison_memory(ret, size);
    ঘূৰাই ret;
}

শূন্য *av_realloc_f(শূন্য *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    শূন্য *r;

    যদি (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        ঘূৰাই রিক্ত;
    }
    r = av_realloc(ptr, size);
    যদি (!r)
        av_free(ptr);
    ঘূৰাই r;
}

পূর্ণাঙ্ক av_reallocp(শূন্য *ptr, size_t size)
{
    শূন্য *val;

    যদি (!size) {
        av_freep(ptr);
        ঘূৰাই 0;
    }

    memcpy(&val, ptr, পরিমাণ(val));
    val = av_realloc(val, size);

    যদি (!val) {
        av_freep(ptr);
        ঘূৰাই AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, পরিমাণ(val));
    ঘূৰাই 0;
}

শূন্য *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    যদি (size_mult(nmemb, size, &result) < 0)
        ঘূৰাই রিক্ত;
    ঘূৰাই av_malloc(result);
}

শূন্য *av_realloc_array(শূন্য *ptr, size_t nmemb, size_t size)
{
    size_t result;
    যদি (size_mult(nmemb, size, &result) < 0)
        ঘূৰাই রিক্ত;
    ঘূৰাই av_realloc(ptr, result);
}

পূর্ণাঙ্ক av_reallocp_array(শূন্য *ptr, size_t nmemb, size_t size)
{
    শূন্য *val;

    memcpy(&val, ptr, পরিমাণ(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, পরিমাণ(val));
    যদি (!val && nmemb && size)
        ঘূৰাই AVERROR(ENOMEM);

    ঘূৰাই 0;
}

শূন্য av_free(শূন্য *ptr)
{
#যদি ASAN_ALIGNED_ALLOC
    যদি (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    অন্যথা
        _aligned_free(ptr);
#নোচেদ্যদি HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#অন্যথা
    মুক্ত(ptr);
#endif
}

শূন্য av_freep(শূন্য *arg)
{
    শূন্য *val;

    memcpy(&val, arg, পরিমাণ(val));
    memcpy(arg, &(শূন্য *){ রিক্ত }, পরিমাণ(val));
    av_free(val);
}

শূন্য *av_mallocz(size_t size)
{
    শূন্য *ptr = av_malloc(size);
    যদি (ptr)
        memset(ptr, 0, size);
    ঘূৰাই ptr;
}

শূন্য *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    যদি (size_mult(nmemb, size, &result) < 0)
        ঘূৰাই রিক্ত;
    ঘূৰাই av_mallocz(result);
}

ৱর্ণ *av_strdup(ধ্রুৱ ৱর্ণ *s)
{
    ৱর্ণ *ptr = রিক্ত;
    যদি (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(রিক্ত, len);
        যদি (ptr)
            memcpy(ptr, s, len);
    }
    ঘূৰাই ptr;
}

ৱর্ণ *av_strndup(ধ্রুৱ ৱর্ণ *s, size_t len)
{
    যদি (!s)
        ঘূৰাই রিক্ত;

    ধ্রুৱ ৱর্ণ *end = memchr(s, 0, len);
    যদি (end)
        len = end - s;

    ৱর্ণ *ret = av_realloc(রিক্ত, len + 1);
    যদি (!ret)
        ঘূৰাই রিক্ত;

    memcpy(ret, s, len);
    ret[len] = 0;
    ঘূৰাই ret;
}

শূন্য *av_memdup(ধ্রুৱ শূন্য *p, size_t size)
{
    শূন্য *ptr = রিক্ত;
    যদি (p) {
        ptr = av_malloc(size);
        যদি (ptr)
            memcpy(ptr, p, size);
    }
    ঘূৰাই ptr;
}

পূর্ণাঙ্ক av_dynarray_add_nofree(শূন্য *tab_ptr, পূর্ণাঙ্ক *nb_ptr, শূন্য *elem)
{
    শূন্য **tab;
    memcpy(&tab, tab_ptr, পরিমাণ(tab));

    FF_DYNARRAY_ADD(INT_MAX, পরিমাণ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, পরিমাণ(tab));
    }, {
        ঘূৰাই AVERROR(ENOMEM);
    });
    ঘূৰাই 0;
}

শূন্য av_dynarray_add(শূন্য *tab_ptr, পূর্ণাঙ্ক *nb_ptr, শূন্য *elem)
{
    শূন্য **tab;
    memcpy(&tab, tab_ptr, পরিমাণ(tab));

    FF_DYNARRAY_ADD(INT_MAX, পরিমাণ(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, পরিমাণ(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

শূন্য *av_dynarray2_add(শূন্য **tab_ptr, পূর্ণাঙ্ক *nb_ptr, size_t elem_size,
                       ধ্রুৱ uint8_t *elem_data)
{
    uint8_t *tab_elem_data = রিক্ত;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        যদি (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        অন্যথা
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    ঘূৰাই tab_elem_data;
}

স্থির শূন্য fill16(uint8_t *dst, পূর্ণাঙ্ক len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    যেতিয়ালৈ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    যেতিয়ালৈ (len--) {
        *dst = dst[-2];
        dst++;
    }
}

স্থির শূন্য fill24(uint8_t *dst, পূর্ণাঙ্ক len)
{
#যদি HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#অন্যথা
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    যেতিয়ালৈ (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    যদি (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    যদি (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    যেতিয়ালৈ (len--) {
        *dst = dst[-3];
        dst++;
    }
}

স্থির শূন্য fill32(uint8_t *dst, পূর্ণাঙ্ক len)
{
    uint32_t v = AV_RN32(dst - 4);

#যদি HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    যেতিয়ালৈ (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    যেতিয়ালৈ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    যেতিয়ালৈ (len--) {
        *dst = dst[-4];
        dst++;
    }
}

শূন্য av_memcpy_backptr(uint8_t *dst, পূর্ণাঙ্ক back, পূর্ণাঙ্ক cnt)
{
    ধ্রুৱ uint8_t *src = &dst[-back];
    যদি (!back)
        ঘূৰাই;

    যদি (back == 1) {
        memset(dst, *src, cnt);
    } অন্যথা যদি (back == 2) {
        fill16(dst, cnt);
    } অন্যথা যদি (back == 3) {
        fill24(dst, cnt);
    } অন্যথা যদি (back == 4) {
        fill32(dst, cnt);
    } অন্যথা {
        যদি (cnt >= 16) {
            পূর্ণাঙ্ক blocklen = back;
            যেতিয়ালৈ (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            ঘূৰাই;
        }
        যদি (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        যদি (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        যদি (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        যদি (cnt)
            *dst = *src;
    }
}

শূন্য *av_fast_realloc(শূন্য *ptr, unsigned পূর্ণাঙ্ক *size, size_t min_size)
{
    size_t max_size;

    যদি (min_size <= *size)
        ঘূৰাই ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    যদি (min_size > max_size) {
        *size = 0;
        ঘূৰাই রিক্ত;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    যদি (!ptr)
        min_size = 0;

    *size = min_size;

    ঘূৰাই ptr;
}

স্থির অন্তঃস্থ শূন্য fast_malloc(শূন্য *ptr, unsigned পূর্ণাঙ্ক *size, size_t min_size, পূর্ণাঙ্ক zero_realloc)
{
    size_t max_size;
    শূন্য *val;

    memcpy(&val, ptr, পরিমাণ(val));
    যদি (min_size <= *size) {
        av_assert0(val || !min_size);
        ঘূৰাই;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    যদি (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        ঘূৰাই;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, পরিমাণ(val));
    যদি (!val)
        min_size = 0;
    *size = min_size;
    ঘূৰাই;
}

শূন্য av_fast_malloc(শূন্য *ptr, unsigned পূর্ণাঙ্ক *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

শূন্য av_fast_mallocz(শূন্য *ptr, unsigned পূর্ণাঙ্ক *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

পূর্ণাঙ্ক av_size_mult(size_t a, size_t b, size_t *r)
{
    ঘূৰাই size_mult(a, b, r);
}

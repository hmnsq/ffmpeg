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

#अन्तर्भाव "config.h"

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव <string.h>
#जइ HAVE_MALLOC_H
#अन्तर्भाव <malloc.h>
#endif

#अन्तर्भाव "attributes.h"
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "dynarray.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "internal.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define मुक्त           AV_JOIN(MALLOC_PREFIX, मुक्त)

शून्य *malloc(size_t size);
शून्य *memalign(size_t align, size_t size);
पूर्णाङ्क   posix_memalign(शून्य **ptr, size_t align, size_t size);
शून्य *realloc(शून्य *ptr, size_t size);
शून्य  मुक्त(शून्य *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

स्थिर शून्य poison_memory(शून्य *ptr, size_t size)
{
#जइ CONFIG_MEMORY_POISONING
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
#जइ HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

स्थिर पूर्णाङ्क asan_aligned_alloc_needed(शून्य)
{
    स्थिर atomic_int needed = -1;
    पूर्णाङ्क ret = atomic_load_explicit(&needed, memory_order_relaxed);

    जइ (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        पूर्णाङ्क probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        जइ (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    प्रत्यागम ret;
}

प्रकारनिर्देश संरचना AsanAlignedHeader {
    शून्य  *base;
    size_t size;
} AsanAlignedHeader;

स्थिर शून्य *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    जइ (size > SIZE_MAX - ALIGN - परिमाण(*hdr))
        प्रत्यागम रिक्त;
    total = size + ALIGN + परिमाण(*hdr);
    base  = malloc(total);
    जइ (!base)
        प्रत्यागम रिक्त;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + परिमाण(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    प्रत्यागम ptr;
}

स्थिर AsanAlignedHeader *asan_aligned_header(शून्य *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, परिमाण(*hdr));
    प्रत्यागम hdr;
}

स्थिर शून्य asan_aligned_free(शून्य *ptr)
{
    जइ (ptr)
        मुक्त(asan_aligned_header(ptr)->base);
}

स्थिर शून्य *asan_aligned_realloc(शून्य *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    शून्य *ret;

    जइ (!ptr)
        प्रत्यागम asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    जइ (!ret)
        प्रत्यागम रिक्त;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    मुक्त(hdr->base);
    प्रत्यागम ret;
}
#अण्णहा
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

स्थिर atomic_size_t max_alloc_size = INT_MAX;

शून्य av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

स्थिर पूर्णाङ्क size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#जइ (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    जइ (__builtin_mul_overflow(a, b, &t))
        प्रत्यागम AVERROR(EINVAL);
#अण्णहा
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    जइ ((a | b) >= ((size_t)1 << (परिमाण(size_t) * 4)) && a && t / a != b)
        प्रत्यागम AVERROR(EINVAL);
#endif
    *r = t;
    प्रत्यागम 0;
}

शून्य *av_malloc(size_t size)
{
    शून्य *ptr = रिक्त;

    जइ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        प्रत्यागम रिक्त;

#जइ ASAN_ALIGNED_ALLOC
    जइ (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    अण्णहा
        ptr = _aligned_malloc(size, ALIGN);
#नोचेद्यदि HAVE_POSIX_MEMALIGN
    जइ (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    जइ (posix_memalign(&ptr, ALIGN, size))
        ptr = रिक्त;
#नोचेद्यदि HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#नोचेद्यदि HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#अण्णहा
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
#अण्णहा
    ptr = malloc(size);
#endif
    जइ(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    जइ (ptr)
        poison_memory(ptr, size);
    प्रत्यागम ptr;
}

शून्य *av_realloc(शून्य *ptr, size_t size)
{
    शून्य *ret;
    जइ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        प्रत्यागम रिक्त;

#जइ ASAN_ALIGNED_ALLOC
    जइ (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    अण्णहा
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#नोचेद्यदि HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#अण्णहा
    ret = realloc(ptr, size + !size);
#endif
    जइ (ret && !ptr)
        poison_memory(ret, size);
    प्रत्यागम ret;
}

शून्य *av_realloc_f(शून्य *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    शून्य *r;

    जइ (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        प्रत्यागम रिक्त;
    }
    r = av_realloc(ptr, size);
    जइ (!r)
        av_free(ptr);
    प्रत्यागम r;
}

पूर्णाङ्क av_reallocp(शून्य *ptr, size_t size)
{
    शून्य *val;

    जइ (!size) {
        av_freep(ptr);
        प्रत्यागम 0;
    }

    memcpy(&val, ptr, परिमाण(val));
    val = av_realloc(val, size);

    जइ (!val) {
        av_freep(ptr);
        प्रत्यागम AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, परिमाण(val));
    प्रत्यागम 0;
}

शून्य *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    जइ (size_mult(nmemb, size, &result) < 0)
        प्रत्यागम रिक्त;
    प्रत्यागम av_malloc(result);
}

शून्य *av_realloc_array(शून्य *ptr, size_t nmemb, size_t size)
{
    size_t result;
    जइ (size_mult(nmemb, size, &result) < 0)
        प्रत्यागम रिक्त;
    प्रत्यागम av_realloc(ptr, result);
}

पूर्णाङ्क av_reallocp_array(शून्य *ptr, size_t nmemb, size_t size)
{
    शून्य *val;

    memcpy(&val, ptr, परिमाण(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, परिमाण(val));
    जइ (!val && nmemb && size)
        प्रत्यागम AVERROR(ENOMEM);

    प्रत्यागम 0;
}

शून्य av_free(शून्य *ptr)
{
#जइ ASAN_ALIGNED_ALLOC
    जइ (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    अण्णहा
        _aligned_free(ptr);
#नोचेद्यदि HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#अण्णहा
    मुक्त(ptr);
#endif
}

शून्य av_freep(शून्य *arg)
{
    शून्य *val;

    memcpy(&val, arg, परिमाण(val));
    memcpy(arg, &(शून्य *){ रिक्त }, परिमाण(val));
    av_free(val);
}

शून्य *av_mallocz(size_t size)
{
    शून्य *ptr = av_malloc(size);
    जइ (ptr)
        memset(ptr, 0, size);
    प्रत्यागम ptr;
}

शून्य *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    जइ (size_mult(nmemb, size, &result) < 0)
        प्रत्यागम रिक्त;
    प्रत्यागम av_mallocz(result);
}

वर्ण *av_strdup(ध्रुव वर्ण *s)
{
    वर्ण *ptr = रिक्त;
    जइ (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(रिक्त, len);
        जइ (ptr)
            memcpy(ptr, s, len);
    }
    प्रत्यागम ptr;
}

वर्ण *av_strndup(ध्रुव वर्ण *s, size_t len)
{
    जइ (!s)
        प्रत्यागम रिक्त;

    ध्रुव वर्ण *end = memchr(s, 0, len);
    जइ (end)
        len = end - s;

    वर्ण *ret = av_realloc(रिक्त, len + 1);
    जइ (!ret)
        प्रत्यागम रिक्त;

    memcpy(ret, s, len);
    ret[len] = 0;
    प्रत्यागम ret;
}

शून्य *av_memdup(ध्रुव शून्य *p, size_t size)
{
    शून्य *ptr = रिक्त;
    जइ (p) {
        ptr = av_malloc(size);
        जइ (ptr)
            memcpy(ptr, p, size);
    }
    प्रत्यागम ptr;
}

पूर्णाङ्क av_dynarray_add_nofree(शून्य *tab_ptr, पूर्णाङ्क *nb_ptr, शून्य *elem)
{
    शून्य **tab;
    memcpy(&tab, tab_ptr, परिमाण(tab));

    FF_DYNARRAY_ADD(INT_MAX, परिमाण(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, परिमाण(tab));
    }, {
        प्रत्यागम AVERROR(ENOMEM);
    });
    प्रत्यागम 0;
}

शून्य av_dynarray_add(शून्य *tab_ptr, पूर्णाङ्क *nb_ptr, शून्य *elem)
{
    शून्य **tab;
    memcpy(&tab, tab_ptr, परिमाण(tab));

    FF_DYNARRAY_ADD(INT_MAX, परिमाण(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, परिमाण(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

शून्य *av_dynarray2_add(शून्य **tab_ptr, पूर्णाङ्क *nb_ptr, size_t elem_size,
                       ध्रुव uint8_t *elem_data)
{
    uint8_t *tab_elem_data = रिक्त;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        जइ (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        अण्णहा
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    प्रत्यागम tab_elem_data;
}

स्थिर शून्य fill16(uint8_t *dst, पूर्णाङ्क len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    जाव (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    जाव (len--) {
        *dst = dst[-2];
        dst++;
    }
}

स्थिर शून्य fill24(uint8_t *dst, पूर्णाङ्क len)
{
#जइ HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#अण्णहा
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    जाव (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    जइ (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    जइ (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    जाव (len--) {
        *dst = dst[-3];
        dst++;
    }
}

स्थिर शून्य fill32(uint8_t *dst, पूर्णाङ्क len)
{
    uint32_t v = AV_RN32(dst - 4);

#जइ HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    जाव (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    जाव (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    जाव (len--) {
        *dst = dst[-4];
        dst++;
    }
}

शून्य av_memcpy_backptr(uint8_t *dst, पूर्णाङ्क back, पूर्णाङ्क cnt)
{
    ध्रुव uint8_t *src = &dst[-back];
    जइ (!back)
        प्रत्यागम;

    जइ (back == 1) {
        memset(dst, *src, cnt);
    } अण्णहा जइ (back == 2) {
        fill16(dst, cnt);
    } अण्णहा जइ (back == 3) {
        fill24(dst, cnt);
    } अण्णहा जइ (back == 4) {
        fill32(dst, cnt);
    } अण्णहा {
        जइ (cnt >= 16) {
            पूर्णाङ्क blocklen = back;
            जाव (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            प्रत्यागम;
        }
        जइ (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        जइ (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        जइ (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        जइ (cnt)
            *dst = *src;
    }
}

शून्य *av_fast_realloc(शून्य *ptr, unsigned पूर्णाङ्क *size, size_t min_size)
{
    size_t max_size;

    जइ (min_size <= *size)
        प्रत्यागम ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    जइ (min_size > max_size) {
        *size = 0;
        प्रत्यागम रिक्त;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    जइ (!ptr)
        min_size = 0;

    *size = min_size;

    प्रत्यागम ptr;
}

स्थिर अन्तःस्थ शून्य fast_malloc(शून्य *ptr, unsigned पूर्णाङ्क *size, size_t min_size, पूर्णाङ्क zero_realloc)
{
    size_t max_size;
    शून्य *val;

    memcpy(&val, ptr, परिमाण(val));
    जइ (min_size <= *size) {
        av_assert0(val || !min_size);
        प्रत्यागम;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    जइ (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        प्रत्यागम;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, परिमाण(val));
    जइ (!val)
        min_size = 0;
    *size = min_size;
    प्रत्यागम;
}

शून्य av_fast_malloc(शून्य *ptr, unsigned पूर्णाङ्क *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

शून्य av_fast_mallocz(शून्य *ptr, unsigned पूर्णाङ्क *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

पूर्णाङ्क av_size_mult(size_t a, size_t b, size_t *r)
{
    प्रत्यागम size_mult(a, b, r);
}

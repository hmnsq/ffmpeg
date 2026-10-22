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

#അന്തര്ഭാവ "config.h"

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <stdlib.h>
#അന്തര്ഭാവ <stdatomic.h>
#അന്തര്ഭാവ <string.h>
#എങ്കിൽ HAVE_MALLOC_H
#അന്തര്ഭാവ <malloc.h>
#endif

#അന്തര്ഭാവ "attributes.h"
#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "dynarray.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "internal.h"
#അന്തര്ഭാവ "intreadwrite.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "sanitizer.h"

#ifdef MALLOC_PREFIX

#define malloc         AV_JOIN(MALLOC_PREFIX, malloc)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define realloc        AV_JOIN(MALLOC_PREFIX, realloc)
#define സ്വതന്ത്രം           AV_JOIN(MALLOC_PREFIX, സ്വതന്ത്രം)

ശൂന്യം *malloc(size_t size);
ശൂന്യം *memalign(size_t align, size_t size);
പൂർണ്ണസംഖ്യ   posix_memalign(ശൂന്യം **ptr, size_t align, size_t size);
ശൂന്യം *realloc(ശൂന്യം *ptr, size_t size);
ശൂന്യം  സ്വതന്ത്രം(ശൂന്യം *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

സ്ഥിതം ശൂന്യം poison_memory(ശൂന്യം *ptr, size_t size)
{
#എങ്കിൽ CONFIG_MEMORY_POISONING
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
#എങ്കിൽ HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

സ്ഥിതം പൂർണ്ണസംഖ്യ asan_aligned_alloc_needed(ശൂന്യം)
{
    സ്ഥിതം atomic_int needed = -1;
    പൂർണ്ണസംഖ്യ ret = atomic_load_explicit(&needed, memory_order_relaxed);

    എങ്കിൽ (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        പൂർണ്ണസംഖ്യ probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        എങ്കിൽ (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    തിരികെ ret;
}

തരനിർവചനം ഘടന AsanAlignedHeader {
    ശൂന്യം  *base;
    size_t size;
} AsanAlignedHeader;

സ്ഥിതം ശൂന്യം *asan_aligned_malloc(size_t size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    size_t total;

    എങ്കിൽ (size > SIZE_MAX - ALIGN - വലുപ്പം(*hdr))
        തിരികെ ശൂന്യ;
    total = size + ALIGN + വലുപ്പം(*hdr);
    base  = malloc(total);
    എങ്കിൽ (!base)
        തിരികെ ശൂന്യ;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + വലുപ്പം(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    തിരികെ ptr;
}

സ്ഥിതം AsanAlignedHeader *asan_aligned_header(ശൂന്യം *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, വലുപ്പം(*hdr));
    തിരികെ hdr;
}

സ്ഥിതം ശൂന്യം asan_aligned_free(ശൂന്യം *ptr)
{
    എങ്കിൽ (ptr)
        സ്വതന്ത്രം(asan_aligned_header(ptr)->base);
}

സ്ഥിതം ശൂന്യം *asan_aligned_realloc(ശൂന്യം *ptr, size_t size)
{
    AsanAlignedHeader *hdr;
    ശൂന്യം *ret;

    എങ്കിൽ (!ptr)
        തിരികെ asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    എങ്കിൽ (!ret)
        തിരികെ ശൂന്യ;
    hdr = asan_aligned_header(ptr);
    memcpy(ret, ptr, FFMIN(size, hdr->size));
    സ്വതന്ത്രം(hdr->base);
    തിരികെ ret;
}
#അല്ലെങ്കിൽ
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

സ്ഥിതം atomic_size_t max_alloc_size = INT_MAX;

ശൂന്യം av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ size_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#എങ്കിൽ (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    എങ്കിൽ (__builtin_mul_overflow(a, b, &t))
        തിരികെ AVERROR(EINVAL);
#അല്ലെങ്കിൽ
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    എങ്കിൽ ((a | b) >= ((size_t)1 << (വലുപ്പം(size_t) * 4)) && a && t / a != b)
        തിരികെ AVERROR(EINVAL);
#endif
    *r = t;
    തിരികെ 0;
}

ശൂന്യം *av_malloc(size_t size)
{
    ശൂന്യം *ptr = ശൂന്യ;

    എങ്കിൽ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        തിരികെ ശൂന്യ;

#എങ്കിൽ ASAN_ALIGNED_ALLOC
    എങ്കിൽ (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    അല്ലെങ്കിൽ
        ptr = _aligned_malloc(size, ALIGN);
#അല്ലെങ്കിലെങ്കിൽ HAVE_POSIX_MEMALIGN
    എങ്കിൽ (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    എങ്കിൽ (posix_memalign(&ptr, ALIGN, size))
        ptr = ശൂന്യ;
#അല്ലെങ്കിലെങ്കിൽ HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#അല്ലെങ്കിലെങ്കിൽ HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#അല്ലെങ്കിൽ
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
#അല്ലെങ്കിൽ
    ptr = malloc(size);
#endif
    എങ്കിൽ(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    എങ്കിൽ (ptr)
        poison_memory(ptr, size);
    തിരികെ ptr;
}

ശൂന്യം *av_realloc(ശൂന്യം *ptr, size_t size)
{
    ശൂന്യം *ret;
    എങ്കിൽ (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        തിരികെ ശൂന്യ;

#എങ്കിൽ ASAN_ALIGNED_ALLOC
    എങ്കിൽ (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    അല്ലെങ്കിൽ
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#അല്ലെങ്കിലെങ്കിൽ HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#അല്ലെങ്കിൽ
    ret = realloc(ptr, size + !size);
#endif
    എങ്കിൽ (ret && !ptr)
        poison_memory(ret, size);
    തിരികെ ret;
}

ശൂന്യം *av_realloc_f(ശൂന്യം *ptr, size_t nelem, size_t elsize)
{
    size_t size;
    ശൂന്യം *r;

    എങ്കിൽ (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        തിരികെ ശൂന്യ;
    }
    r = av_realloc(ptr, size);
    എങ്കിൽ (!r)
        av_free(ptr);
    തിരികെ r;
}

പൂർണ്ണസംഖ്യ av_reallocp(ശൂന്യം *ptr, size_t size)
{
    ശൂന്യം *val;

    എങ്കിൽ (!size) {
        av_freep(ptr);
        തിരികെ 0;
    }

    memcpy(&val, ptr, വലുപ്പം(val));
    val = av_realloc(val, size);

    എങ്കിൽ (!val) {
        av_freep(ptr);
        തിരികെ AVERROR(ENOMEM);
    }

    memcpy(ptr, &val, വലുപ്പം(val));
    തിരികെ 0;
}

ശൂന്യം *av_malloc_array(size_t nmemb, size_t size)
{
    size_t result;
    എങ്കിൽ (size_mult(nmemb, size, &result) < 0)
        തിരികെ ശൂന്യ;
    തിരികെ av_malloc(result);
}

ശൂന്യം *av_realloc_array(ശൂന്യം *ptr, size_t nmemb, size_t size)
{
    size_t result;
    എങ്കിൽ (size_mult(nmemb, size, &result) < 0)
        തിരികെ ശൂന്യ;
    തിരികെ av_realloc(ptr, result);
}

പൂർണ്ണസംഖ്യ av_reallocp_array(ശൂന്യം *ptr, size_t nmemb, size_t size)
{
    ശൂന്യം *val;

    memcpy(&val, ptr, വലുപ്പം(val));
    val = av_realloc_f(val, nmemb, size);
    memcpy(ptr, &val, വലുപ്പം(val));
    എങ്കിൽ (!val && nmemb && size)
        തിരികെ AVERROR(ENOMEM);

    തിരികെ 0;
}

ശൂന്യം av_free(ശൂന്യം *ptr)
{
#എങ്കിൽ ASAN_ALIGNED_ALLOC
    എങ്കിൽ (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    അല്ലെങ്കിൽ
        _aligned_free(ptr);
#അല്ലെങ്കിലെങ്കിൽ HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#അല്ലെങ്കിൽ
    സ്വതന്ത്രം(ptr);
#endif
}

ശൂന്യം av_freep(ശൂന്യം *arg)
{
    ശൂന്യം *val;

    memcpy(&val, arg, വലുപ്പം(val));
    memcpy(arg, &(ശൂന്യം *){ ശൂന്യ }, വലുപ്പം(val));
    av_free(val);
}

ശൂന്യം *av_mallocz(size_t size)
{
    ശൂന്യം *ptr = av_malloc(size);
    എങ്കിൽ (ptr)
        memset(ptr, 0, size);
    തിരികെ ptr;
}

ശൂന്യം *av_calloc(size_t nmemb, size_t size)
{
    size_t result;
    എങ്കിൽ (size_mult(nmemb, size, &result) < 0)
        തിരികെ ശൂന്യ;
    തിരികെ av_mallocz(result);
}

അക്ഷരം *av_strdup(സ്ഥിരം അക്ഷരം *s)
{
    അക്ഷരം *ptr = ശൂന്യ;
    എങ്കിൽ (s) {
        size_t len = strlen(s) + 1;
        ptr = av_realloc(ശൂന്യ, len);
        എങ്കിൽ (ptr)
            memcpy(ptr, s, len);
    }
    തിരികെ ptr;
}

അക്ഷരം *av_strndup(സ്ഥിരം അക്ഷരം *s, size_t len)
{
    എങ്കിൽ (!s)
        തിരികെ ശൂന്യ;

    സ്ഥിരം അക്ഷരം *end = memchr(s, 0, len);
    എങ്കിൽ (end)
        len = end - s;

    അക്ഷരം *ret = av_realloc(ശൂന്യ, len + 1);
    എങ്കിൽ (!ret)
        തിരികെ ശൂന്യ;

    memcpy(ret, s, len);
    ret[len] = 0;
    തിരികെ ret;
}

ശൂന്യം *av_memdup(സ്ഥിരം ശൂന്യം *p, size_t size)
{
    ശൂന്യം *ptr = ശൂന്യ;
    എങ്കിൽ (p) {
        ptr = av_malloc(size);
        എങ്കിൽ (ptr)
            memcpy(ptr, p, size);
    }
    തിരികെ ptr;
}

പൂർണ്ണസംഖ്യ av_dynarray_add_nofree(ശൂന്യം *tab_ptr, പൂർണ്ണസംഖ്യ *nb_ptr, ശൂന്യം *elem)
{
    ശൂന്യം **tab;
    memcpy(&tab, tab_ptr, വലുപ്പം(tab));

    FF_DYNARRAY_ADD(INT_MAX, വലുപ്പം(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, വലുപ്പം(tab));
    }, {
        തിരികെ AVERROR(ENOMEM);
    });
    തിരികെ 0;
}

ശൂന്യം av_dynarray_add(ശൂന്യം *tab_ptr, പൂർണ്ണസംഖ്യ *nb_ptr, ശൂന്യം *elem)
{
    ശൂന്യം **tab;
    memcpy(&tab, tab_ptr, വലുപ്പം(tab));

    FF_DYNARRAY_ADD(INT_MAX, വലുപ്പം(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        memcpy(tab_ptr, &tab, വലുപ്പം(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

ശൂന്യം *av_dynarray2_add(ശൂന്യം **tab_ptr, പൂർണ്ണസംഖ്യ *nb_ptr, size_t elem_size,
                       സ്ഥിരം uint8_t *elem_data)
{
    uint8_t *tab_elem_data = ശൂന്യ;

    FF_DYNARRAY_ADD(INT_MAX, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        എങ്കിൽ (elem_data)
            memcpy(tab_elem_data, elem_data, elem_size);
        അല്ലെങ്കിൽ
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    തിരികെ tab_elem_data;
}

സ്ഥിതം ശൂന്യം fill16(uint8_t *dst, പൂർണ്ണസംഖ്യ len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    ആകുമ്പോൾ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ആകുമ്പോൾ (len--) {
        *dst = dst[-2];
        dst++;
    }
}

സ്ഥിതം ശൂന്യം fill24(uint8_t *dst, പൂർണ്ണസംഖ്യ len)
{
#എങ്കിൽ HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#അല്ലെങ്കിൽ
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    ആകുമ്പോൾ (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    എങ്കിൽ (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    എങ്കിൽ (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    ആകുമ്പോൾ (len--) {
        *dst = dst[-3];
        dst++;
    }
}

സ്ഥിതം ശൂന്യം fill32(uint8_t *dst, പൂർണ്ണസംഖ്യ len)
{
    uint32_t v = AV_RN32(dst - 4);

#എങ്കിൽ HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    ആകുമ്പോൾ (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    ആകുമ്പോൾ (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    ആകുമ്പോൾ (len--) {
        *dst = dst[-4];
        dst++;
    }
}

ശൂന്യം av_memcpy_backptr(uint8_t *dst, പൂർണ്ണസംഖ്യ back, പൂർണ്ണസംഖ്യ cnt)
{
    സ്ഥിരം uint8_t *src = &dst[-back];
    എങ്കിൽ (!back)
        തിരികെ;

    എങ്കിൽ (back == 1) {
        memset(dst, *src, cnt);
    } അല്ലെങ്കിൽ എങ്കിൽ (back == 2) {
        fill16(dst, cnt);
    } അല്ലെങ്കിൽ എങ്കിൽ (back == 3) {
        fill24(dst, cnt);
    } അല്ലെങ്കിൽ എങ്കിൽ (back == 4) {
        fill32(dst, cnt);
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (cnt >= 16) {
            പൂർണ്ണസംഖ്യ blocklen = back;
            ആകുമ്പോൾ (cnt > blocklen) {
                memcpy(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            memcpy(dst, src, cnt);
            തിരികെ;
        }
        എങ്കിൽ (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        എങ്കിൽ (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        എങ്കിൽ (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        എങ്കിൽ (cnt)
            *dst = *src;
    }
}

ശൂന്യം *av_fast_realloc(ശൂന്യം *ptr, unsigned പൂർണ്ണസംഖ്യ *size, size_t min_size)
{
    size_t max_size;

    എങ്കിൽ (min_size <= *size)
        തിരികെ ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    എങ്കിൽ (min_size > max_size) {
        *size = 0;
        തിരികെ ശൂന്യ;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    എങ്കിൽ (!ptr)
        min_size = 0;

    *size = min_size;

    തിരികെ ptr;
}

സ്ഥിതം വരിയിൽ ശൂന്യം fast_malloc(ശൂന്യം *ptr, unsigned പൂർണ്ണസംഖ്യ *size, size_t min_size, പൂർണ്ണസംഖ്യ zero_realloc)
{
    size_t max_size;
    ശൂന്യം *val;

    memcpy(&val, ptr, വലുപ്പം(val));
    എങ്കിൽ (min_size <= *size) {
        av_assert0(val || !min_size);
        തിരികെ;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, UINT_MAX);

    എങ്കിൽ (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        തിരികെ;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    memcpy(ptr, &val, വലുപ്പം(val));
    എങ്കിൽ (!val)
        min_size = 0;
    *size = min_size;
    തിരികെ;
}

ശൂന്യം av_fast_malloc(ശൂന്യം *ptr, unsigned പൂർണ്ണസംഖ്യ *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

ശൂന്യം av_fast_mallocz(ശൂന്യം *ptr, unsigned പൂർണ്ണസംഖ്യ *size, size_t min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

പൂർണ്ണസംഖ്യ av_size_mult(size_t a, size_t b, size_t *r)
{
    തിരികെ size_mult(a, b, r);
}

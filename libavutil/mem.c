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
#जर HAVE_MALLOC_H
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

#define दो_स्मृति         AV_JOIN(MALLOC_PREFIX, दो_स्मृति)
#define memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#define posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#define पुनः_स्मृति        AV_JOIN(MALLOC_PREFIX, पुनः_स्मृति)
#define मुक्त           AV_JOIN(MALLOC_PREFIX, मुक्त)

शून्य *दो_स्मृति(माप_प्रकार size);
शून्य *memalign(माप_प्रकार align, माप_प्रकार size);
पूर्णांक   posix_memalign(शून्य **ptr, माप_प्रकार align, माप_प्रकार size);
शून्य *पुनः_स्मृति(शून्य *ptr, माप_प्रकार size);
शून्य  मुक्त(शून्य *ptr);

#endif /* MALLOC_PREFIX */

#define ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#define FF_MEMORY_POISON 0x2a

स्थिर शून्य poison_memory(शून्य *ptr, माप_प्रकार size)
{
#जर CONFIG_MEMORY_POISONING
    स_रखो(ptr, FF_MEMORY_POISON, size);
#endif
    FF_MEM_UNDEFINED(ptr, size);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#जर HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#define ASAN_ALIGNED_ALLOC 1

स्थिर पूर्णांक asan_aligned_alloc_needed(शून्य)
{
    स्थिर atomic_int needed = -1;
    पूर्णांक ret = atomic_load_explicit(&needed, memory_order_relaxed);

    जर (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        पूर्णांक probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        जर (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    परत ret;
}

प्रकारव्याख्या संरचना AsanAlignedHeader {
    शून्य  *base;
    माप_प्रकार size;
} AsanAlignedHeader;

स्थिर शून्य *asan_aligned_malloc(माप_प्रकार size)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    माप_प्रकार total;

    जर (size > SIZE_MAX - ALIGN - आकार(*hdr))
        परत रिक्त;
    total = size + ALIGN + आकार(*hdr);
    base  = दो_स्मृति(total);
    जर (!base)
        परत रिक्त;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + आकार(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->size = size;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + size, base + total - (ptr + size));
    परत ptr;
}

स्थिर AsanAlignedHeader *asan_aligned_header(शून्य *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, आकार(*hdr));
    परत hdr;
}

स्थिर शून्य asan_aligned_free(शून्य *ptr)
{
    जर (ptr)
        मुक्त(asan_aligned_header(ptr)->base);
}

स्थिर शून्य *asan_aligned_realloc(शून्य *ptr, माप_प्रकार size)
{
    AsanAlignedHeader *hdr;
    शून्य *ret;

    जर (!ptr)
        परत asan_aligned_malloc(size);
    ret = asan_aligned_malloc(size);
    जर (!ret)
        परत रिक्त;
    hdr = asan_aligned_header(ptr);
    स_नकल(ret, ptr, FFMIN(size, hdr->size));
    मुक्त(hdr->base);
    परत ret;
}
#अन्यथा
#define ASAN_ALIGNED_ALLOC 0
#endif

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

स्थिर atomic_size_t max_alloc_size = पूर्णांक_उच्च;

शून्य av_max_alloc(माप_प्रकार max){
    atomic_store_explicit(&max_alloc_size, max, memory_order_relaxed);
}

स्थिर पूर्णांक size_mult(माप_प्रकार a, माप_प्रकार b, माप_प्रकार *r)
{
    माप_प्रकार t;

#जर (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    जर (__builtin_mul_overflow(a, b, &t))
        परत AVERROR(EINVAL);
#अन्यथा
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    जर ((a | b) >= ((माप_प्रकार)1 << (आकार(माप_प्रकार) * 4)) && a && t / a != b)
        परत AVERROR(EINVAL);
#endif
    *r = t;
    परत 0;
}

शून्य *av_malloc(माप_प्रकार size)
{
    शून्य *ptr = रिक्त;

    जर (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        परत रिक्त;

#जर ASAN_ALIGNED_ALLOC
    जर (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(size);
    अन्यथा
        ptr = _aligned_malloc(size, ALIGN);
#किंवाजर HAVE_POSIX_MEMALIGN
    जर (size) //OS X on SDK 10.6 has a broken posix_memalign implementation
    जर (posix_memalign(&ptr, ALIGN, size))
        ptr = रिक्त;
#किंवाजर HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(size, ALIGN);
#किंवाजर HAVE_MEMALIGN
#ifndef __DJGPP__
    ptr = memalign(ALIGN, size);
#अन्यथा
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
#अन्यथा
    ptr = दो_स्मृति(size);
#endif
    जर(!ptr && !size) {
        size = 1;
        ptr= av_malloc(1);
    }
    जर (ptr)
        poison_memory(ptr, size);
    परत ptr;
}

शून्य *av_realloc(शून्य *ptr, माप_प्रकार size)
{
    शून्य *ret;
    जर (size > atomic_load_explicit(&max_alloc_size, memory_order_relaxed))
        परत रिक्त;

#जर ASAN_ALIGNED_ALLOC
    जर (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, size + !size);
    अन्यथा
        ret = _aligned_realloc(ptr, size + !size, ALIGN);
#किंवाजर HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, size + !size, ALIGN);
#अन्यथा
    ret = पुनः_स्मृति(ptr, size + !size);
#endif
    जर (ret && !ptr)
        poison_memory(ret, size);
    परत ret;
}

शून्य *av_realloc_f(शून्य *ptr, माप_प्रकार nelem, माप_प्रकार elsize)
{
    माप_प्रकार size;
    शून्य *r;

    जर (size_mult(elsize, nelem, &size)) {
        av_free(ptr);
        परत रिक्त;
    }
    r = av_realloc(ptr, size);
    जर (!r)
        av_free(ptr);
    परत r;
}

पूर्णांक av_reallocp(शून्य *ptr, माप_प्रकार size)
{
    शून्य *val;

    जर (!size) {
        av_freep(ptr);
        परत 0;
    }

    स_नकल(&val, ptr, आकार(val));
    val = av_realloc(val, size);

    जर (!val) {
        av_freep(ptr);
        परत AVERROR(ENOMEM);
    }

    स_नकल(ptr, &val, आकार(val));
    परत 0;
}

शून्य *av_malloc_array(माप_प्रकार nmemb, माप_प्रकार size)
{
    माप_प्रकार result;
    जर (size_mult(nmemb, size, &result) < 0)
        परत रिक्त;
    परत av_malloc(result);
}

शून्य *av_realloc_array(शून्य *ptr, माप_प्रकार nmemb, माप_प्रकार size)
{
    माप_प्रकार result;
    जर (size_mult(nmemb, size, &result) < 0)
        परत रिक्त;
    परत av_realloc(ptr, result);
}

पूर्णांक av_reallocp_array(शून्य *ptr, माप_प्रकार nmemb, माप_प्रकार size)
{
    शून्य *val;

    स_नकल(&val, ptr, आकार(val));
    val = av_realloc_f(val, nmemb, size);
    स_नकल(ptr, &val, आकार(val));
    जर (!val && nmemb && size)
        परत AVERROR(ENOMEM);

    परत 0;
}

शून्य av_free(शून्य *ptr)
{
#जर ASAN_ALIGNED_ALLOC
    जर (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    अन्यथा
        _aligned_free(ptr);
#किंवाजर HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#अन्यथा
    मुक्त(ptr);
#endif
}

शून्य av_freep(शून्य *arg)
{
    शून्य *val;

    स_नकल(&val, arg, आकार(val));
    स_नकल(arg, &(शून्य *){ रिक्त }, आकार(val));
    av_free(val);
}

शून्य *av_mallocz(माप_प्रकार size)
{
    शून्य *ptr = av_malloc(size);
    जर (ptr)
        स_रखो(ptr, 0, size);
    परत ptr;
}

शून्य *av_calloc(माप_प्रकार nmemb, माप_प्रकार size)
{
    माप_प्रकार result;
    जर (size_mult(nmemb, size, &result) < 0)
        परत रिक्त;
    परत av_mallocz(result);
}

अक्षर *av_strdup(स्थिरांक अक्षर *s)
{
    अक्षर *ptr = रिक्त;
    जर (s) {
        माप_प्रकार len = म_माप(s) + 1;
        ptr = av_realloc(रिक्त, len);
        जर (ptr)
            स_नकल(ptr, s, len);
    }
    परत ptr;
}

अक्षर *av_strndup(स्थिरांक अक्षर *s, माप_प्रकार len)
{
    जर (!s)
        परत रिक्त;

    स्थिरांक अक्षर *end = स_प्रथम(s, 0, len);
    जर (end)
        len = end - s;

    अक्षर *ret = av_realloc(रिक्त, len + 1);
    जर (!ret)
        परत रिक्त;

    स_नकल(ret, s, len);
    ret[len] = 0;
    परत ret;
}

शून्य *av_memdup(स्थिरांक शून्य *p, माप_प्रकार size)
{
    शून्य *ptr = रिक्त;
    जर (p) {
        ptr = av_malloc(size);
        जर (ptr)
            स_नकल(ptr, p, size);
    }
    परत ptr;
}

पूर्णांक av_dynarray_add_nofree(शून्य *tab_ptr, पूर्णांक *nb_ptr, शून्य *elem)
{
    शून्य **tab;
    स_नकल(&tab, tab_ptr, आकार(tab));

    FF_DYNARRAY_ADD(पूर्णांक_उच्च, आकार(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        स_नकल(tab_ptr, &tab, आकार(tab));
    }, {
        परत AVERROR(ENOMEM);
    });
    परत 0;
}

शून्य av_dynarray_add(शून्य *tab_ptr, पूर्णांक *nb_ptr, शून्य *elem)
{
    शून्य **tab;
    स_नकल(&tab, tab_ptr, आकार(tab));

    FF_DYNARRAY_ADD(पूर्णांक_उच्च, आकार(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        स_नकल(tab_ptr, &tab, आकार(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

शून्य *av_dynarray2_add(शून्य **tab_ptr, पूर्णांक *nb_ptr, माप_प्रकार elem_size,
                       स्थिरांक uint8_t *elem_data)
{
    uint8_t *tab_elem_data = रिक्त;

    FF_DYNARRAY_ADD(पूर्णांक_उच्च, elem_size, *tab_ptr, *nb_ptr, {
        tab_elem_data = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_size;
        जर (elem_data)
            स_नकल(tab_elem_data, elem_data, elem_size);
        अन्यथा
            poison_memory(tab_elem_data, elem_size);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    परत tab_elem_data;
}

स्थिर शून्य fill16(uint8_t *dst, पूर्णांक len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    पर्यंत (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    पर्यंत (len--) {
        *dst = dst[-2];
        dst++;
    }
}

स्थिर शून्य fill24(uint8_t *dst, पूर्णांक len)
{
#जर HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#अन्यथा
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#endif

    पर्यंत (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    जर (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    जर (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    पर्यंत (len--) {
        *dst = dst[-3];
        dst++;
    }
}

स्थिर शून्य fill32(uint8_t *dst, पूर्णांक len)
{
    uint32_t v = AV_RN32(dst - 4);

#जर HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    पर्यंत (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#endif

    पर्यंत (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    पर्यंत (len--) {
        *dst = dst[-4];
        dst++;
    }
}

शून्य av_memcpy_backptr(uint8_t *dst, पूर्णांक back, पूर्णांक cnt)
{
    स्थिरांक uint8_t *src = &dst[-back];
    जर (!back)
        परत;

    जर (back == 1) {
        स_रखो(dst, *src, cnt);
    } अन्यथा जर (back == 2) {
        fill16(dst, cnt);
    } अन्यथा जर (back == 3) {
        fill24(dst, cnt);
    } अन्यथा जर (back == 4) {
        fill32(dst, cnt);
    } अन्यथा {
        जर (cnt >= 16) {
            पूर्णांक blocklen = back;
            पर्यंत (cnt > blocklen) {
                स_नकल(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            स_नकल(dst, src, cnt);
            परत;
        }
        जर (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        जर (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        जर (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        जर (cnt)
            *dst = *src;
    }
}

शून्य *av_fast_realloc(शून्य *ptr, अचिन्हित पूर्णांक *size, माप_प्रकार min_size)
{
    माप_प्रकार max_size;

    जर (min_size <= *size)
        परत ptr;

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, अच_पूर्णांक_उच्च);

    जर (min_size > max_size) {
        *size = 0;
        परत रिक्त;
    }

    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));

    ptr = av_realloc(ptr, min_size);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    जर (!ptr)
        min_size = 0;

    *size = min_size;

    परत ptr;
}

स्थिर ओळीत शून्य fast_malloc(शून्य *ptr, अचिन्हित पूर्णांक *size, माप_प्रकार min_size, पूर्णांक zero_realloc)
{
    माप_प्रकार max_size;
    शून्य *val;

    स_नकल(&val, ptr, आकार(val));
    जर (min_size <= *size) {
        av_assert0(val || !min_size);
        परत;
    }

    max_size = atomic_load_explicit(&max_alloc_size, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_size = FFMIN(max_size, अच_पूर्णांक_उच्च);

    जर (min_size > max_size) {
        av_freep(ptr);
        *size = 0;
        परत;
    }
    min_size = FFMIN(max_size, FFMAX(min_size + min_size / 16 + 32, min_size));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_size) : av_malloc(min_size);
    स_नकल(ptr, &val, आकार(val));
    जर (!val)
        min_size = 0;
    *size = min_size;
    परत;
}

शून्य av_fast_malloc(शून्य *ptr, अचिन्हित पूर्णांक *size, माप_प्रकार min_size)
{
    fast_malloc(ptr, size, min_size, 0);
}

शून्य av_fast_mallocz(शून्य *ptr, अचिन्हित पूर्णांक *size, माप_प्रकार min_size)
{
    fast_malloc(ptr, size, min_size, 1);
}

पूर्णांक av_size_mult(माप_प्रकार a, माप_प्रकार b, माप_प्रकार *r)
{
    परत size_mult(a, b, r);
}

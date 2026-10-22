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

#घोषणा _XOPEN_SOURCE 600

#समावेश "config.h"

#समावेश <limits.h>
#समावेश <stdint.h>
#समावेश <stdlib.h>
#समावेश <stdatomic.h>
#समावेश <string.h>
#अगर HAVE_MALLOC_H
#समावेश <malloc.h>
#पूर्ण_अगर

#समावेश "attributes.h"
#समावेश "avassert.h"
#समावेश "dynarray.h"
#समावेश "error.h"
#समावेश "internal.h"
#समावेश "intreadwrite.h"
#समावेश "macros.h"
#समावेश "mem.h"
#समावेश "sanitizer.h"

#अगर_घोषित MALLOC_PREFIX

#घोषणा दो_स्मृति         AV_JOIN(MALLOC_PREFIX, दो_स्मृति)
#घोषणा memalign       AV_JOIN(MALLOC_PREFIX, memalign)
#घोषणा posix_memalign AV_JOIN(MALLOC_PREFIX, posix_memalign)
#घोषणा पुनः_स्मृति        AV_JOIN(MALLOC_PREFIX, पुनः_स्मृति)
#घोषणा मुक्त           AV_JOIN(MALLOC_PREFIX, मुक्त)

व्योम *दो_स्मृति(माप_प्रकार आकार);
व्योम *memalign(माप_प्रकार align, माप_प्रकार आकार);
पूर्णांक   posix_memalign(व्योम **ptr, माप_प्रकार align, माप_प्रकार आकार);
व्योम *पुनः_स्मृति(व्योम *ptr, माप_प्रकार आकार);
व्योम  मुक्त(व्योम *ptr);

#पूर्ण_अगर /* MALLOC_PREFIX */

#घोषणा ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#घोषणा FF_MEMORY_POISON 0x2a

अटल व्योम poison_memory(व्योम *ptr, माप_प्रकार आकार)
{
#अगर CONFIG_MEMORY_POISONING
    स_रखो(ptr, FF_MEMORY_POISON, आकार);
#पूर्ण_अगर
    FF_MEM_UNDEFINED(ptr, आकार);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#अगर HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#घोषणा ASAN_ALIGNED_ALLOC 1

अटल पूर्णांक asan_aligned_alloc_needed(व्योम)
{
    अटल atomic_int needed = -1;
    पूर्णांक ret = atomic_load_explicit(&needed, memory_order_relaxed);

    अगर (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        पूर्णांक probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        अगर (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    वापस ret;
}

प्रकार काष्ठा AsanAlignedHeader {
    व्योम  *base;
    माप_प्रकार आकार;
} AsanAlignedHeader;

अटल व्योम *asan_aligned_malloc(माप_प्रकार आकार)
{
    AsanAlignedHeader *hdr;
    uint8_t *base, *ptr;
    माप_प्रकार योग_2;

    अगर (आकार > SIZE_MAX - ALIGN - माप(*hdr))
        वापस शून्य;
    योग_2 = आकार + ALIGN + माप(*hdr);
    base  = दो_स्मृति(योग_2);
    अगर (!base)
        वापस शून्य;
    ptr = (uint8_t *)FFALIGN((uintptr_t)base + माप(*hdr), ALIGN);
    hdr = (AsanAlignedHeader *)ptr - 1;
    hdr->base = base;
    hdr->आकार = आकार;
    FF_ASAN_POISON(base, ptr - base);
    FF_ASAN_POISON(ptr + आकार, base + योग_2 - (ptr + आकार));
    वापस ptr;
}

अटल AsanAlignedHeader *asan_aligned_header(व्योम *ptr)
{
    AsanAlignedHeader *hdr = (AsanAlignedHeader *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, माप(*hdr));
    वापस hdr;
}

अटल व्योम asan_aligned_free(व्योम *ptr)
{
    अगर (ptr)
        मुक्त(asan_aligned_header(ptr)->base);
}

अटल व्योम *asan_aligned_realloc(व्योम *ptr, माप_प्रकार आकार)
{
    AsanAlignedHeader *hdr;
    व्योम *ret;

    अगर (!ptr)
        वापस asan_aligned_malloc(आकार);
    ret = asan_aligned_malloc(आकार);
    अगर (!ret)
        वापस शून्य;
    hdr = asan_aligned_header(ptr);
    स_नकल(ret, ptr, FFMIN(आकार, hdr->आकार));
    मुक्त(hdr->base);
    वापस ret;
}
#अन्यथा
#घोषणा ASAN_ALIGNED_ALLOC 0
#पूर्ण_अगर

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

अटल atomic_size_t max_alloc_आकार = पूर्णांक_उच्च;

व्योम av_max_alloc(माप_प्रकार max){
    atomic_store_explicit(&max_alloc_आकार, max, memory_order_relaxed);
}

अटल पूर्णांक आकार_mult(माप_प्रकार a, माप_प्रकार b, माप_प्रकार *r)
{
    माप_प्रकार t;

#अगर (!defined(__INTEL_COMPILER) && AV_GCC_VERSION_AT_LEAST(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    अगर (__builtin_mul_overflow(a, b, &t))
        वापस AVERROR(EINVAL);
#अन्यथा
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    अगर ((a | b) >= ((माप_प्रकार)1 << (माप(माप_प्रकार) * 4)) && a && t / a != b)
        वापस AVERROR(EINVAL);
#पूर्ण_अगर
    *r = t;
    वापस 0;
}

व्योम *av_malloc(माप_प्रकार आकार)
{
    व्योम *ptr = शून्य;

    अगर (आकार > atomic_load_explicit(&max_alloc_आकार, memory_order_relaxed))
        वापस शून्य;

#अगर ASAN_ALIGNED_ALLOC
    अगर (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(आकार);
    अन्यथा
        ptr = _aligned_malloc(आकार, ALIGN);
#या_अगर HAVE_POSIX_MEMALIGN
    अगर (आकार) //OS X on SDK 10.6 has a broken posix_memalign implementation
    अगर (posix_memalign(&ptr, ALIGN, आकार))
        ptr = शून्य;
#या_अगर HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(आकार, ALIGN);
#या_अगर HAVE_MEMALIGN
#अगर_अघोषित __DJGPP__
    ptr = memalign(ALIGN, आकार);
#अन्यथा
    ptr = memalign(आकार, ALIGN);
#पूर्ण_अगर
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
    ptr = दो_स्मृति(आकार);
#पूर्ण_अगर
    अगर(!ptr && !आकार) {
        आकार = 1;
        ptr= av_malloc(1);
    }
    अगर (ptr)
        poison_memory(ptr, आकार);
    वापस ptr;
}

व्योम *av_realloc(व्योम *ptr, माप_प्रकार आकार)
{
    व्योम *ret;
    अगर (आकार > atomic_load_explicit(&max_alloc_आकार, memory_order_relaxed))
        वापस शून्य;

#अगर ASAN_ALIGNED_ALLOC
    अगर (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, आकार + !आकार);
    अन्यथा
        ret = _aligned_realloc(ptr, आकार + !आकार, ALIGN);
#या_अगर HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, आकार + !आकार, ALIGN);
#अन्यथा
    ret = पुनः_स्मृति(ptr, आकार + !आकार);
#पूर्ण_अगर
    अगर (ret && !ptr)
        poison_memory(ret, आकार);
    वापस ret;
}

व्योम *av_realloc_f(व्योम *ptr, माप_प्रकार nelem, माप_प्रकार elsize)
{
    माप_प्रकार आकार;
    व्योम *r;

    अगर (आकार_mult(elsize, nelem, &आकार)) {
        av_free(ptr);
        वापस शून्य;
    }
    r = av_realloc(ptr, आकार);
    अगर (!r)
        av_free(ptr);
    वापस r;
}

पूर्णांक av_reallocp(व्योम *ptr, माप_प्रकार आकार)
{
    व्योम *val;

    अगर (!आकार) {
        av_freep(ptr);
        वापस 0;
    }

    स_नकल(&val, ptr, माप(val));
    val = av_realloc(val, आकार);

    अगर (!val) {
        av_freep(ptr);
        वापस AVERROR(ENOMEM);
    }

    स_नकल(ptr, &val, माप(val));
    वापस 0;
}

व्योम *av_malloc_array(माप_प्रकार nmemb, माप_प्रकार आकार)
{
    माप_प्रकार परिणाम;
    अगर (आकार_mult(nmemb, आकार, &परिणाम) < 0)
        वापस शून्य;
    वापस av_malloc(परिणाम);
}

व्योम *av_realloc_array(व्योम *ptr, माप_प्रकार nmemb, माप_प्रकार आकार)
{
    माप_प्रकार परिणाम;
    अगर (आकार_mult(nmemb, आकार, &परिणाम) < 0)
        वापस शून्य;
    वापस av_realloc(ptr, परिणाम);
}

पूर्णांक av_reallocp_array(व्योम *ptr, माप_प्रकार nmemb, माप_प्रकार आकार)
{
    व्योम *val;

    स_नकल(&val, ptr, माप(val));
    val = av_realloc_f(val, nmemb, आकार);
    स_नकल(ptr, &val, माप(val));
    अगर (!val && nmemb && आकार)
        वापस AVERROR(ENOMEM);

    वापस 0;
}

व्योम av_free(व्योम *ptr)
{
#अगर ASAN_ALIGNED_ALLOC
    अगर (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    अन्यथा
        _aligned_free(ptr);
#या_अगर HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#अन्यथा
    मुक्त(ptr);
#पूर्ण_अगर
}

व्योम av_freep(व्योम *arg)
{
    व्योम *val;

    स_नकल(&val, arg, माप(val));
    स_नकल(arg, &(व्योम *){ शून्य }, माप(val));
    av_free(val);
}

व्योम *av_mallocz(माप_प्रकार आकार)
{
    व्योम *ptr = av_malloc(आकार);
    अगर (ptr)
        स_रखो(ptr, 0, आकार);
    वापस ptr;
}

व्योम *av_calloc(माप_प्रकार nmemb, माप_प्रकार आकार)
{
    माप_प्रकार परिणाम;
    अगर (आकार_mult(nmemb, आकार, &परिणाम) < 0)
        वापस शून्य;
    वापस av_mallocz(परिणाम);
}

अक्षर *av_strdup(स्थिर अक्षर *s)
{
    अक्षर *ptr = शून्य;
    अगर (s) {
        माप_प्रकार len = म_माप(s) + 1;
        ptr = av_realloc(शून्य, len);
        अगर (ptr)
            स_नकल(ptr, s, len);
    }
    वापस ptr;
}

अक्षर *av_strndup(स्थिर अक्षर *s, माप_प्रकार len)
{
    अगर (!s)
        वापस शून्य;

    स्थिर अक्षर *end = स_प्रथम(s, 0, len);
    अगर (end)
        len = end - s;

    अक्षर *ret = av_realloc(शून्य, len + 1);
    अगर (!ret)
        वापस शून्य;

    स_नकल(ret, s, len);
    ret[len] = 0;
    वापस ret;
}

व्योम *av_memdup(स्थिर व्योम *p, माप_प्रकार आकार)
{
    व्योम *ptr = शून्य;
    अगर (p) {
        ptr = av_malloc(आकार);
        अगर (ptr)
            स_नकल(ptr, p, आकार);
    }
    वापस ptr;
}

पूर्णांक av_dynarray_add_nofree(व्योम *tab_ptr, पूर्णांक *nb_ptr, व्योम *elem)
{
    व्योम **tab;
    स_नकल(&tab, tab_ptr, माप(tab));

    FF_DYNARRAY_ADD(पूर्णांक_उच्च, माप(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        स_नकल(tab_ptr, &tab, माप(tab));
    }, {
        वापस AVERROR(ENOMEM);
    });
    वापस 0;
}

व्योम av_dynarray_add(व्योम *tab_ptr, पूर्णांक *nb_ptr, व्योम *elem)
{
    व्योम **tab;
    स_नकल(&tab, tab_ptr, माप(tab));

    FF_DYNARRAY_ADD(पूर्णांक_उच्च, माप(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        स_नकल(tab_ptr, &tab, माप(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

व्योम *av_dynarray2_add(व्योम **tab_ptr, पूर्णांक *nb_ptr, माप_प्रकार elem_आकार,
                       स्थिर uint8_t *elem_तथ्य)
{
    uint8_t *tab_elem_तथ्य = शून्य;

    FF_DYNARRAY_ADD(पूर्णांक_उच्च, elem_आकार, *tab_ptr, *nb_ptr, {
        tab_elem_तथ्य = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_आकार;
        अगर (elem_तथ्य)
            स_नकल(tab_elem_तथ्य, elem_तथ्य, elem_आकार);
        अन्यथा
            poison_memory(tab_elem_तथ्य, elem_आकार);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    वापस tab_elem_तथ्य;
}

अटल व्योम fill16(uint8_t *dst, पूर्णांक len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    जबतक (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    जबतक (len--) {
        *dst = dst[-2];
        dst++;
    }
}

अटल व्योम fill24(uint8_t *dst, पूर्णांक len)
{
#अगर HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#अन्यथा
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#पूर्ण_अगर

    जबतक (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    अगर (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    अगर (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    जबतक (len--) {
        *dst = dst[-3];
        dst++;
    }
}

अटल व्योम fill32(uint8_t *dst, पूर्णांक len)
{
    uint32_t v = AV_RN32(dst - 4);

#अगर HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    जबतक (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#पूर्ण_अगर

    जबतक (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    जबतक (len--) {
        *dst = dst[-4];
        dst++;
    }
}

व्योम av_memcpy_backptr(uint8_t *dst, पूर्णांक back, पूर्णांक cnt)
{
    स्थिर uint8_t *src = &dst[-back];
    अगर (!back)
        वापस;

    अगर (back == 1) {
        स_रखो(dst, *src, cnt);
    } अन्यथा अगर (back == 2) {
        fill16(dst, cnt);
    } अन्यथा अगर (back == 3) {
        fill24(dst, cnt);
    } अन्यथा अगर (back == 4) {
        fill32(dst, cnt);
    } अन्यथा {
        अगर (cnt >= 16) {
            पूर्णांक blocklen = back;
            जबतक (cnt > blocklen) {
                स_नकल(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            स_नकल(dst, src, cnt);
            वापस;
        }
        अगर (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        अगर (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        अगर (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        अगर (cnt)
            *dst = *src;
    }
}

व्योम *av_fast_realloc(व्योम *ptr, अचिन्हित पूर्णांक *आकार, माप_प्रकार min_आकार)
{
    माप_प्रकार max_आकार;

    अगर (min_आकार <= *आकार)
        वापस ptr;

    max_आकार = atomic_load_explicit(&max_alloc_आकार, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_आकार = FFMIN(max_आकार, अच_पूर्णांक_उच्च);

    अगर (min_आकार > max_आकार) {
        *आकार = 0;
        वापस शून्य;
    }

    min_आकार = FFMIN(max_आकार, FFMAX(min_आकार + min_आकार / 16 + 32, min_आकार));

    ptr = av_realloc(ptr, min_आकार);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    अगर (!ptr)
        min_आकार = 0;

    *आकार = min_आकार;

    वापस ptr;
}

अटल अंतरभूत व्योम fast_malloc(व्योम *ptr, अचिन्हित पूर्णांक *आकार, माप_प्रकार min_आकार, पूर्णांक zero_realloc)
{
    माप_प्रकार max_आकार;
    व्योम *val;

    स_नकल(&val, ptr, माप(val));
    अगर (min_आकार <= *आकार) {
        av_assert0(val || !min_आकार);
        वापस;
    }

    max_आकार = atomic_load_explicit(&max_alloc_आकार, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_आकार = FFMIN(max_आकार, अच_पूर्णांक_उच्च);

    अगर (min_आकार > max_आकार) {
        av_freep(ptr);
        *आकार = 0;
        वापस;
    }
    min_आकार = FFMIN(max_आकार, FFMAX(min_आकार + min_आकार / 16 + 32, min_आकार));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_आकार) : av_malloc(min_आकार);
    स_नकल(ptr, &val, माप(val));
    अगर (!val)
        min_आकार = 0;
    *आकार = min_आकार;
    वापस;
}

व्योम av_fast_malloc(व्योम *ptr, अचिन्हित पूर्णांक *आकार, माप_प्रकार min_आकार)
{
    fast_malloc(ptr, आकार, min_आकार, 0);
}

व्योम av_fast_mallocz(व्योम *ptr, अचिन्हित पूर्णांक *आकार, माप_प्रकार min_आकार)
{
    fast_malloc(ptr, आकार, min_आकार, 1);
}

पूर्णांक av_आकार_mult(माप_प्रकार a, माप_प्रकार b, माप_प्रकार *r)
{
    वापस आकार_mult(a, b, r);
}

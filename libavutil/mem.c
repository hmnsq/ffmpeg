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

#परिभाषय _XOPEN_SOURCE 600

#अन्तर्भाव "config.h"

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <stdlib.h>
#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव <string.h>
#यदि HAVE_MALLOC_H
#अन्तर्भाव <malloc.h>
#यदि_अन्तः

#अन्तर्भाव "attributes.h"
#अन्तर्भाव "avassert.h"
#अन्तर्भाव "dynarray.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "internal.h"
#अन्तर्भाव "intreadwrite.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "sanitizer.h"

#यदि_परिभाषितम् MALLOC_उपसर्गः

#परिभाषय स्मृतिं_देहि         AV_JOIN(MALLOC_उपसर्गः, स्मृतिं_देहि)
#परिभाषय memalign       AV_JOIN(MALLOC_उपसर्गः, memalign)
#परिभाषय posix_memalign AV_JOIN(MALLOC_उपसर्गः, posix_memalign)
#परिभाषय realloc        AV_JOIN(MALLOC_उपसर्गः, realloc)
#परिभाषय मुक्त           AV_JOIN(MALLOC_उपसर्गः, मुक्त)

शून्य *स्मृतिं_देहि(size_t आकार);
शून्य *memalign(size_t align, size_t आकार);
पूर्णाङ्क   posix_memalign(शून्य **ptr, size_t align, size_t आकार);
शून्य *realloc(शून्य *ptr, size_t आकार);
शून्य  मुक्त(शून्य *ptr);

#यदि_अन्तः /* MALLOC_PREFIX */

#परिभाषय ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#परिभाषय FF_स्मृतिः_POISON 0x2a

स्थिर शून्य poison_स्मृतिः(शून्य *ptr, size_t आकार)
{
#यदि CONFIG_स्मृतिः_POISONING
    स्मृतिं_पूरय(ptr, FF_स्मृतिः_POISON, आकार);
#यदि_अन्तः
    FF_MEM_UNDEFINED(ptr, आकार);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#यदि HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#परिभाषय ASAN_ALIGNED_ALLOC 1

स्थिर पूर्णाङ्क asan_aligned_alloc_needed(शून्य)
{
    स्थिर atomic_int needed = -1;
    पूर्णाङ्क ret = atomic_load_explicit(&needed, memory_order_relaxed);

    यदि (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        पूर्णाङ्क probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        यदि (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    प्रत्यागम ret;
}

प्रकारनिर्देश संरचना Asan_Aligned_शीर्षकम् {
    शून्य  *आधारः_2;
    size_t आकार;
} Asan_Aligned_शीर्षकम्;

स्थिर शून्य *asan_aligned_malloc(size_t आकार)
{
    Asan_Aligned_शीर्षकम् *hdr;
    uint8_t *आधारः_2, *ptr;
    size_t योग_2;

    यदि (आकार > SIZE_MAX - ALIGN - परिमाण(*hdr))
        प्रत्यागम रिक्त;
    योग_2 = आकार + ALIGN + परिमाण(*hdr);
    आधारः_2  = स्मृतिं_देहि(योग_2);
    यदि (!आधारः_2)
        प्रत्यागम रिक्त;
    ptr = (uint8_t *)FFALIGN((uintptr_t)आधारः_2 + परिमाण(*hdr), ALIGN);
    hdr = (Asan_Aligned_शीर्षकम् *)ptr - 1;
    hdr->आधारः_2 = आधारः_2;
    hdr->आकार = आकार;
    FF_ASAN_POISON(आधारः_2, ptr - आधारः_2);
    FF_ASAN_POISON(ptr + आकार, आधारः_2 + योग_2 - (ptr + आकार));
    प्रत्यागम ptr;
}

स्थिर Asan_Aligned_शीर्षकम् *asan_aligned_शीर्षकम्(शून्य *ptr)
{
    Asan_Aligned_शीर्षकम् *hdr = (Asan_Aligned_शीर्षकम् *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, परिमाण(*hdr));
    प्रत्यागम hdr;
}

स्थिर शून्य asan_aligned_free(शून्य *ptr)
{
    यदि (ptr)
        मुक्त(asan_aligned_शीर्षकम्(ptr)->आधारः_2);
}

स्थिर शून्य *asan_aligned_realloc(शून्य *ptr, size_t आकार)
{
    Asan_Aligned_शीर्षकम् *hdr;
    शून्य *ret;

    यदि (!ptr)
        प्रत्यागम asan_aligned_malloc(आकार);
    ret = asan_aligned_malloc(आकार);
    यदि (!ret)
        प्रत्यागम रिक्त;
    hdr = asan_aligned_शीर्षकम्(ptr);
    स्मृतिं_प्रतिलिख(ret, ptr, FFMIN(आकार, hdr->आकार));
    मुक्त(hdr->आधारः_2);
    प्रत्यागम ret;
}
#अन्यथा
#परिभाषय ASAN_ALIGNED_ALLOC 0
#यदि_अन्तः

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

स्थिर atomic_size_t max_alloc_आकार = अधिकतम_पूर्णाङ्कः;

शून्य av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_आकार, max, memory_order_relaxed);
}

स्थिर पूर्णाङ्क आकार_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#यदि (!defined(__INTEL_COMPILER) && AV_GCC_संस्करणम्_AT_न्यूनतमम्(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    यदि (__builtin_mul_overflow(a, b, &t))
        प्रत्यागम AVERROR(EINVAL);
#अन्यथा
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    यदि ((a | b) >= ((size_t)1 << (परिमाण(size_t) * 4)) && a && t / a != b)
        प्रत्यागम AVERROR(EINVAL);
#यदि_अन्तः
    *r = t;
    प्रत्यागम 0;
}

शून्य *av_malloc(size_t आकार)
{
    शून्य *ptr = रिक्त;

    यदि (आकार > atomic_load_explicit(&max_alloc_आकार, memory_order_relaxed))
        प्रत्यागम रिक्त;

#यदि ASAN_ALIGNED_ALLOC
    यदि (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(आकार);
    अन्यथा
        ptr = _aligned_malloc(आकार, ALIGN);
#नोचेद्यदि HAVE_POSIX_MEMALIGN
    यदि (आकार) //OS X on SDK 10.6 has a broken posix_memalign implementation
    यदि (posix_memalign(&ptr, ALIGN, आकार))
        ptr = रिक्त;
#नोचेद्यदि HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(आकार, ALIGN);
#नोचेद्यदि HAVE_MEMALIGN
#यदि_अपरिभाषितम् __DJGPP__
    ptr = memalign(ALIGN, आकार);
#अन्यथा
    ptr = memalign(आकार, ALIGN);
#यदि_अन्तः
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
    ptr = स्मृतिं_देहि(आकार);
#यदि_अन्तः
    यदि(!ptr && !आकार) {
        आकार = 1;
        ptr= av_malloc(1);
    }
    यदि (ptr)
        poison_स्मृतिः(ptr, आकार);
    प्रत्यागम ptr;
}

शून्य *av_realloc(शून्य *ptr, size_t आकार)
{
    शून्य *ret;
    यदि (आकार > atomic_load_explicit(&max_alloc_आकार, memory_order_relaxed))
        प्रत्यागम रिक्त;

#यदि ASAN_ALIGNED_ALLOC
    यदि (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, आकार + !आकार);
    अन्यथा
        ret = _aligned_realloc(ptr, आकार + !आकार, ALIGN);
#नोचेद्यदि HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, आकार + !आकार, ALIGN);
#अन्यथा
    ret = realloc(ptr, आकार + !आकार);
#यदि_अन्तः
    यदि (ret && !ptr)
        poison_स्मृतिः(ret, आकार);
    प्रत्यागम ret;
}

शून्य *av_realloc_f(शून्य *ptr, size_t nelem, size_t elsize)
{
    size_t आकार;
    शून्य *r;

    यदि (आकार_mult(elsize, nelem, &आकार)) {
        av_free(ptr);
        प्रत्यागम रिक्त;
    }
    r = av_realloc(ptr, आकार);
    यदि (!r)
        av_free(ptr);
    प्रत्यागम r;
}

पूर्णाङ्क av_reallocp(शून्य *ptr, size_t आकार)
{
    शून्य *val;

    यदि (!आकार) {
        av_freep(ptr);
        प्रत्यागम 0;
    }

    स्मृतिं_प्रतिलिख(&val, ptr, परिमाण(val));
    val = av_realloc(val, आकार);

    यदि (!val) {
        av_freep(ptr);
        प्रत्यागम AVERROR(ENOMEM);
    }

    स्मृतिं_प्रतिलिख(ptr, &val, परिमाण(val));
    प्रत्यागम 0;
}

शून्य *av_malloc_array(size_t nmemb, size_t आकार)
{
    size_t परिणाम;
    यदि (आकार_mult(nmemb, आकार, &परिणाम) < 0)
        प्रत्यागम रिक्त;
    प्रत्यागम av_malloc(परिणाम);
}

शून्य *av_realloc_array(शून्य *ptr, size_t nmemb, size_t आकार)
{
    size_t परिणाम;
    यदि (आकार_mult(nmemb, आकार, &परिणाम) < 0)
        प्रत्यागम रिक्त;
    प्रत्यागम av_realloc(ptr, परिणाम);
}

पूर्णाङ्क av_reallocp_array(शून्य *ptr, size_t nmemb, size_t आकार)
{
    शून्य *val;

    स्मृतिं_प्रतिलिख(&val, ptr, परिमाण(val));
    val = av_realloc_f(val, nmemb, आकार);
    स्मृतिं_प्रतिलिख(ptr, &val, परिमाण(val));
    यदि (!val && nmemb && आकार)
        प्रत्यागम AVERROR(ENOMEM);

    प्रत्यागम 0;
}

शून्य av_free(शून्य *ptr)
{
#यदि ASAN_ALIGNED_ALLOC
    यदि (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    अन्यथा
        _aligned_free(ptr);
#नोचेद्यदि HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#अन्यथा
    मुक्त(ptr);
#यदि_अन्तः
}

शून्य av_freep(शून्य *arg)
{
    शून्य *val;

    स्मृतिं_प्रतिलिख(&val, arg, परिमाण(val));
    स्मृतिं_प्रतिलिख(arg, &(शून्य *){ रिक्त }, परिमाण(val));
    av_free(val);
}

शून्य *av_mallocz(size_t आकार)
{
    शून्य *ptr = av_malloc(आकार);
    यदि (ptr)
        स्मृतिं_पूरय(ptr, 0, आकार);
    प्रत्यागम ptr;
}

शून्य *av_calloc(size_t nmemb, size_t आकार)
{
    size_t परिणाम;
    यदि (आकार_mult(nmemb, आकार, &परिणाम) < 0)
        प्रत्यागम रिक्त;
    प्रत्यागम av_mallocz(परिणाम);
}

वर्ण *av_strdup(ध्रुव वर्ण *s)
{
    वर्ण *ptr = रिक्त;
    यदि (s) {
        size_t len = वाक्यदैर्घ्यम्(s) + 1;
        ptr = av_realloc(रिक्त, len);
        यदि (ptr)
            स्मृतिं_प्रतिलिख(ptr, s, len);
    }
    प्रत्यागम ptr;
}

वर्ण *av_strndup(ध्रुव वर्ण *s, size_t len)
{
    यदि (!s)
        प्रत्यागम रिक्त;

    ध्रुव वर्ण *अन्तः_2 = memchr(s, 0, len);
    यदि (अन्तः_2)
        len = अन्तः_2 - s;

    वर्ण *ret = av_realloc(रिक्त, len + 1);
    यदि (!ret)
        प्रत्यागम रिक्त;

    स्मृतिं_प्रतिलिख(ret, s, len);
    ret[len] = 0;
    प्रत्यागम ret;
}

शून्य *av_memdup(ध्रुव शून्य *p, size_t आकार)
{
    शून्य *ptr = रिक्त;
    यदि (p) {
        ptr = av_malloc(आकार);
        यदि (ptr)
            स्मृतिं_प्रतिलिख(ptr, p, आकार);
    }
    प्रत्यागम ptr;
}

पूर्णाङ्क av_dynarray_सङ्कलय_nofree(शून्य *tab_ptr, पूर्णाङ्क *nb_ptr, शून्य *elem)
{
    शून्य **tab;
    स्मृतिं_प्रतिलिख(&tab, tab_ptr, परिमाण(tab));

    FF_DYNARRAY_सङ्कलय(अधिकतम_पूर्णाङ्कः, परिमाण(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        स्मृतिं_प्रतिलिख(tab_ptr, &tab, परिमाण(tab));
    }, {
        प्रत्यागम AVERROR(ENOMEM);
    });
    प्रत्यागम 0;
}

शून्य av_dynarray_सङ्कलय(शून्य *tab_ptr, पूर्णाङ्क *nb_ptr, शून्य *elem)
{
    शून्य **tab;
    स्मृतिं_प्रतिलिख(&tab, tab_ptr, परिमाण(tab));

    FF_DYNARRAY_सङ्कलय(अधिकतम_पूर्णाङ्कः, परिमाण(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        स्मृतिं_प्रतिलिख(tab_ptr, &tab, परिमाण(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

शून्य *av_dynarray2_सङ्कलय(शून्य **tab_ptr, पूर्णाङ्क *nb_ptr, size_t elem_आकार,
                       ध्रुव uint8_t *elem_दत्त)
{
    uint8_t *tab_elem_दत्त = रिक्त;

    FF_DYNARRAY_सङ्कलय(अधिकतम_पूर्णाङ्कः, elem_आकार, *tab_ptr, *nb_ptr, {
        tab_elem_दत्त = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_आकार;
        यदि (elem_दत्त)
            स्मृतिं_प्रतिलिख(tab_elem_दत्त, elem_दत्त, elem_आकार);
        अन्यथा
            poison_स्मृतिः(tab_elem_दत्त, elem_आकार);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    प्रत्यागम tab_elem_दत्त;
}

स्थिर शून्य fill16(uint8_t *dst, पूर्णाङ्क len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    यावत् (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    यावत् (len--) {
        *dst = dst[-2];
        dst++;
    }
}

स्थिर शून्य fill24(uint8_t *dst, पूर्णाङ्क len)
{
#यदि HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#अन्यथा
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#यदि_अन्तः

    यावत् (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    यदि (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    यदि (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    यावत् (len--) {
        *dst = dst[-3];
        dst++;
    }
}

स्थिर शून्य fill32(uint8_t *dst, पूर्णाङ्क len)
{
    uint32_t v = AV_RN32(dst - 4);

#यदि HAVE_FAST_64BIT
    uint64_t v2= v + ((uint64_t)v<<32);
    यावत् (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#यदि_अन्तः

    यावत् (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    यावत् (len--) {
        *dst = dst[-4];
        dst++;
    }
}

शून्य av_memcpy_backptr(uint8_t *dst, पूर्णाङ्क पृष्ठभागः, पूर्णाङ्क cnt)
{
    ध्रुव uint8_t *src = &dst[-पृष्ठभागः];
    यदि (!पृष्ठभागः)
        प्रत्यागम;

    यदि (पृष्ठभागः == 1) {
        स्मृतिं_पूरय(dst, *src, cnt);
    } अन्यथा यदि (पृष्ठभागः == 2) {
        fill16(dst, cnt);
    } अन्यथा यदि (पृष्ठभागः == 3) {
        fill24(dst, cnt);
    } अन्यथा यदि (पृष्ठभागः == 4) {
        fill32(dst, cnt);
    } अन्यथा {
        यदि (cnt >= 16) {
            पूर्णाङ्क blocklen = पृष्ठभागः;
            यावत् (cnt > blocklen) {
                स्मृतिं_प्रतिलिख(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            स्मृतिं_प्रतिलिख(dst, src, cnt);
            प्रत्यागम;
        }
        यदि (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        यदि (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        यदि (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        यदि (cnt)
            *dst = *src;
    }
}

शून्य *av_fast_realloc(शून्य *ptr, अचिह्नित पूर्णाङ्क *आकार, size_t min_आकार)
{
    size_t max_आकार;

    यदि (min_आकार <= *आकार)
        प्रत्यागम ptr;

    max_आकार = atomic_load_explicit(&max_alloc_आकार, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_आकार = FFMIN(max_आकार, UINT_MAX);

    यदि (min_आकार > max_आकार) {
        *आकार = 0;
        प्रत्यागम रिक्त;
    }

    min_आकार = FFMIN(max_आकार, FFMAX(min_आकार + min_आकार / 16 + 32, min_आकार));

    ptr = av_realloc(ptr, min_आकार);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    यदि (!ptr)
        min_आकार = 0;

    *आकार = min_आकार;

    प्रत्यागम ptr;
}

स्थिर अन्तःस्थ शून्य fast_malloc(शून्य *ptr, अचिह्नित पूर्णाङ्क *आकार, size_t min_आकार, पूर्णाङ्क zero_realloc)
{
    size_t max_आकार;
    शून्य *val;

    स्मृतिं_प्रतिलिख(&val, ptr, परिमाण(val));
    यदि (min_आकार <= *आकार) {
        av_assert0(val || !min_आकार);
        प्रत्यागम;
    }

    max_आकार = atomic_load_explicit(&max_alloc_आकार, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_आकार = FFMIN(max_आकार, UINT_MAX);

    यदि (min_आकार > max_आकार) {
        av_freep(ptr);
        *आकार = 0;
        प्रत्यागम;
    }
    min_आकार = FFMIN(max_आकार, FFMAX(min_आकार + min_आकार / 16 + 32, min_आकार));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_आकार) : av_malloc(min_आकार);
    स्मृतिं_प्रतिलिख(ptr, &val, परिमाण(val));
    यदि (!val)
        min_आकार = 0;
    *आकार = min_आकार;
    प्रत्यागम;
}

शून्य av_fast_malloc(शून्य *ptr, अचिह्नित पूर्णाङ्क *आकार, size_t min_आकार)
{
    fast_malloc(ptr, आकार, min_आकार, 0);
}

शून्य av_fast_mallocz(शून्य *ptr, अचिह्नित पूर्णाङ्क *आकार, size_t min_आकार)
{
    fast_malloc(ptr, आकार, min_आकार, 1);
}

पूर्णाङ्क av_आकार_mult(size_t a, size_t b, size_t *r)
{
    प्रत्यागम आकार_mult(a, b, r);
}

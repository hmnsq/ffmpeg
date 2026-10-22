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

#నిర్వచించు XOPEN_ఆధారం 600

#అన్తర్భావ "config.h"

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <stdlib.h>
#అన్తర్భావ <stdatomic.h>
#అన్తర్భావ <string.h>
#ఒకవేళ HAVE_MALLOC_H
#అన్తర్భావ <malloc.h>
#అయితే_ముగింపు

#అన్తర్భావ "attributes.h"
#అన్తర్భావ "avassert.h"
#అన్తర్భావ "dynarray.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "internal.h"
#అన్తర్భావ "intreadwrite.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "sanitizer.h"

#నిర్వచితమైతే MALLOC_ఉపసర్గ

#నిర్వచించు జ్ఞాపకం_ఇవ్వు         AV_JOIN(MALLOC_ఉపసర్గ, జ్ఞాపకం_ఇవ్వు)
#నిర్వచించు memalign       AV_JOIN(MALLOC_ఉపసర్గ, memalign)
#నిర్వచించు posix_memalign AV_JOIN(MALLOC_ఉపసర్గ, posix_memalign)
#నిర్వచించు realloc        AV_JOIN(MALLOC_ఉపసర్గ, realloc)
#నిర్వచించు విడుదల           AV_JOIN(MALLOC_ఉపసర్గ, విడుదల)

శూన్య *జ్ఞాపకం_ఇవ్వు(size_t కొలత);
శూన్య *memalign(size_t align, size_t కొలత);
పూర్ణాంకం   posix_memalign(శూన్య **ptr, size_t align, size_t కొలత);
శూన్య *realloc(శూన్య *ptr, size_t కొలత);
శూన్య  విడుదల(శూన్య *ptr);

#అయితే_ముగింపు /* MALLOC_PREFIX */

#నిర్వచించు ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#నిర్వచించు FF_జ్ఞాపకం_POISON 0x2a

స్థిర శూన్య poison_జ్ఞాపకం(శూన్య *ptr, size_t కొలత)
{
#ఒకవేళ CONFIG_జ్ఞాపకం_POISONING
    memset(ptr, FF_జ్ఞాపకం_POISON, కొలత);
#అయితే_ముగింపు
    FF_MEM_UNDEFINED(ptr, కొలత);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#ఒకవేళ HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#నిర్వచించు ASAN_ALIGNED_ALLOC 1

స్థిర పూర్ణాంకం asan_aligned_alloc_needed(శూన్య)
{
    స్థిర atomic_int needed = -1;
    పూర్ణాంకం ret = atomic_load_explicit(&needed, memory_order_relaxed);

    ఒకవేళ (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        పూర్ణాంకం probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        ఒకవేళ (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    తిరిగి ret;
}

రకనిర్వచనం నిర్మాణం Asan_Aligned_శీర్షిక {
    శూన్య  *పునాది_2;
    size_t కొలత;
} Asan_Aligned_శీర్షిక;

స్థిర శూన్య *asan_aligned_malloc(size_t కొలత)
{
    Asan_Aligned_శీర్షిక *hdr;
    uint8_t *పునాది_2, *ptr;
    size_t మొత్తం;

    ఒకవేళ (కొలత > SIZE_MAX - ALIGN - పరిమాణం(*hdr))
        తిరిగి ఖాళీ;
    మొత్తం = కొలత + ALIGN + పరిమాణం(*hdr);
    పునాది_2  = జ్ఞాపకం_ఇవ్వు(మొత్తం);
    ఒకవేళ (!పునాది_2)
        తిరిగి ఖాళీ;
    ptr = (uint8_t *)FFALIGN((uintptr_t)పునాది_2 + పరిమాణం(*hdr), ALIGN);
    hdr = (Asan_Aligned_శీర్షిక *)ptr - 1;
    hdr->పునాది_2 = పునాది_2;
    hdr->కొలత = కొలత;
    FF_ASAN_POISON(పునాది_2, ptr - పునాది_2);
    FF_ASAN_POISON(ptr + కొలత, పునాది_2 + మొత్తం - (ptr + కొలత));
    తిరిగి ptr;
}

స్థిర Asan_Aligned_శీర్షిక *asan_aligned_శీర్షిక(శూన్య *ptr)
{
    Asan_Aligned_శీర్షిక *hdr = (Asan_Aligned_శీర్షిక *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, పరిమాణం(*hdr));
    తిరిగి hdr;
}

స్థిర శూన్య asan_aligned_free(శూన్య *ptr)
{
    ఒకవేళ (ptr)
        విడుదల(asan_aligned_శీర్షిక(ptr)->పునాది_2);
}

స్థిర శూన్య *asan_aligned_realloc(శూన్య *ptr, size_t కొలత)
{
    Asan_Aligned_శీర్షిక *hdr;
    శూన్య *ret;

    ఒకవేళ (!ptr)
        తిరిగి asan_aligned_malloc(కొలత);
    ret = asan_aligned_malloc(కొలత);
    ఒకవేళ (!ret)
        తిరిగి ఖాళీ;
    hdr = asan_aligned_శీర్షిక(ptr);
    జ్ఞాపకం_నకలు(ret, ptr, FFMIN(కొలత, hdr->కొలత));
    విడుదల(hdr->పునాది_2);
    తిరిగి ret;
}
#లేకపోతే
#నిర్వచించు ASAN_ALIGNED_ALLOC 0
#అయితే_ముగింపు

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

స్థిర atomic_size_t max_alloc_కొలత = గరిష్ఠ_పూర్ణాంకం;

శూన్య av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_కొలత, max, memory_order_relaxed);
}

స్థిర పూర్ణాంకం కొలత_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#ఒకవేళ (!defined(__INTEL_COMPILER) && AV_GCC_సంస్కరణ_AT_కనిష్ఠ(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    ఒకవేళ (__builtin_mul_overflow(a, b, &t))
        తిరిగి AVERROR(EINVAL);
#లేకపోతే
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    ఒకవేళ ((a | b) >= ((size_t)1 << (పరిమాణం(size_t) * 4)) && a && t / a != b)
        తిరిగి AVERROR(EINVAL);
#అయితే_ముగింపు
    *r = t;
    తిరిగి 0;
}

శూన్య *av_malloc(size_t కొలత)
{
    శూన్య *ptr = ఖాళీ;

    ఒకవేళ (కొలత > atomic_load_explicit(&max_alloc_కొలత, memory_order_relaxed))
        తిరిగి ఖాళీ;

#ఒకవేళ ASAN_ALIGNED_ALLOC
    ఒకవేళ (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(కొలత);
    లేకపోతే
        ptr = _aligned_malloc(కొలత, ALIGN);
#లేదావేళ HAVE_POSIX_MEMALIGN
    ఒకవేళ (కొలత) //OS X on SDK 10.6 has a broken posix_memalign implementation
    ఒకవేళ (posix_memalign(&ptr, ALIGN, కొలత))
        ptr = ఖాళీ;
#లేదావేళ HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(కొలత, ALIGN);
#లేదావేళ HAVE_MEMALIGN
#నిర్వచితం_కాకపోతే __DJGPP__
    ptr = memalign(ALIGN, కొలత);
#లేకపోతే
    ptr = memalign(కొలత, ALIGN);
#అయితే_ముగింపు
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
#లేకపోతే
    ptr = జ్ఞాపకం_ఇవ్వు(కొలత);
#అయితే_ముగింపు
    ఒకవేళ(!ptr && !కొలత) {
        కొలత = 1;
        ptr= av_malloc(1);
    }
    ఒకవేళ (ptr)
        poison_జ్ఞాపకం(ptr, కొలత);
    తిరిగి ptr;
}

శూన్య *av_realloc(శూన్య *ptr, size_t కొలత)
{
    శూన్య *ret;
    ఒకవేళ (కొలత > atomic_load_explicit(&max_alloc_కొలత, memory_order_relaxed))
        తిరిగి ఖాళీ;

#ఒకవేళ ASAN_ALIGNED_ALLOC
    ఒకవేళ (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, కొలత + !కొలత);
    లేకపోతే
        ret = _aligned_realloc(ptr, కొలత + !కొలత, ALIGN);
#లేదావేళ HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, కొలత + !కొలత, ALIGN);
#లేకపోతే
    ret = realloc(ptr, కొలత + !కొలత);
#అయితే_ముగింపు
    ఒకవేళ (ret && !ptr)
        poison_జ్ఞాపకం(ret, కొలత);
    తిరిగి ret;
}

శూన్య *av_realloc_f(శూన్య *ptr, size_t nelem, size_t elsize)
{
    size_t కొలత;
    శూన్య *r;

    ఒకవేళ (కొలత_mult(elsize, nelem, &కొలత)) {
        av_free(ptr);
        తిరిగి ఖాళీ;
    }
    r = av_realloc(ptr, కొలత);
    ఒకవేళ (!r)
        av_free(ptr);
    తిరిగి r;
}

పూర్ణాంకం av_reallocp(శూన్య *ptr, size_t కొలత)
{
    శూన్య *val;

    ఒకవేళ (!కొలత) {
        av_freep(ptr);
        తిరిగి 0;
    }

    జ్ఞాపకం_నకలు(&val, ptr, పరిమాణం(val));
    val = av_realloc(val, కొలత);

    ఒకవేళ (!val) {
        av_freep(ptr);
        తిరిగి AVERROR(ENOMEM);
    }

    జ్ఞాపకం_నకలు(ptr, &val, పరిమాణం(val));
    తిరిగి 0;
}

శూన్య *av_malloc_array(size_t nmemb, size_t కొలత)
{
    size_t ఫలితం;
    ఒకవేళ (కొలత_mult(nmemb, కొలత, &ఫలితం) < 0)
        తిరిగి ఖాళీ;
    తిరిగి av_malloc(ఫలితం);
}

శూన్య *av_realloc_array(శూన్య *ptr, size_t nmemb, size_t కొలత)
{
    size_t ఫలితం;
    ఒకవేళ (కొలత_mult(nmemb, కొలత, &ఫలితం) < 0)
        తిరిగి ఖాళీ;
    తిరిగి av_realloc(ptr, ఫలితం);
}

పూర్ణాంకం av_reallocp_array(శూన్య *ptr, size_t nmemb, size_t కొలత)
{
    శూన్య *val;

    జ్ఞాపకం_నకలు(&val, ptr, పరిమాణం(val));
    val = av_realloc_f(val, nmemb, కొలత);
    జ్ఞాపకం_నకలు(ptr, &val, పరిమాణం(val));
    ఒకవేళ (!val && nmemb && కొలత)
        తిరిగి AVERROR(ENOMEM);

    తిరిగి 0;
}

శూన్య av_free(శూన్య *ptr)
{
#ఒకవేళ ASAN_ALIGNED_ALLOC
    ఒకవేళ (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    లేకపోతే
        _aligned_free(ptr);
#లేదావేళ HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#లేకపోతే
    విడుదల(ptr);
#అయితే_ముగింపు
}

శూన్య av_freep(శూన్య *arg)
{
    శూన్య *val;

    జ్ఞాపకం_నకలు(&val, arg, పరిమాణం(val));
    జ్ఞాపకం_నకలు(arg, &(శూన్య *){ ఖాళీ }, పరిమాణం(val));
    av_free(val);
}

శూన్య *av_mallocz(size_t కొలత)
{
    శూన్య *ptr = av_malloc(కొలత);
    ఒకవేళ (ptr)
        memset(ptr, 0, కొలత);
    తిరిగి ptr;
}

శూన్య *av_calloc(size_t nmemb, size_t కొలత)
{
    size_t ఫలితం;
    ఒకవేళ (కొలత_mult(nmemb, కొలత, &ఫలితం) < 0)
        తిరిగి ఖాళీ;
    తిరిగి av_mallocz(ఫలితం);
}

అక్షరం *av_strdup(స్థిరరాశి అక్షరం *s)
{
    అక్షరం *ptr = ఖాళీ;
    ఒకవేళ (s) {
        size_t len = అక్షరశ్రేణి_పొడవు(s) + 1;
        ptr = av_realloc(ఖాళీ, len);
        ఒకవేళ (ptr)
            జ్ఞాపకం_నకలు(ptr, s, len);
    }
    తిరిగి ptr;
}

అక్షరం *av_strndup(స్థిరరాశి అక్షరం *s, size_t len)
{
    ఒకవేళ (!s)
        తిరిగి ఖాళీ;

    స్థిరరాశి అక్షరం *చివర = memchr(s, 0, len);
    ఒకవేళ (చివర)
        len = చివర - s;

    అక్షరం *ret = av_realloc(ఖాళీ, len + 1);
    ఒకవేళ (!ret)
        తిరిగి ఖాళీ;

    జ్ఞాపకం_నకలు(ret, s, len);
    ret[len] = 0;
    తిరిగి ret;
}

శూన్య *av_memdup(స్థిరరాశి శూన్య *p, size_t కొలత)
{
    శూన్య *ptr = ఖాళీ;
    ఒకవేళ (p) {
        ptr = av_malloc(కొలత);
        ఒకవేళ (ptr)
            జ్ఞాపకం_నకలు(ptr, p, కొలత);
    }
    తిరిగి ptr;
}

పూర్ణాంకం av_dynarray_కూడు_nofree(శూన్య *tab_ptr, పూర్ణాంకం *nb_ptr, శూన్య *elem)
{
    శూన్య **tab;
    జ్ఞాపకం_నకలు(&tab, tab_ptr, పరిమాణం(tab));

    FF_DYNARRAY_కూడు(గరిష్ఠ_పూర్ణాంకం, పరిమాణం(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        జ్ఞాపకం_నకలు(tab_ptr, &tab, పరిమాణం(tab));
    }, {
        తిరిగి AVERROR(ENOMEM);
    });
    తిరిగి 0;
}

శూన్య av_dynarray_కూడు(శూన్య *tab_ptr, పూర్ణాంకం *nb_ptr, శూన్య *elem)
{
    శూన్య **tab;
    జ్ఞాపకం_నకలు(&tab, tab_ptr, పరిమాణం(tab));

    FF_DYNARRAY_కూడు(గరిష్ఠ_పూర్ణాంకం, పరిమాణం(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        జ్ఞాపకం_నకలు(tab_ptr, &tab, పరిమాణం(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

శూన్య *av_dynarray2_కూడు(శూన్య **tab_ptr, పూర్ణాంకం *nb_ptr, size_t elem_కొలత,
                       స్థిరరాశి uint8_t *elem_దత్తాంశం)
{
    uint8_t *tab_elem_దత్తాంశం = ఖాళీ;

    FF_DYNARRAY_కూడు(గరిష్ఠ_పూర్ణాంకం, elem_కొలత, *tab_ptr, *nb_ptr, {
        tab_elem_దత్తాంశం = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_కొలత;
        ఒకవేళ (elem_దత్తాంశం)
            జ్ఞాపకం_నకలు(tab_elem_దత్తాంశం, elem_దత్తాంశం, elem_కొలత);
        లేకపోతే
            poison_జ్ఞాపకం(tab_elem_దత్తాంశం, elem_కొలత);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    తిరిగి tab_elem_దత్తాంశం;
}

స్థిర శూన్య fill16(uint8_t *dst, పూర్ణాంకం len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    అయితే (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    అయితే (len--) {
        *dst = dst[-2];
        dst++;
    }
}

స్థిర శూన్య fill24(uint8_t *dst, పూర్ణాంకం len)
{
#ఒకవేళ HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#లేకపోతే
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#అయితే_ముగింపు

    అయితే (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    ఒకవేళ (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    ఒకవేళ (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    అయితే (len--) {
        *dst = dst[-3];
        dst++;
    }
}

స్థిర శూన్య fill32(uint8_t *dst, పూర్ణాంకం len)
{
    uint32_t v = AV_RN32(dst - 4);

#ఒకవేళ HAVE_FAST_64_బిట్టు
    uint64_t v2= v + ((uint64_t)v<<32);
    అయితే (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#అయితే_ముగింపు

    అయితే (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    అయితే (len--) {
        *dst = dst[-4];
        dst++;
    }
}

శూన్య av_memcpy_backptr(uint8_t *dst, పూర్ణాంకం వెనుక, పూర్ణాంకం cnt)
{
    స్థిరరాశి uint8_t *src = &dst[-వెనుక];
    ఒకవేళ (!వెనుక)
        తిరిగి;

    ఒకవేళ (వెనుక == 1) {
        memset(dst, *src, cnt);
    } లేకపోతే ఒకవేళ (వెనుక == 2) {
        fill16(dst, cnt);
    } లేకపోతే ఒకవేళ (వెనుక == 3) {
        fill24(dst, cnt);
    } లేకపోతే ఒకవేళ (వెనుక == 4) {
        fill32(dst, cnt);
    } లేకపోతే {
        ఒకవేళ (cnt >= 16) {
            పూర్ణాంకం blocklen = వెనుక;
            అయితే (cnt > blocklen) {
                జ్ఞాపకం_నకలు(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            జ్ఞాపకం_నకలు(dst, src, cnt);
            తిరిగి;
        }
        ఒకవేళ (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        ఒకవేళ (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        ఒకవేళ (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        ఒకవేళ (cnt)
            *dst = *src;
    }
}

శూన్య *av_fast_realloc(శూన్య *ptr, గుర్తులేని పూర్ణాంకం *కొలత, size_t min_కొలత)
{
    size_t max_కొలత;

    ఒకవేళ (min_కొలత <= *కొలత)
        తిరిగి ptr;

    max_కొలత = atomic_load_explicit(&max_alloc_కొలత, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_కొలత = FFMIN(max_కొలత, UINT_MAX);

    ఒకవేళ (min_కొలత > max_కొలత) {
        *కొలత = 0;
        తిరిగి ఖాళీ;
    }

    min_కొలత = FFMIN(max_కొలత, FFMAX(min_కొలత + min_కొలత / 16 + 32, min_కొలత));

    ptr = av_realloc(ptr, min_కొలత);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    ఒకవేళ (!ptr)
        min_కొలత = 0;

    *కొలత = min_కొలత;

    తిరిగి ptr;
}

స్థిర అంతఃవరుస శూన్య fast_malloc(శూన్య *ptr, గుర్తులేని పూర్ణాంకం *కొలత, size_t min_కొలత, పూర్ణాంకం zero_realloc)
{
    size_t max_కొలత;
    శూన్య *val;

    జ్ఞాపకం_నకలు(&val, ptr, పరిమాణం(val));
    ఒకవేళ (min_కొలత <= *కొలత) {
        av_assert0(val || !min_కొలత);
        తిరిగి;
    }

    max_కొలత = atomic_load_explicit(&max_alloc_కొలత, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_కొలత = FFMIN(max_కొలత, UINT_MAX);

    ఒకవేళ (min_కొలత > max_కొలత) {
        av_freep(ptr);
        *కొలత = 0;
        తిరిగి;
    }
    min_కొలత = FFMIN(max_కొలత, FFMAX(min_కొలత + min_కొలత / 16 + 32, min_కొలత));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_కొలత) : av_malloc(min_కొలత);
    జ్ఞాపకం_నకలు(ptr, &val, పరిమాణం(val));
    ఒకవేళ (!val)
        min_కొలత = 0;
    *కొలత = min_కొలత;
    తిరిగి;
}

శూన్య av_fast_malloc(శూన్య *ptr, గుర్తులేని పూర్ణాంకం *కొలత, size_t min_కొలత)
{
    fast_malloc(ptr, కొలత, min_కొలత, 0);
}

శూన్య av_fast_mallocz(శూన్య *ptr, గుర్తులేని పూర్ణాంకం *కొలత, size_t min_కొలత)
{
    fast_malloc(ptr, కొలత, min_కొలత, 1);
}

పూర్ణాంకం av_కొలత_mult(size_t a, size_t b, size_t *r)
{
    తిరిగి కొలత_mult(a, b, r);
}

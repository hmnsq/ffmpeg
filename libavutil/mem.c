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

#تعریف_کرو XOPEN_سروت 600

#ضمن "config.h"

#ضمن <limits.h>
#ضمن <stdint.h>
#ضمن <stdlib.h>
#ضمن <stdatomic.h>
#ضمن <string.h>
#إذا HAVE_MALLOC_H
#ضمن <malloc.h>
#جے_انت

#ضمن "attributes.h"
#ضمن "avassert.h"
#ضمن "dynarray.h"
#ضمن "error.h"
#ضمن "internal.h"
#ضمن "intreadwrite.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "sanitizer.h"

#جے_تعریف_شدہ MALLOC_اگیتر

#تعریف_کرو حافظہ_دیو         AV_JOIN(MALLOC_اگیتر, حافظہ_دیو)
#تعریف_کرو memalign       AV_JOIN(MALLOC_اگیتر, memalign)
#تعریف_کرو posix_memalign AV_JOIN(MALLOC_اگیتر, posix_memalign)
#تعریف_کرو realloc        AV_JOIN(MALLOC_اگیتر, realloc)
#تعریف_کرو حرر           AV_JOIN(MALLOC_اگیتر, حرر)

فراغ *حافظہ_دیو(size_t ناپ);
فراغ *memalign(size_t align, size_t ناپ);
صحيح   posix_memalign(فراغ **ptr, size_t align, size_t ناپ);
فراغ *realloc(فراغ *ptr, size_t ناپ);
فراغ  حرر(فراغ *ptr);

#جے_انت /* MALLOC_PREFIX */

#تعریف_کرو ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#تعریف_کرو FF_حافظہ_POISON 0x2a

ساكن فراغ poison_حافظہ(فراغ *ptr, size_t ناپ)
{
#إذا CONFIG_حافظہ_POISONING
    memset(ptr, FF_حافظہ_POISON, ناپ);
#جے_انت
    FF_MEM_UNDEFINED(ptr, ناپ);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#إذا HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#تعریف_کرو ASAN_ALIGNED_ALLOC 1

ساكن صحيح asan_aligned_alloc_needed(فراغ)
{
    ساكن atomic_int needed = -1;
    صحيح ret = atomic_load_explicit(&needed, memory_order_relaxed);

    إذا (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        صحيح probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        إذا (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    أرجع ret;
}

تعريفنوع بنية Asan_Aligned_سرخی {
    فراغ  *ادھار_2;
    size_t ناپ;
} Asan_Aligned_سرخی;

ساكن فراغ *asan_aligned_malloc(size_t ناپ)
{
    Asan_Aligned_سرخی *hdr;
    uint8_t *ادھار_2, *ptr;
    size_t کل;

    إذا (ناپ > SIZE_MAX - ALIGN - حجم(*hdr))
        أرجع عدم;
    کل = ناپ + ALIGN + حجم(*hdr);
    ادھار_2  = حافظہ_دیو(کل);
    إذا (!ادھار_2)
        أرجع عدم;
    ptr = (uint8_t *)FFALIGN((uintptr_t)ادھار_2 + حجم(*hdr), ALIGN);
    hdr = (Asan_Aligned_سرخی *)ptr - 1;
    hdr->ادھار_2 = ادھار_2;
    hdr->ناپ = ناپ;
    FF_ASAN_POISON(ادھار_2, ptr - ادھار_2);
    FF_ASAN_POISON(ptr + ناپ, ادھار_2 + کل - (ptr + ناپ));
    أرجع ptr;
}

ساكن Asan_Aligned_سرخی *asan_aligned_سرخی(فراغ *ptr)
{
    Asan_Aligned_سرخی *hdr = (Asan_Aligned_سرخی *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, حجم(*hdr));
    أرجع hdr;
}

ساكن فراغ asan_aligned_free(فراغ *ptr)
{
    إذا (ptr)
        حرر(asan_aligned_سرخی(ptr)->ادھار_2);
}

ساكن فراغ *asan_aligned_realloc(فراغ *ptr, size_t ناپ)
{
    Asan_Aligned_سرخی *hdr;
    فراغ *ret;

    إذا (!ptr)
        أرجع asan_aligned_malloc(ناپ);
    ret = asan_aligned_malloc(ناپ);
    إذا (!ret)
        أرجع عدم;
    hdr = asan_aligned_سرخی(ptr);
    حافظہ_نقل(ret, ptr, FFMIN(ناپ, hdr->ناپ));
    حرر(hdr->ادھار_2);
    أرجع ret;
}
#وإلا
#تعریف_کرو ASAN_ALIGNED_ALLOC 0
#جے_انت

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

ساكن atomic_size_t max_alloc_ناپ = ودھ_توں_ودھ_عدد;

فراغ av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_ناپ, max, memory_order_relaxed);
}

ساكن صحيح ناپ_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#إذا (!defined(__INTEL_COMPILER) && AV_GCC_نسخہ_AT_گھٹ_توں_گھٹ(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    إذا (__builtin_mul_overflow(a, b, &t))
        أرجع AVERROR(EINVAL);
#وإلا
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    إذا ((a | b) >= ((size_t)1 << (حجم(size_t) * 4)) && a && t / a != b)
        أرجع AVERROR(EINVAL);
#جے_انت
    *r = t;
    أرجع 0;
}

فراغ *av_malloc(size_t ناپ)
{
    فراغ *ptr = عدم;

    إذا (ناپ > atomic_load_explicit(&max_alloc_ناپ, memory_order_relaxed))
        أرجع عدم;

#إذا ASAN_ALIGNED_ALLOC
    إذا (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(ناپ);
    وإلا
        ptr = _aligned_malloc(ناپ, ALIGN);
#وإلاإذا HAVE_POSIX_MEMALIGN
    إذا (ناپ) //OS X on SDK 10.6 has a broken posix_memalign implementation
    إذا (posix_memalign(&ptr, ALIGN, ناپ))
        ptr = عدم;
#وإلاإذا HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(ناپ, ALIGN);
#وإلاإذا HAVE_MEMALIGN
#جے_بنا_تعریف __DJGPP__
    ptr = memalign(ALIGN, ناپ);
#وإلا
    ptr = memalign(ناپ, ALIGN);
#جے_انت
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
#وإلا
    ptr = حافظہ_دیو(ناپ);
#جے_انت
    إذا(!ptr && !ناپ) {
        ناپ = 1;
        ptr= av_malloc(1);
    }
    إذا (ptr)
        poison_حافظہ(ptr, ناپ);
    أرجع ptr;
}

فراغ *av_realloc(فراغ *ptr, size_t ناپ)
{
    فراغ *ret;
    إذا (ناپ > atomic_load_explicit(&max_alloc_ناپ, memory_order_relaxed))
        أرجع عدم;

#إذا ASAN_ALIGNED_ALLOC
    إذا (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, ناپ + !ناپ);
    وإلا
        ret = _aligned_realloc(ptr, ناپ + !ناپ, ALIGN);
#وإلاإذا HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, ناپ + !ناپ, ALIGN);
#وإلا
    ret = realloc(ptr, ناپ + !ناپ);
#جے_انت
    إذا (ret && !ptr)
        poison_حافظہ(ret, ناپ);
    أرجع ret;
}

فراغ *av_realloc_f(فراغ *ptr, size_t nelem, size_t elsize)
{
    size_t ناپ;
    فراغ *r;

    إذا (ناپ_mult(elsize, nelem, &ناپ)) {
        av_free(ptr);
        أرجع عدم;
    }
    r = av_realloc(ptr, ناپ);
    إذا (!r)
        av_free(ptr);
    أرجع r;
}

صحيح av_reallocp(فراغ *ptr, size_t ناپ)
{
    فراغ *val;

    إذا (!ناپ) {
        av_freep(ptr);
        أرجع 0;
    }

    حافظہ_نقل(&val, ptr, حجم(val));
    val = av_realloc(val, ناپ);

    إذا (!val) {
        av_freep(ptr);
        أرجع AVERROR(ENOMEM);
    }

    حافظہ_نقل(ptr, &val, حجم(val));
    أرجع 0;
}

فراغ *av_malloc_array(size_t nmemb, size_t ناپ)
{
    size_t نتیجہ;
    إذا (ناپ_mult(nmemb, ناپ, &نتیجہ) < 0)
        أرجع عدم;
    أرجع av_malloc(نتیجہ);
}

فراغ *av_realloc_array(فراغ *ptr, size_t nmemb, size_t ناپ)
{
    size_t نتیجہ;
    إذا (ناپ_mult(nmemb, ناپ, &نتیجہ) < 0)
        أرجع عدم;
    أرجع av_realloc(ptr, نتیجہ);
}

صحيح av_reallocp_array(فراغ *ptr, size_t nmemb, size_t ناپ)
{
    فراغ *val;

    حافظہ_نقل(&val, ptr, حجم(val));
    val = av_realloc_f(val, nmemb, ناپ);
    حافظہ_نقل(ptr, &val, حجم(val));
    إذا (!val && nmemb && ناپ)
        أرجع AVERROR(ENOMEM);

    أرجع 0;
}

فراغ av_free(فراغ *ptr)
{
#إذا ASAN_ALIGNED_ALLOC
    إذا (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    وإلا
        _aligned_free(ptr);
#وإلاإذا HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#وإلا
    حرر(ptr);
#جے_انت
}

فراغ av_freep(فراغ *arg)
{
    فراغ *val;

    حافظہ_نقل(&val, arg, حجم(val));
    حافظہ_نقل(arg, &(فراغ *){ عدم }, حجم(val));
    av_free(val);
}

فراغ *av_mallocz(size_t ناپ)
{
    فراغ *ptr = av_malloc(ناپ);
    إذا (ptr)
        memset(ptr, 0, ناپ);
    أرجع ptr;
}

فراغ *av_calloc(size_t nmemb, size_t ناپ)
{
    size_t نتیجہ;
    إذا (ناپ_mult(nmemb, ناپ, &نتیجہ) < 0)
        أرجع عدم;
    أرجع av_mallocz(نتیجہ);
}

حرف *av_strdup(ثابت حرف *s)
{
    حرف *ptr = عدم;
    إذا (s) {
        size_t len = لڑی_لمبائی(s) + 1;
        ptr = av_realloc(عدم, len);
        إذا (ptr)
            حافظہ_نقل(ptr, s, len);
    }
    أرجع ptr;
}

حرف *av_strndup(ثابت حرف *s, size_t len)
{
    إذا (!s)
        أرجع عدم;

    ثابت حرف *سرا = memchr(s, 0, len);
    إذا (سرا)
        len = سرا - s;

    حرف *ret = av_realloc(عدم, len + 1);
    إذا (!ret)
        أرجع عدم;

    حافظہ_نقل(ret, s, len);
    ret[len] = 0;
    أرجع ret;
}

فراغ *av_memdup(ثابت فراغ *p, size_t ناپ)
{
    فراغ *ptr = عدم;
    إذا (p) {
        ptr = av_malloc(ناپ);
        إذا (ptr)
            حافظہ_نقل(ptr, p, ناپ);
    }
    أرجع ptr;
}

صحيح av_dynarray_جوڑو_nofree(فراغ *tab_ptr, صحيح *nb_ptr, فراغ *elem)
{
    فراغ **tab;
    حافظہ_نقل(&tab, tab_ptr, حجم(tab));

    FF_DYNARRAY_جوڑو(ودھ_توں_ودھ_عدد, حجم(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        حافظہ_نقل(tab_ptr, &tab, حجم(tab));
    }, {
        أرجع AVERROR(ENOMEM);
    });
    أرجع 0;
}

فراغ av_dynarray_جوڑو(فراغ *tab_ptr, صحيح *nb_ptr, فراغ *elem)
{
    فراغ **tab;
    حافظہ_نقل(&tab, tab_ptr, حجم(tab));

    FF_DYNARRAY_جوڑو(ودھ_توں_ودھ_عدد, حجم(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        حافظہ_نقل(tab_ptr, &tab, حجم(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

فراغ *av_dynarray2_جوڑو(فراغ **tab_ptr, صحيح *nb_ptr, size_t elem_ناپ,
                       ثابت uint8_t *elem_انکڑے)
{
    uint8_t *tab_elem_انکڑے = عدم;

    FF_DYNARRAY_جوڑو(ودھ_توں_ودھ_عدد, elem_ناپ, *tab_ptr, *nb_ptr, {
        tab_elem_انکڑے = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_ناپ;
        إذا (elem_انکڑے)
            حافظہ_نقل(tab_elem_انکڑے, elem_انکڑے, elem_ناپ);
        وإلا
            poison_حافظہ(tab_elem_انکڑے, elem_ناپ);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    أرجع tab_elem_انکڑے;
}

ساكن فراغ fill16(uint8_t *dst, صحيح len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    طالما (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    طالما (len--) {
        *dst = dst[-2];
        dst++;
    }
}

ساكن فراغ fill24(uint8_t *dst, صحيح len)
{
#إذا HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#وإلا
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#جے_انت

    طالما (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    إذا (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    إذا (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    طالما (len--) {
        *dst = dst[-3];
        dst++;
    }
}

ساكن فراغ fill32(uint8_t *dst, صحيح len)
{
    uint32_t v = AV_RN32(dst - 4);

#إذا HAVE_FAST_64_ثنائی_ہندسہ
    uint64_t v2= v + ((uint64_t)v<<32);
    طالما (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#جے_انت

    طالما (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    طالما (len--) {
        *dst = dst[-4];
        dst++;
    }
}

فراغ av_memcpy_backptr(uint8_t *dst, صحيح پٹھ, صحيح cnt)
{
    ثابت uint8_t *src = &dst[-پٹھ];
    إذا (!پٹھ)
        أرجع;

    إذا (پٹھ == 1) {
        memset(dst, *src, cnt);
    } وإلا إذا (پٹھ == 2) {
        fill16(dst, cnt);
    } وإلا إذا (پٹھ == 3) {
        fill24(dst, cnt);
    } وإلا إذا (پٹھ == 4) {
        fill32(dst, cnt);
    } وإلا {
        إذا (cnt >= 16) {
            صحيح blocklen = پٹھ;
            طالما (cnt > blocklen) {
                حافظہ_نقل(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            حافظہ_نقل(dst, src, cnt);
            أرجع;
        }
        إذا (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        إذا (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        إذا (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        إذا (cnt)
            *dst = *src;
    }
}

فراغ *av_fast_realloc(فراغ *ptr, بنانشانی صحيح *ناپ, size_t min_ناپ)
{
    size_t max_ناپ;

    إذا (min_ناپ <= *ناپ)
        أرجع ptr;

    max_ناپ = atomic_load_explicit(&max_alloc_ناپ, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_ناپ = FFMIN(max_ناپ, UINT_MAX);

    إذا (min_ناپ > max_ناپ) {
        *ناپ = 0;
        أرجع عدم;
    }

    min_ناپ = FFMIN(max_ناپ, FFMAX(min_ناپ + min_ناپ / 16 + 32, min_ناپ));

    ptr = av_realloc(ptr, min_ناپ);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    إذا (!ptr)
        min_ناپ = 0;

    *ناپ = min_ناپ;

    أرجع ptr;
}

ساكن مضمن فراغ fast_malloc(فراغ *ptr, بنانشانی صحيح *ناپ, size_t min_ناپ, صحيح zero_realloc)
{
    size_t max_ناپ;
    فراغ *val;

    حافظہ_نقل(&val, ptr, حجم(val));
    إذا (min_ناپ <= *ناپ) {
        av_assert0(val || !min_ناپ);
        أرجع;
    }

    max_ناپ = atomic_load_explicit(&max_alloc_ناپ, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_ناپ = FFMIN(max_ناپ, UINT_MAX);

    إذا (min_ناپ > max_ناپ) {
        av_freep(ptr);
        *ناپ = 0;
        أرجع;
    }
    min_ناپ = FFMIN(max_ناپ, FFMAX(min_ناپ + min_ناپ / 16 + 32, min_ناپ));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_ناپ) : av_malloc(min_ناپ);
    حافظہ_نقل(ptr, &val, حجم(val));
    إذا (!val)
        min_ناپ = 0;
    *ناپ = min_ناپ;
    أرجع;
}

فراغ av_fast_malloc(فراغ *ptr, بنانشانی صحيح *ناپ, size_t min_ناپ)
{
    fast_malloc(ptr, ناپ, min_ناپ, 0);
}

فراغ av_fast_mallocz(فراغ *ptr, بنانشانی صحيح *ناپ, size_t min_ناپ)
{
    fast_malloc(ptr, ناپ, min_ناپ, 1);
}

صحيح av_ناپ_mult(size_t a, size_t b, size_t *r)
{
    أرجع ناپ_mult(a, b, r);
}

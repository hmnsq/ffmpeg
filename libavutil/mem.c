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

#وصف_ڪريو XOPEN_ذريعو 600

#ضمن "config.h"

#ضمن <limits.h>
#ضمن <stdint.h>
#ضمن <stdlib.h>
#ضمن <stdatomic.h>
#ضمن <string.h>
#إذا HAVE_MALLOC_H
#ضمن <malloc.h>
#جيڪڏهن_پورو

#ضمن "attributes.h"
#ضمن "avassert.h"
#ضمن "dynarray.h"
#ضمن "error.h"
#ضمن "internal.h"
#ضمن "intreadwrite.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "sanitizer.h"

#جيڪڏهن_وصف_ٿيل MALLOC_اڳياڙي

#وصف_ڪريو يادگيري_ڏيو         AV_JOIN(MALLOC_اڳياڙي, يادگيري_ڏيو)
#وصف_ڪريو memalign       AV_JOIN(MALLOC_اڳياڙي, memalign)
#وصف_ڪريو posix_memalign AV_JOIN(MALLOC_اڳياڙي, posix_memalign)
#وصف_ڪريو realloc        AV_JOIN(MALLOC_اڳياڙي, realloc)
#وصف_ڪريو حرر           AV_JOIN(MALLOC_اڳياڙي, حرر)

فراغ *يادگيري_ڏيو(size_t سائيز);
فراغ *memalign(size_t align, size_t سائيز);
صحيح   posix_memalign(فراغ **ptr, size_t align, size_t سائيز);
فراغ *realloc(فراغ *ptr, size_t سائيز);
فراغ  حرر(فراغ *ptr);

#جيڪڏهن_پورو /* MALLOC_PREFIX */

#وصف_ڪريو ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#وصف_ڪريو FF_يادگيري_POISON 0x2a

ساكن فراغ poison_يادگيري(فراغ *ptr, size_t سائيز)
{
#إذا CONFIG_يادگيري_POISONING
    memset(ptr, FF_يادگيري_POISON, سائيز);
#جيڪڏهن_پورو
    FF_MEM_UNDEFINED(ptr, سائيز);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#إذا HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#وصف_ڪريو ASAN_ALIGNED_ALLOC 1

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

تعريفنوع بنية Asan_Aligned_سرو {
    فراغ  *بنياد_2;
    size_t سائيز;
} Asan_Aligned_سرو;

ساكن فراغ *asan_aligned_malloc(size_t سائيز)
{
    Asan_Aligned_سرو *hdr;
    uint8_t *بنياد_2, *ptr;
    size_t ڪل;

    إذا (سائيز > SIZE_MAX - ALIGN - حجم(*hdr))
        أرجع عدم;
    ڪل = سائيز + ALIGN + حجم(*hdr);
    بنياد_2  = يادگيري_ڏيو(ڪل);
    إذا (!بنياد_2)
        أرجع عدم;
    ptr = (uint8_t *)FFALIGN((uintptr_t)بنياد_2 + حجم(*hdr), ALIGN);
    hdr = (Asan_Aligned_سرو *)ptr - 1;
    hdr->بنياد_2 = بنياد_2;
    hdr->سائيز = سائيز;
    FF_ASAN_POISON(بنياد_2, ptr - بنياد_2);
    FF_ASAN_POISON(ptr + سائيز, بنياد_2 + ڪل - (ptr + سائيز));
    أرجع ptr;
}

ساكن Asan_Aligned_سرو *asan_aligned_سرو(فراغ *ptr)
{
    Asan_Aligned_سرو *hdr = (Asan_Aligned_سرو *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, حجم(*hdr));
    أرجع hdr;
}

ساكن فراغ asan_aligned_free(فراغ *ptr)
{
    إذا (ptr)
        حرر(asan_aligned_سرو(ptr)->بنياد_2);
}

ساكن فراغ *asan_aligned_realloc(فراغ *ptr, size_t سائيز)
{
    Asan_Aligned_سرو *hdr;
    فراغ *ret;

    إذا (!ptr)
        أرجع asan_aligned_malloc(سائيز);
    ret = asan_aligned_malloc(سائيز);
    إذا (!ret)
        أرجع عدم;
    hdr = asan_aligned_سرو(ptr);
    يادگيري_نقل(ret, ptr, FFMIN(سائيز, hdr->سائيز));
    حرر(hdr->بنياد_2);
    أرجع ret;
}
#وإلا
#وصف_ڪريو ASAN_ALIGNED_ALLOC 0
#جيڪڏهن_پورو

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

ساكن atomic_size_t max_alloc_سائيز = وڌ_کان_وڌ_عدد;

فراغ av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_سائيز, max, memory_order_relaxed);
}

ساكن صحيح سائيز_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#إذا (!defined(__INTEL_COMPILER) && AV_GCC_نسخو_AT_گهٽ_کان_گهٽ(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    إذا (__builtin_mul_overflow(a, b, &t))
        أرجع AVERROR(EINVAL);
#وإلا
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    إذا ((a | b) >= ((size_t)1 << (حجم(size_t) * 4)) && a && t / a != b)
        أرجع AVERROR(EINVAL);
#جيڪڏهن_پورو
    *r = t;
    أرجع 0;
}

فراغ *av_malloc(size_t سائيز)
{
    فراغ *ptr = عدم;

    إذا (سائيز > atomic_load_explicit(&max_alloc_سائيز, memory_order_relaxed))
        أرجع عدم;

#إذا ASAN_ALIGNED_ALLOC
    إذا (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(سائيز);
    وإلا
        ptr = _aligned_malloc(سائيز, ALIGN);
#وإلاإذا HAVE_POSIX_MEMALIGN
    إذا (سائيز) //OS X on SDK 10.6 has a broken posix_memalign implementation
    إذا (posix_memalign(&ptr, ALIGN, سائيز))
        ptr = عدم;
#وإلاإذا HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(سائيز, ALIGN);
#وإلاإذا HAVE_MEMALIGN
#جيڪڏهن_وصف_نه_ٿيل __DJGPP__
    ptr = memalign(ALIGN, سائيز);
#وإلا
    ptr = memalign(سائيز, ALIGN);
#جيڪڏهن_پورو
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
    ptr = يادگيري_ڏيو(سائيز);
#جيڪڏهن_پورو
    إذا(!ptr && !سائيز) {
        سائيز = 1;
        ptr= av_malloc(1);
    }
    إذا (ptr)
        poison_يادگيري(ptr, سائيز);
    أرجع ptr;
}

فراغ *av_realloc(فراغ *ptr, size_t سائيز)
{
    فراغ *ret;
    إذا (سائيز > atomic_load_explicit(&max_alloc_سائيز, memory_order_relaxed))
        أرجع عدم;

#إذا ASAN_ALIGNED_ALLOC
    إذا (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, سائيز + !سائيز);
    وإلا
        ret = _aligned_realloc(ptr, سائيز + !سائيز, ALIGN);
#وإلاإذا HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, سائيز + !سائيز, ALIGN);
#وإلا
    ret = realloc(ptr, سائيز + !سائيز);
#جيڪڏهن_پورو
    إذا (ret && !ptr)
        poison_يادگيري(ret, سائيز);
    أرجع ret;
}

فراغ *av_realloc_f(فراغ *ptr, size_t nelem, size_t elsize)
{
    size_t سائيز;
    فراغ *r;

    إذا (سائيز_mult(elsize, nelem, &سائيز)) {
        av_free(ptr);
        أرجع عدم;
    }
    r = av_realloc(ptr, سائيز);
    إذا (!r)
        av_free(ptr);
    أرجع r;
}

صحيح av_reallocp(فراغ *ptr, size_t سائيز)
{
    فراغ *val;

    إذا (!سائيز) {
        av_freep(ptr);
        أرجع 0;
    }

    يادگيري_نقل(&val, ptr, حجم(val));
    val = av_realloc(val, سائيز);

    إذا (!val) {
        av_freep(ptr);
        أرجع AVERROR(ENOMEM);
    }

    يادگيري_نقل(ptr, &val, حجم(val));
    أرجع 0;
}

فراغ *av_malloc_array(size_t nmemb, size_t سائيز)
{
    size_t نتيجو;
    إذا (سائيز_mult(nmemb, سائيز, &نتيجو) < 0)
        أرجع عدم;
    أرجع av_malloc(نتيجو);
}

فراغ *av_realloc_array(فراغ *ptr, size_t nmemb, size_t سائيز)
{
    size_t نتيجو;
    إذا (سائيز_mult(nmemb, سائيز, &نتيجو) < 0)
        أرجع عدم;
    أرجع av_realloc(ptr, نتيجو);
}

صحيح av_reallocp_array(فراغ *ptr, size_t nmemb, size_t سائيز)
{
    فراغ *val;

    يادگيري_نقل(&val, ptr, حجم(val));
    val = av_realloc_f(val, nmemb, سائيز);
    يادگيري_نقل(ptr, &val, حجم(val));
    إذا (!val && nmemb && سائيز)
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
#جيڪڏهن_پورو
}

فراغ av_freep(فراغ *arg)
{
    فراغ *val;

    يادگيري_نقل(&val, arg, حجم(val));
    يادگيري_نقل(arg, &(فراغ *){ عدم }, حجم(val));
    av_free(val);
}

فراغ *av_mallocz(size_t سائيز)
{
    فراغ *ptr = av_malloc(سائيز);
    إذا (ptr)
        memset(ptr, 0, سائيز);
    أرجع ptr;
}

فراغ *av_calloc(size_t nmemb, size_t سائيز)
{
    size_t نتيجو;
    إذا (سائيز_mult(nmemb, سائيز, &نتيجو) < 0)
        أرجع عدم;
    أرجع av_mallocz(نتيجو);
}

حرف *av_strdup(ثابت حرف *s)
{
    حرف *ptr = عدم;
    إذا (s) {
        size_t len = لڙي_ڊيگهه(s) + 1;
        ptr = av_realloc(عدم, len);
        إذا (ptr)
            يادگيري_نقل(ptr, s, len);
    }
    أرجع ptr;
}

حرف *av_strndup(ثابت حرف *s, size_t len)
{
    إذا (!s)
        أرجع عدم;

    ثابت حرف *پڇاڙي = memchr(s, 0, len);
    إذا (پڇاڙي)
        len = پڇاڙي - s;

    حرف *ret = av_realloc(عدم, len + 1);
    إذا (!ret)
        أرجع عدم;

    يادگيري_نقل(ret, s, len);
    ret[len] = 0;
    أرجع ret;
}

فراغ *av_memdup(ثابت فراغ *p, size_t سائيز)
{
    فراغ *ptr = عدم;
    إذا (p) {
        ptr = av_malloc(سائيز);
        إذا (ptr)
            يادگيري_نقل(ptr, p, سائيز);
    }
    أرجع ptr;
}

صحيح av_dynarray_جوڙيو_nofree(فراغ *tab_ptr, صحيح *nb_ptr, فراغ *elem)
{
    فراغ **tab;
    يادگيري_نقل(&tab, tab_ptr, حجم(tab));

    FF_DYNARRAY_جوڙيو(وڌ_کان_وڌ_عدد, حجم(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        يادگيري_نقل(tab_ptr, &tab, حجم(tab));
    }, {
        أرجع AVERROR(ENOMEM);
    });
    أرجع 0;
}

فراغ av_dynarray_جوڙيو(فراغ *tab_ptr, صحيح *nb_ptr, فراغ *elem)
{
    فراغ **tab;
    يادگيري_نقل(&tab, tab_ptr, حجم(tab));

    FF_DYNARRAY_جوڙيو(وڌ_کان_وڌ_عدد, حجم(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        يادگيري_نقل(tab_ptr, &tab, حجم(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

فراغ *av_dynarray2_جوڙيو(فراغ **tab_ptr, صحيح *nb_ptr, size_t elem_سائيز,
                       ثابت uint8_t *elem_معلومات)
{
    uint8_t *tab_elem_معلومات = عدم;

    FF_DYNARRAY_جوڙيو(وڌ_کان_وڌ_عدد, elem_سائيز, *tab_ptr, *nb_ptr, {
        tab_elem_معلومات = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_سائيز;
        إذا (elem_معلومات)
            يادگيري_نقل(tab_elem_معلومات, elem_معلومات, elem_سائيز);
        وإلا
            poison_يادگيري(tab_elem_معلومات, elem_سائيز);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    أرجع tab_elem_معلومات;
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
#جيڪڏهن_پورو

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

#إذا HAVE_FAST_64_ٻٽو_انگ
    uint64_t v2= v + ((uint64_t)v<<32);
    طالما (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#جيڪڏهن_پورو

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

فراغ av_memcpy_backptr(uint8_t *dst, صحيح پٺ, صحيح cnt)
{
    ثابت uint8_t *src = &dst[-پٺ];
    إذا (!پٺ)
        أرجع;

    إذا (پٺ == 1) {
        memset(dst, *src, cnt);
    } وإلا إذا (پٺ == 2) {
        fill16(dst, cnt);
    } وإلا إذا (پٺ == 3) {
        fill24(dst, cnt);
    } وإلا إذا (پٺ == 4) {
        fill32(dst, cnt);
    } وإلا {
        إذا (cnt >= 16) {
            صحيح blocklen = پٺ;
            طالما (cnt > blocklen) {
                يادگيري_نقل(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            يادگيري_نقل(dst, src, cnt);
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

فراغ *av_fast_realloc(فراغ *ptr, بنانشان صحيح *سائيز, size_t min_سائيز)
{
    size_t max_سائيز;

    إذا (min_سائيز <= *سائيز)
        أرجع ptr;

    max_سائيز = atomic_load_explicit(&max_alloc_سائيز, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_سائيز = FFMIN(max_سائيز, UINT_MAX);

    إذا (min_سائيز > max_سائيز) {
        *سائيز = 0;
        أرجع عدم;
    }

    min_سائيز = FFMIN(max_سائيز, FFMAX(min_سائيز + min_سائيز / 16 + 32, min_سائيز));

    ptr = av_realloc(ptr, min_سائيز);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    إذا (!ptr)
        min_سائيز = 0;

    *سائيز = min_سائيز;

    أرجع ptr;
}

ساكن مضمن فراغ fast_malloc(فراغ *ptr, بنانشان صحيح *سائيز, size_t min_سائيز, صحيح zero_realloc)
{
    size_t max_سائيز;
    فراغ *val;

    يادگيري_نقل(&val, ptr, حجم(val));
    إذا (min_سائيز <= *سائيز) {
        av_assert0(val || !min_سائيز);
        أرجع;
    }

    max_سائيز = atomic_load_explicit(&max_alloc_سائيز, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_سائيز = FFMIN(max_سائيز, UINT_MAX);

    إذا (min_سائيز > max_سائيز) {
        av_freep(ptr);
        *سائيز = 0;
        أرجع;
    }
    min_سائيز = FFMIN(max_سائيز, FFMAX(min_سائيز + min_سائيز / 16 + 32, min_سائيز));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_سائيز) : av_malloc(min_سائيز);
    يادگيري_نقل(ptr, &val, حجم(val));
    إذا (!val)
        min_سائيز = 0;
    *سائيز = min_سائيز;
    أرجع;
}

فراغ av_fast_malloc(فراغ *ptr, بنانشان صحيح *سائيز, size_t min_سائيز)
{
    fast_malloc(ptr, سائيز, min_سائيز, 0);
}

فراغ av_fast_mallocz(فراغ *ptr, بنانشان صحيح *سائيز, size_t min_سائيز)
{
    fast_malloc(ptr, سائيز, min_سائيز, 1);
}

صحيح av_سائيز_mult(size_t a, size_t b, size_t *r)
{
    أرجع سائيز_mult(a, b, r);
}

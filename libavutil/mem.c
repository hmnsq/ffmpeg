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

#تعریف_کرو XOPEN_ماخذ 600

#شامل "config.h"

#شامل <limits.h>
#شامل <stdint.h>
#شامل <stdlib.h>
#شامل <stdatomic.h>
#شامل <string.h>
#اگر HAVE_MALLOC_H
#شامل <malloc.h>
#اگر_ختم

#شامل "attributes.h"
#شامل "avassert.h"
#شامل "dynarray.h"
#شامل "error.h"
#شامل "internal.h"
#شامل "intreadwrite.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "sanitizer.h"

#اگر_تعریف_شدہ MALLOC_سابقہ

#تعریف_کرو حافظہ_دو         AV_JOIN(MALLOC_سابقہ, حافظہ_دو)
#تعریف_کرو memalign       AV_JOIN(MALLOC_سابقہ, memalign)
#تعریف_کرو posix_memalign AV_JOIN(MALLOC_سابقہ, posix_memalign)
#تعریف_کرو realloc        AV_JOIN(MALLOC_سابقہ, realloc)
#تعریف_کرو آزاد           AV_JOIN(MALLOC_سابقہ, آزاد)

خالی *حافظہ_دو(size_t سائز);
خالی *memalign(size_t align, size_t سائز);
صحیح   posix_memalign(خالی **ptr, size_t align, size_t سائز);
خالی *realloc(خالی *ptr, size_t سائز);
خالی  آزاد(خالی *ptr);

#اگر_ختم /* MALLOC_PREFIX */

#تعریف_کرو ALIGN (HAVE_SIMD_ALIGN_64 ? 64 : (HAVE_SIMD_ALIGN_32 ? 32 : 16))

#تعریف_کرو FF_حافظہ_POISON 0x2a

ساکن خالی poison_حافظہ(خالی *ptr, size_t سائز)
{
#اگر CONFIG_حافظہ_POISONING
    memset(ptr, FF_حافظہ_POISON, سائز);
#اگر_ختم
    FF_MEM_UNDEFINED(ptr, سائز);
}

/* The LLVM ASan runtime for Windows does not intercept the _aligned_malloc
 * family, so the alignment slack around a block stays addressable and small
 * overflows go unnoticed, while the runtime shipped with Visual Studio does
 * intercept it. Which one is linked cannot be told at compile time, so probe
 * once whether the byte after an aligned allocation is poisoned and align by
 * hand only when it is not. */
#اگر HAVE_ASAN && HAVE_ALIGNED_MALLOC && !HAVE_POSIX_MEMALIGN && !HAVE_MEMALIGN
#تعریف_کرو ASAN_ALIGNED_ALLOC 1

ساکن صحیح asan_aligned_alloc_needed(خالی)
{
    ساکن atomic_int needed = -1;
    صحیح ret = atomic_load_explicit(&needed, memory_order_relaxed);

    اگر (ret < 0) {
        uint8_t *p = _aligned_malloc(16, ALIGN);
        صحیح probed = !p || !__asan_address_is_poisoned(p + 16);
        _aligned_free(p);
        /* Every block must be freed by the allocator that made it, so the
         * first probe to finish decides for all callers. */
        اگر (atomic_compare_exchange_strong_explicit(&needed, &ret, probed,
                                                    memory_order_relaxed,
                                                    memory_order_relaxed))
            ret = probed;
    }
    واپس ret;
}

قسمتعریف ساخت Asan_Aligned_سرخی {
    خالی  *بنیاد_2;
    size_t سائز;
} Asan_Aligned_سرخی;

ساکن خالی *asan_aligned_malloc(size_t سائز)
{
    Asan_Aligned_سرخی *hdr;
    uint8_t *بنیاد_2, *ptr;
    size_t کل;

    اگر (سائز > SIZE_MAX - ALIGN - حجم(*hdr))
        واپس تہی;
    کل = سائز + ALIGN + حجم(*hdr);
    بنیاد_2  = حافظہ_دو(کل);
    اگر (!بنیاد_2)
        واپس تہی;
    ptr = (uint8_t *)FFALIGN((uintptr_t)بنیاد_2 + حجم(*hdr), ALIGN);
    hdr = (Asan_Aligned_سرخی *)ptr - 1;
    hdr->بنیاد_2 = بنیاد_2;
    hdr->سائز = سائز;
    FF_ASAN_POISON(بنیاد_2, ptr - بنیاد_2);
    FF_ASAN_POISON(ptr + سائز, بنیاد_2 + کل - (ptr + سائز));
    واپس ptr;
}

ساکن Asan_Aligned_سرخی *asan_aligned_سرخی(خالی *ptr)
{
    Asan_Aligned_سرخی *hdr = (Asan_Aligned_سرخی *)ptr - 1;
    FF_ASAN_UNPOISON(hdr, حجم(*hdr));
    واپس hdr;
}

ساکن خالی asan_aligned_free(خالی *ptr)
{
    اگر (ptr)
        آزاد(asan_aligned_سرخی(ptr)->بنیاد_2);
}

ساکن خالی *asan_aligned_realloc(خالی *ptr, size_t سائز)
{
    Asan_Aligned_سرخی *hdr;
    خالی *ret;

    اگر (!ptr)
        واپس asan_aligned_malloc(سائز);
    ret = asan_aligned_malloc(سائز);
    اگر (!ret)
        واپس تہی;
    hdr = asan_aligned_سرخی(ptr);
    حافظہ_نقل(ret, ptr, FFMIN(سائز, hdr->سائز));
    آزاد(hdr->بنیاد_2);
    واپس ret;
}
#ورنہ
#تعریف_کرو ASAN_ALIGNED_ALLOC 0
#اگر_ختم

/* NOTE: if you want to override these functions with your own
 * implementations (not recommended) you have to link libav* as
 * dynamic libraries and remove -Wl,-Bsymbolic from the linker flags.
 * Note that this will cost performance. */

ساکن atomic_size_t max_alloc_سائز = زیادہ_سے_زیادہ_عدد;

خالی av_max_alloc(size_t max){
    atomic_store_explicit(&max_alloc_سائز, max, memory_order_relaxed);
}

ساکن صحیح سائز_mult(size_t a, size_t b, size_t *r)
{
    size_t t;

#اگر (!defined(__INTEL_COMPILER) && AV_GCC_نسخہ_AT_کم_سے_کم(5,1)) || AV_HAS_BUILTIN(__builtin_mul_overflow)
    اگر (__builtin_mul_overflow(a, b, &t))
        واپس AVERROR(EINVAL);
#ورنہ
    t = a * b;
    /* Hack inspired from glibc: don't try the division if nelem and elsize
     * are both less than sqrt(SIZE_MAX). */
    اگر ((a | b) >= ((size_t)1 << (حجم(size_t) * 4)) && a && t / a != b)
        واپس AVERROR(EINVAL);
#اگر_ختم
    *r = t;
    واپس 0;
}

خالی *av_malloc(size_t سائز)
{
    خالی *ptr = تہی;

    اگر (سائز > atomic_load_explicit(&max_alloc_سائز, memory_order_relaxed))
        واپس تہی;

#اگر ASAN_ALIGNED_ALLOC
    اگر (asan_aligned_alloc_needed())
        ptr = asan_aligned_malloc(سائز);
    ورنہ
        ptr = _aligned_malloc(سائز, ALIGN);
#وگرنہ_اگر HAVE_POSIX_MEMALIGN
    اگر (سائز) //OS X on SDK 10.6 has a broken posix_memalign implementation
    اگر (posix_memalign(&ptr, ALIGN, سائز))
        ptr = تہی;
#وگرنہ_اگر HAVE_ALIGNED_MALLOC
    ptr = _aligned_malloc(سائز, ALIGN);
#وگرنہ_اگر HAVE_MEMALIGN
#اگر_غیر_تعریف_شدہ __DJGPP__
    ptr = memalign(ALIGN, سائز);
#ورنہ
    ptr = memalign(سائز, ALIGN);
#اگر_ختم
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
#ورنہ
    ptr = حافظہ_دو(سائز);
#اگر_ختم
    اگر(!ptr && !سائز) {
        سائز = 1;
        ptr= av_malloc(1);
    }
    اگر (ptr)
        poison_حافظہ(ptr, سائز);
    واپس ptr;
}

خالی *av_realloc(خالی *ptr, size_t سائز)
{
    خالی *ret;
    اگر (سائز > atomic_load_explicit(&max_alloc_سائز, memory_order_relaxed))
        واپس تہی;

#اگر ASAN_ALIGNED_ALLOC
    اگر (asan_aligned_alloc_needed())
        ret = asan_aligned_realloc(ptr, سائز + !سائز);
    ورنہ
        ret = _aligned_realloc(ptr, سائز + !سائز, ALIGN);
#وگرنہ_اگر HAVE_ALIGNED_MALLOC
    ret = _aligned_realloc(ptr, سائز + !سائز, ALIGN);
#ورنہ
    ret = realloc(ptr, سائز + !سائز);
#اگر_ختم
    اگر (ret && !ptr)
        poison_حافظہ(ret, سائز);
    واپس ret;
}

خالی *av_realloc_f(خالی *ptr, size_t nelem, size_t elsize)
{
    size_t سائز;
    خالی *r;

    اگر (سائز_mult(elsize, nelem, &سائز)) {
        av_free(ptr);
        واپس تہی;
    }
    r = av_realloc(ptr, سائز);
    اگر (!r)
        av_free(ptr);
    واپس r;
}

صحیح av_reallocp(خالی *ptr, size_t سائز)
{
    خالی *val;

    اگر (!سائز) {
        av_freep(ptr);
        واپس 0;
    }

    حافظہ_نقل(&val, ptr, حجم(val));
    val = av_realloc(val, سائز);

    اگر (!val) {
        av_freep(ptr);
        واپس AVERROR(ENOMEM);
    }

    حافظہ_نقل(ptr, &val, حجم(val));
    واپس 0;
}

خالی *av_malloc_array(size_t nmemb, size_t سائز)
{
    size_t نتیجہ;
    اگر (سائز_mult(nmemb, سائز, &نتیجہ) < 0)
        واپس تہی;
    واپس av_malloc(نتیجہ);
}

خالی *av_realloc_array(خالی *ptr, size_t nmemb, size_t سائز)
{
    size_t نتیجہ;
    اگر (سائز_mult(nmemb, سائز, &نتیجہ) < 0)
        واپس تہی;
    واپس av_realloc(ptr, نتیجہ);
}

صحیح av_reallocp_array(خالی *ptr, size_t nmemb, size_t سائز)
{
    خالی *val;

    حافظہ_نقل(&val, ptr, حجم(val));
    val = av_realloc_f(val, nmemb, سائز);
    حافظہ_نقل(ptr, &val, حجم(val));
    اگر (!val && nmemb && سائز)
        واپس AVERROR(ENOMEM);

    واپس 0;
}

خالی av_free(خالی *ptr)
{
#اگر ASAN_ALIGNED_ALLOC
    اگر (asan_aligned_alloc_needed())
        asan_aligned_free(ptr);
    ورنہ
        _aligned_free(ptr);
#وگرنہ_اگر HAVE_ALIGNED_MALLOC
    _aligned_free(ptr);
#ورنہ
    آزاد(ptr);
#اگر_ختم
}

خالی av_freep(خالی *arg)
{
    خالی *val;

    حافظہ_نقل(&val, arg, حجم(val));
    حافظہ_نقل(arg, &(خالی *){ تہی }, حجم(val));
    av_free(val);
}

خالی *av_mallocz(size_t سائز)
{
    خالی *ptr = av_malloc(سائز);
    اگر (ptr)
        memset(ptr, 0, سائز);
    واپس ptr;
}

خالی *av_calloc(size_t nmemb, size_t سائز)
{
    size_t نتیجہ;
    اگر (سائز_mult(nmemb, سائز, &نتیجہ) < 0)
        واپس تہی;
    واپس av_mallocz(نتیجہ);
}

حرف *av_strdup(ثابت حرف *s)
{
    حرف *ptr = تہی;
    اگر (s) {
        size_t len = لڑی_لمبائی(s) + 1;
        ptr = av_realloc(تہی, len);
        اگر (ptr)
            حافظہ_نقل(ptr, s, len);
    }
    واپس ptr;
}

حرف *av_strndup(ثابت حرف *s, size_t len)
{
    اگر (!s)
        واپس تہی;

    ثابت حرف *انتہا = memchr(s, 0, len);
    اگر (انتہا)
        len = انتہا - s;

    حرف *ret = av_realloc(تہی, len + 1);
    اگر (!ret)
        واپس تہی;

    حافظہ_نقل(ret, s, len);
    ret[len] = 0;
    واپس ret;
}

خالی *av_memdup(ثابت خالی *p, size_t سائز)
{
    خالی *ptr = تہی;
    اگر (p) {
        ptr = av_malloc(سائز);
        اگر (ptr)
            حافظہ_نقل(ptr, p, سائز);
    }
    واپس ptr;
}

صحیح av_dynarray_جوڑو_nofree(خالی *tab_ptr, صحیح *nb_ptr, خالی *elem)
{
    خالی **tab;
    حافظہ_نقل(&tab, tab_ptr, حجم(tab));

    FF_DYNARRAY_جوڑو(زیادہ_سے_زیادہ_عدد, حجم(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        حافظہ_نقل(tab_ptr, &tab, حجم(tab));
    }, {
        واپس AVERROR(ENOMEM);
    });
    واپس 0;
}

خالی av_dynarray_جوڑو(خالی *tab_ptr, صحیح *nb_ptr, خالی *elem)
{
    خالی **tab;
    حافظہ_نقل(&tab, tab_ptr, حجم(tab));

    FF_DYNARRAY_جوڑو(زیادہ_سے_زیادہ_عدد, حجم(*tab), tab, *nb_ptr, {
        tab[*nb_ptr] = elem;
        حافظہ_نقل(tab_ptr, &tab, حجم(tab));
    }, {
        *nb_ptr = 0;
        av_freep(tab_ptr);
    });
}

خالی *av_dynarray2_جوڑو(خالی **tab_ptr, صحیح *nb_ptr, size_t elem_سائز,
                       ثابت uint8_t *elem_ڈیٹا)
{
    uint8_t *tab_elem_ڈیٹا = تہی;

    FF_DYNARRAY_جوڑو(زیادہ_سے_زیادہ_عدد, elem_سائز, *tab_ptr, *nb_ptr, {
        tab_elem_ڈیٹا = (uint8_t *)*tab_ptr + (*nb_ptr) * elem_سائز;
        اگر (elem_ڈیٹا)
            حافظہ_نقل(tab_elem_ڈیٹا, elem_ڈیٹا, elem_سائز);
        ورنہ
            poison_حافظہ(tab_elem_ڈیٹا, elem_سائز);
    }, {
        av_freep(tab_ptr);
        *nb_ptr = 0;
    });
    واپس tab_elem_ڈیٹا;
}

ساکن خالی fill16(uint8_t *dst, صحیح len)
{
    uint32_t v = AV_RN16(dst - 2);

    v |= v << 16;

    جب (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    جب (len--) {
        *dst = dst[-2];
        dst++;
    }
}

ساکن خالی fill24(uint8_t *dst, صحیح len)
{
#اگر HAVE_BIGENDIAN
    uint32_t v = AV_RB24(dst - 3);
    uint32_t a = v << 8  | v >> 16;
    uint32_t b = v << 16 | v >> 8;
    uint32_t c = v << 24 | v;
#ورنہ
    uint32_t v = AV_RL24(dst - 3);
    uint32_t a = v       | v << 24;
    uint32_t b = v >> 8  | v << 16;
    uint32_t c = v >> 16 | v << 8;
#اگر_ختم

    جب (len >= 12) {
        AV_WN32(dst,     a);
        AV_WN32(dst + 4, b);
        AV_WN32(dst + 8, c);
        dst += 12;
        len -= 12;
    }

    اگر (len >= 4) {
        AV_WN32(dst, a);
        dst += 4;
        len -= 4;
    }

    اگر (len >= 4) {
        AV_WN32(dst, b);
        dst += 4;
        len -= 4;
    }

    جب (len--) {
        *dst = dst[-3];
        dst++;
    }
}

ساکن خالی fill32(uint8_t *dst, صحیح len)
{
    uint32_t v = AV_RN32(dst - 4);

#اگر HAVE_FAST_64_ثنائی_ہندسہ
    uint64_t v2= v + ((uint64_t)v<<32);
    جب (len >= 32) {
        AV_WN64(dst   , v2);
        AV_WN64(dst+ 8, v2);
        AV_WN64(dst+16, v2);
        AV_WN64(dst+24, v2);
        dst += 32;
        len -= 32;
    }
#اگر_ختم

    جب (len >= 4) {
        AV_WN32(dst, v);
        dst += 4;
        len -= 4;
    }

    جب (len--) {
        *dst = dst[-4];
        dst++;
    }
}

خالی av_memcpy_backptr(uint8_t *dst, صحیح عقب, صحیح cnt)
{
    ثابت uint8_t *src = &dst[-عقب];
    اگر (!عقب)
        واپس;

    اگر (عقب == 1) {
        memset(dst, *src, cnt);
    } ورنہ اگر (عقب == 2) {
        fill16(dst, cnt);
    } ورنہ اگر (عقب == 3) {
        fill24(dst, cnt);
    } ورنہ اگر (عقب == 4) {
        fill32(dst, cnt);
    } ورنہ {
        اگر (cnt >= 16) {
            صحیح blocklen = عقب;
            جب (cnt > blocklen) {
                حافظہ_نقل(dst, src, blocklen);
                dst       += blocklen;
                cnt       -= blocklen;
                blocklen <<= 1;
            }
            حافظہ_نقل(dst, src, cnt);
            واپس;
        }
        اگر (cnt >= 8) {
            AV_COPY32U(dst,     src);
            AV_COPY32U(dst + 4, src + 4);
            src += 8;
            dst += 8;
            cnt -= 8;
        }
        اگر (cnt >= 4) {
            AV_COPY32U(dst, src);
            src += 4;
            dst += 4;
            cnt -= 4;
        }
        اگر (cnt >= 2) {
            AV_COPY16U(dst, src);
            src += 2;
            dst += 2;
            cnt -= 2;
        }
        اگر (cnt)
            *dst = *src;
    }
}

خالی *av_fast_realloc(خالی *ptr, غیرعلامتی صحیح *سائز, size_t min_سائز)
{
    size_t max_سائز;

    اگر (min_سائز <= *سائز)
        واپس ptr;

    max_سائز = atomic_load_explicit(&max_alloc_سائز, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_سائز = FFMIN(max_سائز, UINT_MAX);

    اگر (min_سائز > max_سائز) {
        *سائز = 0;
        واپس تہی;
    }

    min_سائز = FFMIN(max_سائز, FFMAX(min_سائز + min_سائز / 16 + 32, min_سائز));

    ptr = av_realloc(ptr, min_سائز);
    /* we could set this to the unmodified min_size but this is safer
     * if the user lost the ptr and uses NULL now
     */
    اگر (!ptr)
        min_سائز = 0;

    *سائز = min_سائز;

    واپس ptr;
}

ساکن اندرونی خالی fast_malloc(خالی *ptr, غیرعلامتی صحیح *سائز, size_t min_سائز, صحیح zero_realloc)
{
    size_t max_سائز;
    خالی *val;

    حافظہ_نقل(&val, ptr, حجم(val));
    اگر (min_سائز <= *سائز) {
        av_assert0(val || !min_سائز);
        واپس;
    }

    max_سائز = atomic_load_explicit(&max_alloc_سائز, memory_order_relaxed);
    /* *size is an unsigned, so the real maximum is <= UINT_MAX. */
    max_سائز = FFMIN(max_سائز, UINT_MAX);

    اگر (min_سائز > max_سائز) {
        av_freep(ptr);
        *سائز = 0;
        واپس;
    }
    min_سائز = FFMIN(max_سائز, FFMAX(min_سائز + min_سائز / 16 + 32, min_سائز));
    av_freep(ptr);
    val = zero_realloc ? av_mallocz(min_سائز) : av_malloc(min_سائز);
    حافظہ_نقل(ptr, &val, حجم(val));
    اگر (!val)
        min_سائز = 0;
    *سائز = min_سائز;
    واپس;
}

خالی av_fast_malloc(خالی *ptr, غیرعلامتی صحیح *سائز, size_t min_سائز)
{
    fast_malloc(ptr, سائز, min_سائز, 0);
}

خالی av_fast_mallocz(خالی *ptr, غیرعلامتی صحیح *سائز, size_t min_سائز)
{
    fast_malloc(ptr, سائز, min_سائز, 1);
}

صحیح av_سائز_mult(size_t a, size_t b, size_t *r)
{
    واپس سائز_mult(a, b, r);
}

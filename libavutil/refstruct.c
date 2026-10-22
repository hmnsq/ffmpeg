/*
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

#ضمن <stdatomic.h>
#ضمن <stdint.h>
#ضمن <string.h>

#ضمن "refstruct.h"
#ضمن "sanitizer.h"

#ضمن "avassert.h"
#ضمن "error.h"
#ضمن "macros.h"
#ضمن "mem.h"
#ضمن "mem_internal.h"
#ضمن "thread.h"

#اگر_تعریف_نشده REFSTRUCT_CHECKED
#اگر_تعریف_نشده ASSERT_LEVEL
#تعریف_کن ASSERT_LEVEL 0
#پایان_اگر
#تعریف_کن REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#پایان_اگر

#إذا REFSTRUCT_CHECKED
#تعریف_کن ff_assert(cond) av_assert0(cond)
#وإلا
#تعریف_کن ff_assert(cond) ((فراغ)0)
#پایان_اگر

#تعریف_کن REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#اگر_تعریف_نشده _MSC_VER
#تعریف_کن REFCOUNT_جابه_جایی FFALIGN(حجم(Ref_شمار), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#وإلا
#تعریف_کن REFCOUNT_جابه_جایی FFALIGN(حجم(Ref_شمار), ALIGN_64)
#پایان_اگر

تعريفنوع بنية Ref_شمار {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    فراغ (*free_cb)(AVRefStructOpaque opaque, فراغ *obj);
    فراغ (*حرر)(فراغ *ref);

#إذا REFSTRUCT_CHECKED
    uint64_t cookie;
#پایان_اگر
} Ref_شمار;

ساكن Ref_شمار *get_refcount(فراغ *obj)
{
    Ref_شمار *ref = (Ref_شمار*)((حرف*)obj - REFCOUNT_جابه_جایی);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    أرجع ref;
}

ساكن ثابت Ref_شمار *cget_refcount(ثابت فراغ *obj)
{
    ثابت Ref_شمار *ref = (ثابت Ref_شمار*)((ثابت حرف*)obj - REFCOUNT_جابه_جایی);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    أرجع ref;
}

ساكن فراغ *get_userdata(فراغ *buf)
{
    أرجع (حرف*)buf + REFCOUNT_جابه_جایی;
}

ساكن فراغ refcount_init(Ref_شمار *ref, AVRefStructOpaque opaque,
                          فراغ (*free_cb)(AVRefStructOpaque opaque, فراغ *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->حرر    = av_free;

#إذا REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#پایان_اگر
}

فراغ *av_refstruct_alloc_ext_c(size_t اندازه, بیعلامت flags, AVRefStructOpaque opaque,
                               فراغ (*free_cb)(AVRefStructOpaque opaque, فراغ *obj))
{
    فراغ *buf, *obj;

    إذا (اندازه > SIZE_MAX - REFCOUNT_جابه_جایی)
        أرجع عدم;
    buf = av_malloc(اندازه + REFCOUNT_جابه_جایی);
    إذا (!buf)
        أرجع عدم;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    إذا (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, اندازه);

    أرجع obj;
}

فراغ av_refstruct_unref(فراغ *objp)
{
    فراغ *obj;
    Ref_شمار *ref;

    کپی_حافظه(&obj, objp, حجم(obj));
    إذا (!obj)
        أرجع;
    کپی_حافظه(objp, &(فراغ *){ عدم }, حجم(obj));

    ref = get_refcount(obj);
    إذا (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        إذا (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->حرر(ref);
    }

    أرجع;
}

فراغ *av_refstruct_ref(فراغ *obj)
{
    Ref_شمار *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    أرجع obj;
}

ثابت فراغ *av_refstruct_ref_c(ثابت فراغ *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_شمار *ref = get_refcount((فراغ*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    أرجع obj;
}

فراغ av_refstruct_replace(فراغ *dstp, ثابت فراغ *src)
{
    ثابت فراغ *dst;
    کپی_حافظه(&dst, dstp, حجم(dst));

    إذا (src == dst)
        أرجع;
    av_refstruct_unref(dstp);
    إذا (src) {
        dst = av_refstruct_ref_c(src);
        کپی_حافظه(dstp, &dst, حجم(dst));
    }
}

صحيح av_refstruct_exclusive(ثابت فراغ *obj)
{
    ثابت Ref_شمار *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    أرجع atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

بنية AVRefStructPool {
    size_t اندازه;
    AVRefStructOpaque opaque;
    صحيح  (*init_cb)(AVRefStructOpaque opaque, فراغ *obj);
    فراغ (*reset_cb)(AVRefStructOpaque opaque, فراغ *obj);
    فراغ (*free_مدخل_cb)(AVRefStructOpaque opaque, فراغ *obj);
    فراغ (*free_cb)(AVRefStructOpaque opaque);

    صحيح uninited;
    بیعلامت مدخل_flags;
    بیعلامت pool_flags;

    /** The number of outstanding entries not in available_entries. */
    atomic_uintptr_t refcount;
    /**
     * This is a linked list of available entries;
     * the RefCount's opaque pointer is used as next pointer
     * for available entries.
     * While the entries are in use, the opaque is a pointer
     * to the corresponding AVRefStructPool.
     */
    Ref_شمار *موجود_entries;
    AVMutex mutex;
};

ساكن فراغ pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    إذا (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

ساكن فراغ pool_free_مدخل(AVRefStructPool *pool, Ref_شمار *ref)
{
    إذا (!pool->free_مدخل_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->اندازه);
    إذا (pool->free_مدخل_cb)
        pool->free_مدخل_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

ساكن فراغ pool_return_مدخل(فراغ *ref_)
{
    Ref_شمار *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_قفل(&pool->mutex);
    إذا (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        إذا (!pool->free_مدخل_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->اندازه);
        ref->opaque.nc = pool->موجود_entries;
        pool->موجود_entries = ref;
        ref = عدم;
    }
    ff_mutex_unlock(&pool->mutex);

    إذا (ref)
        pool_free_مدخل(pool, ref);

    إذا (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ساكن فراغ pool_reset_مدخل(AVRefStructOpaque opaque, فراغ *مدخل)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, مدخل);
}

ساكن صحيح refstruct_pool_get_ext(فراغ *datap, AVRefStructPool *pool)
{
    فراغ *ret = عدم;

    کپی_حافظه(datap, &(فراغ *){ عدم }, حجم(فراغ*));

    ff_mutex_قفل(&pool->mutex);
    ff_assert(!pool->uninited);
    إذا (pool->موجود_entries) {
        Ref_شمار *ref = pool->موجود_entries;
        ret = get_userdata(ref);
        إذا (!pool->free_مدخل_cb)
            FF_ASAN_UNPOISON(ret, pool->اندازه);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        إذا ((pool->مدخل_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_زمان) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_مدخل_cb)
            FF_MEM_UNDEFINED(ret, pool->اندازه);
        pool->موجود_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    إذا (!ret) {
        Ref_شمار *ref;
        ret = av_refstruct_alloc_ext(pool->اندازه, pool->مدخل_flags, pool,
                                     pool->reset_cb ? pool_reset_مدخل : عدم);
        إذا (!ret)
            أرجع AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->حرر = pool_return_مدخل;
        إذا (pool->init_cb) {
            صحيح err = pool->init_cb(pool->opaque, ret);
            إذا (err < 0) {
                إذا (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                إذا (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_مدخل_cb(pool->opaque, ret);
                av_free(ref);
                أرجع err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    إذا (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_زمان)
        memset(ret, 0, pool->اندازه);

    کپی_حافظه(datap, &ret, حجم(ret));

    أرجع 0;
}

فراغ *av_refstruct_pool_get(AVRefStructPool *pool)
{
    فراغ *ret;
    refstruct_pool_get_ext(&ret, pool);
    أرجع ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
ساكن فراغ pool_unref(فراغ *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    إذا (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ساكن فراغ refstruct_pool_uninit(AVRefStructOpaque استفادهنشده, فراغ *obj)
{
    AVRefStructPool *pool = obj;
    Ref_شمار *مدخل;

    ff_mutex_قفل(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    مدخل = pool->موجود_entries;
    pool->موجود_entries = عدم;
    ff_mutex_unlock(&pool->mutex);

    طالما (مدخل) {
        فراغ *بعدی = مدخل->opaque.nc;
        pool_free_مدخل(pool, مدخل);
        مدخل = بعدی;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t اندازه, بیعلامت flags)
{
    أرجع av_refstruct_pool_alloc_ext(اندازه, flags, عدم, عدم, عدم, عدم, عدم);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t اندازه, بیعلامت flags,
                                               AVRefStructOpaque opaque,
                                               صحيح  (*init_cb)(AVRefStructOpaque opaque, فراغ *obj),
                                               فراغ (*reset_cb)(AVRefStructOpaque opaque, فراغ *obj),
                                               فراغ (*free_مدخل_cb)(AVRefStructOpaque opaque, فراغ *obj),
                                               فراغ (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(حجم(*pool), 0, عدم,
                                                   refstruct_pool_uninit);
    صحيح err;

    إذا (!pool)
        أرجع عدم;
    get_refcount(pool)->حرر = pool_unref;

    pool->اندازه          = اندازه;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_مدخل_cb = free_مدخل_cb;
    pool->free_cb       = free_cb;
#تعریف_کن COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->مدخل_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    إذا (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    إذا (!pool->free_مدخل_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    إذا (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_زمان) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->مدخل_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, عدم);
    إذا (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        أرجع عدم;
    }
    أرجع pool;
}

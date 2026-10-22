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

#شامل <stdatomic.h>
#شامل <stdint.h>
#شامل <string.h>

#شامل "refstruct.h"
#شامل "sanitizer.h"

#شامل "avassert.h"
#شامل "error.h"
#شامل "macros.h"
#شامل "mem.h"
#شامل "mem_internal.h"
#شامل "thread.h"

#اگر_غیر_تعریف_شدہ REFSTRUCT_CHECKED
#اگر_غیر_تعریف_شدہ ASSERT_LEVEL
#تعریف_کرو ASSERT_LEVEL 0
#اگر_ختم
#تعریف_کرو REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#اگر_ختم

#اگر REFSTRUCT_CHECKED
#تعریف_کرو ff_assert(cond) av_assert0(cond)
#ورنہ
#تعریف_کرو ff_assert(cond) ((خالی)0)
#اگر_ختم

#تعریف_کرو REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#اگر_غیر_تعریف_شدہ _MSC_VER
#تعریف_کرو REFCOUNT_انحراف FFALIGN(حجم(Ref_گنتی), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#ورنہ
#تعریف_کرو REFCOUNT_انحراف FFALIGN(حجم(Ref_گنتی), ALIGN_64)
#اگر_ختم

قسمتعریف ساخت Ref_گنتی {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    خالی (*free_cb)(AVRefStructOpaque opaque, خالی *obj);
    خالی (*آزاد)(خالی *ref);

#اگر REFSTRUCT_CHECKED
    uint64_t cookie;
#اگر_ختم
} Ref_گنتی;

ساکن Ref_گنتی *get_refcount(خالی *obj)
{
    Ref_گنتی *ref = (Ref_گنتی*)((حرف*)obj - REFCOUNT_انحراف);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    واپس ref;
}

ساکن ثابت Ref_گنتی *cget_refcount(ثابت خالی *obj)
{
    ثابت Ref_گنتی *ref = (ثابت Ref_گنتی*)((ثابت حرف*)obj - REFCOUNT_انحراف);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    واپس ref;
}

ساکن خالی *get_userdata(خالی *buf)
{
    واپس (حرف*)buf + REFCOUNT_انحراف;
}

ساکن خالی refcount_init(Ref_گنتی *ref, AVRefStructOpaque opaque,
                          خالی (*free_cb)(AVRefStructOpaque opaque, خالی *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->آزاد    = av_free;

#اگر REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#اگر_ختم
}

خالی *av_refstruct_alloc_ext_c(size_t سائز, غیرعلامتی flags, AVRefStructOpaque opaque,
                               خالی (*free_cb)(AVRefStructOpaque opaque, خالی *obj))
{
    خالی *buf, *obj;

    اگر (سائز > SIZE_MAX - REFCOUNT_انحراف)
        واپس تہی;
    buf = av_malloc(سائز + REFCOUNT_انحراف);
    اگر (!buf)
        واپس تہی;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    اگر (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, سائز);

    واپس obj;
}

خالی av_refstruct_unref(خالی *objp)
{
    خالی *obj;
    Ref_گنتی *ref;

    حافظہ_نقل(&obj, objp, حجم(obj));
    اگر (!obj)
        واپس;
    حافظہ_نقل(objp, &(خالی *){ تہی }, حجم(obj));

    ref = get_refcount(obj);
    اگر (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        اگر (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->آزاد(ref);
    }

    واپس;
}

خالی *av_refstruct_ref(خالی *obj)
{
    Ref_گنتی *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    واپس obj;
}

ثابت خالی *av_refstruct_ref_c(ثابت خالی *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_گنتی *ref = get_refcount((خالی*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    واپس obj;
}

خالی av_refstruct_replace(خالی *dstp, ثابت خالی *src)
{
    ثابت خالی *dst;
    حافظہ_نقل(&dst, dstp, حجم(dst));

    اگر (src == dst)
        واپس;
    av_refstruct_unref(dstp);
    اگر (src) {
        dst = av_refstruct_ref_c(src);
        حافظہ_نقل(dstp, &dst, حجم(dst));
    }
}

صحیح av_refstruct_exclusive(ثابت خالی *obj)
{
    ثابت Ref_گنتی *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    واپس atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

ساخت AVRefStructPool {
    size_t سائز;
    AVRefStructOpaque opaque;
    صحیح  (*init_cb)(AVRefStructOpaque opaque, خالی *obj);
    خالی (*reset_cb)(AVRefStructOpaque opaque, خالی *obj);
    خالی (*free_اندراج_cb)(AVRefStructOpaque opaque, خالی *obj);
    خالی (*free_cb)(AVRefStructOpaque opaque);

    صحیح uninited;
    غیرعلامتی اندراج_flags;
    غیرعلامتی pool_flags;

    /** The number of outstanding entries not in available_entries. */
    atomic_uintptr_t refcount;
    /**
     * This is a linked list of available entries;
     * the RefCount's opaque pointer is used as next pointer
     * for available entries.
     * While the entries are in use, the opaque is a pointer
     * to the corresponding AVRefStructPool.
     */
    Ref_گنتی *دستیاب_entries;
    AVMutex mutex;
};

ساکن خالی pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    اگر (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

ساکن خالی pool_free_اندراج(AVRefStructPool *pool, Ref_گنتی *ref)
{
    اگر (!pool->free_اندراج_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->سائز);
    اگر (pool->free_اندراج_cb)
        pool->free_اندراج_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

ساکن خالی pool_return_اندراج(خالی *ref_)
{
    Ref_گنتی *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_تالا(&pool->mutex);
    اگر (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        اگر (!pool->free_اندراج_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->سائز);
        ref->opaque.nc = pool->دستیاب_entries;
        pool->دستیاب_entries = ref;
        ref = تہی;
    }
    ff_mutex_unlock(&pool->mutex);

    اگر (ref)
        pool_free_اندراج(pool, ref);

    اگر (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ساکن خالی pool_reset_اندراج(AVRefStructOpaque opaque, خالی *اندراج_2)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, اندراج_2);
}

ساکن صحیح refstruct_pool_get_ext(خالی *datap, AVRefStructPool *pool)
{
    خالی *ret = تہی;

    حافظہ_نقل(datap, &(خالی *){ تہی }, حجم(خالی*));

    ff_mutex_تالا(&pool->mutex);
    ff_assert(!pool->uninited);
    اگر (pool->دستیاب_entries) {
        Ref_گنتی *ref = pool->دستیاب_entries;
        ret = get_userdata(ref);
        اگر (!pool->free_اندراج_cb)
            FF_ASAN_UNPOISON(ret, pool->سائز);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        اگر ((pool->اندراج_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_وقت) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_اندراج_cb)
            FF_MEM_UNDEFINED(ret, pool->سائز);
        pool->دستیاب_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    اگر (!ret) {
        Ref_گنتی *ref;
        ret = av_refstruct_alloc_ext(pool->سائز, pool->اندراج_flags, pool,
                                     pool->reset_cb ? pool_reset_اندراج : تہی);
        اگر (!ret)
            واپس AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->آزاد = pool_return_اندراج;
        اگر (pool->init_cb) {
            صحیح err = pool->init_cb(pool->opaque, ret);
            اگر (err < 0) {
                اگر (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                اگر (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_اندراج_cb(pool->opaque, ret);
                av_free(ref);
                واپس err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    اگر (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_وقت)
        memset(ret, 0, pool->سائز);

    حافظہ_نقل(datap, &ret, حجم(ret));

    واپس 0;
}

خالی *av_refstruct_pool_get(AVRefStructPool *pool)
{
    خالی *ret;
    refstruct_pool_get_ext(&ret, pool);
    واپس ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
ساکن خالی pool_unref(خالی *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    اگر (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ساکن خالی refstruct_pool_uninit(AVRefStructOpaque غیر_مستعمل, خالی *obj)
{
    AVRefStructPool *pool = obj;
    Ref_گنتی *اندراج_2;

    ff_mutex_تالا(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    اندراج_2 = pool->دستیاب_entries;
    pool->دستیاب_entries = تہی;
    ff_mutex_unlock(&pool->mutex);

    جب (اندراج_2) {
        خالی *اگلا = اندراج_2->opaque.nc;
        pool_free_اندراج(pool, اندراج_2);
        اندراج_2 = اگلا;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t سائز, غیرعلامتی flags)
{
    واپس av_refstruct_pool_alloc_ext(سائز, flags, تہی, تہی, تہی, تہی, تہی);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t سائز, غیرعلامتی flags,
                                               AVRefStructOpaque opaque,
                                               صحیح  (*init_cb)(AVRefStructOpaque opaque, خالی *obj),
                                               خالی (*reset_cb)(AVRefStructOpaque opaque, خالی *obj),
                                               خالی (*free_اندراج_cb)(AVRefStructOpaque opaque, خالی *obj),
                                               خالی (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(حجم(*pool), 0, تہی,
                                                   refstruct_pool_uninit);
    صحیح err;

    اگر (!pool)
        واپس تہی;
    get_refcount(pool)->آزاد = pool_unref;

    pool->سائز          = سائز;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_اندراج_cb = free_اندراج_cb;
    pool->free_cb       = free_cb;
#تعریف_کرو COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->اندراج_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    اگر (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    اگر (!pool->free_اندراج_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    اگر (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_وقت) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->اندراج_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, تہی);
    اگر (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        واپس تہی;
    }
    واپس pool;
}

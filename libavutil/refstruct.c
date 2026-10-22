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

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#اگر REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#وگرنه
#define ff_assert(cond) ((تهی)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(اندازه(Ref_شمار), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#وگرنه
#define REFCOUNT_OFFSET FFALIGN(اندازه(Ref_شمار), ALIGN_64)
#endif

تعریفنوع ساختار Ref_شمار {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    تهی (*free_cb)(AVRefStructOpaque opaque, تهی *obj);
    تهی (*آزاد)(تهی *ref);

#اگر REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} Ref_شمار;

ایستا Ref_شمار *get_refcount(تهی *obj)
{
    Ref_شمار *ref = (Ref_شمار*)((نویسه*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    بازگشت ref;
}

ایستا ثابت Ref_شمار *cget_refcount(ثابت تهی *obj)
{
    ثابت Ref_شمار *ref = (ثابت Ref_شمار*)((ثابت نویسه*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    بازگشت ref;
}

ایستا تهی *get_userdata(تهی *buf)
{
    بازگشت (نویسه*)buf + REFCOUNT_OFFSET;
}

ایستا تهی refcount_init(Ref_شمار *ref, AVRefStructOpaque opaque,
                          تهی (*free_cb)(AVRefStructOpaque opaque, تهی *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->آزاد    = av_free;

#اگر REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

تهی *av_refstruct_alloc_ext_c(size_t size, unsigned flags, AVRefStructOpaque opaque,
                               تهی (*free_cb)(AVRefStructOpaque opaque, تهی *obj))
{
    تهی *buf, *obj;

    اگر (size > SIZE_MAX - REFCOUNT_OFFSET)
        بازگشت پوچ;
    buf = av_malloc(size + REFCOUNT_OFFSET);
    اگر (!buf)
        بازگشت پوچ;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    اگر (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, size);

    بازگشت obj;
}

تهی av_refstruct_unref(تهی *objp)
{
    تهی *obj;
    Ref_شمار *ref;

    memcpy(&obj, objp, اندازه(obj));
    اگر (!obj)
        بازگشت;
    memcpy(objp, &(تهی *){ پوچ }, اندازه(obj));

    ref = get_refcount(obj);
    اگر (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        اگر (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->آزاد(ref);
    }

    بازگشت;
}

تهی *av_refstruct_ref(تهی *obj)
{
    Ref_شمار *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    بازگشت obj;
}

ثابت تهی *av_refstruct_ref_c(ثابت تهی *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_شمار *ref = get_refcount((تهی*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    بازگشت obj;
}

تهی av_refstruct_replace(تهی *dstp, ثابت تهی *src)
{
    ثابت تهی *dst;
    memcpy(&dst, dstp, اندازه(dst));

    اگر (src == dst)
        بازگشت;
    av_refstruct_unref(dstp);
    اگر (src) {
        dst = av_refstruct_ref_c(src);
        memcpy(dstp, &dst, اندازه(dst));
    }
}

صحیح av_refstruct_exclusive(ثابت تهی *obj)
{
    ثابت Ref_شمار *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    بازگشت atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

ساختار AVRefStructPool {
    size_t size;
    AVRefStructOpaque opaque;
    صحیح  (*init_cb)(AVRefStructOpaque opaque, تهی *obj);
    تهی (*reset_cb)(AVRefStructOpaque opaque, تهی *obj);
    تهی (*free_entry_cb)(AVRefStructOpaque opaque, تهی *obj);
    تهی (*free_cb)(AVRefStructOpaque opaque);

    صحیح uninited;
    unsigned entry_flags;
    unsigned pool_flags;

    /** The number of outstanding entries not in available_entries. */
    atomic_uintptr_t refcount;
    /**
     * This is a linked list of available entries;
     * the RefCount's opaque pointer is used as next pointer
     * for available entries.
     * While the entries are in use, the opaque is a pointer
     * to the corresponding AVRefStructPool.
     */
    Ref_شمار *available_entries;
    AVMutex mutex;
};

ایستا تهی pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    اگر (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

ایستا تهی pool_free_entry(AVRefStructPool *pool, Ref_شمار *ref)
{
    اگر (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->size);
    اگر (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

ایستا تهی pool_return_entry(تهی *ref_)
{
    Ref_شمار *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    اگر (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        اگر (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->size);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = پوچ;
    }
    ff_mutex_unlock(&pool->mutex);

    اگر (ref)
        pool_free_entry(pool, ref);

    اگر (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ایستا تهی pool_reset_entry(AVRefStructOpaque opaque, تهی *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

ایستا صحیح refstruct_pool_get_ext(تهی *datap, AVRefStructPool *pool)
{
    تهی *ret = پوچ;

    memcpy(datap, &(تهی *){ پوچ }, اندازه(تهی*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    اگر (pool->available_entries) {
        Ref_شمار *ref = pool->available_entries;
        ret = get_userdata(ref);
        اگر (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->size);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        اگر ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->size);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    اگر (!ret) {
        Ref_شمار *ref;
        ret = av_refstruct_alloc_ext(pool->size, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : پوچ);
        اگر (!ret)
            بازگشت AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->آزاد = pool_return_entry;
        اگر (pool->init_cb) {
            صحیح err = pool->init_cb(pool->opaque, ret);
            اگر (err < 0) {
                اگر (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                اگر (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                بازگشت err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    اگر (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        memset(ret, 0, pool->size);

    memcpy(datap, &ret, اندازه(ret));

    بازگشت 0;
}

تهی *av_refstruct_pool_get(AVRefStructPool *pool)
{
    تهی *ret;
    refstruct_pool_get_ext(&ret, pool);
    بازگشت ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
ایستا تهی pool_unref(تهی *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    اگر (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ایستا تهی refstruct_pool_uninit(AVRefStructOpaque unused, تهی *obj)
{
    AVRefStructPool *pool = obj;
    Ref_شمار *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = پوچ;
    ff_mutex_unlock(&pool->mutex);

    وقتی (entry) {
        تهی *next = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = next;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t size, unsigned flags)
{
    بازگشت av_refstruct_pool_alloc_ext(size, flags, پوچ, پوچ, پوچ, پوچ, پوچ);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t size, unsigned flags,
                                               AVRefStructOpaque opaque,
                                               صحیح  (*init_cb)(AVRefStructOpaque opaque, تهی *obj),
                                               تهی (*reset_cb)(AVRefStructOpaque opaque, تهی *obj),
                                               تهی (*free_entry_cb)(AVRefStructOpaque opaque, تهی *obj),
                                               تهی (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(اندازه(*pool), 0, پوچ,
                                                   refstruct_pool_uninit);
    صحیح err;

    اگر (!pool)
        بازگشت پوچ;
    get_refcount(pool)->آزاد = pool_unref;

    pool->size          = size;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    اگر (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    اگر (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    اگر (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, پوچ);
    اگر (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        بازگشت پوچ;
    }
    بازگشت pool;
}

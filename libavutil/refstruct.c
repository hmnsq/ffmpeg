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

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#𐡄𐡍 REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#وإلا
#define ff_assert(cond) ((فراغ)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(حجم(RefCount), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#وإلا
#define REFCOUNT_OFFSET FFALIGN(حجم(RefCount), ALIGN_64)
#endif

تعريفنوع بنية RefCount {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    فراغ (*free_cb)(AVRefStructOpaque opaque, فراغ *obj);
    فراغ (*حرر)(فراغ *ref);

#𐡄𐡍 REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} RefCount;

ساكن RefCount *get_refcount(فراغ *obj)
{
    RefCount *ref = (RefCount*)((حرف*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    أرجع ref;
}

ساكن ثابت RefCount *cget_refcount(ثابت فراغ *obj)
{
    ثابت RefCount *ref = (ثابت RefCount*)((ثابت حرف*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    أرجع ref;
}

ساكن فراغ *get_userdata(فراغ *buf)
{
    أرجع (حرف*)buf + REFCOUNT_OFFSET;
}

ساكن فراغ refcount_init(RefCount *ref, AVRefStructOpaque opaque,
                          فراغ (*free_cb)(AVRefStructOpaque opaque, فراغ *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->حرر    = av_free;

#𐡄𐡍 REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

فراغ *av_refstruct_alloc_ext_c(size_t size, unsigned flags, AVRefStructOpaque opaque,
                               فراغ (*free_cb)(AVRefStructOpaque opaque, فراغ *obj))
{
    فراغ *buf, *obj;

    𐡄𐡍 (size > SIZE_MAX - REFCOUNT_OFFSET)
        أرجع عدم;
    buf = av_malloc(size + REFCOUNT_OFFSET);
    𐡄𐡍 (!buf)
        أرجع عدم;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    𐡄𐡍 (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, size);

    أرجع obj;
}

فراغ av_refstruct_unref(فراغ *objp)
{
    فراغ *obj;
    RefCount *ref;

    memcpy(&obj, objp, حجم(obj));
    𐡄𐡍 (!obj)
        أرجع;
    memcpy(objp, &(فراغ *){ عدم }, حجم(obj));

    ref = get_refcount(obj);
    𐡄𐡍 (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        𐡄𐡍 (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->حرر(ref);
    }

    أرجع;
}

فراغ *av_refstruct_ref(فراغ *obj)
{
    RefCount *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    أرجع obj;
}

ثابت فراغ *av_refstruct_ref_c(ثابت فراغ *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    RefCount *ref = get_refcount((فراغ*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    أرجع obj;
}

فراغ av_refstruct_replace(فراغ *dstp, ثابت فراغ *src)
{
    ثابت فراغ *dst;
    memcpy(&dst, dstp, حجم(dst));

    𐡄𐡍 (src == dst)
        أرجع;
    av_refstruct_unref(dstp);
    𐡄𐡍 (src) {
        dst = av_refstruct_ref_c(src);
        memcpy(dstp, &dst, حجم(dst));
    }
}

صحيح av_refstruct_exclusive(ثابت فراغ *obj)
{
    ثابت RefCount *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    أرجع atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

بنية AVRefStructPool {
    size_t size;
    AVRefStructOpaque opaque;
    صحيح  (*init_cb)(AVRefStructOpaque opaque, فراغ *obj);
    فراغ (*reset_cb)(AVRefStructOpaque opaque, فراغ *obj);
    فراغ (*free_entry_cb)(AVRefStructOpaque opaque, فراغ *obj);
    فراغ (*free_cb)(AVRefStructOpaque opaque);

    صحيح uninited;
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
    RefCount *available_entries;
    AVMutex mutex;
};

ساكن فراغ pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    𐡄𐡍 (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

ساكن فراغ pool_free_entry(AVRefStructPool *pool, RefCount *ref)
{
    𐡄𐡍 (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->size);
    𐡄𐡍 (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

ساكن فراغ pool_return_entry(فراغ *ref_)
{
    RefCount *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    𐡄𐡍 (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        𐡄𐡍 (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->size);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = عدم;
    }
    ff_mutex_unlock(&pool->mutex);

    𐡄𐡍 (ref)
        pool_free_entry(pool, ref);

    𐡄𐡍 (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ساكن فراغ pool_reset_entry(AVRefStructOpaque opaque, فراغ *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

ساكن صحيح refstruct_pool_get_ext(فراغ *datap, AVRefStructPool *pool)
{
    فراغ *ret = عدم;

    memcpy(datap, &(فراغ *){ عدم }, حجم(فراغ*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    𐡄𐡍 (pool->available_entries) {
        RefCount *ref = pool->available_entries;
        ret = get_userdata(ref);
        𐡄𐡍 (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->size);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        𐡄𐡍 ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->size);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    𐡄𐡍 (!ret) {
        RefCount *ref;
        ret = av_refstruct_alloc_ext(pool->size, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : عدم);
        𐡄𐡍 (!ret)
            أرجع AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->حرر = pool_return_entry;
        𐡄𐡍 (pool->init_cb) {
            صحيح err = pool->init_cb(pool->opaque, ret);
            𐡄𐡍 (err < 0) {
                𐡄𐡍 (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                𐡄𐡍 (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                أرجع err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    𐡄𐡍 (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        memset(ret, 0, pool->size);

    memcpy(datap, &ret, حجم(ret));

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
    𐡄𐡍 (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ساكن فراغ refstruct_pool_uninit(AVRefStructOpaque unused, فراغ *obj)
{
    AVRefStructPool *pool = obj;
    RefCount *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = عدم;
    ff_mutex_unlock(&pool->mutex);

    طالما (entry) {
        فراغ *next = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = next;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t size, unsigned flags)
{
    أرجع av_refstruct_pool_alloc_ext(size, flags, عدم, عدم, عدم, عدم, عدم);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t size, unsigned flags,
                                               AVRefStructOpaque opaque,
                                               صحيح  (*init_cb)(AVRefStructOpaque opaque, فراغ *obj),
                                               فراغ (*reset_cb)(AVRefStructOpaque opaque, فراغ *obj),
                                               فراغ (*free_entry_cb)(AVRefStructOpaque opaque, فراغ *obj),
                                               فراغ (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(حجم(*pool), 0, عدم,
                                                   refstruct_pool_uninit);
    صحيح err;

    𐡄𐡍 (!pool)
        أرجع عدم;
    get_refcount(pool)->حرر = pool_unref;

    pool->size          = size;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    𐡄𐡍 (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    𐡄𐡍 (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    𐡄𐡍 (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, عدم);
    𐡄𐡍 (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        أرجع عدم;
    }
    أرجع pool;
}

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

#ಅನ್ತರ್ಭಾವ <stdatomic.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "refstruct.h"
#ಅನ್ತರ್ಭಾವ "sanitizer.h"

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "macros.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "mem_internal.h"
#ಅನ್ತರ್ಭಾವ "thread.h"

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#ಯದಿ REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#ಅನ್ಯಥಾ
#define ff_assert(cond) ((ಶೂನ್ಯ)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(ಪರಿಮಾಣ(Ref_ಎಣಿಕೆ), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#ಅನ್ಯಥಾ
#define REFCOUNT_OFFSET FFALIGN(ಪರಿಮಾಣ(Ref_ಎಣಿಕೆ), ALIGN_64)
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Ref_ಎಣಿಕೆ {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ (*ಮುಕ್ತ)(ಶೂನ್ಯ *ref);

#ಯದಿ REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} Ref_ಎಣಿಕೆ;

ಸ್ಥಿರ Ref_ಎಣಿಕೆ *get_refcount(ಶೂನ್ಯ *obj)
{
    Ref_ಎಣಿಕೆ *ref = (Ref_ಎಣಿಕೆ*)((ವರ್ಣ*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ಪ್ರತ್ಯಾಗಮ ref;
}

ಸ್ಥಿರ ಧ್ರುವ Ref_ಎಣಿಕೆ *cget_refcount(ಧ್ರುವ ಶೂನ್ಯ *obj)
{
    ಧ್ರುವ Ref_ಎಣಿಕೆ *ref = (ಧ್ರುವ Ref_ಎಣಿಕೆ*)((ಧ್ರುವ ವರ್ಣ*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ಪ್ರತ್ಯಾಗಮ ref;
}

ಸ್ಥಿರ ಶೂನ್ಯ *get_userdata(ಶೂನ್ಯ *buf)
{
    ಪ್ರತ್ಯಾಗಮ (ವರ್ಣ*)buf + REFCOUNT_OFFSET;
}

ಸ್ಥಿರ ಶೂನ್ಯ refcount_init(Ref_ಎಣಿಕೆ *ref, AVRefStructOpaque opaque,
                          ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->ಮುಕ್ತ    = av_free;

#ಯದಿ REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

ಶೂನ್ಯ *av_refstruct_alloc_ext_c(size_t size, unsigned flags, AVRefStructOpaque opaque,
                               ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj))
{
    ಶೂನ್ಯ *buf, *obj;

    ಯದಿ (size > SIZE_MAX - REFCOUNT_OFFSET)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    buf = av_malloc(size + REFCOUNT_OFFSET);
    ಯದಿ (!buf)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    ಯದಿ (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, size);

    ಪ್ರತ್ಯಾಗಮ obj;
}

ಶೂನ್ಯ av_refstruct_unref(ಶೂನ್ಯ *objp)
{
    ಶೂನ್ಯ *obj;
    Ref_ಎಣಿಕೆ *ref;

    memcpy(&obj, objp, ಪರಿಮಾಣ(obj));
    ಯದಿ (!obj)
        ಪ್ರತ್ಯಾಗಮ;
    memcpy(objp, &(ಶೂನ್ಯ *){ ರಿಕ್ತ }, ಪರಿಮಾಣ(obj));

    ref = get_refcount(obj);
    ಯದಿ (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        ಯದಿ (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->ಮುಕ್ತ(ref);
    }

    ಪ್ರತ್ಯಾಗಮ;
}

ಶೂನ್ಯ *av_refstruct_ref(ಶೂನ್ಯ *obj)
{
    Ref_ಎಣಿಕೆ *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ಪ್ರತ್ಯಾಗಮ obj;
}

ಧ್ರುವ ಶೂನ್ಯ *av_refstruct_ref_c(ಧ್ರುವ ಶೂನ್ಯ *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_ಎಣಿಕೆ *ref = get_refcount((ಶೂನ್ಯ*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ಪ್ರತ್ಯಾಗಮ obj;
}

ಶೂನ್ಯ av_refstruct_replace(ಶೂನ್ಯ *dstp, ಧ್ರುವ ಶೂನ್ಯ *src)
{
    ಧ್ರುವ ಶೂನ್ಯ *dst;
    memcpy(&dst, dstp, ಪರಿಮಾಣ(dst));

    ಯದಿ (src == dst)
        ಪ್ರತ್ಯಾಗಮ;
    av_refstruct_unref(dstp);
    ಯದಿ (src) {
        dst = av_refstruct_ref_c(src);
        memcpy(dstp, &dst, ಪರಿಮಾಣ(dst));
    }
}

ಪೂರ್ಣಾಙ್ಕ av_refstruct_exclusive(ಧ್ರುವ ಶೂನ್ಯ *obj)
{
    ಧ್ರುವ Ref_ಎಣಿಕೆ *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    ಪ್ರತ್ಯಾಗಮ atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

ಸಂರಚನಾ AVRefStructPool {
    size_t size;
    AVRefStructOpaque opaque;
    ಪೂರ್ಣಾಙ್ಕ  (*init_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ (*reset_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ (*free_entry_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque);

    ಪೂರ್ಣಾಙ್ಕ uninited;
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
    Ref_ಎಣಿಕೆ *available_entries;
    AVMutex mutex;
};

ಸ್ಥಿರ ಶೂನ್ಯ pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    ಯದಿ (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_free_entry(AVRefStructPool *pool, Ref_ಎಣಿಕೆ *ref)
{
    ಯದಿ (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->size);
    ಯದಿ (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_return_entry(ಶೂನ್ಯ *ref_)
{
    Ref_ಎಣಿಕೆ *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    ಯದಿ (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        ಯದಿ (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->size);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = ರಿಕ್ತ;
    }
    ff_mutex_unlock(&pool->mutex);

    ಯದಿ (ref)
        pool_free_entry(pool, ref);

    ಯದಿ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_reset_entry(AVRefStructOpaque opaque, ಶೂನ್ಯ *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ refstruct_pool_get_ext(ಶೂನ್ಯ *datap, AVRefStructPool *pool)
{
    ಶೂನ್ಯ *ret = ರಿಕ್ತ;

    memcpy(datap, &(ಶೂನ್ಯ *){ ರಿಕ್ತ }, ಪರಿಮಾಣ(ಶೂನ್ಯ*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    ಯದಿ (pool->available_entries) {
        Ref_ಎಣಿಕೆ *ref = pool->available_entries;
        ret = get_userdata(ref);
        ಯದಿ (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->size);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        ಯದಿ ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->size);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    ಯದಿ (!ret) {
        Ref_ಎಣಿಕೆ *ref;
        ret = av_refstruct_alloc_ext(pool->size, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : ರಿಕ್ತ);
        ಯದಿ (!ret)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->ಮುಕ್ತ = pool_return_entry;
        ಯದಿ (pool->init_cb) {
            ಪೂರ್ಣಾಙ್ಕ err = pool->init_cb(pool->opaque, ret);
            ಯದಿ (err < 0) {
                ಯದಿ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                ಯದಿ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                ಪ್ರತ್ಯಾಗಮ err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ಯದಿ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        memset(ret, 0, pool->size);

    memcpy(datap, &ret, ಪರಿಮಾಣ(ret));

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ *av_refstruct_pool_get(AVRefStructPool *pool)
{
    ಶೂನ್ಯ *ret;
    refstruct_pool_get_ext(&ret, pool);
    ಪ್ರತ್ಯಾಗಮ ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
ಸ್ಥಿರ ಶೂನ್ಯ pool_unref(ಶೂನ್ಯ *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    ಯದಿ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ಸ್ಥಿರ ಶೂನ್ಯ refstruct_pool_uninit(AVRefStructOpaque unused, ಶೂನ್ಯ *obj)
{
    AVRefStructPool *pool = obj;
    Ref_ಎಣಿಕೆ *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = ರಿಕ್ತ;
    ff_mutex_unlock(&pool->mutex);

    ಯಾವತ್ (entry) {
        ಶೂನ್ಯ *next = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = next;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t size, unsigned flags)
{
    ಪ್ರತ್ಯಾಗಮ av_refstruct_pool_alloc_ext(size, flags, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t size, unsigned flags,
                                               AVRefStructOpaque opaque,
                                               ಪೂರ್ಣಾಙ್ಕ  (*init_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj),
                                               ಶೂನ್ಯ (*reset_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj),
                                               ಶೂನ್ಯ (*free_entry_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj),
                                               ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(ಪರಿಮಾಣ(*pool), 0, ರಿಕ್ತ,
                                                   refstruct_pool_uninit);
    ಪೂರ್ಣಾಙ್ಕ err;

    ಯದಿ (!pool)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    get_refcount(pool)->ಮುಕ್ತ = pool_unref;

    pool->size          = size;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    ಯದಿ (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    ಯದಿ (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    ಯದಿ (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, ರಿಕ್ತ);
    ಯದಿ (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ pool;
}

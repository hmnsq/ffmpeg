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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "refstruct.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sanitizer.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ REFSTRUCT_CHECKED
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ ASSERT_LEVEL
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ASSERT_LEVEL 0
#ਜੇ_ਅੰਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#ਜੇ_ਅੰਤ

#ਜੇ REFSTRUCT_CHECKED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_assert(cond) av_assert0(cond)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ff_assert(cond) ((ਖਾਲੀ)0)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ REFCOUNT_ਵਿੱਥ FFALIGN(ਆਕਾਰ(Ref_ਗਿਣਤੀ), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ REFCOUNT_ਵਿੱਥ FFALIGN(ਆਕਾਰ(Ref_ਗਿਣਤੀ), ALIGN_64)
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Ref_ਗਿਣਤੀ {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    ਖਾਲੀ (*free_cb)(AVRefStructOpaque opaque, ਖਾਲੀ *obj);
    ਖਾਲੀ (*ਮੁਕਤ)(ਖਾਲੀ *ref);

#ਜੇ REFSTRUCT_CHECKED
    uint64_t cookie;
#ਜੇ_ਅੰਤ
} Ref_ਗਿਣਤੀ;

ਸਥਿਰ Ref_ਗਿਣਤੀ *get_refcount(ਖਾਲੀ *obj)
{
    Ref_ਗਿਣਤੀ *ref = (Ref_ਗਿਣਤੀ*)((ਅੱਖਰ*)obj - REFCOUNT_ਵਿੱਥ);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ਵਾਪਸ ref;
}

ਸਥਿਰ ਅਚਲ Ref_ਗਿਣਤੀ *cget_refcount(ਅਚਲ ਖਾਲੀ *obj)
{
    ਅਚਲ Ref_ਗਿਣਤੀ *ref = (ਅਚਲ Ref_ਗਿਣਤੀ*)((ਅਚਲ ਅੱਖਰ*)obj - REFCOUNT_ਵਿੱਥ);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ਵਾਪਸ ref;
}

ਸਥਿਰ ਖਾਲੀ *get_userdata(ਖਾਲੀ *buf)
{
    ਵਾਪਸ (ਅੱਖਰ*)buf + REFCOUNT_ਵਿੱਥ;
}

ਸਥਿਰ ਖਾਲੀ refcount_init(Ref_ਗਿਣਤੀ *ref, AVRefStructOpaque opaque,
                          ਖਾਲੀ (*free_cb)(AVRefStructOpaque opaque, ਖਾਲੀ *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->ਮੁਕਤ    = av_free;

#ਜੇ REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ *av_refstruct_alloc_ext_c(size_t ਮਾਪ, ਬਿਨਾਨਿਸ਼ਾਨੀ flags, AVRefStructOpaque opaque,
                               ਖਾਲੀ (*free_cb)(AVRefStructOpaque opaque, ਖਾਲੀ *obj))
{
    ਖਾਲੀ *buf, *obj;

    ਜੇ (ਮਾਪ > SIZE_MAX - REFCOUNT_ਵਿੱਥ)
        ਵਾਪਸ ਨਿਰਾ;
    buf = av_malloc(ਮਾਪ + REFCOUNT_ਵਿੱਥ);
    ਜੇ (!buf)
        ਵਾਪਸ ਨਿਰਾ;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    ਜੇ (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, ਮਾਪ);

    ਵਾਪਸ obj;
}

ਖਾਲੀ av_refstruct_unref(ਖਾਲੀ *objp)
{
    ਖਾਲੀ *obj;
    Ref_ਗਿਣਤੀ *ref;

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(&obj, objp, ਆਕਾਰ(obj));
    ਜੇ (!obj)
        ਵਾਪਸ;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(objp, &(ਖਾਲੀ *){ ਨਿਰਾ }, ਆਕਾਰ(obj));

    ref = get_refcount(obj);
    ਜੇ (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        ਜੇ (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->ਮੁਕਤ(ref);
    }

    ਵਾਪਸ;
}

ਖਾਲੀ *av_refstruct_ref(ਖਾਲੀ *obj)
{
    Ref_ਗਿਣਤੀ *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ਵਾਪਸ obj;
}

ਅਚਲ ਖਾਲੀ *av_refstruct_ref_c(ਅਚਲ ਖਾਲੀ *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_ਗਿਣਤੀ *ref = get_refcount((ਖਾਲੀ*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ਵਾਪਸ obj;
}

ਖਾਲੀ av_refstruct_replace(ਖਾਲੀ *dstp, ਅਚਲ ਖਾਲੀ *src)
{
    ਅਚਲ ਖਾਲੀ *dst;
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(&dst, dstp, ਆਕਾਰ(dst));

    ਜੇ (src == dst)
        ਵਾਪਸ;
    av_refstruct_unref(dstp);
    ਜੇ (src) {
        dst = av_refstruct_ref_c(src);
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(dstp, &dst, ਆਕਾਰ(dst));
    }
}

ਪੂਰਨ av_refstruct_exclusive(ਅਚਲ ਖਾਲੀ *obj)
{
    ਅਚਲ Ref_ਗਿਣਤੀ *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    ਵਾਪਸ atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

ਬਣਤਰ AVRefStructPool {
    size_t ਮਾਪ;
    AVRefStructOpaque opaque;
    ਪੂਰਨ  (*init_cb)(AVRefStructOpaque opaque, ਖਾਲੀ *obj);
    ਖਾਲੀ (*reset_cb)(AVRefStructOpaque opaque, ਖਾਲੀ *obj);
    ਖਾਲੀ (*free_ਇੰਦਰਾਜ_cb)(AVRefStructOpaque opaque, ਖਾਲੀ *obj);
    ਖਾਲੀ (*free_cb)(AVRefStructOpaque opaque);

    ਪੂਰਨ uninited;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਇੰਦਰਾਜ_flags;
    ਬਿਨਾਨਿਸ਼ਾਨੀ pool_flags;

    /** The number of outstanding entries not in available_entries. */
    atomic_uintptr_t refcount;
    /**
     * This is a linked list of available entries;
     * the RefCount's opaque pointer is used as next pointer
     * for available entries.
     * While the entries are in use, the opaque is a pointer
     * to the corresponding AVRefStructPool.
     */
    Ref_ਗਿਣਤੀ *ਉਪਲਬਧ_entries;
    AVMutex mutex;
};

ਸਥਿਰ ਖਾਲੀ pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    ਜੇ (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

ਸਥਿਰ ਖਾਲੀ pool_free_ਇੰਦਰਾਜ(AVRefStructPool *pool, Ref_ਗਿਣਤੀ *ref)
{
    ਜੇ (!pool->free_ਇੰਦਰਾਜ_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->ਮਾਪ);
    ਜੇ (pool->free_ਇੰਦਰਾਜ_cb)
        pool->free_ਇੰਦਰਾਜ_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

ਸਥਿਰ ਖਾਲੀ pool_return_ਇੰਦਰਾਜ(ਖਾਲੀ *ref_)
{
    Ref_ਗਿਣਤੀ *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_ਤਾਲਾ(&pool->mutex);
    ਜੇ (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        ਜੇ (!pool->free_ਇੰਦਰਾਜ_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->ਮਾਪ);
        ref->opaque.nc = pool->ਉਪਲਬਧ_entries;
        pool->ਉਪਲਬਧ_entries = ref;
        ref = ਨਿਰਾ;
    }
    ff_mutex_unlock(&pool->mutex);

    ਜੇ (ref)
        pool_free_ਇੰਦਰਾਜ(pool, ref);

    ਜੇ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ਸਥਿਰ ਖਾਲੀ pool_reset_ਇੰਦਰਾਜ(AVRefStructOpaque opaque, ਖਾਲੀ *ਇੰਦਰਾਜ)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, ਇੰਦਰਾਜ);
}

ਸਥਿਰ ਪੂਰਨ refstruct_pool_get_ext(ਖਾਲੀ *datap, AVRefStructPool *pool)
{
    ਖਾਲੀ *ret = ਨਿਰਾ;

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(datap, &(ਖਾਲੀ *){ ਨਿਰਾ }, ਆਕਾਰ(ਖਾਲੀ*));

    ff_mutex_ਤਾਲਾ(&pool->mutex);
    ff_assert(!pool->uninited);
    ਜੇ (pool->ਉਪਲਬਧ_entries) {
        Ref_ਗਿਣਤੀ *ref = pool->ਉਪਲਬਧ_entries;
        ret = get_userdata(ref);
        ਜੇ (!pool->free_ਇੰਦਰਾਜ_cb)
            FF_ASAN_UNPOISON(ret, pool->ਮਾਪ);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        ਜੇ ((pool->ਇੰਦਰਾਜ_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_ਸਮਾਂ) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_ਇੰਦਰਾਜ_cb)
            FF_MEM_UNDEFINED(ret, pool->ਮਾਪ);
        pool->ਉਪਲਬਧ_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    ਜੇ (!ret) {
        Ref_ਗਿਣਤੀ *ref;
        ret = av_refstruct_alloc_ext(pool->ਮਾਪ, pool->ਇੰਦਰਾਜ_flags, pool,
                                     pool->reset_cb ? pool_reset_ਇੰਦਰਾਜ : ਨਿਰਾ);
        ਜੇ (!ret)
            ਵਾਪਸ AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->ਮੁਕਤ = pool_return_ਇੰਦਰਾਜ;
        ਜੇ (pool->init_cb) {
            ਪੂਰਨ err = pool->init_cb(pool->opaque, ret);
            ਜੇ (err < 0) {
                ਜੇ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                ਜੇ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_ਇੰਦਰਾਜ_cb(pool->opaque, ret);
                av_free(ref);
                ਵਾਪਸ err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ਜੇ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_ਸਮਾਂ)
        memset(ret, 0, pool->ਮਾਪ);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(datap, &ret, ਆਕਾਰ(ret));

    ਵਾਪਸ 0;
}

ਖਾਲੀ *av_refstruct_pool_get(AVRefStructPool *pool)
{
    ਖਾਲੀ *ret;
    refstruct_pool_get_ext(&ret, pool);
    ਵਾਪਸ ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
ਸਥਿਰ ਖਾਲੀ pool_unref(ਖਾਲੀ *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    ਜੇ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ਸਥਿਰ ਖਾਲੀ refstruct_pool_uninit(AVRefStructOpaque ਅਣਵਰਤਿਆ, ਖਾਲੀ *obj)
{
    AVRefStructPool *pool = obj;
    Ref_ਗਿਣਤੀ *ਇੰਦਰਾਜ;

    ff_mutex_ਤਾਲਾ(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    ਇੰਦਰਾਜ = pool->ਉਪਲਬਧ_entries;
    pool->ਉਪਲਬਧ_entries = ਨਿਰਾ;
    ff_mutex_unlock(&pool->mutex);

    ਜਦੋਂ (ਇੰਦਰਾਜ) {
        ਖਾਲੀ *ਅਗਲਾ = ਇੰਦਰਾਜ->opaque.nc;
        pool_free_ਇੰਦਰਾਜ(pool, ਇੰਦਰਾਜ);
        ਇੰਦਰਾਜ = ਅਗਲਾ;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t ਮਾਪ, ਬਿਨਾਨਿਸ਼ਾਨੀ flags)
{
    ਵਾਪਸ av_refstruct_pool_alloc_ext(ਮਾਪ, flags, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t ਮਾਪ, ਬਿਨਾਨਿਸ਼ਾਨੀ flags,
                                               AVRefStructOpaque opaque,
                                               ਪੂਰਨ  (*init_cb)(AVRefStructOpaque opaque, ਖਾਲੀ *obj),
                                               ਖਾਲੀ (*reset_cb)(AVRefStructOpaque opaque, ਖਾਲੀ *obj),
                                               ਖਾਲੀ (*free_ਇੰਦਰਾਜ_cb)(AVRefStructOpaque opaque, ਖਾਲੀ *obj),
                                               ਖਾਲੀ (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(ਆਕਾਰ(*pool), 0, ਨਿਰਾ,
                                                   refstruct_pool_uninit);
    ਪੂਰਨ err;

    ਜੇ (!pool)
        ਵਾਪਸ ਨਿਰਾ;
    get_refcount(pool)->ਮੁਕਤ = pool_unref;

    pool->ਮਾਪ          = ਮਾਪ;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_ਇੰਦਰਾਜ_cb = free_ਇੰਦਰਾਜ_cb;
    pool->free_cb       = free_cb;
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->ਇੰਦਰਾਜ_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    ਜੇ (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    ਜੇ (!pool->free_ਇੰਦਰਾਜ_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    ਜੇ (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_ਸਮਾਂ) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->ਇੰਦਰਾਜ_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, ਨਿਰਾ);
    ਜੇ (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ pool;
}

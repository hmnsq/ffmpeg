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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ REFSTRUCT_CHECKED
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ ASSERT_LEVEL
#ವ್ಯಾಖ್ಯಾನಿಸು ASSERT_LEVEL 0
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿಸು REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ REFSTRUCT_CHECKED
#ವ್ಯಾಖ್ಯಾನಿಸು ff_assert(cond) av_assert0(cond)
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು ff_assert(cond) ((ಶೂನ್ಯ)0)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ _MSC_VER
#ವ್ಯಾಖ್ಯಾನಿಸು REFCOUNT_ಸ್ಥಾನಾಂತರ FFALIGN(ಗಾತ್ರ(Ref_ಎಣಿಕೆ), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು REFCOUNT_ಸ್ಥಾನಾಂತರ FFALIGN(ಗಾತ್ರ(Ref_ಎಣಿಕೆ), ALIGN_64)
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Ref_ಎಣಿಕೆ {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ (*ಬಿಡುಗಡೆ)(ಶೂನ್ಯ *ref);

#ಆದರೆ REFSTRUCT_CHECKED
    uint64_t cookie;
#ಆದರೆ_ಅಂತ್ಯ
} Ref_ಎಣಿಕೆ;

ಸ್ಥಿರ Ref_ಎಣಿಕೆ *get_refcount(ಶೂನ್ಯ *obj)
{
    Ref_ಎಣಿಕೆ *ref = (Ref_ಎಣಿಕೆ*)((ಅಕ್ಷರ*)obj - REFCOUNT_ಸ್ಥಾನಾಂತರ);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ಹಿಂತಿರುಗಿ ref;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Ref_ಎಣಿಕೆ *cget_refcount(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *obj)
{
    ಸ್ಥಿರಾಂಕ Ref_ಎಣಿಕೆ *ref = (ಸ್ಥಿರಾಂಕ Ref_ಎಣಿಕೆ*)((ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ*)obj - REFCOUNT_ಸ್ಥಾನಾಂತರ);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ಹಿಂತಿರುಗಿ ref;
}

ಸ್ಥಿರ ಶೂನ್ಯ *get_userdata(ಶೂನ್ಯ *buf)
{
    ಹಿಂತಿರುಗಿ (ಅಕ್ಷರ*)buf + REFCOUNT_ಸ್ಥಾನಾಂತರ;
}

ಸ್ಥಿರ ಶೂನ್ಯ refcount_init(Ref_ಎಣಿಕೆ *ref, AVRefStructOpaque opaque,
                          ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->ಬಿಡುಗಡೆ    = av_free;

#ಆದರೆ REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ *av_refstruct_alloc_ext_c(size_t ಗಾತ್ರ_2, ಚಿಹ್ನೆರಹಿತ flags, AVRefStructOpaque opaque,
                               ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj))
{
    ಶೂನ್ಯ *buf, *obj;

    ಆದರೆ (ಗಾತ್ರ_2 > SIZE_MAX - REFCOUNT_ಸ್ಥಾನಾಂತರ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    buf = av_malloc(ಗಾತ್ರ_2 + REFCOUNT_ಸ್ಥಾನಾಂತರ);
    ಆದರೆ (!buf)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    ಆದರೆ (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, ಗಾತ್ರ_2);

    ಹಿಂತಿರುಗಿ obj;
}

ಶೂನ್ಯ av_refstruct_unref(ಶೂನ್ಯ *objp)
{
    ಶೂನ್ಯ *obj;
    Ref_ಎಣಿಕೆ *ref;

    ಸ್ಮರಣೆ_ನಕಲು(&obj, objp, ಗಾತ್ರ(obj));
    ಆದರೆ (!obj)
        ಹಿಂತಿರುಗಿ;
    ಸ್ಮರಣೆ_ನಕಲು(objp, &(ಶೂನ್ಯ *){ ಖಾಲಿ }, ಗಾತ್ರ(obj));

    ref = get_refcount(obj);
    ಆದರೆ (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        ಆದರೆ (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->ಬಿಡುಗಡೆ(ref);
    }

    ಹಿಂತಿರುಗಿ;
}

ಶೂನ್ಯ *av_refstruct_ref(ಶೂನ್ಯ *obj)
{
    Ref_ಎಣಿಕೆ *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ಹಿಂತಿರುಗಿ obj;
}

ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *av_refstruct_ref_c(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_ಎಣಿಕೆ *ref = get_refcount((ಶೂನ್ಯ*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ಹಿಂತಿರುಗಿ obj;
}

ಶೂನ್ಯ av_refstruct_replace(ಶೂನ್ಯ *dstp, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *src)
{
    ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *dst;
    ಸ್ಮರಣೆ_ನಕಲು(&dst, dstp, ಗಾತ್ರ(dst));

    ಆದರೆ (src == dst)
        ಹಿಂತಿರುಗಿ;
    av_refstruct_unref(dstp);
    ಆದರೆ (src) {
        dst = av_refstruct_ref_c(src);
        ಸ್ಮರಣೆ_ನಕಲು(dstp, &dst, ಗಾತ್ರ(dst));
    }
}

ಪೂರ್ಣಾಂಕ av_refstruct_exclusive(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *obj)
{
    ಸ್ಥಿರಾಂಕ Ref_ಎಣಿಕೆ *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    ಹಿಂತಿರುಗಿ atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

ರಚನೆ AVRefStructPool {
    size_t ಗಾತ್ರ_2;
    AVRefStructOpaque opaque;
    ಪೂರ್ಣಾಂಕ  (*init_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ (*reset_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ (*free_ನಮೂದು_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj);
    ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque);

    ಪೂರ್ಣಾಂಕ uninited;
    ಚಿಹ್ನೆರಹಿತ ನಮೂದು_flags;
    ಚಿಹ್ನೆರಹಿತ pool_flags;

    /** The number of outstanding entries not in available_entries. */
    atomic_uintptr_t refcount;
    /**
     * This is a linked list of available entries;
     * the RefCount's opaque pointer is used as next pointer
     * for available entries.
     * While the entries are in use, the opaque is a pointer
     * to the corresponding AVRefStructPool.
     */
    Ref_ಎಣಿಕೆ *ಲಭ್ಯ_entries;
    AVMutex mutex;
};

ಸ್ಥಿರ ಶೂನ್ಯ pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    ಆದರೆ (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_free_ನಮೂದು(AVRefStructPool *pool, Ref_ಎಣಿಕೆ *ref)
{
    ಆದರೆ (!pool->free_ನಮೂದು_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->ಗಾತ್ರ_2);
    ಆದರೆ (pool->free_ನಮೂದು_cb)
        pool->free_ನಮೂದು_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_return_ನಮೂದು(ಶೂನ್ಯ *ref_)
{
    Ref_ಎಣಿಕೆ *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_ಬೀಗ(&pool->mutex);
    ಆದರೆ (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        ಆದರೆ (!pool->free_ನಮೂದು_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->ಗಾತ್ರ_2);
        ref->opaque.nc = pool->ಲಭ್ಯ_entries;
        pool->ಲಭ್ಯ_entries = ref;
        ref = ಖಾಲಿ;
    }
    ff_mutex_unlock(&pool->mutex);

    ಆದರೆ (ref)
        pool_free_ನಮೂದು(pool, ref);

    ಆದರೆ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_reset_ನಮೂದು(AVRefStructOpaque opaque, ಶೂನ್ಯ *ನಮೂದು)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, ನಮೂದು);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ refstruct_pool_get_ext(ಶೂನ್ಯ *datap, AVRefStructPool *pool)
{
    ಶೂನ್ಯ *ret = ಖಾಲಿ;

    ಸ್ಮರಣೆ_ನಕಲು(datap, &(ಶೂನ್ಯ *){ ಖಾಲಿ }, ಗಾತ್ರ(ಶೂನ್ಯ*));

    ff_mutex_ಬೀಗ(&pool->mutex);
    ff_assert(!pool->uninited);
    ಆದರೆ (pool->ಲಭ್ಯ_entries) {
        Ref_ಎಣಿಕೆ *ref = pool->ಲಭ್ಯ_entries;
        ret = get_userdata(ref);
        ಆದರೆ (!pool->free_ನಮೂದು_cb)
            FF_ASAN_UNPOISON(ret, pool->ಗಾತ್ರ_2);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        ಆದರೆ ((pool->ನಮೂದು_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_ಸಮಯ) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_ನಮೂದು_cb)
            FF_MEM_UNDEFINED(ret, pool->ಗಾತ್ರ_2);
        pool->ಲಭ್ಯ_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    ಆದರೆ (!ret) {
        Ref_ಎಣಿಕೆ *ref;
        ret = av_refstruct_alloc_ext(pool->ಗಾತ್ರ_2, pool->ನಮೂದು_flags, pool,
                                     pool->reset_cb ? pool_reset_ನಮೂದು : ಖಾಲಿ);
        ಆದರೆ (!ret)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->ಬಿಡುಗಡೆ = pool_return_ನಮೂದು;
        ಆದರೆ (pool->init_cb) {
            ಪೂರ್ಣಾಂಕ err = pool->init_cb(pool->opaque, ret);
            ಆದರೆ (err < 0) {
                ಆದರೆ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                ಆದರೆ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_ನಮೂದು_cb(pool->opaque, ret);
                av_free(ref);
                ಹಿಂತಿರುಗಿ err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ಆದರೆ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_ಸಮಯ)
        memset(ret, 0, pool->ಗಾತ್ರ_2);

    ಸ್ಮರಣೆ_ನಕಲು(datap, &ret, ಗಾತ್ರ(ret));

    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ *av_refstruct_pool_get(AVRefStructPool *pool)
{
    ಶೂನ್ಯ *ret;
    refstruct_pool_get_ext(&ret, pool);
    ಹಿಂತಿರುಗಿ ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
ಸ್ಥಿರ ಶೂನ್ಯ pool_unref(ಶೂನ್ಯ *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    ಆದರೆ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ಸ್ಥಿರ ಶೂನ್ಯ refstruct_pool_uninit(AVRefStructOpaque ಬಳಸದ, ಶೂನ್ಯ *obj)
{
    AVRefStructPool *pool = obj;
    Ref_ಎಣಿಕೆ *ನಮೂದು;

    ff_mutex_ಬೀಗ(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    ನಮೂದು = pool->ಲಭ್ಯ_entries;
    pool->ಲಭ್ಯ_entries = ಖಾಲಿ;
    ff_mutex_unlock(&pool->mutex);

    ಆಗ (ನಮೂದು) {
        ಶೂನ್ಯ *ಮುಂದಿನ = ನಮೂದು->opaque.nc;
        pool_free_ನಮೂದು(pool, ನಮೂದು);
        ನಮೂದು = ಮುಂದಿನ;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t ಗಾತ್ರ_2, ಚಿಹ್ನೆರಹಿತ flags)
{
    ಹಿಂತಿರುಗಿ av_refstruct_pool_alloc_ext(ಗಾತ್ರ_2, flags, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t ಗಾತ್ರ_2, ಚಿಹ್ನೆರಹಿತ flags,
                                               AVRefStructOpaque opaque,
                                               ಪೂರ್ಣಾಂಕ  (*init_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj),
                                               ಶೂನ್ಯ (*reset_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj),
                                               ಶೂನ್ಯ (*free_ನಮೂದು_cb)(AVRefStructOpaque opaque, ಶೂನ್ಯ *obj),
                                               ಶೂನ್ಯ (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(ಗಾತ್ರ(*pool), 0, ಖಾಲಿ,
                                                   refstruct_pool_uninit);
    ಪೂರ್ಣಾಂಕ err;

    ಆದರೆ (!pool)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    get_refcount(pool)->ಬಿಡುಗಡೆ = pool_unref;

    pool->ಗಾತ್ರ_2          = ಗಾತ್ರ_2;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_ನಮೂದು_cb = free_ನಮೂದು_cb;
    pool->free_cb       = free_cb;
#ವ್ಯಾಖ್ಯಾನಿಸು COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->ನಮೂದು_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    ಆದರೆ (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    ಆದರೆ (!pool->free_ನಮೂದು_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    ಆದರೆ (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_ಸಮಯ) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->ನಮೂದು_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, ಖಾಲಿ);
    ಆದರೆ (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ pool;
}

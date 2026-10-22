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

#అన్తర్భావ <stdatomic.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "refstruct.h"
#అన్తర్భావ "sanitizer.h"

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "macros.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "mem_internal.h"
#అన్తర్భావ "thread.h"

#నిర్వచితం_కాకపోతే REFSTRUCT_CHECKED
#నిర్వచితం_కాకపోతే ASSERT_LEVEL
#నిర్వచించు ASSERT_LEVEL 0
#అయితే_ముగింపు
#నిర్వచించు REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#అయితే_ముగింపు

#ఒకవేళ REFSTRUCT_CHECKED
#నిర్వచించు ff_assert(cond) av_assert0(cond)
#లేకపోతే
#నిర్వచించు ff_assert(cond) ((శూన్య)0)
#అయితే_ముగింపు

#నిర్వచించు REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#నిర్వచితం_కాకపోతే _MSC_VER
#నిర్వచించు REFCOUNT_స్థానభ్రంశం FFALIGN(పరిమాణం(Ref_లెక్క), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#లేకపోతే
#నిర్వచించు REFCOUNT_స్థానభ్రంశం FFALIGN(పరిమాణం(Ref_లెక్క), ALIGN_64)
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం Ref_లెక్క {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    శూన్య (*free_cb)(AVRefStructOpaque opaque, శూన్య *obj);
    శూన్య (*విడుదల)(శూన్య *ref);

#ఒకవేళ REFSTRUCT_CHECKED
    uint64_t cookie;
#అయితే_ముగింపు
} Ref_లెక్క;

స్థిర Ref_లెక్క *get_refcount(శూన్య *obj)
{
    Ref_లెక్క *ref = (Ref_లెక్క*)((అక్షరం*)obj - REFCOUNT_స్థానభ్రంశం);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    తిరిగి ref;
}

స్థిర స్థిరరాశి Ref_లెక్క *cget_refcount(స్థిరరాశి శూన్య *obj)
{
    స్థిరరాశి Ref_లెక్క *ref = (స్థిరరాశి Ref_లెక్క*)((స్థిరరాశి అక్షరం*)obj - REFCOUNT_స్థానభ్రంశం);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    తిరిగి ref;
}

స్థిర శూన్య *get_userdata(శూన్య *buf)
{
    తిరిగి (అక్షరం*)buf + REFCOUNT_స్థానభ్రంశం;
}

స్థిర శూన్య refcount_init(Ref_లెక్క *ref, AVRefStructOpaque opaque,
                          శూన్య (*free_cb)(AVRefStructOpaque opaque, శూన్య *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->విడుదల    = av_free;

#ఒకవేళ REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#అయితే_ముగింపు
}

శూన్య *av_refstruct_alloc_ext_c(size_t కొలత, గుర్తులేని flags, AVRefStructOpaque opaque,
                               శూన్య (*free_cb)(AVRefStructOpaque opaque, శూన్య *obj))
{
    శూన్య *buf, *obj;

    ఒకవేళ (కొలత > SIZE_MAX - REFCOUNT_స్థానభ్రంశం)
        తిరిగి ఖాళీ;
    buf = av_malloc(కొలత + REFCOUNT_స్థానభ్రంశం);
    ఒకవేళ (!buf)
        తిరిగి ఖాళీ;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    ఒకవేళ (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, కొలత);

    తిరిగి obj;
}

శూన్య av_refstruct_unref(శూన్య *objp)
{
    శూన్య *obj;
    Ref_లెక్క *ref;

    జ్ఞాపకం_నకలు(&obj, objp, పరిమాణం(obj));
    ఒకవేళ (!obj)
        తిరిగి;
    జ్ఞాపకం_నకలు(objp, &(శూన్య *){ ఖాళీ }, పరిమాణం(obj));

    ref = get_refcount(obj);
    ఒకవేళ (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        ఒకవేళ (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->విడుదల(ref);
    }

    తిరిగి;
}

శూన్య *av_refstruct_ref(శూన్య *obj)
{
    Ref_లెక్క *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    తిరిగి obj;
}

స్థిరరాశి శూన్య *av_refstruct_ref_c(స్థిరరాశి శూన్య *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_లెక్క *ref = get_refcount((శూన్య*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    తిరిగి obj;
}

శూన్య av_refstruct_replace(శూన్య *dstp, స్థిరరాశి శూన్య *src)
{
    స్థిరరాశి శూన్య *dst;
    జ్ఞాపకం_నకలు(&dst, dstp, పరిమాణం(dst));

    ఒకవేళ (src == dst)
        తిరిగి;
    av_refstruct_unref(dstp);
    ఒకవేళ (src) {
        dst = av_refstruct_ref_c(src);
        జ్ఞాపకం_నకలు(dstp, &dst, పరిమాణం(dst));
    }
}

పూర్ణాంకం av_refstruct_exclusive(స్థిరరాశి శూన్య *obj)
{
    స్థిరరాశి Ref_లెక్క *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    తిరిగి atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

నిర్మాణం AVRefStructPool {
    size_t కొలత;
    AVRefStructOpaque opaque;
    పూర్ణాంకం  (*init_cb)(AVRefStructOpaque opaque, శూన్య *obj);
    శూన్య (*reset_cb)(AVRefStructOpaque opaque, శూన్య *obj);
    శూన్య (*free_నమోదు_cb)(AVRefStructOpaque opaque, శూన్య *obj);
    శూన్య (*free_cb)(AVRefStructOpaque opaque);

    పూర్ణాంకం uninited;
    గుర్తులేని నమోదు_flags;
    గుర్తులేని pool_flags;

    /** The number of outstanding entries not in available_entries. */
    atomic_uintptr_t refcount;
    /**
     * This is a linked list of available entries;
     * the RefCount's opaque pointer is used as next pointer
     * for available entries.
     * While the entries are in use, the opaque is a pointer
     * to the corresponding AVRefStructPool.
     */
    Ref_లెక్క *అందుబాటు_entries;
    AVMutex mutex;
};

స్థిర శూన్య pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    ఒకవేళ (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

స్థిర శూన్య pool_free_నమోదు(AVRefStructPool *pool, Ref_లెక్క *ref)
{
    ఒకవేళ (!pool->free_నమోదు_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->కొలత);
    ఒకవేళ (pool->free_నమోదు_cb)
        pool->free_నమోదు_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

స్థిర శూన్య pool_return_నమోదు(శూన్య *ref_)
{
    Ref_లెక్క *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_తాళం(&pool->mutex);
    ఒకవేళ (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        ఒకవేళ (!pool->free_నమోదు_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->కొలత);
        ref->opaque.nc = pool->అందుబాటు_entries;
        pool->అందుబాటు_entries = ref;
        ref = ఖాళీ;
    }
    ff_mutex_unlock(&pool->mutex);

    ఒకవేళ (ref)
        pool_free_నమోదు(pool, ref);

    ఒకవేళ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

స్థిర శూన్య pool_reset_నమోదు(AVRefStructOpaque opaque, శూన్య *నమోదు_2)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, నమోదు_2);
}

స్థిర పూర్ణాంకం refstruct_pool_get_ext(శూన్య *datap, AVRefStructPool *pool)
{
    శూన్య *ret = ఖాళీ;

    జ్ఞాపకం_నకలు(datap, &(శూన్య *){ ఖాళీ }, పరిమాణం(శూన్య*));

    ff_mutex_తాళం(&pool->mutex);
    ff_assert(!pool->uninited);
    ఒకవేళ (pool->అందుబాటు_entries) {
        Ref_లెక్క *ref = pool->అందుబాటు_entries;
        ret = get_userdata(ref);
        ఒకవేళ (!pool->free_నమోదు_cb)
            FF_ASAN_UNPOISON(ret, pool->కొలత);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        ఒకవేళ ((pool->నమోదు_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_సమయం) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_నమోదు_cb)
            FF_MEM_UNDEFINED(ret, pool->కొలత);
        pool->అందుబాటు_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    ఒకవేళ (!ret) {
        Ref_లెక్క *ref;
        ret = av_refstruct_alloc_ext(pool->కొలత, pool->నమోదు_flags, pool,
                                     pool->reset_cb ? pool_reset_నమోదు : ఖాళీ);
        ఒకవేళ (!ret)
            తిరిగి AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->విడుదల = pool_return_నమోదు;
        ఒకవేళ (pool->init_cb) {
            పూర్ణాంకం err = pool->init_cb(pool->opaque, ret);
            ఒకవేళ (err < 0) {
                ఒకవేళ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                ఒకవేళ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_నమోదు_cb(pool->opaque, ret);
                av_free(ref);
                తిరిగి err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ఒకవేళ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_సమయం)
        memset(ret, 0, pool->కొలత);

    జ్ఞాపకం_నకలు(datap, &ret, పరిమాణం(ret));

    తిరిగి 0;
}

శూన్య *av_refstruct_pool_get(AVRefStructPool *pool)
{
    శూన్య *ret;
    refstruct_pool_get_ext(&ret, pool);
    తిరిగి ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
స్థిర శూన్య pool_unref(శూన్య *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    ఒకవేళ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

స్థిర శూన్య refstruct_pool_uninit(AVRefStructOpaque వాడని, శూన్య *obj)
{
    AVRefStructPool *pool = obj;
    Ref_లెక్క *నమోదు_2;

    ff_mutex_తాళం(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    నమోదు_2 = pool->అందుబాటు_entries;
    pool->అందుబాటు_entries = ఖాళీ;
    ff_mutex_unlock(&pool->mutex);

    అయితే (నమోదు_2) {
        శూన్య *తదుపరి = నమోదు_2->opaque.nc;
        pool_free_నమోదు(pool, నమోదు_2);
        నమోదు_2 = తదుపరి;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t కొలత, గుర్తులేని flags)
{
    తిరిగి av_refstruct_pool_alloc_ext(కొలత, flags, ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t కొలత, గుర్తులేని flags,
                                               AVRefStructOpaque opaque,
                                               పూర్ణాంకం  (*init_cb)(AVRefStructOpaque opaque, శూన్య *obj),
                                               శూన్య (*reset_cb)(AVRefStructOpaque opaque, శూన్య *obj),
                                               శూన్య (*free_నమోదు_cb)(AVRefStructOpaque opaque, శూన్య *obj),
                                               శూన్య (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(పరిమాణం(*pool), 0, ఖాళీ,
                                                   refstruct_pool_uninit);
    పూర్ణాంకం err;

    ఒకవేళ (!pool)
        తిరిగి ఖాళీ;
    get_refcount(pool)->విడుదల = pool_unref;

    pool->కొలత          = కొలత;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_నమోదు_cb = free_నమోదు_cb;
    pool->free_cb       = free_cb;
#నిర్వచించు COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->నమోదు_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    ఒకవేళ (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    ఒకవేళ (!pool->free_నమోదు_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    ఒకవేళ (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_సమయం) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->నమోదు_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, ఖాళీ);
    ఒకవేళ (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        తిరిగి ఖాళీ;
    }
    తిరిగి pool;
}

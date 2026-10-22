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

#અન્તર્ભાવ <stdatomic.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "refstruct.h"
#અન્તર્ભાવ "sanitizer.h"

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "macros.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "mem_internal.h"
#અન્તર્ભાવ "thread.h"

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#જો REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#નહીંતર
#define ff_assert(cond) ((શૂન્ય)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(કદ(Ref_ગણતરી), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#નહીંતર
#define REFCOUNT_OFFSET FFALIGN(કદ(Ref_ગણતરી), ALIGN_64)
#endif

પ્રકારવ્યાખ્યા સંરચના Ref_ગણતરી {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    શૂન્ય (*free_cb)(AVRefStructOpaque opaque, શૂન્ય *obj);
    શૂન્ય (*મુક્ત)(શૂન્ય *ref);

#જો REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} Ref_ગણતરી;

સ્થિર Ref_ગણતરી *get_refcount(શૂન્ય *obj)
{
    Ref_ગણતરી *ref = (Ref_ગણતરી*)((અક્ષર*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    પાછા ref;
}

સ્થિર અચલ Ref_ગણતરી *cget_refcount(અચલ શૂન્ય *obj)
{
    અચલ Ref_ગણતરી *ref = (અચલ Ref_ગણતરી*)((અચલ અક્ષર*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    પાછા ref;
}

સ્થિર શૂન્ય *get_userdata(શૂન્ય *buf)
{
    પાછા (અક્ષર*)buf + REFCOUNT_OFFSET;
}

સ્થિર શૂન્ય refcount_init(Ref_ગણતરી *ref, AVRefStructOpaque opaque,
                          શૂન્ય (*free_cb)(AVRefStructOpaque opaque, શૂન્ય *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->મુક્ત    = av_free;

#જો REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

શૂન્ય *av_refstruct_alloc_ext_c(size_t size, unsigned flags, AVRefStructOpaque opaque,
                               શૂન્ય (*free_cb)(AVRefStructOpaque opaque, શૂન્ય *obj))
{
    શૂન્ય *buf, *obj;

    જો (size > SIZE_MAX - REFCOUNT_OFFSET)
        પાછા ખાલી;
    buf = av_malloc(size + REFCOUNT_OFFSET);
    જો (!buf)
        પાછા ખાલી;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    જો (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, size);

    પાછા obj;
}

શૂન્ય av_refstruct_unref(શૂન્ય *objp)
{
    શૂન્ય *obj;
    Ref_ગણતરી *ref;

    memcpy(&obj, objp, કદ(obj));
    જો (!obj)
        પાછા;
    memcpy(objp, &(શૂન્ય *){ ખાલી }, કદ(obj));

    ref = get_refcount(obj);
    જો (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        જો (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->મુક્ત(ref);
    }

    પાછા;
}

શૂન્ય *av_refstruct_ref(શૂન્ય *obj)
{
    Ref_ગણતરી *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    પાછા obj;
}

અચલ શૂન્ય *av_refstruct_ref_c(અચલ શૂન્ય *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_ગણતરી *ref = get_refcount((શૂન્ય*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    પાછા obj;
}

શૂન્ય av_refstruct_replace(શૂન્ય *dstp, અચલ શૂન્ય *src)
{
    અચલ શૂન્ય *dst;
    memcpy(&dst, dstp, કદ(dst));

    જો (src == dst)
        પાછા;
    av_refstruct_unref(dstp);
    જો (src) {
        dst = av_refstruct_ref_c(src);
        memcpy(dstp, &dst, કદ(dst));
    }
}

પૂર્ણાંક av_refstruct_exclusive(અચલ શૂન્ય *obj)
{
    અચલ Ref_ગણતરી *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    પાછા atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

સંરચના AVRefStructPool {
    size_t size;
    AVRefStructOpaque opaque;
    પૂર્ણાંક  (*init_cb)(AVRefStructOpaque opaque, શૂન્ય *obj);
    શૂન્ય (*reset_cb)(AVRefStructOpaque opaque, શૂન્ય *obj);
    શૂન્ય (*free_entry_cb)(AVRefStructOpaque opaque, શૂન્ય *obj);
    શૂન્ય (*free_cb)(AVRefStructOpaque opaque);

    પૂર્ણાંક uninited;
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
    Ref_ગણતરી *available_entries;
    AVMutex mutex;
};

સ્થિર શૂન્ય pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    જો (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

સ્થિર શૂન્ય pool_free_entry(AVRefStructPool *pool, Ref_ગણતરી *ref)
{
    જો (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->size);
    જો (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

સ્થિર શૂન્ય pool_return_entry(શૂન્ય *ref_)
{
    Ref_ગણતરી *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    જો (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        જો (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->size);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = ખાલી;
    }
    ff_mutex_unlock(&pool->mutex);

    જો (ref)
        pool_free_entry(pool, ref);

    જો (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

સ્થિર શૂન્ય pool_reset_entry(AVRefStructOpaque opaque, શૂન્ય *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

સ્થિર પૂર્ણાંક refstruct_pool_get_ext(શૂન્ય *datap, AVRefStructPool *pool)
{
    શૂન્ય *ret = ખાલી;

    memcpy(datap, &(શૂન્ય *){ ખાલી }, કદ(શૂન્ય*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    જો (pool->available_entries) {
        Ref_ગણતરી *ref = pool->available_entries;
        ret = get_userdata(ref);
        જો (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->size);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        જો ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->size);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    જો (!ret) {
        Ref_ગણતરી *ref;
        ret = av_refstruct_alloc_ext(pool->size, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : ખાલી);
        જો (!ret)
            પાછા AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->મુક્ત = pool_return_entry;
        જો (pool->init_cb) {
            પૂર્ણાંક err = pool->init_cb(pool->opaque, ret);
            જો (err < 0) {
                જો (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                જો (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                પાછા err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    જો (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        memset(ret, 0, pool->size);

    memcpy(datap, &ret, કદ(ret));

    પાછા 0;
}

શૂન્ય *av_refstruct_pool_get(AVRefStructPool *pool)
{
    શૂન્ય *ret;
    refstruct_pool_get_ext(&ret, pool);
    પાછા ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
સ્થિર શૂન્ય pool_unref(શૂન્ય *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    જો (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

સ્થિર શૂન્ય refstruct_pool_uninit(AVRefStructOpaque unused, શૂન્ય *obj)
{
    AVRefStructPool *pool = obj;
    Ref_ગણતરી *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = ખાલી;
    ff_mutex_unlock(&pool->mutex);

    જ્યારે (entry) {
        શૂન્ય *next = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = next;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t size, unsigned flags)
{
    પાછા av_refstruct_pool_alloc_ext(size, flags, ખાલી, ખાલી, ખાલી, ખાલી, ખાલી);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t size, unsigned flags,
                                               AVRefStructOpaque opaque,
                                               પૂર્ણાંક  (*init_cb)(AVRefStructOpaque opaque, શૂન્ય *obj),
                                               શૂન્ય (*reset_cb)(AVRefStructOpaque opaque, શૂન્ય *obj),
                                               શૂન્ય (*free_entry_cb)(AVRefStructOpaque opaque, શૂન્ય *obj),
                                               શૂન્ય (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(કદ(*pool), 0, ખાલી,
                                                   refstruct_pool_uninit);
    પૂર્ણાંક err;

    જો (!pool)
        પાછા ખાલી;
    get_refcount(pool)->મુક્ત = pool_unref;

    pool->size          = size;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    જો (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    જો (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    જો (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, ખાલી);
    જો (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        પાછા ખાલી;
    }
    પાછા pool;
}

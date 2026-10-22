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

#அந்தர்பாவ <stdatomic.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "refstruct.h"
#அந்தர்பாவ "sanitizer.h"

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "macros.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "mem_internal.h"
#அந்தர்பாவ "thread.h"

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#எனில் REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#இல்லையெனில்
#define ff_assert(cond) ((வெறுமை)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(அளவு(Ref_மொத்தம்), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#இல்லையெனில்
#define REFCOUNT_OFFSET FFALIGN(அளவு(Ref_மொத்தம்), ALIGN_64)
#endif

வகைவரை கட்டமைப்பு Ref_மொத்தம் {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    வெறுமை (*free_cb)(AVRefStructOpaque opaque, வெறுமை *obj);
    வெறுமை (*விடுவி)(வெறுமை *ref);

#எனில் REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} Ref_மொத்தம்;

நிலையான Ref_மொத்தம் *get_refcount(வெறுமை *obj)
{
    Ref_மொத்தம் *ref = (Ref_மொத்தம்*)((எழுத்து*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    திரும்பு ref;
}

நிலையான மாறிலி Ref_மொத்தம் *cget_refcount(மாறிலி வெறுமை *obj)
{
    மாறிலி Ref_மொத்தம் *ref = (மாறிலி Ref_மொத்தம்*)((மாறிலி எழுத்து*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    திரும்பு ref;
}

நிலையான வெறுமை *get_userdata(வெறுமை *buf)
{
    திரும்பு (எழுத்து*)buf + REFCOUNT_OFFSET;
}

நிலையான வெறுமை refcount_init(Ref_மொத்தம் *ref, AVRefStructOpaque opaque,
                          வெறுமை (*free_cb)(AVRefStructOpaque opaque, வெறுமை *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->விடுவி    = av_free;

#எனில் REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

வெறுமை *av_refstruct_alloc_ext_c(size_t size, unsigned flags, AVRefStructOpaque opaque,
                               வெறுமை (*free_cb)(AVRefStructOpaque opaque, வெறுமை *obj))
{
    வெறுமை *buf, *obj;

    எனில் (size > SIZE_MAX - REFCOUNT_OFFSET)
        திரும்பு வெற்று;
    buf = av_malloc(size + REFCOUNT_OFFSET);
    எனில் (!buf)
        திரும்பு வெற்று;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    எனில் (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, size);

    திரும்பு obj;
}

வெறுமை av_refstruct_unref(வெறுமை *objp)
{
    வெறுமை *obj;
    Ref_மொத்தம் *ref;

    memcpy(&obj, objp, அளவு(obj));
    எனில் (!obj)
        திரும்பு;
    memcpy(objp, &(வெறுமை *){ வெற்று }, அளவு(obj));

    ref = get_refcount(obj);
    எனில் (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        எனில் (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->விடுவி(ref);
    }

    திரும்பு;
}

வெறுமை *av_refstruct_ref(வெறுமை *obj)
{
    Ref_மொத்தம் *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    திரும்பு obj;
}

மாறிலி வெறுமை *av_refstruct_ref_c(மாறிலி வெறுமை *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_மொத்தம் *ref = get_refcount((வெறுமை*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    திரும்பு obj;
}

வெறுமை av_refstruct_replace(வெறுமை *dstp, மாறிலி வெறுமை *src)
{
    மாறிலி வெறுமை *dst;
    memcpy(&dst, dstp, அளவு(dst));

    எனில் (src == dst)
        திரும்பு;
    av_refstruct_unref(dstp);
    எனில் (src) {
        dst = av_refstruct_ref_c(src);
        memcpy(dstp, &dst, அளவு(dst));
    }
}

முழு av_refstruct_exclusive(மாறிலி வெறுமை *obj)
{
    மாறிலி Ref_மொத்தம் *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    திரும்பு atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

கட்டமைப்பு AVRefStructPool {
    size_t size;
    AVRefStructOpaque opaque;
    முழு  (*init_cb)(AVRefStructOpaque opaque, வெறுமை *obj);
    வெறுமை (*reset_cb)(AVRefStructOpaque opaque, வெறுமை *obj);
    வெறுமை (*free_entry_cb)(AVRefStructOpaque opaque, வெறுமை *obj);
    வெறுமை (*free_cb)(AVRefStructOpaque opaque);

    முழு uninited;
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
    Ref_மொத்தம் *available_entries;
    AVMutex mutex;
};

நிலையான வெறுமை pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    எனில் (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

நிலையான வெறுமை pool_free_entry(AVRefStructPool *pool, Ref_மொத்தம் *ref)
{
    எனில் (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->size);
    எனில் (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

நிலையான வெறுமை pool_return_entry(வெறுமை *ref_)
{
    Ref_மொத்தம் *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    எனில் (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        எனில் (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->size);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = வெற்று;
    }
    ff_mutex_unlock(&pool->mutex);

    எனில் (ref)
        pool_free_entry(pool, ref);

    எனில் (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

நிலையான வெறுமை pool_reset_entry(AVRefStructOpaque opaque, வெறுமை *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

நிலையான முழு refstruct_pool_get_ext(வெறுமை *datap, AVRefStructPool *pool)
{
    வெறுமை *ret = வெற்று;

    memcpy(datap, &(வெறுமை *){ வெற்று }, அளவு(வெறுமை*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    எனில் (pool->available_entries) {
        Ref_மொத்தம் *ref = pool->available_entries;
        ret = get_userdata(ref);
        எனில் (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->size);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        எனில் ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->size);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    எனில் (!ret) {
        Ref_மொத்தம் *ref;
        ret = av_refstruct_alloc_ext(pool->size, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : வெற்று);
        எனில் (!ret)
            திரும்பு AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->விடுவி = pool_return_entry;
        எனில் (pool->init_cb) {
            முழு err = pool->init_cb(pool->opaque, ret);
            எனில் (err < 0) {
                எனில் (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                எனில் (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                திரும்பு err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    எனில் (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        memset(ret, 0, pool->size);

    memcpy(datap, &ret, அளவு(ret));

    திரும்பு 0;
}

வெறுமை *av_refstruct_pool_get(AVRefStructPool *pool)
{
    வெறுமை *ret;
    refstruct_pool_get_ext(&ret, pool);
    திரும்பு ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
நிலையான வெறுமை pool_unref(வெறுமை *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    எனில் (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

நிலையான வெறுமை refstruct_pool_uninit(AVRefStructOpaque unused, வெறுமை *obj)
{
    AVRefStructPool *pool = obj;
    Ref_மொத்தம் *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = வெற்று;
    ff_mutex_unlock(&pool->mutex);

    போது (entry) {
        வெறுமை *next = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = next;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t size, unsigned flags)
{
    திரும்பு av_refstruct_pool_alloc_ext(size, flags, வெற்று, வெற்று, வெற்று, வெற்று, வெற்று);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t size, unsigned flags,
                                               AVRefStructOpaque opaque,
                                               முழு  (*init_cb)(AVRefStructOpaque opaque, வெறுமை *obj),
                                               வெறுமை (*reset_cb)(AVRefStructOpaque opaque, வெறுமை *obj),
                                               வெறுமை (*free_entry_cb)(AVRefStructOpaque opaque, வெறுமை *obj),
                                               வெறுமை (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(அளவு(*pool), 0, வெற்று,
                                                   refstruct_pool_uninit);
    முழு err;

    எனில் (!pool)
        திரும்பு வெற்று;
    get_refcount(pool)->விடுவி = pool_unref;

    pool->size          = size;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    எனில் (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    எனில் (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    எனில் (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, வெற்று);
    எனில் (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        திரும்பு வெற்று;
    }
    திரும்பு pool;
}

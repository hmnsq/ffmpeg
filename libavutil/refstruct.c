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

#অন্তর্ভাব <stdatomic.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "refstruct.h"
#অন্তর্ভাব "sanitizer.h"

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "macros.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "mem_internal.h"
#অন্তর্ভাব "thread.h"

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#যদি REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#অন্যথা
#define ff_assert(cond) ((শূন্য)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(আকার(Ref_গুনতি), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#অন্যথা
#define REFCOUNT_OFFSET FFALIGN(আকার(Ref_গুনতি), ALIGN_64)
#endif

প্রকারলেখ কাঠামো Ref_গুনতি {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    শূন্য (*free_cb)(AVRefStructOpaque opaque, শূন্য *obj);
    শূন্য (*মুক্ত)(শূন্য *ref);

#যদি REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} Ref_গুনতি;

স্থির Ref_গুনতি *get_refcount(শূন্য *obj)
{
    Ref_গুনতি *ref = (Ref_গুনতি*)((অক্ষর*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ফেরত ref;
}

স্থির ধ্রুবক Ref_গুনতি *cget_refcount(ধ্রুবক শূন্য *obj)
{
    ধ্রুবক Ref_গুনতি *ref = (ধ্রুবক Ref_গুনতি*)((ধ্রুবক অক্ষর*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ফেরত ref;
}

স্থির শূন্য *get_userdata(শূন্য *buf)
{
    ফেরত (অক্ষর*)buf + REFCOUNT_OFFSET;
}

স্থির শূন্য refcount_init(Ref_গুনতি *ref, AVRefStructOpaque opaque,
                          শূন্য (*free_cb)(AVRefStructOpaque opaque, শূন্য *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->মুক্ত    = av_free;

#যদি REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

শূন্য *av_refstruct_alloc_ext_c(size_t আকার_2, unsigned flags, AVRefStructOpaque opaque,
                               শূন্য (*free_cb)(AVRefStructOpaque opaque, শূন্য *obj))
{
    শূন্য *buf, *obj;

    যদি (আকার_2 > SIZE_MAX - REFCOUNT_OFFSET)
        ফেরত ফাঁকা;
    buf = av_malloc(আকার_2 + REFCOUNT_OFFSET);
    যদি (!buf)
        ফেরত ফাঁকা;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    যদি (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, আকার_2);

    ফেরত obj;
}

শূন্য av_refstruct_unref(শূন্য *objp)
{
    শূন্য *obj;
    Ref_গুনতি *ref;

    memcpy(&obj, objp, আকার(obj));
    যদি (!obj)
        ফেরত;
    memcpy(objp, &(শূন্য *){ ফাঁকা }, আকার(obj));

    ref = get_refcount(obj);
    যদি (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        যদি (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->মুক্ত(ref);
    }

    ফেরত;
}

শূন্য *av_refstruct_ref(শূন্য *obj)
{
    Ref_গুনতি *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ফেরত obj;
}

ধ্রুবক শূন্য *av_refstruct_ref_c(ধ্রুবক শূন্য *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_গুনতি *ref = get_refcount((শূন্য*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ফেরত obj;
}

শূন্য av_refstruct_replace(শূন্য *dstp, ধ্রুবক শূন্য *src)
{
    ধ্রুবক শূন্য *dst;
    memcpy(&dst, dstp, আকার(dst));

    যদি (src == dst)
        ফেরত;
    av_refstruct_unref(dstp);
    যদি (src) {
        dst = av_refstruct_ref_c(src);
        memcpy(dstp, &dst, আকার(dst));
    }
}

পূর্ণসংখ্যা av_refstruct_exclusive(ধ্রুবক শূন্য *obj)
{
    ধ্রুবক Ref_গুনতি *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    ফেরত atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

কাঠামো AVRefStructPool {
    size_t আকার_2;
    AVRefStructOpaque opaque;
    পূর্ণসংখ্যা  (*init_cb)(AVRefStructOpaque opaque, শূন্য *obj);
    শূন্য (*reset_cb)(AVRefStructOpaque opaque, শূন্য *obj);
    শূন্য (*free_entry_cb)(AVRefStructOpaque opaque, শূন্য *obj);
    শূন্য (*free_cb)(AVRefStructOpaque opaque);

    পূর্ণসংখ্যা uninited;
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
    Ref_গুনতি *available_entries;
    AVMutex mutex;
};

স্থির শূন্য pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    যদি (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

স্থির শূন্য pool_free_entry(AVRefStructPool *pool, Ref_গুনতি *ref)
{
    যদি (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->আকার_2);
    যদি (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

স্থির শূন্য pool_return_entry(শূন্য *ref_)
{
    Ref_গুনতি *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    যদি (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        যদি (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->আকার_2);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = ফাঁকা;
    }
    ff_mutex_unlock(&pool->mutex);

    যদি (ref)
        pool_free_entry(pool, ref);

    যদি (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

স্থির শূন্য pool_reset_entry(AVRefStructOpaque opaque, শূন্য *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

স্থির পূর্ণসংখ্যা refstruct_pool_get_ext(শূন্য *datap, AVRefStructPool *pool)
{
    শূন্য *ret = ফাঁকা;

    memcpy(datap, &(শূন্য *){ ফাঁকা }, আকার(শূন্য*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    যদি (pool->available_entries) {
        Ref_গুনতি *ref = pool->available_entries;
        ret = get_userdata(ref);
        যদি (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->আকার_2);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        যদি ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->আকার_2);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    যদি (!ret) {
        Ref_গুনতি *ref;
        ret = av_refstruct_alloc_ext(pool->আকার_2, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : ফাঁকা);
        যদি (!ret)
            ফেরত AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->মুক্ত = pool_return_entry;
        যদি (pool->init_cb) {
            পূর্ণসংখ্যা err = pool->init_cb(pool->opaque, ret);
            যদি (err < 0) {
                যদি (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                যদি (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                ফেরত err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    যদি (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        memset(ret, 0, pool->আকার_2);

    memcpy(datap, &ret, আকার(ret));

    ফেরত 0;
}

শূন্য *av_refstruct_pool_get(AVRefStructPool *pool)
{
    শূন্য *ret;
    refstruct_pool_get_ext(&ret, pool);
    ফেরত ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
স্থির শূন্য pool_unref(শূন্য *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    যদি (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

স্থির শূন্য refstruct_pool_uninit(AVRefStructOpaque unused, শূন্য *obj)
{
    AVRefStructPool *pool = obj;
    Ref_গুনতি *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = ফাঁকা;
    ff_mutex_unlock(&pool->mutex);

    যখন (entry) {
        শূন্য *পরবর্তী = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = পরবর্তী;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t আকার_2, unsigned flags)
{
    ফেরত av_refstruct_pool_alloc_ext(আকার_2, flags, ফাঁকা, ফাঁকা, ফাঁকা, ফাঁকা, ফাঁকা);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t আকার_2, unsigned flags,
                                               AVRefStructOpaque opaque,
                                               পূর্ণসংখ্যা  (*init_cb)(AVRefStructOpaque opaque, শূন্য *obj),
                                               শূন্য (*reset_cb)(AVRefStructOpaque opaque, শূন্য *obj),
                                               শূন্য (*free_entry_cb)(AVRefStructOpaque opaque, শূন্য *obj),
                                               শূন্য (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(আকার(*pool), 0, ফাঁকা,
                                                   refstruct_pool_uninit);
    পূর্ণসংখ্যা err;

    যদি (!pool)
        ফেরত ফাঁকা;
    get_refcount(pool)->মুক্ত = pool_unref;

    pool->আকার_2          = আকার_2;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    যদি (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    যদি (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    যদি (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, ফাঁকা);
    যদি (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        ফেরত ফাঁকা;
    }
    ফেরত pool;
}

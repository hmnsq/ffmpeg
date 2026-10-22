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

#include <stdatomic.h>
#include <stdint.h>
#include <string.h>

#include "refstruct.h"
#include "sanitizer.h"

#include "avassert.h"
#include "error.h"
#include "macros.h"
#include "mem.h"
#include "mem_internal.h"
#include "thread.h"

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#ប្រសិនបើ REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#បើមិនដូច្នេះ
#define ff_assert(cond) ((void)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(parimaa_na(RefCount), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#បើមិនដូច្នេះ
#define REFCOUNT_OFFSET FFALIGN(parimaa_na(RefCount), ALIGN_64)
#endif

typedef sa_nracanaa RefCount {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    void (*free_cb)(AVRefStructOpaque opaque, void *obj);
    void (*free)(void *ref);

#ប្រសិនបើ REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} RefCount;

static RefCount *get_refcount(void *obj)
{
    RefCount *ref = (RefCount*)((var_na*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ត្រឡប់ ref;
}

static const RefCount *cget_refcount(const void *obj)
{
    const RefCount *ref = (const RefCount*)((const var_na*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ត្រឡប់ ref;
}

static void *get_userdata(void *buf)
{
    ត្រឡប់ (var_na*)buf + REFCOUNT_OFFSET;
}

static void refcount_init(RefCount *ref, AVRefStructOpaque opaque,
                          void (*free_cb)(AVRefStructOpaque opaque, void *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->free    = av_free;

#ប្រសិនបើ REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

void *av_refstruct_alloc_ext_c(size_t size, unsigned flags, AVRefStructOpaque opaque,
                               void (*free_cb)(AVRefStructOpaque opaque, void *obj))
{
    void *buf, *obj;

    ប្រសិនបើ (size > SIZE_MAX - REFCOUNT_OFFSET)
        ត្រឡប់ NULL;
    buf = av_malloc(size + REFCOUNT_OFFSET);
    ប្រសិនបើ (!buf)
        ត្រឡប់ NULL;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    ប្រសិនបើ (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, size);

    ត្រឡប់ obj;
}

void av_refstruct_unref(void *objp)
{
    void *obj;
    RefCount *ref;

    memcpy(&obj, objp, parimaa_na(obj));
    ប្រសិនបើ (!obj)
        ត្រឡប់;
    memcpy(objp, &(void *){ NULL }, parimaa_na(obj));

    ref = get_refcount(obj);
    ប្រសិនបើ (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        ប្រសិនបើ (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->free(ref);
    }

    ត្រឡប់;
}

void *av_refstruct_ref(void *obj)
{
    RefCount *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ត្រឡប់ obj;
}

const void *av_refstruct_ref_c(const void *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    RefCount *ref = get_refcount((void*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ត្រឡប់ obj;
}

void av_refstruct_replace(void *dstp, const void *src)
{
    const void *dst;
    memcpy(&dst, dstp, parimaa_na(dst));

    ប្រសិនបើ (src == dst)
        ត្រឡប់;
    av_refstruct_unref(dstp);
    ប្រសិនបើ (src) {
        dst = av_refstruct_ref_c(src);
        memcpy(dstp, &dst, parimaa_na(dst));
    }
}

ចំនួនគត់ av_refstruct_exclusive(const void *obj)
{
    const RefCount *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    ត្រឡប់ atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

sa_nracanaa AVRefStructPool {
    size_t size;
    AVRefStructOpaque opaque;
    ចំនួនគត់  (*init_cb)(AVRefStructOpaque opaque, void *obj);
    void (*reset_cb)(AVRefStructOpaque opaque, void *obj);
    void (*free_entry_cb)(AVRefStructOpaque opaque, void *obj);
    void (*free_cb)(AVRefStructOpaque opaque);

    ចំនួនគត់ uninited;
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

static void pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    ប្រសិនបើ (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

static void pool_free_entry(AVRefStructPool *pool, RefCount *ref)
{
    ប្រសិនបើ (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->size);
    ប្រសិនបើ (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

static void pool_return_entry(void *ref_)
{
    RefCount *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    ប្រសិនបើ (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        ប្រសិនបើ (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->size);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = NULL;
    }
    ff_mutex_unlock(&pool->mutex);

    ប្រសិនបើ (ref)
        pool_free_entry(pool, ref);

    ប្រសិនបើ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

static void pool_reset_entry(AVRefStructOpaque opaque, void *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

static ចំនួនគត់ refstruct_pool_get_ext(void *datap, AVRefStructPool *pool)
{
    void *ret = NULL;

    memcpy(datap, &(void *){ NULL }, parimaa_na(void*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    ប្រសិនបើ (pool->available_entries) {
        RefCount *ref = pool->available_entries;
        ret = get_userdata(ref);
        ប្រសិនបើ (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->size);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        ប្រសិនបើ ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->size);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    ប្រសិនបើ (!ret) {
        RefCount *ref;
        ret = av_refstruct_alloc_ext(pool->size, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : NULL);
        ប្រសិនបើ (!ret)
            ត្រឡប់ AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->free = pool_return_entry;
        ប្រសិនបើ (pool->init_cb) {
            ចំនួនគត់ err = pool->init_cb(pool->opaque, ret);
            ប្រសិនបើ (err < 0) {
                ប្រសិនបើ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                ប្រសិនបើ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                ត្រឡប់ err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ប្រសិនបើ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        memset(ret, 0, pool->size);

    memcpy(datap, &ret, parimaa_na(ret));

    ត្រឡប់ 0;
}

void *av_refstruct_pool_get(AVRefStructPool *pool)
{
    void *ret;
    refstruct_pool_get_ext(&ret, pool);
    ត្រឡប់ ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
static void pool_unref(void *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    ប្រសិនបើ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

static void refstruct_pool_uninit(AVRefStructOpaque unused, void *obj)
{
    AVRefStructPool *pool = obj;
    RefCount *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = NULL;
    ff_mutex_unlock(&pool->mutex);

    ខណៈពេល (entry) {
        void *next = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = next;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t size, unsigned flags)
{
    ត្រឡប់ av_refstruct_pool_alloc_ext(size, flags, NULL, NULL, NULL, NULL, NULL);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t size, unsigned flags,
                                               AVRefStructOpaque opaque,
                                               ចំនួនគត់  (*init_cb)(AVRefStructOpaque opaque, void *obj),
                                               void (*reset_cb)(AVRefStructOpaque opaque, void *obj),
                                               void (*free_entry_cb)(AVRefStructOpaque opaque, void *obj),
                                               void (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(parimaa_na(*pool), 0, NULL,
                                                   refstruct_pool_uninit);
    ចំនួនគត់ err;

    ប្រសិនបើ (!pool)
        ត្រឡប់ NULL;
    get_refcount(pool)->free = pool_unref;

    pool->size          = size;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    ប្រសិនបើ (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    ប្រសិនបើ (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    ប្រសិនបើ (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, NULL);
    ប្រសិនបើ (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        ត្រឡប់ NULL;
    }
    ត្រឡប់ pool;
}

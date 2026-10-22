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

#അന്തര്ഭാവ <stdatomic.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "refstruct.h"
#അന്തര്ഭാവ "sanitizer.h"

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "macros.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "mem_internal.h"
#അന്തര്ഭാവ "thread.h"

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#എങ്കിൽ REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#അല്ലെങ്കിൽ
#define ff_assert(cond) ((ശൂന്യം)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(വലുപ്പം(Ref_എണ്ണം), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#അല്ലെങ്കിൽ
#define REFCOUNT_OFFSET FFALIGN(വലുപ്പം(Ref_എണ്ണം), ALIGN_64)
#endif

തരനിർവചനം ഘടന Ref_എണ്ണം {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    ശൂന്യം (*free_cb)(AVRefStructOpaque opaque, ശൂന്യം *obj);
    ശൂന്യം (*സ്വതന്ത്രം)(ശൂന്യം *ref);

#എങ്കിൽ REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} Ref_എണ്ണം;

സ്ഥിതം Ref_എണ്ണം *get_refcount(ശൂന്യം *obj)
{
    Ref_എണ്ണം *ref = (Ref_എണ്ണം*)((അക്ഷരം*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    തിരികെ ref;
}

സ്ഥിതം സ്ഥിരം Ref_എണ്ണം *cget_refcount(സ്ഥിരം ശൂന്യം *obj)
{
    സ്ഥിരം Ref_എണ്ണം *ref = (സ്ഥിരം Ref_എണ്ണം*)((സ്ഥിരം അക്ഷരം*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    തിരികെ ref;
}

സ്ഥിതം ശൂന്യം *get_userdata(ശൂന്യം *buf)
{
    തിരികെ (അക്ഷരം*)buf + REFCOUNT_OFFSET;
}

സ്ഥിതം ശൂന്യം refcount_init(Ref_എണ്ണം *ref, AVRefStructOpaque opaque,
                          ശൂന്യം (*free_cb)(AVRefStructOpaque opaque, ശൂന്യം *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->സ്വതന്ത്രം    = av_free;

#എങ്കിൽ REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

ശൂന്യം *av_refstruct_alloc_ext_c(size_t size, unsigned flags, AVRefStructOpaque opaque,
                               ശൂന്യം (*free_cb)(AVRefStructOpaque opaque, ശൂന്യം *obj))
{
    ശൂന്യം *buf, *obj;

    എങ്കിൽ (size > SIZE_MAX - REFCOUNT_OFFSET)
        തിരികെ ശൂന്യ;
    buf = av_malloc(size + REFCOUNT_OFFSET);
    എങ്കിൽ (!buf)
        തിരികെ ശൂന്യ;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    എങ്കിൽ (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, size);

    തിരികെ obj;
}

ശൂന്യം av_refstruct_unref(ശൂന്യം *objp)
{
    ശൂന്യം *obj;
    Ref_എണ്ണം *ref;

    memcpy(&obj, objp, വലുപ്പം(obj));
    എങ്കിൽ (!obj)
        തിരികെ;
    memcpy(objp, &(ശൂന്യം *){ ശൂന്യ }, വലുപ്പം(obj));

    ref = get_refcount(obj);
    എങ്കിൽ (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        എങ്കിൽ (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->സ്വതന്ത്രം(ref);
    }

    തിരികെ;
}

ശൂന്യം *av_refstruct_ref(ശൂന്യം *obj)
{
    Ref_എണ്ണം *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    തിരികെ obj;
}

സ്ഥിരം ശൂന്യം *av_refstruct_ref_c(സ്ഥിരം ശൂന്യം *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_എണ്ണം *ref = get_refcount((ശൂന്യം*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    തിരികെ obj;
}

ശൂന്യം av_refstruct_replace(ശൂന്യം *dstp, സ്ഥിരം ശൂന്യം *src)
{
    സ്ഥിരം ശൂന്യം *dst;
    memcpy(&dst, dstp, വലുപ്പം(dst));

    എങ്കിൽ (src == dst)
        തിരികെ;
    av_refstruct_unref(dstp);
    എങ്കിൽ (src) {
        dst = av_refstruct_ref_c(src);
        memcpy(dstp, &dst, വലുപ്പം(dst));
    }
}

പൂർണ്ണസംഖ്യ av_refstruct_exclusive(സ്ഥിരം ശൂന്യം *obj)
{
    സ്ഥിരം Ref_എണ്ണം *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    തിരികെ atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

ഘടന AVRefStructPool {
    size_t size;
    AVRefStructOpaque opaque;
    പൂർണ്ണസംഖ്യ  (*init_cb)(AVRefStructOpaque opaque, ശൂന്യം *obj);
    ശൂന്യം (*reset_cb)(AVRefStructOpaque opaque, ശൂന്യം *obj);
    ശൂന്യം (*free_entry_cb)(AVRefStructOpaque opaque, ശൂന്യം *obj);
    ശൂന്യം (*free_cb)(AVRefStructOpaque opaque);

    പൂർണ്ണസംഖ്യ uninited;
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
    Ref_എണ്ണം *available_entries;
    AVMutex mutex;
};

സ്ഥിതം ശൂന്യം pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    എങ്കിൽ (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

സ്ഥിതം ശൂന്യം pool_free_entry(AVRefStructPool *pool, Ref_എണ്ണം *ref)
{
    എങ്കിൽ (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->size);
    എങ്കിൽ (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

സ്ഥിതം ശൂന്യം pool_return_entry(ശൂന്യം *ref_)
{
    Ref_എണ്ണം *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    എങ്കിൽ (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        എങ്കിൽ (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->size);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = ശൂന്യ;
    }
    ff_mutex_unlock(&pool->mutex);

    എങ്കിൽ (ref)
        pool_free_entry(pool, ref);

    എങ്കിൽ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

സ്ഥിതം ശൂന്യം pool_reset_entry(AVRefStructOpaque opaque, ശൂന്യം *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ refstruct_pool_get_ext(ശൂന്യം *datap, AVRefStructPool *pool)
{
    ശൂന്യം *ret = ശൂന്യ;

    memcpy(datap, &(ശൂന്യം *){ ശൂന്യ }, വലുപ്പം(ശൂന്യം*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    എങ്കിൽ (pool->available_entries) {
        Ref_എണ്ണം *ref = pool->available_entries;
        ret = get_userdata(ref);
        എങ്കിൽ (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->size);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        എങ്കിൽ ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->size);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    എങ്കിൽ (!ret) {
        Ref_എണ്ണം *ref;
        ret = av_refstruct_alloc_ext(pool->size, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : ശൂന്യ);
        എങ്കിൽ (!ret)
            തിരികെ AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->സ്വതന്ത്രം = pool_return_entry;
        എങ്കിൽ (pool->init_cb) {
            പൂർണ്ണസംഖ്യ err = pool->init_cb(pool->opaque, ret);
            എങ്കിൽ (err < 0) {
                എങ്കിൽ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                എങ്കിൽ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                തിരികെ err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    എങ്കിൽ (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        memset(ret, 0, pool->size);

    memcpy(datap, &ret, വലുപ്പം(ret));

    തിരികെ 0;
}

ശൂന്യം *av_refstruct_pool_get(AVRefStructPool *pool)
{
    ശൂന്യം *ret;
    refstruct_pool_get_ext(&ret, pool);
    തിരികെ ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
സ്ഥിതം ശൂന്യം pool_unref(ശൂന്യം *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    എങ്കിൽ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

സ്ഥിതം ശൂന്യം refstruct_pool_uninit(AVRefStructOpaque unused, ശൂന്യം *obj)
{
    AVRefStructPool *pool = obj;
    Ref_എണ്ണം *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = ശൂന്യ;
    ff_mutex_unlock(&pool->mutex);

    ആകുമ്പോൾ (entry) {
        ശൂന്യം *next = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = next;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t size, unsigned flags)
{
    തിരികെ av_refstruct_pool_alloc_ext(size, flags, ശൂന്യ, ശൂന്യ, ശൂന്യ, ശൂന്യ, ശൂന്യ);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t size, unsigned flags,
                                               AVRefStructOpaque opaque,
                                               പൂർണ്ണസംഖ്യ  (*init_cb)(AVRefStructOpaque opaque, ശൂന്യം *obj),
                                               ശൂന്യം (*reset_cb)(AVRefStructOpaque opaque, ശൂന്യം *obj),
                                               ശൂന്യം (*free_entry_cb)(AVRefStructOpaque opaque, ശൂന്യം *obj),
                                               ശൂന്യം (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(വലുപ്പം(*pool), 0, ശൂന്യ,
                                                   refstruct_pool_uninit);
    പൂർണ്ണസംഖ്യ err;

    എങ്കിൽ (!pool)
        തിരികെ ശൂന്യ;
    get_refcount(pool)->സ്വതന്ത്രം = pool_unref;

    pool->size          = size;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    എങ്കിൽ (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    എങ്കിൽ (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    എങ്കിൽ (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, ശൂന്യ);
    എങ്കിൽ (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        തിരികെ ശൂന്യ;
    }
    തിരികെ pool;
}

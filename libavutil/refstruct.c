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

#ଅନ୍ତର୍ଭାଵ <stdatomic.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "refstruct.h"
#ଅନ୍ତର୍ଭାଵ "sanitizer.h"

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "macros.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "mem_internal.h"
#ଅନ୍ତର୍ଭାଵ "thread.h"

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#ଯଦି REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#ଅନ୍ୟଥା
#define ff_assert(cond) ((ଶୂନ୍ୟ)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(ଆକାର(Ref_ଗଣନା), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#ଅନ୍ୟଥା
#define REFCOUNT_OFFSET FFALIGN(ଆକାର(Ref_ଗଣନା), ALIGN_64)
#endif

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Ref_ଗଣନା {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    ଶୂନ୍ୟ (*free_cb)(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj);
    ଶୂନ୍ୟ (*ମୁକ୍ତ)(ଶୂନ୍ୟ *ref);

#ଯଦି REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} Ref_ଗଣନା;

ସ୍ଥିର Ref_ଗଣନା *get_refcount(ଶୂନ୍ୟ *obj)
{
    Ref_ଗଣନା *ref = (Ref_ଗଣନା*)((ଅକ୍ଷର*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ଫେରନ୍ତୁ ref;
}

ସ୍ଥିର ଅଚଳ Ref_ଗଣନା *cget_refcount(ଅଚଳ ଶୂନ୍ୟ *obj)
{
    ଅଚଳ Ref_ଗଣନା *ref = (ଅଚଳ Ref_ଗଣନା*)((ଅଚଳ ଅକ୍ଷର*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    ଫେରନ୍ତୁ ref;
}

ସ୍ଥିର ଶୂନ୍ୟ *get_userdata(ଶୂନ୍ୟ *buf)
{
    ଫେରନ୍ତୁ (ଅକ୍ଷର*)buf + REFCOUNT_OFFSET;
}

ସ୍ଥିର ଶୂନ୍ୟ refcount_init(Ref_ଗଣନା *ref, AVRefStructOpaque opaque,
                          ଶୂନ୍ୟ (*free_cb)(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->ମୁକ୍ତ    = av_free;

#ଯଦି REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

ଶୂନ୍ୟ *av_refstruct_alloc_ext_c(size_t size, unsigned flags, AVRefStructOpaque opaque,
                               ଶୂନ୍ୟ (*free_cb)(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj))
{
    ଶୂନ୍ୟ *buf, *obj;

    ଯଦି (size > SIZE_MAX - REFCOUNT_OFFSET)
        ଫେରନ୍ତୁ ଖାଲି;
    buf = av_malloc(size + REFCOUNT_OFFSET);
    ଯଦି (!buf)
        ଫେରନ୍ତୁ ଖାଲି;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    ଯଦି (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        memset(obj, 0, size);

    ଫେରନ୍ତୁ obj;
}

ଶୂନ୍ୟ av_refstruct_unref(ଶୂନ୍ୟ *objp)
{
    ଶୂନ୍ୟ *obj;
    Ref_ଗଣନା *ref;

    memcpy(&obj, objp, ଆକାର(obj));
    ଯଦି (!obj)
        ଫେରନ୍ତୁ;
    memcpy(objp, &(ଶୂନ୍ୟ *){ ଖାଲି }, ଆକାର(obj));

    ref = get_refcount(obj);
    ଯଦି (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        ଯଦି (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->ମୁକ୍ତ(ref);
    }

    ଫେରନ୍ତୁ;
}

ଶୂନ୍ୟ *av_refstruct_ref(ଶୂନ୍ୟ *obj)
{
    Ref_ଗଣନା *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ଫେରନ୍ତୁ obj;
}

ଅଚଳ ଶୂନ୍ୟ *av_refstruct_ref_c(ଅଚଳ ଶୂନ୍ୟ *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_ଗଣନା *ref = get_refcount((ଶୂନ୍ୟ*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    ଫେରନ୍ତୁ obj;
}

ଶୂନ୍ୟ av_refstruct_replace(ଶୂନ୍ୟ *dstp, ଅଚଳ ଶୂନ୍ୟ *src)
{
    ଅଚଳ ଶୂନ୍ୟ *dst;
    memcpy(&dst, dstp, ଆକାର(dst));

    ଯଦି (src == dst)
        ଫେରନ୍ତୁ;
    av_refstruct_unref(dstp);
    ଯଦି (src) {
        dst = av_refstruct_ref_c(src);
        memcpy(dstp, &dst, ଆକାର(dst));
    }
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_refstruct_exclusive(ଅଚଳ ଶୂନ୍ୟ *obj)
{
    ଅଚଳ Ref_ଗଣନା *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    ଫେରନ୍ତୁ atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

ସଂରଚନା AVRefStructPool {
    size_t size;
    AVRefStructOpaque opaque;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା  (*init_cb)(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj);
    ଶୂନ୍ୟ (*reset_cb)(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj);
    ଶୂନ୍ୟ (*free_entry_cb)(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj);
    ଶୂନ୍ୟ (*free_cb)(AVRefStructOpaque opaque);

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା uninited;
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
    Ref_ଗଣନା *available_entries;
    AVMutex mutex;
};

ସ୍ଥିର ଶୂନ୍ୟ pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    ଯଦି (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

ସ୍ଥିର ଶୂନ୍ୟ pool_free_entry(AVRefStructPool *pool, Ref_ଗଣନା *ref)
{
    ଯଦି (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->size);
    ଯଦି (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

ସ୍ଥିର ଶୂନ୍ୟ pool_return_entry(ଶୂନ୍ୟ *ref_)
{
    Ref_ଗଣନା *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    ଯଦି (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        ଯଦି (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->size);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = ଖାଲି;
    }
    ff_mutex_unlock(&pool->mutex);

    ଯଦି (ref)
        pool_free_entry(pool, ref);

    ଯଦି (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ସ୍ଥିର ଶୂନ୍ୟ pool_reset_entry(AVRefStructOpaque opaque, ଶୂନ୍ୟ *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା refstruct_pool_get_ext(ଶୂନ୍ୟ *datap, AVRefStructPool *pool)
{
    ଶୂନ୍ୟ *ret = ଖାଲି;

    memcpy(datap, &(ଶୂନ୍ୟ *){ ଖାଲି }, ଆକାର(ଶୂନ୍ୟ*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    ଯଦି (pool->available_entries) {
        Ref_ଗଣନା *ref = pool->available_entries;
        ret = get_userdata(ref);
        ଯଦି (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->size);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        ଯଦି ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->size);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    ଯଦି (!ret) {
        Ref_ଗଣନା *ref;
        ret = av_refstruct_alloc_ext(pool->size, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : ଖାଲି);
        ଯଦି (!ret)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->ମୁକ୍ତ = pool_return_entry;
        ଯଦି (pool->init_cb) {
            ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = pool->init_cb(pool->opaque, ret);
            ଯଦି (err < 0) {
                ଯଦି (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                ଯଦି (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                ଫେରନ୍ତୁ err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ଯଦି (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        memset(ret, 0, pool->size);

    memcpy(datap, &ret, ଆକାର(ret));

    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ *av_refstruct_pool_get(AVRefStructPool *pool)
{
    ଶୂନ୍ୟ *ret;
    refstruct_pool_get_ext(&ret, pool);
    ଫେରନ୍ତୁ ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
ସ୍ଥିର ଶୂନ୍ୟ pool_unref(ଶୂନ୍ୟ *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    ଯଦି (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

ସ୍ଥିର ଶୂନ୍ୟ refstruct_pool_uninit(AVRefStructOpaque unused, ଶୂନ୍ୟ *obj)
{
    AVRefStructPool *pool = obj;
    Ref_ଗଣନା *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = ଖାଲି;
    ff_mutex_unlock(&pool->mutex);

    ଯେତେବେଳେ (entry) {
        ଶୂନ୍ୟ *next = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = next;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t size, unsigned flags)
{
    ଫେରନ୍ତୁ av_refstruct_pool_alloc_ext(size, flags, ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି, ଖାଲି);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t size, unsigned flags,
                                               AVRefStructOpaque opaque,
                                               ପୂର୍ଣ୍ଣସଂଖ୍ୟା  (*init_cb)(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj),
                                               ଶୂନ୍ୟ (*reset_cb)(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj),
                                               ଶୂନ୍ୟ (*free_entry_cb)(AVRefStructOpaque opaque, ଶୂନ୍ୟ *obj),
                                               ଶୂନ୍ୟ (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(ଆକାର(*pool), 0, ଖାଲି,
                                                   refstruct_pool_uninit);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err;

    ଯଦି (!pool)
        ଫେରନ୍ତୁ ଖାଲି;
    get_refcount(pool)->ମୁକ୍ତ = pool_unref;

    pool->size          = size;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    ଯଦି (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    ଯଦି (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    ଯଦି (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, ଖାଲି);
    ଯଦି (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ pool;
}

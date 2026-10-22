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

#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव <stdint.h>
#अन्तर्भाव <string.h>

#अन्तर्भाव "refstruct.h"
#अन्तर्भाव "sanitizer.h"

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "macros.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "mem_internal.h"
#अन्तर्भाव "thread.h"

#ifndef REFSTRUCT_CHECKED
#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL 0
#endif
#define REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#endif

#जर REFSTRUCT_CHECKED
#define ff_assert(cond) av_assert0(cond)
#अन्यथा
#define ff_assert(cond) ((शून्य)0)
#endif

#define REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#ifndef _MSC_VER
#define REFCOUNT_OFFSET FFALIGN(आकार(Ref_मोजणी), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#अन्यथा
#define REFCOUNT_OFFSET FFALIGN(आकार(Ref_मोजणी), ALIGN_64)
#endif

प्रकारव्याख्या संरचना Ref_मोजणी {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    शून्य (*free_cb)(AVRefStructOpaque opaque, शून्य *obj);
    शून्य (*मुक्त)(शून्य *ref);

#जर REFSTRUCT_CHECKED
    uint64_t cookie;
#endif
} Ref_मोजणी;

स्थिर Ref_मोजणी *get_refcount(शून्य *obj)
{
    Ref_मोजणी *ref = (Ref_मोजणी*)((अक्षर*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    परत ref;
}

स्थिर स्थिरांक Ref_मोजणी *cget_refcount(स्थिरांक शून्य *obj)
{
    स्थिरांक Ref_मोजणी *ref = (स्थिरांक Ref_मोजणी*)((स्थिरांक अक्षर*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    परत ref;
}

स्थिर शून्य *get_userdata(शून्य *buf)
{
    परत (अक्षर*)buf + REFCOUNT_OFFSET;
}

स्थिर शून्य refcount_init(Ref_मोजणी *ref, AVRefStructOpaque opaque,
                          शून्य (*free_cb)(AVRefStructOpaque opaque, शून्य *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->मुक्त    = av_free;

#जर REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#endif
}

शून्य *av_refstruct_alloc_ext_c(माप_प्रकार size, अचिन्हित flags, AVRefStructOpaque opaque,
                               शून्य (*free_cb)(AVRefStructOpaque opaque, शून्य *obj))
{
    शून्य *buf, *obj;

    जर (size > SIZE_MAX - REFCOUNT_OFFSET)
        परत रिक्त;
    buf = av_malloc(size + REFCOUNT_OFFSET);
    जर (!buf)
        परत रिक्त;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    जर (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        स_रखो(obj, 0, size);

    परत obj;
}

शून्य av_refstruct_unref(शून्य *objp)
{
    शून्य *obj;
    Ref_मोजणी *ref;

    स_नकल(&obj, objp, आकार(obj));
    जर (!obj)
        परत;
    स_नकल(objp, &(शून्य *){ रिक्त }, आकार(obj));

    ref = get_refcount(obj);
    जर (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        जर (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->मुक्त(ref);
    }

    परत;
}

शून्य *av_refstruct_ref(शून्य *obj)
{
    Ref_मोजणी *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    परत obj;
}

स्थिरांक शून्य *av_refstruct_ref_c(स्थिरांक शून्य *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_मोजणी *ref = get_refcount((शून्य*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    परत obj;
}

शून्य av_refstruct_replace(शून्य *dstp, स्थिरांक शून्य *src)
{
    स्थिरांक शून्य *dst;
    स_नकल(&dst, dstp, आकार(dst));

    जर (src == dst)
        परत;
    av_refstruct_unref(dstp);
    जर (src) {
        dst = av_refstruct_ref_c(src);
        स_नकल(dstp, &dst, आकार(dst));
    }
}

पूर्णांक av_refstruct_exclusive(स्थिरांक शून्य *obj)
{
    स्थिरांक Ref_मोजणी *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    परत atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

संरचना AVRefStructPool {
    माप_प्रकार size;
    AVRefStructOpaque opaque;
    पूर्णांक  (*init_cb)(AVRefStructOpaque opaque, शून्य *obj);
    शून्य (*reset_cb)(AVRefStructOpaque opaque, शून्य *obj);
    शून्य (*free_entry_cb)(AVRefStructOpaque opaque, शून्य *obj);
    शून्य (*free_cb)(AVRefStructOpaque opaque);

    पूर्णांक uninited;
    अचिन्हित entry_flags;
    अचिन्हित pool_flags;

    /** The number of outstanding entries not in available_entries. */
    atomic_uintptr_t refcount;
    /**
     * This is a linked list of available entries;
     * the RefCount's opaque pointer is used as next pointer
     * for available entries.
     * While the entries are in use, the opaque is a pointer
     * to the corresponding AVRefStructPool.
     */
    Ref_मोजणी *available_entries;
    AVMutex mutex;
};

स्थिर शून्य pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    जर (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

स्थिर शून्य pool_free_entry(AVRefStructPool *pool, Ref_मोजणी *ref)
{
    जर (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->size);
    जर (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

स्थिर शून्य pool_return_entry(शून्य *ref_)
{
    Ref_मोजणी *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    जर (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        जर (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->size);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = रिक्त;
    }
    ff_mutex_unlock(&pool->mutex);

    जर (ref)
        pool_free_entry(pool, ref);

    जर (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

स्थिर शून्य pool_reset_entry(AVRefStructOpaque opaque, शून्य *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

स्थिर पूर्णांक refstruct_pool_get_ext(शून्य *datap, AVRefStructPool *pool)
{
    शून्य *ret = रिक्त;

    स_नकल(datap, &(शून्य *){ रिक्त }, आकार(शून्य*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    जर (pool->available_entries) {
        Ref_मोजणी *ref = pool->available_entries;
        ret = get_userdata(ref);
        जर (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->size);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        जर ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->size);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    जर (!ret) {
        Ref_मोजणी *ref;
        ret = av_refstruct_alloc_ext(pool->size, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : रिक्त);
        जर (!ret)
            परत AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->मुक्त = pool_return_entry;
        जर (pool->init_cb) {
            पूर्णांक err = pool->init_cb(pool->opaque, ret);
            जर (err < 0) {
                जर (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                जर (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                परत err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    जर (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        स_रखो(ret, 0, pool->size);

    स_नकल(datap, &ret, आकार(ret));

    परत 0;
}

शून्य *av_refstruct_pool_get(AVRefStructPool *pool)
{
    शून्य *ret;
    refstruct_pool_get_ext(&ret, pool);
    परत ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
स्थिर शून्य pool_unref(शून्य *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    जर (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

स्थिर शून्य refstruct_pool_uninit(AVRefStructOpaque unused, शून्य *obj)
{
    AVRefStructPool *pool = obj;
    Ref_मोजणी *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = रिक्त;
    ff_mutex_unlock(&pool->mutex);

    पर्यंत (entry) {
        शून्य *next = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = next;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(माप_प्रकार size, अचिन्हित flags)
{
    परत av_refstruct_pool_alloc_ext(size, flags, रिक्त, रिक्त, रिक्त, रिक्त, रिक्त);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(माप_प्रकार size, अचिन्हित flags,
                                               AVRefStructOpaque opaque,
                                               पूर्णांक  (*init_cb)(AVRefStructOpaque opaque, शून्य *obj),
                                               शून्य (*reset_cb)(AVRefStructOpaque opaque, शून्य *obj),
                                               शून्य (*free_entry_cb)(AVRefStructOpaque opaque, शून्य *obj),
                                               शून्य (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(आकार(*pool), 0, रिक्त,
                                                   refstruct_pool_uninit);
    पूर्णांक err;

    जर (!pool)
        परत रिक्त;
    get_refcount(pool)->मुक्त = pool_unref;

    pool->size          = size;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#define COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    जर (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    जर (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    जर (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, रिक्त);
    जर (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        परत रिक्त;
    }
    परत pool;
}

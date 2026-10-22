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

#यदि_अपरिभाषितम् REFSTRUCT_CHECKED
#यदि_अपरिभाषितम् ASSERT_LEVEL
#परिभाषय ASSERT_LEVEL 0
#यदि_अन्तः
#परिभाषय REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#यदि_अन्तः

#यदि REFSTRUCT_CHECKED
#परिभाषय ff_assert(cond) av_assert0(cond)
#अन्यथा
#परिभाषय ff_assert(cond) ((शून्य)0)
#यदि_अन्तः

#परिभाषय REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#यदि_अपरिभाषितम् _MSC_VER
#परिभाषय REFCOUNT_विस्थापनम् FFALIGN(परिमाण(Ref_गणनम्), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#अन्यथा
#परिभाषय REFCOUNT_विस्थापनम् FFALIGN(परिमाण(Ref_गणनम्), ALIGN_64)
#यदि_अन्तः

प्रकारनिर्देश संरचना Ref_गणनम् {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    शून्य (*free_cb)(AVRefStructOpaque opaque, शून्य *obj);
    शून्य (*मुक्त)(शून्य *ref);

#यदि REFSTRUCT_CHECKED
    uint64_t cookie;
#यदि_अन्तः
} Ref_गणनम्;

स्थिर Ref_गणनम् *get_refcount(शून्य *obj)
{
    Ref_गणनम् *ref = (Ref_गणनम्*)((वर्ण*)obj - REFCOUNT_विस्थापनम्);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    प्रत्यागम ref;
}

स्थिर ध्रुव Ref_गणनम् *cget_refcount(ध्रुव शून्य *obj)
{
    ध्रुव Ref_गणनम् *ref = (ध्रुव Ref_गणनम्*)((ध्रुव वर्ण*)obj - REFCOUNT_विस्थापनम्);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    प्रत्यागम ref;
}

स्थिर शून्य *get_userdata(शून्य *buf)
{
    प्रत्यागम (वर्ण*)buf + REFCOUNT_विस्थापनम्;
}

स्थिर शून्य refcount_init(Ref_गणनम् *ref, AVRefStructOpaque opaque,
                          शून्य (*free_cb)(AVRefStructOpaque opaque, शून्य *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->मुक्त    = av_free;

#यदि REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#यदि_अन्तः
}

शून्य *av_refstruct_alloc_ext_c(size_t आकार, अचिह्नित flags, AVRefStructOpaque opaque,
                               शून्य (*free_cb)(AVRefStructOpaque opaque, शून्य *obj))
{
    शून्य *buf, *obj;

    यदि (आकार > SIZE_MAX - REFCOUNT_विस्थापनम्)
        प्रत्यागम रिक्त;
    buf = av_malloc(आकार + REFCOUNT_विस्थापनम्);
    यदि (!buf)
        प्रत्यागम रिक्त;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    यदि (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        स्मृतिं_पूरय(obj, 0, आकार);

    प्रत्यागम obj;
}

शून्य av_refstruct_unref(शून्य *objp)
{
    शून्य *obj;
    Ref_गणनम् *ref;

    स्मृतिं_प्रतिलिख(&obj, objp, परिमाण(obj));
    यदि (!obj)
        प्रत्यागम;
    स्मृतिं_प्रतिलिख(objp, &(शून्य *){ रिक्त }, परिमाण(obj));

    ref = get_refcount(obj);
    यदि (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        यदि (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->मुक्त(ref);
    }

    प्रत्यागम;
}

शून्य *av_refstruct_ref(शून्य *obj)
{
    Ref_गणनम् *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    प्रत्यागम obj;
}

ध्रुव शून्य *av_refstruct_ref_c(ध्रुव शून्य *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_गणनम् *ref = get_refcount((शून्य*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    प्रत्यागम obj;
}

शून्य av_refstruct_replace(शून्य *dstp, ध्रुव शून्य *src)
{
    ध्रुव शून्य *dst;
    स्मृतिं_प्रतिलिख(&dst, dstp, परिमाण(dst));

    यदि (src == dst)
        प्रत्यागम;
    av_refstruct_unref(dstp);
    यदि (src) {
        dst = av_refstruct_ref_c(src);
        स्मृतिं_प्रतिलिख(dstp, &dst, परिमाण(dst));
    }
}

पूर्णाङ्क av_refstruct_exclusive(ध्रुव शून्य *obj)
{
    ध्रुव Ref_गणनम् *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    प्रत्यागम atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

संरचना AVRefStructPool {
    size_t आकार;
    AVRefStructOpaque opaque;
    पूर्णाङ्क  (*init_cb)(AVRefStructOpaque opaque, शून्य *obj);
    शून्य (*reset_cb)(AVRefStructOpaque opaque, शून्य *obj);
    शून्य (*free_प्रविष्टिः_cb)(AVRefStructOpaque opaque, शून्य *obj);
    शून्य (*free_cb)(AVRefStructOpaque opaque);

    पूर्णाङ्क uninited;
    अचिह्नित प्रविष्टिः_flags;
    अचिह्नित pool_flags;

    /** The number of outstanding entries not in available_entries. */
    atomic_uintptr_t refcount;
    /**
     * This is a linked list of available entries;
     * the RefCount's opaque pointer is used as next pointer
     * for available entries.
     * While the entries are in use, the opaque is a pointer
     * to the corresponding AVRefStructPool.
     */
    Ref_गणनम् *उपलब्धम्_entries;
    AVMutex mutex;
};

स्थिर शून्य pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    यदि (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

स्थिर शून्य pool_free_प्रविष्टिः(AVRefStructPool *pool, Ref_गणनम् *ref)
{
    यदि (!pool->free_प्रविष्टिः_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->आकार);
    यदि (pool->free_प्रविष्टिः_cb)
        pool->free_प्रविष्टिः_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

स्थिर शून्य pool_return_प्रविष्टिः(शून्य *ref_)
{
    Ref_गणनम् *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_तालकम्(&pool->mutex);
    यदि (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        यदि (!pool->free_प्रविष्टिः_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->आकार);
        ref->opaque.nc = pool->उपलब्धम्_entries;
        pool->उपलब्धम्_entries = ref;
        ref = रिक्त;
    }
    ff_mutex_unlock(&pool->mutex);

    यदि (ref)
        pool_free_प्रविष्टिः(pool, ref);

    यदि (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

स्थिर शून्य pool_reset_प्रविष्टिः(AVRefStructOpaque opaque, शून्य *प्रविष्टिः)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, प्रविष्टिः);
}

स्थिर पूर्णाङ्क refstruct_pool_get_ext(शून्य *datap, AVRefStructPool *pool)
{
    शून्य *ret = रिक्त;

    स्मृतिं_प्रतिलिख(datap, &(शून्य *){ रिक्त }, परिमाण(शून्य*));

    ff_mutex_तालकम्(&pool->mutex);
    ff_assert(!pool->uninited);
    यदि (pool->उपलब्धम्_entries) {
        Ref_गणनम् *ref = pool->उपलब्धम्_entries;
        ret = get_userdata(ref);
        यदि (!pool->free_प्रविष्टिः_cb)
            FF_ASAN_UNPOISON(ret, pool->आकार);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        यदि ((pool->प्रविष्टिः_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_प्रविष्टिः_cb)
            FF_MEM_UNDEFINED(ret, pool->आकार);
        pool->उपलब्धम्_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    यदि (!ret) {
        Ref_गणनम् *ref;
        ret = av_refstruct_alloc_ext(pool->आकार, pool->प्रविष्टिः_flags, pool,
                                     pool->reset_cb ? pool_reset_प्रविष्टिः : रिक्त);
        यदि (!ret)
            प्रत्यागम AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->मुक्त = pool_return_प्रविष्टिः;
        यदि (pool->init_cb) {
            पूर्णाङ्क err = pool->init_cb(pool->opaque, ret);
            यदि (err < 0) {
                यदि (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                यदि (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_प्रविष्टिः_cb(pool->opaque, ret);
                av_free(ref);
                प्रत्यागम err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    यदि (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        स्मृतिं_पूरय(ret, 0, pool->आकार);

    स्मृतिं_प्रतिलिख(datap, &ret, परिमाण(ret));

    प्रत्यागम 0;
}

शून्य *av_refstruct_pool_get(AVRefStructPool *pool)
{
    शून्य *ret;
    refstruct_pool_get_ext(&ret, pool);
    प्रत्यागम ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
स्थिर शून्य pool_unref(शून्य *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    यदि (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

स्थिर शून्य refstruct_pool_uninit(AVRefStructOpaque अप्रयुक्तम्, शून्य *obj)
{
    AVRefStructPool *pool = obj;
    Ref_गणनम् *प्रविष्टिः;

    ff_mutex_तालकम्(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    प्रविष्टिः = pool->उपलब्धम्_entries;
    pool->उपलब्धम्_entries = रिक्त;
    ff_mutex_unlock(&pool->mutex);

    यावत् (प्रविष्टिः) {
        शून्य *अग्र = प्रविष्टिः->opaque.nc;
        pool_free_प्रविष्टिः(pool, प्रविष्टिः);
        प्रविष्टिः = अग्र;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(size_t आकार, अचिह्नित flags)
{
    प्रत्यागम av_refstruct_pool_alloc_ext(आकार, flags, रिक्त, रिक्त, रिक्त, रिक्त, रिक्त);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(size_t आकार, अचिह्नित flags,
                                               AVRefStructOpaque opaque,
                                               पूर्णाङ्क  (*init_cb)(AVRefStructOpaque opaque, शून्य *obj),
                                               शून्य (*reset_cb)(AVRefStructOpaque opaque, शून्य *obj),
                                               शून्य (*free_प्रविष्टिः_cb)(AVRefStructOpaque opaque, शून्य *obj),
                                               शून्य (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(परिमाण(*pool), 0, रिक्त,
                                                   refstruct_pool_uninit);
    पूर्णाङ्क err;

    यदि (!pool)
        प्रत्यागम रिक्त;
    get_refcount(pool)->मुक्त = pool_unref;

    pool->आकार          = आकार;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_प्रविष्टिः_cb = free_प्रविष्टिः_cb;
    pool->free_cb       = free_cb;
#परिभाषय COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->प्रविष्टिः_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    यदि (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    यदि (!pool->free_प्रविष्टिः_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    यदि (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->प्रविष्टिः_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, रिक्त);
    यदि (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        प्रत्यागम रिक्त;
    }
    प्रत्यागम pool;
}

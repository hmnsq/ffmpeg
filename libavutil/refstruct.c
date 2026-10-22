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

#समावेश <stdatomic.h>
#समावेश <stdint.h>
#समावेश <string.h>

#समावेश "refstruct.h"
#समावेश "sanitizer.h"

#समावेश "avassert.h"
#समावेश "error.h"
#समावेश "macros.h"
#समावेश "mem.h"
#समावेश "mem_internal.h"
#समावेश "thread.h"

#अगर_अघोषित REFSTRUCT_CHECKED
#अगर_अघोषित ASSERT_LEVEL
#घोषणा ASSERT_LEVEL 0
#पूर्ण_अगर
#घोषणा REFSTRUCT_CHECKED (ASSERT_LEVEL >= 1)
#पूर्ण_अगर

#अगर REFSTRUCT_CHECKED
#घोषणा ff_assert(cond) av_assert0(cond)
#अन्यथा
#घोषणा ff_assert(cond) ((व्योम)0)
#पूर्ण_अगर

#घोषणा REFSTRUCT_COOKIE AV_NE((uint64_t)MKBETAG('R', 'e', 'f', 'S') << 32 | MKBETAG('t', 'r', 'u', 'c'), \
                               MKTAG('R', 'e', 'f', 'S') | (uint64_t)MKTAG('t', 'r', 'u', 'c') << 32)

#अगर_अघोषित _MSC_VER
#घोषणा REFCOUNT_OFFSET FFALIGN(माप(Ref_गिनती), FFMAX(ALIGN_64, _Alignof(max_align_t)))
#अन्यथा
#घोषणा REFCOUNT_OFFSET FFALIGN(माप(Ref_गिनती), ALIGN_64)
#पूर्ण_अगर

प्रकार काष्ठा Ref_गिनती {
    /**
     * An uintptr_t is big enough to hold the address of every reference,
     * so no overflow can happen when incrementing the refcount as long as
     * the user does not throw away references.
     */
    atomic_uintptr_t  refcount;
    AVRefStructOpaque opaque;
    व्योम (*free_cb)(AVRefStructOpaque opaque, व्योम *obj);
    व्योम (*मुक्त)(व्योम *ref);

#अगर REFSTRUCT_CHECKED
    uint64_t cookie;
#पूर्ण_अगर
} Ref_गिनती;

अटल Ref_गिनती *get_refcount(व्योम *obj)
{
    Ref_गिनती *ref = (Ref_गिनती*)((अक्षर*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    वापस ref;
}

अटल स्थिर Ref_गिनती *cget_refcount(स्थिर व्योम *obj)
{
    स्थिर Ref_गिनती *ref = (स्थिर Ref_गिनती*)((स्थिर अक्षर*)obj - REFCOUNT_OFFSET);
    ff_assert(ref->cookie == REFSTRUCT_COOKIE);
    वापस ref;
}

अटल व्योम *get_userdata(व्योम *buf)
{
    वापस (अक्षर*)buf + REFCOUNT_OFFSET;
}

अटल व्योम refcount_init(Ref_गिनती *ref, AVRefStructOpaque opaque,
                          व्योम (*free_cb)(AVRefStructOpaque opaque, व्योम *obj))
{
    atomic_init(&ref->refcount, 1);
    ref->opaque  = opaque;
    ref->free_cb = free_cb;
    ref->मुक्त    = av_free;

#अगर REFSTRUCT_CHECKED
    ref->cookie  = REFSTRUCT_COOKIE;
#पूर्ण_अगर
}

व्योम *av_refstruct_alloc_ext_c(माप_प्रकार आकार, अचिन्हित flags, AVRefStructOpaque opaque,
                               व्योम (*free_cb)(AVRefStructOpaque opaque, व्योम *obj))
{
    व्योम *buf, *obj;

    अगर (आकार > SIZE_MAX - REFCOUNT_OFFSET)
        वापस शून्य;
    buf = av_malloc(आकार + REFCOUNT_OFFSET);
    अगर (!buf)
        वापस शून्य;
    refcount_init(buf, opaque, free_cb);
    obj = get_userdata(buf);
    अगर (!(flags & AV_REFSTRUCT_FLAG_NO_ZEROING))
        स_रखो(obj, 0, आकार);

    वापस obj;
}

व्योम av_refstruct_unref(व्योम *objp)
{
    व्योम *obj;
    Ref_गिनती *ref;

    स_नकल(&obj, objp, माप(obj));
    अगर (!obj)
        वापस;
    स_नकल(objp, &(व्योम *){ शून्य }, माप(obj));

    ref = get_refcount(obj);
    अगर (atomic_fetch_sub_explicit(&ref->refcount, 1, memory_order_acq_rel) == 1) {
        अगर (ref->free_cb)
            ref->free_cb(ref->opaque, obj);
        ref->मुक्त(ref);
    }

    वापस;
}

व्योम *av_refstruct_ref(व्योम *obj)
{
    Ref_गिनती *ref = get_refcount(obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    वापस obj;
}

स्थिर व्योम *av_refstruct_ref_c(स्थिर व्योम *obj)
{
    /* Casting const away here is fine, as it is only supposed
     * to apply to the user's data and not our bookkeeping data. */
    Ref_गिनती *ref = get_refcount((व्योम*)obj);

    atomic_fetch_add_explicit(&ref->refcount, 1, memory_order_relaxed);

    वापस obj;
}

व्योम av_refstruct_replace(व्योम *dstp, स्थिर व्योम *src)
{
    स्थिर व्योम *dst;
    स_नकल(&dst, dstp, माप(dst));

    अगर (src == dst)
        वापस;
    av_refstruct_unref(dstp);
    अगर (src) {
        dst = av_refstruct_ref_c(src);
        स_नकल(dstp, &dst, माप(dst));
    }
}

पूर्णांक av_refstruct_exclusive(स्थिर व्योम *obj)
{
    स्थिर Ref_गिनती *ref = cget_refcount(obj);
    /* Casting const away here is safe, because it is a load.
     * It is necessary because atomic_load_explicit() does not
     * accept const atomics in C11 (see also N1807). */
    वापस atomic_load_explicit((atomic_uintptr_t*)&ref->refcount, memory_order_acquire) == 1;
}

काष्ठा AVRefStructPool {
    माप_प्रकार आकार;
    AVRefStructOpaque opaque;
    पूर्णांक  (*init_cb)(AVRefStructOpaque opaque, व्योम *obj);
    व्योम (*reset_cb)(AVRefStructOpaque opaque, व्योम *obj);
    व्योम (*free_entry_cb)(AVRefStructOpaque opaque, व्योम *obj);
    व्योम (*free_cb)(AVRefStructOpaque opaque);

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
    Ref_गिनती *available_entries;
    AVMutex mutex;
};

अटल व्योम pool_free(AVRefStructPool *pool)
{
    ff_mutex_destroy(&pool->mutex);
    अगर (pool->free_cb)
        pool->free_cb(pool->opaque);
    av_free(get_refcount(pool));
}

अटल व्योम pool_free_entry(AVRefStructPool *pool, Ref_गिनती *ref)
{
    अगर (!pool->free_entry_cb)
        FF_ASAN_UNPOISON(get_userdata(ref), pool->आकार);
    अगर (pool->free_entry_cb)
        pool->free_entry_cb(pool->opaque, get_userdata(ref));
    av_free(ref);
}

अटल व्योम pool_return_entry(व्योम *ref_)
{
    Ref_गिनती *ref = ref_;
    AVRefStructPool *pool = ref->opaque.nc;

    ff_mutex_lock(&pool->mutex);
    अगर (!pool->uninited) {
        /* An entry with an entry free callback owns allocations while it
         * rests in the pool. LeakSanitizer does not follow pointers stored
         * in poisoned memory, so such entries stay addressable. */
        अगर (!pool->free_entry_cb)
            FF_ASAN_POISON(get_userdata(ref), pool->आकार);
        ref->opaque.nc = pool->available_entries;
        pool->available_entries = ref;
        ref = शून्य;
    }
    ff_mutex_unlock(&pool->mutex);

    अगर (ref)
        pool_free_entry(pool, ref);

    अगर (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

अटल व्योम pool_reset_entry(AVRefStructOpaque opaque, व्योम *entry)
{
    AVRefStructPool *pool = opaque.nc;

    pool->reset_cb(pool->opaque, entry);
}

अटल पूर्णांक refstruct_pool_get_ext(व्योम *datap, AVRefStructPool *pool)
{
    व्योम *ret = शून्य;

    स_नकल(datap, &(व्योम *){ शून्य }, माप(व्योम*));

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    अगर (pool->available_entries) {
        Ref_गिनती *ref = pool->available_entries;
        ret = get_userdata(ref);
        अगर (!pool->free_entry_cb)
            FF_ASAN_UNPOISON(ret, pool->आकार);
        /* Entries are zeroed once at allocation and a user may rely on never
         * written parts staying zero, so only a pool that never zeroes and
         * keeps no state through callbacks gets its reused entries marked
         * undefined. */
        अगर ((pool->entry_flags & AV_REFSTRUCT_FLAG_NO_ZEROING) &&
            !(pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) &&
            !pool->init_cb && !pool->reset_cb && !pool->free_entry_cb)
            FF_MEM_UNDEFINED(ret, pool->आकार);
        pool->available_entries = ref->opaque.nc;
        ref->opaque.nc = pool;
        atomic_init(&ref->refcount, 1);
    }
    ff_mutex_unlock(&pool->mutex);

    अगर (!ret) {
        Ref_गिनती *ref;
        ret = av_refstruct_alloc_ext(pool->आकार, pool->entry_flags, pool,
                                     pool->reset_cb ? pool_reset_entry : शून्य);
        अगर (!ret)
            वापस AVERROR(ENOMEM);
        ref = get_refcount(ret);
        ref->मुक्त = pool_return_entry;
        अगर (pool->init_cb) {
            पूर्णांक err = pool->init_cb(pool->opaque, ret);
            अगर (err < 0) {
                अगर (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR)
                    pool->reset_cb(pool->opaque, ret);
                अगर (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR)
                    pool->free_entry_cb(pool->opaque, ret);
                av_free(ref);
                वापस err;
            }
        }
    }
    atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    अगर (pool->pool_flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME)
        स_रखो(ret, 0, pool->आकार);

    स_नकल(datap, &ret, माप(ret));

    वापस 0;
}

व्योम *av_refstruct_pool_get(AVRefStructPool *pool)
{
    व्योम *ret;
    refstruct_pool_get_ext(&ret, pool);
    वापस ret;
}

/**
 * Hint: The content of pool_unref() and refstruct_pool_uninit()
 * could currently be merged; they are only separate functions
 * in case we would ever introduce weak references.
 */
अटल व्योम pool_unref(व्योम *ref)
{
    AVRefStructPool *pool = get_userdata(ref);
    अगर (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        pool_free(pool);
}

अटल व्योम refstruct_pool_uninit(AVRefStructOpaque unused, व्योम *obj)
{
    AVRefStructPool *pool = obj;
    Ref_गिनती *entry;

    ff_mutex_lock(&pool->mutex);
    ff_assert(!pool->uninited);
    pool->uninited = 1;
    entry = pool->available_entries;
    pool->available_entries = शून्य;
    ff_mutex_unlock(&pool->mutex);

    जबतक (entry) {
        व्योम *अग्र = entry->opaque.nc;
        pool_free_entry(pool, entry);
        entry = अग्र;
    }
}

AVRefStructPool *av_refstruct_pool_alloc(माप_प्रकार आकार, अचिन्हित flags)
{
    वापस av_refstruct_pool_alloc_ext(आकार, flags, शून्य, शून्य, शून्य, शून्य, शून्य);
}

AVRefStructPool *av_refstruct_pool_alloc_ext_c(माप_प्रकार आकार, अचिन्हित flags,
                                               AVRefStructOpaque opaque,
                                               पूर्णांक  (*init_cb)(AVRefStructOpaque opaque, व्योम *obj),
                                               व्योम (*reset_cb)(AVRefStructOpaque opaque, व्योम *obj),
                                               व्योम (*free_entry_cb)(AVRefStructOpaque opaque, व्योम *obj),
                                               व्योम (*free_cb)(AVRefStructOpaque opaque))
{
    AVRefStructPool *pool = av_refstruct_alloc_ext(माप(*pool), 0, शून्य,
                                                   refstruct_pool_uninit);
    पूर्णांक err;

    अगर (!pool)
        वापस शून्य;
    get_refcount(pool)->मुक्त = pool_unref;

    pool->आकार          = आकार;
    pool->opaque        = opaque;
    pool->init_cb       = init_cb;
    pool->reset_cb      = reset_cb;
    pool->free_entry_cb = free_entry_cb;
    pool->free_cb       = free_cb;
#घोषणा COMMON_FLAGS AV_REFSTRUCT_POOL_FLAG_NO_ZEROING
    pool->entry_flags   = flags & COMMON_FLAGS;
    // Filter out nonsense combinations to avoid checks later.
    अगर (!pool->reset_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_RESET_ON_INIT_ERROR;
    अगर (!pool->free_entry_cb)
        flags &= ~AV_REFSTRUCT_POOL_FLAG_FREE_ON_INIT_ERROR;
    pool->pool_flags    = flags;

    अगर (flags & AV_REFSTRUCT_POOL_FLAG_ZERO_EVERY_TIME) {
        // We will zero the buffer before every use, so zeroing
        // upon allocating the buffer is unnecessary.
        pool->entry_flags |= AV_REFSTRUCT_FLAG_NO_ZEROING;
    }

    atomic_init(&pool->refcount, 1);

    err = ff_mutex_init(&pool->mutex, शून्य);
    अगर (err) {
        // Don't call av_refstruct_uninit() on pool, as it hasn't been properly
        // set up and is just a POD right now.
        av_free(get_refcount(pool));
        वापस शून्य;
    }
    वापस pool;
}

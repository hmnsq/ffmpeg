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

#ضمن <stdatomic.h>
#ضمن <stdint.h>
#ضمن <string.h>

#ضمن "avassert.h"
#ضمن "buffer_internal.h"
#ضمن "common.h"
#ضمن "mem.h"
#ضمن "sanitizer.h"
#ضمن "thread.h"

ساكن AVBufferRef *میانگیر_create(AVBuffer *buf, uint8_t *داده, size_t اندازه,
                                  فراغ (*حرر)(فراغ *opaque, uint8_t *داده),
                                  فراغ *opaque, صحيح flags)
{
    AVBufferRef *ref = عدم;

    buf->داده     = داده;
    buf->اندازه     = اندازه;
    buf->حرر     = حرر ? حرر : av_میانگیر_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(حجم(*ref));
    إذا (!ref)
        أرجع عدم;

    ref->میانگیر = buf;
    ref->داده   = داده;
    ref->اندازه   = اندازه;

    أرجع ref;
}

AVBufferRef *av_میانگیر_create(uint8_t *داده, size_t اندازه,
                              فراغ (*حرر)(فراغ *opaque, uint8_t *داده),
                              فراغ *opaque, صحيح flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(حجم(*buf));
    إذا (!buf)
        أرجع عدم;

    ret = میانگیر_create(buf, داده, اندازه, حرر, opaque, flags);
    إذا (!ret) {
        av_free(buf);
        أرجع عدم;
    }
    أرجع ret;
}

فراغ av_میانگیر_default_free(فراغ *opaque, uint8_t *داده)
{
    av_free(داده);
}

AVBufferRef *av_میانگیر_alloc(size_t اندازه)
{
    AVBufferRef *ret = عدم;
    uint8_t    *داده = عدم;

    داده = av_malloc(اندازه);
    إذا (!داده)
        أرجع عدم;

    ret = av_میانگیر_create(داده, اندازه, av_میانگیر_default_free, عدم, 0);
    إذا (!ret)
        av_freep(&داده);

    أرجع ret;
}

AVBufferRef *av_میانگیر_allocz(size_t اندازه)
{
    AVBufferRef *ret = av_میانگیر_alloc(اندازه);
    إذا (!ret)
        أرجع عدم;

    memset(ret->داده, 0, اندازه);
    أرجع ret;
}

AVBufferRef *av_میانگیر_ref(ثابت AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(حجم(*ret));

    إذا (!ret)
        أرجع عدم;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->میانگیر->refcount, 1, memory_order_relaxed);

    أرجع ret;
}

ساكن فراغ میانگیر_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->میانگیر;

    إذا (src) {
        **dst = **src;
        av_freep(src);
    } وإلا
        av_freep(dst);

    إذا (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        صحيح free_avbuffer = !(b->flags_داخلی & میانگیر_FLAG_NO_FREE);
        b->حرر(b->opaque, b->داده);
        إذا (free_avbuffer)
            av_free(b);
    }
}

فراغ av_میانگیر_unref(AVBufferRef **buf)
{
    إذا (!buf || !*buf)
        أرجع;

    میانگیر_replace(buf, عدم);
}

صحيح av_میانگیر_is_writable(ثابت AVBufferRef *buf)
{
    إذا (buf->میانگیر->flags & AV_میانگیر_FLAG_READONLY)
        أرجع 0;

    أرجع atomic_load(&buf->میانگیر->refcount) == 1;
}

فراغ *av_میانگیر_get_opaque(ثابت AVBufferRef *buf)
{
    أرجع buf->میانگیر->opaque;
}

صحيح av_میانگیر_get_ref_شمار(ثابت AVBufferRef *buf)
{
    أرجع atomic_load(&buf->میانگیر->refcount);
}

صحيح av_میانگیر_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    إذا (av_میانگیر_is_writable(buf))
        أرجع 0;

    newbuf = av_میانگیر_alloc(buf->اندازه);
    إذا (!newbuf)
        أرجع AVERROR(ENOMEM);

    کپی_حافظه(newbuf->داده, buf->داده, buf->اندازه);

    میانگیر_replace(pbuf, &newbuf);

    أرجع 0;
}

صحيح av_میانگیر_realloc(AVBufferRef **pbuf, size_t اندازه)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    صحيح ret;

    إذا (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *داده = av_realloc(عدم, اندازه);
        إذا (!داده)
            أرجع AVERROR(ENOMEM);

        buf = av_میانگیر_create(داده, اندازه, av_میانگیر_default_free, عدم, 0);
        إذا (!buf) {
            av_freep(&داده);
            أرجع AVERROR(ENOMEM);
        }

        buf->میانگیر->flags_داخلی |= میانگیر_FLAG_REALLOCATABLE;
        *pbuf = buf;

        أرجع 0;
    } وإلا إذا (buf->اندازه == اندازه)
        أرجع 0;

    إذا (!(buf->میانگیر->flags_داخلی & میانگیر_FLAG_REALLOCATABLE) ||
        !av_میانگیر_is_writable(buf) || buf->داده != buf->میانگیر->داده) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = عدم;

        ret = av_میانگیر_realloc(&new, اندازه);
        إذا (ret < 0)
            أرجع ret;

        کپی_حافظه(new->داده, buf->داده, FFMIN(اندازه, buf->اندازه));

        میانگیر_replace(pbuf, &new);
        أرجع 0;
    }

    tmp = av_realloc(buf->میانگیر->داده, اندازه);
    إذا (!tmp)
        أرجع AVERROR(ENOMEM);

    buf->میانگیر->داده = buf->داده = tmp;
    buf->میانگیر->اندازه = buf->اندازه = اندازه;
    أرجع 0;
}

صحيح av_میانگیر_replace(AVBufferRef **pdst, ثابت AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    إذا (!src) {
        av_میانگیر_unref(pdst);
        أرجع 0;
    }

    إذا (dst && dst->میانگیر == src->میانگیر) {
        /* make sure the data pointers match */
        dst->داده = src->داده;
        dst->اندازه = src->اندازه;
        أرجع 0;
    }

    tmp = av_میانگیر_ref(src);
    إذا (!tmp)
        أرجع AVERROR(ENOMEM);

    av_میانگیر_unref(pdst);
    *pdst = tmp;
    أرجع 0;
}

AVBufferPool *av_میانگیر_pool_init2(size_t اندازه, فراغ *opaque,
                                   AVBufferRef* (*alloc)(فراغ *opaque, size_t اندازه),
                                   فراغ (*pool_free)(فراغ *opaque))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    إذا (!pool)
        أرجع عدم;

    إذا (ff_mutex_init(&pool->mutex, عدم)) {
        av_free(pool);
        أرجع عدم;
    }

    pool->اندازه      = اندازه;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_میانگیر_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    أرجع pool;
}

AVBufferPool *av_میانگیر_pool_init(size_t اندازه, AVBufferRef* (*alloc)(size_t اندازه))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    إذا (!pool)
        أرجع عدم;

    إذا (ff_mutex_init(&pool->mutex, عدم)) {
        av_free(pool);
        أرجع عدم;
    }

    pool->اندازه     = اندازه;
    pool->alloc    = alloc ? alloc : av_میانگیر_alloc;

    atomic_init(&pool->refcount, 1);

    أرجع pool;
}

ساكن فراغ میانگیر_pool_flush(AVBufferPool *pool)
{
    طالما (pool->pool) {
        میانگیر_Pool_مدخل *buf = pool->pool;
        pool->pool = buf->بعدی;

        إذا (buf->حرر == av_میانگیر_default_free)
            FF_ASAN_UNPOISON(buf->داده, pool->اندازه);
        buf->حرر(buf->opaque, buf->داده);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
ساكن فراغ میانگیر_pool_free(AVBufferPool *pool)
{
    میانگیر_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    إذا (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

فراغ av_میانگیر_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    إذا (!ppool || !*ppool)
        أرجع;
    pool   = *ppool;
    *ppool = عدم;

    ff_mutex_قفل(&pool->mutex);
    میانگیر_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    إذا (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        میانگیر_pool_free(pool);
}

ساكن فراغ pool_release_میانگیر(فراغ *opaque, uint8_t *داده)
{
    میانگیر_Pool_مدخل *buf = opaque;
    AVBufferPool *pool = buf->pool;

    إذا (buf->حرر == av_میانگیر_default_free)
        FF_ASAN_POISON(buf->داده, pool->اندازه);

    ff_mutex_قفل(&pool->mutex);
    buf->بعدی = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    إذا (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        میانگیر_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
ساكن AVBufferRef *pool_alloc_میانگیر(AVBufferPool *pool)
{
    میانگیر_Pool_مدخل *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->اندازه) :
                         pool->alloc(pool->اندازه);
    إذا (!ret)
        أرجع عدم;

    buf = av_mallocz(حجم(*buf));
    إذا (!buf) {
        av_میانگیر_unref(&ret);
        أرجع عدم;
    }

    buf->داده   = ret->میانگیر->داده;
    buf->opaque = ret->میانگیر->opaque;
    buf->حرر   = ret->میانگیر->حرر;
    buf->pool   = pool;

    ret->میانگیر->opaque = buf;
    ret->میانگیر->حرر   = pool_release_میانگیر;

    أرجع ret;
}

AVBufferRef *av_میانگیر_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    میانگیر_Pool_مدخل *buf;

    ff_mutex_قفل(&pool->mutex);
    buf = pool->pool;
    إذا (buf) {
        memset(&buf->میانگیر, 0, حجم(buf->میانگیر));
        ret = میانگیر_create(&buf->میانگیر, buf->داده, pool->اندازه,
                            pool_release_میانگیر, buf, 0);
        إذا (ret) {
            pool->pool = buf->بعدی;
            buf->بعدی = عدم;
            buf->میانگیر.flags_داخلی |= میانگیر_FLAG_NO_FREE;
            إذا (buf->حرر == av_میانگیر_default_free) {
                FF_ASAN_UNPOISON(buf->داده, pool->اندازه);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                إذا (!pool->alloc2 && pool->alloc == av_میانگیر_alloc)
                    FF_MEM_UNDEFINED(buf->داده, pool->اندازه);
            }
        }
    } وإلا {
        ret = pool_alloc_میانگیر(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    إذا (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    أرجع ret;
}

فراغ *av_میانگیر_pool_میانگیر_get_opaque(ثابت AVBufferRef *ref)
{
    میانگیر_Pool_مدخل *buf = ref->میانگیر->opaque;
    av_assert0(buf);
    أرجع buf->opaque;
}

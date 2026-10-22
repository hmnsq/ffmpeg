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

ساكن AVBufferRef *بفر_create(AVBuffer *buf, uint8_t *انکڑے, size_t ناپ,
                                  فراغ (*حرر)(فراغ *opaque, uint8_t *انکڑے),
                                  فراغ *opaque, صحيح flags)
{
    AVBufferRef *ref = عدم;

    buf->انکڑے     = انکڑے;
    buf->ناپ     = ناپ;
    buf->حرر     = حرر ? حرر : av_بفر_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(حجم(*ref));
    إذا (!ref)
        أرجع عدم;

    ref->بفر = buf;
    ref->انکڑے   = انکڑے;
    ref->ناپ   = ناپ;

    أرجع ref;
}

AVBufferRef *av_بفر_create(uint8_t *انکڑے, size_t ناپ,
                              فراغ (*حرر)(فراغ *opaque, uint8_t *انکڑے),
                              فراغ *opaque, صحيح flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(حجم(*buf));
    إذا (!buf)
        أرجع عدم;

    ret = بفر_create(buf, انکڑے, ناپ, حرر, opaque, flags);
    إذا (!ret) {
        av_free(buf);
        أرجع عدم;
    }
    أرجع ret;
}

فراغ av_بفر_default_free(فراغ *opaque, uint8_t *انکڑے)
{
    av_free(انکڑے);
}

AVBufferRef *av_بفر_alloc(size_t ناپ)
{
    AVBufferRef *ret = عدم;
    uint8_t    *انکڑے = عدم;

    انکڑے = av_malloc(ناپ);
    إذا (!انکڑے)
        أرجع عدم;

    ret = av_بفر_create(انکڑے, ناپ, av_بفر_default_free, عدم, 0);
    إذا (!ret)
        av_freep(&انکڑے);

    أرجع ret;
}

AVBufferRef *av_بفر_allocz(size_t ناپ)
{
    AVBufferRef *ret = av_بفر_alloc(ناپ);
    إذا (!ret)
        أرجع عدم;

    memset(ret->انکڑے, 0, ناپ);
    أرجع ret;
}

AVBufferRef *av_بفر_ref(ثابت AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(حجم(*ret));

    إذا (!ret)
        أرجع عدم;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->بفر->refcount, 1, memory_order_relaxed);

    أرجع ret;
}

ساكن فراغ بفر_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->بفر;

    إذا (src) {
        **dst = **src;
        av_freep(src);
    } وإلا
        av_freep(dst);

    إذا (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        صحيح free_avbuffer = !(b->flags_اندرونی & بفر_FLAG_NO_FREE);
        b->حرر(b->opaque, b->انکڑے);
        إذا (free_avbuffer)
            av_free(b);
    }
}

فراغ av_بفر_unref(AVBufferRef **buf)
{
    إذا (!buf || !*buf)
        أرجع;

    بفر_replace(buf, عدم);
}

صحيح av_بفر_is_writable(ثابت AVBufferRef *buf)
{
    إذا (buf->بفر->flags & AV_بفر_FLAG_READONLY)
        أرجع 0;

    أرجع atomic_load(&buf->بفر->refcount) == 1;
}

فراغ *av_بفر_get_opaque(ثابت AVBufferRef *buf)
{
    أرجع buf->بفر->opaque;
}

صحيح av_بفر_get_ref_گنتی(ثابت AVBufferRef *buf)
{
    أرجع atomic_load(&buf->بفر->refcount);
}

صحيح av_بفر_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    إذا (av_بفر_is_writable(buf))
        أرجع 0;

    newbuf = av_بفر_alloc(buf->ناپ);
    إذا (!newbuf)
        أرجع AVERROR(ENOMEM);

    حافظہ_نقل(newbuf->انکڑے, buf->انکڑے, buf->ناپ);

    بفر_replace(pbuf, &newbuf);

    أرجع 0;
}

صحيح av_بفر_realloc(AVBufferRef **pbuf, size_t ناپ)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    صحيح ret;

    إذا (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *انکڑے = av_realloc(عدم, ناپ);
        إذا (!انکڑے)
            أرجع AVERROR(ENOMEM);

        buf = av_بفر_create(انکڑے, ناپ, av_بفر_default_free, عدم, 0);
        إذا (!buf) {
            av_freep(&انکڑے);
            أرجع AVERROR(ENOMEM);
        }

        buf->بفر->flags_اندرونی |= بفر_FLAG_REALLOCATABLE;
        *pbuf = buf;

        أرجع 0;
    } وإلا إذا (buf->ناپ == ناپ)
        أرجع 0;

    إذا (!(buf->بفر->flags_اندرونی & بفر_FLAG_REALLOCATABLE) ||
        !av_بفر_is_writable(buf) || buf->انکڑے != buf->بفر->انکڑے) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = عدم;

        ret = av_بفر_realloc(&new, ناپ);
        إذا (ret < 0)
            أرجع ret;

        حافظہ_نقل(new->انکڑے, buf->انکڑے, FFMIN(ناپ, buf->ناپ));

        بفر_replace(pbuf, &new);
        أرجع 0;
    }

    tmp = av_realloc(buf->بفر->انکڑے, ناپ);
    إذا (!tmp)
        أرجع AVERROR(ENOMEM);

    buf->بفر->انکڑے = buf->انکڑے = tmp;
    buf->بفر->ناپ = buf->ناپ = ناپ;
    أرجع 0;
}

صحيح av_بفر_replace(AVBufferRef **pdst, ثابت AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    إذا (!src) {
        av_بفر_unref(pdst);
        أرجع 0;
    }

    إذا (dst && dst->بفر == src->بفر) {
        /* make sure the data pointers match */
        dst->انکڑے = src->انکڑے;
        dst->ناپ = src->ناپ;
        أرجع 0;
    }

    tmp = av_بفر_ref(src);
    إذا (!tmp)
        أرجع AVERROR(ENOMEM);

    av_بفر_unref(pdst);
    *pdst = tmp;
    أرجع 0;
}

AVBufferPool *av_بفر_pool_init2(size_t ناپ, فراغ *opaque,
                                   AVBufferRef* (*alloc)(فراغ *opaque, size_t ناپ),
                                   فراغ (*pool_free)(فراغ *opaque))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    إذا (!pool)
        أرجع عدم;

    إذا (ff_mutex_init(&pool->mutex, عدم)) {
        av_free(pool);
        أرجع عدم;
    }

    pool->ناپ      = ناپ;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_بفر_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    أرجع pool;
}

AVBufferPool *av_بفر_pool_init(size_t ناپ, AVBufferRef* (*alloc)(size_t ناپ))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    إذا (!pool)
        أرجع عدم;

    إذا (ff_mutex_init(&pool->mutex, عدم)) {
        av_free(pool);
        أرجع عدم;
    }

    pool->ناپ     = ناپ;
    pool->alloc    = alloc ? alloc : av_بفر_alloc;

    atomic_init(&pool->refcount, 1);

    أرجع pool;
}

ساكن فراغ بفر_pool_flush(AVBufferPool *pool)
{
    طالما (pool->pool) {
        بفر_Pool_اندراج *buf = pool->pool;
        pool->pool = buf->اگلا;

        إذا (buf->حرر == av_بفر_default_free)
            FF_ASAN_UNPOISON(buf->انکڑے, pool->ناپ);
        buf->حرر(buf->opaque, buf->انکڑے);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
ساكن فراغ بفر_pool_free(AVBufferPool *pool)
{
    بفر_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    إذا (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

فراغ av_بفر_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    إذا (!ppool || !*ppool)
        أرجع;
    pool   = *ppool;
    *ppool = عدم;

    ff_mutex_جندرا(&pool->mutex);
    بفر_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    إذا (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        بفر_pool_free(pool);
}

ساكن فراغ pool_release_بفر(فراغ *opaque, uint8_t *انکڑے)
{
    بفر_Pool_اندراج *buf = opaque;
    AVBufferPool *pool = buf->pool;

    إذا (buf->حرر == av_بفر_default_free)
        FF_ASAN_POISON(buf->انکڑے, pool->ناپ);

    ff_mutex_جندرا(&pool->mutex);
    buf->اگلا = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    إذا (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        بفر_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
ساكن AVBufferRef *pool_alloc_بفر(AVBufferPool *pool)
{
    بفر_Pool_اندراج *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->ناپ) :
                         pool->alloc(pool->ناپ);
    إذا (!ret)
        أرجع عدم;

    buf = av_mallocz(حجم(*buf));
    إذا (!buf) {
        av_بفر_unref(&ret);
        أرجع عدم;
    }

    buf->انکڑے   = ret->بفر->انکڑے;
    buf->opaque = ret->بفر->opaque;
    buf->حرر   = ret->بفر->حرر;
    buf->pool   = pool;

    ret->بفر->opaque = buf;
    ret->بفر->حرر   = pool_release_بفر;

    أرجع ret;
}

AVBufferRef *av_بفر_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    بفر_Pool_اندراج *buf;

    ff_mutex_جندرا(&pool->mutex);
    buf = pool->pool;
    إذا (buf) {
        memset(&buf->بفر, 0, حجم(buf->بفر));
        ret = بفر_create(&buf->بفر, buf->انکڑے, pool->ناپ,
                            pool_release_بفر, buf, 0);
        إذا (ret) {
            pool->pool = buf->اگلا;
            buf->اگلا = عدم;
            buf->بفر.flags_اندرونی |= بفر_FLAG_NO_FREE;
            إذا (buf->حرر == av_بفر_default_free) {
                FF_ASAN_UNPOISON(buf->انکڑے, pool->ناپ);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                إذا (!pool->alloc2 && pool->alloc == av_بفر_alloc)
                    FF_MEM_UNDEFINED(buf->انکڑے, pool->ناپ);
            }
        }
    } وإلا {
        ret = pool_alloc_بفر(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    إذا (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    أرجع ret;
}

فراغ *av_بفر_pool_بفر_get_opaque(ثابت AVBufferRef *ref)
{
    بفر_Pool_اندراج *buf = ref->بفر->opaque;
    av_assert0(buf);
    أرجع buf->opaque;
}

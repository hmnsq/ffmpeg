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

#شامل <stdatomic.h>
#شامل <stdint.h>
#شامل <string.h>

#شامل "avassert.h"
#شامل "buffer_internal.h"
#شامل "common.h"
#شامل "mem.h"
#شامل "sanitizer.h"
#شامل "thread.h"

ساکن AVBufferRef *بفر_create(AVBuffer *buf, uint8_t *ڈیٹا, size_t سائز,
                                  خالی (*آزاد)(خالی *opaque, uint8_t *ڈیٹا),
                                  خالی *opaque, صحیح flags)
{
    AVBufferRef *ref = تہی;

    buf->ڈیٹا     = ڈیٹا;
    buf->سائز     = سائز;
    buf->آزاد     = آزاد ? آزاد : av_بفر_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(حجم(*ref));
    اگر (!ref)
        واپس تہی;

    ref->بفر = buf;
    ref->ڈیٹا   = ڈیٹا;
    ref->سائز   = سائز;

    واپس ref;
}

AVBufferRef *av_بفر_create(uint8_t *ڈیٹا, size_t سائز,
                              خالی (*آزاد)(خالی *opaque, uint8_t *ڈیٹا),
                              خالی *opaque, صحیح flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(حجم(*buf));
    اگر (!buf)
        واپس تہی;

    ret = بفر_create(buf, ڈیٹا, سائز, آزاد, opaque, flags);
    اگر (!ret) {
        av_free(buf);
        واپس تہی;
    }
    واپس ret;
}

خالی av_بفر_default_free(خالی *opaque, uint8_t *ڈیٹا)
{
    av_free(ڈیٹا);
}

AVBufferRef *av_بفر_alloc(size_t سائز)
{
    AVBufferRef *ret = تہی;
    uint8_t    *ڈیٹا = تہی;

    ڈیٹا = av_malloc(سائز);
    اگر (!ڈیٹا)
        واپس تہی;

    ret = av_بفر_create(ڈیٹا, سائز, av_بفر_default_free, تہی, 0);
    اگر (!ret)
        av_freep(&ڈیٹا);

    واپس ret;
}

AVBufferRef *av_بفر_allocz(size_t سائز)
{
    AVBufferRef *ret = av_بفر_alloc(سائز);
    اگر (!ret)
        واپس تہی;

    memset(ret->ڈیٹا, 0, سائز);
    واپس ret;
}

AVBufferRef *av_بفر_ref(ثابت AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(حجم(*ret));

    اگر (!ret)
        واپس تہی;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->بفر->refcount, 1, memory_order_relaxed);

    واپس ret;
}

ساکن خالی بفر_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->بفر;

    اگر (src) {
        **dst = **src;
        av_freep(src);
    } ورنہ
        av_freep(dst);

    اگر (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        صحیح free_avbuffer = !(b->flags_اندرونی & بفر_FLAG_NO_FREE);
        b->آزاد(b->opaque, b->ڈیٹا);
        اگر (free_avbuffer)
            av_free(b);
    }
}

خالی av_بفر_unref(AVBufferRef **buf)
{
    اگر (!buf || !*buf)
        واپس;

    بفر_replace(buf, تہی);
}

صحیح av_بفر_is_writable(ثابت AVBufferRef *buf)
{
    اگر (buf->بفر->flags & AV_بفر_FLAG_READONLY)
        واپس 0;

    واپس atomic_load(&buf->بفر->refcount) == 1;
}

خالی *av_بفر_get_opaque(ثابت AVBufferRef *buf)
{
    واپس buf->بفر->opaque;
}

صحیح av_بفر_get_ref_گنتی(ثابت AVBufferRef *buf)
{
    واپس atomic_load(&buf->بفر->refcount);
}

صحیح av_بفر_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    اگر (av_بفر_is_writable(buf))
        واپس 0;

    newbuf = av_بفر_alloc(buf->سائز);
    اگر (!newbuf)
        واپس AVERROR(ENOMEM);

    حافظہ_نقل(newbuf->ڈیٹا, buf->ڈیٹا, buf->سائز);

    بفر_replace(pbuf, &newbuf);

    واپس 0;
}

صحیح av_بفر_realloc(AVBufferRef **pbuf, size_t سائز)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    صحیح ret;

    اگر (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *ڈیٹا = av_realloc(تہی, سائز);
        اگر (!ڈیٹا)
            واپس AVERROR(ENOMEM);

        buf = av_بفر_create(ڈیٹا, سائز, av_بفر_default_free, تہی, 0);
        اگر (!buf) {
            av_freep(&ڈیٹا);
            واپس AVERROR(ENOMEM);
        }

        buf->بفر->flags_اندرونی |= بفر_FLAG_REALLOCATABLE;
        *pbuf = buf;

        واپس 0;
    } ورنہ اگر (buf->سائز == سائز)
        واپس 0;

    اگر (!(buf->بفر->flags_اندرونی & بفر_FLAG_REALLOCATABLE) ||
        !av_بفر_is_writable(buf) || buf->ڈیٹا != buf->بفر->ڈیٹا) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = تہی;

        ret = av_بفر_realloc(&new, سائز);
        اگر (ret < 0)
            واپس ret;

        حافظہ_نقل(new->ڈیٹا, buf->ڈیٹا, FFMIN(سائز, buf->سائز));

        بفر_replace(pbuf, &new);
        واپس 0;
    }

    tmp = av_realloc(buf->بفر->ڈیٹا, سائز);
    اگر (!tmp)
        واپس AVERROR(ENOMEM);

    buf->بفر->ڈیٹا = buf->ڈیٹا = tmp;
    buf->بفر->سائز = buf->سائز = سائز;
    واپس 0;
}

صحیح av_بفر_replace(AVBufferRef **pdst, ثابت AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    اگر (!src) {
        av_بفر_unref(pdst);
        واپس 0;
    }

    اگر (dst && dst->بفر == src->بفر) {
        /* make sure the data pointers match */
        dst->ڈیٹا = src->ڈیٹا;
        dst->سائز = src->سائز;
        واپس 0;
    }

    tmp = av_بفر_ref(src);
    اگر (!tmp)
        واپس AVERROR(ENOMEM);

    av_بفر_unref(pdst);
    *pdst = tmp;
    واپس 0;
}

AVBufferPool *av_بفر_pool_init2(size_t سائز, خالی *opaque,
                                   AVBufferRef* (*alloc)(خالی *opaque, size_t سائز),
                                   خالی (*pool_free)(خالی *opaque))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    اگر (!pool)
        واپس تہی;

    اگر (ff_mutex_init(&pool->mutex, تہی)) {
        av_free(pool);
        واپس تہی;
    }

    pool->سائز      = سائز;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_بفر_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    واپس pool;
}

AVBufferPool *av_بفر_pool_init(size_t سائز, AVBufferRef* (*alloc)(size_t سائز))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    اگر (!pool)
        واپس تہی;

    اگر (ff_mutex_init(&pool->mutex, تہی)) {
        av_free(pool);
        واپس تہی;
    }

    pool->سائز     = سائز;
    pool->alloc    = alloc ? alloc : av_بفر_alloc;

    atomic_init(&pool->refcount, 1);

    واپس pool;
}

ساکن خالی بفر_pool_flush(AVBufferPool *pool)
{
    جب (pool->pool) {
        بفر_Pool_اندراج *buf = pool->pool;
        pool->pool = buf->اگلا;

        اگر (buf->آزاد == av_بفر_default_free)
            FF_ASAN_UNPOISON(buf->ڈیٹا, pool->سائز);
        buf->آزاد(buf->opaque, buf->ڈیٹا);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
ساکن خالی بفر_pool_free(AVBufferPool *pool)
{
    بفر_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    اگر (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

خالی av_بفر_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    اگر (!ppool || !*ppool)
        واپس;
    pool   = *ppool;
    *ppool = تہی;

    ff_mutex_تالا(&pool->mutex);
    بفر_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    اگر (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        بفر_pool_free(pool);
}

ساکن خالی pool_release_بفر(خالی *opaque, uint8_t *ڈیٹا)
{
    بفر_Pool_اندراج *buf = opaque;
    AVBufferPool *pool = buf->pool;

    اگر (buf->آزاد == av_بفر_default_free)
        FF_ASAN_POISON(buf->ڈیٹا, pool->سائز);

    ff_mutex_تالا(&pool->mutex);
    buf->اگلا = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    اگر (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        بفر_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
ساکن AVBufferRef *pool_alloc_بفر(AVBufferPool *pool)
{
    بفر_Pool_اندراج *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->سائز) :
                         pool->alloc(pool->سائز);
    اگر (!ret)
        واپس تہی;

    buf = av_mallocz(حجم(*buf));
    اگر (!buf) {
        av_بفر_unref(&ret);
        واپس تہی;
    }

    buf->ڈیٹا   = ret->بفر->ڈیٹا;
    buf->opaque = ret->بفر->opaque;
    buf->آزاد   = ret->بفر->آزاد;
    buf->pool   = pool;

    ret->بفر->opaque = buf;
    ret->بفر->آزاد   = pool_release_بفر;

    واپس ret;
}

AVBufferRef *av_بفر_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    بفر_Pool_اندراج *buf;

    ff_mutex_تالا(&pool->mutex);
    buf = pool->pool;
    اگر (buf) {
        memset(&buf->بفر, 0, حجم(buf->بفر));
        ret = بفر_create(&buf->بفر, buf->ڈیٹا, pool->سائز,
                            pool_release_بفر, buf, 0);
        اگر (ret) {
            pool->pool = buf->اگلا;
            buf->اگلا = تہی;
            buf->بفر.flags_اندرونی |= بفر_FLAG_NO_FREE;
            اگر (buf->آزاد == av_بفر_default_free) {
                FF_ASAN_UNPOISON(buf->ڈیٹا, pool->سائز);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                اگر (!pool->alloc2 && pool->alloc == av_بفر_alloc)
                    FF_MEM_UNDEFINED(buf->ڈیٹا, pool->سائز);
            }
        }
    } ورنہ {
        ret = pool_alloc_بفر(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    اگر (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    واپس ret;
}

خالی *av_بفر_pool_بفر_get_opaque(ثابت AVBufferRef *ref)
{
    بفر_Pool_اندراج *buf = ref->بفر->opaque;
    av_assert0(buf);
    واپس buf->opaque;
}

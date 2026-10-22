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

#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "avassert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "buffer_internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "sanitizer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"

ਸਥਿਰ AVBufferRef *ਬਫਰ_create(AVBuffer *buf, uint8_t *ਅੰਕੜੇ, size_t ਮਾਪ,
                                  ਖਾਲੀ (*ਮੁਕਤ)(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ),
                                  ਖਾਲੀ *opaque, ਪੂਰਨ flags)
{
    AVBufferRef *ref = ਨਿਰਾ;

    buf->ਅੰਕੜੇ     = ਅੰਕੜੇ;
    buf->ਮਾਪ     = ਮਾਪ;
    buf->ਮੁਕਤ     = ਮੁਕਤ ? ਮੁਕਤ : av_ਬਫਰ_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(ਆਕਾਰ(*ref));
    ਜੇ (!ref)
        ਵਾਪਸ ਨਿਰਾ;

    ref->ਬਫਰ = buf;
    ref->ਅੰਕੜੇ   = ਅੰਕੜੇ;
    ref->ਮਾਪ   = ਮਾਪ;

    ਵਾਪਸ ref;
}

AVBufferRef *av_ਬਫਰ_create(uint8_t *ਅੰਕੜੇ, size_t ਮਾਪ,
                              ਖਾਲੀ (*ਮੁਕਤ)(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ),
                              ਖਾਲੀ *opaque, ਪੂਰਨ flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(ਆਕਾਰ(*buf));
    ਜੇ (!buf)
        ਵਾਪਸ ਨਿਰਾ;

    ret = ਬਫਰ_create(buf, ਅੰਕੜੇ, ਮਾਪ, ਮੁਕਤ, opaque, flags);
    ਜੇ (!ret) {
        av_free(buf);
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ ret;
}

ਖਾਲੀ av_ਬਫਰ_default_free(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    av_free(ਅੰਕੜੇ);
}

AVBufferRef *av_ਬਫਰ_alloc(size_t ਮਾਪ)
{
    AVBufferRef *ret = ਨਿਰਾ;
    uint8_t    *ਅੰਕੜੇ = ਨਿਰਾ;

    ਅੰਕੜੇ = av_malloc(ਮਾਪ);
    ਜੇ (!ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    ret = av_ਬਫਰ_create(ਅੰਕੜੇ, ਮਾਪ, av_ਬਫਰ_default_free, ਨਿਰਾ, 0);
    ਜੇ (!ret)
        av_freep(&ਅੰਕੜੇ);

    ਵਾਪਸ ret;
}

AVBufferRef *av_ਬਫਰ_allocz(size_t ਮਾਪ)
{
    AVBufferRef *ret = av_ਬਫਰ_alloc(ਮਾਪ);
    ਜੇ (!ret)
        ਵਾਪਸ ਨਿਰਾ;

    memset(ret->ਅੰਕੜੇ, 0, ਮਾਪ);
    ਵਾਪਸ ret;
}

AVBufferRef *av_ਬਫਰ_ref(ਅਚਲ AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(ਆਕਾਰ(*ret));

    ਜੇ (!ret)
        ਵਾਪਸ ਨਿਰਾ;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->ਬਫਰ->refcount, 1, memory_order_relaxed);

    ਵਾਪਸ ret;
}

ਸਥਿਰ ਖਾਲੀ ਬਫਰ_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->ਬਫਰ;

    ਜੇ (src) {
        **dst = **src;
        av_freep(src);
    } ਨਹੀਂਤਾਂ
        av_freep(dst);

    ਜੇ (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        ਪੂਰਨ free_avbuffer = !(b->flags_ਅੰਦਰੂਨੀ & ਬਫਰ_FLAG_NO_FREE);
        b->ਮੁਕਤ(b->opaque, b->ਅੰਕੜੇ);
        ਜੇ (free_avbuffer)
            av_free(b);
    }
}

ਖਾਲੀ av_ਬਫਰ_unref(AVBufferRef **buf)
{
    ਜੇ (!buf || !*buf)
        ਵਾਪਸ;

    ਬਫਰ_replace(buf, ਨਿਰਾ);
}

ਪੂਰਨ av_ਬਫਰ_is_writable(ਅਚਲ AVBufferRef *buf)
{
    ਜੇ (buf->ਬਫਰ->flags & AV_ਬਫਰ_FLAG_READONLY)
        ਵਾਪਸ 0;

    ਵਾਪਸ atomic_load(&buf->ਬਫਰ->refcount) == 1;
}

ਖਾਲੀ *av_ਬਫਰ_get_opaque(ਅਚਲ AVBufferRef *buf)
{
    ਵਾਪਸ buf->ਬਫਰ->opaque;
}

ਪੂਰਨ av_ਬਫਰ_get_ref_ਗਿਣਤੀ(ਅਚਲ AVBufferRef *buf)
{
    ਵਾਪਸ atomic_load(&buf->ਬਫਰ->refcount);
}

ਪੂਰਨ av_ਬਫਰ_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    ਜੇ (av_ਬਫਰ_is_writable(buf))
        ਵਾਪਸ 0;

    newbuf = av_ਬਫਰ_alloc(buf->ਮਾਪ);
    ਜੇ (!newbuf)
        ਵਾਪਸ AVERROR(ENOMEM);

    ਸਮ੍ਰਿਤੀ_ਨਕਲ(newbuf->ਅੰਕੜੇ, buf->ਅੰਕੜੇ, buf->ਮਾਪ);

    ਬਫਰ_replace(pbuf, &newbuf);

    ਵਾਪਸ 0;
}

ਪੂਰਨ av_ਬਫਰ_realloc(AVBufferRef **pbuf, size_t ਮਾਪ)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    ਪੂਰਨ ret;

    ਜੇ (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *ਅੰਕੜੇ = av_realloc(ਨਿਰਾ, ਮਾਪ);
        ਜੇ (!ਅੰਕੜੇ)
            ਵਾਪਸ AVERROR(ENOMEM);

        buf = av_ਬਫਰ_create(ਅੰਕੜੇ, ਮਾਪ, av_ਬਫਰ_default_free, ਨਿਰਾ, 0);
        ਜੇ (!buf) {
            av_freep(&ਅੰਕੜੇ);
            ਵਾਪਸ AVERROR(ENOMEM);
        }

        buf->ਬਫਰ->flags_ਅੰਦਰੂਨੀ |= ਬਫਰ_FLAG_REALLOCATABLE;
        *pbuf = buf;

        ਵਾਪਸ 0;
    } ਨਹੀਂਤਾਂ ਜੇ (buf->ਮਾਪ == ਮਾਪ)
        ਵਾਪਸ 0;

    ਜੇ (!(buf->ਬਫਰ->flags_ਅੰਦਰੂਨੀ & ਬਫਰ_FLAG_REALLOCATABLE) ||
        !av_ਬਫਰ_is_writable(buf) || buf->ਅੰਕੜੇ != buf->ਬਫਰ->ਅੰਕੜੇ) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = ਨਿਰਾ;

        ret = av_ਬਫਰ_realloc(&new, ਮਾਪ);
        ਜੇ (ret < 0)
            ਵਾਪਸ ret;

        ਸਮ੍ਰਿਤੀ_ਨਕਲ(new->ਅੰਕੜੇ, buf->ਅੰਕੜੇ, FFMIN(ਮਾਪ, buf->ਮਾਪ));

        ਬਫਰ_replace(pbuf, &new);
        ਵਾਪਸ 0;
    }

    tmp = av_realloc(buf->ਬਫਰ->ਅੰਕੜੇ, ਮਾਪ);
    ਜੇ (!tmp)
        ਵਾਪਸ AVERROR(ENOMEM);

    buf->ਬਫਰ->ਅੰਕੜੇ = buf->ਅੰਕੜੇ = tmp;
    buf->ਬਫਰ->ਮਾਪ = buf->ਮਾਪ = ਮਾਪ;
    ਵਾਪਸ 0;
}

ਪੂਰਨ av_ਬਫਰ_replace(AVBufferRef **pdst, ਅਚਲ AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    ਜੇ (!src) {
        av_ਬਫਰ_unref(pdst);
        ਵਾਪਸ 0;
    }

    ਜੇ (dst && dst->ਬਫਰ == src->ਬਫਰ) {
        /* make sure the data pointers match */
        dst->ਅੰਕੜੇ = src->ਅੰਕੜੇ;
        dst->ਮਾਪ = src->ਮਾਪ;
        ਵਾਪਸ 0;
    }

    tmp = av_ਬਫਰ_ref(src);
    ਜੇ (!tmp)
        ਵਾਪਸ AVERROR(ENOMEM);

    av_ਬਫਰ_unref(pdst);
    *pdst = tmp;
    ਵਾਪਸ 0;
}

AVBufferPool *av_ਬਫਰ_pool_init2(size_t ਮਾਪ, ਖਾਲੀ *opaque,
                                   AVBufferRef* (*alloc)(ਖਾਲੀ *opaque, size_t ਮਾਪ),
                                   ਖਾਲੀ (*pool_free)(ਖਾਲੀ *opaque))
{
    AVBufferPool *pool = av_mallocz(ਆਕਾਰ(*pool));
    ਜੇ (!pool)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (ff_mutex_init(&pool->mutex, ਨਿਰਾ)) {
        av_free(pool);
        ਵਾਪਸ ਨਿਰਾ;
    }

    pool->ਮਾਪ      = ਮਾਪ;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_ਬਫਰ_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    ਵਾਪਸ pool;
}

AVBufferPool *av_ਬਫਰ_pool_init(size_t ਮਾਪ, AVBufferRef* (*alloc)(size_t ਮਾਪ))
{
    AVBufferPool *pool = av_mallocz(ਆਕਾਰ(*pool));
    ਜੇ (!pool)
        ਵਾਪਸ ਨਿਰਾ;

    ਜੇ (ff_mutex_init(&pool->mutex, ਨਿਰਾ)) {
        av_free(pool);
        ਵਾਪਸ ਨਿਰਾ;
    }

    pool->ਮਾਪ     = ਮਾਪ;
    pool->alloc    = alloc ? alloc : av_ਬਫਰ_alloc;

    atomic_init(&pool->refcount, 1);

    ਵਾਪਸ pool;
}

ਸਥਿਰ ਖਾਲੀ ਬਫਰ_pool_flush(AVBufferPool *pool)
{
    ਜਦੋਂ (pool->pool) {
        ਬਫਰ_Pool_ਇੰਦਰਾਜ *buf = pool->pool;
        pool->pool = buf->ਅਗਲਾ;

        ਜੇ (buf->ਮੁਕਤ == av_ਬਫਰ_default_free)
            FF_ASAN_UNPOISON(buf->ਅੰਕੜੇ, pool->ਮਾਪ);
        buf->ਮੁਕਤ(buf->opaque, buf->ਅੰਕੜੇ);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
ਸਥਿਰ ਖਾਲੀ ਬਫਰ_pool_free(AVBufferPool *pool)
{
    ਬਫਰ_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    ਜੇ (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

ਖਾਲੀ av_ਬਫਰ_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    ਜੇ (!ppool || !*ppool)
        ਵਾਪਸ;
    pool   = *ppool;
    *ppool = ਨਿਰਾ;

    ff_mutex_ਤਾਲਾ(&pool->mutex);
    ਬਫਰ_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    ਜੇ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        ਬਫਰ_pool_free(pool);
}

ਸਥਿਰ ਖਾਲੀ pool_release_ਬਫਰ(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ)
{
    ਬਫਰ_Pool_ਇੰਦਰਾਜ *buf = opaque;
    AVBufferPool *pool = buf->pool;

    ਜੇ (buf->ਮੁਕਤ == av_ਬਫਰ_default_free)
        FF_ASAN_POISON(buf->ਅੰਕੜੇ, pool->ਮਾਪ);

    ff_mutex_ਤਾਲਾ(&pool->mutex);
    buf->ਅਗਲਾ = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    ਜੇ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        ਬਫਰ_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
ਸਥਿਰ AVBufferRef *pool_alloc_ਬਫਰ(AVBufferPool *pool)
{
    ਬਫਰ_Pool_ਇੰਦਰਾਜ *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->ਮਾਪ) :
                         pool->alloc(pool->ਮਾਪ);
    ਜੇ (!ret)
        ਵਾਪਸ ਨਿਰਾ;

    buf = av_mallocz(ਆਕਾਰ(*buf));
    ਜੇ (!buf) {
        av_ਬਫਰ_unref(&ret);
        ਵਾਪਸ ਨਿਰਾ;
    }

    buf->ਅੰਕੜੇ   = ret->ਬਫਰ->ਅੰਕੜੇ;
    buf->opaque = ret->ਬਫਰ->opaque;
    buf->ਮੁਕਤ   = ret->ਬਫਰ->ਮੁਕਤ;
    buf->pool   = pool;

    ret->ਬਫਰ->opaque = buf;
    ret->ਬਫਰ->ਮੁਕਤ   = pool_release_ਬਫਰ;

    ਵਾਪਸ ret;
}

AVBufferRef *av_ਬਫਰ_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    ਬਫਰ_Pool_ਇੰਦਰਾਜ *buf;

    ff_mutex_ਤਾਲਾ(&pool->mutex);
    buf = pool->pool;
    ਜੇ (buf) {
        memset(&buf->ਬਫਰ, 0, ਆਕਾਰ(buf->ਬਫਰ));
        ret = ਬਫਰ_create(&buf->ਬਫਰ, buf->ਅੰਕੜੇ, pool->ਮਾਪ,
                            pool_release_ਬਫਰ, buf, 0);
        ਜੇ (ret) {
            pool->pool = buf->ਅਗਲਾ;
            buf->ਅਗਲਾ = ਨਿਰਾ;
            buf->ਬਫਰ.flags_ਅੰਦਰੂਨੀ |= ਬਫਰ_FLAG_NO_FREE;
            ਜੇ (buf->ਮੁਕਤ == av_ਬਫਰ_default_free) {
                FF_ASAN_UNPOISON(buf->ਅੰਕੜੇ, pool->ਮਾਪ);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                ਜੇ (!pool->alloc2 && pool->alloc == av_ਬਫਰ_alloc)
                    FF_MEM_UNDEFINED(buf->ਅੰਕੜੇ, pool->ਮਾਪ);
            }
        }
    } ਨਹੀਂਤਾਂ {
        ret = pool_alloc_ਬਫਰ(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    ਜੇ (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ਵਾਪਸ ret;
}

ਖਾਲੀ *av_ਬਫਰ_pool_ਬਫਰ_get_opaque(ਅਚਲ AVBufferRef *ref)
{
    ਬਫਰ_Pool_ਇੰਦਰਾਜ *buf = ref->ਬਫਰ->opaque;
    av_assert0(buf);
    ਵਾਪਸ buf->opaque;
}

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

#అన్తర్భావ <stdatomic.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "avassert.h"
#అన్తర్భావ "buffer_internal.h"
#అన్తర్భావ "common.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ "sanitizer.h"
#అన్తర్భావ "thread.h"

స్థిర AVBufferRef *బఫరు_create(AVBuffer *buf, uint8_t *దత్తాంశం, size_t కొలత,
                                  శూన్య (*విడుదల)(శూన్య *opaque, uint8_t *దత్తాంశం),
                                  శూన్య *opaque, పూర్ణాంకం flags)
{
    AVBufferRef *ref = ఖాళీ;

    buf->దత్తాంశం     = దత్తాంశం;
    buf->కొలత     = కొలత;
    buf->విడుదల     = విడుదల ? విడుదల : av_బఫరు_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(పరిమాణం(*ref));
    ఒకవేళ (!ref)
        తిరిగి ఖాళీ;

    ref->బఫరు = buf;
    ref->దత్తాంశం   = దత్తాంశం;
    ref->కొలత   = కొలత;

    తిరిగి ref;
}

AVBufferRef *av_బఫరు_create(uint8_t *దత్తాంశం, size_t కొలత,
                              శూన్య (*విడుదల)(శూన్య *opaque, uint8_t *దత్తాంశం),
                              శూన్య *opaque, పూర్ణాంకం flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(పరిమాణం(*buf));
    ఒకవేళ (!buf)
        తిరిగి ఖాళీ;

    ret = బఫరు_create(buf, దత్తాంశం, కొలత, విడుదల, opaque, flags);
    ఒకవేళ (!ret) {
        av_free(buf);
        తిరిగి ఖాళీ;
    }
    తిరిగి ret;
}

శూన్య av_బఫరు_default_free(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    av_free(దత్తాంశం);
}

AVBufferRef *av_బఫరు_alloc(size_t కొలత)
{
    AVBufferRef *ret = ఖాళీ;
    uint8_t    *దత్తాంశం = ఖాళీ;

    దత్తాంశం = av_malloc(కొలత);
    ఒకవేళ (!దత్తాంశం)
        తిరిగి ఖాళీ;

    ret = av_బఫరు_create(దత్తాంశం, కొలత, av_బఫరు_default_free, ఖాళీ, 0);
    ఒకవేళ (!ret)
        av_freep(&దత్తాంశం);

    తిరిగి ret;
}

AVBufferRef *av_బఫరు_allocz(size_t కొలత)
{
    AVBufferRef *ret = av_బఫరు_alloc(కొలత);
    ఒకవేళ (!ret)
        తిరిగి ఖాళీ;

    memset(ret->దత్తాంశం, 0, కొలత);
    తిరిగి ret;
}

AVBufferRef *av_బఫరు_ref(స్థిరరాశి AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(పరిమాణం(*ret));

    ఒకవేళ (!ret)
        తిరిగి ఖాళీ;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->బఫరు->refcount, 1, memory_order_relaxed);

    తిరిగి ret;
}

స్థిర శూన్య బఫరు_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->బఫరు;

    ఒకవేళ (src) {
        **dst = **src;
        av_freep(src);
    } లేకపోతే
        av_freep(dst);

    ఒకవేళ (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        పూర్ణాంకం free_avbuffer = !(b->flags_అంతర్గత & బఫరు_FLAG_NO_FREE);
        b->విడుదల(b->opaque, b->దత్తాంశం);
        ఒకవేళ (free_avbuffer)
            av_free(b);
    }
}

శూన్య av_బఫరు_unref(AVBufferRef **buf)
{
    ఒకవేళ (!buf || !*buf)
        తిరిగి;

    బఫరు_replace(buf, ఖాళీ);
}

పూర్ణాంకం av_బఫరు_is_writable(స్థిరరాశి AVBufferRef *buf)
{
    ఒకవేళ (buf->బఫరు->flags & AV_బఫరు_FLAG_READONLY)
        తిరిగి 0;

    తిరిగి atomic_load(&buf->బఫరు->refcount) == 1;
}

శూన్య *av_బఫరు_get_opaque(స్థిరరాశి AVBufferRef *buf)
{
    తిరిగి buf->బఫరు->opaque;
}

పూర్ణాంకం av_బఫరు_get_ref_లెక్క(స్థిరరాశి AVBufferRef *buf)
{
    తిరిగి atomic_load(&buf->బఫరు->refcount);
}

పూర్ణాంకం av_బఫరు_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    ఒకవేళ (av_బఫరు_is_writable(buf))
        తిరిగి 0;

    newbuf = av_బఫరు_alloc(buf->కొలత);
    ఒకవేళ (!newbuf)
        తిరిగి AVERROR(ENOMEM);

    జ్ఞాపకం_నకలు(newbuf->దత్తాంశం, buf->దత్తాంశం, buf->కొలత);

    బఫరు_replace(pbuf, &newbuf);

    తిరిగి 0;
}

పూర్ణాంకం av_బఫరు_realloc(AVBufferRef **pbuf, size_t కొలత)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    పూర్ణాంకం ret;

    ఒకవేళ (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *దత్తాంశం = av_realloc(ఖాళీ, కొలత);
        ఒకవేళ (!దత్తాంశం)
            తిరిగి AVERROR(ENOMEM);

        buf = av_బఫరు_create(దత్తాంశం, కొలత, av_బఫరు_default_free, ఖాళీ, 0);
        ఒకవేళ (!buf) {
            av_freep(&దత్తాంశం);
            తిరిగి AVERROR(ENOMEM);
        }

        buf->బఫరు->flags_అంతర్గత |= బఫరు_FLAG_REALLOCATABLE;
        *pbuf = buf;

        తిరిగి 0;
    } లేకపోతే ఒకవేళ (buf->కొలత == కొలత)
        తిరిగి 0;

    ఒకవేళ (!(buf->బఫరు->flags_అంతర్గత & బఫరు_FLAG_REALLOCATABLE) ||
        !av_బఫరు_is_writable(buf) || buf->దత్తాంశం != buf->బఫరు->దత్తాంశం) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = ఖాళీ;

        ret = av_బఫరు_realloc(&new, కొలత);
        ఒకవేళ (ret < 0)
            తిరిగి ret;

        జ్ఞాపకం_నకలు(new->దత్తాంశం, buf->దత్తాంశం, FFMIN(కొలత, buf->కొలత));

        బఫరు_replace(pbuf, &new);
        తిరిగి 0;
    }

    tmp = av_realloc(buf->బఫరు->దత్తాంశం, కొలత);
    ఒకవేళ (!tmp)
        తిరిగి AVERROR(ENOMEM);

    buf->బఫరు->దత్తాంశం = buf->దత్తాంశం = tmp;
    buf->బఫరు->కొలత = buf->కొలత = కొలత;
    తిరిగి 0;
}

పూర్ణాంకం av_బఫరు_replace(AVBufferRef **pdst, స్థిరరాశి AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    ఒకవేళ (!src) {
        av_బఫరు_unref(pdst);
        తిరిగి 0;
    }

    ఒకవేళ (dst && dst->బఫరు == src->బఫరు) {
        /* make sure the data pointers match */
        dst->దత్తాంశం = src->దత్తాంశం;
        dst->కొలత = src->కొలత;
        తిరిగి 0;
    }

    tmp = av_బఫరు_ref(src);
    ఒకవేళ (!tmp)
        తిరిగి AVERROR(ENOMEM);

    av_బఫరు_unref(pdst);
    *pdst = tmp;
    తిరిగి 0;
}

AVBufferPool *av_బఫరు_pool_init2(size_t కొలత, శూన్య *opaque,
                                   AVBufferRef* (*alloc)(శూన్య *opaque, size_t కొలత),
                                   శూన్య (*pool_free)(శూన్య *opaque))
{
    AVBufferPool *pool = av_mallocz(పరిమాణం(*pool));
    ఒకవేళ (!pool)
        తిరిగి ఖాళీ;

    ఒకవేళ (ff_mutex_init(&pool->mutex, ఖాళీ)) {
        av_free(pool);
        తిరిగి ఖాళీ;
    }

    pool->కొలత      = కొలత;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_బఫరు_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    తిరిగి pool;
}

AVBufferPool *av_బఫరు_pool_init(size_t కొలత, AVBufferRef* (*alloc)(size_t కొలత))
{
    AVBufferPool *pool = av_mallocz(పరిమాణం(*pool));
    ఒకవేళ (!pool)
        తిరిగి ఖాళీ;

    ఒకవేళ (ff_mutex_init(&pool->mutex, ఖాళీ)) {
        av_free(pool);
        తిరిగి ఖాళీ;
    }

    pool->కొలత     = కొలత;
    pool->alloc    = alloc ? alloc : av_బఫరు_alloc;

    atomic_init(&pool->refcount, 1);

    తిరిగి pool;
}

స్థిర శూన్య బఫరు_pool_flush(AVBufferPool *pool)
{
    అయితే (pool->pool) {
        బఫరు_Pool_నమోదు *buf = pool->pool;
        pool->pool = buf->తదుపరి;

        ఒకవేళ (buf->విడుదల == av_బఫరు_default_free)
            FF_ASAN_UNPOISON(buf->దత్తాంశం, pool->కొలత);
        buf->విడుదల(buf->opaque, buf->దత్తాంశం);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
స్థిర శూన్య బఫరు_pool_free(AVBufferPool *pool)
{
    బఫరు_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    ఒకవేళ (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

శూన్య av_బఫరు_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    ఒకవేళ (!ppool || !*ppool)
        తిరిగి;
    pool   = *ppool;
    *ppool = ఖాళీ;

    ff_mutex_తాళం(&pool->mutex);
    బఫరు_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    ఒకవేళ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        బఫరు_pool_free(pool);
}

స్థిర శూన్య pool_release_బఫరు(శూన్య *opaque, uint8_t *దత్తాంశం)
{
    బఫరు_Pool_నమోదు *buf = opaque;
    AVBufferPool *pool = buf->pool;

    ఒకవేళ (buf->విడుదల == av_బఫరు_default_free)
        FF_ASAN_POISON(buf->దత్తాంశం, pool->కొలత);

    ff_mutex_తాళం(&pool->mutex);
    buf->తదుపరి = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    ఒకవేళ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        బఫరు_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
స్థిర AVBufferRef *pool_alloc_బఫరు(AVBufferPool *pool)
{
    బఫరు_Pool_నమోదు *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->కొలత) :
                         pool->alloc(pool->కొలత);
    ఒకవేళ (!ret)
        తిరిగి ఖాళీ;

    buf = av_mallocz(పరిమాణం(*buf));
    ఒకవేళ (!buf) {
        av_బఫరు_unref(&ret);
        తిరిగి ఖాళీ;
    }

    buf->దత్తాంశం   = ret->బఫరు->దత్తాంశం;
    buf->opaque = ret->బఫరు->opaque;
    buf->విడుదల   = ret->బఫరు->విడుదల;
    buf->pool   = pool;

    ret->బఫరు->opaque = buf;
    ret->బఫరు->విడుదల   = pool_release_బఫరు;

    తిరిగి ret;
}

AVBufferRef *av_బఫరు_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    బఫరు_Pool_నమోదు *buf;

    ff_mutex_తాళం(&pool->mutex);
    buf = pool->pool;
    ఒకవేళ (buf) {
        memset(&buf->బఫరు, 0, పరిమాణం(buf->బఫరు));
        ret = బఫరు_create(&buf->బఫరు, buf->దత్తాంశం, pool->కొలత,
                            pool_release_బఫరు, buf, 0);
        ఒకవేళ (ret) {
            pool->pool = buf->తదుపరి;
            buf->తదుపరి = ఖాళీ;
            buf->బఫరు.flags_అంతర్గత |= బఫరు_FLAG_NO_FREE;
            ఒకవేళ (buf->విడుదల == av_బఫరు_default_free) {
                FF_ASAN_UNPOISON(buf->దత్తాంశం, pool->కొలత);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                ఒకవేళ (!pool->alloc2 && pool->alloc == av_బఫరు_alloc)
                    FF_MEM_UNDEFINED(buf->దత్తాంశం, pool->కొలత);
            }
        }
    } లేకపోతే {
        ret = pool_alloc_బఫరు(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    ఒకవేళ (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    తిరిగి ret;
}

శూన్య *av_బఫరు_pool_బఫరు_get_opaque(స్థిరరాశి AVBufferRef *ref)
{
    బఫరు_Pool_నమోదు *buf = ref->బఫరు->opaque;
    av_assert0(buf);
    తిరిగి buf->opaque;
}

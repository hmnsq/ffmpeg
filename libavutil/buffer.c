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

ساكن AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  فراغ (*حرر)(فراغ *opaque, uint8_t *data),
                                  فراغ *opaque, صحيح flags)
{
    AVBufferRef *ref = عدم;

    buf->data     = data;
    buf->size     = size;
    buf->حرر     = حرر ? حرر : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(حجم(*ref));
    ܐܢ (!ref)
        ܦܢܐ عدم;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    ܦܢܐ ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              فراغ (*حرر)(فراغ *opaque, uint8_t *data),
                              فراغ *opaque, صحيح flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(حجم(*buf));
    ܐܢ (!buf)
        ܦܢܐ عدم;

    ret = buffer_create(buf, data, size, حرر, opaque, flags);
    ܐܢ (!ret) {
        av_free(buf);
        ܦܢܐ عدم;
    }
    ܦܢܐ ret;
}

فراغ av_buffer_default_free(فراغ *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = عدم;
    uint8_t    *data = عدم;

    data = av_malloc(size);
    ܐܢ (!data)
        ܦܢܐ عدم;

    ret = av_buffer_create(data, size, av_buffer_default_free, عدم, 0);
    ܐܢ (!ret)
        av_freep(&data);

    ܦܢܐ ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    ܐܢ (!ret)
        ܦܢܐ عدم;

    memset(ret->data, 0, size);
    ܦܢܐ ret;
}

AVBufferRef *av_buffer_ref(ثابت AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(حجم(*ret));

    ܐܢ (!ret)
        ܦܢܐ عدم;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    ܦܢܐ ret;
}

ساكن فراغ buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    ܐܢ (src) {
        **dst = **src;
        av_freep(src);
    } ܐܚܪܢܐ
        av_freep(dst);

    ܐܢ (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        صحيح free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->حرر(b->opaque, b->data);
        ܐܢ (free_avbuffer)
            av_free(b);
    }
}

فراغ av_buffer_unref(AVBufferRef **buf)
{
    ܐܢ (!buf || !*buf)
        ܦܢܐ;

    buffer_replace(buf, عدم);
}

صحيح av_buffer_is_writable(ثابت AVBufferRef *buf)
{
    ܐܢ (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        ܦܢܐ 0;

    ܦܢܐ atomic_load(&buf->buffer->refcount) == 1;
}

فراغ *av_buffer_get_opaque(ثابت AVBufferRef *buf)
{
    ܦܢܐ buf->buffer->opaque;
}

صحيح av_buffer_get_ref_count(ثابت AVBufferRef *buf)
{
    ܦܢܐ atomic_load(&buf->buffer->refcount);
}

صحيح av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    ܐܢ (av_buffer_is_writable(buf))
        ܦܢܐ 0;

    newbuf = av_buffer_alloc(buf->size);
    ܐܢ (!newbuf)
        ܦܢܐ AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    ܦܢܐ 0;
}

صحيح av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    صحيح ret;

    ܐܢ (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(عدم, size);
        ܐܢ (!data)
            ܦܢܐ AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, عدم, 0);
        ܐܢ (!buf) {
            av_freep(&data);
            ܦܢܐ AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        ܦܢܐ 0;
    } ܐܚܪܢܐ ܐܢ (buf->size == size)
        ܦܢܐ 0;

    ܐܢ (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = عدم;

        ret = av_buffer_realloc(&new, size);
        ܐܢ (ret < 0)
            ܦܢܐ ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        ܦܢܐ 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    ܐܢ (!tmp)
        ܦܢܐ AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    ܦܢܐ 0;
}

صحيح av_buffer_replace(AVBufferRef **pdst, ثابت AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    ܐܢ (!src) {
        av_buffer_unref(pdst);
        ܦܢܐ 0;
    }

    ܐܢ (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        ܦܢܐ 0;
    }

    tmp = av_buffer_ref(src);
    ܐܢ (!tmp)
        ܦܢܐ AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    ܦܢܐ 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, فراغ *opaque,
                                   AVBufferRef* (*alloc)(فراغ *opaque, size_t size),
                                   فراغ (*pool_free)(فراغ *opaque))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    ܐܢ (!pool)
        ܦܢܐ عدم;

    ܐܢ (ff_mutex_init(&pool->mutex, عدم)) {
        av_free(pool);
        ܦܢܐ عدم;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    ܦܢܐ pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    ܐܢ (!pool)
        ܦܢܐ عدم;

    ܐܢ (ff_mutex_init(&pool->mutex, عدم)) {
        av_free(pool);
        ܦܢܐ عدم;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    ܦܢܐ pool;
}

ساكن فراغ buffer_pool_flush(AVBufferPool *pool)
{
    ܟܡܐ (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        ܐܢ (buf->حرر == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->حرر(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
ساكن فراغ buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    ܐܢ (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

فراغ av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    ܐܢ (!ppool || !*ppool)
        ܦܢܐ;
    pool   = *ppool;
    *ppool = عدم;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    ܐܢ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

ساكن فراغ pool_release_buffer(فراغ *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    ܐܢ (buf->حرر == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    ܐܢ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
ساكن AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    ܐܢ (!ret)
        ܦܢܐ عدم;

    buf = av_mallocz(حجم(*buf));
    ܐܢ (!buf) {
        av_buffer_unref(&ret);
        ܦܢܐ عدم;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->حرر   = ret->buffer->حرر;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->حرر   = pool_release_buffer;

    ܦܢܐ ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    ܐܢ (buf) {
        memset(&buf->buffer, 0, حجم(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        ܐܢ (ret) {
            pool->pool = buf->next;
            buf->next = عدم;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            ܐܢ (buf->حرر == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                ܐܢ (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } ܐܚܪܢܐ {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    ܐܢ (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ܦܢܐ ret;
}

فراغ *av_buffer_pool_buffer_get_opaque(ثابت AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    ܦܢܐ buf->opaque;
}

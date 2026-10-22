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

ایستا AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  تهی (*آزاد)(تهی *opaque, uint8_t *data),
                                  تهی *opaque, صحیح flags)
{
    AVBufferRef *ref = پوچ;

    buf->data     = data;
    buf->size     = size;
    buf->آزاد     = آزاد ? آزاد : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(اندازه(*ref));
    اگر (!ref)
        بازگشت پوچ;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    بازگشت ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              تهی (*آزاد)(تهی *opaque, uint8_t *data),
                              تهی *opaque, صحیح flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(اندازه(*buf));
    اگر (!buf)
        بازگشت پوچ;

    ret = buffer_create(buf, data, size, آزاد, opaque, flags);
    اگر (!ret) {
        av_free(buf);
        بازگشت پوچ;
    }
    بازگشت ret;
}

تهی av_buffer_default_free(تهی *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = پوچ;
    uint8_t    *data = پوچ;

    data = av_malloc(size);
    اگر (!data)
        بازگشت پوچ;

    ret = av_buffer_create(data, size, av_buffer_default_free, پوچ, 0);
    اگر (!ret)
        av_freep(&data);

    بازگشت ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    اگر (!ret)
        بازگشت پوچ;

    memset(ret->data, 0, size);
    بازگشت ret;
}

AVBufferRef *av_buffer_ref(ثابت AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(اندازه(*ret));

    اگر (!ret)
        بازگشت پوچ;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    بازگشت ret;
}

ایستا تهی buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    اگر (src) {
        **dst = **src;
        av_freep(src);
    } وگرنه
        av_freep(dst);

    اگر (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        صحیح free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->آزاد(b->opaque, b->data);
        اگر (free_avbuffer)
            av_free(b);
    }
}

تهی av_buffer_unref(AVBufferRef **buf)
{
    اگر (!buf || !*buf)
        بازگشت;

    buffer_replace(buf, پوچ);
}

صحیح av_buffer_is_writable(ثابت AVBufferRef *buf)
{
    اگر (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        بازگشت 0;

    بازگشت atomic_load(&buf->buffer->refcount) == 1;
}

تهی *av_buffer_get_opaque(ثابت AVBufferRef *buf)
{
    بازگشت buf->buffer->opaque;
}

صحیح av_buffer_get_ref_شمار(ثابت AVBufferRef *buf)
{
    بازگشت atomic_load(&buf->buffer->refcount);
}

صحیح av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    اگر (av_buffer_is_writable(buf))
        بازگشت 0;

    newbuf = av_buffer_alloc(buf->size);
    اگر (!newbuf)
        بازگشت AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    بازگشت 0;
}

صحیح av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    صحیح ret;

    اگر (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(پوچ, size);
        اگر (!data)
            بازگشت AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, پوچ, 0);
        اگر (!buf) {
            av_freep(&data);
            بازگشت AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        بازگشت 0;
    } وگرنه اگر (buf->size == size)
        بازگشت 0;

    اگر (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = پوچ;

        ret = av_buffer_realloc(&new, size);
        اگر (ret < 0)
            بازگشت ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        بازگشت 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    اگر (!tmp)
        بازگشت AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    بازگشت 0;
}

صحیح av_buffer_replace(AVBufferRef **pdst, ثابت AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    اگر (!src) {
        av_buffer_unref(pdst);
        بازگشت 0;
    }

    اگر (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        بازگشت 0;
    }

    tmp = av_buffer_ref(src);
    اگر (!tmp)
        بازگشت AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    بازگشت 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, تهی *opaque,
                                   AVBufferRef* (*alloc)(تهی *opaque, size_t size),
                                   تهی (*pool_free)(تهی *opaque))
{
    AVBufferPool *pool = av_mallocz(اندازه(*pool));
    اگر (!pool)
        بازگشت پوچ;

    اگر (ff_mutex_init(&pool->mutex, پوچ)) {
        av_free(pool);
        بازگشت پوچ;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    بازگشت pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(اندازه(*pool));
    اگر (!pool)
        بازگشت پوچ;

    اگر (ff_mutex_init(&pool->mutex, پوچ)) {
        av_free(pool);
        بازگشت پوچ;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    بازگشت pool;
}

ایستا تهی buffer_pool_flush(AVBufferPool *pool)
{
    وقتی (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        اگر (buf->آزاد == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->آزاد(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
ایستا تهی buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    اگر (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

تهی av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    اگر (!ppool || !*ppool)
        بازگشت;
    pool   = *ppool;
    *ppool = پوچ;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    اگر (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

ایستا تهی pool_release_buffer(تهی *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    اگر (buf->آزاد == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    اگر (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
ایستا AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    اگر (!ret)
        بازگشت پوچ;

    buf = av_mallocz(اندازه(*buf));
    اگر (!buf) {
        av_buffer_unref(&ret);
        بازگشت پوچ;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->آزاد   = ret->buffer->آزاد;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->آزاد   = pool_release_buffer;

    بازگشت ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    اگر (buf) {
        memset(&buf->buffer, 0, اندازه(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        اگر (ret) {
            pool->pool = buf->next;
            buf->next = پوچ;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            اگر (buf->آزاد == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                اگر (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } وگرنه {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    اگر (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    بازگشت ret;
}

تهی *av_buffer_pool_buffer_get_opaque(ثابت AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    بازگشت buf->opaque;
}

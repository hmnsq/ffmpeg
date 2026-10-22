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
    𐤀𐤌 (!ref)
        أرجع عدم;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    أرجع ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              فراغ (*حرر)(فراغ *opaque, uint8_t *data),
                              فراغ *opaque, صحيح flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(حجم(*buf));
    𐤀𐤌 (!buf)
        أرجع عدم;

    ret = buffer_create(buf, data, size, حرر, opaque, flags);
    𐤀𐤌 (!ret) {
        av_free(buf);
        أرجع عدم;
    }
    أرجع ret;
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
    𐤀𐤌 (!data)
        أرجع عدم;

    ret = av_buffer_create(data, size, av_buffer_default_free, عدم, 0);
    𐤀𐤌 (!ret)
        av_freep(&data);

    أرجع ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    𐤀𐤌 (!ret)
        أرجع عدم;

    memset(ret->data, 0, size);
    أرجع ret;
}

AVBufferRef *av_buffer_ref(ثابت AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(حجم(*ret));

    𐤀𐤌 (!ret)
        أرجع عدم;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    أرجع ret;
}

ساكن فراغ buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    𐤀𐤌 (src) {
        **dst = **src;
        av_freep(src);
    } وإلا
        av_freep(dst);

    𐤀𐤌 (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        صحيح free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->حرر(b->opaque, b->data);
        𐤀𐤌 (free_avbuffer)
            av_free(b);
    }
}

فراغ av_buffer_unref(AVBufferRef **buf)
{
    𐤀𐤌 (!buf || !*buf)
        أرجع;

    buffer_replace(buf, عدم);
}

صحيح av_buffer_is_writable(ثابت AVBufferRef *buf)
{
    𐤀𐤌 (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        أرجع 0;

    أرجع atomic_load(&buf->buffer->refcount) == 1;
}

فراغ *av_buffer_get_opaque(ثابت AVBufferRef *buf)
{
    أرجع buf->buffer->opaque;
}

صحيح av_buffer_get_ref_count(ثابت AVBufferRef *buf)
{
    أرجع atomic_load(&buf->buffer->refcount);
}

صحيح av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    𐤀𐤌 (av_buffer_is_writable(buf))
        أرجع 0;

    newbuf = av_buffer_alloc(buf->size);
    𐤀𐤌 (!newbuf)
        أرجع AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    أرجع 0;
}

صحيح av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    صحيح ret;

    𐤀𐤌 (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(عدم, size);
        𐤀𐤌 (!data)
            أرجع AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, عدم, 0);
        𐤀𐤌 (!buf) {
            av_freep(&data);
            أرجع AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        أرجع 0;
    } وإلا 𐤀𐤌 (buf->size == size)
        أرجع 0;

    𐤀𐤌 (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = عدم;

        ret = av_buffer_realloc(&new, size);
        𐤀𐤌 (ret < 0)
            أرجع ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        أرجع 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    𐤀𐤌 (!tmp)
        أرجع AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    أرجع 0;
}

صحيح av_buffer_replace(AVBufferRef **pdst, ثابت AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    𐤀𐤌 (!src) {
        av_buffer_unref(pdst);
        أرجع 0;
    }

    𐤀𐤌 (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        أرجع 0;
    }

    tmp = av_buffer_ref(src);
    𐤀𐤌 (!tmp)
        أرجع AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    أرجع 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, فراغ *opaque,
                                   AVBufferRef* (*alloc)(فراغ *opaque, size_t size),
                                   فراغ (*pool_free)(فراغ *opaque))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    𐤀𐤌 (!pool)
        أرجع عدم;

    𐤀𐤌 (ff_mutex_init(&pool->mutex, عدم)) {
        av_free(pool);
        أرجع عدم;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    أرجع pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(حجم(*pool));
    𐤀𐤌 (!pool)
        أرجع عدم;

    𐤀𐤌 (ff_mutex_init(&pool->mutex, عدم)) {
        av_free(pool);
        أرجع عدم;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    أرجع pool;
}

ساكن فراغ buffer_pool_flush(AVBufferPool *pool)
{
    طالما (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        𐤀𐤌 (buf->حرر == av_buffer_default_free)
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

    𐤀𐤌 (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

فراغ av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    𐤀𐤌 (!ppool || !*ppool)
        أرجع;
    pool   = *ppool;
    *ppool = عدم;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    𐤀𐤌 (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

ساكن فراغ pool_release_buffer(فراغ *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    𐤀𐤌 (buf->حرر == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    𐤀𐤌 (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
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
    𐤀𐤌 (!ret)
        أرجع عدم;

    buf = av_mallocz(حجم(*buf));
    𐤀𐤌 (!buf) {
        av_buffer_unref(&ret);
        أرجع عدم;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->حرر   = ret->buffer->حرر;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->حرر   = pool_release_buffer;

    أرجع ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    𐤀𐤌 (buf) {
        memset(&buf->buffer, 0, حجم(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        𐤀𐤌 (ret) {
            pool->pool = buf->next;
            buf->next = عدم;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            𐤀𐤌 (buf->حرر == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                𐤀𐤌 (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } وإلا {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    𐤀𐤌 (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    أرجع ret;
}

فراغ *av_buffer_pool_buffer_get_opaque(ثابت AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    أرجع buf->opaque;
}

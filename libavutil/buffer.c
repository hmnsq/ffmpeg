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

#अन्तर्भाव "avassert.h"
#अन्तर्भाव "buffer_internal.h"
#अन्तर्भाव "common.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव "sanitizer.h"
#अन्तर्भाव "thread.h"

स्थिर AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  शून्य (*मुक्त)(शून्य *opaque, uint8_t *data),
                                  शून्य *opaque, पूर्णाङ्क flags)
{
    AVBufferRef *ref = रिक्त;

    buf->data     = data;
    buf->size     = size;
    buf->मुक्त     = मुक्त ? मुक्त : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(परिमाण(*ref));
    यदि (!ref)
        प्रत्यागम रिक्त;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    प्रत्यागम ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              शून्य (*मुक्त)(शून्य *opaque, uint8_t *data),
                              शून्य *opaque, पूर्णाङ्क flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(परिमाण(*buf));
    यदि (!buf)
        प्रत्यागम रिक्त;

    ret = buffer_create(buf, data, size, मुक्त, opaque, flags);
    यदि (!ret) {
        av_free(buf);
        प्रत्यागम रिक्त;
    }
    प्रत्यागम ret;
}

शून्य av_buffer_default_free(शून्य *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = रिक्त;
    uint8_t    *data = रिक्त;

    data = av_malloc(size);
    यदि (!data)
        प्रत्यागम रिक्त;

    ret = av_buffer_create(data, size, av_buffer_default_free, रिक्त, 0);
    यदि (!ret)
        av_freep(&data);

    प्रत्यागम ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    यदि (!ret)
        प्रत्यागम रिक्त;

    memset(ret->data, 0, size);
    प्रत्यागम ret;
}

AVBufferRef *av_buffer_ref(ध्रुव AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(परिमाण(*ret));

    यदि (!ret)
        प्रत्यागम रिक्त;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    प्रत्यागम ret;
}

स्थिर शून्य buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    यदि (src) {
        **dst = **src;
        av_freep(src);
    } अन्यथा
        av_freep(dst);

    यदि (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        पूर्णाङ्क free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->मुक्त(b->opaque, b->data);
        यदि (free_avbuffer)
            av_free(b);
    }
}

शून्य av_buffer_unref(AVBufferRef **buf)
{
    यदि (!buf || !*buf)
        प्रत्यागम;

    buffer_replace(buf, रिक्त);
}

पूर्णाङ्क av_buffer_is_writable(ध्रुव AVBufferRef *buf)
{
    यदि (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        प्रत्यागम 0;

    प्रत्यागम atomic_load(&buf->buffer->refcount) == 1;
}

शून्य *av_buffer_get_opaque(ध्रुव AVBufferRef *buf)
{
    प्रत्यागम buf->buffer->opaque;
}

पूर्णाङ्क av_buffer_get_ref_मोजणी(ध्रुव AVBufferRef *buf)
{
    प्रत्यागम atomic_load(&buf->buffer->refcount);
}

पूर्णाङ्क av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    यदि (av_buffer_is_writable(buf))
        प्रत्यागम 0;

    newbuf = av_buffer_alloc(buf->size);
    यदि (!newbuf)
        प्रत्यागम AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    प्रत्यागम 0;
}

पूर्णाङ्क av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    पूर्णाङ्क ret;

    यदि (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(रिक्त, size);
        यदि (!data)
            प्रत्यागम AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, रिक्त, 0);
        यदि (!buf) {
            av_freep(&data);
            प्रत्यागम AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        प्रत्यागम 0;
    } अन्यथा यदि (buf->size == size)
        प्रत्यागम 0;

    यदि (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = रिक्त;

        ret = av_buffer_realloc(&new, size);
        यदि (ret < 0)
            प्रत्यागम ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        प्रत्यागम 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    यदि (!tmp)
        प्रत्यागम AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    प्रत्यागम 0;
}

पूर्णाङ्क av_buffer_replace(AVBufferRef **pdst, ध्रुव AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    यदि (!src) {
        av_buffer_unref(pdst);
        प्रत्यागम 0;
    }

    यदि (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        प्रत्यागम 0;
    }

    tmp = av_buffer_ref(src);
    यदि (!tmp)
        प्रत्यागम AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    प्रत्यागम 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, शून्य *opaque,
                                   AVBufferRef* (*alloc)(शून्य *opaque, size_t size),
                                   शून्य (*pool_free)(शून्य *opaque))
{
    AVBufferPool *pool = av_mallocz(परिमाण(*pool));
    यदि (!pool)
        प्रत्यागम रिक्त;

    यदि (ff_mutex_init(&pool->mutex, रिक्त)) {
        av_free(pool);
        प्रत्यागम रिक्त;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    प्रत्यागम pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(परिमाण(*pool));
    यदि (!pool)
        प्रत्यागम रिक्त;

    यदि (ff_mutex_init(&pool->mutex, रिक्त)) {
        av_free(pool);
        प्रत्यागम रिक्त;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    प्रत्यागम pool;
}

स्थिर शून्य buffer_pool_flush(AVBufferPool *pool)
{
    यावत् (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        यदि (buf->मुक्त == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->मुक्त(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
स्थिर शून्य buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    यदि (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

शून्य av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    यदि (!ppool || !*ppool)
        प्रत्यागम;
    pool   = *ppool;
    *ppool = रिक्त;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    यदि (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

स्थिर शून्य pool_release_buffer(शून्य *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    यदि (buf->मुक्त == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    यदि (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
स्थिर AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    यदि (!ret)
        प्रत्यागम रिक्त;

    buf = av_mallocz(परिमाण(*buf));
    यदि (!buf) {
        av_buffer_unref(&ret);
        प्रत्यागम रिक्त;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->मुक्त   = ret->buffer->मुक्त;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->मुक्त   = pool_release_buffer;

    प्रत्यागम ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    यदि (buf) {
        memset(&buf->buffer, 0, परिमाण(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        यदि (ret) {
            pool->pool = buf->next;
            buf->next = रिक्त;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            यदि (buf->मुक्त == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                यदि (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } अन्यथा {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    यदि (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    प्रत्यागम ret;
}

शून्य *av_buffer_pool_buffer_get_opaque(ध्रुव AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    प्रत्यागम buf->opaque;
}

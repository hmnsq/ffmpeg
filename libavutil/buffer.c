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

स्थिर AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, माप_प्रकार size,
                                  शून्य (*मुक्त)(शून्य *opaque, uint8_t *data),
                                  शून्य *opaque, पूर्णांक flags)
{
    AVBufferRef *ref = रिक्त;

    buf->data     = data;
    buf->size     = size;
    buf->मुक्त     = मुक्त ? मुक्त : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(आकार(*ref));
    जर (!ref)
        परत रिक्त;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    परत ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, माप_प्रकार size,
                              शून्य (*मुक्त)(शून्य *opaque, uint8_t *data),
                              शून्य *opaque, पूर्णांक flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(आकार(*buf));
    जर (!buf)
        परत रिक्त;

    ret = buffer_create(buf, data, size, मुक्त, opaque, flags);
    जर (!ret) {
        av_free(buf);
        परत रिक्त;
    }
    परत ret;
}

शून्य av_buffer_default_free(शून्य *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(माप_प्रकार size)
{
    AVBufferRef *ret = रिक्त;
    uint8_t    *data = रिक्त;

    data = av_malloc(size);
    जर (!data)
        परत रिक्त;

    ret = av_buffer_create(data, size, av_buffer_default_free, रिक्त, 0);
    जर (!ret)
        av_freep(&data);

    परत ret;
}

AVBufferRef *av_buffer_allocz(माप_प्रकार size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    जर (!ret)
        परत रिक्त;

    स_रखो(ret->data, 0, size);
    परत ret;
}

AVBufferRef *av_buffer_ref(स्थिरांक AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(आकार(*ret));

    जर (!ret)
        परत रिक्त;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    परत ret;
}

स्थिर शून्य buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    जर (src) {
        **dst = **src;
        av_freep(src);
    } अन्यथा
        av_freep(dst);

    जर (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        पूर्णांक free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->मुक्त(b->opaque, b->data);
        जर (free_avbuffer)
            av_free(b);
    }
}

शून्य av_buffer_unref(AVBufferRef **buf)
{
    जर (!buf || !*buf)
        परत;

    buffer_replace(buf, रिक्त);
}

पूर्णांक av_buffer_is_writable(स्थिरांक AVBufferRef *buf)
{
    जर (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        परत 0;

    परत atomic_load(&buf->buffer->refcount) == 1;
}

शून्य *av_buffer_get_opaque(स्थिरांक AVBufferRef *buf)
{
    परत buf->buffer->opaque;
}

पूर्णांक av_buffer_get_ref_मोजणी(स्थिरांक AVBufferRef *buf)
{
    परत atomic_load(&buf->buffer->refcount);
}

पूर्णांक av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    जर (av_buffer_is_writable(buf))
        परत 0;

    newbuf = av_buffer_alloc(buf->size);
    जर (!newbuf)
        परत AVERROR(ENOMEM);

    स_नकल(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    परत 0;
}

पूर्णांक av_buffer_realloc(AVBufferRef **pbuf, माप_प्रकार size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    पूर्णांक ret;

    जर (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(रिक्त, size);
        जर (!data)
            परत AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, रिक्त, 0);
        जर (!buf) {
            av_freep(&data);
            परत AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        परत 0;
    } अन्यथा जर (buf->size == size)
        परत 0;

    जर (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = रिक्त;

        ret = av_buffer_realloc(&new, size);
        जर (ret < 0)
            परत ret;

        स_नकल(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        परत 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    जर (!tmp)
        परत AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    परत 0;
}

पूर्णांक av_buffer_replace(AVBufferRef **pdst, स्थिरांक AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    जर (!src) {
        av_buffer_unref(pdst);
        परत 0;
    }

    जर (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        परत 0;
    }

    tmp = av_buffer_ref(src);
    जर (!tmp)
        परत AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    परत 0;
}

AVBufferPool *av_buffer_pool_init2(माप_प्रकार size, शून्य *opaque,
                                   AVBufferRef* (*alloc)(शून्य *opaque, माप_प्रकार size),
                                   शून्य (*pool_free)(शून्य *opaque))
{
    AVBufferPool *pool = av_mallocz(आकार(*pool));
    जर (!pool)
        परत रिक्त;

    जर (ff_mutex_init(&pool->mutex, रिक्त)) {
        av_free(pool);
        परत रिक्त;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    परत pool;
}

AVBufferPool *av_buffer_pool_init(माप_प्रकार size, AVBufferRef* (*alloc)(माप_प्रकार size))
{
    AVBufferPool *pool = av_mallocz(आकार(*pool));
    जर (!pool)
        परत रिक्त;

    जर (ff_mutex_init(&pool->mutex, रिक्त)) {
        av_free(pool);
        परत रिक्त;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    परत pool;
}

स्थिर शून्य buffer_pool_flush(AVBufferPool *pool)
{
    पर्यंत (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        जर (buf->मुक्त == av_buffer_default_free)
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

    जर (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

शून्य av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    जर (!ppool || !*ppool)
        परत;
    pool   = *ppool;
    *ppool = रिक्त;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    जर (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

स्थिर शून्य pool_release_buffer(शून्य *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    जर (buf->मुक्त == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    जर (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
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
    जर (!ret)
        परत रिक्त;

    buf = av_mallocz(आकार(*buf));
    जर (!buf) {
        av_buffer_unref(&ret);
        परत रिक्त;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->मुक्त   = ret->buffer->मुक्त;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->मुक्त   = pool_release_buffer;

    परत ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    जर (buf) {
        स_रखो(&buf->buffer, 0, आकार(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        जर (ret) {
            pool->pool = buf->next;
            buf->next = रिक्त;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            जर (buf->मुक्त == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                जर (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } अन्यथा {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    जर (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    परत ret;
}

शून्य *av_buffer_pool_buffer_get_opaque(स्थिरांक AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    परत buf->opaque;
}

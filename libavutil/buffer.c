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

#અન્તર્ભાવ <stdatomic.h>
#અન્તર્ભાવ <stdint.h>
#અન્તર્ભાવ <string.h>

#અન્તર્ભાવ "avassert.h"
#અન્તર્ભાવ "buffer_internal.h"
#અન્તર્ભાવ "common.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ "sanitizer.h"
#અન્તર્ભાવ "thread.h"

સ્થિર AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  શૂન્ય (*મુક્ત)(શૂન્ય *opaque, uint8_t *data),
                                  શૂન્ય *opaque, પૂર્ણાંક flags)
{
    AVBufferRef *ref = ખાલી;

    buf->data     = data;
    buf->size     = size;
    buf->મુક્ત     = મુક્ત ? મુક્ત : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(કદ(*ref));
    જો (!ref)
        પાછા ખાલી;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    પાછા ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              શૂન્ય (*મુક્ત)(શૂન્ય *opaque, uint8_t *data),
                              શૂન્ય *opaque, પૂર્ણાંક flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(કદ(*buf));
    જો (!buf)
        પાછા ખાલી;

    ret = buffer_create(buf, data, size, મુક્ત, opaque, flags);
    જો (!ret) {
        av_free(buf);
        પાછા ખાલી;
    }
    પાછા ret;
}

શૂન્ય av_buffer_default_free(શૂન્ય *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = ખાલી;
    uint8_t    *data = ખાલી;

    data = av_malloc(size);
    જો (!data)
        પાછા ખાલી;

    ret = av_buffer_create(data, size, av_buffer_default_free, ખાલી, 0);
    જો (!ret)
        av_freep(&data);

    પાછા ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    જો (!ret)
        પાછા ખાલી;

    memset(ret->data, 0, size);
    પાછા ret;
}

AVBufferRef *av_buffer_ref(અચલ AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(કદ(*ret));

    જો (!ret)
        પાછા ખાલી;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    પાછા ret;
}

સ્થિર શૂન્ય buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    જો (src) {
        **dst = **src;
        av_freep(src);
    } નહીંતર
        av_freep(dst);

    જો (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        પૂર્ણાંક free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->મુક્ત(b->opaque, b->data);
        જો (free_avbuffer)
            av_free(b);
    }
}

શૂન્ય av_buffer_unref(AVBufferRef **buf)
{
    જો (!buf || !*buf)
        પાછા;

    buffer_replace(buf, ખાલી);
}

પૂર્ણાંક av_buffer_is_writable(અચલ AVBufferRef *buf)
{
    જો (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        પાછા 0;

    પાછા atomic_load(&buf->buffer->refcount) == 1;
}

શૂન્ય *av_buffer_get_opaque(અચલ AVBufferRef *buf)
{
    પાછા buf->buffer->opaque;
}

પૂર્ણાંક av_buffer_get_ref_ગણતરી(અચલ AVBufferRef *buf)
{
    પાછા atomic_load(&buf->buffer->refcount);
}

પૂર્ણાંક av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    જો (av_buffer_is_writable(buf))
        પાછા 0;

    newbuf = av_buffer_alloc(buf->size);
    જો (!newbuf)
        પાછા AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    પાછા 0;
}

પૂર્ણાંક av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    પૂર્ણાંક ret;

    જો (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(ખાલી, size);
        જો (!data)
            પાછા AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, ખાલી, 0);
        જો (!buf) {
            av_freep(&data);
            પાછા AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        પાછા 0;
    } નહીંતર જો (buf->size == size)
        પાછા 0;

    જો (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = ખાલી;

        ret = av_buffer_realloc(&new, size);
        જો (ret < 0)
            પાછા ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        પાછા 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    જો (!tmp)
        પાછા AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    પાછા 0;
}

પૂર્ણાંક av_buffer_replace(AVBufferRef **pdst, અચલ AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    જો (!src) {
        av_buffer_unref(pdst);
        પાછા 0;
    }

    જો (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        પાછા 0;
    }

    tmp = av_buffer_ref(src);
    જો (!tmp)
        પાછા AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    પાછા 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, શૂન્ય *opaque,
                                   AVBufferRef* (*alloc)(શૂન્ય *opaque, size_t size),
                                   શૂન્ય (*pool_free)(શૂન્ય *opaque))
{
    AVBufferPool *pool = av_mallocz(કદ(*pool));
    જો (!pool)
        પાછા ખાલી;

    જો (ff_mutex_init(&pool->mutex, ખાલી)) {
        av_free(pool);
        પાછા ખાલી;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    પાછા pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(કદ(*pool));
    જો (!pool)
        પાછા ખાલી;

    જો (ff_mutex_init(&pool->mutex, ખાલી)) {
        av_free(pool);
        પાછા ખાલી;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    પાછા pool;
}

સ્થિર શૂન્ય buffer_pool_flush(AVBufferPool *pool)
{
    જ્યારે (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        જો (buf->મુક્ત == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->મુક્ત(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
સ્થિર શૂન્ય buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    જો (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

શૂન્ય av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    જો (!ppool || !*ppool)
        પાછા;
    pool   = *ppool;
    *ppool = ખાલી;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    જો (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

સ્થિર શૂન્ય pool_release_buffer(શૂન્ય *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    જો (buf->મુક્ત == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    જો (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
સ્થિર AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    જો (!ret)
        પાછા ખાલી;

    buf = av_mallocz(કદ(*buf));
    જો (!buf) {
        av_buffer_unref(&ret);
        પાછા ખાલી;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->મુક્ત   = ret->buffer->મુક્ત;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->મુક્ત   = pool_release_buffer;

    પાછા ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    જો (buf) {
        memset(&buf->buffer, 0, કદ(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        જો (ret) {
            pool->pool = buf->next;
            buf->next = ખાલી;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            જો (buf->મુક્ત == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                જો (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } નહીંતર {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    જો (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    પાછા ret;
}

શૂન્ય *av_buffer_pool_buffer_get_opaque(અચલ AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    પાછા buf->opaque;
}

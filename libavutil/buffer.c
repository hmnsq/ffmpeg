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

#அந்தர்பாவ <stdatomic.h>
#அந்தர்பாவ <stdint.h>
#அந்தர்பாவ <string.h>

#அந்தர்பாவ "avassert.h"
#அந்தர்பாவ "buffer_internal.h"
#அந்தர்பாவ "common.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ "sanitizer.h"
#அந்தர்பாவ "thread.h"

நிலையான AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  வெறுமை (*விடுவி)(வெறுமை *opaque, uint8_t *data),
                                  வெறுமை *opaque, முழு flags)
{
    AVBufferRef *ref = வெற்று;

    buf->data     = data;
    buf->size     = size;
    buf->விடுவி     = விடுவி ? விடுவி : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(அளவு(*ref));
    எனில் (!ref)
        திரும்பு வெற்று;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    திரும்பு ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              வெறுமை (*விடுவி)(வெறுமை *opaque, uint8_t *data),
                              வெறுமை *opaque, முழு flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(அளவு(*buf));
    எனில் (!buf)
        திரும்பு வெற்று;

    ret = buffer_create(buf, data, size, விடுவி, opaque, flags);
    எனில் (!ret) {
        av_free(buf);
        திரும்பு வெற்று;
    }
    திரும்பு ret;
}

வெறுமை av_buffer_default_free(வெறுமை *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = வெற்று;
    uint8_t    *data = வெற்று;

    data = av_malloc(size);
    எனில் (!data)
        திரும்பு வெற்று;

    ret = av_buffer_create(data, size, av_buffer_default_free, வெற்று, 0);
    எனில் (!ret)
        av_freep(&data);

    திரும்பு ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    எனில் (!ret)
        திரும்பு வெற்று;

    memset(ret->data, 0, size);
    திரும்பு ret;
}

AVBufferRef *av_buffer_ref(மாறிலி AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(அளவு(*ret));

    எனில் (!ret)
        திரும்பு வெற்று;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    திரும்பு ret;
}

நிலையான வெறுமை buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    எனில் (src) {
        **dst = **src;
        av_freep(src);
    } இல்லையெனில்
        av_freep(dst);

    எனில் (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        முழு free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->விடுவி(b->opaque, b->data);
        எனில் (free_avbuffer)
            av_free(b);
    }
}

வெறுமை av_buffer_unref(AVBufferRef **buf)
{
    எனில் (!buf || !*buf)
        திரும்பு;

    buffer_replace(buf, வெற்று);
}

முழு av_buffer_is_writable(மாறிலி AVBufferRef *buf)
{
    எனில் (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        திரும்பு 0;

    திரும்பு atomic_load(&buf->buffer->refcount) == 1;
}

வெறுமை *av_buffer_get_opaque(மாறிலி AVBufferRef *buf)
{
    திரும்பு buf->buffer->opaque;
}

முழு av_buffer_get_ref_மொத்தம்(மாறிலி AVBufferRef *buf)
{
    திரும்பு atomic_load(&buf->buffer->refcount);
}

முழு av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    எனில் (av_buffer_is_writable(buf))
        திரும்பு 0;

    newbuf = av_buffer_alloc(buf->size);
    எனில் (!newbuf)
        திரும்பு AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    திரும்பு 0;
}

முழு av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    முழு ret;

    எனில் (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(வெற்று, size);
        எனில் (!data)
            திரும்பு AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, வெற்று, 0);
        எனில் (!buf) {
            av_freep(&data);
            திரும்பு AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        திரும்பு 0;
    } இல்லையெனில் எனில் (buf->size == size)
        திரும்பு 0;

    எனில் (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = வெற்று;

        ret = av_buffer_realloc(&new, size);
        எனில் (ret < 0)
            திரும்பு ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        திரும்பு 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    எனில் (!tmp)
        திரும்பு AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    திரும்பு 0;
}

முழு av_buffer_replace(AVBufferRef **pdst, மாறிலி AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    எனில் (!src) {
        av_buffer_unref(pdst);
        திரும்பு 0;
    }

    எனில் (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        திரும்பு 0;
    }

    tmp = av_buffer_ref(src);
    எனில் (!tmp)
        திரும்பு AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    திரும்பு 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, வெறுமை *opaque,
                                   AVBufferRef* (*alloc)(வெறுமை *opaque, size_t size),
                                   வெறுமை (*pool_free)(வெறுமை *opaque))
{
    AVBufferPool *pool = av_mallocz(அளவு(*pool));
    எனில் (!pool)
        திரும்பு வெற்று;

    எனில் (ff_mutex_init(&pool->mutex, வெற்று)) {
        av_free(pool);
        திரும்பு வெற்று;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    திரும்பு pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(அளவு(*pool));
    எனில் (!pool)
        திரும்பு வெற்று;

    எனில் (ff_mutex_init(&pool->mutex, வெற்று)) {
        av_free(pool);
        திரும்பு வெற்று;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    திரும்பு pool;
}

நிலையான வெறுமை buffer_pool_flush(AVBufferPool *pool)
{
    போது (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        எனில் (buf->விடுவி == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->விடுவி(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
நிலையான வெறுமை buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    எனில் (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

வெறுமை av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    எனில் (!ppool || !*ppool)
        திரும்பு;
    pool   = *ppool;
    *ppool = வெற்று;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    எனில் (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

நிலையான வெறுமை pool_release_buffer(வெறுமை *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    எனில் (buf->விடுவி == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    எனில் (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
நிலையான AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    எனில் (!ret)
        திரும்பு வெற்று;

    buf = av_mallocz(அளவு(*buf));
    எனில் (!buf) {
        av_buffer_unref(&ret);
        திரும்பு வெற்று;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->விடுவி   = ret->buffer->விடுவி;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->விடுவி   = pool_release_buffer;

    திரும்பு ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    எனில் (buf) {
        memset(&buf->buffer, 0, அளவு(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        எனில் (ret) {
            pool->pool = buf->next;
            buf->next = வெற்று;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            எனில் (buf->விடுவி == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                எனில் (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } இல்லையெனில் {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    எனில் (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    திரும்பு ret;
}

வெறுமை *av_buffer_pool_buffer_get_opaque(மாறிலி AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    திரும்பு buf->opaque;
}

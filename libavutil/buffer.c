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

#ಅನ್ತರ್ಭಾವ <stdatomic.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>
#ಅನ್ತರ್ಭಾವ <string.h>

#ಅನ್ತರ್ಭಾವ "avassert.h"
#ಅನ್ತರ್ಭಾವ "buffer_internal.h"
#ಅನ್ತರ್ಭಾವ "common.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ "sanitizer.h"
#ಅನ್ತರ್ಭಾವ "thread.h"

ಸ್ಥಿರ AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  ಶೂನ್ಯ (*ಮುಕ್ತ)(ಶೂನ್ಯ *opaque, uint8_t *data),
                                  ಶೂನ್ಯ *opaque, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVBufferRef *ref = ರಿಕ್ತ;

    buf->data     = data;
    buf->size     = size;
    buf->ಮುಕ್ತ     = ಮುಕ್ತ ? ಮುಕ್ತ : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(ಪರಿಮಾಣ(*ref));
    ಯದಿ (!ref)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    ಪ್ರತ್ಯಾಗಮ ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              ಶೂನ್ಯ (*ಮುಕ್ತ)(ಶೂನ್ಯ *opaque, uint8_t *data),
                              ಶೂನ್ಯ *opaque, ಪೂರ್ಣಾಙ್ಕ flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(ಪರಿಮಾಣ(*buf));
    ಯದಿ (!buf)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ret = buffer_create(buf, data, size, ಮುಕ್ತ, opaque, flags);
    ಯದಿ (!ret) {
        av_free(buf);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ av_buffer_default_free(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = ರಿಕ್ತ;
    uint8_t    *data = ರಿಕ್ತ;

    data = av_malloc(size);
    ಯದಿ (!data)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ret = av_buffer_create(data, size, av_buffer_default_free, ರಿಕ್ತ, 0);
    ಯದಿ (!ret)
        av_freep(&data);

    ಪ್ರತ್ಯಾಗಮ ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    ಯದಿ (!ret)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    memset(ret->data, 0, size);
    ಪ್ರತ್ಯಾಗಮ ret;
}

AVBufferRef *av_buffer_ref(ಧ್ರುವ AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(ಪರಿಮಾಣ(*ret));

    ಯದಿ (!ret)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    ಯದಿ (src) {
        **dst = **src;
        av_freep(src);
    } ಅನ್ಯಥಾ
        av_freep(dst);

    ಯದಿ (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        ಪೂರ್ಣಾಙ್ಕ free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->ಮುಕ್ತ(b->opaque, b->data);
        ಯದಿ (free_avbuffer)
            av_free(b);
    }
}

ಶೂನ್ಯ av_buffer_unref(AVBufferRef **buf)
{
    ಯದಿ (!buf || !*buf)
        ಪ್ರತ್ಯಾಗಮ;

    buffer_replace(buf, ರಿಕ್ತ);
}

ಪೂರ್ಣಾಙ್ಕ av_buffer_is_writable(ಧ್ರುವ AVBufferRef *buf)
{
    ಯದಿ (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಪ್ರತ್ಯಾಗಮ atomic_load(&buf->buffer->refcount) == 1;
}

ಶೂನ್ಯ *av_buffer_get_opaque(ಧ್ರುವ AVBufferRef *buf)
{
    ಪ್ರತ್ಯಾಗಮ buf->buffer->opaque;
}

ಪೂರ್ಣಾಙ್ಕ av_buffer_get_ref_ಎಣಿಕೆ(ಧ್ರುವ AVBufferRef *buf)
{
    ಪ್ರತ್ಯಾಗಮ atomic_load(&buf->buffer->refcount);
}

ಪೂರ್ಣಾಙ್ಕ av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    ಯದಿ (av_buffer_is_writable(buf))
        ಪ್ರತ್ಯಾಗಮ 0;

    newbuf = av_buffer_alloc(buf->size);
    ಯದಿ (!newbuf)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    ಪೂರ್ಣಾಙ್ಕ ret;

    ಯದಿ (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(ರಿಕ್ತ, size);
        ಯದಿ (!data)
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, ರಿಕ್ತ, 0);
        ಯದಿ (!buf) {
            av_freep(&data);
            ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        ಪ್ರತ್ಯಾಗಮ 0;
    } ಅನ್ಯಥಾ ಯದಿ (buf->size == size)
        ಪ್ರತ್ಯಾಗಮ 0;

    ಯದಿ (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = ರಿಕ್ತ;

        ret = av_buffer_realloc(&new, size);
        ಯದಿ (ret < 0)
            ಪ್ರತ್ಯಾಗಮ ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    ಯದಿ (!tmp)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಪೂರ್ಣಾಙ್ಕ av_buffer_replace(AVBufferRef **pdst, ಧ್ರುವ AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    ಯದಿ (!src) {
        av_buffer_unref(pdst);
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    ಯದಿ (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    tmp = av_buffer_ref(src);
    ಯದಿ (!tmp)
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    ಪ್ರತ್ಯಾಗಮ 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, ಶೂನ್ಯ *opaque,
                                   AVBufferRef* (*alloc)(ಶೂನ್ಯ *opaque, size_t size),
                                   ಶೂನ್ಯ (*pool_free)(ಶೂನ್ಯ *opaque))
{
    AVBufferPool *pool = av_mallocz(ಪರಿಮಾಣ(*pool));
    ಯದಿ (!pool)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಯದಿ (ff_mutex_init(&pool->mutex, ರಿಕ್ತ)) {
        av_free(pool);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    ಪ್ರತ್ಯಾಗಮ pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(ಪರಿಮಾಣ(*pool));
    ಯದಿ (!pool)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    ಯದಿ (ff_mutex_init(&pool->mutex, ರಿಕ್ತ)) {
        av_free(pool);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    ಪ್ರತ್ಯಾಗಮ pool;
}

ಸ್ಥಿರ ಶೂನ್ಯ buffer_pool_flush(AVBufferPool *pool)
{
    ಯಾವತ್ (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        ಯದಿ (buf->ಮುಕ್ತ == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->ಮುಕ್ತ(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
ಸ್ಥಿರ ಶೂನ್ಯ buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    ಯದಿ (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

ಶೂನ್ಯ av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    ಯದಿ (!ppool || !*ppool)
        ಪ್ರತ್ಯಾಗಮ;
    pool   = *ppool;
    *ppool = ರಿಕ್ತ;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    ಯದಿ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_release_buffer(ಶೂನ್ಯ *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    ಯದಿ (buf->ಮುಕ್ತ == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    ಯದಿ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
ಸ್ಥಿರ AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    ಯದಿ (!ret)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;

    buf = av_mallocz(ಪರಿಮಾಣ(*buf));
    ಯದಿ (!buf) {
        av_buffer_unref(&ret);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->ಮುಕ್ತ   = ret->buffer->ಮುಕ್ತ;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->ಮುಕ್ತ   = pool_release_buffer;

    ಪ್ರತ್ಯಾಗಮ ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    ಯದಿ (buf) {
        memset(&buf->buffer, 0, ಪರಿಮಾಣ(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        ಯದಿ (ret) {
            pool->pool = buf->next;
            buf->next = ರಿಕ್ತ;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            ಯದಿ (buf->ಮುಕ್ತ == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                ಯದಿ (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } ಅನ್ಯಥಾ {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    ಯದಿ (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ಪ್ರತ್ಯಾಗಮ ret;
}

ಶೂನ್ಯ *av_buffer_pool_buffer_get_opaque(ಧ್ರುವ AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    ಪ್ರತ್ಯಾಗಮ buf->opaque;
}

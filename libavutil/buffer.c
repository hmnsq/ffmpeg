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

#include <stdatomic.h>
#include <stdint.h>
#include <string.h>

#include "avassert.h"
#include "buffer_internal.h"
#include "common.h"
#include "mem.h"
#include "sanitizer.h"
#include "thread.h"

static AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  void (*free)(void *opaque, uint8_t *data),
                                  void *opaque, puur_naa_nka flags)
{
    AVBufferRef *ref = NULL;

    buf->data     = data;
    buf->size     = size;
    buf->free     = free ? free : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(parimaa_na(*ref));
    ᨀᨘ (!ref)
        ᨀᨘᨒ NULL;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    ᨀᨘᨒ ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              void (*free)(void *opaque, uint8_t *data),
                              void *opaque, puur_naa_nka flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(parimaa_na(*buf));
    ᨀᨘ (!buf)
        ᨀᨘᨒ NULL;

    ret = buffer_create(buf, data, size, free, opaque, flags);
    ᨀᨘ (!ret) {
        av_free(buf);
        ᨀᨘᨒ NULL;
    }
    ᨀᨘᨒ ret;
}

void av_buffer_default_free(void *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = NULL;
    uint8_t    *data = NULL;

    data = av_malloc(size);
    ᨀᨘ (!data)
        ᨀᨘᨒ NULL;

    ret = av_buffer_create(data, size, av_buffer_default_free, NULL, 0);
    ᨀᨘ (!ret)
        av_freep(&data);

    ᨀᨘᨒ ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    ᨀᨘ (!ret)
        ᨀᨘᨒ NULL;

    memset(ret->data, 0, size);
    ᨀᨘᨒ ret;
}

AVBufferRef *av_buffer_ref(const AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(parimaa_na(*ret));

    ᨀᨘ (!ret)
        ᨀᨘᨒ NULL;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    ᨀᨘᨒ ret;
}

static void buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    ᨀᨘ (src) {
        **dst = **src;
        av_freep(src);
    } ᨀᨘᨁ
        av_freep(dst);

    ᨀᨘ (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        puur_naa_nka free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->free(b->opaque, b->data);
        ᨀᨘ (free_avbuffer)
            av_free(b);
    }
}

void av_buffer_unref(AVBufferRef **buf)
{
    ᨀᨘ (!buf || !*buf)
        ᨀᨘᨒ;

    buffer_replace(buf, NULL);
}

puur_naa_nka av_buffer_is_writable(const AVBufferRef *buf)
{
    ᨀᨘ (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        ᨀᨘᨒ 0;

    ᨀᨘᨒ atomic_load(&buf->buffer->refcount) == 1;
}

void *av_buffer_get_opaque(const AVBufferRef *buf)
{
    ᨀᨘᨒ buf->buffer->opaque;
}

puur_naa_nka av_buffer_get_ref_count(const AVBufferRef *buf)
{
    ᨀᨘᨒ atomic_load(&buf->buffer->refcount);
}

puur_naa_nka av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    ᨀᨘ (av_buffer_is_writable(buf))
        ᨀᨘᨒ 0;

    newbuf = av_buffer_alloc(buf->size);
    ᨀᨘ (!newbuf)
        ᨀᨘᨒ AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    ᨀᨘᨒ 0;
}

puur_naa_nka av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    puur_naa_nka ret;

    ᨀᨘ (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(NULL, size);
        ᨀᨘ (!data)
            ᨀᨘᨒ AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, NULL, 0);
        ᨀᨘ (!buf) {
            av_freep(&data);
            ᨀᨘᨒ AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        ᨀᨘᨒ 0;
    } ᨀᨘᨁ ᨀᨘ (buf->size == size)
        ᨀᨘᨒ 0;

    ᨀᨘ (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = NULL;

        ret = av_buffer_realloc(&new, size);
        ᨀᨘ (ret < 0)
            ᨀᨘᨒ ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        ᨀᨘᨒ 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    ᨀᨘ (!tmp)
        ᨀᨘᨒ AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    ᨀᨘᨒ 0;
}

puur_naa_nka av_buffer_replace(AVBufferRef **pdst, const AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    ᨀᨘ (!src) {
        av_buffer_unref(pdst);
        ᨀᨘᨒ 0;
    }

    ᨀᨘ (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        ᨀᨘᨒ 0;
    }

    tmp = av_buffer_ref(src);
    ᨀᨘ (!tmp)
        ᨀᨘᨒ AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    ᨀᨘᨒ 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, void *opaque,
                                   AVBufferRef* (*alloc)(void *opaque, size_t size),
                                   void (*pool_free)(void *opaque))
{
    AVBufferPool *pool = av_mallocz(parimaa_na(*pool));
    ᨀᨘ (!pool)
        ᨀᨘᨒ NULL;

    ᨀᨘ (ff_mutex_init(&pool->mutex, NULL)) {
        av_free(pool);
        ᨀᨘᨒ NULL;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    ᨀᨘᨒ pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(parimaa_na(*pool));
    ᨀᨘ (!pool)
        ᨀᨘᨒ NULL;

    ᨀᨘ (ff_mutex_init(&pool->mutex, NULL)) {
        av_free(pool);
        ᨀᨘᨒ NULL;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    ᨀᨘᨒ pool;
}

static void buffer_pool_flush(AVBufferPool *pool)
{
    ᨀᨛ (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        ᨀᨘ (buf->free == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->free(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
static void buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    ᨀᨘ (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

void av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    ᨀᨘ (!ppool || !*ppool)
        ᨀᨘᨒ;
    pool   = *ppool;
    *ppool = NULL;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    ᨀᨘ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

static void pool_release_buffer(void *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    ᨀᨘ (buf->free == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    ᨀᨘ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
static AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    ᨀᨘ (!ret)
        ᨀᨘᨒ NULL;

    buf = av_mallocz(parimaa_na(*buf));
    ᨀᨘ (!buf) {
        av_buffer_unref(&ret);
        ᨀᨘᨒ NULL;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->free   = ret->buffer->free;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->free   = pool_release_buffer;

    ᨀᨘᨒ ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    ᨀᨘ (buf) {
        memset(&buf->buffer, 0, parimaa_na(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        ᨀᨘ (ret) {
            pool->pool = buf->next;
            buf->next = NULL;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            ᨀᨘ (buf->free == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                ᨀᨘ (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } ᨀᨘᨁ {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    ᨀᨘ (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ᨀᨘᨒ ret;
}

void *av_buffer_pool_buffer_get_opaque(const AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    ᨀᨘᨒ buf->opaque;
}

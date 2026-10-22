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

#അന്തര്ഭാവ <stdatomic.h>
#അന്തര്ഭാവ <stdint.h>
#അന്തര്ഭാവ <string.h>

#അന്തര്ഭാവ "avassert.h"
#അന്തര്ഭാവ "buffer_internal.h"
#അന്തര്ഭാവ "common.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ "sanitizer.h"
#അന്തര്ഭാവ "thread.h"

സ്ഥിതം AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  ശൂന്യം (*സ്വതന്ത്രം)(ശൂന്യം *opaque, uint8_t *data),
                                  ശൂന്യം *opaque, പൂർണ്ണസംഖ്യ flags)
{
    AVBufferRef *ref = ശൂന്യ;

    buf->data     = data;
    buf->size     = size;
    buf->സ്വതന്ത്രം     = സ്വതന്ത്രം ? സ്വതന്ത്രം : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(വലുപ്പം(*ref));
    എങ്കിൽ (!ref)
        തിരികെ ശൂന്യ;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    തിരികെ ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              ശൂന്യം (*സ്വതന്ത്രം)(ശൂന്യം *opaque, uint8_t *data),
                              ശൂന്യം *opaque, പൂർണ്ണസംഖ്യ flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(വലുപ്പം(*buf));
    എങ്കിൽ (!buf)
        തിരികെ ശൂന്യ;

    ret = buffer_create(buf, data, size, സ്വതന്ത്രം, opaque, flags);
    എങ്കിൽ (!ret) {
        av_free(buf);
        തിരികെ ശൂന്യ;
    }
    തിരികെ ret;
}

ശൂന്യം av_buffer_default_free(ശൂന്യം *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = ശൂന്യ;
    uint8_t    *data = ശൂന്യ;

    data = av_malloc(size);
    എങ്കിൽ (!data)
        തിരികെ ശൂന്യ;

    ret = av_buffer_create(data, size, av_buffer_default_free, ശൂന്യ, 0);
    എങ്കിൽ (!ret)
        av_freep(&data);

    തിരികെ ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    എങ്കിൽ (!ret)
        തിരികെ ശൂന്യ;

    memset(ret->data, 0, size);
    തിരികെ ret;
}

AVBufferRef *av_buffer_ref(സ്ഥിരം AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(വലുപ്പം(*ret));

    എങ്കിൽ (!ret)
        തിരികെ ശൂന്യ;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    തിരികെ ret;
}

സ്ഥിതം ശൂന്യം buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    എങ്കിൽ (src) {
        **dst = **src;
        av_freep(src);
    } അല്ലെങ്കിൽ
        av_freep(dst);

    എങ്കിൽ (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        പൂർണ്ണസംഖ്യ free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->സ്വതന്ത്രം(b->opaque, b->data);
        എങ്കിൽ (free_avbuffer)
            av_free(b);
    }
}

ശൂന്യം av_buffer_unref(AVBufferRef **buf)
{
    എങ്കിൽ (!buf || !*buf)
        തിരികെ;

    buffer_replace(buf, ശൂന്യ);
}

പൂർണ്ണസംഖ്യ av_buffer_is_writable(സ്ഥിരം AVBufferRef *buf)
{
    എങ്കിൽ (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        തിരികെ 0;

    തിരികെ atomic_load(&buf->buffer->refcount) == 1;
}

ശൂന്യം *av_buffer_get_opaque(സ്ഥിരം AVBufferRef *buf)
{
    തിരികെ buf->buffer->opaque;
}

പൂർണ്ണസംഖ്യ av_buffer_get_ref_എണ്ണം(സ്ഥിരം AVBufferRef *buf)
{
    തിരികെ atomic_load(&buf->buffer->refcount);
}

പൂർണ്ണസംഖ്യ av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    എങ്കിൽ (av_buffer_is_writable(buf))
        തിരികെ 0;

    newbuf = av_buffer_alloc(buf->size);
    എങ്കിൽ (!newbuf)
        തിരികെ AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    പൂർണ്ണസംഖ്യ ret;

    എങ്കിൽ (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(ശൂന്യ, size);
        എങ്കിൽ (!data)
            തിരികെ AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, ശൂന്യ, 0);
        എങ്കിൽ (!buf) {
            av_freep(&data);
            തിരികെ AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        തിരികെ 0;
    } അല്ലെങ്കിൽ എങ്കിൽ (buf->size == size)
        തിരികെ 0;

    എങ്കിൽ (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = ശൂന്യ;

        ret = av_buffer_realloc(&new, size);
        എങ്കിൽ (ret < 0)
            തിരികെ ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        തിരികെ 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    എങ്കിൽ (!tmp)
        തിരികെ AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    തിരികെ 0;
}

പൂർണ്ണസംഖ്യ av_buffer_replace(AVBufferRef **pdst, സ്ഥിരം AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    എങ്കിൽ (!src) {
        av_buffer_unref(pdst);
        തിരികെ 0;
    }

    എങ്കിൽ (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        തിരികെ 0;
    }

    tmp = av_buffer_ref(src);
    എങ്കിൽ (!tmp)
        തിരികെ AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    തിരികെ 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, ശൂന്യം *opaque,
                                   AVBufferRef* (*alloc)(ശൂന്യം *opaque, size_t size),
                                   ശൂന്യം (*pool_free)(ശൂന്യം *opaque))
{
    AVBufferPool *pool = av_mallocz(വലുപ്പം(*pool));
    എങ്കിൽ (!pool)
        തിരികെ ശൂന്യ;

    എങ്കിൽ (ff_mutex_init(&pool->mutex, ശൂന്യ)) {
        av_free(pool);
        തിരികെ ശൂന്യ;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    തിരികെ pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(വലുപ്പം(*pool));
    എങ്കിൽ (!pool)
        തിരികെ ശൂന്യ;

    എങ്കിൽ (ff_mutex_init(&pool->mutex, ശൂന്യ)) {
        av_free(pool);
        തിരികെ ശൂന്യ;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    തിരികെ pool;
}

സ്ഥിതം ശൂന്യം buffer_pool_flush(AVBufferPool *pool)
{
    ആകുമ്പോൾ (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        എങ്കിൽ (buf->സ്വതന്ത്രം == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->സ്വതന്ത്രം(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
സ്ഥിതം ശൂന്യം buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    എങ്കിൽ (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

ശൂന്യം av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    എങ്കിൽ (!ppool || !*ppool)
        തിരികെ;
    pool   = *ppool;
    *ppool = ശൂന്യ;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    എങ്കിൽ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

സ്ഥിതം ശൂന്യം pool_release_buffer(ശൂന്യം *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    എങ്കിൽ (buf->സ്വതന്ത്രം == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    എങ്കിൽ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
സ്ഥിതം AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    എങ്കിൽ (!ret)
        തിരികെ ശൂന്യ;

    buf = av_mallocz(വലുപ്പം(*buf));
    എങ്കിൽ (!buf) {
        av_buffer_unref(&ret);
        തിരികെ ശൂന്യ;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->സ്വതന്ത്രം   = ret->buffer->സ്വതന്ത്രം;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->സ്വതന്ത്രം   = pool_release_buffer;

    തിരികെ ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    എങ്കിൽ (buf) {
        memset(&buf->buffer, 0, വലുപ്പം(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        എങ്കിൽ (ret) {
            pool->pool = buf->next;
            buf->next = ശൂന്യ;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            എങ്കിൽ (buf->സ്വതന്ത്രം == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                എങ്കിൽ (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } അല്ലെങ്കിൽ {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    എങ്കിൽ (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    തിരികെ ret;
}

ശൂന്യം *av_buffer_pool_buffer_get_opaque(സ്ഥിരം AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    തിരികെ buf->opaque;
}

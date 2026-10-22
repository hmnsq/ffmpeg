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

#ଅନ୍ତର୍ଭାଵ <stdatomic.h>
#ଅନ୍ତର୍ଭାଵ <stdint.h>
#ଅନ୍ତର୍ଭାଵ <string.h>

#ଅନ୍ତର୍ଭାଵ "avassert.h"
#ଅନ୍ତର୍ଭାଵ "buffer_internal.h"
#ଅନ୍ତର୍ଭାଵ "common.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ "sanitizer.h"
#ଅନ୍ତର୍ଭାଵ "thread.h"

ସ୍ଥିର AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  ଶୂନ୍ୟ (*ମୁକ୍ତ)(ଶୂନ୍ୟ *opaque, uint8_t *data),
                                  ଶୂନ୍ୟ *opaque, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVBufferRef *ref = ଖାଲି;

    buf->data     = data;
    buf->size     = size;
    buf->ମୁକ୍ତ     = ମୁକ୍ତ ? ମୁକ୍ତ : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(ଆକାର(*ref));
    ଯଦି (!ref)
        ଫେରନ୍ତୁ ଖାଲି;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    ଫେରନ୍ତୁ ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              ଶୂନ୍ୟ (*ମୁକ୍ତ)(ଶୂନ୍ୟ *opaque, uint8_t *data),
                              ଶୂନ୍ୟ *opaque, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(ଆକାର(*buf));
    ଯଦି (!buf)
        ଫେରନ୍ତୁ ଖାଲି;

    ret = buffer_create(buf, data, size, ମୁକ୍ତ, opaque, flags);
    ଯଦି (!ret) {
        av_free(buf);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ av_buffer_default_free(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = ଖାଲି;
    uint8_t    *data = ଖାଲି;

    data = av_malloc(size);
    ଯଦି (!data)
        ଫେରନ୍ତୁ ଖାଲି;

    ret = av_buffer_create(data, size, av_buffer_default_free, ଖାଲି, 0);
    ଯଦି (!ret)
        av_freep(&data);

    ଫେରନ୍ତୁ ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    ଯଦି (!ret)
        ଫେରନ୍ତୁ ଖାଲି;

    memset(ret->data, 0, size);
    ଫେରନ୍ତୁ ret;
}

AVBufferRef *av_buffer_ref(ଅଚଳ AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(ଆକାର(*ret));

    ଯଦି (!ret)
        ଫେରନ୍ତୁ ଖାଲି;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    ଫେରନ୍ତୁ ret;
}

ସ୍ଥିର ଶୂନ୍ୟ buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    ଯଦି (src) {
        **dst = **src;
        av_freep(src);
    } ଅନ୍ୟଥା
        av_freep(dst);

    ଯଦି (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->ମୁକ୍ତ(b->opaque, b->data);
        ଯଦି (free_avbuffer)
            av_free(b);
    }
}

ଶୂନ୍ୟ av_buffer_unref(AVBufferRef **buf)
{
    ଯଦି (!buf || !*buf)
        ଫେରନ୍ତୁ;

    buffer_replace(buf, ଖାଲି);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_buffer_is_writable(ଅଚଳ AVBufferRef *buf)
{
    ଯଦି (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        ଫେରନ୍ତୁ 0;

    ଫେରନ୍ତୁ atomic_load(&buf->buffer->refcount) == 1;
}

ଶୂନ୍ୟ *av_buffer_get_opaque(ଅଚଳ AVBufferRef *buf)
{
    ଫେରନ୍ତୁ buf->buffer->opaque;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_buffer_get_ref_ଗଣନା(ଅଚଳ AVBufferRef *buf)
{
    ଫେରନ୍ତୁ atomic_load(&buf->buffer->refcount);
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    ଯଦି (av_buffer_is_writable(buf))
        ଫେରନ୍ତୁ 0;

    newbuf = av_buffer_alloc(buf->size);
    ଯଦି (!newbuf)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    ଯଦି (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(ଖାଲି, size);
        ଯଦି (!data)
            ଫେରନ୍ତୁ AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, ଖାଲି, 0);
        ଯଦି (!buf) {
            av_freep(&data);
            ଫେରନ୍ତୁ AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        ଫେରନ୍ତୁ 0;
    } ଅନ୍ୟଥା ଯଦି (buf->size == size)
        ଫେରନ୍ତୁ 0;

    ଯଦି (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = ଖାଲି;

        ret = av_buffer_realloc(&new, size);
        ଯଦି (ret < 0)
            ଫେରନ୍ତୁ ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        ଫେରନ୍ତୁ 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    ଯଦି (!tmp)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    ଫେରନ୍ତୁ 0;
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_buffer_replace(AVBufferRef **pdst, ଅଚଳ AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    ଯଦି (!src) {
        av_buffer_unref(pdst);
        ଫେରନ୍ତୁ 0;
    }

    ଯଦି (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        ଫେରନ୍ତୁ 0;
    }

    tmp = av_buffer_ref(src);
    ଯଦି (!tmp)
        ଫେରନ୍ତୁ AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    ଫେରନ୍ତୁ 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, ଶୂନ୍ୟ *opaque,
                                   AVBufferRef* (*alloc)(ଶୂନ୍ୟ *opaque, size_t size),
                                   ଶୂନ୍ୟ (*pool_free)(ଶୂନ୍ୟ *opaque))
{
    AVBufferPool *pool = av_mallocz(ଆକାର(*pool));
    ଯଦି (!pool)
        ଫେରନ୍ତୁ ଖାଲି;

    ଯଦି (ff_mutex_init(&pool->mutex, ଖାଲି)) {
        av_free(pool);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    ଫେରନ୍ତୁ pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(ଆକାର(*pool));
    ଯଦି (!pool)
        ଫେରନ୍ତୁ ଖାଲି;

    ଯଦି (ff_mutex_init(&pool->mutex, ଖାଲି)) {
        av_free(pool);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    ଫେରନ୍ତୁ pool;
}

ସ୍ଥିର ଶୂନ୍ୟ buffer_pool_flush(AVBufferPool *pool)
{
    ଯେତେବେଳେ (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        ଯଦି (buf->ମୁକ୍ତ == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->ମୁକ୍ତ(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
ସ୍ଥିର ଶୂନ୍ୟ buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    ଯଦି (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

ଶୂନ୍ୟ av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    ଯଦି (!ppool || !*ppool)
        ଫେରନ୍ତୁ;
    pool   = *ppool;
    *ppool = ଖାଲି;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    ଯଦି (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

ସ୍ଥିର ଶୂନ୍ୟ pool_release_buffer(ଶୂନ୍ୟ *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    ଯଦି (buf->ମୁକ୍ତ == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    ଯଦି (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
ସ୍ଥିର AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    ଯଦି (!ret)
        ଫେରନ୍ତୁ ଖାଲି;

    buf = av_mallocz(ଆକାର(*buf));
    ଯଦି (!buf) {
        av_buffer_unref(&ret);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->ମୁକ୍ତ   = ret->buffer->ମୁକ୍ତ;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->ମୁକ୍ତ   = pool_release_buffer;

    ଫେରନ୍ତୁ ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    ଯଦି (buf) {
        memset(&buf->buffer, 0, ଆକାର(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        ଯଦି (ret) {
            pool->pool = buf->next;
            buf->next = ଖାଲି;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            ଯଦି (buf->ମୁକ୍ତ == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                ଯଦି (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } ଅନ୍ୟଥା {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    ଯଦି (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ଫେରନ୍ତୁ ret;
}

ଶୂନ୍ୟ *av_buffer_pool_buffer_get_opaque(ଅଚଳ AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    ଫେରନ୍ତୁ buf->opaque;
}

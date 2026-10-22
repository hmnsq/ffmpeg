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

#অন্তর্ভাৱ <stdatomic.h>
#অন্তর্ভাৱ <stdint.h>
#অন্তর্ভাৱ <string.h>

#অন্তর্ভাৱ "avassert.h"
#অন্তর্ভাৱ "buffer_internal.h"
#অন্তর্ভাৱ "common.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ "sanitizer.h"
#অন্তর্ভাৱ "thread.h"

স্থির AVBufferRef *buffer_create(AVBuffer *buf, uint8_t *data, size_t size,
                                  শূন্য (*মুক্ত)(শূন্য *opaque, uint8_t *data),
                                  শূন্য *opaque, পূর্ণাঙ্ক flags)
{
    AVBufferRef *ref = রিক্ত;

    buf->data     = data;
    buf->size     = size;
    buf->মুক্ত     = মুক্ত ? মুক্ত : av_buffer_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(পরিমাণ(*ref));
    যদি (!ref)
        ঘূৰাই রিক্ত;

    ref->buffer = buf;
    ref->data   = data;
    ref->size   = size;

    ঘূৰাই ref;
}

AVBufferRef *av_buffer_create(uint8_t *data, size_t size,
                              শূন্য (*মুক্ত)(শূন্য *opaque, uint8_t *data),
                              শূন্য *opaque, পূর্ণাঙ্ক flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(পরিমাণ(*buf));
    যদি (!buf)
        ঘূৰাই রিক্ত;

    ret = buffer_create(buf, data, size, মুক্ত, opaque, flags);
    যদি (!ret) {
        av_free(buf);
        ঘূৰাই রিক্ত;
    }
    ঘূৰাই ret;
}

শূন্য av_buffer_default_free(শূন্য *opaque, uint8_t *data)
{
    av_free(data);
}

AVBufferRef *av_buffer_alloc(size_t size)
{
    AVBufferRef *ret = রিক্ত;
    uint8_t    *data = রিক্ত;

    data = av_malloc(size);
    যদি (!data)
        ঘূৰাই রিক্ত;

    ret = av_buffer_create(data, size, av_buffer_default_free, রিক্ত, 0);
    যদি (!ret)
        av_freep(&data);

    ঘূৰাই ret;
}

AVBufferRef *av_buffer_allocz(size_t size)
{
    AVBufferRef *ret = av_buffer_alloc(size);
    যদি (!ret)
        ঘূৰাই রিক্ত;

    memset(ret->data, 0, size);
    ঘূৰাই ret;
}

AVBufferRef *av_buffer_ref(ধ্রুৱ AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(পরিমাণ(*ret));

    যদি (!ret)
        ঘূৰাই রিক্ত;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->buffer->refcount, 1, memory_order_relaxed);

    ঘূৰাই ret;
}

স্থির শূন্য buffer_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->buffer;

    যদি (src) {
        **dst = **src;
        av_freep(src);
    } অন্যথা
        av_freep(dst);

    যদি (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        পূর্ণাঙ্ক free_avbuffer = !(b->flags_internal & BUFFER_FLAG_NO_FREE);
        b->মুক্ত(b->opaque, b->data);
        যদি (free_avbuffer)
            av_free(b);
    }
}

শূন্য av_buffer_unref(AVBufferRef **buf)
{
    যদি (!buf || !*buf)
        ঘূৰাই;

    buffer_replace(buf, রিক্ত);
}

পূর্ণাঙ্ক av_buffer_is_writable(ধ্রুৱ AVBufferRef *buf)
{
    যদি (buf->buffer->flags & AV_BUFFER_FLAG_READONLY)
        ঘূৰাই 0;

    ঘূৰাই atomic_load(&buf->buffer->refcount) == 1;
}

শূন্য *av_buffer_get_opaque(ধ্রুৱ AVBufferRef *buf)
{
    ঘূৰাই buf->buffer->opaque;
}

পূর্ণাঙ্ক av_buffer_get_ref_গুনতি(ধ্রুৱ AVBufferRef *buf)
{
    ঘূৰাই atomic_load(&buf->buffer->refcount);
}

পূর্ণাঙ্ক av_buffer_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    যদি (av_buffer_is_writable(buf))
        ঘূৰাই 0;

    newbuf = av_buffer_alloc(buf->size);
    যদি (!newbuf)
        ঘূৰাই AVERROR(ENOMEM);

    memcpy(newbuf->data, buf->data, buf->size);

    buffer_replace(pbuf, &newbuf);

    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_buffer_realloc(AVBufferRef **pbuf, size_t size)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    পূর্ণাঙ্ক ret;

    যদি (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *data = av_realloc(রিক্ত, size);
        যদি (!data)
            ঘূৰাই AVERROR(ENOMEM);

        buf = av_buffer_create(data, size, av_buffer_default_free, রিক্ত, 0);
        যদি (!buf) {
            av_freep(&data);
            ঘূৰাই AVERROR(ENOMEM);
        }

        buf->buffer->flags_internal |= BUFFER_FLAG_REALLOCATABLE;
        *pbuf = buf;

        ঘূৰাই 0;
    } অন্যথা যদি (buf->size == size)
        ঘূৰাই 0;

    যদি (!(buf->buffer->flags_internal & BUFFER_FLAG_REALLOCATABLE) ||
        !av_buffer_is_writable(buf) || buf->data != buf->buffer->data) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = রিক্ত;

        ret = av_buffer_realloc(&new, size);
        যদি (ret < 0)
            ঘূৰাই ret;

        memcpy(new->data, buf->data, FFMIN(size, buf->size));

        buffer_replace(pbuf, &new);
        ঘূৰাই 0;
    }

    tmp = av_realloc(buf->buffer->data, size);
    যদি (!tmp)
        ঘূৰাই AVERROR(ENOMEM);

    buf->buffer->data = buf->data = tmp;
    buf->buffer->size = buf->size = size;
    ঘূৰাই 0;
}

পূর্ণাঙ্ক av_buffer_replace(AVBufferRef **pdst, ধ্রুৱ AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    যদি (!src) {
        av_buffer_unref(pdst);
        ঘূৰাই 0;
    }

    যদি (dst && dst->buffer == src->buffer) {
        /* make sure the data pointers match */
        dst->data = src->data;
        dst->size = src->size;
        ঘূৰাই 0;
    }

    tmp = av_buffer_ref(src);
    যদি (!tmp)
        ঘূৰাই AVERROR(ENOMEM);

    av_buffer_unref(pdst);
    *pdst = tmp;
    ঘূৰাই 0;
}

AVBufferPool *av_buffer_pool_init2(size_t size, শূন্য *opaque,
                                   AVBufferRef* (*alloc)(শূন্য *opaque, size_t size),
                                   শূন্য (*pool_free)(শূন্য *opaque))
{
    AVBufferPool *pool = av_mallocz(পরিমাণ(*pool));
    যদি (!pool)
        ঘূৰাই রিক্ত;

    যদি (ff_mutex_init(&pool->mutex, রিক্ত)) {
        av_free(pool);
        ঘূৰাই রিক্ত;
    }

    pool->size      = size;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_buffer_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    ঘূৰাই pool;
}

AVBufferPool *av_buffer_pool_init(size_t size, AVBufferRef* (*alloc)(size_t size))
{
    AVBufferPool *pool = av_mallocz(পরিমাণ(*pool));
    যদি (!pool)
        ঘূৰাই রিক্ত;

    যদি (ff_mutex_init(&pool->mutex, রিক্ত)) {
        av_free(pool);
        ঘূৰাই রিক্ত;
    }

    pool->size     = size;
    pool->alloc    = alloc ? alloc : av_buffer_alloc;

    atomic_init(&pool->refcount, 1);

    ঘূৰাই pool;
}

স্থির শূন্য buffer_pool_flush(AVBufferPool *pool)
{
    যেতিয়ালৈ (pool->pool) {
        BufferPoolEntry *buf = pool->pool;
        pool->pool = buf->next;

        যদি (buf->মুক্ত == av_buffer_default_free)
            FF_ASAN_UNPOISON(buf->data, pool->size);
        buf->মুক্ত(buf->opaque, buf->data);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
স্থির শূন্য buffer_pool_free(AVBufferPool *pool)
{
    buffer_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    যদি (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

শূন্য av_buffer_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    যদি (!ppool || !*ppool)
        ঘূৰাই;
    pool   = *ppool;
    *ppool = রিক্ত;

    ff_mutex_lock(&pool->mutex);
    buffer_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    যদি (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

স্থির শূন্য pool_release_buffer(শূন্য *opaque, uint8_t *data)
{
    BufferPoolEntry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    যদি (buf->মুক্ত == av_buffer_default_free)
        FF_ASAN_POISON(buf->data, pool->size);

    ff_mutex_lock(&pool->mutex);
    buf->next = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    যদি (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        buffer_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
স্থির AVBufferRef *pool_alloc_buffer(AVBufferPool *pool)
{
    BufferPoolEntry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->size) :
                         pool->alloc(pool->size);
    যদি (!ret)
        ঘূৰাই রিক্ত;

    buf = av_mallocz(পরিমাণ(*buf));
    যদি (!buf) {
        av_buffer_unref(&ret);
        ঘূৰাই রিক্ত;
    }

    buf->data   = ret->buffer->data;
    buf->opaque = ret->buffer->opaque;
    buf->মুক্ত   = ret->buffer->মুক্ত;
    buf->pool   = pool;

    ret->buffer->opaque = buf;
    ret->buffer->মুক্ত   = pool_release_buffer;

    ঘূৰাই ret;
}

AVBufferRef *av_buffer_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    BufferPoolEntry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    যদি (buf) {
        memset(&buf->buffer, 0, পরিমাণ(buf->buffer));
        ret = buffer_create(&buf->buffer, buf->data, pool->size,
                            pool_release_buffer, buf, 0);
        যদি (ret) {
            pool->pool = buf->next;
            buf->next = রিক্ত;
            buf->buffer.flags_internal |= BUFFER_FLAG_NO_FREE;
            যদি (buf->মুক্ত == av_buffer_default_free) {
                FF_ASAN_UNPOISON(buf->data, pool->size);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                যদি (!pool->alloc2 && pool->alloc == av_buffer_alloc)
                    FF_MEM_UNDEFINED(buf->data, pool->size);
            }
        }
    } অন্যথা {
        ret = pool_alloc_buffer(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    যদি (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ঘূৰাই ret;
}

শূন্য *av_buffer_pool_buffer_get_opaque(ধ্রুৱ AVBufferRef *ref)
{
    BufferPoolEntry *buf = ref->buffer->opaque;
    av_assert0(buf);
    ঘূৰাই buf->opaque;
}

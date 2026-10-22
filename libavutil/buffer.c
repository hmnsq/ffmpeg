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

#समावेश <stdatomic.h>
#समावेश <stdint.h>
#समावेश <string.h>

#समावेश "avassert.h"
#समावेश "buffer_internal.h"
#समावेश "common.h"
#समावेश "mem.h"
#समावेश "sanitizer.h"
#समावेश "thread.h"

अटल AVBufferRef *बफर_create(AVBuffer *buf, uint8_t *तथ्य, माप_प्रकार आकार,
                                  व्योम (*मुक्त)(व्योम *opaque, uint8_t *तथ्य),
                                  व्योम *opaque, पूर्णांक flags)
{
    AVBufferRef *ref = शून्य;

    buf->तथ्य     = तथ्य;
    buf->आकार     = आकार;
    buf->मुक्त     = मुक्त ? मुक्त : av_बफर_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(माप(*ref));
    अगर (!ref)
        वापस शून्य;

    ref->बफर = buf;
    ref->तथ्य   = तथ्य;
    ref->आकार   = आकार;

    वापस ref;
}

AVBufferRef *av_बफर_create(uint8_t *तथ्य, माप_प्रकार आकार,
                              व्योम (*मुक्त)(व्योम *opaque, uint8_t *तथ्य),
                              व्योम *opaque, पूर्णांक flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(माप(*buf));
    अगर (!buf)
        वापस शून्य;

    ret = बफर_create(buf, तथ्य, आकार, मुक्त, opaque, flags);
    अगर (!ret) {
        av_free(buf);
        वापस शून्य;
    }
    वापस ret;
}

व्योम av_बफर_default_free(व्योम *opaque, uint8_t *तथ्य)
{
    av_free(तथ्य);
}

AVBufferRef *av_बफर_alloc(माप_प्रकार आकार)
{
    AVBufferRef *ret = शून्य;
    uint8_t    *तथ्य = शून्य;

    तथ्य = av_malloc(आकार);
    अगर (!तथ्य)
        वापस शून्य;

    ret = av_बफर_create(तथ्य, आकार, av_बफर_default_free, शून्य, 0);
    अगर (!ret)
        av_freep(&तथ्य);

    वापस ret;
}

AVBufferRef *av_बफर_allocz(माप_प्रकार आकार)
{
    AVBufferRef *ret = av_बफर_alloc(आकार);
    अगर (!ret)
        वापस शून्य;

    स_रखो(ret->तथ्य, 0, आकार);
    वापस ret;
}

AVBufferRef *av_बफर_ref(स्थिर AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(माप(*ret));

    अगर (!ret)
        वापस शून्य;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->बफर->refcount, 1, memory_order_relaxed);

    वापस ret;
}

अटल व्योम बफर_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->बफर;

    अगर (src) {
        **dst = **src;
        av_freep(src);
    } अन्यथा
        av_freep(dst);

    अगर (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        पूर्णांक free_avbuffer = !(b->flags_internal & बफर_FLAG_NO_FREE);
        b->मुक्त(b->opaque, b->तथ्य);
        अगर (free_avbuffer)
            av_free(b);
    }
}

व्योम av_बफर_unref(AVBufferRef **buf)
{
    अगर (!buf || !*buf)
        वापस;

    बफर_replace(buf, शून्य);
}

पूर्णांक av_बफर_is_writable(स्थिर AVBufferRef *buf)
{
    अगर (buf->बफर->flags & AV_बफर_FLAG_READONLY)
        वापस 0;

    वापस atomic_load(&buf->बफर->refcount) == 1;
}

व्योम *av_बफर_get_opaque(स्थिर AVBufferRef *buf)
{
    वापस buf->बफर->opaque;
}

पूर्णांक av_बफर_get_ref_गिनती(स्थिर AVBufferRef *buf)
{
    वापस atomic_load(&buf->बफर->refcount);
}

पूर्णांक av_बफर_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    अगर (av_बफर_is_writable(buf))
        वापस 0;

    newbuf = av_बफर_alloc(buf->आकार);
    अगर (!newbuf)
        वापस AVERROR(ENOMEM);

    स_नकल(newbuf->तथ्य, buf->तथ्य, buf->आकार);

    बफर_replace(pbuf, &newbuf);

    वापस 0;
}

पूर्णांक av_बफर_realloc(AVBufferRef **pbuf, माप_प्रकार आकार)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    पूर्णांक ret;

    अगर (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *तथ्य = av_realloc(शून्य, आकार);
        अगर (!तथ्य)
            वापस AVERROR(ENOMEM);

        buf = av_बफर_create(तथ्य, आकार, av_बफर_default_free, शून्य, 0);
        अगर (!buf) {
            av_freep(&तथ्य);
            वापस AVERROR(ENOMEM);
        }

        buf->बफर->flags_internal |= बफर_FLAG_REALLOCATABLE;
        *pbuf = buf;

        वापस 0;
    } अन्यथा अगर (buf->आकार == आकार)
        वापस 0;

    अगर (!(buf->बफर->flags_internal & बफर_FLAG_REALLOCATABLE) ||
        !av_बफर_is_writable(buf) || buf->तथ्य != buf->बफर->तथ्य) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = शून्य;

        ret = av_बफर_realloc(&new, आकार);
        अगर (ret < 0)
            वापस ret;

        स_नकल(new->तथ्य, buf->तथ्य, FFMIN(आकार, buf->आकार));

        बफर_replace(pbuf, &new);
        वापस 0;
    }

    tmp = av_realloc(buf->बफर->तथ्य, आकार);
    अगर (!tmp)
        वापस AVERROR(ENOMEM);

    buf->बफर->तथ्य = buf->तथ्य = tmp;
    buf->बफर->आकार = buf->आकार = आकार;
    वापस 0;
}

पूर्णांक av_बफर_replace(AVBufferRef **pdst, स्थिर AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    अगर (!src) {
        av_बफर_unref(pdst);
        वापस 0;
    }

    अगर (dst && dst->बफर == src->बफर) {
        /* make sure the data pointers match */
        dst->तथ्य = src->तथ्य;
        dst->आकार = src->आकार;
        वापस 0;
    }

    tmp = av_बफर_ref(src);
    अगर (!tmp)
        वापस AVERROR(ENOMEM);

    av_बफर_unref(pdst);
    *pdst = tmp;
    वापस 0;
}

AVBufferPool *av_बफर_pool_init2(माप_प्रकार आकार, व्योम *opaque,
                                   AVBufferRef* (*alloc)(व्योम *opaque, माप_प्रकार आकार),
                                   व्योम (*pool_free)(व्योम *opaque))
{
    AVBufferPool *pool = av_mallocz(माप(*pool));
    अगर (!pool)
        वापस शून्य;

    अगर (ff_mutex_init(&pool->mutex, शून्य)) {
        av_free(pool);
        वापस शून्य;
    }

    pool->आकार      = आकार;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_बफर_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    वापस pool;
}

AVBufferPool *av_बफर_pool_init(माप_प्रकार आकार, AVBufferRef* (*alloc)(माप_प्रकार आकार))
{
    AVBufferPool *pool = av_mallocz(माप(*pool));
    अगर (!pool)
        वापस शून्य;

    अगर (ff_mutex_init(&pool->mutex, शून्य)) {
        av_free(pool);
        वापस शून्य;
    }

    pool->आकार     = आकार;
    pool->alloc    = alloc ? alloc : av_बफर_alloc;

    atomic_init(&pool->refcount, 1);

    वापस pool;
}

अटल व्योम बफर_pool_flush(AVBufferPool *pool)
{
    जबतक (pool->pool) {
        बफर_Pool_Entry *buf = pool->pool;
        pool->pool = buf->अग्र;

        अगर (buf->मुक्त == av_बफर_default_free)
            FF_ASAN_UNPOISON(buf->तथ्य, pool->आकार);
        buf->मुक्त(buf->opaque, buf->तथ्य);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
अटल व्योम बफर_pool_free(AVBufferPool *pool)
{
    बफर_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    अगर (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

व्योम av_बफर_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    अगर (!ppool || !*ppool)
        वापस;
    pool   = *ppool;
    *ppool = शून्य;

    ff_mutex_lock(&pool->mutex);
    बफर_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    अगर (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        बफर_pool_free(pool);
}

अटल व्योम pool_release_बफर(व्योम *opaque, uint8_t *तथ्य)
{
    बफर_Pool_Entry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    अगर (buf->मुक्त == av_बफर_default_free)
        FF_ASAN_POISON(buf->तथ्य, pool->आकार);

    ff_mutex_lock(&pool->mutex);
    buf->अग्र = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    अगर (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        बफर_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
अटल AVBufferRef *pool_alloc_बफर(AVBufferPool *pool)
{
    बफर_Pool_Entry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->आकार) :
                         pool->alloc(pool->आकार);
    अगर (!ret)
        वापस शून्य;

    buf = av_mallocz(माप(*buf));
    अगर (!buf) {
        av_बफर_unref(&ret);
        वापस शून्य;
    }

    buf->तथ्य   = ret->बफर->तथ्य;
    buf->opaque = ret->बफर->opaque;
    buf->मुक्त   = ret->बफर->मुक्त;
    buf->pool   = pool;

    ret->बफर->opaque = buf;
    ret->बफर->मुक्त   = pool_release_बफर;

    वापस ret;
}

AVBufferRef *av_बफर_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    बफर_Pool_Entry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    अगर (buf) {
        स_रखो(&buf->बफर, 0, माप(buf->बफर));
        ret = बफर_create(&buf->बफर, buf->तथ्य, pool->आकार,
                            pool_release_बफर, buf, 0);
        अगर (ret) {
            pool->pool = buf->अग्र;
            buf->अग्र = शून्य;
            buf->बफर.flags_internal |= बफर_FLAG_NO_FREE;
            अगर (buf->मुक्त == av_बफर_default_free) {
                FF_ASAN_UNPOISON(buf->तथ्य, pool->आकार);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                अगर (!pool->alloc2 && pool->alloc == av_बफर_alloc)
                    FF_MEM_UNDEFINED(buf->तथ्य, pool->आकार);
            }
        }
    } अन्यथा {
        ret = pool_alloc_बफर(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    अगर (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    वापस ret;
}

व्योम *av_बफर_pool_बफर_get_opaque(स्थिर AVBufferRef *ref)
{
    बफर_Pool_Entry *buf = ref->बफर->opaque;
    av_assert0(buf);
    वापस buf->opaque;
}

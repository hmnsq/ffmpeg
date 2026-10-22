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

ಸ್ಥಿರ AVBufferRef *ಬಫರ್_create(AVBuffer *buf, uint8_t *ದತ್ತಾಂಶ, size_t ಗಾತ್ರ_2,
                                  ಶೂನ್ಯ (*ಬಿಡುಗಡೆ)(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ),
                                  ಶೂನ್ಯ *opaque, ಪೂರ್ಣಾಂಕ flags)
{
    AVBufferRef *ref = ಖಾಲಿ;

    buf->ದತ್ತಾಂಶ     = ದತ್ತಾಂಶ;
    buf->ಗಾತ್ರ_2     = ಗಾತ್ರ_2;
    buf->ಬಿಡುಗಡೆ     = ಬಿಡುಗಡೆ ? ಬಿಡುಗಡೆ : av_ಬಫರ್_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(ಗಾತ್ರ(*ref));
    ಆದರೆ (!ref)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ref->ಬಫರ್ = buf;
    ref->ದತ್ತಾಂಶ   = ದತ್ತಾಂಶ;
    ref->ಗಾತ್ರ_2   = ಗಾತ್ರ_2;

    ಹಿಂತಿರುಗಿ ref;
}

AVBufferRef *av_ಬಫರ್_create(uint8_t *ದತ್ತಾಂಶ, size_t ಗಾತ್ರ_2,
                              ಶೂನ್ಯ (*ಬಿಡುಗಡೆ)(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ),
                              ಶೂನ್ಯ *opaque, ಪೂರ್ಣಾಂಕ flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(ಗಾತ್ರ(*buf));
    ಆದರೆ (!buf)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ret = ಬಫರ್_create(buf, ದತ್ತಾಂಶ, ಗಾತ್ರ_2, ಬಿಡುಗಡೆ, opaque, flags);
    ಆದರೆ (!ret) {
        av_free(buf);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ av_ಬಫರ್_default_free(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    av_free(ದತ್ತಾಂಶ);
}

AVBufferRef *av_ಬಫರ್_alloc(size_t ಗಾತ್ರ_2)
{
    AVBufferRef *ret = ಖಾಲಿ;
    uint8_t    *ದತ್ತಾಂಶ = ಖಾಲಿ;

    ದತ್ತಾಂಶ = av_malloc(ಗಾತ್ರ_2);
    ಆದರೆ (!ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ret = av_ಬಫರ್_create(ದತ್ತಾಂಶ, ಗಾತ್ರ_2, av_ಬಫರ್_default_free, ಖಾಲಿ, 0);
    ಆದರೆ (!ret)
        av_freep(&ದತ್ತಾಂಶ);

    ಹಿಂತಿರುಗಿ ret;
}

AVBufferRef *av_ಬಫರ್_allocz(size_t ಗಾತ್ರ_2)
{
    AVBufferRef *ret = av_ಬಫರ್_alloc(ಗಾತ್ರ_2);
    ಆದರೆ (!ret)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    memset(ret->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ_2);
    ಹಿಂತಿರುಗಿ ret;
}

AVBufferRef *av_ಬಫರ್_ref(ಸ್ಥಿರಾಂಕ AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(ಗಾತ್ರ(*ret));

    ಆದರೆ (!ret)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->ಬಫರ್->refcount, 1, memory_order_relaxed);

    ಹಿಂತಿರುಗಿ ret;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಬಫರ್_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->ಬಫರ್;

    ಆದರೆ (src) {
        **dst = **src;
        av_freep(src);
    } ಇಲ್ಲದಿದ್ದರೆ
        av_freep(dst);

    ಆದರೆ (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        ಪೂರ್ಣಾಂಕ free_avbuffer = !(b->flags_ಆಂತರಿಕ & ಬಫರ್_FLAG_NO_FREE);
        b->ಬಿಡುಗಡೆ(b->opaque, b->ದತ್ತಾಂಶ);
        ಆದರೆ (free_avbuffer)
            av_free(b);
    }
}

ಶೂನ್ಯ av_ಬಫರ್_unref(AVBufferRef **buf)
{
    ಆದರೆ (!buf || !*buf)
        ಹಿಂತಿರುಗಿ;

    ಬಫರ್_replace(buf, ಖಾಲಿ);
}

ಪೂರ್ಣಾಂಕ av_ಬಫರ್_is_writable(ಸ್ಥಿರಾಂಕ AVBufferRef *buf)
{
    ಆದರೆ (buf->ಬಫರ್->flags & AV_ಬಫರ್_FLAG_READONLY)
        ಹಿಂತಿರುಗಿ 0;

    ಹಿಂತಿರುಗಿ atomic_load(&buf->ಬಫರ್->refcount) == 1;
}

ಶೂನ್ಯ *av_ಬಫರ್_get_opaque(ಸ್ಥಿರಾಂಕ AVBufferRef *buf)
{
    ಹಿಂತಿರುಗಿ buf->ಬಫರ್->opaque;
}

ಪೂರ್ಣಾಂಕ av_ಬಫರ್_get_ref_ಎಣಿಕೆ(ಸ್ಥಿರಾಂಕ AVBufferRef *buf)
{
    ಹಿಂತಿರುಗಿ atomic_load(&buf->ಬಫರ್->refcount);
}

ಪೂರ್ಣಾಂಕ av_ಬಫರ್_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    ಆದರೆ (av_ಬಫರ್_is_writable(buf))
        ಹಿಂತಿರುಗಿ 0;

    newbuf = av_ಬಫರ್_alloc(buf->ಗಾತ್ರ_2);
    ಆದರೆ (!newbuf)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    ಸ್ಮರಣೆ_ನಕಲು(newbuf->ದತ್ತಾಂಶ, buf->ದತ್ತಾಂಶ, buf->ಗಾತ್ರ_2);

    ಬಫರ್_replace(pbuf, &newbuf);

    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_ಬಫರ್_realloc(AVBufferRef **pbuf, size_t ಗಾತ್ರ_2)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    ಪೂರ್ಣಾಂಕ ret;

    ಆದರೆ (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *ದತ್ತಾಂಶ = av_realloc(ಖಾಲಿ, ಗಾತ್ರ_2);
        ಆದರೆ (!ದತ್ತಾಂಶ)
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

        buf = av_ಬಫರ್_create(ದತ್ತಾಂಶ, ಗಾತ್ರ_2, av_ಬಫರ್_default_free, ಖಾಲಿ, 0);
        ಆದರೆ (!buf) {
            av_freep(&ದತ್ತಾಂಶ);
            ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
        }

        buf->ಬಫರ್->flags_ಆಂತರಿಕ |= ಬಫರ್_FLAG_REALLOCATABLE;
        *pbuf = buf;

        ಹಿಂತಿರುಗಿ 0;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (buf->ಗಾತ್ರ_2 == ಗಾತ್ರ_2)
        ಹಿಂತಿರುಗಿ 0;

    ಆದರೆ (!(buf->ಬಫರ್->flags_ಆಂತರಿಕ & ಬಫರ್_FLAG_REALLOCATABLE) ||
        !av_ಬಫರ್_is_writable(buf) || buf->ದತ್ತಾಂಶ != buf->ಬಫರ್->ದತ್ತಾಂಶ) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = ಖಾಲಿ;

        ret = av_ಬಫರ್_realloc(&new, ಗಾತ್ರ_2);
        ಆದರೆ (ret < 0)
            ಹಿಂತಿರುಗಿ ret;

        ಸ್ಮರಣೆ_ನಕಲು(new->ದತ್ತಾಂಶ, buf->ದತ್ತಾಂಶ, FFMIN(ಗಾತ್ರ_2, buf->ಗಾತ್ರ_2));

        ಬಫರ್_replace(pbuf, &new);
        ಹಿಂತಿರುಗಿ 0;
    }

    tmp = av_realloc(buf->ಬಫರ್->ದತ್ತಾಂಶ, ಗಾತ್ರ_2);
    ಆದರೆ (!tmp)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    buf->ಬಫರ್->ದತ್ತಾಂಶ = buf->ದತ್ತಾಂಶ = tmp;
    buf->ಬಫರ್->ಗಾತ್ರ_2 = buf->ಗಾತ್ರ_2 = ಗಾತ್ರ_2;
    ಹಿಂತಿರುಗಿ 0;
}

ಪೂರ್ಣಾಂಕ av_ಬಫರ್_replace(AVBufferRef **pdst, ಸ್ಥಿರಾಂಕ AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    ಆದರೆ (!src) {
        av_ಬಫರ್_unref(pdst);
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (dst && dst->ಬಫರ್ == src->ಬಫರ್) {
        /* make sure the data pointers match */
        dst->ದತ್ತಾಂಶ = src->ದತ್ತಾಂಶ;
        dst->ಗಾತ್ರ_2 = src->ಗಾತ್ರ_2;
        ಹಿಂತಿರುಗಿ 0;
    }

    tmp = av_ಬಫರ್_ref(src);
    ಆದರೆ (!tmp)
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);

    av_ಬಫರ್_unref(pdst);
    *pdst = tmp;
    ಹಿಂತಿರುಗಿ 0;
}

AVBufferPool *av_ಬಫರ್_pool_init2(size_t ಗಾತ್ರ_2, ಶೂನ್ಯ *opaque,
                                   AVBufferRef* (*alloc)(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2),
                                   ಶೂನ್ಯ (*pool_free)(ಶೂನ್ಯ *opaque))
{
    AVBufferPool *pool = av_mallocz(ಗಾತ್ರ(*pool));
    ಆದರೆ (!pool)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (ff_mutex_init(&pool->mutex, ಖಾಲಿ)) {
        av_free(pool);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    pool->ಗಾತ್ರ_2      = ಗಾತ್ರ_2;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_ಬಫರ್_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    ಹಿಂತಿರುಗಿ pool;
}

AVBufferPool *av_ಬಫರ್_pool_init(size_t ಗಾತ್ರ_2, AVBufferRef* (*alloc)(size_t ಗಾತ್ರ_2))
{
    AVBufferPool *pool = av_mallocz(ಗಾತ್ರ(*pool));
    ಆದರೆ (!pool)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    ಆದರೆ (ff_mutex_init(&pool->mutex, ಖಾಲಿ)) {
        av_free(pool);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    pool->ಗಾತ್ರ_2     = ಗಾತ್ರ_2;
    pool->alloc    = alloc ? alloc : av_ಬಫರ್_alloc;

    atomic_init(&pool->refcount, 1);

    ಹಿಂತಿರುಗಿ pool;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಬಫರ್_pool_flush(AVBufferPool *pool)
{
    ಆಗ (pool->pool) {
        ಬಫರ್_Pool_ನಮೂದು *buf = pool->pool;
        pool->pool = buf->ಮುಂದಿನ;

        ಆದರೆ (buf->ಬಿಡುಗಡೆ == av_ಬಫರ್_default_free)
            FF_ASAN_UNPOISON(buf->ದತ್ತಾಂಶ, pool->ಗಾತ್ರ_2);
        buf->ಬಿಡುಗಡೆ(buf->opaque, buf->ದತ್ತಾಂಶ);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
ಸ್ಥಿರ ಶೂನ್ಯ ಬಫರ್_pool_free(AVBufferPool *pool)
{
    ಬಫರ್_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    ಆದರೆ (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

ಶೂನ್ಯ av_ಬಫರ್_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    ಆದರೆ (!ppool || !*ppool)
        ಹಿಂತಿರುಗಿ;
    pool   = *ppool;
    *ppool = ಖಾಲಿ;

    ff_mutex_ಬೀಗ(&pool->mutex);
    ಬಫರ್_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    ಆದರೆ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        ಬಫರ್_pool_free(pool);
}

ಸ್ಥಿರ ಶೂನ್ಯ pool_release_ಬಫರ್(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ)
{
    ಬಫರ್_Pool_ನಮೂದು *buf = opaque;
    AVBufferPool *pool = buf->pool;

    ಆದರೆ (buf->ಬಿಡುಗಡೆ == av_ಬಫರ್_default_free)
        FF_ASAN_POISON(buf->ದತ್ತಾಂಶ, pool->ಗಾತ್ರ_2);

    ff_mutex_ಬೀಗ(&pool->mutex);
    buf->ಮುಂದಿನ = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    ಆದರೆ (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        ಬಫರ್_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
ಸ್ಥಿರ AVBufferRef *pool_alloc_ಬಫರ್(AVBufferPool *pool)
{
    ಬಫರ್_Pool_ನಮೂದು *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->ಗಾತ್ರ_2) :
                         pool->alloc(pool->ಗಾತ್ರ_2);
    ಆದರೆ (!ret)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    buf = av_mallocz(ಗಾತ್ರ(*buf));
    ಆದರೆ (!buf) {
        av_ಬಫರ್_unref(&ret);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    buf->ದತ್ತಾಂಶ   = ret->ಬಫರ್->ದತ್ತಾಂಶ;
    buf->opaque = ret->ಬಫರ್->opaque;
    buf->ಬಿಡುಗಡೆ   = ret->ಬಫರ್->ಬಿಡುಗಡೆ;
    buf->pool   = pool;

    ret->ಬಫರ್->opaque = buf;
    ret->ಬಫರ್->ಬಿಡುಗಡೆ   = pool_release_ಬಫರ್;

    ಹಿಂತಿರುಗಿ ret;
}

AVBufferRef *av_ಬಫರ್_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    ಬಫರ್_Pool_ನಮೂದು *buf;

    ff_mutex_ಬೀಗ(&pool->mutex);
    buf = pool->pool;
    ಆದರೆ (buf) {
        memset(&buf->ಬಫರ್, 0, ಗಾತ್ರ(buf->ಬಫರ್));
        ret = ಬಫರ್_create(&buf->ಬಫರ್, buf->ದತ್ತಾಂಶ, pool->ಗಾತ್ರ_2,
                            pool_release_ಬಫರ್, buf, 0);
        ಆದರೆ (ret) {
            pool->pool = buf->ಮುಂದಿನ;
            buf->ಮುಂದಿನ = ಖಾಲಿ;
            buf->ಬಫರ್.flags_ಆಂತರಿಕ |= ಬಫರ್_FLAG_NO_FREE;
            ಆದರೆ (buf->ಬಿಡುಗಡೆ == av_ಬಫರ್_default_free) {
                FF_ASAN_UNPOISON(buf->ದತ್ತಾಂಶ, pool->ಗಾತ್ರ_2);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                ಆದರೆ (!pool->alloc2 && pool->alloc == av_ಬಫರ್_alloc)
                    FF_MEM_UNDEFINED(buf->ದತ್ತಾಂಶ, pool->ಗಾತ್ರ_2);
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ret = pool_alloc_ಬಫರ್(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    ಆದರೆ (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ಹಿಂತಿರುಗಿ ret;
}

ಶೂನ್ಯ *av_ಬಫರ್_pool_ಬಫರ್_get_opaque(ಸ್ಥಿರಾಂಕ AVBufferRef *ref)
{
    ಬಫರ್_Pool_ನಮೂದು *buf = ref->ಬಫರ್->opaque;
    av_assert0(buf);
    ಹಿಂತಿರುಗಿ buf->opaque;
}

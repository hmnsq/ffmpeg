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

#অন্তর্ভাব <stdatomic.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "avassert.h"
#অন্তর্ভাব "buffer_internal.h"
#অন্তর্ভাব "common.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব "sanitizer.h"
#অন্তর্ভাব "thread.h"

স্থির AVBufferRef *বাফার_create(AVBuffer *buf, uint8_t *তথ্য, size_t আকার_2,
                                  শূন্য (*মুক্ত)(শূন্য *opaque, uint8_t *তথ্য),
                                  শূন্য *opaque, পূর্ণসংখ্যা flags)
{
    AVBufferRef *ref = ফাঁকা;

    buf->তথ্য     = তথ্য;
    buf->আকার_2     = আকার_2;
    buf->মুক্ত     = মুক্ত ? মুক্ত : av_বাফার_default_free;
    buf->opaque   = opaque;

    atomic_init(&buf->refcount, 1);

    buf->flags = flags;

    ref = av_mallocz(আকার(*ref));
    যদি (!ref)
        ফেরত ফাঁকা;

    ref->বাফার = buf;
    ref->তথ্য   = তথ্য;
    ref->আকার_2   = আকার_2;

    ফেরত ref;
}

AVBufferRef *av_বাফার_create(uint8_t *তথ্য, size_t আকার_2,
                              শূন্য (*মুক্ত)(শূন্য *opaque, uint8_t *তথ্য),
                              শূন্য *opaque, পূর্ণসংখ্যা flags)
{
    AVBufferRef *ret;
    AVBuffer *buf = av_mallocz(আকার(*buf));
    যদি (!buf)
        ফেরত ফাঁকা;

    ret = বাফার_create(buf, তথ্য, আকার_2, মুক্ত, opaque, flags);
    যদি (!ret) {
        av_free(buf);
        ফেরত ফাঁকা;
    }
    ফেরত ret;
}

শূন্য av_বাফার_default_free(শূন্য *opaque, uint8_t *তথ্য)
{
    av_free(তথ্য);
}

AVBufferRef *av_বাফার_alloc(size_t আকার_2)
{
    AVBufferRef *ret = ফাঁকা;
    uint8_t    *তথ্য = ফাঁকা;

    তথ্য = av_malloc(আকার_2);
    যদি (!তথ্য)
        ফেরত ফাঁকা;

    ret = av_বাফার_create(তথ্য, আকার_2, av_বাফার_default_free, ফাঁকা, 0);
    যদি (!ret)
        av_freep(&তথ্য);

    ফেরত ret;
}

AVBufferRef *av_বাফার_allocz(size_t আকার_2)
{
    AVBufferRef *ret = av_বাফার_alloc(আকার_2);
    যদি (!ret)
        ফেরত ফাঁকা;

    memset(ret->তথ্য, 0, আকার_2);
    ফেরত ret;
}

AVBufferRef *av_বাফার_ref(ধ্রুবক AVBufferRef *buf)
{
    AVBufferRef *ret = av_mallocz(আকার(*ret));

    যদি (!ret)
        ফেরত ফাঁকা;

    *ret = *buf;

    atomic_fetch_add_explicit(&buf->বাফার->refcount, 1, memory_order_relaxed);

    ফেরত ret;
}

স্থির শূন্য বাফার_replace(AVBufferRef **dst, AVBufferRef **src)
{
    AVBuffer *b;

    b = (*dst)->বাফার;

    যদি (src) {
        **dst = **src;
        av_freep(src);
    } অন্যথা
        av_freep(dst);

    যদি (atomic_fetch_sub_explicit(&b->refcount, 1, memory_order_acq_rel) == 1) {
        /* b->free below might already free the structure containing *b,
         * so we have to read the flag now to avoid use-after-free. */
        পূর্ণসংখ্যা free_avbuffer = !(b->flags_internal & বাফার_FLAG_NO_FREE);
        b->মুক্ত(b->opaque, b->তথ্য);
        যদি (free_avbuffer)
            av_free(b);
    }
}

শূন্য av_বাফার_unref(AVBufferRef **buf)
{
    যদি (!buf || !*buf)
        ফেরত;

    বাফার_replace(buf, ফাঁকা);
}

পূর্ণসংখ্যা av_বাফার_is_writable(ধ্রুবক AVBufferRef *buf)
{
    যদি (buf->বাফার->flags & AV_বাফার_FLAG_READONLY)
        ফেরত 0;

    ফেরত atomic_load(&buf->বাফার->refcount) == 1;
}

শূন্য *av_বাফার_get_opaque(ধ্রুবক AVBufferRef *buf)
{
    ফেরত buf->বাফার->opaque;
}

পূর্ণসংখ্যা av_বাফার_get_ref_গুনতি(ধ্রুবক AVBufferRef *buf)
{
    ফেরত atomic_load(&buf->বাফার->refcount);
}

পূর্ণসংখ্যা av_বাফার_make_writable(AVBufferRef **pbuf)
{
    AVBufferRef *newbuf, *buf = *pbuf;

    যদি (av_বাফার_is_writable(buf))
        ফেরত 0;

    newbuf = av_বাফার_alloc(buf->আকার_2);
    যদি (!newbuf)
        ফেরত AVERROR(ENOMEM);

    memcpy(newbuf->তথ্য, buf->তথ্য, buf->আকার_2);

    বাফার_replace(pbuf, &newbuf);

    ফেরত 0;
}

পূর্ণসংখ্যা av_বাফার_realloc(AVBufferRef **pbuf, size_t আকার_2)
{
    AVBufferRef *buf = *pbuf;
    uint8_t *tmp;
    পূর্ণসংখ্যা ret;

    যদি (!buf) {
        /* allocate a new buffer with av_realloc(), so it will be reallocatable
         * later */
        uint8_t *তথ্য = av_realloc(ফাঁকা, আকার_2);
        যদি (!তথ্য)
            ফেরত AVERROR(ENOMEM);

        buf = av_বাফার_create(তথ্য, আকার_2, av_বাফার_default_free, ফাঁকা, 0);
        যদি (!buf) {
            av_freep(&তথ্য);
            ফেরত AVERROR(ENOMEM);
        }

        buf->বাফার->flags_internal |= বাফার_FLAG_REALLOCATABLE;
        *pbuf = buf;

        ফেরত 0;
    } অন্যথা যদি (buf->আকার_2 == আকার_2)
        ফেরত 0;

    যদি (!(buf->বাফার->flags_internal & বাফার_FLAG_REALLOCATABLE) ||
        !av_বাফার_is_writable(buf) || buf->তথ্য != buf->বাফার->তথ্য) {
        /* cannot realloc, allocate a new reallocable buffer and copy data */
        AVBufferRef *new = ফাঁকা;

        ret = av_বাফার_realloc(&new, আকার_2);
        যদি (ret < 0)
            ফেরত ret;

        memcpy(new->তথ্য, buf->তথ্য, FFMIN(আকার_2, buf->আকার_2));

        বাফার_replace(pbuf, &new);
        ফেরত 0;
    }

    tmp = av_realloc(buf->বাফার->তথ্য, আকার_2);
    যদি (!tmp)
        ফেরত AVERROR(ENOMEM);

    buf->বাফার->তথ্য = buf->তথ্য = tmp;
    buf->বাফার->আকার_2 = buf->আকার_2 = আকার_2;
    ফেরত 0;
}

পূর্ণসংখ্যা av_বাফার_replace(AVBufferRef **pdst, ধ্রুবক AVBufferRef *src)
{
    AVBufferRef *dst = *pdst;
    AVBufferRef *tmp;

    যদি (!src) {
        av_বাফার_unref(pdst);
        ফেরত 0;
    }

    যদি (dst && dst->বাফার == src->বাফার) {
        /* make sure the data pointers match */
        dst->তথ্য = src->তথ্য;
        dst->আকার_2 = src->আকার_2;
        ফেরত 0;
    }

    tmp = av_বাফার_ref(src);
    যদি (!tmp)
        ফেরত AVERROR(ENOMEM);

    av_বাফার_unref(pdst);
    *pdst = tmp;
    ফেরত 0;
}

AVBufferPool *av_বাফার_pool_init2(size_t আকার_2, শূন্য *opaque,
                                   AVBufferRef* (*alloc)(শূন্য *opaque, size_t আকার_2),
                                   শূন্য (*pool_free)(শূন্য *opaque))
{
    AVBufferPool *pool = av_mallocz(আকার(*pool));
    যদি (!pool)
        ফেরত ফাঁকা;

    যদি (ff_mutex_init(&pool->mutex, ফাঁকা)) {
        av_free(pool);
        ফেরত ফাঁকা;
    }

    pool->আকার_2      = আকার_2;
    pool->opaque    = opaque;
    pool->alloc2    = alloc;
    pool->alloc     = av_বাফার_alloc; // fallback
    pool->pool_free = pool_free;

    atomic_init(&pool->refcount, 1);

    ফেরত pool;
}

AVBufferPool *av_বাফার_pool_init(size_t আকার_2, AVBufferRef* (*alloc)(size_t আকার_2))
{
    AVBufferPool *pool = av_mallocz(আকার(*pool));
    যদি (!pool)
        ফেরত ফাঁকা;

    যদি (ff_mutex_init(&pool->mutex, ফাঁকা)) {
        av_free(pool);
        ফেরত ফাঁকা;
    }

    pool->আকার_2     = আকার_2;
    pool->alloc    = alloc ? alloc : av_বাফার_alloc;

    atomic_init(&pool->refcount, 1);

    ফেরত pool;
}

স্থির শূন্য বাফার_pool_flush(AVBufferPool *pool)
{
    যখন (pool->pool) {
        বাফার_Pool_Entry *buf = pool->pool;
        pool->pool = buf->পরবর্তী;

        যদি (buf->মুক্ত == av_বাফার_default_free)
            FF_ASAN_UNPOISON(buf->তথ্য, pool->আকার_2);
        buf->মুক্ত(buf->opaque, buf->তথ্য);
        av_freep(&buf);
    }
}

/*
 * This function gets called when the pool has been uninited and
 * all the buffers returned to it.
 */
স্থির শূন্য বাফার_pool_free(AVBufferPool *pool)
{
    বাফার_pool_flush(pool);
    ff_mutex_destroy(&pool->mutex);

    যদি (pool->pool_free)
        pool->pool_free(pool->opaque);

    av_freep(&pool);
}

শূন্য av_বাফার_pool_uninit(AVBufferPool **ppool)
{
    AVBufferPool *pool;

    যদি (!ppool || !*ppool)
        ফেরত;
    pool   = *ppool;
    *ppool = ফাঁকা;

    ff_mutex_lock(&pool->mutex);
    বাফার_pool_flush(pool);
    ff_mutex_unlock(&pool->mutex);

    যদি (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        বাফার_pool_free(pool);
}

স্থির শূন্য pool_release_বাফার(শূন্য *opaque, uint8_t *তথ্য)
{
    বাফার_Pool_Entry *buf = opaque;
    AVBufferPool *pool = buf->pool;

    যদি (buf->মুক্ত == av_বাফার_default_free)
        FF_ASAN_POISON(buf->তথ্য, pool->আকার_2);

    ff_mutex_lock(&pool->mutex);
    buf->পরবর্তী = pool->pool;
    pool->pool = buf;
    ff_mutex_unlock(&pool->mutex);

    যদি (atomic_fetch_sub_explicit(&pool->refcount, 1, memory_order_acq_rel) == 1)
        বাফার_pool_free(pool);
}

/* allocate a new buffer and override its free() callback so that
 * it is returned to the pool on free */
স্থির AVBufferRef *pool_alloc_বাফার(AVBufferPool *pool)
{
    বাফার_Pool_Entry *buf;
    AVBufferRef     *ret;

    av_assert0(pool->alloc || pool->alloc2);

    ret = pool->alloc2 ? pool->alloc2(pool->opaque, pool->আকার_2) :
                         pool->alloc(pool->আকার_2);
    যদি (!ret)
        ফেরত ফাঁকা;

    buf = av_mallocz(আকার(*buf));
    যদি (!buf) {
        av_বাফার_unref(&ret);
        ফেরত ফাঁকা;
    }

    buf->তথ্য   = ret->বাফার->তথ্য;
    buf->opaque = ret->বাফার->opaque;
    buf->মুক্ত   = ret->বাফার->মুক্ত;
    buf->pool   = pool;

    ret->বাফার->opaque = buf;
    ret->বাফার->মুক্ত   = pool_release_বাফার;

    ফেরত ret;
}

AVBufferRef *av_বাফার_pool_get(AVBufferPool *pool)
{
    AVBufferRef *ret;
    বাফার_Pool_Entry *buf;

    ff_mutex_lock(&pool->mutex);
    buf = pool->pool;
    যদি (buf) {
        memset(&buf->বাফার, 0, আকার(buf->বাফার));
        ret = বাফার_create(&buf->বাফার, buf->তথ্য, pool->আকার_2,
                            pool_release_বাফার, buf, 0);
        যদি (ret) {
            pool->pool = buf->পরবর্তী;
            buf->পরবর্তী = ফাঁকা;
            buf->বাফার.flags_internal |= বাফার_FLAG_NO_FREE;
            যদি (buf->মুক্ত == av_বাফার_default_free) {
                FF_ASAN_UNPOISON(buf->তথ্য, pool->আকার_2);
                /* A pool that zeroes its buffers may be relied upon for never
                 * written regions staying zero, so only mark a reused buffer
                 * undefined when nothing was ever promised about its contents. */
                যদি (!pool->alloc2 && pool->alloc == av_বাফার_alloc)
                    FF_MEM_UNDEFINED(buf->তথ্য, pool->আকার_2);
            }
        }
    } অন্যথা {
        ret = pool_alloc_বাফার(pool);
    }
    ff_mutex_unlock(&pool->mutex);

    যদি (ret)
        atomic_fetch_add_explicit(&pool->refcount, 1, memory_order_relaxed);

    ফেরত ret;
}

শূন্য *av_বাফার_pool_বাফার_get_opaque(ধ্রুবক AVBufferRef *ref)
{
    বাফার_Pool_Entry *buf = ref->বাফার->opaque;
    av_assert0(buf);
    ফেরত buf->opaque;
}

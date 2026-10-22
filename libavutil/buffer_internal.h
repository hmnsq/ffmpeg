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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ਬਫਰ_ਅੰਦਰੂਨੀ_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ਬਫਰ_ਅੰਦਰੂਨੀ_H

#ਅਨ੍ਤਰ੍ਭਾਵ <stdatomic.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdint.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "buffer.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "thread.h"

/**
 * The buffer was av_realloc()ed, so it is reallocatable.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਬਫਰ_FLAG_REALLOCATABLE (1 << 0)
/**
 * The AVBuffer structure is part of a larger structure
 * and should not be freed.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਬਫਰ_FLAG_NO_FREE       (1 << 1)

ਬਣਤਰ AVBuffer {
    uint8_t *ਅੰਕੜੇ; /**< data described by this buffer */
    size_t ਮਾਪ; /**< size of data in bytes */

    /**
     *  number of existing AVBufferRef instances referring to this buffer
     */
    atomic_uint refcount;

    /**
     * a callback for freeing the data
     */
    ਖਾਲੀ (*ਮੁਕਤ)(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ);

    /**
     * an opaque pointer, to be used by the freeing callback
     */
    ਖਾਲੀ *opaque;

    /**
     * A combination of AV_BUFFER_FLAG_*
     */
    ਪੂਰਨ flags;

    /**
     * A combination of BUFFER_FLAG_*
     */
    ਪੂਰਨ flags_ਅੰਦਰੂਨੀ;
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ ਬਫਰ_Pool_ਇੰਦਰਾਜ {
    uint8_t *ਅੰਕੜੇ;

    /*
     * Backups of the original opaque/free of the AVBuffer corresponding to
     * data. They will be used to free the buffer when the pool is freed.
     */
    ਖਾਲੀ *opaque;
    ਖਾਲੀ (*ਮੁਕਤ)(ਖਾਲੀ *opaque, uint8_t *ਅੰਕੜੇ);

    AVBufferPool *pool;
    ਬਣਤਰ ਬਫਰ_Pool_ਇੰਦਰਾਜ *ਅਗਲਾ;

    /*
     * An AVBuffer structure to (re)use as AVBuffer for subsequent uses
     * of this BufferPoolEntry.
     */
    AVBuffer ਬਫਰ;
} ਬਫਰ_Pool_ਇੰਦਰਾਜ;

ਬਣਤਰ AVBufferPool {
    AVMutex mutex;
    ਬਫਰ_Pool_ਇੰਦਰਾਜ *pool;

    /*
     * This is used to track when the pool is to be freed.
     * The pointer to the pool itself held by the caller is considered to
     * be one reference. Each buffer requested by the caller increases refcount
     * by one, returning the buffer to the pool decreases it by one.
     * refcount reaches zero when the buffer has been uninited AND all the
     * buffers have been released, then it's safe to free the pool and all
     * the buffers in it.
     */
    atomic_uint refcount;

    size_t ਮਾਪ;
    ਖਾਲੀ *opaque;
    AVBufferRef* (*alloc)(size_t ਮਾਪ);
    AVBufferRef* (*alloc2)(ਖਾਲੀ *opaque, size_t ਮਾਪ);
    ਖਾਲੀ         (*pool_free)(ਖਾਲੀ *opaque);
};

#ਜੇ_ਅੰਤ /* AVUTIL_BUFFER_INTERNAL_H */

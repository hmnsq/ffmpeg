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

#నిర్వచితం_కాకపోతే AVUTIL_బఫరు_అంతర్గత_H
#నిర్వచించు AVUTIL_బఫరు_అంతర్గత_H

#అన్తర్భావ <stdatomic.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "buffer.h"
#అన్తర్భావ "thread.h"

/**
 * The buffer was av_realloc()ed, so it is reallocatable.
 */
#నిర్వచించు బఫరు_FLAG_REALLOCATABLE (1 << 0)
/**
 * The AVBuffer structure is part of a larger structure
 * and should not be freed.
 */
#నిర్వచించు బఫరు_FLAG_NO_FREE       (1 << 1)

నిర్మాణం AVBuffer {
    uint8_t *దత్తాంశం; /**< data described by this buffer */
    size_t కొలత; /**< size of data in bytes */

    /**
     *  number of existing AVBufferRef instances referring to this buffer
     */
    atomic_uint refcount;

    /**
     * a callback for freeing the data
     */
    శూన్య (*విడుదల)(శూన్య *opaque, uint8_t *దత్తాంశం);

    /**
     * an opaque pointer, to be used by the freeing callback
     */
    శూన్య *opaque;

    /**
     * A combination of AV_BUFFER_FLAG_*
     */
    పూర్ణాంకం flags;

    /**
     * A combination of BUFFER_FLAG_*
     */
    పూర్ణాంకం flags_అంతర్గత;
};

రకనిర్వచనం నిర్మాణం బఫరు_Pool_నమోదు {
    uint8_t *దత్తాంశం;

    /*
     * Backups of the original opaque/free of the AVBuffer corresponding to
     * data. They will be used to free the buffer when the pool is freed.
     */
    శూన్య *opaque;
    శూన్య (*విడుదల)(శూన్య *opaque, uint8_t *దత్తాంశం);

    AVBufferPool *pool;
    నిర్మాణం బఫరు_Pool_నమోదు *తదుపరి;

    /*
     * An AVBuffer structure to (re)use as AVBuffer for subsequent uses
     * of this BufferPoolEntry.
     */
    AVBuffer బఫరు;
} బఫరు_Pool_నమోదు;

నిర్మాణం AVBufferPool {
    AVMutex mutex;
    బఫరు_Pool_నమోదు *pool;

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

    size_t కొలత;
    శూన్య *opaque;
    AVBufferRef* (*alloc)(size_t కొలత);
    AVBufferRef* (*alloc2)(శూన్య *opaque, size_t కొలత);
    శూన్య         (*pool_free)(శూన్య *opaque);
};

#అయితే_ముగింపు /* AVUTIL_BUFFER_INTERNAL_H */

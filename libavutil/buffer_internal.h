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

#جے_بنا_تعریف AVUTIL_بفر_اندرونی_H
#تعریف_کرو AVUTIL_بفر_اندرونی_H

#ضمن <stdatomic.h>
#ضمن <stdint.h>

#ضمن "buffer.h"
#ضمن "thread.h"

/**
 * The buffer was av_realloc()ed, so it is reallocatable.
 */
#تعریف_کرو بفر_FLAG_REALLOCATABLE (1 << 0)
/**
 * The AVBuffer structure is part of a larger structure
 * and should not be freed.
 */
#تعریف_کرو بفر_FLAG_NO_FREE       (1 << 1)

بنية AVBuffer {
    uint8_t *انکڑے; /**< data described by this buffer */
    size_t ناپ; /**< size of data in bytes */

    /**
     *  number of existing AVBufferRef instances referring to this buffer
     */
    atomic_uint refcount;

    /**
     * a callback for freeing the data
     */
    فراغ (*حرر)(فراغ *opaque, uint8_t *انکڑے);

    /**
     * an opaque pointer, to be used by the freeing callback
     */
    فراغ *opaque;

    /**
     * A combination of AV_BUFFER_FLAG_*
     */
    صحيح flags;

    /**
     * A combination of BUFFER_FLAG_*
     */
    صحيح flags_اندرونی;
};

تعريفنوع بنية بفر_Pool_اندراج {
    uint8_t *انکڑے;

    /*
     * Backups of the original opaque/free of the AVBuffer corresponding to
     * data. They will be used to free the buffer when the pool is freed.
     */
    فراغ *opaque;
    فراغ (*حرر)(فراغ *opaque, uint8_t *انکڑے);

    AVBufferPool *pool;
    بنية بفر_Pool_اندراج *اگلا;

    /*
     * An AVBuffer structure to (re)use as AVBuffer for subsequent uses
     * of this BufferPoolEntry.
     */
    AVBuffer بفر;
} بفر_Pool_اندراج;

بنية AVBufferPool {
    AVMutex mutex;
    بفر_Pool_اندراج *pool;

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

    size_t ناپ;
    فراغ *opaque;
    AVBufferRef* (*alloc)(size_t ناپ);
    AVBufferRef* (*alloc2)(فراغ *opaque, size_t ناپ);
    فراغ         (*pool_free)(فراغ *opaque);
};

#جے_انت /* AVUTIL_BUFFER_INTERNAL_H */

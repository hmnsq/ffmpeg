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

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_بفر_اندروني_H
#وصف_ڪريو AVUTIL_بفر_اندروني_H

#ضمن <stdatomic.h>
#ضمن <stdint.h>

#ضمن "buffer.h"
#ضمن "thread.h"

/**
 * The buffer was av_realloc()ed, so it is reallocatable.
 */
#وصف_ڪريو بفر_FLAG_REALLOCATABLE (1 << 0)
/**
 * The AVBuffer structure is part of a larger structure
 * and should not be freed.
 */
#وصف_ڪريو بفر_FLAG_NO_FREE       (1 << 1)

بنية AVBuffer {
    uint8_t *معلومات; /**< data described by this buffer */
    size_t سائيز; /**< size of data in bytes */

    /**
     *  number of existing AVBufferRef instances referring to this buffer
     */
    atomic_uint refcount;

    /**
     * a callback for freeing the data
     */
    فراغ (*حرر)(فراغ *opaque, uint8_t *معلومات);

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
    صحيح flags_اندروني;
};

تعريفنوع بنية بفر_Pool_داخلا {
    uint8_t *معلومات;

    /*
     * Backups of the original opaque/free of the AVBuffer corresponding to
     * data. They will be used to free the buffer when the pool is freed.
     */
    فراغ *opaque;
    فراغ (*حرر)(فراغ *opaque, uint8_t *معلومات);

    AVBufferPool *pool;
    بنية بفر_Pool_داخلا *ايندڙ;

    /*
     * An AVBuffer structure to (re)use as AVBuffer for subsequent uses
     * of this BufferPoolEntry.
     */
    AVBuffer بفر;
} بفر_Pool_داخلا;

بنية AVBufferPool {
    AVMutex mutex;
    بفر_Pool_داخلا *pool;

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

    size_t سائيز;
    فراغ *opaque;
    AVBufferRef* (*alloc)(size_t سائيز);
    AVBufferRef* (*alloc2)(فراغ *opaque, size_t سائيز);
    فراغ         (*pool_free)(فراغ *opaque);
};

#جيڪڏهن_پورو /* AVUTIL_BUFFER_INTERNAL_H */

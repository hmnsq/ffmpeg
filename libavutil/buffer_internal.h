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

#ifndef AVUTIL_BUFFER_INTERNAL_H
#define AVUTIL_BUFFER_INTERNAL_H

#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "thread.h"

/**
 * The buffer was av_realloc()ed, so it is reallocatable.
 */
#define BUFFER_FLAG_REALLOCATABLE (1 << 0)
/**
 * The AVBuffer structure is part of a larger structure
 * and should not be freed.
 */
#define BUFFER_FLAG_NO_FREE       (1 << 1)

संरचना AVBuffer {
    uint8_t *data; /**< data described by this buffer */
    माप_प्रकार size; /**< size of data in bytes */

    /**
     *  number of existing AVBufferRef instances referring to this buffer
     */
    atomic_uint refcount;

    /**
     * a callback for freeing the data
     */
    शून्य (*मुक्त)(शून्य *opaque, uint8_t *data);

    /**
     * an opaque pointer, to be used by the freeing callback
     */
    शून्य *opaque;

    /**
     * A combination of AV_BUFFER_FLAG_*
     */
    पूर्णांक flags;

    /**
     * A combination of BUFFER_FLAG_*
     */
    पूर्णांक flags_internal;
};

प्रकारव्याख्या संरचना BufferPoolEntry {
    uint8_t *data;

    /*
     * Backups of the original opaque/free of the AVBuffer corresponding to
     * data. They will be used to free the buffer when the pool is freed.
     */
    शून्य *opaque;
    शून्य (*मुक्त)(शून्य *opaque, uint8_t *data);

    AVBufferPool *pool;
    संरचना BufferPoolEntry *next;

    /*
     * An AVBuffer structure to (re)use as AVBuffer for subsequent uses
     * of this BufferPoolEntry.
     */
    AVBuffer buffer;
} BufferPoolEntry;

संरचना AVBufferPool {
    AVMutex mutex;
    BufferPoolEntry *pool;

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

    माप_प्रकार size;
    शून्य *opaque;
    AVBufferRef* (*alloc)(माप_प्रकार size);
    AVBufferRef* (*alloc2)(शून्य *opaque, माप_प्रकार size);
    शून्य         (*pool_free)(शून्य *opaque);
};

#endif /* AVUTIL_BUFFER_INTERNAL_H */

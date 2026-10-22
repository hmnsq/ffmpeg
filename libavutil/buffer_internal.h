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

#अगर_अघोषित AVUTIL_बफर_INTERNAL_H
#घोषणा AVUTIL_बफर_INTERNAL_H

#समावेश <stdatomic.h>
#समावेश <stdint.h>

#समावेश "buffer.h"
#समावेश "thread.h"

/**
 * The buffer was av_realloc()ed, so it is reallocatable.
 */
#घोषणा बफर_FLAG_REALLOCATABLE (1 << 0)
/**
 * The AVBuffer structure is part of a larger structure
 * and should not be freed.
 */
#घोषणा बफर_FLAG_NO_FREE       (1 << 1)

काष्ठा AVBuffer {
    uint8_t *तथ्य; /**< data described by this buffer */
    माप_प्रकार आकार; /**< size of data in bytes */

    /**
     *  number of existing AVBufferRef instances referring to this buffer
     */
    atomic_uint refcount;

    /**
     * a callback for freeing the data
     */
    व्योम (*मुक्त)(व्योम *opaque, uint8_t *तथ्य);

    /**
     * an opaque pointer, to be used by the freeing callback
     */
    व्योम *opaque;

    /**
     * A combination of AV_BUFFER_FLAG_*
     */
    पूर्णांक flags;

    /**
     * A combination of BUFFER_FLAG_*
     */
    पूर्णांक flags_internal;
};

प्रकार काष्ठा बफर_Pool_Entry {
    uint8_t *तथ्य;

    /*
     * Backups of the original opaque/free of the AVBuffer corresponding to
     * data. They will be used to free the buffer when the pool is freed.
     */
    व्योम *opaque;
    व्योम (*मुक्त)(व्योम *opaque, uint8_t *तथ्य);

    AVBufferPool *pool;
    काष्ठा बफर_Pool_Entry *अग्र;

    /*
     * An AVBuffer structure to (re)use as AVBuffer for subsequent uses
     * of this BufferPoolEntry.
     */
    AVBuffer बफर;
} बफर_Pool_Entry;

काष्ठा AVBufferPool {
    AVMutex mutex;
    बफर_Pool_Entry *pool;

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

    माप_प्रकार आकार;
    व्योम *opaque;
    AVBufferRef* (*alloc)(माप_प्रकार आकार);
    AVBufferRef* (*alloc2)(व्योम *opaque, माप_प्रकार आकार);
    व्योम         (*pool_free)(व्योम *opaque);
};

#पूर्ण_अगर /* AVUTIL_BUFFER_INTERNAL_H */

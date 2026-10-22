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

#यदि_अपरिभाषितम् AVUTIL_बफर_आन्तरिकम्_H
#परिभाषय AVUTIL_बफर_आन्तरिकम्_H

#अन्तर्भाव <stdatomic.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "buffer.h"
#अन्तर्भाव "thread.h"

/**
 * The buffer was av_realloc()ed, so it is reallocatable.
 */
#परिभाषय बफर_FLAG_REALLOCATABLE (1 << 0)
/**
 * The AVBuffer structure is part of a larger structure
 * and should not be freed.
 */
#परिभाषय बफर_FLAG_NO_FREE       (1 << 1)

संरचना AVBuffer {
    uint8_t *दत्त; /**< data described by this buffer */
    size_t आकार; /**< size of data in bytes */

    /**
     *  number of existing AVBufferRef instances referring to this buffer
     */
    atomic_uint refcount;

    /**
     * a callback for freeing the data
     */
    शून्य (*मुक्त)(शून्य *opaque, uint8_t *दत्त);

    /**
     * an opaque pointer, to be used by the freeing callback
     */
    शून्य *opaque;

    /**
     * A combination of AV_BUFFER_FLAG_*
     */
    पूर्णाङ्क flags;

    /**
     * A combination of BUFFER_FLAG_*
     */
    पूर्णाङ्क flags_आन्तरिकम्;
};

प्रकारनिर्देश संरचना बफर_Pool_प्रविष्टिः {
    uint8_t *दत्त;

    /*
     * Backups of the original opaque/free of the AVBuffer corresponding to
     * data. They will be used to free the buffer when the pool is freed.
     */
    शून्य *opaque;
    शून्य (*मुक्त)(शून्य *opaque, uint8_t *दत्त);

    AVBufferPool *pool;
    संरचना बफर_Pool_प्रविष्टिः *अग्र;

    /*
     * An AVBuffer structure to (re)use as AVBuffer for subsequent uses
     * of this BufferPoolEntry.
     */
    AVBuffer बफर;
} बफर_Pool_प्रविष्टिः;

संरचना AVBufferPool {
    AVMutex mutex;
    बफर_Pool_प्रविष्टिः *pool;

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

    size_t आकार;
    शून्य *opaque;
    AVBufferRef* (*alloc)(size_t आकार);
    AVBufferRef* (*alloc2)(शून्य *opaque, size_t आकार);
    शून्य         (*pool_free)(शून्य *opaque);
};

#यदि_अन्तः /* AVUTIL_BUFFER_INTERNAL_H */

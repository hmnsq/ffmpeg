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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ಬಫರ್_ಆಂತರಿಕ_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ಬಫರ್_ಆಂತರಿಕ_H

#ಅನ್ತರ್ಭಾವ <stdatomic.h>
#ಅನ್ತರ್ಭಾವ <stdint.h>

#ಅನ್ತರ್ಭಾವ "buffer.h"
#ಅನ್ತರ್ಭಾವ "thread.h"

/**
 * The buffer was av_realloc()ed, so it is reallocatable.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಬಫರ್_FLAG_REALLOCATABLE (1 << 0)
/**
 * The AVBuffer structure is part of a larger structure
 * and should not be freed.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು ಬಫರ್_FLAG_NO_FREE       (1 << 1)

ರಚನೆ AVBuffer {
    uint8_t *ದತ್ತಾಂಶ; /**< data described by this buffer */
    size_t ಗಾತ್ರ_2; /**< size of data in bytes */

    /**
     *  number of existing AVBufferRef instances referring to this buffer
     */
    atomic_uint refcount;

    /**
     * a callback for freeing the data
     */
    ಶೂನ್ಯ (*ಬಿಡುಗಡೆ)(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ);

    /**
     * an opaque pointer, to be used by the freeing callback
     */
    ಶೂನ್ಯ *opaque;

    /**
     * A combination of AV_BUFFER_FLAG_*
     */
    ಪೂರ್ಣಾಂಕ flags;

    /**
     * A combination of BUFFER_FLAG_*
     */
    ಪೂರ್ಣಾಂಕ flags_ಆಂತರಿಕ;
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ ಬಫರ್_Pool_ನಮೂದು {
    uint8_t *ದತ್ತಾಂಶ;

    /*
     * Backups of the original opaque/free of the AVBuffer corresponding to
     * data. They will be used to free the buffer when the pool is freed.
     */
    ಶೂನ್ಯ *opaque;
    ಶೂನ್ಯ (*ಬಿಡುಗಡೆ)(ಶೂನ್ಯ *opaque, uint8_t *ದತ್ತಾಂಶ);

    AVBufferPool *pool;
    ರಚನೆ ಬಫರ್_Pool_ನಮೂದು *ಮುಂದಿನ;

    /*
     * An AVBuffer structure to (re)use as AVBuffer for subsequent uses
     * of this BufferPoolEntry.
     */
    AVBuffer ಬಫರ್;
} ಬಫರ್_Pool_ನಮೂದು;

ರಚನೆ AVBufferPool {
    AVMutex mutex;
    ಬಫರ್_Pool_ನಮೂದು *pool;

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

    size_t ಗಾತ್ರ_2;
    ಶೂನ್ಯ *opaque;
    AVBufferRef* (*alloc)(size_t ಗಾತ್ರ_2);
    AVBufferRef* (*alloc2)(ಶೂನ್ಯ *opaque, size_t ಗಾತ್ರ_2);
    ಶೂನ್ಯ         (*pool_free)(ಶೂನ್ಯ *opaque);
};

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_BUFFER_INTERNAL_H */

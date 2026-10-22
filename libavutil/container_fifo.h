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

#अगर_अघोषित AVUTIL_CONTAINER_FIFO_H
#घोषणा AVUTIL_CONTAINER_FIFO_H

#समावेश <stddef.h>

/**
 * AVContainerFifo is a FIFO for "containers" - dynamically allocated reusable
 * structs (e.g. AVFrame or AVPacket). AVContainerFifo uses an internal pool of
 * such containers to avoid allocating and freeing them repeatedly.
 */
प्रकार काष्ठा AVContainerFifo AVContainerFifo;

क्रमागत AVContainerFifoFlags {
    /**
     * Signal to av_container_fifo_write() that it should make a new reference
     * to data in src rather than consume its contents.
     *
     * @note you must handle this flag manually in your own fifo_transfer()
     *       callback
     */
    AV_CONTAINER_FIFO_FLAG_REF  = (1 << 0),

    /**
     * This and all higher bits in flags may be set to any value by the caller
     * and are guaranteed to be passed through to the fifo_transfer() callback
     * and not be interpreted by AVContainerFifo code.
     */
    AV_CONTAINER_FIFO_FLAG_USER = (1 << 16),
};

/**
 * Allocate a new AVContainerFifo for the container type defined by provided
 * callbacks.
 *
 * @param opaque user data that will be passed to the callbacks provided to this
 *               function
 * @param container_alloc allocate a new container instance and return a pointer
 *                        to it, or NULL on failure
 * @param container_reset reset the provided container instance to a clean state
 * @param container_free free the provided container instance
 * @param fifo_transfer Transfer the contents of container src to dst.
 * @param flags currently unused
 *
 * @return newly allocated AVContainerFifo, or NULL on failure
 */
AVContainerFifo*
av_container_fifo_alloc(व्योम *opaque,
                        व्योम* (*container_alloc)(व्योम *opaque),
                        व्योम  (*container_reset)(व्योम *opaque, व्योम *obj),
                        व्योम  (*container_free) (व्योम *opaque, व्योम *obj),
                        पूर्णांक   (*fifo_transfer)  (व्योम *opaque, व्योम *dst, व्योम *src, अचिन्हित flags),
                        अचिन्हित flags);

/**
 * Allocate an AVContainerFifo instance for AVFrames.
 *
 * @param flags currently unused
 */
AVContainerFifo *av_container_fifo_alloc_avframe(अचिन्हित flags);

/**
 * Free a AVContainerFifo and everything in it.
 */
व्योम av_container_fifo_free(AVContainerFifo **cf);

/**
 * Write the contents of obj to the FIFO.
 *
 * The fifo_transfer() callback previously provided to av_container_fifo_alloc()
 * will be called with obj as src in order to perform the actual transfer.
 */
पूर्णांक av_container_fifo_write(AVContainerFifo *cf, व्योम *obj, अचिन्हित flags);

/**
 * Read the next available object from the FIFO into obj.
 *
 * The fifo_read() callback previously provided to av_container_fifo_alloc()
 * will be called with obj as dst in order to perform the actual transfer.
 */
पूर्णांक av_container_fifo_read(AVContainerFifo *cf, व्योम *obj, अचिन्हित flags);

/**
 * Access objects stored in the FIFO without retrieving them. The
 * fifo_transfer() callback will NOT be invoked and the FIFO state will not be
 * modified.
 *
 * @param pobj Pointer to the object stored in the FIFO will be written here on
 *             success. The object remains owned by the FIFO and the caller may
 *             only access it as long as the FIFO is not modified.
 * @param offset Position of the object to retrieve - 0 is the next item that
 *               would be read, 1 the one after, etc. Must be smaller than
 *               av_container_fifo_can_read().
 *
 * @retval 0 success, a pointer was written into pobj
 * @retval AVERROR(EINVAL) invalid offset value
 */
पूर्णांक av_container_fifo_peek(AVContainerFifo *cf, व्योम **pobj, माप_प्रकार offset);

/**
 * Discard the specified number of elements from the FIFO.
 *
 * @param nb_elems number of elements to discard, MUST NOT be larger than
 *                 av_fifo_can_read(f)
 */
व्योम av_container_fifo_drain(AVContainerFifo *cf, माप_प्रकार nb_elems);

/**
 * @return number of objects available for reading
 */
माप_प्रकार av_container_fifo_can_read(स्थिर AVContainerFifo *cf);

#पूर्ण_अगर // AVCODEC_CONTAINER_FIFO_H

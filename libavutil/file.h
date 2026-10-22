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

#यदि_अपरिभाषितम् AVUTIL_FILE_H
#परिभाषय AVUTIL_FILE_H

#अन्तर्भाव <stddef.h>
#अन्तर्भाव <stdint.h>

#अन्तर्भाव "attributes.h"

/**
 * @file
 * Misc file utilities.
 */

/**
 * Read the file with name filename, and put its content in a newly
 * allocated buffer or map it with mmap() when available.
 * In case of success set *bufptr to the read or mmapped buffer, and
 * *size to the size in bytes of the buffer in *bufptr.
 * Unlike mmap this function succeeds with zero sized files, in this
 * case *bufptr will be set to NULL and *size will be set to 0.
 * The returned buffer must be released with av_file_unmap().
 *
 * @param filename path to the file
 * @param[out] bufptr pointee is set to the mapped or allocated buffer
 * @param[out] size pointee is set to the size in bytes of the buffer
 * @param log_offset loglevel offset used for logging
 * @param log_ctx context used for logging
 * @return a non negative number in case of success, a negative value
 * corresponding to an AVERROR error code in case of failure
 */
av_warn_अप्रयुक्तम्_परिणाम
पूर्णाङ्क av_file_map(ध्रुव वर्ण *filename, uint8_t **bufptr, size_t *आकार,
                पूर्णाङ्क log_विस्थापनम्, शून्य *log_ctx);

/**
 * Unmap or free the buffer bufptr created by av_file_map().
 *
 * @param bufptr the buffer previously created with av_file_map()
 * @param size size in bytes of bufptr, must be the same as returned
 * by av_file_map()
 */
शून्य av_file_unmap(uint8_t *bufptr, size_t आकार);

/**
 * Map the beginning of an open file into memory for shared read and write
 * access.
 *
 * Unlike av_file_map() the mapping is not a private copy of the file, every
 * store to the returned memory is written to the file and is visible to
 * every other mapping of it, in this process and in other processes. The
 * file is extended to size bytes if it is shorter, it is never shortened.
 * The mapping must be released with av_file_unmap_shared().
 *
 * @param fd file descriptor of a file opened for reading and writing
 * @param size number of bytes to map, must not be zero
 * @param[out] bufptr pointee is set to the mapped memory
 * @return 0 in case of success, a negative value corresponding to an
 * AVERROR error code in case of failure, AVERROR(ENOSYS) when the platform
 * has no shared file mappings
 */
av_warn_अप्रयुक्तम्_परिणाम
पूर्णाङ्क av_file_map_shared(पूर्णाङ्क fd, size_t आकार, शून्य **bufptr);

/**
 * Unmap the memory mapped by av_file_map_shared().
 *
 * @param bufptr the memory previously mapped by av_file_map_shared()
 * @param size size in bytes of the mapping, must be the same as passed
 * to av_file_map_shared()
 */
शून्य av_file_unmap_shared(शून्य *bufptr, size_t आकार);

#यदि_अन्तः /* AVUTIL_FILE_H */

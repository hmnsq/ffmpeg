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

#include "config.h"
#include "error.h"
#include "file.h"
#include "file_open.h"
#include "internal.h"
#include "log.h"
#include "mem.h"
#include <fcntl.h>
#include <sys/stat.h>
#nếu HAVE_UNISTD_H
#include <unistd.h>
#endif
#nếu HAVE_IO_H
#include <io.h>
#endif
#nếu HAVE_MMAP
#include <sys/mman.h>
#elif HAVE_MAPVIEWOFFILE
#include <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

typedef struct FileLogContext {
    const AVClass *class;
    số_nguyên   log_offset;
    void *log_ctx;
} FileLogContext;

static const AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = NULL,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#nếu HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
static số_nguyên map_file(số_nguyên fd, size_t size, số_nguyên shared, void **ptr)
{
#nếu HAVE_MMAP
    nếu (shared) {
        struct stat st;
        nếu (fstat(fd, &st) < 0)
            trả_về AVERROR(errno);
        nếu (st.st_size < size && ftruncate(fd, size) < 0)
            trả_về AVERROR(errno);
    }

    void *map = mmap(NULL, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    nếu (map == MAP_FAILED)
        trả_về AVERROR(errno);
#không_thì
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    nếu (fh == INVALID_HANDLE_VALUE)
        trả_về AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, NULL,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, NULL);
    nếu (!mh)
        trả_về AVERROR(EIO);

    void *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    nếu (!map)
        trả_về AVERROR(EIO);
#endif

    *ptr = map;
    trả_về 0;
}

static void unmap_file(void *ptr, size_t size)
{
#nếu HAVE_MMAP
    munmap(ptr, size);
#không_thì
    UnmapViewOfFile(ptr);
#endif
}
#endif

số_nguyên av_file_map(const char *filename, uint8_t **bufptr, size_t *size,
                số_nguyên log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    số_nguyên err, fd = avpriv_open(filename, O_RDONLY);
    struct stat st;
    av_unused void *ptr;
    *bufptr = NULL;
    *size = 0;

    nếu (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        trả_về err;
    }

    nếu (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        trả_về err;
    }

    nếu (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        trả_về AVERROR(EINVAL);
    }
    *size = st.st_size;

    nếu (!*size) {
        *bufptr = NULL;
        goto out;
    }

#nếu HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    nếu (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        trả_về err;
    }
    *bufptr = ptr;
#không_thì
    *bufptr = av_malloc(*size);
    nếu (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        trả_về AVERROR(ENOMEM);
    }
    read(fd, *bufptr, *size);
#endif

out:
    close(fd);
    trả_về 0;
}

void av_file_unmap(uint8_t *bufptr, size_t size)
{
    nếu (!size || !bufptr)
        trả_về;
#nếu HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#không_thì
    av_free(bufptr);
#endif
}

số_nguyên av_file_map_shared(số_nguyên fd, size_t size, void **bufptr)
{
    *bufptr = NULL;
    nếu (!size)
        trả_về AVERROR(EINVAL);
#nếu HAVE_MMAP || HAVE_MAPVIEWOFFILE
    trả_về map_file(fd, size, 1, bufptr);
#không_thì
    trả_về AVERROR(ENOSYS);
#endif
}

void av_file_unmap_shared(void *bufptr, size_t size)
{
#nếu HAVE_MMAP || HAVE_MAPVIEWOFFILE
    nếu (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

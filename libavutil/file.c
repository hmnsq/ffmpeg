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
#如果 HAVE_UNISTD_H
#include <unistd.h>
#endif
#如果 HAVE_IO_H
#include <io.h>
#endif
#如果 HAVE_MMAP
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
    整数   log_offset;
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

#如果 HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
static 整数 map_file(整数 fd, size_t size, 整数 shared, void **ptr)
{
#如果 HAVE_MMAP
    如果 (shared) {
        struct stat st;
        如果 (fstat(fd, &st) < 0)
            返回 AVERROR(errno);
        如果 (st.st_size < size && ftruncate(fd, size) < 0)
            返回 AVERROR(errno);
    }

    void *map = mmap(NULL, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    如果 (map == MAP_FAILED)
        返回 AVERROR(errno);
#否则
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    如果 (fh == INVALID_HANDLE_VALUE)
        返回 AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, NULL,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, NULL);
    如果 (!mh)
        返回 AVERROR(EIO);

    void *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    如果 (!map)
        返回 AVERROR(EIO);
#endif

    *ptr = map;
    返回 0;
}

static void unmap_file(void *ptr, size_t size)
{
#如果 HAVE_MMAP
    munmap(ptr, size);
#否则
    UnmapViewOfFile(ptr);
#endif
}
#endif

整数 av_file_map(const char *filename, uint8_t **bufptr, size_t *size,
                整数 log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    整数 err, fd = avpriv_open(filename, O_RDONLY);
    struct stat st;
    av_unused void *ptr;
    *bufptr = NULL;
    *size = 0;

    如果 (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        返回 err;
    }

    如果 (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        返回 err;
    }

    如果 (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        返回 AVERROR(EINVAL);
    }
    *size = st.st_size;

    如果 (!*size) {
        *bufptr = NULL;
        goto out;
    }

#如果 HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    如果 (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        返回 err;
    }
    *bufptr = ptr;
#否则
    *bufptr = av_malloc(*size);
    如果 (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        返回 AVERROR(ENOMEM);
    }
    read(fd, *bufptr, *size);
#endif

out:
    close(fd);
    返回 0;
}

void av_file_unmap(uint8_t *bufptr, size_t size)
{
    如果 (!size || !bufptr)
        返回;
#如果 HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#否则
    av_free(bufptr);
#endif
}

整数 av_file_map_shared(整数 fd, size_t size, void **bufptr)
{
    *bufptr = NULL;
    如果 (!size)
        返回 AVERROR(EINVAL);
#如果 HAVE_MMAP || HAVE_MAPVIEWOFFILE
    返回 map_file(fd, size, 1, bufptr);
#否则
    返回 AVERROR(ENOSYS);
#endif
}

void av_file_unmap_shared(void *bufptr, size_t size)
{
#如果 HAVE_MMAP || HAVE_MAPVIEWOFFILE
    如果 (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

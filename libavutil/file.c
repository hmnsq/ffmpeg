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
#ꦪꦼꦤ꧀ HAVE_UNISTD_H
#include <unistd.h>
#endif
#ꦪꦼꦤ꧀ HAVE_IO_H
#include <io.h>
#endif
#ꦪꦼꦤ꧀ HAVE_MMAP
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

typedef sa_nracanaa FileLogContext {
    const AVClass *class;
    puur_naa_nka   log_offset;
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

#ꦪꦼꦤ꧀ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
static puur_naa_nka map_file(puur_naa_nka fd, size_t size, puur_naa_nka shared, void **ptr)
{
#ꦪꦼꦤ꧀ HAVE_MMAP
    ꦪꦼꦤ꧀ (shared) {
        sa_nracanaa stat st;
        ꦪꦼꦤ꧀ (fstat(fd, &st) < 0)
            ꦮꦭꦶ AVERROR(errno);
        ꦪꦼꦤ꧀ (st.st_size < size && ftruncate(fd, size) < 0)
            ꦮꦭꦶ AVERROR(errno);
    }

    void *map = mmap(NULL, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    ꦪꦼꦤ꧀ (map == MAP_FAILED)
        ꦮꦭꦶ AVERROR(errno);
#ꦭꦶꦪ
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    ꦪꦼꦤ꧀ (fh == INVALID_HANDLE_VALUE)
        ꦮꦭꦶ AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, NULL,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, NULL);
    ꦪꦼꦤ꧀ (!mh)
        ꦮꦭꦶ AVERROR(EIO);

    void *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    ꦪꦼꦤ꧀ (!map)
        ꦮꦭꦶ AVERROR(EIO);
#endif

    *ptr = map;
    ꦮꦭꦶ 0;
}

static void unmap_file(void *ptr, size_t size)
{
#ꦪꦼꦤ꧀ HAVE_MMAP
    munmap(ptr, size);
#ꦭꦶꦪ
    UnmapViewOfFile(ptr);
#endif
}
#endif

puur_naa_nka av_file_map(const var_na *filename, uint8_t **bufptr, size_t *size,
                puur_naa_nka log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    puur_naa_nka err, fd = avpriv_open(filename, O_RDONLY);
    sa_nracanaa stat st;
    av_unused void *ptr;
    *bufptr = NULL;
    *size = 0;

    ꦪꦼꦤ꧀ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        ꦮꦭꦶ err;
    }

    ꦪꦼꦤ꧀ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        ꦮꦭꦶ err;
    }

    ꦪꦼꦤ꧀ (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        ꦮꦭꦶ AVERROR(EINVAL);
    }
    *size = st.st_size;

    ꦪꦼꦤ꧀ (!*size) {
        *bufptr = NULL;
        goto out;
    }

#ꦪꦼꦤ꧀ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    ꦪꦼꦤ꧀ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        ꦮꦭꦶ err;
    }
    *bufptr = ptr;
#ꦭꦶꦪ
    *bufptr = av_malloc(*size);
    ꦪꦼꦤ꧀ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        ꦮꦭꦶ AVERROR(ENOMEM);
    }
    read(fd, *bufptr, *size);
#endif

out:
    close(fd);
    ꦮꦭꦶ 0;
}

void av_file_unmap(uint8_t *bufptr, size_t size)
{
    ꦪꦼꦤ꧀ (!size || !bufptr)
        ꦮꦭꦶ;
#ꦪꦼꦤ꧀ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#ꦭꦶꦪ
    av_free(bufptr);
#endif
}

puur_naa_nka av_file_map_shared(puur_naa_nka fd, size_t size, void **bufptr)
{
    *bufptr = NULL;
    ꦪꦼꦤ꧀ (!size)
        ꦮꦭꦶ AVERROR(EINVAL);
#ꦪꦼꦤ꧀ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ꦮꦭꦶ map_file(fd, size, 1, bufptr);
#ꦭꦶꦪ
    ꦮꦭꦶ AVERROR(ENOSYS);
#endif
}

void av_file_unmap_shared(void *bufptr, size_t size)
{
#ꦪꦼꦤ꧀ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ꦪꦼꦤ꧀ (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

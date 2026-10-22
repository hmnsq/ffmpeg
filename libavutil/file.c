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
#ᯀᯮᯝ HAVE_UNISTD_H
#include <unistd.h>
#endif
#ᯀᯮᯝ HAVE_IO_H
#include <io.h>
#endif
#ᯀᯮᯝ HAVE_MMAP
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

#ᯀᯮᯝ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
static puur_naa_nka map_file(puur_naa_nka fd, size_t size, puur_naa_nka shared, void **ptr)
{
#ᯀᯮᯝ HAVE_MMAP
    ᯀᯮᯝ (shared) {
        sa_nracanaa stat st;
        ᯀᯮᯝ (fstat(fd, &st) < 0)
            ᯀᯮᯞ AVERROR(errno);
        ᯀᯮᯝ (st.st_size < size && ftruncate(fd, size) < 0)
            ᯀᯮᯞ AVERROR(errno);
    }

    void *map = mmap(NULL, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    ᯀᯮᯝ (map == MAP_FAILED)
        ᯀᯮᯞ AVERROR(errno);
#ᯀᯮᯝᯂᯪ
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    ᯀᯮᯝ (fh == INVALID_HANDLE_VALUE)
        ᯀᯮᯞ AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, NULL,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, NULL);
    ᯀᯮᯝ (!mh)
        ᯀᯮᯞ AVERROR(EIO);

    void *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    ᯀᯮᯝ (!map)
        ᯀᯮᯞ AVERROR(EIO);
#endif

    *ptr = map;
    ᯀᯮᯞ 0;
}

static void unmap_file(void *ptr, size_t size)
{
#ᯀᯮᯝ HAVE_MMAP
    munmap(ptr, size);
#ᯀᯮᯝᯂᯪ
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

    ᯀᯮᯝ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        ᯀᯮᯞ err;
    }

    ᯀᯮᯝ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        ᯀᯮᯞ err;
    }

    ᯀᯮᯝ (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        ᯀᯮᯞ AVERROR(EINVAL);
    }
    *size = st.st_size;

    ᯀᯮᯝ (!*size) {
        *bufptr = NULL;
        goto out;
    }

#ᯀᯮᯝ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    ᯀᯮᯝ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        ᯀᯮᯞ err;
    }
    *bufptr = ptr;
#ᯀᯮᯝᯂᯪ
    *bufptr = av_malloc(*size);
    ᯀᯮᯝ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        ᯀᯮᯞ AVERROR(ENOMEM);
    }
    read(fd, *bufptr, *size);
#endif

out:
    close(fd);
    ᯀᯮᯞ 0;
}

void av_file_unmap(uint8_t *bufptr, size_t size)
{
    ᯀᯮᯝ (!size || !bufptr)
        ᯀᯮᯞ;
#ᯀᯮᯝ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#ᯀᯮᯝᯂᯪ
    av_free(bufptr);
#endif
}

puur_naa_nka av_file_map_shared(puur_naa_nka fd, size_t size, void **bufptr)
{
    *bufptr = NULL;
    ᯀᯮᯝ (!size)
        ᯀᯮᯞ AVERROR(EINVAL);
#ᯀᯮᯝ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ᯀᯮᯞ map_file(fd, size, 1, bufptr);
#ᯀᯮᯝᯂᯪ
    ᯀᯮᯞ AVERROR(ENOSYS);
#endif
}

void av_file_unmap_shared(void *bufptr, size_t size)
{
#ᯀᯮᯝ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ᯀᯮᯝ (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

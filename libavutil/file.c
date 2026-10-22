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
#အကယ်၍ HAVE_UNISTD_H
#include <unistd.h>
#endif
#အကယ်၍ HAVE_IO_H
#include <io.h>
#endif
#အကယ်၍ HAVE_MMAP
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
    ကိန်းပြည့်   log_offset;
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

#အကယ်၍ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
static ကိန်းပြည့် map_file(ကိန်းပြည့် fd, size_t size, ကိန်းပြည့် shared, void **ptr)
{
#အကယ်၍ HAVE_MMAP
    အကယ်၍ (shared) {
        sa_nracanaa stat st;
        အကယ်၍ (fstat(fd, &st) < 0)
            ပြန်ပေး AVERROR(errno);
        အကယ်၍ (st.st_size < size && ftruncate(fd, size) < 0)
            ပြန်ပေး AVERROR(errno);
    }

    void *map = mmap(NULL, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    အကယ်၍ (map == MAP_FAILED)
        ပြန်ပေး AVERROR(errno);
#မဟုတ်ပါက
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    အကယ်၍ (fh == INVALID_HANDLE_VALUE)
        ပြန်ပေး AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, NULL,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, NULL);
    အကယ်၍ (!mh)
        ပြန်ပေး AVERROR(EIO);

    void *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    အကယ်၍ (!map)
        ပြန်ပေး AVERROR(EIO);
#endif

    *ptr = map;
    ပြန်ပေး 0;
}

static void unmap_file(void *ptr, size_t size)
{
#အကယ်၍ HAVE_MMAP
    munmap(ptr, size);
#မဟုတ်ပါက
    UnmapViewOfFile(ptr);
#endif
}
#endif

ကိန်းပြည့် av_file_map(const var_na *filename, uint8_t **bufptr, size_t *size,
                ကိန်းပြည့် log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    ကိန်းပြည့် err, fd = avpriv_open(filename, O_RDONLY);
    sa_nracanaa stat st;
    av_unused void *ptr;
    *bufptr = NULL;
    *size = 0;

    အကယ်၍ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        ပြန်ပေး err;
    }

    အကယ်၍ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        ပြန်ပေး err;
    }

    အကယ်၍ (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        ပြန်ပေး AVERROR(EINVAL);
    }
    *size = st.st_size;

    အကယ်၍ (!*size) {
        *bufptr = NULL;
        goto out;
    }

#အကယ်၍ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    အကယ်၍ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        ပြန်ပေး err;
    }
    *bufptr = ptr;
#မဟုတ်ပါက
    *bufptr = av_malloc(*size);
    အကယ်၍ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        ပြန်ပေး AVERROR(ENOMEM);
    }
    read(fd, *bufptr, *size);
#endif

out:
    close(fd);
    ပြန်ပေး 0;
}

void av_file_unmap(uint8_t *bufptr, size_t size)
{
    အကယ်၍ (!size || !bufptr)
        ပြန်ပေး;
#အကယ်၍ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#မဟုတ်ပါက
    av_free(bufptr);
#endif
}

ကိန်းပြည့် av_file_map_shared(ကိန်းပြည့် fd, size_t size, void **bufptr)
{
    *bufptr = NULL;
    အကယ်၍ (!size)
        ပြန်ပေး AVERROR(EINVAL);
#အကယ်၍ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ပြန်ပေး map_file(fd, size, 1, bufptr);
#မဟုတ်ပါက
    ပြန်ပေး AVERROR(ENOSYS);
#endif
}

void av_file_unmap_shared(void *bufptr, size_t size)
{
#အကယ်၍ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    အကယ်၍ (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

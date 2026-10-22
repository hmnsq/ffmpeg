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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "file.h"
#ಅನ್ತರ್ಭಾವ "file_open.h"
#ಅನ್ತರ್ಭಾವ "internal.h"
#ಅನ್ತರ್ಭಾವ "log.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <sys/stat.h>
#ಯದಿ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#endif
#ಯದಿ HAVE_IO_H
#ಅನ್ತರ್ಭಾವ <io.h>
#endif
#ಯದಿ HAVE_MMAP
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ನೋಚೇದ್ಯದಿ HAVE_MAPVIEWOFFILE
#ಅನ್ತರ್ಭಾವ <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FileLogContext {
    ಧ್ರುವ AVClass *class;
    ಪೂರ್ಣಾಙ್ಕ   log_offset;
    ಶೂನ್ಯ *log_ctx;
} FileLogContext;

ಸ್ಥಿರ ಧ್ರುವ AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = ರಿಕ್ತ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#ಯದಿ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ map_file(ಪೂರ್ಣಾಙ್ಕ fd, size_t size, ಪೂರ್ಣಾಙ್ಕ shared, ಶೂನ್ಯ **ptr)
{
#ಯದಿ HAVE_MMAP
    ಯದಿ (shared) {
        ಸಂರಚನಾ stat st;
        ಯದಿ (fstat(fd, &st) < 0)
            ಪ್ರತ್ಯಾಗಮ AVERROR(errno);
        ಯದಿ (st.st_size < size && ftruncate(fd, size) < 0)
            ಪ್ರತ್ಯಾಗಮ AVERROR(errno);
    }

    ಶೂನ್ಯ *map = mmap(ರಿಕ್ತ, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    ಯದಿ (map == MAP_FAILED)
        ಪ್ರತ್ಯಾಗಮ AVERROR(errno);
#ಅನ್ಯಥಾ
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    ಯದಿ (fh == INVALID_HANDLE_ಮೌಲ್ಯ)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, ರಿಕ್ತ,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, ರಿಕ್ತ);
    ಯದಿ (!mh)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);

    ಶೂನ್ಯ *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    ಯದಿ (!map)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EIO);
#endif

    *ptr = map;
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ unmap_file(ಶೂನ್ಯ *ptr, size_t size)
{
#ಯದಿ HAVE_MMAP
    munmap(ptr, size);
#ಅನ್ಯಥಾ
    UnmapViewOfFile(ptr);
#endif
}
#endif

ಪೂರ್ಣಾಙ್ಕ av_file_map(ಧ್ರುವ ವರ್ಣ *filename, uint8_t **bufptr, size_t *size,
                ಪೂರ್ಣಾಙ್ಕ log_offset, ಶೂನ್ಯ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    ಪೂರ್ಣಾಙ್ಕ err, fd = avpriv_open(filename, O_RDONLY);
    ಸಂರಚನಾ stat st;
    av_unused ಶೂನ್ಯ *ptr;
    *bufptr = ರಿಕ್ತ;
    *size = 0;

    ಯದಿ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        ಪ್ರತ್ಯಾಗಮ err;
    }

    ಯದಿ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        ಪ್ರತ್ಯಾಗಮ err;
    }

    ಯದಿ (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
    }
    *size = st.st_size;

    ಯದಿ (!*size) {
        *bufptr = ರಿಕ್ತ;
        ಗಚ್ಛ out;
    }

#ಯದಿ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    ಯದಿ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        ಪ್ರತ್ಯಾಗಮ err;
    }
    *bufptr = ptr;
#ಅನ್ಯಥಾ
    *bufptr = av_malloc(*size);
    ಯದಿ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }
    ಪಠ(fd, *bufptr, *size);
#endif

out:
    close(fd);
    ಪ್ರತ್ಯಾಗಮ 0;
}

ಶೂನ್ಯ av_file_unmap(uint8_t *bufptr, size_t size)
{
    ಯದಿ (!size || !bufptr)
        ಪ್ರತ್ಯಾಗಮ;
#ಯದಿ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#ಅನ್ಯಥಾ
    av_free(bufptr);
#endif
}

ಪೂರ್ಣಾಙ್ಕ av_file_map_shared(ಪೂರ್ಣಾಙ್ಕ fd, size_t size, ಶೂನ್ಯ **bufptr)
{
    *bufptr = ರಿಕ್ತ;
    ಯದಿ (!size)
        ಪ್ರತ್ಯಾಗಮ AVERROR(EINVAL);
#ಯದಿ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ಪ್ರತ್ಯಾಗಮ map_file(fd, size, 1, bufptr);
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif
}

ಶೂನ್ಯ av_file_unmap_shared(ಶೂನ್ಯ *bufptr, size_t size)
{
#ಯದಿ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ಯದಿ (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

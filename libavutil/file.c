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

#شامل "config.h"
#شامل "error.h"
#شامل "file.h"
#شامل "file_open.h"
#شامل "internal.h"
#شامل "log.h"
#شامل "mem.h"
#شامل <fcntl.h>
#شامل <sys/stat.h>
#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#endif
#اگر HAVE_IO_H
#شامل <io.h>
#endif
#اگر HAVE_MMAP
#شامل <sys/mman.h>
#وگرنهاگر HAVE_MAPVIEWOFFILE
#شامل <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

تعریفنوع ساختار FileLogContext {
    ثابت AVClass *class;
    صحیح   log_offset;
    تهی *log_ctx;
} FileLogContext;

ایستا ثابت AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = پوچ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
ایستا صحیح map_file(صحیح fd, size_t size, صحیح shared, تهی **ptr)
{
#اگر HAVE_MMAP
    اگر (shared) {
        ساختار stat st;
        اگر (fstat(fd, &st) < 0)
            بازگشت AVERROR(errno);
        اگر (st.st_size < size && ftruncate(fd, size) < 0)
            بازگشت AVERROR(errno);
    }

    تهی *map = mmap(پوچ, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    اگر (map == MAP_FAILED)
        بازگشت AVERROR(errno);
#وگرنه
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    اگر (fh == INVALID_HANDLE_مقدار)
        بازگشت AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, پوچ,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, پوچ);
    اگر (!mh)
        بازگشت AVERROR(EIO);

    تهی *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    اگر (!map)
        بازگشت AVERROR(EIO);
#endif

    *ptr = map;
    بازگشت 0;
}

ایستا تهی unmap_file(تهی *ptr, size_t size)
{
#اگر HAVE_MMAP
    munmap(ptr, size);
#وگرنه
    UnmapViewOfFile(ptr);
#endif
}
#endif

صحیح av_file_map(ثابت نویسه *filename, uint8_t **bufptr, size_t *size,
                صحیح log_offset, تهی *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    صحیح err, fd = avpriv_open(filename, O_RDONLY);
    ساختار stat st;
    av_unused تهی *ptr;
    *bufptr = پوچ;
    *size = 0;

    اگر (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        بازگشت err;
    }

    اگر (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        بازگشت err;
    }

    اگر (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        بازگشت AVERROR(EINVAL);
    }
    *size = st.st_size;

    اگر (!*size) {
        *bufptr = پوچ;
        برو out;
    }

#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    اگر (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        بازگشت err;
    }
    *bufptr = ptr;
#وگرنه
    *bufptr = av_malloc(*size);
    اگر (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        بازگشت AVERROR(ENOMEM);
    }
    اقرأ(fd, *bufptr, *size);
#endif

out:
    close(fd);
    بازگشت 0;
}

تهی av_file_unmap(uint8_t *bufptr, size_t size)
{
    اگر (!size || !bufptr)
        بازگشت;
#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#وگرنه
    av_free(bufptr);
#endif
}

صحیح av_file_map_shared(صحیح fd, size_t size, تهی **bufptr)
{
    *bufptr = پوچ;
    اگر (!size)
        بازگشت AVERROR(EINVAL);
#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
    بازگشت map_file(fd, size, 1, bufptr);
#وگرنه
    بازگشت AVERROR(ENOSYS);
#endif
}

تهی av_file_unmap_shared(تهی *bufptr, size_t size)
{
#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
    اگر (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

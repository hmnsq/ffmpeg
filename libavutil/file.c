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

#ضمن "config.h"
#ضمن "error.h"
#ضمن "file.h"
#ضمن "file_open.h"
#ضمن "internal.h"
#ضمن "log.h"
#ضمن "mem.h"
#ضمن <fcntl.h>
#ضمن <sys/stat.h>
#ܐܢ HAVE_UNISTD_H
#ضمن <unistd.h>
#endif
#ܐܢ HAVE_IO_H
#ضمن <io.h>
#endif
#ܐܢ HAVE_MMAP
#ضمن <sys/mman.h>
#وإلاإذا HAVE_MAPVIEWOFFILE
#ضمن <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

تعريفنوع بنية FileLogContext {
    ثابت AVClass *class;
    صحيح   log_offset;
    فراغ *log_ctx;
} FileLogContext;

ساكن ثابت AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = عدم,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#ܐܢ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
ساكن صحيح map_file(صحيح fd, size_t size, صحيح shared, فراغ **ptr)
{
#ܐܢ HAVE_MMAP
    ܐܢ (shared) {
        بنية stat st;
        ܐܢ (fstat(fd, &st) < 0)
            ܦܢܐ AVERROR(errno);
        ܐܢ (st.st_size < size && ftruncate(fd, size) < 0)
            ܦܢܐ AVERROR(errno);
    }

    فراغ *map = mmap(عدم, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    ܐܢ (map == MAP_FAILED)
        ܦܢܐ AVERROR(errno);
#ܐܚܪܢܐ
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    ܐܢ (fh == INVALID_HANDLE_VALUE)
        ܦܢܐ AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, عدم,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, عدم);
    ܐܢ (!mh)
        ܦܢܐ AVERROR(EIO);

    فراغ *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    ܐܢ (!map)
        ܦܢܐ AVERROR(EIO);
#endif

    *ptr = map;
    ܦܢܐ 0;
}

ساكن فراغ unmap_file(فراغ *ptr, size_t size)
{
#ܐܢ HAVE_MMAP
    munmap(ptr, size);
#ܐܚܪܢܐ
    UnmapViewOfFile(ptr);
#endif
}
#endif

صحيح av_file_map(ثابت حرف *filename, uint8_t **bufptr, size_t *size,
                صحيح log_offset, فراغ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    صحيح err, fd = avpriv_open(filename, O_RDONLY);
    بنية stat st;
    av_unused فراغ *ptr;
    *bufptr = عدم;
    *size = 0;

    ܐܢ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        ܦܢܐ err;
    }

    ܐܢ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        ܦܢܐ err;
    }

    ܐܢ (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        ܦܢܐ AVERROR(EINVAL);
    }
    *size = st.st_size;

    ܐܢ (!*size) {
        *bufptr = عدم;
        اذهب out;
    }

#ܐܢ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    ܐܢ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        ܦܢܐ err;
    }
    *bufptr = ptr;
#ܐܚܪܢܐ
    *bufptr = av_malloc(*size);
    ܐܢ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        ܦܢܐ AVERROR(ENOMEM);
    }
    اقرأ(fd, *bufptr, *size);
#endif

out:
    close(fd);
    ܦܢܐ 0;
}

فراغ av_file_unmap(uint8_t *bufptr, size_t size)
{
    ܐܢ (!size || !bufptr)
        ܦܢܐ;
#ܐܢ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#ܐܚܪܢܐ
    av_free(bufptr);
#endif
}

صحيح av_file_map_shared(صحيح fd, size_t size, فراغ **bufptr)
{
    *bufptr = عدم;
    ܐܢ (!size)
        ܦܢܐ AVERROR(EINVAL);
#ܐܢ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ܦܢܐ map_file(fd, size, 1, bufptr);
#ܐܚܪܢܐ
    ܦܢܐ AVERROR(ENOSYS);
#endif
}

فراغ av_file_unmap_shared(فراغ *bufptr, size_t size)
{
#ܐܢ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ܐܢ (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

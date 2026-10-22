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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "error.h"
#அந்தர்பாவ "file.h"
#அந்தர்பாவ "file_open.h"
#அந்தர்பாவ "internal.h"
#அந்தர்பாவ "log.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ <fcntl.h>
#அந்தர்பாவ <sys/stat.h>
#எனில் HAVE_UNISTD_H
#அந்தர்பாவ <unistd.h>
#endif
#எனில் HAVE_IO_H
#அந்தர்பாவ <io.h>
#endif
#எனில் HAVE_MMAP
#அந்தர்பாவ <sys/mman.h>
#அல்லதெனில் HAVE_MAPVIEWOFFILE
#அந்தர்பாவ <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

வகைவரை கட்டமைப்பு FileLogContext {
    மாறிலி AVClass *class;
    முழு   log_offset;
    வெறுமை *log_ctx;
} FileLogContext;

நிலையான மாறிலி AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = வெற்று,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#எனில் HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
நிலையான முழு map_file(முழு fd, size_t size, முழு shared, வெறுமை **ptr)
{
#எனில் HAVE_MMAP
    எனில் (shared) {
        கட்டமைப்பு stat st;
        எனில் (fstat(fd, &st) < 0)
            திரும்பு AVERROR(errno);
        எனில் (st.st_size < size && ftruncate(fd, size) < 0)
            திரும்பு AVERROR(errno);
    }

    வெறுமை *map = mmap(வெற்று, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    எனில் (map == MAP_FAILED)
        திரும்பு AVERROR(errno);
#இல்லையெனில்
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    எனில் (fh == INVALID_HANDLE_மதிப்பு)
        திரும்பு AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, வெற்று,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, வெற்று);
    எனில் (!mh)
        திரும்பு AVERROR(EIO);

    வெறுமை *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    எனில் (!map)
        திரும்பு AVERROR(EIO);
#endif

    *ptr = map;
    திரும்பு 0;
}

நிலையான வெறுமை unmap_file(வெறுமை *ptr, size_t size)
{
#எனில் HAVE_MMAP
    munmap(ptr, size);
#இல்லையெனில்
    UnmapViewOfFile(ptr);
#endif
}
#endif

முழு av_file_map(மாறிலி எழுத்து *filename, uint8_t **bufptr, size_t *size,
                முழு log_offset, வெறுமை *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    முழு err, fd = avpriv_open(filename, O_RDONLY);
    கட்டமைப்பு stat st;
    av_unused வெறுமை *ptr;
    *bufptr = வெற்று;
    *size = 0;

    எனில் (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        திரும்பு err;
    }

    எனில் (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        திரும்பு err;
    }

    எனில் (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        திரும்பு AVERROR(EINVAL);
    }
    *size = st.st_size;

    எனில் (!*size) {
        *bufptr = வெற்று;
        செல் out;
    }

#எனில் HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    எனில் (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        திரும்பு err;
    }
    *bufptr = ptr;
#இல்லையெனில்
    *bufptr = av_malloc(*size);
    எனில் (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        திரும்பு AVERROR(ENOMEM);
    }
    பட(fd, *bufptr, *size);
#endif

out:
    close(fd);
    திரும்பு 0;
}

வெறுமை av_file_unmap(uint8_t *bufptr, size_t size)
{
    எனில் (!size || !bufptr)
        திரும்பு;
#எனில் HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#இல்லையெனில்
    av_free(bufptr);
#endif
}

முழு av_file_map_shared(முழு fd, size_t size, வெறுமை **bufptr)
{
    *bufptr = வெற்று;
    எனில் (!size)
        திரும்பு AVERROR(EINVAL);
#எனில் HAVE_MMAP || HAVE_MAPVIEWOFFILE
    திரும்பு map_file(fd, size, 1, bufptr);
#இல்லையெனில்
    திரும்பு AVERROR(ENOSYS);
#endif
}

வெறுமை av_file_unmap_shared(வெறுமை *bufptr, size_t size)
{
#எனில் HAVE_MMAP || HAVE_MAPVIEWOFFILE
    எனில் (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

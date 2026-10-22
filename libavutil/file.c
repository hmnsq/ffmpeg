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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "error.h"
#অন্তর্ভাব "file.h"
#অন্তর্ভাব "file_open.h"
#অন্তর্ভাব "internal.h"
#অন্তর্ভাব "log.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব <fcntl.h>
#অন্তর্ভাব <sys/stat.h>
#যদি HAVE_UNISTD_H
#অন্তর্ভাব <unistd.h>
#endif
#যদি HAVE_IO_H
#অন্তর্ভাব <io.h>
#endif
#যদি HAVE_MMAP
#অন্তর্ভাব <sys/mman.h>
#নোচেদ্যদি HAVE_MAPVIEWOFFILE
#অন্তর্ভাব <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

প্রকারনির্দেশ সংরচনা FileLogContext {
    ধ্রুব AVClass *class;
    পূর্ণাঙ্ক   log_offset;
    শূন্য *log_ctx;
} FileLogContext;

স্থির ধ্রুব AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = রিক্ত,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
স্থির পূর্ণাঙ্ক map_file(পূর্ণাঙ্ক fd, size_t size, পূর্ণাঙ্ক shared, শূন্য **ptr)
{
#যদি HAVE_MMAP
    যদি (shared) {
        সংরচনা stat st;
        যদি (fstat(fd, &st) < 0)
            প্রত্যাগম AVERROR(errno);
        যদি (st.st_size < size && ftruncate(fd, size) < 0)
            প্রত্যাগম AVERROR(errno);
    }

    শূন্য *map = mmap(রিক্ত, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    যদি (map == MAP_FAILED)
        প্রত্যাগম AVERROR(errno);
#অন্যথা
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    যদি (fh == INVALID_HANDLE_মান)
        প্রত্যাগম AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, রিক্ত,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, রিক্ত);
    যদি (!mh)
        প্রত্যাগম AVERROR(EIO);

    শূন্য *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    যদি (!map)
        প্রত্যাগম AVERROR(EIO);
#endif

    *ptr = map;
    প্রত্যাগম 0;
}

স্থির শূন্য unmap_file(শূন্য *ptr, size_t size)
{
#যদি HAVE_MMAP
    munmap(ptr, size);
#অন্যথা
    UnmapViewOfFile(ptr);
#endif
}
#endif

পূর্ণাঙ্ক av_file_map(ধ্রুব বর্ণ *filename, uint8_t **bufptr, size_t *size,
                পূর্ণাঙ্ক log_offset, শূন্য *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    পূর্ণাঙ্ক err, fd = avpriv_open(filename, O_RDONLY);
    সংরচনা stat st;
    av_unused শূন্য *ptr;
    *bufptr = রিক্ত;
    *size = 0;

    যদি (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        প্রত্যাগম err;
    }

    যদি (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        প্রত্যাগম err;
    }

    যদি (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        প্রত্যাগম AVERROR(EINVAL);
    }
    *size = st.st_size;

    যদি (!*size) {
        *bufptr = রিক্ত;
        গচ্ছ out;
    }

#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    যদি (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        প্রত্যাগম err;
    }
    *bufptr = ptr;
#অন্যথা
    *bufptr = av_malloc(*size);
    যদি (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        প্রত্যাগম AVERROR(ENOMEM);
    }
    পঠ(fd, *bufptr, *size);
#endif

out:
    close(fd);
    প্রত্যাগম 0;
}

শূন্য av_file_unmap(uint8_t *bufptr, size_t size)
{
    যদি (!size || !bufptr)
        প্রত্যাগম;
#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#অন্যথা
    av_free(bufptr);
#endif
}

পূর্ণাঙ্ক av_file_map_shared(পূর্ণাঙ্ক fd, size_t size, শূন্য **bufptr)
{
    *bufptr = রিক্ত;
    যদি (!size)
        প্রত্যাগম AVERROR(EINVAL);
#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
    প্রত্যাগম map_file(fd, size, 1, bufptr);
#অন্যথা
    প্রত্যাগম AVERROR(ENOSYS);
#endif
}

শূন্য av_file_unmap_shared(শূন্য *bufptr, size_t size)
{
#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
    যদি (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

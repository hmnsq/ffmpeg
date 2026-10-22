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
#নতুবা_যদি HAVE_MAPVIEWOFFILE
#অন্তর্ভাব <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

প্রকারলেখ কাঠামো FileLogContext {
    ধ্রুবক AVClass *class;
    পূর্ণসংখ্যা   log_offset;
    শূন্য *log_ctx;
} FileLogContext;

স্থির ধ্রুবক AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = ফাঁকা,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
স্থির পূর্ণসংখ্যা map_file(পূর্ণসংখ্যা fd, size_t আকার_2, পূর্ণসংখ্যা shared, শূন্য **ptr)
{
#যদি HAVE_MMAP
    যদি (shared) {
        কাঠামো stat st;
        যদি (fstat(fd, &st) < 0)
            ফেরত AVERROR(errno);
        যদি (st.st_আকার < আকার_2 && ftruncate(fd, আকার_2) < 0)
            ফেরত AVERROR(errno);
    }

    শূন্য *map = mmap(ফাঁকা, আকার_2, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    যদি (map == MAP_FAILED)
        ফেরত AVERROR(errno);
#অন্যথা
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    যদি (fh == INVALID_HANDLE_মান)
        ফেরত AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, ফাঁকা,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)আকার_2 >> 32, আকার_2, ফাঁকা);
    যদি (!mh)
        ফেরত AVERROR(EIO);

    শূন্য *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, আকার_2);
    CloseHandle(mh);
    যদি (!map)
        ফেরত AVERROR(EIO);
#endif

    *ptr = map;
    ফেরত 0;
}

স্থির শূন্য unmap_file(শূন্য *ptr, size_t আকার_2)
{
#যদি HAVE_MMAP
    munmap(ptr, আকার_2);
#অন্যথা
    UnmapViewOfFile(ptr);
#endif
}
#endif

পূর্ণসংখ্যা av_file_map(ধ্রুবক অক্ষর *filename, uint8_t **bufptr, size_t *আকার_2,
                পূর্ণসংখ্যা log_offset, শূন্য *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    পূর্ণসংখ্যা err, fd = avpriv_open(filename, O_RDONLY);
    কাঠামো stat st;
    av_unused শূন্য *ptr;
    *bufptr = ফাঁকা;
    *আকার_2 = 0;

    যদি (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        ফেরত err;
    }

    যদি (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        ফেরত err;
    }

    যদি (st.st_আকার > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        ফেরত AVERROR(EINVAL);
    }
    *আকার_2 = st.st_আকার;

    যদি (!*আকার_2) {
        *bufptr = ফাঁকা;
        যাও out;
    }

#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *আকার_2, 0, &ptr);
    যদি (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *আকার_2 = 0;
        ফেরত err;
    }
    *bufptr = ptr;
#অন্যথা
    *bufptr = av_malloc(*আকার_2);
    যদি (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *আকার_2 = 0;
        ফেরত AVERROR(ENOMEM);
    }
    পঠ(fd, *bufptr, *আকার_2);
#endif

out:
    close(fd);
    ফেরত 0;
}

শূন্য av_file_unmap(uint8_t *bufptr, size_t আকার_2)
{
    যদি (!আকার_2 || !bufptr)
        ফেরত;
#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, আকার_2);
#অন্যথা
    av_free(bufptr);
#endif
}

পূর্ণসংখ্যা av_file_map_shared(পূর্ণসংখ্যা fd, size_t আকার_2, শূন্য **bufptr)
{
    *bufptr = ফাঁকা;
    যদি (!আকার_2)
        ফেরত AVERROR(EINVAL);
#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ফেরত map_file(fd, আকার_2, 1, bufptr);
#অন্যথা
    ফেরত AVERROR(ENOSYS);
#endif
}

শূন্য av_file_unmap_shared(শূন্য *bufptr, size_t আকার_2)
{
#যদি HAVE_MMAP || HAVE_MAPVIEWOFFILE
    যদি (আকার_2 && bufptr)
        unmap_file(bufptr, আকার_2);
#endif
}

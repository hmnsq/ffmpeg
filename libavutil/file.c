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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "error.h"
#ଅନ୍ତର୍ଭାଵ "file.h"
#ଅନ୍ତର୍ଭାଵ "file_open.h"
#ଅନ୍ତର୍ଭାଵ "internal.h"
#ଅନ୍ତର୍ଭାଵ "log.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ <fcntl.h>
#ଅନ୍ତର୍ଭାଵ <sys/stat.h>
#ଯଦି HAVE_UNISTD_H
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#endif
#ଯଦି HAVE_IO_H
#ଅନ୍ତର୍ଭାଵ <io.h>
#endif
#ଯଦି HAVE_MMAP
#ଅନ୍ତର୍ଭାଵ <sys/mman.h>
#ନଚେତଯଦି HAVE_MAPVIEWOFFILE
#ଅନ୍ତର୍ଭାଵ <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା FileLogContext {
    ଅଚଳ AVClass *class;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା   log_offset;
    ଶୂନ୍ୟ *log_ctx;
} FileLogContext;

ସ୍ଥିର ଅଚଳ AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = ଖାଲି,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#ଯଦି HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା map_file(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, size_t size, ପୂର୍ଣ୍ଣସଂଖ୍ୟା shared, ଶୂନ୍ୟ **ptr)
{
#ଯଦି HAVE_MMAP
    ଯଦି (shared) {
        ସଂରଚନା stat st;
        ଯଦି (fstat(fd, &st) < 0)
            ଫେରନ୍ତୁ AVERROR(errno);
        ଯଦି (st.st_size < size && ftruncate(fd, size) < 0)
            ଫେରନ୍ତୁ AVERROR(errno);
    }

    ଶୂନ୍ୟ *map = mmap(ଖାଲି, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    ଯଦି (map == MAP_FAILED)
        ଫେରନ୍ତୁ AVERROR(errno);
#ଅନ୍ୟଥା
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    ଯଦି (fh == INVALID_HANDLE_ମୂଲ୍ୟ)
        ଫେରନ୍ତୁ AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, ଖାଲି,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, ଖାଲି);
    ଯଦି (!mh)
        ଫେରନ୍ତୁ AVERROR(EIO);

    ଶୂନ୍ୟ *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    ଯଦି (!map)
        ଫେରନ୍ତୁ AVERROR(EIO);
#endif

    *ptr = map;
    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ unmap_file(ଶୂନ୍ୟ *ptr, size_t size)
{
#ଯଦି HAVE_MMAP
    munmap(ptr, size);
#ଅନ୍ୟଥା
    UnmapViewOfFile(ptr);
#endif
}
#endif

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_file_map(ଅଚଳ ଅକ୍ଷର *filename, uint8_t **bufptr, size_t *size,
                ପୂର୍ଣ୍ଣସଂଖ୍ୟା log_offset, ଶୂନ୍ୟ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା err, fd = avpriv_open(filename, O_RDONLY);
    ସଂରଚନା stat st;
    av_unused ଶୂନ୍ୟ *ptr;
    *bufptr = ଖାଲି;
    *size = 0;

    ଯଦି (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        ଫେରନ୍ତୁ err;
    }

    ଯଦି (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        ଫେରନ୍ତୁ err;
    }

    ଯଦି (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        ଫେରନ୍ତୁ AVERROR(EINVAL);
    }
    *size = st.st_size;

    ଯଦି (!*size) {
        *bufptr = ଖାଲି;
        ଯାଅ out;
    }

#ଯଦି HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    ଯଦି (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        ଫେରନ୍ତୁ err;
    }
    *bufptr = ptr;
#ଅନ୍ୟଥା
    *bufptr = av_malloc(*size);
    ଯଦି (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }
    ପଠ(fd, *bufptr, *size);
#endif

out:
    close(fd);
    ଫେରନ୍ତୁ 0;
}

ଶୂନ୍ୟ av_file_unmap(uint8_t *bufptr, size_t size)
{
    ଯଦି (!size || !bufptr)
        ଫେରନ୍ତୁ;
#ଯଦି HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#ଅନ୍ୟଥା
    av_free(bufptr);
#endif
}

ପୂର୍ଣ୍ଣସଂଖ୍ୟା av_file_map_shared(ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd, size_t size, ଶୂନ୍ୟ **bufptr)
{
    *bufptr = ଖାଲି;
    ଯଦି (!size)
        ଫେରନ୍ତୁ AVERROR(EINVAL);
#ଯଦି HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ଫେରନ୍ତୁ map_file(fd, size, 1, bufptr);
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif
}

ଶୂନ୍ୟ av_file_unmap_shared(ଶୂନ୍ୟ *bufptr, size_t size)
{
#ଯଦି HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ଯଦି (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "error.h"
#અન્તર્ભાવ "file.h"
#અન્તર્ભાવ "file_open.h"
#અન્તર્ભાવ "internal.h"
#અન્તર્ભાવ "log.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ <fcntl.h>
#અન્તર્ભાવ <sys/stat.h>
#જો HAVE_UNISTD_H
#અન્તર્ભાવ <unistd.h>
#endif
#જો HAVE_IO_H
#અન્તર્ભાવ <io.h>
#endif
#જો HAVE_MMAP
#અન્તર્ભાવ <sys/mman.h>
#અથવાજો HAVE_MAPVIEWOFFILE
#અન્તર્ભાવ <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

પ્રકારવ્યાખ્યા સંરચના FileLogContext {
    અચલ AVClass *class;
    પૂર્ણાંક   log_offset;
    શૂન્ય *log_ctx;
} FileLogContext;

સ્થિર અચલ AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = ખાલી,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#જો HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
સ્થિર પૂર્ણાંક map_file(પૂર્ણાંક fd, size_t size, પૂર્ણાંક shared, શૂન્ય **ptr)
{
#જો HAVE_MMAP
    જો (shared) {
        સંરચના stat st;
        જો (fstat(fd, &st) < 0)
            પાછા AVERROR(errno);
        જો (st.st_size < size && ftruncate(fd, size) < 0)
            પાછા AVERROR(errno);
    }

    શૂન્ય *map = mmap(ખાલી, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    જો (map == MAP_FAILED)
        પાછા AVERROR(errno);
#નહીંતર
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    જો (fh == INVALID_HANDLE_કિંમત)
        પાછા AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, ખાલી,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, ખાલી);
    જો (!mh)
        પાછા AVERROR(EIO);

    શૂન્ય *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    જો (!map)
        પાછા AVERROR(EIO);
#endif

    *ptr = map;
    પાછા 0;
}

સ્થિર શૂન્ય unmap_file(શૂન્ય *ptr, size_t size)
{
#જો HAVE_MMAP
    munmap(ptr, size);
#નહીંતર
    UnmapViewOfFile(ptr);
#endif
}
#endif

પૂર્ણાંક av_file_map(અચલ અક્ષર *filename, uint8_t **bufptr, size_t *size,
                પૂર્ણાંક log_offset, શૂન્ય *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    પૂર્ણાંક err, fd = avpriv_open(filename, O_RDONLY);
    સંરચના stat st;
    av_unused શૂન્ય *ptr;
    *bufptr = ખાલી;
    *size = 0;

    જો (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        પાછા err;
    }

    જો (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        પાછા err;
    }

    જો (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        પાછા AVERROR(EINVAL);
    }
    *size = st.st_size;

    જો (!*size) {
        *bufptr = ખાલી;
        જાઓ out;
    }

#જો HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    જો (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        પાછા err;
    }
    *bufptr = ptr;
#નહીંતર
    *bufptr = av_malloc(*size);
    જો (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        પાછા AVERROR(ENOMEM);
    }
    પઠ(fd, *bufptr, *size);
#endif

out:
    close(fd);
    પાછા 0;
}

શૂન્ય av_file_unmap(uint8_t *bufptr, size_t size)
{
    જો (!size || !bufptr)
        પાછા;
#જો HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#નહીંતર
    av_free(bufptr);
#endif
}

પૂર્ણાંક av_file_map_shared(પૂર્ણાંક fd, size_t size, શૂન્ય **bufptr)
{
    *bufptr = ખાલી;
    જો (!size)
        પાછા AVERROR(EINVAL);
#જો HAVE_MMAP || HAVE_MAPVIEWOFFILE
    પાછા map_file(fd, size, 1, bufptr);
#નહીંતર
    પાછા AVERROR(ENOSYS);
#endif
}

શૂન્ય av_file_unmap_shared(શૂન્ય *bufptr, size_t size)
{
#જો HAVE_MMAP || HAVE_MAPVIEWOFFILE
    જો (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

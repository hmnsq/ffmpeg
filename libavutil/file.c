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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "error.h"
#അന്തര്ഭാവ "file.h"
#അന്തര്ഭാവ "file_open.h"
#അന്തര്ഭാവ "internal.h"
#അന്തര്ഭാവ "log.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ <fcntl.h>
#അന്തര്ഭാവ <sys/stat.h>
#എങ്കിൽ HAVE_UNISTD_H
#അന്തര്ഭാവ <unistd.h>
#endif
#എങ്കിൽ HAVE_IO_H
#അന്തര്ഭാവ <io.h>
#endif
#എങ്കിൽ HAVE_MMAP
#അന്തര്ഭാവ <sys/mman.h>
#അല്ലെങ്കിലെങ്കിൽ HAVE_MAPVIEWOFFILE
#അന്തര്ഭാവ <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

തരനിർവചനം ഘടന FileLogContext {
    സ്ഥിരം AVClass *class;
    പൂർണ്ണസംഖ്യ   log_offset;
    ശൂന്യം *log_ctx;
} FileLogContext;

സ്ഥിതം സ്ഥിരം AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = ശൂന്യ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#എങ്കിൽ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
സ്ഥിതം പൂർണ്ണസംഖ്യ map_file(പൂർണ്ണസംഖ്യ fd, size_t size, പൂർണ്ണസംഖ്യ shared, ശൂന്യം **ptr)
{
#എങ്കിൽ HAVE_MMAP
    എങ്കിൽ (shared) {
        ഘടന stat st;
        എങ്കിൽ (fstat(fd, &st) < 0)
            തിരികെ AVERROR(errno);
        എങ്കിൽ (st.st_size < size && ftruncate(fd, size) < 0)
            തിരികെ AVERROR(errno);
    }

    ശൂന്യം *map = mmap(ശൂന്യ, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    എങ്കിൽ (map == MAP_FAILED)
        തിരികെ AVERROR(errno);
#അല്ലെങ്കിൽ
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    എങ്കിൽ (fh == INVALID_HANDLE_മൂല്യം)
        തിരികെ AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, ശൂന്യ,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, ശൂന്യ);
    എങ്കിൽ (!mh)
        തിരികെ AVERROR(EIO);

    ശൂന്യം *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    എങ്കിൽ (!map)
        തിരികെ AVERROR(EIO);
#endif

    *ptr = map;
    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം unmap_file(ശൂന്യം *ptr, size_t size)
{
#എങ്കിൽ HAVE_MMAP
    munmap(ptr, size);
#അല്ലെങ്കിൽ
    UnmapViewOfFile(ptr);
#endif
}
#endif

പൂർണ്ണസംഖ്യ av_file_map(സ്ഥിരം അക്ഷരം *filename, uint8_t **bufptr, size_t *size,
                പൂർണ്ണസംഖ്യ log_offset, ശൂന്യം *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    പൂർണ്ണസംഖ്യ err, fd = avpriv_open(filename, O_RDONLY);
    ഘടന stat st;
    av_unused ശൂന്യം *ptr;
    *bufptr = ശൂന്യ;
    *size = 0;

    എങ്കിൽ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        തിരികെ err;
    }

    എങ്കിൽ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        തിരികെ err;
    }

    എങ്കിൽ (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        തിരികെ AVERROR(EINVAL);
    }
    *size = st.st_size;

    എങ്കിൽ (!*size) {
        *bufptr = ശൂന്യ;
        പോകുക out;
    }

#എങ്കിൽ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    എങ്കിൽ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        തിരികെ err;
    }
    *bufptr = ptr;
#അല്ലെങ്കിൽ
    *bufptr = av_malloc(*size);
    എങ്കിൽ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        തിരികെ AVERROR(ENOMEM);
    }
    പഠ(fd, *bufptr, *size);
#endif

out:
    close(fd);
    തിരികെ 0;
}

ശൂന്യം av_file_unmap(uint8_t *bufptr, size_t size)
{
    എങ്കിൽ (!size || !bufptr)
        തിരികെ;
#എങ്കിൽ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#അല്ലെങ്കിൽ
    av_free(bufptr);
#endif
}

പൂർണ്ണസംഖ്യ av_file_map_shared(പൂർണ്ണസംഖ്യ fd, size_t size, ശൂന്യം **bufptr)
{
    *bufptr = ശൂന്യ;
    എങ്കിൽ (!size)
        തിരികെ AVERROR(EINVAL);
#എങ്കിൽ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    തിരികെ map_file(fd, size, 1, bufptr);
#അല്ലെങ്കിൽ
    തിരികെ AVERROR(ENOSYS);
#endif
}

ശൂന്യം av_file_unmap_shared(ശൂന്യം *bufptr, size_t size)
{
#എങ്കിൽ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    എങ്കിൽ (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

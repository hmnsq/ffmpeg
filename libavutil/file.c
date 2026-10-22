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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "file.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "file_open.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "internal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/stat.h>
#ਜੇ HAVE_UNISTD_H
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_IO_H
#ਅਨ੍ਤਰ੍ਭਾਵ <io.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_MMAP
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/mman.h>
#ਜਾਂਜੇ HAVE_MAPVIEWOFFILE
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ stat
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ fstat
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ stat  _stat64
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ fstat _fstat64
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FileLogContext {
    ਅਚਲ AVClass *class;
    ਪੂਰਨ   log_ਵਿੱਥ;
    ਖਾਲੀ *log_ctx;
} FileLogContext;

ਸਥਿਰ ਅਚਲ AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .ਵਸਤੂ_name                 = av_default_ਵਸਤੂ_name,
    .option                    = ਨਿਰਾ,
    .ਸੰਸਕਰਣ                   = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .log_level_ਵਿੱਥ_ਵਿੱਥ   = offsetof(FileLogContext, log_ਵਿੱਥ),
    .ਮਾਪਾ_log_context_ਵਿੱਥ = offsetof(FileLogContext, log_ctx),
};

#ਜੇ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
ਸਥਿਰ ਪੂਰਨ map_file(ਪੂਰਨ fd, size_t ਮਾਪ, ਪੂਰਨ shared, ਖਾਲੀ **ptr)
{
#ਜੇ HAVE_MMAP
    ਜੇ (shared) {
        ਬਣਤਰ stat st;
        ਜੇ (fstat(fd, &st) < 0)
            ਵਾਪਸ AVERROR(errno);
        ਜੇ (st.st_ਮਾਪ < ਮਾਪ && ftruncate(fd, ਮਾਪ) < 0)
            ਵਾਪਸ AVERROR(errno);
    }

    ਖਾਲੀ *map = mmap(ਨਿਰਾ, ਮਾਪ, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_ਨਿੱਜੀ, fd, 0);
    ਜੇ (map == MAP_FAILED)
        ਵਾਪਸ AVERROR(errno);
#ਨਹੀਂਤਾਂ
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    ਜੇ (fh == INVALID_HANDLE_ਮੁੱਲ)
        ਵਾਪਸ AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, ਨਿਰਾ,
                                  shared ? ਪੰਨਾ_READWRITE : ਪੰਨਾ_READONLY,
                                  (uint64_t)ਮਾਪ >> 32, ਮਾਪ, ਨਿਰਾ);
    ਜੇ (!mh)
        ਵਾਪਸ AVERROR(EIO);

    ਖਾਲੀ *map = Map_View_ਦਾ_File(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, ਮਾਪ);
    CloseHandle(mh);
    ਜੇ (!map)
        ਵਾਪਸ AVERROR(EIO);
#ਜੇ_ਅੰਤ

    *ptr = map;
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ unmap_file(ਖਾਲੀ *ptr, size_t ਮਾਪ)
{
#ਜੇ HAVE_MMAP
    munmap(ptr, ਮਾਪ);
#ਨਹੀਂਤਾਂ
    Unmap_View_ਦਾ_File(ptr);
#ਜੇ_ਅੰਤ
}
#ਜੇ_ਅੰਤ

ਪੂਰਨ av_file_map(ਅਚਲ ਅੱਖਰ *filename, uint8_t **bufptr, size_t *ਮਾਪ,
                ਪੂਰਨ log_ਵਿੱਥ, ਖਾਲੀ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_ਵਿੱਥ, log_ctx };
    ਪੂਰਨ err, fd = avpriv_open(filename, O_RDONLY);
    ਬਣਤਰ stat st;
    av_ਅਣਵਰਤਿਆ ਖਾਲੀ *ptr;
    *bufptr = ਨਿਰਾ;
    *ਮਾਪ = 0;

    ਜੇ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        ਵਾਪਸ err;
    }

    ਜੇ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        ਵਾਪਸ err;
    }

    ਜੇ (st.st_ਮਾਪ > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        ਵਾਪਸ AVERROR(EINVAL);
    }
    *ਮਾਪ = st.st_ਮਾਪ;

    ਜੇ (!*ਮਾਪ) {
        *bufptr = ਨਿਰਾ;
        ਜਾਓ ਬਾਹਰਲਾ;
    }

#ਜੇ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *ਮਾਪ, 0, &ptr);
    ਜੇ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *ਮਾਪ = 0;
        ਵਾਪਸ err;
    }
    *bufptr = ptr;
#ਨਹੀਂਤਾਂ
    *bufptr = av_malloc(*ਮਾਪ);
    ਜੇ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *ਮਾਪ = 0;
        ਵਾਪਸ AVERROR(ENOMEM);
    }
    ਪਠ(fd, *bufptr, *ਮਾਪ);
#ਜੇ_ਅੰਤ

ਬਾਹਰਲਾ:
    close(fd);
    ਵਾਪਸ 0;
}

ਖਾਲੀ av_file_unmap(uint8_t *bufptr, size_t ਮਾਪ)
{
    ਜੇ (!ਮਾਪ || !bufptr)
        ਵਾਪਸ;
#ਜੇ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, ਮਾਪ);
#ਨਹੀਂਤਾਂ
    av_free(bufptr);
#ਜੇ_ਅੰਤ
}

ਪੂਰਨ av_file_map_shared(ਪੂਰਨ fd, size_t ਮਾਪ, ਖਾਲੀ **bufptr)
{
    *bufptr = ਨਿਰਾ;
    ਜੇ (!ਮਾਪ)
        ਵਾਪਸ AVERROR(EINVAL);
#ਜੇ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ਵਾਪਸ map_file(fd, ਮਾਪ, 1, bufptr);
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ
}

ਖਾਲੀ av_file_unmap_shared(ਖਾਲੀ *bufptr, size_t ਮਾਪ)
{
#ਜੇ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ਜੇ (ਮਾਪ && bufptr)
        unmap_file(bufptr, ਮਾਪ);
#ਜੇ_ਅੰਤ
}

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
#ಆದರೆ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_IO_H
#ಅನ್ತರ್ಭಾವ <io.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_MMAP
#ಅನ್ತರ್ಭಾವ <sys/mman.h>
#ಅಥವಾಆದರೆ HAVE_MAPVIEWOFFILE
#ಅನ್ತರ್ಭಾವ <windows.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು stat
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು fstat
#ವ್ಯಾಖ್ಯಾನಿಸು stat  _stat64
#ವ್ಯಾಖ್ಯಾನಿಸು fstat _fstat64
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FileLogContext {
    ಸ್ಥಿರಾಂಕ AVClass *class;
    ಪೂರ್ಣಾಂಕ   log_ಸ್ಥಾನಾಂತರ;
    ಶೂನ್ಯ *log_ctx;
} FileLogContext;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .ಅಂಶ_name                 = av_default_ಅಂಶ_name,
    .option                    = ಖಾಲಿ,
    .ಆವೃತ್ತಿ                   = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .log_level_ಸ್ಥಾನಾಂತರ_ಸ್ಥಾನಾಂತರ   = offsetof(FileLogContext, log_ಸ್ಥಾನಾಂತರ),
    .ಪೋಷಕ_log_context_ಸ್ಥಾನಾಂತರ = offsetof(FileLogContext, log_ctx),
};

#ಆದರೆ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ map_file(ಪೂರ್ಣಾಂಕ fd, size_t ಗಾತ್ರ_2, ಪೂರ್ಣಾಂಕ shared, ಶೂನ್ಯ **ptr)
{
#ಆದರೆ HAVE_MMAP
    ಆದರೆ (shared) {
        ರಚನೆ stat st;
        ಆದರೆ (fstat(fd, &st) < 0)
            ಹಿಂತಿರುಗಿ AVERROR(errno);
        ಆದರೆ (st.st_ಗಾತ್ರ < ಗಾತ್ರ_2 && ftruncate(fd, ಗಾತ್ರ_2) < 0)
            ಹಿಂತಿರುಗಿ AVERROR(errno);
    }

    ಶೂನ್ಯ *map = mmap(ಖಾಲಿ, ಗಾತ್ರ_2, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_ಖಾಸಗಿ, fd, 0);
    ಆದರೆ (map == MAP_FAILED)
        ಹಿಂತಿರುಗಿ AVERROR(errno);
#ಇಲ್ಲದಿದ್ದರೆ
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    ಆದರೆ (fh == INVALID_HANDLE_ಮೌಲ್ಯ)
        ಹಿಂತಿರುಗಿ AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, ಖಾಲಿ,
                                  shared ? ಪುಟ_READWRITE : ಪುಟ_READONLY,
                                  (uint64_t)ಗಾತ್ರ_2 >> 32, ಗಾತ್ರ_2, ಖಾಲಿ);
    ಆದರೆ (!mh)
        ಹಿಂತಿರುಗಿ AVERROR(EIO);

    ಶೂನ್ಯ *map = Map_View_ದ_File(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, ಗಾತ್ರ_2);
    CloseHandle(mh);
    ಆದರೆ (!map)
        ಹಿಂತಿರುಗಿ AVERROR(EIO);
#ಆದರೆ_ಅಂತ್ಯ

    *ptr = map;
    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ unmap_file(ಶೂನ್ಯ *ptr, size_t ಗಾತ್ರ_2)
{
#ಆದರೆ HAVE_MMAP
    munmap(ptr, ಗಾತ್ರ_2);
#ಇಲ್ಲದಿದ್ದರೆ
    Unmap_View_ದ_File(ptr);
#ಆದರೆ_ಅಂತ್ಯ
}
#ಆದರೆ_ಅಂತ್ಯ

ಪೂರ್ಣಾಂಕ av_file_map(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *filename, uint8_t **bufptr, size_t *ಗಾತ್ರ_2,
                ಪೂರ್ಣಾಂಕ log_ಸ್ಥಾನಾಂತರ, ಶೂನ್ಯ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_ಸ್ಥಾನಾಂತರ, log_ctx };
    ಪೂರ್ಣಾಂಕ err, fd = avpriv_open(filename, O_RDONLY);
    ರಚನೆ stat st;
    av_ಬಳಸದ ಶೂನ್ಯ *ptr;
    *bufptr = ಖಾಲಿ;
    *ಗಾತ್ರ_2 = 0;

    ಆದರೆ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        ಹಿಂತಿರುಗಿ err;
    }

    ಆದರೆ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        ಹಿಂತಿರುಗಿ err;
    }

    ಆದರೆ (st.st_ಗಾತ್ರ > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
    }
    *ಗಾತ್ರ_2 = st.st_ಗಾತ್ರ;

    ಆದರೆ (!*ಗಾತ್ರ_2) {
        *bufptr = ಖಾಲಿ;
        ಹೋಗು ಹೊರಹೋಗು;
    }

#ಆದರೆ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *ಗಾತ್ರ_2, 0, &ptr);
    ಆದರೆ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *ಗಾತ್ರ_2 = 0;
        ಹಿಂತಿರುಗಿ err;
    }
    *bufptr = ptr;
#ಇಲ್ಲದಿದ್ದರೆ
    *bufptr = av_malloc(*ಗಾತ್ರ_2);
    ಆದರೆ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *ಗಾತ್ರ_2 = 0;
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }
    ಪಠ(fd, *bufptr, *ಗಾತ್ರ_2);
#ಆದರೆ_ಅಂತ್ಯ

ಹೊರಹೋಗು:
    close(fd);
    ಹಿಂತಿರುಗಿ 0;
}

ಶೂನ್ಯ av_file_unmap(uint8_t *bufptr, size_t ಗಾತ್ರ_2)
{
    ಆದರೆ (!ಗಾತ್ರ_2 || !bufptr)
        ಹಿಂತಿರುಗಿ;
#ಆದರೆ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, ಗಾತ್ರ_2);
#ಇಲ್ಲದಿದ್ದರೆ
    av_free(bufptr);
#ಆದರೆ_ಅಂತ್ಯ
}

ಪೂರ್ಣಾಂಕ av_file_map_shared(ಪೂರ್ಣಾಂಕ fd, size_t ಗಾತ್ರ_2, ಶೂನ್ಯ **bufptr)
{
    *bufptr = ಖಾಲಿ;
    ಆದರೆ (!ಗಾತ್ರ_2)
        ಹಿಂತಿರುಗಿ AVERROR(EINVAL);
#ಆದರೆ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ಹಿಂತಿರುಗಿ map_file(fd, ಗಾತ್ರ_2, 1, bufptr);
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ av_file_unmap_shared(ಶೂನ್ಯ *bufptr, size_t ಗಾತ್ರ_2)
{
#ಆದರೆ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ಆದರೆ (ಗಾತ್ರ_2 && bufptr)
        unmap_file(bufptr, ಗಾತ್ರ_2);
#ಆದರೆ_ಅಂತ್ಯ
}

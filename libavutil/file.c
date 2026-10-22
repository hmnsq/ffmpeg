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
#إذا HAVE_UNISTD_H
#ضمن <unistd.h>
#جيڪڏهن_پورو
#إذا HAVE_IO_H
#ضمن <io.h>
#جيڪڏهن_پورو
#إذا HAVE_MMAP
#ضمن <sys/mman.h>
#وإلاإذا HAVE_MAPVIEWOFFILE
#ضمن <windows.h>
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#وصف_رد stat
#وصف_رد fstat
#وصف_ڪريو stat  _stat64
#وصف_ڪريو fstat _fstat64
#جيڪڏهن_پورو

تعريفنوع بنية FileLogContext {
    ثابت AVClass *class;
    صحيح   log_وٿي;
    فراغ *log_ctx;
} FileLogContext;

ساكن ثابت AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .شي_name                 = av_default_شي_name,
    .option                    = عدم,
    .نسخو                   = LIBAVUTIL_نسخو_INT,
    .log_level_وٿي_وٿي   = offsetof(FileLogContext, log_وٿي),
    .والد_log_context_وٿي = offsetof(FileLogContext, log_ctx),
};

#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
ساكن صحيح map_file(صحيح fd, size_t سائيز, صحيح shared, فراغ **ptr)
{
#إذا HAVE_MMAP
    إذا (shared) {
        بنية stat st;
        إذا (fstat(fd, &st) < 0)
            أرجع AVERROR(errno);
        إذا (st.st_سائيز < سائيز && ftruncate(fd, سائيز) < 0)
            أرجع AVERROR(errno);
    }

    فراغ *map = mmap(عدم, سائيز, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_ذاتي, fd, 0);
    إذا (map == MAP_FAILED)
        أرجع AVERROR(errno);
#وإلا
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    إذا (fh == INVALID_HANDLE_قدر)
        أرجع AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, عدم,
                                  shared ? صفحو_READWRITE : صفحو_READONLY,
                                  (uint64_t)سائيز >> 32, سائيز, عدم);
    إذا (!mh)
        أرجع AVERROR(EIO);

    فراغ *map = Map_View_جو_File(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, سائيز);
    CloseHandle(mh);
    إذا (!map)
        أرجع AVERROR(EIO);
#جيڪڏهن_پورو

    *ptr = map;
    أرجع 0;
}

ساكن فراغ unmap_file(فراغ *ptr, size_t سائيز)
{
#إذا HAVE_MMAP
    munmap(ptr, سائيز);
#وإلا
    Unmap_View_جو_File(ptr);
#جيڪڏهن_پورو
}
#جيڪڏهن_پورو

صحيح av_file_map(ثابت حرف *filename, uint8_t **bufptr, size_t *سائيز,
                صحيح log_وٿي, فراغ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_وٿي, log_ctx };
    صحيح err, fd = avpriv_open(filename, O_RDONLY);
    بنية stat st;
    av_اڻ_استعمال_ٿيل فراغ *ptr;
    *bufptr = عدم;
    *سائيز = 0;

    إذا (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        أرجع err;
    }

    إذا (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        أرجع err;
    }

    إذا (st.st_سائيز > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        أرجع AVERROR(EINVAL);
    }
    *سائيز = st.st_سائيز;

    إذا (!*سائيز) {
        *bufptr = عدم;
        اذهب ٻاهريون;
    }

#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *سائيز, 0, &ptr);
    إذا (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *سائيز = 0;
        أرجع err;
    }
    *bufptr = ptr;
#وإلا
    *bufptr = av_malloc(*سائيز);
    إذا (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *سائيز = 0;
        أرجع AVERROR(ENOMEM);
    }
    اقرأ(fd, *bufptr, *سائيز);
#جيڪڏهن_پورو

ٻاهريون:
    close(fd);
    أرجع 0;
}

فراغ av_file_unmap(uint8_t *bufptr, size_t سائيز)
{
    إذا (!سائيز || !bufptr)
        أرجع;
#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, سائيز);
#وإلا
    av_free(bufptr);
#جيڪڏهن_پورو
}

صحيح av_file_map_shared(صحيح fd, size_t سائيز, فراغ **bufptr)
{
    *bufptr = عدم;
    إذا (!سائيز)
        أرجع AVERROR(EINVAL);
#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
    أرجع map_file(fd, سائيز, 1, bufptr);
#وإلا
    أرجع AVERROR(ENOSYS);
#جيڪڏهن_پورو
}

فراغ av_file_unmap_shared(فراغ *bufptr, size_t سائيز)
{
#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
    إذا (سائيز && bufptr)
        unmap_file(bufptr, سائيز);
#جيڪڏهن_پورو
}

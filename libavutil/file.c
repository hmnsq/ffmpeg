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

#شامل "config.h"
#شامل "error.h"
#شامل "file.h"
#شامل "file_open.h"
#شامل "internal.h"
#شامل "log.h"
#شامل "mem.h"
#شامل <fcntl.h>
#شامل <sys/stat.h>
#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#اگر_ختم
#اگر HAVE_IO_H
#شامل <io.h>
#اگر_ختم
#اگر HAVE_MMAP
#شامل <sys/mman.h>
#وگرنہ_اگر HAVE_MAPVIEWOFFILE
#شامل <windows.h>
#اگر_ختم

#اگر_تعریف_شدہ _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#تعریف_منسوخ stat
#تعریف_منسوخ fstat
#تعریف_کرو stat  _stat64
#تعریف_کرو fstat _fstat64
#اگر_ختم

قسمتعریف ساخت FileLogContext {
    ثابت AVClass *class;
    صحیح   log_انحراف;
    خالی *log_ctx;
} FileLogContext;

ساکن ثابت AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .شے_name                 = av_default_شے_name,
    .option                    = تہی,
    .نسخہ                   = LIBAVUTIL_نسخہ_INT,
    .log_level_انحراف_انحراف   = offsetof(FileLogContext, log_انحراف),
    .والد_log_context_انحراف = offsetof(FileLogContext, log_ctx),
};

#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
ساکن صحیح map_file(صحیح fd, size_t سائز, صحیح shared, خالی **ptr)
{
#اگر HAVE_MMAP
    اگر (shared) {
        ساخت stat st;
        اگر (fstat(fd, &st) < 0)
            واپس AVERROR(errno);
        اگر (st.st_سائز < سائز && ftruncate(fd, سائز) < 0)
            واپس AVERROR(errno);
    }

    خالی *map = mmap(تہی, سائز, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_نجی, fd, 0);
    اگر (map == MAP_FAILED)
        واپس AVERROR(errno);
#ورنہ
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    اگر (fh == INVALID_HANDLE_قدر)
        واپس AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, تہی,
                                  shared ? صفحہ_READWRITE : صفحہ_READONLY,
                                  (uint64_t)سائز >> 32, سائز, تہی);
    اگر (!mh)
        واپس AVERROR(EIO);

    خالی *map = Map_View_کا_File(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, سائز);
    CloseHandle(mh);
    اگر (!map)
        واپس AVERROR(EIO);
#اگر_ختم

    *ptr = map;
    واپس 0;
}

ساکن خالی unmap_file(خالی *ptr, size_t سائز)
{
#اگر HAVE_MMAP
    munmap(ptr, سائز);
#ورنہ
    Unmap_View_کا_File(ptr);
#اگر_ختم
}
#اگر_ختم

صحیح av_file_map(ثابت حرف *filename, uint8_t **bufptr, size_t *سائز,
                صحیح log_انحراف, خالی *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_انحراف, log_ctx };
    صحیح err, fd = avpriv_open(filename, O_RDONLY);
    ساخت stat st;
    av_غیر_مستعمل خالی *ptr;
    *bufptr = تہی;
    *سائز = 0;

    اگر (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        واپس err;
    }

    اگر (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        واپس err;
    }

    اگر (st.st_سائز > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        واپس AVERROR(EINVAL);
    }
    *سائز = st.st_سائز;

    اگر (!*سائز) {
        *bufptr = تہی;
        جاؤ برآمد;
    }

#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *سائز, 0, &ptr);
    اگر (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *سائز = 0;
        واپس err;
    }
    *bufptr = ptr;
#ورنہ
    *bufptr = av_malloc(*سائز);
    اگر (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *سائز = 0;
        واپس AVERROR(ENOMEM);
    }
    اقرأ(fd, *bufptr, *سائز);
#اگر_ختم

برآمد:
    close(fd);
    واپس 0;
}

خالی av_file_unmap(uint8_t *bufptr, size_t سائز)
{
    اگر (!سائز || !bufptr)
        واپس;
#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, سائز);
#ورنہ
    av_free(bufptr);
#اگر_ختم
}

صحیح av_file_map_shared(صحیح fd, size_t سائز, خالی **bufptr)
{
    *bufptr = تہی;
    اگر (!سائز)
        واپس AVERROR(EINVAL);
#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
    واپس map_file(fd, سائز, 1, bufptr);
#ورنہ
    واپس AVERROR(ENOSYS);
#اگر_ختم
}

خالی av_file_unmap_shared(خالی *bufptr, size_t سائز)
{
#اگر HAVE_MMAP || HAVE_MAPVIEWOFFILE
    اگر (سائز && bufptr)
        unmap_file(bufptr, سائز);
#اگر_ختم
}

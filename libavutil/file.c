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
#پایان_اگر
#إذا HAVE_IO_H
#ضمن <io.h>
#پایان_اگر
#إذا HAVE_MMAP
#ضمن <sys/mman.h>
#وإلاإذا HAVE_MAPVIEWOFFILE
#ضمن <windows.h>
#پایان_اگر

#اگر_تعریف_شده _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#لغو_تعریف stat
#لغو_تعریف fstat
#تعریف_کن stat  _stat64
#تعریف_کن fstat _fstat64
#پایان_اگر

تعريفنوع بنية FileLogContext {
    ثابت AVClass *class;
    صحيح   log_جابه_جایی;
    فراغ *log_ctx;
} FileLogContext;

ساكن ثابت AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .قلم_name                 = av_default_قلم_name,
    .option                    = عدم,
    .نسخه                   = LIBAVUTIL_نسخه_INT,
    .log_level_جابه_جایی_جابه_جایی   = offsetof(FileLogContext, log_جابه_جایی),
    .والد_log_context_جابه_جایی = offsetof(FileLogContext, log_ctx),
};

#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
ساكن صحيح map_file(صحيح fd, size_t اندازه, صحيح shared, فراغ **ptr)
{
#إذا HAVE_MMAP
    إذا (shared) {
        بنية stat st;
        إذا (fstat(fd, &st) < 0)
            أرجع AVERROR(errno);
        إذا (st.st_اندازه < اندازه && ftruncate(fd, اندازه) < 0)
            أرجع AVERROR(errno);
    }

    فراغ *map = mmap(عدم, اندازه, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_خصوصی, fd, 0);
    إذا (map == MAP_FAILED)
        أرجع AVERROR(errno);
#وإلا
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    إذا (fh == INVALID_HANDLE_مقدار)
        أرجع AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, عدم,
                                  shared ? صفحه_READWRITE : صفحه_READONLY,
                                  (uint64_t)اندازه >> 32, اندازه, عدم);
    إذا (!mh)
        أرجع AVERROR(EIO);

    فراغ *map = Map_View_از_File(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, اندازه);
    CloseHandle(mh);
    إذا (!map)
        أرجع AVERROR(EIO);
#پایان_اگر

    *ptr = map;
    أرجع 0;
}

ساكن فراغ unmap_file(فراغ *ptr, size_t اندازه)
{
#إذا HAVE_MMAP
    munmap(ptr, اندازه);
#وإلا
    Unmap_View_از_File(ptr);
#پایان_اگر
}
#پایان_اگر

صحيح av_file_map(ثابت حرف *filename, uint8_t **bufptr, size_t *اندازه,
                صحيح log_جابه_جایی, فراغ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_جابه_جایی, log_ctx };
    صحيح err, fd = avpriv_open(filename, O_RDONLY);
    بنية stat st;
    av_استفادهنشده فراغ *ptr;
    *bufptr = عدم;
    *اندازه = 0;

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

    إذا (st.st_اندازه > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        أرجع AVERROR(EINVAL);
    }
    *اندازه = st.st_اندازه;

    إذا (!*اندازه) {
        *bufptr = عدم;
        اذهب بیرون;
    }

#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *اندازه, 0, &ptr);
    إذا (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *اندازه = 0;
        أرجع err;
    }
    *bufptr = ptr;
#وإلا
    *bufptr = av_malloc(*اندازه);
    إذا (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *اندازه = 0;
        أرجع AVERROR(ENOMEM);
    }
    اقرأ(fd, *bufptr, *اندازه);
#پایان_اگر

بیرون:
    close(fd);
    أرجع 0;
}

فراغ av_file_unmap(uint8_t *bufptr, size_t اندازه)
{
    إذا (!اندازه || !bufptr)
        أرجع;
#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, اندازه);
#وإلا
    av_free(bufptr);
#پایان_اگر
}

صحيح av_file_map_shared(صحيح fd, size_t اندازه, فراغ **bufptr)
{
    *bufptr = عدم;
    إذا (!اندازه)
        أرجع AVERROR(EINVAL);
#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
    أرجع map_file(fd, اندازه, 1, bufptr);
#وإلا
    أرجع AVERROR(ENOSYS);
#پایان_اگر
}

فراغ av_file_unmap_shared(فراغ *bufptr, size_t اندازه)
{
#إذا HAVE_MMAP || HAVE_MAPVIEWOFFILE
    إذا (اندازه && bufptr)
        unmap_file(bufptr, اندازه);
#پایان_اگر
}

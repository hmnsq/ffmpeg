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
#ضمن "avutil.h"
#ضمن "file_open.h"
#ضمن "mem.h"
#ضمن <stdarg.h>
#ضمن <fcntl.h>
#ضمن <sys/stat.h>
#إذا HAVE_UNISTD_H
#ضمن <unistd.h>
#جے_انت
#إذا HAVE_IO_H
#ضمن <io.h>
#جے_انت

#جے_تعریف_شدہ _WIN32
#تعریف_رد open
#تعریف_رد lseek
#تعریف_رد stat
#تعریف_رد fstat
#ضمن <windows.h>
#ضمن <share.h>
#ضمن <errno.h>
#ضمن "wchar_filename.h"

ساكن صحيح win32_open(ثابت حرف *filename_utf8, صحيح oflag, صحيح pmode)
{
    صحيح fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    إذا (get_extended_win32_رستہ(filename_utf8, &filename_w))
        أرجع -1;
    إذا (!filename_w)
        اذهب fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    إذا (fd != -1 || (oflag & O_CREAT))
        أرجع fd;

fallback:
    /* filename may be in CP_ACP */
    أرجع _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#تعریف_کرو open win32_open
#جے_انت

صحيح avpriv_open(ثابت حرف *filename, صحيح flags, ...)
{
    صحيح fd;
    بنانشانی صحيح منوال = 0;
    va_list ap;

    va_start(ap, flags);
    إذا (flags & O_CREAT)
        منوال = va_arg(ap, بنانشانی صحيح);
    va_end(ap);

#جے_تعریف_شدہ O_CLOEXEC
    flags |= O_CLOEXEC;
#جے_انت
#جے_تعریف_شدہ O_NOINHERIT
    flags |= O_NOINHERIT;
#جے_انت

    fd = open(filename, flags, منوال);
#إذا HAVE_FCNTL
    إذا (fd != -1) {
        إذا (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(عدم, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#جے_انت

    أرجع fd;
}

تعريفنوع بنية FileLogContext {
    ثابت AVClass *class;
    صحيح   log_وتھ;
    فراغ *log_ctx;
} FileLogContext;

ساكن ثابت AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .شے_name                 = av_default_شے_name,
    .option                    = عدم,
    .نسخہ                   = LIBAVUTIL_نسخہ_INT,
    .log_level_وتھ_وتھ   = offsetof(FileLogContext, log_وتھ),
    .ماپا_log_context_وتھ = offsetof(FileLogContext, log_ctx),
};

صحيح avpriv_tempfile(ثابت حرف *اگیتر, حرف **filename, صحيح log_وتھ, فراغ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_وتھ, log_ctx };
    صحيح fd = -1;
#إذا HAVE_MKSTEMP
    size_t len = لڑی_لمبائی(اگیتر) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#وإلاإذا HAVE_TEMPNAM
    فراغ *ptr= tempnam(عدم, اگیتر);
    إذا(!ptr)
        ptr= tempnam(".", اگیتر);
    *filename = av_strdup(ptr);
    حرر(ptr);
#وإلا
    أرجع AVERROR(ENOSYS);
#جے_انت
    /* -----common section-----*/
    إذا (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        أرجع AVERROR(ENOMEM);
    }
#إذا !HAVE_MKSTEMP
#   ifndef O_ثنائی
#       define O_ثنائی 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_ثنائی | O_CREAT | O_EXCL, 0600);
#وإلا
    snprintf(*filename, len, "/tmp/%sXXXXXX", اگیتر);
    fd = mkstemp(*filename);
#إذا defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    إذا (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", اگیتر);
        fd = mkstemp(*filename);
    }
#جے_انت
#جے_انت
    /* -----common section-----*/
    إذا (fd < 0) {
        صحيح err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        أرجع err;
    }
    أرجع fd; /* success */
}

FILE *avpriv_fopen_utf8(ثابت حرف *رستہ, ثابت حرف *منوال)
{
    صحيح fd;
    صحيح access;
    ثابت حرف *m = منوال;

    بدل (*m++) {
    حالة 'r': access = O_RDONLY; اكسر;
    حالة 'w': access = O_CREAT|O_WRONLY|O_TRUNC; اكسر;
    حالة 'a': access = O_CREAT|O_WRONLY|O_APPEND; اكسر;
    افتراضي :
        errno = EINVAL;
        أرجع عدم;
    }
    طالما (*m) {
        إذا (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } وإلا إذا (*m == 'b') {
#جے_تعریف_شدہ O_ثنائی
            access |= O_ثنائی;
#جے_انت
        } وإلا إذا (*m) {
            errno = EINVAL;
            أرجع عدم;
        }
        m++;
    }
    fd = avpriv_open(رستہ, access, 0666);
    إذا (fd == -1)
        أرجع عدم;
    أرجع fdopen(fd, منوال);
}

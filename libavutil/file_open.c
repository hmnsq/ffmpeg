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
#د_که_پای
#إذا HAVE_IO_H
#ضمن <io.h>
#د_که_پای

#که_تعریف_شوی _WIN32
#تعریف_لغوه open
#تعریف_لغوه lseek
#تعریف_لغوه stat
#تعریف_لغوه fstat
#ضمن <windows.h>
#ضمن <share.h>
#ضمن <errno.h>
#ضمن "wchar_filename.h"

ساكن صحيح win32_open(ثابت حرف *filename_utf8, صحيح oflag, صحيح pmode)
{
    صحيح fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    إذا (get_extended_win32_لار(filename_utf8, &filename_w))
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
#تعریف_کړه open win32_open
#د_که_پای

صحيح avpriv_open(ثابت حرف *filename, صحيح flags, ...)
{
    صحيح fd;
    بینښه صحيح ډېرپېښ = 0;
    va_list ap;

    va_start(ap, flags);
    إذا (flags & O_CREAT)
        ډېرپېښ = va_arg(ap, بینښه صحيح);
    va_end(ap);

#که_تعریف_شوی O_CLOEXEC
    flags |= O_CLOEXEC;
#د_که_پای
#که_تعریف_شوی O_NOINHERIT
    flags |= O_NOINHERIT;
#د_که_پای

    fd = open(filename, flags, ډېرپېښ);
#إذا HAVE_FCNTL
    إذا (fd != -1) {
        إذا (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(عدم, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#د_که_پای

    أرجع fd;
}

تعريفنوع بنية FileLogContext {
    ثابت AVClass *class;
    صحيح   log_دننه_واټن;
    فراغ *log_ctx;
} FileLogContext;

ساكن ثابت AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .توکی_name                 = av_default_توکی_name,
    .option                    = عدم,
    .نسخه                   = LIBAVUTIL_نسخه_INT,
    .log_level_دننه_واټن_دننه_واټن   = offsetof(FileLogContext, log_دننه_واټن),
    .پلار_log_context_دننه_واټن = offsetof(FileLogContext, log_ctx),
};

صحيح avpriv_tempfile(ثابت حرف *مختاړی, حرف **filename, صحيح log_دننه_واټن, فراغ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_دننه_واټن, log_ctx };
    صحيح fd = -1;
#إذا HAVE_MKSTEMP
    size_t len = مزي_اوږدوالی(مختاړی) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#وإلاإذا HAVE_TEMPNAM
    فراغ *ptr= tempnam(عدم, مختاړی);
    إذا(!ptr)
        ptr= tempnam(".", مختاړی);
    *filename = av_strdup(ptr);
    حرر(ptr);
#وإلا
    أرجع AVERROR(ENOSYS);
#د_که_پای
    /* -----common section-----*/
    إذا (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        أرجع AVERROR(ENOMEM);
    }
#إذا !HAVE_MKSTEMP
#   ifndef O_دوګونی
#       define O_دوګونی 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_دوګونی | O_CREAT | O_EXCL, 0600);
#وإلا
    snprintf(*filename, len, "/tmp/%sXXXXXX", مختاړی);
    fd = mkstemp(*filename);
#إذا defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    إذا (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", مختاړی);
        fd = mkstemp(*filename);
    }
#د_که_پای
#د_که_پای
    /* -----common section-----*/
    إذا (fd < 0) {
        صحيح err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        أرجع err;
    }
    أرجع fd; /* success */
}

FILE *avpriv_fopen_utf8(ثابت حرف *لار, ثابت حرف *ډېرپېښ)
{
    صحيح fd;
    صحيح access;
    ثابت حرف *m = ډېرپېښ;

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
#که_تعریف_شوی O_دوګونی
            access |= O_دوګونی;
#د_که_پای
        } وإلا إذا (*m) {
            errno = EINVAL;
            أرجع عدم;
        }
        m++;
    }
    fd = avpriv_open(لار, access, 0666);
    إذا (fd == -1)
        أرجع عدم;
    أرجع fdopen(fd, ډېرپېښ);
}

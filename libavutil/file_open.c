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
#شامل "avutil.h"
#شامل "file_open.h"
#شامل "mem.h"
#شامل <stdarg.h>
#شامل <fcntl.h>
#شامل <sys/stat.h>
#اگر HAVE_UNISTD_H
#شامل <unistd.h>
#اگر_ختم
#اگر HAVE_IO_H
#شامل <io.h>
#اگر_ختم

#اگر_تعریف_شدہ _WIN32
#تعریف_منسوخ open
#تعریف_منسوخ lseek
#تعریف_منسوخ stat
#تعریف_منسوخ fstat
#شامل <windows.h>
#شامل <share.h>
#شامل <errno.h>
#شامل "wchar_filename.h"

ساکن صحیح win32_open(ثابت حرف *filename_utf8, صحیح oflag, صحیح pmode)
{
    صحیح fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    اگر (get_extended_win32_راستہ(filename_utf8, &filename_w))
        واپس -1;
    اگر (!filename_w)
        جاؤ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    اگر (fd != -1 || (oflag & O_CREAT))
        واپس fd;

fallback:
    /* filename may be in CP_ACP */
    واپس _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#تعریف_کرو open win32_open
#اگر_ختم

صحیح avpriv_open(ثابت حرف *filename, صحیح flags, ...)
{
    صحیح fd;
    غیرعلامتی صحیح منوال = 0;
    va_list ap;

    va_start(ap, flags);
    اگر (flags & O_CREAT)
        منوال = va_arg(ap, غیرعلامتی صحیح);
    va_end(ap);

#اگر_تعریف_شدہ O_CLOEXEC
    flags |= O_CLOEXEC;
#اگر_ختم
#اگر_تعریف_شدہ O_NOINHERIT
    flags |= O_NOINHERIT;
#اگر_ختم

    fd = open(filename, flags, منوال);
#اگر HAVE_FCNTL
    اگر (fd != -1) {
        اگر (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(تہی, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#اگر_ختم

    واپس fd;
}

قسمتعریف ساخت FileLogContext {
    ثابت AVClass *class;
    صحیح   log_انحراف;
    خالی *log_ctx;
} FileLogContext;

ساکن ثابت AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .شے_name                 = av_default_شے_name,
    .option                    = تہی,
    .نسخہ                   = LIBAVUTIL_نسخہ_INT,
    .log_level_انحراف_انحراف   = offsetof(FileLogContext, log_انحراف),
    .والد_log_context_انحراف = offsetof(FileLogContext, log_ctx),
};

صحیح avpriv_tempfile(ثابت حرف *سابقہ, حرف **filename, صحیح log_انحراف, خالی *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_انحراف, log_ctx };
    صحیح fd = -1;
#اگر HAVE_MKSTEMP
    size_t len = لڑی_لمبائی(سابقہ) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#وگرنہ_اگر HAVE_TEMPNAM
    خالی *ptr= tempnam(تہی, سابقہ);
    اگر(!ptr)
        ptr= tempnam(".", سابقہ);
    *filename = av_strdup(ptr);
    آزاد(ptr);
#ورنہ
    واپس AVERROR(ENOSYS);
#اگر_ختم
    /* -----common section-----*/
    اگر (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        واپس AVERROR(ENOMEM);
    }
#اگر !HAVE_MKSTEMP
#   ifndef O_ثنائی
#       define O_ثنائی 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_ثنائی | O_CREAT | O_EXCL, 0600);
#ورنہ
    snprintf(*filename, len, "/tmp/%sXXXXXX", سابقہ);
    fd = mkstemp(*filename);
#اگر defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    اگر (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", سابقہ);
        fd = mkstemp(*filename);
    }
#اگر_ختم
#اگر_ختم
    /* -----common section-----*/
    اگر (fd < 0) {
        صحیح err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        واپس err;
    }
    واپس fd; /* success */
}

FILE *avpriv_fopen_utf8(ثابت حرف *راستہ, ثابت حرف *منوال)
{
    صحیح fd;
    صحیح access;
    ثابت حرف *m = منوال;

    انتخاب (*m++) {
    حالت 'r': access = O_RDONLY; توڑو;
    حالت 'w': access = O_CREAT|O_WRONLY|O_TRUNC; توڑو;
    حالت 'a': access = O_CREAT|O_WRONLY|O_APPEND; توڑو;
    طےشدہ :
        errno = EINVAL;
        واپس تہی;
    }
    جب (*m) {
        اگر (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } ورنہ اگر (*m == 'b') {
#اگر_تعریف_شدہ O_ثنائی
            access |= O_ثنائی;
#اگر_ختم
        } ورنہ اگر (*m) {
            errno = EINVAL;
            واپس تہی;
        }
        m++;
    }
    fd = avpriv_open(راستہ, access, 0666);
    اگر (fd == -1)
        واپس تہی;
    واپس fdopen(fd, منوال);
}

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
#endif
#اگر HAVE_IO_H
#شامل <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#شامل <windows.h>
#شامل <share.h>
#شامل <errno.h>
#شامل "wchar_filename.h"

ایستا صحیح win32_open(ثابت نویسه *filename_utf8, صحیح oflag, صحیح pmode)
{
    صحیح fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    اگر (get_extended_win32_path(filename_utf8, &filename_w))
        بازگشت -1;
    اگر (!filename_w)
        برو fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    اگر (fd != -1 || (oflag & O_CREAT))
        بازگشت fd;

fallback:
    /* filename may be in CP_ACP */
    بازگشت _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

صحیح avpriv_open(ثابت نویسه *filename, صحیح flags, ...)
{
    صحیح fd;
    unsigned صحیح mode = 0;
    va_list ap;

    va_start(ap, flags);
    اگر (flags & O_CREAT)
        mode = va_arg(ap, unsigned صحیح);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#اگر HAVE_FCNTL
    اگر (fd != -1) {
        اگر (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(پوچ, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    بازگشت fd;
}

تعریفنوع ساختار FileLogContext {
    ثابت AVClass *class;
    صحیح   log_offset;
    تهی *log_ctx;
} FileLogContext;

ایستا ثابت AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = پوچ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

صحیح avpriv_tempfile(ثابت نویسه *prefix, نویسه **filename, صحیح log_offset, تهی *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    صحیح fd = -1;
#اگر HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#وگرنهاگر HAVE_TEMPNAM
    تهی *ptr= tempnam(پوچ, prefix);
    اگر(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    آزاد(ptr);
#وگرنه
    بازگشت AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    اگر (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        بازگشت AVERROR(ENOMEM);
    }
#اگر !HAVE_MKSTEMP
#   ifndef O_دودویی
#       define O_دودویی 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_دودویی | O_CREAT | O_EXCL, 0600);
#وگرنه
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#اگر defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    اگر (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    اگر (fd < 0) {
        صحیح err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        بازگشت err;
    }
    بازگشت fd; /* success */
}

FILE *avpriv_fopen_utf8(ثابت نویسه *path, ثابت نویسه *mode)
{
    صحیح fd;
    صحیح access;
    ثابت نویسه *m = mode;

    انتخاب (*m++) {
    حالت 'r': access = O_RDONLY; بشکن;
    حالت 'w': access = O_CREAT|O_WRONLY|O_TRUNC; بشکن;
    حالت 'a': access = O_CREAT|O_WRONLY|O_APPEND; بشکن;
    پیشفرض :
        errno = EINVAL;
        بازگشت پوچ;
    }
    وقتی (*m) {
        اگر (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } وگرنه اگر (*m == 'b') {
#ifdef O_دودویی
            access |= O_دودویی;
#endif
        } وگرنه اگر (*m) {
            errno = EINVAL;
            بازگشت پوچ;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    اگر (fd == -1)
        بازگشت پوچ;
    بازگشت fdopen(fd, mode);
}

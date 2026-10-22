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
#endif
#إذا HAVE_IO_H
#ضمن <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#ضمن <windows.h>
#ضمن <share.h>
#ضمن <errno.h>
#ضمن "wchar_filename.h"

ساكن صحيح win32_open(ثابت حرف *filename_utf8, صحيح oflag, صحيح pmode)
{
    صحيح fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    إذا (get_extended_win32_path(filename_utf8, &filename_w))
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
#define open win32_open
#endif

صحيح avpriv_open(ثابت حرف *filename, صحيح flags, ...)
{
    صحيح fd;
    unsigned صحيح mode = 0;
    va_list ap;

    va_start(ap, flags);
    إذا (flags & O_CREAT)
        mode = va_arg(ap, unsigned صحيح);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#إذا HAVE_FCNTL
    إذا (fd != -1) {
        إذا (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(عدم, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    أرجع fd;
}

تعريفنوع بنية FileLogContext {
    ثابت AVClass *class;
    صحيح   log_offset;
    فراغ *log_ctx;
} FileLogContext;

ساكن ثابت AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = عدم,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

صحيح avpriv_tempfile(ثابت حرف *prefix, حرف **filename, صحيح log_offset, فراغ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    صحيح fd = -1;
#إذا HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#وإلاإذا HAVE_TEMPNAM
    فراغ *ptr= tempnam(عدم, prefix);
    إذا(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    حرر(ptr);
#وإلا
    أرجع AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    إذا (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        أرجع AVERROR(ENOMEM);
    }
#إذا !HAVE_MKSTEMP
#   ifndef O_ئىككىلىك
#       define O_ئىككىلىك 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_ئىككىلىك | O_CREAT | O_EXCL, 0600);
#وإلا
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#إذا defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    إذا (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    إذا (fd < 0) {
        صحيح err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        أرجع err;
    }
    أرجع fd; /* success */
}

FILE *avpriv_fopen_utf8(ثابت حرف *path, ثابت حرف *mode)
{
    صحيح fd;
    صحيح access;
    ثابت حرف *m = mode;

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
#ifdef O_ئىككىلىك
            access |= O_ئىككىلىك;
#endif
        } وإلا إذا (*m) {
            errno = EINVAL;
            أرجع عدم;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    إذا (fd == -1)
        أرجع عدم;
    أرجع fdopen(fd, mode);
}

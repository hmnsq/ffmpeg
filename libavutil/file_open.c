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
#ਅਨ੍ਤਰ੍ਭਾਵ "avutil.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "file_open.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ <stdarg.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <fcntl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <sys/stat.h>
#ਜੇ HAVE_UNISTD_H
#ਅਨ੍ਤਰ੍ਭਾਵ <unistd.h>
#ਜੇ_ਅੰਤ
#ਜੇ HAVE_IO_H
#ਅਨ੍ਤਰ੍ਭਾਵ <io.h>
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _WIN32
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ open
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ lseek
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ stat
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ fstat
#ਅਨ੍ਤਰ੍ਭਾਵ <windows.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <share.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "wchar_filename.h"

ਸਥਿਰ ਪੂਰਨ win32_open(ਅਚਲ ਅੱਖਰ *filename_utf8, ਪੂਰਨ oflag, ਪੂਰਨ pmode)
{
    ਪੂਰਨ fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    ਜੇ (get_extended_win32_ਰਸਤਾ(filename_utf8, &filename_w))
        ਵਾਪਸ -1;
    ਜੇ (!filename_w)
        ਜਾਓ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    ਜੇ (fd != -1 || (oflag & O_CREAT))
        ਵਾਪਸ fd;

fallback:
    /* filename may be in CP_ACP */
    ਵਾਪਸ _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ open win32_open
#ਜੇ_ਅੰਤ

ਪੂਰਨ avpriv_open(ਅਚਲ ਅੱਖਰ *filename, ਪੂਰਨ flags, ...)
{
    ਪੂਰਨ fd;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਬਹੁਲਕ = 0;
    va_list ap;

    va_start(ap, flags);
    ਜੇ (flags & O_CREAT)
        ਬਹੁਲਕ = va_arg(ap, ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ);
    va_end(ap);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ O_CLOEXEC
    flags |= O_CLOEXEC;
#ਜੇ_ਅੰਤ
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ O_NOINHERIT
    flags |= O_NOINHERIT;
#ਜੇ_ਅੰਤ

    fd = open(filename, flags, ਬਹੁਲਕ);
#ਜੇ HAVE_FCNTL
    ਜੇ (fd != -1) {
        ਜੇ (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(ਨਿਰਾ, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#ਜੇ_ਅੰਤ

    ਵਾਪਸ fd;
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ FileLogContext {
    ਅਚਲ AVClass *class;
    ਪੂਰਨ   log_ਵਿੱਥ;
    ਖਾਲੀ *log_ctx;
} FileLogContext;

ਸਥਿਰ ਅਚਲ AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .ਵਸਤੂ_name                 = av_default_ਵਸਤੂ_name,
    .option                    = ਨਿਰਾ,
    .ਸੰਸਕਰਣ                   = LIBAVUTIL_ਸੰਸਕਰਣ_INT,
    .log_level_ਵਿੱਥ_ਵਿੱਥ   = offsetof(FileLogContext, log_ਵਿੱਥ),
    .ਮਾਪਾ_log_context_ਵਿੱਥ = offsetof(FileLogContext, log_ctx),
};

ਪੂਰਨ avpriv_tempfile(ਅਚਲ ਅੱਖਰ *ਅਗੇਤਰ, ਅੱਖਰ **filename, ਪੂਰਨ log_ਵਿੱਥ, ਖਾਲੀ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_ਵਿੱਥ, log_ctx };
    ਪੂਰਨ fd = -1;
#ਜੇ HAVE_MKSTEMP
    size_t len = ਲੜੀ_ਲੰਬਾਈ(ਅਗੇਤਰ) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#ਜਾਂਜੇ HAVE_TEMPNAM
    ਖਾਲੀ *ptr= tempnam(ਨਿਰਾ, ਅਗੇਤਰ);
    ਜੇ(!ptr)
        ptr= tempnam(".", ਅਗੇਤਰ);
    *filename = av_strdup(ptr);
    ਮੁਕਤ(ptr);
#ਨਹੀਂਤਾਂ
    ਵਾਪਸ AVERROR(ENOSYS);
#ਜੇ_ਅੰਤ
    /* -----common section-----*/
    ਜੇ (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        ਵਾਪਸ AVERROR(ENOMEM);
    }
#ਜੇ !HAVE_MKSTEMP
#   ifndef O_ਦੁਆਧਾਰੀ
#       define O_ਦੁਆਧਾਰੀ 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_ਦੁਆਧਾਰੀ | O_CREAT | O_EXCL, 0600);
#ਨਹੀਂਤਾਂ
    snprintf(*filename, len, "/tmp/%sXXXXXX", ਅਗੇਤਰ);
    fd = mkstemp(*filename);
#ਜੇ defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    ਜੇ (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", ਅਗੇਤਰ);
        fd = mkstemp(*filename);
    }
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ
    /* -----common section-----*/
    ਜੇ (fd < 0) {
        ਪੂਰਨ err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        ਵਾਪਸ err;
    }
    ਵਾਪਸ fd; /* success */
}

FILE *avpriv_fopen_utf8(ਅਚਲ ਅੱਖਰ *ਰਸਤਾ, ਅਚਲ ਅੱਖਰ *ਬਹੁਲਕ)
{
    ਪੂਰਨ fd;
    ਪੂਰਨ access;
    ਅਚਲ ਅੱਖਰ *m = ਬਹੁਲਕ;

    ਚੋਣ (*m++) {
    ਹਾਲਤ 'r': access = O_RDONLY; ਰੋਕੋ;
    ਹਾਲਤ 'w': access = O_CREAT|O_WRONLY|O_TRUNC; ਰੋਕੋ;
    ਹਾਲਤ 'a': access = O_CREAT|O_WRONLY|O_APPEND; ਰੋਕੋ;
    ਮੂਲ :
        errno = EINVAL;
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਜਦੋਂ (*m) {
        ਜੇ (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } ਨਹੀਂਤਾਂ ਜੇ (*m == 'b') {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ O_ਦੁਆਧਾਰੀ
            access |= O_ਦੁਆਧਾਰੀ;
#ਜੇ_ਅੰਤ
        } ਨਹੀਂਤਾਂ ਜੇ (*m) {
            errno = EINVAL;
            ਵਾਪਸ ਨਿਰਾ;
        }
        m++;
    }
    fd = avpriv_open(ਰਸਤਾ, access, 0666);
    ਜੇ (fd == -1)
        ਵਾਪਸ ਨਿਰਾ;
    ਵਾਪਸ fdopen(fd, ਬਹੁਲਕ);
}

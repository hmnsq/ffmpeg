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

#include "config.h"
#include "avutil.h"
#include "file_open.h"
#include "mem.h"
#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>
#если HAVE_UNISTD_H
#include <unistd.h>
#endif
#если HAVE_IO_H
#include <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#include <windows.h>
#include <share.h>
#include <errno.h>
#include "wchar_filename.h"

static целое win32_open(const char *filename_utf8, целое oflag, целое pmode)
{
    целое fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    если (get_extended_win32_path(filename_utf8, &filename_w))
        вернуть -1;
    если (!filename_w)
        goto fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    если (fd != -1 || (oflag & O_CREAT))
        вернуть fd;

fallback:
    /* filename may be in CP_ACP */
    вернуть _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

целое avpriv_open(const char *filename, целое flags, ...)
{
    целое fd;
    unsigned целое mode = 0;
    va_list ap;

    va_start(ap, flags);
    если (flags & O_CREAT)
        mode = va_arg(ap, unsigned целое);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#если HAVE_FCNTL
    если (fd != -1) {
        если (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(NULL, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    вернуть fd;
}

typedef struct FileLogContext {
    const AVClass *class;
    целое   log_offset;
    void *log_ctx;
} FileLogContext;

static const AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = NULL,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

целое avpriv_tempfile(const char *prefix, char **filename, целое log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    целое fd = -1;
#если HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#elif HAVE_TEMPNAM
    void *ptr= tempnam(NULL, prefix);
    если(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    free(ptr);
#иначе
    вернуть AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    если (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        вернуть AVERROR(ENOMEM);
    }
#если !HAVE_MKSTEMP
#   ifndef O_BINARY
#       define O_BINARY 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_BINARY | O_CREAT | O_EXCL, 0600);
#иначе
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#если defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    если (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    если (fd < 0) {
        целое err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        вернуть err;
    }
    вернуть fd; /* success */
}

FILE *avpriv_fopen_utf8(const char *path, const char *mode)
{
    целое fd;
    целое access;
    const char *m = mode;

    switch (*m++) {
    case 'r': access = O_RDONLY; break;
    case 'w': access = O_CREAT|O_WRONLY|O_TRUNC; break;
    case 'a': access = O_CREAT|O_WRONLY|O_APPEND; break;
    default :
        errno = EINVAL;
        вернуть NULL;
    }
    пока (*m) {
        если (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } иначе если (*m == 'b') {
#ifdef O_BINARY
            access |= O_BINARY;
#endif
        } иначе если (*m) {
            errno = EINVAL;
            вернуть NULL;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    если (fd == -1)
        вернуть NULL;
    вернуть fdopen(fd, mode);
}

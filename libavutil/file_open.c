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
#만약 HAVE_UNISTD_H
#include <unistd.h>
#endif
#만약 HAVE_IO_H
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

static 정수 win32_open(const char *filename_utf8, 정수 oflag, 정수 pmode)
{
    정수 fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    만약 (get_extended_win32_path(filename_utf8, &filename_w))
        반환 -1;
    만약 (!filename_w)
        goto fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    만약 (fd != -1 || (oflag & O_CREAT))
        반환 fd;

fallback:
    /* filename may be in CP_ACP */
    반환 _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

정수 avpriv_open(const char *filename, 정수 flags, ...)
{
    정수 fd;
    unsigned 정수 mode = 0;
    va_list ap;

    va_start(ap, flags);
    만약 (flags & O_CREAT)
        mode = va_arg(ap, unsigned 정수);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#만약 HAVE_FCNTL
    만약 (fd != -1) {
        만약 (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(NULL, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    반환 fd;
}

typedef struct FileLogContext {
    const AVClass *class;
    정수   log_offset;
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

정수 avpriv_tempfile(const char *prefix, char **filename, 정수 log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    정수 fd = -1;
#만약 HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#elif HAVE_TEMPNAM
    void *ptr= tempnam(NULL, prefix);
    만약(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    free(ptr);
#아니면
    반환 AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    만약 (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        반환 AVERROR(ENOMEM);
    }
#만약 !HAVE_MKSTEMP
#   ifndef O_BINARY
#       define O_BINARY 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_BINARY | O_CREAT | O_EXCL, 0600);
#아니면
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#만약 defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    만약 (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    만약 (fd < 0) {
        정수 err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        반환 err;
    }
    반환 fd; /* success */
}

FILE *avpriv_fopen_utf8(const char *path, const char *mode)
{
    정수 fd;
    정수 access;
    const char *m = mode;

    switch (*m++) {
    case 'r': access = O_RDONLY; break;
    case 'w': access = O_CREAT|O_WRONLY|O_TRUNC; break;
    case 'a': access = O_CREAT|O_WRONLY|O_APPEND; break;
    default :
        errno = EINVAL;
        반환 NULL;
    }
    동안 (*m) {
        만약 (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } 아니면 만약 (*m == 'b') {
#ifdef O_BINARY
            access |= O_BINARY;
#endif
        } 아니면 만약 (*m) {
            errno = EINVAL;
            반환 NULL;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    만약 (fd == -1)
        반환 NULL;
    반환 fdopen(fd, mode);
}

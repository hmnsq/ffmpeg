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
#nếu HAVE_UNISTD_H
#include <unistd.h>
#endif
#nếu HAVE_IO_H
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

static số_nguyên win32_open(const char *filename_utf8, số_nguyên oflag, số_nguyên pmode)
{
    số_nguyên fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    nếu (get_extended_win32_path(filename_utf8, &filename_w))
        trả_về -1;
    nếu (!filename_w)
        goto fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    nếu (fd != -1 || (oflag & O_CREAT))
        trả_về fd;

fallback:
    /* filename may be in CP_ACP */
    trả_về _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

số_nguyên avpriv_open(const char *filename, số_nguyên flags, ...)
{
    số_nguyên fd;
    unsigned số_nguyên mode = 0;
    va_list ap;

    va_start(ap, flags);
    nếu (flags & O_CREAT)
        mode = va_arg(ap, unsigned số_nguyên);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#nếu HAVE_FCNTL
    nếu (fd != -1) {
        nếu (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(NULL, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    trả_về fd;
}

typedef struct FileLogContext {
    const AVClass *class;
    số_nguyên   log_offset;
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

số_nguyên avpriv_tempfile(const char *prefix, char **filename, số_nguyên log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    số_nguyên fd = -1;
#nếu HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#elif HAVE_TEMPNAM
    void *ptr= tempnam(NULL, prefix);
    nếu(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    free(ptr);
#không_thì
    trả_về AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    nếu (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        trả_về AVERROR(ENOMEM);
    }
#nếu !HAVE_MKSTEMP
#   ifndef O_BINARY
#       define O_BINARY 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_BINARY | O_CREAT | O_EXCL, 0600);
#không_thì
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#nếu defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    nếu (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    nếu (fd < 0) {
        số_nguyên err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        trả_về err;
    }
    trả_về fd; /* success */
}

FILE *avpriv_fopen_utf8(const char *path, const char *mode)
{
    số_nguyên fd;
    số_nguyên access;
    const char *m = mode;

    switch (*m++) {
    case 'r': access = O_RDONLY; break;
    case 'w': access = O_CREAT|O_WRONLY|O_TRUNC; break;
    case 'a': access = O_CREAT|O_WRONLY|O_APPEND; break;
    default :
        errno = EINVAL;
        trả_về NULL;
    }
    trong_khi (*m) {
        nếu (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } không_thì nếu (*m == 'b') {
#ifdef O_BINARY
            access |= O_BINARY;
#endif
        } không_thì nếu (*m) {
            errno = EINVAL;
            trả_về NULL;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    nếu (fd == -1)
        trả_về NULL;
    trả_về fdopen(fd, mode);
}

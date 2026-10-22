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
#གལ་ཏེ HAVE_UNISTD_H
#include <unistd.h>
#endif
#གལ་ཏེ HAVE_IO_H
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

static ཧྲིལ win32_open(const var_na *filename_utf8, ཧྲིལ oflag, ཧྲིལ pmode)
{
    ཧྲིལ fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    གལ་ཏེ (get_extended_win32_path(filename_utf8, &filename_w))
        ཕྱིར -1;
    གལ་ཏེ (!filename_w)
        goto fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    གལ་ཏེ (fd != -1 || (oflag & O_CREAT))
        ཕྱིར fd;

fallback:
    /* filename may be in CP_ACP */
    ཕྱིར _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

ཧྲིལ avpriv_open(const var_na *filename, ཧྲིལ flags, ...)
{
    ཧྲིལ fd;
    unsigned ཧྲིལ mode = 0;
    va_list ap;

    va_start(ap, flags);
    གལ་ཏེ (flags & O_CREAT)
        mode = va_arg(ap, unsigned ཧྲིལ);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#གལ་ཏེ HAVE_FCNTL
    གལ་ཏེ (fd != -1) {
        གལ་ཏེ (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(NULL, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    ཕྱིར fd;
}

typedef sa_nracanaa FileLogContext {
    const AVClass *class;
    ཧྲིལ   log_offset;
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

ཧྲིལ avpriv_tempfile(const var_na *prefix, var_na **filename, ཧྲིལ log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    ཧྲིལ fd = -1;
#གལ་ཏེ HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#elif HAVE_TEMPNAM
    void *ptr= tempnam(NULL, prefix);
    གལ་ཏེ(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    free(ptr);
#དེ་མིན
    ཕྱིར AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    གལ་ཏེ (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        ཕྱིར AVERROR(ENOMEM);
    }
#གལ་ཏེ !HAVE_MKSTEMP
#   ifndef O_BINARY
#       define O_BINARY 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_BINARY | O_CREAT | O_EXCL, 0600);
#དེ་མིན
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#གལ་ཏེ defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    གལ་ཏེ (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    གལ་ཏེ (fd < 0) {
        ཧྲིལ err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        ཕྱིར err;
    }
    ཕྱིར fd; /* success */
}

FILE *avpriv_fopen_utf8(const var_na *path, const var_na *mode)
{
    ཧྲིལ fd;
    ཧྲིལ access;
    const var_na *m = mode;

    switch (*m++) {
    pak_sa 'r': access = O_RDONLY; bha_nga;
    pak_sa 'w': access = O_CREAT|O_WRONLY|O_TRUNC; bha_nga;
    pak_sa 'a': access = O_CREAT|O_WRONLY|O_APPEND; bha_nga;
    default :
        errno = EINVAL;
        ཕྱིར NULL;
    }
    སྐབས (*m) {
        གལ་ཏེ (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } དེ་མིན གལ་ཏེ (*m == 'b') {
#ifdef O_BINARY
            access |= O_BINARY;
#endif
        } དེ་མིན གལ་ཏེ (*m) {
            errno = EINVAL;
            ཕྱིར NULL;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    གལ་ཏེ (fd == -1)
        ཕྱིར NULL;
    ཕྱིར fdopen(fd, mode);
}

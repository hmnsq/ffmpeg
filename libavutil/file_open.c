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
#නම් HAVE_UNISTD_H
#include <unistd.h>
#endif
#නම් HAVE_IO_H
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

static පූර්ණ_සංඛ්‍යා win32_open(const var_na *filename_utf8, පූර්ණ_සංඛ්‍යා oflag, පූර්ණ_සංඛ්‍යා pmode)
{
    පූර්ණ_සංඛ්‍යා fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    නම් (get_extended_win32_path(filename_utf8, &filename_w))
        ආපසු -1;
    නම් (!filename_w)
        goto fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    නම් (fd != -1 || (oflag & O_CREAT))
        ආපසු fd;

fallback:
    /* filename may be in CP_ACP */
    ආපසු _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

පූර්ණ_සංඛ්‍යා avpriv_open(const var_na *filename, පූර්ණ_සංඛ්‍යා flags, ...)
{
    පූර්ණ_සංඛ්‍යා fd;
    unsigned පූර්ණ_සංඛ්‍යා mode = 0;
    va_list ap;

    va_start(ap, flags);
    නම් (flags & O_CREAT)
        mode = va_arg(ap, unsigned පූර්ණ_සංඛ්‍යා);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#නම් HAVE_FCNTL
    නම් (fd != -1) {
        නම් (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(NULL, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    ආපසු fd;
}

typedef sa_nracanaa FileLogContext {
    const AVClass *class;
    පූර්ණ_සංඛ්‍යා   log_offset;
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

පූර්ණ_සංඛ්‍යා avpriv_tempfile(const var_na *prefix, var_na **filename, පූර්ණ_සංඛ්‍යා log_offset, void *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    පූර්ණ_සංඛ්‍යා fd = -1;
#නම් HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#elif HAVE_TEMPNAM
    void *ptr= tempnam(NULL, prefix);
    නම්(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    free(ptr);
#නැතහොත්
    ආපසු AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    නම් (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        ආපසු AVERROR(ENOMEM);
    }
#නම් !HAVE_MKSTEMP
#   ifndef O_BINARY
#       define O_BINARY 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_BINARY | O_CREAT | O_EXCL, 0600);
#නැතහොත්
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#නම් defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    නම් (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    නම් (fd < 0) {
        පූර්ණ_සංඛ්‍යා err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        ආපසු err;
    }
    ආපසු fd; /* success */
}

FILE *avpriv_fopen_utf8(const var_na *path, const var_na *mode)
{
    පූර්ණ_සංඛ්‍යා fd;
    පූර්ණ_සංඛ්‍යා access;
    const var_na *m = mode;

    switch (*m++) {
    pak_sa 'r': access = O_RDONLY; bha_nga;
    pak_sa 'w': access = O_CREAT|O_WRONLY|O_TRUNC; bha_nga;
    pak_sa 'a': access = O_CREAT|O_WRONLY|O_APPEND; bha_nga;
    default :
        errno = EINVAL;
        ආපසු NULL;
    }
    අතරතුර (*m) {
        නම් (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } නැතහොත් නම් (*m == 'b') {
#ifdef O_BINARY
            access |= O_BINARY;
#endif
        } නැතහොත් නම් (*m) {
            errno = EINVAL;
            ආපසු NULL;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    නම් (fd == -1)
        ආපසු NULL;
    ආපසු fdopen(fd, mode);
}

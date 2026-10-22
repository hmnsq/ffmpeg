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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "avutil.h"
#ಅನ್ತರ್ಭಾವ "file_open.h"
#ಅನ್ತರ್ಭಾವ "mem.h"
#ಅನ್ತರ್ಭಾವ <stdarg.h>
#ಅನ್ತರ್ಭಾವ <fcntl.h>
#ಅನ್ತರ್ಭಾವ <sys/stat.h>
#ಯದಿ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#endif
#ಯದಿ HAVE_IO_H
#ಅನ್ತರ್ಭಾವ <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#ಅನ್ತರ್ಭಾವ <windows.h>
#ಅನ್ತರ್ಭಾವ <share.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ "wchar_filename.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ win32_open(ಧ್ರುವ ವರ್ಣ *filename_utf8, ಪೂರ್ಣಾಙ್ಕ oflag, ಪೂರ್ಣಾಙ್ಕ pmode)
{
    ಪೂರ್ಣಾಙ್ಕ fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    ಯದಿ (get_extended_win32_path(filename_utf8, &filename_w))
        ಪ್ರತ್ಯಾಗಮ -1;
    ಯದಿ (!filename_w)
        ಗಚ್ಛ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    ಯದಿ (fd != -1 || (oflag & O_CREAT))
        ಪ್ರತ್ಯಾಗಮ fd;

fallback:
    /* filename may be in CP_ACP */
    ಪ್ರತ್ಯಾಗಮ _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

ಪೂರ್ಣಾಙ್ಕ avpriv_open(ಧ್ರುವ ವರ್ಣ *filename, ಪೂರ್ಣಾಙ್ಕ flags, ...)
{
    ಪೂರ್ಣಾಙ್ಕ fd;
    unsigned ಪೂರ್ಣಾಙ್ಕ mode = 0;
    va_list ap;

    va_start(ap, flags);
    ಯದಿ (flags & O_CREAT)
        mode = va_arg(ap, unsigned ಪೂರ್ಣಾಙ್ಕ);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#ಯದಿ HAVE_FCNTL
    ಯದಿ (fd != -1) {
        ಯದಿ (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(ರಿಕ್ತ, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    ಪ್ರತ್ಯಾಗಮ fd;
}

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ FileLogContext {
    ಧ್ರುವ AVClass *class;
    ಪೂರ್ಣಾಙ್ಕ   log_offset;
    ಶೂನ್ಯ *log_ctx;
} FileLogContext;

ಸ್ಥಿರ ಧ್ರುವ AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = ರಿಕ್ತ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

ಪೂರ್ಣಾಙ್ಕ avpriv_tempfile(ಧ್ರುವ ವರ್ಣ *prefix, ವರ್ಣ **filename, ಪೂರ್ಣಾಙ್ಕ log_offset, ಶೂನ್ಯ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    ಪೂರ್ಣಾಙ್ಕ fd = -1;
#ಯದಿ HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#ನೋಚೇದ್ಯದಿ HAVE_TEMPNAM
    ಶೂನ್ಯ *ptr= tempnam(ರಿಕ್ತ, prefix);
    ಯದಿ(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    ಮುಕ್ತ(ptr);
#ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    ಯದಿ (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        ಪ್ರತ್ಯಾಗಮ AVERROR(ENOMEM);
    }
#ಯದಿ !HAVE_MKSTEMP
#   ifndef O_ದ್ವಿಮಾನ
#       define O_ದ್ವಿಮಾನ 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_ದ್ವಿಮಾನ | O_CREAT | O_EXCL, 0600);
#ಅನ್ಯಥಾ
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#ಯದಿ defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    ಯದಿ (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    ಯದಿ (fd < 0) {
        ಪೂರ್ಣಾಙ್ಕ err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        ಪ್ರತ್ಯಾಗಮ err;
    }
    ಪ್ರತ್ಯಾಗಮ fd; /* success */
}

FILE *avpriv_fopen_utf8(ಧ್ರುವ ವರ್ಣ *path, ಧ್ರುವ ವರ್ಣ *mode)
{
    ಪೂರ್ಣಾಙ್ಕ fd;
    ಪೂರ್ಣಾಙ್ಕ access;
    ಧ್ರುವ ವರ್ಣ *m = mode;

    ವಿಕಲ್ಪ (*m++) {
    ಪಕ್ಷ 'r': access = O_RDONLY; ಭಙ್ಗ;
    ಪಕ್ಷ 'w': access = O_CREAT|O_WRONLY|O_TRUNC; ಭಙ್ಗ;
    ಪಕ್ಷ 'a': access = O_CREAT|O_WRONLY|O_APPEND; ಭಙ್ಗ;
    ಸ್ವಭಾವ :
        errno = EINVAL;
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಯಾವತ್ (*m) {
        ಯದಿ (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } ಅನ್ಯಥಾ ಯದಿ (*m == 'b') {
#ifdef O_ದ್ವಿಮಾನ
            access |= O_ದ್ವಿಮಾನ;
#endif
        } ಅನ್ಯಥಾ ಯದಿ (*m) {
            errno = EINVAL;
            ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    ಯದಿ (fd == -1)
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಪ್ರತ್ಯಾಗಮ fdopen(fd, mode);
}

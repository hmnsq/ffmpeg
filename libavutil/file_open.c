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
#ಆದರೆ HAVE_UNISTD_H
#ಅನ್ತರ್ಭಾವ <unistd.h>
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ HAVE_IO_H
#ಅನ್ತರ್ಭಾವ <io.h>
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _WIN32
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು open
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು lseek
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು stat
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು fstat
#ಅನ್ತರ್ಭಾವ <windows.h>
#ಅನ್ತರ್ಭಾವ <share.h>
#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ "wchar_filename.h"

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ win32_open(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *filename_utf8, ಪೂರ್ಣಾಂಕ oflag, ಪೂರ್ಣಾಂಕ pmode)
{
    ಪೂರ್ಣಾಂಕ fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    ಆದರೆ (get_extended_win32_ಮಾರ್ಗ(filename_utf8, &filename_w))
        ಹಿಂತಿರುಗಿ -1;
    ಆದರೆ (!filename_w)
        ಹೋಗು fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    ಆದರೆ (fd != -1 || (oflag & O_CREAT))
        ಹಿಂತಿರುಗಿ fd;

fallback:
    /* filename may be in CP_ACP */
    ಹಿಂತಿರುಗಿ _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#ವ್ಯಾಖ್ಯಾನಿಸು open win32_open
#ಆದರೆ_ಅಂತ್ಯ

ಪೂರ್ಣಾಂಕ avpriv_open(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *filename, ಪೂರ್ಣಾಂಕ flags, ...)
{
    ಪೂರ್ಣಾಂಕ fd;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಬಹುಲಕ = 0;
    va_list ap;

    va_start(ap, flags);
    ಆದರೆ (flags & O_CREAT)
        ಬಹುಲಕ = va_arg(ap, ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ);
    va_end(ap);

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ O_CLOEXEC
    flags |= O_CLOEXEC;
#ಆದರೆ_ಅಂತ್ಯ
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ O_NOINHERIT
    flags |= O_NOINHERIT;
#ಆದರೆ_ಅಂತ್ಯ

    fd = open(filename, flags, ಬಹುಲಕ);
#ಆದರೆ HAVE_FCNTL
    ಆದರೆ (fd != -1) {
        ಆದರೆ (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(ಖಾಲಿ, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಹಿಂತಿರುಗಿ fd;
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ FileLogContext {
    ಸ್ಥಿರಾಂಕ AVClass *class;
    ಪೂರ್ಣಾಂಕ   log_ಸ್ಥಾನಾಂತರ;
    ಶೂನ್ಯ *log_ctx;
} FileLogContext;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .ಅಂಶ_name                 = av_default_ಅಂಶ_name,
    .option                    = ಖಾಲಿ,
    .ಆವೃತ್ತಿ                   = LIBAVUTIL_ಆವೃತ್ತಿ_INT,
    .log_level_ಸ್ಥಾನಾಂತರ_ಸ್ಥಾನಾಂತರ   = offsetof(FileLogContext, log_ಸ್ಥಾನಾಂತರ),
    .ಪೋಷಕ_log_context_ಸ್ಥಾನಾಂತರ = offsetof(FileLogContext, log_ctx),
};

ಪೂರ್ಣಾಂಕ avpriv_tempfile(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಪೂರ್ವಪ್ರತ್ಯಯ, ಅಕ್ಷರ **filename, ಪೂರ್ಣಾಂಕ log_ಸ್ಥಾನಾಂತರ, ಶೂನ್ಯ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_ಸ್ಥಾನಾಂತರ, log_ctx };
    ಪೂರ್ಣಾಂಕ fd = -1;
#ಆದರೆ HAVE_MKSTEMP
    size_t len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(ಪೂರ್ವಪ್ರತ್ಯಯ) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#ಅಥವಾಆದರೆ HAVE_TEMPNAM
    ಶೂನ್ಯ *ptr= tempnam(ಖಾಲಿ, ಪೂರ್ವಪ್ರತ್ಯಯ);
    ಆದರೆ(!ptr)
        ptr= tempnam(".", ಪೂರ್ವಪ್ರತ್ಯಯ);
    *filename = av_strdup(ptr);
    ಬಿಡುಗಡೆ(ptr);
#ಇಲ್ಲದಿದ್ದರೆ
    ಹಿಂತಿರುಗಿ AVERROR(ENOSYS);
#ಆದರೆ_ಅಂತ್ಯ
    /* -----common section-----*/
    ಆದರೆ (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        ಹಿಂತಿರುಗಿ AVERROR(ENOMEM);
    }
#ಆದರೆ !HAVE_MKSTEMP
#   ifndef O_ದ್ವಿಮಾನ
#       define O_ದ್ವಿಮಾನ 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_ದ್ವಿಮಾನ | O_CREAT | O_EXCL, 0600);
#ಇಲ್ಲದಿದ್ದರೆ
    snprintf(*filename, len, "/tmp/%sXXXXXX", ಪೂರ್ವಪ್ರತ್ಯಯ);
    fd = mkstemp(*filename);
#ಆದರೆ defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    ಆದರೆ (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", ಪೂರ್ವಪ್ರತ್ಯಯ);
        fd = mkstemp(*filename);
    }
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ
    /* -----common section-----*/
    ಆದರೆ (fd < 0) {
        ಪೂರ್ಣಾಂಕ err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        ಹಿಂತಿರುಗಿ err;
    }
    ಹಿಂತಿರುಗಿ fd; /* success */
}

FILE *avpriv_fopen_utf8(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಮಾರ್ಗ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಹುಲಕ)
{
    ಪೂರ್ಣಾಂಕ fd;
    ಪೂರ್ಣಾಂಕ access;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *m = ಬಹುಲಕ;

    ಆಯ್ಕೆ (*m++) {
    ಸ್ಥಿತಿ 'r': access = O_RDONLY; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 'w': access = O_CREAT|O_WRONLY|O_TRUNC; ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 'a': access = O_CREAT|O_WRONLY|O_APPEND; ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ :
        errno = EINVAL;
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಆಗ (*m) {
        ಆದರೆ (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*m == 'b') {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ O_ದ್ವಿಮಾನ
            access |= O_ದ್ವಿಮಾನ;
#ಆದರೆ_ಅಂತ್ಯ
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (*m) {
            errno = EINVAL;
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        m++;
    }
    fd = avpriv_open(ಮಾರ್ಗ, access, 0666);
    ಆದರೆ (fd == -1)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಹಿಂತಿರುಗಿ fdopen(fd, ಬಹುಲಕ);
}

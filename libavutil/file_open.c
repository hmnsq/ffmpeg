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

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "avutil.h"
#অন্তর্ভাৱ "file_open.h"
#অন্তর্ভাৱ "mem.h"
#অন্তর্ভাৱ <stdarg.h>
#অন্তর্ভাৱ <fcntl.h>
#অন্তর্ভাৱ <sys/stat.h>
#যদি HAVE_UNISTD_H
#অন্তর্ভাৱ <unistd.h>
#endif
#যদি HAVE_IO_H
#অন্তর্ভাৱ <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#অন্তর্ভাৱ <windows.h>
#অন্তর্ভাৱ <share.h>
#অন্তর্ভাৱ <errno.h>
#অন্তর্ভাৱ "wchar_filename.h"

স্থির পূর্ণাঙ্ক win32_open(ধ্রুৱ ৱর্ণ *filename_utf8, পূর্ণাঙ্ক oflag, পূর্ণাঙ্ক pmode)
{
    পূর্ণাঙ্ক fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    যদি (get_extended_win32_path(filename_utf8, &filename_w))
        ঘূৰাই -1;
    যদি (!filename_w)
        গচ্ছ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    যদি (fd != -1 || (oflag & O_CREAT))
        ঘূৰাই fd;

fallback:
    /* filename may be in CP_ACP */
    ঘূৰাই _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

পূর্ণাঙ্ক avpriv_open(ধ্রুৱ ৱর্ণ *filename, পূর্ণাঙ্ক flags, ...)
{
    পূর্ণাঙ্ক fd;
    unsigned পূর্ণাঙ্ক mode = 0;
    va_list ap;

    va_start(ap, flags);
    যদি (flags & O_CREAT)
        mode = va_arg(ap, unsigned পূর্ণাঙ্ক);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#যদি HAVE_FCNTL
    যদি (fd != -1) {
        যদি (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(রিক্ত, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    ঘূৰাই fd;
}

প্রকারনির্দেশ সংরচনা FileLogContext {
    ধ্রুৱ AVClass *class;
    পূর্ণাঙ্ক   log_offset;
    শূন্য *log_ctx;
} FileLogContext;

স্থির ধ্রুৱ AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = রিক্ত,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

পূর্ণাঙ্ক avpriv_tempfile(ধ্রুৱ ৱর্ণ *prefix, ৱর্ণ **filename, পূর্ণাঙ্ক log_offset, শূন্য *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    পূর্ণাঙ্ক fd = -1;
#যদি HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#নোচেদ্যদি HAVE_TEMPNAM
    শূন্য *ptr= tempnam(রিক্ত, prefix);
    যদি(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    মুক্ত(ptr);
#অন্যথা
    ঘূৰাই AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    যদি (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        ঘূৰাই AVERROR(ENOMEM);
    }
#যদি !HAVE_MKSTEMP
#   ifndef O_দ্বিমিক
#       define O_দ্বিমিক 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_দ্বিমিক | O_CREAT | O_EXCL, 0600);
#অন্যথা
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#যদি defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    যদি (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    যদি (fd < 0) {
        পূর্ণাঙ্ক err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        ঘূৰাই err;
    }
    ঘূৰাই fd; /* success */
}

FILE *avpriv_fopen_utf8(ধ্রুৱ ৱর্ণ *path, ধ্রুৱ ৱর্ণ *mode)
{
    পূর্ণাঙ্ক fd;
    পূর্ণাঙ্ক access;
    ধ্রুৱ ৱর্ণ *m = mode;

    ৱিকল্প (*m++) {
    পক্ষ 'r': access = O_RDONLY; ভঙ্গ;
    পক্ষ 'w': access = O_CREAT|O_WRONLY|O_TRUNC; ভঙ্গ;
    পক্ষ 'a': access = O_CREAT|O_WRONLY|O_APPEND; ভঙ্গ;
    স্ৱভাৱ :
        errno = EINVAL;
        ঘূৰাই রিক্ত;
    }
    যেতিয়ালৈ (*m) {
        যদি (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } অন্যথা যদি (*m == 'b') {
#ifdef O_দ্বিমিক
            access |= O_দ্বিমিক;
#endif
        } অন্যথা যদি (*m) {
            errno = EINVAL;
            ঘূৰাই রিক্ত;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    যদি (fd == -1)
        ঘূৰাই রিক্ত;
    ঘূৰাই fdopen(fd, mode);
}

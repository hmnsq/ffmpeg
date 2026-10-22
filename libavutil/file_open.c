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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "avutil.h"
#অন্তর্ভাব "file_open.h"
#অন্তর্ভাব "mem.h"
#অন্তর্ভাব <stdarg.h>
#অন্তর্ভাব <fcntl.h>
#অন্তর্ভাব <sys/stat.h>
#যদি HAVE_UNISTD_H
#অন্তর্ভাব <unistd.h>
#endif
#যদি HAVE_IO_H
#অন্তর্ভাব <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#অন্তর্ভাব <windows.h>
#অন্তর্ভাব <share.h>
#অন্তর্ভাব <errno.h>
#অন্তর্ভাব "wchar_filename.h"

স্থির পূর্ণসংখ্যা win32_open(ধ্রুবক অক্ষর *filename_utf8, পূর্ণসংখ্যা oflag, পূর্ণসংখ্যা pmode)
{
    পূর্ণসংখ্যা fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    যদি (get_extended_win32_path(filename_utf8, &filename_w))
        ফেরত -1;
    যদি (!filename_w)
        যাও fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    যদি (fd != -1 || (oflag & O_CREAT))
        ফেরত fd;

fallback:
    /* filename may be in CP_ACP */
    ফেরত _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

পূর্ণসংখ্যা avpriv_open(ধ্রুবক অক্ষর *filename, পূর্ণসংখ্যা flags, ...)
{
    পূর্ণসংখ্যা fd;
    unsigned পূর্ণসংখ্যা mode = 0;
    va_list ap;

    va_start(ap, flags);
    যদি (flags & O_CREAT)
        mode = va_arg(ap, unsigned পূর্ণসংখ্যা);
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
            av_log(ফাঁকা, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    ফেরত fd;
}

প্রকারলেখ কাঠামো FileLogContext {
    ধ্রুবক AVClass *class;
    পূর্ণসংখ্যা   log_offset;
    শূন্য *log_ctx;
} FileLogContext;

স্থির ধ্রুবক AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = ফাঁকা,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

পূর্ণসংখ্যা avpriv_tempfile(ধ্রুবক অক্ষর *prefix, অক্ষর **filename, পূর্ণসংখ্যা log_offset, শূন্য *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    পূর্ণসংখ্যা fd = -1;
#যদি HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#নতুবা_যদি HAVE_TEMPNAM
    শূন্য *ptr= tempnam(ফাঁকা, prefix);
    যদি(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    মুক্ত(ptr);
#অন্যথা
    ফেরত AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    যদি (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        ফেরত AVERROR(ENOMEM);
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
        পূর্ণসংখ্যা err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        ফেরত err;
    }
    ফেরত fd; /* success */
}

FILE *avpriv_fopen_utf8(ধ্রুবক অক্ষর *path, ধ্রুবক অক্ষর *mode)
{
    পূর্ণসংখ্যা fd;
    পূর্ণসংখ্যা access;
    ধ্রুবক অক্ষর *m = mode;

    নির্বাচন (*m++) {
    ক্ষেত্র 'r': access = O_RDONLY; বিরতি;
    ক্ষেত্র 'w': access = O_CREAT|O_WRONLY|O_TRUNC; বিরতি;
    ক্ষেত্র 'a': access = O_CREAT|O_WRONLY|O_APPEND; বিরতি;
    পূর্বনির্ধারিত :
        errno = EINVAL;
        ফেরত ফাঁকা;
    }
    যখন (*m) {
        যদি (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } অন্যথা যদি (*m == 'b') {
#ifdef O_দ্বিমিক
            access |= O_দ্বিমিক;
#endif
        } অন্যথা যদি (*m) {
            errno = EINVAL;
            ফেরত ফাঁকা;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    যদি (fd == -1)
        ফেরত ফাঁকা;
    ফেরত fdopen(fd, mode);
}

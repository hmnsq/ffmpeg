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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "avutil.h"
#ଅନ୍ତର୍ଭାଵ "file_open.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"
#ଅନ୍ତର୍ଭାଵ <stdarg.h>
#ଅନ୍ତର୍ଭାଵ <fcntl.h>
#ଅନ୍ତର୍ଭାଵ <sys/stat.h>
#ଯଦି HAVE_UNISTD_H
#ଅନ୍ତର୍ଭାଵ <unistd.h>
#endif
#ଯଦି HAVE_IO_H
#ଅନ୍ତର୍ଭାଵ <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#ଅନ୍ତର୍ଭାଵ <windows.h>
#ଅନ୍ତର୍ଭାଵ <share.h>
#ଅନ୍ତର୍ଭାଵ <errno.h>
#ଅନ୍ତର୍ଭାଵ "wchar_filename.h"

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା win32_open(ଅଚଳ ଅକ୍ଷର *filename_utf8, ପୂର୍ଣ୍ଣସଂଖ୍ୟା oflag, ପୂର୍ଣ୍ଣସଂଖ୍ୟା pmode)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    ଯଦି (get_extended_win32_path(filename_utf8, &filename_w))
        ଫେରନ୍ତୁ -1;
    ଯଦି (!filename_w)
        ଯାଅ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    ଯଦି (fd != -1 || (oflag & O_CREAT))
        ଫେରନ୍ତୁ fd;

fallback:
    /* filename may be in CP_ACP */
    ଫେରନ୍ତୁ _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

ପୂର୍ଣ୍ଣସଂଖ୍ୟା avpriv_open(ଅଚଳ ଅକ୍ଷର *filename, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags, ...)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd;
    unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା mode = 0;
    va_list ap;

    va_start(ap, flags);
    ଯଦି (flags & O_CREAT)
        mode = va_arg(ap, unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#ଯଦି HAVE_FCNTL
    ଯଦି (fd != -1) {
        ଯଦି (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(ଖାଲି, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    ଫେରନ୍ତୁ fd;
}

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା FileLogContext {
    ଅଚଳ AVClass *class;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା   log_offset;
    ଶୂନ୍ୟ *log_ctx;
} FileLogContext;

ସ୍ଥିର ଅଚଳ AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = ଖାଲି,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

ପୂର୍ଣ୍ଣସଂଖ୍ୟା avpriv_tempfile(ଅଚଳ ଅକ୍ଷର *prefix, ଅକ୍ଷର **filename, ପୂର୍ଣ୍ଣସଂଖ୍ୟା log_offset, ଶୂନ୍ୟ *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd = -1;
#ଯଦି HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#ନଚେତଯଦି HAVE_TEMPNAM
    ଶୂନ୍ୟ *ptr= tempnam(ଖାଲି, prefix);
    ଯଦି(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    ମୁକ୍ତ(ptr);
#ଅନ୍ୟଥା
    ଫେରନ୍ତୁ AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    ଯଦି (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        ଫେରନ୍ତୁ AVERROR(ENOMEM);
    }
#ଯଦି !HAVE_MKSTEMP
#   ifndef O_ଦ୍ୱିମିକ
#       define O_ଦ୍ୱିମିକ 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_ଦ୍ୱିମିକ | O_CREAT | O_EXCL, 0600);
#ଅନ୍ୟଥା
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#ଯଦି defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    ଯଦି (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    ଯଦି (fd < 0) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        ଫେରନ୍ତୁ err;
    }
    ଫେରନ୍ତୁ fd; /* success */
}

FILE *avpriv_fopen_utf8(ଅଚଳ ଅକ୍ଷର *path, ଅଚଳ ଅକ୍ଷର *mode)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା fd;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା access;
    ଅଚଳ ଅକ୍ଷର *m = mode;

    ବାଛ (*m++) {
    ସ୍ଥିତି 'r': access = O_RDONLY; ଭାଙ୍ଗ;
    ସ୍ଥିତି 'w': access = O_CREAT|O_WRONLY|O_TRUNC; ଭାଙ୍ଗ;
    ସ୍ଥିତି 'a': access = O_CREAT|O_WRONLY|O_APPEND; ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ :
        errno = EINVAL;
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଯେତେବେଳେ (*m) {
        ଯଦି (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } ଅନ୍ୟଥା ଯଦି (*m == 'b') {
#ifdef O_ଦ୍ୱିମିକ
            access |= O_ଦ୍ୱିମିକ;
#endif
        } ଅନ୍ୟଥା ଯଦି (*m) {
            errno = EINVAL;
            ଫେରନ୍ତୁ ଖାଲି;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    ଯଦି (fd == -1)
        ଫେରନ୍ତୁ ଖାଲି;
    ଫେରନ୍ତୁ fdopen(fd, mode);
}

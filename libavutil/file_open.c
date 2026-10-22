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

#अन्तर्भाव "config.h"
#अन्तर्भाव "avutil.h"
#अन्तर्भाव "file_open.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव <stdarg.h>
#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <sys/stat.h>
#सचे HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#सचे HAVE_IO_H
#अन्तर्भाव <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#अन्तर्भाव <windows.h>
#अन्तर्भाव <share.h>
#अन्तर्भाव <errno.h>
#अन्तर्भाव "wchar_filename.h"

स्थिर पूर्णाङ्क win32_open(ध्रुव वर्ण *filename_utf8, पूर्णाङ्क oflag, पूर्णाङ्क pmode)
{
    पूर्णाङ्क fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    सचे (get_extended_win32_path(filename_utf8, &filename_w))
        पटिनिवत्त -1;
    सचे (!filename_w)
        गच्छ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    सचे (fd != -1 || (oflag & O_CREAT))
        पटिनिवत्त fd;

fallback:
    /* filename may be in CP_ACP */
    पटिनिवत्त _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

पूर्णाङ्क avpriv_open(ध्रुव वर्ण *filename, पूर्णाङ्क flags, ...)
{
    पूर्णाङ्क fd;
    unsigned पूर्णाङ्क mode = 0;
    va_list ap;

    va_start(ap, flags);
    सचे (flags & O_CREAT)
        mode = va_arg(ap, unsigned पूर्णाङ्क);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#सचे HAVE_FCNTL
    सचे (fd != -1) {
        सचे (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(रिक्त, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    पटिनिवत्त fd;
}

प्रकारनिर्देश संरचना FileLogContext {
    ध्रुव AVClass *class;
    पूर्णाङ्क   log_offset;
    शून्य *log_ctx;
} FileLogContext;

स्थिर ध्रुव AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

पूर्णाङ्क avpriv_tempfile(ध्रुव वर्ण *prefix, वर्ण **filename, पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    पूर्णाङ्क fd = -1;
#सचे HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#नोचेद्यदि HAVE_TEMPNAM
    शून्य *ptr= tempnam(रिक्त, prefix);
    सचे(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    मुक्त(ptr);
#अञ्ञथा
    पटिनिवत्त AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    सचे (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        पटिनिवत्त AVERROR(ENOMEM);
    }
#सचे !HAVE_MKSTEMP
#   ifndef O_द्विमान
#       define O_द्विमान 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_द्विमान | O_CREAT | O_EXCL, 0600);
#अञ्ञथा
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#सचे defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    सचे (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    सचे (fd < 0) {
        पूर्णाङ्क err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        पटिनिवत्त err;
    }
    पटिनिवत्त fd; /* success */
}

FILE *avpriv_fopen_utf8(ध्रुव वर्ण *path, ध्रुव वर्ण *mode)
{
    पूर्णाङ्क fd;
    पूर्णाङ्क access;
    ध्रुव वर्ण *m = mode;

    विकल्प (*m++) {
    पक्ष 'r': access = O_RDONLY; भङ्ग;
    पक्ष 'w': access = O_CREAT|O_WRONLY|O_TRUNC; भङ्ग;
    पक्ष 'a': access = O_CREAT|O_WRONLY|O_APPEND; भङ्ग;
    स्वभाव :
        errno = EINVAL;
        पटिनिवत्त रिक्त;
    }
    याव (*m) {
        सचे (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } अञ्ञथा सचे (*m == 'b') {
#ifdef O_द्विमान
            access |= O_द्विमान;
#endif
        } अञ्ञथा सचे (*m) {
            errno = EINVAL;
            पटिनिवत्त रिक्त;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    सचे (fd == -1)
        पटिनिवत्त रिक्त;
    पटिनिवत्त fdopen(fd, mode);
}

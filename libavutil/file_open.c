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
#यदि HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#यदि_अन्तः
#यदि HAVE_IO_H
#अन्तर्भाव <io.h>
#यदि_अन्तः

#यदि_परिभाषितम् _WIN32
#अपरिभाषय उद्घाटय
#अपरिभाषय lseek
#अपरिभाषय stat
#अपरिभाषय fstat
#अन्तर्भाव <windows.h>
#अन्तर्भाव <share.h>
#अन्तर्भाव <errno.h>
#अन्तर्भाव "wchar_filename.h"

स्थिर पूर्णाङ्क win32_open(ध्रुव वर्ण *filename_utf8, पूर्णाङ्क oflag, पूर्णाङ्क pmode)
{
    पूर्णाङ्क fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    यदि (get_extended_win32_मार्गः(filename_utf8, &filename_w))
        प्रत्यागम -1;
    यदि (!filename_w)
        गच्छ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    यदि (fd != -1 || (oflag & O_CREAT))
        प्रत्यागम fd;

fallback:
    /* filename may be in CP_ACP */
    प्रत्यागम _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#परिभाषय उद्घाटय win32_open
#यदि_अन्तः

पूर्णाङ्क avpriv_open(ध्रुव वर्ण *filename, पूर्णाङ्क flags, ...)
{
    पूर्णाङ्क fd;
    अचिह्नित पूर्णाङ्क बहुलकम् = 0;
    va_list ap;

    va_start(ap, flags);
    यदि (flags & O_CREAT)
        बहुलकम् = va_arg(ap, अचिह्नित पूर्णाङ्क);
    va_end(ap);

#यदि_परिभाषितम् O_CLOEXEC
    flags |= O_CLOEXEC;
#यदि_अन्तः
#यदि_परिभाषितम् O_NOINHERIT
    flags |= O_NOINHERIT;
#यदि_अन्तः

    fd = उद्घाटय(filename, flags, बहुलकम्);
#यदि HAVE_FCNTL
    यदि (fd != -1) {
        यदि (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(रिक्त, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#यदि_अन्तः

    प्रत्यागम fd;
}

प्रकारनिर्देश संरचना FileLogContext {
    ध्रुव AVClass *class;
    पूर्णाङ्क   log_विस्थापनम्;
    शून्य *log_ctx;
} FileLogContext;

स्थिर ध्रुव AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .संस्करणम्                   = LIBAVUTIL_संस्करणम्_INT,
    .log_level_विस्थापनम्_विस्थापनम्   = offsetof(FileLogContext, log_विस्थापनम्),
    .parent_log_context_विस्थापनम् = offsetof(FileLogContext, log_ctx),
};

पूर्णाङ्क avpriv_tempfile(ध्रुव वर्ण *उपसर्गः, वर्ण **filename, पूर्णाङ्क log_विस्थापनम्, शून्य *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_विस्थापनम्, log_ctx };
    पूर्णाङ्क fd = -1;
#यदि HAVE_MKSTEMP
    size_t len = वाक्यदैर्घ्यम्(उपसर्गः) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#नोचेद्यदि HAVE_TEMPNAM
    शून्य *ptr= tempnam(रिक्त, उपसर्गः);
    यदि(!ptr)
        ptr= tempnam(".", उपसर्गः);
    *filename = av_strdup(ptr);
    मुक्त(ptr);
#अन्यथा
    प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः
    /* -----common section-----*/
    यदि (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        प्रत्यागम AVERROR(ENOMEM);
    }
#यदि !HAVE_MKSTEMP
#   ifndef O_द्विमान
#       define O_द्विमान 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = उद्घाटय(*filename, O_RDWR | O_द्विमान | O_CREAT | O_EXCL, 0600);
#अन्यथा
    snprintf(*filename, len, "/tmp/%sXXXXXX", उपसर्गः);
    fd = mkstemp(*filename);
#यदि defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    यदि (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", उपसर्गः);
        fd = mkstemp(*filename);
    }
#यदि_अन्तः
#यदि_अन्तः
    /* -----common section-----*/
    यदि (fd < 0) {
        पूर्णाङ्क err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        प्रत्यागम err;
    }
    प्रत्यागम fd; /* success */
}

FILE *avpriv_fopen_utf8(ध्रुव वर्ण *मार्गः, ध्रुव वर्ण *बहुलकम्)
{
    पूर्णाङ्क fd;
    पूर्णाङ्क access;
    ध्रुव वर्ण *m = बहुलकम्;

    विकल्प (*m++) {
    पक्ष 'r': access = O_RDONLY; भङ्ग;
    पक्ष 'w': access = O_CREAT|O_WRONLY|O_TRUNC; भङ्ग;
    पक्ष 'a': access = O_CREAT|O_WRONLY|O_APPEND; भङ्ग;
    स्वभाव :
        errno = EINVAL;
        प्रत्यागम रिक्त;
    }
    यावत् (*m) {
        यदि (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } अन्यथा यदि (*m == 'b') {
#यदि_परिभाषितम् O_द्विमान
            access |= O_द्विमान;
#यदि_अन्तः
        } अन्यथा यदि (*m) {
            errno = EINVAL;
            प्रत्यागम रिक्त;
        }
        m++;
    }
    fd = avpriv_open(मार्गः, access, 0666);
    यदि (fd == -1)
        प्रत्यागम रिक्त;
    प्रत्यागम fdopen(fd, बहुलकम्);
}

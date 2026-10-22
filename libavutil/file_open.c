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
#endif
#यदि HAVE_IO_H
#अन्तर्भाव <io.h>
#endif

#ifdef _WIN32
#undef खोलो
#undef lseek
#undef stat
#undef ख_स्थिति
#अन्तर्भाव <windows.h>
#अन्तर्भाव <share.h>
#अन्तर्भाव <errno.h>
#अन्तर्भाव "wchar_filename.h"

स्थिर पूर्णाङ्क win32_open(अचर वर्ण *filename_utf8, पूर्णाङ्क oflag, पूर्णाङ्क pmode)
{
    पूर्णाङ्क fd;
    ब_अक्षर_प्रकार *filename_w;

    /* convert UTF-8 to wide chars */
    यदि (get_extended_win32_path(filename_utf8, &filename_w))
        फर्काऊ -1;
    यदि (!filename_w)
        गच्छ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    यदि (fd != -1 || (oflag & O_CREAT))
        फर्काऊ fd;

fallback:
    /* filename may be in CP_ACP */
    फर्काऊ _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define खोलो win32_open
#endif

पूर्णाङ्क avpriv_open(अचर वर्ण *filename, पूर्णाङ्क flags, ...)
{
    पूर्णाङ्क fd;
    अचिन्हित पूर्णाङ्क mode = 0;
    बहु_सूची ap;

    बहु_शुरू(ap, flags);
    यदि (flags & O_CREAT)
        mode = बहु_तर्क(ap, अचिन्हित पूर्णाङ्क);
    बहु_पूर्ण(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = खोलो(filename, flags, mode);
#यदि HAVE_FCNTL
    यदि (fd != -1) {
        यदि (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(रिक्त, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    फर्काऊ fd;
}

प्रकारनिर्देश संरचना FileLogContext {
    अचर AVClass *class;
    पूर्णाङ्क   log_offset;
    शून्य *log_ctx;
} FileLogContext;

स्थिर अचर AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(FileLogContext, log_offset),
    .parent_log_context_offset = दुरत्व(FileLogContext, log_ctx),
};

पूर्णाङ्क avpriv_tempfile(अचर वर्ण *prefix, वर्ण **filename, पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    पूर्णाङ्क fd = -1;
#यदि HAVE_MKSTEMP
    माप_प्रकार len = म_माप(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#अथवायदि HAVE_TEMPNAM
    शून्य *ptr= tempnam(रिक्त, prefix);
    यदि(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    मुक्त(ptr);
#अन्यथा
    फर्काऊ AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    यदि (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        फर्काऊ AVERROR(ENOMEM);
    }
#यदि !HAVE_MKSTEMP
#   ifndef O_द्विआधारी
#       define O_द्विआधारी 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = खोलो(*filename, O_RDWR | O_द्विआधारी | O_CREAT | O_EXCL, 0600);
#अन्यथा
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#यदि defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    यदि (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    यदि (fd < 0) {
        पूर्णाङ्क err = AVERROR(त्रुटि_सं);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        फर्काऊ err;
    }
    फर्काऊ fd; /* success */
}

खाता *avpriv_fopen_utf8(अचर वर्ण *path, अचर वर्ण *mode)
{
    पूर्णाङ्क fd;
    पूर्णाङ्क access;
    अचर वर्ण *m = mode;

    विकल्प (*m++) {
    पक्ष 'r': access = O_RDONLY; रोक;
    पक्ष 'w': access = O_CREAT|O_WRONLY|O_TRUNC; रोक;
    पक्ष 'a': access = O_CREAT|O_WRONLY|O_APPEND; रोक;
    स्वभाव :
        त्रुटि_सं = EINVAL;
        फर्काऊ रिक्त;
    }
    जबसम्म (*m) {
        यदि (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } अन्यथा यदि (*m == 'b') {
#ifdef O_द्विआधारी
            access |= O_द्विआधारी;
#endif
        } अन्यथा यदि (*m) {
            त्रुटि_सं = EINVAL;
            फर्काऊ रिक्त;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    यदि (fd == -1)
        फर्काऊ रिक्त;
    फर्काऊ fdopen(fd, mode);
}

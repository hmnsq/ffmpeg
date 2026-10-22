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
#जर HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#जर HAVE_IO_H
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

स्थिर पूर्णांक win32_open(स्थिरांक अक्षर *filename_utf8, पूर्णांक oflag, पूर्णांक pmode)
{
    पूर्णांक fd;
    ब_अक्षर_प्रकार *filename_w;

    /* convert UTF-8 to wide chars */
    जर (get_extended_win32_path(filename_utf8, &filename_w))
        परत -1;
    जर (!filename_w)
        जा fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    जर (fd != -1 || (oflag & O_CREAT))
        परत fd;

fallback:
    /* filename may be in CP_ACP */
    परत _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define खोलो win32_open
#endif

पूर्णांक avpriv_open(स्थिरांक अक्षर *filename, पूर्णांक flags, ...)
{
    पूर्णांक fd;
    अचिन्हित पूर्णांक mode = 0;
    बहु_सूची ap;

    बहु_शुरू(ap, flags);
    जर (flags & O_CREAT)
        mode = बहु_तर्क(ap, अचिन्हित पूर्णांक);
    बहु_पूर्ण(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = खोलो(filename, flags, mode);
#जर HAVE_FCNTL
    जर (fd != -1) {
        जर (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(रिक्त, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    परत fd;
}

प्रकारव्याख्या संरचना FileLogContext {
    स्थिरांक AVClass *class;
    पूर्णांक   log_offset;
    शून्य *log_ctx;
} FileLogContext;

स्थिर स्थिरांक AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(FileLogContext, log_offset),
    .parent_log_context_offset = दुरत्व(FileLogContext, log_ctx),
};

पूर्णांक avpriv_tempfile(स्थिरांक अक्षर *prefix, अक्षर **filename, पूर्णांक log_offset, शून्य *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    पूर्णांक fd = -1;
#जर HAVE_MKSTEMP
    माप_प्रकार len = म_माप(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#किंवाजर HAVE_TEMPNAM
    शून्य *ptr= tempnam(रिक्त, prefix);
    जर(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    मुक्त(ptr);
#अन्यथा
    परत AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    जर (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        परत AVERROR(ENOMEM);
    }
#जर !HAVE_MKSTEMP
#   ifndef O_द्विमान
#       define O_द्विमान 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = खोलो(*filename, O_RDWR | O_द्विमान | O_CREAT | O_EXCL, 0600);
#अन्यथा
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#जर defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    जर (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    जर (fd < 0) {
        पूर्णांक err = AVERROR(त्रुटि_सं);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        परत err;
    }
    परत fd; /* success */
}

खाता *avpriv_fopen_utf8(स्थिरांक अक्षर *path, स्थिरांक अक्षर *mode)
{
    पूर्णांक fd;
    पूर्णांक access;
    स्थिरांक अक्षर *m = mode;

    निवड (*m++) {
    स्थिती 'r': access = O_RDONLY; थांबा;
    स्थिती 'w': access = O_CREAT|O_WRONLY|O_TRUNC; थांबा;
    स्थिती 'a': access = O_CREAT|O_WRONLY|O_APPEND; थांबा;
    पूर्वनिर्धारित :
        त्रुटि_सं = EINVAL;
        परत रिक्त;
    }
    पर्यंत (*m) {
        जर (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } अन्यथा जर (*m == 'b') {
#ifdef O_द्विमान
            access |= O_द्विमान;
#endif
        } अन्यथा जर (*m) {
            त्रुटि_सं = EINVAL;
            परत रिक्त;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    जर (fd == -1)
        परत रिक्त;
    परत fdopen(fd, mode);
}

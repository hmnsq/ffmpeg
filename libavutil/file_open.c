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

#समावेश "config.h"
#समावेश "avutil.h"
#समावेश "file_open.h"
#समावेश "mem.h"
#समावेश <stdarg.h>
#समावेश <fcntl.h>
#समावेश <sys/stat.h>
#अगर HAVE_UNISTD_H
#समावेश <unistd.h>
#पूर्ण_अगर
#अगर HAVE_IO_H
#समावेश <io.h>
#पूर्ण_अगर

#अगर_घोषित _WIN32
#अघोषित खोलो
#अघोषित lseek
#अघोषित stat
#अघोषित ख_स्थिति
#समावेश <windows.h>
#समावेश <share.h>
#समावेश <errno.h>
#समावेश "wchar_filename.h"

अटल पूर्णांक win32_open(स्थिर अक्षर *filename_utf8, पूर्णांक oflag, पूर्णांक pmode)
{
    पूर्णांक fd;
    ब_अक्षर_प्रकार *filename_w;

    /* convert UTF-8 to wide chars */
    अगर (get_extended_win32_path(filename_utf8, &filename_w))
        वापस -1;
    अगर (!filename_w)
        जाओ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    अगर (fd != -1 || (oflag & O_CREAT))
        वापस fd;

fallback:
    /* filename may be in CP_ACP */
    वापस _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#घोषणा खोलो win32_open
#पूर्ण_अगर

पूर्णांक avpriv_open(स्थिर अक्षर *filename, पूर्णांक flags, ...)
{
    पूर्णांक fd;
    अचिन्हित पूर्णांक mode = 0;
    बहु_सूची ap;

    बहु_शुरू(ap, flags);
    अगर (flags & O_CREAT)
        mode = बहु_तर्क(ap, अचिन्हित पूर्णांक);
    बहु_पूर्ण(ap);

#अगर_घोषित O_CLOEXEC
    flags |= O_CLOEXEC;
#पूर्ण_अगर
#अगर_घोषित O_NOINHERIT
    flags |= O_NOINHERIT;
#पूर्ण_अगर

    fd = खोलो(filename, flags, mode);
#अगर HAVE_FCNTL
    अगर (fd != -1) {
        अगर (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(शून्य, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#पूर्ण_अगर

    वापस fd;
}

प्रकार काष्ठा FileLogContext {
    स्थिर AVClass *class;
    पूर्णांक   log_offset;
    व्योम *log_ctx;
} FileLogContext;

अटल स्थिर AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = शून्य,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(FileLogContext, log_offset),
    .parent_log_context_offset = दुरत्व(FileLogContext, log_ctx),
};

पूर्णांक avpriv_tempfile(स्थिर अक्षर *prefix, अक्षर **filename, पूर्णांक log_offset, व्योम *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    पूर्णांक fd = -1;
#अगर HAVE_MKSTEMP
    माप_प्रकार len = म_माप(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#या_अगर HAVE_TEMPNAM
    व्योम *ptr= tempnam(शून्य, prefix);
    अगर(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    मुक्त(ptr);
#अन्यथा
    वापस AVERROR(ENOSYS);
#पूर्ण_अगर
    /* -----common section-----*/
    अगर (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        वापस AVERROR(ENOMEM);
    }
#अगर !HAVE_MKSTEMP
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
#अगर defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    अगर (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#पूर्ण_अगर
#पूर्ण_अगर
    /* -----common section-----*/
    अगर (fd < 0) {
        पूर्णांक err = AVERROR(त्रुटि_सं);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        वापस err;
    }
    वापस fd; /* success */
}

खाता *avpriv_fopen_utf8(स्थिर अक्षर *path, स्थिर अक्षर *mode)
{
    पूर्णांक fd;
    पूर्णांक access;
    स्थिर अक्षर *m = mode;

    चयन (*m++) {
    हाल 'r': access = O_RDONLY; अवरोध;
    हाल 'w': access = O_CREAT|O_WRONLY|O_TRUNC; अवरोध;
    हाल 'a': access = O_CREAT|O_WRONLY|O_APPEND; अवरोध;
    शेष :
        त्रुटि_सं = EINVAL;
        वापस शून्य;
    }
    जबतक (*m) {
        अगर (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } अन्यथा अगर (*m == 'b') {
#अगर_घोषित O_द्विआधारी
            access |= O_द्विआधारी;
#पूर्ण_अगर
        } अन्यथा अगर (*m) {
            त्रुटि_सं = EINVAL;
            वापस शून्य;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    अगर (fd == -1)
        वापस शून्य;
    वापस fdopen(fd, mode);
}

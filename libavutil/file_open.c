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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "avutil.h"
#അന്തര്ഭാവ "file_open.h"
#അന്തര്ഭാവ "mem.h"
#അന്തര്ഭാവ <stdarg.h>
#അന്തര്ഭാവ <fcntl.h>
#അന്തര്ഭാവ <sys/stat.h>
#എങ്കിൽ HAVE_UNISTD_H
#അന്തര്ഭാവ <unistd.h>
#endif
#എങ്കിൽ HAVE_IO_H
#അന്തര്ഭാവ <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#അന്തര്ഭാവ <windows.h>
#അന്തര്ഭാവ <share.h>
#അന്തര്ഭാവ <errno.h>
#അന്തര്ഭാവ "wchar_filename.h"

സ്ഥിതം പൂർണ്ണസംഖ്യ win32_open(സ്ഥിരം അക്ഷരം *filename_utf8, പൂർണ്ണസംഖ്യ oflag, പൂർണ്ണസംഖ്യ pmode)
{
    പൂർണ്ണസംഖ്യ fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    എങ്കിൽ (get_extended_win32_path(filename_utf8, &filename_w))
        തിരികെ -1;
    എങ്കിൽ (!filename_w)
        പോകുക fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    എങ്കിൽ (fd != -1 || (oflag & O_CREAT))
        തിരികെ fd;

fallback:
    /* filename may be in CP_ACP */
    തിരികെ _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

പൂർണ്ണസംഖ്യ avpriv_open(സ്ഥിരം അക്ഷരം *filename, പൂർണ്ണസംഖ്യ flags, ...)
{
    പൂർണ്ണസംഖ്യ fd;
    unsigned പൂർണ്ണസംഖ്യ mode = 0;
    va_list ap;

    va_start(ap, flags);
    എങ്കിൽ (flags & O_CREAT)
        mode = va_arg(ap, unsigned പൂർണ്ണസംഖ്യ);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#എങ്കിൽ HAVE_FCNTL
    എങ്കിൽ (fd != -1) {
        എങ്കിൽ (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(ശൂന്യ, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    തിരികെ fd;
}

തരനിർവചനം ഘടന FileLogContext {
    സ്ഥിരം AVClass *class;
    പൂർണ്ണസംഖ്യ   log_offset;
    ശൂന്യം *log_ctx;
} FileLogContext;

സ്ഥിതം സ്ഥിരം AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = ശൂന്യ,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

പൂർണ്ണസംഖ്യ avpriv_tempfile(സ്ഥിരം അക്ഷരം *prefix, അക്ഷരം **filename, പൂർണ്ണസംഖ്യ log_offset, ശൂന്യം *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    പൂർണ്ണസംഖ്യ fd = -1;
#എങ്കിൽ HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#അല്ലെങ്കിലെങ്കിൽ HAVE_TEMPNAM
    ശൂന്യം *ptr= tempnam(ശൂന്യ, prefix);
    എങ്കിൽ(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    സ്വതന്ത്രം(ptr);
#അല്ലെങ്കിൽ
    തിരികെ AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    എങ്കിൽ (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        തിരികെ AVERROR(ENOMEM);
    }
#എങ്കിൽ !HAVE_MKSTEMP
#   ifndef O_ദ്വിമാന
#       define O_ദ്വിമാന 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_ദ്വിമാന | O_CREAT | O_EXCL, 0600);
#അല്ലെങ്കിൽ
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#എങ്കിൽ defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    എങ്കിൽ (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    എങ്കിൽ (fd < 0) {
        പൂർണ്ണസംഖ്യ err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        തിരികെ err;
    }
    തിരികെ fd; /* success */
}

FILE *avpriv_fopen_utf8(സ്ഥിരം അക്ഷരം *path, സ്ഥിരം അക്ഷരം *mode)
{
    പൂർണ്ണസംഖ്യ fd;
    പൂർണ്ണസംഖ്യ access;
    സ്ഥിരം അക്ഷരം *m = mode;

    തിരഞ്ഞെടുപ്പ് (*m++) {
    അവസ്ഥ 'r': access = O_RDONLY; നിർത്തുക;
    അവസ്ഥ 'w': access = O_CREAT|O_WRONLY|O_TRUNC; നിർത്തുക;
    അവസ്ഥ 'a': access = O_CREAT|O_WRONLY|O_APPEND; നിർത്തുക;
    സ്ഥിരസ്ഥിതി :
        errno = EINVAL;
        തിരികെ ശൂന്യ;
    }
    ആകുമ്പോൾ (*m) {
        എങ്കിൽ (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } അല്ലെങ്കിൽ എങ്കിൽ (*m == 'b') {
#ifdef O_ദ്വിമാന
            access |= O_ദ്വിമാന;
#endif
        } അല്ലെങ്കിൽ എങ്കിൽ (*m) {
            errno = EINVAL;
            തിരികെ ശൂന്യ;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    എങ്കിൽ (fd == -1)
        തിരികെ ശൂന്യ;
    തിരികെ fdopen(fd, mode);
}

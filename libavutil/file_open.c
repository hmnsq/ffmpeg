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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "avutil.h"
#அந்தர்பாவ "file_open.h"
#அந்தர்பாவ "mem.h"
#அந்தர்பாவ <stdarg.h>
#அந்தர்பாவ <fcntl.h>
#அந்தர்பாவ <sys/stat.h>
#எனில் HAVE_UNISTD_H
#அந்தர்பாவ <unistd.h>
#endif
#எனில் HAVE_IO_H
#அந்தர்பாவ <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#அந்தர்பாவ <windows.h>
#அந்தர்பாவ <share.h>
#அந்தர்பாவ <errno.h>
#அந்தர்பாவ "wchar_filename.h"

நிலையான முழு win32_open(மாறிலி எழுத்து *filename_utf8, முழு oflag, முழு pmode)
{
    முழு fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    எனில் (get_extended_win32_path(filename_utf8, &filename_w))
        திரும்பு -1;
    எனில் (!filename_w)
        செல் fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    எனில் (fd != -1 || (oflag & O_CREAT))
        திரும்பு fd;

fallback:
    /* filename may be in CP_ACP */
    திரும்பு _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

முழு avpriv_open(மாறிலி எழுத்து *filename, முழு flags, ...)
{
    முழு fd;
    unsigned முழு mode = 0;
    va_list ap;

    va_start(ap, flags);
    எனில் (flags & O_CREAT)
        mode = va_arg(ap, unsigned முழு);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#எனில் HAVE_FCNTL
    எனில் (fd != -1) {
        எனில் (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(வெற்று, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    திரும்பு fd;
}

வகைவரை கட்டமைப்பு FileLogContext {
    மாறிலி AVClass *class;
    முழு   log_offset;
    வெறுமை *log_ctx;
} FileLogContext;

நிலையான மாறிலி AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = வெற்று,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

முழு avpriv_tempfile(மாறிலி எழுத்து *prefix, எழுத்து **filename, முழு log_offset, வெறுமை *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    முழு fd = -1;
#எனில் HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#அல்லதெனில் HAVE_TEMPNAM
    வெறுமை *ptr= tempnam(வெற்று, prefix);
    எனில்(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    விடுவி(ptr);
#இல்லையெனில்
    திரும்பு AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    எனில் (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        திரும்பு AVERROR(ENOMEM);
    }
#எனில் !HAVE_MKSTEMP
#   ifndef O_இருமம்
#       define O_இருமம் 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_இருமம் | O_CREAT | O_EXCL, 0600);
#இல்லையெனில்
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#எனில் defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    எனில் (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    எனில் (fd < 0) {
        முழு err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        திரும்பு err;
    }
    திரும்பு fd; /* success */
}

FILE *avpriv_fopen_utf8(மாறிலி எழுத்து *path, மாறிலி எழுத்து *mode)
{
    முழு fd;
    முழு access;
    மாறிலி எழுத்து *m = mode;

    தேர்வு (*m++) {
    நிலை 'r': access = O_RDONLY; நிறுத்து;
    நிலை 'w': access = O_CREAT|O_WRONLY|O_TRUNC; நிறுத்து;
    நிலை 'a': access = O_CREAT|O_WRONLY|O_APPEND; நிறுத்து;
    இயல்பு :
        errno = EINVAL;
        திரும்பு வெற்று;
    }
    போது (*m) {
        எனில் (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } இல்லையெனில் எனில் (*m == 'b') {
#ifdef O_இருமம்
            access |= O_இருமம்;
#endif
        } இல்லையெனில் எனில் (*m) {
            errno = EINVAL;
            திரும்பு வெற்று;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    எனில் (fd == -1)
        திரும்பு வெற்று;
    திரும்பு fdopen(fd, mode);
}

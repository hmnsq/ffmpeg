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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "avutil.h"
#અન્તર્ભાવ "file_open.h"
#અન્તર્ભાવ "mem.h"
#અન્તર્ભાવ <stdarg.h>
#અન્તર્ભાવ <fcntl.h>
#અન્તર્ભાવ <sys/stat.h>
#જો HAVE_UNISTD_H
#અન્તર્ભાવ <unistd.h>
#endif
#જો HAVE_IO_H
#અન્તર્ભાવ <io.h>
#endif

#ifdef _WIN32
#undef open
#undef lseek
#undef stat
#undef fstat
#અન્તર્ભાવ <windows.h>
#અન્તર્ભાવ <share.h>
#અન્તર્ભાવ <errno.h>
#અન્તર્ભાવ "wchar_filename.h"

સ્થિર પૂર્ણાંક win32_open(અચલ અક્ષર *filename_utf8, પૂર્ણાંક oflag, પૂર્ણાંક pmode)
{
    પૂર્ણાંક fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    જો (get_extended_win32_path(filename_utf8, &filename_w))
        પાછા -1;
    જો (!filename_w)
        જાઓ fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    જો (fd != -1 || (oflag & O_CREAT))
        પાછા fd;

fallback:
    /* filename may be in CP_ACP */
    પાછા _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#define open win32_open
#endif

પૂર્ણાંક avpriv_open(અચલ અક્ષર *filename, પૂર્ણાંક flags, ...)
{
    પૂર્ણાંક fd;
    unsigned પૂર્ણાંક mode = 0;
    va_list ap;

    va_start(ap, flags);
    જો (flags & O_CREAT)
        mode = va_arg(ap, unsigned પૂર્ણાંક);
    va_end(ap);

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOINHERIT
    flags |= O_NOINHERIT;
#endif

    fd = open(filename, flags, mode);
#જો HAVE_FCNTL
    જો (fd != -1) {
        જો (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(ખાલી, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#endif

    પાછા fd;
}

પ્રકારવ્યાખ્યા સંરચના FileLogContext {
    અચલ AVClass *class;
    પૂર્ણાંક   log_offset;
    શૂન્ય *log_ctx;
} FileLogContext;

સ્થિર અચલ AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .item_name                 = av_default_item_name,
    .option                    = ખાલી,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

પૂર્ણાંક avpriv_tempfile(અચલ અક્ષર *prefix, અક્ષર **filename, પૂર્ણાંક log_offset, શૂન્ય *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    પૂર્ણાંક fd = -1;
#જો HAVE_MKSTEMP
    size_t len = strlen(prefix) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#અથવાજો HAVE_TEMPNAM
    શૂન્ય *ptr= tempnam(ખાલી, prefix);
    જો(!ptr)
        ptr= tempnam(".", prefix);
    *filename = av_strdup(ptr);
    મુક્ત(ptr);
#નહીંતર
    પાછા AVERROR(ENOSYS);
#endif
    /* -----common section-----*/
    જો (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        પાછા AVERROR(ENOMEM);
    }
#જો !HAVE_MKSTEMP
#   ifndef O_દ્વિઅંકી
#       define O_દ્વિઅંકી 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_દ્વિઅંકી | O_CREAT | O_EXCL, 0600);
#નહીંતર
    snprintf(*filename, len, "/tmp/%sXXXXXX", prefix);
    fd = mkstemp(*filename);
#જો defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    જો (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", prefix);
        fd = mkstemp(*filename);
    }
#endif
#endif
    /* -----common section-----*/
    જો (fd < 0) {
        પૂર્ણાંક err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        પાછા err;
    }
    પાછા fd; /* success */
}

FILE *avpriv_fopen_utf8(અચલ અક્ષર *path, અચલ અક્ષર *mode)
{
    પૂર્ણાંક fd;
    પૂર્ણાંક access;
    અચલ અક્ષર *m = mode;

    પસંદગી (*m++) {
    સ્થિતિ 'r': access = O_RDONLY; તોડો;
    સ્થિતિ 'w': access = O_CREAT|O_WRONLY|O_TRUNC; તોડો;
    સ્થિતિ 'a': access = O_CREAT|O_WRONLY|O_APPEND; તોડો;
    મૂળભૂત :
        errno = EINVAL;
        પાછા ખાલી;
    }
    જ્યારે (*m) {
        જો (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } નહીંતર જો (*m == 'b') {
#ifdef O_દ્વિઅંકી
            access |= O_દ્વિઅંકી;
#endif
        } નહીંતર જો (*m) {
            errno = EINVAL;
            પાછા ખાલી;
        }
        m++;
    }
    fd = avpriv_open(path, access, 0666);
    જો (fd == -1)
        પાછા ખાલી;
    પાછા fdopen(fd, mode);
}

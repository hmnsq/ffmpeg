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

#అన్తర్భావ "config.h"
#అన్తర్భావ "avutil.h"
#అన్తర్భావ "file_open.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ <stdarg.h>
#అన్తర్భావ <fcntl.h>
#అన్తర్భావ <sys/stat.h>
#ఒకవేళ HAVE_UNISTD_H
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_IO_H
#అన్తర్భావ <io.h>
#అయితే_ముగింపు

#నిర్వచితమైతే _WIN32
#నిర్వచనం_రద్దు open
#నిర్వచనం_రద్దు lseek
#నిర్వచనం_రద్దు stat
#నిర్వచనం_రద్దు fstat
#అన్తర్భావ <windows.h>
#అన్తర్భావ <share.h>
#అన్తర్భావ <errno.h>
#అన్తర్భావ "wchar_filename.h"

స్థిర పూర్ణాంకం win32_open(స్థిరరాశి అక్షరం *filename_utf8, పూర్ణాంకం oflag, పూర్ణాంకం pmode)
{
    పూర్ణాంకం fd;
    wchar_t *filename_w;

    /* convert UTF-8 to wide chars */
    ఒకవేళ (get_extended_win32_మార్గం(filename_utf8, &filename_w))
        తిరిగి -1;
    ఒకవేళ (!filename_w)
        వెళ్ళు fallback;

    fd = _wsopen(filename_w, oflag, SH_DENYNO, pmode);
    av_freep(&filename_w);

    ఒకవేళ (fd != -1 || (oflag & O_CREAT))
        తిరిగి fd;

fallback:
    /* filename may be in CP_ACP */
    తిరిగి _sopen(filename_utf8, oflag, SH_DENYNO, pmode);
}
#నిర్వచించు open win32_open
#అయితే_ముగింపు

పూర్ణాంకం avpriv_open(స్థిరరాశి అక్షరం *filename, పూర్ణాంకం flags, ...)
{
    పూర్ణాంకం fd;
    గుర్తులేని పూర్ణాంకం బహుళకం = 0;
    va_list ap;

    va_start(ap, flags);
    ఒకవేళ (flags & O_CREAT)
        బహుళకం = va_arg(ap, గుర్తులేని పూర్ణాంకం);
    va_end(ap);

#నిర్వచితమైతే O_CLOEXEC
    flags |= O_CLOEXEC;
#అయితే_ముగింపు
#నిర్వచితమైతే O_NOINHERIT
    flags |= O_NOINHERIT;
#అయితే_ముగింపు

    fd = open(filename, flags, బహుళకం);
#ఒకవేళ HAVE_FCNTL
    ఒకవేళ (fd != -1) {
        ఒకవేళ (fcntl(fd, F_SETFD, FD_CLOEXEC) == -1)
            av_log(ఖాళీ, AV_LOG_DEBUG, "Failed to set close on exec\n");
    }
#అయితే_ముగింపు

    తిరిగి fd;
}

రకనిర్వచనం నిర్మాణం FileLogContext {
    స్థిరరాశి AVClass *class;
    పూర్ణాంకం   log_స్థానభ్రంశం;
    శూన్య *log_ctx;
} FileLogContext;

స్థిర స్థిరరాశి AVClass file_log_ctx_class = {
    .class_name                = "TEMPFILE",
    .అంశం_name                 = av_default_అంశం_name,
    .option                    = ఖాళీ,
    .సంస్కరణ                   = LIBAVUTIL_సంస్కరణ_INT,
    .log_level_స్థానభ్రంశం_స్థానభ్రంశం   = offsetof(FileLogContext, log_స్థానభ్రంశం),
    .మాతృ_log_context_స్థానభ్రంశం = offsetof(FileLogContext, log_ctx),
};

పూర్ణాంకం avpriv_tempfile(స్థిరరాశి అక్షరం *ఉపసర్గ, అక్షరం **filename, పూర్ణాంకం log_స్థానభ్రంశం, శూన్య *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_స్థానభ్రంశం, log_ctx };
    పూర్ణాంకం fd = -1;
#ఒకవేళ HAVE_MKSTEMP
    size_t len = అక్షరశ్రేణి_పొడవు(ఉపసర్గ) + 12; /* room for "/tmp/" and "XXXXXX\0" */
    *filename  = av_malloc(len);
#లేదావేళ HAVE_TEMPNAM
    శూన్య *ptr= tempnam(ఖాళీ, ఉపసర్గ);
    ఒకవేళ(!ptr)
        ptr= tempnam(".", ఉపసర్గ);
    *filename = av_strdup(ptr);
    విడుదల(ptr);
#లేకపోతే
    తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు
    /* -----common section-----*/
    ఒకవేళ (!*filename) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot allocate file name\n");
        తిరిగి AVERROR(ENOMEM);
    }
#ఒకవేళ !HAVE_MKSTEMP
#   ifndef O_ద్విమాన
#       define O_ద్విమాన 0
#   endif
#   ifndef O_EXCL
#       define O_EXCL 0
#   endif
    fd = open(*filename, O_RDWR | O_ద్విమాన | O_CREAT | O_EXCL, 0600);
#లేకపోతే
    snprintf(*filename, len, "/tmp/%sXXXXXX", ఉపసర్గ);
    fd = mkstemp(*filename);
#ఒకవేళ defined(_WIN32) || defined (__ANDROID__) || defined(__DJGPP__)
    ఒకవేళ (fd < 0) {
        snprintf(*filename, len, "./%sXXXXXX", ఉపసర్గ);
        fd = mkstemp(*filename);
    }
#అయితే_ముగింపు
#అయితే_ముగింపు
    /* -----common section-----*/
    ఒకవేళ (fd < 0) {
        పూర్ణాంకం err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "ff_tempfile: Cannot open temporary file %s\n", *filename);
        av_freep(filename);
        తిరిగి err;
    }
    తిరిగి fd; /* success */
}

FILE *avpriv_fopen_utf8(స్థిరరాశి అక్షరం *మార్గం, స్థిరరాశి అక్షరం *బహుళకం)
{
    పూర్ణాంకం fd;
    పూర్ణాంకం access;
    స్థిరరాశి అక్షరం *m = బహుళకం;

    ఎంపిక (*m++) {
    స్థితి 'r': access = O_RDONLY; ఆపు;
    స్థితి 'w': access = O_CREAT|O_WRONLY|O_TRUNC; ఆపు;
    స్థితి 'a': access = O_CREAT|O_WRONLY|O_APPEND; ఆపు;
    అప్రమేయ :
        errno = EINVAL;
        తిరిగి ఖాళీ;
    }
    అయితే (*m) {
        ఒకవేళ (*m == '+') {
            access &= ~(O_RDONLY | O_WRONLY);
            access |= O_RDWR;
        } లేకపోతే ఒకవేళ (*m == 'b') {
#నిర్వచితమైతే O_ద్విమాన
            access |= O_ద్విమాన;
#అయితే_ముగింపు
        } లేకపోతే ఒకవేళ (*m) {
            errno = EINVAL;
            తిరిగి ఖాళీ;
        }
        m++;
    }
    fd = avpriv_open(మార్గం, access, 0666);
    ఒకవేళ (fd == -1)
        తిరిగి ఖాళీ;
    తిరిగి fdopen(fd, బహుళకం);
}

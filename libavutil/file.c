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
#అన్తర్భావ "error.h"
#అన్తర్భావ "file.h"
#అన్తర్భావ "file_open.h"
#అన్తర్భావ "internal.h"
#అన్తర్భావ "log.h"
#అన్తర్భావ "mem.h"
#అన్తర్భావ <fcntl.h>
#అన్తర్భావ <sys/stat.h>
#ఒకవేళ HAVE_UNISTD_H
#అన్తర్భావ <unistd.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_IO_H
#అన్తర్భావ <io.h>
#అయితే_ముగింపు
#ఒకవేళ HAVE_MMAP
#అన్తర్భావ <sys/mman.h>
#లేదావేళ HAVE_MAPVIEWOFFILE
#అన్తర్భావ <windows.h>
#అయితే_ముగింపు

#నిర్వచితమైతే _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#నిర్వచనం_రద్దు stat
#నిర్వచనం_రద్దు fstat
#నిర్వచించు stat  _stat64
#నిర్వచించు fstat _fstat64
#అయితే_ముగింపు

రకనిర్వచనం నిర్మాణం FileLogContext {
    స్థిరరాశి AVClass *class;
    పూర్ణాంకం   log_స్థానభ్రంశం;
    శూన్య *log_ctx;
} FileLogContext;

స్థిర స్థిరరాశి AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .అంశం_name                 = av_default_అంశం_name,
    .option                    = ఖాళీ,
    .సంస్కరణ                   = LIBAVUTIL_సంస్కరణ_INT,
    .log_level_స్థానభ్రంశం_స్థానభ్రంశం   = offsetof(FileLogContext, log_స్థానభ్రంశం),
    .మాతృ_log_context_స్థానభ్రంశం = offsetof(FileLogContext, log_ctx),
};

#ఒకవేళ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
స్థిర పూర్ణాంకం map_file(పూర్ణాంకం fd, size_t కొలత, పూర్ణాంకం shared, శూన్య **ptr)
{
#ఒకవేళ HAVE_MMAP
    ఒకవేళ (shared) {
        నిర్మాణం stat st;
        ఒకవేళ (fstat(fd, &st) < 0)
            తిరిగి AVERROR(errno);
        ఒకవేళ (st.st_కొలత < కొలత && ftruncate(fd, కొలత) < 0)
            తిరిగి AVERROR(errno);
    }

    శూన్య *map = mmap(ఖాళీ, కొలత, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_వ్యక్తిగత, fd, 0);
    ఒకవేళ (map == MAP_FAILED)
        తిరిగి AVERROR(errno);
#లేకపోతే
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    ఒకవేళ (fh == INVALID_HANDLE_విలువ)
        తిరిగి AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, ఖాళీ,
                                  shared ? పుట_READWRITE : పుట_READONLY,
                                  (uint64_t)కొలత >> 32, కొలత, ఖాళీ);
    ఒకవేళ (!mh)
        తిరిగి AVERROR(EIO);

    శూన్య *map = Map_View_యొక్క_File(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, కొలత);
    CloseHandle(mh);
    ఒకవేళ (!map)
        తిరిగి AVERROR(EIO);
#అయితే_ముగింపు

    *ptr = map;
    తిరిగి 0;
}

స్థిర శూన్య unmap_file(శూన్య *ptr, size_t కొలత)
{
#ఒకవేళ HAVE_MMAP
    munmap(ptr, కొలత);
#లేకపోతే
    Unmap_View_యొక్క_File(ptr);
#అయితే_ముగింపు
}
#అయితే_ముగింపు

పూర్ణాంకం av_file_map(స్థిరరాశి అక్షరం *filename, uint8_t **bufptr, size_t *కొలత,
                పూర్ణాంకం log_స్థానభ్రంశం, శూన్య *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_స్థానభ్రంశం, log_ctx };
    పూర్ణాంకం err, fd = avpriv_open(filename, O_RDONLY);
    నిర్మాణం stat st;
    av_వాడని శూన్య *ptr;
    *bufptr = ఖాళీ;
    *కొలత = 0;

    ఒకవేళ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        తిరిగి err;
    }

    ఒకవేళ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        తిరిగి err;
    }

    ఒకవేళ (st.st_కొలత > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        తిరిగి AVERROR(EINVAL);
    }
    *కొలత = st.st_కొలత;

    ఒకవేళ (!*కొలత) {
        *bufptr = ఖాళీ;
        వెళ్ళు బహిర్గతం;
    }

#ఒకవేళ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *కొలత, 0, &ptr);
    ఒకవేళ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *కొలత = 0;
        తిరిగి err;
    }
    *bufptr = ptr;
#లేకపోతే
    *bufptr = av_malloc(*కొలత);
    ఒకవేళ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *కొలత = 0;
        తిరిగి AVERROR(ENOMEM);
    }
    పఠ(fd, *bufptr, *కొలత);
#అయితే_ముగింపు

బహిర్గతం:
    close(fd);
    తిరిగి 0;
}

శూన్య av_file_unmap(uint8_t *bufptr, size_t కొలత)
{
    ఒకవేళ (!కొలత || !bufptr)
        తిరిగి;
#ఒకవేళ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, కొలత);
#లేకపోతే
    av_free(bufptr);
#అయితే_ముగింపు
}

పూర్ణాంకం av_file_map_shared(పూర్ణాంకం fd, size_t కొలత, శూన్య **bufptr)
{
    *bufptr = ఖాళీ;
    ఒకవేళ (!కొలత)
        తిరిగి AVERROR(EINVAL);
#ఒకవేళ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    తిరిగి map_file(fd, కొలత, 1, bufptr);
#లేకపోతే
    తిరిగి AVERROR(ENOSYS);
#అయితే_ముగింపు
}

శూన్య av_file_unmap_shared(శూన్య *bufptr, size_t కొలత)
{
#ఒకవేళ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    ఒకవేళ (కొలత && bufptr)
        unmap_file(bufptr, కొలత);
#అయితే_ముగింపు
}

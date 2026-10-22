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
#अन्तर्भाव "error.h"
#अन्तर्भाव "file.h"
#अन्तर्भाव "file_open.h"
#अन्तर्भाव "internal.h"
#अन्तर्भाव "log.h"
#अन्तर्भाव "mem.h"
#अन्तर्भाव <fcntl.h>
#अन्तर्भाव <sys/stat.h>
#यदि HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#यदि_अन्तः
#यदि HAVE_IO_H
#अन्तर्भाव <io.h>
#यदि_अन्तः
#यदि HAVE_MMAP
#अन्तर्भाव <sys/mman.h>
#नोचेद्यदि HAVE_MAPVIEWOFFILE
#अन्तर्भाव <windows.h>
#यदि_अन्तः

#यदि_परिभाषितम् _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#अपरिभाषय stat
#अपरिभाषय fstat
#परिभाषय stat  _stat64
#परिभाषय fstat _fstat64
#यदि_अन्तः

प्रकारनिर्देश संरचना FileLogContext {
    ध्रुव AVClass *class;
    पूर्णाङ्क   log_विस्थापनम्;
    शून्य *log_ctx;
} FileLogContext;

स्थिर ध्रुव AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .संस्करणम्                   = LIBAVUTIL_संस्करणम्_INT,
    .log_level_विस्थापनम्_विस्थापनम्   = offsetof(FileLogContext, log_विस्थापनम्),
    .parent_log_context_विस्थापनम् = offsetof(FileLogContext, log_ctx),
};

#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
स्थिर पूर्णाङ्क map_file(पूर्णाङ्क fd, size_t आकार, पूर्णाङ्क shared, शून्य **ptr)
{
#यदि HAVE_MMAP
    यदि (shared) {
        संरचना stat st;
        यदि (fstat(fd, &st) < 0)
            प्रत्यागम AVERROR(errno);
        यदि (st.st_आकार < आकार && ftruncate(fd, आकार) < 0)
            प्रत्यागम AVERROR(errno);
    }

    शून्य *map = mmap(रिक्त, आकार, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_वैयक्तिकम्, fd, 0);
    यदि (map == MAP_FAILED)
        प्रत्यागम AVERROR(errno);
#अन्यथा
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    यदि (fh == INVALID_HANDLE_मानम्)
        प्रत्यागम AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, रिक्त,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)आकार >> 32, आकार, रिक्त);
    यदि (!mh)
        प्रत्यागम AVERROR(EIO);

    शून्य *map = Map_View_सम्बन्धि_File(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, आकार);
    CloseHandle(mh);
    यदि (!map)
        प्रत्यागम AVERROR(EIO);
#यदि_अन्तः

    *ptr = map;
    प्रत्यागम 0;
}

स्थिर शून्य unmap_file(शून्य *ptr, size_t आकार)
{
#यदि HAVE_MMAP
    munmap(ptr, आकार);
#अन्यथा
    Unmap_View_सम्बन्धि_File(ptr);
#यदि_अन्तः
}
#यदि_अन्तः

पूर्णाङ्क av_file_map(ध्रुव वर्ण *filename, uint8_t **bufptr, size_t *आकार,
                पूर्णाङ्क log_विस्थापनम्, शून्य *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_विस्थापनम्, log_ctx };
    पूर्णाङ्क err, fd = avpriv_open(filename, O_RDONLY);
    संरचना stat st;
    av_अप्रयुक्तम् शून्य *ptr;
    *bufptr = रिक्त;
    *आकार = 0;

    यदि (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        प्रत्यागम err;
    }

    यदि (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        प्रत्यागम err;
    }

    यदि (st.st_आकार > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        प्रत्यागम AVERROR(EINVAL);
    }
    *आकार = st.st_आकार;

    यदि (!*आकार) {
        *bufptr = रिक्त;
        गच्छ बहिर्गमनम्;
    }

#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *आकार, 0, &ptr);
    यदि (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *आकार = 0;
        प्रत्यागम err;
    }
    *bufptr = ptr;
#अन्यथा
    *bufptr = av_malloc(*आकार);
    यदि (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *आकार = 0;
        प्रत्यागम AVERROR(ENOMEM);
    }
    पठ(fd, *bufptr, *आकार);
#यदि_अन्तः

बहिर्गमनम्:
    close(fd);
    प्रत्यागम 0;
}

शून्य av_file_unmap(uint8_t *bufptr, size_t आकार)
{
    यदि (!आकार || !bufptr)
        प्रत्यागम;
#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, आकार);
#अन्यथा
    av_free(bufptr);
#यदि_अन्तः
}

पूर्णाङ्क av_file_map_shared(पूर्णाङ्क fd, size_t आकार, शून्य **bufptr)
{
    *bufptr = रिक्त;
    यदि (!आकार)
        प्रत्यागम AVERROR(EINVAL);
#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
    प्रत्यागम map_file(fd, आकार, 1, bufptr);
#अन्यथा
    प्रत्यागम AVERROR(ENOSYS);
#यदि_अन्तः
}

शून्य av_file_unmap_shared(शून्य *bufptr, size_t आकार)
{
#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
    यदि (आकार && bufptr)
        unmap_file(bufptr, आकार);
#यदि_अन्तः
}

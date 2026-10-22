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
#जइ HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#जइ HAVE_IO_H
#अन्तर्भाव <io.h>
#endif
#जइ HAVE_MMAP
#अन्तर्भाव <sys/mman.h>
#नोचेद्यदि HAVE_MAPVIEWOFFILE
#अन्तर्भाव <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef fstat
#define stat  _stat64
#define fstat _fstat64
#endif

प्रकारनिर्देश संरचना FileLogContext {
    ध्रुव AVClass *class;
    पूर्णाङ्क   log_offset;
    शून्य *log_ctx;
} FileLogContext;

स्थिर ध्रुव AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = offsetof(FileLogContext, log_offset),
    .parent_log_context_offset = offsetof(FileLogContext, log_ctx),
};

#जइ HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
स्थिर पूर्णाङ्क map_file(पूर्णाङ्क fd, size_t size, पूर्णाङ्क shared, शून्य **ptr)
{
#जइ HAVE_MMAP
    जइ (shared) {
        संरचना stat st;
        जइ (fstat(fd, &st) < 0)
            प्रत्यागम AVERROR(errno);
        जइ (st.st_size < size && ftruncate(fd, size) < 0)
            प्रत्यागम AVERROR(errno);
    }

    शून्य *map = mmap(रिक्त, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    जइ (map == MAP_FAILED)
        प्रत्यागम AVERROR(errno);
#अण्णहा
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    जइ (fh == INVALID_HANDLE_मानम्)
        प्रत्यागम AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, रिक्त,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, रिक्त);
    जइ (!mh)
        प्रत्यागम AVERROR(EIO);

    शून्य *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    जइ (!map)
        प्रत्यागम AVERROR(EIO);
#endif

    *ptr = map;
    प्रत्यागम 0;
}

स्थिर शून्य unmap_file(शून्य *ptr, size_t size)
{
#जइ HAVE_MMAP
    munmap(ptr, size);
#अण्णहा
    UnmapViewOfFile(ptr);
#endif
}
#endif

पूर्णाङ्क av_file_map(ध्रुव वर्ण *filename, uint8_t **bufptr, size_t *size,
                पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    पूर्णाङ्क err, fd = avpriv_open(filename, O_RDONLY);
    संरचना stat st;
    av_unused शून्य *ptr;
    *bufptr = रिक्त;
    *size = 0;

    जइ (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        प्रत्यागम err;
    }

    जइ (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        प्रत्यागम err;
    }

    जइ (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        प्रत्यागम AVERROR(EINVAL);
    }
    *size = st.st_size;

    जइ (!*size) {
        *bufptr = रिक्त;
        गच्छ out;
    }

#जइ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    जइ (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        प्रत्यागम err;
    }
    *bufptr = ptr;
#अण्णहा
    *bufptr = av_malloc(*size);
    जइ (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        प्रत्यागम AVERROR(ENOMEM);
    }
    पठ(fd, *bufptr, *size);
#endif

out:
    close(fd);
    प्रत्यागम 0;
}

शून्य av_file_unmap(uint8_t *bufptr, size_t size)
{
    जइ (!size || !bufptr)
        प्रत्यागम;
#जइ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#अण्णहा
    av_free(bufptr);
#endif
}

पूर्णाङ्क av_file_map_shared(पूर्णाङ्क fd, size_t size, शून्य **bufptr)
{
    *bufptr = रिक्त;
    जइ (!size)
        प्रत्यागम AVERROR(EINVAL);
#जइ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    प्रत्यागम map_file(fd, size, 1, bufptr);
#अण्णहा
    प्रत्यागम AVERROR(ENOSYS);
#endif
}

शून्य av_file_unmap_shared(शून्य *bufptr, size_t size)
{
#जइ HAVE_MMAP || HAVE_MAPVIEWOFFILE
    जइ (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

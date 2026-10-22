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
#सचे HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#सचे HAVE_IO_H
#अन्तर्भाव <io.h>
#endif
#सचे HAVE_MMAP
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

#सचे HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
स्थिर पूर्णाङ्क map_file(पूर्णाङ्क fd, size_t size, पूर्णाङ्क shared, शून्य **ptr)
{
#सचे HAVE_MMAP
    सचे (shared) {
        संरचना stat st;
        सचे (fstat(fd, &st) < 0)
            पटिनिवत्त AVERROR(errno);
        सचे (st.st_size < size && ftruncate(fd, size) < 0)
            पटिनिवत्त AVERROR(errno);
    }

    शून्य *map = mmap(रिक्त, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    सचे (map == MAP_FAILED)
        पटिनिवत्त AVERROR(errno);
#अञ्ञथा
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    सचे (fh == INVALID_HANDLE_मानम्)
        पटिनिवत्त AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, रिक्त,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, रिक्त);
    सचे (!mh)
        पटिनिवत्त AVERROR(EIO);

    शून्य *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    सचे (!map)
        पटिनिवत्त AVERROR(EIO);
#endif

    *ptr = map;
    पटिनिवत्त 0;
}

स्थिर शून्य unmap_file(शून्य *ptr, size_t size)
{
#सचे HAVE_MMAP
    munmap(ptr, size);
#अञ्ञथा
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

    सचे (fd < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        पटिनिवत्त err;
    }

    सचे (fstat(fd, &st) < 0) {
        err = AVERROR(errno);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        close(fd);
        पटिनिवत्त err;
    }

    सचे (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        close(fd);
        पटिनिवत्त AVERROR(EINVAL);
    }
    *size = st.st_size;

    सचे (!*size) {
        *bufptr = रिक्त;
        गच्छ out;
    }

#सचे HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    सचे (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        close(fd);
        *size = 0;
        पटिनिवत्त err;
    }
    *bufptr = ptr;
#अञ्ञथा
    *bufptr = av_malloc(*size);
    सचे (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        close(fd);
        *size = 0;
        पटिनिवत्त AVERROR(ENOMEM);
    }
    पठ(fd, *bufptr, *size);
#endif

out:
    close(fd);
    पटिनिवत्त 0;
}

शून्य av_file_unmap(uint8_t *bufptr, size_t size)
{
    सचे (!size || !bufptr)
        पटिनिवत्त;
#सचे HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#अञ्ञथा
    av_free(bufptr);
#endif
}

पूर्णाङ्क av_file_map_shared(पूर्णाङ्क fd, size_t size, शून्य **bufptr)
{
    *bufptr = रिक्त;
    सचे (!size)
        पटिनिवत्त AVERROR(EINVAL);
#सचे HAVE_MMAP || HAVE_MAPVIEWOFFILE
    पटिनिवत्त map_file(fd, size, 1, bufptr);
#अञ्ञथा
    पटिनिवत्त AVERROR(ENOSYS);
#endif
}

शून्य av_file_unmap_shared(शून्य *bufptr, size_t size)
{
#सचे HAVE_MMAP || HAVE_MAPVIEWOFFILE
    सचे (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

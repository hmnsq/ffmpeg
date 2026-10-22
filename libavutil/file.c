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
#endif
#यदि HAVE_IO_H
#अन्तर्भाव <io.h>
#endif
#यदि HAVE_MMAP
#अन्तर्भाव <sys/mman.h>
#अथवायदि HAVE_MAPVIEWOFFILE
#अन्तर्भाव <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef ख_स्थिति
#define stat  _stat64
#define ख_स्थिति _fstat64
#endif

प्रकारनिर्देश संरचना FileLogContext {
    अचर AVClass *class;
    पूर्णाङ्क   log_offset;
    शून्य *log_ctx;
} FileLogContext;

स्थिर अचर AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(FileLogContext, log_offset),
    .parent_log_context_offset = दुरत्व(FileLogContext, log_ctx),
};

#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
स्थिर पूर्णाङ्क map_file(पूर्णाङ्क fd, माप_प्रकार size, पूर्णाङ्क shared, शून्य **ptr)
{
#यदि HAVE_MMAP
    यदि (shared) {
        संरचना stat st;
        यदि (ख_स्थिति(fd, &st) < 0)
            फर्काऊ AVERROR(त्रुटि_सं);
        यदि (st.st_size < size && ftruncate(fd, size) < 0)
            फर्काऊ AVERROR(त्रुटि_सं);
    }

    शून्य *map = mmap(रिक्त, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    यदि (map == MAP_FAILED)
        फर्काऊ AVERROR(त्रुटि_सं);
#अन्यथा
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    यदि (fh == INVALID_HANDLE_मान)
        फर्काऊ AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, रिक्त,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, रिक्त);
    यदि (!mh)
        फर्काऊ AVERROR(EIO);

    शून्य *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    यदि (!map)
        फर्काऊ AVERROR(EIO);
#endif

    *ptr = map;
    फर्काऊ 0;
}

स्थिर शून्य unmap_file(शून्य *ptr, माप_प्रकार size)
{
#यदि HAVE_MMAP
    munmap(ptr, size);
#अन्यथा
    UnmapViewOfFile(ptr);
#endif
}
#endif

पूर्णाङ्क av_file_map(अचर वर्ण *filename, uint8_t **bufptr, माप_प्रकार *size,
                पूर्णाङ्क log_offset, शून्य *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    पूर्णाङ्क err, fd = avpriv_open(filename, O_RDONLY);
    संरचना stat st;
    av_unused शून्य *ptr;
    *bufptr = रिक्त;
    *size = 0;

    यदि (fd < 0) {
        err = AVERROR(त्रुटि_सं);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        फर्काऊ err;
    }

    यदि (ख_स्थिति(fd, &st) < 0) {
        err = AVERROR(त्रुटि_सं);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        बंद(fd);
        फर्काऊ err;
    }

    यदि (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        बंद(fd);
        फर्काऊ AVERROR(EINVAL);
    }
    *size = st.st_size;

    यदि (!*size) {
        *bufptr = रिक्त;
        गच्छ out;
    }

#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    यदि (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        बंद(fd);
        *size = 0;
        फर्काऊ err;
    }
    *bufptr = ptr;
#अन्यथा
    *bufptr = av_malloc(*size);
    यदि (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        बंद(fd);
        *size = 0;
        फर्काऊ AVERROR(ENOMEM);
    }
    पठ(fd, *bufptr, *size);
#endif

out:
    बंद(fd);
    फर्काऊ 0;
}

शून्य av_file_unmap(uint8_t *bufptr, माप_प्रकार size)
{
    यदि (!size || !bufptr)
        फर्काऊ;
#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#अन्यथा
    av_free(bufptr);
#endif
}

पूर्णाङ्क av_file_map_shared(पूर्णाङ्क fd, माप_प्रकार size, शून्य **bufptr)
{
    *bufptr = रिक्त;
    यदि (!size)
        फर्काऊ AVERROR(EINVAL);
#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
    फर्काऊ map_file(fd, size, 1, bufptr);
#अन्यथा
    फर्काऊ AVERROR(ENOSYS);
#endif
}

शून्य av_file_unmap_shared(शून्य *bufptr, माप_प्रकार size)
{
#यदि HAVE_MMAP || HAVE_MAPVIEWOFFILE
    यदि (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

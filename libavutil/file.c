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
#जर HAVE_UNISTD_H
#अन्तर्भाव <unistd.h>
#endif
#जर HAVE_IO_H
#अन्तर्भाव <io.h>
#endif
#जर HAVE_MMAP
#अन्तर्भाव <sys/mman.h>
#किंवाजर HAVE_MAPVIEWOFFILE
#अन्तर्भाव <windows.h>
#endif

#ifdef _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#undef stat
#undef ख_स्थिति
#define stat  _stat64
#define ख_स्थिति _fstat64
#endif

प्रकारव्याख्या संरचना FileLogContext {
    स्थिरांक AVClass *class;
    पूर्णांक   log_offset;
    शून्य *log_ctx;
} FileLogContext;

स्थिर स्थिरांक AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = रिक्त,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(FileLogContext, log_offset),
    .parent_log_context_offset = दुरत्व(FileLogContext, log_ctx),
};

#जर HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
स्थिर पूर्णांक map_file(पूर्णांक fd, माप_प्रकार size, पूर्णांक shared, शून्य **ptr)
{
#जर HAVE_MMAP
    जर (shared) {
        संरचना stat st;
        जर (ख_स्थिति(fd, &st) < 0)
            परत AVERROR(त्रुटि_सं);
        जर (st.st_size < size && ftruncate(fd, size) < 0)
            परत AVERROR(त्रुटि_सं);
    }

    शून्य *map = mmap(रिक्त, size, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    जर (map == MAP_FAILED)
        परत AVERROR(त्रुटि_सं);
#अन्यथा
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    जर (fh == INVALID_HANDLE_मूल्य)
        परत AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, रिक्त,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)size >> 32, size, रिक्त);
    जर (!mh)
        परत AVERROR(EIO);

    शून्य *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, size);
    CloseHandle(mh);
    जर (!map)
        परत AVERROR(EIO);
#endif

    *ptr = map;
    परत 0;
}

स्थिर शून्य unmap_file(शून्य *ptr, माप_प्रकार size)
{
#जर HAVE_MMAP
    munmap(ptr, size);
#अन्यथा
    UnmapViewOfFile(ptr);
#endif
}
#endif

पूर्णांक av_file_map(स्थिरांक अक्षर *filename, uint8_t **bufptr, माप_प्रकार *size,
                पूर्णांक log_offset, शून्य *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    पूर्णांक err, fd = avpriv_open(filename, O_RDONLY);
    संरचना stat st;
    av_unused शून्य *ptr;
    *bufptr = रिक्त;
    *size = 0;

    जर (fd < 0) {
        err = AVERROR(त्रुटि_सं);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        परत err;
    }

    जर (ख_स्थिति(fd, &st) < 0) {
        err = AVERROR(त्रुटि_सं);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        बंद(fd);
        परत err;
    }

    जर (st.st_size > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        बंद(fd);
        परत AVERROR(EINVAL);
    }
    *size = st.st_size;

    जर (!*size) {
        *bufptr = रिक्त;
        जा out;
    }

#जर HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *size, 0, &ptr);
    जर (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        बंद(fd);
        *size = 0;
        परत err;
    }
    *bufptr = ptr;
#अन्यथा
    *bufptr = av_malloc(*size);
    जर (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        बंद(fd);
        *size = 0;
        परत AVERROR(ENOMEM);
    }
    पठ(fd, *bufptr, *size);
#endif

out:
    बंद(fd);
    परत 0;
}

शून्य av_file_unmap(uint8_t *bufptr, माप_प्रकार size)
{
    जर (!size || !bufptr)
        परत;
#जर HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, size);
#अन्यथा
    av_free(bufptr);
#endif
}

पूर्णांक av_file_map_shared(पूर्णांक fd, माप_प्रकार size, शून्य **bufptr)
{
    *bufptr = रिक्त;
    जर (!size)
        परत AVERROR(EINVAL);
#जर HAVE_MMAP || HAVE_MAPVIEWOFFILE
    परत map_file(fd, size, 1, bufptr);
#अन्यथा
    परत AVERROR(ENOSYS);
#endif
}

शून्य av_file_unmap_shared(शून्य *bufptr, माप_प्रकार size)
{
#जर HAVE_MMAP || HAVE_MAPVIEWOFFILE
    जर (size && bufptr)
        unmap_file(bufptr, size);
#endif
}

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

#समावेश "config.h"
#समावेश "error.h"
#समावेश "file.h"
#समावेश "file_open.h"
#समावेश "internal.h"
#समावेश "log.h"
#समावेश "mem.h"
#समावेश <fcntl.h>
#समावेश <sys/stat.h>
#अगर HAVE_UNISTD_H
#समावेश <unistd.h>
#पूर्ण_अगर
#अगर HAVE_IO_H
#समावेश <io.h>
#पूर्ण_अगर
#अगर HAVE_MMAP
#समावेश <sys/mman.h>
#या_अगर HAVE_MAPVIEWOFFILE
#समावेश <windows.h>
#पूर्ण_अगर

#अगर_घोषित _WIN32
/* struct stat has a 32 bit st_size with the Windows SDK, use the 64 bit variants */
#अघोषित stat
#अघोषित ख_स्थिति
#घोषणा stat  _stat64
#घोषणा ख_स्थिति _fstat64
#पूर्ण_अगर

प्रकार काष्ठा FileLogContext {
    स्थिर AVClass *class;
    पूर्णांक   log_offset;
    व्योम *log_ctx;
} FileLogContext;

अटल स्थिर AVClass file_log_ctx_class = {
    .class_name                = "FILE",
    .item_name                 = av_default_item_name,
    .option                    = शून्य,
    .version                   = LIBAVUTIL_VERSION_INT,
    .log_level_offset_offset   = दुरत्व(FileLogContext, log_offset),
    .parent_log_context_offset = दुरत्व(FileLogContext, log_ctx),
};

#अगर HAVE_MMAP || HAVE_MAPVIEWOFFILE
/* Map the first size bytes of the file, as a private copy or shared and
 * writable. The shared mapping extends the file to size, on Windows the
 * mapping object does it. */
अटल पूर्णांक map_file(पूर्णांक fd, माप_प्रकार आकार, पूर्णांक shared, व्योम **ptr)
{
#अगर HAVE_MMAP
    अगर (shared) {
        काष्ठा stat st;
        अगर (ख_स्थिति(fd, &st) < 0)
            वापस AVERROR(त्रुटि_सं);
        अगर (st.st_आकार < आकार && ftruncate(fd, आकार) < 0)
            वापस AVERROR(त्रुटि_सं);
    }

    व्योम *map = mmap(शून्य, आकार, PROT_READ | PROT_WRITE,
                     shared ? MAP_SHARED : MAP_PRIVATE, fd, 0);
    अगर (map == MAP_FAILED)
        वापस AVERROR(त्रुटि_सं);
#अन्यथा
    HANDLE fh = (HANDLE)_get_osfhandle(fd);
    अगर (fh == INVALID_HANDLE_मूल्य)
        वापस AVERROR(EBADF);

    HANDLE mh = CreateFileMapping(fh, शून्य,
                                  shared ? PAGE_READWRITE : PAGE_READONLY,
                                  (uint64_t)आकार >> 32, आकार, शून्य);
    अगर (!mh)
        वापस AVERROR(EIO);

    व्योम *map = MapViewOfFile(mh, shared ? FILE_MAP_ALL_ACCESS : FILE_MAP_COPY,
                              0, 0, आकार);
    CloseHandle(mh);
    अगर (!map)
        वापस AVERROR(EIO);
#पूर्ण_अगर

    *ptr = map;
    वापस 0;
}

अटल व्योम unmap_file(व्योम *ptr, माप_प्रकार आकार)
{
#अगर HAVE_MMAP
    munmap(ptr, आकार);
#अन्यथा
    UnmapViewOfFile(ptr);
#पूर्ण_अगर
}
#पूर्ण_अगर

पूर्णांक av_file_map(स्थिर अक्षर *filename, uint8_t **bufptr, माप_प्रकार *आकार,
                पूर्णांक log_offset, व्योम *log_ctx)
{
    FileLogContext file_log_ctx = { &file_log_ctx_class, log_offset, log_ctx };
    पूर्णांक err, fd = avpriv_open(filename, O_RDONLY);
    काष्ठा stat st;
    av_unused व्योम *ptr;
    *bufptr = शून्य;
    *आकार = 0;

    अगर (fd < 0) {
        err = AVERROR(त्रुटि_सं);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot read file '%s': %s\n", filename, av_err2str(err));
        वापस err;
    }

    अगर (ख_स्थिति(fd, &st) < 0) {
        err = AVERROR(त्रुटि_सं);
        av_log(&file_log_ctx, AV_LOG_ERROR, "Error occurred in fstat(): %s\n", av_err2str(err));
        बंद(fd);
        वापस err;
    }

    अगर (st.st_आकार > SIZE_MAX) {
        av_log(&file_log_ctx, AV_LOG_ERROR,
               "File size for file '%s' is too big\n", filename);
        बंद(fd);
        वापस AVERROR(EINVAL);
    }
    *आकार = st.st_आकार;

    अगर (!*आकार) {
        *bufptr = शून्य;
        जाओ out;
    }

#अगर HAVE_MMAP || HAVE_MAPVIEWOFFILE
    err = map_file(fd, *आकार, 0, &ptr);
    अगर (err < 0) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Cannot map file '%s': %s\n", filename, av_err2str(err));
        बंद(fd);
        *आकार = 0;
        वापस err;
    }
    *bufptr = ptr;
#अन्यथा
    *bufptr = av_malloc(*आकार);
    अगर (!*bufptr) {
        av_log(&file_log_ctx, AV_LOG_ERROR, "Memory allocation error occurred\n");
        बंद(fd);
        *आकार = 0;
        वापस AVERROR(ENOMEM);
    }
    पढ़ो(fd, *bufptr, *आकार);
#पूर्ण_अगर

out:
    बंद(fd);
    वापस 0;
}

व्योम av_file_unmap(uint8_t *bufptr, माप_प्रकार आकार)
{
    अगर (!आकार || !bufptr)
        वापस;
#अगर HAVE_MMAP || HAVE_MAPVIEWOFFILE
    unmap_file(bufptr, आकार);
#अन्यथा
    av_free(bufptr);
#पूर्ण_अगर
}

पूर्णांक av_file_map_shared(पूर्णांक fd, माप_प्रकार आकार, व्योम **bufptr)
{
    *bufptr = शून्य;
    अगर (!आकार)
        वापस AVERROR(EINVAL);
#अगर HAVE_MMAP || HAVE_MAPVIEWOFFILE
    वापस map_file(fd, आकार, 1, bufptr);
#अन्यथा
    वापस AVERROR(ENOSYS);
#पूर्ण_अगर
}

व्योम av_file_unmap_shared(व्योम *bufptr, माप_प्रकार आकार)
{
#अगर HAVE_MMAP || HAVE_MAPVIEWOFFILE
    अगर (आकार && bufptr)
        unmap_file(bufptr, आकार);
#पूर्ण_अगर
}

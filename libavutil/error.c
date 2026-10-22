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

#undef _GNU_SOURCE
#define _XOPEN_SOURCE 600 /* XSI-compliant version of strerror_r */
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "macros.h"

#define AVERROR_ಒಳಹರಿವು_AND_OUTPUT_CHANGED (AVERROR_ಒಳಹರಿವು_CHANGED | AVERROR_OUTPUT_CHANGED)

#define AVERROR_LIST(E, E2)                                                                     \
    E(BSF_NOT_FOUND,            "Bitstream filter not found")                                   \
    E(BUG,                      "Internal bug, should not have happened")                       \
    E2(BUG2, BUG,               "Internal bug, should not have happened")                       \
    E(BUFFER_TOO_SMALL,         "Buffer too small")                                             \
    E(DECODER_NOT_FOUND,        "Decoder not found")                                            \
    E(DEMUXER_NOT_FOUND,        "Demuxer not found")                                            \
    E(ENCODER_NOT_FOUND,        "Encoder not found")                                            \
    E(EOF,                      "End of file")                                                  \
    E(EXIT,                     "Immediate exit requested")                                     \
    E(EXTERNAL,                 "Generic error in an external library")                         \
    E(FILTER_NOT_FOUND,         "Filter not found")                                             \
    E(ಒಳಹರಿವು_CHANGED,            "Input changed")                                                \
    E(INVALIDDATA,              "Invalid data found when processing input")                     \
    E(MUXER_NOT_FOUND,          "Muxer not found")                                              \
    E(OPTION_NOT_FOUND,         "Option not found")                                             \
    E(OUTPUT_CHANGED,           "Output changed")                                               \
    E(PATCHWELCOME,             "Not yet implemented in FFmpeg, patches welcome")               \
    E(PROTOCOL_NOT_FOUND,       "Protocol not found")                                           \
    E(STREAM_NOT_FOUND,         "Stream not found")                                             \
    E(UNKNOWN,                  "Unknown error occurred")                                       \
    E(EXPERIMENTAL,             "Experimental feature")                                         \
    E(ಒಳಹರಿವು_AND_OUTPUT_CHANGED, "Input and output changed")                                     \
    E(HTTP_BAD_REQUEST,         "Server returned 400 Bad Request")                              \
    E(HTTP_UNAUTHORIZED,        "Server returned 401 Unauthorized (authorization failed)")      \
    E(HTTP_FORBIDDEN,           "Server returned 403 Forbidden (access denied)")                \
    E(HTTP_NOT_FOUND,           "Server returned 404 Not Found")                                \
    E(HTTP_TOO_MANY_REQUESTS,   "Server returned 429 Too Many Requests")                        \
    E(HTTP_OTHER_4XX,           "Server returned 4XX Client Error, but not one of 40{0,1,3,4}") \
    E(HTTP_SERVER_ERROR,        "Server returned 5XX Server Error reply")                       \

#define STRERROR_LIST(E)                                                     \
    E(E2BIG,             "Argument list too long")                           \
    E(EACCES,            "Permission denied")                                \
    E(EAGAIN,            "Resource temporarily unavailable")                 \
    E(EBADF,             "Bad file descriptor")                              \
    E(EBUSY,             "Device or resource busy")                          \
    E(ECHILD,            "No child processes")                               \
    E(EDEADLK,           "Resource deadlock avoided")                        \
    E(EDOM,              "Numerical argument out of domain")                 \
    E(EEXIST,            "File exists")                                      \
    E(EFAULT,            "Bad address")                                      \
    E(EFBIG,             "File too large")                                   \
    E(EILSEQ,            "Illegal byte sequence")                            \
    E(EINTR,             "Interrupted system call")                          \
    E(EINVAL,            "Invalid argument")                                 \
    E(EIO,               "I/O error")                                        \
    E(EISDIR,            "Is a directory")                                   \
    E(EMFILE,            "Too many open files")                              \
    E(EMLINK,            "Too many links")                                   \
    E(ENAMETOOLONG,      "File name too long")                               \
    E(ENFILE,            "Too many open files in system")                    \
    E(ENODEV,            "No such device")                                   \
    E(ENOENT,            "No such file or directory")                        \
    E(ENOEXEC,           "Exec format error")                                \
    E(ENOLCK,            "No locks available")                               \
    E(ENOMEM,            "Cannot allocate memory")                           \
    E(ENOSPC,            "No space left on device")                          \
    E(ENOSYS,            "Function not implemented")                         \
    E(ENOTDIR,           "Not a directory")                                  \
    E(ENOTEMPTY,         "Directory not empty")                              \
    E(ENOTTY,            "Inappropriate I/O control operation")              \
    E(ENXIO,             "No such device or address")                        \
    E(EPERM,             "Operation not permitted")                          \
    E(EPIPE,             "Broken pipe")                                      \
    E(ERANGE,            "Result too large")                                 \
    E(EROFS,             "Read-only file system")                            \
    E(ESPIPE,            "Illegal seek")                                     \
    E(ESRCH,             "No such process")                                  \
    E(EXDEV,             "Cross-device link")                                \

ಗಣನಾ {
#define OFFSET(CODE, DESC)     \
    ERROR_ ## CODE ## _OFFSET, \
    ERROR_ ## CODE ## _END_OFFSET = ERROR_ ## CODE ## _OFFSET + ಪರಿಮಾಣ(DESC) - 1,
#define NOTHING(CODE, CODE2, DESC)
    AVERROR_LIST(OFFSET, NOTHING)
#ಯದಿ !HAVE_STRERROR_R
    STRERROR_LIST(OFFSET)
#endif
};

#define STRING(CODE, DESC) DESC "\0"
ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ error_stringtable[] =
    AVERROR_LIST(STRING, NOTHING)
#ಯದಿ !HAVE_STRERROR_R
    STRERROR_LIST(STRING)
#endif
;

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ ErrorEntry {
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ;
    unsigned offset;
} error_entries[] = {
#define ENTRY(CODE, DESC) { .ಅಂಕೆ = AVERROR_ ## CODE, .offset = ERROR_ ## CODE ## _OFFSET },
#define ENTRY2(CODE, CODE2, DESC) { .ಅಂಕೆ = AVERROR_ ## CODE, .offset = ERROR_ ## CODE2 ## _OFFSET },
    AVERROR_LIST(ENTRY, ENTRY2)
#ಯದಿ !HAVE_STRERROR_R
#undef ENTRY
#define ENTRY(CODE, DESC) { .ಅಂಕೆ = AVERROR(CODE), .offset = ERROR_ ## CODE ## _OFFSET },
    STRERROR_LIST(ENTRY)
#endif
};

ಪೂರ್ಣಾಙ್ಕ av_strerror(ಪೂರ್ಣಾಙ್ಕ errnum, ವರ್ಣ *errbuf, size_t errbuf_size)
{
    ಪ್ರತಿ (size_t i = 0; i < FF_ARRAY_ELEMS(error_entries); ++i) {
        ಯದಿ (errnum == error_entries[i].ಅಂಕೆ) {
            av_strlcpy(errbuf, error_stringtable + error_entries[i].offset, errbuf_size);
            ಪ್ರತ್ಯಾಗಮ 0;
        }
    }
#ಯದಿ HAVE_STRERROR_R
    ಪೂರ್ಣಾಙ್ಕ ret = AVERROR(strerror_r(AVUNERROR((unsigned)errnum), errbuf, errbuf_size));
#ಅನ್ಯಥಾ
    ಪೂರ್ಣಾಙ್ಕ ret = -1;
#endif
    ಯದಿ (ret < 0)
        snprintf(errbuf, errbuf_size, "Error number %d occurred", errnum);

    ಪ್ರತ್ಯಾಗಮ ret;
}

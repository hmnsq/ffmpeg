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

#अघोषित _GNU_SOURCE
#घोषणा _XOPEN_SOURCE 600 /* XSI-compliant version of strerror_r */
#समावेश <stdio.h>
#समावेश <string.h>
#समावेश "config.h"
#समावेश "avstring.h"
#समावेश "error.h"
#समावेश "macros.h"

#घोषणा AVERROR_निवेश_AND_OUTPUT_CHANGED (AVERROR_निवेश_CHANGED | AVERROR_OUTPUT_CHANGED)

#घोषणा AVERROR_LIST(E, E2)                                                                     \
    E(BSF_NOT_FOUND,            "Bitstream filter not found")                                   \
    E(BUG,                      "Internal bug, should not have happened")                       \
    E2(BUG2, BUG,               "Internal bug, should not have happened")                       \
    E(बफर_TOO_SMALL,         "Buffer too small")                                             \
    E(DECODER_NOT_FOUND,        "Decoder not found")                                            \
    E(DEMUXER_NOT_FOUND,        "Demuxer not found")                                            \
    E(ENCODER_NOT_FOUND,        "Encoder not found")                                            \
    E(खातापूर्ण,                      "End of file")                                                  \
    E(EXIT,                     "Immediate exit requested")                                     \
    E(EXTERNAL,                 "Generic error in an external library")                         \
    E(FILTER_NOT_FOUND,         "Filter not found")                                             \
    E(निवेश_CHANGED,            "Input changed")                                                \
    E(INVALIDDATA,              "Invalid data found when processing input")                     \
    E(MUXER_NOT_FOUND,          "Muxer not found")                                              \
    E(OPTION_NOT_FOUND,         "Option not found")                                             \
    E(OUTPUT_CHANGED,           "Output changed")                                               \
    E(PATCHWELCOME,             "Not yet implemented in FFmpeg, patches welcome")               \
    E(PROTOCOL_NOT_FOUND,       "Protocol not found")                                           \
    E(STREAM_NOT_FOUND,         "Stream not found")                                             \
    E(UNKNOWN,                  "Unknown error occurred")                                       \
    E(EXPERIMENTAL,             "Experimental feature")                                         \
    E(निवेश_AND_OUTPUT_CHANGED, "Input and output changed")                                     \
    E(HTTP_BAD_REQUEST,         "Server returned 400 Bad Request")                              \
    E(HTTP_UNAUTHORIZED,        "Server returned 401 Unauthorized (authorization failed)")      \
    E(HTTP_FORBIDDEN,           "Server returned 403 Forbidden (access denied)")                \
    E(HTTP_NOT_FOUND,           "Server returned 404 Not Found")                                \
    E(HTTP_TOO_MANY_REQUESTS,   "Server returned 429 Too Many Requests")                        \
    E(HTTP_OTHER_4XX,           "Server returned 4XX Client Error, but not one of 40{0,1,3,4}") \
    E(HTTP_SERVER_ERROR,        "Server returned 5XX Server Error reply")                       \

#घोषणा STRERROR_LIST(E)                                                     \
    E(E2BIG,             "Argument list too long")                           \
    E(EACCES,            "Permission denied")                                \
    E(EAGAIN,            "Resource temporarily unavailable")                 \
    E(EBADF,             "Bad file descriptor")                              \
    E(EBUSY,             "Device or resource busy")                          \
    E(ECHILD,            "No child processes")                               \
    E(EDEADLK,           "Resource deadlock avoided")                        \
    E(गलत_तर्क,              "Numerical argument out of domain")                 \
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
    E(दुस्फल,            "Result too large")                                 \
    E(EROFS,             "Read-only file system")                            \
    E(ESPIPE,            "Illegal seek")                                     \
    E(ESRCH,             "No such process")                                  \
    E(EXDEV,             "Cross-device link")                                \

क्रमागत {
#घोषणा OFFSET(CODE, DESC)     \
    ERROR_ ## CODE ## _OFFSET, \
    ERROR_ ## CODE ## _END_OFFSET = ERROR_ ## CODE ## _OFFSET + माप(DESC) - 1,
#घोषणा NOTHING(CODE, CODE2, DESC)
    AVERROR_LIST(OFFSET, NOTHING)
#अगर !HAVE_STRERROR_R
    STRERROR_LIST(OFFSET)
#पूर्ण_अगर
};

#घोषणा STRING(CODE, DESC) DESC "\0"
अटल स्थिर अक्षर error_stringtable[] =
    AVERROR_LIST(STRING, NOTHING)
#अगर !HAVE_STRERROR_R
    STRERROR_LIST(STRING)
#पूर्ण_अगर
;

अटल स्थिर काष्ठा ErrorEntry {
    पूर्णांक अंक;
    अचिन्हित offset;
} error_entries[] = {
#घोषणा ENTRY(CODE, DESC) { .अंक = AVERROR_ ## CODE, .offset = ERROR_ ## CODE ## _OFFSET },
#घोषणा ENTRY2(CODE, CODE2, DESC) { .अंक = AVERROR_ ## CODE, .offset = ERROR_ ## CODE2 ## _OFFSET },
    AVERROR_LIST(ENTRY, ENTRY2)
#अगर !HAVE_STRERROR_R
#अघोषित ENTRY
#घोषणा ENTRY(CODE, DESC) { .अंक = AVERROR(CODE), .offset = ERROR_ ## CODE ## _OFFSET },
    STRERROR_LIST(ENTRY)
#पूर्ण_अगर
};

पूर्णांक av_strerror(पूर्णांक errnum, अक्षर *errbuf, माप_प्रकार errbuf_आकार)
{
    क्रम (माप_प्रकार i = 0; i < FF_ARRAY_ELEMS(error_entries); ++i) {
        अगर (errnum == error_entries[i].अंक) {
            av_strlcpy(errbuf, error_stringtable + error_entries[i].offset, errbuf_आकार);
            वापस 0;
        }
    }
#अगर HAVE_STRERROR_R
    पूर्णांक ret = AVERROR(strerror_r(AVUNERROR((अचिन्हित)errnum), errbuf, errbuf_आकार));
#अन्यथा
    पूर्णांक ret = -1;
#पूर्ण_अगर
    अगर (ret < 0)
        snprintf(errbuf, errbuf_आकार, "Error number %d occurred", errnum);

    वापस ret;
}

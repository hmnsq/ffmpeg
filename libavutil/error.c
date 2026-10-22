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

#अपरिभाषय _GNU_SOURCE
#परिभाषय _XOPEN_SOURCE 600 /* XSI-compliant version of strerror_r */
#अन्तर्भाव <stdio.h>
#अन्तर्भाव <string.h>
#अन्तर्भाव "config.h"
#अन्तर्भाव "avstring.h"
#अन्तर्भाव "error.h"
#अन्तर्भाव "macros.h"

#परिभाषय AVERROR_निवेशः_AND_OUTPUT_परिवर्तितम् (AVERROR_निवेशः_परिवर्तितम् | AVERROR_OUTPUT_परिवर्तितम्)

#परिभाषय AVERROR_LIST(E, E2)                                                                     \
    E(BSF_NOT_प्राप्तम्,            "Bitstream filter not found")                                   \
    E(BUG,                      "Internal bug, should not have happened")                       \
    E2(BUG2, BUG,               "Internal bug, should not have happened")                       \
    E(बफर_TOO_SMALL,         "Buffer too small")                                             \
    E(DECODER_NOT_प्राप्तम्,        "Decoder not found")                                            \
    E(DEMUXER_NOT_प्राप्तम्,        "Demuxer not found")                                            \
    E(ENCODER_NOT_प्राप्तम्,        "Encoder not found")                                            \
    E(EOF,                      "End of file")                                                  \
    E(EXIT,                     "Immediate exit requested")                                     \
    E(EXTERNAL,                 "Generic error in an external library")                         \
    E(FILTER_NOT_प्राप्तम्,         "Filter not found")                                             \
    E(निवेशः_परिवर्तितम्,            "Input changed")                                                \
    E(INVALIDDATA,              "Invalid data found when processing input")                     \
    E(MUXER_NOT_प्राप्तम्,          "Muxer not found")                                              \
    E(OPTION_NOT_प्राप्तम्,         "Option not found")                                             \
    E(OUTPUT_परिवर्तितम्,           "Output changed")                                               \
    E(PATCHWELCOME,             "Not yet implemented in FFmpeg, patches welcome")               \
    E(PROTOCOL_NOT_प्राप्तम्,       "Protocol not found")                                           \
    E(प्रवाहः_NOT_प्राप्तम्,         "Stream not found")                                             \
    E(UNKNOWN,                  "Unknown error occurred")                                       \
    E(EXPERIMENTAL,             "Experimental feature")                                         \
    E(निवेशः_AND_OUTPUT_परिवर्तितम्, "Input and output changed")                                     \
    E(HTTP_BAD_REQUEST,         "Server returned 400 Bad Request")                              \
    E(HTTP_UNAUTHORIZED,        "Server returned 401 Unauthorized (authorization failed)")      \
    E(HTTP_FORBIDDEN,           "Server returned 403 Forbidden (access denied)")                \
    E(HTTP_NOT_प्राप्तम्,           "Server returned 404 Not Found")                                \
    E(HTTP_TOO_MANY_अनुरोधाः,   "Server returned 429 Too Many Requests")                        \
    E(HTTP_OTHER_4XX,           "Server returned 4XX Client Error, but not one of 40{0,1,3,4}") \
    E(HTTP_SERVER_ERROR,        "Server returned 5XX Server Error reply")                       \

#परिभाषय STRERROR_LIST(E)                                                     \
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

गणना {
#परिभाषय विस्थापनम्_2(संहिता_2, DESC)     \
    ERROR_ ## संहिता_2 ## विस्थापनम्_3, \
    ERROR_ ## संहिता_2 ## अन्तः_विस्थापनम् = ERROR_ ## संहिता_2 ## विस्थापनम्_3 + परिमाण(DESC) - 1,
#परिभाषय NOTHING(संहिता_2, CODE2, DESC)
    AVERROR_LIST(विस्थापनम्_2, NOTHING)
#यदि !HAVE_STRERROR_R
    STRERROR_LIST(विस्थापनम्_2)
#यदि_अन्तः
};

#परिभाषय STRING(संहिता_2, DESC) DESC "\0"
स्थिर ध्रुव वर्ण error_stringtable[] =
    AVERROR_LIST(STRING, NOTHING)
#यदि !HAVE_STRERROR_R
    STRERROR_LIST(STRING)
#यदि_अन्तः
;

स्थिर ध्रुव संरचना Error_प्रविष्टिः {
    पूर्णाङ्क अङ्कः;
    अचिह्नित विस्थापनम्;
} error_entries[] = {
#परिभाषय प्रविष्टिः_2(संहिता_2, DESC) { .अङ्कः = AVERROR_ ## संहिता_2, .विस्थापनम् = ERROR_ ## संहिता_2 ## विस्थापनम्_3 },
#परिभाषय ENTRY2(संहिता_2, CODE2, DESC) { .अङ्कः = AVERROR_ ## संहिता_2, .विस्थापनम् = ERROR_ ## CODE2 ## विस्थापनम्_3 },
    AVERROR_LIST(प्रविष्टिः_2, ENTRY2)
#यदि !HAVE_STRERROR_R
#अपरिभाषय प्रविष्टिः_2
#परिभाषय प्रविष्टिः_2(संहिता_2, DESC) { .अङ्कः = AVERROR(संहिता_2), .विस्थापनम् = ERROR_ ## संहिता_2 ## विस्थापनम्_3 },
    STRERROR_LIST(प्रविष्टिः_2)
#यदि_अन्तः
};

पूर्णाङ्क av_strerror(पूर्णाङ्क errnum, वर्ण *errbuf, size_t errbuf_आकार)
{
    प्रति (size_t i = 0; i < FF_ARRAY_ELEMS(error_entries); ++i) {
        यदि (errnum == error_entries[i].अङ्कः) {
            av_strlcpy(errbuf, error_stringtable + error_entries[i].विस्थापनम्, errbuf_आकार);
            प्रत्यागम 0;
        }
    }
#यदि HAVE_STRERROR_R
    पूर्णाङ्क ret = AVERROR(strerror_r(AVUNERROR((अचिह्नित)errnum), errbuf, errbuf_आकार));
#अन्यथा
    पूर्णाङ्क ret = -1;
#यदि_अन्तः
    यदि (ret < 0)
        snprintf(errbuf, errbuf_आकार, "Error number %d occurred", errnum);

    प्रत्यागम ret;
}

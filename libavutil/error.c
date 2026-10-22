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

#وصف_رد GNU_ذريعو
#وصف_ڪريو XOPEN_ذريعو 600 /* XSI-compliant version of strerror_r */
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن "config.h"
#ضمن "avstring.h"
#ضمن "error.h"
#ضمن "macros.h"

#وصف_ڪريو AVERROR_داخلا_AND_OUTPUT_بدليو (AVERROR_داخلا_بدليو | AVERROR_OUTPUT_بدليو)

#وصف_ڪريو AVERROR_LIST(E, E2)                                                                     \
    E(BSF_NOT_مليو,            "Bitstream filter not found")                                   \
    E(BUG,                      "Internal bug, should not have happened")                       \
    E2(BUG2, BUG,               "Internal bug, should not have happened")                       \
    E(بفر_TOO_SMALL,         "Buffer too small")                                             \
    E(DECODER_NOT_مليو,        "Decoder not found")                                            \
    E(DEMUXER_NOT_مليو,        "Demuxer not found")                                            \
    E(ENCODER_NOT_مليو,        "Encoder not found")                                            \
    E(EOF,                      "End of file")                                                  \
    E(EXIT,                     "Immediate exit requested")                                     \
    E(EXTERNAL,                 "Generic error in an external library")                         \
    E(FILTER_NOT_مليو,         "Filter not found")                                             \
    E(داخلا_بدليو,            "Input changed")                                                \
    E(INVALIDDATA,              "Invalid data found when processing input")                     \
    E(MUXER_NOT_مليو,          "Muxer not found")                                              \
    E(OPTION_NOT_مليو,         "Option not found")                                             \
    E(OUTPUT_بدليو,           "Output changed")                                               \
    E(PATCHWELCOME,             "Not yet implemented in FFmpeg, patches welcome")               \
    E(PROTOCOL_NOT_مليو,       "Protocol not found")                                           \
    E(وهڪرو_NOT_مليو,         "Stream not found")                                             \
    E(UNKNOWN,                  "Unknown error occurred")                                       \
    E(EXPERIMENTAL,             "Experimental feature")                                         \
    E(داخلا_AND_OUTPUT_بدليو, "Input and output changed")                                     \
    E(HTTP_BAD_REQUEST,         "Server returned 400 Bad Request")                              \
    E(HTTP_UNAUTHORIZED,        "Server returned 401 Unauthorized (authorization failed)")      \
    E(HTTP_FORBIDDEN,           "Server returned 403 Forbidden (access denied)")                \
    E(HTTP_NOT_مليو,           "Server returned 404 Not Found")                                \
    E(HTTP_TOO_MANY_درخواستون,   "Server returned 429 Too Many Requests")                        \
    E(HTTP_OTHER_4XX,           "Server returned 4XX Client Error, but not one of 40{0,1,3,4}") \
    E(HTTP_SERVER_ERROR,        "Server returned 5XX Server Error reply")                       \

#وصف_ڪريو STRERROR_LIST(E)                                                     \
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

تعداد {
#وصف_ڪريو وٿي_2(ڪوڊ_2, DESC)     \
    ERROR_ ## ڪوڊ_2 ## وٿي_3, \
    ERROR_ ## ڪوڊ_2 ## پڇاڙي_وٿي = ERROR_ ## ڪوڊ_2 ## وٿي_3 + حجم(DESC) - 1,
#وصف_ڪريو NOTHING(ڪوڊ_2, CODE2, DESC)
    AVERROR_LIST(وٿي_2, NOTHING)
#إذا !HAVE_STRERROR_R
    STRERROR_LIST(وٿي_2)
#جيڪڏهن_پورو
};

#وصف_ڪريو STRING(ڪوڊ_2, DESC) DESC "\0"
ساكن ثابت حرف error_stringtable[] =
    AVERROR_LIST(STRING, NOTHING)
#إذا !HAVE_STRERROR_R
    STRERROR_LIST(STRING)
#جيڪڏهن_پورو
;

ساكن ثابت بنية Error_داخلا {
    صحيح انگ;
    بنانشان وٿي;
} error_entries[] = {
#وصف_ڪريو داخلا_2(ڪوڊ_2, DESC) { .انگ = AVERROR_ ## ڪوڊ_2, .وٿي = ERROR_ ## ڪوڊ_2 ## وٿي_3 },
#وصف_ڪريو ENTRY2(ڪوڊ_2, CODE2, DESC) { .انگ = AVERROR_ ## ڪوڊ_2, .وٿي = ERROR_ ## CODE2 ## وٿي_3 },
    AVERROR_LIST(داخلا_2, ENTRY2)
#إذا !HAVE_STRERROR_R
#وصف_رد داخلا_2
#وصف_ڪريو داخلا_2(ڪوڊ_2, DESC) { .انگ = AVERROR(ڪوڊ_2), .وٿي = ERROR_ ## ڪوڊ_2 ## وٿي_3 },
    STRERROR_LIST(داخلا_2)
#جيڪڏهن_پورو
};

صحيح av_strerror(صحيح errnum, حرف *errbuf, size_t errbuf_سائيز)
{
    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(error_entries); ++i) {
        إذا (errnum == error_entries[i].انگ) {
            av_strlcpy(errbuf, error_stringtable + error_entries[i].وٿي, errbuf_سائيز);
            أرجع 0;
        }
    }
#إذا HAVE_STRERROR_R
    صحيح ret = AVERROR(strerror_r(AVUNERROR((بنانشان)errnum), errbuf, errbuf_سائيز));
#وإلا
    صحيح ret = -1;
#جيڪڏهن_پورو
    إذا (ret < 0)
        snprintf(errbuf, errbuf_سائيز, "Error number %d occurred", errnum);

    أرجع ret;
}

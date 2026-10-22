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

#تعریف_لغوه GNU_سرچینه
#تعریف_کړه XOPEN_سرچینه 600 /* XSI-compliant version of strerror_r */
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن "config.h"
#ضمن "avstring.h"
#ضمن "error.h"
#ضمن "macros.h"

#تعریف_کړه AVERROR_ننوت_AND_OUTPUT_بدل_شوی (AVERROR_ننوت_بدل_شوی | AVERROR_OUTPUT_بدل_شوی)

#تعریف_کړه AVERROR_LIST(E, E2)                                                                     \
    E(BSF_NOT_وموندل,            "Bitstream filter not found")                                   \
    E(BUG,                      "Internal bug, should not have happened")                       \
    E2(BUG2, BUG,               "Internal bug, should not have happened")                       \
    E(بفر_TOO_SMALL,         "Buffer too small")                                             \
    E(DECODER_NOT_وموندل,        "Decoder not found")                                            \
    E(DEMUXER_NOT_وموندل,        "Demuxer not found")                                            \
    E(ENCODER_NOT_وموندل,        "Encoder not found")                                            \
    E(EOF,                      "End of file")                                                  \
    E(EXIT,                     "Immediate exit requested")                                     \
    E(EXTERNAL,                 "Generic error in an external library")                         \
    E(FILTER_NOT_وموندل,         "Filter not found")                                             \
    E(ننوت_بدل_شوی,            "Input changed")                                                \
    E(INVALIDDATA,              "Invalid data found when processing input")                     \
    E(MUXER_NOT_وموندل,          "Muxer not found")                                              \
    E(OPTION_NOT_وموندل,         "Option not found")                                             \
    E(OUTPUT_بدل_شوی,           "Output changed")                                               \
    E(PATCHWELCOME,             "Not yet implemented in FFmpeg, patches welcome")               \
    E(PROTOCOL_NOT_وموندل,       "Protocol not found")                                           \
    E(بهیر_NOT_وموندل,         "Stream not found")                                             \
    E(UNKNOWN,                  "Unknown error occurred")                                       \
    E(EXPERIMENTAL,             "Experimental feature")                                         \
    E(ننوت_AND_OUTPUT_بدل_شوی, "Input and output changed")                                     \
    E(HTTP_BAD_REQUEST,         "Server returned 400 Bad Request")                              \
    E(HTTP_UNAUTHORIZED,        "Server returned 401 Unauthorized (authorization failed)")      \
    E(HTTP_FORBIDDEN,           "Server returned 403 Forbidden (access denied)")                \
    E(HTTP_NOT_وموندل,           "Server returned 404 Not Found")                                \
    E(HTTP_TOO_MANY_غوښتنې,   "Server returned 429 Too Many Requests")                        \
    E(HTTP_OTHER_4XX,           "Server returned 4XX Client Error, but not one of 40{0,1,3,4}") \
    E(HTTP_SERVER_ERROR,        "Server returned 5XX Server Error reply")                       \

#تعریف_کړه STRERROR_LIST(E)                                                     \
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
#تعریف_کړه دننه_واټن_2(کوډ_2, DESC)     \
    ERROR_ ## کوډ_2 ## دننه_واټن_3, \
    ERROR_ ## کوډ_2 ## پای_ټکی_دننه_واټن = ERROR_ ## کوډ_2 ## دننه_واټن_3 + حجم(DESC) - 1,
#تعریف_کړه NOTHING(کوډ_2, CODE2, DESC)
    AVERROR_LIST(دننه_واټن_2, NOTHING)
#إذا !HAVE_STRERROR_R
    STRERROR_LIST(دننه_واټن_2)
#د_که_پای
};

#تعریف_کړه STRING(کوډ_2, DESC) DESC "\0"
ساكن ثابت حرف error_stringtable[] =
    AVERROR_LIST(STRING, NOTHING)
#إذا !HAVE_STRERROR_R
    STRERROR_LIST(STRING)
#د_که_پای
;

ساكن ثابت بنية Error_ثبت {
    صحيح عدد;
    بینښه دننه_واټن;
} error_entries[] = {
#تعریف_کړه ثبت_2(کوډ_2, DESC) { .عدد = AVERROR_ ## کوډ_2, .دننه_واټن = ERROR_ ## کوډ_2 ## دننه_واټن_3 },
#تعریف_کړه ENTRY2(کوډ_2, CODE2, DESC) { .عدد = AVERROR_ ## کوډ_2, .دننه_واټن = ERROR_ ## CODE2 ## دننه_واټن_3 },
    AVERROR_LIST(ثبت_2, ENTRY2)
#إذا !HAVE_STRERROR_R
#تعریف_لغوه ثبت_2
#تعریف_کړه ثبت_2(کوډ_2, DESC) { .عدد = AVERROR(کوډ_2), .دننه_واټن = ERROR_ ## کوډ_2 ## دننه_واټن_3 },
    STRERROR_LIST(ثبت_2)
#د_که_پای
};

صحيح av_strerror(صحيح errnum, حرف *errbuf, size_t errbuf_اندازه)
{
    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(error_entries); ++i) {
        إذا (errnum == error_entries[i].عدد) {
            av_strlcpy(errbuf, error_stringtable + error_entries[i].دننه_واټن, errbuf_اندازه);
            أرجع 0;
        }
    }
#إذا HAVE_STRERROR_R
    صحيح ret = AVERROR(strerror_r(AVUNERROR((بینښه)errnum), errbuf, errbuf_اندازه));
#وإلا
    صحيح ret = -1;
#د_که_پای
    إذا (ret < 0)
        snprintf(errbuf, errbuf_اندازه, "Error number %d occurred", errnum);

    أرجع ret;
}

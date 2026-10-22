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

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ GNU_ਸਰੋਤ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ XOPEN_ਸਰੋਤ 600 /* XSI-compliant version of strerror_r */
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <string.h>
#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avstring.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "error.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_ਨਿਵੇਸ਼_AND_OUTPUT_ਬਦਲਿਆ (AVERROR_ਨਿਵੇਸ਼_ਬਦਲਿਆ | AVERROR_OUTPUT_ਬਦਲਿਆ)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_LIST(E, E2)                                                                     \
    E(BSF_NOT_ਮਿਲਿਆ,            "Bitstream filter not found")                                   \
    E(BUG,                      "Internal bug, should not have happened")                       \
    E2(BUG2, BUG,               "Internal bug, should not have happened")                       \
    E(ਬਫਰ_TOO_SMALL,         "Buffer too small")                                             \
    E(DECODER_NOT_ਮਿਲਿਆ,        "Decoder not found")                                            \
    E(DEMUXER_NOT_ਮਿਲਿਆ,        "Demuxer not found")                                            \
    E(ENCODER_NOT_ਮਿਲਿਆ,        "Encoder not found")                                            \
    E(EOF,                      "End of file")                                                  \
    E(EXIT,                     "Immediate exit requested")                                     \
    E(EXTERNAL,                 "Generic error in an external library")                         \
    E(FILTER_NOT_ਮਿਲਿਆ,         "Filter not found")                                             \
    E(ਨਿਵੇਸ਼_ਬਦਲਿਆ,            "Input changed")                                                \
    E(INVALIDDATA,              "Invalid data found when processing input")                     \
    E(MUXER_NOT_ਮਿਲਿਆ,          "Muxer not found")                                              \
    E(OPTION_NOT_ਮਿਲਿਆ,         "Option not found")                                             \
    E(OUTPUT_ਬਦਲਿਆ,           "Output changed")                                               \
    E(PATCHWELCOME,             "Not yet implemented in FFmpeg, patches welcome")               \
    E(PROTOCOL_NOT_ਮਿਲਿਆ,       "Protocol not found")                                           \
    E(ਧਾਰਾ_NOT_ਮਿਲਿਆ,         "Stream not found")                                             \
    E(UNKNOWN,                  "Unknown error occurred")                                       \
    E(EXPERIMENTAL,             "Experimental feature")                                         \
    E(ਨਿਵੇਸ਼_AND_OUTPUT_ਬਦਲਿਆ, "Input and output changed")                                     \
    E(HTTP_BAD_REQUEST,         "Server returned 400 Bad Request")                              \
    E(HTTP_UNAUTHORIZED,        "Server returned 401 Unauthorized (authorization failed)")      \
    E(HTTP_FORBIDDEN,           "Server returned 403 Forbidden (access denied)")                \
    E(HTTP_NOT_ਮਿਲਿਆ,           "Server returned 404 Not Found")                                \
    E(HTTP_TOO_MANY_ਬੇਨਤੀਆਂ,   "Server returned 429 Too Many Requests")                        \
    E(HTTP_OTHER_4XX,           "Server returned 4XX Client Error, but not one of 40{0,1,3,4}") \
    E(HTTP_SERVER_ERROR,        "Server returned 5XX Server Error reply")                       \

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRERROR_LIST(E)                                                     \
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

ਗਿਣਤੀ {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਵਿੱਥ_2(ਕੋਡ_2, DESC)     \
    ERROR_ ## ਕੋਡ_2 ## ਵਿੱਥ_3, \
    ERROR_ ## ਕੋਡ_2 ## ਸਿਰਾ_ਵਿੱਥ = ERROR_ ## ਕੋਡ_2 ## ਵਿੱਥ_3 + ਆਕਾਰ(DESC) - 1,
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ NOTHING(ਕੋਡ_2, CODE2, DESC)
    AVERROR_LIST(ਵਿੱਥ_2, NOTHING)
#ਜੇ !HAVE_STRERROR_R
    STRERROR_LIST(ਵਿੱਥ_2)
#ਜੇ_ਅੰਤ
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ STRING(ਕੋਡ_2, DESC) DESC "\0"
ਸਥਿਰ ਅਚਲ ਅੱਖਰ error_stringtable[] =
    AVERROR_LIST(STRING, NOTHING)
#ਜੇ !HAVE_STRERROR_R
    STRERROR_LIST(STRING)
#ਜੇ_ਅੰਤ
;

ਸਥਿਰ ਅਚਲ ਬਣਤਰ Error_ਇੰਦਰਾਜ {
    ਪੂਰਨ ਅੰਕ;
    ਬਿਨਾਨਿਸ਼ਾਨੀ ਵਿੱਥ;
} error_entries[] = {
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਇੰਦਰਾਜ_2(ਕੋਡ_2, DESC) { .ਅੰਕ = AVERROR_ ## ਕੋਡ_2, .ਵਿੱਥ = ERROR_ ## ਕੋਡ_2 ## ਵਿੱਥ_3 },
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENTRY2(ਕੋਡ_2, CODE2, DESC) { .ਅੰਕ = AVERROR_ ## ਕੋਡ_2, .ਵਿੱਥ = ERROR_ ## CODE2 ## ਵਿੱਥ_3 },
    AVERROR_LIST(ਇੰਦਰਾਜ_2, ENTRY2)
#ਜੇ !HAVE_STRERROR_R
#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ ਇੰਦਰਾਜ_2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਇੰਦਰਾਜ_2(ਕੋਡ_2, DESC) { .ਅੰਕ = AVERROR(ਕੋਡ_2), .ਵਿੱਥ = ERROR_ ## ਕੋਡ_2 ## ਵਿੱਥ_3 },
    STRERROR_LIST(ਇੰਦਰਾਜ_2)
#ਜੇ_ਅੰਤ
};

ਪੂਰਨ av_strerror(ਪੂਰਨ errnum, ਅੱਖਰ *errbuf, size_t errbuf_ਮਾਪ)
{
    ਲਈ (size_t i = 0; i < FF_ARRAY_ELEMS(error_entries); ++i) {
        ਜੇ (errnum == error_entries[i].ਅੰਕ) {
            av_strlcpy(errbuf, error_stringtable + error_entries[i].ਵਿੱਥ, errbuf_ਮਾਪ);
            ਵਾਪਸ 0;
        }
    }
#ਜੇ HAVE_STRERROR_R
    ਪੂਰਨ ret = AVERROR(strerror_r(AVUNERROR((ਬਿਨਾਨਿਸ਼ਾਨੀ)errnum), errbuf, errbuf_ਮਾਪ));
#ਨਹੀਂਤਾਂ
    ਪੂਰਨ ret = -1;
#ਜੇ_ਅੰਤ
    ਜੇ (ret < 0)
        snprintf(errbuf, errbuf_ਮਾਪ, "Error number %d occurred", errnum);

    ਵਾਪਸ ret;
}

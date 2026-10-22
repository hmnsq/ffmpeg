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

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು GNU_ಮೂಲ
#ವ್ಯಾಖ್ಯಾನಿಸು XOPEN_ಮೂಲ 600 /* XSI-compliant version of strerror_r */
#ಅನ್ತರ್ಭಾವ <stdio.h>
#ಅನ್ತರ್ಭಾವ <string.h>
#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "avstring.h"
#ಅನ್ತರ್ಭಾವ "error.h"
#ಅನ್ತರ್ಭಾವ "macros.h"

#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_ಒಳಹರಿವು_AND_OUTPUT_ಬದಲಾಯಿತು (AVERROR_ಒಳಹರಿವು_ಬದಲಾಯಿತು | AVERROR_OUTPUT_ಬದಲಾಯಿತು)

#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_LIST(E, E2)                                                                     \
    E(BSF_NOT_ಸಿಕ್ಕಿತು,            "Bitstream filter not found")                                   \
    E(BUG,                      "Internal bug, should not have happened")                       \
    E2(BUG2, BUG,               "Internal bug, should not have happened")                       \
    E(ಬಫರ್_TOO_SMALL,         "Buffer too small")                                             \
    E(DECODER_NOT_ಸಿಕ್ಕಿತು,        "Decoder not found")                                            \
    E(DEMUXER_NOT_ಸಿಕ್ಕಿತು,        "Demuxer not found")                                            \
    E(ENCODER_NOT_ಸಿಕ್ಕಿತು,        "Encoder not found")                                            \
    E(EOF,                      "End of file")                                                  \
    E(EXIT,                     "Immediate exit requested")                                     \
    E(EXTERNAL,                 "Generic error in an external library")                         \
    E(FILTER_NOT_ಸಿಕ್ಕಿತು,         "Filter not found")                                             \
    E(ಒಳಹರಿವು_ಬದಲಾಯಿತು,            "Input changed")                                                \
    E(INVALIDDATA,              "Invalid data found when processing input")                     \
    E(MUXER_NOT_ಸಿಕ್ಕಿತು,          "Muxer not found")                                              \
    E(OPTION_NOT_ಸಿಕ್ಕಿತು,         "Option not found")                                             \
    E(OUTPUT_ಬದಲಾಯಿತು,           "Output changed")                                               \
    E(PATCHWELCOME,             "Not yet implemented in FFmpeg, patches welcome")               \
    E(PROTOCOL_NOT_ಸಿಕ್ಕಿತು,       "Protocol not found")                                           \
    E(ಹರಿವು_NOT_ಸಿಕ್ಕಿತು,         "Stream not found")                                             \
    E(UNKNOWN,                  "Unknown error occurred")                                       \
    E(EXPERIMENTAL,             "Experimental feature")                                         \
    E(ಒಳಹರಿವು_AND_OUTPUT_ಬದಲಾಯಿತು, "Input and output changed")                                     \
    E(HTTP_BAD_REQUEST,         "Server returned 400 Bad Request")                              \
    E(HTTP_UNAUTHORIZED,        "Server returned 401 Unauthorized (authorization failed)")      \
    E(HTTP_FORBIDDEN,           "Server returned 403 Forbidden (access denied)")                \
    E(HTTP_NOT_ಸಿಕ್ಕಿತು,           "Server returned 404 Not Found")                                \
    E(HTTP_TOO_MANY_ವಿನಂತಿಗಳು,   "Server returned 429 Too Many Requests")                        \
    E(HTTP_OTHER_4XX,           "Server returned 4XX Client Error, but not one of 40{0,1,3,4}") \
    E(HTTP_SERVER_ERROR,        "Server returned 5XX Server Error reply")                       \

#ವ್ಯಾಖ್ಯಾನಿಸು STRERROR_LIST(E)                                                     \
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

ಎಣಿಕೆ {
#ವ್ಯಾಖ್ಯಾನಿಸು ಸ್ಥಾನಾಂತರ_2(ಸಂಕೇತ_3, DESC)     \
    ERROR_ ## ಸಂಕೇತ_3 ## ಸ್ಥಾನಾಂತರ_3, \
    ERROR_ ## ಸಂಕೇತ_3 ## ಕೊನೆ_ಸ್ಥಾನಾಂತರ = ERROR_ ## ಸಂಕೇತ_3 ## ಸ್ಥಾನಾಂತರ_3 + ಗಾತ್ರ(DESC) - 1,
#ವ್ಯಾಖ್ಯಾನಿಸು NOTHING(ಸಂಕೇತ_3, CODE2, DESC)
    AVERROR_LIST(ಸ್ಥಾನಾಂತರ_2, NOTHING)
#ಆದರೆ !HAVE_STRERROR_R
    STRERROR_LIST(ಸ್ಥಾನಾಂತರ_2)
#ಆದರೆ_ಅಂತ್ಯ
};

#ವ್ಯಾಖ್ಯಾನಿಸು STRING(ಸಂಕೇತ_3, DESC) DESC "\0"
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ error_stringtable[] =
    AVERROR_LIST(STRING, NOTHING)
#ಆದರೆ !HAVE_STRERROR_R
    STRERROR_LIST(STRING)
#ಆದರೆ_ಅಂತ್ಯ
;

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ Error_ನಮೂದು {
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ;
    ಚಿಹ್ನೆರಹಿತ ಸ್ಥಾನಾಂತರ;
} error_entries[] = {
#ವ್ಯಾಖ್ಯಾನಿಸು ನಮೂದು_2(ಸಂಕೇತ_3, DESC) { .ಅಂಕೆ = AVERROR_ ## ಸಂಕೇತ_3, .ಸ್ಥಾನಾಂತರ = ERROR_ ## ಸಂಕೇತ_3 ## ಸ್ಥಾನಾಂತರ_3 },
#ವ್ಯಾಖ್ಯಾನಿಸು ENTRY2(ಸಂಕೇತ_3, CODE2, DESC) { .ಅಂಕೆ = AVERROR_ ## ಸಂಕೇತ_3, .ಸ್ಥಾನಾಂತರ = ERROR_ ## CODE2 ## ಸ್ಥಾನಾಂತರ_3 },
    AVERROR_LIST(ನಮೂದು_2, ENTRY2)
#ಆದರೆ !HAVE_STRERROR_R
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು ನಮೂದು_2
#ವ್ಯಾಖ್ಯಾನಿಸು ನಮೂದು_2(ಸಂಕೇತ_3, DESC) { .ಅಂಕೆ = AVERROR(ಸಂಕೇತ_3), .ಸ್ಥಾನಾಂತರ = ERROR_ ## ಸಂಕೇತ_3 ## ಸ್ಥಾನಾಂತರ_3 },
    STRERROR_LIST(ನಮೂದು_2)
#ಆದರೆ_ಅಂತ್ಯ
};

ಪೂರ್ಣಾಂಕ av_strerror(ಪೂರ್ಣಾಂಕ errnum, ಅಕ್ಷರ *errbuf, size_t errbuf_ಗಾತ್ರ)
{
    ಗಾಗಿ (size_t i = 0; i < FF_ARRAY_ELEMS(error_entries); ++i) {
        ಆದರೆ (errnum == error_entries[i].ಅಂಕೆ) {
            av_strlcpy(errbuf, error_stringtable + error_entries[i].ಸ್ಥಾನಾಂತರ, errbuf_ಗಾತ್ರ);
            ಹಿಂತಿರುಗಿ 0;
        }
    }
#ಆದರೆ HAVE_STRERROR_R
    ಪೂರ್ಣಾಂಕ ret = AVERROR(strerror_r(AVUNERROR((ಚಿಹ್ನೆರಹಿತ)errnum), errbuf, errbuf_ಗಾತ್ರ));
#ಇಲ್ಲದಿದ್ದರೆ
    ಪೂರ್ಣಾಂಕ ret = -1;
#ಆದರೆ_ಅಂತ್ಯ
    ಆದರೆ (ret < 0)
        snprintf(errbuf, errbuf_ಗಾತ್ರ, "Error number %d occurred", errnum);

    ಹಿಂತಿರುಗಿ ret;
}

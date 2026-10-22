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

#لغو_تعریف GNU_منبع
#تعریف_کن XOPEN_منبع 600 /* XSI-compliant version of strerror_r */
#ضمن <stdio.h>
#ضمن <string.h>
#ضمن "config.h"
#ضمن "avstring.h"
#ضمن "error.h"
#ضمن "macros.h"

#تعریف_کن AVERROR_درون_داد_AND_OUTPUT_تغییریافته (AVERROR_درون_داد_تغییریافته | AVERROR_OUTPUT_تغییریافته)

#تعریف_کن AVERROR_LIST(E, E2)                                                                     \
    E(BSF_NOT_یافت,            "Bitstream filter not found")                                   \
    E(BUG,                      "Internal bug, should not have happened")                       \
    E2(BUG2, BUG,               "Internal bug, should not have happened")                       \
    E(میانگیر_TOO_SMALL,         "Buffer too small")                                             \
    E(DECODER_NOT_یافت,        "Decoder not found")                                            \
    E(DEMUXER_NOT_یافت,        "Demuxer not found")                                            \
    E(ENCODER_NOT_یافت,        "Encoder not found")                                            \
    E(EOF,                      "End of file")                                                  \
    E(EXIT,                     "Immediate exit requested")                                     \
    E(EXTERNAL,                 "Generic error in an external library")                         \
    E(FILTER_NOT_یافت,         "Filter not found")                                             \
    E(درون_داد_تغییریافته,            "Input changed")                                                \
    E(INVALIDDATA,              "Invalid data found when processing input")                     \
    E(MUXER_NOT_یافت,          "Muxer not found")                                              \
    E(OPTION_NOT_یافت,         "Option not found")                                             \
    E(OUTPUT_تغییریافته,           "Output changed")                                               \
    E(PATCHWELCOME,             "Not yet implemented in FFmpeg, patches welcome")               \
    E(PROTOCOL_NOT_یافت,       "Protocol not found")                                           \
    E(جریان_NOT_یافت,         "Stream not found")                                             \
    E(UNKNOWN,                  "Unknown error occurred")                                       \
    E(EXPERIMENTAL,             "Experimental feature")                                         \
    E(درون_داد_AND_OUTPUT_تغییریافته, "Input and output changed")                                     \
    E(HTTP_BAD_REQUEST,         "Server returned 400 Bad Request")                              \
    E(HTTP_UNAUTHORIZED,        "Server returned 401 Unauthorized (authorization failed)")      \
    E(HTTP_FORBIDDEN,           "Server returned 403 Forbidden (access denied)")                \
    E(HTTP_NOT_یافت,           "Server returned 404 Not Found")                                \
    E(HTTP_TOO_MANY_درخواستها,   "Server returned 429 Too Many Requests")                        \
    E(HTTP_OTHER_4XX,           "Server returned 4XX Client Error, but not one of 40{0,1,3,4}") \
    E(HTTP_SERVER_ERROR,        "Server returned 5XX Server Error reply")                       \

#تعریف_کن STRERROR_LIST(E)                                                     \
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
#تعریف_کن جابه_جایی_2(کد_2, DESC)     \
    ERROR_ ## کد_2 ## جابه_جایی_3, \
    ERROR_ ## کد_2 ## انتها_جابه_جایی = ERROR_ ## کد_2 ## جابه_جایی_3 + حجم(DESC) - 1,
#تعریف_کن NOTHING(کد_2, CODE2, DESC)
    AVERROR_LIST(جابه_جایی_2, NOTHING)
#إذا !HAVE_STRERROR_R
    STRERROR_LIST(جابه_جایی_2)
#پایان_اگر
};

#تعریف_کن STRING(کد_2, DESC) DESC "\0"
ساكن ثابت حرف error_stringtable[] =
    AVERROR_LIST(STRING, NOTHING)
#إذا !HAVE_STRERROR_R
    STRERROR_LIST(STRING)
#پایان_اگر
;

ساكن ثابت بنية Error_مدخل {
    صحيح رقم;
    بیعلامت جابه_جایی;
} error_entries[] = {
#تعریف_کن مدخل_2(کد_2, DESC) { .رقم = AVERROR_ ## کد_2, .جابه_جایی = ERROR_ ## کد_2 ## جابه_جایی_3 },
#تعریف_کن ENTRY2(کد_2, CODE2, DESC) { .رقم = AVERROR_ ## کد_2, .جابه_جایی = ERROR_ ## CODE2 ## جابه_جایی_3 },
    AVERROR_LIST(مدخل_2, ENTRY2)
#إذا !HAVE_STRERROR_R
#لغو_تعریف مدخل_2
#تعریف_کن مدخل_2(کد_2, DESC) { .رقم = AVERROR(کد_2), .جابه_جایی = ERROR_ ## کد_2 ## جابه_جایی_3 },
    STRERROR_LIST(مدخل_2)
#پایان_اگر
};

صحيح av_strerror(صحيح errnum, حرف *errbuf, size_t errbuf_اندازه)
{
    لكل (size_t i = 0; i < FF_ARRAY_ELEMS(error_entries); ++i) {
        إذا (errnum == error_entries[i].رقم) {
            av_strlcpy(errbuf, error_stringtable + error_entries[i].جابه_جایی, errbuf_اندازه);
            أرجع 0;
        }
    }
#إذا HAVE_STRERROR_R
    صحيح ret = AVERROR(strerror_r(AVUNERROR((بیعلامت)errnum), errbuf, errbuf_اندازه));
#وإلا
    صحيح ret = -1;
#پایان_اگر
    إذا (ret < 0)
        snprintf(errbuf, errbuf_اندازه, "Error number %d occurred", errnum);

    أرجع ret;
}

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

#నిర్వచనం_రద్దు GNU_ఆధారం
#నిర్వచించు XOPEN_ఆధారం 600 /* XSI-compliant version of strerror_r */
#అన్తర్భావ <stdio.h>
#అన్తర్భావ <string.h>
#అన్తర్భావ "config.h"
#అన్తర్భావ "avstring.h"
#అన్తర్భావ "error.h"
#అన్తర్భావ "macros.h"

#నిర్వచించు AVERROR_ఆదానం_AND_OUTPUT_మారింది (AVERROR_ఆదానం_మారింది | AVERROR_OUTPUT_మారింది)

#నిర్వచించు AVERROR_LIST(E, E2)                                                                     \
    E(BSF_NOT_దొరికింది,            "Bitstream filter not found")                                   \
    E(BUG,                      "Internal bug, should not have happened")                       \
    E2(BUG2, BUG,               "Internal bug, should not have happened")                       \
    E(బఫరు_TOO_SMALL,         "Buffer too small")                                             \
    E(DECODER_NOT_దొరికింది,        "Decoder not found")                                            \
    E(DEMUXER_NOT_దొరికింది,        "Demuxer not found")                                            \
    E(ENCODER_NOT_దొరికింది,        "Encoder not found")                                            \
    E(EOF,                      "End of file")                                                  \
    E(EXIT,                     "Immediate exit requested")                                     \
    E(EXTERNAL,                 "Generic error in an external library")                         \
    E(FILTER_NOT_దొరికింది,         "Filter not found")                                             \
    E(ఆదానం_మారింది,            "Input changed")                                                \
    E(INVALIDDATA,              "Invalid data found when processing input")                     \
    E(MUXER_NOT_దొరికింది,          "Muxer not found")                                              \
    E(OPTION_NOT_దొరికింది,         "Option not found")                                             \
    E(OUTPUT_మారింది,           "Output changed")                                               \
    E(PATCHWELCOME,             "Not yet implemented in FFmpeg, patches welcome")               \
    E(PROTOCOL_NOT_దొరికింది,       "Protocol not found")                                           \
    E(ప్రవాహం_NOT_దొరికింది,         "Stream not found")                                             \
    E(UNKNOWN,                  "Unknown error occurred")                                       \
    E(EXPERIMENTAL,             "Experimental feature")                                         \
    E(ఆదానం_AND_OUTPUT_మారింది, "Input and output changed")                                     \
    E(HTTP_BAD_REQUEST,         "Server returned 400 Bad Request")                              \
    E(HTTP_UNAUTHORIZED,        "Server returned 401 Unauthorized (authorization failed)")      \
    E(HTTP_FORBIDDEN,           "Server returned 403 Forbidden (access denied)")                \
    E(HTTP_NOT_దొరికింది,           "Server returned 404 Not Found")                                \
    E(HTTP_TOO_MANY_అభ్యర్థనలు,   "Server returned 429 Too Many Requests")                        \
    E(HTTP_OTHER_4XX,           "Server returned 4XX Client Error, but not one of 40{0,1,3,4}") \
    E(HTTP_SERVER_ERROR,        "Server returned 5XX Server Error reply")                       \

#నిర్వచించు STRERROR_LIST(E)                                                     \
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

గణన {
#నిర్వచించు స్థానభ్రంశం_2(సంకేతం_3, DESC)     \
    ERROR_ ## సంకేతం_3 ## స్థానభ్రంశం_3, \
    ERROR_ ## సంకేతం_3 ## చివర_స్థానభ్రంశం = ERROR_ ## సంకేతం_3 ## స్థానభ్రంశం_3 + పరిమాణం(DESC) - 1,
#నిర్వచించు NOTHING(సంకేతం_3, CODE2, DESC)
    AVERROR_LIST(స్థానభ్రంశం_2, NOTHING)
#ఒకవేళ !HAVE_STRERROR_R
    STRERROR_LIST(స్థానభ్రంశం_2)
#అయితే_ముగింపు
};

#నిర్వచించు STRING(సంకేతం_3, DESC) DESC "\0"
స్థిర స్థిరరాశి అక్షరం error_stringtable[] =
    AVERROR_LIST(STRING, NOTHING)
#ఒకవేళ !HAVE_STRERROR_R
    STRERROR_LIST(STRING)
#అయితే_ముగింపు
;

స్థిర స్థిరరాశి నిర్మాణం Error_నమోదు {
    పూర్ణాంకం అంకె;
    గుర్తులేని స్థానభ్రంశం;
} error_entries[] = {
#నిర్వచించు నమోదు_3(సంకేతం_3, DESC) { .అంకె = AVERROR_ ## సంకేతం_3, .స్థానభ్రంశం = ERROR_ ## సంకేతం_3 ## స్థానభ్రంశం_3 },
#నిర్వచించు ENTRY2(సంకేతం_3, CODE2, DESC) { .అంకె = AVERROR_ ## సంకేతం_3, .స్థానభ్రంశం = ERROR_ ## CODE2 ## స్థానభ్రంశం_3 },
    AVERROR_LIST(నమోదు_3, ENTRY2)
#ఒకవేళ !HAVE_STRERROR_R
#నిర్వచనం_రద్దు నమోదు_3
#నిర్వచించు నమోదు_3(సంకేతం_3, DESC) { .అంకె = AVERROR(సంకేతం_3), .స్థానభ్రంశం = ERROR_ ## సంకేతం_3 ## స్థానభ్రంశం_3 },
    STRERROR_LIST(నమోదు_3)
#అయితే_ముగింపు
};

పూర్ణాంకం av_strerror(పూర్ణాంకం errnum, అక్షరం *errbuf, size_t errbuf_కొలత)
{
    కొరకు (size_t i = 0; i < FF_ARRAY_ELEMS(error_entries); ++i) {
        ఒకవేళ (errnum == error_entries[i].అంకె) {
            av_strlcpy(errbuf, error_stringtable + error_entries[i].స్థానభ్రంశం, errbuf_కొలత);
            తిరిగి 0;
        }
    }
#ఒకవేళ HAVE_STRERROR_R
    పూర్ణాంకం ret = AVERROR(strerror_r(AVUNERROR((గుర్తులేని)errnum), errbuf, errbuf_కొలత));
#లేకపోతే
    పూర్ణాంకం ret = -1;
#అయితే_ముగింపు
    ఒకవేళ (ret < 0)
        snprintf(errbuf, errbuf_కొలత, "Error number %d occurred", errnum);

    తిరిగి ret;
}

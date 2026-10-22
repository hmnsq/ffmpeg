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

/**
 * @file
 * error code definitions
 */

#جيڪڏهن_وصف_نه_ٿيل AVUTIL_ERROR_H
#وصف_ڪريو AVUTIL_ERROR_H

#ضمن <errno.h>
#ضمن <stddef.h>

#ضمن "macros.h"

/**
 * @addtogroup lavu_error
 *
 * @{
 */


/* error handling */
#إذا EDOM > 0
#وصف_ڪريو AVERROR(e) (-(e))   ///< Returns a negative error code from a POSIX error code, to return from library functions.
#وصف_ڪريو AVUNERROR(e) (-(e)) ///< Returns a POSIX error code from a library function error return value.
#وإلا
/* Some platforms have E* and errno already negated. */
#وصف_ڪريو AVERROR(e) (e)
#وصف_ڪريو AVUNERROR(e) (e)
#جيڪڏهن_پورو

#وصف_ڪريو FFERRTAG(a, b, c, d) (-(صحيح)MKTAG(a, b, c, d))

#وصف_ڪريو AVERROR_BSF_NOT_مليو      FFERRTAG(0xF8,'B','S','F') ///< Bitstream filter not found
#وصف_ڪريو AVERROR_BUG                FFERRTAG( 'B','U','G','!') ///< Internal bug, also see AVERROR_BUG2
#وصف_ڪريو AVERROR_بفر_TOO_SMALL   FFERRTAG( 'B','U','F','S') ///< Buffer too small
#وصف_ڪريو AVERROR_DECODER_NOT_مليو  FFERRTAG(0xF8,'D','E','C') ///< Decoder not found
#وصف_ڪريو AVERROR_DEMUXER_NOT_مليو  FFERRTAG(0xF8,'D','E','M') ///< Demuxer not found
#وصف_ڪريو AVERROR_ENCODER_NOT_مليو  FFERRTAG(0xF8,'E','N','C') ///< Encoder not found
#وصف_ڪريو AVERROR_EOF                FFERRTAG( 'E','O','F',' ') ///< End of file
#وصف_ڪريو AVERROR_EXIT               FFERRTAG( 'E','X','I','T') ///< Immediate exit was requested; the called function should not be restarted
#وصف_ڪريو AVERROR_EXTERNAL           FFERRTAG( 'E','X','T',' ') ///< Generic error in an external library
#وصف_ڪريو AVERROR_FILTER_NOT_مليو   FFERRTAG(0xF8,'F','I','L') ///< Filter not found
#وصف_ڪريو AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A') ///< Invalid data found when processing input
#وصف_ڪريو AVERROR_MUXER_NOT_مليو    FFERRTAG(0xF8,'M','U','X') ///< Muxer not found
#وصف_ڪريو AVERROR_OPTION_NOT_مليو   FFERRTAG(0xF8,'O','P','T') ///< Option not found
#وصف_ڪريو AVERROR_PATCHWELCOME       FFERRTAG( 'P','A','W','E') ///< Not yet implemented in FFmpeg, patches welcome
#وصف_ڪريو AVERROR_PROTOCOL_NOT_مليو FFERRTAG(0xF8,'P','R','O') ///< Protocol not found

#وصف_ڪريو AVERROR_وهڪرو_NOT_مليو   FFERRTAG(0xF8,'S','T','R') ///< Stream not found
/**
 * This is semantically identical to AVERROR_BUG
 * it has been introduced in Libav after our AVERROR_BUG and with a modified value.
 */
#وصف_ڪريو AVERROR_BUG2               FFERRTAG( 'B','U','G',' ')
#وصف_ڪريو AVERROR_UNKNOWN            FFERRTAG( 'U','N','K','N') ///< Unknown error, typically from an external library
#وصف_ڪريو AVERROR_EXPERIMENTAL       (-0x2bb2afa8) ///< Requested feature is flagged experimental. Set strict_std_compliance if you really want to use it.
#وصف_ڪريو AVERROR_داخلا_بدليو      (-0x636e6701) ///< Input changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_OUTPUT_CHANGED)
#وصف_ڪريو AVERROR_OUTPUT_بدليو     (-0x636e6702) ///< Output changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_INPUT_CHANGED)
/* HTTP & RTSP errors */
#وصف_ڪريو AVERROR_HTTP_BAD_REQUEST   FFERRTAG(0xF8,'4','0','0')
#وصف_ڪريو AVERROR_HTTP_UNAUTHORIZED  FFERRTAG(0xF8,'4','0','1')
#وصف_ڪريو AVERROR_HTTP_FORBIDDEN     FFERRTAG(0xF8,'4','0','3')
#وصف_ڪريو AVERROR_HTTP_NOT_مليو     FFERRTAG(0xF8,'4','0','4')
#وصف_ڪريو AVERROR_HTTP_TOO_MANY_درخواستون FFERRTAG(0xF8,'4','2','9')
#وصف_ڪريو AVERROR_HTTP_OTHER_4XX     FFERRTAG(0xF8,'4','X','X')
#وصف_ڪريو AVERROR_HTTP_SERVER_ERROR  FFERRTAG(0xF8,'5','X','X')

#وصف_ڪريو AV_ERROR_MAX_STRING_سائيز 64

/**
 * Put a description of the AVERROR code errnum in errbuf.
 * In case of failure the global variable errno is set to indicate the
 * error. Even in case of failure av_strerror() will print a generic
 * error message indicating the errnum provided to errbuf.
 *
 * @param errnum      error code to describe
 * @param errbuf      buffer to which description is written
 * @param errbuf_size the size in bytes of errbuf
 * @return 0 on success, a negative value if a description for errnum
 * cannot be found
 */
صحيح av_strerror(صحيح errnum, حرف *errbuf, size_t errbuf_سائيز);

/**
 * Fill the provided buffer with a string containing an error string
 * corresponding to the AVERROR code errnum.
 *
 * @param errbuf         a buffer
 * @param errbuf_size    size in bytes of errbuf
 * @param errnum         error code to describe
 * @return the buffer in input, filled with the error description
 * @see av_strerror()
 */
ساكن مضمن حرف *av_make_error_string(حرف *errbuf, size_t errbuf_سائيز, صحيح errnum)
{
    av_strerror(errnum, errbuf, errbuf_سائيز);
    أرجع errbuf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#وصف_ڪريو av_err2str(errnum) \
    av_make_error_string((حرف[AV_ERROR_MAX_STRING_سائيز]){0}, AV_ERROR_MAX_STRING_سائيز, errnum)

/**
 * @}
 */

#جيڪڏهن_پورو /* AVUTIL_ERROR_H */

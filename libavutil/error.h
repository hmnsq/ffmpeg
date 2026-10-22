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

#నిర్వచితం_కాకపోతే AVUTIL_ERROR_H
#నిర్వచించు AVUTIL_ERROR_H

#అన్తర్భావ <errno.h>
#అన్తర్భావ <stddef.h>

#అన్తర్భావ "macros.h"

/**
 * @addtogroup lavu_error
 *
 * @{
 */


/* error handling */
#ఒకవేళ EDOM > 0
#నిర్వచించు AVERROR(e) (-(e))   ///< Returns a negative error code from a POSIX error code, to return from library functions.
#నిర్వచించు AVUNERROR(e) (-(e)) ///< Returns a POSIX error code from a library function error return value.
#లేకపోతే
/* Some platforms have E* and errno already negated. */
#నిర్వచించు AVERROR(e) (e)
#నిర్వచించు AVUNERROR(e) (e)
#అయితే_ముగింపు

#నిర్వచించు FFERRTAG(a, b, c, d) (-(పూర్ణాంకం)MKTAG(a, b, c, d))

#నిర్వచించు AVERROR_BSF_NOT_దొరికింది      FFERRTAG(0xF8,'B','S','F') ///< Bitstream filter not found
#నిర్వచించు AVERROR_BUG                FFERRTAG( 'B','U','G','!') ///< Internal bug, also see AVERROR_BUG2
#నిర్వచించు AVERROR_బఫరు_TOO_SMALL   FFERRTAG( 'B','U','F','S') ///< Buffer too small
#నిర్వచించు AVERROR_DECODER_NOT_దొరికింది  FFERRTAG(0xF8,'D','E','C') ///< Decoder not found
#నిర్వచించు AVERROR_DEMUXER_NOT_దొరికింది  FFERRTAG(0xF8,'D','E','M') ///< Demuxer not found
#నిర్వచించు AVERROR_ENCODER_NOT_దొరికింది  FFERRTAG(0xF8,'E','N','C') ///< Encoder not found
#నిర్వచించు AVERROR_EOF                FFERRTAG( 'E','O','F',' ') ///< End of file
#నిర్వచించు AVERROR_EXIT               FFERRTAG( 'E','X','I','T') ///< Immediate exit was requested; the called function should not be restarted
#నిర్వచించు AVERROR_EXTERNAL           FFERRTAG( 'E','X','T',' ') ///< Generic error in an external library
#నిర్వచించు AVERROR_FILTER_NOT_దొరికింది   FFERRTAG(0xF8,'F','I','L') ///< Filter not found
#నిర్వచించు AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A') ///< Invalid data found when processing input
#నిర్వచించు AVERROR_MUXER_NOT_దొరికింది    FFERRTAG(0xF8,'M','U','X') ///< Muxer not found
#నిర్వచించు AVERROR_OPTION_NOT_దొరికింది   FFERRTAG(0xF8,'O','P','T') ///< Option not found
#నిర్వచించు AVERROR_PATCHWELCOME       FFERRTAG( 'P','A','W','E') ///< Not yet implemented in FFmpeg, patches welcome
#నిర్వచించు AVERROR_PROTOCOL_NOT_దొరికింది FFERRTAG(0xF8,'P','R','O') ///< Protocol not found

#నిర్వచించు AVERROR_ప్రవాహం_NOT_దొరికింది   FFERRTAG(0xF8,'S','T','R') ///< Stream not found
/**
 * This is semantically identical to AVERROR_BUG
 * it has been introduced in Libav after our AVERROR_BUG and with a modified value.
 */
#నిర్వచించు AVERROR_BUG2               FFERRTAG( 'B','U','G',' ')
#నిర్వచించు AVERROR_UNKNOWN            FFERRTAG( 'U','N','K','N') ///< Unknown error, typically from an external library
#నిర్వచించు AVERROR_EXPERIMENTAL       (-0x2bb2afa8) ///< Requested feature is flagged experimental. Set strict_std_compliance if you really want to use it.
#నిర్వచించు AVERROR_ఆదానం_మారింది      (-0x636e6701) ///< Input changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_OUTPUT_CHANGED)
#నిర్వచించు AVERROR_OUTPUT_మారింది     (-0x636e6702) ///< Output changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_INPUT_CHANGED)
/* HTTP & RTSP errors */
#నిర్వచించు AVERROR_HTTP_BAD_REQUEST   FFERRTAG(0xF8,'4','0','0')
#నిర్వచించు AVERROR_HTTP_UNAUTHORIZED  FFERRTAG(0xF8,'4','0','1')
#నిర్వచించు AVERROR_HTTP_FORBIDDEN     FFERRTAG(0xF8,'4','0','3')
#నిర్వచించు AVERROR_HTTP_NOT_దొరికింది     FFERRTAG(0xF8,'4','0','4')
#నిర్వచించు AVERROR_HTTP_TOO_MANY_అభ్యర్థనలు FFERRTAG(0xF8,'4','2','9')
#నిర్వచించు AVERROR_HTTP_OTHER_4XX     FFERRTAG(0xF8,'4','X','X')
#నిర్వచించు AVERROR_HTTP_SERVER_ERROR  FFERRTAG(0xF8,'5','X','X')

#నిర్వచించు AV_ERROR_MAX_STRING_కొలత 64

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
పూర్ణాంకం av_strerror(పూర్ణాంకం errnum, అక్షరం *errbuf, size_t errbuf_కొలత);

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
స్థిర అంతఃవరుస అక్షరం *av_make_error_string(అక్షరం *errbuf, size_t errbuf_కొలత, పూర్ణాంకం errnum)
{
    av_strerror(errnum, errbuf, errbuf_కొలత);
    తిరిగి errbuf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#నిర్వచించు av_err2str(errnum) \
    av_make_error_string((అక్షరం[AV_ERROR_MAX_STRING_కొలత]){0}, AV_ERROR_MAX_STRING_కొలత, errnum)

/**
 * @}
 */

#అయితే_ముగింపు /* AVUTIL_ERROR_H */

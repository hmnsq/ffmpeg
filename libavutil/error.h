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

#यदि_अपरिभाषितम् AVUTIL_ERROR_H
#परिभाषय AVUTIL_ERROR_H

#अन्तर्भाव <errno.h>
#अन्तर्भाव <stddef.h>

#अन्तर्भाव "macros.h"

/**
 * @addtogroup lavu_error
 *
 * @{
 */


/* error handling */
#यदि EDOM > 0
#परिभाषय AVERROR(e) (-(e))   ///< Returns a negative error code from a POSIX error code, to return from library functions.
#परिभाषय AVUNERROR(e) (-(e)) ///< Returns a POSIX error code from a library function error return value.
#अन्यथा
/* Some platforms have E* and errno already negated. */
#परिभाषय AVERROR(e) (e)
#परिभाषय AVUNERROR(e) (e)
#यदि_अन्तः

#परिभाषय FFERRTAG(a, b, c, d) (-(पूर्णाङ्क)MKTAG(a, b, c, d))

#परिभाषय AVERROR_BSF_NOT_प्राप्तम्      FFERRTAG(0xF8,'B','S','F') ///< Bitstream filter not found
#परिभाषय AVERROR_BUG                FFERRTAG( 'B','U','G','!') ///< Internal bug, also see AVERROR_BUG2
#परिभाषय AVERROR_बफर_TOO_SMALL   FFERRTAG( 'B','U','F','S') ///< Buffer too small
#परिभाषय AVERROR_DECODER_NOT_प्राप्तम्  FFERRTAG(0xF8,'D','E','C') ///< Decoder not found
#परिभाषय AVERROR_DEMUXER_NOT_प्राप्तम्  FFERRTAG(0xF8,'D','E','M') ///< Demuxer not found
#परिभाषय AVERROR_ENCODER_NOT_प्राप्तम्  FFERRTAG(0xF8,'E','N','C') ///< Encoder not found
#परिभाषय AVERROR_EOF                FFERRTAG( 'E','O','F',' ') ///< End of file
#परिभाषय AVERROR_EXIT               FFERRTAG( 'E','X','I','T') ///< Immediate exit was requested; the called function should not be restarted
#परिभाषय AVERROR_EXTERNAL           FFERRTAG( 'E','X','T',' ') ///< Generic error in an external library
#परिभाषय AVERROR_FILTER_NOT_प्राप्तम्   FFERRTAG(0xF8,'F','I','L') ///< Filter not found
#परिभाषय AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A') ///< Invalid data found when processing input
#परिभाषय AVERROR_MUXER_NOT_प्राप्तम्    FFERRTAG(0xF8,'M','U','X') ///< Muxer not found
#परिभाषय AVERROR_OPTION_NOT_प्राप्तम्   FFERRTAG(0xF8,'O','P','T') ///< Option not found
#परिभाषय AVERROR_PATCHWELCOME       FFERRTAG( 'P','A','W','E') ///< Not yet implemented in FFmpeg, patches welcome
#परिभाषय AVERROR_PROTOCOL_NOT_प्राप्तम् FFERRTAG(0xF8,'P','R','O') ///< Protocol not found

#परिभाषय AVERROR_प्रवाहः_NOT_प्राप्तम्   FFERRTAG(0xF8,'S','T','R') ///< Stream not found
/**
 * This is semantically identical to AVERROR_BUG
 * it has been introduced in Libav after our AVERROR_BUG and with a modified value.
 */
#परिभाषय AVERROR_BUG2               FFERRTAG( 'B','U','G',' ')
#परिभाषय AVERROR_UNKNOWN            FFERRTAG( 'U','N','K','N') ///< Unknown error, typically from an external library
#परिभाषय AVERROR_EXPERIMENTAL       (-0x2bb2afa8) ///< Requested feature is flagged experimental. Set strict_std_compliance if you really want to use it.
#परिभाषय AVERROR_निवेशः_परिवर्तितम्      (-0x636e6701) ///< Input changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_OUTPUT_CHANGED)
#परिभाषय AVERROR_OUTPUT_परिवर्तितम्     (-0x636e6702) ///< Output changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_INPUT_CHANGED)
/* HTTP & RTSP errors */
#परिभाषय AVERROR_HTTP_BAD_REQUEST   FFERRTAG(0xF8,'4','0','0')
#परिभाषय AVERROR_HTTP_UNAUTHORIZED  FFERRTAG(0xF8,'4','0','1')
#परिभाषय AVERROR_HTTP_FORBIDDEN     FFERRTAG(0xF8,'4','0','3')
#परिभाषय AVERROR_HTTP_NOT_प्राप्तम्     FFERRTAG(0xF8,'4','0','4')
#परिभाषय AVERROR_HTTP_TOO_MANY_अनुरोधाः FFERRTAG(0xF8,'4','2','9')
#परिभाषय AVERROR_HTTP_OTHER_4XX     FFERRTAG(0xF8,'4','X','X')
#परिभाषय AVERROR_HTTP_SERVER_ERROR  FFERRTAG(0xF8,'5','X','X')

#परिभाषय AV_ERROR_MAX_STRING_आकार 64

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
पूर्णाङ्क av_strerror(पूर्णाङ्क errnum, वर्ण *errbuf, size_t errbuf_आकार);

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
स्थिर अन्तःस्थ वर्ण *av_make_error_string(वर्ण *errbuf, size_t errbuf_आकार, पूर्णाङ्क errnum)
{
    av_strerror(errnum, errbuf, errbuf_आकार);
    प्रत्यागम errbuf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#परिभाषय av_err2str(errnum) \
    av_make_error_string((वर्ण[AV_ERROR_MAX_STRING_आकार]){0}, AV_ERROR_MAX_STRING_आकार, errnum)

/**
 * @}
 */

#यदि_अन्तः /* AVUTIL_ERROR_H */

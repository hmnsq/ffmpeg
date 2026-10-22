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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_ERROR_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_ERROR_H

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stddef.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"

/**
 * @addtogroup lavu_error
 *
 * @{
 */


/* error handling */
#ਜੇ EDOM > 0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR(e) (-(e))   ///< Returns a negative error code from a POSIX error code, to return from library functions.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUNERROR(e) (-(e)) ///< Returns a POSIX error code from a library function error return value.
#ਨਹੀਂਤਾਂ
/* Some platforms have E* and errno already negated. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR(e) (e)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUNERROR(e) (e)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FFERRTAG(a, b, c, d) (-(ਪੂਰਨ)MKTAG(a, b, c, d))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_BSF_NOT_ਮਿਲਿਆ      FFERRTAG(0xF8,'B','S','F') ///< Bitstream filter not found
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_BUG                FFERRTAG( 'B','U','G','!') ///< Internal bug, also see AVERROR_BUG2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_ਬਫਰ_TOO_SMALL   FFERRTAG( 'B','U','F','S') ///< Buffer too small
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_DECODER_NOT_ਮਿਲਿਆ  FFERRTAG(0xF8,'D','E','C') ///< Decoder not found
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_DEMUXER_NOT_ਮਿਲਿਆ  FFERRTAG(0xF8,'D','E','M') ///< Demuxer not found
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_ENCODER_NOT_ਮਿਲਿਆ  FFERRTAG(0xF8,'E','N','C') ///< Encoder not found
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_EOF                FFERRTAG( 'E','O','F',' ') ///< End of file
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_EXIT               FFERRTAG( 'E','X','I','T') ///< Immediate exit was requested; the called function should not be restarted
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_EXTERNAL           FFERRTAG( 'E','X','T',' ') ///< Generic error in an external library
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_FILTER_NOT_ਮਿਲਿਆ   FFERRTAG(0xF8,'F','I','L') ///< Filter not found
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A') ///< Invalid data found when processing input
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_MUXER_NOT_ਮਿਲਿਆ    FFERRTAG(0xF8,'M','U','X') ///< Muxer not found
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_OPTION_NOT_ਮਿਲਿਆ   FFERRTAG(0xF8,'O','P','T') ///< Option not found
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_PATCHWELCOME       FFERRTAG( 'P','A','W','E') ///< Not yet implemented in FFmpeg, patches welcome
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_PROTOCOL_NOT_ਮਿਲਿਆ FFERRTAG(0xF8,'P','R','O') ///< Protocol not found

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_ਧਾਰਾ_NOT_ਮਿਲਿਆ   FFERRTAG(0xF8,'S','T','R') ///< Stream not found
/**
 * This is semantically identical to AVERROR_BUG
 * it has been introduced in Libav after our AVERROR_BUG and with a modified value.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_BUG2               FFERRTAG( 'B','U','G',' ')
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_UNKNOWN            FFERRTAG( 'U','N','K','N') ///< Unknown error, typically from an external library
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_EXPERIMENTAL       (-0x2bb2afa8) ///< Requested feature is flagged experimental. Set strict_std_compliance if you really want to use it.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_ਨਿਵੇਸ਼_ਬਦਲਿਆ      (-0x636e6701) ///< Input changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_OUTPUT_CHANGED)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_OUTPUT_ਬਦਲਿਆ     (-0x636e6702) ///< Output changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_INPUT_CHANGED)
/* HTTP & RTSP errors */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_HTTP_BAD_REQUEST   FFERRTAG(0xF8,'4','0','0')
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_HTTP_UNAUTHORIZED  FFERRTAG(0xF8,'4','0','1')
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_HTTP_FORBIDDEN     FFERRTAG(0xF8,'4','0','3')
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_HTTP_NOT_ਮਿਲਿਆ     FFERRTAG(0xF8,'4','0','4')
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_HTTP_TOO_MANY_ਬੇਨਤੀਆਂ FFERRTAG(0xF8,'4','2','9')
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_HTTP_OTHER_4XX     FFERRTAG(0xF8,'4','X','X')
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVERROR_HTTP_SERVER_ERROR  FFERRTAG(0xF8,'5','X','X')

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_ERROR_MAX_STRING_ਮਾਪ 64

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
ਪੂਰਨ av_strerror(ਪੂਰਨ errnum, ਅੱਖਰ *errbuf, size_t errbuf_ਮਾਪ);

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
ਸਥਿਰ ਸਤਰਅੰਦਰ ਅੱਖਰ *av_make_error_string(ਅੱਖਰ *errbuf, size_t errbuf_ਮਾਪ, ਪੂਰਨ errnum)
{
    av_strerror(errnum, errbuf, errbuf_ਮਾਪ);
    ਵਾਪਸ errbuf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_err2str(errnum) \
    av_make_error_string((ਅੱਖਰ[AV_ERROR_MAX_STRING_ਮਾਪ]){0}, AV_ERROR_MAX_STRING_ਮਾਪ, errnum)

/**
 * @}
 */

#ਜੇ_ਅੰਤ /* AVUTIL_ERROR_H */

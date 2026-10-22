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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ AVUTIL_ERROR_H
#ವ್ಯಾಖ್ಯಾನಿಸು AVUTIL_ERROR_H

#ಅನ್ತರ್ಭಾವ <errno.h>
#ಅನ್ತರ್ಭಾವ <stddef.h>

#ಅನ್ತರ್ಭಾವ "macros.h"

/**
 * @addtogroup lavu_error
 *
 * @{
 */


/* error handling */
#ಆದರೆ EDOM > 0
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR(e) (-(e))   ///< Returns a negative error code from a POSIX error code, to return from library functions.
#ವ್ಯಾಖ್ಯಾನಿಸು AVUNERROR(e) (-(e)) ///< Returns a POSIX error code from a library function error return value.
#ಇಲ್ಲದಿದ್ದರೆ
/* Some platforms have E* and errno already negated. */
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR(e) (e)
#ವ್ಯಾಖ್ಯಾನಿಸು AVUNERROR(e) (e)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು FFERRTAG(a, b, c, d) (-(ಪೂರ್ಣಾಂಕ)MKTAG(a, b, c, d))

#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_BSF_NOT_ಸಿಕ್ಕಿತು      FFERRTAG(0xF8,'B','S','F') ///< Bitstream filter not found
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_BUG                FFERRTAG( 'B','U','G','!') ///< Internal bug, also see AVERROR_BUG2
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_ಬಫರ್_TOO_SMALL   FFERRTAG( 'B','U','F','S') ///< Buffer too small
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_DECODER_NOT_ಸಿಕ್ಕಿತು  FFERRTAG(0xF8,'D','E','C') ///< Decoder not found
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_DEMUXER_NOT_ಸಿಕ್ಕಿತು  FFERRTAG(0xF8,'D','E','M') ///< Demuxer not found
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_ENCODER_NOT_ಸಿಕ್ಕಿತು  FFERRTAG(0xF8,'E','N','C') ///< Encoder not found
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_EOF                FFERRTAG( 'E','O','F',' ') ///< End of file
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_EXIT               FFERRTAG( 'E','X','I','T') ///< Immediate exit was requested; the called function should not be restarted
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_EXTERNAL           FFERRTAG( 'E','X','T',' ') ///< Generic error in an external library
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_FILTER_NOT_ಸಿಕ್ಕಿತು   FFERRTAG(0xF8,'F','I','L') ///< Filter not found
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A') ///< Invalid data found when processing input
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_MUXER_NOT_ಸಿಕ್ಕಿತು    FFERRTAG(0xF8,'M','U','X') ///< Muxer not found
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_OPTION_NOT_ಸಿಕ್ಕಿತು   FFERRTAG(0xF8,'O','P','T') ///< Option not found
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_PATCHWELCOME       FFERRTAG( 'P','A','W','E') ///< Not yet implemented in FFmpeg, patches welcome
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_PROTOCOL_NOT_ಸಿಕ್ಕಿತು FFERRTAG(0xF8,'P','R','O') ///< Protocol not found

#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_ಹರಿವು_NOT_ಸಿಕ್ಕಿತು   FFERRTAG(0xF8,'S','T','R') ///< Stream not found
/**
 * This is semantically identical to AVERROR_BUG
 * it has been introduced in Libav after our AVERROR_BUG and with a modified value.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_BUG2               FFERRTAG( 'B','U','G',' ')
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_UNKNOWN            FFERRTAG( 'U','N','K','N') ///< Unknown error, typically from an external library
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_EXPERIMENTAL       (-0x2bb2afa8) ///< Requested feature is flagged experimental. Set strict_std_compliance if you really want to use it.
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_ಒಳಹರಿವು_ಬದಲಾಯಿತು      (-0x636e6701) ///< Input changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_OUTPUT_CHANGED)
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_OUTPUT_ಬದಲಾಯಿತು     (-0x636e6702) ///< Output changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_INPUT_CHANGED)
/* HTTP & RTSP errors */
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_HTTP_BAD_REQUEST   FFERRTAG(0xF8,'4','0','0')
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_HTTP_UNAUTHORIZED  FFERRTAG(0xF8,'4','0','1')
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_HTTP_FORBIDDEN     FFERRTAG(0xF8,'4','0','3')
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_HTTP_NOT_ಸಿಕ್ಕಿತು     FFERRTAG(0xF8,'4','0','4')
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_HTTP_TOO_MANY_ವಿನಂತಿಗಳು FFERRTAG(0xF8,'4','2','9')
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_HTTP_OTHER_4XX     FFERRTAG(0xF8,'4','X','X')
#ವ್ಯಾಖ್ಯಾನಿಸು AVERROR_HTTP_SERVER_ERROR  FFERRTAG(0xF8,'5','X','X')

#ವ್ಯಾಖ್ಯಾನಿಸು AV_ERROR_MAX_STRING_ಗಾತ್ರ 64

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
ಪೂರ್ಣಾಂಕ av_strerror(ಪೂರ್ಣಾಂಕ errnum, ಅಕ್ಷರ *errbuf, size_t errbuf_ಗಾತ್ರ);

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
ಸ್ಥಿರ ಸಾಲೊಳಗೆ ಅಕ್ಷರ *av_make_error_string(ಅಕ್ಷರ *errbuf, size_t errbuf_ಗಾತ್ರ, ಪೂರ್ಣಾಂಕ errnum)
{
    av_strerror(errnum, errbuf, errbuf_ಗಾತ್ರ);
    ಹಿಂತಿರುಗಿ errbuf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#ವ್ಯಾಖ್ಯಾನಿಸು av_err2str(errnum) \
    av_make_error_string((ಅಕ್ಷರ[AV_ERROR_MAX_STRING_ಗಾತ್ರ]){0}, AV_ERROR_MAX_STRING_ಗಾತ್ರ, errnum)

/**
 * @}
 */

#ಆದರೆ_ಅಂತ್ಯ /* AVUTIL_ERROR_H */

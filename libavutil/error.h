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

#که_نه_تعریف_شوی AVUTIL_ERROR_H
#تعریف_کړه AVUTIL_ERROR_H

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
#تعریف_کړه AVERROR(e) (-(e))   ///< Returns a negative error code from a POSIX error code, to return from library functions.
#تعریف_کړه AVUNERROR(e) (-(e)) ///< Returns a POSIX error code from a library function error return value.
#وإلا
/* Some platforms have E* and errno already negated. */
#تعریف_کړه AVERROR(e) (e)
#تعریف_کړه AVUNERROR(e) (e)
#د_که_پای

#تعریف_کړه FFERRTAG(a, b, c, d) (-(صحيح)MKTAG(a, b, c, d))

#تعریف_کړه AVERROR_BSF_NOT_وموندل      FFERRTAG(0xF8,'B','S','F') ///< Bitstream filter not found
#تعریف_کړه AVERROR_BUG                FFERRTAG( 'B','U','G','!') ///< Internal bug, also see AVERROR_BUG2
#تعریف_کړه AVERROR_بفر_TOO_SMALL   FFERRTAG( 'B','U','F','S') ///< Buffer too small
#تعریف_کړه AVERROR_DECODER_NOT_وموندل  FFERRTAG(0xF8,'D','E','C') ///< Decoder not found
#تعریف_کړه AVERROR_DEMUXER_NOT_وموندل  FFERRTAG(0xF8,'D','E','M') ///< Demuxer not found
#تعریف_کړه AVERROR_ENCODER_NOT_وموندل  FFERRTAG(0xF8,'E','N','C') ///< Encoder not found
#تعریف_کړه AVERROR_EOF                FFERRTAG( 'E','O','F',' ') ///< End of file
#تعریف_کړه AVERROR_EXIT               FFERRTAG( 'E','X','I','T') ///< Immediate exit was requested; the called function should not be restarted
#تعریف_کړه AVERROR_EXTERNAL           FFERRTAG( 'E','X','T',' ') ///< Generic error in an external library
#تعریف_کړه AVERROR_FILTER_NOT_وموندل   FFERRTAG(0xF8,'F','I','L') ///< Filter not found
#تعریف_کړه AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A') ///< Invalid data found when processing input
#تعریف_کړه AVERROR_MUXER_NOT_وموندل    FFERRTAG(0xF8,'M','U','X') ///< Muxer not found
#تعریف_کړه AVERROR_OPTION_NOT_وموندل   FFERRTAG(0xF8,'O','P','T') ///< Option not found
#تعریف_کړه AVERROR_PATCHWELCOME       FFERRTAG( 'P','A','W','E') ///< Not yet implemented in FFmpeg, patches welcome
#تعریف_کړه AVERROR_PROTOCOL_NOT_وموندل FFERRTAG(0xF8,'P','R','O') ///< Protocol not found

#تعریف_کړه AVERROR_بهیر_NOT_وموندل   FFERRTAG(0xF8,'S','T','R') ///< Stream not found
/**
 * This is semantically identical to AVERROR_BUG
 * it has been introduced in Libav after our AVERROR_BUG and with a modified value.
 */
#تعریف_کړه AVERROR_BUG2               FFERRTAG( 'B','U','G',' ')
#تعریف_کړه AVERROR_UNKNOWN            FFERRTAG( 'U','N','K','N') ///< Unknown error, typically from an external library
#تعریف_کړه AVERROR_EXPERIMENTAL       (-0x2bb2afa8) ///< Requested feature is flagged experimental. Set strict_std_compliance if you really want to use it.
#تعریف_کړه AVERROR_ننوت_بدل_شوی      (-0x636e6701) ///< Input changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_OUTPUT_CHANGED)
#تعریف_کړه AVERROR_OUTPUT_بدل_شوی     (-0x636e6702) ///< Output changed between calls. Reconfiguration is required. (can be OR-ed with AVERROR_INPUT_CHANGED)
/* HTTP & RTSP errors */
#تعریف_کړه AVERROR_HTTP_BAD_REQUEST   FFERRTAG(0xF8,'4','0','0')
#تعریف_کړه AVERROR_HTTP_UNAUTHORIZED  FFERRTAG(0xF8,'4','0','1')
#تعریف_کړه AVERROR_HTTP_FORBIDDEN     FFERRTAG(0xF8,'4','0','3')
#تعریف_کړه AVERROR_HTTP_NOT_وموندل     FFERRTAG(0xF8,'4','0','4')
#تعریف_کړه AVERROR_HTTP_TOO_MANY_غوښتنې FFERRTAG(0xF8,'4','2','9')
#تعریف_کړه AVERROR_HTTP_OTHER_4XX     FFERRTAG(0xF8,'4','X','X')
#تعریف_کړه AVERROR_HTTP_SERVER_ERROR  FFERRTAG(0xF8,'5','X','X')

#تعریف_کړه AV_ERROR_MAX_STRING_اندازه 64

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
صحيح av_strerror(صحيح errnum, حرف *errbuf, size_t errbuf_اندازه);

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
ساكن مضمن حرف *av_make_error_string(حرف *errbuf, size_t errbuf_اندازه, صحيح errnum)
{
    av_strerror(errnum, errbuf, errbuf_اندازه);
    أرجع errbuf;
}

/**
 * Convenience macro, the return value should be used only directly in
 * function arguments but never stand-alone.
 */
#تعریف_کړه av_err2str(errnum) \
    av_make_error_string((حرف[AV_ERROR_MAX_STRING_اندازه]){0}, AV_ERROR_MAX_STRING_اندازه, errnum)

/**
 * @}
 */

#د_که_پای /* AVUTIL_ERROR_H */

/*
 * copyright (c) 2006 Michael Niedermayer <michaelni@gmx.at>
 *
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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ AVUTIL_AVUTIL_H
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AVUTIL_AVUTIL_H

/**
 * @file
 * @ingroup lavu
 * Convenience header that includes @ref lavu "libavutil"'s core.
 */

/**
 * @mainpage
 *
 * @section ffmpeg_intro Introduction
 *
 * This document describes the usage of the different libraries
 * provided by FFmpeg.
 *
 * @li @ref libavc "libavcodec" encoding/decoding library
 * @li @ref lavfi "libavfilter" graph-based frame editing library
 * @li @ref libavf "libavformat" I/O and muxing/demuxing library
 * @li @ref lavd "libavdevice" special devices muxing/demuxing library
 * @li @ref lavu "libavutil" common utility library
 * @li @ref lswr "libswresample" audio resampling, format conversion and mixing
 * @li @ref libsws "libswscale" color conversion and scaling library
 *
 * @section ffmpeg_versioning Versioning and compatibility
 *
 * Each of the FFmpeg libraries contains a version.h header, which defines a
 * major, minor and micro version number with the
 * <em>LIBRARYNAME_VERSION_{MAJOR,MINOR,MICRO}</em> macros. The major version
 * number is incremented with backward incompatible changes - e.g. removing
 * parts of the public API, reordering public struct members, etc. The minor
 * version number is incremented for backward compatible API changes or major
 * new features - e.g. adding a new public function or a new decoder. The micro
 * version number is incremented for smaller changes that a calling program
 * might still want to check for - e.g. changing behavior in a previously
 * unspecified situation.
 *
 * FFmpeg guarantees backward API and ABI compatibility for each library as long
 * as its major version number is unchanged. This means that no public symbols
 * will be removed or renamed. Types and names of the public struct members and
 * values of public macros and enums will remain the same (unless they were
 * explicitly declared as not part of the public API). Documented behavior will
 * not change.
 *
 * In other words, any correct program that works with a given FFmpeg snapshot
 * should work just as well without any changes with any later snapshot with the
 * same major versions. This applies to both rebuilding the program against new
 * FFmpeg versions or to replacing the dynamic FFmpeg libraries that a program
 * links against.
 *
 * However, new public symbols may be added and new members may be appended to
 * public structs whose size is not part of public ABI (most public structs in
 * FFmpeg). New macros and enum values may be added. Behavior in undocumented
 * situations may change slightly (and be documented). All those are accompanied
 * by an entry in doc/APIchanges and incrementing either the minor or micro
 * version number.
 */

/**
 * @defgroup lavu libavutil
 * Common code shared across all FFmpeg libraries.
 *
 * @note
 * libavutil is designed to be modular. In most cases, in order to use the
 * functions provided by one component of libavutil you must explicitly include
 * the specific header containing that feature. If you are only using
 * media-related components, you could simply include libavutil/avutil.h, which
 * brings in most of the "core" components.
 *
 * @{
 *
 * @defgroup lavu_crypto Crypto and Hashing
 *
 * @{
 * @}
 *
 * @defgroup lavu_math Mathematics
 * @{
 *
 * @}
 *
 * @defgroup lavu_string String Manipulation
 *
 * @{
 *
 * @}
 *
 * @defgroup lavu_mem Memory Management
 *
 * @{
 *
 * @}
 *
 * @defgroup lavu_data Data Structures
 * @{
 *
 * @}
 *
 * @defgroup lavu_video Video related
 *
 * @{
 *
 * @}
 *
 * @defgroup lavu_audio Audio related
 *
 * @{
 *
 * @}
 *
 * @defgroup lavu_error Error Codes
 *
 * @{
 *
 * @}
 *
 * @defgroup lavu_log Logging Facility
 *
 * @{
 *
 * @}
 *
 * @defgroup lavu_misc Other
 *
 * @{
 *
 * @defgroup preproc_misc Preprocessor String Macros
 *
 * @{
 *
 * @}
 *
 * @defgroup version_utils Library Version Macros
 *
 * @{
 *
 * @}
 */


/**
 * @addtogroup lavu_ver
 * @{
 */

/**
 * Return the LIBAVUTIL_VERSION_INT constant.
 */
ਬਿਨਾਨਿਸ਼ਾਨੀ avutil_ਸੰਸਕਰਣ(ਖਾਲੀ);

/**
 * Return an informative version string. This usually is the actual release
 * version number or a git commit description. This string has no fixed format
 * and can change any time. It should never be parsed by code.
 */
ਅਚਲ ਅੱਖਰ *av_ਸੰਸਕਰਣ_info(ਖਾਲੀ);

/**
 * Return the libavutil build-time configuration.
 */
ਅਚਲ ਅੱਖਰ *avutil_configuration(ਖਾਲੀ);

/**
 * Return the libavutil license.
 */
ਅਚਲ ਅੱਖਰ *avutil_license(ਖਾਲੀ);

/**
 * @}
 */

/**
 * @addtogroup lavu_media Media Type
 * @brief Media Type
 */

ਗਿਣਤੀ AVMediaType {
    AVMEDIA_TYPE_UNKNOWN = -1,  ///< Usually treated as AVMEDIA_TYPE_DATA
    AVMEDIA_TYPE_VIDEO,
    AVMEDIA_TYPE_AUDIO,
    AVMEDIA_TYPE_ਅੰਕੜੇ,          ///< Opaque data information usually continuous
    AVMEDIA_TYPE_SUBTITLE,
    AVMEDIA_TYPE_ATTACHMENT,    ///< Opaque data information usually sparse
    AVMEDIA_TYPE_NB
};

/**
 * Return a string describing the media_type enum, NULL if media_type
 * is unknown.
 */
ਅਚਲ ਅੱਖਰ *av_get_media_type_string(ਗਿਣਤੀ AVMediaType media_type);

/**
 * @defgroup lavu_const Constants
 * @{
 *
 * @defgroup lavu_enc Encoding specific
 *
 * @note those definition should move to avcodec
 * @{
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LAMBDA_ਖਿਸਕਾਓ 7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LAMBDA_SCALE (1<<FF_LAMBDA_ਖਿਸਕਾਓ)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_QP2LAMBDA 118 ///< factor to convert from H.263 QP to lambda
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_LAMBDA_MAX (256*128-1)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ FF_QUALITY_SCALE FF_LAMBDA_SCALE //FIXME maybe remove

/**
 * @}
 * @defgroup lavu_time Timestamp specific
 *
 * FFmpeg internal timebase and timestamp definitions
 *
 * @{
 */

/**
 * @brief Undefined timestamp value
 *
 * Usually reported by demuxer that work on containers that do not provide
 * either pts or dts.
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_NOPTS_ਮੁੱਲ          ((int64_t)UINT64_C(0x8000000000000000))

/**
 * Internal time base represented as integer
 */

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_ਸਮਾਂ_ਅਧਾਰ            1000000

/**
 * Internal time base represented as fractional value
 */

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
/* ISO C++ forbids compound-literals. */
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_ਸਮਾਂ_ਅਧਾਰ_Q          av_make_q(1, AV_ਸਮਾਂ_ਅਧਾਰ)
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_ਸਮਾਂ_ਅਧਾਰ_Q          (AVRational){1, AV_ਸਮਾਂ_ਅਧਾਰ}
#ਜੇ_ਅੰਤ

/**
 * @}
 * @}
 * @defgroup lavu_picture Image related
 *
 * AVPicture types, pixel formats and basic image planes manipulation.
 *
 * @{
 */

ਗਿਣਤੀ AVPictureType {
    AV_PICTURE_TYPE_NONE = 0, ///< Undefined
    AV_PICTURE_TYPE_I,     ///< Intra
    AV_PICTURE_TYPE_P,     ///< Predicted
    AV_PICTURE_TYPE_B,     ///< Bi-dir predicted
    AV_PICTURE_TYPE_S,     ///< S(GMC)-VOP MPEG-4
    AV_PICTURE_TYPE_SI,    ///< Switching Intra
    AV_PICTURE_TYPE_SP,    ///< Switching Predicted
    AV_PICTURE_TYPE_BI,    ///< BI type
};

/**
 * Return a single letter to describe the given picture type
 * pict_type.
 *
 * @param[in] pict_type the picture type @return a single character
 * representing the picture type, '?' if pict_type is unknown
 */
ਅੱਖਰ av_get_picture_type_char(ਗਿਣਤੀ AVPictureType pict_type);

/**
 * @}
 */

#ਅਨ੍ਤਰ੍ਭਾਵ "common.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "rational.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "version.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "macros.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mathematics.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "log.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pixfmt.h"

/**
 * Return x default pointer in case p is NULL.
 */
ਸਥਿਰ ਸਤਰਅੰਦਰ ਖਾਲੀ *av_x_if_null(ਅਚਲ ਖਾਲੀ *p, ਅਚਲ ਖਾਲੀ *x)
{
    ਵਾਪਸ (ਖਾਲੀ *)(intptr_t)(p ? p : x);
}

/**
 * Return the fractional representation of the internal time base.
 */
AVRational av_get_ਸਮਾਂ_ਅਧਾਰ_q(ਖਾਲੀ);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ AV_FOURCC_MAX_STRING_ਮਾਪ 32

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ av_fourcc2str(fourcc) av_fourcc_make_string((ਅੱਖਰ[AV_FOURCC_MAX_STRING_ਮਾਪ]){0}, fourcc)

/**
 * Fill the provided buffer with a string containing a FourCC (four-character
 * code) representation.
 *
 * @param buf    a buffer with size in bytes of at least AV_FOURCC_MAX_STRING_SIZE
 * @param fourcc the fourcc to represent
 * @return the buffer in input
 */
ਅੱਖਰ *av_fourcc_make_string(ਅੱਖਰ *buf, uint32_t fourcc);

/**
 * @}
 * @}
 */

#ਜੇ_ਅੰਤ /* AVUTIL_AVUTIL_H */

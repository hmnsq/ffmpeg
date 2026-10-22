/*
 * copyright (c) 2003 Fabrice Bellard
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

/**
 * @file
 * @ingroup lavu
 * Libavutil version macros
 */

#यदि_अपरिभाषितम् AVUTIL_संस्करणम्_H
#परिभाषय AVUTIL_संस्करणम्_H

#अन्तर्भाव "macros.h"

/**
 * @addtogroup version_utils
 *
 * Useful to check and match library version in order to maintain
 * backward compatibility.
 *
 * The FFmpeg libraries follow a versioning scheme very similar to
 * Semantic Versioning (http://semver.org/)
 * The difference is that the component called PATCH is called MICRO in FFmpeg
 * and its value is reset to 100 instead of 0 to keep it above or equal to 100.
 * Also we do not increase MICRO for every bugfix or change in git master.
 *
 * Prior to FFmpeg 3.2 point releases did not change any lib version number to
 * avoid aliassing different git master checkouts.
 * Starting with FFmpeg 3.2, the released library versions will occupy
 * a separate MAJOR.MINOR that is not used on the master development branch.
 * That is if we branch a release of master 55.10.123 we will bump to 55.11.100
 * for the release and master will continue at 55.12.100 after it. Each new
 * point release will then bump the MICRO improving the usefulness of the lib
 * versions.
 *
 * @{
 */

#परिभाषय AV_संस्करणम्_INT(a, b, c) ((a)<<16 | (b)<<8 | (c))
#परिभाषय AV_संस्करणम्_DOT(a, b, c) a ##.## b ##.## c
#परिभाषय AV_संस्करणम्(a, b, c) AV_संस्करणम्_DOT(a, b, c)

/**
 * Extract version components from the full ::AV_VERSION_INT int as returned
 * by functions like ::avformat_version() and ::avcodec_version()
 */
#परिभाषय AV_संस्करणम्_MAJOR(a) ((a) >> 16)
#परिभाषय AV_संस्करणम्_MINOR(a) (((a) & 0x00FF00) >> 8)
#परिभाषय AV_संस्करणम्_MICRO(a) ((a) & 0xFF)

/**
 * @}
 */

/**
 * @defgroup lavu_ver Version and Build diagnostics
 *
 * Macros and function useful to check at compile time and at runtime
 * which version of libavutil is in use.
 *
 * @{
 */

#परिभाषय LIBAVUTIL_संस्करणम्_MAJOR  61
#परिभाषय LIBAVUTIL_संस्करणम्_MINOR  16
#परिभाषय LIBAVUTIL_संस्करणम्_MICRO 100

#परिभाषय LIBAVUTIL_संस्करणम्_INT   AV_संस्करणम्_INT(LIBAVUTIL_संस्करणम्_MAJOR, \
                                               LIBAVUTIL_संस्करणम्_MINOR, \
                                               LIBAVUTIL_संस्करणम्_MICRO)
#परिभाषय LIBAVUTIL_संस्करणम्       AV_संस्करणम्(LIBAVUTIL_संस्करणम्_MAJOR,     \
                                           LIBAVUTIL_संस्करणम्_MINOR,     \
                                           LIBAVUTIL_संस्करणम्_MICRO)
#परिभाषय LIBAVUTIL_BUILD         LIBAVUTIL_संस्करणम्_INT

#परिभाषय LIBAVUTIL_IDENT         "Lavu" AV_STRINGIFY(LIBAVUTIL_संस्करणम्)

/**
 * @defgroup lavu_depr_guards Deprecation Guards
 * FF_API_* defines may be placed below to indicate public API that will be
 * dropped at a future version bump. The defines themselves are not part of
 * the public API and may change, break or disappear at any time.
 *
 * @note, when bumping the major version it is recommended to manually
 * disable each FF_API_* in its own commit instead of disabling them all
 * at once through the bump. This improves the git bisect-ability of the change.
 *
 * @{
 */

#परिभाषय FF_API_CPU_FLAG_FORCE           (LIBAVUTIL_संस्करणम्_MAJOR < 62)
#परिभाषय FF_API_DOVI_L11_INVALID_PROPS   (LIBAVUTIL_संस्करणम्_MAJOR < 62)
#परिभाषय FF_API_ASSERT_FPU               (LIBAVUTIL_संस्करणम्_MAJOR < 62)
#परिभाषय FF_API_VULKAN_SYNC_QUEUES       (LIBAVUTIL_संस्करणम्_MAJOR < 62)
#परिभाषय FF_API_CHANNEL_LAYOUT_पृष्ठभागः      (LIBAVUTIL_संस्करणम्_MAJOR < 62)

/**
 * @}
 * @}
 */

#यदि_अन्तः /* AVUTIL_VERSION_H */

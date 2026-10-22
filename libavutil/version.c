/*
 * Version functions.
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

#ಅನ್ತರ್ಭಾವ <assert.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "avutil.h"
#ಅನ್ತರ್ಭಾವ "samplefmt.h"
#ಅನ್ತರ್ಭಾವ "version.h"

#ಅನ್ತರ್ಭಾವ "libavutil/ffversion.h"
ಧ್ರುವ ವರ್ಣ av_util_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

ಧ್ರುವ ವರ್ಣ *av_version_info(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ FFMPEG_VERSION;
}

unsigned avutil_version(ಶೂನ್ಯ)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_VERSION_MICRO >= 100, "micro version starts at 100");

    ಪ್ರತ್ಯಾಗಮ LIBAVUTIL_VERSION_INT;
}

ಧ್ರುವ ವರ್ಣ *avutil_configuration(ಶೂನ್ಯ)
{
    ಪ್ರತ್ಯಾಗಮ FFMPEG_CONFIGURATION;
}

ಧ್ರುವ ವರ್ಣ *avutil_license(ಶೂನ್ಯ)
{
#define LICENSE_PREFIX "libavutil license: "
    ಪ್ರತ್ಯಾಗಮ &LICENSE_PREFIX FFMPEG_LICENSE[ಪರಿಮಾಣ(LICENSE_PREFIX) - 1];
}

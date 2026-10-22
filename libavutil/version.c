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

#ଅନ୍ତର୍ଭାଵ <assert.h>

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "avutil.h"
#ଅନ୍ତର୍ଭାଵ "samplefmt.h"
#ଅନ୍ତର୍ଭାଵ "version.h"

#ଅନ୍ତର୍ଭାଵ "libavutil/ffversion.h"
ଅଚଳ ଅକ୍ଷର av_util_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

ଅଚଳ ଅକ୍ଷର *av_version_info(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ FFMPEG_VERSION;
}

unsigned avutil_version(ଶୂନ୍ୟ)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_VERSION_MICRO >= 100, "micro version starts at 100");

    ଫେରନ୍ତୁ LIBAVUTIL_VERSION_INT;
}

ଅଚଳ ଅକ୍ଷର *avutil_configuration(ଶୂନ୍ୟ)
{
    ଫେରନ୍ତୁ FFMPEG_CONFIGURATION;
}

ଅଚଳ ଅକ୍ଷର *avutil_license(ଶୂନ୍ୟ)
{
#define LICENSE_PREFIX "libavutil license: "
    ଫେରନ୍ତୁ &LICENSE_PREFIX FFMPEG_LICENSE[ଆକାର(LICENSE_PREFIX) - 1];
}

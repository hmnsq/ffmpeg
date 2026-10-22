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

#અન્તર્ભાવ <assert.h>

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "avutil.h"
#અન્તર્ભાવ "samplefmt.h"
#અન્તર્ભાવ "version.h"

#અન્તર્ભાવ "libavutil/ffversion.h"
અચલ અક્ષર av_util_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

અચલ અક્ષર *av_version_info(શૂન્ય)
{
    પાછા FFMPEG_VERSION;
}

unsigned avutil_version(શૂન્ય)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_VERSION_MICRO >= 100, "micro version starts at 100");

    પાછા LIBAVUTIL_VERSION_INT;
}

અચલ અક્ષર *avutil_configuration(શૂન્ય)
{
    પાછા FFMPEG_CONFIGURATION;
}

અચલ અક્ષર *avutil_license(શૂન્ય)
{
#define LICENSE_PREFIX "libavutil license: "
    પાછા &LICENSE_PREFIX FFMPEG_LICENSE[કદ(LICENSE_PREFIX) - 1];
}

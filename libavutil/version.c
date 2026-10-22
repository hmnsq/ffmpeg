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

#شامل <assert.h>

#شامل "config.h"
#شامل "avutil.h"
#شامل "samplefmt.h"
#شامل "version.h"

#شامل "libavutil/ffversion.h"
ثابت نویسه av_util_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

ثابت نویسه *av_version_info(تهی)
{
    بازگشت FFMPEG_VERSION;
}

unsigned avutil_version(تهی)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_VERSION_MICRO >= 100, "micro version starts at 100");

    بازگشت LIBAVUTIL_VERSION_INT;
}

ثابت نویسه *avutil_configuration(تهی)
{
    بازگشت FFMPEG_CONFIGURATION;
}

ثابت نویسه *avutil_license(تهی)
{
#define LICENSE_PREFIX "libavutil license: "
    بازگشت &LICENSE_PREFIX FFMPEG_LICENSE[اندازه(LICENSE_PREFIX) - 1];
}

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

#समावेश <assert.h>

#समावेश "config.h"
#समावेश "avutil.h"
#समावेश "samplefmt.h"
#समावेश "version.h"

#समावेश "libavutil/ffversion.h"
स्थिर अक्षर av_util_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

स्थिर अक्षर *av_version_info(व्योम)
{
    वापस FFMPEG_VERSION;
}

अचिन्हित avutil_version(व्योम)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_VERSION_MICRO >= 100, "micro version starts at 100");

    वापस LIBAVUTIL_VERSION_INT;
}

स्थिर अक्षर *avutil_configuration(व्योम)
{
    वापस FFMPEG_CONFIGURATION;
}

स्थिर अक्षर *avutil_license(व्योम)
{
#घोषणा LICENSE_PREFIX "libavutil license: "
    वापस &LICENSE_PREFIX FFMPEG_LICENSE[माप(LICENSE_PREFIX) - 1];
}

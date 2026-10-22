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

#ضمن <assert.h>

#ضمن "config.h"
#ضمن "avutil.h"
#ضمن "samplefmt.h"
#ضمن "version.h"

#ضمن "libavutil/ffversion.h"
ثابت حرف av_util_ffversion[] = "FFmpeg version " FFMPEG_نسخو;

ثابت حرف *av_نسخو_info(فراغ)
{
    أرجع FFMPEG_نسخو;
}

بنانشان avutil_نسخو(فراغ)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_نسخو_MICRO >= 100, "micro version starts at 100");

    أرجع LIBAVUTIL_نسخو_INT;
}

ثابت حرف *avutil_configuration(فراغ)
{
    أرجع FFMPEG_CONFIGURATION;
}

ثابت حرف *avutil_license(فراغ)
{
#وصف_ڪريو LICENSE_اڳياڙي "libavutil license: "
    أرجع &LICENSE_اڳياڙي FFMPEG_LICENSE[حجم(LICENSE_اڳياڙي) - 1];
}

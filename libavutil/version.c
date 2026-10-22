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

#അന്തര്ഭാവ <assert.h>

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "avutil.h"
#അന്തര്ഭാവ "samplefmt.h"
#അന്തര്ഭാവ "version.h"

#അന്തര്ഭാവ "libavutil/ffversion.h"
സ്ഥിരം അക്ഷരം av_util_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

സ്ഥിരം അക്ഷരം *av_version_info(ശൂന്യം)
{
    തിരികെ FFMPEG_VERSION;
}

unsigned avutil_version(ശൂന്യം)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_VERSION_MICRO >= 100, "micro version starts at 100");

    തിരികെ LIBAVUTIL_VERSION_INT;
}

സ്ഥിരം അക്ഷരം *avutil_configuration(ശൂന്യം)
{
    തിരികെ FFMPEG_CONFIGURATION;
}

സ്ഥിരം അക്ഷരം *avutil_license(ശൂന്യം)
{
#define LICENSE_PREFIX "libavutil license: "
    തിരികെ &LICENSE_PREFIX FFMPEG_LICENSE[വലുപ്പം(LICENSE_PREFIX) - 1];
}

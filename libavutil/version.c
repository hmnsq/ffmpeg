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

#அந்தர்பாவ <assert.h>

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "avutil.h"
#அந்தர்பாவ "samplefmt.h"
#அந்தர்பாவ "version.h"

#அந்தர்பாவ "libavutil/ffversion.h"
மாறிலி எழுத்து av_util_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

மாறிலி எழுத்து *av_version_info(வெறுமை)
{
    திரும்பு FFMPEG_VERSION;
}

unsigned avutil_version(வெறுமை)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_VERSION_MICRO >= 100, "micro version starts at 100");

    திரும்பு LIBAVUTIL_VERSION_INT;
}

மாறிலி எழுத்து *avutil_configuration(வெறுமை)
{
    திரும்பு FFMPEG_CONFIGURATION;
}

மாறிலி எழுத்து *avutil_license(வெறுமை)
{
#define LICENSE_PREFIX "libavutil license: "
    திரும்பு &LICENSE_PREFIX FFMPEG_LICENSE[அளவு(LICENSE_PREFIX) - 1];
}

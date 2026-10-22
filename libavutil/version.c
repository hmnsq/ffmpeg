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

#অন্তর্ভাৱ <assert.h>

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "avutil.h"
#অন্তর্ভাৱ "samplefmt.h"
#অন্তর্ভাৱ "version.h"

#অন্তর্ভাৱ "libavutil/ffversion.h"
ধ্রুৱ ৱর্ণ av_util_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

ধ্রুৱ ৱর্ণ *av_version_info(শূন্য)
{
    ঘূৰাই FFMPEG_VERSION;
}

unsigned avutil_version(শূন্য)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_VERSION_MICRO >= 100, "micro version starts at 100");

    ঘূৰাই LIBAVUTIL_VERSION_INT;
}

ধ্রুৱ ৱর্ণ *avutil_configuration(শূন্য)
{
    ঘূৰাই FFMPEG_CONFIGURATION;
}

ধ্রুৱ ৱর্ণ *avutil_license(শূন্য)
{
#define LICENSE_PREFIX "libavutil license: "
    ঘূৰাই &LICENSE_PREFIX FFMPEG_LICENSE[পরিমাণ(LICENSE_PREFIX) - 1];
}

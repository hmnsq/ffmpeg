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

#अन्तर्भाव <assert.h>

#अन्तर्भाव "config.h"
#अन्तर्भाव "avutil.h"
#अन्तर्भाव "samplefmt.h"
#अन्तर्भाव "version.h"

#अन्तर्भाव "libavutil/ffversion.h"
ध्रुव वर्ण av_util_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

ध्रुव वर्ण *av_version_info(शून्य)
{
    प्रत्यागम FFMPEG_VERSION;
}

unsigned avutil_version(शून्य)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_VERSION_MICRO >= 100, "micro version starts at 100");

    प्रत्यागम LIBAVUTIL_VERSION_INT;
}

ध्रुव वर्ण *avutil_configuration(शून्य)
{
    प्रत्यागम FFMPEG_CONFIGURATION;
}

ध्रुव वर्ण *avutil_license(शून्य)
{
#define LICENSE_PREFIX "libavutil license: "
    प्रत्यागम &LICENSE_PREFIX FFMPEG_LICENSE[परिमाण(LICENSE_PREFIX) - 1];
}

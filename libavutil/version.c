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

#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "avutil.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "samplefmt.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "version.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/ffversion.h"
ਅਚਲ ਅੱਖਰ av_util_ffversion[] = "FFmpeg version " FFMPEG_ਸੰਸਕਰਣ;

ਅਚਲ ਅੱਖਰ *av_ਸੰਸਕਰਣ_info(ਖਾਲੀ)
{
    ਵਾਪਸ FFMPEG_ਸੰਸਕਰਣ;
}

ਬਿਨਾਨਿਸ਼ਾਨੀ avutil_ਸੰਸਕਰਣ(ਖਾਲੀ)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_ਸੰਸਕਰਣ_MICRO >= 100, "micro version starts at 100");

    ਵਾਪਸ LIBAVUTIL_ਸੰਸਕਰਣ_INT;
}

ਅਚਲ ਅੱਖਰ *avutil_configuration(ਖਾਲੀ)
{
    ਵਾਪਸ FFMPEG_CONFIGURATION;
}

ਅਚਲ ਅੱਖਰ *avutil_license(ਖਾਲੀ)
{
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ LICENSE_ਅਗੇਤਰ "libavutil license: "
    ਵਾਪਸ &LICENSE_ਅਗੇਤਰ FFMPEG_LICENSE[ਆਕਾਰ(LICENSE_ਅਗੇਤਰ) - 1];
}

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

#ಅನ್ತರ್ಭಾವ <assert.h>

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "avutil.h"
#ಅನ್ತರ್ಭಾವ "samplefmt.h"
#ಅನ್ತರ್ಭಾವ "version.h"

#ಅನ್ತರ್ಭಾವ "libavutil/ffversion.h"
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ av_util_ffversion[] = "FFmpeg version " FFMPEG_ಆವೃತ್ತಿ;

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *av_ಆವೃತ್ತಿ_info(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ FFMPEG_ಆವೃತ್ತಿ;
}

ಚಿಹ್ನೆರಹಿತ avutil_ಆವೃತ್ತಿ(ಶೂನ್ಯ)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_ಆವೃತ್ತಿ_MICRO >= 100, "micro version starts at 100");

    ಹಿಂತಿರುಗಿ LIBAVUTIL_ಆವೃತ್ತಿ_INT;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *avutil_configuration(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ FFMPEG_CONFIGURATION;
}

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *avutil_license(ಶೂನ್ಯ)
{
#ವ್ಯಾಖ್ಯಾನಿಸು LICENSE_ಪೂರ್ವಪ್ರತ್ಯಯ "libavutil license: "
    ಹಿಂತಿರುಗಿ &LICENSE_ಪೂರ್ವಪ್ರತ್ಯಯ FFMPEG_LICENSE[ಗಾತ್ರ(LICENSE_ಪೂರ್ವಪ್ರತ್ಯಯ) - 1];
}

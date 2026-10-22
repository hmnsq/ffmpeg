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

#అన్తర్భావ <assert.h>

#అన్తర్భావ "config.h"
#అన్తర్భావ "avutil.h"
#అన్తర్భావ "samplefmt.h"
#అన్తర్భావ "version.h"

#అన్తర్భావ "libavutil/ffversion.h"
స్థిరరాశి అక్షరం av_util_ffversion[] = "FFmpeg version " FFMPEG_సంస్కరణ;

స్థిరరాశి అక్షరం *av_సంస్కరణ_info(శూన్య)
{
    తిరిగి FFMPEG_సంస్కరణ;
}

గుర్తులేని avutil_సంస్కరణ(శూన్య)
{
    static_assert(AV_SAMPLE_FMT_S64P      == 11 &&
                  AVMEDIA_TYPE_ATTACHMENT ==  4 &&
                  AV_PICTURE_TYPE_BI      ==  7,
                  "Don't insert new sample/media/picture types in the middle of the list");
    static_assert(LIBAVUTIL_సంస్కరణ_MICRO >= 100, "micro version starts at 100");

    తిరిగి LIBAVUTIL_సంస్కరణ_INT;
}

స్థిరరాశి అక్షరం *avutil_configuration(శూన్య)
{
    తిరిగి FFMPEG_CONFIGURATION;
}

స్థిరరాశి అక్షరం *avutil_license(శూన్య)
{
#నిర్వచించు LICENSE_ఉపసర్గ "libavutil license: "
    తిరిగి &LICENSE_ఉపసర్గ FFMPEG_LICENSE[పరిమాణం(LICENSE_ఉపసర్గ) - 1];
}

/**
 * Copyright (c) 2016 Neil Birkbeck <neil.birkbeck@gmail.com>
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

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>
#అన్తర్భావ <string.h>

#అన్తర్భావ "mastering_display_metadata.h"
#అన్తర్భావ "mem.h"

స్థిర శూన్య get_defaults(AVMasteringDisplayMetadata *mastering)
{
    కొరకు (పూర్ణాంకం i = 0; i < 3; i++)
        కొరకు (పూర్ణాంకం j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_బిందువు_2[0] =
    mastering->white_బిందువు_2[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(శూన్య)
{
    తిరిగి av_mastering_display_metadata_alloc_కొలత(ఖాళీ);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_కొలత(size_t *కొలత)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(పరిమాణం(AVMasteringDisplayMetadata));

    ఒకవేళ (కొలత)
        *కొలత = mastering ? పరిమాణం(*mastering) : 0;

    ఒకవేళ (!mastering)
        తిరిగి ఖాళీ;

    get_defaults(mastering);

    తిరిగి mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_దత్తాంశం(AVFrame *చట్రం)
{
    AVFrame_Side_దత్తాంశం *side_దత్తాంశం = av_చట్రం_new_side_దత్తాంశం(చట్రం,
                                                        AV_చట్రం_దత్తాంశం_MASTERING_DISPLAY_METADATA,
                                                        పరిమాణం(AVMasteringDisplayMetadata));
    ఒకవేళ (!side_దత్తాంశం)
        తిరిగి ఖాళీ;

    memset(side_దత్తాంశం->దత్తాంశం, 0, పరిమాణం(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_దత్తాంశం->దత్తాంశం);

    తిరిగి (AVMasteringDisplayMetadata *)side_దత్తాంశం->దత్తాంశం;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *కొలత)
{
    AVContentLightMetadata *metadata = av_mallocz(పరిమాణం(AVContentLightMetadata));

    ఒకవేళ (కొలత)
        *కొలత = metadata ? పరిమాణం(*metadata) : 0;

    తిరిగి metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_దత్తాంశం(AVFrame *చట్రం)
{
    AVFrame_Side_దత్తాంశం *side_దత్తాంశం = av_చట్రం_new_side_దత్తాంశం(చట్రం,
                                                        AV_చట్రం_దత్తాంశం_CONTENT_LIGHT_LEVEL,
                                                        పరిమాణం(AVContentLightMetadata));
    ఒకవేళ (!side_దత్తాంశం)
        తిరిగి ఖాళీ;

    memset(side_దత్తాంశం->దత్తాంశం, 0, పరిమాణం(AVContentLightMetadata));

    తిరిగి (AVContentLightMetadata *)side_దత్తాంశం->దత్తాంశం;
}

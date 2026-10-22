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

#অন্তর্ভাব <stddef.h>
#অন্তর্ভাব <stdint.h>
#অন্তর্ভাব <string.h>

#অন্তর্ভাব "mastering_display_metadata.h"
#অন্তর্ভাব "mem.h"

স্থির শূন্য get_defaults(AVMasteringDisplayMetadata *mastering)
{
    জন্য (পূর্ণসংখ্যা i = 0; i < 3; i++)
        জন্য (পূর্ণসংখ্যা j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_point[0] =
    mastering->white_point[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(শূন্য)
{
    ফেরত av_mastering_display_metadata_alloc_আকার(ফাঁকা);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_আকার(size_t *আকার_2)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(আকার(AVMasteringDisplayMetadata));

    যদি (আকার_2)
        *আকার_2 = mastering ? আকার(*mastering) : 0;

    যদি (!mastering)
        ফেরত ফাঁকা;

    get_defaults(mastering);

    ফেরত mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_তথ্য(AVFrame *frame)
{
    AVFrame_Side_তথ্য *side_তথ্য = av_frame_new_side_তথ্য(frame,
                                                        AV_FRAME_তথ্য_MASTERING_DISPLAY_METADATA,
                                                        আকার(AVMasteringDisplayMetadata));
    যদি (!side_তথ্য)
        ফেরত ফাঁকা;

    memset(side_তথ্য->তথ্য, 0, আকার(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_তথ্য->তথ্য);

    ফেরত (AVMasteringDisplayMetadata *)side_তথ্য->তথ্য;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *আকার_2)
{
    AVContentLightMetadata *metadata = av_mallocz(আকার(AVContentLightMetadata));

    যদি (আকার_2)
        *আকার_2 = metadata ? আকার(*metadata) : 0;

    ফেরত metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_তথ্য(AVFrame *frame)
{
    AVFrame_Side_তথ্য *side_তথ্য = av_frame_new_side_তথ্য(frame,
                                                        AV_FRAME_তথ্য_CONTENT_LIGHT_LEVEL,
                                                        আকার(AVContentLightMetadata));
    যদি (!side_তথ্য)
        ফেরত ফাঁকা;

    memset(side_তথ্য->তথ্য, 0, আকার(AVContentLightMetadata));

    ফেরত (AVContentLightMetadata *)side_তথ্য->তথ্য;
}

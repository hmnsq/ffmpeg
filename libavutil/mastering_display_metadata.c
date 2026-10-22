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

#شامل <stddef.h>
#شامل <stdint.h>
#شامل <string.h>

#شامل "mastering_display_metadata.h"
#شامل "mem.h"

ساکن خالی get_defaults(AVMasteringDisplayMetadata *mastering)
{
    برائے (صحیح i = 0; i < 3; i++)
        برائے (صحیح j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_نقطہ_2[0] =
    mastering->white_نقطہ_2[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(خالی)
{
    واپس av_mastering_display_metadata_alloc_سائز(تہی);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_سائز(size_t *سائز)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(حجم(AVMasteringDisplayMetadata));

    اگر (سائز)
        *سائز = mastering ? حجم(*mastering) : 0;

    اگر (!mastering)
        واپس تہی;

    get_defaults(mastering);

    واپس mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_ڈیٹا(AVFrame *چوکھٹا)
{
    AVFrame_Side_ڈیٹا *side_ڈیٹا = av_چوکھٹا_new_side_ڈیٹا(چوکھٹا,
                                                        AV_چوکھٹا_ڈیٹا_MASTERING_DISPLAY_METADATA,
                                                        حجم(AVMasteringDisplayMetadata));
    اگر (!side_ڈیٹا)
        واپس تہی;

    memset(side_ڈیٹا->ڈیٹا, 0, حجم(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_ڈیٹا->ڈیٹا);

    واپس (AVMasteringDisplayMetadata *)side_ڈیٹا->ڈیٹا;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *سائز)
{
    AVContentLightMetadata *metadata = av_mallocz(حجم(AVContentLightMetadata));

    اگر (سائز)
        *سائز = metadata ? حجم(*metadata) : 0;

    واپس metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_ڈیٹا(AVFrame *چوکھٹا)
{
    AVFrame_Side_ڈیٹا *side_ڈیٹا = av_چوکھٹا_new_side_ڈیٹا(چوکھٹا,
                                                        AV_چوکھٹا_ڈیٹا_CONTENT_LIGHT_LEVEL,
                                                        حجم(AVContentLightMetadata));
    اگر (!side_ڈیٹا)
        واپس تہی;

    memset(side_ڈیٹا->ڈیٹا, 0, حجم(AVContentLightMetadata));

    واپس (AVContentLightMetadata *)side_ڈیٹا->ڈیٹا;
}

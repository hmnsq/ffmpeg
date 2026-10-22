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

#ضمن <stddef.h>
#ضمن <stdint.h>
#ضمن <string.h>

#ضمن "mastering_display_metadata.h"
#ضمن "mem.h"

ساكن فراغ get_defaults(AVMasteringDisplayMetadata *mastering)
{
    لكل (صحيح i = 0; i < 3; i++)
        لكل (صحيح j = 0; j < 2; j++)
            mastering->display_primaries[i][j] = (AVRational) { 0, 1 };
    mastering->white_نقطه_2[0] =
    mastering->white_نقطه_2[1] =
    mastering->min_luminance  =
    mastering->max_luminance  = (AVRational) { 0, 1 };
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc(فراغ)
{
    أرجع av_mastering_display_metadata_alloc_اندازه(عدم);
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_alloc_اندازه(size_t *اندازه)
{
    AVMasteringDisplayMetadata *mastering = av_mallocz(حجم(AVMasteringDisplayMetadata));

    إذا (اندازه)
        *اندازه = mastering ? حجم(*mastering) : 0;

    إذا (!mastering)
        أرجع عدم;

    get_defaults(mastering);

    أرجع mastering;
}

AVMasteringDisplayMetadata *av_mastering_display_metadata_create_side_داده(AVFrame *قاب)
{
    AVFrame_Side_داده *side_داده = av_قاب_new_side_داده(قاب,
                                                        AV_قاب_داده_MASTERING_DISPLAY_METADATA,
                                                        حجم(AVMasteringDisplayMetadata));
    إذا (!side_داده)
        أرجع عدم;

    memset(side_داده->داده, 0, حجم(AVMasteringDisplayMetadata));
    get_defaults((AVMasteringDisplayMetadata *)side_داده->داده);

    أرجع (AVMasteringDisplayMetadata *)side_داده->داده;
}

AVContentLightMetadata *av_content_light_metadata_alloc(size_t *اندازه)
{
    AVContentLightMetadata *metadata = av_mallocz(حجم(AVContentLightMetadata));

    إذا (اندازه)
        *اندازه = metadata ? حجم(*metadata) : 0;

    أرجع metadata;
}

AVContentLightMetadata *av_content_light_metadata_create_side_داده(AVFrame *قاب)
{
    AVFrame_Side_داده *side_داده = av_قاب_new_side_داده(قاب,
                                                        AV_قاب_داده_CONTENT_LIGHT_LEVEL,
                                                        حجم(AVContentLightMetadata));
    إذا (!side_داده)
        أرجع عدم;

    memset(side_داده->داده, 0, حجم(AVContentLightMetadata));

    أرجع (AVContentLightMetadata *)side_داده->داده;
}

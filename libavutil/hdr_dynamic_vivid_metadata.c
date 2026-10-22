/**
 * Copyright (c) 2021 Limin Wang <lance.lmwang at gmail.com>
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

#ଅନ୍ତର୍ଭାଵ "hdr_dynamic_vivid_metadata.h"
#ଅନ୍ତର୍ଭାଵ "mem.h"

AVDynamicHDRVivid *av_dynamic_hdr_vivid_alloc(size_t *size)
{
    AVDynamicHDRVivid *hdr_vivid = av_mallocz(ଆକାର(AVDynamicHDRVivid));

    ଯଦି (size)
        *size = hdr_vivid ? ଆକାର(*hdr_vivid) : 0;

    ଫେରନ୍ତୁ hdr_vivid;
}

AVDynamicHDRVivid *av_dynamic_hdr_vivid_create_side_data(AVFrame *frame)
{
    AVFrameSideData *side_data = av_frame_new_side_data(frame,
                                                        AV_FRAME_DATA_DYNAMIC_HDR_VIVID,
                                                        ଆକାର(AVDynamicHDRVivid));
    ଯଦି (!side_data)
        ଫେରନ୍ତୁ ଖାଲି;

    memset(side_data->data, 0, ଆକାର(AVDynamicHDRVivid));

    ଫେରନ୍ତୁ (AVDynamicHDRVivid *)side_data->data;
}

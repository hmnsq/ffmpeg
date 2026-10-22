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

#अन्तर्भाव "hdr_dynamic_vivid_metadata.h"
#अन्तर्भाव "mem.h"

AVDynamicHDRVivid *av_dynamic_hdr_vivid_alloc(size_t *आकार)
{
    AVDynamicHDRVivid *hdr_vivid = av_mallocz(परिमाण(AVDynamicHDRVivid));

    यदि (आकार)
        *आकार = hdr_vivid ? परिमाण(*hdr_vivid) : 0;

    प्रत्यागम hdr_vivid;
}

AVDynamicHDRVivid *av_dynamic_hdr_vivid_create_side_दत्त(AVFrame *frame)
{
    AVFrame_Side_दत्त *side_दत्त = av_frame_new_side_दत्त(frame,
                                                        AV_FRAME_दत्त_DYNAMIC_HDR_VIVID,
                                                        परिमाण(AVDynamicHDRVivid));
    यदि (!side_दत्त)
        प्रत्यागम रिक्त;

    स्मृतिं_पूरय(side_दत्त->दत्त, 0, परिमाण(AVDynamicHDRVivid));

    प्रत्यागम (AVDynamicHDRVivid *)side_दत्त->दत्त;
}

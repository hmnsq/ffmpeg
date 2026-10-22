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

#समावेश "hdr_dynamic_vivid_metadata.h"
#समावेश "mem.h"

AVDynamicHDRVivid *av_dynamic_hdr_vivid_alloc(माप_प्रकार *आकार)
{
    AVDynamicHDRVivid *hdr_vivid = av_mallocz(माप(AVDynamicHDRVivid));

    अगर (आकार)
        *आकार = hdr_vivid ? माप(*hdr_vivid) : 0;

    वापस hdr_vivid;
}

AVDynamicHDRVivid *av_dynamic_hdr_vivid_create_side_तथ्य(AVFrame *frame)
{
    AVFrame_Side_तथ्य *side_तथ्य = av_frame_new_side_तथ्य(frame,
                                                        AV_FRAME_तथ्य_DYNAMIC_HDR_VIVID,
                                                        माप(AVDynamicHDRVivid));
    अगर (!side_तथ्य)
        वापस शून्य;

    स_रखो(side_तथ्य->तथ्य, 0, माप(AVDynamicHDRVivid));

    वापस (AVDynamicHDRVivid *)side_तथ्य->तथ्य;
}

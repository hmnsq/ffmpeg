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

#অন্তর্ভাব "hdr_dynamic_vivid_metadata.h"
#অন্তর্ভাব "mem.h"

AVDynamicHDRVivid *av_dynamic_hdr_vivid_alloc(size_t *আকার_2)
{
    AVDynamicHDRVivid *hdr_vivid = av_mallocz(আকার(AVDynamicHDRVivid));

    যদি (আকার_2)
        *আকার_2 = hdr_vivid ? আকার(*hdr_vivid) : 0;

    ফেরত hdr_vivid;
}

AVDynamicHDRVivid *av_dynamic_hdr_vivid_create_side_তথ্য(AVFrame *frame)
{
    AVFrame_Side_তথ্য *side_তথ্য = av_frame_new_side_তথ্য(frame,
                                                        AV_FRAME_তথ্য_DYNAMIC_HDR_VIVID,
                                                        আকার(AVDynamicHDRVivid));
    যদি (!side_তথ্য)
        ফেরত ফাঁকা;

    memset(side_তথ্য->তথ্য, 0, আকার(AVDynamicHDRVivid));

    ফেরত (AVDynamicHDRVivid *)side_তথ্য->তথ্য;
}

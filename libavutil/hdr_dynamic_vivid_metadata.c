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

#ਅਨ੍ਤਰ੍ਭਾਵ "hdr_dynamic_vivid_metadata.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "mem.h"

AVDynamicHDRVivid *av_dynamic_hdr_vivid_alloc(size_t *ਮਾਪ)
{
    AVDynamicHDRVivid *hdr_vivid = av_mallocz(ਆਕਾਰ(AVDynamicHDRVivid));

    ਜੇ (ਮਾਪ)
        *ਮਾਪ = hdr_vivid ? ਆਕਾਰ(*hdr_vivid) : 0;

    ਵਾਪਸ hdr_vivid;
}

AVDynamicHDRVivid *av_dynamic_hdr_vivid_create_side_ਅੰਕੜੇ(AVFrame *ਚੌਖਟਾ)
{
    AVFrame_Side_ਅੰਕੜੇ *side_ਅੰਕੜੇ = av_ਚੌਖਟਾ_new_side_ਅੰਕੜੇ(ਚੌਖਟਾ,
                                                        AV_ਚੌਖਟਾ_ਅੰਕੜੇ_DYNAMIC_HDR_VIVID,
                                                        ਆਕਾਰ(AVDynamicHDRVivid));
    ਜੇ (!side_ਅੰਕੜੇ)
        ਵਾਪਸ ਨਿਰਾ;

    memset(side_ਅੰਕੜੇ->ਅੰਕੜੇ, 0, ਆਕਾਰ(AVDynamicHDRVivid));

    ਵਾਪਸ (AVDynamicHDRVivid *)side_ਅੰਕੜੇ->ਅੰਕੜੇ;
}

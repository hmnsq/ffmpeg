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

#ضمن "hdr_dynamic_vivid_metadata.h"
#ضمن "mem.h"

AVDynamicHDRVivid *av_dynamic_hdr_vivid_alloc(size_t *سائيز)
{
    AVDynamicHDRVivid *hdr_vivid = av_mallocz(حجم(AVDynamicHDRVivid));

    إذا (سائيز)
        *سائيز = hdr_vivid ? حجم(*hdr_vivid) : 0;

    أرجع hdr_vivid;
}

AVDynamicHDRVivid *av_dynamic_hdr_vivid_create_side_معلومات(AVFrame *چوکٺو)
{
    AVFrame_Side_معلومات *side_معلومات = av_چوکٺو_new_side_معلومات(چوکٺو,
                                                        AV_چوکٺو_معلومات_DYNAMIC_HDR_VIVID,
                                                        حجم(AVDynamicHDRVivid));
    إذا (!side_معلومات)
        أرجع عدم;

    memset(side_معلومات->معلومات, 0, حجم(AVDynamicHDRVivid));

    أرجع (AVDynamicHDRVivid *)side_معلومات->معلومات;
}

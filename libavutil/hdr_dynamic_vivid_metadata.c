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

#ಅನ್ತರ್ಭಾವ "hdr_dynamic_vivid_metadata.h"
#ಅನ್ತರ್ಭಾವ "mem.h"

AVDynamicHDRVivid *av_dynamic_hdr_vivid_alloc(size_t *ಗಾತ್ರ_2)
{
    AVDynamicHDRVivid *hdr_vivid = av_mallocz(ಗಾತ್ರ(AVDynamicHDRVivid));

    ಆದರೆ (ಗಾತ್ರ_2)
        *ಗಾತ್ರ_2 = hdr_vivid ? ಗಾತ್ರ(*hdr_vivid) : 0;

    ಹಿಂತಿರುಗಿ hdr_vivid;
}

AVDynamicHDRVivid *av_dynamic_hdr_vivid_create_side_ದತ್ತಾಂಶ(AVFrame *ಚೌಕಟ್ಟು)
{
    AVFrame_Side_ದತ್ತಾಂಶ *side_ದತ್ತಾಂಶ = av_ಚೌಕಟ್ಟು_new_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು,
                                                        AV_ಚೌಕಟ್ಟು_ದತ್ತಾಂಶ_DYNAMIC_HDR_VIVID,
                                                        ಗಾತ್ರ(AVDynamicHDRVivid));
    ಆದರೆ (!side_ದತ್ತಾಂಶ)
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;

    memset(side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ, 0, ಗಾತ್ರ(AVDynamicHDRVivid));

    ಹಿಂತಿರುಗಿ (AVDynamicHDRVivid *)side_ದತ್ತಾಂಶ->ದತ್ತಾಂಶ;
}

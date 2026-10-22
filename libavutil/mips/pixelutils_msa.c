/*
 * Copyright (c) 2015 Parag Salasakar (Parag.Salasakar@imgtec.com)
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

#समावेश <stddef.h>
#समावेश <stdint.h>

#समावेश "generic_macros_msa.h"
#समावेश "pixelutils.h"

पूर्णांक ff_pixelutils_sad16_msa(स्थिर uint8_t *src, सूचक_भेद_प्रकार src_stride,
                            स्थिर uint8_t *ref, सूचक_भेद_प्रकार ref_stride)
{
    int32_t ht_cnt = 16/4;
    v16u8 src0, src1, ref0, ref1;
    v8u16 sad = { 0 };

    क्रम (; ht_cnt--; ) {
        LD_UB2(src, src_stride, src0, src1);
        src += (2 * src_stride);
        LD_UB2(ref, ref_stride, ref0, ref1);
        ref += (2 * ref_stride);
        sad += SAD_UB2_UH(src0, src1, ref0, ref1);

        LD_UB2(src, src_stride, src0, src1);
        src += (2 * src_stride);
        LD_UB2(ref, ref_stride, ref0, ref1);
        ref += (2 * ref_stride);
        sad += SAD_UB2_UH(src0, src1, ref0, ref1);
    }
    वापस (HADD_UH_U32(sad));
}

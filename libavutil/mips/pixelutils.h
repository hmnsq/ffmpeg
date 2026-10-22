/*
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

#अगर_अघोषित AVUTIL_MIPS_PIXELUTILS_H
#घोषणा AVUTIL_MIPS_PIXELUTILS_H

#समावेश <stddef.h>
#समावेश <stdint.h>

#समावेश "cpu.h"
#समावेश "libavutil/attributes.h"
#समावेश "libavutil/cpu.h"
#समावेश "libavutil/pixelutils.h"

पूर्णांक ff_pixelutils_sad16_msa(स्थिर uint8_t *src1, सूचक_भेद_प्रकार stride1,
                            स्थिर uint8_t *src2, सूचक_भेद_प्रकार stride2);

अटल अंतरभूत av_cold व्योम ff_pixelutils_sad_init_mips(av_pixelutils_sad_fn *sad, पूर्णांक aligned)
{
    पूर्णांक cpu_flags = av_get_cpu_flags();

    अगर (have_msa(cpu_flags)) {
        sad[3] = ff_pixelutils_sad16_msa;
    }
}
#पूर्ण_अगर

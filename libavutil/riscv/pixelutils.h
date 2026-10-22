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

#నిర్వచితం_కాకపోతే AVUTIL_RISCV_PIXELUTILS_H
#నిర్వచించు AVUTIL_RISCV_PIXELUTILS_H

#అన్తర్భావ <stddef.h>
#అన్తర్భావ <stdint.h>

#అన్తర్భావ "config.h"

#అన్తర్భావ "cpu.h"
#అన్తర్భావ "libavutil/attributes.h"
#అన్తర్భావ "libavutil/cpu.h"
#అన్తర్భావ "libavutil/pixelutils.h"

పూర్ణాంకం ff_pixelutils_sad16_rvv(స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                            స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);
పూర్ణాంకం ff_pixelutils_sad8_rvv (స్థిరరాశి uint8_t *src1, ptrdiff_t stride1,
                            స్థిరరాశి uint8_t *src2, ptrdiff_t stride2);

స్థిర అంతఃవరుస av_cold శూన్య ff_pixelutils_init_riscv(av_pixelutils_sad_fn *sad, పూర్ణాంకం aligned)
{
#ఒకవేళ HAVE_RVV
    పూర్ణాంకం flags = av_get_cpu_flags();

    ఒకవేళ (flags & AV_CPU_FLAG_RVV_I32 && ff_rv_vlen_కనిష్ఠ(128)) {
        sad[3] = ff_pixelutils_sad16_rvv;
        sad[2] = ff_pixelutils_sad8_rvv;
    }
#అయితే_ముగింపు
}
#అయితే_ముగింపు

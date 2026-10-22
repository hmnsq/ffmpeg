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

#شامل <limits.h>
#شامل <stdio.h>

#شامل "libavutil/downmix_info.h"
#شامل "libavutil/frame.h"
#شامل "libavutil/mem.h"

صحیح مین(خالی)
{
    AVFrame *چوکھٹا;
    AVDownmixInfo *info, *info2;

    /* First call: allocates side data, zero-initialized. */
    لکھو("Testing av_downmix_info_update_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    اگر (!چوکھٹا)
        واپس 1;

    info = av_downmix_info_update_side_ڈیٹا(چوکھٹا);
    اگر (info) {
        لکھو("create: OK\n");
        لکھو("defaults: type=%d center=%.3f center_ltrt=%.3f surround=%.3f"
               " surround_ltrt=%.3f lfe=%.3f\n",
               info->preferred_downmix_type,
               info->center_mix_level, info->center_mix_level_ltrt,
               info->surround_mix_level, info->surround_mix_level_ltrt,
               info->lfe_mix_level);

        /* Write fields and read them back. The mix levels are absolute scale
         * factors, not gains in dB, so every value is a distinct nonnegative
         * factor. Each one is a negative power of two or a sum of two, which
         * makes the decimal output exact on any platform. */
        info->preferred_downmix_type  = AV_DOWNMIX_TYPE_LTRT;
        info->center_mix_level        = 0.5;
        info->center_mix_level_ltrt   = 0.625;
        info->surround_mix_level      = 0.25;
        info->surround_mix_level_ltrt = 0.375;
        info->lfe_mix_level           = 0.125;
        لکھو("write: type=%d center=%.3f center_ltrt=%.3f surround=%.3f"
               " surround_ltrt=%.3f lfe=%.3f\n",
               info->preferred_downmix_type,
               info->center_mix_level, info->center_mix_level_ltrt,
               info->surround_mix_level, info->surround_mix_level_ltrt,
               info->lfe_mix_level);
    } ورنہ {
        لکھو("create: FAIL\n");
    }

    /* Second call must reuse the existing side data (same pointer, values kept). */
    info2 = av_downmix_info_update_side_ڈیٹا(چوکھٹا);
    اگر (info && info2) {
        لکھو("reuse: same_pointer=%s preserved_type=%d preserved_center=%.3f\n",
               info == info2 ? "yes" : "no",
               info2->preferred_downmix_type, info2->center_mix_level);
    }

    av_چوکھٹا_free(&چوکھٹا);

    /* OOM path: av_max_alloc(1) forces the internal side data allocation to fail. */
    لکھو("\nTesting OOM path\n");
    چوکھٹا = av_چوکھٹا_alloc();
    اگر (چوکھٹا) {
        av_max_alloc(1);
        info = av_downmix_info_update_side_ڈیٹا(چوکھٹا);
        لکھو("OOM: %s\n", info ? "FAIL" : "OK");
        av_max_alloc(زیادہ_سے_زیادہ_عدد);
        av_چوکھٹا_free(&چوکھٹا);
    }

    واپس 0;
}

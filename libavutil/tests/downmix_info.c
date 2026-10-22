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

#अन्तर्भाव <limits.h>
#अन्तर्भाव <stdio.h>

#अन्तर्भाव "libavutil/downmix_info.h"
#अन्तर्भाव "libavutil/frame.h"
#अन्तर्भाव "libavutil/mem.h"

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVFrame *frame;
    AVDownmixInfo *info, *info2;

    /* First call: allocates side data, zero-initialized. */
    प्रारूप_लिख("Testing av_downmix_info_update_side_data()\n");
    frame = av_frame_alloc();
    यदि (!frame)
        प्रत्यागम 1;

    info = av_downmix_info_update_side_दत्त(frame);
    यदि (info) {
        प्रारूप_लिख("create: OK\n");
        प्रारूप_लिख("defaults: type=%d center=%.3f center_ltrt=%.3f surround=%.3f"
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
        प्रारूप_लिख("write: type=%d center=%.3f center_ltrt=%.3f surround=%.3f"
               " surround_ltrt=%.3f lfe=%.3f\n",
               info->preferred_downmix_type,
               info->center_mix_level, info->center_mix_level_ltrt,
               info->surround_mix_level, info->surround_mix_level_ltrt,
               info->lfe_mix_level);
    } अन्यथा {
        प्रारूप_लिख("create: FAIL\n");
    }

    /* Second call must reuse the existing side data (same pointer, values kept). */
    info2 = av_downmix_info_update_side_दत्त(frame);
    यदि (info && info2) {
        प्रारूप_लिख("reuse: same_pointer=%s preserved_type=%d preserved_center=%.3f\n",
               info == info2 ? "yes" : "no",
               info2->preferred_downmix_type, info2->center_mix_level);
    }

    av_frame_free(&frame);

    /* OOM path: av_max_alloc(1) forces the internal side data allocation to fail. */
    प्रारूप_लिख("\nTesting OOM path\n");
    frame = av_frame_alloc();
    यदि (frame) {
        av_max_alloc(1);
        info = av_downmix_info_update_side_दत्त(frame);
        प्रारूप_लिख("OOM: %s\n", info ? "FAIL" : "OK");
        av_max_alloc(अधिकतम_पूर्णाङ्कः);
        av_frame_free(&frame);
    }

    प्रत्यागम 0;
}

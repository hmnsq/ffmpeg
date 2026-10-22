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

#ضمن <limits.h>
#ضمن <stdio.h>

#ضمن "libavutil/frame.h"
#ضمن "libavutil/hdr_dynamic_vivid_metadata.h"
#ضمن "libavutil/mem.h"

صحيح اصلي(فراغ)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *چوکاټ;
    size_t اندازه;

    /* av_dynamic_hdr_vivid_alloc */
    چاپ_کړه("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&اندازه);
    إذا (vivid) {
        چاپ_کړه("alloc: OK, size>0=%s\n", اندازه > 0 ? "yes" : "no");
        چاپ_کړه("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_پیل_کوډ, vivid->عدد_windows);

        /* write and read back */
        vivid->system_پیل_کوډ = 0x01;
        vivid->عدد_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].اوسط_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].اعظمي_maxrgb = (AVRational){ 1000, 1 };
        چاپ_کړه("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_پیل_کوډ, vivid->عدد_windows);
        چاپ_کړه("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.عدد,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].اوسط_maxrgb.عدد,
               vivid->params[0].اوسط_maxrgb.den,
               vivid->params[0].variance_maxrgb.عدد,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].اعظمي_maxrgb.عدد,
               vivid->params[0].اعظمي_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(عدم);
    چاپ_کړه("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    چاپ_کړه("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        vivid = av_dynamic_hdr_vivid_create_side_معلومات(چوکاټ);
        إذا (vivid) {
            چاپ_کړه("side_data: OK\n");
            vivid->system_پیل_کوډ = 0x02;
            چاپ_کړه("side_data write: system_start_code=%u\n",
                   vivid->system_پیل_کوډ);
        } وإلا {
            چاپ_کړه("side_data: FAIL\n");
        }
        av_چوکاټ_free(&چوکاټ);
    }

    /* OOM paths via av_max_alloc */
    چاپ_کړه("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&اندازه);
    چاپ_کړه("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(لوی_عدد);

    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_معلومات(چوکاټ);
        چاپ_کړه("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(لوی_عدد);
        av_چوکاټ_free(&چوکاټ);
    }

    أرجع 0;
}

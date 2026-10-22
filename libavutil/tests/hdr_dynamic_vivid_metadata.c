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

صحيح اصلی(فراغ)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *قاب;
    size_t اندازه;

    /* av_dynamic_hdr_vivid_alloc */
    چاپ_کن("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&اندازه);
    إذا (vivid) {
        چاپ_کن("alloc: OK, size>0=%s\n", اندازه > 0 ? "yes" : "no");
        چاپ_کن("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_شروع_کد, vivid->رقم_windows);

        /* write and read back */
        vivid->system_شروع_کد = 0x01;
        vivid->رقم_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].معدل_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].بیشینه_maxrgb = (AVRational){ 1000, 1 };
        چاپ_کن("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_شروع_کد, vivid->رقم_windows);
        چاپ_کن("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.رقم,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].معدل_maxrgb.رقم,
               vivid->params[0].معدل_maxrgb.den,
               vivid->params[0].variance_maxrgb.رقم,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].بیشینه_maxrgb.رقم,
               vivid->params[0].بیشینه_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(عدم);
    چاپ_کن("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    چاپ_کن("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    قاب = av_قاب_alloc();
    إذا (قاب) {
        vivid = av_dynamic_hdr_vivid_create_side_داده(قاب);
        إذا (vivid) {
            چاپ_کن("side_data: OK\n");
            vivid->system_شروع_کد = 0x02;
            چاپ_کن("side_data write: system_start_code=%u\n",
                   vivid->system_شروع_کد);
        } وإلا {
            چاپ_کن("side_data: FAIL\n");
        }
        av_قاب_free(&قاب);
    }

    /* OOM paths via av_max_alloc */
    چاپ_کن("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&اندازه);
    چاپ_کن("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(بیشترین_صحیح);

    قاب = av_قاب_alloc();
    إذا (قاب) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_داده(قاب);
        چاپ_کن("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(بیشترین_صحیح);
        av_قاب_free(&قاب);
    }

    أرجع 0;
}

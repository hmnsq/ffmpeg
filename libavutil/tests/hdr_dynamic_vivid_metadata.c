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

#అన్తర్భావ <limits.h>
#అన్తర్భావ <stdio.h>

#అన్తర్భావ "libavutil/frame.h"
#అన్తర్భావ "libavutil/hdr_dynamic_vivid_metadata.h"
#అన్తర్భావ "libavutil/mem.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *చట్రం;
    size_t కొలత;

    /* av_dynamic_hdr_vivid_alloc */
    రాయి("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&కొలత);
    ఒకవేళ (vivid) {
        రాయి("alloc: OK, size>0=%s\n", కొలత > 0 ? "yes" : "no");
        రాయి("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_ప్రారంభం_సంకేతం, vivid->అంకె_windows);

        /* write and read back */
        vivid->system_ప్రారంభం_సంకేతం = 0x01;
        vivid->అంకె_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].సరాసరి_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].గరిష్ఠ_maxrgb = (AVRational){ 1000, 1 };
        రాయి("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_ప్రారంభం_సంకేతం, vivid->అంకె_windows);
        రాయి("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.అంకె,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].సరాసరి_maxrgb.అంకె,
               vivid->params[0].సరాసరి_maxrgb.den,
               vivid->params[0].variance_maxrgb.అంకె,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].గరిష్ఠ_maxrgb.అంకె,
               vivid->params[0].గరిష్ఠ_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(ఖాళీ);
    రాయి("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    రాయి("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        vivid = av_dynamic_hdr_vivid_create_side_దత్తాంశం(చట్రం);
        ఒకవేళ (vivid) {
            రాయి("side_data: OK\n");
            vivid->system_ప్రారంభం_సంకేతం = 0x02;
            రాయి("side_data write: system_start_code=%u\n",
                   vivid->system_ప్రారంభం_సంకేతం);
        } లేకపోతే {
            రాయి("side_data: FAIL\n");
        }
        av_చట్రం_free(&చట్రం);
    }

    /* OOM paths via av_max_alloc */
    రాయి("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&కొలత);
    రాయి("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(గరిష్ఠ_పూర్ణాంకం);

    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_దత్తాంశం(చట్రం);
        రాయి("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(గరిష్ఠ_పూర్ణాంకం);
        av_చట్రం_free(&చట్రం);
    }

    తిరిగి 0;
}

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

#অন্তর্ভাব <limits.h>
#অন্তর্ভাব <stdio.h>

#অন্তর্ভাব "libavutil/frame.h"
#অন্তর্ভাব "libavutil/hdr_dynamic_vivid_metadata.h"
#অন্তর্ভাব "libavutil/mem.h"

পূর্ণসংখ্যা প্রধান(শূন্য)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *frame;
    size_t আকার_2;

    /* av_dynamic_hdr_vivid_alloc */
    printf("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&আকার_2);
    যদি (vivid) {
        printf("alloc: OK, size>0=%s\n", আকার_2 > 0 ? "yes" : "no");
        printf("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_start_code, vivid->অঙ্ক_windows);

        /* write and read back */
        vivid->system_start_code = 0x01;
        vivid->অঙ্ক_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].average_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].maximum_maxrgb = (AVRational){ 1000, 1 };
        printf("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_start_code, vivid->অঙ্ক_windows);
        printf("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.অঙ্ক,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].average_maxrgb.অঙ্ক,
               vivid->params[0].average_maxrgb.den,
               vivid->params[0].variance_maxrgb.অঙ্ক,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].maximum_maxrgb.অঙ্ক,
               vivid->params[0].maximum_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(ফাঁকা);
    printf("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    printf("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    frame = av_frame_alloc();
    যদি (frame) {
        vivid = av_dynamic_hdr_vivid_create_side_তথ্য(frame);
        যদি (vivid) {
            printf("side_data: OK\n");
            vivid->system_start_code = 0x02;
            printf("side_data write: system_start_code=%u\n",
                   vivid->system_start_code);
        } অন্যথা {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    printf("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&আকার_2);
    printf("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(INT_MAX);

    frame = av_frame_alloc();
    যদি (frame) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_তথ্য(frame);
        printf("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(INT_MAX);
        av_frame_free(&frame);
    }

    ফেরত 0;
}

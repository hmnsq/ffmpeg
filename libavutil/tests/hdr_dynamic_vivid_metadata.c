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

#अन्तर्भाव "libavutil/frame.h"
#अन्तर्भाव "libavutil/hdr_dynamic_vivid_metadata.h"
#अन्तर्भाव "libavutil/mem.h"

पूर्णाङ्क main(शून्य)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *frame;
    size_t size;

    /* av_dynamic_hdr_vivid_alloc */
    printf("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&size);
    सचे (vivid) {
        printf("alloc: OK, size>0=%s\n", size > 0 ? "yes" : "no");
        printf("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_start_code, vivid->अङ्कः_windows);

        /* write and read back */
        vivid->system_start_code = 0x01;
        vivid->अङ्कः_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].average_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].maximum_maxrgb = (AVRational){ 1000, 1 };
        printf("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_start_code, vivid->अङ्कः_windows);
        printf("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.अङ्कः,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].average_maxrgb.अङ्कः,
               vivid->params[0].average_maxrgb.den,
               vivid->params[0].variance_maxrgb.अङ्कः,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].maximum_maxrgb.अङ्कः,
               vivid->params[0].maximum_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(रिक्त);
    printf("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    printf("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    frame = av_frame_alloc();
    सचे (frame) {
        vivid = av_dynamic_hdr_vivid_create_side_data(frame);
        सचे (vivid) {
            printf("side_data: OK\n");
            vivid->system_start_code = 0x02;
            printf("side_data write: system_start_code=%u\n",
                   vivid->system_start_code);
        } अञ्ञथा {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    printf("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&size);
    printf("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(INT_MAX);

    frame = av_frame_alloc();
    सचे (frame) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_data(frame);
        printf("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(INT_MAX);
        av_frame_free(&frame);
    }

    पटिनिवत्त 0;
}

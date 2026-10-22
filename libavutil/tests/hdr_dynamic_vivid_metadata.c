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

#അന്തര്ഭാവ <limits.h>
#അന്തര്ഭാവ <stdio.h>

#അന്തര്ഭാവ "libavutil/frame.h"
#അന്തര്ഭാവ "libavutil/hdr_dynamic_vivid_metadata.h"
#അന്തര്ഭാവ "libavutil/mem.h"

പൂർണ്ണസംഖ്യ പ്രധാന(ശൂന്യം)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *frame;
    size_t size;

    /* av_dynamic_hdr_vivid_alloc */
    printf("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&size);
    എങ്കിൽ (vivid) {
        printf("alloc: OK, size>0=%s\n", size > 0 ? "yes" : "no");
        printf("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_start_code, vivid->അക്കം_windows);

        /* write and read back */
        vivid->system_start_code = 0x01;
        vivid->അക്കം_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].average_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].maximum_maxrgb = (AVRational){ 1000, 1 };
        printf("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_start_code, vivid->അക്കം_windows);
        printf("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.അക്കം,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].average_maxrgb.അക്കം,
               vivid->params[0].average_maxrgb.den,
               vivid->params[0].variance_maxrgb.അക്കം,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].maximum_maxrgb.അക്കം,
               vivid->params[0].maximum_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(ശൂന്യ);
    printf("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    printf("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    frame = av_frame_alloc();
    എങ്കിൽ (frame) {
        vivid = av_dynamic_hdr_vivid_create_side_data(frame);
        എങ്കിൽ (vivid) {
            printf("side_data: OK\n");
            vivid->system_start_code = 0x02;
            printf("side_data write: system_start_code=%u\n",
                   vivid->system_start_code);
        } അല്ലെങ്കിൽ {
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
    എങ്കിൽ (frame) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_data(frame);
        printf("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(INT_MAX);
        av_frame_free(&frame);
    }

    തിരികെ 0;
}

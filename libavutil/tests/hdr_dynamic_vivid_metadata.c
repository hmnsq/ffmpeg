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

#समावेश <limits.h>
#समावेश <stdio.h>

#समावेश "libavutil/frame.h"
#समावेश "libavutil/hdr_dynamic_vivid_metadata.h"
#समावेश "libavutil/mem.h"

पूर्णांक मुख्य(व्योम)
{
    AVDynamicHDRVivid *vivid;
    AVFrame *frame;
    माप_प्रकार आकार;

    /* av_dynamic_hdr_vivid_alloc */
    म_लिखो("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&आकार);
    अगर (vivid) {
        म_लिखो("alloc: OK, size>0=%s\n", आकार > 0 ? "yes" : "no");
        म_लिखो("defaults: system_start_code=%u, num_windows=%u\n",
               vivid->system_start_code, vivid->अंक_windows);

        /* write and read back */
        vivid->system_start_code = 0x01;
        vivid->अंक_windows = 1;
        vivid->params[0].minimum_maxrgb = (AVRational){ 100, 1 };
        vivid->params[0].average_maxrgb = (AVRational){ 500, 1 };
        vivid->params[0].variance_maxrgb = (AVRational){ 200, 1 };
        vivid->params[0].maximum_maxrgb = (AVRational){ 1000, 1 };
        म_लिखो("write: system_start_code=%u, num_windows=%u\n",
               vivid->system_start_code, vivid->अंक_windows);
        म_लिखो("params[0]: min=%d/%d avg=%d/%d var=%d/%d max=%d/%d\n",
               vivid->params[0].minimum_maxrgb.अंक,
               vivid->params[0].minimum_maxrgb.den,
               vivid->params[0].average_maxrgb.अंक,
               vivid->params[0].average_maxrgb.den,
               vivid->params[0].variance_maxrgb.अंक,
               vivid->params[0].variance_maxrgb.den,
               vivid->params[0].maximum_maxrgb.अंक,
               vivid->params[0].maximum_maxrgb.den);
        av_free(vivid);
    }

    /* alloc with NULL size */
    vivid = av_dynamic_hdr_vivid_alloc(शून्य);
    म_लिखो("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    म_लिखो("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    frame = av_frame_alloc();
    अगर (frame) {
        vivid = av_dynamic_hdr_vivid_create_side_तथ्य(frame);
        अगर (vivid) {
            म_लिखो("side_data: OK\n");
            vivid->system_start_code = 0x02;
            म_लिखो("side_data write: system_start_code=%u\n",
                   vivid->system_start_code);
        } अन्यथा {
            म_लिखो("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    म_लिखो("\nTesting OOM paths\n");
    av_max_alloc(1);
    vivid = av_dynamic_hdr_vivid_alloc(&आकार);
    म_लिखो("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(पूर्णांक_उच्च);

    frame = av_frame_alloc();
    अगर (frame) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_तथ्य(frame);
        म_लिखो("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(पूर्णांक_उच्च);
        av_frame_free(&frame);
    }

    वापस 0;
}

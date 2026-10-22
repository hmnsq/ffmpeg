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
    माप_प्रकार size;

    /* av_dynamic_hdr_vivid_alloc */
    म_लिखो("Testing av_dynamic_hdr_vivid_alloc()\n");
    vivid = av_dynamic_hdr_vivid_alloc(&size);
    यदि (vivid) {
        म_लिखो("alloc: OK, size>0=%s\n", size > 0 ? "yes" : "no");
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
    vivid = av_dynamic_hdr_vivid_alloc(रिक्त);
    म_लिखो("alloc (no size): %s\n", vivid ? "OK" : "FAIL");
    av_free(vivid);

    /* av_dynamic_hdr_vivid_create_side_data */
    म_लिखो("\nTesting av_dynamic_hdr_vivid_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        vivid = av_dynamic_hdr_vivid_create_side_data(frame);
        यदि (vivid) {
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
    vivid = av_dynamic_hdr_vivid_alloc(&size);
    म_लिखो("alloc OOM: %s\n", vivid ? "FAIL" : "OK");
    av_free(vivid);
    av_max_alloc(पूर्णांक_उच्च);

    frame = av_frame_alloc();
    यदि (frame) {
        av_max_alloc(1);
        vivid = av_dynamic_hdr_vivid_create_side_data(frame);
        म_लिखो("side_data OOM: %s\n", vivid ? "FAIL" : "OK");
        av_max_alloc(पूर्णांक_उच्च);
        av_frame_free(&frame);
    }

    प्रत्यागम 0;
}

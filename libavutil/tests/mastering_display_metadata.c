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
#अन्तर्भाव "libavutil/mastering_display_metadata.h"
#अन्तर्भाव "libavutil/mem.h"

पूर्णाङ्क main(शून्य)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *frame;
    माप_प्रकार size;

    /* av_mastering_display_metadata_alloc */
    म_लिखो("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    यदि (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        म_लिखो("alloc: OK\n");
        म_लिखो("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].अंक,
               mdm->display_primaries[0][0].den,
               mdm->white_point[0].अंक, mdm->white_point[0].den);
        म_लिखो("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.अंक, mdm->min_luminance.den,
               mdm->max_luminance.अंक, mdm->max_luminance.den);
        म_लिखो("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } अन्यथा {
        म_लिखो("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    म_लिखो("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_size(&size);
    यदि (mdm) {
        म_लिखो("alloc_size: OK, size>0=%s\n", size > 0 ? "yes" : "no");
        म_लिखो("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].अंक,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } अन्यथा {
        म_लिखो("alloc_size: FAIL\n");
    }

    /* write and read back */
    म_लिखो("\nTesting write/read back\n");
    mdm = av_mastering_display_metadata_alloc();
    यदि (mdm) {
        mdm->display_primaries[0][0] = (AVRational){ 34000, 50000 };
        mdm->display_primaries[0][1] = (AVRational){ 16000, 50000 };
        mdm->white_point[0] = (AVRational){ 15635, 50000 };
        mdm->white_point[1] = (AVRational){ 16450, 50000 };
        mdm->min_luminance = (AVRational){ 50, 10000 };
        mdm->max_luminance = (AVRational){ 10000000, 10000 };
        mdm->has_primaries = 1;
        mdm->has_luminance = 1;
        म_लिखो("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].अंक,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].अंक,
               mdm->display_primaries[0][1].den);
        म_लिखो("white_point=(%d/%d, %d/%d)\n",
               mdm->white_point[0].अंक, mdm->white_point[0].den,
               mdm->white_point[1].अंक, mdm->white_point[1].den);
        म_लिखो("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.अंक, mdm->min_luminance.den,
               mdm->max_luminance.अंक, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    म_लिखो("\nTesting av_mastering_display_metadata_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        mdm = av_mastering_display_metadata_create_side_data(frame);
        यदि (mdm) {
            म_लिखो("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].अंक,
                   mdm->display_primaries[0][0].den);
        } अन्यथा {
            म_लिखो("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* av_content_light_metadata_alloc */
    म_लिखो("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&size);
    यदि (clm) {
        म_लिखो("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               size > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        म_लिखो("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } अन्यथा {
        म_लिखो("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    म_लिखो("\nTesting av_content_light_metadata_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        clm = av_content_light_metadata_create_side_data(frame);
        यदि (clm) {
            म_लिखो("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } अन्यथा {
            म_लिखो("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    म_लिखो("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    म_लिखो("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_size(&size);
    म_लिखो("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&size);
    म_लिखो("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(पूर्णांक_उच्च);

    frame = av_frame_alloc();
    यदि (frame) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_data(frame);
        म_लिखो("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_data(frame);
        म_लिखो("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(पूर्णांक_उच्च);
        av_frame_free(&frame);
    }

    प्रत्यागम 0;
}

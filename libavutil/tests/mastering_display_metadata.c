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

पूर्णाङ्क मुख्यम्(शून्य)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *frame;
    size_t आकार;

    /* av_mastering_display_metadata_alloc */
    प्रारूप_लिख("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    यदि (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        प्रारूप_लिख("alloc: OK\n");
        प्रारूप_लिख("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].अङ्कः,
               mdm->display_primaries[0][0].den,
               mdm->white_point[0].अङ्कः, mdm->white_point[0].den);
        प्रारूप_लिख("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.अङ्कः, mdm->min_luminance.den,
               mdm->max_luminance.अङ्कः, mdm->max_luminance.den);
        प्रारूप_लिख("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } अन्यथा {
        प्रारूप_लिख("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    प्रारूप_लिख("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_आकार(&आकार);
    यदि (mdm) {
        प्रारूप_लिख("alloc_size: OK, size>0=%s\n", आकार > 0 ? "yes" : "no");
        प्रारूप_लिख("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].अङ्कः,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } अन्यथा {
        प्रारूप_लिख("alloc_size: FAIL\n");
    }

    /* write and read back */
    प्रारूप_लिख("\nTesting write/read back\n");
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
        प्रारूप_लिख("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].अङ्कः,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].अङ्कः,
               mdm->display_primaries[0][1].den);
        प्रारूप_लिख("white_point=(%d/%d, %d/%d)\n",
               mdm->white_point[0].अङ्कः, mdm->white_point[0].den,
               mdm->white_point[1].अङ्कः, mdm->white_point[1].den);
        प्रारूप_लिख("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.अङ्कः, mdm->min_luminance.den,
               mdm->max_luminance.अङ्कः, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    प्रारूप_लिख("\nTesting av_mastering_display_metadata_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        mdm = av_mastering_display_metadata_create_side_दत्त(frame);
        यदि (mdm) {
            प्रारूप_लिख("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].अङ्कः,
                   mdm->display_primaries[0][0].den);
        } अन्यथा {
            प्रारूप_लिख("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* av_content_light_metadata_alloc */
    प्रारूप_लिख("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&आकार);
    यदि (clm) {
        प्रारूप_लिख("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               आकार > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        प्रारूप_लिख("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } अन्यथा {
        प्रारूप_लिख("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    प्रारूप_लिख("\nTesting av_content_light_metadata_create_side_data()\n");
    frame = av_frame_alloc();
    यदि (frame) {
        clm = av_content_light_metadata_create_side_दत्त(frame);
        यदि (clm) {
            प्रारूप_लिख("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } अन्यथा {
            प्रारूप_लिख("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    प्रारूप_लिख("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    प्रारूप_लिख("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_आकार(&आकार);
    प्रारूप_लिख("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&आकार);
    प्रारूप_लिख("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(अधिकतम_पूर्णाङ्कः);

    frame = av_frame_alloc();
    यदि (frame) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_दत्त(frame);
        प्रारूप_लिख("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_दत्त(frame);
        प्रारूप_लिख("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(अधिकतम_पूर्णाङ्कः);
        av_frame_free(&frame);
    }

    प्रत्यागम 0;
}

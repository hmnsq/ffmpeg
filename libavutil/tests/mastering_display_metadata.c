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
#অন্তর্ভাব "libavutil/mastering_display_metadata.h"
#অন্তর্ভাব "libavutil/mem.h"

পূর্ণাঙ্ক main(শূন্য)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *frame;
    size_t size;

    /* av_mastering_display_metadata_alloc */
    printf("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    যদি (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        printf("alloc: OK\n");
        printf("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].অঙ্ক,
               mdm->display_primaries[0][0].den,
               mdm->white_point[0].অঙ্ক, mdm->white_point[0].den);
        printf("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.অঙ্ক, mdm->min_luminance.den,
               mdm->max_luminance.অঙ্ক, mdm->max_luminance.den);
        printf("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } অন্যথা {
        printf("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    printf("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_size(&size);
    যদি (mdm) {
        printf("alloc_size: OK, size>0=%s\n", size > 0 ? "yes" : "no");
        printf("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].অঙ্ক,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } অন্যথা {
        printf("alloc_size: FAIL\n");
    }

    /* write and read back */
    printf("\nTesting write/read back\n");
    mdm = av_mastering_display_metadata_alloc();
    যদি (mdm) {
        mdm->display_primaries[0][0] = (AVRational){ 34000, 50000 };
        mdm->display_primaries[0][1] = (AVRational){ 16000, 50000 };
        mdm->white_point[0] = (AVRational){ 15635, 50000 };
        mdm->white_point[1] = (AVRational){ 16450, 50000 };
        mdm->min_luminance = (AVRational){ 50, 10000 };
        mdm->max_luminance = (AVRational){ 10000000, 10000 };
        mdm->has_primaries = 1;
        mdm->has_luminance = 1;
        printf("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].অঙ্ক,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].অঙ্ক,
               mdm->display_primaries[0][1].den);
        printf("white_point=(%d/%d, %d/%d)\n",
               mdm->white_point[0].অঙ্ক, mdm->white_point[0].den,
               mdm->white_point[1].অঙ্ক, mdm->white_point[1].den);
        printf("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.অঙ্ক, mdm->min_luminance.den,
               mdm->max_luminance.অঙ্ক, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    printf("\nTesting av_mastering_display_metadata_create_side_data()\n");
    frame = av_frame_alloc();
    যদি (frame) {
        mdm = av_mastering_display_metadata_create_side_data(frame);
        যদি (mdm) {
            printf("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].অঙ্ক,
                   mdm->display_primaries[0][0].den);
        } অন্যথা {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* av_content_light_metadata_alloc */
    printf("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&size);
    যদি (clm) {
        printf("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               size > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        printf("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } অন্যথা {
        printf("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    printf("\nTesting av_content_light_metadata_create_side_data()\n");
    frame = av_frame_alloc();
    যদি (frame) {
        clm = av_content_light_metadata_create_side_data(frame);
        যদি (clm) {
            printf("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } অন্যথা {
            printf("side_data: FAIL\n");
        }
        av_frame_free(&frame);
    }

    /* OOM paths via av_max_alloc */
    printf("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    printf("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_size(&size);
    printf("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&size);
    printf("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(INT_MAX);

    frame = av_frame_alloc();
    যদি (frame) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_data(frame);
        printf("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_data(frame);
        printf("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(INT_MAX);
        av_frame_free(&frame);
    }

    প্রত্যাগম 0;
}

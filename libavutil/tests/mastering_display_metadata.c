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
#అన్తర్భావ "libavutil/mastering_display_metadata.h"
#అన్తర్భావ "libavutil/mem.h"

పూర్ణాంకం ప్రధాన(శూన్య)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *చట్రం;
    size_t కొలత;

    /* av_mastering_display_metadata_alloc */
    రాయి("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    ఒకవేళ (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        రాయి("alloc: OK\n");
        రాయి("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].అంకె,
               mdm->display_primaries[0][0].den,
               mdm->white_బిందువు_2[0].అంకె, mdm->white_బిందువు_2[0].den);
        రాయి("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.అంకె, mdm->min_luminance.den,
               mdm->max_luminance.అంకె, mdm->max_luminance.den);
        రాయి("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } లేకపోతే {
        రాయి("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    రాయి("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_కొలత(&కొలత);
    ఒకవేళ (mdm) {
        రాయి("alloc_size: OK, size>0=%s\n", కొలత > 0 ? "yes" : "no");
        రాయి("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].అంకె,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } లేకపోతే {
        రాయి("alloc_size: FAIL\n");
    }

    /* write and read back */
    రాయి("\nTesting write/read back\n");
    mdm = av_mastering_display_metadata_alloc();
    ఒకవేళ (mdm) {
        mdm->display_primaries[0][0] = (AVRational){ 34000, 50000 };
        mdm->display_primaries[0][1] = (AVRational){ 16000, 50000 };
        mdm->white_బిందువు_2[0] = (AVRational){ 15635, 50000 };
        mdm->white_బిందువు_2[1] = (AVRational){ 16450, 50000 };
        mdm->min_luminance = (AVRational){ 50, 10000 };
        mdm->max_luminance = (AVRational){ 10000000, 10000 };
        mdm->has_primaries = 1;
        mdm->has_luminance = 1;
        రాయి("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].అంకె,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].అంకె,
               mdm->display_primaries[0][1].den);
        రాయి("white_point=(%d/%d, %d/%d)\n",
               mdm->white_బిందువు_2[0].అంకె, mdm->white_బిందువు_2[0].den,
               mdm->white_బిందువు_2[1].అంకె, mdm->white_బిందువు_2[1].den);
        రాయి("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.అంకె, mdm->min_luminance.den,
               mdm->max_luminance.అంకె, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    రాయి("\nTesting av_mastering_display_metadata_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        mdm = av_mastering_display_metadata_create_side_దత్తాంశం(చట్రం);
        ఒకవేళ (mdm) {
            రాయి("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].అంకె,
                   mdm->display_primaries[0][0].den);
        } లేకపోతే {
            రాయి("side_data: FAIL\n");
        }
        av_చట్రం_free(&చట్రం);
    }

    /* av_content_light_metadata_alloc */
    రాయి("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&కొలత);
    ఒకవేళ (clm) {
        రాయి("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               కొలత > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        రాయి("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } లేకపోతే {
        రాయి("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    రాయి("\nTesting av_content_light_metadata_create_side_data()\n");
    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        clm = av_content_light_metadata_create_side_దత్తాంశం(చట్రం);
        ఒకవేళ (clm) {
            రాయి("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } లేకపోతే {
            రాయి("side_data: FAIL\n");
        }
        av_చట్రం_free(&చట్రం);
    }

    /* OOM paths via av_max_alloc */
    రాయి("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    రాయి("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_కొలత(&కొలత);
    రాయి("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&కొలత);
    రాయి("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(గరిష్ఠ_పూర్ణాంకం);

    చట్రం = av_చట్రం_alloc();
    ఒకవేళ (చట్రం) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_దత్తాంశం(చట్రం);
        రాయి("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_దత్తాంశం(చట్రం);
        రాయి("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(గరిష్ఠ_పూర్ణాంకం);
        av_చట్రం_free(&చట్రం);
    }

    తిరిగి 0;
}

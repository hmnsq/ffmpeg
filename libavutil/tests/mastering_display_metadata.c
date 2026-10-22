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

#ضمن <limits.h>
#ضمن <stdio.h>

#ضمن "libavutil/frame.h"
#ضمن "libavutil/mastering_display_metadata.h"
#ضمن "libavutil/mem.h"

صحيح اصلی(فراغ)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *قاب;
    size_t اندازه;

    /* av_mastering_display_metadata_alloc */
    چاپ_کن("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    إذا (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        چاپ_کن("alloc: OK\n");
        چاپ_کن("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].رقم,
               mdm->display_primaries[0][0].den,
               mdm->white_نقطه_2[0].رقم, mdm->white_نقطه_2[0].den);
        چاپ_کن("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.رقم, mdm->min_luminance.den,
               mdm->max_luminance.رقم, mdm->max_luminance.den);
        چاپ_کن("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } وإلا {
        چاپ_کن("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    چاپ_کن("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_اندازه(&اندازه);
    إذا (mdm) {
        چاپ_کن("alloc_size: OK, size>0=%s\n", اندازه > 0 ? "yes" : "no");
        چاپ_کن("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].رقم,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } وإلا {
        چاپ_کن("alloc_size: FAIL\n");
    }

    /* write and read back */
    چاپ_کن("\nTesting write/read back\n");
    mdm = av_mastering_display_metadata_alloc();
    إذا (mdm) {
        mdm->display_primaries[0][0] = (AVRational){ 34000, 50000 };
        mdm->display_primaries[0][1] = (AVRational){ 16000, 50000 };
        mdm->white_نقطه_2[0] = (AVRational){ 15635, 50000 };
        mdm->white_نقطه_2[1] = (AVRational){ 16450, 50000 };
        mdm->min_luminance = (AVRational){ 50, 10000 };
        mdm->max_luminance = (AVRational){ 10000000, 10000 };
        mdm->has_primaries = 1;
        mdm->has_luminance = 1;
        چاپ_کن("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].رقم,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].رقم,
               mdm->display_primaries[0][1].den);
        چاپ_کن("white_point=(%d/%d, %d/%d)\n",
               mdm->white_نقطه_2[0].رقم, mdm->white_نقطه_2[0].den,
               mdm->white_نقطه_2[1].رقم, mdm->white_نقطه_2[1].den);
        چاپ_کن("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.رقم, mdm->min_luminance.den,
               mdm->max_luminance.رقم, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    چاپ_کن("\nTesting av_mastering_display_metadata_create_side_data()\n");
    قاب = av_قاب_alloc();
    إذا (قاب) {
        mdm = av_mastering_display_metadata_create_side_داده(قاب);
        إذا (mdm) {
            چاپ_کن("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].رقم,
                   mdm->display_primaries[0][0].den);
        } وإلا {
            چاپ_کن("side_data: FAIL\n");
        }
        av_قاب_free(&قاب);
    }

    /* av_content_light_metadata_alloc */
    چاپ_کن("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&اندازه);
    إذا (clm) {
        چاپ_کن("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               اندازه > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        چاپ_کن("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } وإلا {
        چاپ_کن("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    چاپ_کن("\nTesting av_content_light_metadata_create_side_data()\n");
    قاب = av_قاب_alloc();
    إذا (قاب) {
        clm = av_content_light_metadata_create_side_داده(قاب);
        إذا (clm) {
            چاپ_کن("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } وإلا {
            چاپ_کن("side_data: FAIL\n");
        }
        av_قاب_free(&قاب);
    }

    /* OOM paths via av_max_alloc */
    چاپ_کن("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    چاپ_کن("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_اندازه(&اندازه);
    چاپ_کن("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&اندازه);
    چاپ_کن("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(بیشترین_صحیح);

    قاب = av_قاب_alloc();
    إذا (قاب) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_داده(قاب);
        چاپ_کن("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_داده(قاب);
        چاپ_کن("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(بیشترین_صحیح);
        av_قاب_free(&قاب);
    }

    أرجع 0;
}

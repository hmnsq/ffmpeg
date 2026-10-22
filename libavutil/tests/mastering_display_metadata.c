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

صحيح اصلي(فراغ)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *چوکاټ;
    size_t اندازه;

    /* av_mastering_display_metadata_alloc */
    چاپ_کړه("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    إذا (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        چاپ_کړه("alloc: OK\n");
        چاپ_کړه("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].عدد,
               mdm->display_primaries[0][0].den,
               mdm->white_ټکی_2[0].عدد, mdm->white_ټکی_2[0].den);
        چاپ_کړه("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.عدد, mdm->min_luminance.den,
               mdm->max_luminance.عدد, mdm->max_luminance.den);
        چاپ_کړه("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } وإلا {
        چاپ_کړه("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    چاپ_کړه("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_اندازه(&اندازه);
    إذا (mdm) {
        چاپ_کړه("alloc_size: OK, size>0=%s\n", اندازه > 0 ? "yes" : "no");
        چاپ_کړه("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].عدد,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } وإلا {
        چاپ_کړه("alloc_size: FAIL\n");
    }

    /* write and read back */
    چاپ_کړه("\nTesting write/read back\n");
    mdm = av_mastering_display_metadata_alloc();
    إذا (mdm) {
        mdm->display_primaries[0][0] = (AVRational){ 34000, 50000 };
        mdm->display_primaries[0][1] = (AVRational){ 16000, 50000 };
        mdm->white_ټکی_2[0] = (AVRational){ 15635, 50000 };
        mdm->white_ټکی_2[1] = (AVRational){ 16450, 50000 };
        mdm->min_luminance = (AVRational){ 50, 10000 };
        mdm->max_luminance = (AVRational){ 10000000, 10000 };
        mdm->has_primaries = 1;
        mdm->has_luminance = 1;
        چاپ_کړه("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].عدد,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].عدد,
               mdm->display_primaries[0][1].den);
        چاپ_کړه("white_point=(%d/%d, %d/%d)\n",
               mdm->white_ټکی_2[0].عدد, mdm->white_ټکی_2[0].den,
               mdm->white_ټکی_2[1].عدد, mdm->white_ټکی_2[1].den);
        چاپ_کړه("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.عدد, mdm->min_luminance.den,
               mdm->max_luminance.عدد, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    چاپ_کړه("\nTesting av_mastering_display_metadata_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        mdm = av_mastering_display_metadata_create_side_معلومات(چوکاټ);
        إذا (mdm) {
            چاپ_کړه("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].عدد,
                   mdm->display_primaries[0][0].den);
        } وإلا {
            چاپ_کړه("side_data: FAIL\n");
        }
        av_چوکاټ_free(&چوکاټ);
    }

    /* av_content_light_metadata_alloc */
    چاپ_کړه("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&اندازه);
    إذا (clm) {
        چاپ_کړه("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               اندازه > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        چاپ_کړه("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } وإلا {
        چاپ_کړه("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    چاپ_کړه("\nTesting av_content_light_metadata_create_side_data()\n");
    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        clm = av_content_light_metadata_create_side_معلومات(چوکاټ);
        إذا (clm) {
            چاپ_کړه("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } وإلا {
            چاپ_کړه("side_data: FAIL\n");
        }
        av_چوکاټ_free(&چوکاټ);
    }

    /* OOM paths via av_max_alloc */
    چاپ_کړه("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    چاپ_کړه("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_اندازه(&اندازه);
    چاپ_کړه("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&اندازه);
    چاپ_کړه("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(لوی_عدد);

    چوکاټ = av_چوکاټ_alloc();
    إذا (چوکاټ) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_معلومات(چوکاټ);
        چاپ_کړه("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_معلومات(چوکاټ);
        چاپ_کړه("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(لوی_عدد);
        av_چوکاټ_free(&چوکاټ);
    }

    أرجع 0;
}

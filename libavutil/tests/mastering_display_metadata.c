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

صحيح مکھ(فراغ)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *چوکھٹا;
    size_t ناپ;

    /* av_mastering_display_metadata_alloc */
    لکھو("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    إذا (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        لکھو("alloc: OK\n");
        لکھو("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].عدد,
               mdm->display_primaries[0][0].den,
               mdm->white_نقطہ_2[0].عدد, mdm->white_نقطہ_2[0].den);
        لکھو("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.عدد, mdm->min_luminance.den,
               mdm->max_luminance.عدد, mdm->max_luminance.den);
        لکھو("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } وإلا {
        لکھو("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    لکھو("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_ناپ(&ناپ);
    إذا (mdm) {
        لکھو("alloc_size: OK, size>0=%s\n", ناپ > 0 ? "yes" : "no");
        لکھو("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].عدد,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } وإلا {
        لکھو("alloc_size: FAIL\n");
    }

    /* write and read back */
    لکھو("\nTesting write/read back\n");
    mdm = av_mastering_display_metadata_alloc();
    إذا (mdm) {
        mdm->display_primaries[0][0] = (AVRational){ 34000, 50000 };
        mdm->display_primaries[0][1] = (AVRational){ 16000, 50000 };
        mdm->white_نقطہ_2[0] = (AVRational){ 15635, 50000 };
        mdm->white_نقطہ_2[1] = (AVRational){ 16450, 50000 };
        mdm->min_luminance = (AVRational){ 50, 10000 };
        mdm->max_luminance = (AVRational){ 10000000, 10000 };
        mdm->has_primaries = 1;
        mdm->has_luminance = 1;
        لکھو("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].عدد,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].عدد,
               mdm->display_primaries[0][1].den);
        لکھو("white_point=(%d/%d, %d/%d)\n",
               mdm->white_نقطہ_2[0].عدد, mdm->white_نقطہ_2[0].den,
               mdm->white_نقطہ_2[1].عدد, mdm->white_نقطہ_2[1].den);
        لکھو("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.عدد, mdm->min_luminance.den,
               mdm->max_luminance.عدد, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    لکھو("\nTesting av_mastering_display_metadata_create_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    إذا (چوکھٹا) {
        mdm = av_mastering_display_metadata_create_side_انکڑے(چوکھٹا);
        إذا (mdm) {
            لکھو("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].عدد,
                   mdm->display_primaries[0][0].den);
        } وإلا {
            لکھو("side_data: FAIL\n");
        }
        av_چوکھٹا_free(&چوکھٹا);
    }

    /* av_content_light_metadata_alloc */
    لکھو("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&ناپ);
    إذا (clm) {
        لکھو("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               ناپ > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        لکھو("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } وإلا {
        لکھو("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    لکھو("\nTesting av_content_light_metadata_create_side_data()\n");
    چوکھٹا = av_چوکھٹا_alloc();
    إذا (چوکھٹا) {
        clm = av_content_light_metadata_create_side_انکڑے(چوکھٹا);
        إذا (clm) {
            لکھو("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } وإلا {
            لکھو("side_data: FAIL\n");
        }
        av_چوکھٹا_free(&چوکھٹا);
    }

    /* OOM paths via av_max_alloc */
    لکھو("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    لکھو("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_ناپ(&ناپ);
    لکھو("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&ناپ);
    لکھو("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(ودھ_توں_ودھ_عدد);

    چوکھٹا = av_چوکھٹا_alloc();
    إذا (چوکھٹا) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_انکڑے(چوکھٹا);
        لکھو("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_انکڑے(چوکھٹا);
        لکھو("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(ودھ_توں_ودھ_عدد);
        av_چوکھٹا_free(&چوکھٹا);
    }

    أرجع 0;
}

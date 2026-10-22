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

صحيح مکيه(فراغ)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *چوکٺو;
    size_t سائيز;

    /* av_mastering_display_metadata_alloc */
    لکو("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    إذا (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        لکو("alloc: OK\n");
        لکو("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].انگ,
               mdm->display_primaries[0][0].den,
               mdm->white_نقطو_2[0].انگ, mdm->white_نقطو_2[0].den);
        لکو("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.انگ, mdm->min_luminance.den,
               mdm->max_luminance.انگ, mdm->max_luminance.den);
        لکو("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } وإلا {
        لکو("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    لکو("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_سائيز(&سائيز);
    إذا (mdm) {
        لکو("alloc_size: OK, size>0=%s\n", سائيز > 0 ? "yes" : "no");
        لکو("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].انگ,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } وإلا {
        لکو("alloc_size: FAIL\n");
    }

    /* write and read back */
    لکو("\nTesting write/read back\n");
    mdm = av_mastering_display_metadata_alloc();
    إذا (mdm) {
        mdm->display_primaries[0][0] = (AVRational){ 34000, 50000 };
        mdm->display_primaries[0][1] = (AVRational){ 16000, 50000 };
        mdm->white_نقطو_2[0] = (AVRational){ 15635, 50000 };
        mdm->white_نقطو_2[1] = (AVRational){ 16450, 50000 };
        mdm->min_luminance = (AVRational){ 50, 10000 };
        mdm->max_luminance = (AVRational){ 10000000, 10000 };
        mdm->has_primaries = 1;
        mdm->has_luminance = 1;
        لکو("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].انگ,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].انگ,
               mdm->display_primaries[0][1].den);
        لکو("white_point=(%d/%d, %d/%d)\n",
               mdm->white_نقطو_2[0].انگ, mdm->white_نقطو_2[0].den,
               mdm->white_نقطو_2[1].انگ, mdm->white_نقطو_2[1].den);
        لکو("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.انگ, mdm->min_luminance.den,
               mdm->max_luminance.انگ, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    لکو("\nTesting av_mastering_display_metadata_create_side_data()\n");
    چوکٺو = av_چوکٺو_alloc();
    إذا (چوکٺو) {
        mdm = av_mastering_display_metadata_create_side_معلومات(چوکٺو);
        إذا (mdm) {
            لکو("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].انگ,
                   mdm->display_primaries[0][0].den);
        } وإلا {
            لکو("side_data: FAIL\n");
        }
        av_چوکٺو_free(&چوکٺو);
    }

    /* av_content_light_metadata_alloc */
    لکو("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&سائيز);
    إذا (clm) {
        لکو("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               سائيز > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        لکو("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } وإلا {
        لکو("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    لکو("\nTesting av_content_light_metadata_create_side_data()\n");
    چوکٺو = av_چوکٺو_alloc();
    إذا (چوکٺو) {
        clm = av_content_light_metadata_create_side_معلومات(چوکٺو);
        إذا (clm) {
            لکو("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } وإلا {
            لکو("side_data: FAIL\n");
        }
        av_چوکٺو_free(&چوکٺو);
    }

    /* OOM paths via av_max_alloc */
    لکو("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    لکو("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_سائيز(&سائيز);
    لکو("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&سائيز);
    لکو("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(وڌ_کان_وڌ_عدد);

    چوکٺو = av_چوکٺو_alloc();
    إذا (چوکٺو) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_معلومات(چوکٺو);
        لکو("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_معلومات(چوکٺو);
        لکو("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(وڌ_کان_وڌ_عدد);
        av_چوکٺو_free(&چوکٺو);
    }

    أرجع 0;
}

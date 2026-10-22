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

#ਅਨ੍ਤਰ੍ਭਾਵ <limits.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/frame.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mastering_display_metadata.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "libavutil/mem.h"

ਪੂਰਨ ਮੁੱਖ(ਖਾਲੀ)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *ਚੌਖਟਾ;
    size_t ਮਾਪ;

    /* av_mastering_display_metadata_alloc */
    ਲਿਖੋ("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    ਜੇ (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        ਲਿਖੋ("alloc: OK\n");
        ਲਿਖੋ("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].ਅੰਕ,
               mdm->display_primaries[0][0].den,
               mdm->white_ਬਿੰਦੂ_2[0].ਅੰਕ, mdm->white_ਬਿੰਦੂ_2[0].den);
        ਲਿਖੋ("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.ਅੰਕ, mdm->min_luminance.den,
               mdm->max_luminance.ਅੰਕ, mdm->max_luminance.den);
        ਲਿਖੋ("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    ਲਿਖੋ("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_ਮਾਪ(&ਮਾਪ);
    ਜੇ (mdm) {
        ਲਿਖੋ("alloc_size: OK, size>0=%s\n", ਮਾਪ > 0 ? "yes" : "no");
        ਲਿਖੋ("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].ਅੰਕ,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("alloc_size: FAIL\n");
    }

    /* write and read back */
    ਲਿਖੋ("\nTesting write/read back\n");
    mdm = av_mastering_display_metadata_alloc();
    ਜੇ (mdm) {
        mdm->display_primaries[0][0] = (AVRational){ 34000, 50000 };
        mdm->display_primaries[0][1] = (AVRational){ 16000, 50000 };
        mdm->white_ਬਿੰਦੂ_2[0] = (AVRational){ 15635, 50000 };
        mdm->white_ਬਿੰਦੂ_2[1] = (AVRational){ 16450, 50000 };
        mdm->min_luminance = (AVRational){ 50, 10000 };
        mdm->max_luminance = (AVRational){ 10000000, 10000 };
        mdm->has_primaries = 1;
        mdm->has_luminance = 1;
        ਲਿਖੋ("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].ਅੰਕ,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].ਅੰਕ,
               mdm->display_primaries[0][1].den);
        ਲਿਖੋ("white_point=(%d/%d, %d/%d)\n",
               mdm->white_ਬਿੰਦੂ_2[0].ਅੰਕ, mdm->white_ਬਿੰਦੂ_2[0].den,
               mdm->white_ਬਿੰਦੂ_2[1].ਅੰਕ, mdm->white_ਬਿੰਦੂ_2[1].den);
        ਲਿਖੋ("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.ਅੰਕ, mdm->min_luminance.den,
               mdm->max_luminance.ਅੰਕ, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    ਲਿਖੋ("\nTesting av_mastering_display_metadata_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        mdm = av_mastering_display_metadata_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਜੇ (mdm) {
            ਲਿਖੋ("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].ਅੰਕ,
                   mdm->display_primaries[0][0].den);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("side_data: FAIL\n");
        }
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    /* av_content_light_metadata_alloc */
    ਲਿਖੋ("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&ਮਾਪ);
    ਜੇ (clm) {
        ਲਿਖੋ("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               ਮਾਪ > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        ਲਿਖੋ("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } ਨਹੀਂਤਾਂ {
        ਲਿਖੋ("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    ਲਿਖੋ("\nTesting av_content_light_metadata_create_side_data()\n");
    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        clm = av_content_light_metadata_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਜੇ (clm) {
            ਲਿਖੋ("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } ਨਹੀਂਤਾਂ {
            ਲਿਖੋ("side_data: FAIL\n");
        }
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    /* OOM paths via av_max_alloc */
    ਲਿਖੋ("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    ਲਿਖੋ("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_ਮਾਪ(&ਮਾਪ);
    ਲਿਖੋ("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&ਮਾਪ);
    ਲਿਖੋ("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);

    ਚੌਖਟਾ = av_ਚੌਖਟਾ_alloc();
    ਜੇ (ਚੌਖਟਾ) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਲਿਖੋ("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_ਅੰਕੜੇ(ਚੌਖਟਾ);
        ਲਿਖੋ("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ);
        av_ਚੌਖਟਾ_free(&ਚੌਖਟਾ);
    }

    ਵਾਪਸ 0;
}

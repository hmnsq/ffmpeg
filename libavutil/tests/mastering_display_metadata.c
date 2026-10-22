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

#ಅನ್ತರ್ಭಾವ <limits.h>
#ಅನ್ತರ್ಭಾವ <stdio.h>

#ಅನ್ತರ್ಭಾವ "libavutil/frame.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mastering_display_metadata.h"
#ಅನ್ತರ್ಭಾವ "libavutil/mem.h"

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಶೂನ್ಯ)
{
    AVMasteringDisplayMetadata *mdm;
    AVContentLightMetadata *clm;
    AVFrame *ಚೌಕಟ್ಟು;
    size_t ಗಾತ್ರ_2;

    /* av_mastering_display_metadata_alloc */
    ಬರೆ("Testing av_mastering_display_metadata_alloc()\n");
    mdm = av_mastering_display_metadata_alloc();
    ಆದರೆ (mdm) {
        /* verify defaults: all rationals should be {0, 1} */
        ಬರೆ("alloc: OK\n");
        ಬರೆ("defaults: primaries[0][0]=%d/%d, white_point[0]=%d/%d\n",
               mdm->display_primaries[0][0].ಅಂಕೆ,
               mdm->display_primaries[0][0].den,
               mdm->white_ಬಿಂದು_2[0].ಅಂಕೆ, mdm->white_ಬಿಂದು_2[0].den);
        ಬರೆ("defaults: min_lum=%d/%d, max_lum=%d/%d\n",
               mdm->min_luminance.ಅಂಕೆ, mdm->min_luminance.den,
               mdm->max_luminance.ಅಂಕೆ, mdm->max_luminance.den);
        ಬರೆ("defaults: has_primaries=%d, has_luminance=%d\n",
               mdm->has_primaries, mdm->has_luminance);
        av_free(mdm);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಬರೆ("alloc: FAIL\n");
    }

    /* av_mastering_display_metadata_alloc_size */
    ಬರೆ("\nTesting av_mastering_display_metadata_alloc_size()\n");
    mdm = av_mastering_display_metadata_alloc_ಗಾತ್ರ(&ಗಾತ್ರ_2);
    ಆದರೆ (mdm) {
        ಬರೆ("alloc_size: OK, size>0=%s\n", ಗಾತ್ರ_2 > 0 ? "yes" : "no");
        ಬರೆ("defaults: primaries[0][0]=%d/%d\n",
               mdm->display_primaries[0][0].ಅಂಕೆ,
               mdm->display_primaries[0][0].den);
        av_free(mdm);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಬರೆ("alloc_size: FAIL\n");
    }

    /* write and read back */
    ಬರೆ("\nTesting write/read back\n");
    mdm = av_mastering_display_metadata_alloc();
    ಆದರೆ (mdm) {
        mdm->display_primaries[0][0] = (AVRational){ 34000, 50000 };
        mdm->display_primaries[0][1] = (AVRational){ 16000, 50000 };
        mdm->white_ಬಿಂದು_2[0] = (AVRational){ 15635, 50000 };
        mdm->white_ಬಿಂದು_2[1] = (AVRational){ 16450, 50000 };
        mdm->min_luminance = (AVRational){ 50, 10000 };
        mdm->max_luminance = (AVRational){ 10000000, 10000 };
        mdm->has_primaries = 1;
        mdm->has_luminance = 1;
        ಬರೆ("primaries[0]=(%d/%d, %d/%d)\n",
               mdm->display_primaries[0][0].ಅಂಕೆ,
               mdm->display_primaries[0][0].den,
               mdm->display_primaries[0][1].ಅಂಕೆ,
               mdm->display_primaries[0][1].den);
        ಬರೆ("white_point=(%d/%d, %d/%d)\n",
               mdm->white_ಬಿಂದು_2[0].ಅಂಕೆ, mdm->white_ಬಿಂದು_2[0].den,
               mdm->white_ಬಿಂದು_2[1].ಅಂಕೆ, mdm->white_ಬಿಂದು_2[1].den);
        ಬರೆ("luminance: min=%d/%d max=%d/%d\n",
               mdm->min_luminance.ಅಂಕೆ, mdm->min_luminance.den,
               mdm->max_luminance.ಅಂಕೆ, mdm->max_luminance.den);
        av_free(mdm);
    }

    /* av_mastering_display_metadata_create_side_data */
    ಬರೆ("\nTesting av_mastering_display_metadata_create_side_data()\n");
    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        mdm = av_mastering_display_metadata_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಆದರೆ (mdm) {
            ಬರೆ("side_data: OK, defaults: primaries[0][0]=%d/%d\n",
                   mdm->display_primaries[0][0].ಅಂಕೆ,
                   mdm->display_primaries[0][0].den);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("side_data: FAIL\n");
        }
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    /* av_content_light_metadata_alloc */
    ಬರೆ("\nTesting av_content_light_metadata_alloc()\n");
    clm = av_content_light_metadata_alloc(&ಗಾತ್ರ_2);
    ಆದರೆ (clm) {
        ಬರೆ("alloc: OK, size>0=%s, MaxCLL=%u, MaxFALL=%u\n",
               ಗಾತ್ರ_2 > 0 ? "yes" : "no", clm->MaxCLL, clm->MaxFALL);
        clm->MaxCLL = 1000;
        clm->MaxFALL = 400;
        ಬರೆ("write: MaxCLL=%u, MaxFALL=%u\n", clm->MaxCLL, clm->MaxFALL);
        av_free(clm);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಬರೆ("alloc: FAIL\n");
    }

    /* av_content_light_metadata_create_side_data */
    ಬರೆ("\nTesting av_content_light_metadata_create_side_data()\n");
    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        clm = av_content_light_metadata_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಆದರೆ (clm) {
            ಬರೆ("side_data: OK, MaxCLL=%u\n", clm->MaxCLL);
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಬರೆ("side_data: FAIL\n");
        }
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    /* OOM paths via av_max_alloc */
    ಬರೆ("\nTesting OOM paths\n");
    av_max_alloc(1);
    mdm = av_mastering_display_metadata_alloc();
    ಬರೆ("mastering alloc OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    mdm = av_mastering_display_metadata_alloc_ಗಾತ್ರ(&ಗಾತ್ರ_2);
    ಬರೆ("mastering alloc_size OOM: %s\n", mdm ? "FAIL" : "OK");
    av_free(mdm);
    clm = av_content_light_metadata_alloc(&ಗಾತ್ರ_2);
    ಬರೆ("content alloc OOM: %s\n", clm ? "FAIL" : "OK");
    av_free(clm);
    av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);

    ಚೌಕಟ್ಟು = av_ಚೌಕಟ್ಟು_alloc();
    ಆದರೆ (ಚೌಕಟ್ಟು) {
        av_max_alloc(1);
        mdm = av_mastering_display_metadata_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಬರೆ("mastering side_data OOM: %s\n", mdm ? "FAIL" : "OK");
        clm = av_content_light_metadata_create_side_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟು);
        ಬರೆ("content side_data OOM: %s\n", clm ? "FAIL" : "OK");
        av_max_alloc(ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ);
        av_ಚೌಕಟ್ಟು_free(&ಚೌಕಟ್ಟು);
    }

    ಹಿಂತಿರುಗಿ 0;
}
